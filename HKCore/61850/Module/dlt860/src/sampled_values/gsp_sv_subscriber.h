/*
 *  gsp_sv_subscriber.h
 */

#ifndef GSP_SAMPLED_VALUES_SV_SUBSCRIBER_H_
#define GSP_SAMPLED_VALUES_SV_SUBSCRIBER_H_

#include "libdlt860_common_api.h"
#include "iec61850_common.h"
#include "gsp_hal_ethernet.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct sGspSVSubscriber_ASDU* GspSVSubscriber_ASDU;

typedef struct sGspSVSubscriber* GspSVSubscriber;

typedef void (*GspSVUpdateListener)(GspSVSubscriber subscriber, void* parameter, GspSVSubscriber_ASDU asdu);

typedef struct sGspSVReceiver* GspSVReceiver;

LIB860_API GspSVReceiver GspSVReceiver_create(void);

LIB860_API void GspSVReceiver_disableDestAddrCheck(GspSVReceiver self);

LIB860_API void GspSVReceiver_enableDestAddrCheck(GspSVReceiver self);

LIB860_API void GspSVReceiver_setInterfaceId(GspSVReceiver self, const char* interfaceId);

LIB860_API void GspSVReceiver_addSubscriber(GspSVReceiver self, GspSVSubscriber subscriber);

LIB860_API void GspSVReceiver_removeSubscriber(GspSVReceiver self, GspSVSubscriber subscriber);

LIB860_API void GspSVReceiver_start(GspSVReceiver self);

LIB860_API void GspSVReceiver_stop(GspSVReceiver self);

LIB860_API bool GspSVReceiver_isRunning(GspSVReceiver self);

LIB860_API void GspSVReceiver_destroy(GspSVReceiver self);

LIB860_API EthernetSocket GspSVReceiver_startThreadless(GspSVReceiver self);

LIB860_API void GspSVReceiver_stopThreadless(GspSVReceiver self);

LIB860_API bool GspSVReceiver_tick(GspSVReceiver self);

LIB860_API GspSVSubscriber GspSVSubscriber_create(const uint8_t* ethAddr, uint16_t appID);

LIB860_API void GspSVSubscriber_setListener(GspSVSubscriber self, GspSVUpdateListener listener, void* parameter);

LIB860_API void GspSVSubscriber_destroy(GspSVSubscriber self);

LIB860_API uint16_t GspSVSubscriber_ASDU_getSmpCnt(GspSVSubscriber_ASDU self);

LIB860_API const char* GspSVSubscriber_ASDU_getSvId(GspSVSubscriber_ASDU self);

LIB860_API const char* GspSVSubscriber_ASDU_getDatSet(GspSVSubscriber_ASDU self);

LIB860_API uint32_t GspSVSubscriber_ASDU_getConfRev(GspSVSubscriber_ASDU self);

LIB860_API uint8_t GspSVSubscriber_ASDU_getSmpMod(GspSVSubscriber_ASDU self);

LIB860_API uint16_t GspSVSubscriber_ASDU_getSmpRate(GspSVSubscriber_ASDU self);

LIB860_API bool GspSVSubscriber_ASDU_hasDatSet(GspSVSubscriber_ASDU self);

LIB860_API bool GspSVSubscriber_ASDU_hasRefrTm(GspSVSubscriber_ASDU self);

LIB860_API bool GspSVSubscriber_ASDU_hasSmpMod(GspSVSubscriber_ASDU self);

LIB860_API bool GspSVSubscriber_ASDU_hasSmpRate(GspSVSubscriber_ASDU self);

LIB860_API uint64_t GspSVSubscriber_ASDU_getRefrTmAsMs(GspSVSubscriber_ASDU self);

LIB860_API int8_t GspSVSubscriber_ASDU_getINT8(GspSVSubscriber_ASDU self, int index);

LIB860_API int16_t GspSVSubscriber_ASDU_getINT16(GspSVSubscriber_ASDU self, int index);

