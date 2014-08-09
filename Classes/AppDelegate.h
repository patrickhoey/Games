#ifndef  _APP_DELEGATE_H_
#define  _APP_DELEGATE_H_

#include "cocos2d.h"
#include "editor-support/SpriteBuilder.h"

//String constants for the ad network session/API keys
#define ChartBoostID "53ce8f2b89b0bb212c41a197"
#define ChartBoostSignature "b878fba902e10839c8f88aaa05d8ace63ecfd302"
#define kAppLovin1 "99lggvdEHo00AAq0IrxDZzJdaEG-9s1I0m-gfbwxOxyT5mTObUc9Swn191_Iu0bunZZQATMTOJ6U4fuf9UpbOa"
#define kRevMob1 "53ce902ad03310d30687811b"

#define COCOS2D_DEBUG 1

/**
@brief    The cocos2d Application.

The reason for implement as private inheritance is to hide some interface call by Director.
*/
class  AppDelegate : private cocos2d::Application
{
private:
    int _soundMode;
public:
    AppDelegate();
    virtual ~AppDelegate();
    
    int getSoundMode();
    void setSoundMode(int soundMode);

    /**
    @brief    Implement Director and Scene init code here.
    @return true    Initialize success, app continue.
    @return false   Initialize failed, app terminate.
    */
    virtual bool applicationDidFinishLaunching();

    /**
    @brief  The function be called when the application enter background
    @param  the pointer of the application
    */
    virtual void applicationDidEnterBackground();

    /**
    @brief  The function be called when the application enter foreground
    @param  the pointer of the application
    */
    virtual void applicationWillEnterForeground();
};
 
#endif // _APP_DELEGATE_H_

