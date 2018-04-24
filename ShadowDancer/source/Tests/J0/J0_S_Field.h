/*
 * J0_S_Field.h
 *
 *  Created on: Apr 20, 2018
 *      Author: wei
 */

#ifndef TESTS_J0_J0_S_FIELD_H_
#define TESTS_J0_J0_S_FIELD_H_

#include <cmath>

#include "Common/Object/Block.h"
#include "Common/Object/Wall.h"
#include "J0_A_Robot.h"
#include "J0_T_Nest.h"

class J0_S_Field : public assa2d::SceneMgr {
public:
	struct Configuration : assa2d::SceneMgr::Configuration {
		int TrainingMode = 0; 			// 0, 1, 2, 3.

		std::size_t Robot = 30;
		std::size_t Resource = 10;
		std::size_t Package = 5;
	};

	J0_S_Field(Configuration* conf, ANNWeights* arbi, ANNWeights* w1, ANNWeights* w2, ANNWeights* w3);
	virtual ~J0_S_Field() { }

public:
	// Nodes.
	std::vector<J0_A_Robot*> m_robot;

	J0_T_Nest* m_nest_resource;
	J0_T_Nest* m_nest_package;
};


#endif /* TESTS_J0_J0_S_FIELD_H_ */
