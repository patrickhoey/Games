//
//  AdHelper.cpp
//  2048RPSPort
//
//  Created by Patrick Hoey on 8/13/14.
//
//

#include "AdHelper.h"
#include "cocos2d.h"

bool AdHelper::isAdmobBannerShowing = true;

#if( CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "platform/android/jni/JniHelper.h"
#include <jni.h>

const char* AppActivityClassName = "org/cocos2dx/cpp/AppActivity";

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
    }
}

void AdHelper::showChartboostMoreAppsAd()
{
    cocos2d::JniMethodInfo t;
    CCLOG("showChartboostMoreAppsAd() called");
    
    if( cocos2d::JniHelper::getStaticMethodInfo(t, AppActivityClassName, "showChartboostMoreAppsAd", "()V"))
    {
        t.env->CallStaticVoidMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
        CCLOG("showChartboostMoreAppsAd() JNI called");
    }
}

void AdHelper::showChartboostInterstitualAd()
{
    cocos2d::JniMethodInfo t;
    CCLOG("showChartboostInterstitualAd() called");
    
    if( cocos2d::JniHelper::getStaticMethodInfo(t, AppActivityClassName, "showChartboostInterstitualAd", "()V"))
    {
        t.env->CallStaticVoidMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
        CCLOG("showChartboostInterstitualAd() JNI called");
    }
}


#else

void AdHelper::showAdmobBannerAd()
{
	CCLOG("showAdmobBannerAd() called");
	isAdmobBannerShowing = true;
	return; //nothing;
    
}

void AdHelper::hideAdmobBannerAd()
{
	CCLOG("hideAdmobBannerAd() called");
	isAdmobBannerShowing = false;
	return; //nothing
}


void AdHelper::showAdmobInterstitialAd()
{
	CCLOG("showAdmobInterstitialAd() called");
	return; //nothing;
    
}

void AdHelper::showChartboostMoreAppsAd()
{
    CCLOG("showChartboostMoreAppsAd() called");
    return;
}

void AdHelper::showChartboostInterstitualAd()
{
    CCLOG("showChartboostInterstitualAd() called");
    return;
}



#endif