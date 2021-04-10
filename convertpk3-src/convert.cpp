#ifndef __has_include
  static_assert(false, "__has_include not supported");
#else
#  if __has_include(<filesystem>)
#    include <filesystem>
     namespace fs = std::filesystem;
#  elif __has_include(<experimental/filesystem>)
#    include <experimental/filesystem>
     namespace fs = std::experimental::filesystem;
#  elif __has_include(<boost/filesystem.hpp>)
#    include <boost/filesystem.hpp>
     namespace fs = boost::filesystem;
#  endif
#endif
#include "convert.hpp"

extern "C"
{
#include "wad.h"
};

#include <cstring>
#include <vector>
extern "C" 
{

#include <time.h>
#include <stdlib.h>

static zip_fileinfo* newzipinfo()
{
    const time_t tim = time(NULL);
    struct tm* curtime = localtime(&tim);
    
    if(!curtime) return NULL;
    
    tm_zip ztime;
    zip_fileinfo* zinfo;
    
    
    if(! (zinfo = (zip_fileinfo*)malloc(sizeof(zip_fileinfo))) ) return NULL;
    
    ztime.tm_sec = (curtime->tm_sec >= 60 ? 0 : curtime->tm_sec);
    ztime.tm_min = curtime->tm_min;
    ztime.tm_hour = curtime->tm_hour;
    ztime.tm_mday = curtime->tm_mday;
    ztime.tm_mon = curtime->tm_mon;
    ztime.tm_year = curtime->tm_year+1900u;
    
    zinfo->tmz_date = ztime;
    zinfo->dosDate = zinfo->internal_fa = zinfo->external_fa = 0;
    
    return zinfo;
}



};

const unsigned int numMapLumps = 10;
static const char* mapslumps[numMapLumps]
{
    "THINGS",
    "LINEDEFS",
    "SIDEDEFS",
    "VERTEXES",
    "SEGS",
    "SSECTORS",
    "NODES",
    "SECTORS",
    "REJECT",
    "BLOCKMAP"
};


