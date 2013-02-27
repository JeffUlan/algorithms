#include <stdio.h>
#include <stdio.h>
#include <stdlib.h> 
#include <time.h>

#include "directed_graph.h"
#include "dijkstra.h"

/**
 * randomly generate a graph, for test purpose
 */
struct Graph * directed_graph_rand(int nvertex) 
{
	struct Graph * g = directed_graph_create();
	int i;	
	
	for(i=0;i<nvertex;i++) {
		directed_graph_add_vertex(g, i);
	}

	// random connect
	for(i=0;i<nvertex;i++) {
		int j;
		for(j=i+1;j<nvertex;j++) {
			int dice = rand()%5;
			if (dice == 0) {  // chance 20%
				int w = rand()%100;
				directed_graph_add_edge(g, i, j, w);
			}
		}
	}
	
	return g;
}

int main(void)
{
	using namespace alg;
	srand(time(NULL));
	int NVERTEX = 50;
	struct Graph * g = directed_graph_rand(NVERTEX);
	directed_graph_print(g);

	printf("finding Dijkstra shortest path starting from 0: \n");	
	Dijkstra dijkstra(g, 0);
	struct Adjacent * a;
	HashTable<int32_t> & result = dijkstra.run();

	list_for_each_entry(a, &g->a_head, a_node){
		printf("previous of %u is ", a->v.id);
		int32_t pre = result[a->v.id];
		if (pre ==UNDEFINED) { printf("UNDEFINED\n"); }
		else printf("%d\n", pre);
	}
	
	graph_free(g);
	exit(0);	
}
