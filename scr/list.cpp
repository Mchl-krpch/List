/**
 * Implementation of library functions list.cpp
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "list.h"

ListErr listCtor (ListExample* list, int start_capacity)
{
	assert (list != nullptr);

	list->head     = 0;
	list->tail     = 0;
	list->free	   = 1;

	CellExample *tryCalloc = (CellExample *)calloc (start_capacity, sizeof (CellExample) );
	assert (tryCalloc != nullptr);
	list->cells = tryCalloc;

	list->capacity = start_capacity;

	list->cells[0] = {0, 0, 0};

	for (int elem = 1; elem < list->capacity; elem++) {
		list->cells[elem].prew_index = (elem == 0 || elem == list->capacity) ? 0: -1;

		list->cells[elem].next_index = (elem == list->capacity - 1) ? 0 : elem + 1;
	}

	return ListErr::noErr;
}

//--------------------------------------------------------------------------------

ListErr printList (ListExample *list)
{
	for (int elem = 0; elem < list->capacity; elem++) {
		printf ("{[%2d] %2d, %4d, %2d}\n",
			elem,
			list->cells[elem].prew_index,
			list->cells[elem].elem,
			list->cells[elem].next_index);
	}

	return ListErr::noErr;
}

//--------------------------------------------------------------------------------

int listFindEmptyCell (ListExample *list)
{
	if (list->cells[list->free].next_index == 0) {
		listChangeCapacity (list, list->capacity * INCREASE_COEF);
	}

	int save_free = list->free;
	printf("we save: %d\n",list->free);

	list->free = list->cells[list->free].next_index;

	return save_free;
}

//--------------------------------------------------------------------------------

ListErr InsertAfter (int index, ListExample *list, list_t value)
{
	assert (list != nullptr);

	int inserted_elem = listFindEmptyCell (list);


	list->cells[inserted_elem].elem = value;

	list->cells[inserted_elem].prew_index = index;

// [ #### WORKING WITH ELEMENTS IN TAIL OF LIST ############################## ]
	if (index == list->size) {
		if (list->cells[inserted_elem].prew_index != 0) {
			list->cells[list->cells[inserted_elem].prew_index].next_index = list->save_index;
		}

		list->save_index = list->cells[inserted_elem].next_index;
		list->cells[inserted_elem].next_index = 0;

		list->size++;

		return ListErr::noErr;
	}

// [ #### WORKING WITH ELEMENTS IN MIDL OF LIST ############################# ]
    list->cells[listNext (list, index)].prew_index = inserted_elem;

    list->cells[inserted_elem].next_index = list->cells[index].next_index;
    list->cells[index].next_index = inserted_elem;

	list->size++;

	return ListErr::noErr;
}

//--------------------------------------------------------------------------------

ListErr listChangeCapacity (ListExample *list, int new_capacity)
{
	list->cells = (CellExample *)realloc (list->cells, new_capacity * sizeof (CellExample) );

	list->cells[list->capacity - 1].next_index = list->capacity;
	printf ("[%2d] last index: %d\n", list->capacity - 1, list->cells[list->capacity - 1].next_index);

	for (int elem = list->capacity; elem < new_capacity; elem++) {
		list->cells[elem].prew_index = -1;
		list->cells[elem].elem = 0;
		list->cells[elem].next_index = (elem == new_capacity - 1) ? 0 : elem + 1;
	}

	list->capacity *= INCREASE_COEF;

	return ListErr::noErr;
}

//--------------------------------------------------------------------------------

ListErr listDtor (ListExample *list)
{
	assert (list != nullptr);

	list->head     = 0;
	list->tail     = 0;
	list->free     = 0;
	list->size 	   = 0;
	list->capacity = 0;

	free (list->cells);

	return ListErr::noErr;
}

//--------------------------------------------------------------------------------

list_t listGet (ListExample *list, size_t index)
{
	assert (list != nullptr);

	return list->cells[index].elem;
}

//--------------------------------------------------------------------------------

int listPrew (ListExample *list, size_t index)
{
	assert (list != nullptr);

	return list->cells[index].prew_index;
}

//--------------------------------------------------------------------------------

int listNext (ListExample *list, size_t index)
{
	assert (list != nullptr);

	printf ("\t NEXT: %d\n", list->cells[index].next_index);

	return list->cells[index].next_index;
}
