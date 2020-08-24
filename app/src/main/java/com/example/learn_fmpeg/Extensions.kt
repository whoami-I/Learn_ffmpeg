package com.example.learn_fmpeg

import android.content.Context
import android.widget.Toast

fun String.toast(context:Context){
    Toast.makeText(context,this,Toast.LENGTH_SHORT).show()
}

fun Int.toast(context:Context){
    Toast.makeText(context,this,Toast.LENGTH_SHORT).show()
}

