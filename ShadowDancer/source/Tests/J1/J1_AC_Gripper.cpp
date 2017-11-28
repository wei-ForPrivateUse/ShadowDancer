/*
 * J1_AC_Gripper.cpp
 *
 *  Created on: Nov 14, 2017
 *      Author: wei
 */

#include "J1_AC_Gripper.h"
#include "J1_A_Robot.h"

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
	s.SetAsBox(0.1, 0.2);
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
	m_target_status_mask = conf->TargetStatusMask;
	m_required_mode = conf->RequiredMode;

	m_output_index = conf->OutputIndex;

	m_null_id = conf->NullId;

	m_gripping_resource_id = m_null_id;
	m_gripping_joint = nullptr;
	m_touching_resource_id = m_null_id;
}

J1_AC_Gripper::~J1_AC_Gripper() {
	GetWorld() -> DestroyBody(GetBody());
}

void J1_AC_Gripper::PreSolve(Node* node, b2Contact* contact, const b2Manifold* oldManifold) {
	if(node->GetTag()==m_target_tag && node->GetType()==assa2d::Node_Type::Object) {
		auto resource = static_cast<Block*>(node);
		unsigned int mask = resource->GetMask() & m_target_status_mask;
		if(mask != m_target_status_mask) {
			m_touching_resource_id = resource->GetId();
		}
	}
}

void J1_AC_Gripper::Grip() {
	auto resource = static_cast<Block*>(GetSceneMgr()->GetNodeById(m_touching_resource_id));
	unsigned int mask = resource->GetMask() | m_target_status_mask;
	resource -> SetMask(mask);
	resource -> SetGroundFriction(false, 5.0f, 5.0f);

	b2RevoluteJointDef rjd;
	rjd.Initialize(GetBody(), resource->GetBody(), GetBody()->GetWorldPoint(b2Vec2(0, 0)));
	rjd.enableLimit = true;
	rjd.lowerAngle = 0.0f;
	rjd.upperAngle = 0.0f;

	m_gripping_joint = GetWorld() -> CreateJoint(&rjd);
	m_gripping_resource_id = m_touching_resource_id;
}

void J1_AC_Gripper::Drop() {
	auto resource = static_cast<Block*>(GetSceneMgr()->GetNodeById(m_gripping_resource_id));
	unsigned int mask = resource->GetMask() & (~m_target_status_mask);
	resource->SetMask(mask);
	resource->SetGroundFriction(true, 5.0f, 5.0f);

	GetWorld()->DestroyJoint(m_gripping_joint);

	m_gripping_resource_id = m_null_id;
	m_gripping_joint = nullptr;
}

void J1_AC_Gripper::Act() {
	auto robot = static_cast<J1_A_Robot*>(GetActor());
	// Update touching status.
	if(m_touching_resource_id != m_null_id) {
		if(GetSceneMgr()->CountNodeById(m_touching_resource_id) == 0) {
			m_touching_resource_id = m_null_id;
		} else {
			auto resource = static_cast<Block*>(GetSceneMgr()->GetNodeById(m_touching_resource_id));
			unsigned int mask = resource->GetMask() & m_target_status_mask;
			if(mask == m_target_status_mask) {
				m_touching_resource_id = m_null_id;
			}
		}
	}
	// Update gripping status.
	if(m_gripping_resource_id != m_null_id) {
		if(GetSceneMgr()->CountNodeById(m_gripping_resource_id) == 0) {
			m_gripping_resource_id = m_null_id;
			m_gripping_joint = nullptr;
		}
	}

	// Grip resource if possible.
	if(m_gripping_resource_id==m_null_id && robot->GetMode()==m_required_mode
			&& m_touching_resource_id!=m_null_id) {
		Grip();
	}
	// Drop if necessary.
	if(m_gripping_resource_id!=m_null_id && robot->GetMode()!=m_required_mode) {
		Drop();
	}

	// Set output.
	SetSharedData<float>(m_output_index, m_gripping_resource_id==m_null_id ? 0.0f : 1.0f);
	// Reset touching status.
	m_touching_resource_id = m_null_id;
}
