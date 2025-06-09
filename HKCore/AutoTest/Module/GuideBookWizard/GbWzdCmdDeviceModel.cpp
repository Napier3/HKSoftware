#include "stdafx.h"
#include "GbWzdCmdDeviceModel.h"
#include "GuideBookWizard.h"
#include "GuideBookWizard.h"
#include "..\XLanguageResourceAts.h"
#define GBWZDDVM_STATE_EDIT_DEVICE           0
#define GBWZDDVM_STATE_EDIT_DEVICEMODEL      1
#define GBWZDDVM_STATE_EDIT_CHARACTERISTIC   2

CGbWzdCmdDeviceModel::CGbWzdCmdDeviceModel()
{
	m_nGbWzdCmdDeviceModelIndex = -1;
	m_strName = /*_T("设置设备数据模型")*/g_sLangTxt_SetDeviceDataModel;
	m_strID = _T("DeviceModel");

	m_pCpus = NULL;
	m_pCharacteristics = NULL;
}


CGbWzdCmdDeviceModel::~CGbWzdCmdDeviceModel()
{
	
}


long CGbWzdCmdDeviceModel::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	return 0;
}

long CGbWzdCmdDeviceModel::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	//CGbWzdCmd::XmlReadOwn(oNode,pXmlRWKeys);
	xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strNameKey,oNode,m_strDvmName);
	xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strIDKey,oNode,m_strDvmID);

	xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strFactoryKey,oNode,m_strFactory);
	xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strDeviceTypeKey,oNode,m_strDeviceType);
	xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strIsTimeSetsUnit_ms_Key,oNode,m_nIsTimeSetsUnit_ms);

	return 0;
}

long CGbWzdCmdDeviceModel::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	//CGbWzdCmd::XmlWriteOwn(oXMLDoc,oElement,pXmlRWKeys);

	xml_SetAttributeValue(pXmlRWKeys->m_strNameKey, oElement, m_strDvmName);
	xml_SetAttributeValue(pXmlRWKeys->m_strIDKey, oElement, m_strDvmID);

	xml_SetAttributeValue(CGbXMLKeys::g_pGbXMLKeys->m_strFactoryKey, oElement, m_strFactory);
	xml_SetAttributeValue(CGbXMLKeys::g_pGbXMLKeys->m_strDeviceTypeKey, oElement, m_strDeviceType);
	xml_SetAttributeValue(CGbXMLKeys::g_pGbXMLKeys->m_strIsTimeSetsUnit_ms_Key, oElement, m_nIsTimeSetsUnit_ms);

	return 0;
}

BSTR CGbWzdCmdDeviceModel::GetXmlElementKey()
{
	return CGbWzdToolXmlRWKeys::CGbWzdCmdDeviceModelKey();
}


CExBaseObject* CGbWzdCmdDeviceModel::CreateNewChild(long nClassID)
{
	return NULL;
}

CExBaseObject* CGbWzdCmdDeviceModel::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	if (strClassID == ((CGbWzdToolXmlRWKeys*)pXmlRWKeys)->m_strDeviceModelKey)
	{
		FreeCpus();
		m_pCpus = new CCpus();
		return m_pCpus;
	}

	if (strClassID == ((CGbWzdToolXmlRWKeys*)pXmlRWKeys)->m_strCCharacteristicsKey)
	{
		FreeCharacteristics();
		m_pCharacteristics = new CCharacteristics();
		return m_pCharacteristics;
	}

	return NULL;
}

BOOL CGbWzdCmdDeviceModel::IsEqual(CBaseObject* pObj)
{
	return TRUE;
}

BOOL CGbWzdCmdDeviceModel::CopyOwn(CBaseObject* pDesObj)
{
	return TRUE;
}

CBaseObject* CGbWzdCmdDeviceModel::Clone()
{
	CGbWzdCmdDeviceModel *pNew = new CGbWzdCmdDeviceModel();
	Copy(pNew);
	return pNew;
}


