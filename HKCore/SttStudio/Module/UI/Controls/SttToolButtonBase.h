#ifndef QSTTTOOLBUTTONBASE_H
#define QSTTTOOLBUTTONBASE_H

#include <QToolButton>
#include "../Config/Frame/SttFrame_XBar.h"
#include "../../../../Module/DataMngr/DataGroup.h"
#include "../SttStyleSheetGlobalDefine.h"

class QSttToolButtonBase : public QToolButton
{
public:
    QSttToolButtonBase(CExBaseObject *pCfgData,QWidget *parent=0);
	virtual ~QSttToolButtonBase();
public:
	virtual void UpdateState(CDataGroup *pDataGroup);  //2022-6-9  lijunqing
	virtual void UpdateState(CDvmData *pData);  //2022-6-9  lijunqing  改为virtual
    virtual void SetPic(int nState){		}
	virtual void ShowBtn(bool bShow);
	virtual void UpdateEnableState(const CString &strState);
	//void InitFont();
	//void InitPicPos(CSttFrame_BarBase *pBarBase);

	CDvmData* FindData(CDataGroup *pDataGroup);
	CDvmData* FindData(CDataGroup *pDataGroup, const CString strID);

	//2022-12-02  lijunqing 设置图标
	void SetBtnIcon(CSttFrame_Button *pBtnData);
	void FillBtnIcon(CSttFrame_Button *pBtnData);
public:
    CExBaseObject *m_pCfgData;
	int m_nWidth;
	int m_nHeight;
	bool m_bShow;//初始化的时候都不显示，所以根据是否显示来调整位置不行，所以加一个属性
};


#endif // QSTTTOOLBUTTONBASE_H
