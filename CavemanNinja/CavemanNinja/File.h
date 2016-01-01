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
	
	bool GetAnimInfo(info_type& info, std::string& name, Frame_info& frame_info, float& speed, bool& loop);

private:
	bool Open();
	
	char* path;
	std::ifstream file;
};

#endif //__FILE_H__