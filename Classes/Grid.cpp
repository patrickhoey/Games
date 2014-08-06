//
//  Grid.cpp
//  2048RPSPort
//
//  Created by Patrick Hoey on 8/3/14.
//
//

#include "Grid.h"
#include <array>
#include "SimpleAudioEngine.h"
#include "CCUserDefault.h"
#include "GameEnd.h"

Grid::Grid() :
  score_(0)
, columnWidth_(0.0)
, columnHeight_(0.0)
, tileMarginVertical_(0.0)
, tileMarginHorizontal_(0.0)
, gridArray_(Constants::TOTAL_GRID_SIZE)
, startSwipe_(0,0)
, endSwipe_(0,0)
{

}

Grid::~Grid()
{
}

void Grid::setupBackground()
{
    Node* tile = ::Tile::load();
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
            int index = (row * Constants::GRID_SIZE) + col;
            gridArray_[index] = NULL;
        }
    }
    
    spawnStartTiles();

    //@TODO Add touch gestures here using EventListener
    auto listener = EventListenerTouchOneByOne::create();
    
    // When "swallow touches" is true, then returning 'true' from the onTouchBegan method will "swallow" the touch event, preventing other listeners from using it.
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan =  CC_CALLBACK_2(Grid::onTouchBegan, this);
    listener->onTouchMoved =  CC_CALLBACK_2(Grid::onTouchMoved, this);
    listener->onTouchEnded =  CC_CALLBACK_2(Grid::onTouchEnded, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

bool Grid::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
{
    startSwipe_ = touch->getLocationInView();
    return true;
}

void Grid::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event)
{
}

void Grid::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event)
{
    endSwipe_ = touch->getLocationInView();
   
    cocos2d::Vec2 originVec(startSwipe_);
    cocos2d::Vec2 destVec(endSwipe_);
    
    cocos2d::Vec2 distance(0,0);
    
    cocos2d::Vec2::subtract(destVec, originVec, &distance );
    
    //Remove any negative values
    distance.x *= distance.x;
    distance.y *= distance.y;
    
    if( distance.x >= distance.y )
    {
        if( originVec.x > destVec.x )
        {
            CCLOG("Swipe LEFT");
            swipeLeft();
        }
        else
        {
            CCLOG("Swipe RIGHT");
            swipeRight();
        }
    }
    else
    {
        if( originVec.y > destVec.y )
        {
            CCLOG("Swipe UP");
            swipeUp();
        }
        else
        {
            CCLOG("Swipe DOWN");
            swipeDown();
        }
        
    }
    
}

void Grid::swipeLeft()
{
    move(cocos2d::Vec2(-1,0));
}

void Grid::swipeRight()
{
    move(cocos2d::Vec2(1,0));
}

void Grid::swipeDown()
{
    move(cocos2d::Vec2(0,-1));
}

void Grid::swipeUp()
{
    move(cocos2d::Vec2(0,1));
}


bool Grid::movePossible()
{
    for( int row = 0; row < Constants::GRID_SIZE; row++)
    {
        for(int col = 0; col < Constants::GRID_SIZE; col++)
        {
            int index = (row * Constants::GRID_SIZE) + col;
            ::Tile* tile = gridArray_[index];
            
            if( NULL == tile){
                //No tile at this position
                //Move possible, we have a free field
                return true;
            }
            else{
                //There is a tile at this position, check immediately surrounding neighbors
                ::Tile* topNeighbor = tileForIndex(row+1, col);
                ::Tile* bottomNeighbor = tileForIndex(row-1, col);
                ::Tile* leftNeighbor = tileForIndex(row, col-1);
                ::Tile* rightNeighbor = tileForIndex(row, col+1);
                
                std::array<::Tile*, 4> neighbors = {topNeighbor,bottomNeighbor,leftNeighbor, rightNeighbor};
                
                for(const auto& neighbor: neighbors){
                    if( NULL != neighbor){
                        if( neighbor->getValue() == tile->getValue() ){
                            //We found a neighbor that has the same value as current tile, possible move
                            return true;
                        }
                    }
                }
            }
        }
    }
    
    return false;
}

void Grid::nextRound()
{
    spawnRandomTile();
    for(int row = 0; row < Constants::GRID_SIZE; row++)
    {
        for(int col = 0; col < Constants::GRID_SIZE; col++)
        {
            int index = (row * Constants::GRID_SIZE) + col;
            ::Tile* tile = gridArray_[index];
            
            if( NULL != tile){
                tile->setIsMergedThisRound(false);
            }
        }
    }
    
    bool isMovePossible = movePossible();
    
    if( false == isMovePossible){
        lose();
    }
    
}

