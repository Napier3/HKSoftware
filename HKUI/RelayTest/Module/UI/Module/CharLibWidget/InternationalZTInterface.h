#pragma once
#include "../../../../../Module/API/StringApi.h"
#include "../../../../../Module/DataMngr/DataMngrGlobal.h"
class CInternationalZTInterface
{
public:
	CInternationalZTInterface(void);
	virtual ~CInternationalZTInterface(void);

	virtual void SetAngleAndFaultype(const CString &strAngle, const CString &strFaultype)= 0; //设置页面显示角度与故障类型
	virtual void UpdateZTViewDraw(CString strName[], double dZSeting[], double dTSeting[], double dPlus[], double dMinus[]) = 0;//根据定值现实Z/T折线
	virtual void AddOneTestPoint(const CString &strIDPath, const CString &strFaultType, double dX, double dY);//添加测试点
	virtual void DeleteTestPoint(const CString &strIDPath);//删除测试点
	virtual void UpdateTestPoint(const CString &strIDPath, const CString &strFaultType, double dX, double dY, bool nState = -1);//更新测试点状态
};
