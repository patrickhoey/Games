#ifndef __Tile_SCENE_H__
#define __Tile_SCENE_H__

#include "cocos2d.h"
#include "editor-support/spritebuilder/SpriteBuilder.h"
#include "extensions/cocos-ext.h"

class Tile:
  public cocos2d::Layer
, public spritebuilder::CCBSelectorResolver
, public spritebuilder::CCBMemberVariableAssigner
, public spritebuilder::NodeLoaderListener
{
public:
    SB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(Tile, create);

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    Tile();
    virtual ~Tile();
    
    void setCCBReader(spritebuilder::CCBReader* reader);
    
    virtual void onNodeLoaded(cocos2d::Node* pNode, spritebuilder::NodeLoader* pNodeLoader);
    virtual bool onAssignCCBMemberVariable(cocos2d::Ref* pTarget, const char* pMemberVariableName, cocos2d::Node* pNode);
    virtual bool onAssignCCBCustomProperty(cocos2d::Ref* target, const char* memberVariableName, const cocos2d::Value& value);
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::Ref* pTarget, const char* pSelectorName);
    virtual cocos2d::SEL_CallFuncN onResolveCCBCCCallFuncSelector(cocos2d::Ref* pTarget, const char* pSelectorName);
    virtual cocos2d::extension::Control::Handler onResolveCCBCCControlSelector(cocos2d::Ref* pTarget, const char* pSelectorName);

    void updateValueDisplay();
    
    int getValue();
    void setValue(int value);
    
    bool isMergedThisRound();
    void setIsMergedThisRound(bool isMerged);
    
    static cocos2d::Node* load();
    void showAds();
    
private:
    spritebuilder::CCBReader* reader_;
    int value_;
    bool mergedThisRound_;
    cocos2d::Label* valueLabel_;
    cocos2d::LayerColor* backgroundNode_;
    cocos2d::LayerColor* test_;
    cocos2d::Sprite* im_;
    bool isEmpty_;
};


class TileSceneContentLoader : public spritebuilder::LayerLoader {
public:
    SB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(TileSceneContentLoader, loader);
    
protected:
    SB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(::Tile);
    
};

#endif // __Tile_SCENE_H__
