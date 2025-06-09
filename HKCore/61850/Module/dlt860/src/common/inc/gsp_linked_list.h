/*
 *  gsp_linked_list.h
 *  �Զ������������
 */

#ifndef GSP_LINKED_LIST_H_
#define GSP_LINKED_LIST_H_

#include "libdlt860_common_api.h"
#include <deque>
using namespace std;
namespace GSP {

// ����ṹ�ڵ�
struct sGspLinkedList {
	void* data;
    struct sGspLinkedList* next;
};

/**
 * \brief ����ָ��
 */
typedef deque<void*> * GspLinkedList;

/**
 * \brief �����������
 *
 * \return ��������������
 */
LIB860_API GspLinkedList GspLinkedList_create(void);

/**
 * \brief ɾ����������(ǳ��ɾ��)
 *
 * ɾ�������е���������. �����ͷ����е����ݽڵ�. ��������������ڶ�����Щ�洢�˼򵥶��������.
 *
 * \param self ��������
 */
LIB860_API void GspLinkedList_destroy(GspLinkedList self);


/**
 * ɾ����������ݺ����ص�
 */
typedef void (*GspLinkedListValueDeleteFunction) (void*);

/**
 * \brief ɾ����������(���ɾ��)
 *
 * \param self ��ɾ�����������
 * \param valueDeleteFunction Ԫ��ɾ��ʱ�Ļص�����
 */
LIB860_API void GspLinkedList_destroyDeep(GspLinkedList self, GspLinkedListValueDeleteFunction valueDeleteFunction);

/**
 * \brief ɾ�������ǲ�ɾ������
 * �ú�������ɾ�������д洢��̬���ݵ�����,��ɾ������ɾ������
 * \param self ��ɾ��������
 */
LIB860_API void GspLinkedList_destroyStatic(GspLinkedList self);

/**
 * \brief ��������������һ�����ݽڵ�
 * ������������һ�����ݽڵ�
 * \param self �������
 * \param data Ҫ��ӵ��������������
 */
LIB860_API void GspLinkedList_add(GspLinkedList self, void* data);

/**
 * \brief ��������Ƿ���������
 * \param self ����
 * \param data ��Ҫ��������
 * \return true �������Ƿ���ڸ�����
 */
LIB860_API bool GspLinkedList_contains(GspLinkedList self, void* data);

/**
 * \brief ��������ɾ������
 * \param self ����
 * \param data ���Ƴ�������
 * \return ɾ�������Ƿ�ɹ�
 */
LIB860_API bool GspLinkedList_remove(GspLinkedList self, void* data);

/**
 * \brief ��ȡ�ƶ��������������� (�� 0 ��ʼ).
 * \param self ����
 * \param index Ԫ�����
 */
LIB860_API void *GspLinkedList_get(GspLinkedList self, int index);

/**
 * \brief ��ȡ��������һ��Ԫ��
 * \param listElement ����
 */
LIB860_API void *GspLinkedList_getLastElement(GspLinkedList self);

/**
 * \brief ��ȡ����ߴ�
 * \param self ����
 * \return ����ߴ�
 */
LIB860_API int GspLinkedList_size(GspLinkedList self);

/**
 * @brief LinkedList_printStringList ��ӡ������������
 * @param self ����
 */
LIB860_API void GspLinkedList_printStringList(GspLinkedList self);

}
#endif /* GSP_LINKED_LIST_H_ */
