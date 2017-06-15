/*
 * IdObserver.h
 *
 *  Created on: Jun 14, 2017
 *      Author: wei
 */

#ifndef COMMON_COMPONENT_OMNICAMERA_OBSERVER_IDOBSERVER_H_
#define COMMON_COMPONENT_OMNICAMERA_OBSERVER_IDOBSERVER_H_

#include <set>

#include <assassin2d/assassin2d.h>

#include "../../Common.h"
#include "../OmniCamera.h"

/// Observe specific ids.
class IdObserver : public Observer<float> {
public:
	struct Configuration : public Observer<float>::Configuration {
		std::set<std::size_t> TargetId;
		float32 Range = 0.0f;
		bool ReportAngle =  false;
		bool ReportDistance = false;
	};

	IdObserver(Configuration* conf) : Observer<float>(conf) {
		m_target_id = conf->TargetId;
		m_range = conf->Range;
		m_report_angle = conf->ReportAngle;
		m_report_distance = conf->ReportDistance;
	}
	virtual ~IdObserver() { }

	/// Add a new id.
	void AddId(std::size_t id) {
		m_target_id.insert(id);
	}

	/// Remove an id.
	void RemoveId(std::size_t id) {
		m_target_id.erase(id);
	}

	/// Getters.
	std::set<std::size_t> const& GetTargetId() const {
		return m_target_id;
	}

	float32 GetRange() const {
		return m_range;
	}

	bool IsAngleReported() const {
		return m_report_angle;
	}

	bool IsDistanceReported() const {
		return m_report_distance;
	}

	/// Setters.
	void SetRange(float32 range) {
		m_range = range;
	}

	void SetReportAngle(bool flag) {
		m_report_angle = flag;
	}

	void SetReportDistance(bool flag) {
		m_report_distance = flag;
	}

protected:
	/// Report to the omni-camera.
	virtual std::vector<float> Report() override {
		auto scenemgr = GetOmniCamera()->GetSceneMgr();
		std::vector<float> result;
		for(auto id : GetTargetId()) {
			auto node = scenemgr->GetNodeById(id);
			b2Vec2 const& pos_d = static_cast<assa2d::Actor*>(GetOmniCamera()->GetActor())->GetMainComponent()->GetPosition();
			b2Vec2 const& pos_t = GetNodePosition(node);
			float32 dist = (pos_d-pos_t).Length();
			if(dist > GetRange()) {
				if(IsDistanceReported()) {
					result.push_back(1.0f);
				}
				if(IsAngleReported()) {
					result.push_back(1.0f);
					result.push_back(0.0f);
				}
				continue;
			}
			if(dist > 0.0f) {
				b2Vec2 const& l_pos = static_cast<assa2d::Actor*>(GetOmniCamera()->GetActor())->GetMainComponent()->GetBody()->GetLocalVector(pos_t-pos_d);
				float32 c_ang = l_pos.x / b2Sqrt(l_pos.x*l_pos.x + l_pos.y*l_pos.y);
				float32 s_ang = l_pos.y / b2Sqrt(l_pos.x*l_pos.x + l_pos.y*l_pos.y);
				if(IsDistanceReported()) {
					result.push_back(dist / GetRange());
				}
				if(IsAngleReported()) {
					result.push_back(c_ang);
					result.push_back(s_ang);
				}
			} else {
				if(IsDistanceReported()) {
					result.push_back(0.0f);
				}
				if(IsAngleReported()) {
					result.push_back(1.0f);
					result.push_back(0.0f);
				}
			}
		}
		return result;
	}

private:
	std::set<std::size_t> m_target_id;
	float32 m_range;
	bool m_report_angle;
	bool m_report_distance;
};

#endif /* COMMON_COMPONENT_OMNICAMERA_OBSERVER_IDOBSERVER_H_ */
