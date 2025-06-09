#include "StdAfx.h"
#include "GbMacroGenWzd.h"
#include "../../../../SttStudio/Module/SttGlobalDef.h"
#include "../../../../Module/API/GlobalConfigApi.h"

#include "GbSmartGenWzd.h"

extern CGbSmartGenWzd *g_theGbSmartGenWzd;


CGbMacroGenWzd* gb_wzd_curr_macro_gen()
{
	return g_theGbSmartGenWzd->m_pCurrGbMacroGenWzd;
}


CGbMacroGenWzd::CGbMacroGenWzd(void)
{
	m_nRptTitle = 0;
	m_nTitleLevel = 1;
	m_nRepeatTimes = 0;   //重复测试次数
	m_pCmdGenParas = NULL;
	m_pCmdCfg = NULL;
	m_pMacroUIParas = NULL;
	m_pMacroUIAttrs = NULL;
	m_pCharacteristic = NULL;
	m_pCurrSetpWzd = NULL;

	//参数对象以及根节点
	m_pCmdGenParas = GetCmdGenParas();
	GetFirstStep();

	//通信命令选择 配置
	InitCommCmdCfg();

	//自身属性对象
	m_pMacroUIParas = GetMacroUIParas();
	m_pMacroUIAttrs = GetMacroUIAttrs();
}

CGbMacroGenWzd::~CGbMacroGenWzd(void)
{

}

long CGbMacroGenWzd::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CGbSmartGenWzdXmlRWKeys *pXmlKeys = (CGbSmartGenWzdXmlRWKeys*)pXmlRWKeys;
	CGbWzdXItemBase::XmlReadOwn(oNode, pXmlRWKeys);

	xml_GetAttibuteValue(pXmlKeys->m_strTestClassKey, oNode, m_strTestClass);
	xml_GetAttibuteValue(pXmlKeys->m_strTestMacroUIKey, oNode, m_strTestMacroUI);
	xml_GetAttibuteValue(pXmlKeys->m_strRepeatTimesKey, oNode, m_nRepeatTimes);
	xml_GetAttibuteValue(pXmlKeys->m_strRptTitleKey, oNode, m_nRptTitle);
	xml_GetAttibuteValue(pXmlKeys->m_strTitleLevelKey, oNode, m_nTitleLevel);

	return 0;
}

long CGbMacroGenWzd::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CGbWzdXItemBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CGbSmartGenWzdXmlRWKeys *pXmlKeys = (CGbSmartGenWzdXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strTestClassKey, oElement, m_strTestClass);
	xml_SetAttributeValue(pXmlKeys->m_strTestMacroUIKey, oElement, m_strTestMacroUI);
	xml_SetAttributeValue(pXmlKeys->m_strRepeatTimesKey, oElement, m_nRepeatTimes);
	xml_SetAttributeValue(pXmlKeys->m_strRptTitleKey, oElement, m_nRptTitle);
	xml_SetAttributeValue(pXmlKeys->m_strTitleLevelKey, oElement, m_nTitleLevel);

	return 0;
}

long CGbMacroGenWzd::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CGbWzdXItemBase::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		//BinarySerializeCalLen(oBinaryBuffer, m_strDataType);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		//BinarySerializeRead(oBinaryBuffer, m_strDataType);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		//BinarySerializeWrite(oBinaryBuffer, m_strDataType);
	}

	return 0;
}

void CGbMacroGenWzd::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);

		if (p->m_strID == STT_CMD_PARA_CmdGenParas)
		{
			m_pCmdGenParas = (CDataGroup*)p;
		}
		else if (p->m_strID == STT_CMD_PARA_CmdGenCfg)
		{
			m_pCmdCfg = (CDataGroup*)p;
		}
		else if (p->m_strID == STT_CMD_PARA_MacroUIParas)
		{
			m_pMacroUIParas = (CDataGroup*)p;
		}
		else if (p->m_strID == STT_CMD_PARA_TestMacroUI)
		{
			m_pMacroUIAttrs = (CDataGroup*)p;
		}
		else if (p->m_strID == STT_CMD_PARA_Characteristic)
		{
			m_pCharacteristic = (CDvmContents*)p;
		}
	}
}

BOOL CGbMacroGenWzd::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CGbWzdXItemBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CGbMacroGenWzd *p = (CGbMacroGenWzd*)pObj;

	if (m_nRepeatTimes != p->m_nRepeatTimes)
	{
		return FALSE;
	}

	if (m_nRptTitle != p->m_nRptTitle)
	{
		return FALSE;
	}

	if (m_nTitleLevel != p->m_nTitleLevel)
	{
		return FALSE;
	}

	if (m_strTestClass != p->m_strTestClass)
	{
		return FALSE;
	}

	if (m_strTestMacroUI != p->m_strTestMacroUI)
	{
		return FALSE;
	}

	if (m_strParentItemsID != p->m_strParentItemsID)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CGbMacroGenWzd::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CGbWzdXItemBase::CopyOwn(pDest);

	CGbMacroGenWzd *p = (CGbMacroGenWzd*)pDest;
	p->m_strTestClass = m_strTestClass;
	p->m_strTestMacroUI = m_strTestMacroUI;
	p->m_strParentItemsID = m_strParentItemsID;
	p->m_nRepeatTimes = m_nRepeatTimes;
	p->m_nRptTitle = m_nRptTitle;
	p->m_nTitleLevel = m_nTitleLevel;

	return TRUE;
}

