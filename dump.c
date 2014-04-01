
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

 
#ifndef NUM_COLS
#define NUM_COLS 8
#endif

void dump_hex(void *addr, size_t len, bool show_real_address, bool show_ascii)
{
    size_t offset = 0;
    if(show_real_address)
        offset = (size_t) addr;

    size_t i;

    // fix not NUM_COLS aligned data length	
    unsigned int block_align_correction_bytes;
    if(len % NUM_COLS)
        block_align_correction_bytes = NUM_COLS - (len % NUM_COLS);
    else
        block_align_correction_bytes = 0;

    /* iterate through data and print rows of NUM_COLS bytes, each */
    for(i = 0; i < (len + block_align_correction_bytes); i++)
    {
        // print offset address
        if(i % NUM_COLS == 0)
            printf("0x%06x: ", (i + offset));

        // print block as hex value
        if(i < len)
            printf("%02x ", 0xff & ((char*)addr)[i]);
        else
            printf("   "); // blank for alignment correction

        if(!show_ascii)
            continue;

        // print block as ASCII chars
        if((i % NUM_COLS) == (NUM_COLS - 1))
        {
            size_t k;
            for(k = i - (NUM_COLS - 1); k <= i; k++)
            {
                if(k >= len) // add space at end of block
                    putchar(' ');
                else if(isprint(((char*)addr)[k])) // printable ASCII char
                    putchar(0xff & ((char*)addr)[k]);
                else // no printable ASCII char
                    putchar('.');
            }
            putchar('\n');
        }
    }
}
