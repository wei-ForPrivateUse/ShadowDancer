/*
 * Wall.cpp
 *
 *  Created on: Mar 3, 2017
 *      Author: wei
 */

#include "Wall.h"

Wall::Wall(Configuration* conf) : assa2d::Object(conf) {
	b2BodyDef bd;
	bd.userData = static_cast<assa2d::Node*>(this);
	bd.position.Set(0.0f, 0.0f);

	b2Body* body = GetWorld() -> CreateBody(&bd);
	SetBody(body);

	b2EdgeShape shape;
	shape.Set(conf->StartPoint, conf->EndPoint);

	b2FixtureDef fd;
	fd.shape = &shape;
	fd.density = 0.0f;
	fd.friction = conf->Friction;
	fd.restitution = conf->Restitution;

	GetBody() -> CreateFixture(&fd);
}

Wall::~Wall() {
	GetWorld() -> DestroyBody(GetBody());
}

