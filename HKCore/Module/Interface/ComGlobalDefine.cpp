#include "Stdafx.h"
#include "ComGlobalDefine.h"

//*********************************************************************
//描述：	将ASCII字符串转换成UNICODE字符串
//参数：	
//			pszAnsi：ASCII字符串
//			pbstr：转换后的UNICODE字符串，BSTR类型
//返回：	转换的数据长度，如果为-1表示转换失败
long AnsiStrToBSTR(const char *pszAnsi,BSTR *pbstr)
{
	//如果缓冲区为空，则返回空	
	if (NULL == pszAnsi)
	{
		pbstr = NULL;
		return -1;
	}

	//决定BSTR字符串的长度
	long lStrLen = strlen(pszAnsi) + 1;
	WCHAR* wszBuf;
	wszBuf = new WCHAR [lStrLen*2];
	if (NULL == wszBuf)
	{
		pbstr = NULL;
		return -1;
	}

	//将字符串转换为Unicode.
	if (0 == MultiByteToWideChar(CP_ACP,0,pszAnsi,-1,wszBuf,lStrLen))
	{
		DWORD dwError = GetLastError();
		delete wszBuf;
		pbstr = NULL;
		return -1;
	}
	*pbstr = ::SysAllocString (wszBuf);
	delete wszBuf;
	return lStrLen;
}

//*********************************************************************
//描述：	将UNICODE字符串转换成ASCII字符串
//参数：	
//			pbstr、bstr：转换后的UNICODE字符串，BSTR类型
//			pszAnsi、strAnsi：ASCII字符串
//返回：	转换的数据长度，如果为-1表示转换失败
long BSTRToAnsiStr(BSTR *pbstr,char *pszAnsi)
{
	long lLen = wcslen(*pbstr)*2;
	WideCharToMultiByte(CP_ACP, 0, *pbstr, -1, pszAnsi, lLen, NULL, NULL);
	pszAnsi[lLen] = '\0';
	return lLen;
}

long BSTRToAnsiStr(BSTR *pbstr,CString &strAnsi)
{
	if (pbstr == NULL)
		return -1;

	return BSTRToAnsiStr(*pbstr,strAnsi);
}

long BSTRToAnsiStr(BSTR bstr,char *pszAnsi)
{
	long lLen = wcslen(bstr)*2;
	WideCharToMultiByte(CP_ACP, 0, bstr, -1, pszAnsi, lLen, NULL, NULL);
	pszAnsi[lLen] = 0;
	return lLen;
}

long BSTRToAnsiStr(BSTR bstr,char **pszAnsi)
{
	long lLen = wcslen(bstr)*2;
	*pszAnsi = new char [lLen+2];
	WideCharToMultiByte(CP_ACP, 0, bstr, -1, *pszAnsi, lLen, NULL, NULL);
	(*pszAnsi)[lLen] = 0;
	return lLen;
}

long BSTRToAnsiStr(BSTR bstr,CString &strAnsi)
{
	long lLen = wcslen(bstr)*2;
	char *pBuff = new char[lLen+1];
	memset(pBuff,0,lLen+1);
	WideCharToMultiByte(CP_ACP, 0, bstr, -1, pBuff, lLen, NULL, NULL);
	strAnsi.Format(_T("%s"),pBuff);
	delete pBuff;

	return lLen;
}



//*********************************************************************
//描述：	创建单字节(VT_I1、char)的SafeArray数据数组
//参数：	
//			nArrayLen：原始数据的长度
//			pszValBuff：源数据缓冲区地址
//			pvarBuff：安全数组指针地址，用于保存创建的安全数组的数据
//返回：	无
void CreateAndSetSafeArray_I1(long nArrayLen,char *pszValBuff,VARIANT *pvarBuff)
{
	SAFEARRAYBOUND bound[1];
	SAFEARRAY * pFilter = NULL; 
	bound[0].cElements = nArrayLen;
	bound[0].lLbound=0;
	pFilter = SafeArrayCreate(VT_I1,1,bound);
	
// 	long lIndex = 0;
// 	for(lIndex=0; lIndex<nArrayLen; lIndex++)
// 	{
// 		SafeArrayPutElement(pFilter,&lIndex,(void*)&pszValBuff[lIndex]);
// 	}	
	//2021-8-18  lijunqing  内存拷贝，提高效率
	memcpy(pFilter->pvData, pszValBuff, nArrayLen*sizeof(char));

	
	V_VT(pvarBuff) = VT_I1 | VT_ARRAY; 
	V_ARRAY(pvarBuff) = pFilter; 	
}

