/*
 * A_Robot.cpp
 *
 *  Created on: Oct 1, 2018
 *      Author: wei
 */

#include "A_Robot.h"

A_Robot::A_Robot(Configuration* conf) : assa2d::Actor(conf) {
	// mainbody
	{
		MainBody::Configuration mbc;

		mbc.Id = 10000;
		mbc.Friction = 0.1f;
		mbc.Position = conf->Position;
		mbc.Angle = conf->Angle;
		mbc.CircleShape.m_radius = 0.5;
		m_mainbody = AddComponent<MainBody>(&mbc);
	}
	SetMainComponent(m_mainbody);

	// motors
	{
		Motor::Configuration mc;

		mc.Priority = 2;
		mc.ForwardAttributes = {15.0f, 8.0f, 60.0f};
		mc.BackwardAttributes = {8.0f, 1.0f, 5.0f};
		mc.PolygonShape.SetAsBox(0.25f, 0.1f);
		mc.Anchor.Set(0.0f, 0.0f);

		mc.Id = 150;
		mc.TargetSpeedIndex = 150;
		mc.PowerRequestIndex = 160;
		mc.Position.Set(0.0f, 0.45f);
		m_motor[0] = AddComponent<Motor>(&mc);

		mc.Id = 151;
		mc.TargetSpeedIndex = 151;
		mc.PowerRequestIndex = 161;
		mc.Position.Set(0.0f, -0.45f);
		m_motor[1] = AddComponent<Motor>(&mc);
	}

	// ir sensors
	{
		IRSenser::Configuration irc;

		irc.Priority = 0;
		irc.Range = conf->IRSensorRange;
		irc.Position.Set(0.0f, 0.0f);

		for(int i = 0; i < conf->IRSensor; i++) {
			irc.Angle = M_PI * 2.0f / conf->IRSensor * i + M_PI / conf->IRSensor;
			irc.Id = i;
			irc.OutputIndex = i;

			m_ir_sensor[i] = AddComponent<IRSenser>(&irc);
		}
	}

	// omni-camera
	{
		OmniTag<TagPredicate>::Configuration otc_rp;
		otc_rp.Id = 50;
		otc_rp.Priority = 0;
		otc_rp.Range = conf->OMNICameraRange;
		otc_rp.OutputCount = conf->OMNIRobot;
		otc_rp.OutputIndexInterval.first = 50;
		otc_rp.OutputIndexInterval.second = 50+conf->OMNIRobot*3-1;
		otc_rp.TargetTag = MAKE_TAG('r', 'o', 'b', 'o');
		otc_rp.Predicate.Datum = this;
		otc_rp.Predicate.DatumExemption = true;
		m_omni_robot = AddComponent<OmniTag<TagPredicate>>(&otc_rp);

		OmniTag<TagPredicate>::Configuration otc_rep;
		otc_rep.Id = 100;
		otc_rep.Priority = 0;
		otc_rep.Range = conf->OMNICameraRange;
		otc_rep.OutputCount = conf->OMNIResource;
		otc_rep.OutputIndexInterval.first = 100;
		otc_rep.OutputIndexInterval.second = 100+conf->OMNIResource*3-1;
		otc_rep.TargetTag = MAKE_TAG('r', 'e', 's', 'o');
		otc_rep.Predicate.Datum = this;
		otc_rep.Predicate.DatumExemption = true;
		m_omni_resource = AddComponent<OmniTag<TagPredicate>>(&otc_rep);
	}

	// anns
	{
		ANN::Configuration ac;
		ac.Priority = 1;
		ac.Id = 1000;
		for(int i = 0; i < conf->IRSensor; i++) {
			ac.InputIndex.push_back(i);
		}
		for(int i = 50; i < 50+conf->OMNIRobot*3; i++) {
			ac.InputIndex.push_back(i);
		}
		for(int i = 100; i < 100+conf->OMNIResource*3; i++) {
			ac.InputIndex.push_back(i);
		}
		ac.InputIndex.push_back(120);
		ac.InputIndex.push_back(121);

		ac.OutputIndex = {150, 151};
		m_ann = AddComponent<ANN>(&ac);
	}

	// Set extra parameters for motors.
	GetDataPool().Resize(256);
	GetDataPool().Set<float>(160, 100.0f);
	GetDataPool().Set<float>(161, 100.0f);
}

void A_Robot::PreAct() {
	float32 c_nest = 1.0f;
	float32 s_nest = 0.0f;

	// Angle of the nest_resource & nest_package.
	b2Vec2 const& pos = this->GetMainComponent()->GetPosition();
	if(pos == b2Vec2(0.0f, 0.0f)) { }
	else {
		b2Vec2 const& l_pos = this->GetMainComponent()->GetBody()->GetLocalVector(b2Vec2(0.0f, 0.0f) - pos);
		c_nest = l_pos.x / b2Sqrt(l_pos.x*l_pos.x + l_pos.y*l_pos.y);
		s_nest = l_pos.y / b2Sqrt(l_pos.x*l_pos.x + l_pos.y*l_pos.y);
	}

	// Set outputs.
	GetDataPool().Set<float>(120, c_nest);
	GetDataPool().Set<float>(121, s_nest);
}

