/*
 * Robot.cpp
 *
 *  Created on: Mar 2, 2017
 *      Author: wei
 */

#include "Robot.h"

Robot::Robot(Configuration* conf) : assa2d::Actor(conf) {
	MainBody::Configuration mbc;
	mbc.CircleShape.m_radius = 0.5;
	mbc.Id = 99;
	mb = AddComponent<MainBody>(&mbc);

	SetMainComponent(mb);

	Motor::Configuration mc;
	mc.PolygonShape.SetAsBox(0.25f, 0.1f);
	mc.Anchor.Set(0.0f, 0.0f);
	mc.Position.Set(0.0f, 0.45f);
	mc.Id = 0;
	m1 = AddComponent<Motor>(&mc);

	mc.Id = 1;
	mc.Position.Set(0.0f, -0.45f);
	m2 = AddComponent<Motor>(&mc);

	GetDataPool().Set<float>(0, 1);
	GetDataPool().Set<float>(0, 0);

}

Robot::~Robot() {
	// TODO Auto-generated destructor stub
}

