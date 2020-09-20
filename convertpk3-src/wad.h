

#ifndef _WAD_H_
#define _WAD_H_
#include <stdint.h>

typedef struct 
{
    uint8_t *data;
    unsigned int size;
    char name[9]; //Lump names are at max 8 characters longs, 9th character is for the null byte
} lump_t;

typedef struct
{
    uint32_t numlumps;
    lump_t *lumps;
} wad_t;

wad_t* W_loadwad(const char* filename);
char* W_geterrormsg();
void W_closewad(wad_t* wad); // free wads resources
#endif