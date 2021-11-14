#include <stdio.h>
#include <assert.h>

#include "scr/list.h"

void tests (ListExample *list)
{
  assert (list != nullptr);
  // check variables
  int find_bad_cell = 0;
  int save_data = 0;

  printf("\n_ [checks] _____________________________________________________\n");

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

// [ #### CHANGE LIST'S TAIL AND HEAD ###################### ]
  printf("\nhead before insertion: %d\n", list->head);
  printf("InsertAfter (0, list, 99)  ");
  InsertAfter (0, list, 99);
  printf("head after insertion: %d\n", list->head);

  printf("\ntail before insertion: %d\n", list->tail);
  printf("InsertAfter (list->tail, list, 33)  ");
  InsertAfter (list->tail, list, 33);
  printf("tail now: %d\n", list->tail);

// [ #### INSERTION IN MIDDLE OF LIST ###################### ]
  list_t *array_of_elems = createTestListFrom (list);

  InsertAfter (list->tail, list, 1);
  array_of_elems[list->size] = 1;

  printf("\n_ [insertion test] _________ (insert middle)\n");
  for (int el = 0; el < list->size; el++) {
    if (array_of_elems[el] == list->cells[el].elem) {
      printf("list: %3d array: %3d  [equal]\n", *(array_of_elems + el + 1), list->cells[el + 1].elem);
    }
    else {
      printf("list: %3d array: %3d  [WRONG]\n", *(array_of_elems + el + 1), list->cells[el + 1].elem);  
    }
  }

// [ #### REMOVING ELEM FROM LIST ###################### ]
  array_of_elems = createTestListFrom (list);

  printf ("\nhead befor remove: %d\n", list->head);
  array_of_elems[list->head] = 0;
  listRemove (list, list->head);

  printf("\n_ [removing test] __________ (delete head)\n");
  for (int el = 0; el < list->size; el++) {
    if (array_of_elems[el] == list->cells[el].elem) {
      printf("list: %3d array: %3d  [equal]\n", *(array_of_elems + el + 1), list->cells[el + 1].elem);
    }
    else {
      printf("list: %3d array: %3d  [WRONG]\n", *(array_of_elems + el + 1), list->cells[el + 1].elem);  
    }
  }
  printf ("\nhead after remove: %d\n", list->head);

// [ #### REMOVING TAIL FROM LIST ###################### ]
  array_of_elems = createTestListFrom (list);

  printf("\nlist before removing:\n");
  printList (list);

  printf ("\ntail before remove: %d\n", list->tail);
  array_of_elems[list->tail] = 0;
  listRemove (list, list->tail);

  printf("\n_ [removing test] __________ (delete tail)\n");
  for (int el = 0; el < list->size; el++) {
    if (array_of_elems[el] == list->cells[el].elem) {
      printf("list: %3d array: %3d  [equal]\n", *(array_of_elems + el + 1), list->cells[el + 1].elem);
    }
    else {
      printf("list: %3d array: %3d  [WRONG]\n", *(array_of_elems + el + 1), list->cells[el + 1].elem);  
    }
  }
  printf("\nlist after removing:\n");
  printList (list);
  printf ("\nhead after remove: %d\n", list->tail);

  return;
}

int main (void)
{
  printf ("List program Executin...\n");

  ListExample list = {};
  listCtor (&list, 16);

// [ #### ADD TO END OF LIST ############################## ]
  for (int elem = 0; elem < 5; elem++) {
    InsertAfter (elem, &list, 13 + elem);
  }

  /*
// [ #### ADD TO THE MIDDLE ############################### ]
  for (int elem = 0; elem < 19; elem++) {
    InsertAfter (3, &list, 11);
  }
  */

  printList (&list);
  // createGraph (&list);

  tests (&list);

  listDtor (&list);
  
  return 0;
}
