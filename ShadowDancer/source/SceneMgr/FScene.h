/*
 * FScene.h
 *
 *  Created on: Mar 2, 2017
 *      Author: wei
 */

#ifndef SCENEMGR_FSCENE_H_
#define SCENEMGR_FSCENE_H_

#include "../Actor/Robot.h"
#include "../Object/Wall.h"
#include "../Object/Block.h"

class FScene : public assa2d::SceneMgr {
public:
	FScene(Configuration* conf, ANNWeights* weights);
	virtual ~FScene();

	Robot* robot[30];
	Wall* wall[10];
	Block* block[5];
};

#endif /* SCENEMGR_FSCENE_H_ */
