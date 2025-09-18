
#include <stdio.h>
#include <stdlib.h>
#include "apc.h"

//division 

int division(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR)
{
    if (compare(*head2, *head1) == 1)
    {
        // Dividend < Divisor → Result = 0
        Dlist *new = malloc(sizeof(Dlist));
        new->data = 0;
        new->prev = NULL;
        new->next = NULL;
        *headR = *tailR = new;
        return SUCCESS;
    }

    // Copy dividend to remainder
    Dlist *remHead = NULL, *remTail = NULL;
    copy_list(*head1, *tail1, &remHead, &remTail);

    Dlist *countHead = NULL, *countTail = NULL;

    // Perform repeated subtraction
    while (compare(remHead, *head2) >= 0)
    {
        Dlist *tempHead = NULL, *tempTail = NULL;
        subtraction(&remHead, &remTail, head2, tail2, &tempHead, &tempTail);
        delete_list(&remHead, &remTail);
        copy_list(tempHead, tempTail, &remHead, &remTail);
        delete_list(&tempHead, &tempTail);

        // Increment quotient by 1
        Dlist *oneNode = NULL, *oneTail = NULL;
        string_to_list("1", &oneNode, &oneTail);

        Dlist *newCountHead = NULL, *newCountTail = NULL;
        addition(&countHead, &countTail, &oneNode, &oneTail, &newCountHead, &newCountTail);
        delete_list(&countHead, &countTail);
        copy_list(newCountHead, newCountTail, &countHead, &countTail);
        delete_list(&newCountHead, &newCountTail);
        delete_list(&oneNode, &oneTail);
    }

    // Copy final quotient to result
    copy_list(countHead, countTail, headR, tailR);
    delete_list(&countHead, &countTail);
    delete_list(&remHead, &remTail);

    return SUCCESS;
}