#include "File.h"

using namespace std;

File::File(const char* path)
{
	file.open(path, std::fstream::in);
}

File::~File()
{
	file.close();
}

bool File::GetFrameInfo(string& name, T_frame_info& frame_info)
{
	bool result = false;
	string txt;
	
	if (file.is_open())
	{
		getline(file, name, '_');	// get the name of the animation
		if (name != "")				// there are no more frames
		{
			getline(file, txt, ':');	// to discard: "_01.png"
			getline(file, txt, ':');	// x
			frame_info.x = stoi(txt);
			getline(file, txt, ':');	// y
			frame_info.y = stoi(txt);
			getline(file, txt, ':');	// w
			frame_info.w = stoi(txt);
			getline(file, txt, ':');	// h
			frame_info.h = stoi(txt);
			getline(file, txt, '*');	// x_offset
			frame_info.x_offset = stoi(txt);
			getline(file, txt, '*');	// y_offset
			frame_info.y_offset = stoi(txt);
			getline(file, txt, '\n');	// end of line
			result = true;
		}
	}
	
	return result;
}