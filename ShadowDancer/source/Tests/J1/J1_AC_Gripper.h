/*
 * J1_AC_Gripper.h
 *
 *  Created on: Nov 14, 2017
 *      Author: wei
 */

#ifndef TESTS_J1_J1_AC_GRIPPER_H_
#define TESTS_J1_J1_AC_GRIPPER_H_

#include <assassin2d/assassin2d.h>

class J1_AC_Gripper : public assa2d::Actor::Component {
public:
	J1_AC_Gripper();
	virtual ~J1_AC_Gripper();

protected:
	//
	virtual void Act() override;
};

#endif /* TESTS_J1_J1_AC_GRIPPER_H_ */
