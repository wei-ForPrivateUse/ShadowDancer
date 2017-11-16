/*
 * J1_S_Field.h
 *
 *  Created on: Nov 16, 2017
 *      Author: wei
 */

#include "Common/Object/Block.h"
#include "Common/Object/Wall.h"
#include "J1_A_Robot.h"

#ifndef TESTS_J1_J1_S_FIELD_H_
#define TESTS_J1_J1_S_FIELD_H_

//
class J1_S_Field : public assa2d::SceneMgr {
public:
	J1_S_Field(Configuration* conf);
	virtual ~J1_S_Field() { }
};

#endif /* TESTS_J1_J1_S_FIELD_H_ */
