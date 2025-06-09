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

/* CJSON */
/* JSON parser in C. */

#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <float.h>
#include <limits.h>
#include <ctype.h>
#include "CJSON.h"

static const char *ep;

const char *CJSON_GetErrorPtr(void) {return ep;}

static int CJSON_strcasecmp(const char *s1,const char *s2)
{
	if (!s1) return (s1==s2)?0:1;if (!s2) return 1;
	for(; tolower(*s1) == tolower(*s2); ++s1, ++s2)	if(*s1 == 0)	return 0;
	return tolower(*(const unsigned char *)s1) - tolower(*(const unsigned char *)s2);
}

static void *(*CJSON_malloc)(size_t sz) = malloc;
static void (*CJSON_free)(void *ptr) = free;

static char* CJSON_strdup(const char* str)
{
      size_t len;
      char* copy;

      len = strlen(str) + 1;
      if (!(copy = (char*)CJSON_malloc(len))) return 0;
      memcpy(copy,str,len);
      return copy;
}

void CJSON_InitHooks(CJSON_Hooks* hooks)
{
    if (!hooks) { /* Reset hooks */
        CJSON_malloc = malloc;
        CJSON_free = free;
        return;
    }

	CJSON_malloc = (hooks->malloc_fn)?hooks->malloc_fn:malloc;
	CJSON_free	 = (hooks->free_fn)?hooks->free_fn:free;
}

/* Internal constructor. */
static CJSON *CJSON_New_Item(void)
{
	CJSON* node = (CJSON*)CJSON_malloc(sizeof(CJSON));
	if (node) memset(node,0,sizeof(CJSON));
	return node;
}

/* Delete a CJSON structure. */
void CJSON_Delete(CJSON *c)
{
	CJSON *next;
	while (c)
	{
		next=c->next;
		if (!(c->type&CJSON_IsReference) && c->child) CJSON_Delete(c->child);
		if (!(c->type&CJSON_IsReference) && c->valuestring) CJSON_free(c->valuestring);
		if (!(c->type&CJSON_StringIsConst) && c->string) CJSON_free(c->string);
		CJSON_free(c);
		c=next;
	}
}

/* Parse the input text to generate a number, and populate the result into item. */
static const char *parse_number(CJSON *item,const char *num)
{
	__int64 n=0,sign=1,scale=0;int subscale=0,signsubscale=1;
	double dValue = 1.0;

	if (*num=='-') sign=-1,num++;	/* Has sign? */
	if (*num=='0') num++;			/* is zero */
	if (*num>='1' && *num<='9')     /* Number? */
	{
		do	n=(n*10)+(*num++ -'0');
		while (*num>='0' && *num<='9');	
	}
	if (*num=='.') { item->numType = CJSON_Double; } else { item->numType = CJSON_Int; } //yzj 2021-12-13 加入具体的数值类型判断
	if (*num=='.' && num[1]>='0' && num[1]<='9') {num++;	dValue=dValue*n;	do	dValue=(dValue*10.0)+(*num++ -'0'),scale--; while (*num>='0' && *num<='9');}	/* Fractional part? */
	if (*num=='e' || *num=='E')		/* Exponent? */
	{	num++;if (*num=='+') num++;	else if (*num=='-') signsubscale=-1,num++;		/* With sign? */
		while (*num>='0' && *num<='9') subscale=(subscale*10)+(*num++ - '0');	/* Number? */
	}

	if (item->numType == CJSON_Double)
	{
		dValue=sign*dValue*pow(10.0,(scale+subscale*signsubscale));	/* number = +/- number.fraction * 10^+/- exponent */
	}
	else if(item->numType == CJSON_Int)
	{
		n=sign*n*pow(10.0,(scale+subscale*signsubscale));	/* number = +/- number.fraction * 10^+/- exponent */
		dValue = n;
	}
	
	item->valuedouble=dValue;
	item->valueint=(int)n;
	item->valuen64 = (__int64)n;
	item->type=CJSON_Number;
	return num;
}

static int pow2gt (int x)	{	--x;	x|=x>>1;	x|=x>>2;	x|=x>>4;	x|=x>>8;	x|=x>>16;	return x+1;	}

typedef struct {char *buffer; int length; int offset; } printbuffer;

static char* ensure(printbuffer *p,int needed)
{
	char *newbuffer;int newsize;
	if (!p || !p->buffer) return 0;
	needed+=p->offset;
	if (needed<=p->length) return p->buffer+p->offset;

	newsize=pow2gt(needed);
	newbuffer=(char*)CJSON_malloc(newsize);
	if (!newbuffer) {CJSON_free(p->buffer);p->length=0,p->buffer=0;return 0;}
	if (newbuffer) memcpy(newbuffer,p->buffer,p->length);
	CJSON_free(p->buffer);
	p->length=newsize;
	p->buffer=newbuffer;
	return newbuffer+p->offset;
}

static int update(printbuffer *p)
{
	char *str;
	if (!p || !p->buffer) return 0;
	str=p->buffer+p->offset;
	return p->offset+strlen(str);
}

