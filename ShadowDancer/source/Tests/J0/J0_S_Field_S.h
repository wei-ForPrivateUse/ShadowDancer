/*
 * J0_S_Field_S.h
 *
 *  Created on: Apr 20, 2018
 *      Author: wei
 */

#ifndef TESTS_J0_J0_S_FIELD_S_H_
#define TESTS_J0_J0_S_FIELD_S_H_

#include <cmath>

#include "Common/Object/Block.h"
#include "Common/Object/Wall.h"
#include "J0_A_Robot_S.h"
#include "J0_T_Nest.h"

class J0_S_Field_S : public assa2d::SceneMgr {
public:
	struct Configuration : assa2d::SceneMgr::Configuration {
		int TrainingMode = 0; 			// -2, -1, 0, 1, 2, 3.

		std::size_t Robot = 30;
		std::size_t Resource = 16;
		std::size_t Package = 8;
	};

	J0_S_Field_S(Configuration* conf, ANNWeights* wa_a, ANNWeights* wa_d);
	virtual ~J0_S_Field_S() { }

public:
	// Nodes.
	std::vector<J0_A_Robot_S*> m_robot;

	J0_T_Nest* m_nest_resource;
	J0_T_Nest* m_nest_package;
};


#endif /* TESTS_J0_J0_S_FIELD_S_H_ */
