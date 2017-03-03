/*
 * Motor.h
 *
 *  Created on: Mar 2, 2017
 *      Author: wei
 */

#ifndef COMPONENT_MOTOR_H_
#define COMPONENT_MOTOR_H_

#include "assassin2d.h"

class Motor : public assa2d::Component {
public:
	struct Configuration : public assa2d::Component::Configuration {
		b2PolygonShape PolygonShape;

		b2Vec2 Anchor;
		float32 UpperAngle = 0.0f;
		float32 LowerAngle = 0.0f;

		float32 Density = 1.0f;
		float32 Friction = 0.1f;
		float32 Restitution = 0.3f;

		float32 LateralFriction = 5.0f;
		float32 ForwardFriction = 0.1f;
		float32 ForceFactor = 2.0f;
	};

	Motor(Configuration* conf);
	virtual ~Motor();

protected:
	virtual void Act() override;
	virtual void Act_Anyway() override;

	b2Vec2 GetLateralVelocity() const;
	b2Vec2 GetForwardVelocity() const;

private:
	float32 _M_lateral_friction;
	float32 _M_forward_friction;
	float32 _M_force_factor;

	float32 _T_max_friction;
	float32 _T_max_sliding_impulse;
	float32 _T_max_rolling_impulse;
};

inline b2Vec2 Motor::GetLateralVelocity() const {
	b2Vec2 cln = GetBody()->GetWorldVector(b2Vec2(0,1));
	return b2Dot(cln, GetBody()->GetLinearVelocity()) * cln;
}

inline b2Vec2 Motor::GetForwardVelocity() const {
	b2Vec2 cfn = GetBody()->GetWorldVector(b2Vec2(1,0));
	return b2Dot(cfn, GetBody()->GetLinearVelocity()) * cfn;
}

#endif /* COMPONENT_MOTOR_H_ */
