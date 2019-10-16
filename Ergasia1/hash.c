#include <stdlib.h>
#include "headers.h"

void hash(struct list_node *cur, struct list_node *Hash, unsigned int g, int i){
	cur=Hash;
	if(cur==NULL){
		Hash=malloc(sizeof(struct list_node));
		Hash->next=NULL;
		Hash->g=g;
		Hash->vec_pos=i;
	}else{
		while(cur->next!=NULL){
			cur= cur->next;
		}
		cur->next= malloc(sizeof(struct list_node));
		cur->next->g=g;
		cur->next->next=NULL;
		cur->next->vec_pos=i;
	}
}
