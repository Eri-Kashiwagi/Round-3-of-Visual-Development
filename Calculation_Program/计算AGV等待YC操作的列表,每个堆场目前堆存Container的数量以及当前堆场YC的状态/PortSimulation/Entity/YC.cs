﻿using O2DESNet;
using System.ComponentModel;
using System.Drawing;
using WSC_SimChallenge_2024_Net.Activity;

namespace WSC_SimChallenge_2024_Net.PortSimulation.Entity
{
    public class YC
    {
        public string Id;
        public ControlPoint CP;
        public YardBlock ServedBlock;
        public Container HeldContainer;
        public string status;
        public override string ToString()
        {
            return $"YC[{Id}]";
        }

        public class Repositioning : BaseActivity<YC>
        {
            public void ReBeingIdleYC(YC yc) { yc.HeldContainer = null;}
            public List<Container> ConatinerPendingList = new List<Container>();

            public Repositioning(bool debugMode = false, int seed = 0) : base(nameof(Repositioning), debugMode, seed)
            {
                _debugMode = PortSimModel.DebugofYC;
                NeedExtTryFinish = true;
                TimeSpan = TimeSpan.Zero;
            }
            override public void Start(YC load)
            {
                if (_debugMode) Console.WriteLine($"{ClockTime.ToString("yyyy-MM-dd HH:mm:ss")}  {ActivityName}.Start({load})");
                HourCounter.ObserveChange(1);
                ProcessingList.Add(load);
                PendingList.Remove(load);
                ReadyToStartList.Remove(load);
                load.status = "YC";
                Schedule(() => Complete(load), TimeSpan);
                EmitOnStart(load);
            }
            public override void AttemptToFinish(YC yc)
            {
                if (_debugMode) Console.WriteLine($"{ClockTime.ToString("yyyy-MM-dd HH:mm:ss")}  {ActivityName}.AttemptToFinish({yc})");
                if (CompletedList.Contains(yc) && NeedExtTryFinish && ReadyToFinishList.Contains(yc))// Message before entity
                {
                    Finish(yc);
                }
                else if (CompletedList.Contains(yc) && NeedExtTryFinish && !ReadyToFinishList.Contains(yc) &&
                    ConatinerPendingList.Any(c => c.BlockStacked == yc.ServedBlock))// Entity before messsage, there are vessel waiting
                {
                    Container container = ConatinerPendingList.Find(c => c.BlockStacked == yc.ServedBlock);
                    ConatinerPendingList.Remove(container);
                    yc.HeldContainer = container;
                    ReadyToFinishList.Add(yc);
                    Finish(yc);
                }
            }

            public override void TryFinish(Object obj)
            {
                if (_debugMode) Console.WriteLine($"{ClockTime.ToString("yyyy-MM-dd HH:mm:ss")}  {ActivityName}.TryFinish({obj})");

                Container? container = (obj is Container) ? (obj as Container) : null;
                AGV? agv = (obj is AGV) ? (obj as AGV) : null;

                if (container != null)
                    ConatinerPendingList.Add(container);
                else if (!agv.LoadedContainer.InDischarging)
                {
                    container = agv.LoadedContainer;
                    ConatinerPendingList.Add(container);
                }
                else { return; }

                YC yc = CompletedList.Find(y => y.ServedBlock == container.BlockStacked);
                Container priorityContainer = ConatinerPendingList.Find(c => c.BlockStacked == container.BlockStacked && !c.InDischarging);
                container = priorityContainer == null ? container : priorityContainer;
                if (yc != null)
                {
                    ConatinerPendingList.Remove(container);
                    yc.HeldContainer = container;
                    ReadyToFinishList.Add(yc);
                    AttemptToFinish(yc);
                }
            }
        }

        public class Picking : BaseActivity<YC>
        {
            public Picking(bool debugMode = false, int seed = 0) : base(nameof(Picking), debugMode, seed)
            {
                _debugMode = PortSimModel.DebugofYC;
                TimeSpan = TimeSpan.Zero;
            }
        }

        public class Stacking : BaseActivity<YC>
        {
            public Stacking(bool debugMode = false, int seed = 0) : base(nameof(Stacking), debugMode, seed)
            {
                _debugMode = PortSimModel.DebugofYC;
                TimeSpan = TimeSpan.FromSeconds(90);
            }
            override public void Start(YC load)
            {
                if (_debugMode) Console.WriteLine($"{ClockTime.ToString("yyyy-MM-dd HH:mm:ss")}  {ActivityName}.Start({load})");
                HourCounter.ObserveChange(1);
                ProcessingList.Add(load);
                PendingList.Remove(load);
                ReadyToStartList.Remove(load);
                load.status = "Stacking";
                Schedule(() => Complete(load), TimeSpan);
                EmitOnStart(load);
            }
        }

