#include "shell.h"


/**
 * add_node - it will Adds Node To a Start of List
 *
 * @head: pointer Address To the Head Node
 *
 * @str: string Field Of the Node
 *
 * @num: the Node Index that Used By the History
 * Return: size of list
 */

list_t *add_node(list_t **head, const char *str, int num)
{
        list_t *new_head;

        if (!head)
                return (NULL);
        new_head = malloc(sizeof(list_t));
        if (!new_head)
                return (NULL);
        _memset((void *)new_head, 0, sizeof(list_t));
        new_head->num = num;
        if (str)
        {
                new_head->str = _strdup(str);
                if (!new_head->str)
                {
                        free(new_head);
                        return (NULL);
                }
        }
        new_head->next = *head;
        *head = new_head;
        return (new_head);
}


/**
 * add_node_end - it will Add the Node into End Of List
 *
 * @head: to Address Of Pointer To the Head Node
 *
 * @str: String Field Of the Node
 *
 * @num: the Node Index that Used By a History
 * Return: the Size Of the List
 */

list_t *add_node_end(list_t **head, const char *str, int num)
{
        list_t *new_node, *node;

        if (!head)
                return (NULL);

        node = *head;
        new_node = malloc(sizeof(list_t));
        if (!new_node)
                return (NULL);
        _memset((void *)new_node, 0, sizeof(list_t));
        new_node->num = num;
        if (str)
        {
                new_node->str = _strdup(str);
                if (!new_node->str)
                {
                        free(new_node);
                        return (NULL);
                }
        }
        if (node)
        {
                while (node->next)
                        node = node->next;
                node->next = new_node;
        }
        else
                *head = new_node;
        return (new_node);
}


/**
 * print_list_str - it will Print Only String Element Of the List_t Linked_List
 *
 * @h: a Pointer To 1st Node
 * Return: Size Of the List
 */

size_t print_list_str(const list_t *h)
{
        size_t i = 0;

        while (h)
        {
                _puts(h->str ? h->str : "(nil)");
                _puts("\n");
                h = h->next;
                i++;
        }
        return (i);
}


/**
 * delete_node_at_index - it will Delete The Node At a Given Index
 *
 * @head: Address Of a Pointer into the 1st Node
 *
 * @index: Index Of the Node To be Deleted
 * Return: if Success 1, otherwise 0
 */

int delete_node_at_index(list_t **head, unsigned int index)
{
        list_t *node, *prev_node;
        unsigned int i = 0;

        if (!head || !*head)
                return (0);

        if (!index)
        {
                node = *head;
                *head = (*head)->next;
                free(node->str);
                free(node);
                return (1);
        }
        node = *head;
        while (node)
        {
                if (i == index)
                {
                        prev_node->next = node->next;
                        free(node->str);
                        free(node);
                        return (1);
                }
                i++;
                prev_node = node;
                node = node->next;
        }
        return (0);
}


/**
 * free_list - it will Frees All the Nodes Of the List
 *
 * @head_ptr: to Address Of a Pointer into the Head Node
 * Return: Void
 */

void free_list(list_t **head_ptr)
{
        list_t *node, *next_node, *head;

        if (!head_ptr || !*head_ptr)
                return;
        head = *head_ptr;
        node = head;
        while (node)
        {
                next_node = node->next;
                free(node->str);
                free(node);
                node = next_node;
        }
        *head_ptr = NULL;
}
