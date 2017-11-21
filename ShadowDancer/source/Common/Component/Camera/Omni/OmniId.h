/*
 * OmniId.h
 *
 *  Created on: Jun 14, 2017
 *      Author: wei
 */

#ifndef COMMON_COMPONENT_CAMERA_OMNI_OMNIID_H_
#define COMMON_COMPONENT_CAMERA_OMNI_OMNIID_H_

#include <set>

#include <assassin2d/assassin2d.h>

#include "Common/Common.h"
#include "Common/Component/Camera/Camera.h"

/// Report specific ids.
class OmniId : public Camera<float> {
public:
	struct Configuration : public Camera<float>::Configuration {
		float32 Range = 0.0f;

		std::set<std::size_t> TargetId;

		bool ReportAngle =  true;
		bool ReportDistance = true;
	};

	OmniId(Configuration* conf) : Camera<float>(conf) {
		m_range = conf->Range;

		m_target_id = conf->TargetId;

		m_report_angle = conf->ReportAngle;
		m_report_distance = conf->ReportDistance;
	}
	virtual ~OmniId() { }

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
		auto scenemgr = GetSceneMgr();
		std::vector<float> result;
		for(auto id : m_target_id) {
			auto node = scenemgr->GetNodeById(id);
			b2Vec2 const& pos_d = static_cast<assa2d::Actor*>(GetActor())->GetMainComponent()->GetPosition();
			b2Vec2 const& pos_t = GetNodePosition(node);

			float32 dist = (pos_d-pos_t).Length();
			if(dist > GetRange()) {
				if(m_report_distance) {
					result.push_back(2.0f);
				}
				if(m_report_angle) {
					result.push_back(0.0f);
					result.push_back(0.0f);
				}
				continue;
			}
			if(dist > 0.0f) {
				b2Vec2 const& l_pos = static_cast<assa2d::Actor*>(GetActor())->GetMainComponent()->GetBody()->GetLocalVector(pos_t-pos_d);
				float32 c_ang = l_pos.x / b2Sqrt(l_pos.x*l_pos.x + l_pos.y*l_pos.y);
				float32 s_ang = l_pos.y / b2Sqrt(l_pos.x*l_pos.x + l_pos.y*l_pos.y);
				if(m_report_distance) {
					result.push_back(dist / GetRange());
				}
				if(m_report_angle) {
					result.push_back(c_ang);
					result.push_back(s_ang);
				}
			} else {
				if(m_report_distance) {
					result.push_back(0.0f);
				}
				if(m_report_angle) {
					result.push_back(1.0f);
					result.push_back(0.0f);
				}
			}
		}
		return result;
	}

private:
	float32 m_range;

	std::set<std::size_t> m_target_id;

	bool m_report_angle;
	bool m_report_distance;
};

#endif /* COMMON_COMPONENT_CAMERA_OMNI_OMNIID_H_ */
