/*
 * J0ACGripper.h
 *
 *  Created on: Apr 19, 2018
 *      Author: wei
 */

#ifndef TESTS_J0_J0_AC_GRIPPER_H_
#define TESTS_J0_J0_AC_GRIPPER_H_

#include <assassin2d/assassin2d.h>

#include "Common/Object/Block.h"

#define CATCHED_FLAG 0x1

class J0_AC_Gripper : public assa2d::Component {
public:
	struct Configuration : public assa2d::Component::Configuration {
		std::size_t TargetTag = MAKE_TAG('r', 'e', 's', 'o');;
	};

	J0_AC_Gripper(Configuration* conf);
	virtual ~J0_AC_Gripper();

protected:
	/// Grip if possible.
	virtual void Act() override;

	/// Drop if necessary.
	virtual void Act_Anyway() override;

	/// Find touching resources.
	virtual void PreSolve(Node* node, b2Contact* contact, const b2Manifold* oldManifold) override;

	/// Grip the touching resource.
	void Grip();

	/// Drop the current resource.
	void Drop();

private:
	std::size_t m_target_tag;

	Block* m_gripping_resource;
	b2Joint* m_gripping_joint;

	Block* m_touching_resource;
};

#endif /* TESTS_J0_J0_AC_GRIPPER_H_ */
