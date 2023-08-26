
#include "Memory.cpp"
#include "Offsets.cpp"

struct Level {
	std::string name;
	bool playable;
	bool trainingArea;

	void update()
	{
		name = mem::ReadString(off::REGION + off::LEVEL);
		playable = !name.empty() && name != "mp_lobby";
		trainingArea = name == "mp_rr_canyonlands_staging_mu1";
	}
};
