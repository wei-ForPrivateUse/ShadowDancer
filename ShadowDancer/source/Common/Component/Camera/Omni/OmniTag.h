/*
 * OmniTag.h
 *
 *  Created on: Jun 14, 2017
 *      Author: wei
 */

#ifndef COMMON_COMPONENT_CAMERA_OMNI_OMNITAG_H_
#define COMMON_COMPONENT_CAMERA_OMNI_OMNITAG_H_

#include <vector>
#include <algorithm>

#include <assassin2d/assassin2d.h>

#include "Common/Common.h"
#include "Common/Component/Camera/Camera.h"

/// Filter
struct Filter {
	bool operator()(assa2d::Node* node) {

	}
};

/// Predicate with filter.
template<typename _Tp>
struct TagPredicate {
	bool operator()(assa2d::Node* a, assa2d::Node* b) {

	}

	_Tp filter;
};












/// Functor.
struct _Tag_Observer_Comp {
	bool operator()(assa2d::Node* a, assa2d::Node* b) {
		if(!selfvisibility) {
			if(a == datum) {
				return false;
			}
			if(b == datum) {
				return  true;
			}
		}

		b2Vec2 const& pos_datum = datum->GetMainComponent()->GetPosition();
		b2Vec2 const& pos_a = GetNodePosition(a);
		b2Vec2 const& pos_b = GetNodePosition(b);

		return (pos_datum-pos_a).LengthSquared() < (pos_datum-pos_b).LengthSquared();
	}

	bool selfvisibility = false;
	assa2d::Actor* datum = nullptr;
};

/// Observe specific tags.
class TagObserver : public Camera<float> {
public:
	struct Configuration : public Camera<float>::Configuration {
		std::size_t TargetTag = 0;
		std::size_t OutputCount = 0;
		float32 Range = 0.0f;

		bool SelfVisibility = false;
	};

	TagObserver(Configuration* conf) : Camera<float>(conf) {
		m_target_tag = conf->TargetTag;
		m_output_count = conf->OutputCount;
		m_range = conf->Range;

		m_comp.datum = static_cast<assa2d::Actor*>(GetActor());
		m_comp.selfvisibility = conf->SelfVisibility;
	}
	virtual ~TagObserver() { }

	/// Getter.
	float32 GetRange() const {
		return m_range;
	}

	/// Setter.
	void SetRange(float32 range) {
		m_range = range;
	}

protected:
	/// Report to the omni-camera.
	virtual std::vector<float> Report() override {
		auto const& node_list = GetSceneMgr()->GetNodesByTag(m_target_tag);
		std::vector<assa2d::Node*> ordered_node_list(GetOutputCount());
		std::partial_sort_copy(node_list.begin(), node_list.end(), ordered_node_list.begin(), ordered_node_list.end(), m_comp);
		std::vector<float> result;

		for(auto node : ordered_node_list) {
			if(node == GetActor() || node == nullptr) {
				throw std::runtime_error("TagObserver::Report(...): insufficient nodes to sort.");
			}

			b2Vec2 const& pos_d = static_cast<assa2d::Actor*>(GetActor())->GetMainComponent()->GetPosition();
			b2Vec2 const& pos_t = GetNodePosition(node);

			float32 dist = (pos_d-pos_t).Length();
			if(dist > GetRange()) {
				result.push_back(2.0f);
				result.push_back(0.0f);
				result.push_back(0.0f);
				continue;
			}
			if(dist > 0.0f) {
				b2Vec2 const& l_pos = static_cast<assa2d::Actor*>(GetActor())->GetMainComponent()->GetBody()->GetLocalVector(pos_t-pos_d);
				float32 c_ang = l_pos.x / b2Sqrt(l_pos.x*l_pos.x + l_pos.y*l_pos.y);
				float32 s_ang = l_pos.y / b2Sqrt(l_pos.x*l_pos.x + l_pos.y*l_pos.y);

				result.push_back(dist / GetRange());
				result.push_back(c_ang);
				result.push_back(s_ang);
			} else {
				result.push_back(0.0f);
				result.push_back(1.0f);
				result.push_back(0.0f);
			}
		}
		return  result;
	}

private:
	std::size_t m_target_tag;
	std::size_t m_output_count;
	float32 m_range;

	_Tag_Observer_Comp m_comp;
};

#endif /* COMMON_COMPONENT_CAMERA_OMNI_OMNITAG_H_ */
