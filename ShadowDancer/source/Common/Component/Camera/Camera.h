/*
 * Camera.h
 *
 *  Created on: Jun 4, 2017
 *      Author: wei
 */

#ifndef COMMON_COMPONENT_CAMERA_CAMERA_H_
#define COMMON_COMPONENT_CAMERA_CAMERA_H_

#include <type_traits>
#include <stdexcept>
#include <vector>
#include <set>

#include <assassin2d/assassin2d.h>

/// A camera provides visual information
template<typename _Tp>
class Camera final : public assa2d::Component {
public:
	struct Configuration {
		std::pair<std::size_t, std::size_t> OutputIndexInterval = {0, 0};

	};

	Camera(Configuration* conf) : assa2d::Component(conf) { }
	virtual ~Camera() { }

protected:
	///
	virtual void Act() override {
		for(auto observer : m_observer_list) {
			auto const& result_vec = observer->Report();
			std::size_t index = observer->GetStartIndex();
			for(auto result : result_vec) {
				SetSharedData<_Tp>(index, result);
				index++;
			}
		}
	}

private:

};
































///////////////////////////////////////////////////////////////////////
/// Forward-declaration.
template<typename>
class OmniCamera;

/// An observer return std::vector<_Tp> format information to the omni-camera.
template<typename _Tp>
class Observer {
public:
	struct Configuration {
		std::size_t StartIndex = 0;

		OmniCamera<_Tp>* Parent = nullptr;
	};

	Observer(Configuration* conf) : m_omnicamera(conf->Parent) {
		m_start_index = conf->StartIndex;
	}
	virtual ~Observer() { }

	/// Getters.
	std::size_t GetStartIndex() const {
		return m_start_index;
	}

	OmniCamera<_Tp>* GetOmniCamera() {
		return m_omnicamera;
	}

	const OmniCamera<_Tp>* GetOmniCamera() const {
		return m_omnicamera;
	}

	/// Setter.
	void SetStartIndex(std::size_t index) {
		m_start_index = index;
	}


protected:
	/// Report to the omnicamera at each timestep.
	virtual std::vector<_Tp> Report() = 0;

private:
	template<typename>
	friend class OmniCamera;

	std::size_t m_start_index;

	OmniCamera<_Tp>* const m_omnicamera;
};

/// An omni-camera uses observers to provide
template<typename _Tp>
class OmniCamera final : public assa2d::Component {
public:
	typedef typename assa2d::Component::Configuration Configuration;

	OmniCamera(Configuration* conf) : assa2d::Component(conf) { }

	/// Release all observers.
	virtual ~OmniCamera() {
		for(auto observer : m_observer_list) {
			delete observer;
		}
		m_observer_list.clear();
	}

	/// Add a new observer.
	template<typename _Ob_Tp>
	_Ob_Tp* AddObserver(typename _Ob_Tp::Configuration* conf) {
		static_assert(std::is_base_of<Observer<_Tp>, _Ob_Tp>::value,
				"OmniCamera::AddObserver(...): Type '_Ob_Tp' must be a derived type of Observer<_Tp>.");

		conf->Parent = this;

		_Ob_Tp* observer = new _Ob_Tp(conf);
		m_observer_list.insert(observer);

		return observer;
	}

	/// Remove an observer if it exists.
	void RemoveObserver(Observer<_Tp>* observer) {
		if(!m_observer_list.count(observer)) {
			throw std::out_of_range("OmniCamera::RemoveObserver(...): observer does not exist.");
		}

		m_observer_list.erase(observer);
		delete observer;
	}

protected:
	/// Call each observer at each timestep.
	virtual void Act() override {
		for(auto observer : m_observer_list) {
			auto const& result_vec = observer->Report();
			std::size_t index = observer->GetStartIndex();
			for(auto result : result_vec) {
				SetSharedData<_Tp>(index, result);
				index++;
			}
		}
	}

private:
	std::set<Observer<_Tp>*> m_observer_list;
};

#endif /* COMMON_COMPONENT_CAMERA_CAMERA_H_ */
