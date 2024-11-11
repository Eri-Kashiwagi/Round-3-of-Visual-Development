using WSC_SimChallenge_2024_Net.PortSimulation;
using System.ComponentModel;
using WSC_SimChallenge_2024_Net.PortSimulation.Entity;
using System;
using WSC_SimChallenge_2024_Net.StrategyMaking;
using MathNet.Numerics.Random;
using System.Threading;

namespace WSC_SimChallenge_2024_Net.PortSimulation
{
    class Simulation
    {
        public double Run(int runIndex, int seed)
        {
            Console.WriteLine(String.Concat(Enumerable.Repeat("*", 70)));
            Console.WriteLine($"Seed: {seed}, Scenario {runIndex}:");
            Console.WriteLine($"Simulation running...");

            PortSimModel WSCPort = new PortSimModel()
            {
                NumberofAGVs = 12 * 1,//Times of groups of vessels
                StartTime = new DateTime(2024, 5, 3, 0, 0, 0),
                ContainersInfoFileURL = "conf//transhipment" + runIndex.ToString() + ".csv",
                VesselArrivalTimesURL = "conf//vessel_arrival_time" + runIndex.ToString() + ".csv"
            };
            WSCPort.Initialize(seed);
            DecisionMaker WSCPortDecisionMaker = new DecisionMaker(WSCPort);
            WSCPort.berthBeingIdle.StrategyMaker = WSCPortDecisionMaker;
            WSCPort.agvBeingIdle.StrategyMaker = WSCPortDecisionMaker;
            WSCPort.agvDeliveringtoYard.StrategyMaker = WSCPortDecisionMaker;

            Default WSCPortDefaulter = new Default(WSCPort);
            WSCPort.berthBeingIdle.DefaultMaker = WSCPortDefaulter;
            WSCPort.agvBeingIdle.DefaultMaker = WSCPortDefaulter;
            WSCPort.agvDeliveringtoYard.DefaultMaker = WSCPortDefaulter;
            string currentDirectory = AppDomain.CurrentDomain.BaseDirectory;
            string parentDirectory = currentDirectory;
            for (int i = 0; i < 6; i++)
            {
                DirectoryInfo parentInfo = Directory.GetParent(parentDirectory);
                parentDirectory = parentInfo.FullName;
            }
            string calculatedDataDirectory = Path.Combine(parentDirectory, "Calculated_Data");
            for (int i = 1; i <= 70; i++)
            {
                string filePath = Path.Combine(calculatedDataDirectory, $"AGV_operation_and_its_container{i}.txt");

                using (StreamWriter writer = new StreamWriter(filePath))
                {
                    Console.SetOut(writer);
                    WSCPort.Run(TimeSpan.FromDays(1));
                }
            }
            Environment.Exit(0);
            for (int i = 0; i < WSCPort.Vessels.Count; i++)
            {
                if (WSCPort.Vessels[i].ArrivalTime != DateTime.MinValue && WSCPort.Vessels[i].StartBerthingTime == DateTime.MinValue)
                    WSCPort.Vessels[i].StartBerthingTime = WSCPort.ClockTime;
            }
            for (int i = 0; i < WSCPort.Vessels.Count; i++)
            {
                if (WSCPort.Vessels[i].ArrivalTime != DateTime.MinValue && WSCPort.Vessels[i].StartBerthingTime == DateTime.MinValue)
                    WSCPort.Vessels[i].StartBerthingTime = WSCPort.ClockTime;
            }
            int numofDelayedVessels = WSCPort.Vessels.FindAll(vessel => vessel.ArrivalTime != DateTime.MinValue && vessel.StartBerthingTime != DateTime.MinValue &&
            vessel.StartBerthingTime - vessel.ArrivalTime > TimeSpan.FromHours(2)).Count;
            int numofArrivalVessles = WSCPort.Vessels.FindAll(vessel => vessel.ArrivalTime != DateTime.MinValue).Count;
            double RateofDelayedVessels = (double)numofDelayedVessels / (double)numofArrivalVessles * 100;

            WSCPort.Run(TimeSpan.FromDays(300));//release containers by running additional time without discharging;  

            bool DischargingCondition = WSCPort.WarmUpweeks * WSCPort.containerBeingDischarged.Discharging == WSCPort.containerDwelling.CompletedList.Count * (WSCPort.RunningWeeks);
            bool LoadingCondition = WSCPort.WarmUpweeks * WSCPort.containerBeingLoaded.Loading == WSCPort.containerDwelling.CompletedList.Count * (WSCPort.RunningWeeks - WSCPort.WarmUpweeks);
            bool FlowCondition = WSCPort.containerBeingDischarged.Discharging - WSCPort.containerBeingLoaded.Loading == WSCPort.containerDwelling.CompletedList.Count;
            bool BerthCondition = WSCPort.NumberofBerths == WSCPort.berthBeingIdle.CompletedList.Count;
            bool VesselCondition = WSCPort.vesselWaiting.CompletedList.Count == 0;
            bool QCCondition = WSCPort.qcBeingIdle.CompletedList.Count == WSCPort.NumberofQCs;
            bool AGVCondition = WSCPort.NumberofAGVs == WSCPort.agvBeingIdle.CompletedList.Count;
            bool YCCondition = WSCPort.NumberofYCs == WSCPort.ycRepositioning.CompletedList.Count;

            if (DischargingCondition && LoadingCondition && FlowCondition && BerthCondition && VesselCondition && QCCondition && AGVCondition && YCCondition)
            {
                Console.WriteLine($"Seed: {seed}, Scenario {runIndex}:");
                Console.WriteLine($"Number of delayed vessels: {numofDelayedVessels}; Number of arrival vessels: {numofArrivalVessles}");
                Console.WriteLine($"Rate of delayed vessels: {(RateofDelayedVessels).ToString("0.00")} %");
                Console.WriteLine($"Simulation completed");
                Console.WriteLine(String.Concat(Enumerable.Repeat("*", 70)));

                Console.WriteLine("Debug Checking:");

                Console.WriteLine($"Discharging condition:{DischargingCondition}");
                Console.WriteLine($"Loading condition:{LoadingCondition}");
                Console.WriteLine($"Flow condition:{FlowCondition}");
                Console.WriteLine($"Berth condition:{BerthCondition}");
                Console.WriteLine($"Vessel condition:{VesselCondition}");
                Console.WriteLine($"QC condition:{QCCondition}");
                Console.WriteLine($"AGV condition:{AGVCondition}");
                Console.WriteLine($"YC condition:{YCCondition}");

                return RateofDelayedVessels;
            }
            else
            {
                return Run(runIndex, seed);
            }
        }
    }

