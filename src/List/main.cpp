#include <stdio.h>

#define LISTNODETYPE
typedef int nodetype;
#include "List.h"

int main()
{
	List a;

	a.add(8,0);
	a.add(9,0);
	a.add(10,1);
	printf("%d\n",*(a.getnode(0)));
	a.printthrough();
	a.del(0);
	a.printthrough();
}
