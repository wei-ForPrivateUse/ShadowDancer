/*
 * ANN.h
 *
 *  Created on: Mar 3, 2017
 *      Author: wei
 */

#ifndef COMMON_COMPONENT_CONTROLLER_ANN_H_
#define COMMON_COMPONENT_CONTROLLER_ANN_H_

#include <vector>
#include <random>
#include <iostream>
#include <functional>

#include <assassin2d/assassin2d.h>

/// ANN weights.
struct ANNWeights {
	ANNWeights(std::vector<std::size_t> const& node_number, std::vector<bool> const& recurrent, std::vector<bool> const& bias,
			bool randomize = false, float32 weightlowerboundary = -1.0f, float32 weightupperboundary = 1.0f,
				float32 biaslowerboundary = -0.5f, float32 biasupperboundary = 0.5f) {
		if(node_number.size() < 2) {
			throw std::runtime_error("ANNWeights::ANNWeights(...) : node_number must be at least 2 (input + output).");
		}
		if(node_number.size() != bias.size()) {
			throw std::runtime_error("ANNWeights::ANNWeights(...) : ill-formated bias.");
		}
		if(node_number.size() != recurrent.size()) {
			throw std::runtime_error("ANNWeights::ANNWeights(...) : ill-formated recurrent.");
		}
		if(weightlowerboundary > weightupperboundary || biaslowerboundary > biasupperboundary) {
			throw std::runtime_error("ANNWeights::ANNWeights(...) : invalid boundaries.");
		}

		WeightLowerBoundary = weightlowerboundary;
		WeightUpperBoundary = weightupperboundary;
		BiasLowerBoundary = biaslowerboundary;
		BiasUpperBoundary = biasupperboundary;

		ForwardWeights.resize(node_number.size() - 1);
		for(std::size_t i = 0; i < ForwardWeights.size(); i++) {
			ForwardWeights[i].resize(node_number[i]);
			for(std::size_t j = 0; j < ForwardWeights[i].size(); j++) {
				ForwardWeights[i][j].resize(node_number[i+1]);
			}
		}

		RecurrentWeights.resize(node_number.size());
		for(std::size_t i = 0; i < RecurrentWeights.size(); i++) {
			RecurrentWeights[i].resize(node_number[i]);
			for(std::size_t j = 0; j < RecurrentWeights[i].size(); j++) {
				RecurrentWeights[i][j].resize(node_number[i]);
			}
		}

		Bias.resize(node_number.size());
		for(std::size_t i = 0; i < Bias.size(); i++) {
			Bias[i].resize(node_number[i]);
		}

		RecurrentEnabled = recurrent;
		BiasEnabled = bias;

		if(randomize) {
			Randomize();
		} else {
			SetAverage();
		}
	}
	~ANNWeights() { }

	/// Randomize with default boundaries.
	void Randomize() {
		Randomize(WeightLowerBoundary, WeightUpperBoundary, BiasLowerBoundary, BiasUpperBoundary);
	}

	/// Randomize with new boundaries.
	void Randomize(float32 weightlowerboundary, float32 weightupperboundary, float32 biaslowerboundary, float32 biasupperboundary) {
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<float32> weight_dis(weightlowerboundary, weightupperboundary);
		std::uniform_real_distribution<float32> bias_dis(biaslowerboundary, biasupperboundary);

		for(auto& i : ForwardWeights) {
			for(auto& j : i) {
				for(auto& k : j) {
					k = weight_dis(gen);
				}
			}
		}

		for(auto& i : RecurrentWeights) {
			for(auto& j : i) {
				for(auto& k : j) {
					k = weight_dis(gen);
				}
			}
		}

		for(auto& i : Bias) {
			for(auto& j : i) {
				j = bias_dis(gen);
			}
		}
	}

	/// Set all weights to average value.
	void SetAverage() {
		for(auto& i : ForwardWeights) {
			for(auto& j : i) {
				for(auto& k : j) {
					k = (WeightLowerBoundary + WeightUpperBoundary) / 2.0f;
				}
			}
		}

		for(auto& i : RecurrentWeights) {
			for(auto& j : i) {
				for(auto& k : j) {
					k = (WeightLowerBoundary + WeightUpperBoundary) / 2.0f;
				}
			}
		}

		for(auto& i : Bias) {
			for(auto& j : i) {
				j = (BiasLowerBoundary + BiasUpperBoundary) / 2.0f;
			}
		}
	}

