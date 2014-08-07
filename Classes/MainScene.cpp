#include "MainScene.h"
#include "CCUserDefault.h"
#include "SimpleAudioEngine.h"
#include "Grid.h"
#include "OptionMenu.h"
#include "Constants.h"

using namespace CocosDenshion;

MainScene::MainScene() :
  reader_(NULL)
, grid_(NULL)
{
}

MainScene::~MainScene()
{
}

Scene* MainScene::createScene()
{
    spritebuilder::NodeLoaderLibrary* ccNodeLoaderLibrary = spritebuilder::NodeLoaderLibrary::getInstance();
    ccNodeLoaderLibrary->registerNodeLoader("MainScene", MainSceneSceneContentLoader::loader());
    ccNodeLoaderLibrary->registerNodeLoader("Grid", GridSceneContentLoader::loader());
    
    spritebuilder::CCBReader* ccbReader = new spritebuilder::CCBReader(ccNodeLoaderLibrary);
    
    Scene* scene = ccbReader->createSceneWithNodeGraphFromFile("MainScene.ccbi");
    
    return scene;
}

bool MainScene::init()
{
    //Initializing and binding
    auto listener = EventListenerCustom::create( Constants::UPDATE_SCORE, CC_CALLBACK_1(MainScene::updateScore, this) );
    _eventDispatcher->addEventListenerWithFixedPriority(listener, 1);
    
    cocos2d::Vector<Node*> children = this->getChildren();
    
    return true;
}

void MainScene::updateScore(EventCustom* event)
{
    int* score = static_cast<int*>(event->getUserData());
    if( NULL != score )
    {
        CCLOG("*******Got update for score! %d", *score);
        //scoreLabel_->setString(std::to_string(*score));
    }else{
        CCLOG("*******SCORE IS NULL");
    }
}

void MainScene::onMenuOptionClicked(cocos2d::Ref* sender, cocos2d::extension::Control::EventType pControlEvent)
{
    //CCLOG("***Menu Option Clicked");
    
    auto userDefaults = UserDefault::getInstance();
    bool openOp = userDefaults->getBoolForKey("openop", true);
    
    if(true == openOp)
    {
        //dynamic cast is expensive, must be nicer way of accessing base class
        OptionMenu* optionMenu = static_cast<OptionMenu*>(OptionMenu::load());
        optionMenu->setPosition(0.5f, 0.5f);
        optionMenu->setLocalZOrder(INT_MAX);
        
        this->addChild(optionMenu);
        
        userDefaults->setBoolForKey("openop", false);
        userDefaults->flush();
    }  
    
}

void MainScene::updateHighScore()
{
    auto userDefaults = UserDefault::getInstance();
    int highScore = userDefaults->getIntegerForKey("highscore2", 0);
    //CCLOG("**updateHighScore: %s", std::to_string(highScore).c_str());

    //highscoreLabel_->setString(std::to_string(highScore));
    
}

void MainScene::setCCBReader(spritebuilder::CCBReader* reader)
{
    reader_ = reader;
}

void MainScene::onNodeLoaded(cocos2d::Node* pNode, spritebuilder::NodeLoader* pNodeLoader)
{
    //CCLOG("***Loaded MainScene");
    
    updateHighScore();
    
    auto userDefaults = UserDefault::getInstance();
    bool soundMode = userDefaults->getBoolForKey("soundmode1", true);
    CCLOG("SOUNDMODE: %s", soundMode ? "true" : "false");
    
    //If the mode is sound ON, then make sure it is enabled
    if(true == soundMode){
        CCLOG("Sound ON: %s", soundMode ? "true" : "false");
        
        SimpleAudioEngine* sound = SimpleAudioEngine::getInstance();
        sound->playBackgroundMusic(Constants::BACKGROUND_MUSIC2, true);
    }
    
    //highscoreLabel_->setPosition((highscoreLabel_->getPosition().x)+0.05, highscoreLabel_->getPosition().y);
    //CCLOG("Highest Score Position X: %f", highscoreLabel_->getPosition().x);
}

bool MainScene::onAssignCCBMemberVariable(cocos2d::Ref* pTarget, const char* pMemberVariableName, cocos2d::Node* pNode)
{
    return false;
}

bool MainScene::onAssignCCBCustomProperty(cocos2d::Ref* target, const char* memberVariableName, const cocos2d::Value& value)
{
    return false;
}

cocos2d::SEL_MenuHandler MainScene::onResolveCCBCCMenuItemSelector(cocos2d::Ref * pTarget, const char* pSelectorName)
{
    return NULL;
}

cocos2d::SEL_CallFuncN MainScene::onResolveCCBCCCallFuncSelector(cocos2d::Ref * pTarget, const char* pSelectorName)
{
    return NULL;
}

cocos2d::extension::Control::Handler MainScene::onResolveCCBCCControlSelector(cocos2d::Ref * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "menuOption", MainScene::onMenuOptionClicked);
    return NULL;
}

