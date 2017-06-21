/*
 * Motor.cpp
 *
 *  Created on: Mar 2, 2017
 *      Author: wei
 */

#include "Motor.h"

Motor::Motor(Configuration* conf) : assa2d::Component(conf) {
	b2BodyDef bd;
	bd.userData = static_cast<assa2d::Node*>(this);
	bd.type = b2_dynamicBody;
	bd.position = static_cast<assa2d::Component*>(static_cast<assa2d::Actor*>(GetActor())->GetMainComponent())->GetBody()->GetWorldPoint(conf->Position);
	bd.angle = static_cast<assa2d::Component*>(static_cast<assa2d::Actor*>(GetActor())->GetMainComponent())->GetBody()->GetAngle()+conf->Angle;

	b2Body* body = GetWorld() -> CreateBody(&bd);
	SetBody(body);

	b2FixtureDef fd;
	fd.shape = &conf->PolygonShape;
	fd.friction = conf->Friction;
	fd.density = conf->Density;
	fd.restitution = conf->Restitution;

	GetBody() -> CreateFixture(&fd);

	b2RevoluteJointDef rjd;
	rjd.Initialize(GetBody(), static_cast<assa2d::Component*>(static_cast<assa2d::Actor*>(GetActor())->GetMainComponent())->GetBody(), GetBody()->GetWorldPoint(conf->Anchor));
	rjd.enableLimit = true;
	rjd.lowerAngle = conf->LowerAngle;
	rjd.upperAngle = conf->UpperAngle;

	GetWorld() -> CreateJoint(&rjd);

	m_forward_attributes = conf->ForwardAttributes;
	m_backward_attributes = conf->BackwardAttributes;

	m_target_force_index = conf->TargetForceIndex;
	m_power_request_index = conf->PowerRequestIndex;
}

Motor::~Motor() {
	GetWorld() -> DestroyBody(GetBody());
}

void Motor::Act() {
	float32 targetspeed = GetSharedData<float>(m_target_force_index);
	float32 currentspeed = GetBody()->GetLocalVector(GetForwardVelocity()).x;

	MotorAttribute* attributes = nullptr;
	if(targetspeed > currentspeed + 0.001f) {
		attributes = &m_forward_attributes;
	} else if(targetspeed < currentspeed - 0.001f){
		attributes = &m_backward_attributes;
	}

	float32 availablepower = GetSharedData<float>(m_power_request_index);
	float32 power = std::min(attributes->MaxPower, availablepower);

	if(currentspeed * targetspeed > 0) {
		force = std::max(2,3);
	}








	float32 currentspeed = GetBody()->GetLocalVector(GetForwardVelocity()).x;
	float32 targetspeed = GetSharedData<float>(GetId()) * m_speed_factor;

	if(targetspeed < 0) {
		targetspeed /= 3.0f;
	}

	if(currentspeed < targetspeed - 0.001) {
		GetBody() ->ApplyForceToCenter(t_max_friction * GetBody()->GetWorldVector(b2Vec2(1,0)), true);
	} else if(currentspeed > targetspeed + 0.001) {
		GetBody() ->ApplyForceToCenter(-0.5 * t_max_friction * GetBody()->GetWorldVector(b2Vec2(1,0)), true);
	}
}

void Motor::Act_Anyway() {
	b2Vec2 lateralimpulse = GetBody()->GetMass() * -GetLateralVelocity();
	if(lateralimpulse.Length() > t_max_sliding_impulse) {
		lateralimpulse *= t_max_sliding_impulse / lateralimpulse.Length();
	}
	GetBody() -> ApplyLinearImpulse(lateralimpulse, GetBody()->GetWorldCenter(), true);

	GetBody() ->ApplyAngularImpulse(0.1f * GetBody()->GetInertia() * -GetBody()->GetAngularVelocity(), true);

	b2Vec2 forwardimpulse = GetBody()->GetMass() * -GetForwardVelocity();
	if(forwardimpulse.Length() > t_max_rolling_impulse) {
		forwardimpulse *= t_max_rolling_impulse / forwardimpulse.Length();
	}
	GetBody() -> ApplyLinearImpulse(forwardimpulse, GetBody()->GetWorldCenter(), true);
}

m_total_weight = weight;

assa2d::SceneMgr* scenemgr = static_cast<assa2d::SceneMgr*>(GetSceneMgr());

t_max_friction = m_total_weight * 10.0f * m_force_factor;
t_max_sliding_impulse = t_max_friction * m_lateral_friction * scenemgr-> GetTimeStep();
t_max_rolling_impulse = t_max_friction * m_forward_friction * scenemgr-> GetTimeStep();


