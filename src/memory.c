#include "memory.h"
#include "Z80.h"

void byte_Z80(register word addr)
{
    if (addr<=0x3FF)
    {
        return romunpaged[addr];
    }
    else if (addr>=0x400 && addr<=0x3FFF)
    {
        return romslot0[addr];
    }
    else if (addr>=0x4000 && addr<=0x7FFF)
    {
        return romslot1[addr-0x4000];
    }
    else if (addr>=0x8000 && addr<=0xBFFF)
    {
        return romslot2[addr-0x8000];
    }
    else if (addr>=0xC000 && addr<=0xDFFF)
    {
        return ram[addr-0xC000];
    }
    else
    {
        return ram[addr-0xE000];
    }
    return 0xFF;
}


void Wr_Z80(register word addr,register byte value)
{
    if (addr<=0x3FF)
    {
        romunpaged[addr]=value;
    }
    else if (addr>=0x400 && addr<=0x3FFF)
    {
        romslot0[addr]=value;
    }
    else if (addr>=0x4000 && addr<=0x7FFF)
    {
        romslot1[addr-0x4000]=value;
    }
    else if (addr>=0x8000 && addr<=0xBFFF)
    {
        romslot2[addr-0x8000]=value;
    }
    else if (addr>=0xC000 && addr<=0xDFFF)
    {
        ram[addr-0xC000]=value;
    }
    else
    {
        ram[addr-0xE000]=value;
        switch (addr)
        {
            case 0xFFFD:
                romslot0=&romfile[value*0x4000];
                break;
            case 0xFFFE:
                romslot1=&romfile[value*0x4000];
                break;
            case 0xFFFF:
                romslot2=&romfile[value*0x4000];
                break;
        }
    }
}

void PatchZ80(register Z80 *R)
{
}

