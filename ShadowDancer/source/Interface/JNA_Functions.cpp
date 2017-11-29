//
//  JNA_Functions.cpp
//
//  Created on: Dec 18, 2014
//      Author: wei
//

#include "JNA_Functions.h"

double e1(double w[]);

/// JNA interface function.
double evaluateFcns(double individual[], int func_index)
{
	double fitness = 0.0;
	switch(func_index)
	{
	case 1:
		fitness = e1(individual);
		break;
	default:
		break;
	}
	return fitness;
}

double e1(double w[])
{
	ANNWeights* arbi = new ANNWeights({6, 10, 3}, {false, true, false}, {false, true, true}, true);
	ANNWeights* w1 = new ANNWeights({17, 20, 2}, {false, true, false}, {false, true, true}, true);
	ANNWeights* w2 = new ANNWeights({14, 20, 2}, {false, true, false}, {false, true, true}, true);
	ANNWeights* w3 = new ANNWeights({11, 20, 2}, {false, true, false}, {false, true, true}, true);

	arbi->Randomize();
	//w1->Randomize();
	w2->Randomize();
	w3->Randomize();

	w1->Set(w);

	double fitness = 0.0;

	for(int i = 0; i < 3; i++) {
		b2Vec2 gravity;
		gravity.Set(0.0f, 0.0f);
		b2World* world = new b2World(gravity);
		J1_S_Field::Configuration fc;
		fc.MaxStep = 12000;
		fc.World = world;
		fc.TrainingMode = 1;
		J1_M_M1 monitor;

		assa2d::SceneMgr* scenemgr = new J1_S_Field(&fc, arbi, w1, w2, w3);
		scenemgr->Run(&monitor);

		delete scenemgr;
		delete world;

		fitness += monitor.GetFitness();
	}
	fitness /= 3.0f;

	delete arbi;
	delete w1;
	delete w2;
	delete w3;

	return fitness;
}
