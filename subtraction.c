
#include <stdio.h>
#include <stdlib.h>
#include "apc.h"

// subtraction 

int subtraction(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR)
{
    int borrow = 0, diff;
    Dlist *ptr1 = *tail1, *ptr2 = *tail2;

    while (ptr1)
    {
        diff = ptr1->data - borrow;     
        if (ptr2)
        {
            diff -= ptr2->data;  
            ptr2 = ptr2->prev;
        }
        
        // Handle borrow
        if (diff < 0)
        {
            diff += 10;
            borrow = 1;
        }
        else
        {
            borrow = 0;
        }

        //result node
        Dlist *new = malloc(sizeof(Dlist));
        new->data = diff;
        new->prev = NULL;
        new->next = *headR;
        if (*headR)
            (*headR)->prev = new;
        else
            *tailR = new;
        *headR = new;

        ptr1 = ptr1->prev;
    }

    // Remove leading zeros
    while (*headR && (*headR)->data == 0 && (*headR)->next)
    {
        Dlist *temp = *headR;
        *headR = (*headR)->next;
        (*headR)->prev = NULL;
        free(temp);
    }

    return SUCCESS;
}