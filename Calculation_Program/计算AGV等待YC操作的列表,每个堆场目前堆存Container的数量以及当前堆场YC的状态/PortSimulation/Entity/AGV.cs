﻿using O2DESNet;
using O2DESNet.Standard;
using System.ComponentModel;
using System.Diagnostics;
using System.Linq;
using System.Xml.Linq;
using WSC_SimChallenge_2024_Net.Activity;
using WSC_SimChallenge_2024_Net.StrategyMaking;

namespace WSC_SimChallenge_2024_Net.PortSimulation.Entity
{
    public class AGV
    {
        public ControlPoint CurrentLocation;
        public Container LoadedContainer;
        public YardBlock TargetedYB;
        public QC TargetedQC;
        public double Speed = 4.5; //4.5 m/s
        public bool InDischarging;
        public string Id;
        public override string ToString()
        {
            return $"AGV[{Id}]";
        }

        public class BeingIdle : BaseActivity<AGV>
        {
            public List<Container> ContainersPending = new List<Container>();
            public DecisionMaker StrategyMaker = new DecisionMaker();
            public Default DefaultMaker = new Default();

            public BeingIdle(bool debugMode = false, int seed = 0) : base(nameof(BeingIdle), debugMode, seed)
            {
                _debugMode = PortSimModel.DebugofAGV;
                NeedExtTryFinish = true;
                TimeSpan = TimeSpan.Zero;
            }

            public override void AttemptToFinish(AGV agv)
            {
                if (_debugMode) Console.WriteLine($"{ClockTime.ToString("yyyy-MM-dd HH:mm:ss")}  AGV{ActivityName}.AttemptToFinish({agv})");
                if (CompletedList.Contains(agv) && NeedExtTryFinish && ReadyToFinishList.Contains(agv))// Message before entity
                {
                    Finish(agv);
                }
                else if (CompletedList.Contains(agv) && NeedExtTryFinish && !ReadyToFinishList.Contains(agv) &&
                    ContainersPending.Count > 0)// Entity before messsage, there are vessel waiting
                {
                    AGV selectedAGV = StrategyMaker.CustomeizedAllocatedAGVs(ContainersPending[0]);
                    selectedAGV = selectedAGV == null ? DefaultMaker.CustomeizedAllocatedAGVs(ContainersPending[0]) : selectedAGV;

                    selectedAGV.LoadedContainer = ContainersPending[0];
                    ContainersPending[0].AGVTaken = selectedAGV;
                    selectedAGV.InDischarging = ContainersPending[0].InDischarging;
                    ContainersPending.RemoveAt(0);

                    if (!selectedAGV.InDischarging)
                    {
                        QC qc = DefaultMaker.DetermineQC(selectedAGV.LoadedContainer);
                        selectedAGV.LoadedContainer.TargetQC = qc;
                        selectedAGV.TargetedQC = qc;
                    }

                    ReadyToDepartList.Add(selectedAGV);
                    Finish(selectedAGV);
                }
            }

            public override void TryFinish(Object obj)
            {
                if (_debugMode) Console.WriteLine($"{ClockTime.ToString("yyyy-MM-dd HH:mm:ss")}  {ActivityName}.TryFinish({obj})");
                Container? container = (obj is Container) ? (obj as Container) : null;
                if (container == null) { return; };
                ContainersPending.Add(container);

                AGV selectedAGV = StrategyMaker.CustomeizedAllocatedAGVs(ContainersPending[0]);
                selectedAGV = selectedAGV == null ? DefaultMaker.CustomeizedAllocatedAGVs(ContainersPending[0]) : selectedAGV;

                if (selectedAGV != null && CompletedList.Contains(selectedAGV))
                {
                    selectedAGV.LoadedContainer = ContainersPending[0];
                    ContainersPending[0].AGVTaken = selectedAGV;
                    selectedAGV.InDischarging = ContainersPending[0].InDischarging;
                    ContainersPending.RemoveAt(0);

                    if (!selectedAGV.InDischarging)
                    {
                        QC qc = DefaultMaker.DetermineQC(selectedAGV.LoadedContainer);
                        selectedAGV.LoadedContainer.TargetQC = qc;
                        selectedAGV.TargetedQC = qc;
                    }

                    ReadyToFinishList.Add(selectedAGV);
                    AttemptToFinish(selectedAGV);
                }
            }
        }

        public class Picking : BaseActivity<AGV>
        {
            public Picking(bool debugMode = false, int seed = 0) : base(nameof(Picking), debugMode, seed)
            {
                _debugMode = PortSimModel.DebugofAGV;
            }

