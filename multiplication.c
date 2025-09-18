

#include <stdio.h>
#include <stdlib.h>
#include "apc.h"

//multiplication 

int multiplication(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR)
{
    Dlist *ptr2 = *tail2;
    int shift = 0;

    while (ptr2)  
    {
        int carry = 0;
        Dlist *ptr1 = *tail1;       
        Dlist *headT = NULL, *tailT = NULL;

        while (ptr1)
        {
            int prod = ptr1->data * ptr2->data + carry;
            carry = prod / 10;

            //product digit at head
            Dlist *new = malloc(sizeof(Dlist));
            new->data = prod % 10;
            new->prev = NULL;
            new->next = headT;
            if (headT)
                headT->prev = new;
            else
                tailT = new;
            headT = new;

            ptr1 = ptr1->prev;
        }

        // Insert carry if any
        if (carry)
        {
            Dlist *new = malloc(sizeof(Dlist));
            new->data = carry;
            new->prev = NULL;
            new->next = headT;
            if (headT)
                headT->prev = new;
            else
                tailT = new;
            headT = new;
        }


        for (int i = 0; i < shift; i++)
        {
            Dlist *new = malloc(sizeof(Dlist));
            new->data = 0;
            new->prev = NULL;
            new->next = NULL;
            if (!headT)
            {
                headT = tailT = new;
            }
            else
            {
                tailT->next = new;
                new->prev = tailT;
                tailT = new;
            }
        }

        
        Dlist *tempHead = NULL, *tempTail = NULL;
        addition(headR, tailR, &headT, &tailT, &tempHead, &tempTail);

        delete_list(headR, tailR);
        copy_list(tempHead, tempTail, headR, tailR);
        delete_list(&tempHead, &tempTail);
        delete_list(&headT, &tailT);

        ptr2 = ptr2->prev;
        shift++;
    }

    return SUCCESS;
}
