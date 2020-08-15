export NDK=/local/tools/android-ndk-r14b
export PREBULT=$NDK/toolchains/aarch64-linux-android-4.9/prebuilt
export PLATFORM=$NDK/platforms/android-21/arch-arm64
export PREFIX=androidlib
./configure  --enable-cross-compile  \
--cross-prefix=$PREBULT/linux-x86_64/bin/aarch64-linux-android-  \
--sysroot=$PLATFORM \
--target-os=linux \
--arch=aarch64 \
--enable-asm   --disable-x86asm --enable-neon \
 --disable-ffplay  \
 --disable-ffprobe \
 --enable-shared\
  --disable-debug \
 --disable-doc  \
 --enable-protocol=file \
 --enable-decoder=h264   --enable-decoder=h263    --enable-decoder=mpeg2video --enable-decoder=mpeg4     --enable-decoder=vp8  --enable-decoder=vp9   --enable-decoder=vc1  --enable-decoder=wmv3    --enable-decoder=hevc   --enable-decoder=hevc_mediacodec \
  --enable-muxers --enable-demuxers   \
 --enable-parser=h264  --enable-parser=mpeg4video  --enable-parser=ac3 \
  --extra-cflags="-O3  -fasm "
#\=avi  --enable-demuxer=mpegps  --enable-demuxer=mov  --enable-demuxer=h264   --enable-demuxer=flv    --enable-demuxer=m4v \
