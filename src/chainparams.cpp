// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2019 The PIVX developers
// Copyright (c) 2019 The SpesCoin Core Developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"
#include "random.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>
#include <limits>

#include <boost/assign/list_of.hpp>

using namespace std;
using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

/**
 * Main network
 */

//! Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress>& vSeedsOut, const SeedSpec6* data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7 * 24 * 60 * 60;
    for (unsigned int i = 0; i < count; i++) {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

//   What makes a good checkpoint block?
// + Is surrounded by blocks with reasonable timestamps
//   (no blocks before with a timestamp after, none after with
//    timestamp before)
// + Contains no strange transactions
static Checkpoints::MapCheckpoints mapCheckpoints =
    boost::assign::map_list_of
        (   0, uint256("00005d5599d05ad52c3869b8e9f8d72b6b8341b998d6733be24a339bca58a142"))
	( 998, uint256("0000000057d6223056e0a67077332e0d9f3836d8b6f657f753fdbc6e270a2c66"))
	(1808, uint256("3ae3aa4664cf7f42ed9df1df8f35b1bbfd0a38658ba8e76bb3f76849c2bd50dc"))
	(3008, uint256("fa7bca2cf80ceb8048fe8b1d0d4a29076fb48e895c29a7ea7653cb0d6e941396"))
    ;

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1571207378, // * UNIX timestamp of last checkpoint block
    6039,       // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the SetBestChain debug.log lines)
    862         // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet = boost::assign::map_list_of(0, uint256("0"));
static const Checkpoints::CCheckpointData dataTestnet = {&mapCheckpointsTestnet,
	1570553000, 
	0, 
	250
	};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest = boost::assign::map_list_of(0, uint256("0"));
static const Checkpoints::CCheckpointData dataRegtest = {&mapCheckpointsRegtest, 
	1567570700, 
	0, 
	0
	};

class CMainParams : public CChainParams
{
public:
    CMainParams()
    {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";
        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0xbf;
        pchMessageStart[1] = 0x86;
        pchMessageStart[2] = 0xb7;
        pchMessageStart[3] = 0xf6;
        vAlertPubKey = ParseHex("0468172319f4d1286a257dfe0c9817e74314129453ad0c6d56e5fc10cf9081753cd48d285baa975e10b7c9fe0fdfe556b8cbec34cf591203fbca824041a3ca23d5");
        vGMPubKey = ParseHex("04d2c65ea9ff2e6d9659263c266b65fae3e3420039cb30cd15908fb04444635ce40f29cf238badb0b66325ad24b16dc8f0bab35baccbc3027fc994b6f7cb1e476a");

        nDefaultPort = 32822;
        bnProofOfWorkLimit = ~uint256(0) >> 20;
        bnStartWork = ~uint256(0) >> 24;

        nMaxReorganizationDepth = 100;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 0;
        nTargetSpacing = 3 * 60;  // 3 minute
        nTargetSpacingSlowLaunch = 1 * 60; // before block 100
        nPoSTargetSpacing = 60;  // 1 minute
        nMaturity = 50;
        nMasternodeCountDrift = 3;
        nMaxMoneyOut = 100000000  * COIN;
//		nNewMasternodeCollateral_StartBlock = 10000; // (approximately)

        /** Height or Time Based Activations **/
        nLastPOWBlock = 1000;
        nModifierUpdateBlock = std::numeric_limits<decltype(nModifierUpdateBlock)>::max();

        const char* pszTimestamp = " SPESCoin v2 the future of CHE ";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 0 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("043c8e366da87c46327f88a613ba64cc1cfd59d04fb30a09c48d8e84fb688e48cc76c01463c00bf573f27c426719558a419bd554422a41e4aea000f37ef1e14b62") << OP_CHECKSIG;
        txNew.blob = "Genesis Tx";
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime = 1570536000; // Tuesday, October 8, 2019 12:00:00
        genesis.nBits = 0x1e0ffff0; // 504365040
        genesis.nNonce = 42926;
		
        hashGenesisBlock = genesis.GetHash();

        assert(genesis.hashMerkleRoot == uint256("031678e1a2d0b19fb160953af236800e8d1bf0ae8c128b8416b705fba3ad8c8a"));
        assert(hashGenesisBlock == uint256("00005d5599d05ad52c3869b8e9f8d72b6b8341b998d6733be24a339bca58a142"));

        //vSeeds.clear();
        vSeeds.push_back(CDNSSeedData("", "178.128.164.33"));
        vSeeds.push_back(CDNSSeedData("", "213.136.84.223"));
        vSeeds.push_back(CDNSSeedData("", "144.217.112.129"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 63); // S
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 12); // 5 or 6
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,135);
        // SpesCoin BIP32 pubkeys start with 'xpub' (Bitcoin defaults)
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x02)(0x2D)(0x25)(0x33).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x02)(0x21)(0x31)(0x2B).convert_to_container<std::vector<unsigned char> >();
        // 	BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x98).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        fRequireRPCPassword = true;
        fMiningRequiresPeers = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = true;
        fTestnetToBeDeprecatedFieldRPC = false;
        fHeadersFirstSyncingActive = false;

        nPoolMaxTransactions = 3;

        nStakeInputMin = 5 * COIN;
        strDevFeeAddress = "SdevfuNwLSxjxhBpG2FbwqXCcpoBcHecEj";

        strSporkKey = "04a82b41ab1b5945a0c494e8efe5111dec990e5b26e01f70711ff71e7767cee3256d50ceedce8e82e689ebc4c92bed04fb45a08306ddd3fb99461a20fc8fdb3633";
        strObfuscationPoolDummyAddress = "SVqFAirocpVEQdJrerWJxkY3AD2XyJvMqT";

    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return data;
    }
};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CMainParams
{
public:
    CTestNetParams()
    {
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";
        pchMessageStart[0] = 0xf8;
        pchMessageStart[1] = 0xb0;
        pchMessageStart[2] = 0x9a;
        pchMessageStart[3] = 0x8a;
        vAlertPubKey = ParseHex("0480096dd801feb012c2151a3c2490b88cc7b0e20b96989a5ed8262e6b57cfe21614f916014a72a877d1eaffcc55312a83e14c218946fa1290128572b71b1ada5d");
        vGMPubKey = ParseHex("040214cbca2a170155a777f802e2975d79e7f2f347bea9cbdf2859479b6241af99841f70ce78d9a415ccb234e63bea5c1ddea0ad490864da1b5c1e865831ae5661");

        bnProofOfWorkLimit = ~uint256(0) >> 1;
        bnStartWork = bnProofOfWorkLimit;

        nDefaultPort = 42822;
        nEnforceBlockUpgradeMajority = 51;
        nRejectBlockOutdatedMajority = 75;
        nToCheckBlockUpgradeMajority = 100;
        nMinerThreads = 0;
        nTargetSpacing = 2 * 60;  // 1 minute
		// nLastPOWBlock = std::numeric_limits<decltype(nLastPOWBlock)>::max();
        nMaturity = 20;
        nMasternodeCountDrift = 4;
        nModifierUpdateBlock = std::numeric_limits<decltype(nModifierUpdateBlock)>::max();
        nMaxMoneyOut = 50000000 * COIN;
        genesis.nTime = 1567484300;
        genesis.nNonce = 74463;

        hashGenesisBlock = genesis.GetHash();

        assert(hashGenesisBlock == uint256("0000c76981fa4a104c74014fdbb0b3add9d1c31ecb6269ed1f1844582dc377fa"));

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 125); // Testnet spescoin addresses start with 's'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 19);  // Testnet spescoin script addresses start with '8' or '9'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);     // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x61)(0xa0).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x80)(0x58)(0x37).convert_to_container<std::vector<unsigned char> >();
        // Testnet spescoin BIP44 coin type is '1' (All coin's testnet default)
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0xc9).convert_to_container<std::vector<unsigned char> >();

        //convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        fRequireRPCPassword = true;
        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;

        nPoolMaxTransactions = 2;
        nStakeInputMin = 5 * COIN;
        strDevFeeAddress = "sdevfunXzabZvgFAhazUcWfKrBJtFssmkk";
        strSporkKey = "041981b560aa29fec8881cb54e3bf249e73898b4fc507bad57c2b9f0f938f4971c10fb3af5918c94a34d8add0e61326eb8925231d4ee419248b6668ae1f39386f8";
        strObfuscationPoolDummyAddress = "sKCAtVhCa3xhg4wLamJZrBDE67uSS978NW";


    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataTestnet;
    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CTestNetParams
{
public:
    CRegTestParams()
    {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "regtest";
        strNetworkID = "regtest";
        pchMessageStart[0] = 0xf1;
        pchMessageStart[1] = 0x8b;
        pchMessageStart[2] = 0xf2;
        pchMessageStart[3] = 0x81;
		
        bnStartWork = ~uint256(0) >> 20;

        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 1;
        nTargetSpacing = 1 * 60;
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        genesis.nTime = 1567570700;
        genesis.nBits = 0x207fffff;
        genesis.nNonce = 1;

        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 51476;

        //assert(hashGenesisBlock == uint256("000076579333f5e6fbabcea405a41fe3f1365d961f6fa135ed3981549ac14eb3"));

        vFixedSeeds.clear(); //! Testnet mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Testnet mode doesn't have any DNS seeds.

        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataRegtest;
    }
};
static CRegTestParams regTestParams;

