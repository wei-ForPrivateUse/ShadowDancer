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

class FScene : public assa2d::SceneMgr {
public:
	FScene(Configuration* conf, ANNWeights* weights);
	virtual ~FScene() { }

	Robot* robot[30];
	Wall* wall[10];
	Block* block[5];
};

#endif /* TESTS_SAMPLE_SCENEMGR_FSCENE_H_ */
