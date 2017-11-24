/*
 * J1_S_Field.h
 *
 *  Created on: Nov 16, 2017
 *      Author: wei
 */

#include <cmath>

#include "Common/Object/Block.h"
#include "Common/Object/Wall.h"
#include "J1_A_Robot.h"
#include "J1_O_Package.h"
#include "J1_T_Nest.h"

#ifndef TESTS_J1_J1_S_FIELD_H_
#define TESTS_J1_J1_S_FIELD_H_

//
class J1_S_Field : public assa2d::SceneMgr {
public:
	struct Configuration : assa2d::SceneMgr::Configuration {
		std::size_t MaxResource = 50;
		std::size_t MaxPackage = 1;
		int ResourceSupplement = -1;
		int PackageSupplement = -1;
	};

	J1_S_Field(Configuration* conf);
	virtual ~J1_S_Field() { }

	// Nodes.
	std::vector<J1_A_Robot*> m_robot;


	/////////////////////////////
	std::size_t m_max_resource;
	std::size_t m_max_package;
	int m_resource_supplement;
	int m_package_supplement;
	/////////////////////////////
};

#endif /* TESTS_J1_J1_S_FIELD_H_ */
