/*
 * ANN.cpp
 *
 *  Created on: Mar 3, 2017
 *      Author: wei
 */

#include "ANN.h"

ANN::ANN(Configuration* conf) : assa2d::Component(conf) {
	_M_weights = nullptr;

	_M_input_index = conf->InputIndex;
	_M_output_index = conf->OutputIndex;
}

void ANN::Act() {
	for(std::size_t i = 0 ; i < _T_output_tmp.size(); i++) {
		std::vector<float32> current_res;
		current_res.resize(_T_output_tmp[i].size());
		for(std::size_t j = 0; j < _T_output_tmp[i].size(); j++) {
			current_res[j] = 0.0f;
			if(i == 0) {
				current_res[j] = GetSharedData<float>(_M_input_index[j]);
			} else {
				for(std::size_t k = 0; k < _T_output_tmp[i-1].size(); k++) {
					current_res[j] += _T_output_tmp[i-1][k] * _M_weights->ForwardWeights[i-1][k][j];
				}
				if(_M_weights->RecurrentEnabled[i]) {
					for(std::size_t k = 0; k < _T_output_tmp[i].size(); k++) {
						current_res[j] += _T_output_tmp[i][k] * _M_weights->RecurrentWeights[i][k][j];
					}
				}
				if(_M_weights->BiasEnabled[i]) {
					current_res[j] -= _M_weights->Bias[i][j];
				}
				current_res[j] = ActivationFunction(current_res[j]);
			}
		}
		_T_output_tmp[i] = current_res;
	}
	for(std::size_t r = 0; r < _T_output_tmp[_T_output_tmp.size()-1].size(); r++) {
		SetSharedData<float>(_M_output_index[r], _T_output_tmp[_T_output_tmp.size()-1][r]);
	}
}

void ANN::_COUT_Output() const {
	std::cout<<"********************************"<<std::endl;
	for(auto& i : _T_output_tmp) {
		for(auto j : i) {
			std::cout<<j<<", ";
		}
		std::cout<<std::endl;
	}
}
