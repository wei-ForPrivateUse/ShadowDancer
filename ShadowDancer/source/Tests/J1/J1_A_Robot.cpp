/*
 * J1_A_Robot.cpp
 *
 *  Created on: Oct 4, 2017
 *      Author: wei
 */

#include "J1_A_Robot.h"

J1_A_Robot::J1_A_Robot(Configuration* conf) : assa2d::Actor(conf) {
	// mainbody
	{
		MainBody::Configuration mbc;

		mbc.Id = 0;
		mbc.Position = conf->Position;
		mbc.Angle = conf->Angle;
		mbc.CircleShape.m_radius = 0.5;
		m_mainbody = AddComponent<MainBody>(&mbc);
	}
	SetMainComponent(m_mainbody);

	// motors
	{
		Motor::Configuration mc;

		mc.Priority = 4;
		mc.ForwardAttributes = {16.0f, 9.0f, 100.0f};
		mc.BackwardAttributes = {8.0f, 3.0f, 50.0f};
		mc.PolygonShape.SetAsBox(0.25f, 0.1f);
		mc.Anchor.Set(0.0f, 0.0f);

		mc.Id = 50;
		mc.TargetSpeedIndex = 50;
		mc.PowerRequestIndex = 60;
		mc.Position.Set(0.0f, 0.45f);
		m_motor[0] = AddComponent<Motor>(&mc);

		mc.Id = 51;
		mc.TargetSpeedIndex = 51;
		mc.PowerRequestIndex = 61;
		mc.Position.Set(0.0f, -0.45f);
		m_motor[1] = AddComponent<Motor>(&mc);
	}

	// ir sensors
	{
		IRSenser::Configuration irc;

		irc.Priority = 0;
		irc.Range = 3.0f;
		irc.Position.Set(0.0f, 0.0f);

	    irc.Angle = M_PI / 10.0f;
	    irc.Id = 10;
	    irc.OutputIndex = 0;
	    m_ir_senser[0] = AddComponent<IRSenser>(&irc);
	    irc.Angle = M_PI / 10.0f * 3.0f;
	    irc.Id = 11;
	    irc.OutputIndex = 1;
	    m_ir_senser[1] = AddComponent<IRSenser>(&irc);
	    irc.Angle = M_PI_2;
	    irc.Id = 12;
	    irc.OutputIndex = 2;
	    m_ir_senser[2] = AddComponent<IRSenser>(&irc);
	    irc.Angle = M_PI / 8.0f * 7.0f;
	    irc.Id = 13;
	    irc.OutputIndex = 3;
	    m_ir_senser[3] = AddComponent<IRSenser>(&irc);
	    irc.Angle = - M_PI / 8.0f * 7.0f;
	    irc.Id = 14;
	    irc.OutputIndex = 4;
	    m_ir_senser[4] = AddComponent<IRSenser>(&irc);
	    irc.Angle = - M_PI_2;
	    irc.Id = 15;
	    irc.OutputIndex = 5;
	    m_ir_senser[5] = AddComponent<IRSenser>(&irc);
	    irc.Angle = - M_PI / 10.0f * 3;
	    irc.Id = 16;
	    irc.OutputIndex = 6;
	    m_ir_senser[6] = AddComponent<IRSenser>(&irc);
	    irc.Angle = - M_PI / 10.0f;
	    irc.Id = 17;
	    irc.OutputIndex = 7;
	    m_ir_senser[7] = AddComponent<IRSenser>(&irc);
	}

	// omni-camera
	{
		OmniCamera<float>::Configuration occ;

		occ.Priority = 0;
		occ.Id = 20;
		m_omnicamera = AddComponent<OmniCamera<float>>(&occ);

		TagObserver::Configuration toc;
		toc.Range = 20;

		toc.OutputCount = 3;
		toc.TargetTag = MAKE_TAG('r', 'o', 'b', 'o');
		toc.StartIndex = 10;
		m_omnicamera -> AddObserver<TagObserver>(&toc);

		toc.OutputCount = 1;
		toc.TargetTag = MAKE_TAG('r', 'e', 's', 'o');
		toc.StartIndex = 20;
		m_omnicamera -> AddObserver<TagObserver>(&toc);

		toc.OutputCount = 1;
		toc.TargetTag = MAKE_TAG('e', 'n', 'e', 'm');
		toc.StartIndex = 25;
		m_omnicamera -> AddObserver<TagObserver>(&toc);
	}

	/////TODO
	// anns
	{
		m_a_oa = nullptr;

		m_a_value = nullptr;

		m_a_avoid = nullptr;
		m_a_recharge = nullptr;

		m_a_s1 = nullptr;
		m_a_s2 = nullptr;
		m_a_s3 = nullptr;
	}

	// initial mode
	m_mode = conf -> Mode;
}


