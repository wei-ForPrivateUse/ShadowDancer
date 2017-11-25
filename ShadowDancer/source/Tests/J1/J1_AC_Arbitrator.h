/*
 * J1_AC_Arbitrator.h
 *
 *  Created on: Nov 25, 2017
 *      Author: wei
 */

#ifndef TESTS_J1_J1_AC_ARBITRATOR_H_
#define TESTS_J1_J1_AC_ARBITRATOR_H_

#include <assassin2d/assassin2d.h>

#include "Common/Component/Controller/ANN.h"

class J1_AC_Arbitrator : public ANN {
public:
	struct Configuration : public ANN::Configuration {

	};

	J1_AC_Arbitrator(Configuration* conf);
	virtual ~J1_AC_Arbitrator();
};

#endif /* TESTS_J1_J1_AC_ARBITRATOR_H_ */
