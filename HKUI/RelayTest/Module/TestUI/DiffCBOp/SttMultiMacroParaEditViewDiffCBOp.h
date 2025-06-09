#ifndef STTMULTIMACROPARAEDITVIEWDIFFPROTECTION_H
#define STTMULTIMACROPARAEDITVIEWDIFFPROTECTION_H

#include <QWidget>

#include "../QSttMultiMacroParaEditViewBase.h"
#include "../Module/CommonGrid/QSttMacroParaEditGrid.h"
#include "../../../../Module/TestMacro/TestMacro.h"
#include "DiffCBOpWiringWidget.h"


class QSttMultiMacroParaEditViewDiffCBOp : public QSttMultiMacroParaEditViewBase
{
    Q_OBJECT

public:
    explicit QSttMultiMacroParaEditViewDiffCBOp(const CString &strGridFile,QWidget *parent = 0);
    virtual ~QSttMultiMacroParaEditViewDiffCBOp();

    virtual void InitUI_OneMacro();
    virtual void InitDatas(CSttItems *pCurrRootItems);
    virtual void ConnectAll_SigSlot();
    virtual void DisConnectAll_SigSlot();
	virtual QWidget* GetSystemDiagramWidget(){ return m_pDiagramTab; }			//��ȡģ���е�ϵͳͼ����ָ��
	virtual QWidget* GetWiringDiagramWidget(){ return m_pDiffCBOpWiringWidget; }//��ȡģ���еĽ���ͼ����ָ��
//	//��ӵ���������ʱ,��ȡ��ǰ��Ŀ��Ҫ��ӵĸ��ڵ�,����뱣��,��Ҫ���������ͽ��з���,�統ǰ���ڵ�Items��������Ҫ��������
    virtual CSttItems* GetRootItems_CurrTestMacro(CSttMacroTest *pSttMacroTest);
	virtual void UpdateGoutTab(BOOL bUpdateList = FALSE);

	virtual char* GetMacroID(){ return STT_ORG_MACRO_DiffCBOpTest_I; }
	void InitGridTitleLanguage();   //20241025 ����ͷ�����Դ���
	void SetValueToInstColName(CSttGdInst_Col *pSttGdInst_Col);
public:
    QPushButton *m_pResultAssessBtn;
    QStackedWidget *m_pDiagramTab;
    QLabel *m_pLabel;
	QDiffCBOpWiringWidget *m_pDiffCBOpWiringWidget;
protected:
    CSttGdGridInst *m_pDiffProtectionGrid;

public slots:
    virtual void slot_AddOneItemBtnClick();//��ӵ���������
//		virtual void slot_AddMultiItemBtnClick();//���ϵ��
    virtual void slot_CommonParasBtnClick();//ͨ�ò���
    virtual void slot_BinarysBtnClick();//������
    virtual void slot_DeleteItemBtnClick();//ɾ��������
    virtual void slot_ClearResultBtnClick();//������Խ��


    virtual void slot_DeleteSelItemBtnClick();//ɾ����ǰѡ��
    virtual void slot_DeleteAllItemBtnClick();//ɾ��ȫ��

    virtual void slot_ClearSelResultBtnClick();//���ȫ�����
    virtual void slot_ClearAllResultBtnClick();//������н��
    void slot_strImagePath(const QString &strImagePath);
    void slot_ResultEstimateBtnClick();//�������


	void slot_UpdateDiffCBOpWiringWidget();//�����Ҳ����ͼ
    private slots:
        //void slot_AddOneLNBtnClick();
        //void slot_AddOneLLBtnClick();
        //void slot_AddMultBtnClick();

private:

//    QDialog *m_pAddMultiItemSelectDlg;//ѡ��ҳ��//�������  zhouhj 2024.9.15

    void InitAddMultiItemSelectDlg(QPoint pos,int nDlgState);
    void CheckAllPresence(CExBaseList *pListItems);

    //�����༭�����޸ĺ�,���µ���ǰѡ����
    virtual void slot_ParaEditWidget_To_Grid(CSttMacroTest* pMacroTest);

	typedef enum{
		DELETEITEM_DLG = 0,//ɾ��������Ŀ
		CLEARSELRESULT = 1//������Խ��
	}SELECTDLG_STATE;
};

#endif // STTMULTIMACROPARAEDITVIEWDISTANCE_H
