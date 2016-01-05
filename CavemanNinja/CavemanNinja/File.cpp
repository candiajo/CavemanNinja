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

bool File::GetAnimInfo(info_type& info, std::string& name, GenericData& data)
{
	bool result = false;
	string txt, discard;
	
	if (file.is_open())
	{
		getline(file, name, '_');	// get the name of the animation
		if (name != "endfile")			// there are no more lines
		{
			getline(file, txt, '_');		// "speed", "loop", "colliderframe", "collideranimation", "frame"
			getline(file, discard, ':');	// to discard "xxx.png:" o ":"
			if (txt == "speed")			
			{
				getline(file, txt, '\n');			// speed
				data.val5 = stof(txt);
				info = SPEED_INFO;
			}
			else if (txt == "loop")			// the line says if animation loops or not of the animation............
			{
				getline(file, txt, '\n');			// 0 = no loop,  1 = loop
				data.val1 = stoi(txt);
				info = LOOP_INFO;
			}
			else if (txt == "offset")			// the offset of that frame............
			{
				getline(file, txt, ':');		// x offset
				data.val1 = stoi(txt);
				getline(file, txt, '\n');		// y offset
				data.val2 = stoi(txt);
				info = OFFSET_INFO;
			}
			else if (txt == "frame") 
			{
				getline(file, txt, ':');		// x
				data.val1 = stoi(txt);
				getline(file, txt, ':');		// y
				data.val2 = stoi(txt);
				getline(file, txt, ':');		// w
				data.val3 = stoi(txt);
				getline(file, txt, '\n');		// h
				data.val4 = stoi(txt);

				info = FRAME_INFO;
			}
			else // it's a collider
			{
				if (txt == "colliderframe")	info = FRAME_COLLIDER;
				else if (txt == "collideranimation") info = ANIMATION_COLLIDER;

				getline(file, txt, ':');		// x
				data.val1 = stoi(txt);
				getline(file, txt, ':');		// y
				data.val2 = stoi(txt);
				getline(file, txt, ':');		// w
				data.val3 = stoi(txt);
				getline(file, txt, ':');		// h
				data.val4 = stoi(txt);
				getline(file, txt, '*');		// Collider type
				data.type = static_cast<collider_type>(stoi(txt));
				getline(file, discard, '\n');	// to discard coments
			}
			result = true;
		}
	}
	
	return result;
}

bool File::GetMatrixInfo(GenericData& data)
{
	bool result = false;
	string txt;

	if (file.is_open())
	{
		getline(file, txt, ':');	// row
		if (txt != "endfile")			// there are no more lines
		{
			data.val1 = stoi(txt);
			getline(file, txt, '-');		// column
			data.val2 = stoi(txt);
			getline(file, txt, '\n');		// value (yes / no)
			data.yes_no = (txt == "yes");
			result = true;
		}
		else result = false;
	}

	return result;
}