/*
 * Motor.h
 *
 *  Created on: Mar 2, 2017
 *      Author: wei
 */

#ifndef COMMON_COMPONENT_MOTOR_H_
#define COMMON_COMPONENT_MOTOR_H_

#include <assassin2d/assassin2d.h>

/// Motor attributes.
struct MotorAttribute {
	float32 MaxForce;
	float32 MaxSpeed;
	float32 MaxPower;
};

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
		MotorAttribute ForwardAttributes = {3.0f, 5.0f, 10.0f};
		MotorAttribute BackwardAttributes = {2.0f, 2.0f, 3.0f};
	    float32 SlidingFriction = 5.0f;
	    float32 RollingFriction = 0.1f;

		/// Indexes.
		std::size_t TargetSpeedIndex = 0;
		std::size_t PowerRequestIndex = 0;
	};

	Motor(Configuration* conf);
	virtual ~Motor();

	/// Getters.
	MotorAttribute const& GetForwardAttributes() const {
		return m_forward_attributes;
	}

	MotorAttribute const& GetBackwardAttributes() const {
		return m_backward_attributes;
	}

	/// Setters.
	void SetForwardAttributes(MotorAttribute const& attribute) {
		m_forward_attributes = attribute;
	}

	void SetBackwardAttributes(MotorAttribute const& attribute) {
		m_backward_attributes = attribute;
	}

protected:
	/// Apply motor force.
	virtual void Act() override;

	/// Apply ground friction.
	virtual void Act_Anyway() override;

	/// Get lateral velocity.
	b2Vec2 GetLateralVelocity() const {
		b2Vec2 cln = GetBody()->GetWorldVector(b2Vec2(0,1));
		return b2Dot(cln, GetBody()->GetLinearVelocity()) * cln;
	}

	/// Get forward velocity.
	b2Vec2 GetForwardVelocity() const {
		b2Vec2 cfn = GetBody()->GetWorldVector(b2Vec2(1,0));
		return b2Dot(cfn, GetBody()->GetLinearVelocity()) * cfn;
	}

private:
	MotorAttribute m_forward_attributes;
	MotorAttribute m_backward_attributes;
	float32 m_sliding_friction;
	float32 m_rolling_friction;

	std::size_t m_target_speed_index;
	std::size_t m_power_request_index;
};

#endif /* COMMON_COMPONENT_MOTOR_H_ */
