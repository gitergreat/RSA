#ifndef _CRYPT_H
#define _CRYPT_H

mpz_t c, m, e, d, n; 

int encrypt()
{
    int flag;
    printf("Plaintext format for input:\n1.hex value  2.ASCII code string\n");
    scanf("%d", &flag);
    if (flag != 1 && flag != 2){   
        printf("Wrong choice!\n");
        return 0;
    }
    if (!readFile(m_location, "r")){
        return 0;
    } else {
        if (flag == 1){
            printf("plaintext: \n  %s\n", buff);
            mpz_init_set_str(m, buff, 16);
            
        } else {
            printf("plaintext: \n  %s\n", buff);
            char text[MAXSIZE];
            int i=0, j=0;
            int len = strlen(buff);
            for (i=0; i<len; i++){
                ascii2Hex(buff[i], &text[j], &text[j+1]);
                j = j+2;
            }
            text[j] = '\0';
            mpz_init_set_str(m, text, 16);
        }
        
    }

    if (!readFile(e_location, "r")){
        return 0;
    } else {
        printf("e: \n  %s\n", buff);
        mpz_init_set_str(e, buff, 16);
    }

    if (!readFile(n_location, "r")){
        return 0;
    } else {
        printf("n: \n  %s\n", buff);
        mpz_init_set_str(n, buff, 16);
    }

    mpz_init(c);
    mpz_powm(c, m, e, n); 
    gmp_printf("%s\n  %ZX\n\n", "The encrypted ciphertext: ", c);
        
    if (!writeFile(c_location, "w", c)){
        return 0;
    }
    return 1;
}

int decrypt()
{
    int flag;
    printf("Ciphertext format for output:\n1.hex value  2.ASCII code string\n");
    scanf("%d", &flag);
    if (flag != 1 && flag != 2){   
        printf("Wrong choice!\n");
        return 0;
    }

    if (!readFile(c_location, "r")){
        return 0;
    } else {
        printf("ciphertext: \n  %s\n", buff);
        mpz_set_str(c, buff, 16);
    }

    if (!readFile(d_location, "r")){
        return 0;
    } else {
        printf("d: \n  %s\n", buff);
        mpz_init_set_str(d, buff, 16);
    }

    if (!readFile(n_location, "r")){
        return 0;
    } else {
        printf("n: \n  %s\n", buff);
        mpz_init_set_str(n, buff, 16);
    }
    mpz_init(m);
    mpz_powm(m, c, d, n); 
    
    if(flag == 1){
        gmp_printf("%s\n  %ZX\n\n","The decrypted plaintext: ", m);

        if (!writeFile(m_location, "w", m)){
            return 0;
        }
        return 1;  
    } else {
        char text[MAXSIZE];
        mpz_get_str(text, -16, m);

        FILE *fp = fopen(m_location, "w");

        if (fp==NULL){
            printf("Open %s failed!\n", m_location);
            return 0;
        } 

        int i=0, j=0;
        char s[3];
        char chout;

        printf("%s\n  ", "The decrypted plaintext: ");
        while (i<strlen(text)) {
            s[0] = text[i++];
            s[1] = text[i++];
            s[2] = '\0';
            chout = hex2Ascii(s);
            printf("%c", chout);
            if (fputc(chout, fp)==EOF){
                printf("Write %s failed!\n", m_location);
                return 0;
            }
        }
        printf("\n");
        fclose(fp);
        return 1;
    }
} 

#endif