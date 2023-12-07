#include "shell.h"
/**
 * _memset - fills memory with a constant byte
 * @s: the pointer to the memory area
 * @b: the byte to fill *s with
 * @n: the amount of bytes to be filled
 * Return: a pointer to the memory area @s
 */
char *_memset(char *s, char b, unsigned int n)
{
    unsigned int i;

    for (i = 0; i < n; i++)
    {
        s[i] = b;
    }
    return s;
}

/**
 * ffree - frees a string of strings
 * @pp: a string of strings
 */
void ffree(char **pp)
{
    if (!pp)
    {
        return;
    }

    char **temp = pp;
    while (*pp)
    {
        free(*pp);
        pp++;
    }
    free(temp);
}

/**
 * _realloc - reallocates a block of memory
 * @ptr: pointer to the previous malloc'ated block
 * @old_size: byte size of the previous block
 * @new_size: byte size of the new block
 * Return: a pointer to the new block
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
    char *new_ptr;

    if (!ptr)
    {
        return malloc(new_size);
    }

    if (!new_size)
    {
        free(ptr);
        return NULL;
    }

    if (new_size == old_size)
    {
        return ptr;
    }

    new_ptr = malloc(new_size);

    if (!new_ptr)
    {
        return NULL;
    }

    for (unsigned int i = 0; i < old_size && i < new_size; i++)
    {
        new_ptr[i] = ((char *)ptr)[i];
    }

    free(ptr);
    return new_ptr;
}
