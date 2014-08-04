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
, public spritebuilder::NodeLoaderListener
{
public:
    SB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(Grid, create);
    
    Grid();
    virtual ~Grid();
    
    virtual void onNodeLoaded(cocos2d::Node* pNode, spritebuilder::NodeLoader* pNodeLoader);
    
    void setupBackground();
    void spawnStartTiles();
    void spawnRandomTile();
    
    void addTileAtColumn(int row, int column);
    cocos2d::Vec2 positionForColumn(int row, int column);
    
    void showAds();
    
private:
    float columnWidth_;
    float columnHeight_;
    float tileMarginVertical_;
    float tileMarginHorizontal_;
    std::vector<::Tile*> gridArray_;
    
};



class GridSceneContentLoader : public spritebuilder::LayerColorLoader {
public:
    SB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(GridSceneContentLoader, loader);
    
protected:
    SB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(Grid);
    
};

#endif
