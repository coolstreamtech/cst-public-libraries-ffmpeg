/*
 * Copyright (c) 2007 Benoit Fouet
 * Copyright (c) 2010 Stefano Sabatini
 *
 * This file is part of FFmpeg.
 *
 * FFmpeg is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * FFmpeg is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with FFmpeg; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

/**
 * @file
 * horizontal flip filter
 */

#include <string.h>

#include "avfilter.h"
#include "formats.h"
#include "internal.h"
#include "video.h"
#include "libavutil/pixdesc.h"
#include "libavutil/internal.h"
#include "libavutil/intreadwrite.h"
#include "libavutil/imgutils.h"

typedef struct {
    int max_step[4];    ///< max pixel step for each plane, expressed as a number of bytes
    int hsub, vsub;     ///< chroma subsampling
} FlipContext;

static int query_formats(AVFilterContext *ctx)
{
    AVFilterFormats *pix_fmts = NULL;
    int fmt;

    for (fmt = 0; fmt < AV_PIX_FMT_NB; fmt++) {
        const AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(fmt);
        if (!(desc->flags & PIX_FMT_HWACCEL ||
              desc->flags & PIX_FMT_BITSTREAM ||
              (desc->log2_chroma_w != desc->log2_chroma_h &&
               desc->comp[0].plane == desc->comp[1].plane)))
            ff_add_format(&pix_fmts, fmt);
    }

    ff_set_common_formats(ctx, pix_fmts);
    return 0;
}

static int config_props(AVFilterLink *inlink)
{
    FlipContext *flip = inlink->dst->priv;
    const AVPixFmtDescriptor *pix_desc = av_pix_fmt_desc_get(inlink->format);

    av_image_fill_max_pixsteps(flip->max_step, NULL, pix_desc);
    flip->hsub = pix_desc->log2_chroma_w;
    flip->vsub = pix_desc->log2_chroma_h;

    return 0;
}

static int filter_frame(AVFilterLink *inlink, AVFilterBufferRef *in)
{
    AVFilterContext *ctx  = inlink->dst;
    FlipContext *flip     = ctx->priv;
    AVFilterLink *outlink = ctx->outputs[0];
    AVFilterBufferRef *out;
    uint8_t *inrow, *outrow;
    int i, j, plane, step, hsub, vsub;

    out = ff_get_video_buffer(outlink, AV_PERM_WRITE, outlink->w, outlink->h);
    if (!out) {
        avfilter_unref_bufferp(&in);
        return AVERROR(ENOMEM);
    }
    avfilter_copy_buffer_ref_props(out, in);

    /* copy palette if required */
    if (av_pix_fmt_desc_get(inlink->format)->flags & PIX_FMT_PAL)
        memcpy(out->data[1], in->data[1], AVPALETTE_SIZE);

    for (plane = 0; plane < 4 && in->data[plane] && in->linesize[plane]; plane++) {
        step = flip->max_step[plane];
        hsub = (plane == 1 || plane == 2) ? flip->hsub : 0;
        vsub = (plane == 1 || plane == 2) ? flip->vsub : 0;

        outrow = out->data[plane];
        inrow  = in ->data[plane] + ((inlink->w >> hsub) - 1) * step;
        for (i = 0; i < in->video->h >> vsub; i++) {
            switch (step) {
            case 1:
                for (j = 0; j < (inlink->w >> hsub); j++)
                    outrow[j] = inrow[-j];
            break;

            case 2:
            {
                uint16_t *outrow16 = (uint16_t *)outrow;
                uint16_t * inrow16 = (uint16_t *) inrow;
                for (j = 0; j < (inlink->w >> hsub); j++)
                    outrow16[j] = inrow16[-j];
            }
            break;

            case 3:
            {
                uint8_t *in  =  inrow;
                uint8_t *out = outrow;
                for (j = 0; j < (inlink->w >> hsub); j++, out += 3, in -= 3) {
                    int32_t v = AV_RB24(in);
                    AV_WB24(out, v);
                }
            }
            break;

            case 4:
            {
                uint32_t *outrow32 = (uint32_t *)outrow;
                uint32_t * inrow32 = (uint32_t *) inrow;
                for (j = 0; j < (inlink->w >> hsub); j++)
                    outrow32[j] = inrow32[-j];
            }
            break;

            default:
                for (j = 0; j < (inlink->w >> hsub); j++)
                    memcpy(outrow + j*step, inrow - j*step, step);
            }

            inrow  += in ->linesize[plane];
            outrow += out->linesize[plane];
        }
    }

    avfilter_unref_bufferp(&in);
    return ff_filter_frame(outlink, out);
}

static const AVFilterPad avfilter_vf_hflip_inputs[] = {
    {
        .name         = "default",
        .type         = AVMEDIA_TYPE_VIDEO,
        .filter_frame = filter_frame,
        .config_props = config_props,
        .min_perms    = AV_PERM_READ,
    },
    { NULL }
};

static const AVFilterPad avfilter_vf_hflip_outputs[] = {
    {
        .name = "default",
        .type = AVMEDIA_TYPE_VIDEO,
    },
    { NULL }
};

AVFilter avfilter_vf_hflip = {
    .name      = "hflip",
    .description = NULL_IF_CONFIG_SMALL("Horizontally flip the input video."),
    .priv_size = sizeof(FlipContext),
    .query_formats = query_formats,

    .inputs    = avfilter_vf_hflip_inputs,
    .outputs   = avfilter_vf_hflip_outputs,
};
