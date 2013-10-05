#include <stdio.h>
#include <generic.h>
#include <time.h>

#include "shuffle.h"
#include "binary_search_tree.h"

using namespace alg;
int main()
{
	const int MAX_ELEMENTS = 10;
	int key[MAX_ELEMENTS];
	int value[MAX_ELEMENTS];

	BST<int, int> t;

	int i = 0;
	srand(time(NULL));
	// generate random numbers and fill them to the list
	for(i = 0; i < MAX_ELEMENTS; i++ ){
		key[i] = rand()%100; 
		value[i] = rand()%1000; 
	}

	for(i = 0; i < MAX_ELEMENTS; i++){
		printf("insert %d->%d\n",key[i], value[i]);
		t.insert(key[i], value[i]);
	}

	for(i = 0; i < MAX_ELEMENTS; i++){
		printf("getting %d->%d\n",key[i], t[key[i]]);
	}

	for(i = 0; i < MAX_ELEMENTS; i++){
		int k = rand()%100;
		printf("testing %d-> %s\n",k,t.contains(k)?"YES":"NO");
	}

	for(i = 0; i < MAX_ELEMENTS; i++){
		t.deleteKey(key[i]);
		printf("delete %d\n", key[i]);
	}

	for(i = 0; i < MAX_ELEMENTS; i++){
		int k = rand()%100;
		printf("testing %d-> %s\n",k,t.contains(k)?"YES":"NO");
	}

	return 0;
}
