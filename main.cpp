#include <stdio.h>
#include <assert.h>

#include "scr/list.h"

void tests (ListExample *list)
{
	assert (list != nullptr);
	// check variables
	int find_bad_cell = 0;
	int save_data = 0;

	printf("\n[ ######## CHECKS ############################################# ]\n");

// [ #### BAD NEXT & PREW INDEX ############################## ]
	save_data = list->cells[10].next_index;
	list->cells[10].next_index = -10;
	ListErr data = listVerify (list, &find_bad_cell);

	printf ("err: %-32s (in node: %d)\t line: %d\n",
		translateErrorCode(data), find_bad_cell, __LINE__);

	list->cells[10].next_index = save_data;

	save_data = list->cells[2].prew_index;
	list->cells[2].prew_index = -10;
	data = listVerify (list, &find_bad_cell);

	printf("err: %-32s (in node: %d)\t line: %d\n",
		translateErrorCode(data), find_bad_cell, __LINE__);
	list->cells[2].prew_index = save_data;

// [ #### BAD TAIL & HEAD #################################### ]
	save_data = list->tail;

	list->tail = 9;
	data = listVerify (list, &find_bad_cell);

	printf("err: %-32s (in node: %d)\t line: %d\n",
		translateErrorCode(data), find_bad_cell, __LINE__);
	list->tail = save_data;

	save_data = list->head;
	list->head = -11;
	data = listVerify (list, &find_bad_cell);

	printf("err: %-32s (in node: %d)\t line: %d\n",
		translateErrorCode(data), find_bad_cell, __LINE__);
	list->head = save_data;
// [ #### BAD INSERTION INDEX ############################## ]
	data = InsertAfter (-1, list, 666);
	printf ("err: %-32s (in node: %d)\t line: %d\n",
		translateErrorCode(data), find_bad_cell, __LINE__);

	return;
}

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

	// createGraph (&list);

	// printList (&list);
	createGraph (&list);

	tests (&list);

	listDtor (&list);
	
	return 0;
}