/* Render the number nicely from the given item into a string. */
static char *print_number(CJSON *item,printbuffer *p)
{	
	char *str=0;
	double d=0.0;

	if (item->numType == CJSON_Int64)
	{
		if (p)	str=ensure(p,64);
		else	str=(char*)CJSON_malloc(64);

#ifdef _PSX_QT_LINUX_
        sprintf(str,"%lld",item->valuen64);
//        lltoa(item->valuen64,str,10);
#else
		_i64toa(item->valuen64,str,10);
#endif

		return str;
	}

	if (item->numType == CJSON_Int)
	{
		if (p)	str=ensure(p,21);
		else	str=(char*)CJSON_malloc(21);	/* 2^64+1 can be represented in 21 chars. */
		if (str)	sprintf(str,"%d",item->valueint);
		return str;
	}

	d=item->valuedouble;
	if (d==0)
	{
		if (p)	str=ensure(p,2);
		else	str=(char*)CJSON_malloc(2);	/* special case for 0. */
		if (str) strcpy(str,"0");
	}
	else if (fabs(((double)item->valueint)-d)<=DBL_EPSILON && d<=INT_MAX && d>=INT_MIN)
	{
		if (p)	str=ensure(p,21);
		else	str=(char*)CJSON_malloc(21);	/* 2^64+1 can be represented in 21 chars. */
		if (str)	sprintf(str,"%d",item->valueint);
	}
	else
	{
		if (p)	str=ensure(p,64);
		else	str=(char*)CJSON_malloc(64);	/* This is a nice tradeoff. */
		if (str)
		{
			if (fabs(floor(d)-d)<=DBL_EPSILON && fabs(d)<1.0e60)sprintf(str,"%.0f",d);
			else if (fabs(d)<1.0e-6 || fabs(d)>1.0e9)			sprintf(str,"%e",d);
			else												sprintf(str,"%f",d);
		}
	}
	return str;
}

static unsigned parse_hex4(const char *str)
{
	unsigned h=0;
	if (*str>='0' && *str<='9') h+=(*str)-'0'; else if (*str>='A' && *str<='F') h+=10+(*str)-'A'; else if (*str>='a' && *str<='f') h+=10+(*str)-'a'; else return 0;
	h=h<<4;str++;
	if (*str>='0' && *str<='9') h+=(*str)-'0'; else if (*str>='A' && *str<='F') h+=10+(*str)-'A'; else if (*str>='a' && *str<='f') h+=10+(*str)-'a'; else return 0;
	h=h<<4;str++;
	if (*str>='0' && *str<='9') h+=(*str)-'0'; else if (*str>='A' && *str<='F') h+=10+(*str)-'A'; else if (*str>='a' && *str<='f') h+=10+(*str)-'a'; else return 0;
	h=h<<4;str++;
	if (*str>='0' && *str<='9') h+=(*str)-'0'; else if (*str>='A' && *str<='F') h+=10+(*str)-'A'; else if (*str>='a' && *str<='f') h+=10+(*str)-'a'; else return 0;
	return h;
}

/* Parse the input text into an unescaped cstring, and populate item. */
static const unsigned char firstByteMark[7] = { 0x00, 0x00, 0xC0, 0xE0, 0xF0, 0xF8, 0xFC };
static const char *parse_string(CJSON *item,const char *str)
{
	const char *ptr=str+1;char *ptr2;char *out;int len=0;unsigned uc,uc2;
	if (*str!='\"') {ep=str;return 0;}	/* not a string! */
	
	while (*ptr!='\"' && *ptr && ++len) if (*ptr++ == '\\') ptr++;	/* Skip escaped quotes. */
	
	out=(char*)CJSON_malloc(len+1);	/* This is how long we need for the string, roughly. */
	if (!out) return 0;
	
	ptr=str+1;ptr2=out;
	while (*ptr!='\"' && *ptr)
	{
		if (*ptr!='\\') *ptr2++=*ptr++;
		else
		{
			ptr++;
			switch (*ptr)
			{
				case 'b': *ptr2++='\b';	break;
				case 'f': *ptr2++='\f';	break;
				case 'n': *ptr2++='\n';	break;
				case 'r': *ptr2++='\r';	break;
				case 't': *ptr2++='\t';	break;
				case 'u':	 /* transcode utf16 to utf8. */
					uc=parse_hex4(ptr+1);ptr+=4;	/* get the unicode char. */

					if ((uc>=0xDC00 && uc<=0xDFFF) || uc==0)	break;	/* check for invalid.	*/

					if (uc>=0xD800 && uc<=0xDBFF)	/* UTF16 surrogate pairs.	*/
					{
						if (ptr[1]!='\\' || ptr[2]!='u')	break;	/* missing second-half of surrogate.	*/
						uc2=parse_hex4(ptr+3);ptr+=6;
						if (uc2<0xDC00 || uc2>0xDFFF)		break;	/* invalid second-half of surrogate.	*/
						uc=0x10000 + (((uc&0x3FF)<<10) | (uc2&0x3FF));
					}

					len=4;if (uc<0x80) len=1;else if (uc<0x800) len=2;else if (uc<0x10000) len=3; ptr2+=len;
					
					switch (len) {
						case 4: *--ptr2 =((uc | 0x80) & 0xBF); uc >>= 6;
						case 3: *--ptr2 =((uc | 0x80) & 0xBF); uc >>= 6;
						case 2: *--ptr2 =((uc | 0x80) & 0xBF); uc >>= 6;
						case 1: *--ptr2 =(uc | firstByteMark[len]);
					}
					ptr2+=len;
					break;
				default:  *ptr2++=*ptr; break;
			}
			ptr++;
		}
	}
	*ptr2=0;
	if (*ptr=='\"') ptr++;
	item->valuestring=out;
	item->type=CJSON_String;
	return ptr;
}

