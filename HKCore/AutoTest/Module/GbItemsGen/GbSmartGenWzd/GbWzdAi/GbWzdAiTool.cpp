#include "StdAfx.h"
#include "GbWzdAiTool.h"
#include "GbWzdAiSwitch.h"

#include "../../../../../IotProtoServer/Module/SttPxCommCmdDef.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CGbWzdAiTool *g_theGbWzdAiTool = NULL;

void Create_GbWzdAiTool()
{
	CGbSmartGenWzdXmlRWKeys::Create();

	if (g_theGbWzdAiTool == NULL)
	{
		g_theGbWzdAiTool = new CGbWzdAiTool();
	}
}

void Release_GbWzdAiTool()
{
	if (g_theGbWzdAiTool != NULL)
	{
		delete g_theGbWzdAiTool;
		g_theGbWzdAiTool = NULL;
	}

	CGbSmartGenWzdXmlRWKeys::Release();
}

//////////////////////////////////////////////////////////////////////////
//
CGbWzdAiTool::CGbWzdAiTool()
{
	m_pKeyDB = NULL;
	m_pDevice = NULL;
	m_pMacroParas = NULL;
	m_pSttGuideBook = NULL;
}

CGbWzdAiTool::~CGbWzdAiTool()
{
	m_oDvmMatchListFilter.RemoveAll();
}

long CGbWzdAiTool::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseList::SerializeOwn(oBinaryBuffer);


	return 0;
}

CExBaseObject* CGbWzdAiTool::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	if (strClassID == CGbSmartGenWzdXmlRWKeys::g_pGbSmartGenWzdKeys->m_strGbWzdAiSwitchKey)
	{
		return new CGbAiSwitch();
	}

	return CGbWzdAiParasBase::CreateNewChild(strClassID, bAddToTail, pXmlRWKeys);
}

CExBaseObject* CGbWzdAiTool::CreateNewChild(long nClassID)
{
	if (nClassID == GBCLASSID_GbWzdAiSwitch)
	{
		return new CGbAiSwitch();
	}

	return CGbWzdAiParasBase::CreateNewChild(nClassID);
}

long CGbWzdAiTool::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseList::XmlReadOwn(oNode, pXmlRWKeys);

	CGbSmartGenWzdXmlRWKeys *pXmlKeys = (CGbSmartGenWzdXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CGbWzdAiTool::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseList::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CGbSmartGenWzdXmlRWKeys *pXmlKeys = (CGbSmartGenWzdXmlRWKeys*)pXmlRWKeys;

	return 0;
}

void CGbWzdAiTool::SetXKeyDB(CXKeyDB *pKeyDB)
{
	m_pKeyDB = pKeyDB;
}

void CGbWzdAiTool::InitGbAiDataKey()
{
	POS pos = GetHeadPosition();
	CGbWzdAiMacroPara *p = NULL;

	while (pos != NULL)
	{
		p = (CGbWzdAiMacroPara *)GetNext(pos);
		p->InitGbAiDataKey(m_pKeyDB);
	}
}

void CGbWzdAiTool::SetDvmDevice(CDvmDevice *pDevice)
{
	m_pDevice = pDevice;

	m_oParameterMatchList.DeleteAll();
	m_oDvmMatchList.DeleteAll();
	m_oDvmMatchListFilter.RemoveAll();

	//���������߼��豸����ȡ��ֵ���ݼ���װ�ò������ݼ������������ݼ��Ĺؼ���
	POS pos = pDevice->GetHeadPosition();
	CDvmLogicDevice *pLd = NULL;

	while (pos != NULL)
	{
		pLd = (CDvmLogicDevice *)pDevice->GetNext(pos);

		if (pLd->GetClassID() != DVMCLASSID_CDVMLOGICDEVICE)
		{
			continue;
		}

		POS posDs = pLd->GetHeadPosition();
		CDvmDataset *pDataset = NULL;

		while (posDs != NULL)
		{
			pDataset = (CDvmDataset *)pLd->GetNext(posDs);
			InitDvmMatchList(pDataset);
		}
	}
}

