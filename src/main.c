#include "lists.h"
#include "thermals.h"

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    struct NODE *sensors = (struct NODE *)malloc(sizeof(struct NODE *));

    get_sensors(sensors);

    return 0;
}

void linked_list_test(void)
{
    struct NODE *base;
    struct NODE *head;

    base = (struct NODE *)malloc(sizeof(struct NODE));
    base->data = "Hello, ";
    base->next = (struct NODE *)malloc(sizeof(struct NODE));

    head = base->next;
    head->data = "World! ";
    head->next = (struct NODE *)malloc(sizeof(struct NODE));

    head = head->next;
    head->data = "How ";
    head->next = (struct NODE *)malloc(sizeof(struct NODE));

    head = head->next;
    head->data = "are ";
    head->next = (struct NODE *)malloc(sizeof(struct NODE));

    head = head->next;
    head->data = "You?";
    head->next = (struct NODE *)malloc(sizeof(struct NODE));

    struct NODE *current = base;
    while (current != NULL)
    {
        printf(current->data);
        current = current->next;
    }
}