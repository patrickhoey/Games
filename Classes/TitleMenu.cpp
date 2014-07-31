#include "TitleMenu.h"

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
    mReader = reader;
}

void TitleMenu::onNodeLoaded(cocos2d::Node * pNode, spritebuilder::NodeLoader* pNodeLoader)
{
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
    CCLOG("*********CLICKED ON PLAY");
}
void TitleMenu::onSettingClicked(cocos2d::Ref * sender, cocos2d::extension::Control::EventType pControlEvent)
{
    CCLOG("*********CLICKED ON SETTING");
}
void TitleMenu::onMoregameClicked(cocos2d::Ref * sender, cocos2d::extension::Control::EventType pControlEvent)
{
    CCLOG("*********CLICKED ON MOREGAME");
}
