/*
 * M_M0.h
 *
 *  Created on: Oct 5, 2018
 *      Author: wei
 */

#ifndef TESTS_J_FOR_HIRAGA_2018_M_M0_H_
#define TESTS_J_FOR_HIRAGA_2018_M_M0_H_

#include <unordered_map>

#include <assassin2d/assassin2d.h>

#include "S_Field.h"

/////
class M_M0 : public assa2d::Monitor {
public:
	M_M0() {
		bonus = 0.0f;
		penalty = 0.0f;

		penalty_goal = 0.0f;
		penalty_boot = 0.0f;
	};
	virtual ~M_M0() { };

	float32 GetFitness() const {
		return bonus - penalty;
	}

	float32 GetBonus() const {
		return bonus;
	}

	float32 GetPenalty() const {
		return penalty;
	}

	float32 penalty_goal;
	float32 penalty_boot;

protected:
	virtual void Initialize() override { }

	virtual void Step() override {
		auto a_s = static_cast<const S_Field*>(GetSceneMgr());
		auto s = const_cast<S_Field*>(a_s);

		// Record original position of resources.
		if(s->CountNodesByTag(MAKE_TAG('r', 'e', 's', 'o')) > 0) {
			for(auto node : s->GetNodesByTag(MAKE_TAG('r', 'e', 's', 'o'))) {
				auto resource = static_cast<Block*>(node);
				if(mapping.count(resource->GetId()) == 0) {
					mapping[resource->GetId()] = NodeInfo(resource->GetPosition().Length(), resource->GetFlag());
				}
			}
		}
	}

	virtual void Finalize() override {
		auto a_s = static_cast<const S_Field*>(GetSceneMgr());
		auto s = const_cast<S_Field*>(a_s);

		//
		for(auto& node : mapping) {
			if(s->CountNodeById(node.first) == 0) {
				if(node.second.flag == 0) {
					bonus += node.second.ori_dis;
				} else {
					penalty += node.second.ori_dis * penalty_goal;
				}
			} else {
				if(node.second.ori_dis > static_cast<Block*>(s->GetNodeById(node.first))->GetPosition().Length()) {
					if(node.second.flag == 0) {
						bonus += node.second.ori_dis - static_cast<Block*>(s->GetNodeById(node.first))->GetPosition().Length();
					} else {
						penalty += (node.second.ori_dis - static_cast<Block*>(s->GetNodeById(node.first))->GetPosition().Length()) * penalty_boot;
					}
				}
			}
		}
	}

private:
	struct NodeInfo {
		NodeInfo() : ori_dis(0.0f), flag(0) {}
		NodeInfo(float32 d, unsigned int f) : ori_dis(d), flag(f) { }

		float32 ori_dis;
		unsigned int flag;

	};
	float32 bonus;
	float32 penalty;

	std::unordered_map<std::size_t, NodeInfo> mapping;
};



#endif /* TESTS_J_FOR_HIRAGA_2018_M_M0_H_ */
