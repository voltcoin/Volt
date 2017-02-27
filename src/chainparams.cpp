// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "assert.h"

#include "chainparams.h"
#include "main.h"
#include "util.h"

#include <boost/assign/list_of.hpp>

using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

//
// Main network
//

// Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress> &vSeedsOut, const SeedSpec6 *data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7*24*60*60;
    for (unsigned int i = 0; i < count; i++)
    {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

class CMainParams : public CChainParams {
public:
    CMainParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0x12;
        pchMessageStart[1] = 0x69;
        pchMessageStart[2] = 0x51;
        pchMessageStart[3] = 0x22;
	vAlertPubKey = ParseHex("04c7a3c3caf4c5033fa564d07fe81f8773cbd7c937d04cf002e6db079b2881ef684cf58d57865527fa8f417c268915ef826c7a8d0e8f5ceefb18451191fbd891c9");
        nDefaultPort = 11516;
        nRPCPort = 15615;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 20);

        // Build the genesis block. Note that the output of the genesis coinbase cannot
        // be spent as it did not originally exist in the database.
        //
	// CBlock(hash=000009b88ae01c8e009d08651c904a1b00f9e24d72538f49c242ba2ee14d859a, ver=1, pow_hash=000009b88ae01c8e009d08651c904a1b00f9e24d72538f49c242ba2ee14d859a, hashPrevBlock=0000000000000000000000000000000000000000000000000000000000000000, hashMerkleRoot=f13219df992036c16529305d015d11fe84ee11550d060bfed7a8cc58951040c4, nTime=1450199185, nBits=1e0fffff, nNonce=921682, vtx=1)
  	//  Coinbase(hash=f13219df992036c16529305d015d11fe84ee11550d060bfed7a8cc58951040c4, nTime=1393221600, ver=1, vin.size=1, vout.size=1, nLockTime=0)
    	//   CTxIn(COutPoint(0000000000, 4294967295), coinbase 00012a15477265656e436f696e5632204c61756e636865732e)
    	//   CTxOut(empty)
  	//  vMerkleTree: f13219df992036c16529305d015d11fe84ee11550d060bfed7a8cc58951040c4

        const char* pszTimestamp = "Volta 18 February 1745";
        std::vector<CTxIn> vin;
        vin.resize(1);
        vin[0].scriptSig = CScript() << 0 << CBigNum(42) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        std::vector<CTxOut> vout;
        vout.resize(1);
        vout[0].SetEmpty();
        CTransaction txNew(1, 1393221600, vin, vout, 0);
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1488068390;
        genesis.nBits    = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce   = 2388982;
        nLastPoWBlock    = 150;



 

    hashGenesisBlock = genesis.GetHash();

  assert(hashGenesisBlock == uint256("0x0000038be9d28a7189fdfbd10e2c05fa51e555430da4967b03dcd374ee1ba9ec"));
       assert(genesis.hashMerkleRoot == uint256("0x242b1c907adfeb7f879da9308856c3564b483eac01e5813284b94c22dfa95973"));


	vSeeds.push_back(CDNSSeedData("198.211.126.38", "198.211.126.38"));

        base58Prefixes[PUBKEY_ADDRESS] = list_of(70); // V
        base58Prefixes[SCRIPT_ADDRESS] = list_of(85);
        base58Prefixes[SECRET_KEY] =     list_of(166);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x88)(0xB2)(0x1E);
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x88)(0xAD)(0xE4);
        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));
    }

    virtual const CBlock& GenesisBlock() const { return genesis; }
    virtual Network NetworkID() const { return CChainParams::MAIN; }

    virtual const vector<CAddress>& FixedSeeds() const {
        return vFixedSeeds;
    }
protected:
    CBlock genesis;
    vector<CAddress> vFixedSeeds;
};
static CMainParams mainParams;


//
// Testnet
//

