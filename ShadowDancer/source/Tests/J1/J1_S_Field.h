/*
 * J1_S_Field.h
 *
 *  Created on: Nov 16, 2017
 *      Author: wei
 */

#include <cmath>

#include "Common/Object/Block.h"
#include "Common/Object/Wall.h"
#include "J1_A_Robot.h"
#include "J1_O_Package.h"
#include "J1_T_Nest.h"

#ifndef TESTS_J1_J1_S_FIELD_H_
#define TESTS_J1_J1_S_FIELD_H_

///
class J1_S_Field : public assa2d::SceneMgr {
public:
	struct Configuration : assa2d::SceneMgr::Configuration {
		int TrainingMode = 0; 			// 0, 1, 2, 3.

		std::size_t Robot = 50;			// Number of robots.

		// Nest parameters.
		std::size_t Resource = 30;		// Number of resources.
		std::size_t Package = 6;		// Number of packages.
		int ResourceSupplement = -1; 	// Policy for resource supplement, -1 means recreate immediately.
		int PackageSupplement = -1;		// Policy for package supplement, -1 means recreate immediately.

		// Package parameters.
		std::size_t MinStepTouch = 3;
		std::size_t MaxStepTouch = 6;
		std::size_t RequiredTouch = 1800;
	};

	J1_S_Field(Configuration* conf, ANNWeights* arbi, ANNWeights* w1, ANNWeights* w2, ANNWeights* w3);
	virtual ~J1_S_Field() { }

public:
	// Nodes.
	std::vector<J1_A_Robot*> m_robot;

	J1_T_Nest* m_nest;
};

#endif /* TESTS_J1_J1_S_FIELD_H_ */
