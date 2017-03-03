/*
 * FMonitor.h
 *
 *  Created on: Mar 4, 2017
 *      Author: wei
 */

#ifndef MONITOR_FMONITOR_H_
#define MONITOR_FMONITOR_H_

#include <assassin2d.h>

class FMonitor : public assa2d::Monitor , public b2ContactListener {
public:
	FMonitor() {
		fitness = 0.0f;
	}
	virtual ~FMonitor() { };

	void Initialize() {
		auto b_s = const_cast<bul::manager::SceneMgr*>(GetSceneMgr());
		auto a_s = static_cast<assa2d::SceneMgr*>(b_s);
		a_s->GetContactMgr().AddContactListener(this);
	};
	void Step() {};
	void Finalize() {};

	virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
	{
		b2Body* bA = contact->GetFixtureA()->GetBody();
		b2Body* bB = contact->GetFixtureB()->GetBody();
		assa2d::Node* nA = static_cast<assa2d::Node*>(bA->GetUserData());
		assa2d::Node* nB = static_cast<assa2d::Node*>(bB->GetUserData());

		std::size_t idA = nA->GetId();
		std::size_t idB = nB->GetId();

		assa2d::Node_Type ntA = nA->GetType();
		assa2d::Node_Type ntB = nB->GetType();

		if(idA == 100 || idB == 100) {
			if(ntA == assa2d::Node_Type::Actor_Component || ntB == assa2d::Node_Type::Actor_Component) {
				fitness += 1.0f;
			}
		}

		if(idA == 101 || idB == 101) {
			if(ntA == assa2d::Node_Type::Actor_Component || ntB == assa2d::Node_Type::Actor_Component) {
				fitness -= 1.0f;
			}
		}
	}

	float32 fitness;
};

#endif /* MONITOR_FMONITOR_H_ */
