/*
 * PScene.h
 *
 *  Created on: Mar 2, 2017
 *      Author: wei
 */

#ifndef TESTS_POISONFOOD_PSCENE_H_
#define TESTS_POISONFOOD_PSCENE_H_

#include "Common/Object/Block.h"
#include "Common/Object/Wall.h"
#include "PRobot.h"
#include "PNest.h"

/// Sample scene.
class PScene : public assa2d::SceneMgr {
public:
	PScene(Configuration* conf, ANNWeights* weights);
	virtual ~PScene() { }

	const std::list<assa2d::Node*>*  m_food_list;
	PNest* m_nest;
};

#endif /* TESTS_POISONFOOD_PSCENE_H_ */