/* Render the cstring provided to an escaped version that can be printed. */
static char *print_string_ptr(const char *str,printbuffer *p)
{
	const char *ptr;char *ptr2,*out;int len=0,flag=0;unsigned char token;
	
	for (ptr=str;*ptr;ptr++) flag|=((*ptr>0 && *ptr<32)||(*ptr=='\"')||(*ptr=='\\'))?1:0;
	if (!flag)
	{
		len=ptr-str;
		if (p) out=ensure(p,len+3);
		else		out=(char*)CJSON_malloc(len+3);
		if (!out) return 0;
		ptr2=out;*ptr2++='\"';
		strcpy(ptr2,str);
		ptr2[len]='\"';
		ptr2[len+1]=0;
		return out;
	}
	
	if (!str)
	{
		if (p)	out=ensure(p,3);
		else	out=(char*)CJSON_malloc(3);
		if (!out) return 0;
		strcpy(out,"\"\"");
		return out;
	}
	ptr=str;while ((token=*ptr) && ++len) {if (strchr("\"\\\b\f\n\r\t",token)) len++; else if (token<32) len+=5;ptr++;}
	
	if (p)	out=ensure(p,len+3);
	else	out=(char*)CJSON_malloc(len+3);
	if (!out) return 0;

	ptr2=out;ptr=str;
	*ptr2++='\"';
	while (*ptr)
	{
		if ((unsigned char)*ptr>31 && *ptr!='\"' && *ptr!='\\') *ptr2++=*ptr++;
		else
		{
			*ptr2++='\\';
			switch (token=*ptr++)
			{
				case '\\':	*ptr2++='\\';	break;
				case '\"':	*ptr2++='\"';	break;
				case '\b':	*ptr2++='b';	break;
				case '\f':	*ptr2++='f';	break;
				case '\n':	*ptr2++='n';	break;
				case '\r':	*ptr2++='r';	break;
				case '\t':	*ptr2++='t';	break;
				default: sprintf(ptr2,"u%04x",token);ptr2+=5;	break;	/* escape and print */
			}
		}
	}
	*ptr2++='\"';*ptr2++=0;
	return out;
}
/* Invote print_string_ptr (which is useful) on an item. */
static char *print_string(CJSON *item,printbuffer *p)	{return print_string_ptr(item->valuestring,p);}

/* Predeclare these prototypes. */
static const char *parse_value(CJSON *item,const char *value);
static char *print_value(CJSON *item,int depth,int fmt,printbuffer *p);
static const char *parse_array(CJSON *item,const char *value);
static char *print_array(CJSON *item,int depth,int fmt,printbuffer *p);
static const char *parse_object(CJSON *item,const char *value);
static char *print_object(CJSON *item,int depth,int fmt,printbuffer *p);

/* Utility to jump whitespace and cr/lf */
static const char *skip(const char *in) {while (in && *in && (unsigned char)*in<=32) in++; return in;}

/* Parse an object - create a new root, and populate. */
CJSON *CJSON_ParseWithOpts(const char *value,const char **return_parse_end,int require_null_terminated)
{
	const char *end=0;
	CJSON *c=CJSON_New_Item();
	ep=0;
	if (!c) return 0;       /* memory fail */

	end=parse_value(c,skip(value));
	if (!end)	{CJSON_Delete(c);return 0;}	/* parse failure. ep is set. */

	/* if we require null-terminated JSON without appended garbage, skip and then check for a null terminator */
	if (require_null_terminated) {end=skip(end);if (*end) {CJSON_Delete(c);ep=end;return 0;}}
	if (return_parse_end) *return_parse_end=end;
	return c;
}


CJSON *CJSON_Open_File(const char *strFile)
{
	int file_size = 0, nRead = 0;
	char *pBuf = NULL;
	CJSON *fileJson = NULL;
	FILE *fp = fopen(strFile, "rb");

	if (fp == NULL)
	{
		return NULL;
	}

	file_size = 0;
	fseek( fp,0,SEEK_END );
	//获取文件的大小
	file_size=ftell(fp);

	if (file_size <= 0)
	{
		fclose(fp);
		return NULL;
	}

	pBuf = malloc(file_size+2);
	pBuf[file_size] = 0;
	pBuf[file_size+1] = 0;

	fseek( fp,0,SEEK_SET );
	nRead = fread(pBuf, 1,file_size,  fp);
	fclose(fp);

	if (nRead != file_size)
	{
		free(pBuf);
		return NULL;
	}

	fileJson = CJSON_Parse(pBuf);
	free(pBuf);

	return fileJson;
}

long CJSON_Write_File(CJSON *item, const char *strFile)
{
	FILE *fp = fopen(strFile, "w+b");
	char *pBuf = NULL;
	int nLen=0, nWrite=0;

	if (fp == NULL)
	{
		return 0;
	}

	pBuf = CJSON_Print(item);

	if (pBuf == NULL)
	{
		return 0;
	}

	nLen = strlen(pBuf);
	fseek( fp,0,SEEK_SET );
	nWrite = fwrite(pBuf, 1, nLen, fp);
	free(pBuf);
	fclose(fp);

	return 1;
}

CJSON *CJSON_Open_File_Utf8(const char *strFile)
{
	return NULL;
}

/* Default options for CJSON_Parse */
CJSON *CJSON_Parse(const char *value) {return CJSON_ParseWithOpts(value,0,0);}

/* Render a CJSON item/entity/structure to text. */
char *CJSON_Print(CJSON *item)				{return print_value(item,0,1,0);}
char *CJSON_PrintUnformatted(CJSON *item)	{return print_value(item,0,0,0);}

char *CJSON_PrintBuffered(CJSON *item,int prebuffer,int fmt)
{
	printbuffer p;
	p.buffer=(char*)CJSON_malloc(prebuffer);
	p.length=prebuffer;
	p.offset=0;
	return print_value(item,0,fmt,&p);
	return p.buffer;
}


/* Parser core - when encountering text, process appropriately. */
static const char *parse_value(CJSON *item,const char *value)
{
	if (!value)						return 0;	/* Fail on null. */
	if (!strncmp(value,"null",4))	{ item->type=CJSON_NULL;  return value+4; }
	if (!strncmp(value,"false",5))	{ item->type=CJSON_False; return value+5; }
	if (!strncmp(value,"true",4))	{ item->type=CJSON_True; item->valueint=1;	item->valuen64=1;	return value+4; }
	if (*value=='\"')				{ return parse_string(item,value); }
	if (*value=='-' || (*value>='0' && *value<='9'))	{ return parse_number(item,value); }
	if (*value=='[')				{ return parse_array(item,value); }
	if (*value=='{')				{ return parse_object(item,value); }

	ep=value;return 0;	/* failure. */
}