/**
 * Unit test
 */
class CUnitTestParams : public CMainParams, public CModifiableParams
{
public:
    CUnitTestParams()
    {
        networkID = CBaseChainParams::UNITTEST;
        strNetworkID = "unittest";
        nDefaultPort = 51478;
        vFixedSeeds.clear(); //! Unit test mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Unit test mode doesn't have any DNS seeds.

        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fMineBlocksOnDemand = true;


    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        // UnitTest share the same checkpoints as MAIN
        return data;
    }

    //! Published setters to allow changing values in unit test cases
    virtual void setEnforceBlockUpgradeMajority(int anEnforceBlockUpgradeMajority) { nEnforceBlockUpgradeMajority = anEnforceBlockUpgradeMajority; }
    virtual void setRejectBlockOutdatedMajority(int anRejectBlockOutdatedMajority) { nRejectBlockOutdatedMajority = anRejectBlockOutdatedMajority; }
    virtual void setToCheckBlockUpgradeMajority(int anToCheckBlockUpgradeMajority) { nToCheckBlockUpgradeMajority = anToCheckBlockUpgradeMajority; }
    virtual void setDefaultConsistencyChecks(bool afDefaultConsistencyChecks) { fDefaultConsistencyChecks = afDefaultConsistencyChecks; }
    virtual void setSkipProofOfWorkCheck(bool afSkipProofOfWorkCheck) { fSkipProofOfWorkCheck = afSkipProofOfWorkCheck; }
};
static CUnitTestParams unitTestParams;


static CChainParams* pCurrentParams = 0;

CModifiableParams* ModifiableParams()
{
    assert(pCurrentParams);
    assert(pCurrentParams == &unitTestParams);
    return (CModifiableParams*)&unitTestParams;
}

const CChainParams& Params()
{
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(CBaseChainParams::Network network)
{
    switch (network) {
    case CBaseChainParams::MAIN:
        return mainParams;
    case CBaseChainParams::TESTNET:
        return testNetParams;
    case CBaseChainParams::REGTEST:
        return regTestParams;
    case CBaseChainParams::UNITTEST:
        return unitTestParams;
    default:
        assert(false && "Unimplemented network");
        return mainParams;
    }
}

void SelectParams(CBaseChainParams::Network network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;

    SelectParams(network);
    return true;
}
