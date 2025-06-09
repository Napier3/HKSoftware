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
 //   CExBaseList *GetMacroTestParaDatas_Inner();//zhouhj 2024.9.4 移入基类
	void AutoCalcKpx();//计算平衡系数
	void UpdatePara(CString strID, CString strValue);
	virtual void InitLanuage();
	bool isinf(double x) {  
		return x == std::numeric_limits<double>::infinity() || x == -std::numeric_limits<double>::infinity();  
	}//2024.10.17 zhangyq

	QLabel *m_pCurLabel;
	QComboBox *m_pCurCmbAdoptWind;
	CSttDiffCurrCalculatTool m_oDiffCBOpCalTool;

	int nKph;     //是否设置平衡系数
	float m_fKph;//高压侧差动平衡系数
	float m_fKpm;//中压侧差动平衡系数
	float m_fKpl;//低压侧差动平衡系数
	int		m_nInSel;	//基准电流选择 0-高侧二次额定电流 1-设定值 2-各侧二次额定电流 平台模板没有，恒为0 用以计算INOM
	float	m_fIbase;	//基准电流设定值
	BOOL	m_bMinAxis;	//定制整定方式 0-有名值 1-标幺值 平台模板没有，恒为1
	int		m_nConnectMode;	//测试绕组之间角差（钟点数）0-11 12点、1点--11点  11 即平台的变压器接线组别
	int		m_nPhase;		//故障相别	

	int m_nAdoptWind;		   //测试绕组
	int m_nPhCorrectMode;    //校正选择
	int m_nIbiasCal;         //制动方程
	int m_nWindH;            //高
	int m_nWindM;			 //中
	int m_nWindL;            //低
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
	//void sig_UpdateCurrSelGridData(CSttMacroTest* pSttMacroTest);	//20240805 huangliang 已入基类
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
