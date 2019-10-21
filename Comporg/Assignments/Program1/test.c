#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "cs3843p1.h"
#define PRINTABLE(c) (((c >= ' ') && (c <= '~')) ? 1 : 0)

/************************** hexDump ******************************************
int hexDump(char *psbBuffer, int iBufferLength, int iBytesPerLine)
Purpose:
    Prints the contents of the specified buffer in both printable
    characters(where possible) and hexadecimal. 
Parameters:
    - char *psbBuffer    a buffer which can contain printable and binary
                         characters
    - int iBufferLength  the length of sbBuffer in bytes. You may assume that
                         this must be less than 4800 bytes
    - int iBytesPerLine  the number of bytes to print per line. This value must
                         be at least 10 and at most 50
Notes:
    1. Num lines printed is iBufferLength/iBytesPerLine
    2. Each printed line must include its beginning offset(relative to 0) shown
       in hex, printable characters, and corresponding hexadecimal characters.
       If a particular byte isn't printable, display a period. A space is 
       printed after every four characters of data
    3. Must compile and execute on a fox server
Return Value:
    -1    invalid parameter
    n     number of lines printed including suppressed lines
****************************************************************************/

int hexDump(char *psbBuffer, int iBufferLength, int iBytesPerLine)
{
    int isZero;                                       // index to check if current byte is non printable
    bool allZero;                                     // flag to check if line is all zeros
    int printChar;                                    // index of current byte being read (x)
    int printHex;                                     // used for hex representation printing
    int jump;                                         // line iterator (y)
    int numLines = iBufferLength / iBytesPerLine + 1; // number of lines
    int zeroLines = 0;                                // keeps track of the number of lines that are all 0

    printf("hexDump of %d bytes beginning at %p\n", iBufferLength, psbBuffer);

    // for loop that traverses psbBuffer by chunks of iBytesPerLine
    for (jump = 0; jump < iBufferLength; jump = jump + iBytesPerLine)
    {
        //
        // setting isZero index
        isZero = jump;
        // setting allZero flag
        allZero = true;

        // while loop to check if this line is all zeros
        while (isZero < jump + iBytesPerLine)
        {
            // exit while loop if a printable char is encountered
            if (PRINTABLE(psbBuffer[isZero]))
            {
                allZero = false; // the line does not have all zeroes
                break;           // break out of this while loop
            }

            isZero++; // move along psbBuffer chunk
        }
        // if the line is all zeroes, increment the counter and move to the next
        // line
        if (allZero == true)
        {
            zeroLines++; // increment the number of zero lines
            continue;
        }
        // otherwise if the line isn't all zeroes, print out the number of
        // suppressed lines, reset the counter and carry on normally.
        else if (zeroLines > 0)
        {
            printf(">>>> (%d lines) suppressed - all zero\n", zeroLines);
            zeroLines = 0; // reset zeroLines counter
        }
        //

        // offset
        printf("%04x  ", jump);

        // setting char index
        printChar = jump;

        // setting hex index
        printHex = jump;

        // while loop that prints out printable chars where possible
        while (printChar < jump + iBytesPerLine)
        {
            // Each character is followed by a space for readibility.
            // An extra space is included between each four characters printed.
            // If a character isn't printable, show a dot.
            if (PRINTABLE(psbBuffer[printChar]))
            {
                if ((printChar - 3) % 4 == 0)
                    printf("%c  ", psbBuffer[printChar]);
                else
                    printf("%c ", psbBuffer[printChar]);
            }
            else
            {
                if ((printChar - 3) % 4 == 0)
                    printf("%c  ", 0x2E);
                else
                    printf("%c ", 0x2E);
            }

            // increment char index
            printChar++;
        }

        // prints hex vals row and indents it by 5 chars
        printf("\n     ");

        // while loop that prints out hex values
        while (printHex < jump + iBytesPerLine)
        {
            // Each character is followed by a space for readibility.
            // An extra space is included between each four characters printed.
            // If a character isn't printable, show a dot.
            if (PRINTABLE(psbBuffer[printHex]))
            {
                if ((printHex - 3) % 4 == 0)
                    printf("%02X  ", psbBuffer[printHex]);
                else
                    printf("%02X", psbBuffer[printHex]);
            }
            else
            {
                if ((printHex - 3) % 4 == 0)
                    printf("%02X  ", 0);
                else
                    printf("%02X", 0);
            }

            // increment hex index
            printHex++;
        }

        // move on to next chunk in buffer
        printf("\n");
    }

    return numLines;
}