#include "shell.h"

/**
 * addNode - adds a node to the start of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: pointer to the new node, or NULL on failure
 */
list_t *addNode(list_t **head, const char *str, int num)
{
    if (!head)
        return NULL;

    list_t *newNode = malloc(sizeof(list_t));
    if (!newNode)
        return NULL;

    newNode->num = num;
    newNode->str = str ? _strdup(str) : NULL;
    newNode->next = *head;
    *head = newNode;

    return newNode;
}

/**
 * addNodeEnd - adds a node to the end of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: pointer to the new node, or NULL on failure
 */
list_t *addNodeEnd(list_t **head, const char *str, int num)
{
    if (!head)
        return NULL;

    list_t *newNode = malloc(sizeof(list_t));
    if (!newNode)
        return NULL;

    newNode->num = num;
    newNode->str = str ? _strdup(str) : NULL;
    newNode->next = NULL;

    if (*head)
    {
        list_t *node = *head;
        while (node->next)
            node = node->next;
        node->next = newNode;
    }
    else
    {
        *head = newNode;
    }

    return newNode;
}

/**
 * printListStr - prints only the str element of a list_t linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t printListStr(const list_t *h)
{
    size_t i = 0;

    while (h)
    {
        _puts(h->str ? h->str : "(nil)");
        _putchar(' ');
        h = h->next;
        i++;
    }
    _puts("\n");
    return i;
}

/**
 * deleteNodeAtIndex - deletes node at given index
 * @head: address of pointer to first node
 * @index: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int deleteNodeAtIndex(list_t **head, unsigned int index)
{
    if (!head || !*head)
        return 0;

    list_t *node = *head;

    if (index == 0)
    {
        *head = node->next;
        free(node->str);
        free(node);
        return 1;
    }

    for (unsigned int i = 0; node; i++)
    {
        if (i + 1 == index && node->next)
        {
            list_t *nextNode = node->next;
            node->next = nextNode->next;
            free(nextNode->str);
            free(nextNode);
            return 1;
        }
        node = node->next;
    }

    return 0;
}

/**
 * freeList - frees all nodes of a list
 * @head: address of pointer to head node
 *
 * Return: void
 */
void freeList(list_t **head)
{
    list_t *node, *nextNode;

    if (!head || !*head)
        return;

    node = *head;

    while (node)
    {
        nextNode = node->next;
        free(node->str);
        free(node);
        node = nextNode;
    }

    *head = NULL;
}
