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

	//遍历所有逻辑设备，获取定值数据集、装置参数数据集，分析各数据集的关键字
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

//打开智能向导文件
void CGbWzdAiTool::OpenGbWzdAiFile(const CString &strAiFile)
{
	//第一步：打开智能向导文件
	OpenXmlFile(strAiFile, CGbSmartGenWzdXmlRWKeys::g_pGbSmartGenWzdKeys);

	//第二步，遍历每个CGbAiParaScript对象，初始化智能判断运算操作数据树的所有Key
	InitGbAiDataKey();
}

//通过测试功能参数文件，打开智能向导文件，例如：测试功能参数文件为：Distance_Paras.xml
//则智能向导文件为：Distance_Paras_ai.xml
void CGbWzdAiTool::OpenGbWzdFileByMacroParaFile(const CString &strUIFile)
{
	
}

//设置扩展关键字，过滤设备数据模型中的数据，主要是定值数据
void CGbWzdAiTool::SetExtendKeys(const CString &strExtendKeys)
{
	m_pKeyDB->QueryKeys(strExtendKeys, &m_listExtendXKeys);
}

void CGbWzdAiTool::AddExtendKeys(const CString &strExtendKeys)
{
	
}

//根据设备数据模型，智能设置测试功能的参数
void CGbWzdAiTool::SetMacroParasByAI(CDataGroup *pMacroParas)
{
	//清空脚本计算的状态：
	ClearScptState();

	//第一步：遍历每个Data
	InitMacroPara(pMacroParas);

	//第二步：智能配置参数：属于第一遍遍历，主要针对Tool对象下的Para对象以及Switch对象
	SetMacroParasValueByAI(&m_oDvmMatchListFilter, m_pSttGuideBook);

	//第三步：智能配置参数，属于第二遍遍历，主要针对Tool对象下的switch对象，执行各case对象下para对象的智能设置
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

//总的接口
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

