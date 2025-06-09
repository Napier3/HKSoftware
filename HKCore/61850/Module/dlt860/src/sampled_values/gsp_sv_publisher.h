/*
 *  sv_publisher.h
 */


#ifndef GSP_SRC_SAMPLED_VALUES_SV_PUBLISHER_H_
#define GSP_SRC_SAMPLED_VALUES_SV_PUBLISHER_H_

#include "libdlt860_platform_includes.h"
#include "dlt860_common.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef GOOSE_SV_COMM_PARAMETERS
#define GOOSE_SV_COMM_PARAMETERS

typedef struct sGspCommParameters {
    uint8_t vlanPriority;
    uint16_t vlanId;
    uint16_t appId;
    uint8_t dstAddress[6];
} GspCommParameters;

#endif

#define DLT860_SV_SMPSYNC_NOT_SYNCHRONIZED 0
#define DLT860_SV_SMPSYNC_SYNCED_UNSPEC_LOCAL_CLOCK 1
#define DLT860_SV_SMPSYNC_SYNCED_GLOBAL_CLOCK 2
#define DLT860_SV_SMPMOD_PER_NOMINAL_PERIOD 0
#define DLT860_SV_SMPMOD_SAMPLES_PER_SECOND 1
#define DLT860_SV_SMPMOD_SECONDS_PER_SAMPLE 2

typedef struct sGspSVPublisher* GspSVPublisher;
typedef struct sGspSVPublisher_ASDU* GspSVPublisher_ASDU;

LIB860_API GspSVPublisher GspSVPublisher_create(GspCommParameters* parameters, const char* interfaceId);

LIB860_API GspSVPublisher GspSVPublisher_createEx(GspCommParameters* parameters, const char* interfaceId, bool useVlanTag);

LIB860_API GspSVPublisher_ASDU GspSVPublisher_addASDU(GspSVPublisher self, const char* svID, const char* datset, uint32_t confRev);

LIB860_API void GspSVPublisher_setupComplete(GspSVPublisher self);

LIB860_API void GspSVPublisher_publish(GspSVPublisher self);

LIB860_API void GspSVPublisher_destroy(GspSVPublisher self);

LIB860_API void GspSVPublisher_ASDU_resetBuffer(GspSVPublisher_ASDU self);

LIB860_API int GspSVPublisher_ASDU_addINT8(GspSVPublisher_ASDU self);

LIB860_API void GspSVPublisher_ASDU_setINT8(GspSVPublisher_ASDU self, int index, int8_t value);

LIB860_API int GspSVPublisher_ASDU_addINT32(GspSVPublisher_ASDU self);

LIB860_API void GspSVPublisher_ASDU_setINT32(GspSVPublisher_ASDU self, int index, int32_t value);

LIB860_API int GspSVPublisher_ASDU_addINT64(GspSVPublisher_ASDU self);

LIB860_API void GspSVPublisher_ASDU_setINT64(GspSVPublisher_ASDU self, int index, int64_t value);

LIB860_API int GspSVPublisher_ASDU_addFLOAT(GspSVPublisher_ASDU self);

LIB860_API void GspSVPublisher_ASDU_setFLOAT(GspSVPublisher_ASDU self, int index, float value);

LIB860_API int GspSVPublisher_ASDU_addFLOAT64(GspSVPublisher_ASDU self);

LIB860_API void GspSVPublisher_ASDU_setFLOAT64(GspSVPublisher_ASDU self, int index, double value);

LIB860_API int GspSVPublisher_ASDU_addTimestamp(GspSVPublisher_ASDU self);

LIB860_API void GspSVPublisher_ASDU_setTimestamp(GspSVPublisher_ASDU self, int index, Timestamp value);

LIB860_API int GspSVPublisher_ASDU_addQuality(GspSVPublisher_ASDU self);

LIB860_API void GspSVPublisher_ASDU_setQuality(GspSVPublisher_ASDU self, int index, Quality value);

LIB860_API void GspSVPublisher_ASDU_setSmpCnt(GspSVPublisher_ASDU self, uint16_t value);

LIB860_API uint16_t GspSVPublisher_ASDU_getSmpCnt(GspSVPublisher_ASDU self);

