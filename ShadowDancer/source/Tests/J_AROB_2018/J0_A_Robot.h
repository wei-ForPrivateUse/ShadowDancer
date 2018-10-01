/*
 * J0ARobot.h
 *
 *  Created on: Apr 20, 2018
 *      Author: wei
 */

#ifndef TESTS_J_AROB_2018_J0_A_ROBOT_H_
#define TESTS_J_AROB_2018_J0_A_ROBOT_H_

#include "Common/Component/MainBody.h"
#include "Common/Component/Motor.h"
#include "Common/Component/IRSenser.h"
#include "Common/Component/Controller/ANN.h"
#include "Common/Component/Camera/Omni/OmniId.h"
#include "Common/Component/Camera/Omni/OmniTag.h"
#include "Common/Object/Block.h"

#include "J0_AC_Gripper.h"
#include "J0_AC_Arbitrator.h"

///
class J0_A_Robot : public assa2d::Actor {
public:
	struct Configuration : public assa2d::Actor::Configuration {
		b2Vec2 Position;
		float32 Angle = 0.0f;

		int TrainingMode = 0;
	};

	J0_A_Robot(Configuration* conf);
	virtual ~J0_A_Robot() {}

	/// Get mode.
	int GetMode() const {
		if(m_a_s1->IsActive()) {
			return 1;
		} else if(m_a_s2->IsActive()) {
			return 2;
		} else if(m_a_s3->IsActive()) {
			return 3;
		}
		return 0;
	}

protected:
	///
	virtual void PreAct() override;

public:
	MainBody* m_mainbody;
	IRSenser* m_ir_senser[8];
	Camera<float>* m_omni_robot;
	Camera<float>* m_omni_resource;
	Camera<float>* m_omni_package;
	Motor* m_motor[2];
	J0_AC_Gripper* m_gripper;

	J1_AC_Arbitrator* m_arbi;

	ANN* m_a_s1;
	ANN* m_a_s2;
	ANN* m_a_s3;

private:
	int m_training_mode;
};

#endif /* TESTS_J_AROB_2018_J0_A_ROBOT_H_ */
