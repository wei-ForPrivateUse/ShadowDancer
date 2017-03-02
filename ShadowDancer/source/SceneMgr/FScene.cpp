/*
 * FScene.cpp
 *
 *  Created on: Mar 2, 2017
 *      Author: wei
 */

#include "FScene.h"

FScene::FScene(Configuration* conf) : assa2d::SceneMgr(conf) {
	Robot::Configuration rc;
	rc.Id = 1;

	AddNode<Robot>(&rc);

}

FScene::~FScene() {
	// TODO Auto-generated destructor stub
}