CBaseObject* CGbMacroGenWzd::Clone()
{
	CGbMacroGenWzd *p = new CGbMacroGenWzd();
	Copy(p);
	return p;
}

CBaseObject* CGbMacroGenWzd::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CGbMacroGenWzd *p = new CGbMacroGenWzd();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

CExBaseObject* CGbMacroGenWzd::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CGbSmartGenWzdXmlRWKeys *pXmlKeys = (CGbSmartGenWzdXmlRWKeys*)pXmlRWKeys;

	pNew = CGbWzdXItemBase::CreateNewChild(strClassID, bAddToTail, pXmlRWKeys);

	return pNew;
}

CExBaseObject* CGbMacroGenWzd::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;

	pNew = CGbWzdXItemBase::CreateNewChild(nClassID);

	return pNew;
}

CString CGbMacroGenWzd::GetInitXmlFile()
{
	CString strFile;
	strFile = _P_GetConfigPath();
	strFile += _T("GbMacroGenWzd.xml");

	return strFile;
}

void CGbMacroGenWzd::OpenInitXmlFile()
{
	CString strFile = GetInitXmlFile();

	CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData++;
	CGbSmartGenWzdXmlRWKeys::g_pGbSmartGenWzdKeys->m_nIsGroupUseDvmData++;
	OpenXmlFile(strFile, CGbSmartGenWzdXmlRWKeys::g_pGbSmartGenWzdKeys);
	CGbSmartGenWzdXmlRWKeys::g_pGbSmartGenWzdKeys->m_nIsGroupUseDvmData--;
	CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData--;

}

void CGbMacroGenWzd::SaveInitXmlFile()
{
	CString strFile = GetInitXmlFile();
	SaveXmlFile(strFile, CGbSmartGenWzdXmlRWKeys::g_pGbSmartGenWzdKeys);
}

void CGbMacroGenWzd::InitGbMacroGenWzd(CGbMacroGenWzd *pSrc)
{
	m_strTestClass = pSrc->m_strTestClass;

	m_pCmdCfg->DeleteAll();
	m_pCmdCfg->AppendCloneEx(*(pSrc->m_pCmdCfg));
}

//////////////////////////////////////////////////////////////////////////
//
CSttCmdWzd_Step* CGbMacroGenWzd::GetFirstStep()
{
	CSttCmdWzd_Step *pRoot = (CSttCmdWzd_Step*)m_oListCmdWzdStep.GetHead();

	if (pRoot == NULL)
	{
		pRoot = new CSttCmdWzd_Step();
		pRoot->m_strID = m_pCmdGenParas->m_strID;
		pRoot->m_strName = m_pCmdGenParas->m_strName;
		pRoot->m_pCmdGrpRef = m_pCmdGenParas;
		m_oListCmdWzdStep.AddHead(pRoot);
		pRoot->SetParent(&m_oListCmdWzdStep);
	}

	m_pCurrSetpWzd = pRoot;

	return pRoot;
}


void CGbMacroGenWzd::OnAtsGenerateItems_CmdWzd(CExBaseList *pCmdGrp)
{
	m_pCmdGenParas->DeleteAll();
	m_pCmdGenParas->AppendCloneEx2(*pCmdGrp, TRUE, TRUE, TRUE);
	m_oListCmdWzdStep.DeleteAll();
	GetFirstStep();
	InitCmdWzdRef(m_pCmdGenParas);

// 	CString strFile;
// 	strFile = _P_GetDBPath();
// 	strFile += _T("GbMacroGenWzd.xml");
// 	m_pCmdGenParas->SaveXmlFile(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);
}

CSttCmdWzd_Step* CGbMacroGenWzd::GetRelatedStep(CSttCmdWzd_Step *pStep)
{
	if (pStep->m_pCmdGrpRef->m_strDataType != COMMCMD_RWOPTR_WRITE
		|| pStep->m_strType != _T("_BeforeTest_"))
	{
		return NULL;
	}

	CSttCmdWzd_Step* pFind = NULL;
	POS pos = m_oListCmdWzdStep.GetHeadPosition();
	//写指令，只有一个关联数据集，因此可以直接GetHead
	CDataGroup *pGrpDsSrc = (CDataGroup *)pStep->m_pCmdGrpRef->GetHead(); 
	CString strDsPath = pGrpDsSrc->m_strID;

	while (pos != NULL)
	{
		CSttCmdWzd_Step* p = (CSttCmdWzd_Step *)m_oListCmdWzdStep.GetNext(pos);

		if (p->m_strType != _T("_AfterTest_")
			|| p->m_pCmdGrpRef->m_strDataType != COMMCMD_RWOPTR_WRITE)
		{
			continue;
		}

		//写指令，只有一个关联数据集，因此可以直接GetHead
		CDataGroup *pGrpDs = (CDataGroup *)p->m_pCmdGrpRef->GetHead(); 

		if (pGrpDs->m_strID == strDsPath)
		{
			pFind = p;
			break;
		}
	}

	return pFind;
}

void CGbMacroGenWzd::InitCmdWzdRef(CDataGroup *pRoot)
{
	CDataGroup *pBFT = (CDataGroup *)pRoot->FindByID(STT_CMD_PARA_Before_Test);
	CDataGroup *pAFT = (CDataGroup *)pRoot->FindByID(STT_CMD_PARA_After_Test);

	if (pBFT != NULL)
	{
		//m_oListCmdWzdRef.Append(*pBFT);
		InitCmdWzdRefEx(pBFT);
	}

	if (pAFT != NULL)
	{
		//m_oListCmdWzdRef.Append(*pAFT);
		InitCmdWzdRefEx(pAFT);
	}
}


