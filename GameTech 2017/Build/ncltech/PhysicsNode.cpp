#include "PhysicsNode.h"
#include "PhysicsEngine.h"


void PhysicsNode::IntegrateForVelocity(float dt)
{
	Vector3 tmp_force = this->force;
	if (invMass > 0.0f)
	{
		tmp_force += PhysicsEngine::Instance()->GetGravity() / invMass;
	}

	/* TUTORIAL 2 CODE */
	this->linVelocity = SemiImplicit::IntegVelocity(this->linVelocity, tmp_force*this->invMass, dt );
	this->linVelocity = this->linVelocity * PhysicsEngine::Instance()->GetDampingFactor();


	//angular velocity
	angVelocity += invInertia * torque * dt;
	angVelocity = angVelocity * PhysicsEngine::Instance()->GetDampingFactor();
}

/* Between these two functions the physics engine will solve for velocity
   based on collisions/constraints etc. So we need to integrate velocity, solve 
   constraints, then use final velocity to update position. 
*/

void PhysicsNode::IntegrateForPosition(float dt)
{
	/* TUTORIAL 2 CODE */
	this->position = SemiImplicit::IntegPos(this->position, this->linVelocity, dt);

	orientation = orientation + Quaternion(angVelocity * dt * 0.5, 0.0f) * orientation;
	orientation.Normalise();


	//Finally: Notify any listener's that this PhysicsNode has a new world transform.
	// - This is used by GameObject to set the worldTransform of any RenderNode's. 
	//   Please don't delete this!!!!!
	FireOnUpdateCallback();
}