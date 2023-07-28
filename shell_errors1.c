#include "shell.h"

/**
 * _erratoi - it will Converts the String To Integer
 *
 * @t: String that will Be Converted
 *
 * Return: in case of ther's No Numbs In String 0, Otherwise Converted Num
 *
 *       in case of error -1
 */

int _erratoi(char *t)
{
        unsigned long int rslt = 0;
        int i = 0;

        if (*t == '+')
                t++;  /* TODO: Why that Make Main Return 255? */
        for (i = 0;  t[i] != '\0'; i++)
        {
                if (t[i] >= '0' && t[i] <= '9')
                {
                        rslt *= 10;
                        rslt += (t[i] - '0');
                        if (rslt > INT_MAX)
                                return (-1);
                }
                else
                        return (-1);
        }
        return (rslt);
}


/**
 * print_error - it will Prints a Message in case of error
 *
 * @ifo: Parameter and Return ifo Struct
 *
 * @strg: the String that Containing Specified Error Type
 *
 * Return: in case of there No Numbs in string 0, Otherwise Convert Num
 *
 *        in case of error -1
 */

void print_error(info_t *ifo, char *strg)
{
        _eputs(ifo->fname);
        _eputs(": ");
        print_d(ifo->line_count, STDERR_FILENO);
        _eputs(": ");
        _eputs(ifo->argv[0]);
        _eputs(": ");
        _eputs(strg);
}

/**
 * print_d - Function that Prints Decimal (int) Num (base 10)
 *
 * @inpt: an Input
 *
 * @fed: a Filedescriptor that will Write into
 * Return: Numb Of Chars that will be Printed
 */

int print_d(int inpt, int fed)
{
        unsigned int _abc_, curr;
        int l, count = 0;
        int (*__putchar)(char) = _putchar;

        if (fed == STDERR_FILENO)
                __putchar = _putchar;
        if (inpt < 0)
        {
                _abc_ = -inpt;
                __putchar('-');
                count++;
        }
        else
                _abc_ = inpt;
        curr = _abc_;
        for (l = 1000000000; l > 1; l /= 10)
        {
                if (_abc_ / l)
                {
                        __putchar('0' + curr / l);
                        count++;
                }
                curr %= l;
        }
        __putchar('0' + curr);
        count++;

        return (count);
}


/**
 * convert_number - it's a Converter Function, Clone Of itoa
 *
 * @Nums: Number
 *
 * @abase: Base
 *
 * @aflags: Argument Flag
 * Return: String
 */

char *convert_number(long int Nums, int abase, int aflags)
{
        unsigned long N = Nums;
        char sgn = 0;
        char *potr;
        static char buff[50];
        static char *arr;

        if (!(aflags & CONVERT_UNSIGNED) && Nums < 0)
        {
                N = -Nums;
                sgn = '-';

        }
        arr = aflags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
        potr = &buff[49];
        *potr = '\0';

        do      {
                *--potr = arr[N % abase];
                N /= abase;
        } while (N != 0);

        if (sgn)
                *--potr = sgn;
        return (potr);
}


/**
 * remove_comments - a Function that Replaces 1st Instance Of '#' to '\0'
 *
 * @buff: the Address Of a String To be Modified
 * Return: 0 always;
 */

void remove_comments(char *buff)
{
        int l;

        for (l = 0; buff[l] != '\0'; l++)
                if (buff[l] == '#' && (!l || buff[l - 1] == ' '))
                {
                        buff[l] = '\0';
                        break;
                }
}