void CGbMacroGenWzd::InitCmdWzdRefEx(CDataGroup *pA_Bft)
{
	if (pA_Bft == NULL)
	{
		return;
	}

	POS pos = pA_Bft->GetHeadPosition();
	CSttCmdWzd_Step *pCmdDatasets = NULL;

	QMap<CString, CSttCmdWzd_Step*> oTempIDList;

	while (pos != NULL)
	{
		CDataGroup *pCmdGrp = (CDataGroup *)pA_Bft->GetNext(pos);
		if(CSttCmdWzd_Step* pStep = oTempIDList.take(pCmdGrp->m_strID))
		{
			//相同的项目合并到第一个集合
			CDataGroup* pFirstGroup = (CDataGroup*)pStep->m_pCmdGrpRef->GetHead();
			CDataGroup* pGroup = (CDataGroup*)pCmdGrp->GetHead();
			POS posData = pGroup->GetHeadPosition();
			while (posData)
			{
				CExBaseObject* pDataObj = pGroup->GetNext(posData);
				pFirstGroup->AddTail(pDataObj);
			}
			pGroup->RemoveAll();
			delete pStep->m_pCmdGrpBk;
			pStep->m_pCmdGrpBk = (CDataGroup *)pStep->m_pCmdGrpRef->CloneEx(TRUE, TRUE);
			oTempIDList.insert(pStep->m_strID, pStep);
			continue;
		}

		pCmdDatasets = new CSttCmdWzd_Step;
		pCmdDatasets->m_pCmdGrpRef = pCmdGrp;
		pCmdDatasets->m_pCmdGrpBk = (CDataGroup *)pCmdGrp->CloneEx(TRUE, TRUE);
		pCmdDatasets->m_strID = pCmdGrp->m_strID;
		pCmdDatasets->m_strType = pA_Bft->m_strID;

		//write、read、register
		if (pCmdGrp->m_strDataType != COMMCMD_RWOPTR_WRITE)
		{
			POS pos2 = pCmdGrp->GetHeadPosition();

			while (pos2 != NULL)
			{
				CDataGroup *pObj = (CDataGroup *)pCmdGrp->GetNext(pos2);
				CSttCmdWzd_CmdDataset *pCmdDataset = new CSttCmdWzd_CmdDataset;
				pCmdDataset->m_pCmdGrpRef = pObj;
				pCmdDataset->m_strID = pObj->m_strID;
				pCmdDatasets->AddNewChild(pCmdDataset);
			}
		}

		m_oListCmdWzdStep.AddTail(pCmdDatasets);
		oTempIDList.insert(pCmdDatasets->m_strID, pCmdDatasets);
	}
}


BOOL CGbMacroGenWzd::IsLastSetp()
{
	long nIndex = m_oListCmdWzdStep.FindIndex(m_pCurrSetpWzd);

	if (nIndex == m_oListCmdWzdStep.GetCount() - 1)
	{
		return TRUE;
	}

	while (CSttCmdWzd_Step* pCurrSetpWzd = (CSttCmdWzd_Step*)m_oListCmdWzdStep.GetAt(++nIndex))
	{
		CExBaseObject *pParent = (CExBaseObject *)pCurrSetpWzd->m_pCmdGrpRef->GetParent();

		if (pParent == NULL)
		{
			//误差限设置页面
			return FALSE;
		}

		if (pParent->m_strID == GBID_AfterTest_)
		{
			//通讯后，自动适配，不开放给用户设置
			return TRUE;
		}
		else if(pCurrSetpWzd->m_pCmdGrpRef->m_strDataType == COMMCMD_RWOPTR_READ
			|| pCurrSetpWzd->m_pCmdGrpRef->m_strDataType == COMMCMD_RWOPTR_REGISTER)
		{
			continue;
		}
		else
		{
			break;
		}
	}

	return FALSE;
}

BOOL CGbMacroGenWzd::IsFirstSetp()
{
	if (m_pCurrSetpWzd == m_oListCmdWzdStep.GetHead())
	{
		return TRUE;
	}

	return FALSE;
}

BOOL CGbMacroGenWzd::HasStepNeedShow()
{
	if (m_oListCmdWzdStep.GetCount() == 0)
	{
		return FALSE;
	}

	POS pos = m_oListCmdWzdStep.GetHeadPosition();

	while (pos != NULL)
	{
		CSttCmdWzd_Step *pStep = (CSttCmdWzd_Step *)m_oListCmdWzdStep.GetNext(pos);

		if (pStep->m_strID == STT_CMD_PARA_CmdGenParas)
		{
			//跳过ROOT步骤
			continue;
		}

		if (pStep->m_pCmdGrpRef->m_strDataType.IsEmpty()
			|| pStep->m_pCmdGrpRef->m_strDataType == COMMCMD_RWOPTR_WRITE)
		{
			//为空表示是误差设置页面
			return TRUE;
		}
	}

	return FALSE;
}

BOOL CGbMacroGenWzd::IsFirstSetp(CSttCmdWzd_Step *pStep)
{
	if (pStep == m_oListCmdWzdStep.GetHead())
	{
		return TRUE;
	}

	return FALSE;
}

