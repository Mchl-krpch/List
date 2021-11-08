#include <stdio.h>

#include "scr/list.h"

int main (void)
{
	printf("List program Executin...\n");

	ListExample list = {};

	listCtor(&list, 16);

	list.cells[0].content = 9;

	printf("%d", list.cells[0].content);

	listDtor(&list);
	
	return 0;
}