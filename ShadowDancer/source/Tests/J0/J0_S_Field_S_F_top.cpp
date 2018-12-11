/*
 * J0_S_Field_S.cpp
 *
 *  Created on: Apr 20, 2018
 *      Author: wei
 */

#include "J0_S_Field_S_F_top.h"

J0_S_Field_S_F_top::J0_S_Field_S_F_top(Configuration* conf, ANNWeights* wa_a, ANNWeights* wa_d) : assa2d::SceneMgr(conf) {
	// Walls.
	{
		Wall::Configuration wc;
		wc.Friction = 0.0f;
		wc.Tag = MAKE_TAG('w', 'a', 'l', 'l');

		//wc.Id = 900;
		//wc.StartPoint = b2Vec2(68.284f, 20.0f);
		//wc.EndPoint = b2Vec2(48.284f, 20.0f);
		//AddNode<Wall>(&wc);

		wc.Id = 901;
		wc.StartPoint = b2Vec2(48.284f, 20.0f);
		wc.EndPoint = b2Vec2(20.0, 48.284f);
		AddNode<Wall>(&wc);

		//wc.Id = 902;
		//wc.StartPoint = b2Vec2(20.0, 48.284f);
		//wc.EndPoint = b2Vec2(-20.0f, 48.284f);
		//AddNode<Wall>(&wc);

		wc.Id = 903;
		wc.StartPoint = b2Vec2(-20.0f, 48.284f);
		wc.EndPoint = b2Vec2(-48.284f, 20.0f);
		AddNode<Wall>(&wc);

		wc.Id = 904;
		wc.StartPoint = b2Vec2(-48.284f, 20.0f);
		wc.EndPoint = b2Vec2(-68.284f, 20.0f);
		AddNode<Wall>(&wc);

		wc.Id = 905;
		wc.StartPoint = b2Vec2(-68.284f, 20.0f);
		wc.EndPoint = b2Vec2(-68.284f, -20.0f);
		AddNode<Wall>(&wc);

		wc.Id = 906;
		wc.StartPoint = b2Vec2(-68.284f, -20.0f);
		wc.EndPoint = b2Vec2(-48.284f, -20.0f);
		AddNode<Wall>(&wc);

		wc.Id = 907;
		wc.StartPoint = b2Vec2(-48.284f, -20.0f);
		wc.EndPoint = b2Vec2(-20.0f, -48.284f);
		AddNode<Wall>(&wc);

		wc.Id = 908;
		wc.StartPoint = b2Vec2(-20.0f, -48.284f);
		wc.EndPoint = b2Vec2(20.0f, -48.284f);
		AddNode<Wall>(&wc);

		wc.Id = 909;
		wc.StartPoint = b2Vec2(20.0f, -48.284f);
		wc.EndPoint = b2Vec2(48.284f, -20.0f);
		AddNode<Wall>(&wc);

		//wc.Id = 910;
		//wc.StartPoint = b2Vec2(48.284f, -20.0f);
		//wc.EndPoint = b2Vec2(68.284f, -20.0f);
		//AddNode<Wall>(&wc);

		//wc.Id = 911;
		//wc.StartPoint = b2Vec2(68.284f, -20.0f);
		//wc.EndPoint = b2Vec2(68.284f, 20.0f);
		//AddNode<Wall>(&wc);

		wc.Id = 912;
		wc.StartPoint = b2Vec2(48.284f, -20.0f);
		wc.EndPoint = b2Vec2(48.284f, 20.0f);
		AddNode<Wall>(&wc);

		wc.Id = 913;
		wc.StartPoint = b2Vec2(20.0f, 48.284f);
		wc.EndPoint = b2Vec2(20.0f, 68.284f);
		AddNode<Wall>(&wc);

		wc.Id = 914;
		wc.StartPoint = b2Vec2(20.0f, 68.284f);
		wc.EndPoint = b2Vec2(-20.0f, 68.284f);
		AddNode<Wall>(&wc);

		wc.Id = 915;
		wc.StartPoint = b2Vec2(-20.0f, 48.284f);
		wc.EndPoint = b2Vec2(-20.0f, 68.284f);
		AddNode<Wall>(&wc);

	}

	// Barriers.
	{
		Block::Configuration bc;
		bc.Tag = MAKE_TAG('b', 'a', 'r', 'r');
		bc.ShapeType = assa2d::ShapeType::Polygon;
		bc.PolygonShape.SetAsBox(0.3f, 1.25f);
		bc.StaticBody = true;
		bc.Friction = 0.0f;

		for(std::size_t i = 0; i < 4; i++) {
			bc.Id = 950 + i;
			float32 x = -48.284f;
			float32 y = -12.75 + i*8.5;
			bc.Position.Set(x, y);
			AddNode<Block>(&bc);
		}
	}

	// Robots.
	{
		srand(time(NULL));
		J0_A_Robot_S::Configuration rc;
		rc.Tag = MAKE_TAG('r', 'o', 'b', 'o');
		rc.TrainingMode = conf->TrainingMode;

		std::vector<b2Vec2> robot_pos = GetRandomPositions(b2Vec2(-67.284f, 19.0f), b2Vec2(-49.284, -19.0f), conf->Robot, 1.3f);
		for(std::size_t i = 0; i < conf->Robot; i++) {
			rc.Id = i;
            rc.Position = robot_pos[i];
            rc.Angle = assa2d::RandomFloat(0, M_PI*2.0f);

            auto robot = AddNode<J0_A_Robot_S>(&rc);
            robot->m_single_0->SetWeights(wa_a);
            robot->m_single_1->SetWeights(wa_d);
            m_robot.push_back(robot);
		}
	}

	std::vector<b2Vec2> pos = GetRandomPositions(3.0f, 40.0f, conf->Resource + conf->Package, 9.0f);
	// Resources.
	{
		Block::Configuration bc;
		bc.Tag = MAKE_TAG('r', 'e', 's', 'o');
		bc.CircleShape.m_radius = 1.0f;
		bc.Density = 0.55f;
		bc.Friction = 0.05f;
		bc.GroundFrictionForce = 1.0f;
		bc.GroundFrictionTorque = 2.0f;

		for(std::size_t i = 0; i < conf->Resource; i++) {
			bc.Id = 1000 + i;
			bc.Position = pos[i];
			AddNode<Block>(&bc);
		}
	}

	// Packages.
	{
		Block::Configuration bc;
		bc.Tag = MAKE_TAG('p', 'a', 'c', 'k');
		bc.ShapeType = assa2d::ShapeType::Polygon;
		b2Vec2 w_v[6];
		w_v[5] = b2Vec2(2.0f, 3.464f);
		w_v[4] = b2Vec2(-2.0f, 3.464f);
		w_v[3] = b2Vec2(-4.0f, 0.0f);
		w_v[2] = b2Vec2(-2.0f, -3.464f);
		w_v[1] = b2Vec2(2.0f, -3.464f);
		w_v[0] = b2Vec2(4.0f, 0.0f);
		bc.PolygonShape.Set(w_v, 6);
		bc.Friction = 1.0f;
		bc.Density = 0.5f;
		bc.GroundFrictionForce = 0.5f;
		bc.GroundFrictionTorque = 0.6f;

		for(std::size_t i = 0; i < conf->Package; i++) {
			bc.Id = 10000 + i;
			bc.Position = pos[conf->Resource+i];
			bc.Angle = assa2d::RandomFloat(0, M_PI*2.0f);
			AddNode<Block>(&bc);
		}
	}

	// Nest_resource.
	{
		J0_T_Nest::Configuration nc;
		nc.Id = 500;
		nc.Tag = MAKE_TAG('n', 'e', 's', 't');
		nc.TargetTag = MAKE_TAG('r', 'e', 's', 'o');
		nc.recreate = false;
		nc.Internal.Set(-68.284f, -48.284f);
		m_nest_resource = AddNode<J0_T_Nest>(&nc);
	}
	// Nest_package.
	{
		J0_T_Nest::Configuration nc;
		nc.Id = 501;
		nc.axis = 'y';
		nc.Tag = MAKE_TAG('n', 'e', 's', 't');
		nc.TargetTag = MAKE_TAG('p', 'a', 'c', 'k');
		nc.recreate = true;
		nc.Internal.Set(48.284f, 68.284f);
		nc.NewResourceID = 1000000;
		m_nest_package = AddNode<J0_T_Nest>(&nc);
	}

	robust_test = conf->robust_test;
}
