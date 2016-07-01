#include <fstream>

#include "SoundFX.h"

SoundFX::SoundFX(Ogre::ResourceManager* creator, const Ogre::String& resource_name,
		 Ogre::ResourceHandle handle, const Ogre::String& resource_group,
		 bool isManual, Ogre::ManualResourceLoader* loader):
  Ogre::Resource(creator, resource_name, handle, resource_group, isManual, loader) {
  
  createParamDictionary("SoundFX");

  _pSound = 0;
  _path = "";
  _size = 0;
}

SoundFX::~SoundFX() {  
  unload();
}

int SoundFX::play(int loop) {
  int channel;
  Ogre::LogManager* pLogManager = Ogre::LogManager::getSingletonPtr();
  
  if ((channel = Mix_PlayChannel(-1, _pSound, loop)) == -1) {
    pLogManager->logMessage("SoundFX::play() Imposible reproducir el efecto de sonido.");
    throw (Ogre::Exception(Ogre::Exception::ERR_INTERNAL_ERROR,
			   "Imposible reproducir el efecto de sonido", "SoundFX::play()"));
  }

  return channel;
}

void SoundFX::loadImpl() {
  Ogre::LogManager* pLogManager = Ogre::LogManager::getSingletonPtr();
  
  Ogre::FileInfoListPtr info;
  info = Ogre::ResourceGroupManager::getSingleton().findResourceFileInfo(mGroup, mName);
  for (Ogre::FileInfoList::iterator i = info->begin(); i != info->end(); ++i) {
    _path = i->archive->getName() + "/" + i->filename;
  }
    
  if (_path == "") {
    pLogManager->logMessage("SoundFX::loadImpl() Imposible encontrar el recurso.");
    throw (Ogre::Exception(Ogre::Exception::ERR_FILE_NOT_FOUND,
			   "Imposible encontrar el recurso", "SoundFX::loadImpl()"));
  }
    
  if ((_pSound = Mix_LoadWAV(_path.c_str())) == NULL) {
    pLogManager->logMessage("SoundFX::loadImpl() Imposible cargar el efecto.");
	printf(Mix_GetError());
    throw (Ogre::Exception(Ogre::Exception::ERR_INTERNAL_ERROR,
			   "Imposible cargar el efecto", "SoundFX::loadImpl()"));
  }
    
  std::ifstream stream;
  char byteBuffer;
  stream.open(_path.c_str(), std::ios_base::binary);
  
  while (stream >> byteBuffer) {
    ++_size;
  }
  
  stream.close();
}

void SoundFX::unloadImpl() {
  if (_pSound) {    
    Mix_FreeChunk(_pSound);
  }
}

size_t SoundFX::calculateSize() const {
  return _size;
}
