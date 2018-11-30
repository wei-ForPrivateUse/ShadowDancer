/*
 * J0_M_M0.h
 *
 *  Created on: Dec 1, 2017
 *      Author: wei
 */

#ifndef TESTS_J0_J0_M_M0_H_
#define TESTS_J0_J0_M_M0_H_

#include <unordered_map>

#include <assassin2d/assassin2d.h>

#include "J0_S_Field.h"

class J0_M_M0 : public assa2d::Monitor, public assa2d::ContactListener {
public:
	J0_M_M0() {
		fitness_s1 = 0.0f;
		fitness_s2 = 0.0f;
		fitness_s3 = 0.0f;
		bonus = 0.0f;

		resource_6000 = 0.0f;
		package_6000 = 0.0f;
		resource_8000 = 0.0f;
		package_8000 = 0.0f;
		resource_10000 = 0.0f;
		package_10000 = 0.0f;
		resource_12000 = 0.0f;
		package_12000 = 0.0f;

	};
	virtual ~J0_M_M0() { };

	float GetFitnessS1() const {
		return fitness_s1;
	}

	float GetFitnessS2() const {
		return fitness_s2;
	}

	float GetFitnessS3() const {
		return fitness_s3;
	}

	float GetBonus() const {
		return bonus;
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
		auto s = const_cast<J0_S_Field*>(a_s);
		/// s1
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
		}

		fitness_s1 += visited_count;

		/// s2
		// Record original position of resources.
		if(s->CountNodesByTag(MAKE_TAG('p', 'a', 'c', 'k')) > 0) {
			for(auto node : s->GetNodesByTag(MAKE_TAG('p', 'a', 'c', 'k'))) {
				auto package = static_cast<Block*>(node);
				if(mapping_s2.count(package->GetId()) == 0) {
					mapping_s2[package->GetId()] = (package->GetPosition()-b2Vec2(70.0f, 0.0f)).Length();
				}
			}
		}

		/// s3
		// Record original position of resources.
		if(s->CountNodesByTag(MAKE_TAG('r', 'e', 's', 'o')) > 0) {
			for(auto node : s->GetNodesByTag(MAKE_TAG('r', 'e', 's', 'o'))) {
				auto package = static_cast<Block*>(node);
				if(mapping_s3.count(package->GetId()) == 0) {
					mapping_s3[package->GetId()] = (package->GetPosition()-b2Vec2(-70.0f, 0.0f)).Length();
				}
			}
		}

//		if(s->CountNodesByTag(MAKE_TAG('r', 'e', 's', 'o'))==0 && s->CountNodesByTag(MAKE_TAG('p', 'a', 'c', 'k'))==0) {
//			bonus = s->GetMaxStep() - s->GetCurrentStep();
//			s->Terminate();
//		}

		//////
		if(GetSceneMgr()->GetCurrentStep() == 6000) {
			resource_6000 = static_cast<const J0_S_Field*>(GetSceneMgr())->m_nest_resource->GetCount();
			package_6000 = static_cast<const J0_S_Field*>(GetSceneMgr())->m_nest_package->GetCount();
		}
		if(GetSceneMgr()->GetCurrentStep() == 8000) {
			resource_8000 = static_cast<const J0_S_Field*>(GetSceneMgr())->m_nest_resource->GetCount();
			package_8000 = static_cast<const J0_S_Field*>(GetSceneMgr())->m_nest_package->GetCount();
		}
		if(GetSceneMgr()->GetCurrentStep() == 10000) {
			resource_10000 = static_cast<const J0_S_Field*>(GetSceneMgr())->m_nest_resource->GetCount();
			package_10000 = static_cast<const J0_S_Field*>(GetSceneMgr())->m_nest_package->GetCount();
		}
		if(GetSceneMgr()->GetCurrentStep() == 12000) {
			resource_12000 = static_cast<const J0_S_Field*>(GetSceneMgr())->m_nest_resource->GetCount();
			package_12000 = static_cast<const J0_S_Field*>(GetSceneMgr())->m_nest_package->GetCount();
		}
	}

	virtual void Finalize() override {
		auto a_s = static_cast<const J0_S_Field*>(GetSceneMgr());
		auto s = const_cast<J0_S_Field*>(a_s);

		// s1
		fitness_s1 /= s->GetMaxStep();

		// s2
		for(auto& node : mapping_s2) {
			if(s->CountNodeById(node.first) == 0) {
				fitness_s2 += node.second;
			} else {
				if(node.second > (static_cast<Block*>(s->GetNodeById(node.first))->GetPosition()-b2Vec2(70.0f, 0.0f)).Length()) {
					fitness_s2 += node.second - (static_cast<Block*>(s->GetNodeById(node.first))->GetPosition()-b2Vec2(70.0f, 0.0f)).Length();
				}
			}
		}

		// s3
		for(auto& node : mapping_s3) {
			if(s->CountNodeById(node.first) == 0) {
				fitness_s3 += node.second;
			} else {
				if(node.second > (static_cast<Block*>(s->GetNodeById(node.first))->GetPosition()-b2Vec2(-70.0f, 0.0f)).Length()) {
					fitness_s3 += node.second - (static_cast<Block*>(s->GetNodeById(node.first))->GetPosition()-b2Vec2(-70.0f, 0.0f)).Length();
				}
			}
		}
	};

private:
	float32 fitness_s1;
	float32 fitness_s2;
	float32 fitness_s3;
	float32 bonus;
public:
	float32 resource_6000;
	float32 package_6000;
	float32 resource_8000;
	float32 package_8000;
	float32 resource_10000;
	float32 package_10000;
	float32 resource_12000;
	float32 package_12000;


	/// s1
	struct CheckPoint {
		b2Vec2 Position;
		std::size_t record = 0;
	};
	std::vector<CheckPoint> m_check_point_vector;

	/// s2
	std::unordered_map<std::size_t, float32> mapping_s2;

	/// s3
	std::unordered_map<std::size_t, float32> mapping_s3;
};

#endif /* TESTS_J0_J0_M_M0_H_ */
