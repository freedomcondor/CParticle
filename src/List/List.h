#ifndef LIST
#define LIST

/*
#ifndef LISTNODETYPE
typedef int nodetype;
#else
typedef LISTNODETYPE nodetype;
#endif
*/

#include <stdlib.h>
#include "../Signal.h"
typedef Signal nodetype;

struct node
{
	nodetype obj;
	struct node *next;
};

class List
{
public:
	struct node *head;
	List();
	~List();
	int freelist();
	int add(nodetype x,int i);	
		// from 0 to n, add before the ith, head node is -1th
	int del(int i);	
		// from 0 to n, del the ith, head node is -1th
	int printnode(struct node *p);
	nodetype* getnode(int i);
		// from 0 to n-1, add behind the ith, head node is -1th
	int printthrough();
};

/*
 head -> empty
 		 next   ->  number 0	-> number 1
 */

#endif
