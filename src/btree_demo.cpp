#include <stdio.h>
#include "btree.h"

using namespace alg;
int main(void) {
	BTree x("./btree.dat");
	int32_t i;

	for (i=0;i<100000;i++) {
		x.Insert(i);	
		BTree::nr r = x.Search(i);
	}
	
	for (i=0;i<100000;i++) {
		x.DeleteKey(i);
		BTree::nr r = x.Search(i);
		printf("key[%d] offset[%x] idx[%d]\n", i, r.offset, r.idx);
	}
}
