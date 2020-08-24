//
// Created by user on 20-8-14.
//

#include <jni.h>
#include <string>
#include <android/log.h>
//
#define LOG_TAG "zasko"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)

//#define LOGE(...)  __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)


#ifdef __cplusplus
extern "C" {
#endif
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include <SLES/OpenSLES.h>
#include "zplay-lib.h"
#include "stdio.h"
#include "libswscale/swscale.h"

JNIEXPORT jstring
JNICALL
Java_com_zasko_ffmpeg_RenderManager_getConfig(JNIEnv *env, jclass type) {

    char info[10000] = {0};
    sprintf(info, "%s\n", avcodec_configuration());

    int a[4] = {1, 2, 3, 4};
    int *ptr1 = (int *) (&a + 1);

    LOGD("From JNi Test %d", a[0]);
    return env->NewStringUTF(info);
}

JNIEXPORT jstring JNICALL
Java_com_example_learn_1fmpeg_MainActivity_getConfig(JNIEnv *env, jobject thiz) {
    char info[10000] = {0};
    sprintf(info, "%s\n", avcodec_configuration());

    int a[4] = {1, 2, 3, 4};
    int *ptr1 = (int *) (&a + 1);

    //LOGI("From JNi Test %d", a[0]);
    return env->NewStringUTF(info);
}

JNIEXPORT void
JNICALL
Java_com_zasko_ffmpeg_RenderManager_playFile(JNIEnv *env, jclass type, jstring filePath) {
    avformat_network_init();

    char input_str[500] = {0};
    sprintf(input_str, "%s", env->GetStringUTFChars(filePath, NULL));
    AVFormatContext *avFormatContext = avformat_alloc_context();
    //打开文件
    if (avformat_open_input(&avFormatContext, input_str, NULL, NULL) != 0) {

    }
    //查找文件的流信息
    if (avformat_find_stream_info(avFormatContext, NULL) < 0) {

    }
    int videoIndex = -1;
    int audioIndex = -1;
    for (int i = 0; i < avFormatContext->nb_streams; i++) {
        if (avFormatContext->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_AUDIO) {
            videoIndex = i;
        } else if (avFormatContext->streams[i]) {}

    }
    if (videoIndex == -1) {

    }

    //打开音频解码流
    AVCodec *audioCodec;

    AVCodecContext *audioCCtx;
    audioCodec = avcodec_find_decoder(audioCCtx->codec_id);

//    AVCodecParameters *avCodecParameters = avFormatContext->streams[audioIndex]->codecpar;
//    audioCodec = avcodec_find_decoder(avCodecParameters->codec_id);

    if (!audioCodec) {


    }

    if (avcodec_open2(audioCCtx, audioCodec, NULL) < 0) {

    }
    int width = audioCCtx->width;
    int height = audioCCtx->height;


}

JNIEXPORT void
JNICALL Java_com_zasko_ffmpeg_RenderManager_pcm2Wav(JNIEnv *env, jclass type) {
}

JNIEXPORT jint JNICALL
Java_com_example_ffmpeg_FFMpeg_convertVideoToH264(JNIEnv *env, jobject thiz, jstring src_file_path,
                                                  jstring h264_file_path, jstring yuv_file_path,
                                                  jstring yuv_y_file_path) {

    AVFormatContext *pFormatCtx = NULL;        //声明了AVFormatContext视频数据指针

    int videoIndex = -1;//视频的位置索引

    AVCodecContext *pCodecCtx = NULL;          //解码器信息指针

    AVCodec *pCodec = NULL;                    //解码器指针

    AVFrame *pFrame = NULL;                    //像素数据指针 解码出来的

    AVFrame *pFrameYUV = NULL;                  //经过转码之后的

    uint8_t *out_buffer = NULL;                //缓冲数组

    AVPacket *packet = NULL;                    //h.264包数据指针

    AVCodecParameters *pCodecParam = NULL;      //码流的属性结构体

    int ret = -1;                              //返回值

    struct SwsContext *img_convert_ctx = NULL;  //图像转换格式上下文信息

    int frame_cnt = 0;                        //总的帧数

    char *filepath = (char *) env->GetStringUTFChars(src_file_path, 0);         //输入文件路径

    //分配空间

    pFormatCtx = avformat_alloc_context();

    //打开文件

    if (avformat_open_input(&pFormatCtx, filepath, NULL, NULL) != 0) {
        LOGD("Couldn't open input file");
        return -1;
    }

    //获取视频流信息
    if (avformat_find_stream_info(pFormatCtx, NULL) < 0) {
        LOGD("Couldn't find stream information.\n");
        return -1;

    }

    //打开了视频并且获取了视频流 ，设置视频索引值默认值
    for (int i = 0; pFormatCtx->nb_streams; i++) {

        if (pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO) {
            videoIndex = i;
            break;
        }
    }

    //如果没有找到视频的索引，说明并不是一个视频文件

    if (videoIndex == -1) {
        LOGD("Couldn't find a video stream.\n");
        return -1;
    }

    //取得视频的解码器信息
    pCodecParam = pFormatCtx->streams[videoIndex]->codecpar;

    //分配空间
    pCodecCtx = avcodec_alloc_context3(NULL);

    //获取编解码器上下文信息
    if (avcodec_parameters_to_context(pCodecCtx, pCodecParam) < 0) {
        return -1;
    }

    //得到的解码器
    pCodec = avcodec_find_decoder(pCodecCtx->codec_id);

    //解码器未找到
    if (pCodec == NULL) {
        LOGD("Couldn't find codec.\n");
        return -1;
    }

    //打开解码器
    if (avcodec_open2(pCodecCtx, pCodec, NULL) < 0) {
        LOGD("Couldn't open codec.\n");
        return -1;
    }

    //初始化yuv容器，并且初始化内存空间
    pFrame = av_frame_alloc();
    pFrameYUV = av_frame_alloc();
    out_buffer = (uint8_t *) av_malloc(
            avpicture_get_size(AV_PIX_FMT_YUV420P, pCodecCtx->width, pCodecCtx->height));

    //设置图像内容
    avpicture_fill((AVPicture *) pFrameYUV, out_buffer, AV_PIX_FMT_YUV420P, pCodecCtx->width,
                   pCodecCtx->height);

    //初始化h.264容器
    packet = (AVPacket *) av_malloc(sizeof(AVPacket));
    av_dump_format(pFormatCtx, 0, filepath, 0);

    //上文说的对图形进行宽度上方的裁剪，以便于显示的更好
    img_convert_ctx = sws_getContext(pCodecCtx->width, pCodecCtx->height, pCodecCtx->pix_fmt,

                                     pCodecCtx->width, pCodecCtx->height, AV_PIX_FMT_YUV420P,
                                     SWS_BICUBIC, NULL, NULL, NULL);
    FILE *fp_h264 = NULL;
    fp_h264 = fopen((char *) env->GetStringUTFChars(h264_file_path, 0), "wb+");
    FILE *fp_yuv = NULL;
    fp_yuv = fopen((char *) env->GetStringUTFChars(yuv_file_path, 0), "wb+");
    FILE *fp_yuv_y = NULL;
    fp_yuv_y = fopen((char *) env->GetStringUTFChars(yuv_y_file_path, 0), "wb+");

    //如果读流成功
    while (av_read_frame(pFormatCtx, packet) >= 0) {
        if (packet->stream_index == videoIndex) {
            //在此处添加输出H264码流的代码 取自于packet，使用fwrite()
            fwrite(packet->data, static_cast<size_t>(packet->size), 1, fp_h264);
            ret = avcodec_send_packet(pCodecCtx, packet);
            if (ret < 0 && ret != AVERROR(EAGAIN) && ret != AVERROR_EOF) {
                av_packet_unref(packet);
                return -1;
            }
            ret = avcodec_receive_frame(pCodecCtx, pFrame);
            if (ret < 0 && ret != AVERROR(EAGAIN) && ret != AVERROR_EOF) {
                av_packet_unref(packet);
                return -1;
            } else {
                //上文说的对图形进行宽度上方的裁剪，以便于显示的更好
                sws_scale(img_convert_ctx, (const uint8_t *const *) pFrame->data, pFrame->linesize,
                          0, pCodecCtx->height,
                          pFrameYUV->data, pFrameYUV->linesize);
//                LOGD("Decoded frame index: %d\n", frame_cnt);
//                //在此处添加输出YUV的代码  取自于pFrameYUV，使用fwrite()
//                LOGD("CodecCtx->width=%d------pCodecCtx->height%d\n", pCodecCtx->width,
//                     pCodecCtx->height);
                fwrite(pFrameYUV->data[0],
                       static_cast<size_t>((pCodecCtx->width) * (pCodecCtx->height)), 1, fp_yuv_y);
                fwrite(pFrameYUV->data[0],
                       static_cast<size_t>((pCodecCtx->width) * (pCodecCtx->height)), 1, fp_yuv);
                fwrite(pFrameYUV->data[1],
                       static_cast<size_t>((pCodecCtx->width) * (pCodecCtx->height) / 4), 1, fp_yuv);
                fwrite(pFrameYUV->data[2],
                       static_cast<size_t>((pCodecCtx->width) * (pCodecCtx->height) / 4), 1, fp_yuv);
                //计数
                frame_cnt++;
            }
        }
        //释放packet
        av_packet_unref(packet);
    }
    fclose(fp_h264);
    fclose(fp_yuv);
    fclose(fp_yuv_y);

    //释放相关资源
    sws_freeContext(img_convert_ctx);
    av_frame_free(&pFrameYUV);
    av_frame_free(&pFrame);
    avcodec_close(pCodecCtx);
    avformat_close_input(&pFormatCtx);
    return 0;
}
};
}
