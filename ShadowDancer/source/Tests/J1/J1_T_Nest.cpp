/*
 * J1_T_Nest.cpp
 *
 *  Created on: Nov 24, 2017
 *      Author: wei
 */

#include "J1_T_Nest.h"
#include <iostream>

J1_T_Nest::J1_T_Nest(Configuration* conf) : assa2d::Trigger(conf) {
	m_max_resource = conf->Resource;
	m_max_package = conf->Package;
	m_resource_supplement = conf->ResourceSupplement;
	m_package_supplement = conf->PackageSupplement;
	m_resource_mask = conf->ResourceMask;
	t_new_resource_id = conf->NewResourceId;
	t_new_package_id = conf->NewPackageId;
}

void J1_T_Nest::Act() {
	// Updates packages, see if there are some packages to be removed.
	if(GetSceneMgr()->CountNodesByTag(MAKE_TAG('p', 'a', 'c', 'k')) > 0) {
		// Get package list.
		auto const& package_list = GetSceneMgr()->GetNodesByTag(MAKE_TAG('p', 'a', 'c', 'k'));
		// Remove packages carefully (with iterator).
		auto end = package_list.end();
		for(auto begin = package_list.begin(); begin != end;) {
			auto iter = begin++;
			auto package = static_cast<J1_O_Package*>(*iter);
			// Updates m_required_touch and reset m_current_touch.
			if(package->m_current_touch >= package->m_min_step_touch) {
				package->m_required_touch -= std::min(package->m_current_touch, package->m_max_step_touch);
			}
			package->m_current_touch = 0;
			// Remove a package if m_required_touch < 0;
			if(package->m_required_touch < 0) {
				// Pre-calculate position and angle for resources
				std::vector
				GetSceneMgr()->RemoveNode(package);
				// Generate resources.

				// Regenerate package if policy is -1.
				if(m_package_supplement == -1) {
					J1_O_Package::Configuration pc;
					pc.Tag = MAKE_TAG('p', 'a', 'c', 'k');
					pc.StaticBody = true;
					pc.ShapeType = assa2d::ShapeType::Polygon;
					pc.PolygonShape.SetAsBox(1.5f, 2.0f);
					pc.Id = t_new_package_id++;
					float32 r = assa2d::RandomFloat(25.0f, 90.0f);
					float32 a = assa2d::RandomFloat(0, M_PI*2.0f);
					float32 x = r * std::cos(a);
					float32 y = r * std::sin(a);
					pc.Position.Set(x, y);
					pc.Angle = assa2d::RandomFloat(0, M_PI*2.0f);
					GetSceneMgr()->AddNode<J1_O_Package>(&pc);
				}
			}
		}
	}
}
