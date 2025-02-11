#include "GameEnd.h"
#include "CCUserDefault.h"
#include "SimpleAudioEngine.h"
#include "MainScene.h"
#include "Constants.h"
#include "AdHelper.h"

using namespace CocosDenshion;

GameEnd::GameEnd() :
 reader_(NULL)
, messageLabel_(NULL)
, scoreLabel_(NULL)
{
}

GameEnd::~GameEnd()
{
}

Scene* GameEnd::createScene()
{
    spritebuilder::NodeLoaderLibrary* ccNodeLoaderLibrary = spritebuilder::NodeLoaderLibrary::getInstance();
    ccNodeLoaderLibrary->registerNodeLoader("GameEnd", GameEndSceneContentLoader::loader());
    
    spritebuilder::CCBReader* ccbReader = new spritebuilder::CCBReader(ccNodeLoaderLibrary);
    
    return ccbReader->createSceneWithNodeGraphFromFile("GameEnd.ccbi");
}

Node* GameEnd::load()
{
    spritebuilder::NodeLoaderLibrary* ccNodeLoaderLibrary = spritebuilder::NodeLoaderLibrary::getInstance();
    ccNodeLoaderLibrary->registerNodeLoader("GameEnd", GameEndSceneContentLoader::loader());
    
    spritebuilder::CCBReader* ccbReader = new spritebuilder::CCBReader(ccNodeLoaderLibrary);
    
    return ccbReader->readNodeGraphFromFile("GameEnd.ccbi");
}

void GameEnd::onEnter()
{
    auto director = Director::getInstance();
    director->pause();
    
    auto userDefaults = UserDefault::getInstance();
    userDefaults->setBoolForKey("openop", false);
    userDefaults->flush();
    
    cocos2d::Node::onEnter();
}

void GameEnd::onExit()
{
    auto director = Director::getInstance();
    director->resume();
    
    auto userDefaults = UserDefault::getInstance();
    userDefaults->setBoolForKey("openop", true);
    userDefaults->flush();
    
    cocos2d::Node::onExit();
}


void GameEnd::setMessage(const std::string& message, int score)
{
    messageLabel_->setString(message);
    messageLabel_->setScale(.75);
    scoreLabel_->setString(std::to_string(score));
    
    auto userDefaults = UserDefault::getInstance();
    int highScore = userDefaults->getIntegerForKey("highscore2", 0);

    if( score > highScore){
        userDefaults->setIntegerForKey("highscore2", score);
        userDefaults->flush();
    }
}

void GameEnd::setCCBReader(spritebuilder::CCBReader* reader)
{
    reader_ = reader;
}

void GameEnd::onNodeLoaded(cocos2d::Node* pNode, spritebuilder::NodeLoader* pNodeLoader)
{
    //CCLOG("***Loaded GameEnd");
}

bool GameEnd::onAssignCCBMemberVariable(cocos2d::Ref* pTarget, const char* pMemberVariableName, cocos2d::Node* pNode)
{
    //CCLOG("GameEnd::onAssignCCBMemberVariable %s", pMemberVariableName);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_messageLabel", Label*, this->messageLabel_);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_scoreLabel", Label*, this->scoreLabel_);
    return true;
}

bool GameEnd::onAssignCCBCustomProperty(cocos2d::Ref* target, const char* memberVariableName, const cocos2d::Value& value)
{
    //CCLOG("GameEnd::onAssignCCBCustomProperty %s", memberVariableName);
    return false;
}

cocos2d::SEL_MenuHandler GameEnd::onResolveCCBCCMenuItemSelector(cocos2d::Ref * pTarget, const char* pSelectorName)
{
    //CCLOG("GameEnd::onResolveCCBCCMenuItemSelector %s", pSelectorName);
    return NULL;
}

cocos2d::SEL_CallFuncN GameEnd::onResolveCCBCCCallFuncSelector(cocos2d::Ref * pTarget, const char* pSelectorName)
{
    //CCLOG("GameEnd::onResolveCCBCCCallFuncSelector %s", pSelectorName);
    return NULL;
}

void GameEnd::onNewGameClicked(cocos2d::Ref * sender, cocos2d::extension::Control::EventType pControlEvent)
{
    int testNum = rand()%2; //Either 1 or 0
    
    if(0 == testNum){
        AdHelper::showAdmobInterstitialAd();
    }else{
        AdHelper::showChartboostInterstitualAd();
    }
    
    auto director = Director::getInstance();
    auto runningScene = director->getRunningScene();
    _eventDispatcher->removeCustomEventListeners(Constants::UPDATE_SCORE);
    runningScene->cleanup();
    
    // create a scene. it's an autorelease object
    auto scene = MainScene::createScene();
    director->replaceScene(scene);
}

cocos2d::extension::Control::Handler GameEnd::onResolveCCBCCControlSelector(cocos2d::Ref * pTarget, const char* pSelectorName)
{
    //CCLOG("GameEnd::onResolveCCBCCControlSelector %s", pSelectorName);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "newGame", GameEnd::onNewGameClicked);
    //CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "GameEnd", TitleMenu::onGameEndClicked);
    //CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "moregame", TitleMenu::onMoregameClicked);
    return NULL;
}

