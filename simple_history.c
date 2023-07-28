#include "shell.h"


/**
 * get_history_file - to Gets a History File
 *
 * @info: struct the Parameter
 * Return: to Allocat String that Containg History File
 */


char *get_history_file(info_t *info)
{
        char *buff, *dr;

        dr = _getenv(info, "home=");
        if (!dr)
                return (NULL);
        buff = malloc(sizeof(char) * (_strlen(dr) + _strlen(HIST_FILE) + 2));
        if (!buff)
                return (NULL);
        buff[0] = 0;
        _strcpy(buff, dr);
        _strcat(buff, "/");
        _strcat(buff, HIST_FILE);
        return (buff);
}


/**
 * write_history - to Create the File Or to Append To the Existing File
 *
 * @info: struct Parameter
 * Return: in case of Success return 1, otherwise -1
 */

int write_history(info_t *info)
{
        char *filename = get_history_file(info);
        list_t *node = NULL;
        ssize_t fd;

        if (!filename)
                return (-1);

        fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
        free(filename);
        if (fd == -1)
                return (-1);
        for (node = info->history; node; node = node->next)
        {
                _putsfd(node->str, fd);
                _putfd('\n', fd);
        }
        _putfd(BUF_FLUSH, fd);
        close(fd);
        return (1);
}


/**
 * read_history - it will Read the History From a File
 *
 * @info: struct a Parameter
 * Return: History Count in case of Success, Otherwise 0
 */

int read_history(info_t *info)
{
        char *buf = NULL, *filename = get_history_file(info);
        ssize_t fd, rdlen, fsize = 0;
        struct stat st;
        int i, last = 0, linecount = 0;

        if (!filename)
                return (0);

        fd = open(filename, O_RDONLY);
        free(filename);
        if (fd == -1)
                return (0);
        if (!fstat(fd, &st))
                fsize = st.st_size;
        if (fsize < 2)
                return (0);
        buf = malloc(sizeof(char) * (fsize + 1));
        if (!buf)
                return (0);
        rdlen = read(fd, buf, fsize);
        buf[fsize] = 0;
        if (rdlen <= 0)
                return (free(buf), 0);
        close(fd);
        for (i = 0; i < fsize; i++)
                if (buf[i] == '\n')
                {
                        buf[i] = 0;
                        build_history_list(info, buf + last, linecount++);
                        last = i + 1;
                }
        if (last != i)
                build_history_list(info, buf + last, linecount++);
        free(buf);
        info->histcount = linecount;
        while (info->histcount-- >= HIST_MAX)
                delete_node_at_index(&(info->history), 0);
        renumber_history(info);
        return (info->histcount);
}


/**
 * build_history_list - to Add an Entry into the History Linked_List
 *
 * @info: a structure that Containing a Potential Argums & used for Maintaining
 *
 * @buf: Buffer
 *
 * @linecount: History Linecount, Histcount
 * Return: 0 always
 */

int build_history_list(info_t *info, char *buf, int linecount)
{
        list_t *node = NULL;

        if (info->history)
                node = info->history;
        add_node_end(&node, buf, linecount);

        if (!info->history)
                info->history = node;
        return (0);
}


/**
 * renumber_history - to Renumber a History Linked_List aAter Changes
 *
 * @info: a structure that Containing a Potential Argums & used for Maintaining
 * Return: New History Count
 */

int renumber_history(info_t *info)
{
        int i = 0;
        list_t *node = info->history;

        while (node)
        {
                node->num = i++;
                node = node->next;
        }
        return (info->histcount = i);
}
