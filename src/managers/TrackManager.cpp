#include <TrackManager.h>

template<> TrackManager* Ogre::Singleton<TrackManager>::msSingleton = 0;

TrackManager::TrackManager() {
	
	mResourceType = "Track";
	
	mLoadOrder = 30.f;
	
	Ogre::ResourceGroupManager::getSingleton()._registerResourceManager(mResourceType, this);
}

TrackManager::~TrackManager() {
	
	Ogre::ResourceGroupManager::getSingleton()._unregisterResourceManager(mResourceType);
}

TrackPtr TrackManager::load(const Ogre::String& name, const Ogre::String& group) {
	
	TrackPtr trackPtr = createOrRetrieve(name, group, false, 0, 0).first.staticCast<Track>();

	
	trackPtr->load();

	return trackPtr;
}

TrackManager& TrackManager::getSingleton() {
	assert(msSingleton);
	return (*msSingleton);
}

TrackManager* TrackManager::getSingletonPtr() {
	assert(msSingleton);
	return msSingleton;
}

Ogre::Resource* TrackManager::createImpl(const Ogre::String& resource_name,
	Ogre::ResourceHandle handle,
	const Ogre::String& resource_group,
	bool isManual,
	Ogre::ManualResourceLoader* loader,
	const Ogre::NameValuePairList* createParams) {
	return new Track(this, resource_name, handle, resource_group, isManual, loader);
}
