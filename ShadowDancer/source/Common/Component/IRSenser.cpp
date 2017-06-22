/*
 * IRSenser.cpp
 *
 *  Created on: Mar 3, 2017
 *      Author: wei
 */

#include "IRSenser.h"

IRSenser::IRSenser(Configuration* conf) : assa2d::Component(conf) {
	_M_position = conf->Position;
	_M_angle = conf->Angle;

	_M_range = conf->Range;

	_M_output_index = conf->OutputIndex;
}

void IRSenser::Act() {
	assa2d::Actor* actor = static_cast<assa2d::Actor*>(GetActor());
	b2Body* body = static_cast<assa2d::Component*>(actor->GetMainComponent())->GetBody();

	b2Vec2 sp, ep;
	sp = body->GetWorldPoint(_M_position);
	ep.x = sp.x + _M_range * cosf(body->GetAngle() + _M_angle);
	ep.y = sp.y + _M_range * sinf(body->GetAngle() + _M_angle);

	IRRayCastClosestCallback callback(static_cast<assa2d::Actor*>(GetActor()));
	GetWorld() -> RayCast(&callback, sp, ep);

	if(callback._M_hit) {
		SetSharedData<float>(_M_output_index, (callback._M_point - sp).Length() / _M_range);
	} else {
		SetSharedData<float>(_M_output_index, 1.0f);
	}
}

