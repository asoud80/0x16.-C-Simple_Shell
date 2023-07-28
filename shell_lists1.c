#include "shell.h"


/**
 * list_len - it will Determine the Len Of the Linked_List
 *
 * @h: a Pointer To the 1st Node
 * Return: the Size Of the List
 */

size_t list_len(const list_t *h)
{
        size_t i = 0;

        while (h)
        {
                h = h->next;
                i++;
        }
        return (i);
}


/**
 * list_to_strings - it will Return the Arr Of the String Of The list->str
 *
 * @head: a Pointer To 1st Node
 * Return: an Array Of the String
 */

char **list_to_strings(list_t *head)
{
        list_t *node = head;
        size_t i = list_len(head), j;
        char **strs;
        char *str;

        if (!head || !i)
                return (NULL);
        strs = malloc(sizeof(char *) * (i + 1));
        if (!strs)
                return (NULL);
        for (i = 0; node; node = node->next, i++)
        {
                str = malloc(_strlen(node->str) + 1);
                if (!str)
                {
                        for (j = 0; j < i; j++)
                                free(strs[j]);
                        free(strs);
                        return (NULL);
                }

                str = _strcpy(str, node->str);
                strs[i] = str;
        }
        strs[i] = NULL;
        return (strs);
}

/**
 * print_list - it will Prints All the Elements Of the List_t Linked_List
 *
 * @h: a Pointer To the 1st Node
 * Return: the Size Of the List
 */

size_t print_list(const list_t *h)
{
        size_t i = 0;

        while (h)
        {
                _puts(convert_number(h->num, 10, 0));
                _putchar(':');
                _putchar(' ');
                _puts(h->str ? h->str : "(nil)");
                _puts("\n");
                h = h->next;
                i++;
        }
        return (i);
}


/**
 * node_starts_with - it Return the Node Whom the Str will Starts by a Prefix
 *
 * @node: a Pointer To a List Head
 *
 * @prefix: it will String To be Matched
 *
 * @c: Next Char After Prefix To be Matched
 * Return: to Match a Node Or NULL
 */

list_t *node_starts_with(list_t *node, char *prefix, char c)
{
        char *p = NULL;

        while (node)
        {
                p = starts_with(node->str, prefix);
                if (p && ((c == -1) || (*p == c)))
                        return (node);
                node = node->next;
        }
        return (NULL);
}


/**
 * get_node_index - to Get an Index Of the NODE
 *
 * @head: a Pointer To List Head
 *
 * @node: a Pointer To a Node
 * Return: Index Of Node Or -1
 */

ssize_t get_node_index(list_t *head, list_t *node)
{
        size_t i = 0;

        while (head)
        {
                if (head == node)
                        return (i);
                head = head->next;
                i++;
        }
        return (-1);
}