//*********************************************************************
//描述：	创建双字节整数(VT_I2、short)的SafeArray数据数组
//参数：	
//			nArrayLen：原始数据的长度
//			pshortValBuff：源数据缓冲区地址
//			pvarBuff：安全数组指针地址，用于保存创建的安全数组的数据
//返回：	无
void CreateAndSetSafeArray_I2(long nArrayLen,short *pshortValBuff,VARIANT *pvarBuff)
{
	SAFEARRAYBOUND bound;
	SAFEARRAY * pFilter = NULL; 
	bound.cElements = nArrayLen;
	bound.lLbound=0;
	pFilter = SafeArrayCreate(VT_I2,1,&bound);
	
// 	long lIndex = 0;
// 	for(lIndex=0; lIndex<nArrayLen; lIndex++)
// 	{
// 		SafeArrayPutElement(pFilter,&lIndex,(void*)&pshortValBuff[lIndex]);
// 	}	
	//2021-8-18  lijunqing  内存拷贝，提高效率
	memcpy(pFilter->pvData, pshortValBuff, nArrayLen*sizeof(short));

	V_VT(pvarBuff) = VT_I2 | VT_ARRAY; 
	V_ARRAY(pvarBuff) = pFilter; 	
}

//*********************************************************************
//描述：	创建四字节整数(VT_I4、long)的SafeArray数据数组
//参数：	
//			nArrayLen：原始数据的长度
//			plValBuff：源数据缓冲区地址
//			pvarBuff：安全数组指针地址，用于保存创建的安全数组的数据
//返回：	无
void CreateAndSetSafeArray_I4(long nArrayLen,long *plValBuff,VARIANT *pvarBuff)
{
	SAFEARRAYBOUND bound;
	SAFEARRAY * pFilter = NULL; 
	bound.cElements = nArrayLen;
	bound.lLbound=0;
	pFilter = SafeArrayCreate(VT_I4,1,&bound);
	
// 	long lIndex = 0;
// 	for(lIndex=0; lIndex<nArrayLen; lIndex++)
// 	{
// 		SafeArrayPutElement(pFilter,&lIndex,(void*)&plValBuff[lIndex]);
// 	}	
	//2021-8-18  lijunqing  内存拷贝，提高效率
	memcpy(pFilter->pvData, plValBuff, nArrayLen*sizeof(long));

	V_VT(pvarBuff) = VT_I4 | VT_ARRAY; 
	V_ARRAY(pvarBuff) = pFilter; 	
}

//*********************************************************************
//描述：	创建无符号单字节(VT_UI1、unsigned char)的SafeArray数据数组
//参数：	
//			nArrayLen：原始数据的长度
//			pbyteValBuff：源数据缓冲区地址
//			pvarBuff：安全数组指针地址，用于保存创建的安全数组的数据
//返回：	无
void CreateAndSetSafeArray_UI1(long nArrayLen,BYTE *pbyteValBuff,VARIANT *pvarBuff)
{
	SAFEARRAYBOUND bound[1];
	SAFEARRAY * pFilter = NULL; 
	bound[0].cElements = nArrayLen;
	bound[0].lLbound=0;
	pFilter = SafeArrayCreate(VT_UI1,1,bound);
	
// 	long lIndex = 0;
// 	for(lIndex=0; lIndex<nArrayLen; lIndex++)
// 	{
// 		SafeArrayPutElement(pFilter,&lIndex,(void*)&pbyteValBuff[lIndex]);
// 	}	
	//2021-8-18  lijunqing  内存拷贝，提高效率
	memcpy(pFilter->pvData, pbyteValBuff, nArrayLen*sizeof(BYTE));

	V_VT(pvarBuff) = VT_UI1 | VT_ARRAY; 
	V_ARRAY(pvarBuff) = pFilter; 	
}

