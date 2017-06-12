/*
 * MainBody.h
 *
 *  Created on: Mar 2, 2017
 *      Author: wei
 */

#ifndef COMPONENT_MAINBODY_H_
#define COMPONENT_MAINBODY_H_

#include <assassin2d/assassin2d.h>

class MainBody : public assa2d::Component {
public:
	struct Configuration : public assa2d::Component::Configuration {
		b2Vec2 Position;
		float32 Angle = 0.0f;

		assa2d::ShapeType ShapeType = assa2d::ShapeType::Circle;

		b2PolygonShape PolygonShape;
		b2CircleShape CircleShape;

		float32 Density = 1.0f;
		float32 Friction = 0.2f;
		float32 Restitution = 0.3f;
	};

	MainBody(Configuration* conf);
	virtual ~MainBody();

protected:
	virtual void Act() override { }
};

#endif /* COMPONENT_MAINBODY_H_ */
