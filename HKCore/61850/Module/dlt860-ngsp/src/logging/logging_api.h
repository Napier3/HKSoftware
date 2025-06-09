/*
 *  logging_api.h
 */

#ifndef GSP_SRC_LOGGING_LOGGING_API_H_
#define GSP_SRC_LOGGING_LOGGING_API_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "libdlt860_common_api.h"

typedef struct sGspLogStorage* GspLogStorage;

typedef bool (*GspLogEntryCallback) (void* parameter, uint64_t timestamp, uint64_t entryID, bool moreFollow);

typedef bool (*GspLogEntryDataCallback) (void* parameter, const char* dataRef, uint8_t* data, int dataSize, uint8_t reasonCode, bool moreFollow);

struct sGspLogStorage {

    void* instanceData;

    int maxLogEntries;

    uint64_t (*addEntry) (GspLogStorage self,
                          uint64_t timestamp);

    bool (*addEntryData) (GspLogStorage self,
                          uint64_t entryID,
                          const char* dataRef,
                          uint8_t* data,
                          int dataSize,
                          uint8_t reasonCode);

    bool (*getEntries) (GspLogStorage self,
                        uint64_t startingTime,
                        uint64_t endingTime,
                        GspLogEntryCallback entryCallback,
                        GspLogEntryDataCallback entryDataCallback,
                        void* parameter);

    bool (*getEntriesAfter) (GspLogStorage self,
                             uint64_t startingTime,
                             uint64_t entryID,
                             GspLogEntryCallback entryCallback,
                             GspLogEntryDataCallback entryDataCallback,
                             void* parameter);

    bool (*getOldestAndNewestEntries) (GspLogStorage self,
                                       uint64_t* newEntry,
                                       uint64_t* newEntryTime,
                                       uint64_t* oldEntry,
                                       uint64_t* oldEntryTime);

    void (*destroy) (GspLogStorage self);
};

LIB860_API void GspLogStorage_setMaxLogEntries(GspLogStorage self, int maxEntries);

LIB860_API uint64_t GspLogStorage_addEntry(GspLogStorage self, uint64_t timestamp);

LIB860_API bool GspLogStorage_addEntryData(GspLogStorage self,
                                           uint64_t entryID,
                                           const char* dataRef,
                                           uint8_t* data,
                                           int dataSize,
                                           uint8_t reasonCode);

LIB860_API bool GspLogStorage_getEntries(GspLogStorage self,
                                         uint64_t startingTime,
                                         uint64_t endingTime,
                                         GspLogEntryCallback entryCallback,
                                         GspLogEntryDataCallback entryDataCallback,
                                         void* parameter);

LIB860_API bool GspLogStorage_getEntriesAfter(GspLogStorage self,
                                              uint64_t startingTime,
                                              uint64_t entryID,
                                              GspLogEntryCallback entryCallback,
                                              GspLogEntryDataCallback entryDataCallback,
                                              void* parameter);

LIB860_API bool GspLogStorage_getOldestAndNewestEntries(GspLogStorage self,
                                                        uint64_t* newEntry,
                                                        uint64_t* newEntryTime,
                                                        uint64_t* oldEntry,
                                                        uint64_t* oldEntryTime);

LIB860_API void GspLogStorage_destroy(GspLogStorage self);

LIB860_API GspLogStorage SqliteLogStorage_createInstance(const char* filename);

#ifdef __cplusplus
}
#endif

#endif /* LIBIEC61850_SRC_LOGGING_LOGGING_API_H_ */
