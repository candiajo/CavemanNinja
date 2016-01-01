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

// returns the info of the next line in the .ini file
// it can be frame info
// or animation speed info
bool File::GetAnimInfo(info_type& info, string& name, Frame_info& frame_info, float& speed, bool& loop)
{
	bool result = false;
	string txt;
	
	if (file.is_open())
	{
		getline(file, name, '_');	// get the name of the animation
		if (name != "end")			// there are no more frames
		{
			getline(file, txt, ':');	// "speed", "loop" or text to discard: "_01.png"
			if (txt == "speed")			// the line has the speed of the animation............
			{
				getline(file, txt, '*');			// speed
				speed = stof(txt);
				getline(file, txt, '\n');			// end of line
				info = SPEED_INFO;
			}
			else if (txt == "loopinfo")			// the line says if animation loops or not of the animation............
			{
				getline(file, txt, '*');			// "loop" or "noloop"
				loop = (txt == "loop");
				getline(file, txt, '\n');			// end of line
				info = LOOP_INFO;
			}
			else						// the line has frame info.............................
			{
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
				info = FRAME_INFO;
			}
			result = true;
		}
	}
	
	return result;
}