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

		wc.Id = 1000;
		wc.StartPoint = b2Vec2(-36.2132034f, -15.0f);
		wc.EndPoint = b2Vec2(-15.0f, -36.2132034f);
		wall[0] = AddNode<Wall>(&wc);

		wc.Id = 1001;
		wc.StartPoint = b2Vec2(-15.0f, -36.2132034f);
		wc.EndPoint = b2Vec2(15.0f, -36.2132034f);
		wall[1] = AddNode<Wall>(&wc);

		wc.Id = 1002;
		wc.StartPoint = b2Vec2(15.0f, -36.2132034f);
		wc.EndPoint = b2Vec2(36.2132034f, -15.0f);
		wall[2] = AddNode<Wall>(&wc);

		wc.Id = 1003;
		wc.StartPoint = b2Vec2(36.2132034f, -15.0f);
		wc.EndPoint = b2Vec2(36.2132034f, 15.0f);
		wall[3] = AddNode<Wall>(&wc);

		wc.Id = 1004;
		wc.StartPoint = b2Vec2(36.2132034f, 15.0f);
		wc.EndPoint = b2Vec2(15.0f, 36.2132034f);
		wall[4] = AddNode<Wall>(&wc);

		wc.Id = 1005;
		wc.StartPoint = b2Vec2(15.0f, 36.2132034f);
		wc.EndPoint = b2Vec2(-15.0f, 36.2132034f);
		wall[5] = AddNode<Wall>(&wc);

		wc.Id = 1006;
		wc.StartPoint = b2Vec2(-15.0f, 36.2132034f);
		wc.EndPoint = b2Vec2(-36.2132034f, 15.0f);
		wall[6] = AddNode<Wall>(&wc);

		wc.Id = 1007;
		wc.StartPoint = b2Vec2(-36.2132034f, 15.0f);
		wc.EndPoint = b2Vec2(-60.0f, 15.0f);
		wall[7] = AddNode<Wall>(&wc);

		wc.Id = 1008;
		wc.StartPoint = b2Vec2(-60.0f, 15.0f);
		wc.EndPoint = b2Vec2(-60.0f, -15.0f);
		wall[8] = AddNode<Wall>(&wc);

		wc.Id = 1009;
		wc.StartPoint = b2Vec2(-60.0f, -15.0f);
		wc.EndPoint = b2Vec2(-36.2132034f, -15.0f);
		wall[9] = AddNode<Wall>(&wc);
	}

	{
		srand(time(NULL));
		Robot::Configuration rc;

		for(int32 i = 0; i < 5; i++) {
			for(int32 j = 0; j < 6; j++) {
				float32 x, y;
                x = -56.0f + i * 3.4f + assa2d::RandomFloat()*0.7;
                y = -12.0f + j * 4.8 + assa2d::RandomFloat()*0.7;

                rc.Id = i*6+j;
                rc.Position.Set(x, y);
                rc.Angle = assa2d::RandomFloat(0, 6);

                robot[i*6+j] = AddNode<Robot>(&rc);
                robot[i*6+j] -> _M_ann ->SetWeights(weights);
			}
		}
	}

	{
		Block::Configuration bc;
		bc.Id = 100;
		bc.Tag = MAKE_TAG('p', 'o', 'i', 's');
		bc.Position.Set(assa2d::RandomFloat(-22, 22), assa2d::RandomFloat(-22, 22));
		bc.CircleShape.m_radius = 8;
		block[0] = AddNode<Block>(&bc);

		bc.Id = 101;
		bc.Position.Set(assa2d::RandomFloat(-16, 16), assa2d::RandomFloat(-16, 16));
		bc.CircleShape.m_radius = 9;
		block[1] = AddNode<Block>(&bc);

		bc.Id = 102;
		bc.Tag = MAKE_TAG('f', 'o', 'o', 'd');
		bc.Position.Set(assa2d::RandomFloat(-25, 25), assa2d::RandomFloat(-25, 25));
		bc.CircleShape.m_radius = 2;
		block[2] = AddNode<Block>(&bc);

		bc.Id = 103;
		bc.Position.Set(assa2d::RandomFloat(-25, 25), assa2d::RandomFloat(-25, 25));
		bc.CircleShape.m_radius = 3;
		block[3] = AddNode<Block>(&bc);

		bc.Id = 104;
		bc.Position.Set(assa2d::RandomFloat(-25, 25), assa2d::RandomFloat(-25, 25));
		bc.CircleShape.m_radius = 2.5;
		block[4] = AddNode<Block>(&bc);
	}

}

FScene::~FScene() {
	// TODO Auto-generated destructor stub
}

