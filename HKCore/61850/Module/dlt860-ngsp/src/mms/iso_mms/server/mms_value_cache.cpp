/*
 *  mms_value_cache.c
 */

#include "libdlt860_platform_includes.h"
#include "mms_value_cache.h"
#include "stack_config.h"

struct sMmsValueCache {
	GspMmsDomain* domain;
    StrHashMap<sGspMmsValueCacheEntry *> *map;
};

void
Gsp_MmsValueCache_insertValue(ValueHashMap *self, GspMmsDomain *domain, char* itemId, GspMmsValue* value)
{
    GspMmsVariableSpecification* typeSpec = GspMmsDomain_getNamedVariable(domain, itemId);

	if (typeSpec != NULL) {
        GspMmsValueCacheEntry* cacheEntry = new GspMmsValueCacheEntry();

		cacheEntry->value = value;
		cacheEntry->typeSpec = typeSpec;
        self->insert(std::make_pair(itemId, cacheEntry));
	}
	else
        if (DEBUG_SERVER) printf("Cannot insert value into cache %s : no typeSpec found!\n", itemId);
}

static char*
getParentSubString(char* itemId)
{
	int len = strlen(itemId);

	char* strPos = itemId + len;

	while (--strPos > itemId) {
		if (*strPos == '$') {
			*strPos = 0;
			return itemId;
		}
	}

	return NULL;
}

static const char*
getChildSubString (const char* itemId, char* parentId)
{
	return itemId + strlen(parentId) + 1;
}

static GspMmsValue*
searchCacheForValue(ValueHashMap *self, GspMmsDomain *domain, const char* itemId, char* parentId)
{
    GspMmsValueCacheEntry* cacheEntry = nullptr;
	GspMmsValue* value = NULL;

	if(auto iter = self->find(parentId); iter == self->end()) {
		char* parentItemId = getParentSubString(parentId);

		if (parentItemId != NULL) {
            value = searchCacheForValue(self, domain, itemId, parentItemId);
		}
	}
	else {
		cacheEntry = iter->second;
		const char* childId = getChildSubString(itemId, parentId);

        GspMmsVariableSpecification* typeSpec = GspMmsDomain_getNamedVariable(domain, parentId);
		value = GspMmsVariableSpecification_getChildValue(typeSpec, cacheEntry->value, childId);
	}

	return value;
}

GspMmsValue*
Gsp_MmsValueCache_lookupValue(ValueHashMap *self, GspMmsDomain *domain, const char* itemId)
{
	/*
	 * get value for first matching key substring!
	 * Then iterate the value for the exact value.
     */

	GspMmsValue* value = NULL;
    GspMmsValueCacheEntry* cacheEntry = nullptr;

	if(auto iter = self->find(itemId); iter == self->end()) {
		char* itemIdCopy = StringUtils_copyString(itemId);
		char* parentItemId = getParentSubString(itemIdCopy);

		if (parentItemId != NULL) {
            value = searchCacheForValue(self, domain, itemId, parentItemId);
		}

		GLOBAL_FREEMEM(itemIdCopy);
	} else {
		cacheEntry = iter->second;
	}

	if (cacheEntry != NULL)
		return cacheEntry->value;
	else
		return value;
}

