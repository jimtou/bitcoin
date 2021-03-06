# Copyright (c) 2013-2016 The Bitcoin Core developers
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.

DIST_SUBDIRS = secp256k1 univalue

AM_LDFLAGS = $(PTHREAD_CFLAGS) $(LIBTOOL_LDFLAGS) $(HARDENED_LDFLAGS) $(GPROF_LDFLAGS) $(SANITIZER_LDFLAGS)
AM_CXXFLAGS = $(DEBUG_CXXFLAGS) $(HARDENED_CXXFLAGS) $(WARN_CXXFLAGS) $(NOWARN_CXXFLAGS) $(ERROR_CXXFLAGS) $(GPROF_CXXFLAGS) $(SANITIZER_CXXFLAGS)
AM_CPPFLAGS = $(DEBUG_CPPFLAGS) $(HARDENED_CPPFLAGS)
AM_LIBTOOLFLAGS = --preserve-dup-deps
EXTRA_LIBRARIES =

if EMBEDDED_UNIVALUE
LIBUNIVALUE = univalue/libunivalue.la

$(LIBUNIVALUE): $(wildcard univalue/lib/*) $(wildcard univalue/include/*)
	$(AM_V_at)$(MAKE) $(AM_MAKEFLAGS) -C $(@D) $(@F)
else
LIBUNIVALUE = $(UNIVALUE_LIBS)
endif

BITCOIN_INCLUDES=-I$(builddir) $(BDB_CPPFLAGS) $(BOOST_CPPFLAGS) $(LEVELDB_CPPFLAGS) $(CRYPTO_CFLAGS) $(SSL_CFLAGS)

BITCOIN_INCLUDES += -I$(srcdir)/secp256k1/include
BITCOIN_INCLUDES += $(UNIVALUE_CFLAGS)

DAG_INCLUDES=-I$(builddir) $(BDB_CPPFLAGS) $(BOOST_CPPFLAGS) $(LEVELDB_CPPFLAGS) $(CRYPTO_CFLAGS) $(SSL_CFLAGS)
DAG_INCLUDES += -I$(srcdir)/dag
DAG_INCLUDES += -I$(srcdir)/dag/cclient
##keccak test
#DAG_INCLUDES += -I$(srcdir)/dag/external/keccak
DAG_INCLUDES += -I$(srcdir)/dag/external/keccak/bin/generic64/libkeccak.a.headers
DAG_INCLUDES += -I$(srcdir)/dag/external/uthash/src

LIBBITCOIN_SERVER=libbitcoin_server.a
LIBBITCOIN_COMMON=libbitcoin_common.a
LIBBITCOIN_CONSENSUS=libbitcoin_consensus.a
LIBBITCOIN_CLI=libbitcoin_cli.a
LIBBITCOIN_UTIL=libbitcoin_util.a
LIBBITCOIN_CRYPTO_BASE=crypto/libbitcoin_crypto_base.a
LIBBITCOINQT=qt/libbitcoinqt.a
LIBSECP256K1=secp256k1/libsecp256k1.la
LIBDAG_CIRI=libdag_ciri.a
LIBDAG_COMMON=libdag_common.a
LIBDAG_CONSENSUS=libdag_consensus.a
LIBDAG_GOSSIP=libdag_gossip.a
LIBDAG_NETWORK=libdag_network.a
LIBDAG_UTILS=libdag_utils.a

if ENABLE_ZMQ
LIBBITCOIN_ZMQ=libbitcoin_zmq.a
endif
if BUILD_BITCOIN_LIBS
LIBBITCOINCONSENSUS=libbitcoinconsensus.la
endif
if ENABLE_WALLET
LIBBITCOIN_WALLET=libbitcoin_wallet.a
endif

LIBBITCOIN_CRYPTO= $(LIBBITCOIN_CRYPTO_BASE)
if ENABLE_SSE41
LIBBITCOIN_CRYPTO_SSE41 = crypto/libbitcoin_crypto_sse41.a
LIBBITCOIN_CRYPTO += $(LIBBITCOIN_CRYPTO_SSE41)
endif
if ENABLE_AVX2
LIBBITCOIN_CRYPTO_AVX2 = crypto/libbitcoin_crypto_avx2.a
LIBBITCOIN_CRYPTO += $(LIBBITCOIN_CRYPTO_AVX2)
endif
if ENABLE_SHANI
LIBBITCOIN_CRYPTO_SHANI = crypto/libbitcoin_crypto_shani.a
LIBBITCOIN_CRYPTO += $(LIBBITCOIN_CRYPTO_SHANI)
endif

$(LIBSECP256K1): $(wildcard secp256k1/src/*.h) $(wildcard secp256k1/src/*.c) $(wildcard secp256k1/include/*)
	$(AM_V_at)$(MAKE) $(AM_MAKEFLAGS) -C $(@D) $(@F)

# Make is not made aware of per-object dependencies to avoid limiting building parallelization
# But to build the less dependent modules first, we manually select their order here:
EXTRA_LIBRARIES += \
  $(LIBBITCOIN_CRYPTO) \
  $(LIBBITCOIN_UTIL) \
  $(LIBBITCOIN_COMMON) \
  $(LIBBITCOIN_CONSENSUS) \
  $(LIBBITCOIN_SERVER) \
  $(LIBBITCOIN_CLI) \
  $(LIBBITCOIN_WALLET) \
  $(LIBBITCOIN_ZMQ) \
  $(LIBDAG_CIRI) \
  $(LIBDAG_COMMON) \
  $(LIBDAG_CONSENSUS) \
  $(LIBDAG_GOSSIP) \
  $(LIBDAG_NETWORK) \
  $(LIBDAG_UTILS)

lib_LTLIBRARIES = $(LIBBITCOINCONSENSUS)

bin_PROGRAMS =
noinst_PROGRAMS =
TESTS =
BENCHMARKS =

if BUILD_BITCOIND
  bin_PROGRAMS += bitcoind
endif

if BUILD_BITCOIN_CLI
  bin_PROGRAMS += bitcoin-cli
endif
if BUILD_BITCOIN_TX
  bin_PROGRAMS += bitcoin-tx
endif

.PHONY: FORCE check-symbols check-security
# bitcoin core #
BITCOIN_CORE_H = \
  addrdb.h \
  addrman.h \
  base58.h \
  bech32.h \
  bloom.h \
  blockencodings.h \
  blockfilter.h \
  chain.h \
  chainparams.h \
  chainparamsbase.h \
  chainparamsseeds.h \
  checkpoints.h \
  checkqueue.h \
  clientversion.h \
  coins.h \
  compat.h \
  compat/byteswap.h \
  compat/endian.h \
  compat/sanity.h \
  compressor.h \
  consensus/consensus.h \
  consensus/tx_verify.h \
  core_io.h \
  core_memusage.h \
  cuckoocache.h \
  fs.h \
  httprpc.h \
  httpserver.h \
  index/base.h \
  index/txindex.h \
  indirectmap.h \
  init.h \
  interfaces/handler.h \
  interfaces/node.h \
  interfaces/wallet.h \
  key.h \
  key_io.h \
  keystore.h \
  dbwrapper.h \
  limitedmap.h \
  logging.h \
  memusage.h \
  merkleblock.h \
  miner.h \
  net.h \
  net_processing.h \
  netaddress.h \
  netbase.h \
  netmessagemaker.h \
  noui.h \
  outputtype.h \
  policy/feerate.h \
  policy/fees.h \
  policy/policy.h \
  policy/rbf.h \
  pow.h \
  protocol.h \
  random.h \
  reverse_iterator.h \
  reverselock.h \
  rpc/blockchain.h \
  rpc/client.h \
  rpc/mining.h \
  rpc/protocol.h \
  rpc/server.h \
  rpc/rawtransaction.h \
  rpc/register.h \
  rpc/util.h \
  scheduler.h \
  script/descriptor.h \
  script/ismine.h \
  script/sigcache.h \
  script/sign.h \
  script/standard.h \
  shutdown.h \
  streams.h \
  support/allocators/secure.h \
  support/allocators/zeroafterfree.h \
  support/cleanse.h \
  support/events.h \
  support/lockedpool.h \
  sync.h \
  threadsafety.h \
  threadinterrupt.h \
  timedata.h \
  torcontrol.h \
  txdb.h \
  txmempool.h \
  ui_interface.h \
  undo.h \
  util/bytevectorhash.h \
  util/system.h \
  util/memory.h \
  util/moneystr.h \
  util/time.h \
  validation.h \
  validationinterface.h \
  versionbits.h \
  versionbitsinfo.h \
  walletinitinterface.h \
  wallet/coincontrol.h \
  wallet/crypter.h \
  wallet/db.h \
  wallet/feebumper.h \
  wallet/fees.h \
  wallet/rpcwallet.h \
  wallet/wallet.h \
  wallet/walletdb.h \
  wallet/walletutil.h \
  wallet/coinselection.h \
  warnings.h \
  zmq/zmqabstractnotifier.h \
  zmq/zmqconfig.h\
  zmq/zmqnotificationinterface.h \
  zmq/zmqpublishnotifier.h \
  zmq/zmqrpc.h 

# dag core #
DAG_CORE_H = \
  dag/ciri/api/api.h \
  dag/ciri/api/conf.h \
  dag/ciri/conf.h \
  dag/ciri/core.h \
  dag/ciri/usage.h \
  dag/common/errors.h \
  dag/common/defs.h \
  dag/common/error_strings.h \
  dag/common/stdint.h \
  dag/common/curl-p/bct.h \
  dag/common/curl-p/const.h \
  dag/common/curl-p/curl_p_b_s.h \
  dag/common/curl-p/curl_p_s.h \
  dag/common/curl-p/curl_s_digest.h \
  dag/common/curl-p/digest.h \
  dag/common/curl-p/hamming.h \
  dag/common/curl-p/hashcash.h \
  dag/common/curl-p/indices.h \
  dag/common/curl-p/pearl_diver.h \
  dag/common/curl-p/ptrit.h \
  dag/common/curl-p/search.h \
  dag/common/curl-p/trit.h \
  dag/common/kerl/bigint.h \
  dag/common/kerl/converter.h \
  dag/common/kerl/hash.h \
  dag/common/kerl/kerl.h \
  dag/common/model/bundle.h \
  dag/common/model/milestone.h \
  dag/common/model/transaction.h \
  dag/common/model/transfer.h \
  dag/common/model/tryte_transaction.h \
  dag/common/network/endpoint.h \
  dag/common/network/network.h \
  dag/common/network/uri_parser.h \
  dag/common/pow/pow.h \
  dag/common/sign/normalize.h \
  dag/common/sign/v1/iss_curl.h \
  dag/common/sign/v1/iss_kerl.h \
  dag/common/sign/v2/iss_curl.h \
  dag/common/sign/v2/iss_kerl.h \
  dag/common/storage/connection.h \
  dag/common/storage/defs.h \
  dag/common/storage/pack.h \
  dag/common/storage/storage.h \
  dag/common/storage/sql/defs.h \
  dag/common/storage/sql/statements.h \
  dag/common/trinary/add.h \
  dag/common/trinary/bct.h \
  dag/common/trinary/bytes.h \
  dag/common/trinary/ptrit.h \
  dag/common/trinary/ptrit_incr.h \
  dag/common/trinary/trit_array.h \
  dag/common/trinary/trit_byte.h \
  dag/common/trinary/trit_long.h \
  dag/common/trinary/trit_ptrit.h \
  dag/common/trinary/trits.h \
  dag/common/trinary/trit_tryte.h \
  dag/common/trinary/tryte_ascii.h \
  dag/common/trinary/tryte.h \
  dag/common/trinary/tryte_long.h \
  dag/common/trinary/flex_trit.h \
  dag/common/trinary/flex_trit_array.h \
  dag/consensus/bundle_validator/bundle_validator.h \
  dag/consensus/cw_rating_calculator/cw_rating_calculator.h \
  dag/consensus/cw_rating_calculator/cw_rating_dfs_impl.h \
  dag/consensus/entry_point_selector/entry_point_selector.h \
  dag/consensus/exit_probability_randomizer/exit_probability_randomizer.h \
  dag/consensus/exit_probability_randomizer/walker.h \
  dag/consensus/exit_probability_validator/exit_probability_validator.h \
  dag/consensus/ledger_validator/ledger_validator.h \
  dag/consensus/milestone_tracker/milestone_tracker.h \
  dag/consensus/snapshot/snapshot.h \
  dag/consensus/snapshot/state_delta.h \
  dag/consensus/tangle/tangle.h \
  dag/consensus/tip_selector/tip_selector.h \
  dag/consensus/transaction_solidifier/transaction_solidifier.h \
  dag/consensus/transaction_validator/transaction_validator.h \
  dag/consensus/utils/tangle_traversals.h \
  dag/consensus/conf.h \
  dag/consensus/consensus.h \
  dag/consensus/model.h \
  dag/gossip/components/broadcaster.h \
  dag/gossip/components/processor.h \
  dag/gossip/components/receiver.h \
  dag/gossip/components/responder.h \
  dag/gossip/components/transaction_requester.h \
  dag/gossip/services/receiver.h \
  dag/gossip/services/tcp_receiver.hpp \
  dag/gossip/services/tcp_sender.hpp \
  dag/gossip/services/udp_receiver.hpp \
  dag/gossip/services/udp_sender.hpp \
  dag/gossip/conf.h \
  dag/gossip/iota_packet.h \
  dag/gossip/neighbor.h \
  dag/gossip/node.h \
  dag/gossip/tips_cache.h \
  dag/gossip/transaction_request.h \
  dag/network/sockets.h \
  dag/utils/containers/hash/hash243_set.h \
  dag/utils/containers/lists/concurrent_list_neighbor.h \
  dag/utils/containers/lists/concurrent_list_trit_array.h \
  dag/utils/containers/queues/concurrent_queue_trit_array.h \
  dag/utils/containers/bitset.h \
  dag/utils/handles/cond.h \
  dag/utils/handles/lock.h \
  dag/utils/handles/rand.h \
  dag/utils/handles/rw_lock.h \
  dag/utils/handles/thread.h \
  dag/utils/export.h \
  dag/utils/files.h \
  dag/utils/hash_maps.h \
  dag/utils/logger_helper.h \
  dag/utils/macros.h \
  dag/utils/merkle.h \
  dag/utils/signed_files.h \
  dag/utils/system.h \
  dag/utils/time.h \
  dag/utils/logger.h \
  dag/utils/utarray.h \
  dag/utils/uthash.h \
  dag/utils/utlist.h \
  dag/utils/utringbuffer.h \
  dag/utils/utstack.h \
  dag/utils/utstring.h 
  


obj/build.h: FORCE
	@$(MKDIR_P) $(builddir)/obj
	@$(top_srcdir)/share/genbuild.sh "$(abs_top_builddir)/src/obj/build.h" \
	  "$(abs_top_srcdir)"
libbitcoin_util_a-clientversion.$(OBJEXT): obj/build.h

# server: shared between bitcoind and bitcoin-qt
libbitcoin_server_a_CPPFLAGS = $(AM_CPPFLAGS) $(BITCOIN_INCLUDES) $(MINIUPNPC_CPPFLAGS) $(EVENT_CFLAGS) $(EVENT_PTHREADS_CFLAGS) $(PIC_FLAGS)
libbitcoin_server_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS) $(PIC_FLAGS)
libbitcoin_server_a_SOURCES = \
  addrdb.cpp \
  addrman.cpp \
  bloom.cpp \
  blockencodings.cpp \
  blockfilter.cpp \
  chain.cpp \
  checkpoints.cpp \
  consensus/tx_verify.cpp \
  httprpc.cpp \
  httpserver.cpp \
  index/base.cpp \
  index/txindex.cpp \
  interfaces/handler.cpp \
  interfaces/node.cpp \
  init.cpp \
  dbwrapper.cpp \
  merkleblock.cpp \
  miner.cpp \
  net.cpp \
  net_processing.cpp \
  noui.cpp \
  outputtype.cpp \
  policy/fees.cpp \
  policy/policy.cpp \
  policy/rbf.cpp \
  pow.cpp \
  rest.cpp \
  rpc/blockchain.cpp \
  rpc/mining.cpp \
  rpc/misc.cpp \
  rpc/net.cpp \
  rpc/rawtransaction.cpp \
  rpc/server.cpp \
  rpc/util.cpp \
  script/sigcache.cpp \
  shutdown.cpp \
  timedata.cpp \
  torcontrol.cpp \
  txdb.cpp \
  txmempool.cpp \
  ui_interface.cpp \
  validation.cpp \
  validationinterface.cpp \
  versionbits.cpp \
  $(BITCOIN_CORE_H)

if !ENABLE_WALLET
libbitcoin_server_a_SOURCES += dummywallet.cpp
endif

if ENABLE_ZMQ
libbitcoin_zmq_a_CPPFLAGS = $(BITCOIN_INCLUDES) $(ZMQ_CFLAGS)
libbitcoin_zmq_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libbitcoin_zmq_a_SOURCES = \
  zmq/zmqabstractnotifier.cpp \
  zmq/zmqnotificationinterface.cpp \
  zmq/zmqpublishnotifier.cpp \
  zmq/zmqrpc.cpp
endif


# wallet: shared between bitcoind and bitcoin-qt, but only linked
# when wallet enabled
libbitcoin_wallet_a_CPPFLAGS = $(AM_CPPFLAGS) $(BITCOIN_INCLUDES)
libbitcoin_wallet_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libbitcoin_wallet_a_SOURCES = \
  interfaces/wallet.cpp \
  wallet/coincontrol.cpp \
  wallet/crypter.cpp \
  wallet/db.cpp \
  wallet/feebumper.cpp \
  wallet/fees.cpp \
  wallet/init.cpp \
  wallet/rpcdump.cpp \
  wallet/rpcwallet.cpp \
  wallet/wallet.cpp \
  wallet/walletdb.cpp \
  wallet/walletutil.cpp \
  wallet/coinselection.cpp \
  $(BITCOIN_CORE_H)

# crypto primitives library
crypto_libbitcoin_crypto_base_a_CPPFLAGS = $(AM_CPPFLAGS)
crypto_libbitcoin_crypto_base_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
crypto_libbitcoin_crypto_base_a_SOURCES = \
  crypto/aes.cpp \
  crypto/aes.h \
  crypto/chacha20.h \
  crypto/chacha20.cpp \
  crypto/common.h \
  crypto/hmac_sha256.cpp \
  crypto/hmac_sha256.h \
  crypto/hmac_sha512.cpp \
  crypto/hmac_sha512.h \
  crypto/ripemd160.cpp \
  crypto/ripemd160.h \
  crypto/sha1.cpp \
  crypto/sha1.h \
  crypto/sha256.cpp \
  crypto/sha256.h \
  crypto/sha512.cpp \
  crypto/sha512.h \
  crypto/siphash.cpp \
  crypto/siphash.h

if USE_ASM
crypto_libbitcoin_crypto_base_a_SOURCES += crypto/sha256_sse4.cpp
endif

crypto_libbitcoin_crypto_sse41_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
crypto_libbitcoin_crypto_sse41_a_CPPFLAGS = $(AM_CPPFLAGS)
crypto_libbitcoin_crypto_sse41_a_CXXFLAGS += $(SSE41_CXXFLAGS)
crypto_libbitcoin_crypto_sse41_a_CPPFLAGS += -DENABLE_SSE41
crypto_libbitcoin_crypto_sse41_a_SOURCES = crypto/sha256_sse41.cpp

crypto_libbitcoin_crypto_avx2_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
crypto_libbitcoin_crypto_avx2_a_CPPFLAGS = $(AM_CPPFLAGS)
crypto_libbitcoin_crypto_avx2_a_CXXFLAGS += $(AVX2_CXXFLAGS)
crypto_libbitcoin_crypto_avx2_a_CPPFLAGS += -DENABLE_AVX2
crypto_libbitcoin_crypto_avx2_a_SOURCES = crypto/sha256_avx2.cpp

crypto_libbitcoin_crypto_shani_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
crypto_libbitcoin_crypto_shani_a_CPPFLAGS = $(AM_CPPFLAGS)
crypto_libbitcoin_crypto_shani_a_CXXFLAGS += $(SHANI_CXXFLAGS)
crypto_libbitcoin_crypto_shani_a_CPPFLAGS += -DENABLE_SHANI
crypto_libbitcoin_crypto_shani_a_SOURCES = crypto/sha256_shani.cpp

# consensus: shared between all executables that validate any consensus rules.
libbitcoin_consensus_a_CPPFLAGS = $(AM_CPPFLAGS) $(BITCOIN_INCLUDES)
libbitcoin_consensus_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libbitcoin_consensus_a_SOURCES = \
  amount.h \
  arith_uint256.cpp \
  arith_uint256.h \
  consensus/merkle.cpp \
  consensus/merkle.h \
  consensus/params.h \
  consensus/validation.h \
  hash.cpp \
  hash.h \
  prevector.h \
  primitives/block.cpp \
  primitives/block.h \
  primitives/transaction.cpp \
  primitives/transaction.h \
  pubkey.cpp \
  pubkey.h \
  script/bitcoinconsensus.cpp \
  script/interpreter.cpp \
  script/interpreter.h \
  script/script.cpp \
  script/script.h \
  script/script_error.cpp \
  script/script_error.h \
  serialize.h \
  span.h \
  tinyformat.h \
  uint256.cpp \
  uint256.h \
  util/strencodings.cpp \
  util/strencodings.h \
  version.h

# common: shared between bitcoind, and bitcoin-qt and non-server tools
libbitcoin_common_a_CPPFLAGS = $(AM_CPPFLAGS) $(BITCOIN_INCLUDES)
libbitcoin_common_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libbitcoin_common_a_SOURCES = \
  base58.cpp \
  bech32.cpp \
  chainparams.cpp \
  coins.cpp \
  compressor.cpp \
  core_read.cpp \
  core_write.cpp \
  key.cpp \
  key_io.cpp \
  keystore.cpp \
  netaddress.cpp \
  netbase.cpp \
  policy/feerate.cpp \
  protocol.cpp \
  scheduler.cpp \
  script/descriptor.cpp \
  script/ismine.cpp \
  script/sign.cpp \
  script/standard.cpp \
  versionbitsinfo.cpp \
  warnings.cpp \
  $(BITCOIN_CORE_H)

# util: shared between all executables.
# This library *must* be included to make sure that the glibc
# backward-compatibility objects and their sanity checks are linked.
libbitcoin_util_a_CPPFLAGS = $(AM_CPPFLAGS) $(BITCOIN_INCLUDES)
libbitcoin_util_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libbitcoin_util_a_SOURCES = \
  support/lockedpool.cpp \
  chainparamsbase.cpp \
  clientversion.cpp \
  compat/glibc_sanity.cpp \
  compat/glibcxx_sanity.cpp \
  compat/strnlen.cpp \
  fs.cpp \
  logging.cpp \
  random.cpp \
  rpc/protocol.cpp \
  support/cleanse.cpp \
  sync.cpp \
  threadinterrupt.cpp \
  util/bytevectorhash.cpp \
  util/system.cpp \
  util/moneystr.cpp \
  util/strencodings.cpp \
  util/time.cpp \
  $(BITCOIN_CORE_H)

if GLIBC_BACK_COMPAT
libbitcoin_util_a_SOURCES += compat/glibc_compat.cpp
AM_LDFLAGS += $(COMPAT_LDFLAGS)
endif

# cli: shared between bitcoin-cli and bitcoin-qt
libbitcoin_cli_a_CPPFLAGS = $(AM_CPPFLAGS) $(BITCOIN_INCLUDES)
libbitcoin_cli_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libbitcoin_cli_a_SOURCES = \
  rpc/client.cpp \
  $(BITCOIN_CORE_H)

nodist_libbitcoin_util_a_SOURCES = $(srcdir)/obj/build.h
#

# dag ciri: dag ciri
libdag_ciri_a_CPPFLAGS = $(AM_CPPFLAGS) $(BITCOIN_INCLUDES) $(DAG_INCLUDES) $(PIC_FLAGS)
libdag_ciri_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS) $(PIC_FLAGS)
libdag_ciri_a_SOURCES = \
  dag/ciri/api/api.c \
  dag/ciri/api/conf.c \
  dag/ciri/conf.c \
  dag/ciri/core.c \
  dag/ciri/usage.c \
  dag/ciri/exec.c \
  dag/cclient/response/get_tips.c \
  dag/cclient/types/types.c \
  dag/cclient/response/get_trytes.c \
  dag/cclient/serialization/json/json_serializer.c \
  dag/cclient/response/get_neighbors.c \
  dag/common/storage/sql/sqlite3/storage.c \
  $(BITCOIN_CORE_H) \
  $(DAG_CORE_H)

# dag common library
libdag_common_a_CPPFLAGS = $(AM_CPPFLAGS) $(BITCOIN_INCLUDES)  $(DAG_INCLUDES) $(PIC_FLAGS)
libdag_common_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS) $(PIC_FLAGS)
libdag_common_a_SOURCES = \
  dag/common/errors.c \
  dag/common/curl-p/curl_p_bct.c \
  dag/common/curl-p/curl_p_ptrit.c \
  dag/common/curl-p/curl_p_s.c \
  dag/common/curl-p/curl_p.c \
  dag/common/curl-p/digest.c \
  dag/common/curl-p/hamming.c \
  dag/common/curl-p/hashcash.c \
  dag/common/curl-p/pearl_diver.c \
  dag/common/kerl/bigint.c \
  dag/common/kerl/converter.c \
  dag/common/kerl/hash.c \
  dag/common/kerl/kerl.c \
  dag/common/model/bundle.c \
  dag/common/model/transfer.c \
  dag/common/model/transaction.c \
  dag/common/model/tryte_transaction.cc \
  dag/common/network/uri_parser.c \
  dag/common/pow/pow.c \
  dag/common/sign/normalize.c \
  dag/common/sign/v1/iss_curl.c \
  dag/common/sign/v1/iss_kerl.c \
  dag/common/sign/v2/iss_curl.c \
  dag/common/sign/v2/iss_kerl.c \
  dag/common/storage/pack.c \
  dag/common/storage/sql/statements.c \  
  dag/common/trinary/add.c \
  dag/common/trinary/ptrit_incr.c \
  dag/common/trinary/trit_array.c \
  dag/common/trinary/trit_byte.c \
  dag/common/trinary/trit_long.c \
  dag/common/trinary/trit_ptrit.c \
  dag/common/trinary/trit_tryte.c \
  dag/common/trinary/tryte_ascii.c \
  dag/common/trinary/tryte_long.c \
  dag/common/trinary/flex_trit.c \
  dag/common/trinary/flex_trit_array.cc \
  dag/common/sign/v2/iss_curl.c \
  $(BITCOIN_CORE_H) \
  $(DAG_CORE_H)

# dag consensus library
libdag_consensus_a_CPPFLAGS = $(AM_CPPFLAGS) $(BITCOIN_INCLUDES)  $(DAG_INCLUDES) $(PIC_FLAGS)
libdag_consensus_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS) $(PIC_FLAGS)
libdag_consensus_a_SOURCES = \
  dag/consensus/bundle_validator/bundle_validator.c \
  dag/consensus/cw_rating_calculator/cw_rating_calculator.c \
  dag/consensus/cw_rating_calculator/cw_rating_dfs_impl.c \
  dag/consensus/entry_point_selector/entry_point_selector.c \
  dag/consensus/exit_probability_randomizer/exit_probability_randomizer.c \
  dag/consensus/exit_probability_randomizer/walker.c \
  dag/consensus/exit_probability_validator/exit_probability_validator.c \
  dag/consensus/ledger_validator/ledger_validator.c \
  dag/consensus/milestone_tracker/milestone_tracker.c \
  dag/consensus/snapshot/state_delta.c \
  dag/consensus/snapshot/snapshot.c \
  dag/consensus/tangle/tangle.c \
  dag/consensus/tip_selector/tip_selector.c \
  dag/consensus/transaction_solidifier/transaction_solidifier.c \
  dag/consensus/transaction_validator/transaction_validator.c \
  dag/consensus/utils/tangle_traversals.c \
  dag/consensus/conf.c \
  dag/consensus/consensus.c \
  dag/common/storage/sql/sqlite3/storage.c \
  dag/common/model/bundle.c \
  dag/common/model/transfer.c \
  dag/common/helpers/sign.c \
  dag/common/storage/sql/statements.c \
  dag/common/storage/sql/sqlite3/connection.c \
  dag/common/kerl/kerl.c \
  dag/common/sign/v1/iss_kerl.c \
  dag/common/sign/v2/iss_curl.c \
  $(BITCOIN_CORE_H) \
  $(DAG_CORE_H)
  
# dag gossip: dag gossip
libdag_gossip_a_CPPFLAGS = $(AM_CPPFLAGS) $(BITCOIN_INCLUDES) $(DAG_INCLUDES) $(PIC_FLAGS)
libdag_gossip_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS) $(PIC_FLAGS)
libdag_gossip_a_SOURCES = \
  dag/gossip/components/broadcaster.c \
  dag/gossip/components/processor.c \
  dag/gossip/components/receiver.c \
  dag/gossip/components/responder.c \
  dag/gossip/components/transaction_requester.c \
  dag/gossip/services/tcp_sender.cc \
  dag/gossip/services/receiver.cc \
  dag/gossip/services/tcp_receiver.cc \
  dag/gossip/services/udp_receiver.cc \
  dag/gossip/services/udp_sender.cc \
  dag/gossip/conf.c \
  dag/gossip/node.c \
  dag/gossip/iota_packet.c \
  dag/gossip/neighbor.c \
  dag/gossip/tips_cache.c \
  dag/gossip/transaction_request.c \
  dag/gossip/components/tips_requester.c \
  dag/common/network/uri_parser.c \
  $(BITCOIN_CORE_H) \
  $(DAG_CORE_H)

# dag network: dag network sockets
libdag_network_a_CPPFLAGS = $(AM_CPPFLAGS) $(BITCOIN_INCLUDES) $(PIC_FLAGS)
libdag_network_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS) $(PIC_FLAGS)
libdag_network_a_SOURCES = \
  dag/network/sockets.c \
  $(BITCOIN_CORE_H) \
  $(DAG_CORE_H)
  
# dag utils: dag utils
libdag_utils_a_CPPFLAGS = $(AM_CPPFLAGS) $(BITCOIN_INCLUDES) $(DAG_INCLUDES) $(PIC_FLAGS)
libdag_utils_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS) $(PIC_FLAGS)
libdag_utils_a_SOURCES = \
  dag/utils/containers/hash/hash243_queue.c \
  dag/utils/containers/hash/hash243_set.c \
  dag/utils/containers/hash/hash243_stack.c \
  dag/utils/containers/hash/hash8019_queue.c \
  dag/utils/containers/hash/hash8019_stack.c \
  dag/utils/containers/hash/hash81_queue.c \
  dag/utils/containers/hash/hash243_set.c \
  dag/utils/containers/hash/hash_stack.c.tpl \
  dag/utils/containers/lists/concurrent_list_neighbor.c \
  dag/utils/containers/lists/concurrent_list_trit_array.c \
  dag/utils/containers/queues/concurrent_queue_trit_array.c \
  dag/utils/containers/bitset.c \
  dag/utils/files.c \
  dag/utils/hash_maps.c \
  dag/utils/logger_helper.c \
  dag/utils/merkle.c \
  dag/utils/signed_files.c \
  dag/utils/system.c \
  dag/utils/time.c \
  dag/utils/logger.c \
  dag/common/kerl/converter.c \
  dag/common/kerl/bigint.c \
  dag/common/sign/normalize.c \
  dag/common/trinary/tryte_ascii.c \
  dag/common/trinary/add.c \
  dag/common/sign/v2/iss_curl.c \
  $(BITCOIN_CORE_H) \
  $(DAG_CORE_H)

# bitcoind binary #
bitcoind_SOURCES = bitcoind.cpp
bitcoind_CPPFLAGS = $(AM_CPPFLAGS) $(BITCOIN_INCLUDES)
bitcoind_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
bitcoind_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS)

if TARGET_WINDOWS
bitcoind_SOURCES += bitcoind-res.rc
endif

bitcoind_LDADD = \
  $(LIBBITCOIN_SERVER) \
  $(LIBBITCOIN_WALLET) \
  $(LIBBITCOIN_COMMON) \
  $(LIBUNIVALUE) \
  $(LIBBITCOIN_UTIL) \
  $(LIBBITCOIN_ZMQ) \
  $(LIBBITCOIN_CONSENSUS) \
  $(LIBBITCOIN_CRYPTO) \
  $(LIBLEVELDB) \
  $(LIBLEVELDB_SSE42) \
  $(LIBMEMENV) \
  $(LIBSECP256K1) \
  $(LIBDAG_CIRI) \
  $(LIBDAG_COMMON) \
  $(LIBDAG_CONSENSUS) \
  $(LIBDAG_GOSSIP) \
  $(LIBDAG_NETWORK) \
  $(LIBDAG_UTILS) 

bitcoind_LDADD += $(BOOST_LIBS) $(BDB_LIBS) $(CRYPTO_LIBS) $(MINIUPNPC_LIBS) $(EVENT_PTHREADS_LIBS) $(EVENT_LIBS) $(ZMQ_LIBS) 
bitcoind_LDADD += $(SQLITE3_LIBS) $(CJSON_LIBS) 

##keccak test
bitcoind_LDADD += -lkeccak

# bitcoin-cli binary #
bitcoin_cli_SOURCES = bitcoin-cli.cpp
bitcoin_cli_CPPFLAGS = $(AM_CPPFLAGS) $(BITCOIN_INCLUDES) $(EVENT_CFLAGS)
bitcoin_cli_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
bitcoin_cli_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS)

if TARGET_WINDOWS
bitcoin_cli_SOURCES += bitcoin-cli-res.rc
endif

bitcoin_cli_LDADD = \
  $(LIBBITCOIN_CLI) \
  $(LIBUNIVALUE) \
  $(LIBBITCOIN_UTIL) \
  $(LIBBITCOIN_CRYPTO)

bitcoin_cli_LDADD += $(BOOST_LIBS) $(CRYPTO_LIBS) $(EVENT_LIBS)
#

# bitcoin-tx binary #
bitcoin_tx_SOURCES = bitcoin-tx.cpp
bitcoin_tx_CPPFLAGS = $(AM_CPPFLAGS) $(BITCOIN_INCLUDES)
bitcoin_tx_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
bitcoin_tx_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS)

if TARGET_WINDOWS
bitcoin_tx_SOURCES += bitcoin-tx-res.rc
endif

bitcoin_tx_LDADD = \
  $(LIBUNIVALUE) \
  $(LIBBITCOIN_COMMON) \
  $(LIBBITCOIN_UTIL) \
  $(LIBBITCOIN_CONSENSUS) \
  $(LIBBITCOIN_CRYPTO) \
  $(LIBSECP256K1)

bitcoin_tx_LDADD += $(BOOST_LIBS) $(CRYPTO_LIBS)
#

# bitcoinconsensus library #
if BUILD_BITCOIN_LIBS
include_HEADERS = script/bitcoinconsensus.h
libbitcoinconsensus_la_SOURCES = $(crypto_libbitcoin_crypto_base_a_SOURCES) $(libbitcoin_consensus_a_SOURCES)

if GLIBC_BACK_COMPAT
  libbitcoinconsensus_la_SOURCES += compat/glibc_compat.cpp
endif

libbitcoinconsensus_la_LDFLAGS = $(AM_LDFLAGS) -no-undefined $(RELDFLAGS)
libbitcoinconsensus_la_LIBADD = $(LIBSECP256K1)
libbitcoinconsensus_la_CPPFLAGS = $(AM_CPPFLAGS) -I$(builddir)/obj -I$(srcdir)/secp256k1/include -DBUILD_BITCOIN_INTERNAL
libbitcoinconsensus_la_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)

endif
#

CTAES_DIST =  crypto/ctaes/bench.c
CTAES_DIST += crypto/ctaes/ctaes.c
CTAES_DIST += crypto/ctaes/ctaes.h
CTAES_DIST += crypto/ctaes/README.md
CTAES_DIST += crypto/ctaes/test.c

CLEANFILES = $(EXTRA_LIBRARIES)

CLEANFILES += *.gcda *.gcno
CLEANFILES += compat/*.gcda compat/*.gcno
CLEANFILES += consensus/*.gcda consensus/*.gcno
CLEANFILES += crypto/*.gcda crypto/*.gcno
CLEANFILES += policy/*.gcda policy/*.gcno
CLEANFILES += primitives/*.gcda primitives/*.gcno
CLEANFILES += script/*.gcda script/*.gcno
CLEANFILES += support/*.gcda support/*.gcno
CLEANFILES += univalue/*.gcda univalue/*.gcno
CLEANFILES += wallet/*.gcda wallet/*.gcno
CLEANFILES += wallet/test/*.gcda wallet/test/*.gcno
CLEANFILES += zmq/*.gcda zmq/*.gcno
CLEANFILES += obj/build.h

EXTRA_DIST = $(CTAES_DIST)


config/bitcoin-config.h: config/stamp-h1
	@$(MAKE) -C $(top_builddir) $(subdir)/$(@)
config/stamp-h1: $(top_srcdir)/$(subdir)/config/bitcoin-config.h.in $(top_builddir)/config.status
	$(AM_V_at)$(MAKE) -C $(top_builddir) $(subdir)/$(@)
$(top_srcdir)/$(subdir)/config/bitcoin-config.h.in:  $(am__configure_deps)
	$(AM_V_at)$(MAKE) -C $(top_srcdir) $(subdir)/config/bitcoin-config.h.in

clean-local:
	-$(MAKE) -C secp256k1 clean
	-$(MAKE) -C univalue clean
	-rm -f leveldb/*/*.gcda leveldb/*/*.gcno leveldb/helpers/memenv/*.gcda leveldb/helpers/memenv/*.gcno
	-rm -f config.h
	-rm -rf test/__pycache__

.rc.o:
	@test -f $(WINDRES)
	## FIXME: How to get the appropriate modulename_CPPFLAGS in here?
	$(AM_V_GEN) $(WINDRES) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(CPPFLAGS) -DWINDRES_PREPROC -i $< -o $@

check-symbols: $(bin_PROGRAMS)
if GLIBC_BACK_COMPAT
	@echo "Checking glibc back compat..."
	$(AM_V_at) READELF=$(READELF) CPPFILT=$(CPPFILT) $(top_srcdir)/contrib/devtools/symbol-check.py < $(bin_PROGRAMS)
endif

check-security: $(bin_PROGRAMS)
if HARDEN
	@echo "Checking binary security..."
	$(AM_V_at) READELF=$(READELF) OBJDUMP=$(OBJDUMP) $(top_srcdir)/contrib/devtools/security-check.py < $(bin_PROGRAMS)
endif

if ENABLE_BIP70
%.pb.cc %.pb.h: %.proto
	@test -f $(PROTOC)
	$(AM_V_GEN) $(PROTOC) --cpp_out=$(@D) --proto_path=$(<D) $<
endif

if EMBEDDED_LEVELDB
include Makefile.leveldb.include
endif

if ENABLE_TESTS
include Makefile.test.include
endif

if ENABLE_BENCH
include Makefile.bench.include
endif

if ENABLE_QT
include Makefile.qt.include
endif

if ENABLE_QT_TESTS
include Makefile.qttest.include
endif
