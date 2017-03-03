//
//  JNA_Functions.cpp
//
//  Created on: Dec 18, 2014
//      Author: wei
//

#include "JNA_Functions.h"

double test(double w[]);


double evaluateFcns(double individual[], int func_index)
{
	double fitness = 0.0;
	switch(func_index)
	{
	case 0:
		fitness = test(individual);
		break;
	default:
		break;
	}
	return fitness;
}

double test(double w[])
{
	ANNWeights* weights = new ANNWeights({8, 2}, {false, false}, {false, true});
	weights->Set(w);

	FScene::Configuration fc;
	FMonitor monitor;
	assa2d::SceneMgr* scenemgr = new FScene(&fc, weights);
	scenemgr->Run(&monitor);

	delete scenemgr;
	delete weights;

	return monitor.fitness;
}


