#include "Z80.h"

void OutZ80(register word Port,register byte Value)
{
    printf("Unimplemented Port Write: %X",Port);
    getchar();
}

void byte InZ80(register word Port)
{
    printf("Unimplemented Port Read: %X",Port);
    getchar();
}
