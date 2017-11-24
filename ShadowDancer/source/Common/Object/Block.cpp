/*
 * Block.cpp
 *
 *  Created on: Mar 3, 2017
 *      Author: wei
 */

#include "Block.h"

Block::Block(Configuration* conf) : assa2d::Object(conf) {
	b2BodyDef bd;
	bd.userData = static_cast<assa2d::Node*>(this);
	if(conf->StaticBody) {
		bd.type = b2_staticBody;
	} else {
		bd.type = b2_dynamicBody;
	}
	bd.position = conf->Position;
	bd.angle = conf->Angle;

	b2Body* body = GetWorld() -> CreateBody(&bd);
	SetBody(body);

	b2FixtureDef fd;
	if(conf->ShapeType == assa2d::ShapeType::Circle) {
		fd.shape = &conf->CircleShape;
	} else if (conf->ShapeType == assa2d::ShapeType::Polygon) {
		fd.shape = &conf->PolygonShape;
	}
	fd.density = conf->Density;
	fd.restitution = conf->Restitution;
	fd.friction = conf->Friction;

	GetBody() -> CreateFixture(&fd);

	m_mark = conf->Mark;

	m_ground_friction_joint = nullptr;
	SetGroundFriction(conf->GroundFriction);
}

Block::~Block() {
	GetWorld() -> DestroyBody(GetBody());
}

void Block::SetGroundFriction(bool flag) {
	if(m_ground_friction_joint && !flag) {
		GetWorld() -> DestroyJoint(m_ground_friction_joint);

		m_ground_friction_joint = nullptr;
	} else if(!m_ground_friction_joint && flag) {
		assa2d::SceneMgr* scenemgr = static_cast<assa2d::SceneMgr*>(GetSceneMgr());

		float32 radius = b2Sqrt(2.0f * GetBody()->GetInertia() / GetBody()->GetMass());

		b2FrictionJointDef fjd;
		fjd.localAnchorA = GetBody()->GetLocalCenter();
		fjd.localAnchorB.SetZero();
		fjd.bodyA = GetBody();
		fjd.bodyB = scenemgr -> GetGround();
		fjd.collideConnected = true;
		fjd.maxForce = GetBody()->GetMass() * 10.0f;
		fjd.maxTorque = GetBody()->GetMass() * radius * 10.0f;

		m_ground_friction_joint = GetWorld() -> CreateJoint(&fjd);
	}
}
