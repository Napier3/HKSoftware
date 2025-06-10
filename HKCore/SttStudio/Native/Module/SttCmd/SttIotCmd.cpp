//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttIotCmd.cpp  CSttIotCmd


#include "stdafx.h"
#include "SttIotCmd.h"
#include "../../../IotAtsMngr/Module/PxEngineServer/IotPxEngineInterface.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSttIotCmd::CSttIotCmd()
{
	//初始化属性

	//初始化成员变量
	m_strTestor = STT_SOFT_ID_IOT;
}

CSttIotCmd::~CSttIotCmd()
{
	CIotPxCommChannelInterface *pInterface = (CIotPxCommChannelInterface *)GetSttCmmOptrInterface();

	if (pInterface != NULL)
	{
		pInterface->FreeCmd(this);
	}
}

long CSttIotCmd::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CSttCmdBase::XmlReadOwn(oNode, pXmlRWKeys);
	CSttCmdDefineXmlRWKeys *pXmlKeys = (CSttCmdDefineXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strTestorKey, oNode, m_strTestor);
	return 0;
}

long CSttIotCmd::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CSttCmdBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CSttCmdDefineXmlRWKeys *pXmlKeys = (CSttCmdDefineXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strTestorKey, oElement, m_strTestor);
	return 0;
}

long CSttIotCmd::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CSttCmdBase::SerializeOwn(oBinaryBuffer);
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strTestor);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strTestor);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strTestor);
	}
	return 0;
}

BOOL CSttIotCmd::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CSttCmdBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CSttIotCmd *p = (CSttIotCmd*)pObj;

	if(m_strTestor != p->m_strTestor)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CSttIotCmd::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CSttCmdBase::CopyOwn(pDest);

	CSttIotCmd *p = (CSttIotCmd*)pDest;

	p->m_strTestor = m_strTestor;

	return TRUE;
}

CBaseObject* CSttIotCmd::Clone()
{
	CSttIotCmd *p = new CSttIotCmd();
	Copy(p);
	return p;
}

CBaseObject* CSttIotCmd::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CSttIotCmd *p = new CSttIotCmd();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CSttIotCmd::CanPaste(UINT nClassID)
{
	return FALSE;
}

//////////////////////////////////////////////////////////////////////////
CSttIotCmdDriver::CSttIotCmdDriver()
: CXObjectRefDriver(CSttIotCmd::New)
{
	
}

CSttIotCmdDriver::~CSttIotCmdDriver()
{
	
}

CSttIotCmd* CSttIotCmdDriver::NewSttIotCmd(void *pCmmInterface)
{
	New();
	CSttIotCmd *p = SttIotCmd();
	p->SetSttCmmOptrInterface(pCmmInterface);

	CIotPxCommChannelInterface* pInterface = (CIotPxCommChannelInterface *)pCmmInterface;
	pInterface->AddCmd(p);

	return p;
}

//2022-10-19 lijunqing
CXObjectRefDriver* CSttIotCmdDriver::Clone()
{
	CSttIotCmdDriver *pNew = new CSttIotCmdDriver();
	*pNew = *this;
	return pNew;
}

