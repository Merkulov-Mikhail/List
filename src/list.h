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


void listCTOR( List* lst );
