#include "AppDelegate.h"
#include "TitleMenu.h"

//#include "TitleMenu.h"
#define PHYSICS_FACTOR 32
//#define CC_SPRITE_DEBUG_DRAW 1

USING_NS_CC;
using namespace CocosDenshion;
/*
static Resource smallResource  =  { cocos2d::Size(480, 320),   "iphone" };
static Resource mediumResource =  { cocos2d::Size(1024, 768),  "ipad"   };
static Resource largeResource  =  { cocos2d::Size(2048, 1536), "ipadhd" };
static cocos2d::Size designResolutionSize = cocos2d::Size(480, 320);
*/
 
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
    
    /*
    glview->setDesignResolutionSize(size.width, size.height, ResolutionPolicy::NO_BORDER);
    Size frameSize = glview->getFrameSize();
    // In this demo, we select resource according to the frame's height.
    // If the resource size is different from design resolution size, you need to set contentScaleFactor.
    // We use the ratio of resource's height to the height of design resolution,
    // this can make sure that the resource's height could fit for the height of design resolution.
    
    // if the frame's height is larger than the height of medium resource size, select large resource.
    if (frameSize.height > mediumResource.size.height)
    {
        //searchPath.push_back(largeResource.directory);
        director->setContentScaleFactor(largeResource.size.height/designResolutionSize.height);
    }
    // if the frame's height is larger than the height of small resource size, select medium resource.
    else if (frameSize.height > smallResource.size.height)
    {
        //searchPath.push_back(mediumResource.directory);
        director->setContentScaleFactor(mediumResource.size.height/designResolutionSize.height);
    }
    // if the frame's height is smaller than the height of medium resource size, select small resource.
    else
    {
        //searchPath.push_back(smallResource.directory);
        director->setContentScaleFactor(smallResource.size.height/designResolutionSize.height);
    }
    */
    
    //Scale factor info
    Size size = director->getWinSize();
    float scaleFactor = size.height / 320.0f;
    glview->setDesignResolutionSize(size.width / scaleFactor, 320, ResolutionPolicy::SHOW_ALL);
    director->setContentScaleFactor(scaleFactor / (size.height / 640)); //because the current resource is phonehd's
    
    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);
    
    //CCLOG("WIDTH: %f and HEIGHT: %f", size.width, size.height);

    //This sets up the singleton FileUtils configuration for the directory heirarchy to parse
    spritebuilder::CCBReader::setupSpriteBuilder("resources-phonehd", PHYSICS_FACTOR);
    //cocos2d::SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Published-iOS/resources-phone/image_crown.plist");
    cocos2d::SpriteFrameCache::getInstance()->addSpriteFramesWithFile("effect3-hd.plist");
    FileUtils::getInstance()->addSearchPath("Published-iOS/resources-phone/image_crown");
    FileUtils::getInstance()->addSearchPath("Published-iOS/resources-phone");
    
    
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
