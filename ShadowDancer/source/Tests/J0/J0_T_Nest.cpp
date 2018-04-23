/*
 * J0_T_Nest.cpp
 *
 *  Created on: Apr 20, 2018
 *      Author: wei
 */

#include "J0_T_Nest.h"
#include "Common/Object/Block.h"

J0_T_Nest::J0_T_Nest(Configuration* conf) : assa2d::Trigger(conf) {
	m_internal = conf->Internal;

	m_target_tag = conf->TargetTag;

	m_recreate = conf->recreate;

	count = 0;

	m_new_resource_id = conf->NewResourceID;
}

void J0_T_Nest::Act() {
	//check if target > 0
	if(GetSceneMgr()->CountNodesByTag(m_target_tag) > 0) {
		//get target list
		auto const& list = GetSceneMgr()->GetNodesByTag(m_target_tag);
		//perpare for removing
		auto end = list.end();
		for(auto begin = list.begin(); begin != end;) {
			auto iter = begin++;
			Block* node = static_cast<Block*>(*iter);
			//if the target is in the nest
			if(node->GetPosition().x>m_internal.x && node->GetPosition().x<m_internal.y) {
				count++;
				if(m_recreate) {
					std::vector<b2Vec2> pos(6);
					for(int i = 0; i < 2; i++) {
						for(int j = 0; j < 3; j++) {
							b2Vec2 l_pos;
							l_pos.Set(i*2.5-1.25, j*2.5-2.5);
							pos[i*3+j] = node->GetBody()->GetWorldPoint(l_pos);
						}
					}

					Block::Configuration bc;
					bc.Tag = MAKE_TAG('r', 'e', 's', 'o');
					bc.CircleShape.m_radius = 1.0f;
					bc.GroundFrictionForce = 3.0f;
					bc.GroundFrictionTorque = 3.0f;
					for(auto & p : pos) {
						bc.Id = m_new_resource_id++;
						bc.Position = p;
						GetSceneMgr()->AddNode<Block>(&bc);
					}
				}
				GetSceneMgr()->RemoveNode(node);
			}
		}
	}
}