LIB860_API int32_t GspSVSubscriber_ASDU_getINT32(GspSVSubscriber_ASDU self, int index);

LIB860_API int64_t GspSVSubscriber_ASDU_getINT64(GspSVSubscriber_ASDU self, int index);

LIB860_API uint8_t GspSVSubscriber_ASDU_getINT8U(GspSVSubscriber_ASDU self, int index);

LIB860_API uint16_t GspSVSubscriber_ASDU_getINT16U(GspSVSubscriber_ASDU self, int index);

LIB860_API uint32_t GspSVSubscriber_ASDU_getINT32U(GspSVSubscriber_ASDU self, int index);

LIB860_API uint64_t GspSVSubscriber_ASDU_getINT64U(GspSVSubscriber_ASDU self, int index);

LIB860_API float GspSVSubscriber_ASDU_getFLOAT32(GspSVSubscriber_ASDU self, int index);

LIB860_API double GspSVSubscriber_ASDU_getFLOAT64(GspSVSubscriber_ASDU self, int index);

LIB860_API GspTimestamp GspSVSubscriber_ASDU_getTimestamp(GspSVSubscriber_ASDU self, int index);

LIB860_API GspQuality GspSVSubscriber_ASDU_getQuality(GspSVSubscriber_ASDU self, int index);

LIB860_API int GspSVSubscriber_ASDU_getDataSize(GspSVSubscriber_ASDU self);

#ifndef DEPRECATED
#if defined(__GNUC__) || defined(__clang__)
  #define DEPRECATED __attribute__((deprecated))
#else
  #define DEPRECATED
#endif
#endif

typedef struct sGspSVSubscriberASDU* GspSVClientASDU;

LIB860_API DEPRECATED uint16_t GspSVClientASDU_getSmpCnt(GspSVSubscriber_ASDU self);

LIB860_API DEPRECATED const char* GspSVClientASDU_getSvId(GspSVSubscriber_ASDU self);

LIB860_API DEPRECATED uint32_t GspSVClientASDU_getConfRev(GspSVSubscriber_ASDU self);

LIB860_API DEPRECATED bool GspSVClientASDU_hasRefrTm(GspSVSubscriber_ASDU self);

LIB860_API DEPRECATED uint64_t GspSVClientASDU_getRefrTmAsMs(GspSVSubscriber_ASDU self);

LIB860_API DEPRECATED int8_t GspSVClientASDU_getINT8(GspSVSubscriber_ASDU self, int index);

LIB860_API DEPRECATED int16_t GspSVClientASDU_getINT16(GspSVSubscriber_ASDU self, int index);

LIB860_API DEPRECATED int32_t GspSVClientASDU_getINT32(GspSVSubscriber_ASDU self, int index);

LIB860_API DEPRECATED int64_t GspSVClientASDU_getINT64(GspSVSubscriber_ASDU self, int index);

LIB860_API DEPRECATED uint8_t GspSVClientASDU_getINT8U(GspSVSubscriber_ASDU self, int index);

LIB860_API DEPRECATED uint16_t GspSVClientASDU_getINT16U(GspSVSubscriber_ASDU self, int index);

LIB860_API DEPRECATED uint32_t GspSVClientASDU_getINT32U(GspSVSubscriber_ASDU self, int index);

LIB860_API DEPRECATED uint64_t GspSVClientASDU_getINT64U(GspSVSubscriber_ASDU self, int index);

LIB860_API DEPRECATED float GspSVClientASDU_getFLOAT32(GspSVSubscriber_ASDU self, int index);

LIB860_API DEPRECATED double GspSVClientASDU_getFLOAT64(GspSVSubscriber_ASDU self, int index);

LIB860_API DEPRECATED int GspSVClientASDU_getDataSize(GspSVSubscriber_ASDU self);

#ifdef __cplusplus
}
#endif

#endif /* SAMPLED_VALUES_SV_SUBSCRIBER_ */
