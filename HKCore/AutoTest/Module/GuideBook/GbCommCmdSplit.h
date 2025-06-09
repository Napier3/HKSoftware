#pragma once

#include "../GuideBook/Device.h"
#include "../GuideBook/CommCmd.h"
#include "../GuideBook/GuideBook.h"

//数据集映射的一个组别，对应一个Items
class CGbCommCmdSplit
{
public:
	CGbCommCmdSplit();
	virtual ~CGbCommCmdSplit();

	void AttatchCpus(CCpus *pCpus)	{	m_pCpus = pCpus;	}
	void AttatchDatasetMaps(CExBaseList *pDatasetMaps)	{	m_pDatasetMaps = pDatasetMaps;		}
	void InitCommCmdItemDatasetPath(CDevice *pDevice, CCommCmd *pCommCmd);
	void InitCommCmdItemDatasetPath(CCommCmd *pCommCmd);

protected:
	void GetListDatasetFromDatas(CDevice *pDevice, CCommCmd *pCommCmd, CExBaseList *pDatasetList);
	//对于“不使用设置的数据”的通讯命令，从数据集映射中查找数据集列表   shaolei 20220530
	void GetListDatasetFromMaps(CDevice *pDevice, CCommCmd *pCommCmd, CExBaseList *pDatasetList);
	void GetListDatasetFromMaps(CDevice *pDevice, const CString &strDatasetID, CExBaseList *pDatasetList);
	CCpus* GetCpus(CDevice *pDevice);
	CCpus *m_pCpus;
	CDevice *m_pDevice;

	//shaolei 20220427 
	//记录所有的数据集映射，用于通讯命令绑定的数据集替换
	//根据映射ID查找到映射的数据集
	CExBaseList *m_pDatasetMaps;

	void ValidateCmdValues(CDevice *pDevice, CCommCmd *pCommCmd);
	CExBaseObject* FindDataObjByRptDataPath(const CString &strPath, CCpus *pCpus);

	//根据当前通讯命令的数据集路径，查找对应的模型映射
	CExBaseObject* SelectDatasetMap(const CString &strDsPath);
	//shaolei 2023-2-22  根据原始数据集ID，查找所有的模型映射
	long SelectDatasetMaps(const CString &strDsID, CExBaseList *pMapList);
	//添加通讯命令
	long AddCommCmd(long nAdd, CExBaseList *pListCommcmd, CCommCmd *pCommCmd);
};

class CGbCommCmdSplitTool : public CGbCommCmdSplit
{
public:
	CGbCommCmdSplitTool();
	virtual ~CGbCommCmdSplitTool();

public:
	void GbCommCmdSplit(CCpus *pCpus);

protected:
	void SplitCommCmd(CExBaseList *pList);

};

