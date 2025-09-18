
#include <stdio.h>
#include <stdlib.h>
#include "apc.h"

// addition
int addition(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR)
{
    int carry = 0, digit_sum;
    Dlist *ptr1 = *tail1, *ptr2 = *tail2;

    while (ptr1 || ptr2 || carry) 
    {
        digit_sum = carry;
        if (ptr1)
        {
            digit_sum += ptr1->data;
            ptr1 = ptr1->prev;
        }
        if (ptr2)
        {
            digit_sum += ptr2->data;
            ptr2 = ptr2->prev;
        }

        // new node
        Dlist *new = malloc(sizeof(Dlist));
        new->data = digit_sum % 10;
        new->prev = NULL;
        new->next = *headR;
        if (*headR)
            (*headR)->prev = new;
        else
            *tailR = new;
        *headR = new;

        carry = digit_sum / 10; // Update carry
    }

    return SUCCESS;
}