void Grid::win()
{
    auto userDefaults = cocos2d::UserDefault::getInstance();
    bool soundMode = userDefaults->getBoolForKey("soundmode1", true);
    //CCLOG("**SOUNDMODE: %s", soundMode ? "true" : "false");
    
    //If the mode is sound ON, then make sure it is enabled
    if(true == soundMode){
        //CCLOG("**Sound ON: %s", soundMode ? "true" : "false");
        
        CocosDenshion::SimpleAudioEngine* sound = CocosDenshion::SimpleAudioEngine::getInstance();
        sound->playEffect(Constants::WIN_SOUND);
    }
    
    endGameWithMessage("You win! Congratulations!");
}

void Grid::lose()
{
    auto userDefaults = cocos2d::UserDefault::getInstance();
    bool soundMode = userDefaults->getBoolForKey("soundmode1", true);
    //CCLOG("**SOUNDMODE: %s", soundMode ? "true" : "false");
    
    //If the mode is sound ON, then make sure it is enabled
    if(true == soundMode){
        //CCLOG("**Sound ON: %s", soundMode ? "true" : "false");
        
        CocosDenshion::SimpleAudioEngine* sound = CocosDenshion::SimpleAudioEngine::getInstance();
        sound->playEffect(Constants::LOSE_SOUND);
    }
    
    endGameWithMessage("You didn't win. Please play Again!");
}

void Grid::endGameWithMessage(const std::string& message)
{
    GameEnd* gameEndPopover = static_cast<GameEnd*>(GameEnd::load());
    
    gameEndPopover->setPosition(0.5f, 0.5f);
    gameEndPopover->setLocalZOrder(INT_MAX);
    
    gameEndPopover->setMessage(message, score_);
    
    this->addChild(gameEndPopover);
}

void Grid::move(cocos2d::Vec2 direction)
{
    //Apply negative vector until reaching boundary, this way we get the tile that is furthest away
    int currentX = 0;
    int currentY = 0;
    
    //bottom left corner
    bool movedTilesThisRound = false;
    
    //1) Move to relevant edge by applying direction until reaching border
    while( true == isIndexValid(direction.x, direction.y))
    {
        float nextX = currentX + direction.x;
        float nextY = currentY + direction.y;
        
        if( true == isIndexValid(nextX, nextY) ){
            currentX = nextX;
            currentY = nextY;
        }else{
            break;
        }
    }
    
    //store initial row value to reset after completing each column
    int initialY = currentY;
    
    //define changing of x and y value (moving left, up, down, or right)
    int xChange = -direction.x;
    int yChange = -direction.y;
    
    if(0 == xChange){
        xChange = 1;
    }
    
    if( 0 == yChange){
        yChange = 1;
    }
    
    //Visit column for column
    while( true == isIndexValid(currentX, currentY))
    {
        while(true == isIndexValid(currentX, currentY))
        {
            //Get tile at current index
            int index = (currentX * Constants::GRID_SIZE) + currentY;
            ::Tile* tile = gridArray_[index];
            
            if(NULL == tile){
                //If there is no tile at this index then skip
                currentY += yChange;
                continue;
            }
            
            //store index in temp variables to change them and store new location of this tile
            int newX = currentX;
            int newY = currentY;
            
            //Find the furthest position by iterating in direction of the vector until we reach border of grid or an occupid cell
            
            while( isIndexValidAndUnoccupied(newX+direction.x, newY+direction.y))
            {
                newX += direction.x;
                newY += direction.y;
            }
            
            bool performMove = false;
            
            //If we stopped moving in vector direction, but next index in vector direction is valid,
            //this means the cell is occupied
            
            if( true == isIndexValid(newX + direction.x, newY + direction.y))
            {
                //get the other tile
                int otherTileX = newX + direction.x;
                int otherTileY = newY + direction.y;
                int index = (otherTileX * Constants::GRID_SIZE) + otherTileY;
                ::Tile* otherTile = gridArray_[index];
                
                //compare value of other tile and also check if the other tile has been merged this round
                if( tile->getValue() == otherTile->getValue() &&
                   (false == otherTile->isMergedThisRound()) )
                {
                    //merge tiles
                    mergeTileAtIndex(currentX, currentY, otherTileX, otherTileY);
                    movedTilesThisRound = true;
                }
                else
                {
                    //We cannot merge so we want to perform a move
                    performMove = true;
                }
            }
            else
            {
                //we cannot merge so we want ot perform a move
                performMove = true;
            }
            
            if( true == performMove)
            {
                //Move tile to furthest position
                if( newX != currentX || newY != currentY)
                {
                    //Only move tile if position changed
                    moveTile(tile, currentX, currentY, newX, newY);
                    movedTilesThisRound = true;
                }
            }
            
            //Move further in this column
            currentY += yChange;
        
        }
        
        //Move to the next column, start at the initial row
        currentX += xChange;
        currentY += initialY;
    }
    
    if( true == movedTilesThisRound )
    {
        nextRound();
    }
}

