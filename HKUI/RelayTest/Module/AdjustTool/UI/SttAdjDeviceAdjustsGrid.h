//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

#pragma once

#include "..\..\..\..\Module\DataMngr\UI\XDataGroupGridBase.h"


class CSttAdjDeviceAdjustsGrid : public CXDvmGrid_GroupRowDataCol
{
public:
	CSttAdjDeviceAdjustsGrid();
	virtual ~CSttAdjDeviceAdjustsGrid();

	virtual void InitGrid();
	virtual void InitGridTitle();

//重载函数
public: 
	virtual CDataType* FindDataType(const CString &strDataType);

//私有成员变量
private:

//私有成员变量访问方法
public:
	void ShowAdjDevice(CDataGroup *pAdjDevice);
protected:
	long ShowAdjModule(CDataGroup *pAdjModule, long &nRowIndex);
	long ShowAdjTemprature(CDataGroup *pTemprature, long &nRowIndex);
	long ShowAdjChannel_DC(CDataGroup *pChDC, long &nRowIndex);
	long ShowAdjChannel(CDataGroup *pChannel, long &nRowIndex);
	long ShowAdjChWave(CDataGroup *pChWave, long &nRowIndex);
	long ShowAdjChWaveGear(CDataGroup *pChWaveGear, long &nRowIndex);
	void AddAdjRows(long nRowIndex);
};

