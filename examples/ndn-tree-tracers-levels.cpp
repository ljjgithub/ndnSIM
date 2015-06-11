/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/**
 * Copyright (c) 2011-2015  Regents of the University of California.
 *
 * This file is part of ndnSIM. See AUTHORS for complete list of ndnSIM authors and
 * contributors.
 *
 * ndnSIM is free software: you can redistribute it and/or modify it under the terms
 * of the GNU General Public License as published by the Free Software Foundation,
 * either version 3 of the License, or (at your option) any later version.
 *
 * ndnSIM is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 * PURPOSE.  See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * ndnSIM, e.g., in COPYING.md file.  If not, see <http://www.gnu.org/licenses/>.
 **/

// ndn-tree-tracers-levels.cpp

#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/ndnSIM-module.h"
#include<cstring>

namespace ns3 {

/**
 * This scenario simulates a tree topology (using topology reader module)
 *
 *
 * To run scenario and see what is happening, use the following command:
 *
 *     ./waf --run=ndn-tree-tracers-levels
 */

std::string getNodePrefix(std::string s)
{
  std::string outs = "/";
  int index=0;
  while(index<s.length()&&s.find('-',index)!=std::string::npos)
  {
    outs+=s.substr(index,s.find('-',index)-index);
    index=s.find('-',index)+1;
    outs+="/";
  }
  if(index<s.length())
  {
    outs+=s.substr(index,s.length()-index);
  }
  //std::cout<<outs<<endl;
  return outs;
}

int
main(int argc, char* argv[])
{
  CommandLine cmd;
  cmd.Parse(argc, argv);

  AnnotatedTopologyReader topologyReader("", 1);
  topologyReader.SetFileName("src/ndnSIM/examples/topologies/topo-tree-levels.txt");
  topologyReader.Read();

  // Install NDN stack on all nodes
  ndn::StackHelper ndnHelper;
  ndnHelper.InstallAll();

  // Choosing forwarding strategy
  ndn::StrategyChoiceHelper::InstallAll("/prefix", "/localhost/nfd/strategy/best-route");

  // Installing global routing interface on all nodes
  ndn::GlobalRoutingHelper ndnGlobalRoutingHelper;
  ndnGlobalRoutingHelper.InstallAll();

  // Getting containers for the consumer/producer
  Ptr<Node> consumers[4] = {
Names::Find<Node>("root"),
Names::Find<Node>("root-build0"), Names::Find<Node>("root-build1"), Names::Find<Node>("root-build2")
         };
  Ptr<Node> producers[15] = {
Names::Find<Node>("root-build0-floor0-room0"), Names::Find<Node>("root-build0-floor0-room1"), Names::Find<Node>("root-build0-floor1-room0"), 
Names::Find<Node>("root-build0-floor2-room0"), Names::Find<Node>("root-build0-floor3-room0"), Names::Find<Node>("root-build1-floor0-room0"), 
Names::Find<Node>("root-build1-floor1-room0"), Names::Find<Node>("root-build1-floor1-room1"), Names::Find<Node>("root-build1-floor2-room0"), 
Names::Find<Node>("root-build2-floor0-room0"), Names::Find<Node>("root-build2-floor1-room0"), Names::Find<Node>("root-build2-floor2-room0"), 
Names::Find<Node>("root-build2-floor2-room1"), Names::Find<Node>("root-build2-floor2-room2"), Names::Find<Node>("root-build2-floor3-room0")
         };

  for (int i = 0; i < 4; i++) {
    ndn::AppHelper consumerHelper("ns3::ndn::ConsumerCbr");
    consumerHelper.SetAttribute("Frequency", StringValue("100")); // 100 interests a second

    consumerHelper.SetPrefix(getNodePrefix(Names::FindName(producers[i*2])));
    consumerHelper.Install(consumers[i]);
  }

  for (int i = 0; i < 15; i++) {
    ndn::AppHelper producerHelper("ns3::ndn::Producer");
    producerHelper.SetAttribute("PayloadSize", StringValue("1024"));

    ndnGlobalRoutingHelper.AddOrigins(getNodePrefix(Names::FindName(producers[i])), producers[i]);
    producerHelper.SetPrefix(getNodePrefix(Names::FindName(producers[i])));
    producerHelper.Install(producers[i]);
  }

  // Calculate and install FIBs
  ndn::GlobalRoutingHelper::CalculateRoutes();

  Simulator::Stop(Seconds(20.0));

  ndn::L3RateTracer::InstallAll("rate-trace.txt", Seconds(0.5));

  Simulator::Run();
  Simulator::Destroy();

  return 0;
}

} // namespace ns3

int
main(int argc, char* argv[])
{
  return ns3::main(argc, argv);
}