void Grid::moveTile(::Tile* tile, const int& fromX, const int& fromY, const int& toX, const int& toY)
{
    
    int fromIndex = (fromX * Constants::GRID_SIZE) + fromY;
    int toIndex = (toX * Constants::GRID_SIZE) + toY;
    
    gridArray_[toIndex] = gridArray_[fromIndex];
    gridArray_[fromIndex] = NULL;
    
    cocos2d::Vec2 newPosition = positionForColumn(toX, toY);
    
    cocos2d::MoveTo* moveTo = cocos2d::MoveTo::create(0.2f, newPosition);

    tile->runAction(moveTo);
}

void Grid::mergeTileAtIndex(const int& fromX, const int& fromY, const int& toX, const int& toY)
{
    auto userDefaults = cocos2d::UserDefault::getInstance();
    bool soundMode = userDefaults->getBoolForKey("soundmode1", true);
    //CCLOG("**SOUNDMODE: %s", soundMode ? "true" : "false");
    
    //If the mode is sound ON, then make sure it is enabled
    if(true == soundMode){
        //CCLOG("**Sound ON: %s", soundMode ? "true" : "false");
        
        CocosDenshion::SimpleAudioEngine* sound = CocosDenshion::SimpleAudioEngine::getInstance();
        sound->playEffect(Constants::MERGE_SOUND);
    }
    
    int fromIndex = (fromX * Constants::GRID_SIZE) + fromY;
    ::Tile* mergedTile = gridArray_[fromIndex];
    
    int toIndex = (toX * Constants::GRID_SIZE) + toY;
    ::Tile* otherTile = gridArray_[toIndex];
    
    score_ += mergedTile->getValue() + otherTile->getValue();
    
    otherTile->setValue(otherTile->getValue()*2);
    otherTile->setIsMergedThisRound(true);
    
    if( otherTile->getValue() == Constants::WIN_TILE)
    {
        win();
    }
    
    gridArray_[fromIndex] = NULL;
    
    cocos2d::Vec2 otherTilePosition(toX, toY);
    
    cocos2d::MoveTo* moveTo = cocos2d::MoveTo::create(0.2f, otherTilePosition);
    cocos2d::RemoveSelf* remove = cocos2d::RemoveSelf::create();
    cocos2d::CallFuncN* callSelectorAction = cocos2d::CallFuncN::create(CC_CALLBACK_0(::Tile::updateValueDisplay,otherTile));
    
    cocos2d::Sequence* sequence = cocos2d::Sequence::create(moveTo, remove, callSelectorAction, NULL);
    
    mergedTile->runAction(sequence);
    
    //@TODO add scale logic here
    
    cocos2d::SpriteFrameCache::getInstance()->addSpriteFramesWithFile("effect3-hd.plist");
    
    cocos2d::Sprite* explosionSprite = cocos2d::Sprite::create("explosion_001.png");
    explosionSprite->setPosition(otherTilePosition.x+30, otherTilePosition.y+30);
    
    this->addChild(explosionSprite);
    
    cocos2d::Vector<cocos2d::SpriteFrame*> spriteFrames;
    
    for(int i=0; i <= 6; ++i)
    {
        std::string frameName = "explosion_00" + std::to_string(i) + ".png";
        cocos2d::SpriteFrame* spriteFrame = cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName);
        spriteFrames.pushBack(spriteFrame);
    }
    
    cocos2d::Animation* animation = cocos2d::Animation::createWithSpriteFrames(spriteFrames);
    cocos2d::Animate* animate = cocos2d::Animate::create(animation);
    cocos2d::Sequence* movingSequeceAndOtherStuffAfter = cocos2d::Sequence::create(animate, remove, NULL);

    explosionSprite->runAction(movingSequeceAndOtherStuffAfter);
}


::Tile* Grid::tileForIndex(int x, int y)
{
    bool validIndex = isIndexValid(x,y);
    
    if( false == validIndex ){
        return NULL;
    }else{
        int index = (x * Constants::GRID_SIZE) + y;
        return gridArray_[index];
    }
}

bool Grid::isIndexValidAndUnoccupied(const int& x, const int& y)
{
    if( false == isIndexValid(x,y) )
    {
        return false;
    }
    
    int index = (x * Constants::GRID_SIZE) + y;
    
    if( NULL != gridArray_[index] )
    {
        return false;
    }
    
    return true;
}

bool Grid::isIndexValid(const int& x, const int& y)
{
    //Check bounds
    if( x < 0 || x >= Constants::GRID_SIZE ){
        return false;
    }
    
    if( y < 0 || y >= Constants::GRID_SIZE ){
        return false;
    }
    
    return true;
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
        bool isPositionFree = (gridArray_[index] == NULL) ? true : false;
        
        if(true == isPositionFree){
            addTileAtColumn(randomRow, randomCol);
            spawned = true;
        }
    }
}

void Grid::addTileAtColumn(int row, int column)
{
    ::Tile* tile = static_cast<::Tile*>(::Tile::load());
    
    int index = (row * Constants::GRID_SIZE) + column;
    gridArray_[index] = tile;
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