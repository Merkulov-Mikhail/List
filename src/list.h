#include <stdlib.h>


typedef int elem;


const int LIST_SIZE = 101;


struct List{
    int head;
    int tail;
    int free;
    int size;

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
