#include "solve-2-2.h"

int main(void){
    struct SqList list;
    struct SqList *lp;
    lp = &list;

    InitSeq(lp);
    Print(lp);
    DeleteX_st3(lp, 0, 8);
    Print(lp);

    return 0;
}