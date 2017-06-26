/*
 * Robot.cpp
 *
 *  Created on: Mar 2, 2017
 *      Author: wei
 */

#include "Robot.h"

Robot::Robot(Configuration* conf) : assa2d::Actor(conf) {
	{
		MainBody::Configuration mbc;
		mbc.Id = 300;
		mbc.Position = conf->Position;
		mbc.Angle = conf->Angle;
		mbc.CircleShape.m_radius = 0.5;
		m_mainbody = AddComponent<MainBody>(&mbc);
	}
	SetMainComponent(m_mainbody);

	{
		Motor::Configuration mc;
		mc.Id = 50;
		mc.Priority = 2;
		mc.TargetSpeedIndex = 50;
		mc.PowerRequestIndex = 60;
		mc.PolygonShape.SetAsBox(0.25f, 0.1f);
		mc.Anchor.Set(0.0f, 0.0f);
		mc.Position.Set(0.0f, 0.45f);
		m_motor[0] = AddComponent<Motor>(&mc);

		mc.Id = 51;
		mc.TargetSpeedIndex = 51;
		mc.PowerRequestIndex = 61;
		mc.Position.Set(0.0f, -0.45f);
		m_motor[1] = AddComponent<Motor>(&mc);
	}

	{
		IRSenser::Configuration irc;
		irc.Range = 3.0f;
		irc.Priority = 0;
		irc.Position.Set(0.0f, 0.0f);

	    irc.Angle = M_PI / 10.0f;
	    irc.Id = 0;
	    irc.OutputIndex = 0;
	    m_ir_senser[0] = AddComponent<IRSenser>(&irc);
	    irc.Angle = M_PI / 10.0f * 3.0f;
	    irc.Id = 1;
	    irc.OutputIndex = 1;
	    m_ir_senser[1] = AddComponent<IRSenser>(&irc);
	    irc.Angle = M_PI_2;
	    irc.Id = 2;
	    irc.OutputIndex = 2;
	    m_ir_senser[2] = AddComponent<IRSenser>(&irc);
	    irc.Angle = M_PI / 8.0f * 7.0f;
	    irc.Id = 3;
	    irc.OutputIndex = 3;
	    m_ir_senser[3] = AddComponent<IRSenser>(&irc);
	    irc.Angle = - M_PI / 8.0f * 7.0f;
	    irc.Id = 4;
	    irc.OutputIndex = 4;
	    m_ir_senser[4] = AddComponent<IRSenser>(&irc);
	    irc.Angle = - M_PI_2;
	    irc.Id = 5;
	    irc.OutputIndex = 5;
	    m_ir_senser[5] = AddComponent<IRSenser>(&irc);
	    irc.Angle = - M_PI / 10.0f * 3;
	    irc.Id = 6;
	    irc.OutputIndex = 6;
	    m_ir_senser[6] = AddComponent<IRSenser>(&irc);
	    irc.Angle = - M_PI / 10.0f;
	    irc.Id = 7;
	    irc.OutputIndex = 7;
	    m_ir_senser[7] = AddComponent<IRSenser>(&irc);
	}

	{
		OmniCamera<float>::Configuration occ;
		occ.Id = 10;
		occ.Priority = 0;
		m_omnicamera = AddComponent<OmniCamera<float>>(&occ);

		TagObserver::Configuration toc;
		toc.OutputCount = 2;
		toc.TargetTag = MAKE_TAG('r', 'o', 'b', 'o');
		toc.Range = 15;
		toc.StartIndex = 10;
		m_omnicamera -> AddObserver<TagObserver>(&toc);

		toc.TargetTag = MAKE_TAG('f', 'o', 'o', 'd');
		toc.StartIndex = 20;
		m_omnicamera -> AddObserver<TagObserver>(&toc);

		toc.TargetTag = MAKE_TAG('o', 'b', 's', 't');
		toc.StartIndex = 30;
		m_omnicamera -> AddObserver<TagObserver>(&toc);

		IdObserver::Configuration ioc;
		ioc.Range = 15;
		ioc.ReportAngle = true;
		ioc.ReportDistance = false;
		ioc.TargetId = {9999};
		ioc.StartIndex = 40;
		//m_omnicamera -> AddObserver<IdObserver>(&ioc);
	}

	{
		ANN::Configuration ac;
		ac.Id = 1000;
		for(int i = 0; i < 8; i++) {
			ac.InputIndex.push_back(i);
		}
		for(int i = 10; i < 16; i++) {
			ac.InputIndex.push_back(i);
		}
		for(int i = 20; i < 26; i++) {
			ac.InputIndex.push_back(i);
		}
		for(int i = 30; i < 36; i++) {
			ac.InputIndex.push_back(i);
		}
		for(int i = 40; i < 42; i++) {
			ac.InputIndex.push_back(i);
		}

		ac.OutputIndex = {50, 51};
		ac.Priority = 1;
		m_ann = AddComponent<ANN>(&ac);
	}

	GetDataPool().Set<float>(60, 100.0f);
	GetDataPool().Set<float>(61, 100.0f);
}
