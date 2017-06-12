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
		mbc.Position = conf->Position;
		mbc.Angle = conf->Angle;
		mbc.CircleShape.m_radius = 0.5;
		mbc.Id = 300;
		_M_mainbody = AddComponent<MainBody>(&mbc);
	}
	SetMainComponent(_M_mainbody);

	{
		Motor::Configuration mc;
		mc.Priority = 2;
		mc.PolygonShape.SetAsBox(0.25f, 0.1f);
		mc.Anchor.Set(0.0f, 0.0f);
		mc.Position.Set(0.0f, 0.45f);
		mc.Id = 50;
		_M_motor[0] = AddComponent<Motor>(&mc);

		mc.Id = 51;
		mc.Position.Set(0.0f, -0.45f);
		_M_motor[1] = AddComponent<Motor>(&mc);
	}

	{
		IRSenser::Configuration irc;
		irc.Range = 3.0f;
		irc.Priority = 0;
		irc.Position.Set(0.0f, 0.0f);

		for(int i = 0; i < 36; i++) {
			irc.Id = i;
			irc.Angle = M_PI / 18.0f * i;
			_M_ir_senser[i] = AddComponent<IRSenser>(&irc);
		}
	}

	{
		ANN::Configuration ac;
		ac.Id = 1000;
		for(int i = 0; i < 36; i++) {
			ac.InputIndex.push_back(i);
		}
		ac.OutputIndex = {50, 51};
		ac.Priority = 1;
		_M_ann = AddComponent<ANN>(&ac);
	}
}