    class Program
    {
        static readonly object lockObject = new object(); // Lock object for thread-safe operations on double
        static void Main(string[] args)
        {
            int[] Seeds = {73386, 77742, 18078};
            double TotalDelayedRate = 0;
            int NumofScenarios = 5;
            int MaxDegreeOfParallelism = 5; // Set your desired maximum parallelism here

            SemaphoreSlim semaphore = new SemaphoreSlim(MaxDegreeOfParallelism);
            bool Ifparallel = false;

            foreach (var seed in Seeds)
            {
                if (!Ifparallel)
                {
                    //option 1: no parallel 
                    for (int runIndex = 4; runIndex < NumofScenarios; runIndex++)
                    {
                        Simulation simulation = new Simulation();
                        double RateofDelayedVessels = simulation.Run(runIndex, seed);
                        TotalDelayedRate += RateofDelayedVessels;
                    }
                }
                else 
                {
                    //option 2: parallel 
                    Parallel.For(0, NumofScenarios, runIndex =>
                    {
                        semaphore.Wait(); // Wait for an available slot in the pool

                        try
                        {
                            Simulation simulation = new Simulation();
                            double RateofDelayedVessels = simulation.Run(runIndex, seed);

                            // Use lock to ensure thread-safe addition of double value
                            lock (lockObject)
                            {
                                TotalDelayedRate += RateofDelayedVessels;
                            }
                        }
                        finally
                        {
                            semaphore.Release(); // Release the semaphore slot after the task completes
                        }
                    });
                }

            }

            // Output the average rate of delayed vessels
            Console.WriteLine($"Average rate of delayed vessels: {(TotalDelayedRate / (NumofScenarios * Seeds.Length)).ToString("0.00")} %");
        }           
    }
}