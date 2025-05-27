#include <stdio.h>
#include <stdlib.h>

#include "memory.h"
#include "z80.h"

void loadrom(char* filename)  /// init rom  
{
    FILE* fp;
    long fsize;
    size_t result;

    fp=fopen(filename,"rb");
    if (fp==NULL)
    {
        printf("Cannot Find %s\n",filename);
        exit(0);
    }
    fseek(fp,0,SEEK_END);
    fsize=ftell(fp);
    rewind(fp);
    romfile=(char*)malloc(fsize);
    result=fread(romfile,1,fsize,fp);
    if (result != fsize)
    {
        printf("Read Error");
        exit(0);
    }
    printf("Read %i KB from %s\n",result/1024,filename);
    fclose(fp);
}

void closerom()
{
    free(romfile);
}

int main(int argc, char* argv[])  
{
    if (!argv[1])
    {
        loadrom("test.sms");
    }
    else
    {
        loadrom(argv[1]);
    }
    romunpaged=&romfile[0];
    romslot0=&romfile[0];
    romslot1=&romfile[0x4000];
    romslot2=&romfile[0x8000];
    closerom();
    return 0;
}


