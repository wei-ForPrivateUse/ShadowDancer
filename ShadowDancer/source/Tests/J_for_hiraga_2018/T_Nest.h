/*
 * T_Nest.h
 *
 *  Created on: Oct 2, 2018
 *      Author: wei
 */

#ifndef TESTS_J_FOR_HIRAGA_2018_T_NEST_H_
#define TESTS_J_FOR_HIRAGA_2018_T_NEST_H_

#include <assassin2d/assassin2d.h>

#include "Common/Common.h"

class T_Nest : public assa2d::Trigger {
public:
	struct Configuration : public assa2d::Trigger::Configuration {
		float32 Range;
		std::size_t TargetTag = 0;

		float32 FoodRadius = 5.0f;
		float32 PoisonRadius = 4.0f;
		float32 FoodDensity = 0.12f;
		float32 PoisonDensity = 0.12f;

		bool Recreate = true;
		std::size_t NewResourceID = 200000;
	};

	T_Nest(Configuration* conf);
	virtual ~T_Nest() { };

	std::size_t GetPoisonCount() const {
		return poison_count;
	}

	std::size_t GetFoodCount() const {
		return food_count;
	}

protected:
	virtual void Act() override;

private:
	float32 m_range;
	std::size_t m_target_tag;

	float32 m_food_radius;
	float32 m_poison_radius;
	float32 m_food_density;
	float32 m_poison_density;

	bool m_recreate;
	std::size_t m_new_resource_id;

	std::size_t poison_count;
	std::size_t food_count;
};

#endif /* TESTS_J_FOR_HIRAGA_2018_T_NEST_H_ */
