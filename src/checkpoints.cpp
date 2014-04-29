// Copyright (c) 2009-2012 The Bitcoin developers
// Copyright (c) 2011-2012 Litecoin Developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <boost/assign/list_of.hpp> // for 'map_list_of()'
#include <boost/foreach.hpp>

#include "checkpoints.h"

#include "main.h"
#include "uint256.h"

namespace Checkpoints
{
    typedef std::map<int, uint256> MapCheckpoints;

    //
    // What makes a good checkpoint block?
    // Ask a coin developer.
    //   
    //   
    //
    static MapCheckpoints mapCheckpoints =
        boost::assign::map_list_of // TODO: needs to adjusted for checkpoint checks, also see main.cpp
         (	  0, uint256("0x499c271e5fafbe06c3b7262133eb1838e1ab3b529998a5ca00bc0167bb5a417e"))

         (  8603, uint256("0x07a977e5f2c175e088843d341d7264cb92d6d0ebee7dddaf2a457382dab987a0"))
         
		 ( 26882, uint256("0xc1c0a0322b3170ea2062a08aec22c8409176a9b8a20f8c5e3bf5a1ecfecc323d"))
            
		 (  51323, uint256("0xbab45304c24fb95479c56ef54368b8b08fdcaa1d1d868b168bbfbd82097f5ae8"))
	
      	 (  59010, uint256("0x0468792facee5daf02c3d73fa4b9db612ccb888c0d2c4251f4ca7050b7f9cb91"))

		
		;
      

     bool CheckBlock(int nHeight, const uint256& hash)
    {
        if (fTestNet) return true; // Testnet has no checkpoints

        MapCheckpoints::const_iterator i = mapCheckpoints.find(nHeight);
        if (i == mapCheckpoints.end()) return true;
        return hash == i->second;
    }

    int GetTotalBlocksEstimate()
    {
        if (fTestNet) return 0;
        return mapCheckpoints.rbegin()->first;
    }

    CBlockIndex* GetLastCheckpoint(const std::map<uint256, CBlockIndex*>& mapBlockIndex)
    {
        if (fTestNet) return NULL;

        BOOST_REVERSE_FOREACH(const MapCheckpoints::value_type& i, mapCheckpoints)
        {
            const uint256& hash = i.second;
            std::map<uint256, CBlockIndex*>::const_iterator t = mapBlockIndex.find(hash);
            if (t != mapBlockIndex.end())
                return t->second;
        }
        return NULL;
    }
}
