#include "list.h"


int listInsert( List* lst, int index, int value ){

    // if prev[index] is -1, then this index isn't used in List, so return error code
    if ( lst->prev[index] <= -1 ) return -1;

    /*
        1   2   3       we have
                        ----------
        \       /       next(1): 3
         \-----/        prev(3): 1
          \---/         ----------

        1    2    3     we need
                        ----------
        \   /\   /      next(1): 2
         \ /  \ /       prev(3): 2
          V    V
                        next(2): 3
                        prev(2): 1
                        ----------
    */

    // position of new Node
    int pos = lst->free;
    // sets free to the next index of free block
    lst->free = lst->next[lst->free];

    lst->data[pos] = value;

    // next(2): 3; prev(2): 1
    lst->next[pos] = lst->next[index];
    lst->prev[pos] = index;

    // next(1): 2
    lst->next[index] = pos;

    // prev(3): 2
    lst->prev[lst->next[pos]] = pos;

    if ( lst->next[pos] == 0 ) // A node whose next element is 0 is tail
        lst->tail = pos;

    lst->size++;

    return pos;
}



int listCTOR( List* lst ){
    lst->free = 1;
    lst->head = 0;
    lst->tail = 0;
    lst->size = 0;
    lst->capt = LIST_SIZE;

    lst->next = ( int* )  calloc( sizeof( int ),  LIST_SIZE );
    lst->prev = ( int* )  calloc( sizeof( int ),  LIST_SIZE );

    for ( int i = 0; i < LIST_SIZE; i++ ){
        lst->next[i] = i + 1;
        lst->prev[i] = -1;
    }
    // Element zero - starting element, so it's next and prev is itself
    lst->prev[0] = 0;
    lst->next[0] = 0;
    // next(last_index) = 0
    lst->next[LIST_SIZE - 1] = 0;

    lst->data = ( elem* ) calloc( sizeof( elem ), LIST_SIZE );

    // if one of the callocs didn't work, we return an error code
    if ( !lst->next ||
         !lst->prev ||
         !lst->data )
        return 1;

    return 0;

}

void listDTOR( List* lst ){

    for ( int i = 0; i < lst->size; i++ ){
        lst->data[i] = 0;
        lst->next[i] = 0;
        lst->prev[i] = 0;
    }

    lst->free = -1;
    lst->head = -1;
    lst->size = -1;
    lst->capt = -1;

    free( lst->next );
    free( lst->prev );
    free( lst->data );

    lst->next = nullptr;
    lst->prev = nullptr;
    lst->data = nullptr;
}


void listDump( List* lst ){
    printf("--LIST--\n");
    printf("head %d\ntail %d\nfree %d\n\n", lst->head, lst->tail, lst->free);
    for ( int i = 0; i < lst->size + 1; i++ ){
        printf("--NODE #%d--\n", i);;
        printf("value %d\n", lst->data[i]);
        printf("next %d\n" , lst->next[i]);
        printf("prev %d\n" , lst->prev[i]);
        printf("\n");
    }

    printf("\nnext");

    for ( int i = 0; i < lst->capt; i++ ){
        printf("%5d", lst->next[i]);
    }

    printf("\nprev");

    for ( int i = 0; i < lst->capt; i++ ){
        printf("%5d", lst->prev[i]);
    }
}