CSttCmdWzd_Step* CGbMacroGenWzd::GetNextStep()
{
	if (m_pCurrSetpWzd == NULL)
	{
		return NULL;
	}

	long nIndex = m_oListCmdWzdStep.FindIndex(m_pCurrSetpWzd);

	m_pCurrSetpWzd = (CSttCmdWzd_Step *)m_oListCmdWzdStep.GetAtIndex(nIndex + 1);
	return m_pCurrSetpWzd;
}

CSttCmdWzd_Step* CGbMacroGenWzd::GetPreStep()
{
	long nIndex = 0;

	if (m_pCurrSetpWzd == NULL)
	{
		nIndex = m_oListCmdWzdStep.GetCount() - 1;
	}
	else
	{
		nIndex = m_oListCmdWzdStep.FindIndex(m_pCurrSetpWzd);
	}

	m_pCurrSetpWzd = (CSttCmdWzd_Step *)m_oListCmdWzdStep.GetAtIndex(nIndex - 1);
	return m_pCurrSetpWzd;
}


/*
pCommCmdCfg的数据结构如下：

<group name="测试前准备" id="cmd-bft" data-type="cmd-bft">
	<data name="读定值" id="ReadSetting" format="dsSetting" value="ReadSetting"/>
	<data name="读软压板" id="ReadEna" format="dsEna" value="ReadEna"/>
	<data name="修改定值" id="WriteSetting" format="dsSetting" value="WriteSetting"/>
	<data name="投退软压板" id="WriteEna" format="dsEna" value="WriteEna"/>
	<data name="读装置参数" id="ReadParameter" format="dsParameter" value="ReadParameter"/>
	<data name="修改装置参数" id="WriteParameter" format="dsParameter" value="WriteParameter"/>
	<data name="启动报告" id="RegisterReport" format="all" value="RegisterReport"/>
	<data name="停止报告" id="UnRegisterReport" format="all" value="UnRegisterReport"/>
</group>
<group name="测试后恢复" id="cmd-aft" data-type="cmd-aft">
	<data name="修改定值" id="WriteSetting" format="dsSetting" value="WriteSetting"/>
	<data name="投退软压板" id="WriteEna" format="dsEna" value="WriteEna"/>
	<data name="修改装置参数" id="WriteParameter" format="dsParameter" value="WriteParameter"/>
	<data name="停止报告" id="UnRegisterReport" format="all" value="UnRegisterReport"/>
</group>
*/
void CGbMacroGenWzd::NextClick_Init(CDataGroup &oCommCmd, BOOL bAdd_AFT)
{
	CDataGroup *pBFT = (CDataGroup *)m_pCmdCfg->FindByID(STT_CMD_PARA_CMDBFT);

	//if (pBFT->m_dwReserved == 1)
	//2022-9-12  lijuniqng  使用m_dwReserved不能保存到文件，所以使用Value属性
	if (dvm_GetDvmX_Value_long(pBFT) == 1)
	{
		CDataGroup *pNew = oCommCmd.AddNewGroup(STT_CMD_PARA_Before_Test, STT_CMD_PARA_Before_Test, _T(""));
		POS pos = pBFT->GetHeadPosition();

		while (pos != NULL)
		{
			CDvmData *pData = (CDvmData *)pBFT->GetNext(pos);

			//2022-9-12  lijuniqng  使用m_dwReserved不能保存到文件，所以使用Value属性
			//if (pData->m_dwReserved == 1)
			if (dvm_GetDvmX_Value_long(pData) == 1)
			{
				pNew->AddNewData(pData->m_strID, _T("1"));
			}
		}
	}

	if (!bAdd_AFT)
	{
		//不添加测试后恢复，则删除测试后恢复的配置
		//不能删，删了之后通过上一次的记录去初始化时，会出现问题
		//m_pCmdCfg->DeleteByID(STT_CMD_PARA_CMDAFT);
		return;
	}

	CDataGroup *pAFT = (CDataGroup *)m_pCmdCfg->FindByID(STT_CMD_PARA_CMDAFT);

	//2022-9-12  lijuniqng  使用m_dwReserved不能保存到文件，所以使用Value属性
	//if (pAFT->m_dwReserved == 1)
	if (dvm_GetDvmX_Value_long(pAFT) == 1)
	{
		CDataGroup *pNew = oCommCmd.AddNewGroup(STT_CMD_PARA_After_Test, STT_CMD_PARA_After_Test, _T(""));
		POS pos = pAFT->GetHeadPosition();

		while (pos != NULL)
		{
			CDvmData *pData = (CDvmData *)pAFT->GetNext(pos);

			//2022-9-12  lijuniqng  使用m_dwReserved不能保存到文件，所以使用Value属性
			//if (pData->m_dwReserved == 1)
			if (dvm_GetDvmX_Value_long(pData) == 1)
			{
				pNew->AddNewData(pData->m_strID, _T("1"));
			}
		}
	}
}

