#ifndef SttIecGooseGrid_TurnList_H
#define SttIecGooseGrid_TurnList_H

#include "SttIecChsGridBase.h"
#include "SttIecRcdFuncInterface.h"

//GOOSE  ��λ�б�
class CSttIecGooseGrid_TurnList : public CSttIecChsGridBase, public CSttIecRcdFuncInterface
{
public:
	CSttIecGooseGrid_TurnList(QWidget* pparent);
	virtual ~CSttIecGooseGrid_TurnList();

	virtual void IecRcdFunc(CCapDeviceBase *pCapDevice);
	virtual void IecRcdFuncUpdate(CCapDeviceBase *pCapDevice);
	virtual void Release();
	virtual void Config();//ҳ�湦������
	virtual BOOL NeedConfig(){return TRUE;}
	virtual BOOL NeedAddToSubPub(){return TRUE;}

public:
	virtual void InitGridTitle();

	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE){};
	
	void ShowTurnList();
	void ShowTurn(PEP_GOOSE_BINARY_TURN pPrevTurn,PEP_GOOSE_BINARY_TURN pCurrTurn, long nRow);
};

#endif // SttIecGooseGrid_TurnList_H
