#include <stdio.h>

#include "scr/list.h"

int main (void)
{
	printf ("List program Executin...\n");

	ListExample list = {};
	listCtor (&list, 16);

	for (int elem = 0; elem < 19; elem++) {
		InsertAfter (elem, &list, 99);
	}

	
	for (int elem = 0; elem < 19; elem++) {
		InsertAfter (3, &list, 11);
	}
	
	printf("size now: %d\n", list.size);

	printList (&list);

	listDtor (&list);
	
	return 0;
}