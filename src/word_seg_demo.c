#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "generic.h"
#include "word_seg.h"

int main(void)
{
	struct WordSeg * ws = word_seg_init("./src/dict.txt.sogou");
	
	char buf[1024];
	printf("input a sentence in GB18030 encoding, no more than 256 words:\n");
	
	while(1){
		scanf("%s", buf);
		word_seg_strip(ws, buf);
		char *part, *brkt;
		char *sep=" ";
		
	    for (part = strtok_r(buf, sep, &brkt);
	             part;
	             part = strtok_r(NULL, sep, &brkt))
	    {
			Queue * q = word_seg_run(ws, part);
			short cursor = 0;
			while(!queue_is_empty(q)) {
				int state = queue_front(q);
				uint32_t CH;
				cursor += gb18030_read(part,cursor,&CH);
				gb18030_putchar(CH);
				putchar(state);
				if(state=='0') printf(" ");
				if(state=='3') printf(" ");
				dequeue(q);
			}
			printf("\n");
			queue_destroy(q);		
		}
	}
	
	exit(0);
}
