//cs3843p1.c by Abit Gurung
// If compiling using visual studio, tell the compiler not to give its warnings
// about the safety of scanf and printf
#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdarg.h>
#include "cs3843p2.h"

/*
    defines what is prinatable and returns 1 
*/
#define PRINTABLE(c) ((c >= ' ' && c <= '~') ? 1 : 0)
#define DEBUG_ON
#ifndef DEBUG_ON
// define the DEBUG macros as null values (i.e. doesn't do anything)
#define DEBUG(S)
#define DEBUGD(S)
#define DEBUGL(S)
#else
#define DEBUG(S) fprintf(stderr, "debug: at line %d, %s is '%s'\n", __LINE__, #S, S)
#define DEBUGD(S) fprintf(stderr, "debug: at line %d, %s is %10.2lf\n", __LINE__, #S, S)
#define DEBUGL(S) fprintf(stderr, "debug: at line %d, %s is %ld\n", __LINE__, #S, S)
#endif

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
int encrypt(char *psbInBuffer, int iInBufferLgth, char *pszKey, char *psbOutBuffer, int iOutMaxBufferLgth)
{
    char *pcCharL;
    char *pcInBuf;

    strcpy(psbOutBuffer, pszKey);
    memcpy(psbOutBuffer + strlen(pszKey), &iInBufferLgth, sizeof(iInBufferLgth));
    memcpy(psbOutBuffer + strlen(pszKey) + sizeof(iInBufferLgth), psbInBuffer, iInBufferLgth);

    int totalLengeth = strlen(pszKey) + 4 + iInBufferLgth;

    int pcPad = 0;

    if (totalLengeth % 4 != 0)
    {
        pcPad = 4 - (totalLengeth % 4);
        memset(psbOutBuffer + strlen(pszKey) + 4 + iInBufferLgth, '\0', pcPad);
        totalLengeth = totalLengeth + pcPad;
    }
    char *pCh;
    int iSum = sumKey(pszKey);
    int k = (iSum % (64 - strlen(pszKey))) + 1;

#ifdef DEBUG_ON
    printf("padded with %d for a total of %d bytes\n", pcPad, totalLengeth);
    hexDump(psbOutBuffer, totalLengeth, B_PER_LINE);
#endif

    charSwap(pCh, k, totalLengeth);

#ifdef DEBUG_ON
    printf("swapping every %d bytes, size = %d\n", k, totalLengeth);
    hexDump(psbOutBuffer, totalLengeth, B_PER_LINE);
#endif

    int i;
    k = iSum % 17 + 1;

    for (pCh = psbOutBuffer, i = 0; i < totalLengeth; pCh += 4, i += 4)
    {
        unsigned int uixResult = *((unsigned int *)pCh);
        uixResult = bitSwap(uixResult, k);
        memcpy(&psbOutBuffer[i], &uixResult, 4);
    }
#ifdef DEBUG_ON
    printf("left rotational shift by %d bits, Size = %d bytes\n", k, totalLengeth);
    hexDump(psbOutBuffer, totalLengeth, B_PER_LINE);
#endif

    k = iSum % 7 + 1;

    for (pCh = psbOutBuffer, i = 0; i < totalLengeth; pCh += 4, i += 4)
    {
        unsigned int uixResult = *((unsigned int *)pCh);
        uixResult = rotateLeft(uixResult, k);
        memcpy(&psbOutBuffer[i], &uixResult, 4);
    }
#ifdef DEBUG_ON
    printf("swap every %d bits, Size = %d bytes\n", k, totalLengeth);
    hexDump(psbOutBuffer, totalLengeth, B_PER_LINE);
#endif

    return totalLengeth;
}
int decrypt(char *psbInBuffer, int iInBufferLgth, char *pszKey, char *psbOutBuffer, int iOutMaxBufferLgth)
{
    memcpy(psbOutBuffer, psbInBuffer, iInBufferLgth);
    char *pCh;
    unsigned int uixResult = *((unsigned int *)pCh);
    int i;
    int iSum = sumKey(pszKey);
    int k = iSum % 7 + 1;
    for (pCh = psbOutBuffer, i = 0; i < iInBufferLgth; i += 4, pCh += 4)
    {
        unsigned int uixResult = *((unsigned int *)pCh);
        uixResult = bitSwap(uixResult, k);
        memcpy(&psbOutBuffer[i], &uixResult, 4);
    }
#ifdef DEBUG_ON
    printf("swap every %d bits, size = %d bytes\n", k, iInBufferLgth);
    hexDump(psbOutBuffer, iInBufferLgth, B_PER_LINE);
#endif
    k = iSum % 17 + 1;
    pCh = psbOutBuffer;
    for (i = 0, pCh = psbOutBuffer; i < iInBufferLgth; i += 4, pCh += 4)
    {
        unsigned int uixResult = *((unsigned int *)pCh);
        uixResult = rotateLeft(uixResult, 32 - k);
        memcpy(&psbOutBuffer[i], &uixResult, 4);
    }
#ifdef DEBUG_ON
    printf("right rotational shift by %d bits, size = %d bytes\n", k, iInBufferLgth);
    hexDump(psbOutBuffer, iInBufferLgth, B_PER_LINE);
#endif

    k = (iSum % (64 - strlen(pszKey))) + 1;
    charSwap(psbOutBuffer, k, iInBufferLgth);
#ifdef DEBUG_ON
    printf("swapping every %d bytes, size = %d\n", k, iInBufferLgth);
    hexDump(psbOutBuffer, iInBufferLgth, B_PER_LINE);
#endif
    if (memcmp(pszKey, psbOutBuffer, strlen(pszKey)) == 0)
    {
        printf("Keys match!!!\n");
    }
    else
    {
        return -8;
    }
    int buffer;
    buffer = iInBufferLgth - (strlen(pszKey) + sizeof(iInBufferLgth));
    memmove(psbOutBuffer, psbOutBuffer + strlen(pszKey) + sizeof(buffer), buffer);
    return buffer;
}

unsigned int bitSwap(unsigned int uiOrig, int k)
{
    unsigned int uiResult = uiOrig;
    int i, j;
    for (i = 0, j = k; j < 32; i += k + 1, j += k + 1)
    {
        unsigned uiBiti = ((uiResult & (1 << i)) && 1);
        unsigned uiBitj = ((uiResult & (1 << j)) && 1);

        if (uiBiti ^ uiBitj == 1)
        {
            uiResult ^= 1 << i;
            uiResult ^= 1 << j;
        }
    }
    return uiResult;
}
void charSwap(char *psbBuf, int k, int iBuffLgth)
{
    char *buffer4 = psbBuf + k;
    char *current = psbBuf;
    char temp;

    while (current < iBuffLgth + psbBuf)
    {
        temp = *buffer4;
        *buffer4 = *current;
        *current = temp;

        current = current + 5;
        buffer4 = buffer4 + k + 1;
    }
}
unsigned int rotateLeft(unsigned int uiOrig, int k)
{
    unsigned int uiSave = (uiOrig << k);
    uiSave |= uiOrig >> (sizeof(uiOrig) * 32 - k);
    return uiSave;
}
