/*
 * J1_M_M0.h
 *
 *  Created on: Dec 1, 2017
 *      Author: wei
 */

#ifndef TESTS_J1_J1_M_M0_H_
#define TESTS_J1_J1_M_M0_H_

#include <unordered_map>

#include <assassin2d/assassin2d.h>

#include "J1_S_Field.h"

class J1_M_M0 : public assa2d::Monitor, public assa2d::ContactListener {
public:
	J1_M_M0() {
		fitness = 0.0f;
	};
	virtual ~J1_M_M0() { };

	float GetFitness() const {
		return fitness;
	}

protected:
	virtual void Initialize() override { }

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

private:
	float32 fitness;

	std::unordered_map<std::size_t, float32> mapping;
};

#endif /* TESTS_J1_J1_M_M0_H_ */