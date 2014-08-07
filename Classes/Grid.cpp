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
, startSwipe_(0,0)
, endSwipe_(0,0)
{

}

Grid::~Grid()
{
}

const std::array<::Tile*, Constants::TOTAL_GRID_SIZE>& Grid::getGridArray()
{
    return gridArray_;
}

void Grid::setupBackground()
{
    Node* tile = ::Tile::load();
    columnWidth_ = (tile->getContentSize()).width;
    columnHeight_ = (tile->getContentSize()).height;
    
    //CCLOG("GRID: The tile dimensions are width %f and height %f", columnWidth_, columnHeight_);

    tileMarginHorizontal_ = ((this->getContentSize()).width - (Constants::GRID_SIZE * columnWidth_)) / (Constants::GRID_SIZE + 1);
    tileMarginVertical_ = ((this->getContentSize()).height - (Constants::GRID_SIZE * columnWidth_)) / (Constants::GRID_SIZE + 1);

    float x = tileMarginHorizontal_;
    float y = tileMarginVertical_;
    
    CCLOG("Tile margin horiz %f and vertical %f", tileMarginHorizontal_, tileMarginVertical_ );
    
    for( int i = 0; i < Constants::GRID_SIZE; i++ )
    {
        x = tileMarginHorizontal_;
        
        for(int j=0; j < Constants::GRID_SIZE; j++ )
        {
            LayerColor* backgroundTile = LayerColor::create(cocos2d::Color4B::GRAY);
            backgroundTile->setContentSize(cocos2d::Size(columnWidth_, columnHeight_));
            CCLOG("BackgroundTile position x%f, y%f", x,y);
            backgroundTile->setPosition(x, y);
            //backgroundTile->setLocalZOrder(INT_MAX);
            //backgroundTile->setOrderOfArrival(5);
            //backgroundTile->setOpacity(0.2);
            this->addChild(backgroundTile);
            
            x += columnWidth_ + tileMarginHorizontal_;
        }
        
        y += columnHeight_ + tileMarginVertical_;
    }
}

void Grid::onNodeLoaded(cocos2d::Node* pNode, spritebuilder::NodeLoader* pNodeLoader)
{
    //CCLOG("***Loaded Grid");
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
            //CCLOG("Swipe LEFT");
            swipeLeft();
        }
        else
        {
            //CCLOG("Swipe RIGHT");
            swipeRight();
        }
    }
    else
    {
        if( originVec.y > destVec.y )
        {
            //CCLOG("Swipe UP");
            swipeUp();
        }
        else
        {
            //CCLOG("Swipe DOWN");
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
                ::Tile* topNeighbor = tileForIndex(row, col+1);
                ::Tile* bottomNeighbor = tileForIndex(row, col-1);
                ::Tile* leftNeighbor = tileForIndex(row-1, col);
                ::Tile* rightNeighbor = tileForIndex(row+1, col);
                
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
            
            //CCLOG("move:: Tile %p", tile);
            
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
                //CCLOG("move:: OtherTile %p", otherTile);
                
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
                    //CCLOG("Moving Tile %p from %d,%d to %d,%d", tile, currentX, currentY, newX, newY);
                    moveTile(tile, currentX, currentY, newX, newY);
                    movedTilesThisRound = true;
                }
            }
            
            //Move further in this column
            currentY += yChange;
        
        }
        
        //Move to the next column, start at the initial row
        currentX += xChange;
        currentY = initialY;
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
    
    //::Tile* tile1 = gridArray_[toIndex];
    //::Tile* tile2 = gridArray_[fromIndex];
    //CCLOG("BEFORE: Copying from tile %p to tile %p", tile2, tile1);
    
    gridArray_[toIndex] = gridArray_[fromIndex];
    gridArray_[fromIndex] = NULL;
    
    
    //::Tile* tile3 = gridArray_[toIndex];
    //::Tile* tile4 = gridArray_[fromIndex];
    //CCLOG("AFTER: Copied from tile %p to tile %p", tile4, tile3);
    
    cocos2d::Vec2 newPosition = positionForColumn(toX, toY);
    cocos2d::MoveTo* moveTo = cocos2d::MoveTo::create(0.2f, newPosition);

    tile->runAction(moveTo);
}

