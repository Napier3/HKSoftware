#pragma once
#include "../../../../../Module/API/StringApi.h"
#include "../../../../../Module/DataMngr/DataMngrGlobal.h"
class CInternationalZTInterface
{
public:
	CInternationalZTInterface(void);
	virtual ~CInternationalZTInterface(void);

	virtual void SetAngleAndFaultype(const CString &strAngle, const CString &strFaultype)= 0; //����ҳ����ʾ�Ƕ����������
	virtual void UpdateZTViewDraw(CString strName[], double dZSeting[], double dTSeting[], double dPlus[], double dMinus[]) = 0;//���ݶ�ֵ��ʵZ/T����
	virtual void AddOneTestPoint(const CString &strIDPath, const CString &strFaultType, double dX, double dY);//��Ӳ��Ե�
	virtual void DeleteTestPoint(const CString &strIDPath);//ɾ�����Ե�
	virtual void UpdateTestPoint(const CString &strIDPath, const CString &strFaultType, double dX, double dY, bool nState = -1);//���²��Ե�״̬
};
