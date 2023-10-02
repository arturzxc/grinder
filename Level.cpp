#pragma once
struct Level {
	std::string name;
	bool playable;
	bool trainingArea;

	void readFromMemory() {
		name = mem::ReadString(OFF_REGION + OFF_LEVEL, 1024);
		playable = !name.empty() && name != "mp_lobby";
		trainingArea = name == "mp_rr_canyonlands_staging_mu1";
	}
};
