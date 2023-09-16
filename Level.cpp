
#pragma once
struct Level {
	std::string name;
	bool playable;
	bool trainingArea;

	void readMemory() {
		name = mem::ReadString(off::REGION + off::LEVEL);
		playable = !name.empty() && name != "mp_lobby";
		trainingArea = name == "mp_rr_canyonlands_staging_mu1";
	}
};
