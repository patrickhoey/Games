#/bin/sh
declare -x ANT_ROOT="${HOME}/Development/apache-ant-1.9.4/bin"
declare -x ANDROID_SDK_ROOT="${HOME}/Development/adt-bundle-mac-x86_64-20140702/sdk"
declare -x NDK_ROOT="${HOME}/Development/android-ndk-r9d"
cocos compile -p android -m debug --ndk-mode NDK_DEBUG=1
#cocos compile -p android -m release --ndk-mode NDK_DEBUG=0
#cocos compile -p android -m release --ndk-mode NDK_DEBUG=0 --ap 19