LIB860_API void GspSVPublisher_ASDU_increaseSmpCnt(GspSVPublisher_ASDU self);

LIB860_API void GspSVPublisher_ASDU_setSmpCntWrap(GspSVPublisher_ASDU self, uint16_t value);

LIB860_API void GspSVPublisher_ASDU_enableRefrTm(GspSVPublisher_ASDU self);

LIB860_API void GspSVPublisher_ASDU_setRefrTm(GspSVPublisher_ASDU self, uint64_t refrTm);

LIB860_API void GspSVPublisher_ASDU_setSmpMod(GspSVPublisher_ASDU self, uint8_t smpMod);

LIB860_API void GspSVPublisher_ASDU_setSmpRate(GspSVPublisher_ASDU self, uint16_t smpRate);

LIB860_API void GspSVPublisher_ASDU_setSmpSynch(GspSVPublisher_ASDU self, uint16_t smpSynch);

#ifndef DEPRECATED
#if defined(__GNUC__) || defined(__clang__)
  #define DEPRECATED __attribute__((deprecated))
#else
  #define DEPRECATED
#endif
#endif

typedef struct sGspSVPublisher* GspSampledValuesPublisher;

typedef struct sGspSV_ASDU* GspSV_ASDU;

LIB860_API DEPRECATED GspSVPublisher GspSampledValuesPublisher_create(GspCommParameters* parameters, const char* interfaceId);

LIB860_API DEPRECATED GspSVPublisher_ASDU GspSampledValuesPublisher_addASDU(GspSVPublisher self, char* svID, char* datset, uint32_t confRev);

LIB860_API DEPRECATED void GspSampledValuesPublisher_setupComplete(GspSVPublisher self);

LIB860_API DEPRECATED void GspSampledValuesPublisher_publish(GspSVPublisher self);

LIB860_API DEPRECATED void GspSampledValuesPublisher_destroy(GspSVPublisher self);

LIB860_API DEPRECATED void GspSV_ASDU_resetBuffer(GspSVPublisher_ASDU self);

LIB860_API DEPRECATED int GspSV_ASDU_addINT8(GspSVPublisher_ASDU self);

LIB860_API DEPRECATED void GspSV_ASDU_setINT8(GspSVPublisher_ASDU self, int index, int8_t value);

LIB860_API DEPRECATED int GspSV_ASDU_addINT32(GspSVPublisher_ASDU self);

LIB860_API DEPRECATED void GspSV_ASDU_setINT32(GspSVPublisher_ASDU self, int index, int32_t value);

LIB860_API DEPRECATED int GspSV_ASDU_addINT64(GspSVPublisher_ASDU self);

LIB860_API DEPRECATED void GspSV_ASDU_setINT64(GspSVPublisher_ASDU self, int index, int64_t value);

LIB860_API DEPRECATED int GspSV_ASDU_addFLOAT(GspSVPublisher_ASDU self);

LIB860_API DEPRECATED void GspSV_ASDU_setFLOAT(GspSVPublisher_ASDU self, int index, float value);

LIB860_API DEPRECATED int GspSV_ASDU_addFLOAT64(GspSVPublisher_ASDU self);

LIB860_API DEPRECATED void GspSV_ASDU_setFLOAT64(GspSVPublisher_ASDU self, int index, double value);

LIB860_API DEPRECATED void GspSV_ASDU_setSmpCnt(GspSVPublisher_ASDU self, uint16_t value);

LIB860_API DEPRECATED uint16_t GspSV_ASDU_getSmpCnt(GspSVPublisher_ASDU self);

LIB860_API DEPRECATED void GspSV_ASDU_increaseSmpCnt(GspSVPublisher_ASDU self);

LIB860_API DEPRECATED void GspSV_ASDU_setRefrTm(GspSVPublisher_ASDU self, uint64_t refrTm);

LIB860_API DEPRECATED void GspSV_ASDU_setSmpMod(GspSVPublisher_ASDU self, uint8_t smpMod);

LIB860_API DEPRECATED void GspSV_ASDU_setSmpRate(GspSVPublisher_ASDU self, uint16_t smpRate);

#ifdef __cplusplus
}
#endif

#endif /* GSP_SRC_SAMPLED_VALUES_SV_PUBLISHER_H_ */
