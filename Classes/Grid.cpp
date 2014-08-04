//
//  Grid.cpp
//  2048RPSPort
//
//  Created by Patrick Hoey on 8/3/14.
//
//

#include "Grid.h"

Grid::Grid() :
 reader_(NULL)
, columnWidth_(0.0)
, columnHeight_(0.0)
, tileMarginVertical_(0.0)
, tileMarginHorizontal_(0.0)
, gridArray_(Constants::TOTAL_GRID_SIZE)
{
    
}

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

void Grid::setupBackground()
{
    Node* tile = Tile::load();
    columnWidth_ = (tile->getContentSize()).width;
    columnHeight_ = (tile->getContentSize()).height;
    
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
            backgroundTile->setOpacity(0.2);
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
