/*
 * J1_S_Field.cpp
 *
 *  Created on: Nov 16, 2017
 *      Author: wei
 */

#include "J1_S_Field.h"

J1_S_Field::J1_S_Field(Configuration* conf) : assa2d::SceneMgr(conf) {
	// Parameters.
	m_max_resource = conf -> MaxResource;
	m_max_package = conf -> MaxPackage;
	m_resource_supplement = conf -> ResourceSupplement;
	m_package_supplement = conf -> PackageSupplement;

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
		for(int i = 0; i < 50; i++) {
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
            m_robot[i] = AddNode<J1_A_Robot>(&rc);
		}
	}

	// Resources.
	{
		Block::Configuration bc;
		bc.CircleShape.m_radius = 0.4f;
		bc.Tag = MAKE_TAG('r', 'e', 's', 'o');
		for(std::size_t i = 0; i < m_max_resource; i++) {
			bc.Id = 1000 + i;
			float32 r = assa2d::RandomFloat(20.0f, 95.0f);
			float32 a = assa2d::RandomFloat(0, M_PI*2.0f);
			float32 x = r * std::cos(a);
			float32 y = r * std::sin(a);
			bc.Position.Set(x, y);
			AddNode<Block>(&bc);
		}
	}

	// Packages. TODO
	{
		Block::Configuration bc;
		bc.Tag = MAKE_TAG('p', 'a', 'c', 'k');

		for(std::size_t i = 200; i < 206; i++) {
			bc.Id = i;

			float32 x, y;
			do {
				x = assa2d::RandomFloat(-45, 45);
				y = assa2d::RandomFloat(-45, 45);
			} while((x>-22.0f&&x<22.0f) && (y>-22.0f&&y<22.0f));
			bc.Position.Set(x, y);


			bool isbadfood = (i-200) > 2 ? true : false;
			bc.CircleShape.m_radius = isbadfood ? 2 : 4;
			bc.Density = isbadfood ? 1.0f : 0.4f;
			AddNode<Block>(&bc);
		}
	}

	// Trigger.
	{

	}
}

