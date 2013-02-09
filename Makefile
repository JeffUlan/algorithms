.PHONY: all clean
CC=gcc
CPP=g++
AR=ar
RANLIB=ranlib
CFLAGS=-g -Wall
SRCDIR = ./src
INCLUDEDIR = ./include
DEPS = 
LIBS = -lm
PROGRAMS =  insertion_sort_demo \
			radix_sort_demo \
			shuffle_demo \
			quick_sort_demo \
			merge_sort_demo \
			random_select_demo \
			prime_sieve_eratosthenes \
			hash_multi_demo \
			hash_table_demo \
			double_linked_list_demo \
			stack_demo \
			queue_demo \
			priority_queue_demo \
			prime_test \
			universal_hash_demo \
			perfect_hash_demo \
			binary_search_tree_demo \
			rbtree_demo \
			heap_demo \
			interval_tree_demo \
			dos_tree_demo \
			skip_list_demo \
			lcs_demo	\
			graph_demo \
			prim_mst_demo \
			directed_graph_demo \
			dijkstra_demo 	\
			bellman_ford_demo \
			graph_search_demo \
			hash_string_demo \
			bitset_demo	\
			bloom_filter_demo \
			sha1_demo	\
			huffman_demo \
			word_seg_demo 
			

all: $(PROGRAMS)

heap_demo: $(SRCDIR)/heap_demo.c $(DEPS)
	$(CC) $(CFLAGS) -o $@ $< -I$(INCLUDEDIR) $(LIBS)

insertion_sort_demo: $(SRCDIR)/insertion_sort_demo.c $(DEPS)
	$(CC) $(CFLAGS) -o $@ $< -I$(INCLUDEDIR) $(LIBS)

radix_sort_demo: $(SRCDIR)/radix_sort_demo.c $(DEPS)
	$(CC) $(CFLAGS) -o $@ $< -I$(INCLUDEDIR) $(LIBS)

shuffle_demo: $(SRCDIR)/shuffle_demo.c $(DEPS)
	$(CC) $(CFLAGS) -o $@ $< -I$(INCLUDEDIR) $(LIBS)

quick_sort_demo: $(SRCDIR)/quick_sort_demo.c $(DEPS)
	$(CC) $(CFLAGS) -o $@ $< -I$(INCLUDEDIR) $(LIBS)

merge_sort_demo: $(SRCDIR)/merge_sort_demo.c $(DEPS)
	$(CC) $(CFLAGS) -o $@ $< -I$(INCLUDEDIR) $(LIBS)

random_select_demo: $(SRCDIR)/random_select_demo.c $(DEPS)
	$(CC) $(CFLAGS) -o $@ $< -I$(INCLUDEDIR) $(LIBS)

prime_sieve_eratosthenes: $(SRCDIR)/prime_sieve_eratosthenes.c $(DEPS)
	$(CC) $(CFLAGS) -o $@ $< -I$(INCLUDEDIR) $(LIBS)

hash_multi_demo: $(SRCDIR)/hash_multi_demo.c $(DEPS)
	$(CC) $(CFLAGS) -o $@ $< -I$(INCLUDEDIR) $(LIBS)

hash_table_demo: $(SRCDIR)/hash_table_demo.c $(DEPS)
	$(CC) $(CFLAGS) -o $@ $< -I$(INCLUDEDIR) $(LIBS)

double_linked_list_demo: $(SRCDIR)/double_linked_list_demo.c $(DEPS)
	$(CC) $(CFLAGS) -o $@ $< -I$(INCLUDEDIR) $(LIBS)

stack_demo: $(SRCDIR)/stack_demo.c $(DEPS)
	$(CC) $(CFLAGS) -o $@ $< -I$(INCLUDEDIR) $(LIBS)

queue_demo: $(SRCDIR)/queue_demo.c $(DEPS)
	$(CC) $(CFLAGS) -o $@ $< -I$(INCLUDEDIR) $(LIBS)

priority_queue_demo: $(SRCDIR)/priority_queue_demo.c $(DEPS)
	$(CC) $(CFLAGS) -o $@ $< -I$(INCLUDEDIR) $(LIBS)

