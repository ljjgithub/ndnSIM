/* -*-  Mode: C++; c-file-style: "gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2011 University of California, Los Angeles
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Author: Ilya Moiseenko <iliamo@cs.ucla.edu>
 */

#include "ns3/node.h"
#include "ns3/node-list.h"
#include "ns3/simulator.h"
#include "ns3/ccnx-forwarding-strategy.h"
#include "ns3/ccnx-bestroute-strategy.h"
#include "ccnx-forwarding-helper.h"

namespace ns3 {

CcnxForwardingHelper::CcnxForwardingHelper()
{
    m_strategy = Ccnx::NDN_FLOODING;
}
    
CcnxForwardingHelper::CcnxForwardingHelper (Ccnx::ForwardingStrategy strategy)
{
    m_strategy = strategy;
}

void 
CcnxForwardingHelper::SetForwarding (Ptr<Ccnx> ccnx) const
{
    if(m_strategy == Ccnx::NDN_FLOODING)
    {
        Ptr<CcnxFloodingStrategy> ccnxForwarding = CreateObject<CcnxFloodingStrategy> ();
        ccnx->SetForwardingStrategy (ccnxForwarding);
    }
    else if(m_strategy == Ccnx::NDN_BESTROUTE)
    {
        Ptr<CcnxBestRouteStrategy> ccnxForwarding = CreateObject<CcnxBestRouteStrategy> ();
        ccnx->SetForwardingStrategy (ccnxForwarding);
    }
    else if (m_strategy == Ccnx::NDN_RANKING)
    {}
}

// void
// CcnxForwardingHelper::PrintForwardingTableAllAt (Time printTime, Ptr<OutputStreamWrapper> stream) const
// {
//   for (uint32_t i = 0; i < NodeList::GetNNodes (); i++)
//     {
//       Ptr<Node> node = NodeList::GetNode (i);
//       Simulator::Schedule (printTime, &CcnxForwardingHelper::Print, this, node, stream);
//     }
// }

// void
// CcnxForwardingHelper::PrintForwardingTableAllEvery (Time printInterval, Ptr<OutputStreamWrapper> stream) const
// {
//   for (uint32_t i = 0; i < NodeList::GetNNodes (); i++)
//     {
//       Ptr<Node> node = NodeList::GetNode (i);
//       Simulator::Schedule (printInterval, &CcnxForwardingHelper::PrintEvery, this, printInterval, node, stream);
//     }
// }

// void
// CcnxForwardingHelper::PrintForwardingTableAt (Time printTime, Ptr<Node> node, Ptr<OutputStreamWrapper> stream) const
// {
//   Simulator::Schedule (printTime, &CcnxForwardingHelper::Print, this, node, stream);
// }

// void
// CcnxForwardingHelper::PrintForwardingTableEvery (Time printInterval,Ptr<Node> node, Ptr<OutputStreamWrapper> stream) const
// {
//   Simulator::Schedule (printInterval, &CcnxForwardingHelper::PrintEvery, this, printInterval, node, stream);
// }

// void
// CcnxForwardingHelper::Print (Ptr<Node> node, Ptr<OutputStreamWrapper> stream) const
// {
//   Ptr<Ccnx> ccnx = node->GetObject<Ccnx> ();
//   Ptr<CcnxForwardingStrategy> rp = ccnx->GetForwardingStrategy ();
//   NS_ASSERT (rp);
//   rp->PrintForwardingTable (stream);
// }

// void
// CcnxForwardingHelper::PrintEvery (Time printInterval, Ptr<Node> node, Ptr<OutputStreamWrapper> stream) const
// {
//   Ptr<Ccnx> ccnx = node->GetObject<Ccnx> ();
//   Ptr<CcnxForwardingStrategy> rp = ccnx->GetForwardingStrategy ();
//   NS_ASSERT (rp);
//   rp->PrintForwardingTable (stream);
//   Simulator::Schedule (printInterval, &CcnxForwardingHelper::PrintEvery, this, printInterval, node, stream);
// }

} // namespace ns3
