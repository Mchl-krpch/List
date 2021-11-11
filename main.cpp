#include <stdio.h>

#include "scr/list.h"

int main (void)
{
	printf ("List program Executin...\n");

	ListExample list = {};
	listCtor (&list, 16);

// [ #### ADD TO END OF LIST ############################## ]
	for (int elem = 0; elem < 5; elem++) {
		InsertAfter (elem, &list, 99);
	}

	/*
	*/
// [ #### ADD TO THE MIDDLE ############################### ]
	for (int elem = 0; elem < 19; elem++) {
		InsertAfter (3, &list, 11);
	}
<<<<<<< HEAD
=======

>>>>>>> 5087143a3a18eb1a0e1bb1932d42472025f920b5
	createGraph (&list);

	printList (&list);

	listDtor (&list);
	
	return 0;
}
