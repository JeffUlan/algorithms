/*******************************************************************************
 * DANIEL'S ALGORITHM IMPLEMENTAIONS
 *
 *  /\  |  _   _  ._ o _|_ |_  ._ _   _ 
 * /--\ | (_| (_) |  |  |_ | | | | | _> 
 *         _|                      
 *
 * GENERIC HASH TABLE 
 *
 * Features:
 * 1. separate chaining for resolving collisions
 * 
 * http://en.wikipedia.org/wiki/Hash_table
 *
 ******************************************************************************/

#ifndef __HASH_TABLE_H__
#define __HASH_TABLE_H__

#include <stdint.h>
#include <limits.h>
#include "double_linked_list.h"
#include "hash_multi.h"

struct HashKV {
	uint32_t key;
	uintptr_t value;
	struct list_head node;
};

struct HashSlot {
	struct HashKV kv; 
	struct list_head head;	
};

struct HashTable {
	uint32_t size;		
	struct HashSlot * slots;
	struct MultiHash * multi;
};

/**
 * hash table create with size
 */
static inline struct HashTable * hash_table_create(uint32_t num_elements)
{
	struct HashTable * ht = (struct HashTable *)malloc(sizeof(struct HashTable));
	// init multiplication hash function
	ht->multi = multi_hash_init(num_elements);
	ht->size = MULTI_HASH_TABLE_SIZE(ht->multi);
	ht->slots = (struct HashSlot *)malloc(sizeof(struct HashSlot) * ht->size);

	int i;
	for (i=0; i<ht->size; i++) {
		ht->slots[i].kv.key = UINT_MAX;
		INIT_LIST_HEAD(&ht->slots[i].head);
	}

	return ht;
}

/**
 * set a value
 */
static inline void hash_table_set(struct HashTable * ht, uint32_t key, uintptr_t value)
{
	uint32_t hash = multi_hash(ht->multi, key);

	// found 
	if (ht->slots[hash].kv.key == key) {
		ht->slots[hash].kv.value = value;
		return;
	}
	
	// try list	
	struct HashKV * kv;
	list_for_each_entry(kv, &ht->slots[hash].head, node){
		if (kv->key == key) {
			kv->value = value;
			return;
		}
	}

	// create new key, and insert into list
	kv = (struct HashKV *)malloc(sizeof(struct HashKV));	
	kv->key = key;
	kv->value = value;
	
	list_add(&kv->node, &ht->slots[hash].head);
}

/**
 * get a value
 */
static inline uintptr_t hash_table_get(struct HashTable * ht, uint32_t key)
{
	uint32_t hash = multi_hash(ht->multi, key);

	// found 
	if (ht->slots[hash].kv.key == key) {
		return ht->slots[hash].kv.value;
	}
	
	// try list	
	struct HashKV * kv;
	list_for_each_entry(kv, &ht->slots[hash].head, node){
		if (kv->key == key) {
			return kv->value;
		}
	}

	return 0;
}

/**
 * hash table destroy
 */
static inline void hash_table_destroy(struct HashTable * ht)
{
	if (ht==NULL) return;
	free(ht->multi);

	struct HashKV * kv, *nkv;
	int i;
	for (i=0;i<ht->size;i++) {
		list_for_each_entry_safe(kv,nkv,&ht->slots[i].head, node){
			list_del(&kv->node);
			free(kv);
		}
	}

	free(ht->slots);
	free(ht);
}

#endif //
