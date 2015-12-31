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

bool File::GetFrameInfo(string& name, Frame_info& frame_info)
{
	bool result = false;
	string txt;
	
	if (file.is_open())
	{
		getline(file, name, '_');	// get the name of the animation
		if (name != "end")			// there are no more frames
		{
			getline(file, txt, ':');	// to discard: "_01.png"
			getline(file, txt, ':');	// x
			frame_info.section.x = stoi(txt);
			getline(file, txt, ':');	// y
			frame_info.section.y = stoi(txt);
			getline(file, txt, ':');	// w
			frame_info.section.w = stoi(txt);
			getline(file, txt, ':');	// h
			frame_info.section.h = stoi(txt);
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