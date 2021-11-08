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

    list_t content =  0;

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
	size_t capacity    = 0;

    int head           = 0;
    int tail           = 0;
    int free           = 0;

	CellExample *cells =  0;

	int next_index = -1;
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
ListErr listCtor (ListExample* list, list_t start_capacity);

/**
 * @brief Destructror of list data
 * 
 * @param list current list structure
 * 
 * @return ListErr value [ check ListErr enum ]
 */
ListErr listDtor (ListExample *list);

/**
 * @brief Change list capacity to new velue
 * 
 * @param list current list structure
 * @param new_cap capacity in bytes
 * 
 * @return ListErr value [ check ListErr enum ]
 */
ListErr listChangeCapacity (ListExample *list, size_t new_cap);

/**
 * @brief Insert new element on empty position in list
 * 
 * @param list current list structure
 * @param index index which content will be replaced
 * @param value new value in index-position of cur. list
 * 
 * @return ListErr value [ check ListErr enum ]
 */
ListErr listInsert (ListExample *list, int index, list_t value);

/**
 * @brief Remove element on [ index ] - position 
 * 
 * @param list current list structure
 * @param index cell of list which contains list's value
 * 
 * @return ListErr value [ check ListErr enum ]
 */
ListErr listRemove (ListExample *list, int index, list_t value);

/**
 * @brief Find empty position in list
 * 
 * @param list current list structure
 * 
 * @return ListErr value [ check ListErr enum ]
 */
ListErr listFindEmptyCell (ListExample *list);

/**
 * @brief Change list capacity to new velue
 * 
 * @param list current list structure
 * @param index cell of list which contains list's value
 * 
 * @return ListErr value [ check ListErr enum ]
 */
list_t listGet (ListExample *list, int index);

/**
 * @brief ListGet analogue, but we get prew elemetn
 * 
 * @param list current list structure
 * @param index current place in list
 * 
 * @return ListErr value [ check ListErr enum ]
 */
list_t listPrew (ListExample *list, int index);

/**
 * @brief ListGet analogue, but we get Next elemetn
 * 
 * @param list current list structure
 * @param index current place in list
 * 
 * @return ListErr value [ check ListErr enum ]
 */
list_t listNext (ListExample *list, int index);


#endif//LIST_H