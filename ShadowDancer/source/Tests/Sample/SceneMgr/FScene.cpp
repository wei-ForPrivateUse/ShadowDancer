/*
 * FScene.cpp
 *
 *  Created on: Mar 2, 2017
 *      Author: wei
 */

#include "FScene.h"

FScene::FScene(Configuration* conf, ANNWeights* weights) : assa2d::SceneMgr(conf) {
	{
		Wall::Configuration wc;

		wc.Tag = MAKE_TAG('w', 'a', 'l', 'l');

		wc.Id = 1000;
		wc.StartPoint = b2Vec2(-35.0f, -35.0f);
		wc.EndPoint = b2Vec2(35.0f, -35.0f);
		AddNode<Wall>(&wc);

		wc.Id = 1001;
		wc.StartPoint = b2Vec2(35.0f, -35.0f);
		wc.EndPoint = b2Vec2(35.0f, 35.0f);
		AddNode<Wall>(&wc);

		wc.Id = 1002;
		wc.StartPoint = b2Vec2(35.0f, 35.0f);
		wc.EndPoint = b2Vec2(-35.0f, 35.0f);
		AddNode<Wall>(&wc);

		wc.Id = 1003;
		wc.StartPoint = b2Vec2(-35.0f, 35.0f);
		wc.EndPoint = b2Vec2(-35.0f, -35.0f);
		AddNode<Wall>(&wc);
	}

	{
		srand(time(NULL));
		Robot::Configuration rc;

		rc.Tag = MAKE_TAG('r', 'o', 'b', 'o');

		for(int32 i = 0; i < 6; i++) {
			for(int32 j = 0; j < 6; j++) {
				float32 x, y;
                x = -7.5f + i * 3.0f + assa2d::RandomFloat()*0.7;
                y = -7.5f + j * 3.0f + assa2d::RandomFloat()*0.7;

                rc.Id = i*6+j;
                rc.Position.Set(x, y);
                rc.Angle = assa2d::RandomFloat(0, 6);

                auto robot = AddNode<Robot>(&rc);
                robot -> m_ann ->SetWeights(weights);
			}
		}
	}

	{
		Block::Configuration bc;
		bc.StaticBody = true;
		bc.CircleShape.m_radius = 3.5;
		bc.Tag = MAKE_TAG('o', 'b', 's', 't');
		for(int i = 0; i < 4; i++) {
			for(int j = 0; j < 2; j++) {
				bc.Id = 100 + i*2 + j;
				bc.Position.Set(-15.0f + 10*i, -15.0f + 30*j);
				AddNode<Block>(&bc);
			}
		}
	}

	{
		Block::Configuration bc;
		bc.Tag = MAKE_TAG('f', 'o', 'o', 'd');

		bc.Id = 290;
		bc.Position.Set(100.0f, 100.0f);
		bc.CircleShape.m_radius = 1.0f;
		AddNode<Block>(&bc);
		bc.Id = 291;
		bc.Position.Set(110.0f, 110.0f);
		AddNode<Block>(&bc);

		for(std::size_t i = 200; i < 206; i++) {
			bc.Id = i;

			float32 x, y;
			do {
				x = assa2d::RandomFloat(-30, 30);
				y = assa2d::RandomFloat(-30, 30);
			} while((x>-18.5f&&x<18.5f) && (y>-18.5f&&y<18.5f));
			bc.Position.Set(x, y);

			bool isbadfood = (i-200) > 2 ? true : false;
			bc.CircleShape.m_radius = isbadfood ? 1.5 : 5;
			bc.Density = isbadfood ? 1.0f : 0.25f;
			AddNode<Block>(&bc);
		}
	}

	{
		Nest::Configuration nc;
		nc.Id = 9999;
		nc.LeftTop = b2Vec2(-10.0f, 10.0f);
		nc.RightBottom = b2Vec2(10.0f, -10.0f);
		nc.TargetTag = MAKE_TAG('f', 'o', 'o', 'd');
		m_nest = AddNode<Nest>(&nc);
	}

	m_food_list = &GetNodesByTag(MAKE_TAG('f', 'o', 'o', 'd'));
}

