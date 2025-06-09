//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//XExprBase.h  CXExprBase

#pragma once

#include "XExprGlobal.h"
#include "XExprValue_Ex.h"
#include "../DataMngr/DvmValue.h"

class CXExprBase : public CExBaseList
{
public:
	CXExprBase();
	virtual ~CXExprBase();

	CString m_strUse;   //���������ڱ����ļ�
	long m_nIsUse;   //�Ƿ����ã������������߼��ж�
	long m_nResult;
	long m_nCntRslt; //�Ƿ����������С�Ĭ��Ϊ1������Ϊ0����ʾ���ʽֻ�����㣬���������ս�������

//���غ���
public:
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual void InitAfterRead();

public:
	virtual long Calc(CExBaseObject *pExprParent, CXExprCalInterface *pCalInterface) = 0;
	virtual long CalcEx(CExBaseObject *pExprParent, CXExprCalInterface *pCalInterface, long nCurrTestTimes, long nRepeatTimes)	{	return 0;	}
	virtual void ExprRsltBind(CExBaseObject *pExprParent, CXExprCalInterface *pCalInterface) = 0;
	virtual void GetRsltExprValues(CExBaseObject *pExprParent, CExBaseList *pReportValues, CXExprCalInterface *pCalInterface, CExBaseList *pRsltExprValues, CExBaseList *pListXExprValues) = 0;

	virtual void GetRsltExprValues_ExprMode(const CString &strMode, CExBaseList *pRsltExprValues);
	virtual BOOL ExprModeValid(const CString &strMode);
	virtual BOOL GetValueName(const CString &strID, CString &strName)	{	return FALSE;	}

};