/* Render a value to text. */
static char *print_value(CJSON *item,int depth,int fmt,printbuffer *p)
{
	char *out=0;
	if (!item) return 0;
	if (p)
	{
		switch ((item->type)&255)
		{
			case CJSON_NULL:	{out=ensure(p,5);	if (out) strcpy(out,"null");	break;}
			case CJSON_False:	{out=ensure(p,6);	if (out) strcpy(out,"false");	break;}
			case CJSON_True:	{out=ensure(p,5);	if (out) strcpy(out,"true");	break;}
			case CJSON_Number:	out=print_number(item,p);break;
			case CJSON_String:	out=print_string(item,p);break;
			case CJSON_Array:	out=print_array(item,depth,fmt,p);break;
			case CJSON_Object:	out=print_object(item,depth,fmt,p);break;
		}
	}
	else
	{
		switch ((item->type)&255)
		{
			case CJSON_NULL:	out=CJSON_strdup("null");	break;
			case CJSON_False:	out=CJSON_strdup("false");break;
			case CJSON_True:	out=CJSON_strdup("true"); break;
			case CJSON_Number:	out=print_number(item,0);break;
			case CJSON_String:	out=print_string(item,0);break;
			case CJSON_Array:	out=print_array(item,depth,fmt,0);break;
			case CJSON_Object:	out=print_object(item,depth,fmt,0);break;
		}
	}
	return out;
}

/* Build an array from input text. */
static const char *parse_array(CJSON *item,const char *value)
{
	CJSON *child;
	if (*value!='[')	{ep=value;return 0;}	/* not an array! */

	item->type=CJSON_Array;
	value=skip(value+1);
	if (*value==']') return value+1;	/* empty array. */

	item->child=child=CJSON_New_Item();
	if (!item->child) return 0;		 /* memory fail */
	value=skip(parse_value(child,skip(value)));	/* skip any spacing, get the value. */
	if (!value) return 0;

	while (*value==',')
	{
		CJSON *new_item;
		if (!(new_item=CJSON_New_Item())) return 0; 	/* memory fail */
		child->next=new_item;new_item->prev=child;child=new_item;
		value=skip(parse_value(child,skip(value+1)));
		if (!value) return 0;	/* memory fail */
	}

	if (*value==']') return value+1;	/* end of array */
	ep=value;return 0;	/* malformed. */
}

/* Render an array to text */
static char *print_array(CJSON *item,int depth,int fmt,printbuffer *p)
{
	char **entries;
	char *out=0,*ptr,*ret;int len=5;
	CJSON *child=item->child;
	int numentries=0,i=0,fail=0;
	size_t tmplen=0;
	
	/* How many entries in the array? */
	while (child) numentries++,child=child->next;
	/* Explicitly handle numentries==0 */
	if (!numentries)
	{
		if (p)	out=ensure(p,3);
		else	out=(char*)CJSON_malloc(3);
		if (out) strcpy(out,"[]");
		return out;
	}

	if (p)
	{
		/* Compose the output array. */
		i=p->offset;
		ptr=ensure(p,1);if (!ptr) return 0;	*ptr='[';	p->offset++;
		child=item->child;
		while (child && !fail)
		{
			print_value(child,depth+1,fmt,p);
			p->offset=update(p);
			if (child->next) {len=fmt?2:1;ptr=ensure(p,len+1);if (!ptr) return 0;*ptr++=',';if(fmt)*ptr++=' ';*ptr=0;p->offset+=len;}
			child=child->next;
		}
		ptr=ensure(p,2);if (!ptr) return 0;	*ptr++=']';*ptr=0;
		out=(p->buffer)+i;
	}
	else
	{
		/* Allocate an array to hold the values for each */
		entries=(char**)CJSON_malloc(numentries*sizeof(char*));
		if (!entries) return 0;
		memset(entries,0,numentries*sizeof(char*));
		/* Retrieve all the results: */
		child=item->child;
		while (child && !fail)
		{
			ret=print_value(child,depth+1,fmt,0);
			entries[i++]=ret;
			if (ret) len+=strlen(ret)+2+(fmt?1:0); else fail=1;
			child=child->next;
		}
		
		/* If we didn't fail, try to malloc the output string */
		if (!fail)	out=(char*)CJSON_malloc(len);
		/* If that fails, we fail. */
		if (!out) fail=1;

		/* Handle failure. */
		if (fail)
		{
			for (i=0;i<numentries;i++) if (entries[i]) CJSON_free(entries[i]);
			CJSON_free(entries);
			return 0;
		}
		
		/* Compose the output array. */
		*out='[';
		ptr=out+1;*ptr=0;
		for (i=0;i<numentries;i++)
		{
			tmplen=strlen(entries[i]);memcpy(ptr,entries[i],tmplen);ptr+=tmplen;
			if (i!=numentries-1) {*ptr++=',';if(fmt)*ptr++=' ';*ptr=0;}
			CJSON_free(entries[i]);
		}
		CJSON_free(entries);
		*ptr++=']';*ptr++=0;
	}
	return out;	
}

/* Build an object from the text. */
static const char *parse_object(CJSON *item,const char *value)
{
	CJSON *child;
	if (*value!='{')	{ep=value;return 0;}	/* not an object! */
	
	item->type=CJSON_Object;
	value=skip(value+1);
	if (*value=='}') return value+1;	/* empty array. */
	
	item->child=child=CJSON_New_Item();
	if (!item->child) return 0;
	value=skip(parse_string(child,skip(value)));
	if (!value) return 0;
	child->string=child->valuestring;child->valuestring=0;
	if (*value!=':') {ep=value;return 0;}	/* fail! */
	value=skip(parse_value(child,skip(value+1)));	/* skip any spacing, get the value. */
	if (!value) return 0;
	
	while (*value==',')
	{
		CJSON *new_item;
		if (!(new_item=CJSON_New_Item()))	return 0; /* memory fail */
		child->next=new_item;new_item->prev=child;child=new_item;
		value=skip(parse_string(child,skip(value+1)));
		if (!value) return 0;
		child->string=child->valuestring;child->valuestring=0;
		if (*value!=':') {ep=value;return 0;}	/* fail! */
		value=skip(parse_value(child,skip(value+1)));	/* skip any spacing, get the value. */
		if (!value) return 0;
	}
	
	if (*value=='}') return value+1;	/* end of array */
	ep=value;return 0;	/* malformed. */
}

