//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//TcpEdgePkgData_GetHisEventResp.cpp  CTcpEdgePkgData_GetHisEventResp


#include "stdafx.h"
#include "TcpEdgePkgData_GetHisEventResp.h"
#include "Pkg_GetHisEventResp_Devices.h"
#include "Pkg_GetHisEventResp_Device.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CTcpEdgePkgData_GetHisEventResp::CTcpEdgePkgData_GetHisEventResp()
{
	//初始化属性

	//初始化成员变量
}

CTcpEdgePkgData_GetHisEventResp::~CTcpEdgePkgData_GetHisEventResp()
{
}

BOOL CTcpEdgePkgData_GetHisEventResp::xml_GetAttibuteValue(const BSTR strAttrName, CXmlRWNodeBase &oNode, CString &strAttrVal)
{
	//在这里判断报文中的String字段是否有误
	QString strTemp;
	CString strAttr(strAttrName);
	CString strID(GetXmlElementKey());
	BOOL bRet = oNode.xml_GetAttibuteValue(strAttrName,strAttrVal);
	if(!strAttrVal.GetLength())
	{
		//值不存在时检查是否必需
		for(int i = 0; i < 64; i++)
		{
			if(m_arrayNotMust[i] == strAttr)
			{
				return bRet;
			}
		}

		strTemp = QString("【错误】【必需项缺失】GetHisEventResp：[%1]=>[%2]必需字段缺失;\n").arg(strID).arg(strAttr);
		m_strErrorInfo += strTemp;
		m_strNecessityLack += strTemp;
	}
	else if(oNode.xml_GetAttibuteType(strAttrName) != CJSON_String)
	{
		//值存在时检查类型是否正确
		strTemp = QString("【错误】【必需项错误】GetHisEventResp：[%1]=>[%2]字段类型错误;\n").arg(strID).arg(strAttr);
		m_strErrorInfo += strTemp;
		m_strNecessityErr += strTemp;
	}

	return bRet;
}

long CTcpEdgePkgData_GetHisEventResp::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
    //CTcpEdgePkgData::XmlReadOwn(oNode, pXmlRWKeys);
    CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strContinueKey, oNode, m_strContinue);

    //取到JSON
    CJSON* pJson = ((CJsonNode*)&oNode)->m_pJsonNode;
    if(pJson == NULL)
    {
        return 0;
    }

    //检测JSON报文中是否存在LinkState节点，存在则动态创建LinkState并添加
    CJSON* pDatasJson = CJSON_GetObjectItem(pJson, PkgData_Node_Devices);
    if(pDatasJson)
    {
        CPkg_GetHisEventResp_Devices* pDatas = new CPkg_GetHisEventResp_Devices;
        pDatas->m_strID = pDatas->m_strName = PkgData_Node_Devices;
        AddNewChild(pDatas);

        //遍历Devices，动态创建子结构
        CJSON* pDatasChild = pDatasJson->child;
        while (pDatasChild)
        {
            CPkg_GetHisEventResp_Device* pData = new CPkg_GetHisEventResp_Device;

            CJsonNode* pTempJsonNode = new CJsonNode(pDatasChild);
            //调用子类里的函数来解析数据，如果子类中包含数组，去子类的该函数中做类似处理
			pData->m_strErrorInfo = m_strErrorInfo;
			pData->m_strNecessityLack = m_strNecessityLack;
			pData->m_strNecessityErr = m_strNecessityErr;
			pData->m_strRangeOut = m_strRangeOut;
			pData->m_strReturnFalse = m_strReturnFalse;
			pData->XmlReadOwn(*(CXmlRWNodeBase*)pTempJsonNode, pXmlRWKeys);
			m_strErrorInfo = pData->m_strErrorInfo;
			m_strNecessityLack = pData->m_strNecessityLack;
			m_strNecessityErr = pData->m_strNecessityErr;
			m_strRangeOut = pData->m_strRangeOut;
			m_strReturnFalse = pData->m_strReturnFalse;
            delete pTempJsonNode;
            //解析完成后作为次级报文添加到pDevices
            pDatas->AddNewChild(pData);

            pDatasChild = pDatasChild->next;
        }
    }
	else
	{
		QString strTemp;
		CString strID(GetXmlElementKey());
		strTemp = QString("【错误】【必需项缺失】GetHisEventResp：[%1]=>[%2]必需字段array缺失;\n").arg(strID).arg(PkgData_Node_Devices);
		m_strErrorInfo += strTemp;
		m_strNecessityLack += strTemp;
	}

	//lmy,20230915修改
	//if(m_strContinue != _T("0") || m_strContinue != _T("1"))
	if(m_strContinue != _T("0") && m_strContinue != _T("1"))
	{
		QString strTemp;
		strTemp = QString(_T("【错误】【超过范围】GetHisEventResp：[%1]=>[%2]字段超出范围;\n")).arg(PkgData_Node_Data).arg(PkgData_Node_Continue);
		m_strErrorInfo += strTemp;
		m_strRangeOut += strTemp;
	}

	return 0;
}