BOOL CGbWzdCmdDeviceModel::Execute(DWORD dwExecMode)
{
	CGbWzdCmd::Execute(dwExecMode);

	CGuideBook *pGuideBook = GetGuideBook();
	CTreeCtrl *pGbTree = GetGuideBookEditTreeCtrl();
	CFrameWnd* pFrameWnd = GetMaiFrame();
	CDevice *pDevice = NULL;

	if (dwExecMode == WZDEXEC_AUTO)
	{
		if (!IsCmdFinish())
		{
			pGbTree->SendMessage(WM_USER + 1055, (WPARAM)pGuideBook, (LPARAM)pGuideBook);
			pFrameWnd->SendMessage(WM_COMMAND, ID_NEW_DEVICE, 0);
			ShowGbWzdMsg(_T("设置设备的属性，建议将名称和ID设置为保护型号的名字"));
		}

		return TRUE;
	}

	if (m_nGbWzdCmdDeviceModelIndex == -1)
	{
		m_nGbWzdCmdDeviceModelIndex = GBWZDDVM_STATE_EDIT_DEVICE;
	}
	else
	{
		m_nGbWzdCmdDeviceModelIndex++;
	}

	switch (m_nGbWzdCmdDeviceModelIndex)
	{
	case GBWZDDVM_STATE_EDIT_DEVICE:
		pGbTree->SendMessage(WM_USER + 1055, (WPARAM)pGuideBook, (LPARAM)pGuideBook);
		pFrameWnd->PostMessage(WM_COMMAND, ID_NEW_DEVICE, 0);
		ShowGbWzdMsg(/*_T("设置设备的属性，建议将名称和ID设置为保护型号的名字")*/g_sLangTxt_SetDeviceAttr);
		

		if (CGuideBookWizard::IsQuickWizard() || CGuideBookWizard::IsGbWzdAuto())
		{
			CFrameWnd *pFrameWnd = GetMaiFrame();
			pFrameWnd->PostMessage(WM_EXEC_GBWZD_EXEC_NEXT, 0, 0);
		}

		break;

	case GBWZDDVM_STATE_EDIT_DEVICEMODEL:
		//ID_OPTR_DEVICE_IMPORT_MMS
		pDevice = GetDevice();
		ASSERT (pDevice != NULL);

		if (pDevice != NULL)
		{
			pGbTree->SendMessage(WM_USER + 1055, (WPARAM)pDevice->m_pCpus, (LPARAM)pDevice->m_pCpus);
			ShowGbWzdMsg(/*_T("设置设备的数据模型，选择磁盘上已经存在的设备数据模型文件，此文件通过MMS客户端从保护装置枚举得到")*/g_sLangTxt_SetDeviceDataType);
			pFrameWnd->PostMessage(WM_COMMAND, 32781, 0);//导入设备数据模型对话框
		}

		break;

	case GBWZDDVM_STATE_EDIT_CHARACTERISTIC:
		pDevice = GetDevice();
		ASSERT (pDevice != NULL);

		if (pDevice != NULL)
		{
			pGbTree->SendMessage(WM_USER + 1055, (WPARAM)pDevice->m_pCharacteristics, (LPARAM)pDevice->m_pCharacteristics);
			ShowGbWzdMsg(/*_T("设置设备的特性曲线，此步骤可以暂时不设置，设置子模板时再设置特性曲线")*/g_sLangTxt_SetDeviceCharCurve);
		}

		if (CGuideBookWizard::IsQuickWizard() || CGuideBookWizard::IsGbWzdAuto())
		{
			CFrameWnd *pFrameWnd = GetMaiFrame();
			pFrameWnd->PostMessage(WM_EXEC_GBWZD_EXEC_NEXT, 0, 0);
		}

		break;
	}

	return TRUE;
}


void CGbWzdCmdDeviceModel::GetCmdInfor(CString &strText)
{
	strText = m_strName;

	switch (m_nGbWzdCmdDeviceModelIndex)
	{
	case GBWZDDVM_STATE_EDIT_DEVICE:
		strText += /*_T(" ==>> 设置设备的属性")*/g_sLangTxt_SetDeviceAttr2;
		break;

	case GBWZDDVM_STATE_EDIT_DEVICEMODEL:
		//ID_OPTR_DEVICE_IMPORT_MMS
		strText += /*_T(" ==>> 设置设备的数据模型")*/g_sLangTxt_SetDeviceDataType2;
		break;

	case GBWZDDVM_STATE_EDIT_CHARACTERISTIC:
		strText += /*_T(" ==>> 设置设备的特性曲线")*/g_sLangTxt_SetDeviceCharCurve2;
		break;
	}

	if (m_nCmdExecState == GBWZDCMD_STATE_FINISH)
	{
		strText = m_strName;
	}
}

BOOL CGbWzdCmdDeviceModel::IsCmdFinish()
{
	if( m_nGbWzdCmdDeviceModelIndex >= GBWZDDVM_STATE_EDIT_CHARACTERISTIC)
	{
		m_nCmdExecState = GBWZDCMD_STATE_FINISH;
	}

	return (m_nCmdExecState == GBWZDCMD_STATE_FINISH);
}

void CGbWzdCmdDeviceModel::SetCpus(CCpus *pCpus)
{
	FreeCpus();
	m_pCpus = (CCpus*)pCpus->Clone();
	AddNewChild(m_pCpus);
}

void CGbWzdCmdDeviceModel::SetCharacteristics(CCharacteristics *pCharacteristics)
{
	FreeCharacteristics();
	m_pCharacteristics = (CCharacteristics*)pCharacteristics->Clone();
	AddNewChild(m_pCharacteristics);
}

void CGbWzdCmdDeviceModel::InitByDevice(CDevice *pDevice)
{
	m_strDvmName = pDevice->m_strName;
	m_strDvmID = pDevice->m_strID;
	m_strFactory = pDevice->m_strFactory;
	m_strDeviceType = pDevice->m_strDeviceType;
	m_nIsTimeSetsUnit_ms = pDevice->m_nIsTimeSetsUnit_ms;
}

void CGbWzdCmdDeviceModel::InitDevice(CDevice *pDevice)
{
	pDevice->m_strName = m_strDvmName;
	pDevice->m_strID = m_strDvmID;
	pDevice->m_strFactory = m_strFactory;
	pDevice->m_strDeviceType = m_strDeviceType;
	pDevice->m_nIsTimeSetsUnit_ms = m_nIsTimeSetsUnit_ms;

	if (m_pCpus != NULL)
	{
		CCpus *pCpus = pDevice->GetCpus();
		pCpus->DeleteAll();
		pCpus->AppendCloneEx(*m_pCpus);
	}

	if (m_pCharacteristics != NULL)
	{
		CCharacteristics *pCharacteristics = pDevice->GetCharacteristics();

		ASSERT( pCharacteristics != NULL);
		pCharacteristics->DeleteAll();
		pCharacteristics->AppendCloneEx(*m_pCharacteristics);
	}

	pDevice->InitAfterRead();

	SetFinishState();
}