prime_test: $(SRCDIR)/prime_test.c $(DEPS)
	$(CC) $(CFLAGS) -o $@ $< -I$(INCLUDEDIR) $(LIBS)

universal_hash_demo: $(SRCDIR)/universal_hash_demo.c $(DEPS)
	$(CC) $(CFLAGS) -o $@ $< -I$(INCLUDEDIR) $(LIBS)

perfect_hash_demo: $(SRCDIR)/perfect_hash_demo.c $(DEPS)
	$(CC) $(CFLAGS) -o $@ $< -I$(INCLUDEDIR) $(LIBS)

binary_search_tree_demo: $(SRCDIR)/binary_search_tree_demo.c $(DEPS)
	$(CC) $(CFLAGS) -o $@ $< -I$(INCLUDEDIR) $(LIBS)

rbtree_demo: $(SRCDIR)/rbtree_demo.c $(DEPS)
	$(CC) $(CFLAGS) -o $@ $< -I$(INCLUDEDIR) $(LIBS)

interval_tree_demo: $(SRCDIR)/interval_tree_demo.c $(DEPS)
	$(CC) $(CFLAGS) -o $@ $< -I$(INCLUDEDIR) $(LIBS)

dos_tree_demo: $(SRCDIR)/dos_tree_demo.c $(DEPS)
	$(CC) $(CFLAGS) -o $@ $< -I$(INCLUDEDIR) $(LIBS)

skip_list_demo: $(SRCDIR)/skip_list_demo.c $(DEPS)
	$(CC) $(CFLAGS) -o $@ $< -I$(INCLUDEDIR) $(LIBS)

lcs_demo: $(SRCDIR)/lcs_demo.c $(DEPS)
	$(CC) $(CFLAGS) -o $@ $< -I$(INCLUDEDIR) $(LIBS)

graph_demo: $(SRCDIR)/graph_demo.c $(DEPS)
	$(CC) $(CFLAGS) -o $@ $< -I$(INCLUDEDIR) $(LIBS)

prim_mst_demo: $(SRCDIR)/prim_mst_demo.c $(DEPS)
	$(CC) $(CFLAGS) -o $@ $< -I$(INCLUDEDIR) $(LIBS)

directed_graph_demo: $(SRCDIR)/directed_graph_demo.c $(DEPS)
	$(CC) $(CFLAGS) -o $@ $< -I$(INCLUDEDIR) $(LIBS)

dijkstra_demo: $(SRCDIR)/dijkstra_demo.c $(DEPS)
	$(CC) $(CFLAGS) -o $@ $< -I$(INCLUDEDIR) $(LIBS)

bellman_ford_demo: $(SRCDIR)/bellman_ford_demo.c $(DEPS)
	$(CC) $(CFLAGS) -o $@ $< -I$(INCLUDEDIR) $(LIBS)

graph_search_demo: $(SRCDIR)/graph_search_demo.c $(DEPS)
	$(CC) $(CFLAGS) -o $@ $< -I$(INCLUDEDIR) $(LIBS)

hash_string_demo: $(SRCDIR)/hash_string_demo.c $(DEPS)
	$(CC) $(CFLAGS) -o $@ $< -I$(INCLUDEDIR) $(LIBS)

bitset_demo: $(SRCDIR)/bitset_demo.c $(DEPS)
	$(CC) $(CFLAGS) -o $@ $< -I$(INCLUDEDIR) $(LIBS)

bloom_filter_demo: $(SRCDIR)/bloom_filter_demo.c $(DEPS)
	$(CC) $(CFLAGS) -o $@ $< -I$(INCLUDEDIR) $(LIBS)

sha1_demo: $(SRCDIR)/sha1_demo.c $(DEPS)
	$(CC) $(CFLAGS) -o $@ $< -I$(INCLUDEDIR) $(LIBS)

huffman_demo: $(SRCDIR)/huffman_demo.c $(DEPS)
	$(CC) $(CFLAGS) -o $@ $< -I$(INCLUDEDIR) $(LIBS)

word_seg_demo: $(SRCDIR)/word_seg_demo.c $(DEPS)
	$(CC) $(CFLAGS) -o $@ $< -I$(INCLUDEDIR) $(LIBS) 

clean:
	rm -rf $(PROGRAMS) *.dSYM
