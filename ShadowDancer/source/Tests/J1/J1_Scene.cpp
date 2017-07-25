/*
 * J1_Scene.cpp
 *
 *  Created on: Mar 2, 2017
 *      Author: wei
 */

#include "J1_Scene.h"

//J1_Scene::J1_Scene(Configuration* conf, ANNWeights* weights,
//		std::pair<float32, float32> goodfood, std::pair<float32, float32> badfood) : assa2d::SceneMgr(conf) {
//	{
//		Wall::Configuration wc;
//
//		wc.Tag = MAKE_TAG('w', 'a', 'l', 'l');
//
//		wc.Id = 1000;
//		wc.StartPoint = b2Vec2(-50.0f, -50.0f);
//		wc.EndPoint = b2Vec2(50.0f, -50.0f);
//		AddNode<Wall>(&wc);
//
//		wc.Id = 1001;
//		wc.StartPoint = b2Vec2(50.0f, -50.0f);
//		wc.EndPoint = b2Vec2(50.0f, 50.0f);
//		AddNode<Wall>(&wc);
//
//		wc.Id = 1002;
//		wc.StartPoint = b2Vec2(50.0f, 50.0f);
//		wc.EndPoint = b2Vec2(-50.0f, 50.0f);
//		AddNode<Wall>(&wc);
//
//		wc.Id = 1003;
//		wc.StartPoint = b2Vec2(-50.0f, 50.0f);
//		wc.EndPoint = b2Vec2(-50.0f, -50.0f);
//		AddNode<Wall>(&wc);
//	}
//
//	{
//		srand(time(NULL));
//		PRobot::Configuration rc;
//
//		rc.Tag = MAKE_TAG('r', 'o', 'b', 'o');
//
//		for(int32 i = 0; i < 6; i++) {
//			for(int32 j = 0; j < 6; j++) {
//				float32 x, y;
//                x = -10.0f + i * 4.0f + assa2d::RandomFloat()*0.7;
//                y = -10.0f + j * 4.0f + assa2d::RandomFloat()*0.7;
//
//                rc.Id = i*6+j;
//                rc.Position.Set(x, y);
//                rc.Angle = assa2d::RandomFloat(0, 6);
//
//                auto robot = AddNode<PRobot>(&rc);
//                robot -> m_ann ->SetWeights(weights);
//			}
//		}
//	}
//
//	{
//		Block::Configuration bc;
//		bc.StaticBody = true;
//		bc.CircleShape.m_radius = 4.0f;
//		bc.Tag = MAKE_TAG('o', 'b', 's', 't');
//		for(int i = 0; i < 2; i++) {
//			for(int j = 0; j < 2; j++) {
//				bc.Id = 100 + i*2 + j;
//				bc.Position.Set(-16.0f + 32*i, -16.0f + 32*j);
//				AddNode<Block>(&bc);
//			}
//		}
//	}
//
//	{
//		Block::Configuration bc;
//		bc.Tag = MAKE_TAG('f', 'o', 'o', 'd');
//
//		bc.Id = 290;
//		bc.Position.Set(200.0f, 200.0f);
//		bc.CircleShape.m_radius = 1.0f;
//		AddNode<Block>(&bc);
//		bc.Id = 291;
//		bc.Position.Set(210.0f, 210.0f);
//		AddNode<Block>(&bc);
//
//		for(std::size_t i = 200; i < 206; i++) {
//			bc.Id = i;
//
//			float32 x, y;
//			do {
//				x = assa2d::RandomFloat(-45, 45);
//				y = assa2d::RandomFloat(-45, 45);
//			} while((x>-22.0f&&x<22.0f) && (y>-22.0f&&y<22.0f));
//			bc.Position.Set(x, y);
//
//			bool isbadfood = (i-200) > 2 ? true : false;
//			bc.CircleShape.m_radius = isbadfood ? 2 : 4;
//			bc.Density = isbadfood ? 1.0f : 0.4f;
//			AddNode<Block>(&bc);
//		}
//	}
//
//	{
//		PNest::Configuration nc;
//		nc.GoodFood = goodfood;
//		nc.BadFood = badfood;
//		nc.Id = 9999;
//		nc.LeftTop = b2Vec2(-12.0f, 12.0f);
//		nc.RightBottom = b2Vec2(12.0f, -12.0f);
//		nc.TargetTag = MAKE_TAG('f', 'o', 'o', 'd');
//		m_nest = AddNode<PNest>(&nc);
//	}
//
//	m_food_list = &GetNodesByTag(MAKE_TAG('f', 'o', 'o', 'd'));
//}

