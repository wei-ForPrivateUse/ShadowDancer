/*
 * J1_AC_Arbitrator.h
 *
 *  Created on: Nov 25, 2017
 *      Author: wei
 */

#ifndef TESTS_J_AROB_2018_J0_AC_ARBITRATOR_H_
#define TESTS_J_AROB_2018_J0_AC_ARBITRATOR_H_

#include <vector>
#include <stdexcept>

#include <assassin2d/assassin2d.h>

#include "Common/Component/Controller/ANN.h"

class J1_AC_Arbitrator : public ANN {
public:
	struct Configuration : public ANN::Configuration {
		std::vector<std::size_t> SubControllerId;
	};

	J1_AC_Arbitrator(Configuration* conf);
	virtual ~J1_AC_Arbitrator() { };

protected:
	/// Perform ANN::Act() and activate / deactivate sub controllers.
	virtual void Act() override;

private:
	std::vector<std::size_t> m_sub_controller_id;
};

#endif /* TESTS_J_AROB_2018_J0_AC_ARBITRATOR_H_ */
