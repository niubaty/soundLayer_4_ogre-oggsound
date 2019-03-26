
#include "soundlayer.h"

soundLayer::soundLayer(Ogre::SceneManager* scnMgr) {
	mSoundMgr = OgreOggSound::OgreOggSoundManager::getSingletonPtr();
	if (!mSoundMgr)mSoundMgr = new OgreOggSound::OgreOggSoundManager();
	mSoundMgr->setSceneManager(scnMgr);
	mSoundMgr->init();
}
soundLayer::~soundLayer() {

}

void soundLayer::addSound(std::string name, std::string resourcePath) {
	mSoundMgr->createSound(name, resourcePath);
}

void soundLayer::play(std::string name) {
	OgreOggSound::OgreOggISound * snd = mSoundMgr->getSound(name);
	snd->play(true);
}

void soundLayer::stop(std::string name) {
	OgreOggSound::OgreOggISound * snd = mSoundMgr->getSound(name);
	snd->stop(true);
}

void soundLayer::restart(std::string name) {
	OgreOggSound::OgreOggISound * snd = mSoundMgr->getSound(name);
	snd->stop(true);
	snd->play(true);
}