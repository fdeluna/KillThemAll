#ifndef __TRACKH__
#define __TRACKH__

#include <OGRE/Ogre.h>
#include <OGRE/OgreResourceManager.h>
#include <OGRE/OgreSharedPtr.h>
#include <SDL_mixer.h>

class Track : public Ogre::Resource {
 public:
  
  Track (Ogre::ResourceManager* pManager,
	 const Ogre::String& resource_name,
	 Ogre::ResourceHandle handle,
	 const Ogre::String& resource_group,
	 bool manual_load = false,
	 Ogre::ManualResourceLoader* pLoader = 0);
  ~Track ();

  void play (int loop = -1);
  void pause ();
  void stop ();
  
  void fadeIn (int ms, int loop);
  void fadeOut (int ms);
  static bool isPlaying ();

 private:  
  void loadImpl ();   
  void unloadImpl (); 
  size_t calculateSize () const;

  Mix_Music* _pTrack; 
  Ogre::String _path; 
  size_t _size;       
};

typedef Ogre::SharedPtr<Track> TrackPtr;
#endif