/* Render an object to text. */
static char *print_object(CJSON *item,int depth,int fmt,printbuffer *p)
{
	char **entries=0,**names=0;
	char *out=0,*ptr,*ret,*str;int len=7,i=0,j;
	CJSON *child=item->child;
	int numentries=0,fail=0;
	size_t tmplen=0;
	/* Count the number of entries. */
	while (child) numentries++,child=child->next;
	/* Explicitly handle empty object case */
	if (!numentries)
	{
		if (p) out=ensure(p,fmt?depth+4:3);
		else	out=(char*)CJSON_malloc(fmt?depth+4:3);
		if (!out)	return 0;
		ptr=out;*ptr++='{';
		if (fmt) {*ptr++='\n';for (i=0;i<depth-1;i++) *ptr++='\t';}
		*ptr++='}';*ptr++=0;
		return out;
	}
	if (p)
	{
		/* Compose the output: */
		i=p->offset;
		len=fmt?2:1;	ptr=ensure(p,len+1);	if (!ptr) return 0;
		*ptr++='{';	if (fmt) *ptr++='\n';	*ptr=0;	p->offset+=len;
		child=item->child;depth++;
		while (child)
		{
			if (fmt)
			{
				ptr=ensure(p,depth);	if (!ptr) return 0;
				for (j=0;j<depth;j++) *ptr++='\t';
				p->offset+=depth;
			}
			print_string_ptr(child->string,p);
			p->offset=update(p);
			
			len=fmt?2:1;
			ptr=ensure(p,len);	if (!ptr) return 0;
			*ptr++=':';if (fmt) *ptr++='\t';
			p->offset+=len;
			
			print_value(child,depth,fmt,p);
			p->offset=update(p);

			len=(fmt?1:0)+(child->next?1:0);
			ptr=ensure(p,len+1); if (!ptr) return 0;
			if (child->next) *ptr++=',';
			if (fmt) *ptr++='\n';*ptr=0;
			p->offset+=len;
			child=child->next;
		}
		ptr=ensure(p,fmt?(depth+1):2);	 if (!ptr) return 0;
		if (fmt)	for (i=0;i<depth-1;i++) *ptr++='\t';
		*ptr++='}';*ptr=0;
		out=(p->buffer)+i;
	}
	else
	{
		/* Allocate space for the names and the objects */
		entries=(char**)CJSON_malloc(numentries*sizeof(char*));
		if (!entries) return 0;
		names=(char**)CJSON_malloc(numentries*sizeof(char*));
		if (!names) {CJSON_free(entries);return 0;}
		memset(entries,0,sizeof(char*)*numentries);
		memset(names,0,sizeof(char*)*numentries);

		/* Collect all the results into our arrays: */
		child=item->child;depth++;if (fmt) len+=depth;
		while (child)
		{
			names[i]=str=print_string_ptr(child->string,0);
			entries[i++]=ret=print_value(child,depth,fmt,0);
			if (str && ret) len+=strlen(ret)+strlen(str)+2+(fmt?2+depth:0); else fail=1;
			child=child->next;
		}
		
		/* Try to allocate the output string */
		if (!fail)	out=(char*)CJSON_malloc(len);
		if (!out) fail=1;

		/* Handle failure */
		if (fail)
		{
			for (i=0;i<numentries;i++) {if (names[i]) CJSON_free(names[i]);if (entries[i]) CJSON_free(entries[i]);}
			CJSON_free(names);CJSON_free(entries);
			return 0;
		}
		
		/* Compose the output: */
		*out='{';ptr=out+1;if (fmt)*ptr++='\n';*ptr=0;
		for (i=0;i<numentries;i++)
		{
			if (fmt) for (j=0;j<depth;j++) *ptr++='\t';
			tmplen=strlen(names[i]);memcpy(ptr,names[i],tmplen);ptr+=tmplen;
			*ptr++=':';if (fmt) *ptr++='\t';
			strcpy(ptr,entries[i]);ptr+=strlen(entries[i]);
			if (i!=numentries-1) *ptr++=',';
			if (fmt) *ptr++='\n';*ptr=0;
			CJSON_free(names[i]);CJSON_free(entries[i]);
		}
		
		CJSON_free(names);CJSON_free(entries);
		if (fmt) for (i=0;i<depth-1;i++) *ptr++='\t';
		*ptr++='}';*ptr++=0;
	}
	return out;	
}

/* Get Array size/item / object item. */
int    CJSON_GetArraySize(CJSON *array)							{CJSON *c=array->child;int i=0;while(c)i++,c=c->next;return i;}
CJSON *CJSON_GetArrayItem(CJSON *array,int item)				{CJSON *c=array->child;  while (c && item>0) item--,c=c->next; return c;}
CJSON *CJSON_GetObjectItem(CJSON *object,const char *string)	{CJSON *c=object->child; while (c && CJSON_strcasecmp(c->string,string)) c=c->next; return c;}

/* Utility for array list handling. */
static void suffix_object(CJSON *prev,CJSON *item) {prev->next=item;item->prev=prev;}
/* Utility for handling references. */
static CJSON *create_reference(CJSON *item) {CJSON *ref=CJSON_New_Item();if (!ref) return 0;memcpy(ref,item,sizeof(CJSON));ref->string=0;ref->type|=CJSON_IsReference;ref->next=ref->prev=0;return ref;}

