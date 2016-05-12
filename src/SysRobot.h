#pragma once

#include "RobotData.h"
#include "ofxBox2d.h"
#include "CollisionObject.h"
#include "PMx.h"
#include "Timer.h"

class SysRobot : public CollisionObject {
	public:
		SysRobot() {
			isinit = false;
		}

		void init(int _id, ETeam _team);
		void setPos(Position _pos);
		void setState(EState _state);
		void setShot(bool _shot);
		void update();
		void draw();
		int getId();
		RobotData getData();

		// override CollisionObject
		virtual void collisionListner(CollisionObject *other);
	private:
		RobotData data;
		ofxBox2dCircle b2dCircle;
		PMx *PM;

		Timer *timer;

		void sufferDamage(int _damage);
		double HP;
		double energy; // 弾の発射に必要なエネルギー
		int thermo; // ダメージを受けると熱上昇し、体力が自然回復しなくなる
		int coolTime; // 1射撃後のフレーム数を記録

		int deadTime; // dead状態のフレーム数を記録
		int recoveyTime; // recovery状態のフレーム数を記録
		int itemTime; // itemを取得してからのフレーム数を記録

		bool isinit;
};
