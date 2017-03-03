/*
 * Wall.h
 *
 *  Created on: Mar 3, 2017
 *      Author: wei
 */

#ifndef OBJECT_WALL_H_
#define OBJECT_WALL_H_

#include <assassin2d.h>

class Wall : public assa2d::Object {
public:
	struct Configuration : assa2d::Object::Configuration {
		b2Vec2 StartPoint;
		b2Vec2 EndPoint;

		float32 Friction = 0.1f;
		float32 Restitution = 0.3f;
	};

	Wall(Configuration* conf);
	virtual ~Wall();

	b2Body* _M_body;
};

#endif /* OBJECT_WALL_H_ */
