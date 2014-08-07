#include "TitleMenu.h"
#include "CCUserDefault.h"
#include "SimpleAudioEngine.h"
#include "Setting.h"
#include "MainScene.h"
#include "Constants.h"

using namespace CocosDenshion;

TitleMenu::TitleMenu() :
 reader_(NULL)
, bg11_(NULL)
{
    bg11_ = cocos2d::Sprite::create();
}

TitleMenu::~TitleMenu()
{
}

Scene* TitleMenu::createScene()
{
    spritebuilder::NodeLoaderLibrary* ccNodeLoaderLibrary = spritebuilder::NodeLoaderLibrary::getInstance();
    ccNodeLoaderLibrary->registerNodeLoader("TitleMenu", TitleMenuSceneContentLoader::loader());
    
    spritebuilder::CCBReader * ccbReader = new spritebuilder::CCBReader(ccNodeLoaderLibrary);
    
    return ccbReader->createSceneWithNodeGraphFromFile("TitleMenu.ccbi");
}

void TitleMenu::setCCBReader(spritebuilder::CCBReader* reader)
{
    reader_ = reader;
}

void TitleMenu::onNodeLoaded(cocos2d::Node* pNode, spritebuilder::NodeLoader* pNodeLoader)
{
    //CCLOG("***Loaded TitleMenu");
    auto director = Director::getInstance();
    
    Size size = director->getWinSize();
    CCLOG("WIDTH: %f and HEIGHT: %f", size.width, size.height);
    
    if( 512 == size.height )
    {
        bg11_->setScale(1,1);
    }
 
    auto userDefaults = UserDefault::getInstance();
    bool soundMode = userDefaults->getBoolForKey("soundmode1", true);
    //CCLOG("**SOUNDMODE: %s", soundMode ? "true" : "false");
    
    //If the mode is sound ON, then make sure it is enabled
    if(true == soundMode){
        //CCLOG("**Sound ON: %s", soundMode ? "true" : "false");
        
        SimpleAudioEngine* sound = SimpleAudioEngine::getInstance();
        sound->playBackgroundMusic(Constants::BACKGROUND_MUSIC, true);
    }

    userDefaults->setBoolForKey("openop", true);
    userDefaults->flush();
    
}

bool TitleMenu::onAssignCCBMemberVariable(cocos2d::Ref* pTarget, const char* pMemberVariableName, cocos2d::Node* pNode)
{
    return false;
}

bool TitleMenu::onAssignCCBCustomProperty(cocos2d::Ref* target, const char* memberVariableName, const cocos2d::Value& value)
{
    return false;
}

cocos2d::SEL_MenuHandler TitleMenu::onResolveCCBCCMenuItemSelector(cocos2d::Ref * pTarget, const char* pSelectorName)
{
    return NULL;
}

cocos2d::SEL_CallFuncN TitleMenu::onResolveCCBCCCallFuncSelector(cocos2d::Ref * pTarget, const char* pSelectorName)
{
    return NULL;
}

cocos2d::extension::Control::Handler TitleMenu::onResolveCCBCCControlSelector(cocos2d::Ref * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "play", TitleMenu::onPlayClicked);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "setting", TitleMenu::onSettingClicked);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "moregame", TitleMenu::onMoregameClicked);
    return NULL;
}

void TitleMenu::onPlayClicked(cocos2d::Ref * sender, cocos2d::extension::Control::EventType pControlEvent)
{
    //CCLOG("CLICKED ON PLAY");
    // create a scene. it's an autorelease object
    auto scene = MainScene::createScene();
    auto director = Director::getInstance();
    director->pushScene(scene);
}
void TitleMenu::onSettingClicked(cocos2d::Ref * sender, cocos2d::extension::Control::EventType pControlEvent)
{
    //CCLOG("CLICKED ON SETTING");
    // create a scene. it's an autorelease object
    auto scene = Setting::createScene();
    auto director = Director::getInstance();
    director->pushScene(scene);
}
void TitleMenu::onMoregameClicked(cocos2d::Ref * sender, cocos2d::extension::Control::EventType pControlEvent)
{
    CCLOG("Implement more game here");
}
