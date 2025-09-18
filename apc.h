#ifndef APC_H
#define APC_H
#define SUCCESS 0
#define FAILURE -1

typedef int data_t;
typedef struct node
{
	struct node *prev;
	data_t data;
	struct node *next;
}Dlist;

// Convert input string to doubly linked list (digit by digit)
int string_to_list(char *str, Dlist **head, Dlist **tail); 

// Print the number stored in the doubly linked list
int print_list(Dlist *head);

// Compare two numbers represented as linked lists
int compare(Dlist *head1, Dlist *head2);

// Free memory of a list from head to tail
void free_list(Dlist **head);

// Free and delete entire list
int delete_list(Dlist **head, Dlist **tail);

// Copy source list to destination list
int copy_list(Dlist *src_head, Dlist *src_tail, Dlist **dst_head, Dlist **dst_tail);

// Check if the list represents zero
int is_zero(Dlist *head);

/* Include the prototypes here */
int addition(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR);
int subtraction(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR);
int multiplication(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR);
int division(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR);

#endif