	/// Set weights with array.
	void Set(double weights[]) {
		int index = 0;
		for(std::size_t i = 0; i < ForwardWeights.size(); i++) {
			for(std::size_t j = 0; j < ForwardWeights[i].size(); j++) {
				for(std::size_t k = 0; k < ForwardWeights[i][j].size(); k++) {
					ForwardWeights[i][j][k] = _CheckValue(weights[index++], WeightLowerBoundary, WeightUpperBoundary);
				}
			}
		}

		for(std::size_t i = 0; i < RecurrentWeights.size(); i++) {
			if(!RecurrentEnabled[i]) {
				continue;
			}
			for(std::size_t j = 0; j < RecurrentWeights[i].size(); j++) {
				for(std::size_t k = 0; k < RecurrentWeights[i][j].size(); k++) {
					RecurrentWeights[i][j][k] = _CheckValue(weights[index++], WeightLowerBoundary, WeightUpperBoundary);
				}
			}
		}

		for(std::size_t i = 0; i < Bias.size(); i++) {
			if(!BiasEnabled[i]) {
				continue;
			}
			for(std::size_t j = 0; j < Bias[i].size(); j++) {
				Bias[i][j] = _CheckValue(weights[index++], BiasLowerBoundary, BiasUpperBoundary);
			}
		}
	}

	/// Getters.
	std::size_t GetLayerCount() const {
		return RecurrentEnabled.size();
	}

	std::size_t GetNodeNumber(std::size_t layer) const {
		return RecurrentWeights[layer].size();
	}

	/// Check boundaries.
	float32 _CheckValue(float32 value, float32 lowerboundary, float32 upperboundary) {
		value = value > upperboundary ? upperboundary : value;
		value = value < lowerboundary ? lowerboundary : value;
		return value;
	}

	/// Output weights.
	void _COUT_Output() const {
		std::cout<<"Layers: "<<RecurrentWeights.size()<<" -> {";
		for(auto const& i : RecurrentWeights) {
			std::cout<<i.size()<<", ";
		}
		std::cout<<"*end*}"<<std::endl;

		std::cout<<"Is recurrent? -> {";
		for(auto i : RecurrentEnabled) {
			std::cout<<i<<", ";
		}
		std::cout<<"*end*}"<<std::endl;

		std::cout<<"WLB, WUB, BLB, BUB -> "<<WeightLowerBoundary<<", "<<WeightUpperBoundary<<", "<<
				BiasLowerBoundary<<", "<<BiasUpperBoundary<<std::endl;

		std::cout<<"ForwardWeights: "<<std::endl;
		for(auto& i : ForwardWeights) {
			for(auto& j : i) {
				for(auto& k : j) {
					std::cout<<k<<", ";
				}
				std::cout<<std::endl;
			}
			std::cout<<std::endl;
		}

		std::cout<<"RecurrentWeights: "<<std::endl;
		for(auto& i : RecurrentWeights) {
			for(auto& j : i) {
				for(auto& k : j) {
					std::cout<<k<<", ";
				}
				std::cout<<std::endl;
			}
			std::cout<<std::endl;
		}

		std::cout<<"Bias: "<<std::endl;
		for(auto& i : Bias) {
			for(auto& j : i) {
				std::cout<<j<<", ";
			}
			std::cout<<std::endl;
		}
	}

	float32 WeightLowerBoundary;
	float32 WeightUpperBoundary;
	float32 BiasLowerBoundary;
	float32 BiasUpperBoundary;

	std::vector<std::vector<std::vector<float32>>> ForwardWeights;
	std::vector<std::vector<std::vector<float32>>> RecurrentWeights;
	std::vector<bool> RecurrentEnabled;
	std::vector<std::vector<float32>> Bias;
	std::vector<bool> BiasEnabled;
};

/// FF-ANN controller.
class ANN : public assa2d::Component {
public:
	struct Configuration : public assa2d::Component::Configuration {
		std::vector<std::size_t> InputIndex;
		std::vector<std::size_t> OutputIndex;
	};

	ANN(Configuration* conf);
	virtual ~ANN() { }

	/// Set weights.
	void SetWeights(ANNWeights* weights);

	/// Output temporary calculation results.
	void _COUT_Output() const;

protected:
	/// Calculate outputs.
	virtual void Act() override;

	/// Logistic activation function
	float32 ActivationFunction(float32 sum) const;

protected:
	std::vector<std::size_t> m_input_index;
	std::vector<std::size_t> m_output_index;

private:
	ANNWeights* m_weights;

	std::vector<std::vector<float32>> t_output_tmp;
};

inline void ANN::SetWeights(ANNWeights* weights) {
	m_weights = weights;

	if(weights->GetNodeNumber(0) != m_input_index.size() || weights->GetNodeNumber(weights->GetLayerCount()-1) != m_output_index.size()) {
		throw std::runtime_error("ANN::SetWeights(...) : ill-formated weights.");
	}

	t_output_tmp.resize(weights->GetLayerCount());
	for(std::size_t i = 0; i < weights->GetLayerCount(); i ++) {
		t_output_tmp[i].resize(weights->GetNodeNumber(i));
	}

	for(auto& i : t_output_tmp) {
		for(auto& j : i) {
			j = 0.0f;
		}
	}
}

inline float32 ANN::ActivationFunction(float32 sum) const {
	return -1.0f + 2.0f / (1.0f + expf(-sum));
}

#endif /* COMMON_COMPONENT_CONTROLLER_ANN_H_ */
