/*
 * IRSenser.cpp
 *
 *  Created on: Mar 3, 2017
 *      Author: wei
 */

#include "IRSenser.h"

IRSenser::IRSenser(Configuration* conf) : assa2d::Component(conf) {
	m_position = conf->Position;
	m_angle = conf->Angle;

	m_range = conf->Range;

	m_output_index = conf->OutputIndex;
}

void IRSenser::Act() {
	assa2d::Actor* actor = static_cast<assa2d::Actor*>(GetActor());
	b2Body* body = static_cast<assa2d::Component*>(actor->GetMainComponent())->GetBody();

	b2Vec2 sp, ep;
	sp = body->GetWorldPoint(m_position);
	ep.x = sp.x + m_range * cosf(body->GetAngle() + m_angle);
	ep.y = sp.y + m_range * sinf(body->GetAngle() + m_angle);

	IRRayCastClosestCallback callback(static_cast<assa2d::Actor*>(GetActor()));
	GetWorld() -> RayCast(&callback, sp, ep);

	if(callback.m_hit) {
		SetSharedData<float>(m_output_index, (callback.m_point - sp).Length() / m_range);
	} else {
		SetSharedData<float>(m_output_index, 1.0f);
	}
}
