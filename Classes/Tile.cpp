#include "Tile.h"
#include "CCUserDefault.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

Tile::Tile() :
reader_(NULL)
, value_(0)
, mergedThisRound_(false)
, valueLabel_(NULL)
, backgroundNode_(NULL)
, test_(NULL)
, im_(NULL)
, isEmpty_(true)
{
    //value seeded with time at startup
    value_ = (rand() % 2 + 1) * 2;
    CCLOG("Tile value: %d", value_);
    
    valueLabel_ = cocos2d::Label::create();
    
    backgroundNode_ = cocos2d::LayerColor::create();
    test_ = cocos2d::LayerColor::create();
    
    im_ = cocos2d::Sprite::create();
}

Tile::~Tile()
{
}

cocos2d::Scene* Tile::createScene()
{
    spritebuilder::NodeLoaderLibrary* ccNodeLoaderLibrary = spritebuilder::NodeLoaderLibrary::getInstance();
    ccNodeLoaderLibrary->registerNodeLoader("Tile", TileSceneContentLoader::loader());
    
    spritebuilder::CCBReader* ccbReader = new spritebuilder::CCBReader(ccNodeLoaderLibrary);
    
    return ccbReader->createSceneWithNodeGraphFromFile("Tile.ccbi");
}

cocos2d::Node* Tile::load()
{
    spritebuilder::NodeLoaderLibrary* ccNodeLoaderLibrary = spritebuilder::NodeLoaderLibrary::getInstance();
    ccNodeLoaderLibrary->registerNodeLoader("Tile", TileSceneContentLoader::loader());
    
    spritebuilder::CCBReader* ccbReader = new spritebuilder::CCBReader(ccNodeLoaderLibrary);
    
    return ccbReader->readNodeGraphFromFile("Tile.ccbi");
}

bool Tile::isEmpty()
{
    return isEmpty_;
}

void Tile::setIsEmpty(bool isEmpty)
{
    isEmpty_ = isEmpty;
}

void Tile::setCCBReader(spritebuilder::CCBReader* reader)
{
    reader_ = reader;
}

void Tile::onNodeLoaded(cocos2d::Node* pNode, spritebuilder::NodeLoader* pNodeLoader)
{
    CCLOG("***Loaded Tile");
    updateValueDisplay();
}

void Tile::updateValueDisplay()
{
    valueLabel_->setString(std::to_string(value_));
    
    cocos2d::Color3B backgroundColor;
    int tt = 0;
    
    switch (value_) {
        case 2:
            backgroundColor = cocos2d::Color3B(20.0f/255.0f, 20.0f/255.0f, 80.0f/255.0f);
            //[CCColor colorWithRed:20.f/255.f green:20.f/255.f blue:80.f/255.f];
            tt=1;
            break;
        case 4:
            backgroundColor = cocos2d::Color3B(20.0f/255.0f, 20.0f/255.0f, 140.0f/255.0f);
            //backgroundColor = [CCColor colorWithRed:20.f/255.f green:20.f/255.f blue:140.f/255.f];
            tt=2;
            break;
        case 8:
            backgroundColor = cocos2d::Color3B(20.0f/255.0f, 60.0f/255.0f, 220.0f/255.0f);
            //backgroundColor = [CCColor colorWithRed:20.f/255.f green:60.f/255.f blue:220.f/255.f];
            tt=3;
            break;
        case 16:
            backgroundColor = cocos2d::Color3B(20.0f/255.0f, 120.0f/255.0f, 120.0f/255.0f);
            //backgroundColor = [CCColor colorWithRed:20.f/255.f green:120.f/255.f blue:120.f/255.f];
            tt=4;
            break;
        case 32:
            backgroundColor = cocos2d::Color3B(20.0f/255.0f, 160.0f/255.0f, 120.0f/255.0f);
            //backgroundColor = [CCColor colorWithRed:20.f/255.f green:160.f/255.f blue:120.f/255.f];
            tt=5;
            break;
        case 64:
            backgroundColor = cocos2d::Color3B(20.0f/255.0f, 160.0f/255.0f, 60.0f/255.0f);
            //backgroundColor = [CCColor colorWithRed:20.f/255.f green:160.f/255.f blue:60.f/255.f];
            tt=6;
            showAds();
            break;
        case 128:
            backgroundColor = cocos2d::Color3B(50.0f/255.0f, 160.0f/255.0f, 60.0f/255.0f);
            //backgroundColor = [CCColor colorWithRed:50.f/255.f green:160.f/255.f blue:60.f/255.f];
            tt=7;
            showAds();
            break;
        case 256:
            backgroundColor = cocos2d::Color3B(80.0f/255.0f, 120.0f/255.0f, 60.0f/255.0f);
            //backgroundColor = [CCColor colorWithRed:80.f/255.f green:120.f/255.f blue:60.f/255.f];
            tt=8;
            showAds();
            break;
        case 512:
            backgroundColor = cocos2d::Color3B(140.0f/255.0f, 70.0f/255.0f, 60.0f/255.0f);
            //backgroundColor = [CCColor colorWithRed:140.f/255.f green:70.f/255.f blue:60.f/255.f];
            tt=9;
            showAds();
            break;
        case 1024:
            backgroundColor = cocos2d::Color3B(170.0f/255.0f, 30.0f/255.0f, 60.0f/255.0f);
            //backgroundColor = [CCColor colorWithRed:170.f/255.f green:30.f/255.f blue:60.f/255.f];
            tt=10;
            showAds();
            break;
        case 2048:
            backgroundColor = cocos2d::Color3B(220.0f/255.0f, 30.0f/255.0f, 30.0f/255.0f);
            //backgroundColor = [CCColor colorWithRed:220.f/255.f green:30.f/255.f blue:30.f/255.f];
            tt=11;
            break;
        default:
            backgroundColor = cocos2d::Color3B::GREEN;
            tt=12;
            break;
    }

    backgroundNode_->setColor(backgroundColor);
    
    std::string frameName = "image_crown/b" + std::to_string(tt) + ".png";
    //std::string frameName = "b" + std::to_string(tt) + ".png";
    cocos2d::SpriteFrame* frame = cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName);
    
    test_->setColor(backgroundColor);
    im_->setSpriteFrame(frame);
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
    return false;
}

bool Tile::onAssignCCBCustomProperty(cocos2d::Ref* target, const char* memberVariableName, const cocos2d::Value& value)
{
    return false;
}

cocos2d::SEL_MenuHandler Tile::onResolveCCBCCMenuItemSelector(cocos2d::Ref * pTarget, const char* pSelectorName)
{
    return NULL;
}

cocos2d::SEL_CallFuncN Tile::onResolveCCBCCCallFuncSelector(cocos2d::Ref * pTarget, const char* pSelectorName)
{
    return NULL;
}

cocos2d::extension::Control::Handler Tile::onResolveCCBCCControlSelector(cocos2d::Ref * pTarget, const char* pSelectorName)
{
    //CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "play", TitleMenu::onPlayClicked);
    //CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "Tile", TitleMenu::onTileClicked);
    //CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "moregame", TitleMenu::onMoregameClicked);
    return NULL;
}

