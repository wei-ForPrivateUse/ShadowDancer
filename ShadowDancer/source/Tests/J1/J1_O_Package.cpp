/*
 * J1_O_Package.cpp
 *
 *  Created on: Nov 24, 2017
 *      Author: wei
 */

#include "J1_O_Package.h"
#include "J1_A_Robot.h"

J1_O_Package::J1_O_Package(Configuration* conf) : Block(conf) {
	m_target_tag = conf -> TargetTag;
	m_target_robot_mode = conf -> TargetRobotMode;

	m_min_step_touch = conf -> MinStepTouch;
	m_max_step_touch = conf -> MaxStepTouch;
	m_required_touch = conf -> RequiredTouch;

	m_current_touch = 0;
}

void J1_O_Package::PreSolve(Node* node, b2Contact* contact, const b2Manifold* oldManifold) {
	if(node->GetType()==bul::dynamics::Node_Type::Actor_Component && node->GetTag()==m_target_tag) {
		auto robot = static_cast<J1_A_Robot*>(static_cast<assa2d::Component*>(node)->GetActor());
		if(robot->GetMode() == m_target_robot_mode) {
			m_current_touch++;
		}
	}
}
