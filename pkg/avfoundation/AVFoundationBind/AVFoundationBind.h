//
//  AVFoundationBind.h
//  AVFoundationBind
//
//  Created by Herman, Lukas on 5/23/20.
//  Copyright © 2020 Herman, Lukas. All rights reserved.
//

#pragma once

#include <stddef.h>

#define MAX_DEVICES                      8
#define MAX_PROPERTIES                   64
#define MAX_DEVICE_UID_CHARS             64

typedef const char* STATUS;
static STATUS STATUS_OK                       = (STATUS) NULL;
static STATUS STATUS_NULL_ARG                 = (STATUS) "One of the arguments was null";
static STATUS STATUS_DEVICE_INIT_FAILED       = (STATUS) "Failed to init device";
static STATUS STATUS_UNSUPPORTED_FRAME_FORMAT = (STATUS) "Unsupported frame format";
static STATUS STATUS_UNSUPPORTED_MEDIA_TYPE   = (STATUS) "Unsupported media type";
static STATUS STATUS_FAILED_TO_ACQUIRE_LOCK   = (STATUS) "Failed to acquire a lock";
static STATUS STATUS_UNSUPPORTED_FORMAT       = (STATUS) "Unsupported device format";

typedef enum AVBindMediaType {
    AVBindMediaTypeVideo,
    AVBindMediaTypeAudio,
} AVBindMediaType;

typedef enum AVBindFrameFormat {
    AVBindFrameFormatI420,
    AVBindFrameFormatNV21,
    AVBindFrameFormatYUY2,
    AVBindFrameFormatUYVY,
} AVBindFrameFormat;

typedef void (*AVBindDataCallback)(void *userData, void *buf, int len);

typedef struct AVBindMediaProperty {
    // video property
    int width, height;
    AVBindFrameFormat frameFormat;
    
    // audio property
    
} AVBindMediaProperty, *PAVBindMediaProperty;

typedef struct AVBindSession AVBindSession, *PAVBindSession;

typedef struct {
    char uid[MAX_DEVICE_UID_CHARS + 1];
} AVBindDevice, *PAVBindDevice;

// AVBindDevices returns a list of AVBindDevices. The result array is pointing to a static
// memory. The caller is expected to not hold on to the address for a long time and make a copy.
// Everytime this function gets called, the array will be overwritten and the memory will be reused.
STATUS AVBindDevices(AVBindMediaType, PAVBindDevice*, int*);

STATUS AVBindSessionInit(AVBindDevice, PAVBindSession*);
STATUS AVBindSessionFree(PAVBindSession*);
STATUS AVBindSessionOpen(PAVBindSession, AVBindMediaProperty, AVBindDataCallback, void*);
STATUS AVBindSessionClose(PAVBindSession);
STATUS AVBindSessionProperties(PAVBindSession, PAVBindMediaProperty*, int*);
