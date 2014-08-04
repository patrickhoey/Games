//
//  Grid.h
//  2048RPSPort
//
//  Created by Patrick Hoey on 8/3/14.
//
//

#ifndef _048RPSPort_Grid_h
#define _048RPSPort_Grid_h

#include "cocos2d.h"
#include "editor-support/spritebuilder/SpriteBuilder.h"
#include "extensions/cocos-ext.h"
#include "Tile.h"
#include "Constants.h"

class Grid:
public cocos2d::LayerColor
, public spritebuilder::CCBSelectorResolver
, public spritebuilder::CCBMemberVariableAssigner
, public spritebuilder::NodeLoaderListener
{
public:
    SB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(Grid, create);
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    Grid();
    virtual ~Grid();
    
    void setCCBReader(spritebuilder::CCBReader* reader);
    
    virtual void onNodeLoaded(cocos2d::Node* pNode, spritebuilder::NodeLoader* pNodeLoader);
    virtual bool onAssignCCBMemberVariable(cocos2d::Ref* pTarget, const char* pMemberVariableName, cocos2d::Node* pNode);
    virtual bool onAssignCCBCustomProperty(cocos2d::Ref* target, const char* memberVariableName, const cocos2d::Value& value);
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::Ref* pTarget, const char* pSelectorName);
    virtual cocos2d::SEL_CallFuncN onResolveCCBCCCallFuncSelector(cocos2d::Ref* pTarget, const char* pSelectorName);
    virtual cocos2d::extension::Control::Handler onResolveCCBCCControlSelector(cocos2d::Ref* pTarget, const char* pSelectorName);
    
    void setupBackground();
    void spawnStartTiles();
    
private:
    spritebuilder::CCBReader* reader_;
    float columnWidth_;
    float columnHeight_;
    float tileMarginVertical_;
    float tileMarginHorizontal_;
    cocos2d::Vector<::Tile*> gridArray_;
    
};



class GridSceneContentLoader : public spritebuilder::LayerColorLoader {
public:
    SB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(GridSceneContentLoader, loader);
    
protected:
    SB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(Grid);
    
};

#endif
