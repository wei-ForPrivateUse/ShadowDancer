/*
 * T_Nest.cpp
 *
 *  Created on: Oct 2, 2018
 *      Author: wei
 */

#include "Common/Object/Block.h"

#include "T_Nest.h""


T_Nest::T_Nest(Configuration* conf) : assa2d::Trigger(conf) {
	m_range = conf->Range;
	m_target_tag = conf->TargetTag;

	m_recreate = conf->Recreate;
	m_new_resource_id = conf->NewResourceID;

	poison_count = 0;
	food_count = 0;
}

void T_Nest::Act() {
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
			if(node->GetPosition().LengthSquared() < m_range*m_range) {
				unsigned int mark = node->GetFlag();
				if(mark==0) {		//0: food, 1: poison
					food_count++;

					Block::Configuration bc;
					bc.Tag = MAKE_TAG('r', 'e', 's', 'o');
					bc.CircleShape.m_radius = 3.0f;
					bc.Density = 0.7f;
					bc.Friction = 0.2f;
					bc.GroundFrictionForce = 1.0f;
					bc.GroundFrictionTorque = 2.0f;
					bc.Id = m_new_resource_id++;

					bc.Position = p;

					GetSceneMgr()->AddNode<Block>(&bc);
				} else {
					poison_count++;


				}
				if(m_recreate) {
					std::vector<b2Vec2> pos(7);
					pos[0] = node->GetBody()->GetWorldPoint(b2Vec2(0.0f, 0.0f));
					pos[1] = node->GetBody()->GetWorldPoint(b2Vec2(1.25f, 2.165f));
					pos[2] = node->GetBody()->GetWorldPoint(b2Vec2(-1.25f, 2.165f));
					pos[3] = node->GetBody()->GetWorldPoint(b2Vec2(-2.5f, 0.0f));
					pos[4] = node->GetBody()->GetWorldPoint(b2Vec2(-1.25f, -2.165f));
					pos[5] = node->GetBody()->GetWorldPoint(b2Vec2(1.25f, -2.165f));
					pos[6] = node->GetBody()->GetWorldPoint(b2Vec2(2.5f, 0.0f));

					Block::Configuration bc;
					bc.Tag = MAKE_TAG('r', 'e', 's', 'o');
					bc.CircleShape.m_radius = 1.0f;
					bc.Density = 0.7f;
					bc.Friction = 0.05f;
					bc.GroundFrictionForce = 1.0f;
					bc.GroundFrictionTorque = 2.0f;
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

