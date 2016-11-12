#pragma once

#include "ofMain.h"
#include "Position.h"
#include "EFX.h"
#include "Const.h"
#include "PMx.h"

// このクラスで色々なエフェクトを実装する
// 今後各エフェクト毎に派生クラスを作る構造にするかも

// エフェクトを追加したい時はFXManager.h内の列挙型のEFXに追記してください
// 各エフェクトの処理はEFXで分岐して，全てここに書いてください
// 用済みになったらdeleteFlagをtrueにしてください．インスタンスが勝手に破壊されます

class FX {
public:
  void init(Position _pos, EFX _FXType);
  void update();
  void draw();
  bool getDeleteFlag();
private:
  Position pos;
  EFX FXType;
  bool deleteFlag = false;
  double size;
  double maxSize;
  
  PMx *pmx;
};
