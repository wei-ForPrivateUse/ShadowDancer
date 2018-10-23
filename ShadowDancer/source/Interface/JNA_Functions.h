//
//  JNA_Functions.h
//
//  Created on: Dec 18, 2014
//      Author: wei
//

#ifndef __Interface_for_JNA__
#define __Interface_for_JNA__

#include "../ShadowDancer.h"

extern "C"
{
	double evaluateFcns(double individual[], int func_index, long long_buffer[], double double_buffer[], int add_info_length);
}

#endif /* __Interface_for_JNA__ */
