/*
 * Motor.h
 *
 *  Created on: Mar 2, 2017
 *      Author: wei
 */

#ifndef COMMON_COMPONENT_MOTOR_H_
#define COMMON_COMPONENT_MOTOR_H_

#include <assassin2d/assassin2d.h>

class Motor : public assa2d::Component {
public:
	struct Configuration : public assa2d::Component::Configuration {
		b2Vec2 Position;
		float32 Angle = 0.0f;

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
		float32 SpeedFactor = 5.0f;

		float32 TotalWeight = 1.0f;
	};

	Motor(Configuration* conf);
	virtual ~Motor();

	/// Get current weight, which is used to calculate frictions and powers.
	float32 GetTotalWeight() const;

	/// Set total weight.
	void SetTotalWeight(float32 weight);

protected:
	virtual void Act() override;
	virtual void Act_Anyway() override;

	b2Vec2 GetLateralVelocity() const;
	b2Vec2 GetForwardVelocity() const;

private:
	float32 _M_lateral_friction;
	float32 _M_forward_friction;
	float32 _M_force_factor;
	float32 _M_speed_factor;
	float32 _M_total_weight;

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

inline float32 Motor::GetTotalWeight() const {
	return _M_total_weight;
}

inline void Motor::SetTotalWeight(float32 weight) {
	_M_total_weight = weight;

	assa2d::SceneMgr* scenemgr = static_cast<assa2d::SceneMgr*>(GetSceneMgr());

	_T_max_friction = _M_total_weight * 10.0f * _M_force_factor;
	_T_max_sliding_impulse = _T_max_friction * _M_lateral_friction * scenemgr-> GetTimeStep();
	_T_max_rolling_impulse = _T_max_friction * _M_forward_friction * scenemgr-> GetTimeStep();
}

#endif /* COMMON_COMPONENT_MOTOR_H_ */
