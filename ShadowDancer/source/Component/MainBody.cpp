/*
 * MainBody.cpp
 *
 *  Created on: Mar 2, 2017
 *      Author: wei
 */

#include "MainBody.h"

MainBody::MainBody(Configuration* conf) : assa2d::Component(conf) {
	b2BodyDef bd;
	bd.userData = static_cast<assa2d::Node*>(this);
	bd.type = b2_dynamicBody;
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
}

MainBody::~MainBody() {
	GetWorld() -> DestroyBody(GetBody());
	SetBody(nullptr);
}

