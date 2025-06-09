/*
  Copyright (c) 2009 Dave Gamble
 
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:
 
  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.
 
  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  THE SOFTWARE.
*/

#ifndef CJSON__h
#define CJSON__h

#ifdef __cplusplus
extern "C"
{
#endif

/* CJSON Types: */
#define CJSON_False 0
#define CJSON_True 1
#define CJSON_NULL 2
#define CJSON_Number 3
#define CJSON_String 4
#define CJSON_Array 5
#define CJSON_Object 6

//yzj 2021-12-13 在不影响其本身的情况下加入number类型的判断
#define CJSON_Int	 30
#define CJSON_Double 31
#define CJSON_Int64  32
	
#define CJSON_IsReference 256
#define CJSON_StringIsConst 512

#ifdef _PSX_QT_LINUX_
#ifndef __int64
#define __int64 long long
#endif
#endif

/* The CJSON structure: */
typedef struct cjson {
	struct cjson *next,*prev;	/* next/prev allow you to walk array/object chains. Alternatively, use GetArraySize/GetArrayItem/GetObjectItem */
	struct cjson *child;		/* An array or object item will have a child pointer pointing to a chain of the items in the array/object. */

	int type;					/* The type of the item, as above. */
	int numType;	//加入一个新的成员用于分辨number具体指代的类型

	char *valuestring;			/* The item's string, if type==CJSON_String */
	int valueint;				/* The item's number, if type==CJSON_Number */
	double valuedouble;			/* The item's number, if type==CJSON_Number */
	__int64 valuen64;				/* The item's number, if type==CJSON_Number */

	char *string;				/* The item's name string, if this item is the child of, or is in the list of subitems of an object. */
} CJSON;

typedef struct CJSON_Hooks {
      void *(*malloc_fn)(size_t sz);
      void (*free_fn)(void *ptr);
} CJSON_Hooks;

/* Supply malloc, realloc and free functions to CJSON */
extern void CJSON_InitHooks(CJSON_Hooks* hooks);

//2022-6-23  lijunqing open json text file 
extern CJSON *CJSON_Open_File(const char *strFile);
extern long CJSON_Write_File(CJSON *item, const char *strFile);

extern CJSON *CJSON_Open_File_Utf8(const char *strFile);


/* Supply a block of JSON, and this returns a CJSON object you can interrogate. Call CJSON_Delete when finished. */
extern CJSON *CJSON_Parse(const char *value);
/* Render a CJSON entity to text for transfer/storage. Free the char* when finished. */
extern char  *CJSON_Print(CJSON *item);
/* Render a CJSON entity to text for transfer/storage without any formatting. Free the char* when finished. */
extern char  *CJSON_PrintUnformatted(CJSON *item);
/* Render a CJSON entity to text using a buffered strategy. prebuffer is a guess at the final size. guessing well reduces reallocation. fmt=0 gives unformatted, =1 gives formatted */
extern char *CJSON_PrintBuffered(CJSON *item,int prebuffer,int fmt);
/* Delete a CJSON entity and all subentities. */
extern void   CJSON_Delete(CJSON *c);

/* Returns the number of items in an array (or object). */
extern int	  CJSON_GetArraySize(CJSON *array);
/* Retrieve item number "item" from array "array". Returns NULL if unsuccessful. */
extern CJSON *CJSON_GetArrayItem(CJSON *array,int item);
/* Get item "string" from object. Case insensitive. */
extern CJSON *CJSON_GetObjectItem(CJSON *object,const char *string);

/* For analysing failed parses. This returns a pointer to the parse error. You'll probably need to look a few chars back to make sense of it. Defined when CJSON_Parse() returns 0. 0 when CJSON_Parse() succeeds. */
extern const char *CJSON_GetErrorPtr(void);
	
/* These calls create a CJSON item of the appropriate type. */
extern CJSON *CJSON_CreateNull(void);
extern CJSON *CJSON_CreateTrue(void);
extern CJSON *CJSON_CreateFalse(void);
extern CJSON *CJSON_CreateBool(int b);
extern CJSON *CJSON_CreateNumber(double num);
extern CJSON *CJSON_CreateString(const char *string);
extern CJSON *CJSON_CreateArray(void);
extern CJSON *CJSON_CreateObject(void);
extern CJSON *CJSON_CreateNumber_int64(__int64 num);

/* These utilities create an Array of count items. */
extern CJSON *CJSON_CreateIntArray(const int *numbers,int count);
extern CJSON *CJSON_CreateFloatArray(const float *numbers,int count);
extern CJSON *CJSON_CreateDoubleArray(const double *numbers,int count);
extern CJSON *CJSON_CreateStringArray(const char **strings,int count);

/* Append item to the specified array/object. */
extern void CJSON_AddItemToArray(CJSON *array, CJSON *item);
extern void	CJSON_AddItemToObject(CJSON *object,const char *string,CJSON *item);
extern void	CJSON_AddItemToObjectCS(CJSON *object,const char *string,CJSON *item);	/* Use this when string is definitely const (i.e. a literal, or as good as), and will definitely survive the CJSON object */
/* Append reference to item to the specified array/object. Use this when you want to add an existing CJSON to a new CJSON, but don't want to corrupt your existing CJSON. */
extern void CJSON_AddItemReferenceToArray(CJSON *array, CJSON *item);
extern void	CJSON_AddItemReferenceToObject(CJSON *object,const char *string,CJSON *item);

/* Remove/Detatch items from Arrays/Objects. */
extern CJSON *CJSON_DetachItemFromArray(CJSON *array,int which);
extern void   CJSON_DeleteItemFromArray(CJSON *array,int which);
extern CJSON *CJSON_DetachItemFromObject(CJSON *object,const char *string);
extern void   CJSON_DeleteItemFromObject(CJSON *object,const char *string);
	
/* Update array items. */
extern void CJSON_InsertItemInArray(CJSON *array,int which,CJSON *newitem);	/* Shifts pre-existing items to the right. */
extern void CJSON_ReplaceItemInArray(CJSON *array,int which,CJSON *newitem);
extern void CJSON_ReplaceItemInObject(CJSON *object,const char *string,CJSON *newitem);

/* Duplicate a CJSON item */
extern CJSON *CJSON_Duplicate(CJSON *item,int recurse);
/* Duplicate will create a new, identical CJSON item to the one you pass, in new memory that will
need to be released. With recurse!=0, it will duplicate any children connected to the item.
The item->next and ->prev pointers are always zero on return from Duplicate. */

/* ParseWithOpts allows you to require (and check) that the JSON is null terminated, and to retrieve the pointer to the final byte parsed. */
extern CJSON *CJSON_ParseWithOpts(const char *value,const char **return_parse_end,int require_null_terminated);

extern void CJSON_Minify(char *json);


/* Macros for creating things quickly. */
#define CJSON_AddNullToObject(object,name)		CJSON_AddItemToObject(object, name, CJSON_CreateNull())
#define CJSON_AddTrueToObject(object,name)		CJSON_AddItemToObject(object, name, CJSON_CreateTrue())
#define CJSON_AddFalseToObject(object,name)		CJSON_AddItemToObject(object, name, CJSON_CreateFalse())
#define CJSON_AddBoolToObject(object,name,b)	CJSON_AddItemToObject(object, name, CJSON_CreateBool(b))
#define CJSON_AddNumberToObject(object,name,n)	CJSON_AddItemToObject(object, name, CJSON_CreateNumber(n))
#define CJSON_AddStringToObject(object,name,s)	CJSON_AddItemToObject(object, name, CJSON_CreateString(s))
#define CJSON_AddNumber_int64ToObject(object,name,n)	CJSON_AddItemToObject(object, name, CJSON_CreateNumber_int64(n))

/* When assigning an integer value, it needs to be propagated to valuedouble too. */
#define CJSON_SetIntValue(object,val)			((object)?(object)->valueint=(object)->valuedouble=(val):(val))
#define CJSON_SetNumberValue(object,val)		((object)?(object)->valueint=(object)->valuedouble=(val):(val))

//清除数组子节点string=NULL
extern void CJSON_ClearArrayKey2(CJSON *pArrItem);
extern void CJSON_ClearArrayKey(CJSON *pNode);

extern int CJSON_GetSameItemCount(CJSON *pNode,const char *string);

//合并相同项为数组
extern void CJSON_MergeSameItemToArray(CJSON *pNode);

//lijunqing 2022-6-23 
extern long json_is_object_or_array(CJSON *item);
extern long json_cmp_object(CJSON *p1, CJSON *p2);
extern CJSON* CJSON_Copy(CJSON *pSrc);
extern CJSON* json_find_child(CJSON *item, const char *pszItemName, const char *pszItemValue);

#ifdef __cplusplus
}
#endif

#endif
