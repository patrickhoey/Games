//
//  AdHelper.h
//  2048RPSPort
//
//  Created by Patrick Hoey on 8/13/14.
//
//

#ifndef _048RPSPort_AdHelper_h
#define _048RPSPort_AdHelper_h

class AdHelper
{
public:
    
    static void hideAdmobInterstitialAd();
    static void hideAdmobBannerAd();
    
    static void showAdmobInterstitialAd();
    static void showAdmobBannerAd();
    
    static bool isAdmobInterstitialShowing;
    static bool isAdmobBannerShowing;
};

#endif
