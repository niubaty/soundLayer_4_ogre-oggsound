#include <Ogre.h>
#include <OgreApplicationContext.h>

#include <string>

#include <OgreOggISound.h>
#include <OgreOggSoundManager.h>

class ImguiExample : public OgreBites::ApplicationContext, public OgreBites::InputListener
{
public:
	ImguiExample() : OgreBites::ApplicationContext("OgreImguiExample")
	{
	}

	bool frameStarted(const Ogre::FrameEvent& evt)
	{
		OgreBites::ApplicationContext::frameStarted(evt);
		return true;
	}

#ifndef OGRE_BUILD_COMPONENT_RTSHADERSYSTEM
	void locateResources()
	{
		OgreBites::ApplicationContext::locateResources();
		// we have to manually specify the shaders
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
			"../resources", "FileSystem", Ogre::ResourceGroupManager::INTERNAL_RESOURCE_GROUP_NAME);
	}
#endif

	void setup()
	{
		OgreBites::ApplicationContext::setup();
		addInputListener(this);

		// get a pointer to the already created root
		Ogre::Root* root = getRoot();
		Ogre::SceneManager* scnMgr = root->createSceneManager();

		// register our scene with the RTSS
		Ogre::RTShader::ShaderGenerator* shadergen = Ogre::RTShader::ShaderGenerator::getSingletonPtr();
		shadergen->addSceneManager(scnMgr);


		Ogre::Light* light = scnMgr->createLight("MainLight");
		Ogre::SceneNode* lightNode = scnMgr->getRootSceneNode()->createChildSceneNode();
		lightNode->setPosition(0, 10, 15);
		lightNode->attachObject(light);


		Ogre::SceneNode* camNode = scnMgr->getRootSceneNode()->createChildSceneNode();
		camNode->setPosition(0, 0, 15);
		camNode->lookAt(Ogre::Vector3(0, 0, -1), Ogre::Node::TS_PARENT);

		Ogre::Camera* cam = scnMgr->createCamera("myCam");
		cam->setNearClipDistance(5); // specific to this sample
		cam->setAutoAspectRatio(true);
		camNode->attachObject(cam);
		getRenderWindow()->addViewport(cam);

		//Ogre::Entity* ent = scnMgr->createEntity("Sinbad.mesh");
		//Ogre::SceneNode* node = scnMgr->getRootSceneNode()->createChildSceneNode();
		//node->attachObject(ent);
		//set oggSoundMgr
		//remember to delete
		//mSoundMgr = new OgreOggSound::OgreOggSoundManager();
		mSoundMgr = OgreOggSound::OgreOggSoundManager::getSingletonPtr();
		if (!mSoundMgr)mSoundMgr = new OgreOggSound::OgreOggSoundManager();
		mSoundMgr->setSceneManager(scnMgr);
		/*OgreOggSound::OgreOggSoundFactory* factory = new OgreOggSound::OgreOggSoundFactory();
		root->addMovableObjectFactory(factory);*/
		mSoundMgr->init();
		mSoundMgr->createSound(std::string("sound1"), std::string("bgm_013.wav"));
		mSoundMgr->createSound(std::string("sound2"), std::string("bgm_013.wav"));

	}

	bool keyPressed(const OgreBites::KeyboardEvent& evt)
	{
		if (evt.keysym.sym == 27)
		{
			getRoot()->queueEndRendering();
		}

		if (evt.keysym.sym == int('p')) {
			OgreOggSound::OgreOggISound * snd = mSoundMgr->getSound(std::string("sound1"));
			snd->play(true);
		}
		if (evt.keysym.sym == int('s')) {
			OgreOggSound::OgreOggISound * snd = mSoundMgr->getSound(std::string("sound1"));
			snd->stop(true);
		}

		if (evt.keysym.sym == int('o')) {
			OgreOggSound::OgreOggISound * snd2 = mSoundMgr->getSound(std::string("sound2"));
			snd2->play(true);
		}

		return true;
	}

	OgreOggSound::OgreOggSoundManager *mSoundMgr;
};


int main(int argc, char *argv[])
{
	ImguiExample app;
	app.initApp();
	app.getRoot()->startRendering();
	app.closeApp();

	return 0;
}
