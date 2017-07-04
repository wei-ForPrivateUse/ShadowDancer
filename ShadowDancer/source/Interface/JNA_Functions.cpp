//
//  JNA_Functions.cpp
//
//  Created on: Dec 18, 2014
//      Author: wei
//

#include "JNA_Functions.h"

double test(double w[], bool flag);
double test1(double w[], std::size_t flag);

/// JNA interface function.
double evaluateFcns(double individual[], int func_index)
{
	double fitness = 0.0;
	switch(func_index)
	{
	case 0:
		fitness = test(individual, false);
		break;
	case 1:
		fitness = test(individual, true);
		break;
	case 100:
		fitness = test1(individual, 0);
		break;
	case 101:
		fitness = test1(individual, 1);
		break;
	case 102:
		fitness = test1(individual, 2);
		break;
	default:
		break;
	}
	return fitness;
}

double test(double w[], bool flag)
{
	ANNWeights* weights = new ANNWeights({28, 20, 2}, {false, true, false}, {false, true, true}, true);
	weights->Set(w);

	double fitness = 0.0;

	for(int i = 0; i < 8; i++) {
		b2Vec2 gravity;
		gravity.Set(0.0f, 0.0f);
		b2World* world = new b2World(gravity);
		FScene::Configuration fc;
		fc.MaxStep = 6000;
		fc.World = world;
		FMonitor monitor(flag);

		assa2d::SceneMgr* scenemgr = new FScene(&fc, weights);
		scenemgr->Run(&monitor);

		delete scenemgr;
		delete world;

		fitness += monitor.GetFitness();
	}
	fitness /= 8.0f;

	delete weights;

	return fitness;
}

double test1(double w[], std::size_t flag) {
	ANNWeights* weights = new ANNWeights({28, 20, 2}, {false, true, false}, {false, true, true}, true);
	weights->Set(w);

	double fitness = 0.0;

	for(int i = 0; i < 5; i++) {
		b2Vec2 gravity;
		gravity.Set(0.0f, 0.0f);
		b2World* world = new b2World(gravity);

		PScene::Configuration pc;
		pc.MaxStep = 12000;
		pc.World = world;
		PMonitor monitor(flag);

		assa2d::SceneMgr* scenemgr = new PScene(&pc, weights);
		scenemgr->Run(&monitor);

		delete scenemgr;
		delete world;

		fitness += monitor.GetFitness();
	}
	fitness /= 5.0f;

	delete weights;

	return fitness;
}
