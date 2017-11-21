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

/// Predicate with filter.
struct TagPredicate {
	/// Configuration.
	struct Configuration {
		assa2d::Node* Datum = nullptr;
		bool DatumExemption = true;
	};

	TagPredicate(Configuration* conf) {
		m_datum = conf->Datum;
		m_datum_exemption = conf->DatumExemption;
	}
	virtual ~TagPredicate() { }

	/// Return true if 'a' should be ahead of b.
	bool operator()(assa2d::Node* a, assa2d::Node* b) {
		if(Filter(a)) {
			return false;
		}
		if(Filter(b)) {
			return true;
		}
		b2Vec2 const& pos_datum = GetNodePosition(m_datum);
		b2Vec2 const& pos_a = GetNodePosition(a);
		b2Vec2 const& pos_b = GetNodePosition(b);
		return (pos_datum-pos_a).LengthSquared() < (pos_datum-pos_b).LengthSquared();
	}

	/// Return true if 'node' is not to be sorted.
	bool Filter(assa2d::Node* node) {
		if(node==m_datum && m_datum_exemption) {
			return true;
		}
		return FilterAdditional(node);
	}

	/// Return true if 'node' is not to be sorted.
	virtual bool FilterAdditional(assa2d::Node* node) {
		return false;
	}

	assa2d::Node* m_datum;
	bool m_datum_exemption;
};

/// Observe specific tags with predicate _Tp.
template<typename _Tp>
class OmniTag : public Camera<float> {
public:
	struct Configuration : public Camera<float>::Configuration {
		float32 Range = 0.0f;

		std::size_t TargetTag = 0;
		std::size_t OutputCount = 0;

		_Tp::Configuration Predicate;
	};

	OmniTag(Configuration* conf) : Camera<float>(conf), m_predicate(&conf->Predicate) {
		m_range = conf->Range;

		m_target_tag = conf->TargetTag;
		m_output_count = conf->OutputCount;
	}
	virtual ~OmniTag() { }

	/// Getter.
	float32 GetRange() const {
		return m_range;
	}

	/// Setter.
	void SetRange(float32 range) {
		m_range = range;
	}

protected:
	/// Report outputs.
	virtual std::vector<float> Report() override {
		std::vector<float> result;

		std::size_t count = std::min(GetSceneMgr()->CountNodesByTag(m_target_tag), m_output_count);
		if(count == 0) {
			_Fill(result);
			return result;
		}

		auto const& node_list = GetSceneMgr()->GetNodesByTag(m_target_tag);
		std::vector<assa2d::Node*> ordered_node_list(count);
		std::partial_sort_copy(node_list.begin(), node_list.end(), ordered_node_list.begin(), ordered_node_list.end(), m_predicate);

		for(auto node : ordered_node_list) {
			b2Vec2 const& pos_d = static_cast<assa2d::Actor*>(GetActor())->GetMainComponent()->GetPosition();
			b2Vec2 const& pos_t = GetNodePosition(node);
			float32 dist = (pos_d-pos_t).Length();

			if(m_predicate.Filter(node) || dist > GetRange()) {
				_Fill(result);
				return result;
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

	/// Fill the result vector.
	void _Fill(std::vector<float> & vec) {
		std::size_t count = vec.size() / 3;
		vec.resize(m_output_count * 3);
		for(int i = count; i < m_output_count; i++) {
			vec[i*3] = 2.0f;
		}
	}

private:
	float32 m_range;

	std::size_t m_target_tag;
	std::size_t m_output_count;

	_Tp m_predicate;
};

#endif /* COMMON_COMPONENT_CAMERA_OMNI_OMNITAG_H_ */