void CGbMacroGenWzd::NextClick_Finish(CDataGroup &oCommCmd)
{
	//结束发送GenerateItems报文，带comm-cmd参数
	CDataGroup *pBft = oCommCmd.AddNewGroup(STT_CMD_PARA_Before_Test, STT_CMD_PARA_Before_Test, _T(""));
	CDataGroup *pAft = oCommCmd.AddNewGroup(STT_CMD_PARA_After_Test, STT_CMD_PARA_After_Test, _T(""));

	POS pos = m_oListCmdWzdStep.GetHeadPosition();
	CSttCmdWzd_Step *pCmdDatasets = NULL;
	m_oListCmdWzdStep.GetNext(pos);   //跳过ROOT节点

	if (pos == NULL)
	{
		//没勾选任何通讯命令
		oCommCmd.DeleteAll();
	}

	CExBaseList oTempList;
	oTempList.Append((CDataGroup*)m_pCmdGenParas->GetHead());

	if (m_pCmdGenParas->GetCount() > 1)
	{
		oTempList.Append((CDataGroup*)m_pCmdGenParas->GetTail());
	}

	//WriteSetting
	long nIndex = 0;
	while (pos != NULL)
	{
		pCmdDatasets = (CSttCmdWzd_Step *)m_oListCmdWzdStep.GetNext(pos);
		CDataGroup *pParent = (CDataGroup *)pCmdDatasets->m_pCmdGrpRef->GetParent();

		if(!pParent)
		{
			continue;
		}

		while(oTempList.GetAt(nIndex) != pCmdDatasets->m_pCmdGrpRef)
		{
			//合并项只有write
			CDataGroup* pGroup = (CDataGroup*)oTempList.GetAt(nIndex);
			CDataGroup* pParentGroup = (CDataGroup*)pGroup->GetParent();
			CSttCmdWzd_Step oTempStep;
			oTempStep.m_pCmdGrpRef = pGroup;
			if (pParentGroup->m_strID == STT_CMD_PARA_Before_Test)
			{
				InitGenerateItemsParas(&oTempStep, pBft);
			}
			else
			{
				InitGenerateItemsParas(&oTempStep, pAft);
			}
			nIndex++;
		}

		if (pParent->m_strID == STT_CMD_PARA_Before_Test)
		{
			InitGenerateItemsParas(pCmdDatasets, pBft);
		}
		else
		{
			InitGenerateItemsParas(pCmdDatasets, pAft);
		}

		nIndex++;
	}

	//Ena
	while(nIndex < oTempList.GetCount())
	{
		//合并项只有write
		CDataGroup* pGroup = (CDataGroup*)oTempList.GetAt(nIndex);
		CDataGroup* pParentGroup = (CDataGroup*)pGroup->GetParent();
		CSttCmdWzd_Step oTempStep;
		oTempStep.m_pCmdGrpRef = pGroup;
		if (pParentGroup->m_strID == STT_CMD_PARA_Before_Test)
		{
			InitGenerateItemsParas(&oTempStep, pBft);
		}
		else
		{
			InitGenerateItemsParas(&oTempStep, pAft);
		}
		nIndex++;
	}

	oTempList.RemoveAll();
}

void CGbMacroGenWzd::InitGenerateItemsParas(CSttCmdWzd_Step *pCmdDatasets, CDataGroup *pA_Bft)
{
	CDataGroup *pNewCmdGrp = new CDataGroup;
	pCmdDatasets->m_pCmdGrpRef->CopyOwn(pNewCmdGrp);
	pA_Bft->AddNewChild(pNewCmdGrp);

	//write指令，过滤掉value = NULL的数据
	if (pCmdDatasets->m_pCmdGrpRef->m_strDataType == COMMCMD_RWOPTR_WRITE)
	{
		CDataGroup *pDs = (CDataGroup *)pCmdDatasets->m_pCmdGrpRef->GetHead();  //写指令指关联一个数据集
		CDataGroup *pNewDs = new CDataGroup;
		pDs->CopyOwn(pNewDs);
		pNewCmdGrp->AddNewChild(pNewDs);

		if (pCmdDatasets->m_nZoneIndex != -1)
		{
			pNewCmdGrp->AddNewData(STT_CMD_PARA_ZoneIndex, pCmdDatasets->m_nZoneIndex);
		}

		CString strDelay = pCmdDatasets->m_strDelayBft;

		if (strDelay.IsEmpty())
		{
			strDelay = _T("0");
		}

		pNewCmdGrp->AddNewData(STT_CMD_PARA_DelayBeforeCmd, strDelay);

		strDelay = pCmdDatasets->m_strDelayAft;

		if (strDelay.IsEmpty())
		{
			strDelay = _T("0");
		}

		pNewCmdGrp->AddNewData(STT_CMD_PARA_DelayAfterCmd, strDelay);

		POS pos = pDs->GetHeadPosition();

		while (pos != NULL)
		{
			CDvmData *pData = (CDvmData *)pDs->GetNext(pos);

			if (pData->m_strValue.IsEmpty())
			{
				continue;
			}

			pNewDs->AddNewData(pData->m_strName, pData->m_strID, pData->m_strDataType, pData->m_strValue);
		}

		if (pNewDs->GetCount() == 0)
		{
			pA_Bft->Delete(pNewCmdGrp);
		}

		return;
	}

	//read和register，需要根据勾选确认参数
	POS pos = pCmdDatasets->GetHeadPosition();

	while (pos != NULL)
	{
		CSttCmdWzd_CmdDataset *pCmdDataset = (CSttCmdWzd_CmdDataset *)pCmdDatasets->GetNext(pos);

		if (pCmdDataset->m_nSelect != 1)
		{
			continue;
		}

		CDataGroup *pDs = pNewCmdGrp->AddNewGroup(pCmdDataset->m_pCmdGrpRef->m_strName, pCmdDataset->m_pCmdGrpRef->m_strID, pCmdDataset->m_pCmdGrpRef->m_strDataType);

		if (pCmdDatasets->m_strID == _T("RegisterReport"))
		{
			pDs->AddNewData(STT_CMD_PARA_TrgOps_4, pCmdDataset->m_nPeriod);   //周期上送
			pDs->AddNewData(STT_CMD_PARA_TrgOps_2, pCmdDataset->m_nQuqlity);   //品质上送
			pDs->AddNewData(STT_CMD_PARA_TrgOps_1, pCmdDataset->m_nChange);   //突变上送
			pDs->AddNewData(STT_CMD_PARA_IntgPd, pCmdDataset->m_nPeriod_Time);   //周期上送时间
		}
	}

	if (pCmdDatasets->m_nZoneIndex != -1)
	{
		pNewCmdGrp->AddNewData(STT_CMD_PARA_ZoneIndex, pCmdDatasets->m_nZoneIndex);
	}

	pNewCmdGrp->AddNewData(STT_CMD_PARA_DelayBeforeCmd, "2000");
	pNewCmdGrp->AddNewData(STT_CMD_PARA_DelayAfterCmd, "2000");
}


