/*
 *  Copyright (c) 2011 The WebRTC project authors. All Rights Reserved.
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree. An additional intellectual property rights grant can be found
 *  in the file PATENTS.  All contributing project authors may
 *  be found in the AUTHORS file in the root of the source tree.
 */

// This sub-API supports the following functionalities:
//
//  - RTP header modification (time stamp and sequence number fields).
//  - Playout delay tuning to synchronize the voice with video.
//  - Playout delay monitoring.
//
// Usage example, omitting error checking:
//
//  using namespace webrtc;
//  VoiceEngine* voe = VoiceEngine::Create();
//  VoEBase* base = VoEBase::GetInterface(voe);
//  VoEVideoSync* vsync  = VoEVideoSync::GetInterface(voe);
//  base->Init();
//  ...
//  int buffer_ms(0);
//  vsync->GetPlayoutBufferSize(buffer_ms);
//  ...
//  base->Terminate();
//  base->Release();
//  vsync->Release();
//  VoiceEngine::Delete(voe);
//
#ifndef WEBRTC_VOICE_ENGINE_VOE_VIDEO_SYNC_H
#define WEBRTC_VOICE_ENGINE_VOE_VIDEO_SYNC_H

#include "common_types.h"

namespace webrtc {

class RtpRtcp;
class VoiceEngine;

class WEBRTC_DLLEXPORT VoEVideoSync
{
public:
    // Factory for the VoEVideoSync sub-API. Increases an internal
    // reference counter if successful. Returns NULL if the API is not
    // supported or if construction fails.
    static VoEVideoSync* GetInterface(VoiceEngine* voiceEngine);

    // Releases the VoEVideoSync sub-API and decreases an internal
    // reference counter. Returns the new reference count. This value should
    // be zero for all sub-API:s before the VoiceEngine object can be safely
    // deleted.
    virtual int Release() = 0;

    // Gets the current sound card buffer size (playout delay).
    virtual int GetPlayoutBufferSize(int& bufferMs) = 0;

    // Sets an additional delay for the playout jitter buffer.
    virtual int SetMinimumPlayoutDelay(int channel, int delayMs) = 0;

    // Gets the sum of the algorithmic delay, jitter buffer delay, and the
    // playout buffer delay for a specified |channel|.
    virtual int GetDelayEstimate(int channel, int& delayMs) = 0;

    // Manual initialization of the RTP timestamp.
    virtual int SetInitTimestamp(int channel, unsigned int timestamp) = 0;

    // Manual initialization of the RTP sequence number.
    virtual int SetInitSequenceNumber(int channel, short sequenceNumber) = 0;

    // Get the received RTP timestamp
    virtual int GetPlayoutTimestamp(int channel, unsigned int& timestamp) = 0;

    virtual int GetRtpRtcp (int channel, RtpRtcp* &rtpRtcpModule) = 0;

protected:
    VoEVideoSync() { }
    virtual ~VoEVideoSync() { }
};

}   // namespace webrtc

#endif  // #ifndef WEBRTC_VOICE_ENGINE_VOE_VIDEO_SYNC_H