//*********************************************************************
//描述：	创建无符号双字节整数(VT_UI2、unsigned short)的SafeArray数据数组
//参数：	
//			nArrayLen：原始数据的长度
//			pwValBuff：源数据缓冲区地址
//			pvarBuff：安全数组指针地址，用于保存创建的安全数组的数据
//返回：	无
void CreateAndSetSafeArray_UI2(long nArrayLen,WORD *pwValBuff,VARIANT *pvarBuff)
{
	SAFEARRAYBOUND bound;
	SAFEARRAY * pFilter = NULL; 
	bound.cElements = nArrayLen;
	bound.lLbound=0;
	pFilter = SafeArrayCreate(VT_UI2,1,&bound);
	
// 	long lIndex = 0;
// 	for(lIndex=0; lIndex<nArrayLen; lIndex++)
// 	{
// 		SafeArrayPutElement(pFilter,&lIndex,(void*)&pwValBuff[lIndex]);
// 	}	
	//2021-8-18  lijunqing  内存拷贝，提高效率
	memcpy(pFilter->pvData, pwValBuff, nArrayLen*sizeof(WORD));

	V_VT(pvarBuff) = VT_UI2 | VT_ARRAY; 
	V_ARRAY(pvarBuff) = pFilter; 	
}

//*********************************************************************
//描述：	创建无符号四字节整数(VT_UI4、unsigned long)的SafeArray数据数组
//参数：	
//			nArrayLen：原始数据的长度
//			pdwValBuff：源数据缓冲区地址
//			pvarBuff：安全数组指针地址，用于保存创建的安全数组的数据
//返回：	无
void CreateAndSetSafeArray_UI4(long nArrayLen,DWORD *pdwValBuff,VARIANT *pvarBuff)
{
	SAFEARRAYBOUND bound;
	SAFEARRAY * pFilter = NULL; 
	bound.cElements = nArrayLen;
	bound.lLbound = 0;
	pFilter = SafeArrayCreate(VT_UI4,1,&bound);
	
// 	long lIndex = 0;
// 	for(lIndex=0; lIndex<nArrayLen; lIndex++)
// 	{
// 		SafeArrayPutElement(pFilter,&lIndex,(void*)&pdwValBuff[lIndex]);
// 	}	
	//2021-8-18  lijunqing  内存拷贝，提高效率
	memcpy(pFilter->pvData, pdwValBuff, nArrayLen*sizeof(DWORD));

	V_VT(pvarBuff) = VT_UI4 | VT_ARRAY; 
	V_ARRAY(pvarBuff) = pFilter; 	
}

//*********************************************************************
//描述：	创建无符号四字节浮点数(VT_R4、float)的SafeArray数据数组
//参数：	
//			nArrayLen：原始数据的长度
//			pfValBuff：源数据缓冲区地址
//			pvarBuff：安全数组指针地址，用于保存创建的安全数组的数据
//返回：	无
void CreateAndSetSafeArray_R4(long nArrayLen,float *pfValBuff,VARIANT *pvarBuff)
{
	SAFEARRAYBOUND bound;
	SAFEARRAY * pFilter = NULL; 
	bound.cElements = nArrayLen;
	bound.lLbound=0;
	pFilter = SafeArrayCreate(VT_R4,1,&bound);
	
// 	long lIndex = 0;
// 	for(lIndex=0; lIndex<nArrayLen; lIndex++)
// 	{
// 		SafeArrayPutElement(pFilter,&lIndex,(void*)&pfValBuff[lIndex]);
// 	}	
	//2021-8-18  lijunqing  内存拷贝，提高效率
	memcpy(pFilter->pvData, pfValBuff, nArrayLen*sizeof(float));

	V_VT(pvarBuff) = VT_R4 | VT_ARRAY; 
	V_ARRAY(pvarBuff) = pFilter; 	
}

//*********************************************************************
//描述：	从VARIANT中获取数据，返回获取到的数据的长度	
//参数：	从单字节(VT_I1、char)的SafeArray数据数组中获取数据
//			ppszValBuff：用于返回数据的地址指针
//			pvarBuff：安全数组指针地址，存放需要获得的源数据
//返回：	无
long GetDataFromSafeArray_I1(char **ppszValBuff,VARIANT *pvarBuff)
{
	long lLBound = 0;
	long lUBound = 0;
	SAFEARRAY * pFilter = V_ARRAY(pvarBuff); 
	
	if (SafeArrayGetLBound(pFilter,1,&lLBound) != S_OK)
		return -1;
	if (SafeArrayGetUBound(pFilter,1,&lUBound) != S_OK)
		return -1;
	
	if(pvarBuff->vt !=(VT_ARRAY|VT_I1))
	{
		return -1;
	}
	
	long lIndex = 0;
	long nElements = lUBound - lLBound + 1;
	if ((*ppszValBuff) == NULL)
	{
		*ppszValBuff = new char [nElements];
		memset(*ppszValBuff,0,sizeof(char)*nElements);		
	}
	
// 	for(lIndex=lLBound; lIndex<=lUBound; lIndex++)
// 	{
// 		SafeArrayGetElement(pFilter,&lIndex,(void*)&((*ppszValBuff)[lIndex-lLBound]));
// 	}
	//2021-8-18  lijunqing  内存拷贝，提高效率
	memcpy(*ppszValBuff, pFilter->pvData, nElements *sizeof(char));

	return nElements;
}

