//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CmdExecRslt.cpp  CCmdExecRslt


#include "stdafx.h"
#include "CmdExecRslt.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CCmdExecRslt::CCmdExecRslt()
{
	//初始化属性

	//初始化成员变量
	m_pDvmDataset = NULL;
	m_pExecResult = NULL;
}

CCmdExecRslt::~CCmdExecRslt()
{
}

long CCmdExecRslt::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CCmdExecXmlRWKeys *pXmlKeys = (CCmdExecXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CCmdExecRslt::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CCmdExecXmlRWKeys *pXmlKeys = (CCmdExecXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CCmdExecRslt::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
	}
	else if(oBinaryBuffer.IsReadMode())
	{
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
	}
	return 0;
}

void CCmdExecRslt::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == DVMCLASSID_CDVMDATASET)
		{
			m_pDvmDataset = (CDvmDataset*)p;
		}
		else if (nClassID == MNGRCLASSID_CEXECRESULT)
		{
			m_pExecResult = (CExecResult*)p;
		}
	}

	if (m_pDvmDataset == NULL)
	{
		m_pDvmDataset = (CDvmDataset*)AddNewChild(new CDvmDataset());
	}

	if (m_pExecResult == NULL)
	{
		m_pExecResult = (CExecResult*)AddNewChild(new CExecResult());
	}

}

BOOL CCmdExecRslt::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CCmdExecRslt *p = (CCmdExecRslt*)pObj;

	return TRUE;
}

BOOL CCmdExecRslt::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CCmdExecRslt *p = (CCmdExecRslt*)pDest;

	return TRUE;
}

CBaseObject* CCmdExecRslt::Clone()
{
	CCmdExecRslt *p = new CCmdExecRslt();
	Copy(p);
	return p;
}

CBaseObject* CCmdExecRslt::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CCmdExecRslt *p = new CCmdExecRslt();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CCmdExecRslt::CanPaste(UINT nClassID)
{
	if (nClassID == MNGRCLASSID_CEXECRESULT)
	{
		return TRUE;
	}

	if (nClassID == DVMCLASSID_CDVMDATASET)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CCmdExecRslt::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CCmdExecXmlRWKeys *pXmlKeys = (CCmdExecXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCExecResultKey)
	{
		pNew = new CExecResult();
	}
	else if (strClassID == pXmlKeys->m_strCDvmDatasetKey)
	{
		pNew = new CDvmDataset();
	}

	return pNew;
}

CExBaseObject* CCmdExecRslt::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MNGRCLASSID_CEXECRESULT)
	{
		pNew = new CExecResult();
	}
	else if (nClassID == DVMCLASSID_CDVMDATASET)
	{
		pNew = new CDvmDataset();
	}

	return pNew;
}

void CCmdExecRslt::GenerateCmdExecRslt(long nRslt,CDvmDataset *pDataset)
{
	DeleteAll();

	m_pExecResult = (CExecResult*)AddNewChild(new CExecResult());
	m_pDvmDataset = (CDvmDataset *)pDataset->Clone();
	AddNewChild(m_pDvmDataset);

	CString strTime,strValue,strErrInfo = _T("");
	strValue.Format(_T("%d"),nRslt);

	if (nRslt == 1)
	{
		strErrInfo = _T("执行失败");
	}
	else if (nRslt == 2)
	{
		strErrInfo = _T("执行超时");
	}
	else if(nRslt > 2)
	{
		strErrInfo.Format(_T("执行异常，错误码：%d"),nRslt);
	}

	SYSTEMTIME tm;
	GetLocalTime(&tm);
	SystemTime_To_StringEx(tm,strTime);

	m_pExecResult->AddNewData(_T("报告时间"),_T("time"),_T(""),strTime);
	m_pExecResult->AddNewData(_T("执行结果"),_T("rslt"),_T(""),strValue);
	if(nRslt > 0)
	{
		m_pExecResult->AddNewData(_T("异常信息"),_T("Err"),_T(""),strErrInfo);
	}
}