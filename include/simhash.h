/*******************************************************************************
 * DANIEL'S ALGORITHM IMPLEMENTAIONS
 *
 *  /\  |  _   _  ._ o _|_ |_  ._ _   _ 
 * /--\ | (_| (_) |  |  |_ | | | | | _> 
 *         _|                      
 *
 * SIMHASH FUNCTIONS
 *
 * http://matpalm.com/resemblance/simhash/
 * 2. http://www.isthe.com/chongo/tech/comp/fnv/
 *
 ******************************************************************************/

#ifndef __SIMHASH_H__
#define __SIMHASH_H__

#include <string.h>
#include <stdint.h>
#include "hash_string.h"

namespace alg {
	class SimHash {
	private:
		int V[32];
	public:
		SimHash() {
			memset(V, 0, sizeof(V));
		}

		void AddWord(const char * word, uint32_t len) {
			uint32_t hash = hash_fnv1a(word,len);
			for(int i=0;i<32;i++) {
				if (hash&(1<<i)) {
					V[i]++;
				}
			}
		}

		uint32_t Hash() {
			uint32_t hash=0;
			for(int i=0;i<32;i++) {
				if (V[i] > 0) {
					hash|= (1<<i);
				}
			}

			return hash;
		}
	};
}

#endif //
