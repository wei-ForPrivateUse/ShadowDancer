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
		wc.Tag = MAKE_TAG('w', 'a', 'l', 'l');

		wc.Id = 900;
		wc.StartPoint = b2Vec2(41.42136f, 100.0f);
		wc.EndPoint = b2Vec2(-41.42136f, 100.0f);
		AddNode<Wall>(&wc);

		wc.Id = 901;
		wc.StartPoint = b2Vec2(-41.42136f, 100.0f);
		wc.EndPoint = b2Vec2(-100.0f, 41.42136f);
		AddNode<Wall>(&wc);

		wc.Id = 902;
		wc.StartPoint = b2Vec2(-100.0f, 41.42136f);
		wc.EndPoint = b2Vec2(-100.0f, -41.42136f);
		AddNode<Wall>(&wc);

		wc.Id = 903;
		wc.StartPoint = b2Vec2(-100.0f, -41.42136f);
		wc.EndPoint = b2Vec2(-41.42136f, -100.0f);
		AddNode<Wall>(&wc);

		wc.Id = 904;
		wc.StartPoint = b2Vec2(-41.42136f, -100.0f);
		wc.EndPoint = b2Vec2(41.42136f, -100.0f);
		AddNode<Wall>(&wc);

		wc.Id = 905;
		wc.StartPoint = b2Vec2(41.42136f, -100.0f);
		wc.EndPoint = b2Vec2(100.0f, -41.42136f);
		AddNode<Wall>(&wc);

		wc.Id = 906;
		wc.StartPoint = b2Vec2(100.0f, -41.42136f);
		wc.EndPoint = b2Vec2(100.0f, 41.42136f);
		AddNode<Wall>(&wc);

		wc.Id = 907;
		wc.StartPoint = b2Vec2(100.0f, 41.42136f);
		wc.EndPoint = b2Vec2(41.42136f, 100.0f);
		AddNode<Wall>(&wc);
	}

	// Robots.
	{
		srand(time(NULL));
		A_Robot::Configuration rc;
		rc.Tag = MAKE_TAG('r', 'o', 'b', 'o');

		rc.IRSensor = conf->IRSensorNumber;
		rc.IRSensorRange = conf->IRRange;
		rc.OMNIRobot = conf->OMNIRobotNumber;
		rc.OMNICameraRange = conf->OMNIRange;

		std::vector<b2Vec2> robot_pos = GetRandomPositions(25, 90, conf->Robot, 1.5);
		for(int i = 0; i < conf->Robot; i++) {
			rc.Id = i;
			rc.Position = robot_pos[i];
			rc.Angle = assa2d::RandomFloat(0.0f, M_PI*2.0f);

			auto robot = AddNode<A_Robot>(&rc);
			robot->m_ann->SetWeights(w);
			m_robot.push_back(robot);
		}
	}

	///////////////////////////
	// Resources.
	{
		Block::Configuration bc;
		bc.Tag = MAKE_TAG('r', 'e', 's', 'o');
		bc.CircleShape.m_radius = 0.4f;
		bc.GroundFrictionForce = 5.0f;
		bc.GroundFrictionTorque = 5.0f;

		for(std::size_t i = 0; i < conf->Resource; i++) {
			bc.Id = 1000 + i;
			float32 r = assa2d::RandomFloat(20.0f, 90.0f);
			float32 a = assa2d::RandomFloat(0, M_PI*2.0f);
			float32 x = r * std::cos(a);
			float32 y = r * std::sin(a);
			bc.Position.Set(x, y);
			AddNode<Block>(&bc);
		}
	}

	// Packages.
	{
		J1_O_Package::Configuration pc;
		pc.Tag = MAKE_TAG('p', 'a', 'c', 'k');
		pc.StaticBody = true;
		pc.ShapeType = assa2d::ShapeType::Polygon;
		pc.PolygonShape.SetAsBox(1.5f, 2.0f);
		pc.MinStepTouch = conf->MinStepTouch;
		pc.MaxStepTouch = conf->MaxStepTouch;
		pc.RequiredTouch = conf->RequiredTouch;

		for(std::size_t i = 0; i < conf->Package; i++) {
			pc.Id = 10000 + i;
			float32 r = assa2d::RandomFloat(20.0f, 90.0f);
			float32 a = assa2d::RandomFloat(0, M_PI*2.0f);
			float32 x = r * std::cos(a);
			float32 y = r * std::sin(a);
			pc.Position.Set(x, y);
			pc.Angle = assa2d::RandomFloat(0, M_PI*2.0f);
			AddNode<J1_O_Package>(&pc);
		}
	}

	// Nest.
	{
		T_Nest::Configuration nc;
		nc.Id = 500;
		nc.Tag = MAKE_TAG('n', 'e', 's', 't');
		nc.Range = 15.0f;
		nc.TargetTag = MAKE_TAG('r', 'e', 's', 'o');

		m_nest = AddNode<T_Nest>(&nc);
	}
}