            public override void Start(AGV agv)
            {
                if (_debugMode) Console.WriteLine($"{ClockTime.ToString("yyyy-MM-dd HH:mm:ss")}  {ActivityName}.Start({agv})");
                HourCounter.ObserveChange(1);
                ProcessingList.Add(agv);
                PendingList.Remove(agv);
                ReadyToStartList.Remove(agv);
                TimeSpan = TimeSpan.FromSeconds(CalculateDistance(agv.CurrentLocation, agv.LoadedContainer.CurrentLocation) / agv.Speed);// Customized TimeSpan
                Schedule(() => Complete(agv), TimeSpan);
                EmitOnStart(agv);
            }

            public override void Depart(AGV agv)
            {
                if (ReadyToDepartList.Contains(agv))
                {
                    if (_debugMode) Console.WriteLine($"{ClockTime.ToString("yyyy-MM-dd HH:mm:ss")}  {ActivityName}.Depart({agv})");
                    HourCounter.ObserveChange(-1);
                    ReadyToDepartList.Remove(agv);
                    agv.CurrentLocation = agv.LoadedContainer.CurrentLocation;
                    AttemptToStart();
                }
            }
        }

        public class DeliveringtoYard : BaseActivity<AGV>
        {
            public DecisionMaker StrategyMaker = new DecisionMaker();
            public Default DefaultMaker = new Default();
            public DeliveringtoYard(bool debugMode = false, int seed = 0) : base(nameof(DeliveringtoYard), debugMode, seed)
            {
                _debugMode = PortSimModel.DebugofAGV;
            }


            public override void Start(AGV agv)
            {
                if (_debugMode) Console.WriteLine($"{ClockTime.ToString("yyyy-MM-dd HH:mm:ss")}  {ActivityName}.Start({agv})");
                YardBlock block = StrategyMaker.CustomeizedDetermineYardBlock(agv);
                block = block == null ? DefaultMaker.CustomeizedDetermineYardBlock(agv) : block;
                block.ReserveSlot();
                agv.TargetedYB = block;
                agv.LoadedContainer.BlockStacked = block;
                HourCounter.ObserveChange(1);
                ProcessingList.Add(agv);
                PendingList.Remove(agv);
                ReadyToStartList.Remove(agv);
                TimeSpan = TimeSpan.FromSeconds(CalculateDistance(agv.CurrentLocation, agv.TargetedYB.CP) / agv.Speed);// Customized TimeSpan
                Schedule(() => Complete(agv), TimeSpan);
                EmitOnStart(agv);
            }
        }

        public class HoldingatYard : BaseActivity<AGV>
        {
            public List<Container> ContainersPending = new List<Container>();
            public HoldingatYard(bool debugMode = false, int seed = 0) : base(nameof(HoldingatYard), debugMode, seed)
            {
                _debugMode = PortSimModel.DebugofAGV;
                NeedExtTryFinish = true;
                TimeSpan = TimeSpan.Zero;
            }
            public override void Start(AGV load)
            {
                if (_debugMode) Console.WriteLine($"{ClockTime.ToString("yyyy-MM-dd HH:mm:ss")}  {ActivityName}.Start({load})");
                HourCounter.ObserveChange(1);
                ProcessingList.Add(load);
                PendingList.Remove(load);
                ReadyToStartList.Remove(load);
                Schedule(() => Complete(load), TimeSpan);
                EmitOnStart(load);
                if (!load.TargetedYB.agvs.Contains((load, 1))) load.TargetedYB.agvs.Add((load, 1));
            }
            public override void AttemptToFinish(AGV agv)
            {
                if (_debugMode) Console.WriteLine($"{ClockTime.ToString("yyyy-MM-dd HH:mm:ss")}  {ActivityName}.AttemptToFinish({agv})");
                if (CompletedList.Contains(agv) && NeedExtTryFinish && ReadyToFinishList.Contains(agv))// Message before entity
                {
                    Finish(agv);
                }
                else if (CompletedList.Contains(agv) && NeedExtTryFinish && !ReadyToFinishList.Contains(agv) &&
                    ContainersPending.Count > 0)// Entity before messsage, there are AGVs waiting
                {
                    if (ContainersPending.Contains(agv.LoadedContainer))
                    {
                        ContainersPending.Remove(agv.LoadedContainer);
                        if (agv.TargetedYB.agvs.Contains((agv, 1))) agv.TargetedYB.agvs.Remove((agv, 1));
                        agv.LoadedContainer.CurrentLocation = agv.TargetedYB.CP;
                        //Update AGV's dynamics
                        agv.CurrentLocation = agv.TargetedYB.CP;
                        agv.LoadedContainer = null;
                        agv.TargetedYB = null;
                        agv.InDischarging = false;
                        ReadyToFinishList.Add(agv);

                        Finish(agv);
                    }
                    else 
                    {
                        Console.WriteLine($"Error：{ClockTime.ToString("yyyy-MM-dd HH:mm:ss")}  {ActivityName}.TryFinish({agv}): we don't find the determined container for unloading");
                    }
                }
            }

