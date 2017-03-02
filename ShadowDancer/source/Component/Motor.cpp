/*
 * Motor.cpp
 *
 *  Created on: Mar 2, 2017
 *      Author: wei
 */

#include "Motor.h"

Motor::Motor(Configuration* conf) : assa2d::Component(conf) {
	assa2d::SceneMgr* scenemgr = static_cast<assa2d::SceneMgr*>(GetSceneMgr());
	b2World* world = scenemgr->GetWorld();

	b2BodyDef bd;
	bd.type = b2_dynamicBody;
	bd.position = static_cast<assa2d::Component*>(static_cast<assa2d::Actor*>(GetActor())->GetMainComponent())->GetBody()->GetWorldPoint(conf->Position);
	bd.angle = static_cast<assa2d::Component*>(static_cast<assa2d::Actor*>(GetActor())->GetMainComponent())->GetBody()->GetAngle()+conf->Angle;
	bd.userData = static_cast<assa2d::Node*>(this);

	b2Body* body = world -> CreateBody(&bd);
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

	world -> CreateJoint(&rjd);

	_M_lateral_friction = conf->LateralFriction;
	_M_forward_friction = conf->ForwardFriction;
	_M_force_factor = conf->ForceFactor;

	_T_max_friction = 1.0f * 10.0f * _M_force_factor;
	_T_max_sliding_impulse = _T_max_friction * _M_lateral_friction * scenemgr-> GetTimeStep();
	_T_max_rolling_impulse = _T_max_friction * _M_forward_friction * scenemgr-> GetTimeStep();
}

Motor::~Motor() {
	assa2d::SceneMgr* scenemgr = static_cast<assa2d::SceneMgr*>(GetSceneMgr());
	b2World* world = scenemgr->GetWorld();

	world -> DestroyBody(GetBody());
}

void Motor::Act() {
	float32 currentspeed = GetBody()->GetLocalVector(GetForwardVelocity()).x;
	float32 targetspeed = GetSharedData<float>(GetId());

	if(currentspeed < targetspeed) {
		GetBody() ->ApplyForceToCenter(_T_max_friction * GetBody()->GetWorldVector(b2Vec2(1,0)), true);
	}
}

void Motor::Act_Anyway() {
	b2Vec2 lateralimpulse = GetBody()->GetMass() * -GetLateralVelocity();
	if(lateralimpulse.Length() > _T_max_sliding_impulse) {
		lateralimpulse *= _T_max_sliding_impulse / lateralimpulse.Length();
	}
	GetBody() -> ApplyLinearImpulse(lateralimpulse, GetBody()->GetWorldCenter(), true);

	GetBody() ->ApplyAngularImpulse(0.1f * GetBody()->GetInertia() * -GetBody()->GetAngularVelocity(), true);

	b2Vec2 forwardimpulse = GetBody()->GetMass() * -GetForwardVelocity();
	if(forwardimpulse.Length() > _T_max_rolling_impulse) {
		forwardimpulse *= _T_max_rolling_impulse / forwardimpulse.Length();
	}
	GetBody() -> ApplyLinearImpulse(forwardimpulse, GetBody()->GetWorldCenter(), true);
}


