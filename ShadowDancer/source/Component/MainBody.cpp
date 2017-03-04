/*
 * MainBody.cpp
 *
 *  Created on: Mar 2, 2017
 *      Author: wei
 */

#include "MainBody.h"

MainBody::MainBody(Configuration* conf) : assa2d::Component(conf) {
	assa2d::SceneMgr* scenemgr = static_cast<assa2d::SceneMgr*>(GetSceneMgr());
	b2World* world = scenemgr -> GetWorld();

	b2BodyDef bd;
	bd.userData = static_cast<assa2d::Node*>(this);
	bd.type = b2_dynamicBody;
	bd.position = conf->Position;
	bd.angle = conf->Angle;

	b2Body* body = world -> CreateBody(&bd);
	SetBody(body);

	b2FixtureDef fd;
	if(conf->ShapeType == assa2d::SDShapeType::Circle) {
		fd.shape = &conf->CircleShape;
	} else if (conf->ShapeType == assa2d::SDShapeType::Polygon) {
		fd.shape = &conf->PolygonShape;
	}
	fd.density = conf->Density;
	fd.restitution = conf->Restitution;
	fd.friction = conf->Friction;

	GetBody() -> CreateFixture(&fd);
}

MainBody::~MainBody() {
	assa2d::SceneMgr* scenemgr = static_cast<assa2d::SceneMgr*>(GetSceneMgr());
	b2World* world = scenemgr->GetWorld();
	if(world) {
		world -> DestroyBody(GetBody());
	}
}

