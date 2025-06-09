#pragma once
#include "../../../module/gridctrl/gridctrl.h"
#include "../GuideBook/GuideBookInterface.h"

class CCommCmdGrid :	public CGridCtrl
{
public:
	CCommCmdGrid(void);
	~CCommCmdGrid(void);

	void InitGrid();
	void InitGridTitle(); //��ʼ������

	void InitVariables(CCpu* pCpu);

	//Ҫ��GridCtrl����ʾ����Ŀ
	void InitVariables(CExBaseList* pShortDatas,CValues * pValues);
	void SaveValue(long nRow,long nCol);

protected:
		virtual void SaveValue(CExBaseObject *pParaObject, const CString &strValue) = 0;

protected:
	CString m_strType;
	CCpu* m_pCurCpu;

protected:
	virtual CExBaseList* GetDatas() = 0;
	virtual BOOL ShowOneObject(CExBaseObject * pParaObject,long &nRow) = 0;

	void UpdateVariables(CExBaseList *pList);
};
