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
#include "editor-support/SpriteBuilder.h"
#include "extensions/cocos-ext.h"
#include "Tile.h"
#include "Constants.h"
#include <array>

class Grid:
  public cocos2d::LayerColor
, public spritebuilder::CCBSelectorResolver
, public spritebuilder::CCBMemberVariableAssigner
, public spritebuilder::NodeLoaderListener
{
public:
    SB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(Grid, create);
    
    Grid();
    virtual ~Grid();
    
    virtual void onNodeLoaded(cocos2d::Node* pNode, spritebuilder::NodeLoader* pNodeLoader);

    virtual bool onAssignCCBMemberVariable(cocos2d::Ref* pTarget, const char* pMemberVariableName, cocos2d::Node* pNode);
    virtual bool onAssignCCBCustomProperty(cocos2d::Ref* target, const char* memberVariableName, const cocos2d::Value& value);
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::Ref* pTarget, const char* pSelectorName);
    virtual cocos2d::SEL_CallFuncN onResolveCCBCCCallFuncSelector(cocos2d::Ref* pTarget, const char* pSelectorName);
    virtual cocos2d::extension::Control::Handler onResolveCCBCCControlSelector(cocos2d::Ref* pTarget, const char* pSelectorName);
    
    
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
    void updateTileMoveFinished();
    
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
    
    const std::array<::Tile*, Constants::TOTAL_GRID_SIZE>& getGridArray();
    
private:
    std::atomic_int numTilesProcessingAnimThisRound_;
    int score_;
    float columnWidth_;
    float columnHeight_;
    float tileMarginVertical_;
    float tileMarginHorizontal_;
    std::array<::Tile*, Constants::TOTAL_GRID_SIZE> gridArray_;
    cocos2d::Vec2 startSwipe_;
    cocos2d::Vec2 endSwipe_;
    bool isReadyToReceiveInput_;
    bool showWinPopup_;
    bool showLosePopup_;
    
};



class GridSceneContentLoader : public spritebuilder::LayerColorLoader {
public:
    SB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(GridSceneContentLoader, loader);
    
protected:
    SB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(Grid);
    
};

#endif
