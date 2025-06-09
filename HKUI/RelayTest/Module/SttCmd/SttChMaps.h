﻿//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttChMaps.h  CSttChMaps

#pragma once

#include "SttCmdDefineGlobal.h"


#include "SttChMap.h"

#define MAPS_MAX_BINARYIN_COUNT		20
#define MAPS_MAX_BINARYOUT_COUNT		20
#define MAPS_MAX_ExBINARY_COUNT		256//最大扩展开关量数量,软件资源开放256in,256out,最大8个扩展模块

#define	MAPS_BINARY_TYPE_BIN		0
#define	MAPS_BINARY_TYPE_EXBIN		1
#define	MAPS_BINARY_TYPE_BOUT		2
#define	MAPS_BINARY_TYPE_EXBOUT		3

#define	MAPS_BINARY_ID_BIN			"Bin"
#define	MAPS_BINARY_ID_BINEX		"BinEx"
#define	MAPS_BINARY_ID_BOUT			"Bout"
#define	MAPS_BINARY_ID_BOUTEX		"BoutEx"


class CSttChMaps : public CExBaseList
{
public:
	CSttChMaps();
	virtual ~CSttChMaps();


//重载函数
public:
	virtual UINT GetClassID() {    return STTCMDCLASSID_CSTTCHMAPS;   }
	virtual BSTR GetXmlElementKey()  {      return CSttCmdDefineXmlRWKeys::CSttChMapsKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);
	virtual BOOL CanPaste(UINT nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

//私有成员变量
private:
	//20240904 huangliang 分别记录模拟量、开入、开出
	//QChar m_szBinDesc[MAPS_MAX_BINARYIN_COUNT][256];
	//QChar m_szBinExDesc[MAPS_MAX_ExBINARY_COUNT][256];
	//QChar m_szBoutDesc[MAPS_MAX_BINARYOUT_COUNT][256];
	//QChar m_szBoutExDesc[MAPS_MAX_ExBINARY_COUNT][256];
	CString m_szBinDesc[MAPS_MAX_BINARYIN_COUNT];
	CString m_szBinExDesc[MAPS_MAX_ExBINARY_COUNT];
	CString m_szBoutDesc[MAPS_MAX_BINARYOUT_COUNT];
	CString m_szBoutExDesc[MAPS_MAX_ExBINARY_COUNT];

//私有成员变量访问方法
public:

//属性变量访问方法
public:
	CSttChMap* FindByHdCh(long nType, const CString &strChID);
	CSttChMap* FindByHdCh(const CString &strType, const CString &strChID);
	CSttChMap* FindByHdCh(const CString &strType, const CString &strChID,float &fHdChCoef);//增加用于获取硬件通道系数

	CSttChMap* GetChMap(const CString &strSoftRsID);//查找子通道
	CSttChMap* AddChMap(const CString &strSoftRsName,const CString &strSoftRsID);

	CSttChMap* AddChMap_FindByID(const CString &strSoftRsName,const CString &strSoftRsID);//zhouhj 20211110 查找添加软件资源,先根据ID查找,如果查找到

	void SetChCountU(long nChNum);
	void SetChCountI(long nChNum);

	BOOL OpenChMapsFile(const CString &strChMapsPath);
	BOOL SaveChMapsFile(const CString &strChMapsPath);
	BOOL HasAnalogCurrModuleHdCh(long nModuleIndex);//判断是否包含模拟量电流插件模块,Index从1开始编号  zhouhj20211005

	void SortByRsIndex();//根据RsIndex对链表中通道进行重新排序
	BOOL HasMapHdResource(long nHasAnalog,long nHasDigital,long nHasWeek);//根据当前选择的输出类型，判断该通道是否应该存在软件资源
	BOOL GetMaxValue_WeekRates(double &dMaxVol,double &dMaxCur);

	//2022-9-19  lijunqing
	BOOL SetChMapsString(const CString &strChMaps);
	long GetChNum(const CString &strChID);//获取电压或电流通道的数量
	void UpdateWeekRateValue();//弱信号一次值或二次值修改后,更新其比例系数(网页界面下处理)

	//2024-5-6 wangtao
    void UpdateAliasByName();//更新别名，使其与Name保持一致

	//20240904 huangliang 
	void CreateDefaultBinBoutMaps();	//创建默认值
	void ClearBinBoutMaps();	//删除开入量开出量数据
	CString GetBinBoutNameForIndex(int iBin, int nIndex);	//获取开入开出

	void CopyBinBout(CBaseObject* pDest);	//20240921 huangliang 拷贝开入开出

	void CreateBinToList(CExBaseList *plistBin);
	void CreateBinExToList(CExBaseList *plistBin);
	void CreateBoutToList(CExBaseList *plistBout);
	void CreateBoutExToList(CExBaseList *plistBout);

	void ReadListToBin(CExBaseList *plistBin);
	void ReadListToBinEx(CExBaseList *plistBin);
	void ReadListToBout(CExBaseList *plistBout);
	void ReadListToBoutEx(CExBaseList *plistBout);
};

void Global_UpdateWeekRateValue(CExBaseList *pAnalogChMapList);
BOOL Global_HasMapHdResource(CExBaseList *pAnalogChMapList,long nHasAnalog, long nHasDigital, long nHasWeek);//根据当前选择的输出类型，判断该通道是否应该存在软件资源
BOOL Global_GetMaxValue_WeekRates(CExBaseList *pAnalogChMapList, double &dMaxVol, double &dMaxCur);
BOOL Global_HasAnalogCurrModuleHdCh(CExBaseList *pAnalogChMapList, long nModuleIndex);//判断是否包含模拟量电流插件模块,Index从1开始编号  zhouhj20211005
long Global_GetChNum(CExBaseList *pAnalogChMapList, const CString &strChID);//获取电压或电流通道的数量

