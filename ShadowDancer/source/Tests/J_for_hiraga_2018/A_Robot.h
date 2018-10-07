/*
 * A_Robot.h
 *
 *  Created on: Oct 1, 2018
 *      Author: wei
 */

#ifndef TESTS_J_FOR_HIRAGA_2018_A_ROBOT_H_
#define TESTS_J_FOR_HIRAGA_2018_A_ROBOT_H_

#include "Common/Component/MainBody.h"
#include "Common/Component/Motor.h"
#include "Common/Component/IRSenser.h"
#include "Common/Component/Controller/ANN.h"
#include "Common/Component/Camera/Omni/OmniTag.h"
#include "Common/Object/Block.h"

class A_Robot : public assa2d::Actor {
public:
	struct Configuration : public assa2d::Actor::Configuration {
		b2Vec2 Position;
		float32 Angle = 0.0f;

		int IRSensor = 8;
		int OMNIRobot = 2;
		int OMNIResource = 2;

		float32 IRSensorRange = 3.0f;
		float32 OMNICameraRange = 15.0f;
	};

	A_Robot(Configuration* conf);
	virtual ~A_Robot() {}

protected:
	///
	virtual void PreAct() override;

public:
	MainBody* m_mainbody;
	IRSenser* m_ir_sensor[32];
	Camera<float>* m_omni_robot;
	Camera<float>* m_omni_resource;
	Motor* m_motor[2];

	ANN* m_ann;
};

#endif /* TESTS_J_FOR_HIRAGA_2018_A_ROBOT_H_ */