void Grid::mergeTileAtIndex(const int& fromX, const int& fromY, const int& toX, const int& toY)
{
    //CCLOG("***mergeTileAtIndex***");
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
    
    //CCLOG("1) MergedTile: %p OtherTile %p", mergedTile, otherTile);
    
    score_ += mergedTile->getValue() + otherTile->getValue();
    
    int newValue = 2*(otherTile->getValue());
    
    //CCLOG("MergedTile: %p OtherTile %p", mergedTile, otherTile);
    
    otherTile->setValue(newValue);
    otherTile->setIsMergedThisRound(true);
    
    //CCLOG("MergedTile: %p OtherTile %p", mergedTile, otherTile);
    
    if( otherTile->getValue() == Constants::WIN_TILE)
    {
        win();
    }
    
    gridArray_[fromIndex] = NULL;
    
    cocos2d::Vec2 otherTilePosition = positionForColumn(toX, toY);
    //CCLOG("Merge Tile to position %f, %f", otherTilePosition.x, otherTilePosition.y);
    
    cocos2d::MoveTo* moveTo = cocos2d::MoveTo::create(0.2f, otherTilePosition);
    cocos2d::CallFuncN* callSelectorAction = cocos2d::CallFuncN::create(CC_CALLBACK_0(::Tile::updateValueDisplay,otherTile));
    //cocos2d::CallFuncN* callSelectorAction = cocos2d::CallFuncN::create(CC_CALLBACK_1(::Tile::updateValueDisplayCB,otherTile));
    cocos2d::RemoveSelf* remove = cocos2d::RemoveSelf::create();

    cocos2d::Sequence* sequence = cocos2d::Sequence::create(moveTo, callSelectorAction, remove, NULL);

    //CCLOG("BEFORE: MergedTile: %p: ", mergedTile);
    mergedTile->runAction(sequence);

    //CCLOG("AFTER:  MergedTile: %p: ", mergedTile);

    //@TODO add scale logic here
    //CCLOG("Explosion effects");
    
    //cocos2d::SpriteFrame* explosionSprite = cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName("explosion_001.png");
    cocos2d::Sprite* explosionSprite = cocos2d::Sprite::createWithSpriteFrameName("explosion_001.png");
    float centerOffset = 30.0f;
    explosionSprite->setPosition(otherTilePosition.x+centerOffset, otherTilePosition.y+centerOffset);
    
    //CCLOG("Explosion position %f, %f", otherTilePosition.x, otherTilePosition.y);
    
    this->addChild(explosionSprite);
    
    cocos2d::Vector<cocos2d::SpriteFrame*> spriteFrames;
    
    for(int i=1; i <= 6; i++)
    {
        std::string frameName = "explosion_00" + std::to_string(i) + ".png";
        //CCLOG("Explosion frames %d of 6 named %s", i,frameName.c_str());
        cocos2d::SpriteFrame* spriteFrame = cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName);
        spriteFrames.pushBack(spriteFrame);
    }
    
    //cocos2d::MoveTo* moveAnimTo = cocos2d::MoveTo::create(0.2f, otherTilePosition);
    cocos2d::Animation* animation = cocos2d::Animation::createWithSpriteFrames(spriteFrames,0.05f);
    cocos2d::Animate* animate = cocos2d::Animate::create(animation);
    cocos2d::RemoveSelf* removeAnim = cocos2d::RemoveSelf::create();
    cocos2d::Sequence* movingSequenceAndOtherStuffAfter = cocos2d::Sequence::create(animate, removeAnim, NULL);

    explosionSprite->runAction(movingSequenceAndOtherStuffAfter);
    
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
        //CCLOG("BAD X isIndexValid X %d Y %d", x,y );
        return false;
    }
    
    if( y < 0 || y >= Constants::GRID_SIZE ){
        //CCLOG("BAD Y isIndexValid X %d Y %d", x,y );
        return false;
    }
 
    //CCLOG("isIndexValid X %d Y %d", x,y );
    return true;
}


void Grid::spawnStartTiles()
{
    for(int i = 0; i < Constants::START_TILES; i++){
        //CCLOG("Spawning tile %d of %d", i, Constants::START_TILES-1);
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
            //CCLOG("Adding tile at location %d,%d", randomRow, randomCol);
            addTileAtColumn(randomRow, randomCol);
            spawned = true;
        }
    }
}

void Grid::addTileAtColumn(int row, int column)
{
    //::Tile* tile = static_cast<::Tile*>(::Tile::load());
    ::Tile* tile = static_cast<::Tile*>(::Tile::create());
    
    int index = (row * Constants::GRID_SIZE) + column;
    
    gridArray_[index] = tile;
    
    //CCLOG("addtileatcolumn: Fresh tile position is x%f, y%f, z%f", tile->getPositionX(), tile->getPositionY(), tile->getPositionZ());
    
    tile->setScale(0.0f);
    tile->setPosition(positionForColumn(row, column));
    
    //CCLOG("addtileatcolumn: After set position is x%f, y%f, z%f", tile->getPositionX(), tile->getPositionY(), tile->getPositionZ());
    
    cocos2d::DelayTime* delay = cocos2d::DelayTime::create(0.3f);
    cocos2d::ScaleTo* scaleTo = cocos2d::ScaleTo::create(0.2f, 1.0f);
    cocos2d::Sequence* sequence = cocos2d::Sequence::create(delay, scaleTo, NULL);
    
    tile->runAction(sequence);
    this->addChild(tile);
    
    /*
    CCLOG("Number of Grid's Children: %ld", this->getChildrenCount());
    
    for(int i=0; i < Constants::TOTAL_GRID_SIZE; i++)
    {
        if( NULL != gridArray_[i])
        {
            CCLOG("Tile child number %d with an address of %p", i, gridArray_[i]);
        }
    }
     */
}

cocos2d::Vec2 Grid::positionForColumn(int row, int column)
{
    //CCLOG("Position for incoming row %d col %d", row, column);

    int newRow = tileMarginHorizontal_ + row * (tileMarginHorizontal_ + columnWidth_);
    int newColumn = tileMarginVertical_ + column * (tileMarginVertical_ + columnHeight_);
    
    //CCLOG("Position for new row %d col %d", newRow, newColumn);
    
    return cocos2d::Vec2(newRow, newColumn);
}


void Grid::showAds()
{
    
}