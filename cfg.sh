#!/bin/bash

export CFLAGS=-march=armv6

source ~/coolstream/coolstream.sh

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
--disable-decoders \
--enable-decoder=h264 \
--enable-decoder=mpeg4video \
--enable-decoder=vc1 \
--enable-decoder=mpegvideo \
--enable-decoder=mpegaudio \
--enable-decoder=aac \
--enable-decoder=dca \
--enable-decoder=ac3 \
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
--disable-encoders \
--disable-muxers \
--disable-ffplay \
--disable-ffmpeg \
--disable-ffserver \
--disable-static \
--disable-filters \
--enable-armv6 \
--disable-protocols \
--enable-protocol=file \
--enable-bsfs \
--disable-devices \
--disable-mmx     \
--disable-altivec  \
--disable-zlib   \
--disable-network \
--enable-cross-compile \
--enable-shared \
--cross-prefix=arm-cx2450x-linux-gnueabi- \
--arch=arm \
--enable-bzlib \
--enable-debug \
--enable-stripping \
--target-os=linux \
--prefix=/opt/newcross/arm-cx2450x-linux-gnueabi/arm-cx2450x-linux-gnueabi/sys-root/usr
