/**
 * Implementation of library functions list.cpp
 */

/**
 * it is an implementation of a list, functions from the
 * library can create a linked list in which all empty and
 * non-empty cells will be linked.
 * 
 * in the list it is possible: insert an element at the end
 * of the list, in the middle of the list, delete elements
 * print the list get the value of the list.
 * 
 * also the list can quickly
 * change the typeof stored items
 * 
 * also added the ability to build a visual representation of
 * the graph using graphvis
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "list.h"

#ifdef DEBUG
  #define OUT list->dump_file
#else
  #define OUT stdout
#endif

ListErr listCtor (ListExample* list, int start_capacity)
{
  assert (list != nullptr);

  if (start_capacity < 0) {
    return ListErr::memory_error;
  }

  list->head     = 0;
  list->tail     = 0;
  list->free     = 1;

  CellExample *tryCalloc = (CellExample *)calloc (start_capacity, sizeof (CellExample) );
  assert (tryCalloc != nullptr);
  list->cells = tryCalloc;

  list->capacity = start_capacity;

  list->cells[0] = {0, 0, 0};

  for (int elem = 1; elem < list->capacity; elem++) {
    list->cells[elem].prew_index = (elem == 0 || elem == list->capacity) ? 0: -1;

    list->cells[elem].next_index = (elem == list->capacity - 1) ? 0 : elem + 1;
  }

  #ifdef DEBUG
    list->dump_file = fopen("dump.txt", "w");
  #endif//DEBUG

  return ListErr::noErr;
}

//--------------------------------------------------------------------------------

ListErr printList (ListExample *list)
{
  assert (list != nullptr);

  for (int elem = 0; elem < list->capacity; elem++) {
    printf ("%2d {%2d, %4d, %2d}\n",
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
  assert (list != nullptr);

  if (list->cells[list->free].next_index == 0) {
    listChangeCapacity (list, list->capacity * INCREASE_COEF);
  }

  int save_free = list->free;

  list->free = list->cells[list->free].next_index;

  return save_free;
}

//--------------------------------------------------------------------------------

ListErr InsertAfter (int index, ListExample *list, list_t value)
{
  assert (list  != nullptr);

  if (index < 0) {
    return ListErr::bad_index;
  }

  int inserted_elem = listFindEmptyCell (list);

  list->cells[inserted_elem].elem = value;

  list->cells[inserted_elem].prew_index = index;
  list->cells[listNext (list, index)].prew_index = inserted_elem;

  list->cells[inserted_elem].next_index = list->cells[index].next_index;
  list->cells[index].next_index = inserted_elem;

  list->size++;

  if (list->cells[inserted_elem].next_index == 0 && list->cells[inserted_elem].prew_index != -1) {
    list->tail = inserted_elem;
  }

  if (list->cells[inserted_elem].prew_index == 0) {
    list->head = inserted_elem;
  }

  return ListErr::noErr;
}

//--------------------------------------------------------------------------------

ListErr listRemove (ListExample *list, int index)
{
  assert (list != nullptr);

  if (index < 0 || list->cells[index].prew_index == -1) {
    return ListErr::bad_index;
  }

  if (list->cells[index].prew_index == 0) {
    list->head = list->cells[index].next_index;
  }

  if (list->cells[index].next_index == 0 && list->cells[index].prew_index != -1) {
    list->tail = list->cells[index].prew_index;
  }

  list->cells[index].elem = 0;

  list->cells[list->cells[index].next_index].prew_index = list->cells[index].prew_index;
  list->cells[list->cells[index].prew_index].next_index = list->cells[index].next_index;

  list->cells[index].next_index = list->free;
  list->cells[index].prew_index = -1;

  list->free = index;

  list->size--;

  return ListErr::noErr;
}

//--------------------------------------------------------------------------------

ListErr listChangeCapacity (ListExample *list, int new_capacity)
{
  assert (list != nullptr);

  if (new_capacity < 1) {
    return ListErr::memory_error;
  }

  list->cells = (CellExample *)realloc (list->cells, new_capacity * sizeof (CellExample) );

  list->cells[list->capacity - 1].next_index = list->capacity;

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
  list->size     = 0;
  list->capacity = 0;

  free (list->cells);

  #ifdef DEBUG
    fclose(list->dump_file);
  #endif//DEBUG

  return ListErr::noErr;
}

//--------------------------------------------------------------------------------

list_t listGet (ListExample *list, int index)
{
  assert (list != nullptr);
  assert (index > 0);

  return list->cells[index].elem;
}

//--------------------------------------------------------------------------------

int listPrew (ListExample *list, int index)
{
  assert (list != nullptr);
  assert (index > 0);

  return list->cells[index].prew_index;
}

//--------------------------------------------------------------------------------

int listNext (ListExample *list, int index)
{
  assert (list != nullptr);
  assert (index >= 0);

  return list->cells[index].next_index;
}

//--------------------------------------------------------------------------------

void listDump (ListExample* list)
{
  fprintf (OUT, "[ ######################### DUMP ################################ ]\n");
  fprintf (OUT, "  ---------------------------------------------------------------\n");

    for (int checked_elem = 0; checked_elem < list->capacity; checked_elem++) {
      fprintf (OUT, "el: [%3d] is %4d\t", checked_elem, list->cells[checked_elem].elem);
      fprintf (OUT, "Next [%3d] is %4d \t", checked_elem , list->cells[checked_elem].next_index);
      fprintf (OUT, "Prev [%3d] is %4d\n", checked_elem ,list->cells[checked_elem].prew_index);
  }

  fprintf (OUT, "  ---------------------------------------------------------------\n");
    fprintf (OUT, "\n");

    fprintf (OUT, "The maximum size of list - %d\n", list->capacity);
    fprintf (OUT, "Free`s index - %d\n", list->free);
    fprintf (OUT, "Size - %d\n",list->size);
    fprintf (OUT, "Head - %d\n", list->head);
    fprintf (OUT, "Tail - %d\n", list->tail);

    fprintf (OUT, "============================\n\n");
    fprintf (OUT, "I hope it helps you, good luck debug\n");
}

//--------------------------------------------------------------------------------

void createGraph (ListExample *list)
{
  assert (list != nullptr);

  char graph_name[MAX_NAME_LEN] = {};
  sprintf(graph_name, "%sdump_file.dot", DIR_PTR);

  FILE *graph_file = fopen (graph_name, "w");
  assert (graph_file != nullptr);

  fprintf (graph_file, "digraph G {\n");

// [ #### RENDERING GRAPH-FILE ############################# ]
  for (int graph_index = 0; graph_index < list->capacity; ++graph_index) {
        fprintf (graph_file, "\tL%d[shape=\"record\", label=\" <lp%d> %d | {%d | %d} | <ln%d> %d\"];\n",
          graph_index, graph_index, list->cells[graph_index].prew_index, graph_index,
          list->cells[graph_index].elem, graph_index, list->cells[graph_index].next_index);
    }

    for (int graph_index = 0; graph_index < list->capacity - 1; ++graph_index){
        fprintf (graph_file, "\tL%d->L%d[color=\"white\"];\n", graph_index, graph_index + 1);
    }

  for (int graph_index = 0; graph_index < list->capacity; ++graph_index){
        fprintf (graph_file, "\tL%d:<ln%d> -> L%d[color=\"%s\"];\n",
          graph_index, graph_index ,list->cells[graph_index].next_index,
          ( (list->cells[graph_index].prew_index == -1) ? "black" : "green" ) );
        if(list->cells[graph_index].prew_index != -1){
            fprintf (graph_file, "\tL%d -> L%d[color=\"%s\"];\n",
              graph_index, list->cells[graph_index].prew_index, "red");
        }
    }

    fprintf (graph_file, "\tFree[shape=\"rectangle\",style=\"filled\",fillcolor=\"lightgrey\"]");
    fprintf (graph_file, "\tFree->L%d[color=\"%s\"]", list->free, "black");
    
  fprintf (graph_file, "\n}\n");

  fclose (graph_file);

// [ #### RENDER COMMAND ############################# ]
  char command[MAX_COMMAND_LEN] = {};
  sprintf (command, "dot %sdump_file.dot -T png -o %sdump_file.png", DIR_PTR, DIR_PTR);
  system (command);

  return;
}

//--------------------------------------------------------------------------------

ListErr verifyListStruct (ListExample *list)
{
  assert(list != nullptr);
  
  if (list->head == list->tail && list->size > 1) {
    return ListErr::incorrect_size;
  }

  if (list->size > 1) {
    if (list->tail == 0){
        return ListErr::bad_tail_have_nodes;
    }
    if (list->head < 0) {
        return ListErr::bad_hade_have_nodes;
    }
  }

  if (list->size > list->capacity) {
      return ListErr::memory_error;
  }

  return ListErr::noErr;
}

//--------------------------------------------------------------------------------

ListErr listVerify (ListExample *list, int *find_bad_cell)
{
  assert (list != nullptr);
  assert (find_bad_cell != nullptr);

  if (list->tail < 0) {
    return ListErr::bad_hade_have_nodes;
  }
  for (int cur_node = 0; cur_node < list->capacity; cur_node++) {
    CellExample cur_cell = list->cells[cur_node];
    
    if (cur_cell.next_index < 0 && cur_cell.prew_index != -1) {
      *find_bad_cell = cur_node;
      return ListErr::bad_index_next;
    }

    if (cur_cell.prew_index == 0 && cur_node > 0 && list->head != 0) {
      if (cur_node != list->head) {
        return ListErr::bad_hade_have_nodes;
      }
    }

    if (cur_cell.next_index == cur_cell.prew_index) {
      if (list->capacity > 2) {
        *find_bad_cell = cur_node;
        return ListErr::endless_loop;
      }
    }

    if (cur_node != list->cells[cur_cell.prew_index].next_index && cur_node > 1 && cur_cell.prew_index != -1) {
      *find_bad_cell = cur_node;
      return ListErr::bad_index_next;
    }

    if ((cur_cell.next_index == 0) && (cur_cell.prew_index != -1)) {
      if (cur_node != list->tail) {
        *find_bad_cell = cur_node;
        return ListErr::bad_tail_have_nodes;
      }
    }

    else if ((cur_node != list->cells[cur_cell.next_index].prew_index) && (cur_cell.prew_index != -1)) {
      *find_bad_cell = cur_node;
      return ListErr::bad_index_prew;
    }
    
  }

  return ListErr::noErr;
}

const char* translateErrorCode (ListErr error)
{
  switch (error) {
    case ListErr::noErr:                 return "No errors in list";

    case ListErr::bad_index:      return "Incorrect insertion data";
    case ListErr::strucNullptr:          return "Bad ptr to structure";
    case ListErr::listEmpty:             return "Empy list error";
    case ListErr::badElType:             return "Element in list have bad type";

    case ListErr::head_equal_tail:       return "Head and tail in list is equal";
    case ListErr::break_point:           return "List have breakpoint";
    case ListErr::endless_loop:          return "Endless loop in list";

    case ListErr::have_nodes:            return "sag";
    case ListErr::memory_error:          return "Size in list more than capacity";
    case ListErr::incorrect_size:        return "Tail == head, list have elements";

    case ListErr::bad_tail_have_nodes:   return "List have incorrect tail";
    case ListErr::bad_hade_have_nodes:   return "List have incorrect head";

    case ListErr::bad_index_prew:        return "Incorrect prew index in list";
    case ListErr::bad_index_next:        return "incorrect next index in list";

    default:                             return "undef. error";
  }
}

list_t *createTestListFrom (ListExample *list)
{
  list_t *array = nullptr;

  array = (list_t *)calloc (list->size + 2, sizeof(list_t) );

  for (int elem = 0; elem < list->size + 1; elem++) {
    array[elem] = list->cells[elem].elem;
  }


  return array;
}
