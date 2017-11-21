/*
 * Camera.h
 *
 *  Created on: Jun 4, 2017
 *      Author: wei
 */

#ifndef COMMON_COMPONENT_CAMERA_CAMERA_H_
#define COMMON_COMPONENT_CAMERA_CAMERA_H_

#include <stdexcept>
#include <vector>

#include <assassin2d/assassin2d.h>

/// A camera provides visual information
template<typename _Tp>
class Camera : public assa2d::Component {
public:
	struct Configuration : assa2d::Component::Configuration {
		std::pair<std::size_t, std::size_t> OutputIndexInterval = {0, 0};
	};

	Camera(Configuration* conf) : assa2d::Component(conf) {
		m_output_index_interval = conf->OutputIndexInterval;
	}
	virtual ~Camera() { }

protected:
	/// Report outputs.
	virtual std::vector<_Tp> Report() = 0;

	/// Set shared data exactly in [m_output_index_interval.first, m_output_index_interval.second].
	virtual void Act() override {
		auto const& result_vec = Report();
		if(result_vec.size() != m_output_index_interval.second-m_output_index_interval.first+1) {
			throw std::logic_error("Camera::Report(...): Output size does not fit.");
		}
		std::size_t index = m_output_index_interval.first;
		for(auto result : result_vec) {
			SetSharedData<_Tp>(index, result);
			index++;
		}
	}

private:
	std::pair<std::size_t, std::size_t> m_output_index_interval;
};

#endif /* COMMON_COMPONENT_CAMERA_CAMERA_H_ */
