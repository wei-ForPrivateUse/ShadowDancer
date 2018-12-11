/*
 * J1_T_Nest.h
 *
 *  Created on: Nov 24, 2017
 *      Author: wei
 */

#ifndef TESTS_J1_J1_T_NEST_H_
#define TESTS_J1_J1_T_NEST_H_

#include <assassin2d/assassin2d.h>

#include "J1_O_Package.h"

class J1_T_Nest : public assa2d::Trigger {
public:
	struct Configuration : public assa2d::Trigger::Configuration {
		b2Vec2 Position;					// Position of the nest.
		float32 Radius = 15.0f;				// Radius of the nest.

		std::size_t Resource = 30; 			// Number of resources.
		std::size_t Package = 5;			// Number of packages.
		int ResourceSupplement = -1;		// Policy for resource supplement,
											// -1 means recreate immediately.
		int PackageSupplement = -1;			// Policy for package supplement,
											// -1 means recreate immediately.
		unsigned int ResourceMask = 0x2;	// Mask of resources to tell
											// which are generated by packages.
		std::size_t NewResourceId = 0; 		// Start id for new resources.
		std::size_t NewPackageId = 0;		// Start id for new packages.
	};

	J1_T_Nest(Configuration* conf);
	virtual ~J1_T_Nest() { };

	/// Getters.
	std::size_t GetPackageCollected() const {
		return m_package_collected;
	}

	std::size_t GetUnmaskedResourceCollected() const {
		return m_unmasked_resource_collected;
	}

	std::size_t GetMaskedResourceCollected() const {
		return m_masked_resource_collected;
	}

	std::size_t GetResourceCollected() const {
		return GetUnmaskedResourceCollected() + GetMaskedResourceCollected();
	}

	/// Check a position.
	bool IsInNest(b2Vec2 const& position) {
		return (position-m_position).LengthSquared() < m_radius*m_radius;
	}

protected:
	/// Update and check packages & resources.
	virtual void Act() override;

	/// Add a package.
	void AddPackage();

	/// Add a unmasked resource.
	void AddUnmaskedResource();

	/// Add masked resources.
	void AddMaskedResources(std::vector<b2Vec2> const& pos);

private:
	b2Vec2 m_position;
	float32 m_radius;

	std::size_t m_max_resource;
	std::size_t m_max_package;
	int m_resource_supplement;
	int m_package_supplement;
	unsigned int m_resource_mask;

	std::size_t m_package_collected;
	std::size_t m_unmasked_resource_collected;
	std::size_t m_masked_resource_collected;	//resources from package.

	std::size_t m_new_resource_id;
	std::size_t m_new_package_id;
};

#endif /* TESTS_J1_J1_T_NEST_H_ */