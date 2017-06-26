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
	case bul::dynamics::Node_Type::Object:
		return static_cast<assa2d::Object*>(node)->GetPosition();
		break;
	default:
		throw std::runtime_error("GetNodePosition()(...) : unexpected node type.");
		break;
	}
}

#endif /* COMMON_COMMON_H_ */
