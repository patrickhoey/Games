//
//  Grid.cpp
//  2048RPSPort
//
//  Created by Patrick Hoey on 8/3/14.
//
//

#include "Grid.h"

Grid::Grid() :
 columnWidth_(0.0)
, columnHeight_(0.0)
, tileMarginVertical_(0.0)
, tileMarginHorizontal_(0.0)
, gridArray_(0)
{
    
}

Grid::~Grid()
{
}

void Grid::setupBackground()
{
    Node* tile = Tile::load();
    columnWidth_ = (tile->getContentSize()).width;
    columnHeight_ = (tile->getContentSize()).height;
    
    CCLOG("GRID: The tile dimensions are width %f and height %f", columnWidth_, columnHeight_);
    
    tileMarginHorizontal_ = ((this->getContentSize()).width - (Constants::GRID_SIZE * columnWidth_)) / (Constants::GRID_SIZE + 1);
    tileMarginVertical_ = ((this->getContentSize()).height - (Constants::GRID_SIZE * columnWidth_)) / (Constants::GRID_SIZE + 1);

    float x = tileMarginHorizontal_;
    float y = tileMarginVertical_;
    
    for( int i = 0; i < Constants::GRID_SIZE; i++ )
    {
        x = tileMarginHorizontal_;
        
        for(int j=0; j < Constants::GRID_SIZE; j++ )
        {
            LayerColor* backgroundTile = LayerColor::create(cocos2d::Color4B::GRAY);
            backgroundTile->setContentSize(cocos2d::Size(columnWidth_, columnHeight_));
            backgroundTile->setPosition(x, y);
            //backgroundTile->setOpacity(0.2);
            this->addChild(backgroundTile);
            
            x += columnWidth_ + tileMarginHorizontal_;
        }
        
        y += columnHeight_ + tileMarginVertical_;
    }
}

void Grid::onNodeLoaded(cocos2d::Node* pNode, spritebuilder::NodeLoader* pNodeLoader)
{
    CCLOG("***Loaded Grid");
    setupBackground();
    
    //For a matrix, to access: (row * numCol) + col
    for(int row = 0; row < Constants::GRID_SIZE; row++){
        for(int col=0; col < Constants::GRID_SIZE; col++){
            //Get current index
            //int index = (row * Constants::GRID_SIZE) + col;
            gridArray_.push_back(::Tile::create());
        }
    }
    
    spawnStartTiles();
}

void Grid::spawnStartTiles()
{
    for(int i = 0; i < Constants::START_TILES; i++){
        spawnRandomTile();
    }
}

void Grid::spawnRandomTile()
{
    bool spawned = false;
    
    while( false == spawned )
    {
        int randomRow = rand() % Constants::GRID_SIZE;
        int randomCol = rand() % Constants::GRID_SIZE;
        
        int index = (randomRow * Constants::GRID_SIZE) + randomCol;
        bool isPositionFree = gridArray_[index]->isEmpty();
        
        if(true == isPositionFree){
            addTileAtColumn(randomRow, randomCol);
            spawned = true;
        }
    }
}

void Grid::addTileAtColumn(int row, int column)
{
    Tile* tile = static_cast<Tile*>(Tile::load());
    
    int index = (row * Constants::GRID_SIZE) + column;
    gridArray_[index] = tile;
    tile->setIsEmpty(false);
    tile->setScale(0.0f);
    this->addChild(tile);
    
    tile->setPosition(positionForColumn(row, column));
    
    cocos2d::DelayTime* delay = cocos2d::DelayTime::create(0.3f);
    cocos2d::ScaleTo* scaleTo = cocos2d::ScaleTo::create(0.2f, 1.0f);
    cocos2d::Sequence* sequence = cocos2d::Sequence::create(delay, scaleTo, NULL);
    
    tile->runAction(sequence);
    
}

cocos2d::Vec2 Grid::positionForColumn(int row, int column)
{

    int newRow = tileMarginHorizontal_ + row * (tileMarginHorizontal_ + columnWidth_);
    int newColumn = tileMarginVertical_ + column * (tileMarginVertical_ + columnHeight_);
    
    return cocos2d::Vec2(newRow, newColumn);
}


void Grid::showAds()
{
    
}