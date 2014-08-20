#include "OptionMenu.h"
#include "CCUserDefault.h"
#include "SimpleAudioEngine.h"
#include "TitleMenu.h"
#include "MainScene.h"
#include "Constants.h"

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

Node* OptionMenu::load()
{
    spritebuilder::NodeLoaderLibrary* ccNodeLoaderLibrary = spritebuilder::NodeLoaderLibrary::getInstance();
    ccNodeLoaderLibrary->registerNodeLoader("OptionMenu", OptionMenuSceneContentLoader::loader());
    
    spritebuilder::CCBReader* ccbReader = new spritebuilder::CCBReader(ccNodeLoaderLibrary);

    return ccbReader->readNodeGraphFromFile("OptionMenu.ccbi");
}

void OptionMenu::onEnter()
{
    auto director = Director::getInstance();
    director->pause();
    cocos2d::Node::onEnter();
}

void OptionMenu::onExit()
{
    auto director = Director::getInstance();
    director->resume();
    cocos2d::Node::onExit();
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
    //CCLOG("OptionMenu::onAssignCCBMemberVariable: %s", pMemberVariableName);
    return true;
}

bool OptionMenu::onAssignCCBCustomProperty(cocos2d::Ref* target, const char* memberVariableName, const cocos2d::Value& value)
{
    //CCLOG("OptionMenu::onAssignCCBCustomProperty: %s", memberVariableName);
    return false;
}

cocos2d::SEL_MenuHandler OptionMenu::onResolveCCBCCMenuItemSelector(cocos2d::Ref * pTarget, const char* pSelectorName)
{
    //CCLOG("OptionMenu::onResolveCCBCCMenuItemSelector: %s", pSelectorName);
    return NULL;
}

cocos2d::SEL_CallFuncN OptionMenu::onResolveCCBCCCallFuncSelector(cocos2d::Ref * pTarget, const char* pSelectorName)
{
    //CCLOG("OptionMenu::onResolveCCBCCCallFuncSelector: %s", pSelectorName);
    return NULL;
}

cocos2d::extension::Control::Handler OptionMenu::onResolveCCBCCControlSelector(cocos2d::Ref * pTarget, const char* pSelectorName)
{
    //CCLOG("OptionMenu::onResolveCCBCCControlSelector: %s", pSelectorName);
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
    auto runningScene = director->getRunningScene();
    _eventDispatcher->removeCustomEventListeners(Constants::UPDATE_SCORE);
    runningScene->cleanup();
    
    director->popToRootScene();
}

void OptionMenu::onRestartGameClicked(cocos2d::Ref* sender, cocos2d::extension::Control::EventType pControlEvent)
{
    auto userDefaults = UserDefault::getInstance();
    userDefaults->setBoolForKey("openop", true);
    userDefaults->flush();
    
    auto director = Director::getInstance();
    auto runningScene = director->getRunningScene();
    _eventDispatcher->removeCustomEventListeners(Constants::UPDATE_SCORE);
    runningScene->cleanup();
    
    
    auto scene = MainScene::createScene();
    director->replaceScene(scene);
}

void OptionMenu::onResumeClicked(cocos2d::Ref* sender, cocos2d::extension::Control::EventType pControlEvent)
{
    auto userDefaults = UserDefault::getInstance();
    userDefaults->setBoolForKey("openop", true);
    userDefaults->flush();
    
    this->removeFromParent();
}
