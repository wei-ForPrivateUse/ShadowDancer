/*
 * J1_T_Nest.cpp
 *
 *  Created on: Nov 24, 2017
 *      Author: wei
 */

#include "J1_T_Nest.h"
#include <iostream>

J1_T_Nest::J1_T_Nest(Configuration* conf) : assa2d::Trigger(conf) {
	m_position = conf->Position;
	m_radius = conf->Radius;

	m_max_resource = conf->Resource;
	m_max_package = conf->Package;
	m_resource_supplement = conf->ResourceSupplement;
	m_package_supplement = conf->PackageSupplement;
	m_resource_mask = conf->ResourceMask;

	m_package_collected = 0;
	m_unmasked_resource_collected = 0;
	m_masked_resource_collected = 0;

	m_new_resource_id = conf->NewResourceId;
	m_new_package_id = conf->NewPackageId;
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
				std::vector<b2Vec2> pos(12);
				for(int i = 0; i < 3; i++) {
					for(int j = 0; j < 4; j++) {
						b2Vec2 l_pos;
						l_pos.Set(i-1, j-1.5);
						pos[i*4+j] = package->GetBody()->GetWorldPoint(l_pos);
					}
				}
				// Remove this package.
				GetSceneMgr()->RemoveNode(package);
				// Count this package.
				m_package_collected++;
				// Generate resources.
				AddMaskedResources(pos);
				// Regenerate package if policy is -1.
				if(m_package_supplement == -1) {
					AddPackage();
				}
			}
		}
	}

	// Check resources, see if some have been moved into the nest.
	if(GetSceneMgr()->CountNodesByTag(MAKE_TAG('r', 'e', 's', 'o')) > 0) {
		// Get resource list.
		auto const& resource_list = GetSceneMgr()->GetNodesByTag(MAKE_TAG('r', 'e', 's', 'o'));
		// Remove packages carefully (with iterator).
		auto end = resource_list.end();
		for(auto begin = resource_list.begin(); begin != end;) {
			auto iter = begin++;
			auto resource = static_cast<Block*>(*iter);
			// Remove this resource when it is in the nest
			if(IsInNest(resource->GetPosition())) {
				unsigned int mask = resource->GetMask() & m_resource_mask;
				GetSceneMgr()->RemoveNode(resource);
				if(mask != m_resource_mask) {
					m_unmasked_resource_collected++;
					// Regenerate resource if policy is -1, in the case of unmasked resource.
					if(m_resource_supplement == -1) {
						AddUnmaskedResource();
					}
				} else {
					m_masked_resource_collected++;
				}
			}
		}
	}

	// Check the number of resources and packages regularly, regenerate if necessary.
	std::size_t package_count = GetSceneMgr()->CountNodesByTag(MAKE_TAG('p', 'a', 'c', 'k'));
	if(m_package_supplement>0 && package_count<m_max_package) {
		if(GetSceneMgr()->GetCurrentStep() % m_package_supplement == 0) {
			AddPackage();
		}
	}

	std::size_t count = GetSceneMgr()->CountNodesByTag(MAKE_TAG('r', 'e', 's', 'o'));
	if(count > 0) {
		for(auto resource : GetSceneMgr()->GetNodesByTag(MAKE_TAG('r', 'e', 's', 'o'))) {
			unsigned int mask = static_cast<Block*>(resource)->GetMask() & m_resource_mask;
			if(mask == m_resource_mask) {
				count--;
			}
		}
	}
	if(m_resource_supplement>0 && count<m_max_resource) {
		if(GetSceneMgr()->GetCurrentStep() % m_resource_supplement == 0) {
			AddUnmaskedResource();
		}
	}
}

void J1_T_Nest::AddPackage() {
	J1_O_Package::Configuration pc;
	pc.Tag = MAKE_TAG('p', 'a', 'c', 'k');
	pc.StaticBody = true;
	pc.ShapeType = assa2d::ShapeType::Polygon;
	pc.PolygonShape.SetAsBox(1.5f, 2.0f);
	pc.Id = m_new_package_id++;
	float32 r = assa2d::RandomFloat(25.0f, 90.0f);
	float32 a = assa2d::RandomFloat(0, M_PI*2.0f);
	float32 x = r * std::cos(a);
	float32 y = r * std::sin(a);
	pc.Position.Set(x, y);
	pc.Angle = assa2d::RandomFloat(0, M_PI*2.0f);
	GetSceneMgr()->AddNode<J1_O_Package>(&pc);
}

void J1_T_Nest::AddUnmaskedResource() {
	Block::Configuration bc;
	bc.Tag = MAKE_TAG('r', 'e', 's', 'o');
	bc.CircleShape.m_radius = 0.4f;
	bc.GroundFrictionForce = 5.0f;
	bc.GroundFrictionTorque = 5.0f;
	bc.Id = m_new_resource_id++;
	float32 r = assa2d::RandomFloat(20.0f, 95.0f);
	float32 a = assa2d::RandomFloat(0, M_PI*2.0f);
	float32 x = r * std::cos(a);
	float32 y = r * std::sin(a);
	bc.Position.Set(x, y);
	GetSceneMgr()->AddNode<Block>(&bc);
}

void J1_T_Nest::AddMaskedResources(std::vector<b2Vec2> const& pos) {
	Block::Configuration bc;
	bc.Tag = MAKE_TAG('r', 'e', 's', 'o');
	bc.CircleShape.m_radius = 0.4f;
	bc.GroundFrictionForce = 5.0f;
	bc.GroundFrictionTorque = 5.0f;
	bc.Mask = m_resource_mask;
	for(auto & p : pos) {
		bc.Id = m_new_resource_id++;
		bc.Position = p;
		GetSceneMgr()->AddNode<Block>(&bc);
	}
}
