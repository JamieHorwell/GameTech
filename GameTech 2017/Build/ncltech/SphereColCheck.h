#pragma once
#include "PhysicsNode.h"
class SphereColCheck
{
public:
	SphereColCheck();
	~SphereColCheck();
	
	static bool checkSphereCollision(PhysicsNode* pNodeA, PhysicsNode* pNodeB);
};

