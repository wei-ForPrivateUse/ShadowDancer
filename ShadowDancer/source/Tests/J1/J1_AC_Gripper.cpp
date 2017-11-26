/*
 * J1_AC_Gripper.cpp
 *
 *  Created on: Nov 14, 2017
 *      Author: wei
 */

#include "J1_AC_Gripper.h"

J1_AC_Gripper::J1_AC_Gripper(Configuration* conf) : assa2d::Component(conf) {
	b2BodyDef bd;
	bd.userData = static_cast<assa2d::Node*>(this);
	bd.type = b2_dynamicBody;
	bd.position = static_cast<assa2d::Component*>(static_cast<assa2d::Actor*>(GetActor())->GetMainComponent())->GetBody()->GetWorldPoint(b2Vec2(0.45, 0));
	bd.angle = static_cast<assa2d::Component*>(static_cast<assa2d::Actor*>(GetActor())->GetMainComponent())->GetBody()->GetAngle();

	b2Body* body = GetWorld() -> CreateBody(&bd);
	SetBody(body);

	b2FixtureDef fd;
	b2PolygonShape s;
	s.SetAsBox(0.1, 0.25);
	fd.shape = &s;
	fd.friction = 0.1f;
	fd.density = 1.0f;
	fd.restitution = 0.3f;

	GetBody() -> CreateFixture(&fd);

	b2RevoluteJointDef rjd;
	rjd.Initialize(GetBody(), static_cast<assa2d::Component*>(static_cast<assa2d::Actor*>(GetActor())->GetMainComponent())->GetBody(), GetBody()->GetWorldPoint(b2Vec2(0, 0)));
	rjd.enableLimit = true;
	rjd.lowerAngle = 0.0f;
	rjd.upperAngle = 0.0f;

	GetWorld() -> CreateJoint(&rjd);

	m_target_tag = conf->TargetTag;
	m_target_mask = conf->TargetMask;

	m_loaded = false;
}

J1_AC_Gripper::~J1_AC_Gripper() {
	GetWorld() -> DestroyBody(GetBody());
}

