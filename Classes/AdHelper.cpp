//
//  AdHelper.cpp
//  2048RPSPort
//
//  Created by Patrick Hoey on 8/13/14.
//
//

#include "AdHelper.h"
#include "cocos2d.h"

bool AdHelper::isAdmobInterstitialShowing = true;
bool AdHelper::isAdmobBannerShowing = true;

#if( CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "platform/android/jni/JniHelper.h"
#include <jni.h>

const char* AppActivityClassName = "org/cocos2dx/cpp/AppActivity";

void AdHelper::hideAdmobInterstitialAd()
{
    cocos2d::JniMethodInfo t;
    CCLOG("hideAdmobInterstitialAd() called");
    
    if( cocos2d::JniHelper::getStaticMethodInfo(t, AppActivityClassName, "hideAdmobInterstitialAd", "()V"))
    {
        t.env->CallStaticVoidMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
        CCLOG("hideAdmobInterstitialAd() JNI called");
        isAdmobInterstitialShowing = false;
    }
}

void AdHelper::hideAdmobBannerAd()
{
    cocos2d::JniMethodInfo t;
    CCLOG("hideAdmobBannerAd() called");
    
    if( cocos2d::JniHelper::getStaticMethodInfo(t, AppActivityClassName, "hideAdmobBannerAd", "()V"))
    {
        t.env->CallStaticVoidMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
        CCLOG("hideAdmobBannerAd() JNI called");
        isAdmobBannerShowing = false;
    }
}

void AdHelper::showAdmobInterstitialAd()
{
    cocos2d::JniMethodInfo t;
    CCLOG("showAdmobInterstitialAd() called");
    
    if( cocos2d::JniHelper::getStaticMethodInfo(t, AppActivityClassName, "showAdmobInterstitialAd", "()V"))
    {
        t.env->CallStaticVoidMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
        CCLOG("showAdmobInterstitialAd() JNI called");
        isAdmobInterstitialShowing = true;
    }
}

void AdHelper::showAdmobBannerAd()
{
    cocos2d::JniMethodInfo t;
    CCLOG("showAdmobBannerAd() called");
    
    if( cocos2d::JniHelper::getStaticMethodInfo(t, AppActivityClassName, "showAdmobBannerAd", "()V"))
    {
        t.env->CallStaticVoidMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
        CCLOG("showAdmobBannerAd() JNI called");
        isAdmobBannerShowing = true;
    }
}

#else

void AdHelper::hideAdmobInterstitialAd()
{
	CCLOG("hideAd() called");
	isAdmobInterstitialShowing = false;
	return; //nothing
}

void AdHelper::hideAdmobBannerAd()
{
	CCLOG("hideAd() called");
	isAdmobBannerShowing = false;
	return; //nothing
}


void AdHelper::showAdmobInterstitialAd()
{
	CCLOG("showAd() called");
	isAdmobInterstitialShowing = true;
	return; //nothing;
    
}

void AdHelper::showAdmobBannerAd()
{
	CCLOG("showAd() called");
	isAdmobBannerShowing = true;
	return; //nothing;
    
}


#endif