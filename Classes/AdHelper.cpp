//
//  AdHelper.cpp
//  2048RPSPort
//
//  Created by Patrick Hoey on 8/13/14.
//
//

#include "AdHelper.h"
#include "cocos2d.h"

bool AdHelper::isAdShowing = true;

#if( CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "platform/android/jni/JniHelper.h"
#include <jni.h>

const char* AppActivityClassName = "org/cocos2dx/cpp/AppActivity";

void AdHelper::hideAd()
{
    cocos2d::JniMethodInfo t;
    CCLOG("hideAd() called");
    
    if( cocos2d::JniHelper::getStaticMethodInfo(t, AppActivityClassName, "hideAd", "()V"))
    {
        t.env->CallStaticVoidMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
        CCLOG("hideAd() JNI called");
        isAdShowing = false;
    }
}

void AdHelper::showAd()
{
    cocos2d::JniMethodInfo t;
    CCLOG("showAd() called");
    
    if( cocos2d::JniHelper::getStaticMethodInfo(t, AppActivityClassName, "showAd", "()V"))
    {
        t.env->CallStaticVoidMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
        CCLOG("showAd() JNI called");
        isAdShowing = true;
    }
}

#else

void AdHelper::hideAd()
{
	CCLOG("hideAd() called");
	isAdShowing = false;
	return; //nothing
}


void AdHelper::showAd()
{
	CCLOG("showAd() called");
	isAdShowing = true;
	return; //nothing;
    
}


#endif