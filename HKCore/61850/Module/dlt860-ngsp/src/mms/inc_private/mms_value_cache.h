/*
 *  mms_value_cache.h
 */

#ifndef GSP_MMS_VARIABLE_CACHE_H_
#define GSP_MMS_VARIABLE_CACHE_H_

#include "mms_device_model.h"
#include "gsp_mms_value.h"
#include "stringmap.h"
#include <string>

using std::string;

typedef struct sGspMmsValueCacheEntry {
    GspMmsValue* value;
    GspMmsVariableSpecification* typeSpec;
} GspMmsValueCacheEntry;

using ValueHashMap = StrHashMap<GspMmsValueCacheEntry*>;

LIB860_INTERNAL void Gsp_MmsValueCache_insertValue(ValueHashMap *self, GspMmsDomain *domain, char* itemId, GspMmsValue* value);

LIB860_INTERNAL GspMmsValue* Gsp_MmsValueCache_lookupValue(ValueHashMap *self, GspMmsDomain *domain, const char* itemId);

#endif /* MMS_VARIABLE_CACHE_H_ */
