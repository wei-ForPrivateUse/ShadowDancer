/*
 * Common.h
 *
 *  Created on: Jun 15, 2017
 *      Author: wei
 */

#ifndef COMMON_COMMON_H_
#define COMMON_COMMON_H_

#include <stdexcept>

#include <assassin2d/assassin2d.h>

/// Get const-reference to the node's position.
inline b2Vec2 const& GetNodePosition(assa2d::Node* node) {
	switch(node->GetType()) {
	case bul::dynamics::Node_Type::Actor:
		return static_cast<assa2d::Actor*>(node)->GetMainComponent()->GetPosition();
		break;
	case bul::dynamics::Node_Type::Actor_Component:
		return static_cast<assa2d::Component*>(node)->GetPosition();
		break;
	case bul::dynamics::Node_Type::Object:
		return static_cast<assa2d::Object*>(node)->GetPosition();
		break;
	default:
		throw std::runtime_error("GetNodePosition()(...) : unexpected node type.");
		break;
	}
}

//
inline std::vector<b2Vec2> GetRandomPositions(float32 lower_bound, float32 upper_bound, int number, float32 distance) {
	std::vector<b2Vec2> pos;
	pos.resize(number);

	for(int index = 0, attempt = 0; index < number; index++) {
		b2Vec2 p;
		bool flag = false;

		do {
			float32 r = assa2d::RandomFloat(lower_bound, upper_bound);
			float32 a = assa2d::RandomFloat(0, M_PI * 2.0f);

			p.Set(r*std::cos(a), r*std::sin(a));

			for(auto& i : pos) {
				if((i-p).LengthSquared() < distance*distance) {
					flag = false;
				}
			}
		} while(flag);

		pos[index] = p;
	}

	return pos;
}

#endif /* COMMON_COMMON_H_ */
