/**
 * The library of the list was written in November 2021 as part of
 * the project of Ilya Rudolfovich Dedinsky.
 */

/**
 * A doubly linked list allows you to quickly add items to an existing
 * database.
 * 
 * The speed of adding to the list is faster due to the fact that time
 * is spent only searching for an empty field in the list, and its 
 * insertion is carried out equally quickly, regardless of the length
 * of the list.
 */

/**
 * Debug library will be added a little later and as an optionally
 * executed task.
 */
#ifndef LIST_H
#define LIST_H

#include <stdlib.h>

#define MAX_NAME_LEN 32
#define MAX_COMMAND_LEN 100
#define DIR_PTR "visualize/"
#define DEBUG

#define INCREASE_COEF 2
#define POISON_LIST   0xF2EE

/**
 * @brief list value type
 */
typedef int list_t;

/**
 * @brief Element of List structure
 * 
 * @param prew_index contains prew element index
 * @param content contains value in this cell of
 * list
 * 
 * @param next_index contains next element index
 */
struct CellExample
{
    int prew_index = -1;

    list_t elem    =  0;

    int next_index = -1;
};

/**
 * @brief Main list structure
 * 
 * @param capacity current capacity of list
 * @param head first element in queque of list
 * @param tail last element in queque of list
 * @param[in,out] cells
 */
struct ListExample
{
	int    capacity     = 0;

    int head            = 0;
    int tail            = 0;
    int free            = 0;
    int size            = 0;

    #ifdef DEBUG
        FILE *dump_file = nullptr;
    #endif//DEBUG

	CellExample *cells  = 0;
};

/**
 * @brief Errors enum class to check list condition
 * 
 * @param strucNullptr ListCtor error [ bad callocation ]
 */
enum class ListErr: char
{
	noErr,

	strucNullptr,
	listEmpty,
	badElType
};

/**
 * @brief Constructor list data
 * 
 * @param[in,out] list
 * 
 * @return ListErr value [ check ListErr enum ]
 */
ListErr listCtor (ListExample* list, int start_capacity);

/**
 * @brief Destructror of list data
 * 
 * @param list current list structure
 * 
 * @return ListErr value [ check ListErr enum ]
 */
ListErr listDtor (ListExample *list);

/**
 * @brief Print all list data in stdout
 * 
 * @param[in,out] list
 * 
 * @return ListErr value [ check ListErr enum ]
 */
ListErr printList (ListExample *list);

/**
 * @brief Change list capacity to new velue
 * 
 * @param list current list structure
 * @param new_cap capacity in bytes
 * 
 * @return ListErr value [ check ListErr enum ]
 */
ListErr listChangeCapacity (ListExample *list, int new_capacity);

/**
 * @brief Insert new element on empty position in list
 * 
 * @param list current list structure
 * @param index index which content will be replaced
 * @param value new value in index-position of cur. list
 * 
 * @return ListErr value [ check ListErr enum ]
 */
ListErr InsertAfter (int index, ListExample *list, list_t value);

/**
 * @brief Remove element on [ index ] - position 
 * 
 * @param list current list structure
 * @param index cell of list which contains list's value
 * 
 * @return ListErr value [ check ListErr enum ]
 */
ListErr listRemove (ListExample *list, int index);

/**
 * @brief Find empty position in list
 * 
 * @param list current list structure
 * 
 * @return ListErr value [ check ListErr enum ]
 */
int listFindEmptyCell (ListExample *list);

/**
 * @brief Change list capacity to new velue
 * 
 * @param list current list structure
 * @param index cell of list which contains list's value
 * 
 * @return ListErr value [ check ListErr enum ]
 */
list_t listGet (ListExample *list, size_t index);

/**
 * @brief ListGet analogue, but we get prew elemetn
 * 
 * @param list current list structure
 * @param index current place in list
 * 
 * @return ListErr value [ check ListErr enum ]
 */
int listPrew (ListExample *list, size_t index);

/**
 * @brief ListGet analogue, but we get Next elemetn
 * 
 * @param list current list structure
 * @param index current place in list
 * 
 * @return ListErr value [ check ListErr enum ]
 */
int listNext (ListExample *list, size_t index);

/**
 * @brief Dump list example
 * 
 * @param list current list structure
 */
void listDump (ListExample* List);

/**
 * @brief Create graph of list connections [ used graphviz library ]
 * 
 * @param list current list structure
 */
void createGraph (ListExample *list);


#endif//LIST_H