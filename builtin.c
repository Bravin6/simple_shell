#include "shell.h"

/**
 * myExit - exits the shell
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: exits with a given exit status (0) if info.argv[0] != "exit"
 */
int myExit(info_t *info)
{
    int exitCheck;

    if (info->argv[1]) /* If there is an exit argument */
    {
        exitCheck = _errAtoi(info->argv[1]);
        if (exitCheck == -1)
        {
            info->status = 2;
            printError(info, "Illegal number: ");
            _ePuts(info->argv[1]);
            _ePutchar('\n');
            return 1;
        }
        info->errNum = _errAtoi(info->argv[1]);
        return -2;
    }
    info->errNum = -1;
    return -2;
}

/**
 * myCd - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int myCd(info_t *info)
{
    char *s, *dir, buffer[1024];
    int chdirRet;

    s = getcwd(buffer, 1024);
    if (!s)
        _puts("TODO: >>getcwd failure emsg here<<\n");
    if (!info->argv[1])
    {
        dir = _getenv(info, "HOME=");
        if (!dir)
            chdirRet = /* TODO: what should this be? */
                chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
        else
            chdirRet = chdir(dir);
    }
    else if (_strcmp(info->argv[1], "-") == 0)
    {
        if (!_getenv(info, "OLDPWD="))
        {
            _puts(s);
            _putchar('\n');
            return 1;
        }
        _puts(_getenv(info, "OLDPWD=")), _putchar('\n');
        chdirRet = /* TODO: what should this be? */
            chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
    }
    else
        chdirRet = chdir(info->argv[1]);
    if (chdirRet == -1)
    {
        printError(info, "can't cd to ");
        _ePuts(info->argv[1]), _ePutchar('\n');
    }
    else
    {
        _setenv(info, "OLDPWD", _getenv(info, "PWD="));
        _setenv(info, "PWD", getcwd(buffer, 1024));
    }
    return 0;
}

/**
 * myHelp - prints help information
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int myHelp(info_t *info)
{
    char **argArray;

    argArray = info->argv;
    _puts("Help function is not yet implemented.\n");
    if (0)
        _puts(*argArray); /* temp att_unused workaround */
    return 0;
}
