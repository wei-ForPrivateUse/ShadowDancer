/*
 * J1_T_Nest.cpp
 *
 *  Created on: Nov 24, 2017
 *      Author: wei
 */

#include "J1_T_Nest.h"
#include <iostream>

J1_T_Nest::J1_T_Nest(Configuration* conf) : assa2d::Trigger(conf) {
	// TODO Auto-generated constructor stub

}

J1_T_Nest::~J1_T_Nest() {
	// TODO Auto-generated destructor stub
}

void J1_T_Nest::Act() {
	if(GetSceneMgr()->CountNodesByTag(MAKE_TAG('p', 'a', 'c', 'k')) > 0) {
		auto const& package_list = GetSceneMgr()->GetNodesByTag(MAKE_TAG('p', 'a', 'c', 'k'));
		int i = 1;
		for(auto begin = package_list.begin(); begin != package_list.end();) {
			std::cout<<i<<" / "<< package_list.size();
			auto iter = begin;
			begin++;
			auto package = static_cast<J1_O_Package*>(*iter);
			if(package->m_current_touch >= package->m_min_step_touch) {
				package->m_required_touch -= std::min(package->m_current_touch, package->m_max_step_touch);
			}
			package->m_current_touch = 0;
			if(package->m_required_touch < 0) {
				std::cout<<"!!!!"<<std::endl;
				GetSceneMgr()->RemoveNode(package);
			}
			i++;
		}
	}
}
