#include "list.h"


int listInsert( List* lst, int index, int value ){
    #ifndef _NO_LIST_VERIFY
        int res = listVerify( lst );
        if ( res ) return res;
    #endif

    // if prev[index] is -1, then this index isn't used in List, so return error code
    if ( lst->prev[index] <= -1 ) return FICTIVE_INDEX;

    /*
        listInsert( &lst, 1, 2 )

                       we have
          1      3     ----------
           \    /      next(1): 3
            \  /       prev(3): 1
             \/        ----------

        1    2    3    we need
                       ----------
        \   /\   /     next(1): 2
         \ /  \ /      prev(3): 2
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


int listDelete( List* lst, int index ){

    #ifndef _NO_LIST_VERIFY
        int res = listVerify( lst );
        if ( res ) return res;
    #endif

    // if prev[index] is -1, then this index isn't used in List, so return error code
    if ( lst->prev[index] == -1 ) return FICTIVE_INDEX;

    // we CAN NOT delete 0 index
    if ( index == 0 )             return ZERO_DELETE;

    /*
        listDelete( &lst, 2 )


        1    2    3     we have
                        ----------
         \   /\   /     next(1): 2
          \ /  \ /      next(2): 3
           V    V
                        prev(2): 1
                        prev(3): 2
                        ----------


          1    3        we need
          \    /        ----------
           \  /         next(1): 3
            \/          prev(3): 1
                        ----------
    */

    int prev = lst->prev[index], \
        next = lst->next[index];

    // next(1): 3
    lst->next[prev] = next;

    // prev(3): 1
    lst->prev[next] = prev;

    elem toReturn = lst->data[index];

    lst->data[index] = -1;
    lst->prev[index] = -1;

    // updates singly linked list of fictive elements
    lst->next[index] = lst->free;
    lst->free = index;

    // if element's previous index is 0, then this element is head
    if ( lst->prev[prev] == 0 ) lst->head = prev;
    if ( lst->prev[next] == 0 ) lst->head = prev;

    lst->size--;

    return toReturn;
}



int listCTOR( List* lst, int size = LIST_SIZE ){

    lst->free = 1;
    lst->head = 0;
    lst->tail = 0;
    lst->size = 0;
    lst->capt = size;

    lst->next = ( int* )  calloc( sizeof( int ),  lst->capt );
    lst->prev = ( int* )  calloc( sizeof( int ),  lst->capt );

    for ( int i = 0; i < lst->capt; i++ ){
        lst->next[i] = i + 1;
        lst->prev[i] = -1;
    }
    // Element zero - starting element, so it's next and prev is itself
    lst->prev[0] = 0;
    lst->next[0] = 0;
    // next(last_index) = 0
    lst->next[lst->capt - 1] = 0;

    lst->data = ( elem* ) calloc( sizeof( elem ), lst->capt );

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

    for ( int i = 0; i < lst->capt; i++ ){
        if ( lst->prev[i] == -1 )
            continue;
        printf("--NODE #%d--\n", i);;
        printf("value %d\n", lst->data[i]);
        printf("next %d\n" , lst->next[i]);
        printf("prev %d\n" , lst->prev[i]);
        printf("\n");
    }

    printf("index\t");
    for ( int i = 0; i < lst->capt; i++)
        printf("%5d", i);
    printf("\nnext\t");

    for ( int i = 0; i < lst->capt; i++ ){
        printf("%5d", lst->next[i]);
    }

    printf("\nprev\t");
    for ( int i = 0; i < lst->capt; i++ ){
        printf("%5d", lst->prev[i]);
    }
    printf("\n--END OF LIST--\n\n");
}

int listVerify( List* lst ){

    if ( !lst )
        return LIST_NULL;

    if ( lst->prev[0] == -1 )
        return ZERO_IS_FICTIVE;

    #ifdef _AUTO_LIST_REALLOC
        if ( lst->capt == lst.size + 1 )
            listRealloc( lst );
    #endif

    return 0;
}


int listRealloc( List* lst, int size = 0 ){

    List* tmp = {};
    int res = 0

    if ( !size )
        res = listCTOR( tmp, lst->capt * _LIST_MULTIPLIER );
    else
        res = listCTOR( tmp, size );

    if ( res )
        return res

    lst->free = tmp->free;
    lst->head = tmp->head;
    lst->tail = tmp->tail;

    for ( int i = 0; i < tmp->capt; i++ ){
        if ( i == lst->capt )
            break;

        tmp->prev[i] = lst->prev[i];
        tmp->next[i] = lst->next[i];
        tmp->data[i] = lst->data[i];
    }

    tmp->size = lst->capt < tmp->capt ? lst->capt : tmp->capt;

    listDTOR( lst );

    lst = tmp;

    return res;
}
