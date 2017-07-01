/*
 * PMonitor.h
 *
 *  Created on: Mar 4, 2017
 *      Author: wei
 */

#ifndef TESTS_POISONFOOD_PMONITOR_H_
#define TESTS_POISONFOOD_PMONITOR_H_

#include <assassin2d/assassin2d.h>

#include "PScene.h"

/// Awards.
struct PAward {
	float32 Contact;
	float32 DistanceMoved;
	float32 Goal;
};

/// Evaluate this simulation.
class PMonitor : public assa2d::Monitor , public assa2d::ContactListener {
public:
	PMonitor() {
		m_awards = {0.01, 2500.0f, 3000.0f};

		m_fitness = 0.0f;
	}
	virtual ~PMonitor() { };

	/// Backdoor.
	void f(bul::manager::SceneMgr* s) {
		auto a_s = static_cast<assa2d::SceneMgr*>(s);
		a_s->GetContactMgr().AddContactListener(this);
	}

	/// Get fitness.
	float32 GetFitness() const {
		return m_fitness;
	}

protected:
	/// Add this monitor to contact listener list & save original position of foods.
	void Initialize() {
		auto a_s = static_cast<const PScene*>(GetSceneMgr());
		a_s->GetContactMgr().AddContactListener(this);
	};

	/// Add extra bonus.
	void Step() {
		auto a_s = static_cast<const PScene*>(GetSceneMgr());

		for(auto node : *a_s->m_food_list) {
			if(m_original_position.count(node) == 0) {
				m_original_position[node] = GetNodePosition(node);
			}
		}
	};

	/// Calculate moved and goal awards.
	void Finalize() {
		auto a_s = static_cast<const PScene*>(GetSceneMgr());

		m_fitness += a_s->m_nest->GetGoodFoodsCollected() * m_awards.Goal;
		m_fitness -= a_s->m_nest->GetBadFoodsCollected() * m_awards.Goal;

		for(auto node : *a_s->m_food_list) {
			auto const& pos_n = GetNodePosition(node);
			auto const& pos_o = m_original_position[node];

			float32 dist_n = pos_n.Length();
			float32 dist_o = pos_o.Length();

			int32 flag = static_cast<assa2d::Object*>(node)->GetBody()->GetFixtureList()->GetShape()->m_radius>2.5f ? 1 : 0;
			if(dist_n < dist_o) {
				m_fitness += flag * m_awards.DistanceMoved * (dist_o - dist_n) / dist_o;
			}
		}
	};

	/// Calculate contact awards.
	virtual void PreSolve(const b2Contact* contact, const b2Manifold* oldManifold) override
	{
		const b2Body* bA = contact->GetFixtureA()->GetBody();
		const b2Body* bB = contact->GetFixtureB()->GetBody();
		assa2d::Node* nA = static_cast<assa2d::Node*>(bA->GetUserData());
		assa2d::Node* nB = static_cast<assa2d::Node*>(bB->GetUserData());

		std::size_t tagA = nA->GetTag();
		std::size_t tagB = nB->GetTag();

		assa2d::Node_Type ntA = nA->GetType();
		assa2d::Node_Type ntB = nB->GetType();

		if(tagA == MAKE_TAG('f', 'o', 'o', 'd') && ntB == assa2d::Node_Type::Actor_Component) {
			int32 flag = static_cast<assa2d::Object*>(nA)->GetBody()->GetFixtureList()->GetShape()->m_radius>2.5f ? 1 : 0;

			m_fitness += flag* m_awards.Contact;
		}

		if(tagB == MAKE_TAG('f', 'o', 'o', 'd') && ntA == assa2d::Node_Type::Actor_Component) {
			int32 flag = static_cast<assa2d::Object*>(nB)->GetBody()->GetFixtureList()->GetShape()->m_radius>2.5f ? 1 : 0;

			m_fitness += flag* m_awards.Contact;
		}
	}

private:
	PAward m_awards;
	float32 m_fitness;

	std::map<assa2d::Node*, b2Vec2> m_original_position;
};

#endif /* TESTS_POISONFOOD_PMONITOR_H_ */
