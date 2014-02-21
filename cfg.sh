#!/bin/bash

export CFLAGS=-march=armv6

./configure \
--disable-parsers \
--enable-parser=aac \
--enable-parser=aac_latm \
--enable-parser=ac3 \
--enable-parser=ac3 \
--enable-parser=dca \
--enable-parser=mpeg4video \
--enable-parser=mpegvideo \
--enable-parser=mpegaudio \
--enable-parser=h264 \
--enable-parser=vc1 \
--enable-parser=dvdsub \
--enable-parser=dvbsub \
--enable-parser=flac \
--enable-parser=vorbis \
--disable-decoders \
--enable-decoder=dca \
--enable-decoder=dvdsub \
--enable-decoder=dvbsub \
--enable-decoder=text \
--enable-decoder=srt \
--enable-decoder=subrip \
--enable-decoder=subviewer \
--enable-decoder=subviewer1 \
--enable-decoder=xsub \
--enable-decoder=pgssub \
--enable-decoder=mp3 \
--enable-decoder=flac \
--enable-decoder=vorbis \
--enable-decoder=aac \
--enable-decoder=mjpeg \
--enable-decoder=pcm_s16le \
--enable-decoder=pcm_s16le_planar \
--disable-demuxers \
--enable-demuxer=aac \
--enable-demuxer=ac3 \
--enable-demuxer=avi \
--enable-demuxer=mov \
--enable-demuxer=vc1 \
--enable-demuxer=mpegts \
--enable-demuxer=mpegtsraw \
--enable-demuxer=mpegps \
--enable-demuxer=mpegvideo \
--enable-demuxer=wav \
--enable-demuxer=pcm_s16be \
--enable-demuxer=mp3 \
--enable-demuxer=pcm_s16le \
--enable-demuxer=matroska \
--enable-demuxer=flv \
--enable-demuxer=rm \
--enable-demuxer=rtsp \
--enable-demuxer=hls \
--enable-demuxer=dts \
--enable-demuxer=wav \
--enable-demuxer=ogg \
--enable-demuxer=flac \
--enable-demuxer=srt \
--disable-encoders \
--disable-muxers \
--disable-ffplay \
--disable-ffmpeg \
--disable-ffserver \
--disable-static \
--disable-filters \
--disable-protocols \
--enable-protocol=file \
--enable-protocol=http \
--enable-protocol=rtmp \
--enable-protocol=rtmpe \
--enable-protocol=rtmps \
--enable-protocol=rtmpte \
--enable-protocol=mmsh \
--enable-protocol=mmst \
--enable-protocol=bluray \
--enable-bsfs \
--disable-devices \
--enable-swresample \
--disable-postproc \
--disable-swscale \
--disable-mmx     \
--disable-altivec  \
--enable-libbluray \
--enable-network \
--enable-cross-compile \
--enable-shared \
--enable-bzlib \
--enable-debug \
--enable-stripping \
--target-os=linux \
--arch=arm \
--disable-neon \
--cpu=armv6 \
--cross-prefix=arm-cx2450x-linux-gnueabi- \
--prefix=/opt/arm/arm-cx2450x-linux-gnueabi/arm-cx2450x-linux-gnueabi/sys-root/usr $*

#--enable-decoder=h264 \
#--enable-decoder=mpeg4video \
#--enable-decoder=vc1 \
#--enable-decoder=mpegvideo \
#--enable-decoder=mpegaudio \
#--enable-decoder=aac \
#--enable-decoder=ac3 \
#--extra-cflags="-ggdb3"
