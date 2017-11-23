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

		wc.Id = 1000;
		wc.StartPoint = b2Vec2(41.42136f, 100.0f);
		wc.EndPoint = b2Vec2(-41.42136f, 100.0f);
		AddNode<Wall>(&wc);

		wc.Id = 1001;
		wc.StartPoint = b2Vec2(-41.42136f, 100.0f);
		wc.EndPoint = b2Vec2(-100.0f, 41.42136f);
		AddNode<Wall>(&wc);

		wc.Id = 1002;
		wc.StartPoint = b2Vec2(-100.0f, 41.42136f);
		wc.EndPoint = b2Vec2(-100.0f, -41.42136f);
		AddNode<Wall>(&wc);

		wc.Id = 1003;
		wc.StartPoint = b2Vec2(-100.0f, -41.42136f);
		wc.EndPoint = b2Vec2(-41.42136f, -100.0f);
		AddNode<Wall>(&wc);

		wc.Id = 1004;
		wc.StartPoint = b2Vec2(-41.42136f, -100.0f);
		wc.EndPoint = b2Vec2(41.42136f, -100.0f);
		AddNode<Wall>(&wc);

		wc.Id = 1005;
		wc.StartPoint = b2Vec2(41.42136f, -100.0f);
		wc.EndPoint = b2Vec2(100.0f, -41.42136f);
		AddNode<Wall>(&wc);

		wc.Id = 1006;
		wc.StartPoint = b2Vec2(100.0f, -41.42136f);
		wc.EndPoint = b2Vec2(100.0f, 41.42136f);
		AddNode<Wall>(&wc);

		wc.Id = 1007;
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
		bc.StaticBody = true;
		bc.CircleShape.m_radius = 4.0f;
		bc.Tag = MAKE_TAG('r', 'e', 's', 'o');
		for(int i = 0; i < 2; i++) {
			for(int j = 0; j < 2; j++) {
				bc.Id = 100 + i*2 + j;
				bc.Position.Set(-16.0f + 32*i, -16.0f + 32*j);
				AddNode<Block>(&bc);
			}
		}
	}

	// Packages.
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

