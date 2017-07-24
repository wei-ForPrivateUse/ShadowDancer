/*
 * J1_Scene.h
 *
 *  Created on: Mar 2, 2017
 *      Author: wei
 */

#ifndef TESTS_J1_J1_SCENE_H_
#define TESTS_J1_J1_SCENE_H_

#include "Common/Object/Block.h"
#include "Common/Object/Wall.h"

///scene.
class J1_Scene : public assa2d::SceneMgr {
public:
	J1_Scene(Configuration* conf, ANNWeights* weights,
			std::pair<float32, float32> goodfood={4.0f, 0.4f}, std::pair<float32, float32> badfood={2.0f, 1.0f});
	virtual ~J1_Scene() { }

	const std::list<assa2d::Node*>*  m_food_list;
	PNest* m_nest;
};

#endif /* TESTS_J1_J1_SCENE_H_ */
