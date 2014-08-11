#/bin/sh
declare -x ANT_ROOT="/Users/phoey/Development/apache-ant-1.9.4/bin"
declare -x ANDROID_SDK_ROOT="/Users/phoey/Development/adt-bundle-mac-x86_64-20140702/sdk"
declare -x NDK_ROOT="/Users/phoey/Development/android-ndk-r9d"
#cocos compile -p android
cocos compile -p android -m debug --ndk-mode NDK_DEBUG=1
#cocos compile -p android -m release --ndk-mode NDK_DEBUG=1