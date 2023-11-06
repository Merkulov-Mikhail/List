#include "list.h"


int listCTOR( List* lst ){
    lst->free = 1;
    lst->head = 0;
    lst->tail = 0;
    lst->size = 0;

    lst->next = ( int* )  calloc( sizeof( int ),  LIST_SIZE );
    lst->prev = ( int* )  calloc( sizeof( int ),  LIST_SIZE );

    lst->data = ( elem* ) calloc( sizeof( elem ), LIST_SIZE );

}

void listDTOR( List* lst ){

    for ( int i = 0; i < lst->size; i++ ){
        lst->data[i] = 0;
        lst->next[i] = 0;
        lst->prev[i] = 0;
    }

    lst->free = -1;
    lst->head = -1;
    lst->next = -1;
    lst->size = -1;

    free( lst->next );
    free( lst->prev );
    free( lst->data );

    lst->next = nullptr;
    lst->prev = nullptr;
    lst->data = nullptr;
}
