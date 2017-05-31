/*
 * Block.h
 *
 *  Created on: Mar 3, 2017
 *      Author: wei
 */

#ifndef OBJECT_BLOCK_H_
#define OBJECT_BLOCK_H_

#include <assassin2d/assassin2d.h>

class Block : public assa2d::Object {
public:
	struct Configuration : public assa2d::Object::Configuration {
		b2Vec2 Position;
		float32 Angle;

		assa2d::ShapeType ShapeType = assa2d::ShapeType::Circle;

		b2PolygonShape PolygonShape;
		b2CircleShape CircleShape;

		float32 Density = 1.0f;
		float32 Friction = 0.2f;
		float32 Restitution = 0.3f;

		bool GroundFrictionEnabled = true;
		bool StaticBody = false;
	};

	Block(Configuration* conf);
	virtual ~Block();
};

#endif /* OBJECT_BLOCK_H_ */
