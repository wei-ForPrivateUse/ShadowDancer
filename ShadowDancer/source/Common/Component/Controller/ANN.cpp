/*
 * ANN.cpp
 *
 *  Created on: Mar 3, 2017
 *      Author: wei
 */

#include "ANN.h"

ANN::ANN(Configuration* conf) : assa2d::Component(conf) {
	m_weights = nullptr;

	m_input_index = conf->InputIndex;
	m_output_index = conf->OutputIndex;
}

void ANN::Act() {
	for(std::size_t i = 0 ; i < t_output_tmp.size(); i++) {
		std::vector<float32> current_res;
		current_res.resize(t_output_tmp[i].size());
		for(std::size_t j = 0; j < t_output_tmp[i].size(); j++) {
			current_res[j] = 0.0f;
			if(i == 0) {
				current_res[j] = GetSharedData<float>(m_input_index[j]);
			} else {
				for(std::size_t k = 0; k < t_output_tmp[i-1].size(); k++) {
					current_res[j] += t_output_tmp[i-1][k] * m_weights->ForwardWeights[i-1][k][j];
				}
				if(m_weights->RecurrentEnabled[i]) {
					for(std::size_t k = 0; k < t_output_tmp[i].size(); k++) {
						current_res[j] += t_output_tmp[i][k] * m_weights->RecurrentWeights[i][k][j];
					}
				}
				if(m_weights->BiasEnabled[i]) {
					current_res[j] -= m_weights->Bias[i][j];
				}
				current_res[j] = ActivationFunction(current_res[j]);
			}
		}
		t_output_tmp[i] = current_res;
	}
	for(std::size_t r = 0; r < t_output_tmp[t_output_tmp.size()-1].size(); r++) {
		SetSharedData<float>(m_output_index[r], t_output_tmp[t_output_tmp.size()-1][r]);
	}
}

void ANN::_COUT_Output() const {
	std::cout<<"********************************"<<std::endl;
	for(auto& i : t_output_tmp) {
		for(auto j : i) {
			std::cout<<j<<", ";
		}
		std::cout<<std::endl;
	}
	std::cout<<"********************************"<<std::endl;
}
