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
	m_sliding_friction = conf->SlidingFriction;
	m_rolling_friction = conf->RollingFriction;

	m_target_speed_index = conf->TargetSpeedIndex;
	m_power_request_index = conf->PowerRequestIndex;
}

Motor::~Motor() {
	GetWorld() -> DestroyBody(GetBody());
}

void Motor::Act() {
	float32 speedfactor = GetSharedData<float>(m_target_speed_index);
	float32 targetspeed = speedfactor * (speedfactor>0.0f ? m_forward_attributes.MaxSpeed : m_backward_attributes.MaxSpeed);
	float32 currentspeed = GetBody()->GetLocalVector(GetForwardVelocity()).x;

	MotorAttribute* attributes = nullptr;
	int32 direction = 0;
	if(targetspeed > currentspeed + 0.001f) {
		attributes = &m_forward_attributes;
		direction = 1;
	} else if(targetspeed < currentspeed - 0.001f){
		attributes = &m_backward_attributes;
		direction = -1;
	} else {
		return;
	}

	float32 availablepower = GetSharedData<float>(m_power_request_index);
	float32 power = std::min(attributes->MaxPower, availablepower);

	float32 force = 0.0f;
	if(currentspeed * direction > 0) {
		force = std::min(attributes->MaxForce, std::fabs(power/currentspeed));
	} else {
		force = attributes->MaxForce;
	}

	GetBody() -> ApplyForceToCenter(force * direction * GetBody()->GetWorldVector(b2Vec2(1,0)), true);
}

void Motor::Act_Anyway() {
	assa2d::SceneMgr* scenemgr = static_cast<assa2d::SceneMgr*>(GetSceneMgr());
	float32 maxfriction = std::max(m_forward_attributes.MaxForce, m_backward_attributes.MaxForce);
	float32 maxslidingimpulse = maxfriction * m_sliding_friction * scenemgr-> GetTimeStep();
	float32 maxrollingimpulse = maxfriction * m_rolling_friction * scenemgr-> GetTimeStep();

	b2Vec2 lateralimpulse = GetBody()->GetMass() * -GetLateralVelocity();
	if(lateralimpulse.Length() > maxslidingimpulse) {
		lateralimpulse *= maxslidingimpulse / lateralimpulse.Length();
	}
	GetBody() -> ApplyLinearImpulse(lateralimpulse, GetBody()->GetWorldCenter(), true);

	GetBody() ->ApplyAngularImpulse(0.1f * GetBody()->GetInertia() * -GetBody()->GetAngularVelocity(), true);

	b2Vec2 forwardimpulse = GetBody()->GetMass() * -GetForwardVelocity();
	if(forwardimpulse.Length() > maxrollingimpulse) {
		forwardimpulse *= maxrollingimpulse / forwardimpulse.Length();
	}
	GetBody() -> ApplyLinearImpulse(forwardimpulse, GetBody()->GetWorldCenter(), true);
}
