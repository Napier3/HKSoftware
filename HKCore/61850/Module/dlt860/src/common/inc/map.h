/*
 *  map.h
 *  map 封装
 */

#ifndef GSP_MAP_H_
#define GSP_MAP_H_

#include "libdlt860_common_api.h"
#include "gsp_linked_list.h"
#include <unordered_map>

namespace GSP {

// map对象
typedef unordered_map<void *, void *>* Map;

/**
 * @brief Map_create 创建一个 map
 * @return map 对象
 */
LIB860_INTERNAL Map Map_create(void);

/**
 * @brief Map_size map 尺寸
 * @param map 对象
 * @return
 */
LIB860_INTERNAL int Map_size(Map map);

/**
 * @brief Map_addEntry 增加 map 节点
 * @param map 对象
 * @param key 关键字
 * @param value 值
 * @return
 */
LIB860_INTERNAL void* Map_addEntry(Map map, void* key, void* value);

/**
 * @brief Map_removeEntry 删除 map 节点
 * @param map map
 * @param key 键值
 * @param deleteKey 是否删除键值
 * @return
 */
LIB860_INTERNAL void* Map_removeEntry(Map map, void* key, bool deleteKey);

/**
 * @brief Map_getEntry 获取指定键的值
 * @param map 对象
 * @param key 键值
 * @return 值
 */
LIB860_INTERNAL void* Map_getEntry(Map map, void* key);

/**
 * @brief Map_delete 删除map对象(删除值)
 * @param map 对象
 * @param deleteKey 是否删除键值
 */
LIB860_INTERNAL void Map_delete(Map map, bool deleteKey);

/**
 * @brief Map_deleteStatic 删除map对象(不删除值)
 * @param map 对象
 * @param deleteKey 是否删除键值
 */
LIB860_INTERNAL void Map_deleteStatic(Map map, bool deleteKey);

/**
 * @brief Map_deleteDeep 删除map对象(深删除)
 * @param map 对象
 * @param deleteKey 是否删除键值
 */
LIB860_INTERNAL void Map_deleteDeep(Map map, bool deleteKey, void (*valueDeleteFunction) (void*));

}
#endif /* GSP_MAP_H_ */
