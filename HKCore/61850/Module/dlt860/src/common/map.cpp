/*
 *  map.c
 *  map 封装
 */

#include "libdlt860_platform_includes.h"
#include "map.h"

using namespace GSP;

// map 节点
typedef struct sMapEntry
{
    void* key;
    void* value;
} MapEntry;

Map GSP::Map_create()
{
    auto m = new unordered_map<void *, void *>();
    return m;
}

int GSP::Map_size(Map map)
{
    return map->size();
}

void* GSP::Map_addEntry(Map map, void* key, void* value)
{
    map->insert({key, value});
    return key;
}

void* GSP::Map_removeEntry(Map map, void* key, bool deleteKey)
{
    auto it = map->find(key);
    if(it != map->end())
    {
        auto value = it->second;
        if(deleteKey)
        {
            GLOBAL_FREEMEM(it->first);
        }
        map->erase(it);
        return value;
    }
    return nullptr;
}

void* GSP::Map_getEntry(Map map, void* key)
{
    auto iter = map->find(key);
    return iter == map->end() ? nullptr : iter->second;
}

void GSP::Map_delete(Map map, bool deleteKey)
{
    for(auto &item : *map)
    {
        if(deleteKey)
        {
            GLOBAL_FREEMEM(item.first);
        }
        GLOBAL_FREEMEM(item.second);
    }
    delete map;
}

void GSP::Map_deleteStatic(Map map, bool deleteKey)
{
    for(auto &item : *map)
    {
        if(deleteKey)
        {
            GLOBAL_FREEMEM(item.first);
        }
    }
    delete map;
}

void GSP::Map_deleteDeep(Map map, bool deleteKey, void (*valueDeleteFunction)(void*))
{
    for(auto &item : *map)
    {
        if(deleteKey)
        {
            GLOBAL_FREEMEM(item.first);
        }
        valueDeleteFunction(item.second);
    }
    delete map;
}