void CGbMacroGenWzd::InitCommCmdCfg()
{
	if (m_pCmdCfg != NULL)
	{
		return;
	}

	m_pCmdCfg = new CDataGroup;
	m_pCmdCfg->AppendCloneEx2(*g_theGbSmartGenWzd->m_pCommCmdCfg, TRUE, TRUE);  //SttCommCmdCfg.xml
	m_pCmdCfg->DeleteByID(STT_CMD_PARA_CMDSINGLE); 
	AddNewChild(m_pCmdCfg);
	m_pCmdCfg->m_strName = STT_CMD_PARA_CmdGenCfg;
	m_pCmdCfg->m_strID = STT_CMD_PARA_CmdGenCfg;
	m_pCmdCfg->m_strDataType = STT_CMD_PARA_CmdGenCfg;
}

CDataGroup* CGbMacroGenWzd::GetCmdGenParas()
{
	if (m_pCmdGenParas == NULL)
	{
		m_pCmdGenParas = AddNewGroup(_T("选择测试功能和通讯命令"), STT_CMD_PARA_CmdGenParas, STT_CMD_PARA_CmdGenParas);
	}

	return m_pCmdGenParas;
}

CDataGroup* CGbMacroGenWzd::GetCmdCfg()
{
	return m_pCmdCfg;
}

CDataGroup* CGbMacroGenWzd::GetMacroUIParas()
{
	if (m_pMacroUIParas == NULL)
	{
		m_pMacroUIParas = AddNewGroup(STT_CMD_PARA_MacroUIParas,STT_CMD_PARA_MacroUIParas, STT_CMD_PARA_MacroUIParas);
	}

	return m_pMacroUIParas;
}

CDataGroup* CGbMacroGenWzd::GetMacroUIAttrs()
{
	if (m_pMacroUIAttrs == NULL)
	{
		m_pMacroUIAttrs = AddNewGroup(STT_CMD_PARA_TestMacroUI,STT_CMD_PARA_TestMacroUI, STT_CMD_PARA_TestMacroUI);
	}

	return m_pMacroUIAttrs;
}

CDvmContents* CGbMacroGenWzd::GetCharacteristic()
{
	if (m_pCharacteristic == NULL)
	{
		m_pCharacteristic = new CDvmContents();
		AddNewChild(m_pCharacteristic);
		m_pCharacteristic->m_strName = STT_CMD_PARA_Characteristic;
		m_pCharacteristic->m_strID = STT_CMD_PARA_Characteristic;
		m_pCharacteristic->m_strDataType = STT_CMD_PARA_Characteristic;
	}

	return m_pCharacteristic;
}

// CDvmData* CGbMacroGenWzd::GetCmdCfgData(const CString &strCmdID)
// {
// 	CDataGroup *pGroupBft = (CDataGroup*)m_pCmdCfg->FindByID(STT_CMD_PARA_CMDBFT);
// 
// 	if (pGroupBft == NULL)
// 	{
// 		return NULL;
// 	}
// 
// 	CDvmData *pFind = (CDvmData*)pGroupBft->FindByID(strCmdID);
// 
// 	return pFind;
// }

/*
<macro-gen id="" data-type="" value="" test-class="精度测试" items-name="ww" items-id="ww" test-macro-ui-id="ManualTest" parent-items-id="">
	<group id="cmd-gen-paras" data-type="cmd-gen-paras" value="">
		<group id="_BeforeTest_" data-type="" value="">
			<group id="WriteSetting" data-type="write" value="">
				<group id="XLBH931PROT$LLN0$dsSetting" data-type="" value="">
					<data id="LLN0$SG$DPFCStr" data-type="STRUCT" value="0.200000" />
					<data id="LLN0$SG$ROCStr" data-type="STRUCT" value="0.200000" />
					<data id="PDIF1$SG$StrValSG" data-type="STRUCT" value="10.000000" />
*/
void CGbMacroGenWzd::AddDataToWzdCmd(const CString &strItemsID, const CString &strCommCmdID, const CString &strDatasetPath, CDvmData *pData)
{
	CDataGroup *pDataset = FindGroup_Dataset(strItemsID, strCommCmdID, strDatasetPath);

	//对应ID = 数据集路径的group
	if (pDataset == NULL)
	{
		return;
	}

	CDvmData *pFind = (CDvmData*)pDataset->FindByID(pData->m_strID);

	if (pFind != NULL)
	{
		if (pData->m_strValue.IsEmpty())
		{
			//删除值为空的
			pDataset->Delete(pFind);
			return;
		}

		pFind->m_strValue = pData->m_strValue;
		return;
	}

	//此处只需要拷贝自身即可
	pFind = (CDvmData*)pData->CloneEx(TRUE, FALSE);
	pDataset->AddNewChild(pFind);
}