//���������ļ�
void CGbWzdAiTool::OpenGbWzdAiFile(const CString &strAiFile)
{
	//��һ�������������ļ�
	OpenXmlFile(strAiFile, CGbSmartGenWzdXmlRWKeys::g_pGbSmartGenWzdKeys);

	//�ڶ���������ÿ��CGbAiParaScript���󣬳�ʼ�������ж��������������������Key
	InitGbAiDataKey();
}

//ͨ�����Թ��ܲ����ļ������������ļ������磺���Թ��ܲ����ļ�Ϊ��Distance_Paras.xml
//���������ļ�Ϊ��Distance_Paras_ai.xml
void CGbWzdAiTool::OpenGbWzdFileByMacroParaFile(const CString &strUIFile)
{
	
}

//������չ�ؼ��֣������豸����ģ���е����ݣ���Ҫ�Ƕ�ֵ����
void CGbWzdAiTool::SetExtendKeys(const CString &strExtendKeys)
{
	m_pKeyDB->QueryKeys(strExtendKeys, &m_listExtendXKeys);
}

void CGbWzdAiTool::AddExtendKeys(const CString &strExtendKeys)
{
	
}

//�����豸����ģ�ͣ��������ò��Թ��ܵĲ���
void CGbWzdAiTool::SetMacroParasByAI(CDataGroup *pMacroParas)
{
	//��սű������״̬��
	ClearScptState();

	//��һ��������ÿ��Data
	InitMacroPara(pMacroParas);

	//�ڶ������������ò��������ڵ�һ���������Ҫ���Tool�����µ�Para�����Լ�Switch����
	SetMacroParasValueByAI(&m_oDvmMatchListFilter, m_pSttGuideBook);

	//���������������ò��������ڵڶ����������Ҫ���Tool�����µ�switch����ִ�и�case������para�������������
	ScptCalEx(&m_oDvmMatchListFilter, TRUE, m_pSttGuideBook);
}

void CGbWzdAiTool::DvmFilterByExtendKeys()
{
	m_oDvmMatchListFilter.RemoveAll();

	if (m_listExtendXKeys.GetCount() == 0)
	{
		m_oDvmMatchListFilter.Append(m_oDvmMatchList);
	}
	else
	{
		m_oDvmMatchListFilter.Append(m_oDvmMatchList);
	}
}

//�ܵĽӿ�
BOOL CGbWzdAiTool::GbWzdAi(const CString &strAiFile, CDataGroup *pMacroParas)
{
	if (m_strCurrAiFile == strAiFile)
	{
		SetMacroParasByAI(pMacroParas);
		return TRUE;
	}

	if (! IsFileExist(strAiFile))
	{
		return FALSE;
	}

	m_strCurrAiFile = strAiFile;
	OpenGbWzdAiFile(strAiFile);
	SetMacroParasByAI(pMacroParas);

	return TRUE;
}

void CGbWzdAiTool::InitDvmMatchList(CDvmDataset *pDvmDataset)
{
	CXMatchList oList;

	if (Px_JdgDataset(pDvmDataset->m_strID, PX_DSID_dsParameter))
	{
		oList.Init(pDvmDataset, m_pKeyDB);
		m_oParameterMatchList.Append(oList);
		oList.RemoveAll();

		return;
	}

	if (Px_JdgDataset(pDvmDataset->m_strID, PX_DSID_dsSetting))
	{
		oList.Init(pDvmDataset, m_pKeyDB);
		m_oDvmMatchList.Append(oList);
		oList.RemoveAll();

		return;
	}

}

DWORD CGbWzdAiTool::ScptCalEx(CXMatchList *pDvmMatchListFilter, BOOL bAllMatchMode, CSttGuideBook *pSttGuideBook)
{
	POS pos = GetHeadPosition();
	CGbAiOptrInterface *p = NULL;

	while (pos != NULL)
	{
		p = (CGbAiOptrInterface *)GetNext(pos);
		p->ScptCalEx(pDvmMatchListFilter, TRUE, pSttGuideBook);
	}

	return 0;
}

