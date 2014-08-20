#ifndef __GameEnd_SCENE_H__
#define __GameEnd_SCENE_H__

#include "cocos2d.h"
#include "editor-support/SpriteBuilder.h"
#include "extensions/cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class GameEnd:
  public cocos2d::Layer
, public spritebuilder::CCBSelectorResolver
, public spritebuilder::CCBMemberVariableAssigner
, public spritebuilder::NodeLoaderListener {
public:
    SB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(GameEnd, create);

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    static cocos2d::Node* load();
    
    GameEnd();
    virtual ~GameEnd();
    
    void setCCBReader(spritebuilder::CCBReader* reader);
    
    virtual void onNodeLoaded(cocos2d::Node* pNode, spritebuilder::NodeLoader* pNodeLoader);
    virtual bool onAssignCCBMemberVariable(cocos2d::Ref* pTarget, const char* pMemberVariableName, cocos2d::Node* pNode);
    virtual bool onAssignCCBCustomProperty(cocos2d::Ref* target, const char* memberVariableName, const cocos2d::Value& value);
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::Ref* pTarget, const char* pSelectorName);
    virtual cocos2d::SEL_CallFuncN onResolveCCBCCCallFuncSelector(cocos2d::Ref* pTarget, const char* pSelectorName);
    virtual cocos2d::extension::Control::Handler onResolveCCBCCControlSelector(cocos2d::Ref* pTarget, const char* pSelectorName);
    
    void onNewGameClicked(cocos2d::Ref * sender, cocos2d::extension::Control::EventType pControlEvent);
    void setMessage(const std::string& message, int score);
    
    virtual void onEnter();
    virtual void onExit();
    
private:
    spritebuilder::CCBReader* reader_;
    cocos2d::Label* messageLabel_;
    cocos2d::Label* scoreLabel_;
};


class GameEndSceneContentLoader : public spritebuilder::LayerLoader {
public:
    SB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(GameEndSceneContentLoader, loader);
    
protected:
    SB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(GameEnd);
    
};

#endif // __GameEnd_SCENE_H__