//*********************************************************************
//描述：	从VARIANT中获取数据，返回获取到的数据的长度	
//参数：	从单字节(VT_I1、char)的SafeArray数据数组中获取数据
//			ppszValBuff：用于返回数据的地址指针
//			pvarBuff：安全数组指针地址，存放需要获得的源数据
//返回：	无
long GetDataFromSafeArray_I2(short **ppshortValBuff,VARIANT *pvarBuff)
{
	long lLBound = 0;
	long lUBound = 0;
	SAFEARRAY * pFilter = V_ARRAY(pvarBuff); 
	
	if (SafeArrayGetLBound(pFilter,1,&lLBound) != S_OK)
		return -1;
	if (SafeArrayGetUBound(pFilter,1,&lUBound) != S_OK)
		return -1;
	
	if(pvarBuff->vt !=(VT_ARRAY|VT_I2))
	{
		return -1;
	}
	
	long lIndex = 0;
	long nElements = lUBound - lLBound + 1;
	if ((*ppshortValBuff) == NULL)
	{
		*ppshortValBuff = new short [nElements];
		memset(*ppshortValBuff,0,sizeof(short)*nElements);
	}		

// 	for(lIndex=lLBound; lIndex<=lUBound; lIndex++)
// 	{
// 		SafeArrayGetElement(pFilter,&lIndex,(void*)&((*ppshortValBuff)[lIndex-lLBound]));
// 	}
	//2021-8-18  lijunqing  内存拷贝，提高效率
	memcpy(*ppshortValBuff, pFilter->pvData, nElements *sizeof(short));

	return nElements;
}

long GetDataFromSafeArray_I4(long **pplValBuff,VARIANT *pvarBuff)
{
	long lLBound = 0;
	long lUBound = 0;
	SAFEARRAY * pFilter = V_ARRAY(pvarBuff); 
	
	if (SafeArrayGetLBound(pFilter,1,&lLBound) != S_OK)
		return -1;
	if (SafeArrayGetUBound(pFilter,1,&lUBound) != S_OK)
		return -1;
	
	if(pvarBuff->vt !=(VT_ARRAY|VT_I4))
	{
		return -1;
	}
	
	long lIndex = 0;
	long nElements = lUBound - lLBound + 1;
	if ((*pplValBuff) == NULL)
	{
		*pplValBuff = new long [nElements];
		memset(*pplValBuff,0,sizeof(long)*nElements);
	}
	
// 	for(lIndex=lLBound; lIndex<=lUBound; lIndex++)
// 	{
// 		SafeArrayGetElement(pFilter,&lIndex,(void*)&((*pplValBuff)[lIndex-lLBound]));
// 	}
	//2021-8-18  lijunqing  内存拷贝，提高效率
	memcpy(*pplValBuff, pFilter->pvData, nElements *sizeof(long));

	return nElements;
}

long GetDataFromSafeArray_UI1(BYTE **ppbyteValBuff,VARIANT *pvarBuff)
{
	long lLBound = 0;
	long lUBound = 0;
	SAFEARRAY * pFilter = V_ARRAY(pvarBuff); 
	if(pvarBuff->vt !=(VT_ARRAY|VT_UI1))
	{
		return -1;
	}
	
	if (SafeArrayGetLBound(pFilter,1,&lLBound) != S_OK)
		return -1;
	if (SafeArrayGetUBound(pFilter,1,&lUBound) != S_OK)
		return -1;
	
	
	long lIndex = 0;
	long nElements = lUBound - lLBound + 1;
	if ((*ppbyteValBuff) == NULL)
	{
		*ppbyteValBuff = new BYTE [nElements];
		memset(*ppbyteValBuff,0,sizeof(BYTE)*nElements);
	}

// 	for(lIndex=lLBound; lIndex<=lUBound; lIndex++)
// 	{
// 		SafeArrayGetElement(pFilter,&lIndex,(void*)&((*ppbyteValBuff)[lIndex-lLBound]));
// 	}
	//2021-8-18  lijunqing  内存拷贝，提高效率
	memcpy(*ppbyteValBuff, pFilter->pvData, nElements *sizeof(BYTE));

	return nElements;
}

