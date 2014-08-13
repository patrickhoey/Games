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

import com.google.android.gms.ads.AdSize;
import com.google.android.gms.ads.AdRequest;
import com.google.android.gms.ads.AdView;

import android.graphics.Color;
import android.os.Bundle;
import android.view.View;
import android.widget.RelativeLayout;

public class AppActivity extends Cocos2dxActivity {

	private static AppActivity _appActivity;
	private AdView adView;
	private static final String AD_UNIT_ID_INTERSTITIAL = "ca-app-pub-8379829573491079/1697101740";
	private static final String AD_UNIT_ID_BANNER = "ca-app-pub-8379829573491079/9220368549";

	@Override
	protected void onCreate(Bundle savedInstanceState){
		super.onCreate(savedInstanceState);
		
		adView = new AdView(this);

        RelativeLayout.LayoutParams params = new RelativeLayout.LayoutParams(
        RelativeLayout.LayoutParams.MATCH_PARENT, RelativeLayout.LayoutParams.WRAP_CONTENT);

		AdRequest adRequest = new AdRequest.Builder()
		.addTestDevice(AdRequest.DEVICE_ID_EMULATOR)
		.addTestDevice("HASH_DEVICE_ID")
		.build();

		adView.setAdSize(AdSize.BANNER);
		adView.setAdUnitId(AD_UNIT_ID_BANNER);
		adView.setBackgroundColor(Color.BLACK);
		adView.setBackgroundColor(0);
		adView.loadAd(adRequest);
		addContentView(adView,params);

		_appActivity = this;

	}


	public static void hideAd()
	{
		_appActivity.runOnUiThread(new Runnable()
		{

			@Override
			public void run()
			{
				if (_appActivity.adView.isEnabled())
					_appActivity.adView.setEnabled(false);
				if (_appActivity.adView.getVisibility() != 4 )
					_appActivity.adView.setVisibility(View.INVISIBLE);
			}
		});

	}


	public static void showAd()
	{
		_appActivity.runOnUiThread(new Runnable()
		{

			@Override
			public void run()
			{	
				if (!_appActivity.adView.isEnabled())
					_appActivity.adView.setEnabled(true);
				if (_appActivity.adView.getVisibility() == 4 )
					_appActivity.adView.setVisibility(View.VISIBLE);	
			}
		});

	}

	@Override
	protected void onResume() {
		super.onResume();
		if (adView != null) {
			adView.resume();
		}
	}

	@Override
	protected void onPause() {
		if (adView != null) {
			adView.pause();
		}
		super.onPause();
	}

	@Override
	protected void onDestroy() {
		adView.destroy();
		super.onDestroy();
	}

}

