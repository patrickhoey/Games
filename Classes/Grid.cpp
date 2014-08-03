//
//  Grid.cpp
//  2048RPSPort
//
//  Created by Patrick Hoey on 8/3/14.
//
//

#include "Grid.h"

Grid::~Grid()
{
}

cocos2d::Scene* Grid::createScene()
{
    spritebuilder::NodeLoaderLibrary* ccNodeLoaderLibrary = spritebuilder::NodeLoaderLibrary::getInstance();
    ccNodeLoaderLibrary->registerNodeLoader("Grid", GridSceneContentLoader::loader());
    
    spritebuilder::CCBReader* ccbReader = new spritebuilder::CCBReader(ccNodeLoaderLibrary);
    
    return ccbReader->createSceneWithNodeGraphFromFile("Grid.ccbi");
}

void Grid::setCCBReader(spritebuilder::CCBReader* reader)
{
    reader_ = reader;
}

void Grid::onNodeLoaded(cocos2d::Node* pNode, spritebuilder::NodeLoader* pNodeLoader)
{
    CCLOG("***Loaded Grid");
    /*
     auto director = Director::getInstance();
     
     Size size = director->getWinSize();
     CCLOG("WIDTH: %f and HEIGHT: %f", size.width, size.height);
     
     auto userDefaults = UserDefault::getInstance();
     bool soundMode = userDefaults->getBoolForKey("soundmode1", true);
     CCLOG("**SOUNDMODE: %s", soundMode ? "true" : "false");
     
     //If the mode is sound ON, then make sure it is enabled
     if(true == soundMode){
     CCLOG("**Sound ON: %s", soundMode ? "true" : "false");
     
     SimpleAudioEngine* sound = SimpleAudioEngine::getInstance();
     sound->playBackgroundMusic("Castle.mp3", true);
     }
     
     userDefaults->setBoolForKey("openop", true);
     userDefaults->flush();
     */
    
}

bool Grid::onAssignCCBMemberVariable(cocos2d::Ref* pTarget, const char* pMemberVariableName, cocos2d::Node* pNode)
{
    return false;
}

bool Grid::onAssignCCBCustomProperty(cocos2d::Ref* target, const char* memberVariableName, const cocos2d::Value& value)
{
    return false;
}

cocos2d::SEL_MenuHandler Grid::onResolveCCBCCMenuItemSelector(cocos2d::Ref * pTarget, const char* pSelectorName)
{
    return NULL;
}

cocos2d::SEL_CallFuncN Grid::onResolveCCBCCCallFuncSelector(cocos2d::Ref * pTarget, const char* pSelectorName)
{
    return NULL;
}

cocos2d::extension::Control::Handler Grid::onResolveCCBCCControlSelector(cocos2d::Ref * pTarget, const char* pSelectorName)
{
    //CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "play", TitleMenu::onPlayClicked);
    //CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "Grid", TitleMenu::onGridClicked);
    //CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "moregame", TitleMenu::onMoregameClicked);
    return NULL;
}
