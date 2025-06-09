#include "stdafx.h"
#include "PxProtoDeviceBase.h"
#include "../../../Module/GpsPcTime/GpsPcTime.h"
#include "../IotEngineGlobalDef.h"

#ifdef _DEBUG  
#define new DEBUG_NEW  
#undef THIS_FILE  
static char THIS_FILE[] = __FILE__; 
#endif  

CPxProtoDeviceBase::CPxProtoDeviceBase()
{
	m_pPxProtocol = NULL;
	m_pProtoEventInterface = NULL;
	m_bCanDelete = FALSE;
}

CPxProtoDeviceBase::~CPxProtoDeviceBase()
{
}

//提取所有未处理的报文，用于过程处理
void CPxProtoDeviceBase::GetNotProcessedPkgs(CExBaseList &oList)
{
	POS pos = m_listRcvPkg.GetHeadPosition();
	CPxPkgBase *p = NULL;

	while(pos != NULL)
	{
		p = (CPxPkgBase *)m_listRcvPkg.GetNext(pos);

		if (p->IsPkgState_NotProcessed())
		{
			oList.AddTail(p);
		}
	}
}

//删除所有无效报文，保证链表不能为空
void CPxProtoDeviceBase::DeleteUnvalidPkgs(SYSTEMTIME &tmCur,long nValidTimeLong)
{
	if (nValidTimeLong <= 0)
	{
		return;
	}

	long nPkgCnt = m_listRcvPkg.GetCount();
	
	if (nPkgCnt <= 1)
	{//保证链表不能为空
		return;
	}

	long nPkgLifeTime = 0;
	POS pos = m_listRcvPkg.GetHeadPosition();
	POS posTail = m_listRcvPkg.GetTailPosition();
	POS prePos = NULL;
	CPxPkgBase *p = NULL;

	while(pos != NULL)
	{
		if (pos == posTail)
		{//保证最后一个节点不被删除，这样AddTail就不会冲突
			break;
		}

		prePos = pos;
		p = (CPxPkgBase *)m_listRcvPkg.GetNext(pos);

		if (p->IsPkgState_CanDelete())
		{
			m_listRcvPkg.DeleteAt(prePos);
			continue;
		}

		nPkgLifeTime = GetSpanMSeconds(p->m_tmPkg,tmCur);
		if (nPkgLifeTime >= nValidTimeLong)
		{//报文超过有效生命周期仍未被处理，则丢弃
			m_listRcvPkg.DeleteAt(prePos);
			continue;
		}
	}
}

void CPxProtoDeviceBase::AttachProtoEventInterface(CPxProtoEventInterface *pProtoEventInterface)
{
	m_pProtoEventInterface = pProtoEventInterface;
}

//更新指定数据集
CDvmDataset *CPxProtoDeviceBase::UpdateDataset(CDvmDataset *pSrcDataset)
{
	if (pSrcDataset == NULL)
	{
		return NULL;
	}

	CString strDsID = GetIDFromPath(pSrcDataset->m_strID,'$');
	CDvmDataset *pDstDataset = m_oDvmDevice.FindDataset(strDsID);
	if (pDstDataset != NULL)
	{
		pDstDataset->UpdateDataValue(pSrcDataset);
	}

	return pDstDataset;
}

/******************************
具体协议服务对象中，创建并初始化ProcedureRun类对象，并添加到g_pIotSvrEngine中m_listPrcdr链表中
******************************/
long CPxProtoDeviceBase::RunProcedure(const CString &strProcedureID,CExBaseList *pListDatas
										  ,CDvmDataset *pDataset,const CString &strRecordMode)
{
	if(m_pProtoEventInterface == NULL)
	{
		return 0;
	}

	CDvmDataset* pAttrs = m_oDvmDevice.GetDeviceAttrs();

	if (strProcedureID == PROCEDURE_ID_WriteMmsAttr)
	{//如果是更新全局数据集过程		
		pAttrs->UpdateDataValue(pDataset);

//		m_pProtoEventInterface->OnPrcdrFinishedEx(RUNPROCEDURE_EVENT_CommFinish,pAttrs);
		return 1;
	}
	
	//从规约模板中找到对应的过程对象
	CPxPrcdrBase *pProcedure = m_pPxProtocol->FindProcedure(strProcedureID);

	if (pProcedure == NULL)
	{
		return 0;
	}

	//克隆备份，在ProcedureRun中释放
	CPxPrcdrBase *pDstProcedure = (CPxPrcdrBase *)pProcedure->Clone();

	//更新参数列表
	CDvmData* pDstInterface = pDstProcedure->GetDataInterface();
	ASSERT (pListDatas->GetClassID() == DVMCLASSID_CDVMDATA);
	pDstInterface->AppendClone(pListDatas);

	//更新数据集
	CDvmDataset *pDstDataset = UpdateDataset(pDataset);

	//提取过程对象中超时参数:输入Dataset永远是全局attr数据集
	pDstProcedure->UpdateNodeTimers(pAttrs);

	//添加到过程链表
	m_pPxProtocol->AddProcedureRun(this,pDstProcedure,pListDatas,pDstDataset,strRecordMode);

	return 1;
}

long CPxProtoDeviceBase::PkgPrase(char *pBuf,long nLen,CDvmDataset &oRetDataset)
{
	return 0;
}

long CPxProtoDeviceBase::PkgProduce(const CString &strProduceID,CDvmDataset &oDataset,char **ppBuf,long &nLen)
{
	return 0;
}

