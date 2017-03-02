/*
 * Robot.h
 *
 *  Created on: Mar 2, 2017
 *      Author: wei
 */

#ifndef OBJECT_ROBOT_H_
#define OBJECT_ROBOT_H_

#include "../Component/MainBody.h"
#include "../Component/Motor.h"

class Robot : public assa2d::Actor {
public:
	struct Configuration : public assa2d::Actor::Configuration {

	};

	Robot(Configuration* conf);
	virtual ~Robot();

	Motor* m1, *m2;
	MainBody* mb;
};

#endif /* OBJECT_ROBOT_H_ */
