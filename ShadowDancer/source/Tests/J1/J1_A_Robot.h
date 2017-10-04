/*
 * J1_A_Robot.h
 *
 *  Created on: Oct 4, 2017
 *      Author: wei
 */

#ifndef TESTS_J1_J1_A_ROBOT_H_
#define TESTS_J1_J1_A_ROBOT_H_

#include "Common/Component/MainBody.h"
#include "Common/Component/Motor.h"
#include "Common/Component/IRSenser.h"
#include "Common/Component/Controller/ANN.h"
#include "Common/Component/OmniCamera/Observer/IdObserver.h"
#include "Common/Component/OmniCamera/Observer/TagObserver.h"

//
class J1_A_Robot : public assa2d::Actor {
public:
	struct Configuration : public assa2d::Actor::Configuration {
		b2Vec2 Position;
		float32 Angle;
	};

	J1_A_Robot(Configuration* conf);
	virtual ~J1_A_Robot() {}

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

#endif /* TESTS_J1_J1_A_ROBOT_H_ */
