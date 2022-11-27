#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#define LIST_APPEND(string) list_append((struct list_node **)&my_linked_list, (struct list_node *)string_item_new(string));

struct list_node
{
    struct list_node *next;
};

struct list_node *list_get_tail(struct list_node **head)
{
    struct list_node *current_node = *head;
    struct list_node *last_node = NULL;

    while (current_node)
    {
        last_node = current_node;
        current_node = current_node->next;
    }

    return last_node;
};

struct list_node *list_append(struct list_node **head, struct list_node *item)
{

    struct list_node *tail = list_get_tail(head);
    if (!tail)
    {
        *head = item;
    }
    else
    {
        tail->next = item;
    }
    item->next = NULL;
    return item;
}

struct list_node *list_pop(struct list_node **head)
{
    struct list_node *current_head = *head;
    if (!current_head)
    {
        return NULL;
    }
    *head = (*head)->next;
    current_head->next = NULL;
    return current_head;
}

struct list_node *list_remove_item(struct list_node **head, const int index_to_remove)
{
    struct list_node *current_node = *head;
    struct list_node *previous_head = current_node;

    if (!current_node)
    {
        puts("Check the parameters you passed");
        return NULL;
    }

    int index = 0;

    for (;;)
    {

        if (index == index_to_remove)
        {
            previous_head->next = current_node->next;
            break;
        }

        index++;
        previous_head = current_node;
        current_node = current_node->next;
    }

    return previous_head;
}

struct list_node *list_reverse(struct list_node **head)
{
    struct list_node *temp;
    temp = *head;
    struct list_node *prev;
    struct list_node *reversedList = NULL;
    while (temp != NULL)
    {
        prev = temp;
        temp = temp->next;
        prev->next = reversedList;
        reversedList = prev;
    }
    *head = reversedList;
    return *head;
}

struct string_item
{
    struct list_node node;
    const char *string;
};

struct string_item *string_item_new(const char *string)
{
    struct string_item *item = malloc(sizeof(struct string_item));
    if (!item)
    {
        return NULL;
    }
    item->string = string;
    return item;
}
int main()
{
    struct string_item *my_linked_list = NULL;
    LIST_APPEND("Hello World");
    LIST_APPEND("Test001");
    LIST_APPEND("Test002");
    LIST_APPEND("Last Item of the Linked List");

    // list_remove_item((struct list_node **)&my_linked_list, 3);
    list_reverse((struct list_node **)&my_linked_list);

    struct string_item *string_item = my_linked_list;

    while (string_item)
    {
        printf("%s\n", string_item->string);
        string_item = (struct string_item *)string_item->node.next;
    }

    return 0;
}
