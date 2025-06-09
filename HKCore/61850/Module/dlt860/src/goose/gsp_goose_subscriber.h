/*
 *  gsp_goose_subscriber.h
 */

#ifndef GSP_GOOSE_SUBSCRIBER_H_
#define GSP_GOOSE_SUBSCRIBER_H_

#include "libdlt860_common_api.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "gsp_mms_value.h"

typedef struct sGspGooseSubscriber* GspGooseSubscriber;

typedef void (*GspGooseListener)(GspGooseSubscriber subscriber, void* parameter);

LIB860_API GspGooseSubscriber GspGooseSubscriber_create(char* goCbRef, GspMmsValue* dataSetValues);

LIB860_API void GspGooseSubscriber_setDstMac(GspGooseSubscriber self, uint8_t dstMac[6]);

LIB860_API void GspGooseSubscriber_setAppId(GspGooseSubscriber self, uint16_t appId);

LIB860_API bool GspGooseSubscriber_isValid(GspGooseSubscriber self);

LIB860_API void GspGooseSubscriber_destroy(GspGooseSubscriber self);

LIB860_API void GspGooseSubscriber_setListener(GspGooseSubscriber self, GspGooseListener listener, void* parameter);

LIB860_API uint32_t GspGooseSubscriber_getStNum(GspGooseSubscriber self);

LIB860_API uint32_t GspGooseSubscriber_getSqNum(GspGooseSubscriber self);

LIB860_API bool GspGooseSubscriber_isTest(GspGooseSubscriber self);

LIB860_API uint32_t GspGooseSubscriber_getConfRev(GspGooseSubscriber self);

LIB860_API bool GspGooseSubscriber_needsCommission(GspGooseSubscriber self);

LIB860_API uint32_t GspGooseSubscriber_getTimeAllowedToLive(GspGooseSubscriber self);

LIB860_API uint64_t GspGooseSubscriber_getTimestamp(GspGooseSubscriber self);

LIB860_API GspMmsValue* GspGooseSubscriber_getDataSetValues(GspGooseSubscriber self);

#ifdef __cplusplus
}
#endif

#endif /* GSP_GOOSE_SUBSCRIBER_H_ */
