#include "SoundManager.h"

vector<ofSoundPlayer> SoundManager::SEs;

void SoundManager::init() {
  bgm.load("bgm.mp3");
  bgm.setMultiPlay(false);
  bgm.setLoop(false);
  
  SEs.emplace_back();
  SEs[0].load("shot.wav");
  SEs.emplace_back();
  SEs[1].load("damage.wav");
  
  for (auto& se : SEs) {
    se.setMultiPlay(true);
    se.setLoop(false);
  }
}

void SoundManager::update() {
  ofSoundUpdate();
}

void SoundManager::startBGM() {
  bgm.play();
}

void SoundManager::stopBGM() {
  bgm.stop();
}

void SoundManager::makeSE(ESE _SE) {
  SEs[(int)_SE].play();
}
