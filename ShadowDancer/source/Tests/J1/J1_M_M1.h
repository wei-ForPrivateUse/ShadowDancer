/*
 * J1_M_M1.h
 *
 *  Created on: Nov 16, 2017
 *      Author: wei
 */

#ifndef TESTS_J1_J1_M_M1_H_
#define TESTS_J1_J1_M_M1_H_

#include <assassin2d/assassin2d.h>

#include "J1_S_Field.h"

struct CheckPoint {
	b2Vec2 Position;
	std::size_t record = 0;
};

class J1_M_M1 : public assa2d::Monitor, public assa2d::ContactListener {
public:
	J1_M_M1() {
		fitness = 0.0f;
	};
	virtual ~J1_M_M1() { };

	float GetFitness() const {
		return fitness;
	}

protected:
	virtual void Initialize() override {
		auto a_s = static_cast<const J1_S_Field*>(GetSceneMgr());
		a_s->GetContactMgr().AddContactListener(this);

		CheckPoint cp;
		for(int i = -100; i < 100; i = i + 20){
			for(int j = -100; j < 100; j = j + 20) {
				cp.Position.Set(i, j);
				if(cp.Position.LengthSquared() < 10000 && cp.Position.LengthSquared() > 256) {
					m_check_point_vector.push_back(cp);
				}
			}
		}
	}

	virtual void Step() override {
		auto a_s = static_cast<const J1_S_Field*>(GetSceneMgr());
		for(auto & cp : m_check_point_vector) {
			bool visited = false;
			for(auto robot : a_s->m_robot) {
				if((robot->GetMainComponent()->GetPosition()-cp.Position).LengthSquared() < 144) {
					visited = true;
					break;
				}
			}
			if(visited) {
				cp.record = 0;
			} else {
				cp.record++;
			}
		}

		for(auto & cp : m_check_point_vector) {
			fitness -= cp.record;
		}
	}

	virtual void Finalize() { };

	/// Obstacle avoidance.
	virtual void PreSolve(const b2Contact* contact, const b2Manifold* oldManifold) override {
		const b2Body* bA = contact->GetFixtureA()->GetBody();
		const b2Body* bB = contact->GetFixtureB()->GetBody();
		assa2d::Node* nA = static_cast<assa2d::Node*>(bA->GetUserData());
		assa2d::Node* nB = static_cast<assa2d::Node*>(bB->GetUserData());

		auto ntA = nA->GetType();
		auto ntB = nB->GetType();

		if(ntA == assa2d::Node_Type::Actor_Component || ntB == assa2d::Node_Type::Actor_Component) {
			fitness -= 100.0f;
		}
	}

private:
	float32 fitness;

	std::vector<CheckPoint> m_check_point_vector;
};



#endif /* TESTS_J1_J1_M_M1_H_ */
