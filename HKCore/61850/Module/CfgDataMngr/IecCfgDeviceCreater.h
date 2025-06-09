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
	void InitCreate(CIecCfgDevice *pSrcIecfg, CIecCfgDevice *pNewIecfg, CSclToIecCfgTool *pSclToIecCfgTool,CSclIed *pCurrSelSclIed);//zhouhj 20220204 增加传参,公共模块内容与工程代码分离
	//将源.iecfg文件的对象指针，传递给m_pSrcIecfg；SCD文件信息传给m_pSclToIecCfgTool

	CIecCfgDatasMngr * CreateCIecCfgDatasMngr( CIecCfgDatasMngr *pSrc );
	//1、在外部依次获取源CIecCfgDevice中的CIecCfgDatasMngr，在此函数中new新的CIecCfgDatasMngr对象；
	//2、再分别调用Smvs、Gins的函数创建新的成员变量对象，Gouts的直接拷贝源中的； 
	//3、bIndex标记是否创建的第一个管理对象，如是第一次，将创建好的CIecCfgDatasMngr放入新的
	//CIecCfgDevice的基类CExBaseList头节点，第二节点存入新的Ied对象；
	//4、返回新的CIecCfgDatasMngr对象，如创建失败返回NULL；

protected:
	void CreateCIecCfgDatasMngr_CfgSmvDatas(CIecCfgDatasSMV*pSrc , CIecCfgDatasMngr *pNew/*CIecCfgDatasSMV*pNew*/);
	//1、依次获取源datas中的CIecCfg92Data对象通过下面的data函数new新的data对象，直接存入datas中；

	void CreateCIecCfgDatasMngr_CfgSmvData(CIecCfg92Data*pSrc , CIecCfgDatasMngr *pNew/*CIecCfgDatasSMV*pNew*/);
	//1、获取源data中各通道中index-external值不为-1的，找出此通道对应的addr-external值（即SCD文件中对应的//本IED的内部路径），在新SCD的本保护IED中找到与此路径值匹配的通道，找到此通道对应的合并单元//的IED名称，再找到对应合并单元的SMVOUT信息；
	//2、创建此合并单元的所有通道，将光口号、电压、电流的通道匹配等信息替换入新的data中；
	//3、将新合并单元IED名称存入m_iedName中，以便在查找合并单元前先判断此ied是否已经被创建；
	//4、如发现新建合并单元已经被创建过，则直接找到对应的配置将电压电流通道匹配等替换；
	CIecCfg92Ch* CreateCIecCfgDatasMngr_SearchPath(CString path , CIecCfgDatasSMV  *pIecCfgDatasNew);
	CIecCfgGoutCh* CreateCIecCfgDatasMngr_SearchPath(CString path , CIecCfgGoutDatas  *pIecCfgDatasNew);

	void CreateCIecCfgDatasMngr_CfgGoutDatas(CIecCfgGoutDatas *pSrc  ,CIecCfgDatasMngr *pNew);
	void CreateCIecCfgDatasMngr_CfgGoutData(CIecCfgGoutData *pSrc  ,CIecCfgDatasMngr *pNew);

	void CreateCIecCfgDatasMngr_CfgGinDatas(CIecCfgGinDatas *pSrc  ,CIecCfgDatasMngr *pNew);
	void CreateCIecCfgDatasMngr_CfgGinData(CIecCfgGinData *pSrc  ,CIecCfgDatasMngr *pNew);

};

