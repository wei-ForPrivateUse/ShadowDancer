/*
 * PNest.h
 *
 *  Created on: Jun 22, 2017
 *      Author: wei
 */

#ifndef TESTS_POISONFOOD_PNEST_H_
#define TESTS_POISONFOOD_PNEST_H_

#include <assassin2d/assassin2d.h>

#include "Common/Object/Block.h"
#include "Common/Common.h"

/// Collect and reproduce foods..
class PNest : public assa2d::Trigger {
public:
	struct Configuration : public assa2d::Trigger::Configuration {
		b2Vec2 LeftTop;
		b2Vec2 RightBottom;

		std::size_t TargetTag;
	};

	PNest(Configuration* conf) : assa2d::Trigger(conf) {
		m_lefttop = conf->LeftTop;
		m_rightbottom = conf->RightBottom;

		m_target_tag = conf->TargetTag;

		m_collected_good_food = 0;
		m_collected_bad_food = 0;

		m_cid = 1000000;
	}
	virtual ~PNest() { }

	/// Getters.
	int32 GetGoodFoodsCollected() const {
		return m_collected_good_food;
	}

	int32 GetBadFoodsCollected() const {
		return m_collected_bad_food;
	}

protected:
	/// Collect foods in the nest.
	virtual void Act() override {
		auto const& list = GetSceneMgr()->GetNodesByTag(m_target_tag);
		for(auto iter = list.begin(); iter != list.end() ;) {
			auto tmp = iter;
			iter++;
			auto node = *tmp;
			auto const& pos = GetNodePosition(node);
			if((pos.x > m_lefttop.x && pos.x < m_rightbottom.x) && (pos.y > m_rightbottom.y && pos.y < m_lefttop.y)) {
				bool getgoodfood = static_cast<assa2d::Object*>(node)->GetBody()->GetFixtureList()->GetShape()->m_radius > 2.5f ? true : false;
				if(getgoodfood) {
					m_collected_good_food++;
				} else {
					m_collected_bad_food++;
				}
				GetSceneMgr()->RemoveNode(node);

				Block::Configuration bc;
				bc.Tag = MAKE_TAG('f', 'o', 'o', 'd');
				bc.Id = m_cid++;

				float32 x, y;
				do {
					x = assa2d::RandomFloat(-45, 45);
					y = assa2d::RandomFloat(-45, 45);
				} while((x>-22.0f&&x<22.0f) && (y>-22.0f&&y<22.0f));
				bc.Position.Set(x, y);

				bc.CircleShape.m_radius = !getgoodfood ? 2 : 4;
				bc.Density = !getgoodfood ? 1.0f : 0.4f;
				GetSceneMgr()->AddNode<Block>(&bc);
			}
		}
	}

private:
	b2Vec2 m_lefttop;
	b2Vec2 m_rightbottom;

	std::size_t m_target_tag;

	std::size_t m_collected_good_food;
	std::size_t m_collected_bad_food;

	std::size_t m_cid;
};



#endif /* TESTS_POISONFOOD_PNEST_H_ */
