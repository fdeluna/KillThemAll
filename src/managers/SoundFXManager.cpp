#include <SDL_mixer.h>

#include "SoundFXManager.h"

template<> SoundFXManager* Ogre::Singleton<SoundFXManager>::msSingleton = 0;

int SoundFXManager::_numChannels = 32;

SoundFXManager::SoundFXManager() {
	
	mResourceType = "SoundFX";
	
	mLoadOrder = 30.f;
	
	Ogre::ResourceGroupManager::getSingleton()._registerResourceManager(mResourceType, this);
	
	Mix_AllocateChannels(_numChannels);
}

SoundFXManager::~SoundFXManager() {
	
	Ogre::ResourceGroupManager::getSingleton()._unregisterResourceManager(mResourceType);
}

SoundFXPtr SoundFXManager::load(const Ogre::String& name, const Ogre::String& group) {
	
	SoundFXPtr soundFXPtr = createOrRetrieve(name, group, false, 0, 0).first.staticCast<SoundFX>();

	
	soundFXPtr->load();

	return soundFXPtr;
}

SoundFXManager& SoundFXManager::getSingleton() {
	assert(msSingleton);
	return (*msSingleton);
}

SoundFXManager* SoundFXManager::getSingletonPtr() {
	assert(msSingleton);
	return msSingleton;
}

int SoundFXManager::getAvailableChannels() {
	return _numChannels;
}

Ogre::Resource* SoundFXManager::createImpl(const Ogre::String& name, Ogre::ResourceHandle handle,
	const Ogre::String& group, bool isManual,
	Ogre::ManualResourceLoader* loader,
	const Ogre::NameValuePairList* createParams) {
	return new SoundFX(this, name, handle, group, isManual, loader);
}