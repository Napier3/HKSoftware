#include "mms_string.h"
#include <assert.h>

#ifdef use_rep_capacity
static struct tagMmsStringRep mms_string_nullrep_ = { 0, 0, { '\0' } };
#else
static struct tagMmsStringRep mms_string_nullrep_ = { 0, { '\0' } };
#endif

void mms_str_init(PMMS_MEM_STRING dest)
{
	dest->rep_ =  &mms_string_nullrep_;
	dest->rep_->size = 0;
	assert(mms_str_length(dest) == 0);

#ifdef use_rep_capacity
	dest->rep_->capacity = 0;
#endif
}

int mms_str_is_null(PMMS_MEM_STRING dest)
{
	if (dest->rep_ == NULL)
	{
		return 1;
	}

	return (dest->rep_ == &mms_string_nullrep_);
}

void mms_str_quit(PMMS_MEM_STRING str)
{
	if (str->rep_ == NULL)
	{
		return;
	}

	if (str->rep_ != &mms_string_nullrep_)
	{
		free(  str->rep_ );
		str->rep_ = &mms_string_nullrep_;
		mms_str_set_size(str, 0);
	}
}

void mms_str_init2(PMMS_MEM_STRING dest, int sz)
{
	mms_str_init3(dest, sz, sz);
}

void mms_str_init3(PMMS_MEM_STRING dest, int sz, int cap)
{
	int cap_dest = 0;
	int bytesNeeded = 0;
	int intsNeeded = 0;

	if (cap > 0)
	{
		if (!mms_str_is_null(dest))
		{
			cap_dest = mms_str_capacity(dest);

			if (cap_dest > cap)
			{
				dest->rep_->size = sz;
				dest->rep_->str[ sz ] = '\0';
				return;
			}
		}

		mms_str_quit(dest);
	
		bytesNeeded = sizeof(MMSSTRINGREP) + cap;
		intsNeeded = ( bytesNeeded + sizeof(int) - 1 ) / sizeof( int ); 
		intsNeeded *= sizeof (int);
		dest->rep_ = (MMSSTRINGREP*)( malloc(intsNeeded));
		dest->rep_->size = sz;
		memset(dest->rep_->str, 0, sz);
		dest->rep_->str[ sz ] = '\0';
#ifdef use_rep_capacity
		dest->rep_->capacity = cap;
#endif
	}
	else
	{
		dest->rep_ = &mms_string_nullrep_;
		dest->rep_->size = 0;
		dest->rep_->str[ 0 ] = '\0';
#ifdef use_rep_capacity
		dest->rep_->capacity = 0;
#endif
	}
}

void mms_str_set_size(PMMS_MEM_STRING dest, int sz) 
{
	if (mms_str_is_null(dest))
	{
		return;
	}

	if (mms_str_capacity(dest) < sz)
	{
		MMS_MEM_STRING tmp;
		memset(&tmp, 0, sizeof(MMS_MEM_STRING));
		mms_str_init2(&tmp, sz);
		memcpy(mms_string(&tmp), mms_string(dest), mms_str_length(dest));
		mms_str_swap(dest, &tmp);
		mms_str_quit(&tmp);
		dest->rep_->size = sz;
		dest->rep_->str[ sz ] = '\0'; 
	}
	else
	{
		dest->rep_->size = sz;
		dest->rep_->str[ sz ] = '\0'; 
	}
}

void mms_str_cat(PMMS_MEM_STRING dest, const char* str)
{
	char *pstring;
	long len;
	long cap;

	if (mms_str_is_null(dest))
	{
		mms_str_set(dest, str);
	}
	else
	{
		len = strlen(str);
		cap = len + mms_str_length(dest);
		mms_str_set_size(dest, cap);
		pstring = mms_string(dest);
		strcat(pstring, str);
	}
}

void mms_str_copy(PMMS_MEM_STRING dest, PMMS_MEM_STRING src)
{
	mms_str_assign3(dest, src);
}

void mms_str_copy2(char *dest, PMMS_MEM_STRING src)
{
	if (mms_str_is_null(src))
	{
		*dest = 0;
		return;
	}

	strcpy(dest, mms_string(src));
}

char* mms_string(PMMS_MEM_STRING dest)
{
	if (dest->rep_ == NULL)
	{
		mms_str_init(dest);
//		return mms_string_nullrep_.str;
	}
	else if (dest->rep_->size == 0)//zhouhj 20180324 有时会出现size为0时，dest->rep_->str[ 0 ] != '\0',导致保存设备数据模型的结果出错，特别是在枚举数据集后，保存设备数据模型
	{
		assert(mms_str_length(dest) == 0);
		dest->rep_->str[ 0 ] = '\0';
	}

	return dest->rep_->str;
}


void mms_str_assign (PMMS_MEM_STRING src, const char* str)
{
	mms_str_assign2(src, str, strlen(str));
}

void mms_str_assign2 (PMMS_MEM_STRING dest, const char* str, int len)
{
	int cap = mms_str_capacity(dest);

	if (len > cap || cap > 3*(len + 8))
	{
		MMS_MEM_STRING tmp;
		memset(&tmp, 0, sizeof(MMS_MEM_STRING));
		mms_str_init2(&tmp, len);
		memcpy(mms_string(&tmp), str, len);
		mms_str_swap(dest, &tmp);
		mms_str_quit(&tmp);
	}
	else
	{
		memmove(mms_string(dest), str, len);
		mms_str_set_size(dest, len);
	}
}

void mms_str_append (PMMS_MEM_STRING dest, const char* str)
{
	mms_str_append2(dest, str, strlen(str));
}

void mms_str_assign3 (PMMS_MEM_STRING dest, PMMS_MEM_STRING src)
{
	if (src->rep_ == NULL)
	{
		mms_str_quit(dest);
		return;
	}

	mms_str_assign2(dest, src->rep_->str, src->rep_->size);
}

void mms_str_append2 (PMMS_MEM_STRING dest, const char* str, int len)
{
	int size = dest->rep_->size;
	int newsize = size + len;
	int cap = mms_str_capacity(dest);

	if (newsize > cap)
	{
		mms_str_reserve (dest, cap + len);
	}

	memmove(dest->rep_->str + size, str, len);
	mms_str_set_size(dest, newsize);
}

void mms_str_append3 (PMMS_MEM_STRING dest, PMMS_MEM_STRING src)
{
	mms_str_append2(dest, mms_string(src), mms_str_length(src));
}

void mms_str_reserve (PMMS_MEM_STRING dest, int cap)
{
#ifdef use_rep_capacity
	if (cap > mms_str_capacity(dest))
#endif
	{
		MMS_MEM_STRING tmp;
		memset(&tmp, 0, sizeof(MMS_MEM_STRING));
		mms_str_init2(&tmp, cap);
		mms_str_set2(&tmp, dest->rep_->str, dest->rep_->size);
		mms_str_swap(dest, &tmp);
		mms_str_quit(&tmp);
	}
}
