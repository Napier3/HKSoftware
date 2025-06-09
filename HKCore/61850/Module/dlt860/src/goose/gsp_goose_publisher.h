/*
 *  gsp_goose_publisher.h
 */

#ifndef GSP_GOOSE_PUBLISHER_H_
#define GSP_GOOSE_PUBLISHER_H_

#include "libdlt860_platform_includes.h"
#include "gsp_linked_list.h"
#include "gsp_mms_value.h"

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

typedef struct sGspGoosePublisher* GspGoosePublisher;

LIB860_API GspGoosePublisher GspGoosePublisher_create(GspCommParameters* parameters, const char* interfaceID);

LIB860_API GspGoosePublisher GspGoosePublisher_createEx(GspCommParameters* parameters, const char* interfaceID, bool useVlanTag);

LIB860_API void GspGoosePublisher_destroy(GspGoosePublisher self);

LIB860_API int GspGoosePublisher_publish(GspGoosePublisher self, LinkedList dataSet);

LIB860_API void GspGoosePublisher_setGoID(GspGoosePublisher self, char* goID);

LIB860_API void GspGoosePublisher_setGoCbRef(GspGoosePublisher self, char* goCbRef);

LIB860_API void GspGoosePublisher_setTimeAllowedToLive(GspGoosePublisher self, uint32_t timeAllowedToLive);

LIB860_API void GspGoosePublisher_setDataSetRef(GspGoosePublisher self, char* dataSetRef);

LIB860_API void GspGoosePublisher_setConfRev(GspGoosePublisher self, uint32_t confRev);

LIB860_API void GspGoosePublisher_setSimulation(GspGoosePublisher self, bool simulation);

LIB860_API void GspGoosePublisher_setNeedsCommission(GspGoosePublisher self, bool ndsCom);

LIB860_API uint64_t GspGoosePublisher_increaseStNum(GspGoosePublisher self);

LIB860_API void GspGoosePublisher_reset(GspGoosePublisher self);

#ifdef __cplusplus
}
#endif

#endif /* GSP_GOOSE_PUBLISHER_H_ */
