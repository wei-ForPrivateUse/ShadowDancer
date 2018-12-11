/*
 * J0_S_Field_S.h
 *
 *  Created on: Apr 20, 2018
 *      Author: wei
 */

#ifndef TESTS_J0_J0_S_FIELD_S_F_TOP_H_
#define TESTS_J0_J0_S_FIELD_S_F_TOP_H_

#include <cmath>

#include "Common/Object/Block.h"
#include "Common/Object/Wall.h"
#include "J0_A_Robot_S.h"
#include "J0_T_Nest.h"

class J0_S_Field_S_F_top : public assa2d::SceneMgr {
public:
	struct Configuration : assa2d::SceneMgr::Configuration {
		int TrainingMode = 0; 			// -2, -1, 0, 1, 2, 3.

		std::size_t Robot = 30;
		std::size_t Resource = 10;
		std::size_t Package = 5;

		int robust_test = 0;
	};

	J0_S_Field_S_F_top(Configuration* conf, ANNWeights* wa_a, ANNWeights* wa_d);
	virtual ~J0_S_Field_S_F_top() { }

public:
	// Nodes.
	std::vector<J0_A_Robot_S*> m_robot;

	J0_T_Nest* m_nest_resource;
	J0_T_Nest* m_nest_package;

	int robust_test;

protected:
	virtual void PreStep() override {
		if(GetCurrentStep() == 1500) {
			std::vector<int> vec;
			for(int i = 0; i < m_robot.size(); i++) {
				vec.push_back(i);
			}
			std::random_device seed_gen;
			std::mt19937 eng(seed_gen());
			std::shuffle(vec.begin(), vec.end(), eng);
			for(int i = 0; i < robust_test; i++) {
				m_robot[vec[i]]->m_gripper->SetActive(false);
				m_robot[vec[i]]->SetActive(false);
			}


		}
	}
};


#endif /* TESTS_J0_J0_S_FIELD_S_F_TOP_H_ */
