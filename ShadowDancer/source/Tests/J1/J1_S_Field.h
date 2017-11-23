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

#ifndef TESTS_J1_J1_S_FIELD_H_
#define TESTS_J1_J1_S_FIELD_H_

//
class J1_S_Field : public assa2d::SceneMgr {
public:
	struct Configuration : assa2d::SceneMgr::Configuration {
		std::size_t MaxResource = 60;
		std::size_t MaxPackage = 10;
		int ResourceSupplement = -1;
		int PackageSupplement = -1;
	};

	J1_S_Field(Configuration* conf);
	virtual ~J1_S_Field() { }

	// Nodes.
	J1_A_Robot* m_robot[50];


	/////////////////////////////
	std::size_t m_max_resource;
	std::size_t m_max_package;
	int m_resource_supplement;
	int m_package_supplement;
	/////////////////////////////
};

#endif /* TESTS_J1_J1_S_FIELD_H_ */
