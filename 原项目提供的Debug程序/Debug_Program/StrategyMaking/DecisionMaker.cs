using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using WSC_SimChallenge_2024_Net.PortSimulation.Entity;

namespace WSC_SimChallenge_2024_Net.PortSimulation
{
    public class DecisionMaker
    {
        public PortSimModel WSCPort { get; set; }        
        public Berth CustomeizedAllocatedBerth(Vessel arrivalVessel)
        {
            Berth allocatedBerth = null;

            return allocatedBerth;
        }

        public AGV CustomeizedAllocatedAGVs(Container container)
        {
            AGV allocatedAGV = null;

            return allocatedAGV;
        }

        public YardBlock CustomeizedDetermineYardBlock(AGV agv)
        {
            YardBlock yardBlock = null;

            return yardBlock;
        }

        public DecisionMaker(PortSimModel wSCPort)
        {
            WSCPort = wSCPort;
        }

        public DecisionMaker() { }
    }
}