/* Add item to array/object. */
void   CJSON_AddItemToArray(CJSON *array, CJSON *item)						{CJSON *c=array->child;if (!item) return; if (!c) {array->child=item;} else {while (c && c->next) c=c->next; suffix_object(c,item);}}
void   CJSON_AddItemToObject(CJSON *object,const char *string,CJSON *item)	{if (!item) return; if (item->string) CJSON_free(item->string);item->string=CJSON_strdup(string);CJSON_AddItemToArray(object,item);}
void   CJSON_AddItemToObjectCS(CJSON *object,const char *string,CJSON *item)	{if (!item) return; if (!(item->type&CJSON_StringIsConst) && item->string) CJSON_free(item->string);item->string=(char*)string;item->type|=CJSON_StringIsConst;CJSON_AddItemToArray(object,item);}
void	CJSON_AddItemReferenceToArray(CJSON *array, CJSON *item)						{CJSON_AddItemToArray(array,create_reference(item));}
void	CJSON_AddItemReferenceToObject(CJSON *object,const char *string,CJSON *item)	{CJSON_AddItemToObject(object,string,create_reference(item));}

CJSON *CJSON_DetachItemFromArray(CJSON *array,int which)			{CJSON *c=array->child;while (c && which>0) c=c->next,which--;if (!c) return 0;
	if (c->prev) c->prev->next=c->next;if (c->next) c->next->prev=c->prev;if (c==array->child) array->child=c->next;c->prev=c->next=0;return c;}
void   CJSON_DeleteItemFromArray(CJSON *array,int which)			{CJSON_Delete(CJSON_DetachItemFromArray(array,which));}
CJSON *CJSON_DetachItemFromObject(CJSON *object,const char *string) {int i=0;CJSON *c=object->child;while (c && CJSON_strcasecmp(c->string,string)) i++,c=c->next;if (c) return CJSON_DetachItemFromArray(object,i);return 0;}
void   CJSON_DeleteItemFromObject(CJSON *object,const char *string) {CJSON_Delete(CJSON_DetachItemFromObject(object,string));}

/* Replace array/object items with new ones. */
void   CJSON_InsertItemInArray(CJSON *array,int which,CJSON *newitem)		{CJSON *c=array->child;while (c && which>0) c=c->next,which--;if (!c) {CJSON_AddItemToArray(array,newitem);return;}
	newitem->next=c;newitem->prev=c->prev;c->prev=newitem;if (c==array->child) array->child=newitem; else newitem->prev->next=newitem;}
void   CJSON_ReplaceItemInArray(CJSON *array,int which,CJSON *newitem)		{CJSON *c=array->child;while (c && which>0) c=c->next,which--;if (!c) return;
	newitem->next=c->next;newitem->prev=c->prev;if (newitem->next) newitem->next->prev=newitem;
	if (c==array->child) array->child=newitem; else newitem->prev->next=newitem;c->next=c->prev=0;CJSON_Delete(c);}
void   CJSON_ReplaceItemInObject(CJSON *object,const char *string,CJSON *newitem){int i=0;CJSON *c=object->child;while(c && CJSON_strcasecmp(c->string,string))i++,c=c->next;if(c){newitem->string=CJSON_strdup(string);CJSON_ReplaceItemInArray(object,i,newitem);}}

/* Create basic types: */
CJSON *CJSON_CreateNull(void)					{CJSON *item=CJSON_New_Item();if(item)item->type=CJSON_NULL;return item;}
CJSON *CJSON_CreateTrue(void)					{CJSON *item=CJSON_New_Item();if(item)item->type=CJSON_True;return item;}
CJSON *CJSON_CreateFalse(void)					{CJSON *item=CJSON_New_Item();if(item)item->type=CJSON_False;return item;}
CJSON *CJSON_CreateBool(int b)					{CJSON *item=CJSON_New_Item();if(item)item->type=b?CJSON_True:CJSON_False;return item;}
CJSON *CJSON_CreateNumber(double num)			{CJSON *item=CJSON_New_Item();if(item){item->type=CJSON_Number;item->valuedouble=num;item->valueint=(int)num;item->valuen64=(__int64)num;}return item;}
CJSON *CJSON_CreateString(const char *string)	{CJSON *item=CJSON_New_Item();if(item){item->type=CJSON_String;item->valuestring=CJSON_strdup(string);}return item;}
CJSON *CJSON_CreateArray(void)					{CJSON *item=CJSON_New_Item();if(item)item->type=CJSON_Array;return item;}
CJSON *CJSON_CreateObject(void)					{CJSON *item=CJSON_New_Item();if(item)item->type=CJSON_Object;return item;}
CJSON *CJSON_CreateNumber_int64(__int64 num)	{CJSON *item=CJSON_New_Item();if(item){item->type=CJSON_Number;item->numType=CJSON_Int64;item->valuedouble=num;item->valueint=(int)num;item->valuen64=num;}return item;}

/* Create Arrays: */
CJSON *CJSON_CreateIntArray(const int *numbers,int count)		{int i;CJSON *n=0,*p=0,*a=CJSON_CreateArray();for(i=0;a && i<count;i++){n=CJSON_CreateNumber(numbers[i]);if(!i)a->child=n;else suffix_object(p,n);p=n;}return a;}
CJSON *CJSON_CreateFloatArray(const float *numbers,int count)	{int i;CJSON *n=0,*p=0,*a=CJSON_CreateArray();for(i=0;a && i<count;i++){n=CJSON_CreateNumber(numbers[i]);if(!i)a->child=n;else suffix_object(p,n);p=n;}return a;}
CJSON *CJSON_CreateDoubleArray(const double *numbers,int count)	{int i;CJSON *n=0,*p=0,*a=CJSON_CreateArray();for(i=0;a && i<count;i++){n=CJSON_CreateNumber(numbers[i]);if(!i)a->child=n;else suffix_object(p,n);p=n;}return a;}
CJSON *CJSON_CreateStringArray(const char **strings,int count)	{int i;CJSON *n=0,*p=0,*a=CJSON_CreateArray();for(i=0;a && i<count;i++){n=CJSON_CreateString(strings[i]);if(!i)a->child=n;else suffix_object(p,n);p=n;}return a;}

