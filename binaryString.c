#include <stdio.h>
#include <string.h>
#include <stdlib.h>
char *inputString(FILE* fr, size_t size){
//The size is extended by the input with the value of the provisional
    char *str;
    int ch;
    size_t len = 0;
    str = realloc(NULL, sizeof(char)*size);//size is start size
    if(!str)return str;
    while(EOF!=(ch=fgetc(fr)) && ch != '\n'){
        str[len++]=ch;
        if(len==size){
            str = realloc(str, sizeof(char)*(size+=16));
            if(!str)return str;
        }
    }
    str[len++]='\0';

    return realloc(str, sizeof(char)*len);
}

int CopyBin2Text(char* rafname, char* txtname)      // changed return value
{
    FILE *fraf, *ftxt;
char *c;    
c = inputString(fraf, 10);
    if ((fraf = fopen(rafname,"rb")) == NULL)
        return 0;                                   // failure

    if ((ftxt = fopen(txtname,"wt")) == NULL) {     // changed mode
        fclose(fraf);
        return 0;                                   // failure
    }
    fprintf(ftxt, "---------------------------------------\n");
    while(fread(&fraf, strlen(c), 1, ftxt) == 1)       // use return value to loop
        fprintf(ftxt, "%s\n",NULL);
    fclose(ftxt);

    fclose(fraf);
    return 1;                                       // success
}

int makefile(char* rafname)
{
    FILE *fraf, *ftxt;
    
    if ((fraf = fopen(rafname,"wb")) == NULL)
        return 0;                                   // failure

    fclose(fraf);
    return 1;                                       // success
}

int main(void)
{
    if (makefile("abc.bin") == 0)
        printf("Failure\n");
    else {
        if (CopyBin2Text("abc.bin", "cba.txt") == 0)
            printf("Failure\n");
        else
            printf("Success\n");
    }
    return 0;
}
