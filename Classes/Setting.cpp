#include "Setting.h"
#include "CCUserDefault.h"
#include "SimpleAudioEngine.h"
#include "Constants.h"

using namespace CocosDenshion;

Setting::Setting() :
reader_(NULL)
, bg11_(NULL)
{
}

Setting::~Setting()
{
}

Scene* Setting::createScene()
{
    spritebuilder::NodeLoaderLibrary* ccNodeLoaderLibrary = spritebuilder::NodeLoaderLibrary::getInstance();
    ccNodeLoaderLibrary->registerNodeLoader("Setting", SettingSceneContentLoader::loader());
    
    spritebuilder::CCBReader* ccbReader = new spritebuilder::CCBReader(ccNodeLoaderLibrary);
    
    return ccbReader->createSceneWithNodeGraphFromFile("Setting.ccbi");
}

void Setting::setCCBReader(spritebuilder::CCBReader* reader)
{
    reader_ = reader;
}

void Setting::onNodeLoaded(cocos2d::Node* pNode, spritebuilder::NodeLoader* pNodeLoader)
{
    /*
    Size viewSize = Director::getInstance()->getVisibleSize();
    
    if( viewSize.height >= 512)
    {
        bg11_->setScale(1.0,1.0); //Fixes the scaling issues
    }
    else
    {
        bg11_->setScale(0.9,0.95); //Fixes the scaling issues
    }*/
    //CCLOG("***Loaded Setting");
}

bool Setting::onAssignCCBMemberVariable(cocos2d::Ref* pTarget, const char* pMemberVariableName, cocos2d::Node* pNode)
{
    //CCLOG("Setting::onAssignCCBMemberVariable: %s", pMemberVariableName);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_bg11", Sprite*, this->bg11_);
    return true;
}

bool Setting::onAssignCCBCustomProperty(cocos2d::Ref* target, const char* memberVariableName, const cocos2d::Value& value)
{
    //CCLOG("Setting::onAssignCCBCustomProperty: %s", memberVariableName);
    return false;
}

cocos2d::SEL_MenuHandler Setting::onResolveCCBCCMenuItemSelector(cocos2d::Ref * pTarget, const char* pSelectorName)
{
    //CCLOG("Setting::onResolveCCBCCMenuItemSelector: %s", pSelectorName);
    return NULL;
}

cocos2d::SEL_CallFuncN Setting::onResolveCCBCCCallFuncSelector(cocos2d::Ref * pTarget, const char* pSelectorName)
{
    //CCLOG("Setting::onResolveCCBCCCallFuncSelector: %s", pSelectorName);
    return NULL;
}

cocos2d::extension::Control::Handler Setting::onResolveCCBCCControlSelector(cocos2d::Ref * pTarget, const char* pSelectorName)
{
    //CCLOG("Setting::onResolveCCBCCControlSelector: %s", pSelectorName);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "soundon", Setting::onSoundOnClicked);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "soundoff", Setting::onSoundOffClicked);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "back", Setting::onBackClicked);
    return NULL;
}


void Setting::onSoundOnClicked(cocos2d::Ref* sender, cocos2d::extension::Control::EventType pControlEvent)
{
    // if you use SimpleAudioEngine, it must be pause
    if( true == FileUtils::getInstance()->isFileExist(Constants::BACKGROUND_MUSIC) )
    {
        SimpleAudioEngine::getInstance()->playBackgroundMusic(Constants::BACKGROUND_MUSIC, true);
    }
    
    auto userDefaults = UserDefault::getInstance();
    userDefaults->setBoolForKey("soundmode1", true);
    userDefaults->flush();
    
}

void Setting::onSoundOffClicked(cocos2d::Ref* sender, cocos2d::extension::Control::EventType pControlEvent)
{
    // if you use SimpleAudioEngine, it must be pause
    if( true == FileUtils::getInstance()->isFileExist(Constants::BACKGROUND_MUSIC) )
    {
        SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    }
    
    auto userDefaults = UserDefault::getInstance();
    userDefaults->setBoolForKey("soundmode1", false);
    userDefaults->flush();
}

void Setting::onBackClicked(cocos2d::Ref* sender, cocos2d::extension::Control::EventType pControlEvent)
{
    auto director = Director::getInstance();
    director->popScene();
}
