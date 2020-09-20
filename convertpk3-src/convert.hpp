#include <iostream>

extern "C"
{
#include "zip.h"
};

bool convert2pk3(const char* filename, const char* savename, int method, int level, std::ostream& omsg);