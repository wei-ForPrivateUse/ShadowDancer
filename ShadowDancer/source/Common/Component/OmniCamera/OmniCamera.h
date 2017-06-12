/*
 * OmniCamera.h
 *
 *  Created on: Jun 4, 2017
 *      Author: wei
 */

#ifndef COMPONENT_OMNICAMERA_H_
#define COMPONENT_OMNICAMERA_H_

#include <type_traits>
#include <tuple>

#include <assassin2d/assassin2d.h>



template<typename... _Tpls>
class OmniCamera final : public assa2d::Component {
public:
	struct Configuration : public assa2d::Component::Configuration {
		std::size_t OutputStartIndex;
	};

	OmniCamera(Configuration* conf, typename _Tpls::Configuration... ob_confs) :
			assa2d::Component(conf), m_observers(ob_confs...) {
		m_output_start_index = conf->OutputStartIndex;
	}
	virtual ~OmniCamera() { }

protected:
	virtual void Act() override {


	}

	template<std::size_t _Index>
	void _M_GetReport() {
		auto const& observer = std::get<_Index>(m_observers);
		auto const& report = observer.Report();


	}

	template<std::size_t _Index>
	void _M_SetOutput() {

	}

private:
	std::size_t m_output_start_index;

	std::tuple<_Tpls...> m_observers;
};

#endif /* COMPONENT_OMNICAMERA_H_ */
