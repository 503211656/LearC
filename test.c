/****************************************************************************************
 *
 * file name : test
 * auther    : Wxl
 * date      : 2025/3/25
 * note      : none
 *
 * CopyRight (c) : 2025             all right reasever
 *
 ****************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <stdio.h>

char *strcat(char *dest, const char *src)
{
    char *dest1 = dest;
    while (*dest != '\0')
    {
        dest++;
    }
    while (*src != '\0')
    {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';

    return dest1;
}

int main()
{

    char dest[20] = "hello";
    char *src = "word";
    strcat(dest, src);
    printf("%s", dest);
    return 0;
}
