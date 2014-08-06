#include "AppDelegate.h"
#include "TitleMenu.h"

//#include "TitleMenu.h"
#define PHYSICS_FACTOR 32

USING_NS_CC;
using namespace CocosDenshion;

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate() 
{
}

int AppDelegate::getSoundMode(){
    return _soundMode;
}

void AppDelegate::setSoundMode(int soundMode){
    _soundMode = soundMode;
}

bool AppDelegate::applicationDidFinishLaunching() {
    //Investigate a better random generator (Cocos2DX has no Math library)
    //Seeding the random number generator
    srand((unsigned)time(0));
    
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLView::create("Rock Paper Scissors 2048");
        director->setOpenGLView(glview);
    }
    
    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);
    
    //Scale factor info
    Size size = director->getWinSize();
    //CCLOG("WIDTH: %f and HEIGHT: %f", size.width, size.height);

    //This sets up the singleton FileUtils configuration for the directory heirarchy to parse
    spritebuilder::CCBReader::setupSpriteBuilder("resources-phone", PHYSICS_FACTOR);
    //FileUtils::getInstance()->loadFilenameLookupDictionaryFromFile("configCocos2d.plist");
    //FileUtils::getInstance()->loadFilenameLookupDictionaryFromFile("image_crown.plist");
    FileUtils::getInstance()->addSearchPath("Published-iOS/resources-phone/image_crown");
    FileUtils::getInstance()->addSearchPath("Published-iOS/resources-phone");
    //std::string fullpath = FileUtils::getInstance()->fullPathForFilename("b1.png");
    //if (fullpath.size() == 0)
    //{
    //    CCLOG("Could not find file!");
    //}
    
    //!!TEMPORARY!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    auto userDefaults = UserDefault::getInstance();
    userDefaults->setBoolForKey("soundmode1", false);
    userDefaults->flush();
    
    
    // create a scene. it's an autorelease object
    auto scene = TitleMenu::createScene();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
