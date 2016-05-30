#include "RigidBodyComponent.h"

RigidBodyComponent::RigidBodyComponent(GameObject* gameObject, GameObjectType type, SceneNodeComponent* sceneNodeComponent) : Component(gameObject), _shape(nullptr), _rigidBody(nullptr){
	

	switch (type)
	{
	case OBSTACLE:
		_shape = new OgreBulletCollisions::BoxCollisionShape(Ogre::Vector3(0.5, 0.5, 0.5));;
		break;
	case MAP_FLOOR:		
		std::cout << "Plane SCALE:" << sceneNodeComponent->getSceneNode()->getScale() << std::endl;		
		std::shared_ptr<OgreBulletCollisions::VertexIndexToShape> meshToShapeConverter;
		meshToShapeConverter = std::make_shared<OgreBulletCollisions::StaticMeshToShapeConverter>(sceneNodeComponent->getEntity());
		_shape = meshToShapeConverter->createConvex();

		break;		
	}

	Ogre::String rigidName(sceneNodeComponent->getSceneNode()->getName());
	Ogre::SceneNode* sceneNode = sceneNodeComponent->getSceneNode();
	rigidName.append("RigidBody");
	PhysicsManager* physicsMgr = PhysicsManager::getSingletonPtr();

	
	

	_rigidBody = new OgreBulletDynamics::RigidBody(rigidName, physicsMgr->getWorld(), 0, 1);
	_rigidBody->setShape(sceneNode, _shape, 0.01, 1, 100.0, sceneNode->getPosition(), sceneNode->getOrientation());	
	
			
	_rigidBody->getBulletRigidBody()->setLinearFactor(btVector3(0, 0, 0));
	_rigidBody->getBulletRigidBody()->setAngularFactor(btVector3(0, 0, 0));
	_rigidBody->disableDeactivation();
		
	_rigidBody->getBulletRigidBody()->setUserPointer(gameObject);
}

RigidBodyComponent::~RigidBodyComponent(){
	if (_rigidBody) {		
		delete _rigidBody;		
	}
	if (_shape) {
		delete _shape;
	}
}
void RigidBodyComponent::setWorldPosition(Ogre::Vector3 position){
	
	btTransform transform; //Declaration of the btTransform
	transform.setIdentity(); //This function put the variable of the object to default. The ctor of btTransform doesnt do it.
	transform.setOrigin(OgreBulletCollisions::OgreBtConverter::to(position)); //Set the new position/origin
	_rigidBody->getBulletRigidBody()->setWorldTransform(transform);

}