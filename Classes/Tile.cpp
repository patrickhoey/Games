#include "Tile.h"
#include "CCUserDefault.h"
#include "SimpleAudioEngine.h"
#include "Constants.h"
#include "Grid.h"

using namespace CocosDenshion;

Tile::Tile() :
  value_(0)
, mergedThisRound_(false)
, valueLabel_(NULL)
, backgroundNode_(NULL)
, test_(NULL)
, im_(NULL)
{
    //value seeded with time at startup
    value_ = (rand() % 2 + 1) * 2;
    //CCLOG("Tile value: %d", value_);
    
    valueLabel_ = cocos2d::Label::create();
    backgroundNode_ = cocos2d::LayerColor::create();
    test_ = cocos2d::LayerColor::create();
    im_ = cocos2d::Sprite::create();
    
    this->addChild(valueLabel_);
    this->addChild(backgroundNode_);
    this->addChild(test_);
    this->addChild(im_);
}

Tile::~Tile()
{
    
}

bool Tile::init()
{
    //CCLOG("Tile init() called...");
    updateValueDisplay();
    return true;
}

void Tile::updateValueDisplay()
{
    //CCLOG("Updating valueDisplay with %p", this);
    /*
    if( NULL != this->getParent() )
    {
      CCLOG("updateValueDisplay:: Number of Grid's Children: %ld", this->getParent()->getChildrenCount());
        
        for(int i=0; i < Constants::TOTAL_GRID_SIZE; i++)
        {
            if( NULL != static_cast<Grid*>(this->getParent())->getGridArray()[i])
            {
                CCLOG("Tile child number %d with an address of %p", i, static_cast<Grid*>(this->getParent())->getGridArray()[i]);
            }
        }
    }else{
       CCLOG("updateValueDisplay:: No parent %p", this);
    }
    */
    //@TODO REMOVE ME
    //value_ = 8;
    
    cocos2d::Color3B backgroundColor;
    int tt = 0;
    
    switch (value_) {
        case 2:
            backgroundColor = cocos2d::Color3B(20, 20, 80);
            //[CCColor colorWithRed:20.f/255.f green:20.f/255.f blue:80.f/255.f];
            tt=1;
            break;
        case 4:
            backgroundColor = cocos2d::Color3B(20, 20, 140);
            //backgroundColor = [CCColor colorWithRed:20.f/255.f green:20.f/255.f blue:140.f/255.f];
            tt=2;
            break;
        case 8:
            backgroundColor = cocos2d::Color3B(20, 60, 220);
            //backgroundColor = [CCColor colorWithRed:20.f/255.f green:60.f/255.f blue:220.f/255.f];
            tt=3;
            break;
        case 16:
            backgroundColor = cocos2d::Color3B(20, 120, 120);
            //backgroundColor = [CCColor colorWithRed:20.f/255.f green:120.f/255.f blue:120.f/255.f];
            tt=4;
            break;
        case 32:
            backgroundColor = cocos2d::Color3B(20, 160, 120);
            //backgroundColor = [CCColor colorWithRed:20.f/255.f green:160.f/255.f blue:120.f/255.f];
            tt=5;
            break;
        case 64:
            backgroundColor = cocos2d::Color3B(20, 160, 60);
            //backgroundColor = [CCColor colorWithRed:20.f/255.f green:160.f/255.f blue:60.f/255.f];
            tt=6;
            showAds();
            break;
        case 128:
            backgroundColor = cocos2d::Color3B(50, 160, 60);
            //backgroundColor = [CCColor colorWithRed:50.f/255.f green:160.f/255.f blue:60.f/255.f];
            tt=7;
            showAds();
            break;
        case 256:
            backgroundColor = cocos2d::Color3B(80, 120, 60);
            //backgroundColor = [CCColor colorWithRed:80.f/255.f green:120.f/255.f blue:60.f/255.f];
            tt=8;
            showAds();
            break;
        case 512:
            backgroundColor = cocos2d::Color3B(140, 70, 60);
            //backgroundColor = [CCColor colorWithRed:140.f/255.f green:70.f/255.f blue:60.f/255.f];
            tt=9;
            showAds();
            break;
        case 1024:
            backgroundColor = cocos2d::Color3B(170, 30, 60);
            //backgroundColor = [CCColor colorWithRed:170.f/255.f green:30.f/255.f blue:60.f/255.f];
            tt=10;
            showAds();
            break;
        case 2048:
            backgroundColor = cocos2d::Color3B(220, 30, 30);
            //backgroundColor = [CCColor colorWithRed:220.f/255.f green:30.f/255.f blue:30.f/255.f];
            tt=11;
            break;
        default:
            backgroundColor = cocos2d::Color3B::GREEN;
            tt=12;
            break;
    }

   
    std::string frameName = "image_crown/b" + std::to_string(tt) + ".png";
    //std::string frameName = "b" + std::to_string(tt) + ".png";
    cocos2d::SpriteFrame* frame = cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName);
    
    if( NULL == frame)
    {
        CCLOG("Could not find frame %s", frameName.c_str());
    }
    
    //CCLOG("Tile: %s with value %s", frameName.c_str(), std::to_string(value_).c_str());
    im_->setSpriteFrame(frame);
    im_->setOrderOfArrival(1);

    backgroundNode_->setColor(backgroundColor);
    backgroundNode_->setOrderOfArrival(3);
   
    test_->setColor(backgroundColor);
    test_->setOrderOfArrival(2);
    
    valueLabel_->setString(std::to_string(value_));
    valueLabel_->setOrderOfArrival(4);
    
    /*
    cocos2d::Vector<Node*> children = this->getChildren();
    for( const auto& child : children)
    {
        child->setOpacity(1);
    }
     */
    
    
    CCLOG("Setting frame %s for %p", frameName.c_str(), this);
    CCLOG("Number of children %ld for %p", this->getChildrenCount(), this);
    CCLOG("Current tile position with UpdateValueDisplay: x%f, y%f, z%f", this->getPositionX(), this->getPositionY(), this->getPositionZ());
}

void Tile::showAds()
{
    
}


int Tile::getValue()
{
    return value_;
}

void Tile::setValue(int value)
{
    value_ = value;
}

bool Tile::isMergedThisRound()
{
    return mergedThisRound_;
}

void Tile::setIsMergedThisRound(bool isMerged)
{
    mergedThisRound_ = isMerged;
}

