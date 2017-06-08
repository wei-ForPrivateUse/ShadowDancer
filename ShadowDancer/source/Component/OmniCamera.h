/*
 * OmniCamera.h
 *
 *  Created on: Jun 4, 2017
 *      Author: wei
 */

#ifndef COMPONENT_OMNICAMERA_H_
#define COMPONENT_OMNICAMERA_H_

#include <vector>
#include <set>

#include <assassin2d/assassin2d.h>

template<typename...>
class OmniCamera;

template<typename... _Tpls>
class Observer {
public:
	Observer() { }
	virtual ~Observer() { }

	virtual void Report(std::size_t index) = 0;

protected:

private:
	std
};

template<typename... _Tpls>
class OmniCamera : public assa2d::Component {
public:
	struct Configuration : public assa2d::Component::Configuration {

	}
	OmniCamera(Configuration* conf);
	virtual ~OmniCamera();

protected:
	virtual void Act() override;

private:
	std::vector<std::size_t>
};

#endif /* COMPONENT_OMNICAMERA_H_ */
