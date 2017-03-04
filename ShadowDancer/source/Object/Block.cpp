/*
 * Block.cpp
 *
 *  Created on: Mar 3, 2017
 *      Author: wei
 */

#include "Block.h"

Block::Block(Configuration* conf) : assa2d::Object(conf) {
	assa2d::SceneMgr* scenemgr = static_cast<assa2d::SceneMgr*>(GetSceneMgr());
	b2World* world = scenemgr -> GetWorld();

	b2BodyDef bd;
	bd.userData = static_cast<assa2d::Node*>(this);
	if(conf->StaticBody) {
		bd.type = b2_staticBody;
	} else {
		bd.type = b2_dynamicBody;
	}
	bd.position = conf->Position;
	bd.angle = conf->Angle;

	_M_body = world -> CreateBody(&bd);

	b2FixtureDef fd;
	if(conf->ShapeType == assa2d::SDShapeType::Circle) {
		fd.shape = &conf->CircleShape;
	} else if (conf->ShapeType == assa2d::SDShapeType::Polygon) {
		fd.shape = &conf->PolygonShape;
	}
	fd.density = conf->Density;
	fd.restitution = conf->Restitution;
	fd.friction = conf->Friction;

	_M_body -> CreateFixture(&fd);

	if(conf->GroundFrictionEnabled) {
		float32 radius = b2Sqrt(2.0f * _M_body->GetInertia() / _M_body->GetMass());

		b2FrictionJointDef fjd;
		fjd.localAnchorA = _M_body->GetLocalCenter();
		fjd.localAnchorB.SetZero();
		fjd.bodyA = _M_body;
		fjd.bodyB = scenemgr -> GetGround();
		fjd.collideConnected = true;
		fjd.maxForce = _M_body->GetMass() * 10.0f;
		fjd.maxTorque = _M_body->GetMass() * radius * 10.0f;

		world -> CreateJoint(&fjd);
	}

}

Block::~Block() {
	assa2d::SceneMgr* scenemgr = static_cast<assa2d::SceneMgr*>(GetSceneMgr());
	b2World* world = scenemgr -> GetWorld();
	if(world)
		world -> DestroyBody(_M_body);
}

