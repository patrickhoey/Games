#include "AppDelegate.h"
#include "TitleMenu.h"
#include "Constants.h"
#include "AdHelper.h"

//#include "TitleMenu.h"
#define PHYSICS_FACTOR 32
//#define CC_SPRITE_DEBUG_DRAW 1

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
    AdHelper::hideAdmobBannerAd();
    
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
    
    //Scale factor info
    
    //Scale factor info
    /*
    Size size = director->getWinSize();
    float scaleFactor = size.height / size.width;
    glview->setDesignResolutionSize(size.width / scaleFactor, size.width, ResolutionPolicy::SHOW_ALL);
    director->setContentScaleFactor(scaleFactor);
    */
    cocos2d::Size size = director->getWinSize();
    //CCLOG("Win Size: x %f, y %f", size.width, size.height);
    
    glview->setDesignResolutionSize(320, 480, ResolutionPolicy::EXACT_FIT);
    director->setContentScaleFactor(2);
    //CCLOG("Win Size: x %f, y %f", size.width, size.height);
    
    // turn on display FPS
    director->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);
    
    //CCLOG("WIDTH: %f and HEIGHT: %f", size.width, size.height);

    //This sets up the singleton FileUtils configuration for the directory heirarchy to parse
    spritebuilder::CCBReader::setupSpriteBuilder("resources-phonehd", PHYSICS_FACTOR);
    //cocos2d::SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Published-iOS/resources-phone/image_crown.plist");
    FileUtils::getInstance()->addSearchPath("Icons");
    FileUtils::getInstance()->addSearchPath("sound");
    FileUtils::getInstance()->addSearchPath("fonts");
    FileUtils::getInstance()->addSearchPath("Published-iOS");
    FileUtils::getInstance()->addSearchPath("Published-iOS/resources-phonehd/image_crown");
    FileUtils::getInstance()->addSearchPath("Published-iOS/resources-phonehd");
    
    if( true == FileUtils::getInstance()->isFileExist(Constants::BACKGROUND_MUSIC) )
    {
      SimpleAudioEngine::getInstance()->preloadBackgroundMusic(Constants::BACKGROUND_MUSIC);
    }
 
    
    //!!TEMPORARY!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    //auto userDefaults = UserDefault::getInstance();
    //userDefaults->setBoolForKey("soundmode1", false);
    //userDefaults->flush();
    
    
    AdHelper::showAdmobInterstitialAd();
    
    // create a scene. it's an autorelease object
    auto scene = TitleMenu::createScene();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    CCLOG("AppDelegate::applicationDidEnterBackground()");
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    if( true == FileUtils::getInstance()->isFileExist(Constants::BACKGROUND_MUSIC) )
    {
        SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
    }
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    CCLOG("AppDelegate::applicationWillEnterForeground()");
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    if( true == FileUtils::getInstance()->isFileExist(Constants::BACKGROUND_MUSIC) )
    {
        SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
    }
}
