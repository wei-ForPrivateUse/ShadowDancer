/*
 * J0_M_M2.h
 *
 *  Created on: Nov 29, 2017
 *      Author: wei
 */

#ifndef TESTS_J0_J0_M_M2_H_
#define TESTS_J0_J0_M_M2_H_

#include <unordered_map>

#include <assassin2d/assassin2d.h>

#include "J0_S_Field.h"

class J0_M_M2 : public assa2d::Monitor, public assa2d::ContactListener {
public:
	J0_M_M2() {
		fitness = 0.0f;
	};
	virtual ~J0_M_M2() { };

	float GetFitness() const {
		return fitness;
	}

protected:
	virtual void Initialize() override {
		auto a_s = static_cast<const J0_S_Field*>(GetSceneMgr());
		a_s->GetContactMgr().AddContactListener(this);
	}

	virtual void Step() override {
		auto a_s = static_cast<const J0_S_Field*>(GetSceneMgr());
		auto s = const_cast<J0_S_Field*>(a_s);

		// Record original position of resources.
		if(s->CountNodesByTag(MAKE_TAG('p', 'a', 'c', 'k')) > 0) {
			for(auto node : s->GetNodesByTag(MAKE_TAG('p', 'a', 'c', 'k'))) {
				auto package = static_cast<Block*>(node);
				if(mapping.count(package->GetId()) == 0) {
					mapping[package->GetId()] = (package->GetPosition()-b2Vec2(70.0f, 0.0f)).Length();
				}
			}
		} else {
			fitness += s->GetMaxStep() - s->GetCurrentStep();
			s->Terminate();
		}
	}

	virtual void Finalize() override {
		auto a_s = static_cast<const J0_S_Field*>(GetSceneMgr());
		auto s = const_cast<J0_S_Field*>(a_s);

		//
		for(auto& node : mapping) {
			if(s->CountNodeById(node.first) == 0) {
				fitness += node.second;
			} else {
				if(node.second > (static_cast<Block*>(s->GetNodeById(node.first))->GetPosition()-b2Vec2(70.0f, 0.0f)).Length()) {
					fitness += node.second - (static_cast<Block*>(s->GetNodeById(node.first))->GetPosition()-b2Vec2(70.0f, 0.0f)).Length();
				}
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

		if((ntA == assa2d::Node_Type::Actor_Component&&tagB == MAKE_TAG('p', 'a', 'c', 'k')) ||
				(ntB == assa2d::Node_Type::Actor_Component&&tagA == MAKE_TAG('p', 'a', 'c', 'k'))) {
			fitness += 0.001;
		}
	}

private:
	float32 fitness;

	std::unordered_map<std::size_t, float32> mapping;
};

#endif /* TESTS_J0_J0_M_M2_H_ */
