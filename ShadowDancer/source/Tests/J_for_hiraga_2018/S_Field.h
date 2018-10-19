/*
 * S_Field.h
 *
 *  Created on: Oct 4, 2018
 *      Author: wei
 */

#ifndef TESTS_J_FOR_HIRAGA_2018_S_FIELD_H_
#define TESTS_J_FOR_HIRAGA_2018_S_FIELD_H_

#include <cmath>

#include "Common/Object/Block.h"
#include "Common/Object/Wall.h"

#include "A_Robot.h"
#include "T_Nest.h"

class S_Field : public assa2d::SceneMgr {
public:
	struct Configuration : assa2d::SceneMgr::Configuration {
		std::size_t Robot = 50;
		std::size_t Food = 4;
		std::size_t Poison = 4;

		float32 FoodRadius = 5.0f;
		float32 PoisonRadius = 2.5f;
		float32 FoodDensity = 0.12f;
		float32 PoisonDensity = 0.48f;

		// for each robot
		int IRSensorNumber = 8;
		int OMNIRobotNumber = 2;
		int OMNIResourceNumber =2;

		float32 IRRange = 3.0f;
		float32 OMNIRange = 15.0f;
	};

	S_Field(Configuration* conf, ANNWeights* w);
	virtual ~S_Field() { }

public:
	// Nodes.
	std::vector<A_Robot*> m_robot;

	T_Nest* m_nest;
};
#endif /* TESTS_J_FOR_HIRAGA_2018_S_FIELD_H_ */
