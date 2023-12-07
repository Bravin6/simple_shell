#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

typedef struct {
    /* Define any necessary data structures or fields here */
} info_t;

#define S_IFREG 0100000

/**
 * is_cmd - determines if a file is an executable command
 * @info: the info struct
 * @path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int is_cmd(info_t *info, char *path)
{
    struct stat st;

    (void)info;
    if (!path || stat(path, &st))
        return 0;

    if (st.st_mode & S_IFREG)
    {
        return 1;
    }
    return 0;
}

/**
 * dup_chars - duplicates characters
 * @pathstr: the PATH string
 * @start: starting index
 * @stop: stopping index
 *
 * Return: pointer to new buffer (caller must free)
 */
char *dup_chars(char *pathstr, int start, int stop)
{
    char *buf = NULL;
    int i, k;

    if (start >= stop)
        return NULL;

    buf = (char *)malloc((stop - start + 1) * sizeof(char));
    if (!buf)
    {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    for (k = 0, i = start; i < stop; i++)
    {
        buf[k++] = pathstr[i];
    }
    buf[k] = '\0';
    return buf;
}

/**
 * find_path - finds this cmd in the PATH string
 * @info: the info struct
 * @pathstr: the PATH string
 * @cmd: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
    int i = 0, curr_pos = 0;
    char *path;

    if (!pathstr)
        return NULL;
    if ((strlen(cmd) > 2) && strncmp(cmd, "./", 2) == 0)
    {
        if (is_cmd(info, cmd))
            return strdup(cmd);
    }
    while (1)
    {
        if (!pathstr[i] || pathstr[i] == ':')
        {
            path = dup_chars(pathstr, curr_pos, i);
            if (!*path)
                strcat(path, cmd);
            else
            {
                strcat(path, "/");
                strcat(path, cmd);
            }
            if (is_cmd(info, path))
                return path;
            if (!pathstr[i])
                break;
            curr_pos = i + 1;
        }
        i++;
    }
    return NULL;
}

int main() {
    info_t my_info;
    char *path = getenv("PATH");
    char *cmd_to_find = "ls";
    
    char *full_path = find_path(&my_info, path, cmd_to_find);
    if (full_path) {
        printf("Full path of %s: %s\n", cmd_to_find, full_path);
        free(full_path); // Don't forget to free the allocated memory
    } else {
        printf("Command %s not found in PATH.\n", cmd_to_find);
    }

    return 0;
}
