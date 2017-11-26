/*
 * J1_AC_Gripper.h
 *
 *  Created on: Nov 14, 2017
 *      Author: wei
 */

#ifndef TESTS_J1_J1_AC_GRIPPER_H_
#define TESTS_J1_J1_AC_GRIPPER_H_

#include <assassin2d/assassin2d.h>

class J1_AC_Gripper : public assa2d::Component {
public:
	struct Configuration : public assa2d::Component::Configuration {
		std::size_t TargetTag = 0;
		unsigned int TargetMask = 0;
	};

	J1_AC_Gripper(Configuration* conf);
	virtual ~J1_AC_Gripper();

protected:
	///
	virtual void Act() override { };


private:
	std::size_t m_target_tag;
	std::size_t m_target_mask;

	bool m_loaded;
};

#endif /* TESTS_J1_J1_AC_GRIPPER_H_ */
