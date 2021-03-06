/*
 * IRSenser.h
 *
 *  Created on: Mar 3, 2017
 *      Author: wei
 */

#ifndef COMMON_COMPONENT_IRSENSER_H_
#define COMMON_COMPONENT_IRSENSER_H_

#include <assassin2d/assassin2d.h>

/// Ray cast callback.
class IRRayCastClosestCallback : public b2RayCastCallback {
public:
	IRRayCastClosestCallback(assa2d::Actor* actor) {
		m_actor = actor;

		m_hit = false;
		m_point.SetZero();
	}

	/// See b2RayCastCallback for details.
	virtual float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction) override {
		b2Body* body = fixture->GetBody();
		assa2d::Node* node = static_cast<assa2d::Node*>(body->GetUserData());
		if(node == nullptr) {
			throw std::runtime_error("IRRayCastCallBack : uncaught b2Body*.");
		}
		if(node->GetType() == assa2d::Node_Type::Actor_Component) {
			assa2d::Actor* actor = static_cast<assa2d::Actor*>(static_cast<assa2d::Component*>(node)->GetActor());
			if(actor == m_actor) {
				return -1.0f;
			}
		}
		if(node->GetType() == assa2d::Node_Type::Actor) {
			assa2d::Actor* actor = static_cast<assa2d::Actor*>(node);
			if(actor == m_actor) {
				return -1.0f;
			}
		}

		m_hit = true;
		m_point = point;

		return fraction;
	}

	assa2d::Actor* m_actor;

	bool m_hit;
	b2Vec2 m_point;
};

/// IRSenser.
class IRSenser : public assa2d::Component {
public:
	struct Configuration : public assa2d::Component::Configuration {
		b2Vec2 Position;
		float32 Angle = 0.0f;

		float32 Range = 10.0f;

		std::size_t OutputIndex = 0;
	};

	IRSenser(Configuration* conf);
	virtual ~IRSenser() { }

protected:
	/// Detect distance from specific position and angle (in the sight of this actor's main component).
	virtual void Act() override;

private:
	b2Vec2 m_position;
	float32 m_angle;

	float32 m_range;

	std::size_t m_output_index;
};

#endif /* COMMON_COMPONENT_IRSENSER_H_ */
