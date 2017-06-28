//
//  JNA_Functions.cpp
//
//  Created on: Dec 18, 2014
//      Author: wei
//

#include "JNA_Functions.h"

double test(double w[], bool flag);

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

		fitness += monitor.GetFitness();
	}

	fitness /= 8.0f;

	delete weights;

	return fitness;
}