/* Duplication */
CJSON *CJSON_Duplicate(CJSON *item,int recurse)
{
	CJSON *newitem,*cptr,*nptr=0,*newchild;
	/* Bail on bad ptr */
	if (!item) return 0;
	/* Create new item */
	newitem=CJSON_New_Item();
	if (!newitem) return 0;
	/* Copy over all vars */
	newitem->type=item->type&(~CJSON_IsReference),newitem->valueint=item->valueint,newitem->valuen64=item->valuen64,newitem->valuedouble=item->valuedouble;
	if (item->valuestring)	{newitem->valuestring=CJSON_strdup(item->valuestring);	if (!newitem->valuestring)	{CJSON_Delete(newitem);return 0;}}
	if (item->string)		{newitem->string=CJSON_strdup(item->string);			if (!newitem->string)		{CJSON_Delete(newitem);return 0;}}
	/* If non-recursive, then we're done! */
	if (!recurse) return newitem;
	/* Walk the ->next chain for the child. */
	cptr=item->child;
	while (cptr)
	{
		newchild=CJSON_Duplicate(cptr,1);		/* Duplicate (with recurse) each item in the ->next chain */
		if (!newchild) {CJSON_Delete(newitem);return 0;}
		if (nptr)	{nptr->next=newchild,newchild->prev=nptr;nptr=newchild;}	/* If newitem->child already set, then crosswire ->prev and ->next and move on */
		else		{newitem->child=newchild;nptr=newchild;}					/* Set newitem->child and move to it */
		cptr=cptr->next;
	}
	return newitem;
}

void CJSON_Minify(char *json)
{
	char *into=json;
	while (*json)
	{
		if (*json==' ') json++;
		else if (*json=='\t') json++;	/* Whitespace characters. */
		else if (*json=='\r') json++;
		else if (*json=='\n') json++;
		else if (*json=='/' && json[1]=='/')  while (*json && *json!='\n') json++;	/* double-slash comments, to end of line. */
		else if (*json=='/' && json[1]=='*') {while (*json && !(*json=='*' && json[1]=='/')) json++;json+=2;}	/* multiline comments. */
		else if (*json=='\"'){*into++=*json++;while (*json && *json!='\"'){if (*json=='\\') *into++=*json++;*into++=*json++;}*into++=*json++;} /* string literals, which are \" sensitive. */
		else *into++=*json++;			/* All other characters. */
	}
	*into=0;	/* and null-terminate. */
}

// void CJSON_ClearArrayKey(CJSON *pNode)
// {
// 	CJSON *pChild = NULL;
// 	CJSON *p = NULL;
// 	int nArraySize = 0;
// 	int i=0;
// 
// 	if (pNode == NULL)
// 	{
// 		return;
// 	}
// 
// 	if (pNode->type != CJSON_Object)
// 	{
// 		return;
// 	}
// 
// 	pChild = pNode->child;
// 	
// 	while(pChild != NULL)
// 	{
// 		if (pChild->type == CJSON_Array)
// 		{
// 			nArraySize = CJSON_GetArraySize(pChild);
// 
// 			for (i=0; i<nArraySize; i++)
// 			{
// 				p = CJSON_GetArrayItem(pChild,i);
// 				p->string = NULL;
// 
// 				CJSON_ClearArrayKey(p);
// 			}
// 		}
// 		else
// 		{
// 			CJSON_ClearArrayKey(pChild);
// 		}
// 
// 		pChild = pChild->next;
// 	}
// }

void CJSON_ClearArrayKey2(CJSON *pArrItem)
{//清除数组子节点string=NULL
	CJSON *p = NULL;
	int i = 0;
	int nArraySize = CJSON_GetArraySize(pArrItem);

	for (i=0; i<nArraySize; i++)
	{
		p = CJSON_GetArrayItem(pArrItem,i);
		p->string = NULL;

		CJSON_ClearArrayKey(p);
	}
}

void CJSON_ClearArrayKey(CJSON *pNode)
{
	CJSON *pChild = NULL;

	if (pNode == NULL)
	{
		return;
	}

	if (pNode->type == CJSON_Array)
	{
		CJSON_ClearArrayKey2(pNode);

		return;
	}

	if (pNode->type != CJSON_Object)
	{
		return;
	}

	pChild = pNode->child;

	while(pChild != NULL)
	{
		if (pChild->type == CJSON_Array)
		{
			CJSON_ClearArrayKey2(pChild);
		}
		else
		{
			CJSON_ClearArrayKey(pChild);
		}

		pChild = pChild->next;
	}
}

int CJSON_GetSameItemCount(CJSON *pNode,const char *string)
{
	CJSON *pChild = NULL;
	int nRetCnt = 0;

	pChild = pNode->child;

	while(pChild != NULL)
	{
		if (!CJSON_strcasecmp(pChild->string,string))
		{
			if ((pChild->type == CJSON_Object) || (pChild->type == CJSON_Array))
			{
				nRetCnt++;
			}
		}

		pChild = pChild->next;
	}

	return nRetCnt;
}

