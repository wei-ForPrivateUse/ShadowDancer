/*
 * Motor.h
 *
 *  Created on: Mar 2, 2017
 *      Author: wei
 */

#ifndef COMMON_COMPONENT_MOTOR_H_
#define COMMON_COMPONENT_MOTOR_H_

#include <assassin2d/assassin2d.h>

/// Motor.
class Motor : public assa2d::Component {
public:
	struct Configuration : public assa2d::Component::Configuration {
		/// Relative position & angle (in the sight of main component).
		b2Vec2 Position;
		float32 Angle = 0.0f;

		/// Shape.
		b2PolygonShape PolygonShape;

		/// Anchor position and allowed angle.
		b2Vec2 Anchor;
		float32 UpperAngle = 0.0f;
		float32 LowerAngle = 0.0f;

		/// Rigid body attributes.
		float32 Density = 1.0f;
		float32 Friction = 0.1f;
		float32 Restitution = 0.3f;

		/// Motor attributes.
		float32 MaxPower = 1.0f;
		float32 MaxSpeed = 3.0f;
		float32 MaxForce = 1.0f;
		float32 MaxBackPower = 0.3f;
		float32 MaxBackSpeed = 1.0f;
		float32 MaxBackForce = 0.3f;

		/// Indexes.
		std::size_t TargetForceIndex = 0;
		std::size_t PowerRequestIndex = 0;
	};

	Motor(Configuration* conf);
	virtual ~Motor();

protected:
	/// Apply motor force.
	virtual void Act() override;

	/// Apply ground friction.
	virtual void Act_Anyway() override;

	/// Get lateral velocity.
	b2Vec2 GetLateralVelocity() const;

	/// Get forward velocity.
	b2Vec2 GetForwardVelocity() const;

private:
	std::size_t m_target_force_index;
	std::size_t m_power_request_index;

	float32 m_max_power;
	float32 m_max_speed;
	float32 m_max_force;
	float32 m_max_back_power;
	float32 m_max_back_speed;
	float32 m_max_back_force;
};

inline b2Vec2 Motor::GetLateralVelocity() const {
	b2Vec2 cln = GetBody()->GetWorldVector(b2Vec2(0,1));
	return b2Dot(cln, GetBody()->GetLinearVelocity()) * cln;
}

inline b2Vec2 Motor::GetForwardVelocity() const {
	b2Vec2 cfn = GetBody()->GetWorldVector(b2Vec2(1,0));
	return b2Dot(cfn, GetBody()->GetLinearVelocity()) * cfn;
}

#endif /* COMMON_COMPONENT_MOTOR_H_ */
