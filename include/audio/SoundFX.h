#ifndef __SOUNDFXH__
#define __SOUNDFXH__

#include <OGRE/Ogre.h>
#include <OGRE/OgreResourceManager.h>
#include <OGRE/OgreSharedPtr.h>
#include <SDL_mixer.h>

class SoundFX: public Ogre::Resource {
 public:  
  SoundFX(Ogre::ResourceManager* creator, const Ogre::String& resource_name,
	  Ogre::ResourceHandle handle, const Ogre::String& resource_group,
	  bool isManual = false, Ogre::ManualResourceLoader* loader = 0);  
  ~SoundFX();

  int play(int loop = 0);
        
 protected:
  void loadImpl();
  void unloadImpl();
  size_t calculateSize() const;
  
 private:
  Mix_Chunk* _pSound; 
  Ogre::String _path; 
  size_t _size;       
};

typedef Ogre::SharedPtr<SoundFX> SoundFXPtr;
#endif
