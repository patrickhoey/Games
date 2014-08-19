/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2013-2014 Chukong Technologies Inc.

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
 ****************************************************************************/
package org.cocos2dx.cpp;

import org.cocos2dx.lib.Cocos2dxActivity;

import com.google.android.gms.ads.AdListener;
import com.google.android.gms.ads.AdSize;
import com.google.android.gms.ads.AdRequest;
import com.google.android.gms.ads.AdView;
import com.google.android.gms.ads.InterstitialAd;

import android.graphics.Color;
import android.os.Bundle;
import android.view.Gravity;
import android.view.View;
import android.widget.FrameLayout;

import com.chartboost.sdk.*;
import com.chartboost.sdk.Libraries.CBLogging.Level;
import com.chartboost.sdk.Libraries.CBOrientation;

public class AppActivity extends Cocos2dxActivity {

	private static boolean _showAdMobBanner = false;
	private static AdRequest _adRequest;
	private static AppActivity _appActivity;
	private AdView admobBannerAdView;
	private InterstitialAd admobInterstitialAdView;
	private static final String AD_UNIT_ID_INTERSTITIAL = "ca-app-pub-8379829573491079/1697101740";
	private static final String AD_UNIT_ID_BANNER = "ca-app-pub-8379829573491079/9220368549";
	private static final String CB_APP_ID = "53e920941873da4da78745c4";
	private static final String CB_APP_SIG = "01d9f804b09f736f30c331bec1309c6425488e08";
	private static Chartboost _cb;

	@Override
	protected void onCreate(Bundle savedInstanceState){
		super.onCreate(savedInstanceState);
		
		// Configure Chartboost
		_cb = Chartboost.sharedChartboost();
		_cb.onCreate(this, CB_APP_ID, CB_APP_SIG, null);
		CBPreferences.getInstance().setLoggingLevel(Level.ALL);
		CBPreferences.getInstance().setOrientation(CBOrientation.PORTRAIT);
		CBPreferences.getInstance().setImpressionsUseActivities(true);
		
		//Removes the Cocos2dxEditText
		//super.mFrameLayout.removeViewAt(0);
		
		//View parent = (View) super.mFrameLayout.getParent();
		//parent.setPadding(0, 0, 0, 0);
		
		//super.mFrameLayout.setPadding(0, 0, 0, 0);
		
		//Update parents layout parameters
		//FrameLayout.LayoutParams parentLayout = (LayoutParams) super.mFrameLayout.getLayoutParams();
		//parentLayout.width = FrameLayout.LayoutParams.MATCH_PARENT;
		//parentLayout.height = FrameLayout.LayoutParams.MATCH_PARENT;
		//parentLayout.gravity = Gravity.NO_GRAVITY;
		//super.mFrameLayout.setLayoutParams(parentLayout);
		        
		_adRequest = new AdRequest.Builder()
		.addTestDevice(AdRequest.DEVICE_ID_EMULATOR)
		.addTestDevice("HASH_DEVICE_ID")
		.build();        
		
		//Interstitial
		admobInterstitialAdView = new InterstitialAd(this);
		admobInterstitialAdView.setAdUnitId(AD_UNIT_ID_INTERSTITIAL);
	     // Set an AdListener.
		admobInterstitialAdView.setAdListener(new AdListener() {
            @Override
            public void onAdLoaded() {
            	admobInterstitialAdView.loadAd(_adRequest);
            }
            
            @Override
            public void onAdClosed(){
            	admobInterstitialAdView.loadAd(_adRequest);
            }
            
            @Override
            public void onAdFailedToLoad(int errorCode){
            	admobInterstitialAdView.loadAd(_adRequest);
            }
            
            @Override
            public void onAdOpened(){
            	admobInterstitialAdView.loadAd(_adRequest);
            }
            
        });
		
		admobInterstitialAdView.loadAd(_adRequest);
			
		//Banner
		FrameLayout.LayoutParams params = new FrameLayout.LayoutParams(FrameLayout.LayoutParams.MATCH_PARENT, FrameLayout.LayoutParams.WRAP_CONTENT);
		params.gravity = Gravity.BOTTOM;
		admobBannerAdView = new AdView(this);
		
		admobBannerAdView.setAdListener(new AdListener() {
            @Override
            public void onAdLoaded() {
           	
            	if(true == _showAdMobBanner)
            	{
            		showAdmobBannerAd();
            	}
            		
            }
            
            @Override
            public void onAdClosed(){
            	admobBannerAdView.loadAd(_adRequest);
            	
            	if(true == _showAdMobBanner)
            	{
            		showAdmobBannerAd();
            	}
            }
            
            @Override
            public void onAdFailedToLoad(int errorCode){
            	admobBannerAdView.loadAd(_adRequest);
            	
            	if(true == _showAdMobBanner)
            	{
            		showAdmobBannerAd();
            	}
            }
            
        });
		
		admobBannerAdView.setAdSize(AdSize.SMART_BANNER);
		admobBannerAdView.setAdUnitId(AD_UNIT_ID_BANNER);
        admobBannerAdView.setBackgroundColor(Color.TRANSPARENT);
        admobBannerAdView.setPadding(0, 0, 0, 0);        
        admobBannerAdView.loadAd(_adRequest);
        
        addContentView(admobBannerAdView, params);
		
		_appActivity = this;

	}
	
