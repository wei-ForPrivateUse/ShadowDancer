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
#include "Common/Component/Camera/Omni/OmniId.h"
#include "Common/Component/Camera/Omni/OmniTag.h"

struct Pred : public TagPredicate {
	Pred(Configuration* conf): TagPredicate(conf){}
	virtual bool FilterAdditional(assa2d::Node* node) override {
		if(node->GetId() < 2)
			return false;
		return true;
	}
};


class J1_A_Robot : public assa2d::Actor {
public:
	struct Configuration : public assa2d::Actor::Configuration {
		b2Vec2 Position;
		float32 Angle;

		int Mode;
	};

	J1_A_Robot(Configuration* conf);
	virtual ~J1_A_Robot() {}

protected:
	///
	virtual void PreAct() override { };

public:
	int m_mode;

	MainBody* m_mainbody;
	IRSenser* m_ir_senser[8];
	OmniId* m_omni_nest;
	OmniTag<TagPredicate>* m_omni_robot;
	OmniTag<TagPredicate>* m_omni_resource;
	OmniTag<TagPredicate>* m_omni_package;
	Motor* m_motor[2];

	ANN* m_a_arbi;

	ANN* m_a_s1;
	ANN* m_a_s2;
	ANN* m_a_s3;
};

#endif /* TESTS_J1_J1_A_ROBOT_H_ */
