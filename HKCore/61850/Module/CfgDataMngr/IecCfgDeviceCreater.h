#pragma once
#include "IecCfgDevice.h"
#include "../IecCfgSclTool/SclToIecCfgTool.h"
class CIecCfgDeviceCreater
{
public:
	CIecCfgDeviceCreater();
	~CIecCfgDeviceCreater();

	CIecCfgDevice *m_pSrcIecfg;
	CSclToIecCfgTool *m_pSclToIecCfgTool;
private:
	CSclIed *m_pCurrSelSclIed;
	CIecCfgDevice *m_pNewIecfg;
// 	CSclCtrlsSmvIn  *m_pSmvins;
// 	CSclCtrlsGsIn *m_pGsins;
// 	CSclCtrlsGsOut *m_pGsouts;

public:
	CIecCfgDevice* GetNewIecCfgDevice(){   return m_pNewIecfg;   }
	void InitCreate(CIecCfgDevice *pSrcIecfg, CIecCfgDevice *pNewIecfg, CSclToIecCfgTool *pSclToIecCfgTool,CSclIed *pCurrSelSclIed);//zhouhj 20220204 ���Ӵ���,����ģ�������빤�̴������
	//��Դ.iecfg�ļ��Ķ���ָ�룬���ݸ�m_pSrcIecfg��SCD�ļ���Ϣ����m_pSclToIecCfgTool

	CIecCfgDatasMngr * CreateCIecCfgDatasMngr( CIecCfgDatasMngr *pSrc );
	//1�����ⲿ���λ�ȡԴCIecCfgDevice�е�CIecCfgDatasMngr���ڴ˺�����new�µ�CIecCfgDatasMngr����
	//2���ٷֱ����Smvs��Gins�ĺ��������µĳ�Ա��������Gouts��ֱ�ӿ���Դ�еģ� 
	//3��bIndex����Ƿ񴴽��ĵ�һ������������ǵ�һ�Σ��������õ�CIecCfgDatasMngr�����µ�
	//CIecCfgDevice�Ļ���CExBaseListͷ�ڵ㣬�ڶ��ڵ�����µ�Ied����
	//4�������µ�CIecCfgDatasMngr�����紴��ʧ�ܷ���NULL��

protected:
	void CreateCIecCfgDatasMngr_CfgSmvDatas(CIecCfgDatasSMV*pSrc , CIecCfgDatasMngr *pNew/*CIecCfgDatasSMV*pNew*/);
	//1�����λ�ȡԴdatas�е�CIecCfg92Data����ͨ�������data����new�µ�data����ֱ�Ӵ���datas�У�

	void CreateCIecCfgDatasMngr_CfgSmvData(CIecCfg92Data*pSrc , CIecCfgDatasMngr *pNew/*CIecCfgDatasSMV*pNew*/);
	//1����ȡԴdata�и�ͨ����index-externalֵ��Ϊ-1�ģ��ҳ���ͨ����Ӧ��addr-externalֵ����SCD�ļ��ж�Ӧ��//��IED���ڲ�·����������SCD�ı�����IED���ҵ����·��ֵƥ���ͨ�����ҵ���ͨ����Ӧ�ĺϲ���Ԫ//��IED���ƣ����ҵ���Ӧ�ϲ���Ԫ��SMVOUT��Ϣ��
	//2�������˺ϲ���Ԫ������ͨ��������ںš���ѹ��������ͨ��ƥ�����Ϣ�滻���µ�data�У�
	//3�����ºϲ���ԪIED���ƴ���m_iedName�У��Ա��ڲ��Һϲ���Ԫǰ���жϴ�ied�Ƿ��Ѿ���������
	//4���緢���½��ϲ���Ԫ�Ѿ�������������ֱ���ҵ���Ӧ�����ý���ѹ����ͨ��ƥ����滻��
	CIecCfg92Ch* CreateCIecCfgDatasMngr_SearchPath(CString path , CIecCfgDatasSMV  *pIecCfgDatasNew);
	CIecCfgGoutCh* CreateCIecCfgDatasMngr_SearchPath(CString path , CIecCfgGoutDatas  *pIecCfgDatasNew);

	void CreateCIecCfgDatasMngr_CfgGoutDatas(CIecCfgGoutDatas *pSrc  ,CIecCfgDatasMngr *pNew);
	void CreateCIecCfgDatasMngr_CfgGoutData(CIecCfgGoutData *pSrc  ,CIecCfgDatasMngr *pNew);

	void CreateCIecCfgDatasMngr_CfgGinDatas(CIecCfgGinDatas *pSrc  ,CIecCfgDatasMngr *pNew);
	void CreateCIecCfgDatasMngr_CfgGinData(CIecCfgGinData *pSrc  ,CIecCfgDatasMngr *pNew);

};

