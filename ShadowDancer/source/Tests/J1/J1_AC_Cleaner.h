/*
 * J1_AC_Cleaner.h
 *
 *  Created on: Nov 14, 2017
 *      Author: wei
 */

#ifndef TESTS_J1_J1_AC_CLEANER_H_
#define TESTS_J1_J1_AC_CLEANER_H_

#include <assassin2d/assassin2d.h>

class J1_AC_Cleaner : public assa2d::Component {
public:
	struct Configuration : public assa2d::Component::Configuration {

	};

	J1_AC_Cleaner(Configuration* conf);
	virtual ~J1_AC_Cleaner();

protected:
	//
	virtual void Act() override { };
};

#endif /* TESTS_J1_J1_AC_CLEANER_H_ */
