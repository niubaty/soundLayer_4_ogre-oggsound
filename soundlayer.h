#pragma once
#include <Ogre.h>
#include <OgreOggISound.h>
#include <OgreOggSoundManager.h>

/*

*/
class soundLayer
{
public:
	soundLayer(Ogre::SceneManager*);
	~soundLayer();
	void addSound(std::string,std::string);
	void play(std::string);
	void stop(std::string);
	void restart(std::string);
protected:
	OgreOggSound::OgreOggSoundManager *mSoundMgr;
};