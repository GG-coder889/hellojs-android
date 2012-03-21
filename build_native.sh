# set params
NDK_ROOT_LOCAL=/path/to/android/ndk
COCOS2DX_ROOT_LOCAL=/path/to/cocos2d-x
MOZILLA_ROOT_LOCAL=/path/to/spidermonkey
GAME_ROOT_LOCAL=/path/to/the/game/directory

buildexternalsfromsource=

usage(){
cat << EOF
usage: $0 [options]

Build C/C++ native code using Android NDK

OPTIONS:
   -s	Build externals from source
   -h	this help
EOF
}

while getopts "s" OPTION; do
	case "$OPTION" in
		s)
			buildexternalsfromsource=1
			;;
		h)
			usage
			exit 0
			;;
	esac
done

# try to get global variable
if [ $NDK_ROOT"aaa" != "aaa" ]; then
    NDK_ROOT_LOCAL=$NDK_ROOT
    echo "use global definition of NDK_ROOT: $NDK_ROOT"
fi

if [ $COCOS2DX_ROOT"aaa" != "aaa" ]; then
    COCOS2DX_ROOT_LOCAL=$COCOS2DX_ROOT
    echo "use global definition of COCOS2DX_ROOT: $COCOS2DX_ROOT"
fi

if [ $MOZILLA_ROOT"aaa" != "aaa" ]; then
    MOZILLA_ROOT_LOCAL=$MOZILLA_ROOT
    echo "use global definition of MOZILLA_ROOT: $MOZILLA_ROOT"
fi

if [ $GAME_ROOT"aaa" != "aaa" ]; then
    GAME_ROOT_LOCAL=$GAME_ROOT
    echo "use global definition of GAME_ROOT: $GAME_ROOT_LOCAL"
else
# if GAME_ROOT is not set
# use current directory
    GAME_ROOT_LOCAL=$PWD
    echo "using current directory for GAME_ROOT: $GAME_ROOT_LOCAL"
fi

# Currently we only have the android game
GAME_ANDROID_ROOT=$GAME_ROOT_LOCAL

# GAME_ROOT=_Set this to something_
# GAME_ANDROID_ROOT=$GAME_ROOT/android
# GAME_RESOURCE_ROOT=$GAME_ROOT/Resources

# # make sure assets is exist
# if [ -d $GAME_ANDROID_ROOT/assets ]; then
#     rm -rf $GAME_ANDROID_ROOT/assets
# fi

# mkdir $GAME_ANDROID_ROOT/assets

# # copy resources
# for file in $GAME_RESOURCE_ROOT/*
# do
#     if [ -d $file ]; then
#         cp -rf $file $GAME_ANDROID_ROOT/assets
#     fi

#     if [ -f $file ]; then
#         cp $file $GAME_ANDROID_ROOT/assets
#     fi
# done

# build
if [[ $buildexternalsfromsource ]]; then
    echo "Building external dependencies from source"
    $NDK_ROOT_LOCAL/ndk-build -C $GAME_ANDROID_ROOT \
        NDK_MODULE_PATH=${GAME_ANDROID_ROOT}/jni:${COCOS2DX_ROOT_LOCAL}:${COCOS2DX_ROOT_LOCAL}/cocos2dx/platform/third_party/android/source:${MOZILLA_ROOT_LOCAL}
else
    echo "Using prebuilt externals"
    $NDK_ROOT_LOCAL/ndk-build -C $GAME_ANDROID_ROOT \
        NDK_MODULE_PATH=${GAME_ANDROID_ROOT}/jni:${COCOS2DX_ROOT_LOCAL}:${COCOS2DX_ROOT_LOCAL}/cocos2dx/platform/third_party/android/prebuilt:${MOZILLA_ROOT_LOCAL} \
        V=1 \
        NDK_LOG=1
fi
