/*******************************************************************************
 * ALGORITHM IMPLEMENTAIONS
 *
 *  /\  |  _   _  ._ o _|_ |_  ._ _   _ 
 * /--\ | (_| (_) |  |  |_ | | | | | _> 
 *         _|                      
 *
 * B-TREE
 *
 * In computer science, a B-tree is a tree data structure that keeps data sorted 
 * and allows searches, sequential access, insertions, and deletions in 
 * logarithmic time. The B-tree is a generalization of a binary search tree in 
 * that a node can have more than two children. (Comer 1979, p. 123) Unlike 
 * self-balancing binary search trees, the B-tree is optimized for systems that 
 * read and write large blocks of data. It is commonly used in databases and 
 * filesystems.
 *
 * http://en.wikipedia.org/wiki/B-tree
 ******************************************************************************/

#ifndef __BTREE_H__
#define __BTREE_H__

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <memory>

#define BLOCKSIZE	4096
#define T 255
namespace alg {
	class BTree {
	private:
		// 4K node, 4096 bytes to write
		// t = 255
		struct node_t {
			int16_t leaf;		// is leaf?
			int16_t n;			// num key
			int32_t offset;		// block offset (8 byte head)
			int32_t key[509];	// key
			int32_t c[510];		// childs pointers (file offsets related to 0)
			char padding[12];	// padding to 4096
		} __attribute__ ((packed));
		typedef struct node_t *node;

	public:
		/**
		 * search result
		 */
		struct search_r {
			node n;
			int32_t i;
		};
	private:
		node m_root;
		int fd;
	private:
		BTree(const BTree &);
		BTree& operator=(const BTree&);
	public:
		BTree(const char * path) {
			fd = open(path, O_RDWR|O_CREAT, 0640);
			if (fd == -1)
				return;
			node x = (node)allocate_node();
			int n = read(fd,x,BLOCKSIZE);
			if (n != BLOCKSIZE) {	// init new btree
				x->leaf = true;
				WRITE(x);
			}
			m_root = (node)x;
		}

		~BTree() {
			close(fd);
		}
		
		search_r Search(int32_t x) {
			return search(m_root, x);
		}

		void Insert(int32_t k) {
			node r = m_root;
			if (r->n == 2*T - 1) {
				node s = (node)allocate_node();
				// place the old root node to the end of the file
				m_root->offset = -1;
				WRITE(m_root);	
				// new root
				s->offset = 0;
				s->n = 0;
				s->c[0] = m_root->offset;
				free(m_root);
				m_root = s;
				split_child(s, 0);
				insert_nonfull(s, k);
			} else {
				insert_nonfull(r, k);
			}
		}

	private:
		/**
		 * search a key, returns node and index
		 */
		search_r search(node x, int32_t k) {
			int i = 0;
			search_r ret;
			while (i<x->n && k > x->key[i]) i++;

			if (i < x->n && k == x->key[i]) {
				ret.n = x, ret.i = i;
				return ret;
			} else if (x->leaf) {
				ret.n = NULL, ret.i = i;
				return ret;
			} else {
				std::auto_ptr<node_t> xi(READ(x, i));
				return search(xi.get(), k);
			}
		}

		/**
		 * insert into non-full node
		 */
		void insert_nonfull(node x, int32_t k) {
			int32_t i = x->n-1;
			if (x->leaf) {
				while (i>=0 && k <x->key[i]) {
					x->key[i+1] = x->key[i];
					i = i - 1;
				}
				x->key[i+1] = k;
				x->n = x->n + 1;
				WRITE(x);
			} else {
				while(i>=0 && k < x->key[i]) {
					i = i-1;
				}
				i=i+1;
				std::auto_ptr<node_t> xi(READ(x, i));
				if (xi->n == 2*T-1) {
					split_child(x, i);
					if (k > x->key[i]) {
						i = i+1;
					}
				}
				insert_nonfull(xi.get(), k);
			}
		}

		// disk ops
		void * allocate_node() {
			node x = (node)malloc(sizeof(node_t));
			x->leaf = false;
			x->n = 0;
			x->offset = -1;
			memset(x->key, 0, sizeof(x->key));
			memset(x->c, 0, sizeof(x->c));
			return x;
		}

		void split_child(node x, int32_t i) {
			std::auto_ptr<node_t> z((node)allocate_node());
			std::auto_ptr<node_t> y(READ(x, i));
			z->leaf = y->leaf;
			z->n = T - 1;

			int j;
			for (j=0;j<T-1;j++) {	// init z
				z->key[j] = y->key[j+T];
			}

			if (!y->leaf) {
				for (j=0;j<T;j++) {
					z->c[j] = y->c[j+T];
				}
			}

			y->n = T-1;	// splited y
			WRITE(y.get());
			WRITE(z.get());

			for (j=x->n;j>=i+1;j--) {
				x->c[j+1] = x->c[j];	// shift
			}

			// relocate z
			x->c[i+1] = z->offset;

			for (j=x->n-1;j>=i;j--) {
				x->key[j+1] = x->key[j];
			}
			x->key[i] = y->key[T];
			x->n = x->n +1;
			WRITE(x);
		}

		node READ(node x, int32_t i) {
			void *xi = allocate_node();
			lseek(fd, x->c[i], SEEK_SET);
			read(fd, xi, BLOCKSIZE);
			return (node)xi;
		}

		void WRITE(node x) {
			if (x->offset !=-1) {
				lseek(fd, x->offset, SEEK_SET);
			} else {
				x->offset = lseek(fd,0, SEEK_END);
			}
			write(fd, x, BLOCKSIZE);
		}
	};
}
#endif //
