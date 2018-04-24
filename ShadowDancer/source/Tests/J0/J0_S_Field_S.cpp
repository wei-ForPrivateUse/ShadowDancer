/*
 * J0_S_Field_S.cpp
 *
 *  Created on: Apr 20, 2018
 *      Author: wei
 */

#include "J0_S_Field_S.h"

J0_S_Field_S::J0_S_Field_S(Configuration* conf, ANNWeights* wa_a, ANNWeights* wa_d) : assa2d::SceneMgr(conf) {
	// Walls.
	{
		Wall::Configuration wc;
		wc.Tag = MAKE_TAG('w', 'a', 'l', 'l');

		wc.Id = 900;
		wc.StartPoint = b2Vec2(68.284f, 20.0f);
		wc.EndPoint = b2Vec2(48.284f, 20.0f);
		AddNode<Wall>(&wc);

		wc.Id = 901;
		wc.StartPoint = b2Vec2(48.284f, 20.0f);
		wc.EndPoint = b2Vec2(20.0, 48.284f);
		AddNode<Wall>(&wc);

		wc.Id = 902;
		wc.StartPoint = b2Vec2(20.0, 48.284f);
		wc.EndPoint = b2Vec2(-20.0f, 48.284f);
		AddNode<Wall>(&wc);

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

		wc.Id = 910;
		wc.StartPoint = b2Vec2(48.284f, -20.0f);
		wc.EndPoint = b2Vec2(68.284f, -20.0f);
		AddNode<Wall>(&wc);

		wc.Id = 911;
		wc.StartPoint = b2Vec2(68.284f, -20.0f);
		wc.EndPoint = b2Vec2(68.284f, 20.0f);
		AddNode<Wall>(&wc);
	}

	// Barriers.
	{
		Block::Configuration bc;
		bc.Tag = MAKE_TAG('b', 'a', 'r', 'r');
		bc.ShapeType = assa2d::ShapeType::Polygon;
		bc.PolygonShape.SetAsBox(0.3f, 2.5f);
		bc.StaticBody = true;

		for(std::size_t i = 0; i < 4; i++) {
			bc.Id = 950 + i;
			float32 x = -48.284f;
			float32 y = -13.5 + i*9;
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

		bool flag[5][8] = {false};
		for(std::size_t i = 0; i < conf->Robot; i++) {
			int d1, d2;
			do {
				d1 = assa2d::RandomFloat(0.0f, 4.99f);
				d2 = assa2d::RandomFloat(0.0f, 7.99f);
			} while(flag[d1][d2]);
			flag[d1][d2] = true;

			float32 x, y;
			x = -66 + d1*4.0f + assa2d::RandomFloat()*1.5f;
			y = -17.5 + d2*5.0f + assa2d::RandomFloat()*2.0f;

			rc.Id = i;
            rc.Position.Set(x, y);
            rc.Angle = assa2d::RandomFloat(0, M_PI*2.0f);

            auto robot = AddNode<J0_A_Robot_S>(&rc);
            robot->m_single_0->SetWeights(wa_a);
            robot->m_single_1->SetWeights(wa_d);
            m_robot.push_back(robot);
		}
	}

	// Resources.
	{
		Block::Configuration bc;
		bc.Tag = MAKE_TAG('r', 'e', 's', 'o');
		bc.CircleShape.m_radius = 1.0f;
		bc.GroundFrictionForce = 3.0f;
		bc.GroundFrictionTorque = 3.0f;

		for(std::size_t i = 0; i < conf->Resource; i++) {
			bc.Id = 1000 + i;
			float32 r = assa2d::RandomFloat(4.0f, 45.0f);
			float32 a = assa2d::RandomFloat(0, M_PI*2.0f);
			float32 x = r * std::cos(a);
			float32 y = r * std::sin(a);
			bc.Position.Set(x, y);
			AddNode<Block>(&bc);
		}
	}

	// Packages.
	{
		Block::Configuration bc;
		bc.Tag = MAKE_TAG('p', 'a', 'c', 'k');
		bc.ShapeType = assa2d::ShapeType::Polygon;
		bc.PolygonShape.SetAsBox(2.5, 3.75);
		bc.GroundFrictionForce = 3.0f;
		bc.GroundFrictionTorque = 3.0f;

		for(std::size_t i = 0; i < conf->Package; i++) {
			bc.Id = 10000 + i;
			float32 r = assa2d::RandomFloat(8.0f, 40.0f);
			float32 a = assa2d::RandomFloat(0, M_PI*2.0f);
			float32 x = r * std::cos(a);
			float32 y = r * std::sin(a);
			bc.Position.Set(x, y);
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
		nc.Tag = MAKE_TAG('n', 'e', 's', 't');
		nc.TargetTag = MAKE_TAG('p', 'a', 'c', 'k');
		nc.recreate = true;
		nc.Internal.Set(48.284f, 68.284f);
		nc.NewResourceID = 1000000;
		m_nest_package = AddNode<J0_T_Nest>(&nc);
	}
}