        public class Unstacking : BaseActivity<YC>
        {
            public Unstacking(bool debugMode = false, int seed = 0) : base(nameof(Unstacking), debugMode, seed)
            {
                _debugMode = PortSimModel.DebugofYC;
                TimeSpan = TimeSpan.FromSeconds(90);
            }
            override public void Start(YC load)
            {
                if (_debugMode) Console.WriteLine($"{ClockTime.ToString("yyyy-MM-dd HH:mm:ss")}  {ActivityName}.Start({load})");
                HourCounter.ObserveChange(1);
                ProcessingList.Add(load);
                PendingList.Remove(load);
                ReadyToStartList.Remove(load);
                load.status = "Unstacking";
                Schedule(() => Complete(load), TimeSpan);
                EmitOnStart(load);
            }
        }

        public class HoldingonUnstacking : BaseActivity<YC>
        {
            public List<Container> ConatinerPendingList = new List<Container>();
            public HoldingonUnstacking(bool debugMode = false, int seed = 0) : base(nameof(HoldingonUnstacking), debugMode, seed)
            {
                _debugMode = PortSimModel.DebugofYC;
                NeedExtTryFinish = true;
                TimeSpan = TimeSpan.Zero;
            }
            override public void Start(YC load)
            {
                if (_debugMode) Console.WriteLine($"{ClockTime.ToString("yyyy-MM-dd HH:mm:ss")}  {ActivityName}.Start({load})");
                HourCounter.ObserveChange(1);
                ProcessingList.Add(load);
                PendingList.Remove(load);
                ReadyToStartList.Remove(load);
                load.status = "HoldingonUnstacking";
                Schedule(() => Complete(load), TimeSpan);
                EmitOnStart(load);
            }
            public override void AttemptToFinish(YC yc)
            {
                if (_debugMode) Console.WriteLine($"{ClockTime.ToString("yyyy-MM-dd HH:mm:ss")}  {ActivityName}.AttemptToFinish({yc})");
                if (CompletedList.Contains(yc) && NeedExtTryFinish && ReadyToFinishList.Contains(yc))// Message before entity
                {
                    Finish(yc);
                }
                else if (CompletedList.Contains(yc) && NeedExtTryFinish && !ReadyToFinishList.Contains(yc) &&
                    ConatinerPendingList.Any(c => c == yc.HeldContainer))// Entity before messsage, there are vessel waiting
                {
                    Container container = ConatinerPendingList.Find(c => c == yc.HeldContainer);
                    ConatinerPendingList.Remove(container);
                    ReadyToFinishList.Add(yc);
                    Finish(yc);
                }
            }

            public override void TryFinish(Object obj)
            {
                if (_debugMode) Console.WriteLine($"{ClockTime.ToString("yyyy-MM-dd HH:mm:ss")}  {ActivityName}.TryFinish({obj})");

                Container? container = (obj is Container) ? (obj as Container) : null;
                if (container == null) { return; };
                ConatinerPendingList.Add(container);

                YC yc = CompletedList.Find(y => y.HeldContainer == container);
                if (yc != null)
                {
                    ConatinerPendingList.Remove(container);
                    ReadyToFinishList.Add(yc);
                    AttemptToFinish(yc);
                }
            }
        }
    }

    public class YardBlock   
    {
        public YC EquipedYC;
        public string Id;
        public List<Container> StackedContainers = new List<Container> ();
        public int ReservedSlots = 0;
        public int Capacity;
        public ControlPoint CP;
        public List<(AGV, int)> agvs = new List<(AGV, int)>();
        public int ContainerNum;
        public void ReserveSlot()
        {
            if (StackedContainers.Count + ReservedSlots < Capacity)
            {
                ReservedSlots += 1;
            }
            else{ Console.WriteLine($"Failed reserving slot at yardblock: {Id}, current status: stacked container number{StackedContainers.Count}," +
                $"ReservedSlots: {ReservedSlots}"); }
        }

        public void StackingContainer(Container container)
        {
            ReservedSlots -= 1;
            StackedContainers.Add(container);
        }

        public void UnstackingContainer(Container container)
        {
            StackedContainers.Remove(container);
        }
    }
}
