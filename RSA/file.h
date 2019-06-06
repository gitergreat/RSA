#ifndef _FILE_H
#define _FILE_H
#define TEXTSIZE 1024
#define MAXSIZE 2048
#define LOCSIZE 100

char buff[TEXTSIZE];
char m_location[LOCSIZE] = "rsa_plain.txt";
char c_location[LOCSIZE] = "rsa_cipher.txt";
char n_location[LOCSIZE] = "n.txt";
char e_location[LOCSIZE] = "e.txt";
char d_location[LOCSIZE] = "d.txt";

int readFile(char * filename, char * mode)
{
    int i = 0;
    char ch;
    FILE *fp = fopen(filename, mode);
   
    if (fp==NULL)
    {
        printf("Open %s failed!\n", filename);
        return 0;
    }

    for (i=0, ch=fgetc(fp); (ch!=EOF)&&(i<1023); i++)
    {
        buff[i] = ch;
        ch=fgetc(fp);
    }
    buff[i] = '\0';
    fclose(fp);
    return 1;
}


int writeFile(char * filename, char * mode, mpz_t cm)
{
    FILE *fp = fopen(filename, mode);

    if (fp==NULL)
    {
        printf("Open %s failed!\n", filename);
        return 0;
    }

    mpz_out_str(fp, -16, cm);
    fclose(fp);
    return 1;
}

int get_option(int argc, char **argv){    
    int crypt;
    int opt;  
    int opt_count = 0;     

	while((opt=getopt(argc,argv,"p:n:e:d:c:"))!=-1)       
	{
        if (opt == 'e') crypt = 1;
        if (opt == 'd') {
            if (crypt == 1){
                printf("\"-e\" and \"-d\" cannot appear together!\n");
                return -1;
            } else {
                crypt = 0;
            }
        }

        switch(opt)     
	    {       
		case 'p':      
			strcpy(m_location, optarg);    
			break;       
		case 'n':       
			strcpy(n_location, optarg);      
			break;       
		case 'e':       
			strcpy(e_location, optarg);   
			break;       
		case 'd': 
			strcpy(d_location, optarg);
		case 'c': 
			strcpy(c_location, optarg);      
			break;   
		default:       
			printf("Unknown option!\n");
            return -1;     
	    }
        opt_count++;
    }

    if (opt_count!=4){
        printf("The number of options error!\n");
        return -1;
    }
    return crypt;
}

int tolower(int c)  
{  
    if (c >= 'A' && c <= 'Z')  
    {  
        return c + 'a' - 'A';  
    }  
    else  
    {  
        return c;  
    }  
}

char hex2Ascii(char s[])  
{  
    int i = 0;  
    char n = 0;  

    for (; (s[i]>='0' && s[i]<='9') || (s[i]>='a' && s[i]<='z') || (s[i]>='A' && s[i]<='Z'); ++i)  
    {  
        if (tolower(s[i])>'9') {  
            n = 16*n+(10+tolower(s[i])-'a');  
        } else {  
            n = 16*n+(tolower(s[i])-'0');  
        }  
    }  
    return n;  
} 

void ascii2Hex(char ch, char *h1, char *h2)
{
    char b;
    b = ch%16;
    if (b<10){
        *h2 = '0'+b;
    } else {
        *h2 = 'A'+b-10;
    }
    ch = ch/16;
    b = ch%16;
    if (b<10) {
        *h1 = '0'+b;
    } else {
        *h1 = 'A'+b-10; 
    }
}

#endif