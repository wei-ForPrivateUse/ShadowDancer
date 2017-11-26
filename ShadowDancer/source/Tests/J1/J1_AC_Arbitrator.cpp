/*
 * J1_AC_Arbitrator.cpp
 *
 *  Created on: Nov 25, 2017
 *      Author: wei
 */

#include "J1_AC_Arbitrator.h"

J1_AC_Arbitrator::J1_AC_Arbitrator(Configuration* conf) : ANN(conf) {
	m_sub_controller_id = conf->SubControllerId;
	if(m_sub_controller_id.size() != conf->OutputIndex.size()) {
		throw std::logic_error("J1_AC_Arbitrator::J1_AC_Arbitrator(...): Output size does not fit sub controllers.");
	}
}

void J1_AC_Arbitrator::Act() {
	ANN::Act();

	std::size_t index = 0;
	float32 max_value = GetSharedData<float>(m_output_index[0]);
	for(std::size_t i = 0; i < m_output_index.size(); i++) {
		if(GetSharedData<float>(m_output_index[i]) > max_value) {
			index = i;
			max_value = GetSharedData<float>(m_output_index[i]);
		}
	}

	for(std::size_t i = 0; i < m_sub_controller_id.size(); i++) {
		if(i == index) {
			static_cast<assa2d::Component*>(GetActor()->GetComponentById(m_sub_controller_id[i]))->SetActive(true);
		} else {
			static_cast<assa2d::Component*>(GetActor()->GetComponentById(m_sub_controller_id[i]))->SetActive(false);
		}
	}
}
