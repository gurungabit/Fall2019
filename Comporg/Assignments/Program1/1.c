/*++

Module:

    Hex dump program.

    CSE 373 2000 Winter Quarter
    University of Washington

Description:

    This module is a quick and dirty hex dump program that reads
    in and produces a hex dump of a file.  The input is stdin and
    the output is stdout.  The program is fairly dumb in that it
    is limited to files of at most 50,000 bytes.

Author:

    Gary Kimura     [GaryKi@cs.washington.edu]      4-Feb-2000

Revision History:

--*/

#include <stdio.h>

//
//  We'll simply declare an array to hold the input buffer and keep
//  a count of how many bytes are being used
//

unsigned char InputString[50000];
int InputStringLength;

int ReadBuffer(unsigned char *Buffer, int Limit)

/*++

Routine Descriptoin:

    A simply routine to simply read in from stdin and fill the buffer
    up to the limit

Arguments:

    Buffer - A pointer to the buffer we're to fill

    Limit - The maximum number of characters we can use in the buffer

Return Value:

    int - The actual number of bytes read in

--*/

{
    int c, i;

    //
    //  Loop until we've exhausted the input or the limit
    //

    i = 0;
    while ((--Limit > 0) && ((c = getchar())) != EOF)
    {

        Buffer[i++] = c;
    }

    //
    //  And return the number of bytes we're read in
    //

    return i;
}

void HexDumpBuffer(
    void *Buffer,
    int Count)

/*++

Routine Description:

    A simple routine that simply does a hex dump of an buffer

Arguments:

    Buffer - Supplies the buffer to dump

    Count - Supplies the number of characters (bytes) to dump

Return Value:

    None.

--*/

{
    int i, j;
    unsigned char *c = (unsigned char *)Buffer;
    unsigned char CharBuffer[17];

    //
    //  Loop through every byte in the buffer, and output
    //  its hex value.  For every 16 bytes we'll also output
    //  the line header and afterwards the printable version
    //  of the buffer
    //

    CharBuffer[16] = 0;

    for (i = 0; i < Count; i += 1)
    {

        if ((i % 16) == 0)
        {
            printf("%08lx", i);
        }

        printf(" %02x", c[i]);

        CharBuffer[i % 16] = (c[i] > 31 && c[i] < 127 ? c[i] : '.');

        if ((i % 16) == 15)
        {
            printf(" %16s\n", CharBuffer);
        }
    }

    //
    //  Now handle the case where we haven't finished the last line
    //  of char buffer
    //

    if ((i % 16) != 15)
    {

        for (j = (i % 16); j < 16; j += 1)
        {
            printf("  ");
        }

        CharBuffer[(i) % 16] = 0;
        printf(" %16s\n", CharBuffer);
    }

    //
    //  And return to our caller
    //

    return;
}

void main(
    int argc,
    char *argv[])

/*++

Routine Description:

    Reads is and hex dumps a file

Arguments:

    None.

Return Value:

    None.

--*/

{
    printf("%d \n", argc);
    printf("%s\n", argv[1]);

    if (argc >= 2)
    {

        if (stdin != freopen(argv[1], "rb", stdin))
        {

            printf("Redirection of stdin error\n");
            return;
        }
    }

    if (argc >= 3)
    {

        if (stdout != freopen(argv[2], "wb", stdout))
        {

            printf("Redirection of stdout error\n");
            return;
        }
    }

    InputStringLength = ReadBuffer(InputString, 50000);
    HexDumpBuffer(InputString, InputStringLength);

    return;
}