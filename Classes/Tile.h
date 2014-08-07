#ifndef __Tile_SCENE_H__
#define __Tile_SCENE_H__

#include "cocos2d.h"
#include "editor-support/spritebuilder/SpriteBuilder.h"
#include "extensions/cocos-ext.h"

class Tile:
  public cocos2d::Layer
, public spritebuilder::NodeLoaderListener
{
public:
    SB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(Tile, create);

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    Tile();
    virtual ~Tile();
    
    virtual void onNodeLoaded(cocos2d::Node* pNode, spritebuilder::NodeLoader* pNodeLoader);

    void updateValueDisplay();
    void updateValueDisplayCB(Node* sender);
    
    int getValue();
    void setValue(int value);
    
    bool isMergedThisRound();
    void setIsMergedThisRound(bool isMerged);
    
    static cocos2d::Node* load();
    void showAds();
    
private:
    int value_;
    bool mergedThisRound_;
    cocos2d::Label* valueLabel_;
    cocos2d::LayerColor* backgroundNode_;
    cocos2d::LayerColor* test_;
    cocos2d::Sprite* im_;
};


class TileSceneContentLoader : public spritebuilder::LayerLoader {
public:
    SB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(TileSceneContentLoader, loader);
    
protected:
    SB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(::Tile);
    
};

#endif // __Tile_SCENE_H__
