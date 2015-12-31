#ifndef __FILE_H__
#define __FILE_H__

#include <fstream>
#include <string>
#include "Globals.h"

class File
{
public:
	File(const char* path);
	~File();
	
	bool GetFrameInfo(std::string& name, Frame_info& frame_info);

private:
	bool Open();
	
	char* path;
	std::ifstream file;
};

#endif //__FILE_H__