//合并相同项为数组
void CJSON_MergeSameItemToArray(CJSON *pNode)
{
	CJSON *pChild = NULL;
	CJSON *pItem = NULL;
	CJSON *pArrItems = NULL;
	int nSameCnt = 0;
	int nIndex = 0,j=0;
	int nArraySize2 = 0;

	if (pNode == NULL)
	{
		return;
	}

	if (pNode->type == CJSON_Array)
	{
		nArraySize2 = CJSON_GetArraySize(pNode);
		for (j=0; j<nArraySize2; j++)
		{
			pItem = CJSON_GetArrayItem(pNode,j);
			CJSON_MergeSameItemToArray(pItem);
		}
		return;
	}

	if (pNode->type != CJSON_Object)
	{
		return;
	}

	pChild = pNode->child;

	while(pChild != NULL)
	{
		if ((pChild->type == CJSON_Object) || (pChild->type == CJSON_Array))
		{
			pArrItems = NULL;
			nSameCnt = CJSON_GetSameItemCount(pNode,pChild->string);

			if (nSameCnt == 1)
			{
				CJSON_MergeSameItemToArray(pChild);
			}
			else
			{
				pArrItems = CJSON_CreateArray();
				pArrItems->string = CJSON_strdup(pChild->string);

				while((pItem = CJSON_DetachItemFromObject(pNode,pArrItems->string)) != NULL)
				{
					if (pItem->type == CJSON_Object)
					{
						//将数组子对象key清空
						if (pItem->string != NULL)
						{
							CJSON_free(pItem->string);
							pItem->string = NULL;
						}

						CJSON_AddItemToArray(pArrItems, pItem);
					}
					else if (pItem->type == CJSON_Array)
					{
						nArraySize2 = CJSON_GetArraySize(pItem);
						for (j=0; j<nArraySize2; j++)
						{
							pChild = CJSON_DetachItemFromArray(pItem,j);

							//将数组子对象key清空
							if (pChild->string != NULL)
							{
								CJSON_free(pChild->string);
								pChild->string = NULL;
							}
							
							CJSON_AddItemToArray(pArrItems, pChild);
						}
						CJSON_Delete(pItem);
					}
				}

				CJSON_InsertItemInArray(pNode,nIndex,pArrItems);
				pChild = pArrItems;

				CJSON_MergeSameItemToArray(pArrItems);	
			}
		}

		pChild = pChild->next;
		nIndex++;
	}
}


//

long json_is_object_or_array(CJSON *item)
{
	switch ((item->type)&255)
	{
	case CJSON_Array:	
		return 1;

	case CJSON_Object:	
		return 1;
	}

	return 0;
}


long json_cmp_object(CJSON *p1, CJSON *p2)
{
	CJSON *child1 = NULL;
	CJSON *child2 = NULL;

	if (p1->type != p1->type)
	{
		return 0;
	}

	if (p1->string != NULL && p2->string != NULL)
	{
		if (strcmp(p1->string, p2->string) != 0)
		{
			return 0;
		}
	}

	if ( (p1->string != NULL && p2->string == NULL)
		||  (p1->string == NULL && p2->string != NULL))
	{
		return 0;
	}

	if (p1->valuestring != NULL && p2->valuestring != NULL)
	{
		if (strcmp(p1->valuestring, p2->valuestring) != 0)
		{
			return 0;
		}
	}

	if ( (p1->valuestring != NULL && p2->valuestring == NULL)
		||  (p1->valuestring == NULL && p2->valuestring != NULL))
	{
		return 0;
	}

	child1 = p1->child;
	child2 = NULL;

	//比较子对象
	while (child1)
	{
		if (json_is_object_or_array(child1) )
		{
			child1 = child1->next;
			continue;
		}

		child2 = CJSON_GetObjectItem (p2, child1->string);

		if (json_cmp_object(child1, child2) == 0)
		{
			return 0;
		}

		child1 = child1->next;
	}

	return 1;
}

CJSON* CJSON_Copy(CJSON *pSrc)
{
	CJSON *pNew = CJSON_Duplicate(pSrc, 0);

	CJSON *child = pSrc->child;

	while (child != NULL)
	{
		if (json_is_object_or_array(child) == 0) //相同的子元素，表示此对象的父对象已经创建
		{
			CJSON *p = CJSON_Duplicate(child, 0);
			CJSON_AddItemToArray(pNew, p);
		}

		child = child->next;
	}

	return pNew;
}

/* Render an array to text */
CJSON* json_find_child_array(CJSON *item,const char *pszItemName, const char *pszItemValue)
{
	char **entries;
	char *out=0,*ptr,*ret;int len=5;
	CJSON *child=item->child;
	int numentries=0,i=0,fail=0;
	size_t tmplen=0;
	CJSON *pFind = NULL;

	child=item->child;

	while (child && !fail)
	{
		if (json_is_object_or_array(child))
		{
			pFind = json_find_child(child, pszItemName, pszItemValue);

			if (pFind != NULL)
			{
				break;
			}
		}

		child=child->next;
	}

	return pFind;
}



/* Render an object to text. */
CJSON* json_find_child_object(CJSON *item,const char *pszItemName, const char *pszItemValue)
{
	CJSON *child=item->child;
	CJSON *pFind = NULL;

	child=item->child;

	while (child)
	{
		if (child->string != NULL)
		{
			if (strcmp(child->string, pszItemName) == 0)
			{
				if (child->type == CJSON_String)
				{
					if (strcmp(child->valuestring, pszItemValue) == 0)
					{
						return item;
					}
				}
			}
		}

		if (json_is_object_or_array(child))
		{
			pFind = json_find_child(child,pszItemName,pszItemValue);

			if (pFind != NULL)
			{
				break;
			}
		}

		child=child->next;
	}

	return pFind;
}


CJSON* json_find_child(CJSON *item, const char *pszItemName, const char *pszItemValue)
{
	if (!item) return 0;

	switch ((item->type)&255)
	{

	case CJSON_Array:	
		return json_find_child_array(item,pszItemName,pszItemValue);

	case CJSON_Object:	
		return json_find_child_object(item,pszItemName,pszItemValue);
	}

	return NULL;
}
