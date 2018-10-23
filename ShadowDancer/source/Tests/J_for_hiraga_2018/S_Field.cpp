/*
 * S_Field.cpp
 *
 *  Created on: Oct 4, 2018
 *      Author: wei
 */

#include "S_Field.h"

S_Field::S_Field(Configuration* conf, ANNWeights* w) : assa2d::SceneMgr(conf) {
	// Walls.
	{
		Wall::Configuration wc;
		wc.Friction = 0.0f;
		wc.Tag = MAKE_TAG('w', 'a', 'l', 'l');

		wc.Id = 900;
		wc.StartPoint = b2Vec2(24.85282f, 60.0f);
		wc.EndPoint = b2Vec2(-24.85282f, 60.0f);
		AddNode<Wall>(&wc);

		wc.Id = 901;
		wc.StartPoint = b2Vec2(-24.85282f, 60.0f);
		wc.EndPoint = b2Vec2(-60.0f, 24.85282f);
		AddNode<Wall>(&wc);

		wc.Id = 902;
		wc.StartPoint = b2Vec2(-60.0f, 24.85282f);
		wc.EndPoint = b2Vec2(-60.0f, -24.85282f);
		AddNode<Wall>(&wc);

		wc.Id = 903;
		wc.StartPoint = b2Vec2(-60.0f, -24.85282f);
		wc.EndPoint = b2Vec2(-24.85282f, -60.0f);
		AddNode<Wall>(&wc);

		wc.Id = 904;
		wc.StartPoint = b2Vec2(-24.85282f, -60.0f);
		wc.EndPoint = b2Vec2(24.85282f, -60.0f);
		AddNode<Wall>(&wc);

		wc.Id = 905;
		wc.StartPoint = b2Vec2(24.85282f, -60.0f);
		wc.EndPoint = b2Vec2(60.0f, -24.85282f);
		AddNode<Wall>(&wc);

		wc.Id = 906;
		wc.StartPoint = b2Vec2(60.0f, -24.85282f);
		wc.EndPoint = b2Vec2(60.0f, 24.85282f);
		AddNode<Wall>(&wc);

		wc.Id = 907;
		wc.StartPoint = b2Vec2(60.0f, 24.85282f);
		wc.EndPoint = b2Vec2(24.85282f, 60.0f);
		AddNode<Wall>(&wc);
	}

	// Robots.
	{
		A_Robot::Configuration rc;
		rc.Tag = MAKE_TAG('r', 'o', 'b', 'o');

		rc.IRSensor = conf->IRSensorNumber;
		rc.IRSensorRange = conf->IRRange;
		rc.OMNIRobot = conf->OMNIRobotNumber;
		rc.OMNIResource = conf->OMNIResourceNumber;
		rc.OMNICameraRange = conf->OMNIRange;

		std::vector<b2Vec2> robot_pos = GetRandomPositions(0.0f, 14.0f, conf->Robot, 1.5f);
		for(unsigned int i = 0; i < conf->Robot; i++) {
			rc.Id = i;
			rc.Position = robot_pos[i];
			rc.Angle = assa2d::RandomFloat(0.0f, M_PI*2.0f);

			auto robot = AddNode<A_Robot>(&rc);
			robot->m_ann->SetWeights(w);
			m_robot.push_back(robot);
		}
	}

	// Resources.
	{
		Block::Configuration bc;
		bc.Tag = MAKE_TAG('r', 'e', 's', 'o');
		bc.Friction = 0.1f;
		bc.GroundFrictionForce = 1.0f;
		bc.GroundFrictionTorque = 1.0f;

		std::vector<b2Vec2> pos = GetRandomPositions(25.0f, 50.0f, conf->Food+conf->Poison, 15.0f);

		bc.CircleShape.m_radius = conf->FoodRadius;
		bc.Density = conf->FoodDensity;
		for(std::size_t i = 0; i < conf->Food; i++) {
			bc.Id = 1000 + i;
			bc.Position = pos[i];
			AddNode<Block>(&bc);
		}

		bc.CircleShape.m_radius = conf->PoisonRadius;
		bc.Density = conf->PoisonDensity;
		bc.Flag = 0x1;
		for(std::size_t i = conf->Food; i < conf->Food+conf->Poison; i++) {
			bc.Id = 1000 + i;
			bc.Position = pos[i];
			AddNode<Block>(&bc);
		}
	}

	// Nest.
	{
		T_Nest::Configuration nc;
		nc.Id = 500;
		nc.Tag = MAKE_TAG('n', 'e', 's', 't');
		nc.Range = 15.0f;
		nc.TargetTag = MAKE_TAG('r', 'e', 's', 'o');

		nc.FoodRadius = conf->FoodRadius;
		nc.PoisonRadius = conf->PoisonRadius;
		nc.FoodDensity = conf->FoodDensity;
		nc.PoisonDensity = conf->PoisonDensity;

		m_nest = AddNode<T_Nest>(&nc);
	}
}
