/*******************************************************************************
 * DANIEL'S ALGORITHM IMPLEMENTAIONS
 *
 *  /\  |  _   _  ._ o _|_ |_  ._ _   _ 
 * /--\ | (_| (_) |  |  |_ | | | | | _> 
 *         _|                      
 *
 * PRIORITY QUEUE 
 *
 * Features:
 * 1. A queue with prioity implemented in double linked list.
 * 2. The queue is in ascending order of priority.
 *
 * http://en.wikipedia.org/wiki/Priority_queue
 *
 ******************************************************************************/

#ifndef __PRIORITY_QUEUE_H__
#define __PRIORITY_QUEUE_H__

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

#include "double_linked_list.h"

namespace alg 
{
	/**
	 * definition of a Priority Queue.
	 */
	template<typename T>
	class PQ {
		/**
		 * definition of a node of priority queue.
		 */
		struct PQNode {
			int priority;		
			T value;
			struct list_head node;
		};

	private:
		uint32_t m_count;
		struct list_head m_head;	
	public:
		/**
		 * create an empty priority queue.
		 */
		PQ() 
		{
			m_count = 0;
			INIT_LIST_HEAD(&m_head);
		}
	
		~PQ()
		{
			PQNode * pos, * n;
			list_for_each_entry_safe(pos,n, &m_head, node) {
				list_del(&pos->node);
				delete pos;
			}
		}

		/**
		 * queue a value with priority into the priority queue.
		 */
		void queue(const T &value, uint32_t priority)
		{
			PQNode * n = new PQNode;
			n->priority = priority;
			n->value = value;

			if (list_empty(&m_head))	// empty list, just add in.
			{
				list_add(&n->node, &m_head);
				m_count++;
			}
			else
			{
				// sequentially find the apropriate position
				PQNode * pos;
				bool found = false;
				list_for_each_entry(pos, &m_head, node) {
					if (n->priority <= pos->priority) {
						__list_add(&n->node, pos->node.prev, &pos->node);
						m_count++;
						found = true;
						break;
					}
				}

				if (!found) {	// we reach the end of the list.
					list_add_tail(&n->node, &m_head);
					m_count++;
				}
			}
		}
		
		/**
		 * dequeue the most priority element, i.e. the first element.
		 * return 0 when the list is empty.
		 * check is_empty() before dequeue().
		 */
		const T & dequeue(int * prio)
		{
			if (list_empty(&m_head)) return 0;

			PQNode * n;
			n = list_entry(m_head.next, PQNode, node);
			list_del(&n->node);
			m_count--;

			T ret = n->value;
			*prio = n->priority;
			delete n;

			return ret;
		}

		/**
		 * test whether the priority queue is empty
		 */
		inline bool is_empty() const {
			if (list_empty(&m_head)) return true;
			return false;
		}

		/**
		 * get the exact number of data
		 */
		inline uint32_t count() const { return m_count; }
	};
}

#endif //
