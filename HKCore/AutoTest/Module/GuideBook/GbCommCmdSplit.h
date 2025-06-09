#pragma once

#include "../GuideBook/Device.h"
#include "../GuideBook/CommCmd.h"
#include "../GuideBook/GuideBook.h"

//���ݼ�ӳ���һ����𣬶�Ӧһ��Items
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
	//���ڡ���ʹ�����õ����ݡ���ͨѶ��������ݼ�ӳ���в������ݼ��б�   shaolei 20220530
	void GetListDatasetFromMaps(CDevice *pDevice, CCommCmd *pCommCmd, CExBaseList *pDatasetList);
	void GetListDatasetFromMaps(CDevice *pDevice, const CString &strDatasetID, CExBaseList *pDatasetList);
	CCpus* GetCpus(CDevice *pDevice);
	CCpus *m_pCpus;
	CDevice *m_pDevice;

	//shaolei 20220427 
	//��¼���е����ݼ�ӳ�䣬����ͨѶ����󶨵����ݼ��滻
	//����ӳ��ID���ҵ�ӳ������ݼ�
	CExBaseList *m_pDatasetMaps;

	void ValidateCmdValues(CDevice *pDevice, CCommCmd *pCommCmd);
	CExBaseObject* FindDataObjByRptDataPath(const CString &strPath, CCpus *pCpus);

	//���ݵ�ǰͨѶ��������ݼ�·�������Ҷ�Ӧ��ģ��ӳ��
	CExBaseObject* SelectDatasetMap(const CString &strDsPath);
	//shaolei 2023-2-22  ����ԭʼ���ݼ�ID���������е�ģ��ӳ��
	long SelectDatasetMaps(const CString &strDsID, CExBaseList *pMapList);
	//���ͨѶ����
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

