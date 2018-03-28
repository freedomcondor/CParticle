#include "List.h"
#include <stdio.h>
#include <stdlib.h>

List::List()
{
	//printf("list construct %d\n",this);
	head = (struct node*)malloc(sizeof(struct node));
	head->next = NULL;
}
List::~List()
{
	//printf("list desstruct %d\n",this);
	freelist();
}

int List::freelist()
{
	//printf("free list\n");
	struct node *p;
	while (head != NULL)
	{
		p = head->next;
		delete(head);
		head = p;
	}
	return 0;
}

int List::add(nodetype x, int i)
{
	struct node *p,*q;
	int j;

	p = (struct node*)malloc(sizeof(struct node));
	p ->obj = x;
	p->next = NULL;

	q = head;
	for (j = 0; j < i; j++)
	{
		if (q->next == NULL) break;
		q = q->next;
	}
	p->next = q->next;
	q->next = p;

	return 0;
}

int List::del(int i)
{
	struct node *p,*q;
	int j;

	q = head;
	for (j = 0; j < i; j++)
	{
		if (q->next == NULL) return -1;
		q = q->next;
	}
	p = q->next;
	q->next = q->next->next;
	free(p);
	return 0;
}

int List::printnode(struct node *p)
{
	//printf("list node : %d\n",p->obj);
	printf("list node : %s\n",(p->obj).l.toStr());	// in the case of Signal
	return 0;
}

nodetype* List::getnode(int i)
{
	struct node *q;
	int j;
	q = head;
	for (j = 0; j < i+1; j++)
	{
		if (q->next == NULL) return NULL;
		q = q->next;
	}
	return &(q->obj);
}

int List::printthrough()
{
	struct node *q;
	int j;
	q = head;
	while (q->next != NULL)
	{
		q = q->next;
		printnode(q);
	}
	return 0;
}
