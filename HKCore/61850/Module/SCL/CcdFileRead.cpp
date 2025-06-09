//#include "global.h"
#include "CcdFileRead.h"
#include "../../../Module/API/StringConvert/String_Utf8_To_Gbk.h"

//#include "../../../Module/OSInterface/QT/XMessageBox.h"

// #if _MSC_VER >= 1600
// #pragma execution_character_set("utf-8")
// #endif


CcdFileRead::CcdFileRead() 
{
	m_pSclStation = NULL;
	m_pProgressInterface = NULL;
	m_bIsInReadState = FALSE;
	m_pReadThread = NULL;
}

CcdFileRead::~CcdFileRead()
{
	FreeReadThread();
}

void CcdFileRead::FreeThreadAndDatas()
{
	FreeReadThread();
}

void CcdFileRead::FreeReadThread()
{
	if (m_pReadThread != NULL)
	{
		m_pReadThread->PostThreadMessage(WM_QUIT, 0, 0);
		m_pReadThread->wait();
		m_pReadThread = NULL;
	}
}

BOOL CcdFileRead::ReadSclFile(const CString &strSclFilePath, CSclStation *pSclStation)
{   
	m_pSclStation = pSclStation;
	m_pSclStation->DeleteAll();
	m_pSclStation->SetScdFile(strSclFilePath);
	m_pSclStation->m_strName = ParseFileName(strSclFilePath);
	m_pSclStation->m_strID = m_pSclStation->m_strName;

	FreeReadThread();
	m_bIsInReadState = TRUE;
	m_pReadThread = new CWinThread(ReadSCLThread,this);
	m_pReadThread->m_bAutoDelete = FALSE;
	m_pReadThread->start();
	return TRUE;
}

void CcdFileRead::InitThreadProgress()
{
	if (m_pProgressInterface != NULL)
	{
		m_pProgressInterface->InitThreadProgress(100,1);
		m_pProgressInterface->StepIt();
	}
}

UINT CcdFileRead::ReadSCLThread( LPVOID pParam )
{
	CcdFileRead *pSclFileRead = (CcdFileRead *)pParam;
	pSclFileRead->m_bIsInReadState = TRUE;
	CString strSclFilePath;
	strSclFilePath = pSclFileRead->m_pSclStation->GetScdFile();

	pSclFileRead->ReadSclStation(strSclFilePath);
	pSclFileRead->m_bIsInReadState = FALSE;
	return 1;
}

DWORD CcdFileRead::GetHexValue(const QString &strHexText)
{
	CString strNewHexText = strHexText;
//	strNewHexText = QString("0x%1").arg(strHexText);
	DWORD dwValue = 0;
	HexToDWORD(strNewHexText,dwValue);
	return dwValue;
}

CString CString_utf8_to_gbk(const xpugi::char_t* chtUtf8)
{
	int nGBKLenth = 0;
	char chUtf8[512] = {0};
	memcpy(chUtf8,chtUtf8, 512);
	unsigned char wszGBK[512] = {0};
	char chGBK[512] = {0};
	utf8_to_gbk((unsigned char*)chUtf8, strlen(chUtf8), (unsigned char*)wszGBK, &nGBKLenth);
	memcpy(chGBK,wszGBK , nGBKLenth);

	CString strGBK(chGBK);
	return strGBK;
}