long GetDataFromSafeArray_UI2(WORD **ppwValBuff,VARIANT *pvarBuff)
{
	long lLBound = 0;
	long lUBound = 0;
	SAFEARRAY * pFilter = V_ARRAY(pvarBuff); 
	
	if (SafeArrayGetLBound(pFilter,1,&lLBound) != S_OK)
		return -1;
	if (SafeArrayGetUBound(pFilter,1,&lUBound) != S_OK)
		return -1;
	
	if(pvarBuff->vt !=(VT_ARRAY|VT_UI2))
	{
		return -1;
	}
	
	long nElements = lUBound - lLBound + 1;
	long lIndex = 0;
	if ((*ppwValBuff) == NULL)
	{
		*ppwValBuff = new WORD [nElements];
		memset(*ppwValBuff,0,sizeof(WORD)*nElements);
	}
	
// 	for(lIndex=lLBound; lIndex<=lUBound; lIndex++)
// 	{
// 		SafeArrayGetElement(pFilter,&lIndex,(void*)&((*ppwValBuff)[lIndex-lLBound]));
// 	}
	//2021-8-18  lijunqing  内存拷贝，提高效率
	memcpy(*ppwValBuff, pFilter->pvData, nElements *sizeof(WORD));

	return nElements;
}

long GetDataFromSafeArray_UI4(DWORD **ppdwValBuff,VARIANT *pvarBuff)
{
	long lLBound = 0;
	long lUBound = 0;
	SAFEARRAY * pFilter = V_ARRAY(pvarBuff); 
	
	if (SafeArrayGetLBound(pFilter,1,&lLBound) != S_OK)
		return -1;
	if (SafeArrayGetUBound(pFilter,1,&lUBound) != S_OK)
		return -1;
	
	if(pvarBuff->vt !=(VT_ARRAY|VT_UI4))
	{
		return -1;
	}
	
	long nElements = lUBound - lLBound + 1;
	long lIndex = 0;
	if (*ppdwValBuff == NULL)
	{
		*ppdwValBuff = new DWORD[nElements];
		memset(*ppdwValBuff,0,sizeof(DWORD)*nElements);
	}

// 	for(lIndex=lLBound; lIndex<=lUBound; lIndex++)
// 	{
// 		SafeArrayGetElement(pFilter,&lIndex,(void*)&((*ppdwValBuff)[lIndex-lLBound]));
// 	}
	//2021-8-18  lijunqing  内存拷贝，提高效率
	memcpy(*ppdwValBuff, pFilter->pvData, nElements *sizeof(DWORD));

	return nElements;
}

long GetDataFromSafeArray_R4(float **ppfValBuff,VARIANT *pvarBuff)
{
	long lLBound = 0;
	long lUBound = 0;
	SAFEARRAY * pFilter = V_ARRAY(pvarBuff); 
	
	if (SafeArrayGetLBound(pFilter,1,&lLBound) != S_OK)
		return -1;
	if (SafeArrayGetUBound(pFilter,1,&lUBound) != S_OK)
		return -1;
	
	if(pvarBuff->vt !=(VT_ARRAY|VT_R4))
	{
		return -1;
	}
	
	long nElements = lUBound - lLBound + 1;
	long lIndex = 0;
	if ((*ppfValBuff) == NULL)
	{
		*ppfValBuff = new float[nElements];
		memset(*ppfValBuff,0,sizeof(float)*nElements);
	}		

// 	for(lIndex=lLBound; lIndex<=lUBound; lIndex++)
// 	{
// 		SafeArrayGetElement(pFilter,&lIndex,(void*)&((*ppfValBuff)[lIndex-lLBound]));
// 	}
	//2021-8-18  lijunqing  内存拷贝，提高效率
	memcpy(*ppfValBuff, pFilter->pvData, nElements *sizeof(float));

	return nElements;
}


