/*
 *  log_storage.c
 */

#include "logging_api.h"


void
GspLogStorage_setMaxLogEntries(GspLogStorage self, int maxEntries)
{
    self->maxLogEntries = maxEntries;
}

uint64_t
GspLogStorage_addEntry(GspLogStorage self, uint64_t timestamp)
{
    return self->addEntry(self, timestamp);
}

bool
GspLogStorage_addEntryData(GspLogStorage self, uint64_t entryID, const char* dataRef, uint8_t* data, int dataSize, uint8_t reasonCode)
{
    return self->addEntryData(self, entryID, dataRef, data, dataSize, reasonCode);
}

bool
GspLogStorage_getEntries(GspLogStorage self, uint64_t startingTime, uint64_t endingTime,
        GspLogEntryCallback entryCallback, GspLogEntryDataCallback entryDataCallback, void* parameter)
{
    return self->getEntries(self, startingTime, endingTime, entryCallback, entryDataCallback, parameter);
}

bool
GspLogStorage_getEntriesAfter(GspLogStorage self, uint64_t startingTime, uint64_t entryID,
        GspLogEntryCallback entryCallback, GspLogEntryDataCallback entryDataCallback, void* parameter)
{
    return self->getEntriesAfter(self, startingTime, entryID, entryCallback, entryDataCallback, parameter);
}

void
GspLogStorage_destroy(GspLogStorage self)
{
    self->destroy(self);
}


bool
GspLogStorage_getOldestAndNewestEntries(GspLogStorage self, uint64_t* newEntry, uint64_t* newEntryTime,
        uint64_t* oldEntry, uint64_t* oldEntryTime)
{
    return self->getOldestAndNewestEntries(self, newEntry, newEntryTime, oldEntry, oldEntryTime);
}

