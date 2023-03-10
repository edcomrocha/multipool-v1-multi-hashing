#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "../common/sha3/sph_blake.h"
#include "../common/sha3/sph_bmw.h"
#include "../common/sha3/sph_groestl.h"
#include "../common/sha3/sph_jh.h"
#include "../common/sha3/sph_keccak.h"
#include "../common/sha3/sph_skein.h"
#include "../common/sha3/sph_luffa.h"
#include "../common/sha3/sph_cubehash.h"
#include "../common/sha3/sph_shavite.h"
#include "../common/sha3/sph_simd.h"
#include "../common/sha3/sph_echo.h"
#include "../common/sha3/sph_hamsi.h"
#include "../common/sha3/sph_fugue.h"
#include "../common/sha3/sph_shabal.h"
#include "../common/sha3/sph_whirlpool.h"
#include "../common/sha3/sph_sha2.h"
#include "../common/sha3/sph_tiger.h"

//#include "common.h"

enum Algo {
	BLAKE = 0,
	BMW,
	GROESTL,
	JH,
	KECCAK,
	SKEIN,
	LUFFA,
	CUBEHASH,
	SHAVITE,
	SIMD,
	ECHO,
	HAMSI,
	FUGUE,
	SHABAL,
	WHIRLPOOL,
	SHA512,
	HASH_FUNC_COUNT
};

enum AlgoV2 {
	V2_BLAKE = 0,
	V2_BMW,
	V2_GROESTL,
	V2_JH,
	V2_TIGER_KECCAK,
	V2_SKEIN,
	V2_TIGER_LUFFA,
	V2_CUBEHASH,
	V2_SHAVITE,
	V2_SIMD,
	V2_ECHO,
	V2_HAMSI,
	V2_FUGUE,
	V2_SHABAL,
	V2_WHIRLPOOL,
	V2_TIGER_SHA512,
	V2_HASH_FUNC_COUNT
};

static void getAlgoString(const uint8_t* prevblock, char *output, int hashFuncCount)
{
	char *sptr = output;
	int j;

	for (j = 0; j < hashFuncCount; j++) {
		char b = (15 - j) >> 1; // 16 ascii hex chars, reversed
		uint8_t algoDigit = (j & 1) ? prevblock[b] & 0xF : prevblock[b] >> 4;
		if (algoDigit >= 10)
			sprintf(sptr, "%c", 'A' + (algoDigit - 10));
		else
			sprintf(sptr, "%u", (uint32_t) algoDigit);
		sptr++;
	}
	*sptr = '\0';
}

