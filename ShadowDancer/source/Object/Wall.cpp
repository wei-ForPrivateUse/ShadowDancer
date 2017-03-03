/*
 * Wall.cpp
 *
 *  Created on: Mar 3, 2017
 *      Author: wei
 */

#include "Wall.h"

Wall::Wall(Configuration* conf) : assa2d::Object(conf) {
	assa2d::SceneMgr* scenemgr = static_cast<assa2d::SceneMgr*>(GetSceneMgr());
	b2World* world = scenemgr -> GetWorld();

	b2BodyDef bd;
	bd.position.Set(0.0f, 0.0f);
	bd.userData = static_cast<assa2d::Node*>(this);

	_M_body = world -> CreateBody(&bd);

	b2EdgeShape shape;
	shape.Set(conf->StartPoint, conf->EndPoint);

	b2FixtureDef fd;
	fd.shape = &shape;
	fd.density = 0.0f;
	fd.friction = conf->Friction;
	fd.restitution = conf->Restitution;

	_M_body -> CreateFixture(&fd);
}

Wall::~Wall() {
	assa2d::SceneMgr* scenemgr = static_cast<assa2d::SceneMgr*>(GetSceneMgr());
	b2World* world = scenemgr -> GetWorld();
	if(world)
		world -> DestroyBody(_M_body);
}

