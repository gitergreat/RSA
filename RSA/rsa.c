#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <gmp.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include "file.h"
#include "crypt.h"
#include "initial.h"

void main(int argc, char **argv)
{
    printf("- - - - - - - - - - RSA - - - - - - - - - -\n");
    int ch;
    ch = get_option(argc, argv);
    if (ch == 1)
    {
        printf("Encrypt-->\n\n");
        printf("Regenerate key?\ny(yes)  n(no)\n");
        if (getchar() == 'y') initial();
        if(!encrypt()){
            printf("Encryption failed!\n");
        }
    } else if (ch == 0) {
        printf("Decrypt-->\n\n");
        if(!decrypt()){
            printf("Decryption failed!\n");
        }
    }

    mpz_clear(m);
    mpz_clear(c);
    mpz_clear(e);
    mpz_clear(d);
    mpz_clear(n);
}