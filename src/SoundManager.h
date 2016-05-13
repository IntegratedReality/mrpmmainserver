#pragma once

#include "ofMain.h"
#include "ESE.h"
#include <vector>

class SoundManager {
	public:
		void init();
		void update();
		void startBGM();
		void stopBGM();
		static void makeSE(ESE _SE);
	private:
		ofSoundPlayer bgm;
		static vector<ofSoundPlayer> SEs;
};
