#include "Stdafx.h"
#include "ComGlobalDefine.h"

//*********************************************************************
//������	��ASCII�ַ���ת����UNICODE�ַ���
//������	
//			pszAnsi��ASCII�ַ���
//			pbstr��ת�����UNICODE�ַ�����BSTR����
//���أ�	ת�������ݳ��ȣ����Ϊ-1��ʾת��ʧ��
long AnsiStrToBSTR(const char *pszAnsi,BSTR *pbstr)
{
	//���������Ϊ�գ��򷵻ؿ�	
	if (NULL == pszAnsi)
	{
		pbstr = NULL;
		return -1;
	}

	//����BSTR�ַ����ĳ���
	long lStrLen = strlen(pszAnsi) + 1;
	WCHAR* wszBuf;
	wszBuf = new WCHAR [lStrLen*2];
	if (NULL == wszBuf)
	{
		pbstr = NULL;
		return -1;
	}

	//���ַ���ת��ΪUnicode.
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
//������	��UNICODE�ַ���ת����ASCII�ַ���
//������	
//			pbstr��bstr��ת�����UNICODE�ַ�����BSTR����
//			pszAnsi��strAnsi��ASCII�ַ���
//���أ�	ת�������ݳ��ȣ����Ϊ-1��ʾת��ʧ��
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
//������	�������ֽ�(VT_I1��char)��SafeArray��������
//������	
//			nArrayLen��ԭʼ���ݵĳ���
//			pszValBuff��Դ���ݻ�������ַ
//			pvarBuff����ȫ����ָ���ַ�����ڱ��洴���İ�ȫ���������
//���أ�	��
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
	//2021-8-18  lijunqing  �ڴ濽�������Ч��
	memcpy(pFilter->pvData, pszValBuff, nArrayLen*sizeof(char));

	
	V_VT(pvarBuff) = VT_I1 | VT_ARRAY; 
	V_ARRAY(pvarBuff) = pFilter; 	
}

//*********************************************************************
//������	����˫�ֽ�����(VT_I2��short)��SafeArray��������
//������	
//			nArrayLen��ԭʼ���ݵĳ���
//			pshortValBuff��Դ���ݻ�������ַ
//			pvarBuff����ȫ����ָ���ַ�����ڱ��洴���İ�ȫ���������
//���أ�	��
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
	//2021-8-18  lijunqing  �ڴ濽�������Ч��
	memcpy(pFilter->pvData, pshortValBuff, nArrayLen*sizeof(short));

	V_VT(pvarBuff) = VT_I2 | VT_ARRAY; 
	V_ARRAY(pvarBuff) = pFilter; 	
}

//*********************************************************************
//������	�������ֽ�����(VT_I4��long)��SafeArray��������
//������	
//			nArrayLen��ԭʼ���ݵĳ���
//			plValBuff��Դ���ݻ�������ַ
//			pvarBuff����ȫ����ָ���ַ�����ڱ��洴���İ�ȫ���������
//���أ�	��
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
	//2021-8-18  lijunqing  �ڴ濽�������Ч��
	memcpy(pFilter->pvData, plValBuff, nArrayLen*sizeof(long));

	V_VT(pvarBuff) = VT_I4 | VT_ARRAY; 
	V_ARRAY(pvarBuff) = pFilter; 	
}

//*********************************************************************
//������	�����޷��ŵ��ֽ�(VT_UI1��unsigned char)��SafeArray��������
//������	
//			nArrayLen��ԭʼ���ݵĳ���
//			pbyteValBuff��Դ���ݻ�������ַ
//			pvarBuff����ȫ����ָ���ַ�����ڱ��洴���İ�ȫ���������
//���أ�	��
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
	//2021-8-18  lijunqing  �ڴ濽�������Ч��
	memcpy(pFilter->pvData, pbyteValBuff, nArrayLen*sizeof(BYTE));

	V_VT(pvarBuff) = VT_UI1 | VT_ARRAY; 
	V_ARRAY(pvarBuff) = pFilter; 	
}

//*********************************************************************
//������	�����޷���˫�ֽ�����(VT_UI2��unsigned short)��SafeArray��������
//������	
//			nArrayLen��ԭʼ���ݵĳ���
//			pwValBuff��Դ���ݻ�������ַ
//			pvarBuff����ȫ����ָ���ַ�����ڱ��洴���İ�ȫ���������
//���أ�	��
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
	//2021-8-18  lijunqing  �ڴ濽�������Ч��
	memcpy(pFilter->pvData, pwValBuff, nArrayLen*sizeof(WORD));

	V_VT(pvarBuff) = VT_UI2 | VT_ARRAY; 
	V_ARRAY(pvarBuff) = pFilter; 	
}

//*********************************************************************
//������	�����޷������ֽ�����(VT_UI4��unsigned long)��SafeArray��������
//������	
//			nArrayLen��ԭʼ���ݵĳ���
//			pdwValBuff��Դ���ݻ�������ַ
//			pvarBuff����ȫ����ָ���ַ�����ڱ��洴���İ�ȫ���������
//���أ�	��
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
	//2021-8-18  lijunqing  �ڴ濽�������Ч��
	memcpy(pFilter->pvData, pdwValBuff, nArrayLen*sizeof(DWORD));

	V_VT(pvarBuff) = VT_UI4 | VT_ARRAY; 
	V_ARRAY(pvarBuff) = pFilter; 	
}

//*********************************************************************
//������	�����޷������ֽڸ�����(VT_R4��float)��SafeArray��������
//������	
//			nArrayLen��ԭʼ���ݵĳ���
//			pfValBuff��Դ���ݻ�������ַ
//			pvarBuff����ȫ����ָ���ַ�����ڱ��洴���İ�ȫ���������
//���أ�	��
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
	//2021-8-18  lijunqing  �ڴ濽�������Ч��
	memcpy(pFilter->pvData, pfValBuff, nArrayLen*sizeof(float));

	V_VT(pvarBuff) = VT_R4 | VT_ARRAY; 
	V_ARRAY(pvarBuff) = pFilter; 	
}

//*********************************************************************
//������	��VARIANT�л�ȡ���ݣ����ػ�ȡ�������ݵĳ���	
//������	�ӵ��ֽ�(VT_I1��char)��SafeArray���������л�ȡ����
//			ppszValBuff�����ڷ������ݵĵ�ַָ��
//			pvarBuff����ȫ����ָ���ַ�������Ҫ��õ�Դ����
//���أ�	��
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
	//2021-8-18  lijunqing  �ڴ濽�������Ч��
	memcpy(*ppszValBuff, pFilter->pvData, nElements *sizeof(char));

	return nElements;
}

//*********************************************************************
//������	��VARIANT�л�ȡ���ݣ����ػ�ȡ�������ݵĳ���	
//������	�ӵ��ֽ�(VT_I1��char)��SafeArray���������л�ȡ����
//			ppszValBuff�����ڷ������ݵĵ�ַָ��
//			pvarBuff����ȫ����ָ���ַ�������Ҫ��õ�Դ����
//���أ�	��
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
	//2021-8-18  lijunqing  �ڴ濽�������Ч��
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
	//2021-8-18  lijunqing  �ڴ濽�������Ч��
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
	//2021-8-18  lijunqing  �ڴ濽�������Ч��
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
	//2021-8-18  lijunqing  �ڴ濽�������Ч��
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
	//2021-8-18  lijunqing  �ڴ濽�������Ч��
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
	//2021-8-18  lijunqing  �ڴ濽�������Ч��
	memcpy(*ppfValBuff, pFilter->pvData, nElements *sizeof(float));

	return nElements;
}


