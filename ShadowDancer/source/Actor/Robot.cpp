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
		mbc.Id = 30;
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

		irc.Id = 0;
		irc.Angle = M_PI / 10.0f;
		_M_ir_senser[0] = AddComponent<IRSenser>(&irc);

		irc.Id = 1;
		irc.Angle = M_PI / 10.0f * 3.0f;
		_M_ir_senser[1] = AddComponent<IRSenser>(&irc);

		irc.Id = 2;
		irc.Angle = M_PI_2;
		_M_ir_senser[2] = AddComponent<IRSenser>(&irc);

		irc.Id = 3;
		irc.Angle = M_PI / 8.0 * 7.0f;
		_M_ir_senser[3] = AddComponent<IRSenser>(&irc);

		irc.Id = 4;
		irc.Angle = - M_PI / 8.0 * 7.0f;
		_M_ir_senser[4] = AddComponent<IRSenser>(&irc);

		irc.Id = 5;
		irc.Angle = - M_PI_2;
		_M_ir_senser[5] = AddComponent<IRSenser>(&irc);

		irc.Id = 6;
		irc.Angle = - M_PI / 10.0f * 3.0f;
		_M_ir_senser[6] = AddComponent<IRSenser>(&irc);

		irc.Id = 7;
		irc.Angle = - M_PI / 10.0f;
		_M_ir_senser[7] = AddComponent<IRSenser>(&irc);
	}

	{
		ANN::Configuration ac;
		ac.Id = 1000;
		ac.InputIndex = {0, 1, 2, 3, 4, 5, 6, 7};
		ac.OutputIndex = {50, 51};
		ac.Priority = 1;
		_M_ann = AddComponent<ANN>(&ac);
	}
}

Robot::~Robot() {
	// TODO Auto-generated destructor stub
}

