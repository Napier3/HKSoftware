//////////////////////////////////////////////////////////////////////////
//mms_string.h
#ifndef mms_mem_string_h__
#define mms_mem_string_h__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include<string.h> 
#include <stdlib.h>

//#define _MVL_TYPE_CTRL_use_one_device_

#define use_rep_capacity

#define MMS_MEM_STRING_NULL_POS  (-1)

	typedef struct tagMmsStringRep
	{
		int size;
#ifdef use_rep_capacity
		int capacity;
#endif
		char str[1];
	}MMSSTRINGREP;


	struct tagMmsString
	{
		MMSSTRINGREP *rep_;
	};

	typedef struct tagMmsString MMS_MEM_STRING;
	typedef struct tagMmsString* PMMS_MEM_STRING;

	extern void mms_str_init(PMMS_MEM_STRING dest);

	extern void mms_str_quit(PMMS_MEM_STRING str);
	extern void mms_str_init2(PMMS_MEM_STRING dest, int sz);
	extern void mms_str_init3(PMMS_MEM_STRING dest, int sz, int cap);

	extern int mms_str_is_null(PMMS_MEM_STRING dest);

	static int mms_str_length(PMMS_MEM_STRING dest)
	{
		if (dest->rep_ == NULL)
		{
			return 0;
		}
		else
		{
			return dest->rep_->size;
		}
	}

	static int mms_str_capacity(PMMS_MEM_STRING dest)
	{
#ifdef use_rep_capacity
		if (dest->rep_ == NULL)
		{
			return 0;
		}
		else
		{
			return dest->rep_->capacity;
		}
#else
		return dest->rep_->size;
#endif
	}

	char* mms_string(PMMS_MEM_STRING dest);
	static char mms_str_at(PMMS_MEM_STRING dest, int pos)
	{
		if (dest->rep_ == NULL)
		{
			return 0;
		}

		return dest->rep_->str[pos];
	}

	static int mms_reverse_find(PMMS_MEM_STRING dest, char ch ,int num)//参数3表示反向数，出现该字符的次数
	{
		int i ,j = -1,k = 0;
		if (dest->rep_ == NULL)
		{
			return -1;
		}

		for (i = dest->rep_->size - 1;i>=0;i--)
		{
			if (dest->rep_->str[i] == ch)
			{
				k++;

				if (k == num)
				{
					j= i;
					break;
				}
			}
		}

		return j;
	}

	static char* mms_str_pos(PMMS_MEM_STRING dest,int pos)
	{
		if (dest->rep_ == NULL)
		{
			return NULL;
		}

		return dest->rep_->str + pos;
	}

	static char* mms_str_finish(PMMS_MEM_STRING dest)
	{
		if (dest->rep_ == NULL)
		{
			return NULL;
		}

		return dest->rep_->str + dest->rep_->size;
	}
	static char* mms_string_start(PMMS_MEM_STRING dest)
	{
		if (dest->rep_ == NULL)
		{
			return NULL;
		}

		return dest->rep_->str;
	}
	extern void mms_str_set_size(PMMS_MEM_STRING dest, int sz) ;

	static void mms_str_set2(PMMS_MEM_STRING dest, const char* str, int len)
	{
		if (mms_str_is_null(dest))
		{
			mms_str_init2(dest, len);
		}
		else
		{
			mms_str_init3(dest, len, len);
		}

		memcpy(dest->rep_->str, str, len);
		dest->rep_->str[len] = '\0';
		dest->rep_->size = len;
	}
	static void mms_str_set3(PMMS_MEM_STRING dest, const char* str, int lenadd)
	{
		int len = strlen(str);

		if (mms_str_is_null(dest))
		{
			mms_str_init2(dest, len+lenadd);
		}

		memcpy(dest->rep_->str, str, len);
		dest->rep_->str[len] = '\0';
		dest->rep_->size = len;
	}

	static void mms_str_set(PMMS_MEM_STRING dest, const char* str)
	{
		mms_str_set2(dest, str, strlen(str));
	}

	static void mms_str_swap (PMMS_MEM_STRING str1, PMMS_MEM_STRING str2)
	{
		MMSSTRINGREP* r = str1->rep_;
		str1->rep_ = str2->rep_;
		str2->rep_ = r;
	}

	extern void mms_str_cat(PMMS_MEM_STRING dest, const char* str);
	extern void mms_str_copy(PMMS_MEM_STRING dest, PMMS_MEM_STRING src);
	extern void mms_str_copy2(char *dest, PMMS_MEM_STRING src);

	static long mms_str_cmp(PMMS_MEM_STRING dest, PMMS_MEM_STRING src)
	{
		if (dest->rep_ == NULL)
		{
			mms_str_init(dest);
		}

		if (src->rep_ == NULL)
		{
			mms_str_init(src);
		}

		return strcmp(dest->rep_->str, src->rep_->str);
	}

	extern void mms_str_assign (PMMS_MEM_STRING dest, const char* str);
	extern void mms_str_assign2 (PMMS_MEM_STRING dest, const char* str, int len);
	extern void mms_str_assign3 (PMMS_MEM_STRING dest, PMMS_MEM_STRING src);

	extern void mms_str_append (PMMS_MEM_STRING dest, const char* str);
	extern void mms_str_append2 (PMMS_MEM_STRING dest, const char* str, int len);
	extern void mms_str_append3 (PMMS_MEM_STRING dest, PMMS_MEM_STRING src);
	extern void mms_str_reserve (PMMS_MEM_STRING dest, int cap);

#ifdef __cplusplus
}
#endif

#endif	// mms_mem_string_h__
