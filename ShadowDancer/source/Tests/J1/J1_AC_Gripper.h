/*
 * J1_AC_Gripper.h
 *
 *  Created on: Nov 14, 2017
 *      Author: wei
 */

#ifndef TESTS_J1_J1_AC_GRIPPER_H_
#define TESTS_J1_J1_AC_GRIPPER_H_

#include <assassin2d/assassin2d.h>

#include "Common/Object/Block.h"

class J1_AC_Gripper : public assa2d::Component {
public:
	struct Configuration : public assa2d::Component::Configuration {
		std::size_t TargetTag = MAKE_TAG('r', 'e', 's', 'o');;
		unsigned int TargetStatusMask = 0x1;
		int RequiredMode = 2;

		std::size_t OutputIndex = 0;

		std::size_t NullId = 999999;
	};

	J1_AC_Gripper(Configuration* conf);
	virtual ~J1_AC_Gripper();

protected:
	/// Grip / drop if necessary.
	virtual void Act() override;

	/// Find touching resources.
	virtual void PreSolve(Node* node, b2Contact* contact, const b2Manifold* oldManifold) override;

	/// Grip the touching resource.
	void Grip();

	/// Drop the current resource.
	void Drop();

private:
	std::size_t m_target_tag;
	unsigned int m_target_status_mask;
	int m_required_mode;

	std::size_t m_output_index;

	std::size_t m_null_id;

	std::size_t m_gripping_resource_id;
	b2Joint* m_gripping_joint;
	std::size_t m_touching_resource_id;
};

#endif /* TESTS_J1_J1_AC_GRIPPER_H_ */
