/*
 * libdlna: reference DLNA standards implementation.
 * Copyright (C) 2007 Benjamin Zores <ben@geexbox.org>
 *
 * This file is part of libdlna.
 *
 * libdlna is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * libdlna is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with libdlna; if not, write to the Free Software
 * Foundation, Inc, 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#include <stdlib.h>
#include <string.h>

#include "dlna_internals.h"
#include "profiles.h"

#ifdef USE_ORIGINAL_DLAN_PROFILE
/* Profile for audio media class content */
static dlna_profile_t atrac3 = {
  .id = "ATRAC3plus",
  .mime = MIME_AUDIO_ATRAC,
  .label = LABEL_AUDIO_2CH_MULTI
};

audio_profile_t
audio_profile_guess_atrac (AVCodecContext *ac)
{
  if (!ac)
    return AUDIO_PROFILE_INVALID;

#if LIBAVCODEC_VERSION_INT >= ((51<<16)+(40<<8)+4)
  if (ac->codec_id == CODEC_ID_ATRAC3)
    return AUDIO_PROFILE_ATRAC;
#endif

  return AUDIO_PROFILE_INVALID;
}

static dlna_profile_t *
probe_atrac3 (AVFormatContext *ctx dlna_unused,
              dlna_container_type_t st dlna_unused,
              av_codecs_t *codecs)
{
  if (!stream_ctx_is_audio (codecs))
    return NULL;
  
  if (audio_profile_guess_atrac (codecs->ac) == AUDIO_PROFILE_ATRAC)
    return &atrac3;

  return NULL;
}

/* get dlna profile by extension. by HouXB, 08Oct10 */
static dlna_profile_t *
probe2_atrac3 ()
{
	return &atrac3;
}

#else

/* Profile for audio media class content 
static dlna_profile_t atrac3_tp = {
  .id = "ATRAC3plus",
  .mime = MIME_AUDIO_ATRAC,
  .label = LABEL_AUDIO_2CH_MULTI
};
*/

/* Profile for audio media class content */
static dlna_profile_t atrac3_tp = {
  .id = DLNA_ID_ATRAC3PLUS,
  .mime = DLNA_MIME_AUDIO_ATRAC
};


static dlna_profile_t *
probe_atrac3 ()
{
	return NULL;
}

/* get dlna profile by extension. by HouXB, 08Oct10 */
static dlna_profile_t *
probe2_atrac3 ()
{
	return &atrac3_tp;
}

#endif

dlna_registered_profile_t dlna_profile_audio_atrac3 = {
  .id = DLNA_PROFILE_AUDIO_ATRAC3,
  .class = DLNA_CLASS_AUDIO,
  .extensions = "at3p,acm",
  .probe = probe_atrac3,
  .probe2 = probe2_atrac3,
  .next = NULL
};
