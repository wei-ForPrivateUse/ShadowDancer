/*
 * J1_A_Robot.cpp
 *
 *  Created on: Oct 4, 2017
 *      Author: wei
 */

#include "J1_A_Robot.h"
#include "J1_O_Package.h"

/// Predicate for resource.
struct ResourcePred : public TagPredicate {
	ResourcePred(Configuration* conf): TagPredicate(conf){}
	virtual bool FilterAdditional(assa2d::Node* node) override {
		unsigned int mask = static_cast<Block*>(node)->GetMask() & 0x1;
		if(mask == 0x1)
			return true;
		return false;
	}
};

/// Predicate for robot.
struct RobotPred : public TagPredicate {
	RobotPred(Configuration* conf): TagPredicate(conf){}
	virtual bool FilterAdditional(assa2d::Node* node) override {
		int mode = static_cast<J1_A_Robot*>(node)->GetMode();
		if(mode != 1)
			return true;
		return false;
	}
};

J1_A_Robot::J1_A_Robot(Configuration* conf) : assa2d::Actor(conf) {
	// mainbody
	{
		MainBody::Configuration mbc;

		mbc.Id = 0;
		mbc.Position = conf->Position;
		mbc.Angle = conf->Angle;
		mbc.CircleShape.m_radius = 0.5;
		m_mainbody = AddComponent<MainBody>(&mbc);
	}
	SetMainComponent(m_mainbody);

	// motors
	{
		Motor::Configuration mc;

		mc.Priority = 4;
		mc.ForwardAttributes = {16.0f, 9.0f, 80.0f};
		mc.BackwardAttributes = {10.0f, 3.0f, 10.0f};
		mc.PolygonShape.SetAsBox(0.25f, 0.1f);
		mc.Anchor.Set(0.0f, 0.0f);

		mc.Id = 50;
		mc.TargetSpeedIndex = 50;
		mc.PowerRequestIndex = 60;
		mc.Position.Set(0.0f, 0.45f);
		m_motor[0] = AddComponent<Motor>(&mc);

		mc.Id = 51;
		mc.TargetSpeedIndex = 51;
		mc.PowerRequestIndex = 61;
		mc.Position.Set(0.0f, -0.45f);
		m_motor[1] = AddComponent<Motor>(&mc);
	}

	// Gripper
	{
		J1_AC_Gripper::Configuration gc;
		gc.Id = 52;
		gc.Priority = 3;
		gc.Tag = MAKE_TAG('g', 'r', 'i', 'p');
		gc.TargetTag = MAKE_TAG('r', 'e', 's', 'o');
		gc.TargetStatusMask = 0x1;
		gc.RequiredMode = 2;
		gc.OutputIndex = 33;
		gc.NullId = 999999;
		AddComponent<J1_AC_Gripper>(&gc);
	}

	// ir sensors
	{
		IRSenser::Configuration irc;

		irc.Priority = 0;
		irc.Range = 3.0f;
		irc.Position.Set(0.0f, 0.0f);

	    irc.Angle = M_PI / 10.0f;
	    irc.Id = 10;
	    irc.OutputIndex = 0;
	    m_ir_senser[0] = AddComponent<IRSenser>(&irc);
	    irc.Angle = M_PI / 10.0f * 3.0f;
	    irc.Id = 11;
	    irc.OutputIndex = 1;
	    m_ir_senser[1] = AddComponent<IRSenser>(&irc);
	    irc.Angle = M_PI_2;
	    irc.Id = 12;
	    irc.OutputIndex = 2;
	    m_ir_senser[2] = AddComponent<IRSenser>(&irc);
	    irc.Angle = M_PI / 8.0f * 7.0f;
	    irc.Id = 13;
	    irc.OutputIndex = 3;
	    m_ir_senser[3] = AddComponent<IRSenser>(&irc);
	    irc.Angle = - M_PI / 8.0f * 7.0f;
	    irc.Id = 14;
	    irc.OutputIndex = 4;
	    m_ir_senser[4] = AddComponent<IRSenser>(&irc);
	    irc.Angle = - M_PI_2;
	    irc.Id = 15;
	    irc.OutputIndex = 5;
	    m_ir_senser[5] = AddComponent<IRSenser>(&irc);
	    irc.Angle = - M_PI / 10.0f * 3;
	    irc.Id = 16;
	    irc.OutputIndex = 6;
	    m_ir_senser[6] = AddComponent<IRSenser>(&irc);
	    irc.Angle = - M_PI / 10.0f;
	    irc.Id = 17;
	    irc.OutputIndex = 7;
	    m_ir_senser[7] = AddComponent<IRSenser>(&irc);
	}

	// omni-camera
	{
		OmniTag<RobotPred>::Configuration otc_rp;
		otc_rp.Id = 21;
		otc_rp.Priority = 0;
		otc_rp.Range = 12;
		otc_rp.OutputIndexInterval = {20, 28};
		otc_rp.OutputCount = 3;
		otc_rp.TargetTag = MAKE_TAG('r', 'o', 'b', 'o');
		otc_rp.Predicate.Datum = this;
		otc_rp.Predicate.DatumExemption = true;
		m_omni_robot = AddComponent<OmniTag<RobotPred>>(&otc_rp);

		OmniTag<ResourcePred>::Configuration otc_rep;
		otc_rep.Id = 22;
		otc_rep.Priority = 0;
		otc_rep.Range = 12;
		otc_rep.OutputIndexInterval = {30, 32};
		otc_rep.OutputCount = 1;
		otc_rep.TargetTag = MAKE_TAG('r', 'e', 's', 'o');
		otc_rep.Predicate.Datum = this;
		otc_rep.Predicate.DatumExemption = true;
		m_omni_resource = AddComponent<OmniTag<ResourcePred>>(&otc_rep);

		OmniTag<TagPredicate>::Configuration otc_tp;
		otc_tp.Id = 23;
		otc_tp.Priority = 0;
		otc_tp.Range = 12;
		otc_tp.OutputIndexInterval = {35, 37};
		otc_tp.OutputCount = 1;
		otc_tp.TargetTag = MAKE_TAG('p', 'a', 'c', 'k');
		otc_tp.Predicate.Datum = this;
		otc_tp.Predicate.DatumExemption = true;
		m_omni_package = AddComponent<OmniTag<TagPredicate>>(&otc_tp);
	}

	// anns
	{
		J1_AC_Arbitrator::Configuration arbic;
		arbic.Id = 30;
		arbic.Priority = 1;
		arbic.InputIndex = {10, 11, 12, 13, 14, 15};
		arbic.OutputIndex = {40, 41, 42};
		arbic.SubControllerId = {31, 32, 33};
		m_arbi = AddComponent<J1_AC_Arbitrator>(&arbic);

		ANN::Configuration ac;
		ac.Priority = 2;

		ac.Id = 31;
		ac.InputIndex = {0, 1, 2, 3, 4, 5, 6, 7, 20, 21, 22, 23, 24, 25, 26, 27, 28};
		ac.OutputIndex = {50, 51};
		m_a_s1 = AddComponent<ANN>(&ac);

		ac.Id = 32;
		ac.InputIndex = {0, 1, 2, 3, 4, 5, 6, 7, 30, 31, 32, 33, 16, 17};
		ac.OutputIndex = {50, 51};
		m_a_s2 = AddComponent<ANN>(&ac);

		ac.Id = 33;
		ac.InputIndex = {0, 1, 2, 3, 4, 5, 6, 7, 35, 36, 37};
		ac.OutputIndex = {50, 51};
		m_a_s3 = AddComponent<ANN>(&ac);
	}

	// Training mode.
	m_training_mode = conf->TrainingMode;

	// Set extra parameters for motors.
	GetDataPool().Set<float>(60, 100.0f);
	GetDataPool().Set<float>(61, 100.0f);
}

