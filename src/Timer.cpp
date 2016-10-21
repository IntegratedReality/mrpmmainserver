#include "Timer.h"

void Timer::init() {
  prevtime = 0;
  time = 0;
  start = std::chrono::system_clock::now();
}

void Timer::update() {
  now = std::chrono::system_clock::now();
  auto dur = now - start;
  auto msec = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
  prevtime = time;
  time = (int)msec;
}

int Timer::getTime() {
  return time;
}

int Timer::getDiff() {
  return time - prevtime;
}
