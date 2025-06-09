/*
 *  gsp_goose_receiver.h
 */

#ifndef GSP_GOOSE_RECEIVER_H_
#define GSP_GOOSE_RECEIVER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#include "gsp_hal_ethernet.h"
#include "gsp_goose_subscriber.h"

typedef struct GspGooseReceiver* GspGooseReceiver;

LIB860_API GspGooseReceiver GspGooseReceiver_create(void);

LIB860_API GspGooseReceiver GspGooseReceiver_createEx(uint8_t* buffer);

LIB860_API void GspGooseReceiver_setInterfaceId(GspGooseReceiver self, const char* interfaceId);

LIB860_API const char* GspGooseReceiver_getInterfaceId(GspGooseReceiver self);

LIB860_API void GspGooseReceiver_addSubscriber(GspGooseReceiver self, GspGooseSubscriber subscriber);

LIB860_API void GspGooseReceiver_removeSubscriber(GspGooseReceiver self, GspGooseSubscriber subscriber);

LIB860_API void GspGooseReceiver_start(GspGooseReceiver self);

LIB860_API void GspGooseReceiver_stop(GspGooseReceiver self);

LIB860_API bool GspGooseReceiver_isRunning(GspGooseReceiver self);

LIB860_API void GspGooseReceiver_destroy(GspGooseReceiver self);

LIB860_API EthernetSocket GspGooseReceiver_startThreadless(GspGooseReceiver self);

LIB860_API void GspGooseReceiver_stopThreadless(GspGooseReceiver self);

LIB860_API bool GspGooseReceiver_tick(GspGooseReceiver self);

LIB860_API void GspGooseReceiver_handleMessage(GspGooseReceiver self, uint8_t* buffer, int size);

#ifdef __cplusplus
}
#endif

#endif /* GSP_GOOSE_RECEIVER_H_ */