            public override void TryFinish(Object obj)
            {
                if (_debugMode) Console.WriteLine($"{ClockTime.ToString("yyyy-MM-dd HH:mm:ss")}  {ActivityName}.TryFinish({obj})");

                Container? container = (obj is Container) ? (obj as Container) : null;
                if (container == null) { return; };
                ContainersPending.Add(container);

                AGV agv = CompletedList.Find(a => a.LoadedContainer == container);
                if (agv != null)
                {
                    ContainersPending.Remove(container);
                    container.BlockStacked = agv.TargetedYB;
                    //Update AGV's dynamics
                    if (agv.TargetedYB.agvs.Contains((agv, 1))) agv.TargetedYB.agvs.Remove((agv, 1));
                    agv.CurrentLocation = agv.TargetedYB.CP;
                    agv.LoadedContainer = null;
                    agv.TargetedYB = null;
                    agv.InDischarging = false;
                    ReadyToFinishList.Add(agv);

                    AttemptToFinish(agv);
                }
            }
        }

        public class DeliveringtoQuaySide : BaseActivity<AGV>
        {
            List<YC> YCPendingList = new List<YC>();
            public DeliveringtoQuaySide(bool debugMode = false, int seed = 0) : base(nameof(DeliveringtoQuaySide), debugMode, seed)
            {
                _debugMode = PortSimModel.DebugofAGV;
                NeedExtTryStart = true;
            }
            public override void RequestToStart(AGV load)
            {
                if (_debugMode) Console.WriteLine($"{ClockTime.ToString("yyyy-MM-dd HH:mm:ss")}  {ActivityName}.RequestToStart({load})");
                PendingList.Add(load);
                if (!load.LoadedContainer.BlockStacked.agvs.Contains((load, 2))) load.LoadedContainer.BlockStacked.agvs.Add((load, 2));
                Schedule(() => AttemptToStart(), TimeSpan.FromMicroseconds(1));
            }
            public override void AttemptToStart() // function without parameters: Get the 1st eligible one in PendingList
            {
                if (_debugMode) Console.WriteLine($"{ClockTime.ToString("yyyy-MM-dd HH:mm:ss")}  {ActivityName}.AttemptToStart()");
                if (PendingList.Count > 0 && CapacityOccupied < Capacity)
                {
                    for (int i = 0; i < PendingList.Count; i++)
                    {
                        if (ReadyToStartList.Contains(PendingList[i]))
                        {
                            Start(PendingList[i]);
                            break;
                        }
                        else if (!ReadyToStartList.Contains(PendingList[i]) &&
                            YCPendingList.Any(yc => yc.HeldContainer == PendingList[i].LoadedContainer))
                        {
                            YC yc = YCPendingList.Find(yc => yc.HeldContainer == PendingList[i].LoadedContainer);
                            YCPendingList.Remove(yc);
                            if (PendingList[i].LoadedContainer.BlockStacked.agvs.Contains((PendingList[i], 2))) PendingList[i].LoadedContainer.BlockStacked.agvs.Remove((PendingList[i], 2));
                            Start(PendingList[i]);
                            break;
                        }
                    }
                }
            }

            public override void TryStart(Object obj)
            {
                if (_debugMode) Console.WriteLine($"{ClockTime.ToString("yyyy-MM-dd HH:mm:ss")}  {ActivityName}.TryStart({obj})");

                YC? yc = (obj is YC) ? (obj as YC) : null;
                YCPendingList.Add(yc);

                AGV agv = PendingList.Find(agv => yc.HeldContainer == agv.LoadedContainer);
                if (agv != null)
                {
                    if (agv.LoadedContainer.BlockStacked.agvs.Contains((agv, 2))) agv.LoadedContainer.BlockStacked.agvs.Remove((agv, 2));
                    YCPendingList.Remove(yc);
                    ReadyToStartList.Add(agv);
                    AttemptToStart();
                }
            }