long CTcpEdgePkgData_GetHisEventResp::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
    //CTcpEdgePkgData::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

    CJSON* pJson = ((CJsonNode*)&oElement)->m_pJsonNode;
    if(pJson == NULL)
    {
        return 0;
    }

    CPkg_GetHisEventResp_Devices* pDatas = (CPkg_GetHisEventResp_Devices*)FindByID(PkgData_Node_Devices);
    if(pDatas == NULL)
    {
        return 0;
    }

    CJSON* pDatasJson = CJSON_CreateArray();
    POS pos = pDatas->GetHeadPosition();
    while(pos)
    {
        CPkg_GetHisEventResp_Device* pData = (CPkg_GetHisEventResp_Device*)pDatas->GetNext(pos);
        CJSON* pDataJson = CJSON_CreateObject();
        CJsonNode* pTempJsonNode = new CJsonNode(pDataJson);
        pData->XmlWriteOwn(oXMLDoc, *(CXmlRWElementBase*)pTempJsonNode, pXmlRWKeys);
        delete pTempJsonNode;

        CJSON_AddItemToArray(pDatasJson, pDataJson);
    }

    CJSON_AddItemToObject(pJson, PkgData_Node_Devices, pDatasJson);

    DeleteByID(PkgData_Node_Devices);


	xml_SetAttributeValue(pXmlKeys->m_strContinueKey, oElement, m_strContinue);
	return 0;
}

long CTcpEdgePkgData_GetHisEventResp::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CTcpEdgePkgData::SerializeOwn(oBinaryBuffer);
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strContinue);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strContinue);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strContinue);
	}
	return 0;
}

void CTcpEdgePkgData_GetHisEventResp::InitAfterRead()
{
}

BOOL CTcpEdgePkgData_GetHisEventResp::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CTcpEdgePkgData::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CTcpEdgePkgData_GetHisEventResp *p = (CTcpEdgePkgData_GetHisEventResp*)pObj;

	if(m_strContinue != p->m_strContinue)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CTcpEdgePkgData_GetHisEventResp::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CTcpEdgePkgData::CopyOwn(pDest);

	CTcpEdgePkgData_GetHisEventResp *p = (CTcpEdgePkgData_GetHisEventResp*)pDest;

	p->m_strContinue = m_strContinue;
	return TRUE;
}

CBaseObject* CTcpEdgePkgData_GetHisEventResp::Clone()
{
	CTcpEdgePkgData_GetHisEventResp *p = new CTcpEdgePkgData_GetHisEventResp();
	Copy(p);
	return p;
}

CBaseObject* CTcpEdgePkgData_GetHisEventResp::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CTcpEdgePkgData_GetHisEventResp *p = new CTcpEdgePkgData_GetHisEventResp();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CTcpEdgePkgData_GetHisEventResp::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CTcpEdgePkgData_GetHisEventResp::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CTcpEdgePkgData_GetHisEventResp::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
long CTcpEdgePkgData_GetHisEventResp::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgData::DB_ReadFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strContinueKey, m_strContinue);
	return 0;
}

long CTcpEdgePkgData_GetHisEventResp::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgData::DB_WriteFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strContinueKey, m_strContinue);
	return 0;
}

