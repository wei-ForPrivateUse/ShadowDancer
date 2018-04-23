/*
 * J0_T_Nest.h
 *
 *  Created on: Apr 20, 2018
 *      Author: wei
 */

#ifndef TESTS_J0_J0_T_NEST_H_
#define TESTS_J0_J0_T_NEST_H_

#include <assassin2d/assassin2d.h>

class J0_T_Nest : public assa2d::Trigger {
public:
	struct Configuration : public assa2d::Trigger::Configuration {
		b2Vec2 Internal;

		std::size_t TargetTag = 0;

		bool recreate = false;

		std::size_t NewResourceID = 0;
	};

	J0_T_Nest(Configuration* conf);
	virtual ~J0_T_Nest() { };

	std::size_t GetCount() const {
		return count;
	}

protected:
	virtual void Act() override;

private:
	b2Vec2 m_internal;

	std::size_t m_target_tag;

	bool m_recreate;

	std::size_t count;

	std::size_t m_new_resource_id;
};

#endif /* TESTS_J0_J0_T_NEST_H_ */