void CcdFileRead::ReadSclStation(const CString &strSclFilePath)
{

	CSclIed *pNewIed = NULL;
	CSclCtrlsSmvOut* pCurSmvOuts = NULL;
	CSclCtrlsSmvIn*  pCurSmvIns = NULL;
	CSclCtrlsGsOut*  pCurGsOuts = NULL;
	CSclCtrlsGsIn*   pCurGsIns = NULL;

	CSclCtrlsSmvOut* pVirualSmvOuts = NULL;
	CSclCtrlsGsOut*  pVirualGsOuts = NULL;
	CSclCtrlSmvOut *pVirualSclCtrlSmvOut = NULL;
	CSclCtrlGsOut *pVirualSclCtrlGsOut = NULL;

	CSclCtrlSmvOut *pNewSclCtrlSmvOut = NULL;
	CSclCtrlGsOut *pNewSclCtrlGsOut = NULL;
	CSclCtrlSmvIn *pSclCtrlSmvIn = NULL;
	CSclCtrlGsIn *pSclCtrlGsIn = NULL;
	CSclChBase *pSclChBase = NULL;
	CSclChGs *pSclChGs = NULL;

	CSclCtrlSmvOut *pSclCtrlSmvOut = NULL;
	CSclCtrlGsOut *pSclCtrlGsOut = NULL;
	CSclChSmvIn *pSclChSmvIn = NULL;
	CSclChGsIn *pSclChGsIn = NULL;

	
	long nCurrIndex = 0;
	CString strMsgString;

	//装载SCD文件
	xpugi::xml_document oPugiDoc;
	const char *pzfFilePath = strSclFilePath.GetString();

	if (!oPugiDoc.load_file(pzfFilePath,xpugi::parse_default,xpugi::encoding_utf8))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("open SCL file(%s)failed."),strSclFilePath.GetString());
		return ;
	}

	xpugi::xpath_node_set SVP_list = oPugiDoc.select_nodes("IED/SVPUB/SMVCBref");
	xpugi::xpath_node_set GOP_list = oPugiDoc.select_nodes("IED/GOOSEPUB/GOCBref");
	xpugi::xpath_node_set SVS_list = oPugiDoc.select_nodes("IED/SVSUB/SMVCBref");
	xpugi::xpath_node_set GOS_list = oPugiDoc.select_nodes("IED/GOOSESUB/GOCBref");

	if (m_pProgressInterface != NULL)
	{
		//2024.4.22 Xuzt 修改进度条总长度
		m_pProgressInterface->InitThreadProgress(SVP_list.size()+GOP_list.size()+SVS_list.size()+GOS_list.size(),1);
		m_pProgressInterface->StepIt();
	}

	//获取IED列表
	xpugi::xml_node Cur_IED=oPugiDoc.child("IED");

	pNewIed = new CSclIed();
	m_pSclStation->AddNewChild(pNewIed);

	pNewIed->m_strID = CString_utf8_to_gbk(Cur_IED.attribute("name").value());
	pNewIed->m_strManufacturer = CString_utf8_to_gbk(Cur_IED.attribute("manufacturer").value());
	pNewIed->m_strName = CString_utf8_to_gbk(Cur_IED.attribute("desc").value());
	pNewIed->m_strModel = CString_utf8_to_gbk(Cur_IED.attribute("type").value());

	if (pNewIed->m_strName.isEmpty())
	{
		pNewIed->m_strName = pNewIed->m_strID;
	}

	pCurSmvOuts = pNewIed->GetSmvOuts();
	pCurGsOuts = pNewIed->GetGsOuts();
	pCurSmvIns = pNewIed->GetSmvIns();
	pCurGsIns = pNewIed->GetGsIns();

	//SMV 输出
	for(xpugi::xpath_node_set::const_iterator SVP_it=SVP_list.begin();
		SVP_it!=SVP_list.end();SVP_it++)
	{
		xpugi::xml_node SVP_node = SVP_it->node();

		xpugi::xml_node ConnectedAP_node=SVP_node.child("ConnectedAP");

		pNewSclCtrlSmvOut = new CSclCtrlSmvOut();
		pCurSmvOuts->AddNewChild(pNewSclCtrlSmvOut);

		xpugi::xml_node SMV_node=ConnectedAP_node.child("SMV");


		pNewSclCtrlSmvOut->apName = CString_utf8_to_gbk(ConnectedAP_node.attribute("apName").value());
		pNewSclCtrlSmvOut->m_strID = CString_utf8_to_gbk(SMV_node.attribute("cbName").value());
		pNewSclCtrlSmvOut->ldName = CString_utf8_to_gbk(SMV_node.attribute("ldInst").value());

		pNewSclCtrlSmvOut->m_dwItemData = 1;
		//Address
		xpugi::xpath_node_set Address_list=SMV_node.select_nodes("./Address/P");
		for(xpugi::xpath_node_set::const_iterator Address_it=Address_list.begin();
			Address_it!=Address_list.end();Address_it++)
		{
			xpugi::xpath_node Address_node=*Address_it;
			CString Addressstr = CString_utf8_to_gbk(Address_node.node().attribute("type").value());
			if(Addressstr=="MAC-Address")
			{
				pNewSclCtrlSmvOut->m_strMac = CString_utf8_to_gbk(Address_node.node().text().as_string());
			}
			else if(Addressstr=="VLAN-ID")
			{
				pNewSclCtrlSmvOut->scl_smv_VLANID = GetHexValue(CString_utf8_to_gbk(Address_node.node().text().as_string()));
			}
			else if(Addressstr=="APPID")
			{
				pNewSclCtrlSmvOut->m_dwAppID = GetHexValue(CString_utf8_to_gbk(Address_node.node().text().as_string()));
			}
			else if(Addressstr=="VLAN-PRIORITY")
			{
				pNewSclCtrlSmvOut->scl_smv_VLANPRI = GetHexValue(CString_utf8_to_gbk(Address_node.node().text().as_string()));
			}
		}

		//查找SampledValueControl
		xpugi::xml_node SampledValueControl_node=SVP_node.child("SampledValueControl");

		pNewSclCtrlSmvOut->m_strDataSet = CString_utf8_to_gbk(SampledValueControl_node.attribute("datSet").value());
		pNewSclCtrlSmvOut->m_strDataSetPath.Format(_T("%s%s/LLN0$%s"), pNewIed->m_strID.GetString(), pNewSclCtrlGsOut->ldName.GetString(), pNewSclCtrlGsOut->m_strDataSet.GetString());

		pNewSclCtrlSmvOut->m_strSVID = CString_utf8_to_gbk(SampledValueControl_node.attribute("appID").value());

		xpugi::xpath_node DataSet_node = SVP_node.child("DataSet");
		pNewSclCtrlSmvOut->m_strDataSetDesc = CString_utf8_to_gbk(SampledValueControl_node.attribute("desc").value());
		if (pNewSclCtrlSmvOut->m_strDataSetDesc == "")
		{
			pNewSclCtrlSmvOut->m_strDataSetDesc = pNewSclCtrlSmvOut->m_strDataSet;
		}

		pNewSclCtrlSmvOut->scl_svcb_confRev = CString_utf8_to_gbk(SampledValueControl_node.attribute("confRev").value()).toULong();

		pNewSclCtrlSmvOut->scl_svcb_smpRate = CString_utf8_to_gbk(SampledValueControl_node.attribute("smpRate").value()).toULong();
		pNewSclCtrlSmvOut->scl_svcb_nofASDU = CString_utf8_to_gbk(SampledValueControl_node.attribute("nofASDU").value()).toULong();

		//进入FCDA节点
		xpugi::xpath_node_set FCDA_list=DataSet_node.node().select_nodes("FCDA");
		pNewSclCtrlSmvOut->m_nChnCount=FCDA_list.size();

		for(xpugi::xpath_node_set::const_iterator FCDA_it=FCDA_list.begin();FCDA_it!=FCDA_list.end();FCDA_it++)
		{
			//遍历发布数据集
			xpugi::xml_node FCDA_node=FCDA_it->node();

			pSclChBase = pNewSclCtrlSmvOut->CreateNewCh();

			if (strlen(FCDA_node.attribute("daName").value()) > 0)
			{
				pSclChBase->m_strID=pNewIed->m_strName + CString_utf8_to_gbk("%1/%2%3%4.%5.%6").arg(CString_utf8_to_gbk(FCDA_node.attribute("ldInst").value()),
					CString_utf8_to_gbk(FCDA_node.attribute("prefix").value()),
					CString_utf8_to_gbk(FCDA_node.attribute("lnClass").value()),
					CString_utf8_to_gbk(FCDA_node.attribute("lnInst").value()),
					CString_utf8_to_gbk(FCDA_node.attribute("doName").value()),
					CString_utf8_to_gbk(FCDA_node.attribute("daName").value())
					);
			} 
			else
			{
				pSclChBase->m_strID=pNewIed->m_strName + CString_utf8_to_gbk("%1/%2%3%4.%5").arg(CString_utf8_to_gbk(FCDA_node.attribute("ldInst").value()),
					CString_utf8_to_gbk(FCDA_node.attribute("prefix").value()),
					CString_utf8_to_gbk(FCDA_node.attribute("lnClass").value()),
					CString_utf8_to_gbk(FCDA_node.attribute("lnInst").value()),
					CString_utf8_to_gbk(FCDA_node.attribute("doName").value())
					);
			}

			pSclChBase->m_strName = CString_utf8_to_gbk(FCDA_node.attribute("desc").value());
			pSclChBase->fcda_dodesc = pSclChBase->m_strName;
			pSclChBase->fcda_desc = pSclChBase->m_strName;
			pSclChBase->fcda_name = pSclChBase->m_strID;
		}
		if (m_pProgressInterface != NULL)
		{
			m_pProgressInterface->StepIt();
		}
	}


	
	//GOOSE 输出
	for(xpugi::xpath_node_set::const_iterator GOC_it=GOP_list.begin();
		GOC_it!=GOP_list.end();GOC_it++)
	{
		xpugi::xml_node GOC_node = GOC_it->node();

		xpugi::xml_node ConnectedAP_node=GOC_node.child("ConnectedAP");

		pNewSclCtrlGsOut = new CSclCtrlGsOut();
		pCurGsOuts->AddNewChild(pNewSclCtrlGsOut);

		xpugi::xml_node GSE_node=ConnectedAP_node.child("GSE");

		pNewSclCtrlGsOut->apName = CString_utf8_to_gbk(ConnectedAP_node.attribute("apName").value());
		pNewSclCtrlGsOut->gocbref = CString_utf8_to_gbk(GSE_node.attribute("cbName").value());
		pNewSclCtrlGsOut->m_strID = pNewSclCtrlGsOut->gocbref;
		pNewSclCtrlGsOut->ldName = CString_utf8_to_gbk(GSE_node.attribute("ldInst").value());
		pNewSclCtrlGsOut->m_strgocbRef.Format(_T("%s%s/LLN0$GO$%s"), pNewIed->m_strID.GetString(), pNewSclCtrlGsOut->ldName.GetString(), pNewSclCtrlGsOut->gocbref.GetString());

		pNewSclCtrlGsOut->m_dwItemData = 1;
		//Address
		xpugi::xpath_node_set Address_list=GSE_node.select_nodes("./Address/P");
		for(xpugi::xpath_node_set::const_iterator Address_it=Address_list.begin();
			Address_it!=Address_list.end();Address_it++)
		{
			xpugi::xpath_node Address_node=*Address_it;
			CString Addressstr = CString_utf8_to_gbk(Address_node.node().attribute("type").value());
			if(Addressstr=="MAC-Address")
			{
				pNewSclCtrlGsOut->m_strMac = CString_utf8_to_gbk(Address_node.node().text().as_string());
			}
			else if(Addressstr=="VLAN-ID")
			{
				pNewSclCtrlGsOut->m_dwVLandID = GetHexValue(CString_utf8_to_gbk(Address_node.node().text().as_string()));
			}
			else if(Addressstr=="APPID")
			{
				pNewSclCtrlGsOut->m_dwAppID = GetHexValue(CString_utf8_to_gbk(Address_node.node().text().as_string()));
			}
			else if(Addressstr=="VLAN-PRIORITY")
			{
				pNewSclCtrlGsOut->m_dwVLandPriority = GetHexValue(CString_utf8_to_gbk(Address_node.node().text().as_string()));
			}
		}
		xpugi::xpath_node MinTime_node=GSE_node.select_node("./MinTime");
		pNewSclCtrlGsOut->scl_gse_MinTime = MinTime_node.node().text().as_int();
		xpugi::xpath_node MaxTime_node=GSE_node.select_node("./MaxTime");
		pNewSclCtrlGsOut->scl_gse_MaxTime = MaxTime_node.node().text().as_int();

		//查找GSEControl
		xpugi::xml_node GSEControl_node=GOC_node.child("GSEControl");

		pNewSclCtrlGsOut->m_strDataSet = CString_utf8_to_gbk(GSEControl_node.attribute("datSet").value());
		pNewSclCtrlGsOut->m_strDataSetPath.Format(_T("%s%s/LLN0$%s"), pNewIed->m_strID.GetString(), pNewSclCtrlGsOut->ldName.GetString(), pNewSclCtrlGsOut->m_strDataSet.GetString());

		pNewSclCtrlGsOut->m_strGooseId = CString_utf8_to_gbk(GSEControl_node.attribute("appID").value());
		pNewSclCtrlGsOut->m_dwVersion = CString_utf8_to_gbk(GSEControl_node.attribute("confRev").value()).toULong();

		xpugi::xpath_node DataSet_node = GOC_node.child("DataSet");
		pNewSclCtrlGsOut->m_strDataSetDesc = CString_utf8_to_gbk(DataSet_node.node().attribute("desc").value());
		if (pNewSclCtrlGsOut->m_strDataSetDesc == "")
		{
			pNewSclCtrlGsOut->m_strDataSetDesc = pNewSclCtrlGsOut->m_strDataSet;
		}

		//进入FCDA节点
		xpugi::xpath_node_set FCDA_list=DataSet_node.node().select_nodes("FCDA");
		pNewSclCtrlGsOut->m_nChnCount=FCDA_list.size();

		for(xpugi::xpath_node_set::const_iterator FCDA_it=FCDA_list.begin();FCDA_it!=FCDA_list.end();FCDA_it++)
		{
			//遍历发布数据集
			xpugi::xml_node FCDA_node=FCDA_it->node();

			pSclChGs = (CSclChGs*)pNewSclCtrlGsOut->CreateNewCh();

			if (strlen(FCDA_node.attribute("daName").value()) > 0)
			{
				pSclChGs->m_strID=pNewIed->m_strID + CString_utf8_to_gbk("%1/%2%3%4.%5.%6").arg(CString_utf8_to_gbk(FCDA_node.attribute("ldInst").value()),
					CString_utf8_to_gbk(FCDA_node.attribute("prefix").value()),
					CString_utf8_to_gbk(FCDA_node.attribute("lnClass").value()),
					CString_utf8_to_gbk(FCDA_node.attribute("lnInst").value()),
					CString_utf8_to_gbk(FCDA_node.attribute("doName").value()),
					CString_utf8_to_gbk(FCDA_node.attribute("daName").value())
					);
			} 
			else
			{
				pSclChGs->m_strID=pNewIed->m_strID + CString_utf8_to_gbk("%1/%2%3%4.%5").arg(CString_utf8_to_gbk(FCDA_node.attribute("ldInst").value()),
					CString_utf8_to_gbk(FCDA_node.attribute("prefix").value()),
					CString_utf8_to_gbk(FCDA_node.attribute("lnClass").value()),
					CString_utf8_to_gbk(FCDA_node.attribute("lnInst").value()),
					CString_utf8_to_gbk(FCDA_node.attribute("doName").value())
					);
			}

			//查找数据类型
			CString daName = CString_utf8_to_gbk(FCDA_node.attribute(_T("daName")).value());
			if((daName.GetLength()-2) == daName.Find(".t"))
			{
				pSclChGs->fcda_type=_T("Timestamp");
			}
			else if((daName.GetLength()-2) == daName.Find(".q"))
			{
				pSclChGs->fcda_type=_T("Quality");
			}
			else
			{
				pSclChGs->fcda_type=CString_utf8_to_gbk(FCDA_node.attribute("bType").value());
			}
			pSclChGs->m_strName = CString_utf8_to_gbk(FCDA_node.attribute("desc").value());
			pSclChGs->fcda_dodesc = pSclChGs->m_strName;
			pSclChGs->fcda_name = pSclChGs->m_strID;
		}
		if (m_pProgressInterface != NULL)
		{
			m_pProgressInterface->StepIt();
		}
	}



	long nInIndex = 0;
	long nOutIndex = 0;
	nCurrIndex = 0;

	
	////SMV 接收
	for(xpugi::xpath_node_set::const_iterator SVS_it=SVS_list.begin();
		SVS_it!=SVS_list.end();SVS_it++)
	{
		xpugi::xml_node SVS_node = SVS_it->node();

		xpugi::xml_node ConnectedAP_node=SVS_node.child("ConnectedAP");

		pSclCtrlSmvIn = new CSclCtrlSmvIn();
		pCurSmvIns->AddNewChild(pSclCtrlSmvIn);

		xpugi::xml_node SMV_node=ConnectedAP_node.child("SMV");

		pSclCtrlSmvIn->apName = CString_utf8_to_gbk(ConnectedAP_node.attribute("apName").value());
		pSclCtrlSmvIn->m_strID = CString_utf8_to_gbk(SMV_node.attribute("cbName").value());
		pSclCtrlSmvIn->ldName = CString_utf8_to_gbk(SMV_node.attribute("ldInst").value());

		pSclCtrlSmvIn->iedExtName = CString_utf8_to_gbk(ConnectedAP_node.attribute("iedName").value());
		pSclCtrlSmvIn->m_strExIedDesc = /*CString_utf8_to_gbk*/("虚拟IED");
		//Address
		xpugi::xpath_node_set Address_list=SMV_node.select_nodes("./Address/P");
		for(xpugi::xpath_node_set::const_iterator Address_it=Address_list.begin();
			Address_it!=Address_list.end();Address_it++)
		{
			xpugi::xpath_node Address_node=*Address_it;
			QString Addressstr = QString(Address_node.node().attribute("type").value());
			if(Addressstr=="MAC-Address")
			{
				pSclCtrlSmvIn->m_strMac = CString_utf8_to_gbk(Address_node.node().text().as_string());
			}
			else if(Addressstr=="VLAN-ID")
			{
				pSclCtrlSmvIn->scl_smv_VLANID = GetHexValue(CString_utf8_to_gbk(Address_node.node().text().as_string()));
			}
			else if(Addressstr=="APPID")
			{
				pSclCtrlSmvIn->m_dwAppID = GetHexValue(CString_utf8_to_gbk(Address_node.node().text().as_string()));
			}
			else if(Addressstr=="VLAN-PRIORITY")
			{
				pSclCtrlSmvIn->scl_smv_VLANPRI = GetHexValue(CString_utf8_to_gbk(Address_node.node().text().as_string()));
			}
		}

		//查找SampledValueControl
		xpugi::xml_node SampledValueControl_node=SVS_node.child("SampledValueControl");

		pSclCtrlSmvIn->m_strDataSet = CString_utf8_to_gbk(SampledValueControl_node.attribute("datSet").value());
		pSclCtrlSmvIn->m_strDataSetPath.Format(_T("%s%s/LLN0$%s"), pNewIed->m_strID.GetString(), pNewSclCtrlGsOut->ldName.GetString(), pNewSclCtrlGsOut->m_strDataSet.GetString());

		pSclCtrlSmvIn->m_strSVID = CString_utf8_to_gbk(SampledValueControl_node.attribute("smvID").value());

		pSclCtrlSmvIn->m_strDataSetDesc = CString_utf8_to_gbk(SampledValueControl_node.attribute("desc").value());
		if (pSclCtrlSmvIn->m_strDataSetDesc == "")
		{
			pSclCtrlSmvIn->m_strDataSetDesc = pSclCtrlSmvIn->m_strDataSet;
		}
		pSclCtrlSmvIn->scl_svcb_confRev = CString_utf8_to_gbk(SampledValueControl_node.attribute("confRev").value()).toULong();

		pSclCtrlSmvIn->scl_svcb_smpRate = CString_utf8_to_gbk(SampledValueControl_node.attribute("smpRate").value()).toULong();
		pSclCtrlSmvIn->scl_svcb_nofASDU = CString_utf8_to_gbk(SampledValueControl_node.attribute("nofASDU").value()).toULong();


		xpugi::xpath_node DataSet_node = SVS_node.child("DataSet");

		//进入FCDA节点
		xpugi::xpath_node_set FCDA_list=DataSet_node.node().select_nodes("FCDA");
		pSclCtrlSmvIn->m_nChnRefCount=FCDA_list.size();

		nInIndex = 0;
		nOutIndex = -1;
		for(xpugi::xpath_node_set::const_iterator FCDA_it=FCDA_list.begin();FCDA_it!=FCDA_list.end();FCDA_it++)
		{
			nOutIndex++;
			//遍历发布数据集
			xpugi::xml_node FCDA_node=FCDA_it->node();

			CString strAddrDesc = CString_utf8_to_gbk(FCDA_node.child("intAddr").attribute("desc").value());

			if (strAddrDesc == "")
			{
				continue;
			}
			pSclChSmvIn = (CSclChSmvIn *)pSclCtrlSmvIn->CreateNewCh();
			//zhouhj 2023.9.19 改为外部通道描述
			pSclChSmvIn->outIndex = nOutIndex;
			pSclChSmvIn->inIndex = nInIndex++;
			pSclChSmvIn->inDODesc = strAddrDesc;
			pSclCtrlSmvIn->m_nChnCount++;

			if (strlen(FCDA_node.attribute("daName").value()) > 0)
			{
				pSclChSmvIn->inPath = CString_utf8_to_gbk("%1/%2%3%4.%5.%6").arg(CString_utf8_to_gbk(FCDA_node.attribute("ldInst").value()),
					CString_utf8_to_gbk(FCDA_node.attribute("prefix").value()),
					CString_utf8_to_gbk(FCDA_node.attribute("lnClass").value()),
					CString_utf8_to_gbk(FCDA_node.attribute("lnInst").value()),
					CString_utf8_to_gbk(FCDA_node.attribute("doName").value()),
					CString_utf8_to_gbk(FCDA_node.attribute("daName").value())
					);
			} 
			else
			{
				pSclChSmvIn->inPath=CString_utf8_to_gbk("%1/%2%3%4.%5").arg(CString_utf8_to_gbk(FCDA_node.attribute("ldInst").value()),
					CString_utf8_to_gbk(FCDA_node.attribute("prefix").value()),
					CString_utf8_to_gbk(FCDA_node.attribute("lnClass").value()),
					CString_utf8_to_gbk(FCDA_node.attribute("lnInst").value()),
					CString_utf8_to_gbk(FCDA_node.attribute("doName").value())
					);
			}
			pSclChSmvIn->m_strID=pNewIed->m_strID + pSclChSmvIn->inPath;

			pSclChSmvIn->m_strName = CString_utf8_to_gbk(FCDA_node.attribute("desc").value());
			pSclChSmvIn->fcda_dodesc = pSclChSmvIn->m_strName;
			pSclChSmvIn->fcda_desc = pSclChSmvIn->m_strName;
			pSclChSmvIn->fcda_name = pSclChSmvIn->m_strID;
		}

		
		
		CSclIed *pVirualIed = (CSclIed*)m_pSclStation->FindByID(pSclCtrlSmvIn->iedExtName);
		if (pVirualIed == NULL)
		{
			pVirualIed = new CSclIed();
			m_pSclStation->AddNewChild(pVirualIed);
			pVirualIed->m_strID = pSclCtrlSmvIn->iedExtName;
			pVirualIed->m_strName = /*CString_utf8_to_gbk*/("虚拟IED");
		}

		pVirualSmvOuts = pVirualIed->GetSmvOuts();

		pVirualSclCtrlSmvOut = new CSclCtrlSmvOut();
		pVirualSmvOuts->AddNewChild(pVirualSclCtrlSmvOut);
		pVirualSclCtrlSmvOut->apName = pSclCtrlSmvIn->apName;
		pVirualSclCtrlSmvOut->m_strID = pSclCtrlSmvIn->m_strID;
		pVirualSclCtrlSmvOut->ldName = pSclCtrlSmvIn->ldName;

		pVirualSclCtrlSmvOut->m_strMac = pSclCtrlSmvIn->m_strMac;
		pVirualSclCtrlSmvOut->scl_smv_VLANID = pSclCtrlSmvIn->scl_smv_VLANID;
		pVirualSclCtrlSmvOut->m_dwAppID = pSclCtrlSmvIn->m_dwAppID;
		pVirualSclCtrlSmvOut->scl_smv_VLANPRI = pSclCtrlSmvIn->scl_smv_VLANPRI;

		pVirualSclCtrlSmvOut->m_strDataSet = pSclCtrlSmvIn->m_strDataSet;
		pVirualSclCtrlSmvOut->m_strDataSetPath = pSclCtrlSmvIn->m_strDataSetPath;
		pVirualSclCtrlSmvOut->m_strSVID = pSclCtrlSmvIn->m_strSVID;

		pVirualSclCtrlSmvOut->m_strDataSetDesc = pSclCtrlSmvIn->m_strDataSetDesc;
		pVirualSclCtrlSmvOut->scl_svcb_confRev  = pSclCtrlSmvIn->scl_svcb_confRev;

		pVirualSclCtrlSmvOut->scl_svcb_smpRate  = pSclCtrlSmvIn->scl_svcb_smpRate;
		pVirualSclCtrlSmvOut->scl_svcb_nofASDU  = pSclCtrlSmvIn->scl_svcb_nofASDU;

		pVirualSclCtrlSmvOut->m_nChnCount=pSclCtrlSmvIn->m_nChnCount;
		pVirualSclCtrlSmvOut->m_dwItemData = pSclCtrlSmvIn->m_dwItemData;

		CSclChSmvIn *pObj = NULL;
		POS pos = pSclCtrlSmvIn->GetHeadPosition();
		while (pos != NULL)
		{
			pObj = (CSclChSmvIn*)pSclCtrlSmvIn->GetNext(pos);
			pSclChBase = pVirualSclCtrlSmvOut->CreateNewCh();
			pSclChBase->m_strID = pObj->m_strID;

			pSclChBase->m_strName = pObj->m_strName;
			pSclChBase->fcda_dodesc = pSclChBase->m_strName;
			pSclChBase->fcda_name = pSclChBase->m_strID;
		}
		if (m_pProgressInterface != NULL)
		{
			m_pProgressInterface->StepIt();
		}
	}

	//GOOSE 接收
	for(xpugi::xpath_node_set::const_iterator GOS_it=GOS_list.begin();
		GOS_it!=GOS_list.end();GOS_it++)
	{
		xpugi::xml_node GOS_node = GOS_it->node();

		xpugi::xml_node ConnectedAP_node=GOS_node.child("ConnectedAP");

		pSclCtrlGsIn= new CSclCtrlGsIn();
		pCurGsIns->AddNewChild(pSclCtrlGsIn);

		xpugi::xml_node GSE_node=ConnectedAP_node.child("GSE");

		pSclCtrlGsIn->apName = CString_utf8_to_gbk(ConnectedAP_node.attribute("apName").value());
		pSclCtrlGsIn->apName_own = pSclCtrlGsIn->apName;//zhouhj 20220415 当前未记录自身apName用此标识
		pSclCtrlGsIn->m_strID = CString_utf8_to_gbk(GSE_node.attribute("cbName").value());
		pSclCtrlGsIn->ldName = CString_utf8_to_gbk(GSE_node.attribute("ldInst").value());
		pSclCtrlGsIn->m_strgocbRef.Format(_T("%s%s/LLN0$GO$%s"), pNewIed->m_strID.GetString(), pSclCtrlGsIn->ldName.GetString(), pSclCtrlGsIn->gocbref.GetString());

		pSclCtrlGsIn->m_strName = pNewIed->m_strName;
		pSclCtrlGsIn->m_strLDdesc = pSclCtrlGsIn->ldName;
		pSclCtrlGsIn->m_strIedID = CString_utf8_to_gbk(ConnectedAP_node.attribute("iedName").value());
		pSclCtrlGsIn->m_strExIedDesc = /*CString_utf8_to_gbk*/("虚拟IED");

		//Address
		xpugi::xpath_node_set Address_list=GSE_node.select_nodes("./Address/P");
		for(xpugi::xpath_node_set::const_iterator Address_it=Address_list.begin();
			Address_it!=Address_list.end();Address_it++)
		{
			xpugi::xpath_node Address_node=*Address_it;
			CString Addressstr = CString_utf8_to_gbk(Address_node.node().attribute("type").value());
			if(Addressstr=="MAC-Address")
			{
				pSclCtrlGsIn->m_strMac = CString_utf8_to_gbk(Address_node.node().text().as_string());
			}
			else if(Addressstr=="VLAN-ID")
			{
				pSclCtrlGsIn->m_dwVLandID = GetHexValue(CString_utf8_to_gbk(Address_node.node().text().as_string()));
			}
			else if(Addressstr=="APPID")
			{
				pSclCtrlGsIn->m_dwAppID = GetHexValue(CString_utf8_to_gbk(Address_node.node().text().as_string()));
			}
			else if(Addressstr=="VLAN-PRIORITY")
			{
				pSclCtrlGsIn->m_dwVLandPriority = GetHexValue(CString_utf8_to_gbk(Address_node.node().text().as_string()));
			}
		}
		xpugi::xpath_node MinTime_node=GSE_node.select_node("./MinTime");
		pSclCtrlGsIn->scl_gse_MinTime = MinTime_node.node().text().as_int();
		xpugi::xpath_node MaxTime_node=GSE_node.select_node("./MaxTime");
		pSclCtrlGsIn->scl_gse_MaxTime = MaxTime_node.node().text().as_int();

		//查找GSEControl
		xpugi::xml_node GSEControl_node=GOS_node.child("GSEControl");

		pSclCtrlGsIn->m_strDataSet = CString_utf8_to_gbk(GSEControl_node.attribute("datSet").value());
		pSclCtrlGsIn->m_strDataSetPath.Format(_T("%s%s/LLN0$%s"), pNewIed->m_strID.GetString(), pSclCtrlGsIn->ldName.GetString(), pSclCtrlGsIn->m_strDataSet.GetString());

		pSclCtrlGsIn->m_dwVersion = CString_utf8_to_gbk(GSEControl_node.attribute("confRev").value()).toULong();
		pSclCtrlGsIn->m_strGooseId = CString_utf8_to_gbk(GSEControl_node.attribute("appID").value());

		xpugi::xpath_node DataSet_node = GOS_node.child("DataSet");
		pSclCtrlGsIn->m_strDataSetDesc = CString_utf8_to_gbk(DataSet_node.node().attribute("desc").value());
		if (pSclCtrlGsIn->m_strDataSetDesc == "")
		{
			pSclCtrlGsIn->m_strDataSetDesc = pSclCtrlGsIn->m_strDataSet;
		}

		//进入FCDA节点
		xpugi::xpath_node_set FCDA_list=DataSet_node.node().select_nodes("FCDA");
		pSclCtrlGsIn->m_nChnRefCount = FCDA_list.size();

		nInIndex = 0;
		nOutIndex = -1;
		for(xpugi::xpath_node_set::const_iterator FCDA_it=FCDA_list.begin();FCDA_it!=FCDA_list.end();FCDA_it++)
		{
			nOutIndex++;
			//遍历发布数据集
			xpugi::xml_node FCDA_node=FCDA_it->node();
			QString strAddrDesc = CString_utf8_to_gbk(FCDA_node.child("intAddr").attribute("desc").value());

			if (strAddrDesc == "")
			{
				continue;
			}

			pSclCtrlGsIn->m_nChnCount++;
			pSclChGsIn = (CSclChGsIn*)pSclCtrlGsIn->CreateNewCh();

			//zhouhj 2023.9.19 改为外部通道描述
			pSclChGsIn->outIndex = nOutIndex;
			pSclChGsIn->inIndex = nInIndex++;

			pSclChGsIn->inDODesc = strAddrDesc;

			if (strlen(FCDA_node.attribute("daName").value()) > 0)
			{
				pSclChGsIn->inPath = CString_utf8_to_gbk("%1/%2%3%4.%5.%6").arg(CString_utf8_to_gbk(FCDA_node.attribute("ldInst").value()),
					CString_utf8_to_gbk(FCDA_node.attribute("prefix").value()),
					CString_utf8_to_gbk(FCDA_node.attribute("lnClass").value()),
					CString_utf8_to_gbk(FCDA_node.attribute("lnInst").value()),
					CString_utf8_to_gbk(FCDA_node.attribute("doName").value()),
					CString_utf8_to_gbk(FCDA_node.attribute("daName").value())
					);
				pSclChGsIn->m_strID=pNewIed->m_strID + pSclChGsIn->inPath;
			} 
			else
			{
				pSclChGsIn->inPath = CString_utf8_to_gbk("%1/%2%3%4.%5").arg(CString_utf8_to_gbk(FCDA_node.attribute("ldInst").value()),
					CString_utf8_to_gbk(FCDA_node.attribute("prefix").value()),
					CString_utf8_to_gbk(FCDA_node.attribute("lnClass").value()),
					CString_utf8_to_gbk(FCDA_node.attribute("lnInst").value()),
					CString_utf8_to_gbk(FCDA_node.attribute("doName").value())
					);
				pSclChGsIn->m_strID=pNewIed->m_strID + pSclChGsIn->inPath;
			}

			//查找数据类型
			CString daName = CString_utf8_to_gbk(FCDA_node.attribute(_T("daName")).value());
			if((daName.GetLength()-2) == daName.Find(".t"))
			{
				pSclChGsIn->fcda_type=_T("Timestamp");
			}
			else if((daName.GetLength()-2) == daName.Find(".q"))
			{
				pSclChGsIn->fcda_type=_T("Quality");
			}
			else
			{
				pSclChGsIn->fcda_type=CString_utf8_to_gbk(FCDA_node.attribute("bType").value());
			}
			pSclChGsIn->m_strName = CString_utf8_to_gbk(FCDA_node.attribute("desc").value());
			pSclChGsIn->fcda_dodesc = pSclChGsIn->m_strName;
			pSclChGsIn->fcda_desc = pSclChGsIn->m_strName;
			pSclChGsIn->fcda_name = pSclChGsIn->m_strID;
		}
	

		CSclIed *pVirualIed = (CSclIed*)m_pSclStation->FindByID(pSclCtrlGsIn->m_strIedID);
		if (pVirualIed == NULL)
		{
			pVirualIed = new CSclIed();
			m_pSclStation->AddNewChild(pVirualIed);
			pVirualIed->m_strID = pSclCtrlGsIn->m_strIedID;
			pVirualIed->m_strName = /*CString_utf8_to_gbk*/("虚拟IED");
		}

		pVirualGsOuts = pVirualIed->GetGsOuts();

		pVirualSclCtrlGsOut = new CSclCtrlGsOut();
		pVirualGsOuts->AddNewChild(pVirualSclCtrlGsOut);
		pVirualSclCtrlGsOut->apName = pSclCtrlGsIn->apName;
		pVirualSclCtrlGsOut->gocbref = pSclCtrlGsIn->gocbref;
		pVirualSclCtrlGsOut->m_strID = pVirualSclCtrlGsOut->gocbref;
		pVirualSclCtrlGsOut->ldName = pSclCtrlGsIn->ldName;
		pVirualSclCtrlGsOut->m_strgocbRef = pSclCtrlGsIn->m_strgocbRef;
		
		pVirualSclCtrlGsOut->m_strMac = pSclCtrlGsIn->m_strMac;
		pVirualSclCtrlGsOut->m_dwVLandID = pSclCtrlGsIn->m_dwVLandID;
		pVirualSclCtrlGsOut->m_dwAppID = pSclCtrlGsIn->m_dwAppID;
		pVirualSclCtrlGsOut->m_dwVLandPriority = pSclCtrlGsIn->m_dwVLandPriority;
	
		pVirualSclCtrlGsOut->scl_gse_MinTime = pSclCtrlGsIn->scl_gse_MinTime;
		pVirualSclCtrlGsOut->scl_gse_MaxTime = pSclCtrlGsIn->scl_gse_MaxTime;

		pVirualSclCtrlGsOut->m_strDataSet = pSclCtrlGsIn->m_strDataSet;
		pVirualSclCtrlGsOut->m_strDataSetPath = pSclCtrlGsIn->m_strDataSetPath;
		pVirualSclCtrlGsOut->m_strGooseId = pSclCtrlGsIn->m_strGooseId;
		pVirualSclCtrlGsOut->m_dwVersion = pSclCtrlGsIn->m_dwVersion;

		pVirualSclCtrlGsOut->m_strDataSetDesc = pSclCtrlGsIn->m_strDataSetDesc;
		pVirualSclCtrlGsOut->m_dwItemData = pSclCtrlGsIn->m_dwItemData;
		pVirualSclCtrlGsOut->m_nChnCount=pSclCtrlGsIn->m_nChnCount;

		CSclChGsIn *pObj = NULL;
		POS pos = pSclCtrlGsIn->GetHeadPosition();
		while (pos != NULL)
		{
			pObj = (CSclChGsIn*)pSclCtrlGsIn->GetNext(pos);
			pSclChGs = (CSclChGs*)pVirualSclCtrlGsOut->CreateNewCh();
			pSclChGs->m_strID = pObj->m_strID;
			pSclChGs->fcda_type=pObj->fcda_type;
			
			pSclChGs->m_strName = pObj->m_strName;
			pSclChGs->fcda_dodesc = pSclChGs->m_strName;
			pSclChGs->fcda_name = pSclChGs->m_strID;
		}
		if (m_pProgressInterface != NULL)
		{
			m_pProgressInterface->StepIt();
		}
	}
}