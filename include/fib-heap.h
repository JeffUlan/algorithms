/*******************************************************************************
 * DANIEL'S ALGORITHM IMPLEMENTAIONS
 *
 *  /\  |  _   _  ._ o _|_ |_  ._ _   _ 
 * /--\ | (_| (_) |  |  |_ | | | | | _> 
 *         _|                      
 *
 * FIBONACCI HEAP
 *
 * In computer science, a Fibonacci heap is a heap data structure consisting of 
 * a collection of trees. It has a better amortized running time than a binomial
 * heap. Fibonacci heaps were developed by Michael L. Fredman and Robert E. Tarjan
 * in 1984 and first published in a scientific journal in 1987. The name of 
 * Fibonacci heap comes from Fibonacci numbers which are used in the 
 * running time analysis.
 *
 * http://en.wikipedia.org/wiki/Fibonacci_heap
 ******************************************************************************/

#ifndef __FIB_HEAP_H__
#define __FIB_HEAP_H__
#include <math.h>
#include <stdint.h>
#include <unistd.h>
#include "double_linked_list.h"
namespace alg {
		template<typename _Key, typename _Val>
		class FibHeap {
			public:
				typedef _Key key_type;
				typedef _Val value_type;
				struct node_t {
					int32_t degree;
					node_t * parent;
					bool mark;
					key_type key;
					value_type value;
					struct list_head child_head;	// child list head
					struct list_head node;	// sibling list
				};
				typedef struct node_t *Node;
			private:
				FibHeap(const FibHeap &);
				FibHeap& operator=(const FibHeap&);
			private:
				int32_t n;	
				Node min;
				struct list_head m_root;	// root list
			public:
				FibHeap():n(0),min(NULL){
					INIT_LIST_HEAD(&m_root);
				}

				/**
				 * insert a value into the Fibonacci Heap
				 */
				void Insert(key_type key, value_type value) {
					Node x = new node_t;
					x->degree = 0;
					x->parent = NULL;
					x->mark = false;
					x->key = key;
					x->value = value;
					INIT_LIST_HEAD(&x->child_head);
					if (min == NULL) {
						min = x;
						list_add(&x->node, &m_root);
					} else {
						list_add(&x->node, &m_root);
						if (x->key < min->key) {
							min = x;
						}
					}
					n = n+1;
				}

				/**
				 * Union 2 Fibonacci-Heap
				 */
				static FibHeap* Union(FibHeap *H1, FibHeap *H2) {
					FibHeap * H = new FibHeap();
					H->min = H1->min;
					H->m_root = H1->m_root;
					list_splice(&H->m_root, &H1->m_root);	// concat 2 root-list
					list_splice(&H->m_root, &H2->m_root);
					if (H1->min == NULL || (H2.min != NULL && H2->min.key < H1->min.key)) {
						H->min = H2->min;
					}
					H->n = H1->n + H2->n;
					return H;
				}

				/**
				 * Extract Min Element
				 */
				Node ExtractMin() {
					Node z = min;
					if (z != NULL) {
						Node x, xs;
						// for each child x of z, add x to the root list of H
						list_for_each_entry_safe(x, xs, &z->child_head, node) {
							list_del(&x->node);
							list_add(&x->node, &m_root);
							x->parent = NULL;
						}

						if (z->node.next != &m_root) {	// pick one sibling 
							min = list_entry(z->node.next, node_t, node);
							list_del(&z->node);
							Consolidate();
						} else if (z->node.prev != &m_root ) {	
							min = list_entry(z->node.prev, node_t, node);
							list_del(&z->node);
							Consolidate();
						} else { // the only node on the root list
							min = NULL;
						}
						// remove z from the root list of H
						n = n + 1;
					}
					return z;
				}

				void Consolidate() {
					int32_t dn = D(n);
					Node A[dn+1];			// let A[0..D(H.n)] to be a new array
					int32_t i;	
					for (i=0;i<=dn;i++) {
						A[i] = NULL;
					}

					Node w, ws;
					// for each node w in the root list of H
					list_for_each_entry_safe(w, ws, &m_root, node){
						Node x = w;
						printf("%d %d\n", x->degree, x->key);
						int32_t d = x->degree;
						while (A[d] != NULL) {
							Node y = A[d];	// another node with the same degree as x
							if (x->key > y->key) {	// exchange x with y
								Node tmp = x;
								x = y;
								y = tmp;
							}
							Link(y,x);
							A[d] = NULL;
							d = d + 1;
						}
						A[d] = x;
					}
					min = NULL;
					for (i=0;i<=dn;i++) {
						if (A[i]!=NULL) {
							if (min == NULL) {
								// insert into rootlist
								list_add(&A[i]->node, &m_root);
								min = A[i];
							} else {
								list_add(&A[i]->node, &m_root);
								if (A[i]->key < min->key) {
									min = A[i];
								}
							}
						}
					}
				}
			private:	
				int32_t D(int32_t n) {
					return int32_t(ceil(log(n)));
				}

				void Link(Node y, Node x) {
					y->parent = x;
					list_add(&y->node, &x->child_head);
					x->degree = x->degree + 1;
					y->mark = false;
				}
		};
}

#endif //
