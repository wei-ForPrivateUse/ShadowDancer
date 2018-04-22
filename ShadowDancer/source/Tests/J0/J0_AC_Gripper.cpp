/*
 * J0ACGripper.cpp
 *
 *  Created on: Apr 19, 2018
 *      Author: wei
 */

#include "J0_AC_Gripper.h"

J0_AC_Gripper::J0_AC_Gripper(Configuration* conf) : assa2d::Component(conf) {
	b2BodyDef bd;
	bd.userData = static_cast<assa2d::Node*>(this);
	bd.type = b2_dynamicBody;
	bd.position = static_cast<assa2d::Component*>(static_cast<assa2d::Actor*>(GetActor())->GetMainComponent())->GetBody()->GetWorldPoint(b2Vec2(0.35f, 0.0f));
	bd.angle = static_cast<assa2d::Component*>(static_cast<assa2d::Actor*>(GetActor())->GetMainComponent())->GetBody()->GetAngle();

	b2Body* body = GetWorld() -> CreateBody(&bd);
	SetBody(body);

	b2FixtureDef fd;
	b2PolygonShape s;
	b2Vec2 v[3];
	v[0].Set(0.2f, 0.0f);
	v[1].Set(-0.3f, 0.2f);
	v[2].Set(-0.3f, -0.2f);
	s.Set(v, 3);
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

	m_gripping_resource = nullptr;
	m_gripping_joint = nullptr;

	m_touching_resource = nullptr;
}

J0_AC_Gripper::~J0_AC_Gripper() {
	GetWorld() -> DestroyBody(GetBody());
}

void J0_AC_Gripper::PreSolve(Node* node, b2Contact* contact, const b2Manifold* oldManifold) {
	if(node->GetTag()==m_target_tag && node->GetType()==assa2d::Node_Type::Object) {
		if(!node->CheckFlag(CATCHED_FLAG)) {
			m_touching_resource = static_cast<Block*>(node);
		}
	}
}

void J0_AC_Gripper::Grip() {
	m_touching_resource -> AddFlag(CATCHED_FLAG);
	m_touching_resource -> SetGroundFriction(false, 5.0f, 5.0f);

	b2RevoluteJointDef rjd;
	rjd.Initialize(GetBody(), m_touching_resource->GetBody(), GetBody()->GetWorldPoint(b2Vec2(0, 0)));
	rjd.enableLimit = true;
	rjd.lowerAngle = 0.0f;
	rjd.upperAngle = 0.0f;

	m_gripping_resource = m_touching_resource;
	m_gripping_joint = GetWorld() -> CreateJoint(&rjd);
}

void J0_AC_Gripper::Drop() {
	m_gripping_resource -> RemoveFlag(CATCHED_FLAG);
	m_gripping_resource -> SetGroundFriction(true, 5.0f, 5.0f);

	GetWorld()->DestroyJoint(m_gripping_joint);

	m_gripping_resource = nullptr;
	m_gripping_joint = nullptr;
}

void J0_AC_Gripper::Act() {
	if(m_touching_resource && !m_gripping_resource) {
		 if(GetSceneMgr()->CountNodeByPointer(m_touching_resource)>0) {
			 if(!m_touching_resource->CheckFlag(CATCHED_FLAG)) {
				 Grip();
			 }
		 }
	}
}

void J0_AC_Gripper::Act_Anyway() {
	if(m_gripping_resource) {
		 if(GetSceneMgr()->CountNodeByPointer(m_gripping_resource) == 0) {
				m_gripping_resource = nullptr;
				m_gripping_joint = nullptr;
		 } else {
			 if(!IsActive()) {
				 Drop();
			 }
		 }
	}
	m_touching_resource = nullptr;
}
