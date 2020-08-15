package com.example.learn_fmpeg;

import android.app.Application;

public class AppApplication extends Application {

    static {
        System.loadLibrary("avcodec-58");
        System.loadLibrary("avfilter-7");
        System.loadLibrary("avformat-58");
        System.loadLibrary("avutil-56");
        System.loadLibrary("swresample-3");
        System.loadLibrary("swscale-5");
        System.loadLibrary("avdevice-58");
        System.loadLibrary("zplay-lib");
    }

    @Override
    public void onCreate() {
        super.onCreate();
    }
}
