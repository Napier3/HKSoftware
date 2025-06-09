//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//TcpEdgePkgData_GetHisEvent.cpp  CTcpEdgePkgData_GetHisEvent


#include "stdafx.h"
#include "TcpEdgePkgData_GetHisEvent.h"
#include "Pkg_GetHisEvent_Devices.h"
#include "Pkg_GetHisEvent_Device.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CTcpEdgePkgData_GetHisEvent::CTcpEdgePkgData_GetHisEvent()
{
	//��ʼ������

	//��ʼ����Ա����
}

CTcpEdgePkgData_GetHisEvent::~CTcpEdgePkgData_GetHisEvent()
{
}

long CTcpEdgePkgData_GetHisEvent::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
    //CTcpEdgePkgData::XmlReadOwn(oNode, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

    //ȡ��JSON
    CJSON* pJson = ((CJsonNode*)&oNode)->m_pJsonNode;
    if(pJson == NULL)
    {
        return 0;
    }

    //���JSON�������Ƿ����LinkState�ڵ㣬������̬����LinkState�����
    CJSON* pDatasJson = CJSON_GetObjectItem(pJson, PkgData_Node_Devices);
    if(pDatasJson)
    {
        CPkg_GetHisEvent_Devices* pDatas = new CPkg_GetHisEvent_Devices;
        pDatas->m_strID = pDatas->m_strName = PkgData_Node_Devices;
        AddNewChild(pDatas);

        //����Devices����̬�����ӽṹ
        CJSON* pDatasChild = pDatasJson->child;
        while (pDatasChild)
        {
            CPkg_GetHisEvent_Device* pData = new CPkg_GetHisEvent_Device;

            CJsonNode* pTempJsonNode = new CJsonNode(pDatasChild);
            //����������ĺ������������ݣ���������а������飬ȥ����ĸú����������ƴ���
            pData->XmlReadOwn(*(CXmlRWNodeBase*)pTempJsonNode, pXmlRWKeys);
            delete pTempJsonNode;
            //������ɺ���Ϊ�μ�������ӵ�pDevices
            pDatas->AddNewChild(pData);

            pDatasChild = pDatasChild->next;
        }
    }

	return 0;
}

long CTcpEdgePkgData_GetHisEvent::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
    //CTcpEdgePkgData::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

    CJSON* pJson = ((CJsonNode*)&oElement)->m_pJsonNode;
    if(pJson == NULL)
    {
        return 0;
    }

    CPkg_GetHisEvent_Devices* pDatas = (CPkg_GetHisEvent_Devices*)FindByID(PkgData_Node_Devices);
    if(pDatas == NULL)
    {
        return 0;
    }

    CJSON* pDatasJson = CJSON_CreateArray();
    POS pos = pDatas->GetHeadPosition();
    while(pos)
    {
        CPkg_GetHisEvent_Device* pData = (CPkg_GetHisEvent_Device*)pDatas->GetNext(pos);
        CJSON* pDataJson = CJSON_CreateObject();
        CJsonNode* pTempJsonNode = new CJsonNode(pDataJson);
        pData->XmlWriteOwn(oXMLDoc, *(CXmlRWElementBase*)pTempJsonNode, pXmlRWKeys);
        delete pTempJsonNode;

        CJSON_AddItemToArray(pDatasJson, pDataJson);
    }

    CJSON_AddItemToObject(pJson, PkgData_Node_Devices, pDatasJson);

    DeleteByID(PkgData_Node_Devices);

	return 0;
}

long CTcpEdgePkgData_GetHisEvent::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CTcpEdgePkgData::SerializeOwn(oBinaryBuffer);
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

void CTcpEdgePkgData_GetHisEvent::InitAfterRead()
{
}

BOOL CTcpEdgePkgData_GetHisEvent::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CTcpEdgePkgData::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CTcpEdgePkgData_GetHisEvent *p = (CTcpEdgePkgData_GetHisEvent*)pObj;

	return TRUE;
}

BOOL CTcpEdgePkgData_GetHisEvent::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CTcpEdgePkgData::CopyOwn(pDest);

	CTcpEdgePkgData_GetHisEvent *p = (CTcpEdgePkgData_GetHisEvent*)pDest;

	return TRUE;
}

CBaseObject* CTcpEdgePkgData_GetHisEvent::Clone()
{
	CTcpEdgePkgData_GetHisEvent *p = new CTcpEdgePkgData_GetHisEvent();
	Copy(p);
	return p;
}

CBaseObject* CTcpEdgePkgData_GetHisEvent::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CTcpEdgePkgData_GetHisEvent *p = new CTcpEdgePkgData_GetHisEvent();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CTcpEdgePkgData_GetHisEvent::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CTcpEdgePkgData_GetHisEvent::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CTcpEdgePkgData_GetHisEvent::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}

CDvmDataset* CTcpEdgePkgData_GetHisEvent::ToDataset()
{
	CDvmDataset* pDataset = new CDvmDataset;
	pDataset->m_strID = PkgData_Node_Data;
	pDataset->m_strDataType = PkgData_Type_Object;
	pDataset->m_dwItemData = 1;
	pDataset->m_dwReserved = 1;
	
	CDvmDatasetGroup* pDatasetArray = CPkg_GetHisEvent_Devices::ToDataset();
	pDatasetArray->m_dwItemData = 1;
	pDataset->AddNewChild(pDatasetArray);

	return pDataset;
}

BOOL CTcpEdgePkgData_GetHisEvent::NewData(CDvmDatasetGroup* pArray)
{
	CPkg_GetHisEvent_Device* pObj = new CPkg_GetHisEvent_Device;
	AddNewChild(pObj);

	CDvmDataset* pDataset = CPkg_GetHisEvent_Device::ToDataset();
	pDataset->m_strID = "";
	pDataset->m_dwReserved = (DWORD)pObj;
	pArray->AddNewChild(pDataset);

	return TRUE;
}