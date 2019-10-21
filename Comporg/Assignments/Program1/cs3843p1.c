//cs3843p1.c by Abit Gurung
// If compiling using visual studio, tell the compiler not to give its warnings
// about the safety of scanf and printf
#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdarg.h>
#include "cs3843p1.h"

/*
    defines what is prinatable and returns 1 
*/
#define PRINTABLE(c) ((c >= ' ' && c <= '~') ? 1 : 0)

/************************** hexDump ******************************************
int hexDump(char *psbBuffer, int iBufferLength, int iBytesPerLine)
Purpose:
    int hexDump(char *psbBuffer, int iBufferLength, int iBytesPerLine) 
    prints (to stdout) the contents of the specified buffer in 
    both printable characters (where possible) and hexadecimal. 
Parameters:
    - char *psbBuffer    a buffer which can contain printable and binary
                         characters
    - int iBufferLength  the length of sbBuffer in bytes. You may assume that
                         this must be less than 4800 bytes
    - int iBytesPerLine  the number of bytes to print per line. This value must
                         be at least 10 and at most 50
Return Value:
    -1    invalid parameter
     n     number of lines printed including suppressed lines
****************************************************************************/
int hexDump(char *psbBuffer, int iBufferLength, int iBytesPerLine)
{
    int i, j, k;
    printf("hexDump of %d bytes beginning at %p\n", iBufferLength, psbBuffer);

    //loops through the buffer line by line
    for (i = 0; i < iBufferLength; i = i + iBytesPerLine)
    {
        //prints 4 digit offset
        printf("%04x ", i);

        //set offset to beginig of next line and loop through each char in the line
        for (j = i; j < i + iBytesPerLine; j++)
        {
            //if printable prints to the stdout else print a dot
            if (PRINTABLE(psbBuffer[j]))
            {
                if ((j - 3) % 4 == 0)
                    printf("%c  ", psbBuffer[j]);
                else
                    printf("%c ", psbBuffer[j]);
            }
            else
            {
                if ((j - 3) % 4 == 0)
                    printf("%c  ", 0x2E);
                else
                    printf("%c ", 0x2E);
            }
        }
        printf("\n     ");
        //set offset to beginig of next line and loop through each char in the line
        for (k = i; k < i + iBytesPerLine; k++)
        {
            //if printable prints to the stdout else print a zero
            if (PRINTABLE(psbBuffer[k]))
            {
                if ((k - 3) % 4 == 0)
                    printf("%02X ", psbBuffer[k]);
                else
                    printf("%02X", psbBuffer[k]);
            }
            else
            {
                if ((k - 3) % 4 == 0)
                    printf("%02X ", 0);
                else
                    printf("%02X", 0);
            }
        }
        printf("\n");
    }
    return iBufferLength / iBytesPerLine + 1;
}