            public override void Start(AGV agv)
            {
                if (_debugMode) Console.WriteLine($"{ClockTime.ToString("yyyy-MM-dd HH:mm:ss")}  {ActivityName}.Start({agv})");

                HourCounter.ObserveChange(1);
                ProcessingList.Add(agv);
                PendingList.Remove(agv);
                ReadyToStartList.Remove(agv);
                TimeSpan = TimeSpan.FromSeconds(CalculateDistance(agv.CurrentLocation, agv.TargetedQC.CP) / agv.Speed);// Customized TimeSpan
                Schedule(() => Complete(agv), TimeSpan);
                EmitOnStart(agv);
            }
        }

        public class HoldingatQuaySide : BaseActivity<AGV>
        {
            public List<Container> ContainersPending = new List<Container>();
            public HoldingatQuaySide(bool debugMode = false, int seed = 0) : base(nameof(HoldingatQuaySide), debugMode, seed)
            {
                _debugMode = PortSimModel.DebugofAGV;
                NeedExtTryFinish = true;
                TimeSpan = TimeSpan.Zero;
            }

            public override void Start(AGV agv)
            {
                if (_debugMode) Console.WriteLine($"{ClockTime.ToString("yyyy-MM-dd HH:mm:ss")}  {ActivityName}.Start({agv})");
                HourCounter.ObserveChange(1);
                ProcessingList.Add(agv);
                PendingList.Remove(agv);
                ReadyToStartList.Remove(agv);
                Schedule(() => Complete(agv), TimeSpan);
                EmitOnStart(agv);
            }

            public override void AttemptToFinish(AGV agv)
            {
                if (_debugMode) Console.WriteLine($"{ClockTime.ToString("yyyy-MM-dd HH:mm:ss")}  {ActivityName}.AttemptToFinish({agv})");
                if (CompletedList.Contains(agv) && NeedExtTryFinish && ReadyToFinishList.Contains(agv))// Message before entity
                {
                    Finish(agv);
                }
                else if (CompletedList.Contains(agv) && NeedExtTryFinish && !ReadyToFinishList.Contains(agv) &&
                    ContainersPending.Count > 0)// Entity before messsage, there are AGVs waiting
                {
                    ContainersPending.Remove(agv.LoadedContainer);
                    //Update AGV's dynamics
                    agv.CurrentLocation = agv.TargetedQC.CP;
                    agv.LoadedContainer = null;
                    agv.TargetedQC = null;
                    agv.InDischarging = false;
                    ReadyToFinishList.Add(agv);

                    Finish(agv);
                }
            }

            public override void TryFinish(Object obj)
            {
                if (_debugMode) Console.WriteLine($"{ClockTime.ToString("yyyy-MM-dd HH:mm:ss")}  {ActivityName}.TryFinish({obj})");

                Container? container = (obj is Container) ? (obj as Container) : null;
                if (container == null) { return; };
                ContainersPending.Add(container);

                AGV agv = CompletedList.Find(a => a.LoadedContainer == container);
                if (agv != null)
                {
                    ContainersPending.Remove(container);
                    //Update AGV's dynamics
                    agv.CurrentLocation = agv.TargetedQC.CP;
                    agv.LoadedContainer = null;
                    agv.TargetedQC = null;
                    agv.InDischarging = false;
                    ReadyToFinishList.Add(agv);

                    AttemptToFinish(agv);
                }
            }
        }

        public static ControlPoint LeftNetworkCP = new ControlPoint {Id = "Left Network Control point", Xcoordinate = 0, Ycoordinate = 100};
        public static ControlPoint RightNetworkCP = new ControlPoint { Id = "Right Network Control point", Xcoordinate = 1600, Ycoordinate = 100};
        public static double CalculateDistance(ControlPoint cp1, ControlPoint cp2)
        {
            double distance = 0;
            if (Math.Abs(cp1.Ycoordinate - cp2.Ycoordinate) > 100)//travel between quayside and second row YC
            {
                double leftRouteDistance = ManhattanDistance(cp1, LeftNetworkCP) + ManhattanDistance(LeftNetworkCP, cp2);
                double rightRouteDistance = ManhattanDistance(cp1, RightNetworkCP) + ManhattanDistance(RightNetworkCP, cp2);

                distance = Math.Min(leftRouteDistance, rightRouteDistance);
            }
            else
                distance = ManhattanDistance(cp1, cp2);

            return distance;
        }

        public static double ManhattanDistance(ControlPoint cp1, ControlPoint cp2)
        {
            return Math.Abs(cp1.Ycoordinate - cp2.Ycoordinate) + Math.Abs(cp1.Xcoordinate - cp2.Xcoordinate);
        }
    }
}
