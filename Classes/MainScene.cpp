#include "MainScene.h"
#include "CCUserDefault.h"
#include "SimpleAudioEngine.h"
#include "Grid.h"
#include "OptionMenu.h"
#include "Constants.h"
#include "AdHelper.h"

using namespace CocosDenshion;

MainScene::MainScene() :
  reader_(NULL)
, imbg_(NULL)
, grid_(NULL)
, txtscore_(NULL)
, scoreLabel_(NULL)
, txthighscore_(NULL)
, highscoreLabel_(NULL)
, btoption_(NULL)
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
    //CCLOG("MainScene::init()");
    auto listener = cocos2d::EventListenerCustom::create( Constants::UPDATE_SCORE, CC_CALLBACK_1(MainScene::updateScore, this) );
    _eventDispatcher->addEventListenerWithFixedPriority(listener, 1);
    
    //cocos2d::Vector<Node*> children = this->getChildren();
    
    return true;
}

bool MainScene::onAssignCCBMemberVariable(cocos2d::Ref* pTarget, const char* pMemberVariableName, cocos2d::Node* pNode)
{
    //CCLOG("MainScene::onAssignCCBMemberVariable: %s", pMemberVariableName);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_imbg", Sprite*, this->imbg_);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_grid", Grid*, this->grid_);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_txtscore", Label*, this->txtscore_);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_scoreLabel", Label*, this->scoreLabel_);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_txthighscore", Label*, this->txthighscore_);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_highscoreLabel", Label*, this->highscoreLabel_);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_btoption", ControlButton*, this->btoption_);
    return true;
}

void MainScene::updateScore(EventCustom* event)
{
    if( NULL == event )
    {
        CCLOG("MainScene::updateScore:: EventCustom is NULL");
        return;
    }
    
    //CCLOG("MainScene::updateScore %p", this);
    if( NULL == scoreLabel_ )
    {
        CCLOG("MainScene::updateScore:: NULL. Removing listeners");
        _eventDispatcher->removeEventListenersForTarget(this);
        return;
    }
    
    if( false == this->isRunning() )
    {
        CCLOG("MainScene::updateScore:: MainScene is NOT RUNNING. Removing listeners");
        _eventDispatcher->removeEventListenersForTarget(this);
    }
    
    int* userData = static_cast<int*>(event->getUserData());
    
    if( NULL == userData)
    {
        CCLOG("*******UserData Score IS NULL");
        return;
    }
    
    int score = *userData;
    
    //Test bounds
    if( score < 0 || score > INT_MAX)
    {
        CCLOG("*******Score IS INVALID");
        return;
    }
    
    //CCLOG("*******Got update for score! %d from %p", score, this);
    scoreLabel_->setString(std::to_string(score));
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
        optionMenu->setNormalizedPosition(cocos2d::Vec2(.49f, 0.425f));
        optionMenu->setLocalZOrder(INT_MAX-1);
        
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

    highscoreLabel_->setString(std::to_string(highScore));
    
}

void MainScene::setCCBReader(spritebuilder::CCBReader* reader)
{
    reader_ = reader;
}

void MainScene::onEnter()
{
    //CCLOG("######Entering callback");
    AdHelper::hideAdmobBannerAd();
    
    cocos2d::Node::onEnter();
}



void MainScene::onNodeLoaded(cocos2d::Node* pNode, spritebuilder::NodeLoader* pNodeLoader)
{    
    txtscore_->enableOutline(cocos2d::Color4B::BLACK, 1.0f);
    scoreLabel_->enableOutline(cocos2d::Color4B::BLACK, 1.0f);
    txthighscore_->enableOutline(cocos2d::Color4B::BLACK, 1.0f);
    highscoreLabel_->enableOutline(cocos2d::Color4B::BLACK, 1.0f);
    CCLOG("Current font is %s size %f", txtscore_->getSystemFontName().c_str(), txtscore_->getSystemFontSize());
    
    Size viewSize = Director::getInstance()->getVisibleSize();
    
    if( viewSize.height <= 480)
    {
        imbg_->setScale(0.9,0.95); //Fixes the scaling issues
    }
    else
    {
        imbg_->setScale(1.0,1.0); //Fixes the scaling issues
    }
    
    //@TODO Try to find nicer way of setting this position

    grid_->setPosition(10.0f,55.0f);
    
    //CCLOG("***Loaded MainScene");
    updateHighScore();
    
    auto userDefaults = UserDefault::getInstance();
    bool soundMode = userDefaults->getBoolForKey("soundmode1", true);
    //CCLOG("SOUNDMODE: %s", soundMode ? "true" : "false");
    
    //If the mode is sound ON, then make sure it is enabled
    if(true == soundMode){
        //CCLOG("Sound ON: %s", soundMode ? "true" : "false");
        SimpleAudioEngine* sound = SimpleAudioEngine::getInstance();
        sound->stopAllEffects();
        
        if( true == FileUtils::getInstance()->isFileExist(Constants::BACKGROUND_MUSIC2) )
        {
            sound->playBackgroundMusic(Constants::BACKGROUND_MUSIC2, true);
        }
    }
    
    //highscoreLabel_->setPosition((highscoreLabel_->getPosition().x)+0.05, highscoreLabel_->getPosition().y);
    //CCLOG("Highest Score Position X: %f", highscoreLabel_->getPosition().x);
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

