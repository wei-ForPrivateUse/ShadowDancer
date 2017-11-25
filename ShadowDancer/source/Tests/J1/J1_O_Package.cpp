/*
 * J1_O_Package.cpp
 *
 *  Created on: Nov 24, 2017
 *      Author: wei
 */

#include "J1_O_Package.h"

J1_O_Package::J1_O_Package(Configuration* conf) : Block(conf) {
	m_target_tag = conf -> TargetTag;
	m_min_step_touch = conf -> MinStepTouch;
	m_max_step_touch = conf -> MaxStepTouch;
	m_required_touch = conf -> RequiredTouch;
	m_current_touch = 0;
}

void J1_O_Package::PreSolve(Node* node, b2Contact* contact, const b2Manifold* oldManifold) {
	// TODO verify robot mode
	if(node->GetType()==bul::dynamics::Node_Type::Actor_Component
			&& node->GetId()==0) {
		m_current_touch++;
	}
}
