package com.example.learn_fmpeg

import android.os.Bundle
import android.view.View
import android.widget.TextView
import androidx.appcompat.app.AppCompatActivity
import com.example.ffmpeg.FFMpeg
import com.permissionx.guolindev.PermissionX
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.GlobalScope
import kotlinx.coroutines.launch
import kotlinx.coroutines.withContext
import java.io.File

class MainActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        PermissionX.init(this).permissions(
                android.Manifest.permission.WRITE_EXTERNAL_STORAGE,
                android.Manifest.permission.READ_EXTERNAL_STORAGE
        )
                .request { allGranted, grantedList, deniedList ->
                    run {
                        if (deniedList.isNotEmpty()) {
                            finish()
                        } else {
                            doSomething()
                        }
                    }
                }
    }

    private fun doSomething() {
        val ffMpeg = FFMpeg()
        val srcFile = File("/sdcard/test.mp4")
        val h264File = File("/sdcard/h264.h264")
        val yuvFile = File("/sdcard/yuvFile.yuv")
        val yuvYFile = File("/sdcard/yuvYFile.yuv")
        if (srcFile.exists()) {
            GlobalScope.launch {
                ffMpeg.convertVideoToH264(srcFile.absolutePath,
                        h264File.absolutePath, yuvFile.absolutePath, yuvYFile.absolutePath)
                withContext(Dispatchers.Main) {
                    "decode success".toast(this@MainActivity)
                }
            }
        } else {
            "${srcFile.absolutePath} not exist".toast(this@MainActivity)
        }
    }
}