long CPxProtoDeviceBase::GetDataset(const CString &strDatasetPath,CDvmDataset &oRetDataset)
{
	CString strDsID = GetIDFromPath(strDatasetPath,'$');

	oRetDataset.DeleteAll();

	CDvmDataset *pSrcDataset = m_oDvmDevice.FindDataset(strDsID);
	if (pSrcDataset != NULL)
	{
		pSrcDataset->Copy(&oRetDataset);
	}

	oRetDataset.m_strID = strDatasetPath;

	return 1;
}

long CPxProtoDeviceBase::ConfigDevice(const CString &strConfig)
{
	return 0;
}

long CPxProtoDeviceBase::CloseDevice()
{
	//将转换接口模块指针清0
	m_pProtoEventInterface = NULL;

	//设置删除标志，在主线程开始位置统一删除
	m_bCanDelete = TRUE;
	m_pDatasetView = NULL;

	return 0;
}

//初始化协议服务模块接口
void CPxProtoDeviceBase::InitProtocol(const CString &strDeviceID,const CString &strDvmFile,const CString &strPpxmlFile
				  ,const CString &strCmmCfgFile,CDataGroup *pCfgGroup)
{
	m_strID = strDeviceID;

	m_oDvmDevice.DeleteAll();
	m_oDvmDevice.m_strID = strDvmFile;
	m_oDvmDevice.OpenXmlFile(strDvmFile,CDataMngrXmlRWKeys::g_pXmlKeys);

	//规约模板链表在CreateDevice主题处理逻辑前半部分已经初始化好了
	//m_pPxProtocol = g_pIotSvrEngine->FindPxProtocol(strPpxmlFile);
}

//处理传感器业务报文逻辑
void CPxProtoDeviceBase::ProcessPkg(char *pBuf,long nLen)
{
/*
	//数据流解析为PkgInfo结构体
	PkgInfo *pPkgInfo = new PkgInfo;
	long nRet = CProtocalEngine::PrasePkgInfo(pBuf,nLen,*pPkgInfo);
	if (nRet)
	{//分片或错误报文
		if (PP_PRASE_ErrType_FRAG == nRet)
		{//分片报文，报文数据已保存到全局CFragMngr::m_vecFragSDU链表中
			delete pPkgInfo;
		}
		else
		{//是错误报文
			
			//保存错误报文缓存
			pPkgInfo->m_pPkgBuf = new BYTE[nLen];
			pPkgInfo->m_nPkgBufLen = nLen;
			memcpy(pPkgInfo->m_pPkgBuf,pBuf,nLen);
			
			CPxPkgBase *pPkg = new CPxPkgBase;
			pPkg->m_pPkgInfo = pPkgInfo;
			pPkg->SetPkgState(PX_PKG_STATE_ERROR);
			m_listRcvPkg.AddNewChild(pPkg);
		}

		return;
	}

	//后续优化逻辑：分片分包和拼包逻辑放到DeviceCtrl中
// 	if (分片报文)
// 	{
//		添加到列表末尾
// 		if（分片的最后一帧）
// 		{
// 			查找分片第一帧（根据类型查找）
// 			将后续的同类型的分片拼接到第一帧的m_pFragSDUBuf
// 			解析第一帧的m_pFragSDUBuf : CProtocalEngine::PrasePkgInfo(m_pFragSDUBuf,nLen,*pPkgInfo);
// 			跳转到数据处理
// 		}
// 		else
// 		{
// 			return
// 		}
// 	}

	//正确解析报文后逻辑

	//根据帧头查找匹配解析节点
	CIotPpParse *pPrase = m_pPxProtocol->FindPpParse(pPkgInfo->m_nPkgType,pPkgInfo->m_nCtrlType
		,pPkgInfo->m_nRequestSetFlag);
	if (pPrase == NULL)
	{//不是规约模板匹配的报文
		CPxPkgBase *pPkg = new CPxPkgBase;
		pPkg->m_pPkgInfo = pPkgInfo;
		pPkg->SetPkgState(PX_PKG_STATE_PROCESSED_NOTMATCH);
		m_listRcvPkg.AddNewChild(pPkg);
		return;
	}

	CString strDatasetID = pPrase->GetDatasetID();

	if (pPrase->IsModelOptr_Write())
	{//更新数据集
		CDvmDataset *pDataset = m_oDvmDevice.FindDataset(strDatasetID);
		ASSERT(pDataset != NULL);

		//根据报文结构体更新数据集
		UpdateDatasetValue(*pPkgInfo,pDataset);

		if (strDatasetID == _T("dsAin"))
		{//监测或报警报文

			//更新数据库
			BOOL bWarning = (_PKG_TYPE_WARNING == pPkgInfo->m_nPkgType);

			//更新装置实时数据库表
			g_pIotSvrEngine->UpdateRTDeviceData(m_strID,pDataset,bWarning);
		}
	}

	//添加到接收报文链表中
	CPxPkgBase *pPkg = new CPxPkgBase;
	pPkg->m_pPkgInfo = pPkgInfo;
	m_listRcvPkg.AddNewChild(pPkg);
*/
}

//过程结束事件返回接口，m_pProtoEventInterface指向的是CIotEngineTo
void CPxProtoDeviceBase::OnPrcdrFinished(const CString &strEventID,CDvmDataset *pDataset)
{
	if (m_bCanDelete)
	{
		return;
	}

	if (m_pProtoEventInterface != NULL)
	{
		m_pProtoEventInterface->OnPrcdrFinishedEx((char *)strEventID.GetString(),pDataset);
	}
}

