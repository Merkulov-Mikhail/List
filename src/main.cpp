#include "list.h"


int main(){
    List lst;
    listCTOR( &lst );
    listInsert( &lst, 0, 1 );
    listInsert( &lst, 0, 2 );
    listInsert( &lst, 2, 3 );
    listDump( &lst );
    listDelete( &lst, 1 );
    listDump( &lst );
}
