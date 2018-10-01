/*
 * J0_M_M1.h
 *
 *  Created on: Nov 16, 2017
 *      Author: wei
 */

#ifndef TESTS_J_AROB_2018_J0_M_M1_H_
#define TESTS_J_AROB_2018_J0_M_M1_H_

#include <assassin2d/assassin2d.h>

#include "J0_S_Field.h"

class J0_M_M1 : public assa2d::Monitor, public assa2d::ContactListener {
public:
	J0_M_M1() {
		fitness_A = 0.0f;
		fitness_B = 0.0f;
	};
	virtual ~J0_M_M1() { };

	float GetFitnessA() const {
		return fitness_A;
	}

	float GetFitnessB() const {
		return fitness_B;
	}

protected:
	virtual void Initialize() override {
		auto a_s = static_cast<const J0_S_Field*>(GetSceneMgr());
		a_s->GetContactMgr().AddContactListener(this);

		CheckPoint cp;
		for(int i = 0; i < 100; i++) {
			float32 r = assa2d::RandomFloat(0.0f, 48.0f);
			float32 a = assa2d::RandomFloat(0, M_PI*2.0f);
			float32 x = r * std::cos(a);
			float32 y = r * std::sin(a);
			cp.Position.Set(x, y);
			m_check_point_vector.push_back(cp);
		}
	}

	virtual void Step() override {
		auto a_s = static_cast<const J0_S_Field*>(GetSceneMgr());
		for(auto & cp : m_check_point_vector) {
			bool visited = false;
			for(auto robot : a_s->m_robot) {
				if((robot->GetMainComponent()->GetPosition()-cp.Position).LengthSquared() < 64) {
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

		float visited_count = 0.0f;

		for(auto & cp : m_check_point_vector) {
			if(cp.record==0) {
				visited_count = visited_count + 1;
			}
			fitness_A -= cp.record*0.01;
		}

		fitness_B += visited_count;
	}

	virtual void Finalize() {
		auto a_s = static_cast<const J0_S_Field*>(GetSceneMgr());
		fitness_B /= a_s->GetMaxStep();
	};

	/// Obstacle avoidance.
	virtual void PreSolve(const b2Contact* contact, const b2Manifold* oldManifold) override {
		const b2Body* bA = contact->GetFixtureA()->GetBody();
		const b2Body* bB = contact->GetFixtureB()->GetBody();
		assa2d::Node* nA = static_cast<assa2d::Node*>(bA->GetUserData());
		assa2d::Node* nB = static_cast<assa2d::Node*>(bB->GetUserData());

		auto ntA = nA->GetType();
		auto ntB = nB->GetType();

		if(ntA == assa2d::Node_Type::Actor_Component || ntB == assa2d::Node_Type::Actor_Component) {
			fitness_A -= 5.0f;
			fitness_B -= 1.0f;
		}
	}

private:
	struct CheckPoint {
		b2Vec2 Position;
		std::size_t record = 0;
	};

	float32 fitness_A;
	float32 fitness_B;

	std::vector<CheckPoint> m_check_point_vector;
};

#endif /* TESTS_J_AROB_2018_J0_M_M1_H_ */
