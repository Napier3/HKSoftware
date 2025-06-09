#pragma once

#include "GbItemDvmVarReplace.h"
#include "../../../Module/DataMngr/DvmCmp/DvmDatasetMap.h"
#include "../../../Module/BaseClass/ThreadProgressInterface.h"

#define WM_DVMREPLACE_FINISH (WM_USER + 1525)

//2023-4-19  lijunqing
class CGbDvmReplaceEventInterface
{
public:
	virtual void ReplaceFinished() = 0;
};

//////////////////////////////////////////////////////////////////////////
//GbDvmReplaceDsMapCrossBreak
//CDvmDatasetMap整理对象，GbDvmReplaceDsMapCrossBreak的子对象为CDvmMapObject
class CGbDvmReplaceDsMapCrossBreak : public CExBaseList
{
public:
	CGbDvmReplaceDsMapCrossBreak(CDvmDatasetMap *pDvmDsMap);
	virtual ~CGbDvmReplaceDsMapCrossBreak();

	CString m_strDsID;
	CString m_strDsMapID;
	CString  m_strLdviceMap;
	CString  m_strLdvice;

	void ResetDataMap();
	BOOL HasValidMap();

protected:
	//用于记录CDvmDatasetMap的全部数据，临时记录
	CExBaseList m_listDataMapTemp;
	CExBaseList m_listCrossSingle;
	CExBaseList m_listCrossLoop;
	CExBaseList m_listNewDataMap;

	//以pDataMap为参考对象，构建交叉替换链表
	void BuildDataMap();
	void BuildDataMapFilterSame();
	void BuildDataMapInitCross();
	void BuildDataMapFilterCross();
	void BuildDataMapCreateCross_Single();
	void BuildDataMapCreateCross_Loop();
	//解锁交叉替换链表
	void BuildDataMapBreakCross_Single();
	void BuildDataMapBreakCross_Loop();

	void FreeCrossList(CExBaseList *pCrossList);
};


//////////////////////////////////////////////////////////////////////////
//CGbDvmReplaceTool
class CGbDvmReplaceTool : public CExBaseList
{
public:
	CGbDvmReplaceTool();
	virtual ~CGbDvmReplaceTool();

	void SetReplaceMacroTest(BOOL b=TRUE)	{	m_oGbItemDvmVarReplace.SetReplaceMacroTest(b);	}
	void SetReplaceSafety(BOOL b=TRUE)		{	m_oGbItemDvmVarReplace.SetReplaceSafety(b);		}
	void SetReplaceCommCmd(BOOL b=TRUE)		{	m_oGbItemDvmVarReplace.SetReplaceCommCmd(b);		}
	void SetReplaceSysparaEdit(BOOL b=TRUE)		{	m_oGbItemDvmVarReplace.SetReplaceSysparaEdit(b);		}


	CGbItemDvmVarReplace m_oGbItemDvmVarReplace;
	CGbDvmReplaceEventInterface *m_pGbDvmReplaceEvent;   //2023-4-19  lijunqing
public:
	//模型替换的项目列表构建
	void BuildRepalce(CExBaseList *pGbItems, CCpus *pCpus);

	//添加数据集映射
	void AddDatasetMap(CDvmDatasetMap *pDvmDatasetMap);

	//创建Replace线程，开始替换
	void CreateGbDvmReplaceThread(CThreadProgressInterface *pTrheadPrgsInterface);
	
	//创建检索线程
	void CreateGbDvmQueryThread(CThreadProgressInterface *pTrheadPrgsInterface);
	void CreateGbDvmStxmlReplaceThread(CThreadProgressInterface *pTrheadPrgsInterface, CGbtDatas *pGbtDatas);
	void CreateDvmMatchReplaceThread(CThreadProgressInterface *pTrheadPrgsInterface, CExBaseList *pListMatchMaps);

	//停止线程
	void StopGbDvmReplaceThread();

	//是否正在进行设备数据模型替换
	BOOL IsInGbDvmReplaceThread()	{	return m_pGbDvmReplaceThread != NULL;	}



//属性
protected:
	CCpus *m_pCpus;
	CGbtDatas *m_pGbtDatas;
	CExBaseList *m_pListMatchMaps;
	CThreadProgressInterface *m_pTrheadPrgsInterface;
	BOOL m_bStopGbDvmReplaceThread;
	CWinThread *m_pGbDvmReplaceThread;
	long m_nTotalRepalceCount;
	long m_nCurrRepalceIndex;
	CDvmMapObject m_oLdeviceMap;

	static UINT GbDvmReplaceThread(LPVOID pParameter);
	void GbDvmReplaceThread();

	static UINT GbDvmQueryThread(LPVOID pParameter);
	static UINT GbDvmStxmlReplaceThread(LPVOID pParameter);
	static UINT DvmMatchReplaceThread(LPVOID pParameter);
	void GbDvmQueryThread();
	void GbDvmStxmlReplaceThread();
	void DvmMatchReplaceThread();

	void ResetDataMap();


protected:
	void Replace(CExBaseObject *pDestObject, const CString &strSrcID, const CString &strDestID);
	BOOL HasReplace(CExBaseObject *pDestObject, const CString &strSrcID);

	//20231106 huangliang 添加子级中查找
	void ReplaceChild(const CString &strCpuID, const CString &strDsID, CDvmDataMap *pDataMap);

};

