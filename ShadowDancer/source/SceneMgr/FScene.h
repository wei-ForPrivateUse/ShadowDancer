/*
 * FScene.h
 *
 *  Created on: Mar 2, 2017
 *      Author: wei
 */

#ifndef SCENEMGR_FSCENE_H_
#define SCENEMGR_FSCENE_H_

#include "../Actor/Robot.h"

class FScene : public assa2d::SceneMgr {
public:
	FScene(Configuration* conf);
	virtual ~FScene();


};

#endif /* SCENEMGR_FSCENE_H_ */
