/*
 * J1_M_M3.h
 *
 *  Created on: Nov 30, 2017
 *      Author: wei
 */

#ifndef TESTS_J1_J1_M_M3_H_
#define TESTS_J1_J1_M_M3_H_

#include <assassin2d/assassin2d.h>

#include "J1_S_Field.h"

class J1_M_M3 : public assa2d::Monitor, public assa2d::ContactListener {
public:
	J1_M_M3() {
		fitness = 0.0f;
	};
	virtual ~J1_M_M3() { };

	float GetFitness() const {
		return fitness;
	}

protected:
	virtual void Initialize() override {
		auto a_s = static_cast<const J1_S_Field*>(GetSceneMgr());
		a_s->GetContactMgr().AddContactListener(this);
	}

	virtual void Step() override { }

	virtual void Finalize() override {
		auto a_s = static_cast<const J1_S_Field*>(GetSceneMgr());
		auto s = const_cast<J1_S_Field*>(a_s);

		// Direct bonus.
		fitness += s->m_nest->GetPackageCollected() * 1800.0f;

		// Bootstrapping part.
		if(s->CountNodesByTag(MAKE_TAG('p', 'a', 'c', 'k')) > 0) {
			for(auto node : s->GetNodesByTag(MAKE_TAG('p', 'a', 'c', 'k'))) {
				auto package = static_cast<J1_O_Package*>(node);
				fitness += 1800.0f - package->GetRequiredTouch();
			}
		}
	};

	/// Obstacle avoidance.
	virtual void PreSolve(const b2Contact* contact, const b2Manifold* oldManifold) override {
		const b2Body* bA = contact->GetFixtureA()->GetBody();
		const b2Body* bB = contact->GetFixtureB()->GetBody();
		assa2d::Node* nA = static_cast<assa2d::Node*>(bA->GetUserData());
		assa2d::Node* nB = static_cast<assa2d::Node*>(bB->GetUserData());

		auto ntA = nA->GetType();
		auto ntB = nB->GetType();

		auto tagA = nA->GetTag();
		auto tagB = nB->GetTag();

		if(tagA == MAKE_TAG('w', 'a', 'l', 'l') || tagB == MAKE_TAG('w', 'a', 'l', 'l')) {
			fitness -= 1.0f;
		}

		if(ntA == assa2d::Node_Type::Actor_Component && ntB == assa2d::Node_Type::Actor_Component) {
			auto robotA = static_cast<assa2d::Component*>(nA)->GetActor();
			auto robotB = static_cast<assa2d::Component*>(nB)->GetActor();
			if(robotA != robotB) {
				fitness -= 1.0f;
			}
		}
	}

private:
	float32 fitness;
};

#endif /* TESTS_J1_J1_M_M3_H_ */
