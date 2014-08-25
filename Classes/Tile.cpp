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
, im_(NULL)
{
    //value seeded with time at startup
    value_ = (rand() % 2 + 1) * 2;
    //CCLOG("Tile value: %d", value_);
}

Tile::~Tile()
{
    
}

bool Tile::init()
{
    //CCLOG("Tile init() called...");
    return true;
}

cocos2d::Node* Tile::load()
{
    spritebuilder::NodeLoaderLibrary* ccNodeLoaderLibrary = spritebuilder::NodeLoaderLibrary::getInstance();
    ccNodeLoaderLibrary->registerNodeLoader("Tile", TileSceneContentLoader::loader());
    
    spritebuilder::CCBReader* ccbReader = new spritebuilder::CCBReader(ccNodeLoaderLibrary);
    
    return ccbReader->readNodeGraphFromFile("Tile.ccbi");
}

void Tile::onNodeLoaded(cocos2d::Node* pNode, spritebuilder::NodeLoader* pNodeLoader)
{
    //CCLOG("onNodeLoaded callback called...");
    updateValueDisplay();
}

void Tile::updateTileActions()
{
    static_cast<Grid*>(this->getParent())->removeTileAction(this, TILE_CREATION_ANIMATION);
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
    backgroundNode_->setColor(backgroundColor);
    valueLabel_->setString(std::to_string(value_));
    
    //CCLOG("Setting frame %s for %p", frameName.c_str(), this);
    //CCLOG("Number of children %ld for %p", this->getChildrenCount(), this);
    //CCLOG("Current tile position with UpdateValueDisplay: x%f, y%f, z%f", this->getPositionX(), this->getPositionY(), this->getPositionZ());
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

bool Tile::onAssignCCBMemberVariable(cocos2d::Ref* pTarget, const char* pMemberVariableName, cocos2d::Node* pNode)
{
    //CCLOG("Tile::onAssignCCBMemberVariable: %s", pMemberVariableName);
    
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_backgroundNode", cocos2d::LayerColor*, this->backgroundNode_);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_im", cocos2d::Sprite*, this->im_);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_valueLabel", cocos2d::Label*, this->valueLabel_);
    
    return true;
}

bool Tile::onAssignCCBCustomProperty(cocos2d::Ref* target, const char* memberVariableName, const cocos2d::Value& value)
{
    //CCLOG("Tile::onAssignCCBCustomProperty: %s", memberVariableName);
    return false;
}

cocos2d::SEL_MenuHandler Tile::onResolveCCBCCMenuItemSelector(cocos2d::Ref * pTarget, const char* pSelectorName)
{
    //CCLOG("Tile::onResolveCCBCCMenuItemSelector: %s", pSelectorName);
    return NULL;
}

cocos2d::SEL_CallFuncN Tile::onResolveCCBCCCallFuncSelector(cocos2d::Ref * pTarget, const char* pSelectorName)
{
    //CCLOG("Tile::onResolveCCBCCCallFuncSelector: %s", pSelectorName);
    return NULL;
}

cocos2d::extension::Control::Handler Tile::onResolveCCBCCControlSelector(cocos2d::Ref * pTarget, const char* pSelectorName)
{
    //CCLOG("Tile::onResolveCCBCCControlSelector: %s", pSelectorName);
    //CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "play", TitleMenu::onPlayClicked);
    //CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "Tile", TitleMenu::onTileClicked);
    //CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "moregame", TitleMenu::onMoregameClicked);
    return NULL;
}

