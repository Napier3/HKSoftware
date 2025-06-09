/*
 *  goose_subscriber.c
 *
 */

#include "libdlt860_platform_includes.h"
#include "stack_config.h"
#include "gsp_goose_subscriber.h"
#include "gsp_hal_ethernet.h"
#include "gsp_hal_thread.h"
#include "ber_decode.h"
#include "gsp_mms_value.h"
#include "mms_value_internal.h"
#include "goose_receiver_internal.h"

GooseSubscriber
GooseSubscriber_create(char* goCbRef, MmsValue* dataSetValues)
{
    GooseSubscriber self = (GooseSubscriber) GLOBAL_CALLOC(1, sizeof(struct sGooseSubscriber));

    self->goCBRef = StringUtils_copyString(goCbRef);
    self->goCBRefLen = strlen(goCbRef);
    self->timestamp = MmsValue_newUtcTime(0);
    self->dataSetValues = dataSetValues;

    if (dataSetValues != NULL)
        self->dataSetValuesSelfAllocated = false;

    memset(self->dstMac, 0xFF, 6);
    self->dstMacSet = false;
    self->appId = -1;

    return self;
}

bool
GooseSubscriber_isValid(GooseSubscriber self)
{
    if (self->stateValid == false)
        return false;

    if (Hal_getTimeInMs() > self->invalidityTime)
        return false;

    return true;
}

void
GooseSubscriber_setDstMac(GooseSubscriber self, uint8_t dstMac[6])
{
  memcpy(self->dstMac, dstMac,6);
  self->dstMacSet = true;
}

void
GooseSubscriber_setAppId(GooseSubscriber self, uint16_t appId)
{
    self->appId = (int32_t) appId;
}

void
GooseSubscriber_destroy(GooseSubscriber self)
{
    GLOBAL_FREEMEM(self->goCBRef);

    MmsValue_delete(self->timestamp);

    if (self->dataSetValuesSelfAllocated)
        MmsValue_delete(self->dataSetValues);

    GLOBAL_FREEMEM(self);
}

void
GooseSubscriber_setListener(GooseSubscriber self, GooseListener listener, void* parameter)
{
    self->listener = listener;
    self->listenerParameter = parameter;
}

uint32_t
GooseSubscriber_getStNum(GooseSubscriber self)
{
    return self->stNum;
}

uint32_t
GooseSubscriber_getSqNum(GooseSubscriber self)
{
    return self->sqNum;
}

bool
GooseSubscriber_isTest(GooseSubscriber self)
{
    return self->simulation;
}

uint32_t
GooseSubscriber_getConfRev(GooseSubscriber self)
{
    return self->confRev;
}

bool
GooseSubscriber_needsCommission(GooseSubscriber self)
{
    return self->ndsCom;
}

uint32_t
GooseSubscriber_getTimeAllowedToLive(GooseSubscriber self)
{
    return self->timeAllowedToLive;
}

uint64_t
GooseSubscriber_getTimestamp(GooseSubscriber self)
{
    return MmsValue_getUtcTimeInMs(self->timestamp);
}

MmsValue*
GooseSubscriber_getDataSetValues(GooseSubscriber self)
{
    return self->dataSetValues;
}








