#include <OgreArchive.h>
#include <OgreResourceGroupManager.h>
#include <OgreLogManager.h>

#include <Track.h>

Track::Track(Ogre::ResourceManager *pManager, const Ogre::String& resource_name,
	Ogre::ResourceHandle handle, const Ogre::String& resource_group,
	bool manual_load, Ogre::ManualResourceLoader* pLoader) :

	Ogre::Resource(pManager, resource_name, handle, resource_group, manual_load, pLoader) {

	createParamDictionary("Track");

	_pTrack = 0;
	_size = 0;
}

Track::~Track() {
	unload();
}

void Track::loadImpl() {
	Ogre::LogManager* pLogManager = Ogre::LogManager::getSingletonPtr();

	Ogre::FileInfoListPtr info;
	info = Ogre::ResourceGroupManager::getSingleton().findResourceFileInfo(mGroup, mName);

	for (Ogre::FileInfoList::const_iterator i = info->begin(); i != info->end(); ++i) {
		_path = i->archive->getName() + "/" + i->filename;
	}

	if (_path == "") {
		pLogManager->logMessage("Track::loadImpl() Imposible cargar el recurso de sonido.");
		printf(Mix_GetError());
		throw (Ogre::Exception(Ogre::Exception::ERR_FILE_NOT_FOUND,
			"Archivo no encontrado", "Track::loadImpl()"));
	}

	if ((_pTrack = Mix_LoadMUS(_path.c_str())) == NULL) {
		pLogManager->logMessage("Track::loadI() Imposible cargar el recurso de sonido.");
		printf(Mix_GetError());
		throw (Ogre::Exception(Ogre::Exception::ERR_FILE_NOT_FOUND,
			"Archivo no encontrado", "Track::loadI()"));
	}

	std::ifstream stream;
	char byteBuffer;
	stream.open(_path.c_str(), std::ios_base::binary);

	while (stream >> byteBuffer) {
		_size++;
	}

	stream.close();
}

void Track::unloadImpl() {
	if (_pTrack) {
		Mix_FreeMusic(_pTrack);
	}
}

size_t Track::calculateSize() const {
	return _size;
}

void Track::play(int loop) {
	Ogre::LogManager* pLogManager = Ogre::LogManager::getSingletonPtr();

	if (Mix_PausedMusic()) {
		Mix_ResumeMusic();
	}
	else {
		if (Mix_PlayMusic(_pTrack, loop) == -1) {
			pLogManager->logMessage("Track::play() Error al reproducir el recurso de sonido.");
			throw (Ogre::Exception(Ogre::Exception::ERR_FILE_NOT_FOUND,
				"Imposible reproducir el recurso de sonido", "Track::play()"));
		}
	}
}

void Track::pause() {
	Mix_PauseMusic();
}

void Track::stop() {
	Mix_HaltMusic();
}

void Track::fadeIn(int ms, int loop) {
	Ogre::LogManager* pLogManager = Ogre::LogManager::getSingletonPtr();

	if (Mix_FadeInMusic(_pTrack, ms, loop) == -1) {
		pLogManager->logMessage("Track::fadeIn() Error al aplicar efecto de sonido.");
		throw (Ogre::Exception(Ogre::Exception::ERR_INTERNAL_ERROR,
			"Imposible aplicar suavizado de sonido", "Track::fadeIn()"));
	}
}

void Track::fadeOut(int ms) {
	Ogre::LogManager* pLogManager = Ogre::LogManager::getSingletonPtr();

	if (Mix_FadeOutMusic(ms) == -1) {
		pLogManager->logMessage("Track::fadeIn() Error al aplicar efecto de sonido.");
		throw (Ogre::Exception(Ogre::Exception::ERR_INTERNAL_ERROR,
			"Imposible aplicar suavizado de sonido", "Track::fadeIn()"));
	}
}

bool Track::isPlaying() {
	return Mix_PlayingMusic();
}
