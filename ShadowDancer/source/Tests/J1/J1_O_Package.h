/*
 * J1_O_Package.h
 *
 *  Created on: Nov 24, 2017
 *      Author: wei
 */

#ifndef TESTS_J1_J1_O_PACKAGE_H_
#define TESTS_J1_J1_O_PACKAGE_H_

#include <assassin2d/assassin2d.h>

#include "Common/Object/Block.h"

class J1_T_Nest;

class J1_O_Package : public Block {
public:
	struct Configuration : public Block::Configuration {
		unsigned int TargetTag = MAKE_TAG('r', 'o', 'b', 'o');

		std::size_t MinStepTouch = 3;
		std::size_t MaxStepTouch = 6;
		std::size_t RequiredTouch = 1800;
	};

	J1_O_Package(Configuration* conf);
	virtual ~J1_O_Package() { };

//protected:
	virtual void PreSolve(Node* node, b2Contact* contact, const b2Manifold* oldManifold);

//private:
	friend class J1_T_Nest;

	unsigned int m_target_tag;

	std::size_t m_min_step_touch;
	std::size_t m_max_step_touch;

	long int m_required_touch;
	std::size_t m_current_touch;
};

#endif /* TESTS_J1_J1_O_PACKAGE_H_ */
