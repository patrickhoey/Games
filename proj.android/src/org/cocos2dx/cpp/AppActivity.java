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

import com.google.android.gms.ads.AdRequest;
import com.google.android.gms.ads.AdView;
import com.taptapdone.Port2048.R;

import android.os.Bundle;
import android.view.View;

public class AppActivity extends Cocos2dxActivity {

	private static AppActivity _appActivity;
	private AdView admobBannerAdView;
	private AdView admobInterstitialAdView;
	//private static final String AD_UNIT_ID_INTERSTITIAL = "ca-app-pub-8379829573491079/1697101740";
	//private static final String AD_UNIT_ID_BANNER = "ca-app-pub-8379829573491079/9220368549";

	@Override
	protected void onCreate(Bundle savedInstanceState){
		super.onCreate(savedInstanceState);	
		setContentView(R.layout.main_layout);
				
		admobBannerAdView = (AdView) findViewById(R.id.admobBannerAdView);
		//admobInterstitialAdView = new AdView(this);
        
		AdRequest adRequest = new AdRequest.Builder()
		.addTestDevice(AdRequest.DEVICE_ID_EMULATOR)
		.addTestDevice("HASH_DEVICE_ID")
		.build();        
		
		//Interstitial
		/*
		admobInterstitialAdView.setAdSize(AdSize.FULL_BANNER);
		admobInterstitialAdView.setAdUnitId(AD_UNIT_ID_INTERSTITIAL);		
		admobInterstitialAdView.setBackgroundColor(Color.BLACK);
		admobInterstitialAdView.setPadding(0, 0, 0, 0);
		admobInterstitialAdView.loadAd(adRequest);
		*/
		
		//Banner
		/*
		admobBannerAdView.setAdSize(AdSize.BANNER);
		admobBannerAdView.setAdUnitId(AD_UNIT_ID_BANNER);		
        admobBannerAdView.setBackgroundColor(Color.BLACK);
        admobBannerAdView.setPadding(0, 0, 0, 0);
        */
		
        admobBannerAdView.loadAd(adRequest);
		
		_appActivity = this;

	}


	public static void hideAdmobInterstitialAd()
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
				
				if (_appActivity.admobInterstitialAdView.isEnabled())
					_appActivity.admobInterstitialAdView.setEnabled(false);
				if (_appActivity.admobInterstitialAdView.getVisibility() != 4 )
					_appActivity.admobInterstitialAdView.setVisibility(View.INVISIBLE);
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
				
				if (_appActivity.admobBannerAdView.isEnabled())
					_appActivity.admobBannerAdView.setEnabled(false);
				if (_appActivity.admobBannerAdView.getVisibility() != 4 )
					_appActivity.admobBannerAdView.setVisibility(View.INVISIBLE);
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
				
				if (!_appActivity.admobInterstitialAdView.isEnabled())
					_appActivity.admobInterstitialAdView.setEnabled(true);
				if (_appActivity.admobInterstitialAdView.getVisibility() == 4 )
					_appActivity.admobInterstitialAdView.setVisibility(View.VISIBLE);	
			}
		});

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
				
				if (!_appActivity.admobBannerAdView.isEnabled())
					_appActivity.admobBannerAdView.setEnabled(true);
				if (_appActivity.admobBannerAdView.getVisibility() == 4 )
					_appActivity.admobBannerAdView.setVisibility(View.VISIBLE);	
			}
		});

	}


	@Override
	protected void onResume() 
	{
		super.onResume();
		if (admobBannerAdView != null ) 
		{
			admobBannerAdView.resume();
		}
		if( admobInterstitialAdView != null )
		{
			admobInterstitialAdView.resume();
		}
	}

	@Override
	protected void onPause() 
	{
		if (admobBannerAdView != null) 
		{
			admobBannerAdView.pause();
		}
		if( admobInterstitialAdView != null )
		{
			admobInterstitialAdView.pause();
		}
		
		super.onPause();
	}

	@Override
	protected void onDestroy() {
		if( null != _appActivity.admobBannerAdView )
		{
			admobBannerAdView.destroy();
		}
		
		if( null != _appActivity.admobInterstitialAdView )
		{
			admobInterstitialAdView.destroy();
		}

		super.onDestroy();
	}

}

