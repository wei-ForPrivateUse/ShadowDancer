/*
 * FMonitor.h
 *
 *  Created on: Mar 4, 2017
 *      Author: wei
 */

#ifndef TESTS_SAMPLE_MONITOR_FMONITOR_H_
#define TESTS_SAMPLE_MONITOR_FMONITOR_H_

#include <assassin2d/assassin2d.h>

class FMonitor : public assa2d::Monitor , public assa2d::ContactListener {
public:
	FMonitor() {
		fitness = 0.0f;

		poison = -1.0f;
		food = 1.5f;
	}
	virtual ~FMonitor() { };

	float32 poison;
	float32 food;

	void f(bul::manager::SceneMgr* s) {
		auto a_s = static_cast<assa2d::SceneMgr*>(s);
		a_s->GetContactMgr().AddContactListener(this);
	}

	void Initialize() {
		auto a_s = static_cast<const assa2d::SceneMgr*>(GetSceneMgr());
		a_s->GetContactMgr().AddContactListener(this);
	};
	void Step() {};
	void Finalize() {};

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

		if(tagA == MAKE_TAG('p', 'o', 'i', 's') || tagB == MAKE_TAG('p', 'o', 'i', 's')) {
			if(ntA == assa2d::Node_Type::Actor_Component || ntB == assa2d::Node_Type::Actor_Component) {
				fitness += poison;
			}
		}


		if(tagA == MAKE_TAG('f', 'o', 'o', 'd') || tagB == MAKE_TAG('f', 'o', 'o', 'd')) {
			if(ntA == assa2d::Node_Type::Actor_Component || ntB == assa2d::Node_Type::Actor_Component) {
				fitness += food;
			}
		}
	}

	float32 fitness;
};

#endif /* TESTS_SAMPLE_MONITOR_FMONITOR_H_ */
