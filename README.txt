-----------------------------------------------
 List description [5th project]
-----------------------------------------------

I have a new goal: I want to try to write the design and contents of the repository so that the person who comes here for the first time understands how it happens.

   Autor: (Michael Krapchatov) 11.2021                                              I would be glad if you write issue




                                    The program should solve the following problems:
-----
[ 1 ] CREATING AN EMPTY LIST TO GET STARTED
-----

we create the first parent cell {0, 0, 0} and a list of cells {-1, 0, index + 1} - the standard kind of free cells in the list, note that they are ALREADY connected to each other. - all this happens in the functions listCtor () and listChangeCapacity (), but we leave the last cell in the format {-1, 0, 0} - to show that the list of empty elements is complete.
{0,  0, 0}
{-1, 0, 2} this is what the list looks like
{-1, 0, 3} after () ()
{-1, 0, 4}
{-1, 0, 0} example (1)

-----
[ 2 ] INSERTING NEW EMPTY ELEMENTS
-----

after that it is worth solving the problem of filling the list with new elements. We have a variable (list->free) - a pointer to the first cell of the format {-1, 0, index + 1} - in example 1 it will be a cell with index 1. Then with each addition we make a new inserted cell final (tail-cell) and save index + 1, which used to be here {-1, 0, index + 1}, so that when adding the second next cell, we can put this saved index instead of 0

 Insert (0, &list, 9)            |    Insert (1, &list, 9)
             -->                 |                 -->
{ 0, 0, 0}          { 0, 0, 0}   |   { 0, 0, 0}          { 0, 0,     0     }
{-1, 0, 2} <free    { 0, 9, 0}   |   { 0, 9, 0}          { 0, 9, save_index} = 2
{-1, 0, 3}          {-1, 0, 3}   |   {-1, 0, 3} <free    { 1, 9,     0     } (we saved 3)
{-1, 0, 4}          {-1, 0, 4}   |   {-1, 0, 4}          {-1, 0,     4     }
{-1, 0, 0}          {-1, 0, 0}   |   {-1, 0, 0}          {-1, 0,     0     }
                                 |
 save 2 to list->save_index      |     insert save_index to {0, 9, 0}
                                         & save 3 to list->save_index 

-----
[ 3 ] INSERT AFTER X-ELEMENT 
-----

insertion is performed by changing the indices of the element, after which the insertion occurs and following the inserting elements of the indices

 Insert (1, &list, 7)            
             -->                -->             
{ 0, 0, 0}          { 0, 0, 0}       { 0, 0, 0} 
{ 0, 9, 2}          { 0, 9, 4} <     { 0, 9, 4}
{ 1, 9, 3}        > { 4, 9, 3}       { 4, 9, 3}
{ 2, 9, 0}          { 2, 9, 0}       { 2, 9, 0}
{-1, 0, 0} <free    {-1, 0, 0}     > { 1, 7, 2} 
                                         ...  -  we should change capacity
we change indices 1-st and 2nd element          
(before & after inserted element elements) 
to pointers to free element
