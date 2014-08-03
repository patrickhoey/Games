#include "OptionMenu.h"
#include "CCUserDefault.h"
#include "SimpleAudioEngine.h"
#include "TitleMenu.h"

using namespace CocosDenshion;

OptionMenu::~OptionMenu()
{
}

Scene* OptionMenu::createScene()
{
    spritebuilder::NodeLoaderLibrary* ccNodeLoaderLibrary = spritebuilder::NodeLoaderLibrary::getInstance();
    ccNodeLoaderLibrary->registerNodeLoader("OptionMenu", OptionMenuSceneContentLoader::loader());
    
    spritebuilder::CCBReader* ccbReader = new spritebuilder::CCBReader(ccNodeLoaderLibrary);
    
    return ccbReader->createSceneWithNodeGraphFromFile("OptionMenu.ccbi");
}

void OptionMenu::setCCBReader(spritebuilder::CCBReader* reader)
{
    reader_ = reader;
}

void OptionMenu::onNodeLoaded(cocos2d::Node* pNode, spritebuilder::NodeLoader* pNodeLoader)
{
    CCLOG("***Loaded OptionMenu");
}

bool OptionMenu::onAssignCCBMemberVariable(cocos2d::Ref* pTarget, const char* pMemberVariableName, cocos2d::Node* pNode)
{
    return false;
}

bool OptionMenu::onAssignCCBCustomProperty(cocos2d::Ref* target, const char* memberVariableName, const cocos2d::Value& value)
{
    return false;
}

cocos2d::SEL_MenuHandler OptionMenu::onResolveCCBCCMenuItemSelector(cocos2d::Ref * pTarget, const char* pSelectorName)
{
    return NULL;
}

cocos2d::SEL_CallFuncN OptionMenu::onResolveCCBCCCallFuncSelector(cocos2d::Ref * pTarget, const char* pSelectorName)
{
    return NULL;
}

cocos2d::extension::Control::Handler OptionMenu::onResolveCCBCCControlSelector(cocos2d::Ref * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "mainMenu", OptionMenu::onMainMenuClicked);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "restartGame", OptionMenu::onRestartGameClicked);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "resume", OptionMenu::onResumeClicked);
    return NULL;
}

void OptionMenu::onMainMenuClicked(cocos2d::Ref* sender, cocos2d::extension::Control::EventType pControlEvent)
{
    auto userDefaults = UserDefault::getInstance();
    userDefaults->setBoolForKey("openop", true);
    userDefaults->flush();
    
    auto director = Director::getInstance();
    director->popToRootScene();
}

void OptionMenu::onRestartGameClicked(cocos2d::Ref* sender, cocos2d::extension::Control::EventType pControlEvent)
{
    auto userDefaults = UserDefault::getInstance();
    userDefaults->setBoolForKey("openop", true);
    userDefaults->flush();
}

void OptionMenu::onResumeClicked(cocos2d::Ref* sender, cocos2d::extension::Control::EventType pControlEvent)
{
    auto userDefaults = UserDefault::getInstance();
    userDefaults->setBoolForKey("openop", true);
    userDefaults->flush();
    
    auto director = Director::getInstance();
    director->popScene();
}