void x16r_hash(const char* input, char* output, uint32_t len)
{
	uint32_t hash[64/4];
	char hashOrder[HASH_FUNC_COUNT + 1] = { 0 };

	sph_blake512_context     ctx_blake;
	sph_bmw512_context       ctx_bmw;
	sph_groestl512_context   ctx_groestl;
	sph_skein512_context     ctx_skein;
	sph_jh512_context        ctx_jh;
	sph_keccak512_context    ctx_keccak;
	sph_luffa512_context     ctx_luffa;
	sph_cubehash512_context  ctx_cubehash;
	sph_shavite512_context   ctx_shavite;
	sph_simd512_context      ctx_simd;
	sph_echo512_context      ctx_echo;
	sph_hamsi512_context     ctx_hamsi;
	sph_fugue512_context     ctx_fugue;
	sph_shabal512_context    ctx_shabal;
	sph_whirlpool_context    ctx_whirlpool;
	sph_sha512_context       ctx_sha512;

	void *in = (void*) input;
	int size = len;
    int i;

	getAlgoString(&input[4], hashOrder, HASH_FUNC_COUNT);

	for (i = 0; i < 16; i++)
	{
		const char elem = hashOrder[i];
		const uint8_t algo = elem >= 'A' ? elem - 'A' + 10 : elem - '0';

		switch (algo) {
		case BLAKE:
			sph_blake512_init(&ctx_blake);
			sph_blake512(&ctx_blake, in, size);
			sph_blake512_close(&ctx_blake, hash);
			break;
		case BMW:
			sph_bmw512_init(&ctx_bmw);
			sph_bmw512(&ctx_bmw, in, size);
			sph_bmw512_close(&ctx_bmw, hash);
			break;
		case GROESTL:
			sph_groestl512_init(&ctx_groestl);
			sph_groestl512(&ctx_groestl, in, size);
			sph_groestl512_close(&ctx_groestl, hash);
			break;
		case SKEIN:
			sph_skein512_init(&ctx_skein);
			sph_skein512(&ctx_skein, in, size);
			sph_skein512_close(&ctx_skein, hash);
			break;
		case JH:
			sph_jh512_init(&ctx_jh);
			sph_jh512(&ctx_jh, in, size);
			sph_jh512_close(&ctx_jh, hash);
			break;
		case KECCAK:
			sph_keccak512_init(&ctx_keccak);
			sph_keccak512(&ctx_keccak, in, size);
			sph_keccak512_close(&ctx_keccak, hash);
			break;
		case LUFFA:
			sph_luffa512_init(&ctx_luffa);
			sph_luffa512(&ctx_luffa, in, size);
			sph_luffa512_close(&ctx_luffa, hash);
			break;
		case CUBEHASH:
			sph_cubehash512_init(&ctx_cubehash);
			sph_cubehash512(&ctx_cubehash, in, size);
			sph_cubehash512_close(&ctx_cubehash, hash);
			break;
		case SHAVITE:
			sph_shavite512_init(&ctx_shavite);
			sph_shavite512(&ctx_shavite, in, size);
			sph_shavite512_close(&ctx_shavite, hash);
			break;
		case SIMD:
			sph_simd512_init(&ctx_simd);
			sph_simd512(&ctx_simd, in, size);
			sph_simd512_close(&ctx_simd, hash);
			break;
		case ECHO:
			sph_echo512_init(&ctx_echo);
			sph_echo512(&ctx_echo, in, size);
			sph_echo512_close(&ctx_echo, hash);
			break;
		case HAMSI:
			sph_hamsi512_init(&ctx_hamsi);
			sph_hamsi512(&ctx_hamsi, in, size);
			sph_hamsi512_close(&ctx_hamsi, hash);
			break;
		case FUGUE:
			sph_fugue512_init(&ctx_fugue);
			sph_fugue512(&ctx_fugue, in, size);
			sph_fugue512_close(&ctx_fugue, hash);
			break;
		case SHABAL:
			sph_shabal512_init(&ctx_shabal);
			sph_shabal512(&ctx_shabal, in, size);
			sph_shabal512_close(&ctx_shabal, hash);
			break;
		case WHIRLPOOL:
			sph_whirlpool_init(&ctx_whirlpool);
			sph_whirlpool(&ctx_whirlpool, in, size);
			sph_whirlpool_close(&ctx_whirlpool, hash);
			break;
		case SHA512:
			sph_sha512_init(&ctx_sha512);
			sph_sha512(&ctx_sha512,(const void*) in, size);
			sph_sha512_close(&ctx_sha512,(void*) hash);
			break;
		}
		in = (void*) hash;
		size = 64;
	}
	memcpy(output, hash, 32);
}

