/*
 * J1_M_M2.h
 *
 *  Created on: Nov 29, 2017
 *      Author: wei
 */

#ifndef TESTS_J1_J1_M_M2_H_
#define TESTS_J1_J1_M_M2_H_

#include <unordered_map>

#include <assassin2d/assassin2d.h>

#include "J1_S_Field.h"

class J1_M_M2 : public assa2d::Monitor, public assa2d::ContactListener {
public:
	J1_M_M2() {
		fitness = 0.0f;
	};
	virtual ~J1_M_M2() { };

	float GetFitness() const {
		return fitness;
	}

protected:
	virtual void Initialize() override {
		auto a_s = static_cast<const J1_S_Field*>(GetSceneMgr());
		a_s->GetContactMgr().AddContactListener(this);
	}

	virtual void Step() override {
		auto a_s = static_cast<const J1_S_Field*>(GetSceneMgr());
		auto s = const_cast<J1_S_Field*>(a_s);

		// Record original position of resources.
		if(s->CountNodesByTag(MAKE_TAG('r', 'e', 's', 'o')) > 0) {
			for(auto node : s->GetNodesByTag(MAKE_TAG('r', 'e', 's', 'o'))) {
				auto resource = static_cast<Block*>(node);
				if(mapping.count(resource->GetId()) == 0) {
					mapping[resource->GetId()] = resource->GetPosition().Length();
				}
			}
		}
	}

	virtual void Finalize() override {
		auto a_s = static_cast<const J1_S_Field*>(GetSceneMgr());
		auto s = const_cast<J1_S_Field*>(a_s);

		// Direct bonus.
		fitness += s->m_nest->GetResourceCollected() * 100.0f;

		// Bootstrapping part.
		if(s->CountNodesByTag(MAKE_TAG('r', 'e', 's', 'o')) > 0) {
			for(auto node : s->GetNodesByTag(MAKE_TAG('r', 'e', 's', 'o'))) {
				auto resource = static_cast<Block*>(node);

				fitness += std::max(0.0f, mapping[resource->GetId()] - resource->GetPosition().Length());
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

	std::unordered_map<std::size_t, float32> mapping;
};

#endif /* TESTS_J1_J1_M_M2_H_ */
