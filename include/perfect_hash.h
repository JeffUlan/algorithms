/*******************************************************************************
 * DANIEL'S ALGORITHM IMPLEMENTAIONS
 *
 *  /\  |  _   _  ._ o _|_ |_  ._ _   _ 
 * /--\ | (_| (_) |  |  |_ | | | | | _> 
 *         _|                      
 *
 * PERFECT HASH
 * 
 * http://en.wikipedia.org/wiki/Perfect_hash 
 *
 ******************************************************************************/
#ifndef __PERFECT_HASH_H__
#define __PERFECT_HASH_H__
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <exception>
#include "generic.h"
#include "universal_hash.h"
#include "stack.h"

class PerfHTException: public std::exception
{
public:
	virtual const char * what() const throw()
	{
		return "key does not exist";
	}
};

template<typename T=uintptr_t>
class PerfHT {
private:
	// Level-2 Slot definition
	class SlotL2 {
	public:
		uint32_t cnt;	// collison count
		uint32_t key;	//key
		T value;		// value
	};

	// Level-1 Slot definition
	struct SlotL1 {
	public:
		uint32_t cnt;			 	// collison count
		struct UHash params;	 	// 2nd level 
		struct SlotL2 * lv2_slots;	// level 2 slots

		uint32_t key;				// key	
		T value;					// value

		~SlotL1() {
			if (cnt>1) delete [] lv2_slots;
		}
	};
	
	struct SlotL1 * slots;	// level 1 slots
	struct UHash params;   // 1st level 
	uint32_t num_slots;
	PerfHTException error;
public:
	PerfHT(uint32_t keys[], uint32_t len) {
		// remove duplicate keys
		uint32_t newlen = remove_dup<uint32_t>(keys, len);

		// 1-level hashing 
		uhash_init(&this->params, newlen);
		
		this->slots = new SlotL1[this->params.prime];
		for(uint32_t i=0;i<this->params.prime;i++) {
			this->slots[i].cnt = 0;
		}

		for (uint32_t i = 0; i < newlen; i++) {
			uint32_t hash = uhash_integer(&this->params, keys[i]);
			slots[hash].cnt++;
			slots[hash].key = keys[i];
		}

		// 2-level processing
		lv2_init(keys, newlen);
	};

	~PerfHT() {
		delete [] slots;
	}

	// return the 
	T& operator[] (uint32_t key) throw (PerfHTException) {
		uint32_t hash;
		hash  = uhash_integer(&params, key);
		printf("level1 %d->%d\n", key, slots[hash].key);
		if (slots[hash].key == key) {
			return slots[hash].value;
		} else if (slots[hash].cnt > 1) {	// maybe in the 2nd level slot
			SlotL1 & slot = slots[hash];
			uint32_t hash2 = uhash_integer(&slot.params, key);
			
			// 2nd-level available
			printf("level2 %d->%d\n", key, slot.lv2_slots[hash2].key);
			if (slot.lv2_slots[hash2].key == key) {
				return slot.lv2_slots[hash2].value;
			}
		}

		throw error;
	};

private:
	/**
	 * level-2 hash pre-work
	 * collect collides for each level-1 slots
	 */
	void lv2_init(uint32_t keys[], uint32_t len)
	{
		for (uint32_t i = 0; i < params.prime; i++) {
			if (slots[i].cnt > 1) {	
				// stacks for temporary storing keys
				Stack<uint32_t> collides(len);
				
				// find collide keys
				for(uint32_t j=0;j<len;j++) {
					if(uhash_integer(&params, keys[j]) == i) {
						collides.push(keys[j]);
					}
				}
				
				lv2_slot_init(&slots[i], collides); 
			}
		}
	}

	/**
	 * init level-2 slots with known collides 
	 * the routine will find another hash function never collides again!!
	 */
	void lv2_slot_init(struct SlotL1 * lv1_slot, Stack<uint32_t> & collides) {
		// init another hash function & 2nd level 
		uhash_init(&lv1_slot->params, lv1_slot->cnt * lv1_slot->cnt);
		SlotL2 * lv2_slots = new SlotL2[lv1_slot->params.prime];
		lv1_slot->lv2_slots = lv2_slots;
		
retry:
		for(uint32_t i=0;i<lv1_slot->params.prime;i++) {
			lv2_slots[i].cnt = 0;
		}

		// try another hash function
		uhash_init(&lv1_slot->params, lv1_slot->cnt * lv1_slot->cnt);

		// check collide	
		for(uint32_t i=0; i<collides.count();i++) {
			uint32_t key = collides[i];
			uint32_t hash = uhash_integer(&lv1_slot->params, key);
			lv2_slots[hash].key = key;
			if (++lv2_slots[hash].cnt > 1) { goto retry; }
		}
	}
};

#endif //
