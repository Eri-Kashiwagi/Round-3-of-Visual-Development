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
            string filePath1 = Path.Combine(parentDirectory, "Calculated_Data");
            filePath1 = Path.Combine(filePath1, "Berth_Vessel1.txt");
            using (StreamWriter writer = new StreamWriter(filePath1))
            {
                Console.SetOut(writer);
                WSCPort.Run(TimeSpan.FromDays(7 * WSCPort.RunningWeeks / 10));
            }

            string filePath2 = Path.Combine(parentDirectory, "Calculated_Data");
            filePath2 = Path.Combine(filePath2, "Berth_Vessel2.txt");
            using (StreamWriter writer = new StreamWriter(filePath2))
            {
                Console.SetOut(writer);
                WSCPort.Run(TimeSpan.FromDays(7 * WSCPort.RunningWeeks / 10));
            }

            string filePath3 = Path.Combine(parentDirectory, "Calculated_Data");
            filePath3 = Path.Combine(filePath3, "Berth_Vessel3.txt");
            using (StreamWriter writer = new StreamWriter(filePath3))
            {
                Console.SetOut(writer);
                WSCPort.Run(TimeSpan.FromDays(7 * WSCPort.RunningWeeks / 10));
            }

            string filePath4 = Path.Combine(parentDirectory, "Calculated_Data");
            filePath4 = Path.Combine(filePath4, "Berth_Vessel4.txt");
            using (StreamWriter writer = new StreamWriter(filePath4))
            {
                Console.SetOut(writer);
                WSCPort.Run(TimeSpan.FromDays(7 * WSCPort.RunningWeeks / 10));
            }

            string filePath5 = Path.Combine(parentDirectory, "Calculated_Data");
            filePath5 = Path.Combine(filePath5, "Berth_Vessel5.txt");
            using (StreamWriter writer = new StreamWriter(filePath5))
            {
                Console.SetOut(writer);
                WSCPort.Run(TimeSpan.FromDays(7 * WSCPort.RunningWeeks / 10));
            }

            string filePath6 = Path.Combine(parentDirectory, "Calculated_Data");
            filePath6 = Path.Combine(filePath6, "Berth_Vessel6.txt");
            using (StreamWriter writer = new StreamWriter(filePath6))
            {
                Console.SetOut(writer);
                WSCPort.Run(TimeSpan.FromDays(7 * WSCPort.RunningWeeks / 10));
            }

            string filePath7 = Path.Combine(parentDirectory, "Calculated_Data");
            filePath7 = Path.Combine(filePath7, "Berth_Vessel7.txt");
            using (StreamWriter writer = new StreamWriter(filePath7))
            {
                Console.SetOut(writer);
                WSCPort.Run(TimeSpan.FromDays(7 * WSCPort.RunningWeeks / 10));
            }

            string filePath8 = Path.Combine(parentDirectory, "Calculated_Data");
            filePath8 = Path.Combine(filePath8, "Berth_Vessel8.txt");
            using (StreamWriter writer = new StreamWriter(filePath8))
            {
                Console.SetOut(writer);
                WSCPort.Run(TimeSpan.FromDays(7 * WSCPort.RunningWeeks / 10));
            }

            string filePath9 = Path.Combine(parentDirectory, "Calculated_Data");
            filePath9 = Path.Combine(filePath9, "Berth_Vessel9.txt");
            using (StreamWriter writer = new StreamWriter(filePath9))
            {
                Console.SetOut(writer);
                WSCPort.Run(TimeSpan.FromDays(7 * WSCPort.RunningWeeks / 10));
            }

            string filePath10 = Path.Combine(parentDirectory, "Calculated_Data");
            filePath10 = Path.Combine(filePath10, "Berth_Vessel10.txt");
            using (StreamWriter writer = new StreamWriter(filePath10))
            {
                Console.SetOut(writer);
                WSCPort.Run(TimeSpan.FromDays(7 * WSCPort.RunningWeeks / 10));
            }
            Environment.Exit(0);
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
            int[] Seeds = {18078, 77742, 73386};
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
                    for (int runIndex = 0; runIndex < NumofScenarios; runIndex++)
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