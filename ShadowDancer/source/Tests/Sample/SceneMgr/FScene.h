/*
 * FScene.h
 *
 *  Created on: Mar 2, 2017
 *      Author: wei
 */

#ifndef TESTS_SAMPLE_SCENEMGR_FSCENE_H_
#define TESTS_SAMPLE_SCENEMGR_FSCENE_H_

#include "../../../Common/Object/Block.h"
#include "../../../Common/Object/Wall.h"
#include "../Actor/Robot.h"

/// Sample scene.
class FScene : public assa2d::SceneMgr {
public:
	FScene(Configuration* conf, ANNWeights* weights);
	virtual ~FScene() { }
};

#endif /* TESTS_SAMPLE_SCENEMGR_FSCENE_H_ */
