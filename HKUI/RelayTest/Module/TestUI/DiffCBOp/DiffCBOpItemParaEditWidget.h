#ifndef DIFFCBOPITEMPARAEDITWIDGET_H
#define DIFFCBOPITEMPARAEDITWIDGET_H

#include <QWidget>
#include <limits>
#include "../Interface/QItemParaEditWidgetBase.h"
#include "./DiffCBOpCommonParasDlg.h"
#include "SttMultiMacroParaEditViewDiffCBOp.h"
#include "../../SttTestBase/SttDiffCurrCalculatTool.h"

namespace Ui {
    class QDiffCBOpItemParaEditWidget;
}

class QDiffCBOpItemParaEditWidget : public QItemParaEditWidgetBase

{
    Q_OBJECT

public:
	Ui::QDiffCBOpItemParaEditWidget *m_pParaUI;

    explicit QDiffCBOpItemParaEditWidget(QWidget *parent = 0);
    virtual ~QDiffCBOpItemParaEditWidget();
    virtual void UpdateParas(CSttMacroTest *pSttMacroTest);
    CString CheckDataMinMax(CString strValue,float nMax,float nMin,int nAfterPoint);
    CExBaseList *GetMacroTestParaDatas();
 //   CExBaseList *GetMacroTestParaDatas_Inner();//zhouhj 2024.9.4 �������
	void AutoCalcKpx();//����ƽ��ϵ��
	void UpdatePara(CString strID, CString strValue);
	virtual void InitLanuage();
	bool isinf(double x) {  
		return x == std::numeric_limits<double>::infinity() || x == -std::numeric_limits<double>::infinity();  
	}//2024.10.17 zhangyq

	QLabel *m_pCurLabel;
	QComboBox *m_pCurCmbAdoptWind;
	CSttDiffCurrCalculatTool m_oDiffCBOpCalTool;

	int nKph;     //�Ƿ�����ƽ��ϵ��
	float m_fKph;//��ѹ��ƽ��ϵ��
	float m_fKpm;//��ѹ��ƽ��ϵ��
	float m_fKpl;//��ѹ��ƽ��ϵ��
	int		m_nInSel;	//��׼����ѡ�� 0-�߲���ζ���� 1-�趨ֵ 2-������ζ���� ƽ̨ģ��û�У���Ϊ0 ���Լ���INOM
	float	m_fIbase;	//��׼�����趨ֵ
	BOOL	m_bMinAxis;	//����������ʽ 0-����ֵ 1-����ֵ ƽ̨ģ��û�У���Ϊ1
	int		m_nConnectMode;	//��������֮��ǲ�ӵ�����0-11 12�㡢1��--11��  11 ��ƽ̨�ı�ѹ���������
	int		m_nPhase;		//�������	

	int m_nAdoptWind;		   //��������
	int m_nPhCorrectMode;    //У��ѡ��
	int m_nIbiasCal;         //�ƶ�����
	int m_nWindH;            //��
	int m_nWindM;			 //��
	int m_nWindL;            //��
	int m_nK1;
	int m_nK2;
	int m_nBalanceterms;
	int m_nCT;
	int m_nKcal;

private slots:
    void on_m_pCmbFaultType_currentIndexChanged(int index);
    void on_m_pCmbFaultLocation_currentIndexChanged(int index);


    void on_m_pEditCurent_editingFinished();
    void on_m_pEditFrep_editingFinished();
    void on_m_pEditTransfHvKph_editingFinished();
    void on_m_pEditTransfHvVol_editingFinished();
    void on_m_pEditTransfHvCur_editingFinished();
    void on_m_pEditTransfHvCT_editingFinished();
    void on_m_pEditTransfHvKVA_editingFinished();
    void on_m_pEditTransfMvKpm_editingFinished();
    void on_m_pEditTransfMvVol_editingFinished();
    void on_m_pEditTransfMvCur_editingFinished();
    void on_m_pEditTransfMvCT_editingFinished();
    void on_m_pEditTransfLvKpl_editingFinished();
    void on_m_pEditTransfLvVol_editingFinished();
    void on_m_pEditTransfLvCur_editingFinished();
    void on_m_pEditTransfLvCT_editingFinished();
    void on_m_pEditAbsErrSum_editingFinished();
    void on_m_pEditAbsErrReduce_editingFinished();
    void on_m_pEditRelErr_editingFinished();
	void on_m_pChkKph_clicked(bool nState);

signals:
	//void sig_UpdateCurrSelGridData(CSttMacroTest* pSttMacroTest);	//20240805 huangliang �������
    void sig_strImagePath(const QString &strImagePath);

private:
    void InitUI();
	
    int m_nModify;

    void SetValueToPage(CSttMacroTestParaData *pData);

    void SetModeText(int nIndex);

    void CheckAllPresence(CExBaseList *pParas);
    void CheckForPresence(CExBaseList *pParas,CString strID);
};
#endif // PARASETWIDGET_H
