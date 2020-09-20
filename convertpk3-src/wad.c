#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "lzf.h"

//#include <stdint.h>  //wad.h already includes it.
#include "wad.h"

static char* errmsg=NULL;

static void errormsg(const char* msg)
{
    if(errmsg) free(errmsg);
    
    errmsg = malloc(strlen(msg)+1);
    strcpy(errmsg,msg);
}

char* W_geterrormsg()
{
    return errmsg;    
}

struct 
{
    char name[4];
    uint32_t numlumps;
    uint32_t offset;
} *header = NULL;

struct {
    uint32_t offset;
    uint32_t size;
    char name[8];
} *curlump;

wad_t* W_loadwad(const char* filename)
{
    //Open wad file
    wad_t* nwad;
    uint8_t* fbuf;
    bool compressed=false;
    long flen;

    FILE *fp = fopen(filename,"rb");
    if(!fp)
    {
        errormsg("Couldn't open wad file"); 
        free(nwad);
        fclose(fp);
        return NULL;
    }
    
    fseek(fp,0,SEEK_END);
    flen = ftell(fp);
    fbuf = malloc(flen);
    fseek(fp,0,SEEK_SET);
    
    if(fread(fbuf,1,flen,fp) < flen)
    {
        errormsg("Couldn't write file data to memory");
        free(nwad);
        fclose(fp);
        return NULL;
    }
    fclose(fp);
    
    header = fbuf;
    if(strncmp(header->name,"IWAD",4) && strncmp(header->name,"PWAD",4))
    {
        if(!strncmp(header->name,"ZWAD",4)) //is it a compressed wad?
        {
            errormsg("zwads are unsupported\nUse wadzip to extract it");
            return NULL;
        }
            //compressed = true;
        else
        {
            errormsg("specified file isn't a recognized wad file");
            return NULL;
        }
    }
    
    nwad = malloc(sizeof(wad_t));
    nwad->numlumps=header->numlumps;

    nwad->lumps = malloc(sizeof(lump_t)*nwad->numlumps);
    
    curlump = (fbuf+header->offset);
    for(unsigned int i=0;i<nwad->numlumps;i++,curlump++)
    {
        lump_t *lump = nwad->lumps+i;
        
//        for(unsigned int j=0;j<8 && curlump->name[j] != "\0";j++) putchar(curlump->name[j]);
        
        lump->size = curlump->size;
        if(lump->size) //Is it a lump marker?
        {
            if(compressed)
            {
                uint32_t usize = *((uint32_t*)fbuf+curlump->offset);
                if(!usize)
                {
                    puts("not compressed");
                    lump->size -= 4; 
                    curlump->offset += 4; 
                    goto jp1;
                }
                
                puts("now doing.."); for(unsigned j=0;j<8;j++) putchar(curlump->name[j]); putchar('\n');
                lump->data = malloc(usize); lump->size=usize;
                if(!lzf_decompress(fbuf+curlump->offset+4,curlump->size-4,lump->data,usize))
                {
                    errormsg("failed to decompress data");
                    return NULL;
                }
                puts("Decompressed!");
            }
            else
            {
jp1:
                lump->data = malloc(lump->size);
                memcpy(lump->data,fbuf+curlump->offset,lump->size);
            }
        }
        
        strncpy(lump->name,curlump->name,8);
        lump->name[8] = '\0';
    }
    
    free(fbuf);
    return nwad;
}

void W_closewad(wad_t* wad)
{
    for(unsigned int i=0;i<wad->numlumps;i++)
    {
        lump_t* lump = wad->lumps+i;
        if(lump->size) free(lump->data);
    }
    
    free(wad);
}