	public static void showAdmobBannerAd()
	{
		_appActivity.runOnUiThread(new Runnable()
		{

			@Override
			public void run()
			{	
				if( null == _appActivity.admobBannerAdView )
				{
					return;
				}
				_showAdMobBanner = true;
				_appActivity.admobBannerAdView.setEnabled(true);
				_appActivity.admobBannerAdView.setVisibility(View.VISIBLE);	
			}
		});

	}
	
	public static void hideAdmobBannerAd()
	{
		_appActivity.runOnUiThread(new Runnable()
		{

			@Override
			public void run()
			{
				if( null == _appActivity.admobBannerAdView )
				{
					return;
				}
				_showAdMobBanner = false;
				_appActivity.admobBannerAdView.setEnabled(false);
				_appActivity.admobBannerAdView.setVisibility(View.INVISIBLE);
			}
		});

	}

	public static void showChartboostInterstitualAd()
	{   
		_appActivity.runOnUiThread(new Runnable()
		{

			@Override
			public void run()
			{
				if( null == _cb )
				{
					return;
				}
				
				_cb.showInterstitial();
			}
		});
	}
	
	public static void showChartboostMoreAppsAd()
	{   
		_appActivity.runOnUiThread(new Runnable()
		{

			@Override
			public void run()
			{
				if( null == _cb )
				{
					return;
				}
				
				_cb.showMoreApps();
			}
		});
	}
	

	public static void showAdmobInterstitialAd()
	{
		_appActivity.runOnUiThread(new Runnable()
		{

			@Override
			public void run()
			{
				if( null == _appActivity.admobInterstitialAdView )
				{
					return;
				}
				
				if (_appActivity.admobInterstitialAdView.isLoaded())
				{
					_appActivity.admobInterstitialAdView.show();
					_appActivity.admobInterstitialAdView.loadAd(_adRequest);
				}
			}
		});

	}

	@Override
	protected void onStart() {
		super.onStart();
		
	    _cb.onStart(this);
	    _cb.cacheInterstitial();
	}

	@Override
	protected void onResume() 
	{
		super.onResume();
		if (admobBannerAdView != null ) 
		{
			admobBannerAdView.resume();
		}
	}

	@Override
	protected void onPause() 
	{
		if (admobBannerAdView != null) 
		{
			admobBannerAdView.pause();
		}
		super.onPause();
	}

	@Override
	protected void onDestroy() {
		if( _cb != null )
		{
			_cb.onDestroy(this); 			
		}
	        
		if( null != _appActivity.admobBannerAdView )
		{
			admobBannerAdView.destroy();
		}

		super.onDestroy();
	}
	
	
	// In onBackPressed()
	@Override
	public void onBackPressed() { 
	    // If an interstitial is on screen, close it. Otherwise continue as normal. 
	    if (_cb.onBackPressed()){ 
	        return; 
	    }
	    else{ 
	        super.onBackPressed();
	    }
	}
	
	@Override
	protected void onStop(){
	    super.onStop(); 
        
	    _cb.onStop(this); 	
	}

}

