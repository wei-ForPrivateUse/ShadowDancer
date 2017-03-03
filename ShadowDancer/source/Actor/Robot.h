/*
 * Robot.h
 *
 *  Created on: Mar 2, 2017
 *      Author: wei
 */

#ifndef OBJECT_ROBOT_H_
#define OBJECT_ROBOT_H_

#include "../Component/MainBody.h"
#include "../Component/Motor.h"
#include "../Component/IRSenser.h"
#include "../Component/ANN.h"

class Robot : public assa2d::Actor {
public:
	struct Configuration : public assa2d::Actor::Configuration {
		b2Vec2 Position;
		float32 Angle;
	};

	Robot(Configuration* conf);
	virtual ~Robot();

	MainBody* _M_mainbody;
	IRSenser* _M_ir_senser[8];
	ANN* _M_ann;
	Motor* _M_motor[2];
};

#endif /* OBJECT_ROBOT_H_ */
