
#include<stdio.h>
#include<stdlib.h>
#include "apc.h"


int main(int argc, char *argv[])
{
    if (argc != 4) // Validate
    {
        printf("Usage: ./apc <num1> <operator> <num2>\n");
        return FAILURE;
    }

    Dlist *head1 = NULL, *tail1 = NULL;
    Dlist *head2 = NULL, *tail2 = NULL;
    Dlist *headR = NULL, *tailR = NULL;

    int sign1 = 1, sign2 = 1;

    if (argv[1][0] == '-')
    {
        sign1 = -1;
        argv[1]++;
    }
    if (argv[3][0] == '-') 
    {
        sign2 = -1;
        argv[3]++;
    }

    string_to_list(argv[1], &head1, &tail1); // string to doubly linked lists
    string_to_list(argv[3], &head2, &tail2); //  string to doubly linked lists

    char operator = argv[2][0];

    int result_sign = 1;
    int cmp = compare(head1, head2); 

   switch (operator)
   {
    case '+': 
        if (sign1 == sign2)
        {
            addition(&head1, &tail1, &head2, &tail2, &headR, &tailR);
            result_sign = sign1;
        }
        else
        {
            if (cmp >= 0)
            {
                subtraction(&head1, &tail1, &head2, &tail2, &headR, &tailR);
                result_sign = sign1;
            }
            else
            {
                subtraction(&head2, &tail2, &head1, &tail1, &headR, &tailR);
                result_sign = sign2;
            }
        }
        break;

    case '-': 
        sign2 *= -1;
        if (sign1 == sign2)
        {
            addition(&head1, &tail1, &head2, &tail2, &headR, &tailR);
            result_sign = sign1;
        }
        else
        {
            if (cmp >= 0)
            {
                subtraction(&head1, &tail1, &head2, &tail2, &headR, &tailR);
                result_sign = sign1;
            }
            else
            {
                subtraction(&head2, &tail2, &head1, &tail1, &headR, &tailR);
                result_sign = sign2;
            }
        }
        break;

    case 'x': 
    case 'X':
        multiplication(&head1, &tail1, &head2, &tail2, &headR, &tailR);
        result_sign = sign1 * sign2;
        break;

    case '/':  
        if (compare(head2, NULL) == 0 || (head2->data == 0 && head2->next == NULL)) {
            printf("Error: Division by zero\n");
            return FAILURE;
        }
        division(&head1, &tail1, &head2, &tail2, &headR, &tailR);
        result_sign = sign1 * sign2;
        break;

    default:
        printf("Invalid operator. Use +, -, x, or /\n");
        return FAILURE;

        
}

if (headR == NULL || (headR->data == 0 && headR->next == NULL))
    result_sign = 1;

if (result_sign == -1)
    printf("Result: -"); 
else
    printf("Result: "); 

print_list(headR);
printf("\n");


}

int string_to_list(char *str, Dlist **head, Dlist **tail)
{
    for (int i = 0; str[i]; i++)
    {
        Dlist *new = malloc(sizeof(Dlist));
        new->data = str[i] - '0';
        new->next = NULL;
        new->prev = *tail;

        if (*tail)
            (*tail)->next = new;
        else
            *head = new;

        *tail = new;
    }
    return SUCCESS;
}

int print_list(Dlist *head)
{
    if (!head)
    {
        printf("0");
        return SUCCESS;
    }

    Dlist *temp = head;
    while (temp)
    {
        printf("%d", temp->data);
        temp = temp->next;
    }
    return SUCCESS;
}


int compare(Dlist *head1, Dlist *head2)
{
    int len1 = 0, len2 = 0;
    Dlist *temp;

    temp = head1;
    while (temp) { len1++; temp = temp->next; }
    temp = head2;
    while (temp) { len2++; temp = temp->next; }

    if (len1 != len2)
        return len1 - len2;

    while (head1 && head2)
    {
        if (head1->data != head2->data)
            return head1->data - head2->data;
        head1 = head1->next;
        head2 = head2->next;
    }

    return 0;
}

void free_list(Dlist **head)
{
    Dlist *temp;
    while (*head)
    {
        temp = *head;
        *head = (*head)->next;
        free(temp);
    }
}

int insert_at_end(Dlist **head, Dlist **tail, int data)
{
    Dlist *new = malloc(sizeof(Dlist));
    if (!new) return FAILURE;

    new->data = data;
    new->prev = *tail;
    new->next = NULL;

    if (*tail)
        (*tail)->next = new;
    else
        *head = new;

    *tail = new;
    return SUCCESS;
}
int copy_list(Dlist *src_head, Dlist *src_tail, Dlist **dst_head, Dlist **dst_tail)
{
    Dlist *temp = src_head;
    while (temp)
    {
        if (insert_at_end(dst_head, dst_tail, temp->data) == FAILURE)
            return FAILURE;
        temp = temp->next;
    }
    return SUCCESS;
}
int is_zero(Dlist *head)
{
    while (head)
    {
        if (head->data != 0)
            return 0;
        head = head->next;
    }
    return 1; 
}
int delete_list(Dlist **head, Dlist **tail)
{
    Dlist *temp = *head;
    while (temp)
    {
        Dlist *next = temp->next;
        free(temp);
        temp = next;
    }
    *head = *tail = NULL;
    return SUCCESS;
}