class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0x12;
        pchMessageStart[1] = 0x0b;
        pchMessageStart[2] = 0x1e;
        pchMessageStart[3] = 0xbc;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);
        vAlertPubKey = ParseHex("047ace9689d8c7e7ed1c2adbe036b74e1c2cf81401923ced52c5125eac694e8eef1eb129275d6e313d939a36aa0bbb661532da6d3b7f2aad562efde1d4834741c6");
        nDefaultPort = 25723;
        nRPCPort = 25722;
        strDataDir = "testnet";
	// CBlock(has286770h=00003845b6cba6a72017f62f5299ecfbb832a4675082543d2db1e091b37a4b80, ver=1, pow_hash=00003845b6cba6a72017f62f5299ecfbb832a4675082543d2db1e091b37a4b80, hashPrevBlock=0000000000000000000000000000000000000000000000000000000000000000, hashMerkleRoot=f13219df992036c16529305d015d11fe84ee11550d060bfed7a8cc58951040c4, nTime=1450199186, nBits=1f00ffff, nNonce=57246, vtx=1)
  	//  Coinbase(hash=f13219df992036c16529305d015d11fe84ee11550d060bfed7a8cc58951040c4, nTime=1393221600, ver=1, vin.size=1, vout.size=1, nLockTime=0)
    	//    CTxIn(COutPoint(0000000000, 4294967295), coinbase 00012a15477265656e436f696e5632204c61756e636865732e)
    	//    CTxOut(empty)
  	//  vMerkleTree: f13219df992036c16529305d015d11fe84ee11550d060bfed7a8cc58951040c4

        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
	genesis.nTime  = 1488069842;
	genesis.nNonce = 286770;
        hashGenesisBlock = genesis.GetHash();
        //assert(hashGenesisBlock == uint256("0x428a037df5084eb76ff82b6a9981bb8ded721be0f4c72d7d7d628c49eac0d38e"));
        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = list_of(113);
        base58Prefixes[SCRIPT_ADDRESS] = list_of(196);
        base58Prefixes[SECRET_KEY]     = list_of(241);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x35)(0x87)(0xCF);
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x35)(0x83)(0x94);

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

    }
    virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;


//
// Regression test
//
class CRegTestParams : public CTestNetParams {
public:
    CRegTestParams() {
        pchMessageStart[0] = 0xad;
        pchMessageStart[1] = 0x5b;
        pchMessageStart[2] = 0xfb;
        pchMessageStart[3] = 0xaf;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 5);
	// CBlock(hash=005526eaf237a937d98a85568d99a317b658ca29d12a8e23033e003828087bba, ver=1, pow_hash=005526eaf237a937d98a85568d99a317b658ca29d12a8e23033e003828087bba, hashPrevBlock=0000000000000000000000000000000000000000000000000000000000000000, hashMerkleRoot=f13219df992036c16529305d015d11fe84ee11550d060bfed7a8cc58951040c4, nTime=1450199187, nBits=2007ffff, nNonce=33, vtx=1)
  	//   Coinbase(hash=f13219df992036c16529305d015d11fe84ee11550d060bfed7a8cc58951040c4, nTime=1393221600, ver=1, vin.size=1, vout.size=1, nLockTime=0)
    	//    CTxIn(COutPoint(0000000000, 4294967295), coinbase 00012a15477265656e436f696e5632204c61756e636865732e)
    	//    CTxOut(empty)
  	//   vMerkleTree: f13219df992036c16529305d015d11fe84ee11550d060bfed7a8cc58951040c4

        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 33;
	genesis.nTime  = 1450199187;
        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 18444;
        strDataDir = "regtest";
        //assert(hashGenesisBlock == uint256("0x005526eaf237a937d98a85568d99a317b658ca29d12a8e23033e003828087bba"));

        vSeeds.clear();  // Regtest mode doesn't have any DNS seeds.
    }

    virtual bool RequireRPCPassword() const { return false; }
    virtual Network NetworkID() const { return CChainParams::REGTEST; }
};
static CRegTestParams regTestParams;

static CChainParams *pCurrentParams = &mainParams;

const CChainParams &Params() {
    return *pCurrentParams;
}

void SelectParams(CChainParams::Network network) {
    switch (network) {
        case CChainParams::MAIN:
            pCurrentParams = &mainParams;
            break;
        case CChainParams::TESTNET:
            pCurrentParams = &testNetParams;
            break;
        case CChainParams::REGTEST:
            pCurrentParams = &regTestParams;
            break;
        default:
            assert(false && "Unimplemented network");
            return;
    }
}

bool SelectParamsFromCommandLine() {
    bool fRegTest = GetBoolArg("-regtest", false);
    bool fTestNet = GetBoolArg("-testnet", false);

    if (fTestNet && fRegTest) {
        return false;
    }

    if (fRegTest) {
        SelectParams(CChainParams::REGTEST);
    } else if (fTestNet) {
        SelectParams(CChainParams::TESTNET);
    } else {
        SelectParams(CChainParams::MAIN);
    }
    return true;
}
