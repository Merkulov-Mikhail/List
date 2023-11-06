#include <stdio.h>
#include <stdlib.h>


typedef int elem;


const int LIST_SIZE = 11;


struct List{
    int head;
    int tail;
    int free;
    int size;
    int capt; // capacity

    elem* data;

    int* next;
    int* prev;
};


/*
    \brief creates struct List

    \param lst - pointer to List struct
    \return 1 if failed to allocate memory, 0 otherwise
*/
int listCTOR( List* lst );

/*
    \brief destroys struct List

    \param lst - pointer to List struct
*/
void listDTOR( List* lst );

/*
    \brief adds new element to List
    Inserts new element right after [index] element. If there is no data in [index], then returns error code.
    Updates tail if new element added right after previous tail.

    \return -1 if [index] is not used in lst. Otherwise - returns index of inserted element
*/
int listInsert( List* lst, int index, int value );

int listDelete( List* lst, int index );

void listDump( List* lst );
