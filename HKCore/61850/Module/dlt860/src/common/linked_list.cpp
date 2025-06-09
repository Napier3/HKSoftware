/*
 *  linked_list.c
 *
 */

#include "libdlt860_platform_includes.h"
#include "gsp_linked_list.h"
#include <algorithm>

using namespace GSP;

void * GSP::GspLinkedList_getLastElement(GspLinkedList list)
{
    return list->back();
}

GspLinkedList GSP::GspLinkedList_create()
{
    return new deque<void *>();
}

/**
 * Destroy list (free). Also frees element data with helper function.
 */
void GSP::GspLinkedList_destroyDeep(GspLinkedList list, GspLinkedListValueDeleteFunction valueDeleteFunction)
{
    if(!list)
    {
        return;
    }

#ifdef NOT_USE_IN_C11
	deque<void *> d = *list;

	for(deque<void *>::const_iterator it = d.begin(); it != d.end(); it++)
	{
		void* item = (void*)(*it);

		if(item)
		{
			valueDeleteFunction(item);
		}
	}
#else
    for(auto & item : *list)
    {
        if(item)
        {
            valueDeleteFunction(item);
        }
    }
#endif
    delete list;
}

void GSP::GspLinkedList_destroy(GspLinkedList list)
{
    GSP::GspLinkedList_destroyDeep(list, GspMemory_free);
}

/**
 * Destroy list (free) without freeing the element data
 */
void GSP::GspLinkedList_destroyStatic(GspLinkedList list)
{
    if(list){
        delete list;
    }
}

int GSP::GspLinkedList_size(GspLinkedList list)
{
    return (int)list->size();
}

void GSP::GspLinkedList_add(GspLinkedList list, void* data)
{
    list->push_back(data);
}

bool GSP::GspLinkedList_contains(GspLinkedList list, void* data)
{
    return std::find(list->begin(), list->end(), data) != list->end();
}

bool GSP::GspLinkedList_remove(GspLinkedList list, void* data)
{
#ifdef NOT_USE_IN_C11
    deque<void *>::iterator it = std::find(list->begin(), list->end(), data);
	if(it != list->end())
#else
    auto it = std::find(list->begin(), list->end(), data);
    if(it != list->end())
#endif
    {
        list->erase(it);
        return true;
    }
    return false;
}

void * GSP::GspLinkedList_get(GspLinkedList list, int index)
{
    return list->at(index);
}


void GSP::GspLinkedList_printStringList(GspLinkedList list)
{
#ifdef NOT_USE_IN_C11
	deque<void *> d = *list;

	for(deque<void *>::const_iterator it = d.begin(); it != d.end(); it++)
	{
		char* item = (char*)(*it);
		printf("%s\n", item);
	}
#else
    for(auto &item : *list)
    {
        printf("%s\n", (char *)item);
    }
#endif
}



