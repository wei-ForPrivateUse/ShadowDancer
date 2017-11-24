/*
 * J1_T_Nest.h
 *
 *  Created on: Nov 24, 2017
 *      Author: wei
 */

#ifndef TESTS_J1_J1_T_NEST_H_
#define TESTS_J1_J1_T_NEST_H_

#include <assassin2d/assassin2d.h>

#include "J1_O_Package.h"

class J1_T_Nest : public assa2d::Trigger {
public:
	struct Configuration : public assa2d::Trigger::Configuration {

	};

	J1_T_Nest(Configuration* conf);
	virtual ~J1_T_Nest();

protected:
	virtual void Act() override;

private:

};

#endif /* TESTS_J1_J1_T_NEST_H_ */
