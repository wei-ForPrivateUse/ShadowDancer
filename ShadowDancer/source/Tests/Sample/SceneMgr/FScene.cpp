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
		wc.StartPoint = b2Vec2(-25.0f, -25.0f);
		wc.EndPoint = b2Vec2(25.0f, -25.0f);
		AddNode<Wall>(&wc);

		wc.Id = 1001;
		wc.StartPoint = b2Vec2(25.0f, -25.0f);
		wc.EndPoint = b2Vec2(25.0f, 25.0f);
		AddNode<Wall>(&wc);

		wc.Id = 1002;
		wc.StartPoint = b2Vec2(25.0f, 25.0f);
		wc.EndPoint = b2Vec2(-25.0f, 25.0f);
		AddNode<Wall>(&wc);

		wc.Id = 1003;
		wc.StartPoint = b2Vec2(-25.0f, 25.0f);
		wc.EndPoint = b2Vec2(-25.0f, -25.0f);
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
		bc.CircleShape.m_radius = 3;
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
		bc.Id = 200;
		bc.Position.Set(assa2d::RandomFloat(-22, 22), assa2d::RandomFloat(-22, 22));
		bc.CircleShape.m_radius = 2;
		AddNode<Block>(&bc);

		bc.Id = 201;
		bc.Position.Set(assa2d::RandomFloat(-16, 16), assa2d::RandomFloat(-16, 16));
		bc.CircleShape.m_radius = 3;
		AddNode<Block>(&bc);

		bc.Id = 202;
		bc.Position.Set(assa2d::RandomFloat(-25, 25), assa2d::RandomFloat(-25, 25));
		bc.CircleShape.m_radius = 1;
		AddNode<Block>(&bc);

		bc.Id = 203;
		bc.Position.Set(assa2d::RandomFloat(-25, 25), assa2d::RandomFloat(-25, 25));
		bc.CircleShape.m_radius = 3;
		AddNode<Block>(&bc);

		bc.Id = 204;
		bc.Position.Set(assa2d::RandomFloat(-25, 25), assa2d::RandomFloat(-25, 25));
		bc.CircleShape.m_radius = 2.5;
		AddNode<Block>(&bc);
	}

	{
		Nest::Configuration nc;
		nc.Id = 9999;
		nc.LeftTop = b2Vec2(-10.0f, 10.0f);
		nc.RightBottom = b2Vec2(10.0f, -10.0f);
		nc.TargetTag = MAKE_TAG('f', 'o', 'o', 'd');
		AddNode<Nest>(&nc);
	}

}