//Convert function
//filename = the wad file
//savename = the name of the new archive file to be created where the lumps will be stored
//method = compression methods for the files inside the archive
//level = compression level for DEFLATE. ignored if the chosen compression method is other than deflate.
//omsg = ostream object where verbose output will be feed
bool convert2pk3(const char* path, const char* savename, int method, int level, std::ostream& omsg)
{
    using namespace std::literals;
    zipFile nzip;
    zip_fileinfo* zinfo;

    
    omsg << "Creating archive file " << savename << "..." << std::endl;
    if(! (nzip = zipOpen(savename,APPEND_STATUS_CREATE)) )
    {
        omsg << "could not create archive file " << savename << std::endl;
        return false;
    }
    
    if(! (zinfo = newzipinfo()) ) 
    {
        omsg << "could not retrieve a new zip info" << std::endl;
        return false;
    }
    
    if(fs::exists(path + "/Lua"s) && fs::is_directory(path + "/Lua"s))
    {
        zipOpenNewFileInZip(nzip,"Lua/",zinfo,NULL,0,NULL,0,NULL,method,level);
        zipCloseFileInZip(nzip);
        
        for (const auto & entry : fs::recursive_directory_iterator(path + "/Lua"s))
        {
            if(!fs::is_directory(entry.path().c_str())){
                FILE* fp = fopen(entry.path().c_str(),"rb");
                fseek(fp, 0 , SEEK_END);
                long fileSize = ftell(fp);
                fseek(fp, 0 , SEEK_SET);// needed for next read from beginning of file

                char *buffer;
                buffer = (char *)malloc(fileSize * sizeof(char)); // Enough memory for the file
                fread(buffer, fileSize, 1, fp); // Read in the entire file
                
                zipOpenNewFileInZip(nzip,("Lua/"s + entry.path().filename().c_str()).c_str(),zinfo,NULL,0,NULL,0,NULL,method,level);
                zipWriteInFileInZip(nzip,buffer,fileSize);
                zipCloseFileInZip(nzip);
                fclose(fp);
            }
        }
    }
    
    if(fs::exists(path + "/Sounds"s) && fs::is_directory(path + "/Sounds"s))
    {
        zipOpenNewFileInZip(nzip,"Sounds/",zinfo,NULL,0,NULL,0,NULL,method,level);
        zipCloseFileInZip(nzip);
        
        for (const auto & entry : fs::recursive_directory_iterator(path + "/Sounds"s))
        {
            if(!fs::is_directory(entry.path().c_str())){
                FILE* fp = fopen(entry.path().c_str(),"rb");
                fseek(fp, 0 , SEEK_END);
                long fileSize = ftell(fp);
                fseek(fp, 0 , SEEK_SET);// needed for next read from beginning of file

                char *buffer;
                buffer = (char *)malloc(fileSize * sizeof(char)); // Enough memory for the file
                fread(buffer, fileSize, 1, fp); // Read in the entire file
                
                zipOpenNewFileInZip(nzip,("Sounds/"s + entry.path().filename().c_str()).c_str(),zinfo,NULL,0,NULL,0,NULL,method,level);
                zipWriteInFileInZip(nzip,buffer,fileSize);
                zipCloseFileInZip(nzip);
                fclose(fp);
            }
        }
    }
    
    if(fs::exists(path + "/Sprites"s) && fs::is_directory(path + "/Sprites"s))
    {
        zipOpenNewFileInZip(nzip,"Sprites/",zinfo,NULL,0,NULL,0,NULL,method,level);
        zipCloseFileInZip(nzip);
        
        for (const auto & entry : fs::recursive_directory_iterator(path + "/Sprites"s))
        {
            if(!fs::is_directory(entry.path().c_str())){
                FILE* fp = fopen(entry.path().c_str(),"rb");
                fseek(fp, 0 , SEEK_END);
                long fileSize = ftell(fp);
                fseek(fp, 0 , SEEK_SET);// needed for next read from beginning of file

                char *buffer;
                buffer = (char *)malloc(fileSize * sizeof(char)); // Enough memory for the file
                fread(buffer, fileSize, 1, fp); // Read in the entire file
                
                zipOpenNewFileInZip(nzip,("Sprites/"s + entry.path().filename().c_str()).c_str(),zinfo,NULL,0,NULL,0,NULL,method,level);
                zipWriteInFileInZip(nzip,buffer,fileSize);
                zipCloseFileInZip(nzip);
                fclose(fp);
            }
        }
    }
    
    if(fs::exists(path + "/Sfx"s) && fs::is_directory(path + "/Sfx"s))
    {
        zipOpenNewFileInZip(nzip,"Sfx/",zinfo,NULL,0,NULL,0,NULL,method,level);
        zipCloseFileInZip(nzip);
        
        for (const auto & entry : fs::recursive_directory_iterator(path + "/Sfx"s))
        {
            if(!fs::is_directory(entry.path().c_str())){
                FILE* fp = fopen(entry.path().c_str(),"rb");
                fseek(fp, 0 , SEEK_END);
                long fileSize = ftell(fp);
                fseek(fp, 0 , SEEK_SET);// needed for next read from beginning of file

                char *buffer;
                buffer = (char *)malloc(fileSize * sizeof(char)); // Enough memory for the file
                fread(buffer, fileSize, 1, fp); // Read in the entire file
                
                zipOpenNewFileInZip(nzip,("Sfx/"s + entry.path().filename().c_str()).c_str(),zinfo,NULL,0,NULL,0,NULL,method,level);
                zipWriteInFileInZip(nzip,buffer,fileSize);
                zipCloseFileInZip(nzip);
                fclose(fp);
            }
        }
    }
        
    zipClose(nzip,NULL);
    
    omsg << "Done writing output file " << savename << std::endl;
    
    return true;
}
