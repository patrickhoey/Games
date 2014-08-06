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
#include <array>

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
    ::Tile* tileForIndex(int x, int y);
    
    bool isIndexValid(const int& x, const int& y);
    bool isIndexValidAndUnoccupied(const int& x, const int& y);
    
    void nextRound();
    void lose();
    void win();
    
    void move(cocos2d::Vec2 direction);
    void moveTile(::Tile* tile, const int& fromX, const int& fromY, const int& toX, const int& toY);
    
    void endGameWithMessage(const std::string& message);
    cocos2d::Vec2 positionForColumn(int row, int column);
    
    void mergeTileAtIndex(const int& fromX, const int& fromY, const int& toX, const int& toY);
    
    bool movePossible();
    
    //gestures/Touch interface
    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
    
    void swipeLeft();
    void swipeRight();
    void swipeDown();
    void swipeUp();
    
    
    
    void showAds();
    
private:
    int score_;
    float columnWidth_;
    float columnHeight_;
    float tileMarginVertical_;
    float tileMarginHorizontal_;
    std::array<::Tile*, Constants::TOTAL_GRID_SIZE> gridArray_;
    cocos2d::Vec2 startSwipe_;
    cocos2d::Vec2 endSwipe_;
    
};



class GridSceneContentLoader : public spritebuilder::LayerColorLoader {
public:
    SB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(GridSceneContentLoader, loader);
    
protected:
    SB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(Grid);
    
};

#endif
