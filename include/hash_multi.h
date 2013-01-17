/*******************************************************************************
 * DANIEL'S ALGORITHM IMPLEMENTAIONS
 *
 *  /\  |  _   _  ._ o _|_ |_  ._ _   _ 
 * /--\ | (_| (_) |  |  |_ | | | | | _> 
 *         _|                      
 * 
 * HASH BY MULTIPLICATION
 *
 * Features:
 * 	1. h(k) = (A*k mod 2^w) >> (w-r)
 *  2. bucket size(m): 2^r, eg, m = 8 = 2^3
 *	3. w: word size (usually 32-bit)
 * 	4. the value of A is chosen between 2^(w-r) and 2^w odd number.
 *
 ******************************************************************************/

#ifndef __HASH_MULTIPLICATION_H__
#define __HASH_MULTIPLICATION_H__

#include <math.h>
#include <string.h>
#include "generic.h"
#include "prime.h"

struct MultiHT {
	uint64_t A;
	uint32_t r; // prime
};

#define BITWIDTH 32

#define MULTI_HASH_TABLE_SIZE(ht) 1<<(ht->r)

/**
 * multi_hash_hash.
 */
inline uint32_t multi_hash_hash(uint32_t key, const struct MultiHT * ht)
{
	uint32_t hash;
	hash = ((ht->A * key)&0xFFFFFFFF)>>(BITWIDTH-ht->r); //mod 2^w equals logic bitmask ops
	return hash;
}

/**
 * init a hash table with size specified.
 */
inline struct MultiHT * multi_hash_init(uint32_t size)
{
	// find prime larger than log2(size)
	uint32_t r = ceil(log2(size));
	int i;
	for (i = r; ;i++) {
		if (is_prime(i)) {
			r = i;
			break;
		}
	}

	struct MultiHT * ht = (struct MultiHT *) malloc(sizeof(struct MultiHT));
	uint32_t a = 1 << (BITWIDTH-r);
	ht->A = a+1;
	ht->r = r;

	return ht;
}

#endif //
