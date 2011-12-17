# File with all CMake user preferences

IF(WIN32)
	# Android
	# Generator: MinGW makefiles
	# Toolchain: android.toolchain.cmake
	SET (ANDROID_NDK 				C:/Android/android-ndk-r6b)
	SET (ENV{ANDROID_API_LEVEL}		android-9)
	SET (ARM_TARGET 				armeabi) # armeabi; armeabi-v7a; armeabi-v7a with NEON; armeabi-v7a with VFPV3

	# Generator: MinGW makefiles
	# Toolchain: mingw.toolchain.cmake
	SET(MINGW_ROOT_PATH 			C:/MinGW)

ELSE()
	MESSAGE(WARNING "Only Win32 system has been tested yet.")
ENDIF(WIN32)