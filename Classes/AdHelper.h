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

    static void showAdmobBannerAd();
    static void hideAdmobBannerAd();
    static void showAdmobInterstitialAd();
    static bool isAdmobBannerShowing;
    
    static void showChartboostMoreAppsAd();
    static void showChartboostInterstitualAd();

};

#endif
