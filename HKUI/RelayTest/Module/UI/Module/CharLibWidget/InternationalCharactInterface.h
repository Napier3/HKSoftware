#pragma once
#include "../../../../../Module/API/StringApi.h"

class CInternationalCharactInterface
{
public:
	CInternationalCharactInterface(void);
	virtual ~CInternationalCharactInterface(void);

	//添加距离保护单个测试项对应测试点,参数1传递当前测试项路径,参数2、3对应电阻值、电抗值、参数4对应故障类型，参数5对应区段 参数6对应当前测试点状态
	virtual void AddUpdateTestPoint_Imp(const CString &strIDPath, double dX, double dY, int nFaultType, int nZoneType, int nState = -1);

	virtual void AddUpdateTestPoint(const CString &strIDPath, double dX, double dY, int nFaultType, int nState = -1);

	//添加距离搜索单个测试项对应测试点, 参数1传递当前测试项路径, 参数2、3对应起始点电阻值、电抗值、参数4、5对应终值点电阻电抗值，参数6对应故障类型，参数7对应区段
	virtual void AddUpdateTestLine_Imp(const CString &strIDPath, double dBegX, double dBegY, double dEndX, double dEndY, int nFaultType, int nZoneType, int nState = -1);

	// 删除测试点 / 线
	virtual void DeleteTestData(const CString &strIDPath);
	//同期更新允许压差、允许频差参数,更新曲线界面显示
	virtual void UpdateTestCharParas_Syn(double dDFzd, double dDVzd);
	//更新指定特性曲线,对于测试功能对应单个特性曲线的情况,如差动比率制动\谐波制动
	virtual void UpdateCharacteristic(const CString &strCharID);
	//add wangtao 20240924差动的测试线添加到特性曲线图
	virtual void AddUpdateTestLine(const CString &strIDPath, double dBegX, double dBegY, double dEndX, double dEndY, int nFaultType, int nState = -1);
	//add wangtao 20240924差动的测试点添加到特性曲线图
//	virtual void AddUpdateTestPoint_Diff(const CString &strIDPath, double dX, double dY, int nFaultType, int nState = -1);
	virtual void UpdateCharacterisByFaultType(int nFaultType);//20241012 luozibing 未添加测试点时更新界面显示曲线故障类型

public slots:
    virtual void slot_UpdateDrawCharacters();   //20241015 wanmj

};