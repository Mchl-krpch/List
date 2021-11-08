#include <stdio.h>
#include <stdlib.h>

#include "list.h"

ListErr listCtor (ListExample* list, list_t start_capacity)
{
	printf ("start cap: %u\n", start_capacity);

	CellExample *tryCalloc = (CellExample *)calloc (start_capacity, sizeof(CellExample) );
	if (tryCalloc == nullptr) {
		return ListErr::strucNullptr;
	}
	list->cells = tryCalloc;

	return ListErr::noErr;
}

//--------------------------------------------------------------------------------

ListErr listDtor (ListExample *list)
{
	free (list->cells);
	return ListErr::noErr;
}