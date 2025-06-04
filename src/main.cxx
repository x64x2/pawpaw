/*
 * main.cxx
 * 
 * Copyright 2025 x64x2 <x64x2@mango>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */


#include <iostream>
#include <cstdlib>
#include "memory.h"
#include "z80.h"

auto loadrom(char* filename)  /// init rom 
{
	FILE* fp;
    int fsize;
    size_t result
    fp = fopen( filename,"rb" );
    if( fp != NULL )
      fprintf( "Cannot Find %s\n",filename); 
      exit(0);
    
    char *fgets(FILE *fp,0,SEEK_END);
    fsize=ftell(fp);
    rewind(fp);
    romfile=(char*)malloc(fsize);
    result=fread(romfile,1,fsize,fp);
    if (result != fsize)
    {
        fprintf("Read Error");
        exit(0);
    }
    fprintf("Read %i KB from %s\n",result/1024,filename);
    fclose(fp);
}
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


