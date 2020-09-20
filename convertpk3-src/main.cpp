#include <iostream>
#include <string>

extern "C" 
{
#include "zip.h"
};

#include "convert.hpp"

void show_help()
{
    std::cout << "convertpk3 <wadfile> <pk3file> [<compression  method>] [<compression level>]\n"
    "convertpk3 command line utility to convert wad to pk3\n"
    "Copyright (C) 2018 Filipe \"filpam\" Paulino\n"
    "\n"
    "[<compression method>] which compression to choose (default: deflate)\n"
    "the valid compressions are:\n"
    "deflate (Deflated compression)\n"
    "lzf (Lzf compression)\n"
    "stored (no compression)\n\n"
    "[<compression level>] (deflate-only) the compression method to choose.(default: best)\n"
    "The valid compression levels are\n"
    "stored (no compression)\n"
    "fast (faster compression)\n"
    "best (best compression)\n" << std::endl;
}

int main(int argc, char** argv)
{
    using namespace std::literals;
    int method = Z_DEFLATED;
    int level = Z_DEFAULT_COMPRESSION;
    if(argc < 3)
    {
        show_help();
        std::cout << "Error: Not enough arguments" << std::endl;
        return -1;
    }
    
    if(argc >= 4)
    {
        if("stored"s == argv[3]) method = 0;
        else if("deflate"s == argv[3]) method = Z_DEFLATED;
        else if("lzf"s == argv[3]) method = Z_LZF;
        else
        {
            show_help();
            std::cout << "Error: Unrecognized compression method " << argv[3] << std::endl;
            return -1;
        }
    }
    
    if(argc >= 5)
    {
        if("best"s == argv[4]) level = Z_BEST_COMPRESSION;
        else if ("fast"s == argv[4]) level = Z_BEST_SPEED;
        else if ("stored"s == argv[4]) level = Z_NO_COMPRESSION;
        else
        {
            show_help();
            std::cout << "Error: Unknow compression level (valid levels are: best fast stored)" << argv[4] << std::endl;
            return -1;
        }
    }
    
    
    if(!convert2pk3(argv[1],argv[2],method,level,std::cout)) 
    {
        std::cout << "ERROR: conversion failed" << std::endl;
        return -1;
    }
    
    std::cout << "Done!" << std::endl;
    return 0;
}