void J1_A_Robot::PreAct() {
	std::size_t robot_s1_count = 0;
	std::size_t robot_s2_count = 0;
	std::size_t robot_s3_count = 0;
	std::size_t resource_count = 0;
	std::size_t package_count = 0;

	float32 c_ang = 1.0f;
	float32 s_ang = 0.0f;

	// Count robots.
	auto const& robot_list = GetSceneMgr()->GetNodesByTag(MAKE_TAG('r', 'o', 'b', 'o'));
	for(auto node : robot_list) {
		auto robot = static_cast<J1_A_Robot*>(node);
		if(robot != this) {
			float32 dist_squared = (robot->GetMainComponent()->GetPosition()-this->GetMainComponent()->GetPosition()).LengthSquared();
			float32 omni_range = static_cast<OmniTag<RobotPred>*>(m_omni_robot)->GetRange();
			float32 omni_range_squared = omni_range * omni_range;
			if(dist_squared < omni_range_squared) {
				switch(robot->GetMode()) {
				case 1: {
					robot_s1_count++;
				}
					break;
				case 2: {
					robot_s2_count++;
				}
					break;
				case 3: {
					robot_s3_count++;
				}
					break;
				default:
					break;
				}
			}
		}
	}

	// Count resources.
	if(GetSceneMgr()->CountNodesByTag(MAKE_TAG('r', 'e', 's', 'o')) > 0) {
		auto const& resource_list = GetSceneMgr()->GetNodesByTag(MAKE_TAG('r', 'e', 's', 'o'));
		for(auto node : resource_list) {
			auto resource = static_cast<Block*>(node);
			float32 dist_squared = (resource->GetPosition()-this->GetMainComponent()->GetPosition()).LengthSquared();
			float32 omni_range = static_cast<OmniTag<ResourcePred>*>(m_omni_resource)->GetRange();
			float32 omni_range_squared = omni_range * omni_range;
			if(dist_squared < omni_range_squared) {
				unsigned int mask = resource->GetMask() & 0x1;
				if(mask != 0x1) {
					resource_count++;
				}
			}

		}
	}

	// Count Packages.
	if(GetSceneMgr()->CountNodesByTag(MAKE_TAG('p', 'a', 'c', 'k')) > 0) {
		auto const& package_list = GetSceneMgr()->GetNodesByTag(MAKE_TAG('p', 'a', 'c', 'k'));
		for(auto node : package_list) {
			auto package = static_cast<J1_O_Package*>(node);
			float32 dist_squared = (package->GetPosition()-this->GetMainComponent()->GetPosition()).LengthSquared();
			float32 omni_range = static_cast<OmniTag<TagPredicate>*>(m_omni_package)->GetRange();
			float32 omni_range_squared = omni_range * omni_range;
			if(dist_squared < omni_range_squared) {
				package_count++;
			}
		}
	}


	// Angle of the nest.
	b2Vec2 const& pos = this->GetMainComponent()->GetPosition();
	if(pos == b2Vec2(0.0f, 0.0f)) { }
	else {
		b2Vec2 const& l_pos = this->GetMainComponent()->GetBody()->GetLocalVector(-pos);
		c_ang = l_pos.x / b2Sqrt(l_pos.x*l_pos.x + l_pos.y*l_pos.y);
		s_ang = l_pos.y / b2Sqrt(l_pos.x*l_pos.x + l_pos.y*l_pos.y);
	}

	// Set outputs.
	GetDataPool().Set<float>(10, GetMode());
	GetDataPool().Set<float>(11, robot_s1_count);
	GetDataPool().Set<float>(12, robot_s2_count);
	GetDataPool().Set<float>(13, robot_s3_count);
	GetDataPool().Set<float>(14, resource_count);
	GetDataPool().Set<float>(15, package_count);
	GetDataPool().Set<float>(16, c_ang);
	GetDataPool().Set<float>(17, s_ang);

	// Training modes.
	switch(m_training_mode) {
	case 1: {
		m_arbi -> SetActive(false);
		m_a_s1 -> SetActive(true);
		m_a_s2 -> SetActive(false);
		m_a_s3 -> SetActive(false);
	}
		break;
	case 2: {
		m_arbi -> SetActive(false);
		m_a_s3 -> SetActive(false);

		if(resource_count==0 && GetDataPool().Get<float>(33)==0.0f) {
			m_a_s1 -> SetActive(true);
			m_a_s2 -> SetActive(false);
		} else {
			m_a_s1 -> SetActive(false);
			m_a_s2 -> SetActive(true);
		}
	}
		break;
	case 3: {
		m_arbi -> SetActive(false);
		m_a_s2 -> SetActive(false);

		if(package_count == 0) {
			m_a_s1 -> SetActive(true);
			m_a_s3 -> SetActive(false);
		} else {
			m_a_s1 -> SetActive(false);
			m_a_s3 -> SetActive(true);
		}
	}
		break;
	default:
		break;
	}
}
