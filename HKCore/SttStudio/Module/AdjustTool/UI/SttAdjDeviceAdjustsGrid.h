//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

#pragma once

#include "..\..\..\..\Module\DataMngr\UI\XDataGroupGridBase.h"


class CSttAdjDeviceAdjustsGrid : public CXDvmGrid_GroupRowDataCol
{
public:
	CSttAdjDeviceAdjustsGrid();
	virtual ~CSttAdjDeviceAdjustsGrid();

	virtual void InitGrid();
	virtual void InitGridTitle();

//���غ���
public: 
	virtual CDataType* FindDataType(const CString &strDataType);

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
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

