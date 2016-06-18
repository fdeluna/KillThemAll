#include "PhysicsManager.h"

template<> PhysicsManager* Ogre::Singleton<PhysicsManager>::msSingleton = 0;

PhysicsManager::PhysicsManager(Ogre::SceneManager* sceneManager, bool debug) : _sceneManager(sceneManager), _debug(debug) {

	// Creacion del modulo de debug visual de Bullet
	_debugDrawer = new OgreBulletCollisions::DebugDrawer();
	_debugDrawer->setDrawWireframe(true);
	Ogre::SceneNode *debugNode = _sceneManager->getRootSceneNode()->createChildSceneNode("debugNode", Ogre::Vector3::ZERO);
	debugNode->attachObject(static_cast <Ogre::SimpleRenderable *>(_debugDrawer));

	// Creacion del mundo (definicion de limites y gravedad)
	Ogre::AxisAlignedBox worldBounds = Ogre::AxisAlignedBox(
		Ogre::Vector3(-10000, -10000, -10000),
		Ogre::Vector3(10000, 10000, 10000));
	Ogre::Vector3 gravity = Ogre::Vector3(0, -15, 0);

	_world = new OgreBulletDynamics::DynamicsWorld(_sceneManager, worldBounds, gravity);
	_world->setDebugDrawer(_debugDrawer);
	_world->setShowDebugShapes(_debug);
}

PhysicsManager::~PhysicsManager() {
	if (_debugDrawer) {
		delete _debugDrawer;
		_world->setDebugDrawer(nullptr);
	}

	if (_world) {
		delete _world;
	}
}

Ogre::Vector3& PhysicsManager::getMouseWorldPosition(float x, float y){

	Ogre::Camera* cam = _sceneManager->getCamera("PlayState");
	Ogre::Ray ray = cam->getCameraToViewportRay(x, y);	
	Ogre::Vector3 position;
	
	OgreBulletCollisions::CollisionClosestRayResultCallback cQuery = OgreBulletCollisions::CollisionClosestRayResultCallback(ray, _world, 10000);	
	_world->launchRay(cQuery);

	if (cQuery.doesCollide()) {
		position = cQuery.getCollisionPoint();
	}
	return position;
}


void PhysicsManager::updatePhysics(Ogre::Real deltaTime) {
	_world->stepSimulation(deltaTime, 50);
	checkCollisions();
}

void PhysicsManager::checkCollisions() {
	btCollisionWorld *bulletWorld = _world->getBulletCollisionWorld();
	int numManifolds = bulletWorld->getDispatcher()->getNumManifolds();
	for (int i = 0; i < numManifolds; i++) {
		btPersistentManifold *contactManifold = bulletWorld->getDispatcher()->getManifoldByIndexInternal(i);
		int numContacts = contactManifold->getNumContacts();
		if (numContacts > 0) {
			btCollisionObject *obA = (btCollisionObject*)(contactManifold->getBody0());
			btCollisionObject *obB = (btCollisionObject*)(contactManifold->getBody1());
			GameObject *gA = (GameObject*)obA->getUserPointer();
			GameObject *gB = (GameObject*)obB->getUserPointer();

			if (gA && gA->isActive()) {
				gA->collision(gB);
			}

			if (gB && gB->isActive()) {
				gB->collision(gA);
			}
		}
	}
}



PhysicsManager* PhysicsManager::getSingletonPtr() {
	return msSingleton;
}

PhysicsManager& PhysicsManager::getSingleton() {
	assert(msSingleton);
	return *msSingleton;
}