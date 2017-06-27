/*
 * Robot.h
 *
 *  Created on: Mar 2, 2017
 *      Author: wei
 */

#ifndef TESTS_SAMPLE_ACTOR_ROBOT_H_
#define TESTS_SAMPLE_ACTOR_ROBOT_H_

#include "Common/Component/MainBody.h"
#include "Common/Component/Motor.h"
#include "Common/Component/IRSenser.h"
#include "Common/Component/Controller/ANN.h"
#include "Common/Component/OmniCamera/Observer/IdObserver.h"
#include "Common/Component/OmniCamera/Observer/TagObserver.h"

/// A robot with eight ir sensors, one omnicamera, one main body, one ANN controller and two motors.
class Robot : public assa2d::Actor {
public:
	struct Configuration : public assa2d::Actor::Configuration {
		b2Vec2 Position;
		float32 Angle;
	};

	Robot(Configuration* conf);
	virtual ~Robot() { }

protected:
	/// Calculate nest direction.
	virtual void PreAct() override;

public:
	MainBody* m_mainbody;
	IRSenser* m_ir_senser[8];
	OmniCamera<float>* m_omnicamera;
	ANN* m_ann;
	Motor* m_motor[2];
};

#endif /* TESTS_SAMPLE_ACTOR_ROBOT_H_ */
