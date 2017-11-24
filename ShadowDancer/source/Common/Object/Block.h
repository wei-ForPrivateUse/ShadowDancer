/*
 * Block.h
 *
 *  Created on: Mar 3, 2017
 *      Author: wei
 */

#ifndef COMMON_OBJECT_BLOCK_H_
#define COMMON_OBJECT_BLOCK_H_

#include <assassin2d/assassin2d.h>

/// Static or dynamic block (e.g. obstacle).
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

		bool StaticBody = false;

		bool GroundFriction = true;
		float32 GroundFrictionForce = 1.0f;
		float32 GroundFrictionTorque = 1.0f;

		unsigned int Mark = 0;
	};

	Block(Configuration* conf);
	virtual ~Block();

	/// Set ground friction.
	void SetGroundFriction(bool flag, float32 gff, float32 gft);

	/// Get mark.
	unsigned int GetMark() const {
		return m_mark;
	}

	/// Set mark.
	void SetMark(unsigned int mark) {
		m_mark = mark;
	}

private:
	unsigned int m_mark;

	b2Joint* m_ground_friction_joint;
};

#endif /* COMMON_OBJECT_BLOCK_H_ */
