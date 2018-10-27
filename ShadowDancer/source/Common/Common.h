/*
 * Common.h
 *
 *  Created on: Jun 15, 2017
 *      Author: wei
 */

#ifndef COMMON_COMMON_H_
#define COMMON_COMMON_H_

#include <stdexcept>
#include <numeric>
#include <iostream>

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

// Get random positions.
inline std::vector<b2Vec2> GetRandomPositions(float32 lower_raidus, float32 upper_raidus, unsigned int number, float32 distance) {
	std::vector<b2Vec2> pos;
	while(pos.size()<number) {
		b2Vec2 p;
		bool flag;
		unsigned int attempt = 0;
		do {
			float32 r = assa2d::RandomFloat(lower_raidus, upper_raidus);
			float32 a = assa2d::RandomFloat(0, M_PI * 2.0f);

			p.Set(r*std::cos(a), r*std::sin(a));

			flag = false;
			for(auto& i : pos) {
				if((i-p).LengthSquared() < distance*distance) {
					flag = true;
				}
			}

			attempt++;
			if(attempt > number*1000) {
				throw std::runtime_error("GetRandomPositions()(...) : too many attempts.");
			}
		} while(flag);
		pos.push_back(p);
	}
	return pos;
}



// Get random positions with fixed total distance.
inline std::vector<b2Vec2> GetFixedTotalRandomPositions(float32 lower_radius, float32 upper_radius, float32 average_radius,
		unsigned int number, float32 distance, std::vector<b2Vec2>* external_pos) {
	std::vector<b2Vec2> pos;

	std::vector<float32> radius;
	do {
		radius.clear();
		float32 total_r = 0.0f;
		for(unsigned int i = 0; i < number; i ++) {
			float32 r;
			if(total_r > average_radius * radius.size()) {
				r = assa2d::RandomFloat(lower_radius, average_radius);
			} else {
				r = assa2d::RandomFloat(average_radius, upper_radius);
			}
			if(radius.size() == number-1) {
				r = average_radius*number - total_r;
			}
			total_r += r;
			radius.push_back(r);
		}
	} while(radius[number-1] < lower_radius || radius[number-1] > upper_radius);

	for(unsigned int i = 0; i < number; i++) {
		b2Vec2 p;
		bool flag;
		unsigned int attempt = 0;
		do {
			float32 r = radius[i];
			float32 a = assa2d::RandomFloat(0, M_PI * 2.0f);

			p.Set(r*std::cos(a), r*std::sin(a));

			flag = false;
			for(auto& i : pos) {
				if((i-p).LengthSquared() < distance*distance) {
					flag = true;
				}
			}
			if(external_pos != nullptr) {
				for(auto& i : *external_pos) {
					if((i-p).LengthSquared() < distance*distance) {
						flag = true;
					}
				}
			}

			attempt++;
			if(attempt > number*1000) {
				throw std::runtime_error("GetFixedTotalRandomPositions()(...) : too many attempts.");
			}
		} while(flag);
		pos.push_back(p);
	}
	return pos;
}

// Get a random position.
inline b2Vec2 GetRandomPosition(float32 lower_radius, float32 upper_radius) {
	b2Vec2 p;
	float32 r = assa2d::RandomFloat(lower_radius, upper_radius);
	float32 a = assa2d::RandomFloat(0, M_PI * 2.0f);
	p.Set(r*std::cos(a), r*std::sin(a));
	return p;
}

#endif /* COMMON_COMMON_H_ */