void CGbMacroGenWzd::AddDataToWzdCmd(const CString &strItemsID, const CString &strCommCmdID, const CString &strDatasetPath, CValue *pValue)
{
	CDataGroup *pDataset = FindGroup_Dataset(strItemsID, strCommCmdID, strDatasetPath);

	//对应ID = 数据集路径的group
	if (pDataset == NULL)
	{
		return;
	}

	CDvmData *pFind = (CDvmData*)pDataset->FindByID(pValue->m_strID);

	if (pFind != NULL)
	{
		if (pValue->m_strValue.IsEmpty())
		{
			//删除值为空的
			pDataset->Delete(pFind);
			return;
		}

		pFind->m_strValue = pValue->m_strValue;
		return;
	}

	pFind = new CDvmData();
	pFind->m_strValue = pValue->m_strValue;
	pFind->m_strID = pValue->m_strID;
	pDataset->AddNewChild(pFind);
}

void CGbMacroGenWzd::DeleteDataFromWzdCmd(const CString &strItemsID, const CString &strCommCmdID, const CString &strDatasetPath, const CString &strDataID)
{
	CDataGroup *pDataset = FindGroup_Dataset(strItemsID, strCommCmdID, strDatasetPath);

	//对应ID = 数据集路径的group
	if (pDataset == NULL)
	{
		return;
	}

	pDataset->DeleteByID(strDataID);
}

void CGbMacroGenWzd::UpdateDataToWzdCmdCfg(const CString &strItemsID, const CString &strCommCmdID, const CString &strDatasetPath, CDvmData *pDvmData)
{
	CDataGroup *pDataset = FindGroup_Dataset(strItemsID, strCommCmdID, strDatasetPath);

	//对应ID = 数据集路径的group
	if (pDataset == NULL)
	{
		return;
	}

	CDvmData *pFind = (CDvmData*)pDataset->FindByID(pDvmData->m_strID);

	if (pFind != NULL)
	{
		pFind->m_strValue = pDvmData->m_strValue;
	}
}

void CGbMacroGenWzd::DeleteAllDatasToWzdCmdCfg(const CString &strItemsID, const CString &strCommCmdID, const CString &strDatasetPath)
{
	CDataGroup *pDataset = FindGroup_Dataset(strItemsID, strCommCmdID, strDatasetPath);

	//对应ID = 数据集路径的group
	if (pDataset != NULL)
	{
		pDataset->DeleteAll();
	}
}

void CGbMacroGenWzd::UpdateZoneIndexToWzdCmdCfg(const CString &strItemsID, const CString &strCommCmdID, const CString &strDatasetPath, int nZoneIndex)
{
	CDvmData *pZoneIndex = FindData_ZoneIndex(strItemsID, strCommCmdID, strDatasetPath);

	if (pZoneIndex != NULL)
	{
		pZoneIndex->m_strValue.Format(_T("%d"), nZoneIndex);
	}
}

void CGbMacroGenWzd::UpdateDelayBftToWzdCmdCfg(const CString &strItemsID, const CString &strCommCmdID, const CString &strDatasetPath, const CString &strDelay)
{
	CDvmData *pDelay = FindData_DelayBftCmd(strItemsID, strCommCmdID, strDatasetPath);

	if (pDelay != NULL)
	{
		pDelay->m_strValue = strDelay;
	}
}

void CGbMacroGenWzd::UpdateDelayAftToWzdCmdCfg(const CString &strItemsID, const CString &strCommCmdID, const CString &strDatasetPath, const CString &strDelay)
{
	CDvmData *pDelay = FindData_DelayAftCmd(strItemsID, strCommCmdID, strDatasetPath);

	if (pDelay != NULL)
	{
		pDelay->m_strValue = strDelay;
	}
}

////pItemsGroup对应_BeforeTest_或_AfterTest_
CDataGroup* CGbMacroGenWzd::FindGroup_Item(CDataGroup *pItemsGroup, const CString &strCommCmdID, const CString &strDatasetPath)
{
	POS pos = pItemsGroup->GetHeadPosition();
	CDataGroup *p = NULL;
	CDataGroup *pDs = NULL;

	while (pos != NULL)
	{
		p = (CDataGroup *)pItemsGroup->GetNext(pos);

		if (p->m_strID != strCommCmdID)
		{
			continue;
		}

		//此处Head有可能是zone-index的CDvmData对象
		//pDs = (CDataGroup *)p->GetHead();
		pDs = (CDataGroup *)p->FindByClassID(DTMCLASSID_CDATAGROUP);

		if (pDs == NULL)
		{
			continue;
		}

// 		if (pDs->GetClassID() != DTMCLASSID_CDATAGROUP)
// 		{
// 			continue;
// 		}

		if (pDs->m_strID == strDatasetPath)
		{
			return pDs;
		}
	}

	return NULL;
}

