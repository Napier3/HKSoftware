/*
 *  gsp_linked_list.h
 *  自定义的数据链表
 */

#ifndef GSP_LINKED_LIST_H_
#define GSP_LINKED_LIST_H_

#include "libdlt860_common_api.h"
#include <deque>
using namespace std;
namespace GSP {

// 链表结构节点
struct sGspLinkedList {
	void* data;
    struct sGspLinkedList* next;
};

/**
 * \brief 链表指针
 */
typedef deque<void*> * GspLinkedList;

/**
 * \brief 创建链表对象
 *
 * \return 创建后的链表对象
 */
LIB860_API GspLinkedList GspLinkedList_create(void);

/**
 * \brief 删除链表数据(浅层删除)
 *
 * 删除链表中的所有数据. 它将释放所有的数据节点. 这个函数仅适用于对于那些存储了简单对象的链表.
 *
 * \param self 链表数据
 */
LIB860_API void GspLinkedList_destroy(GspLinkedList self);


/**
 * 删除链表的数据函数回调
 */
typedef void (*GspLinkedListValueDeleteFunction) (void*);

/**
 * \brief 删除链表数据(深层删除)
 *
 * \param self 待删除的链表对象
 * \param valueDeleteFunction 元素删除时的回调函数
 */
LIB860_API void GspLinkedList_destroyDeep(GspLinkedList self, GspLinkedListValueDeleteFunction valueDeleteFunction);

/**
 * \brief 删除链表但是不删除数据
 * 该函数用来删除链表中存储静态数据的链表,进删除链表不删除数据
 * \param self 待删除的链表
 */
LIB860_API void GspLinkedList_destroyStatic(GspLinkedList self);

/**
 * \brief 在链表中增加中一个数据节点
 * 在链表中增加一个数据节点
 * \param self 链表对象
 * \param data 要添加到数据链表的数据
 */
LIB860_API void GspLinkedList_add(GspLinkedList self, void* data);

/**
 * \brief 检查数据是否在链表中
 * \param self 链表
 * \param data 需要检查的数据
 * \return true 链表中是否存在该数据
 */
LIB860_API bool GspLinkedList_contains(GspLinkedList self, void* data);

/**
 * \brief 从链表中删除数据
 * \param self 链表
 * \param data 待移除的数据
 * \return 删除数据是否成功
 */
LIB860_API bool GspLinkedList_remove(GspLinkedList self, void* data);

/**
 * \brief 获取制定索引的链表数据 (以 0 开始).
 * \param self 链表
 * \param index 元素序号
 */
LIB860_API void *GspLinkedList_get(GspLinkedList self, int index);

/**
 * \brief 获取链表的最后一个元素
 * \param listElement 链表
 */
LIB860_API void *GspLinkedList_getLastElement(GspLinkedList self);

/**
 * \brief 获取链表尺寸
 * \param self 链表
 * \return 链表尺寸
 */
LIB860_API int GspLinkedList_size(GspLinkedList self);

/**
 * @brief LinkedList_printStringList 打印整个链表数据
 * @param self 链表
 */
LIB860_API void GspLinkedList_printStringList(GspLinkedList self);

}
#endif /* GSP_LINKED_LIST_H_ */
