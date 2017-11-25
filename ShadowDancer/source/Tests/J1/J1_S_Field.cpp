/*
 * J1_S_Field.cpp
 *
 *  Created on: Nov 16, 2017
 *      Author: wei
 */

#include "J1_S_Field.h"

J1_S_Field::J1_S_Field(Configuration* conf) : assa2d::SceneMgr(conf) {
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
		J1_A_Robot::Configuration rc;
		rc.Tag = MAKE_TAG('r', 'o', 'b', 'o');

		int l_count[6] = {30, 22, 17, 9, 5 ,1};
		float l_radius[6] = {14, 11.3, 8, 5, 2, 0.2};
		bool flag[6][30] = {false};
		for(std::size_t i = 0; i < conf->Robot; i++) {
			int l, p;
			do {
				l = assa2d::RandomFloat(0.0f, 5.9f);
				p = assa2d::RandomFloat(0.0f, l_count[l]-0.01f);
			} while(flag[l][p]);
			flag[l][p] = true;

			float32 x, y;
			x = l_radius[l] * std::cos(2.0f*M_PI/l_count[l]*p) + assa2d::RandomFloat()*0.7f;
			y = l_radius[l] * std::sin(2.0f*M_PI/l_count[l]*p) + assa2d::RandomFloat()*0.7f;

			rc.Id = i;
            rc.Position.Set(x, y);
            rc.Angle = assa2d::RandomFloat(0, M_PI*2.0f);
            m_robot.push_back(AddNode<J1_A_Robot>(&rc));
		}
	}

	// Resources.
	{
		Block::Configuration bc;
		bc.Tag = MAKE_TAG('r', 'e', 's', 'o');
		bc.CircleShape.m_radius = 0.4f;
		bc.GroundFrictionForce = 5.0f;
		bc.GroundFrictionTorque = 5.0f;

		for(std::size_t i = 0; i < conf->Resource; i++) {
			bc.Id = 1000 + i;
			float32 r = assa2d::RandomFloat(20.0f, 95.0f);
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

		for(std::size_t i = 0; i < conf->Package; i++) {
			pc.Id = 10000 + i;
			float32 r = assa2d::RandomFloat(25.0f, 90.0f);
			float32 a = assa2d::RandomFloat(0, M_PI*2.0f);
			float32 x = r * std::cos(a);
			float32 y = r * std::sin(a);
			pc.Position.Set(x, y);
			pc.Angle = assa2d::RandomFloat(0, M_PI*2.0f);
			AddNode<J1_O_Package>(&pc);
		}
	}

	// Trigger.
	{
		J1_T_Nest::Configuration nc;
		nc.Id = 500;
		nc.Tag = MAKE_TAG('n', 'e', 's', 't');
		nc.Resource = conf->Resource;
		nc.Package = conf->Package;
		nc.ResourceSupplement = conf->ResourceSupplement;
		nc.PackageSupplement = conf->PackageSupplement;
		nc.ResourceMask = conf->ResourceMask;
		nc.NewResourceId = 1000 + conf->Resource;
		nc.NewPackageId = 10000 + conf->Package;
		AddNode<J1_T_Nest>(&nc);
	}
}