/*
<macro-gen id="" data-type="" value="" test-class="精度测试" items-name="ww" items-id="ww" test-macro-ui-id="ManualTest" parent-items-id="">
	<group id="cmd-gen-paras" data-type="cmd-gen-paras" value="">
		<group id="_BeforeTest_" data-type="" value="">
			<group id="WriteSetting" data-type="write" value="">
				<group id="XLBH931PROT$LLN0$dsSetting" data-type="" value="">
					<data id="LLN0$SG$DPFCStr" data-type="STRUCT" value="0.200000" />
					<data id="LLN0$SG$ROCStr" data-type="STRUCT" value="0.200000" />
					<data id="PDIF1$SG$StrValSG" data-type="STRUCT" value="10.000000" />
*/
CDataGroup* CGbMacroGenWzd::FindGroup_Dataset(const CString &strItemsID, const CString &strCommCmdID, const CString &strDatasetPath)
{
	if (m_pCmdGenParas == NULL)
	{
		return NULL;
	}

	CDataGroup *pItems = (CDataGroup*)m_pCmdGenParas->FindByID(strItemsID);

	//对应_BeforeTest_或_AfterTest_
	if (pItems == NULL)
	{
		return NULL;
	}
	
	//返回对应ID = 数据集路径的group
	return FindGroup_Item(pItems, strCommCmdID, strDatasetPath);
}

CDvmData* CGbMacroGenWzd::FindData(const CString strDataID, const CString &strItemsID, const CString &strCommCmdID, const CString &strDatasetPath)
{
	if (m_pCmdGenParas == NULL)
	{
		return NULL;
	}

	CDataGroup *pItems = (CDataGroup*)m_pCmdGenParas->FindByID(strItemsID);

	//对应_BeforeTest_或_AfterTest_
	if (pItems == NULL)
	{
		return NULL;
	}

	//返回对应ID = 数据集路径的group
	CDataGroup *pDs = FindGroup_Item(pItems, strCommCmdID, strDatasetPath);

	if (pDs == NULL)
	{
		return NULL;
	}

	CDataGroup *pCmdGrp = (CDataGroup *)pDs->GetParent();
	return (CDvmData *)pCmdGrp->FindByID(strDataID);
}

CDvmData* CGbMacroGenWzd::FindData_ZoneIndex(const CString &strItemsID, const CString &strCommCmdID, const CString &strDatasetPath)
{
	return FindData(STT_CMD_PARA_ZoneIndex, strItemsID, strCommCmdID, strDatasetPath);
// 	if (m_pCmdGenParas == NULL)
// 	{
// 		return NULL;
// 	}
// 
// 	CDataGroup *pItems = (CDataGroup*)m_pCmdGenParas->FindByID(strItemsID);
// 
// 	//对应_BeforeTest_或_AfterTest_
// 	if (pItems == NULL)
// 	{
// 		return NULL;
// 	}
// 
// 	//返回对应ID = 数据集路径的group
// 	CDataGroup *pDs = FindGroup_Item(pItems, strCommCmdID, strDatasetPath);
// 	
// 	if (pDs == NULL)
// 	{
// 		return NULL;
// 	}
// 
// 	CDataGroup *pCmdGrp = (CDataGroup *)pDs->GetParent();
// 	return (CDvmData *)pCmdGrp->FindByID(STT_CMD_PARA_ZoneIndex);
}

CDvmData* CGbMacroGenWzd::FindData_DelayBftCmd(const CString &strItemsID, const CString &strCommCmdID, const CString &strDatasetPath)
{
	return FindData(STT_CMD_PARA_DelayBeforeCmd, strItemsID, strCommCmdID, strDatasetPath);
}

CDvmData* CGbMacroGenWzd::FindData_DelayAftCmd(const CString &strItemsID, const CString &strCommCmdID, const CString &strDatasetPath)
{
	return FindData(STT_CMD_PARA_DelayAfterCmd, strItemsID, strCommCmdID, strDatasetPath);
}

/*
<macro-gen id="" data-type="" value="" test-class="精度测试" items-name="ww" items-id="ww" test-macro-ui-id="ManualTest" parent-items-id="">
	<group id="cmd-gen-paras" data-type="cmd-gen-paras" value="">
		<group id="_BeforeTest_" data-type="" value="">
			<group id="WriteSetting" data-type="write" value="">
				<group id="XLBH931PROT$LLN0$dsSetting" data-type="" value="">
					<data id="LLN0$SG$DPFCStr" data-type="STRUCT" value="0.200000" />
					<data id="LLN0$SG$ROCStr" data-type="STRUCT" value="0.200000" />
					<data id="PDIF1$SG$StrValSG" data-type="STRUCT" value="10.000000" />
*/
void CGbMacroGenWzd::ClearEmptyCmdParas(const CString &strItemsID, const CString &strCommCmdID, const CString &strDatasetPath)
{
	CDataGroup *pDataset = FindGroup_Dataset(strItemsID, strCommCmdID, strDatasetPath);

	//对应ID = 数据集路径的group
	if (pDataset == NULL)
	{
		return;
	}

	POS pos = pDataset->GetHeadPosition();

	while (pos != NULL)
	{
		CDvmData *pData = (CDvmData *)pDataset->GetNext(pos);

		if (pData->m_strValue.IsEmpty())
		{
			pDataset->Delete(pData);
		}
	}
}

//清空通讯命令配置参数后，原向导中重新生成项目时，则不添加通讯命令项目了。
void CGbMacroGenWzd::ClearAllCmdGenParas()
{
	if (m_pCmdGenParas == NULL)
	{
		return;
	}

	m_pCmdGenParas->DeleteAll();
}