void x16rv2_hash(const char* input, char* output, uint32_t len)
{
	uint32_t hash[64/4];
	char hashOrder[V2_HASH_FUNC_COUNT + 1] = { 0 };

	sph_blake512_context     ctx_blake;
	sph_bmw512_context       ctx_bmw;
	sph_groestl512_context   ctx_groestl;
	sph_jh512_context        ctx_jh;
	sph_keccak512_context    ctx_keccak;
	sph_skein512_context     ctx_skein;
	sph_luffa512_context     ctx_luffa;
	sph_cubehash512_context  ctx_cubehash;
	sph_shavite512_context   ctx_shavite;
	sph_simd512_context      ctx_simd;
	sph_echo512_context      ctx_echo;
	sph_hamsi512_context     ctx_hamsi;
	sph_fugue512_context     ctx_fugue;
	sph_shabal512_context    ctx_shabal;
	sph_whirlpool_context    ctx_whirlpool;
	sph_sha512_context       ctx_sha512;
	sph_tiger_context        ctx_tiger;

	void *in = (void*) input;
	int size = len;
    int i;
	int j;

	getAlgoString(&input[4], hashOrder, V2_HASH_FUNC_COUNT);

	for (i = 0; i < 16; i++)
	{
		const char elem = hashOrder[i];
		const uint8_t algo = elem >= 'A' ? elem - 'A' + 10 : elem - '0';

		switch (algo) {
		case V2_BLAKE:
			sph_blake512_init(&ctx_blake);
			sph_blake512(&ctx_blake, in, size);
			sph_blake512_close(&ctx_blake, hash);
			break;
		case V2_BMW:
			sph_bmw512_init(&ctx_bmw);
			sph_bmw512(&ctx_bmw, in, size);
			sph_bmw512_close(&ctx_bmw, hash);
			break;
		case V2_GROESTL:
			sph_groestl512_init(&ctx_groestl);
			sph_groestl512(&ctx_groestl, in, size);
			sph_groestl512_close(&ctx_groestl, hash);
			break;
		case V2_JH:
			sph_jh512_init(&ctx_jh);
			sph_jh512(&ctx_jh, in, size);
			sph_jh512_close(&ctx_jh, hash);
			break;
		case V2_TIGER_KECCAK:
			sph_tiger_init(&ctx_tiger);
			sph_tiger(&ctx_tiger, in, size);
			sph_tiger_close(&ctx_tiger, hash);
			for (j = 24; j < 64; ++j) {
				((uint8_t*)hash)[j] = 0; // Pad the 24 bytes to bring it to 64 bytes
			}

			sph_keccak512_init(&ctx_keccak);
			sph_keccak512(&ctx_keccak, hash, 64);
			sph_keccak512_close(&ctx_keccak, hash);
			break;
		case V2_SKEIN:
			sph_skein512_init(&ctx_skein);
			sph_skein512(&ctx_skein, in, size);
			sph_skein512_close(&ctx_skein, hash);
			break;
		case V2_TIGER_LUFFA:
			sph_tiger_init(&ctx_tiger);
			sph_tiger(&ctx_tiger, in, size);
			sph_tiger_close(&ctx_tiger, hash);
			for (j = 24; j < 64; ++j) {
				((uint8_t*)hash)[j] = 0; // Pad the 24 bytes to bring it to 64 bytes
			}

			sph_luffa512_init(&ctx_luffa);
			sph_luffa512(&ctx_luffa, hash, 64);
			sph_luffa512_close(&ctx_luffa, hash);
			break;
		case V2_CUBEHASH:
			sph_cubehash512_init(&ctx_cubehash);
			sph_cubehash512(&ctx_cubehash, in, size);
			sph_cubehash512_close(&ctx_cubehash, hash);
			break;
		case V2_SHAVITE:
			sph_shavite512_init(&ctx_shavite);
			sph_shavite512(&ctx_shavite, in, size);
			sph_shavite512_close(&ctx_shavite, hash);
			break;
		case V2_SIMD:
			sph_simd512_init(&ctx_simd);
			sph_simd512(&ctx_simd, in, size);
			sph_simd512_close(&ctx_simd, hash);
			break;
		case V2_ECHO:
			sph_echo512_init(&ctx_echo);
			sph_echo512(&ctx_echo, in, size);
			sph_echo512_close(&ctx_echo, hash);
			break;
		case V2_HAMSI:
			sph_hamsi512_init(&ctx_hamsi);
			sph_hamsi512(&ctx_hamsi, in, size);
			sph_hamsi512_close(&ctx_hamsi, hash);
			break;
		case V2_FUGUE:
			sph_fugue512_init(&ctx_fugue);
			sph_fugue512(&ctx_fugue, in, size);
			sph_fugue512_close(&ctx_fugue, hash);
			break;
		case V2_SHABAL:
			sph_shabal512_init(&ctx_shabal);
			sph_shabal512(&ctx_shabal, in, size);
			sph_shabal512_close(&ctx_shabal, hash);
			break;
		case V2_WHIRLPOOL:
			sph_whirlpool_init(&ctx_whirlpool);
			sph_whirlpool(&ctx_whirlpool, in, size);
			sph_whirlpool_close(&ctx_whirlpool, hash);
			break;
		case V2_TIGER_SHA512:
			sph_tiger_init(&ctx_tiger);
			sph_tiger(&ctx_tiger, in, size);
			sph_tiger_close(&ctx_tiger, hash);
			for (j = 24; j < 64; ++j) {
				((uint8_t*)hash)[j] = 0; // Pad the 24 bytes to bring it to 64 bytes
			}

			sph_sha512_init(&ctx_sha512);
			sph_sha512(&ctx_sha512,(const void*) hash, 64);
			sph_sha512_close(&ctx_sha512,(void*) hash);
			break;
		}
		in = (void*) hash;
		size = 64;
	}
	memcpy(output, hash, 32);
}
