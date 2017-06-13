/*
 * Robot.h
 *
 *  Created on: Mar 2, 2017
 *      Author: wei
 */

#ifndef TESTS_SAMPLE_ACTOR_ROBOT_H_
#define TESTS_SAMPLE_ACTOR_ROBOT_H_

#include "../Component/MainBody.h"
#include "../Component/Motor.h"
#include "../Component/IRSenser.h"
#include "../Component/Controller/ANN.h"

class Robot : public assa2d::Actor {
public:
	struct Configuration : public assa2d::Actor::Configuration {
		b2Vec2 Position;
		float32 Angle;
	};

	Robot(Configuration* conf);
	virtual ~Robot() { }

	MainBody* _M_mainbody;
	IRSenser* _M_ir_senser[36];
	ANN* _M_ann;
	Motor* _M_motor[2];
};

#endif /* TESTS_SAMPLE_ACTOR_ROBOT_H_ */
