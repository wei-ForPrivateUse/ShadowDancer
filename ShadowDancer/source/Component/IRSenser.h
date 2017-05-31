/*
 * IRSenser.h
 *
 *  Created on: Mar 3, 2017
 *      Author: wei
 */

#ifndef COMPONENT_IRSENSER_H_
#define COMPONENT_IRSENSER_H_

#include <assassin2d/assassin2d.h>

class IRRayCastClosestCallback : public b2RayCastCallback {
public:
	IRRayCastClosestCallback(assa2d::Actor* actor) {
		_M_actor = actor;

		_M_hit = false;
		_M_point.SetZero();
	}

	virtual float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction) override {
		b2Body* body = fixture->GetBody();
		assa2d::Node* node = static_cast<assa2d::Node*>(body->GetUserData());
		if(node == nullptr) {
			throw std::runtime_error("IRRayCastCallBack : uncaught b2Body*.");
		}
		if(node->GetType() == assa2d::Node_Type::Actor_Component) {
			assa2d::Actor* actor = static_cast<assa2d::Actor*>(static_cast<assa2d::Component*>(node)->GetActor());
			if(actor == _M_actor) {
				return -1.0f;
			}
		}
		if(node->GetType() == assa2d::Node_Type::Actor) {
			assa2d::Actor* actor = static_cast<assa2d::Actor*>(node);
			if(actor == _M_actor) {
				return -1.0f;
			}
		}

		_M_hit = true;
		_M_point = point;

		return fraction;
	}

	assa2d::Actor* _M_actor;

	bool _M_hit;
	b2Vec2 _M_point;
};

/// IRSenser.
class IRSenser : public assa2d::Component {
public:
	struct Configuration : public assa2d::Component::Configuration {
		b2Vec2 Position;
		float32 Angle = 0.0f;

		float32 Range = 10.0f;
	};

	IRSenser(Configuration* conf);
	virtual ~IRSenser() { }

protected:
	virtual void Act() override;

private:
	b2Vec2 _M_position;
	float32 _M_angle;

	float32 _M_range;
};

#endif /* COMPONENT_IRSENSER_H_ */
