#ifndef CharEditWidget_Diff_H
#define CharEditWidget_Diff_H

#include <QWidget>
#include <QLabel>
#include "ui_CharEditWidget_Diff.h"
#include "CharEditWidgetBase.h"
#include "CharEditMainWidget.h"
#include "../../../../../Module/FaultCal/DiffCharCal.h"
#include "../../../../../AutoTest/Module/Characteristic/Characteristic.h"
#include <QStackedWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QRadioButton>
class QCharEditRadioNormalWidget;
class QCharEditRadioHarmWidget;


#define DIFF_GRID_CLOS 4
#define CharDiff_ID_StartCurr_Check              _T("StartCurr_Check")//��������ѡ��
#define CharDiff_ID_RateCoef1_Check              _T("RateCoef1_Check")//����ָ��ϵ��1ѡ��
#define CharDiff_ID_RateCoef2_Check              _T("RateCoef2_Check")//����ָ��ϵ��2ѡ��
#define CharDiff_ID_RateCoef3_Check              _T("RateCoef3_Check")//����ָ��ϵ��3ѡ��
#define CharDiff_ID_QuickCurr_Check              _T("QuickCurr_Check")//��ٶ�ѡ��
#define CharDiff_ID_IDoor                        _T("IDoor")//��ż�ֵ
#define CharDiff_ID_IQuickSetting                _T("IQuickSetting")//��ٶ϶�ֵ
#define CharDiff_ID_Limp1                        _T("Limp1")//�յ�1����ֵ
#define CharDiff_ID_Limp2                        _T("Limp2")//�յ�2����ֵ
#define CharDiff_ID_Limp3                        _T("Limp3")//�յ�3����ֵ
#define CharDiff_ID_StartCurr_Kid                _T("StartCurr_Kid")//������б��
#define CharDiff_ID_RateCoef_Kid1                _T("RateCoef_Kid1")//�б��1
#define CharDiff_ID_RateCoef_Kid2                _T("RateCoef_Kid2")//�б��2
#define CharDiff_ID_RateCoef_Kid3                _T("RateCoef_Kid3")//�б��3
#define CharDiff_ID_RateHarm                      _T("RateHarm")//г���ƶ�ϵ��
#define CharDiff_ID_CTPoint							_T("CTPoint")//CT����

#define CharDiff_ID_MinAxis                      _T("MinAxis")//��ֵ������ʽ
#define CharDiff_ID_Insel                        _T("Insel")//��׼����ѡ��
#define CharDiff_ID_In                           _T("In")//��׼����(����)
#define CharDiff_ID_HarmIndex                    _T("HarmIndex")//г������

#define CharDiff_RateCoef1_Index                 1
#define CharDiff_RateCoef2_Index                 2
#define CharDiff_RateCoef3_Index                 3
#define CharDiff_QuickCurr_Index                 4

#define CharDiff_ID_StartCurrPointNum              _T("StartCurrPointNum")
#define CharDiff_ID_RateCoef1PointNum              _T("RateCoef1PointNum")   
#define CharDiff_ID_RateCoef2PointNum              _T("RateCoef2PointNum")   
#define CharDiff_ID_RateCoef3PointNum              _T("RateCoef3PointNum")   
#define CharDiff_ID_QuickCurrPointNum              _T("QuickCurrPointNum")   

#define CharDiff_ID_StartCurrErrorBand              _T("StartCurrErrorBand")
#define CharDiff_ID_RateCoef1ErrorBand              _T("RateCoef1ErrorBand")
#define CharDiff_ID_RateCoef2ErrorBand              _T("RateCoef2ErrorBand")
#define CharDiff_ID_RateCoef3ErrorBand              _T("RateCoef3ErrorBand")
#define CharDiff_ID_QuickCurrErrorBand              _T("QuickCurrErrorBand")


#define ElecRailway_TransType_0_YV                         0
#define ElecRailway_TransType_1_YD11                       1//��ת��
#define ElecRailway_TransType_2_Single                     2
#define ElecRailway_TransType_3_YDD                        3
#define ElecRailway_TransType_4_Scott1                     4
#define ElecRailway_TransType_5_VV1                        5
#define ElecRailway_TransType_6_VX                         6
#define ElecRailway_TransType_7_YA                         7
#define ElecRailway_TransType_8_ThreeVV                    8
#define ElecRailway_TransType_9_Scott2                     9
#define ElecRailway_TransType_10_Scott3                    10
#define ElecRailway_TransType_11_VV2                       11
#define ElecRailway_TransType_12_Scott4                    12
#define ElecRailway_TransType_13_ThreeVV2                  13
#define ElecRailway_TransType_14_ThreeVV3                  14
#define ElecRailway_TransType_15_ThreeYV2                  15//��ת��
#define ElecRailway_TransType_16_Scott5                    16
#define ElecRailway_TransType_17_YD11_YT                   17//��Y�����ת��
#define ElecRailway_TransType_18_ThreeYV2_YT               18//��Y�����ת��

//QCharEditGrid_DiffLine���
class QCharEditGrid_DiffLine : public QCharEditGridBase
{
	Q_OBJECT

public:
	QCharEditGrid_DiffLine(QWidget* pParent);
	virtual ~QCharEditGrid_DiffLine();

public:
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
	virtual void EmitCharChanged();
	void GridDoubleClicked_ShowKeyBoard(int nRow,int nCol);
	static void EndEditCell_TestPoints(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid);
	static void EndEditCell_ErrorBand(int nRow, int nCol, QGV_ITEM *pCell, QExBaseListGridBase *pGrid);

	void EmitTestPointsErrorBandChanged();
	virtual void slot_CurrentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn);

signals:
	void sig_TestPointsErrorBandChanged();
	void sig_DiffCharChanged();

private slots:
	void slot_doubleClicked(int nRow,int nCol);
};

////////////////////////////////////////////////////////��·�///////////////////////////////////////////////////////////////////////////////////////
class QCharEditWidget_LineDiff : public QWidget, public QCharEditWidgetBase, public CExBaseListGridOptrInterface
{
	Q_OBJECT

public:
	QCharEditWidget_LineDiff(BOOL bShowIp2,QWidget *parent = 0);//����1ȷ���Ƿ���ʾб��2
	~QCharEditWidget_LineDiff();

	QCharEditGrid_DiffLine *m_pGridCharLine;
	QCharEditMainWidget* m_pMainWidget; 

signals:
	void sig_CharChanged(CExBaseObject *,int);

private:
//	Ui::QCharEditWidget_Diff ui;
	QVBoxLayout *m_pMain_VLayout;
	QGridLayout *m_pDiffChar_GridLayout;
	QHBoxLayout *m_pCustomAdd_HLayout;

	//����������ؿؼ�
	QLabel *m_pCharName_Label;
	QLabel *m_pCharSetting_Label;
	QLabel *m_pCharCurrent_Label;
	QLabel *m_pCharK_Label;

	QLabel *m_pIcdqd_Label;
	QLabel *m_pK1_Label;
	QCheckBox *m_pK2_CheckBox;

	QLabel *m_pIcdqd_SettingLabel;
	QLabel *m_pK1_SettingLabel;
	QLabel *m_pK2_SettingLabel;
	QLabel *m_pMaxId_Label;//������ֵ

	QSttLineEdit *m_pIcdqd_Edit;
	QSttLineEdit *m_pIp1_Edit;
	QSttLineEdit *m_pIp2_Edit;
	QSttLineEdit *m_pMaxId_Edit;//������ֵ

	QSttLineEdit *m_pKcdqd_Edit;
	QSttLineEdit *m_pKp1_Edit;
	QSttLineEdit *m_pKp2_Edit;
	BOOL m_bShowIp2;


	//����Զ������ؿؼ�
	QLabel *m_pIdCustom_Label;
	QSttLineEdit *m_pIdCustom_Edit;
	QSpacerItem *m_pAddCustom_HorizontalSpacer;
	QPushButton *m_pAddCustomPoint_PushButton;
	QPushButton *m_pClearCustomPoint_PushButton;

	CDiffCharCal m_oDiffCharCal;

public:
	void InitUI();
	void InitConnect();
	void InitChar();
	void UpdateChar(BOOL bUpdateTable = FALSE,BOOL bCharTypeChanged = FALSE,BOOL bParasChanged = TRUE);//����2λ�Ƿ�����ƶ���г���ƶ��л�,����3Ϊ�Ƿ�����ı����
	void InitDiffData();
	void InitUI_Unit();//���½��浥λ
	float SetParaI(QLineEdit* pEdit, float& fv);
	float SetParaK(QLineEdit* pEdit, float& fv);
	float SetLimit(float min,float max,float val);
	float CalLineK(CCharElementLined* pLine);

	void SetDiffFont(); //2022-10-31 sy  ��������
	virtual void OnLeftButtonDown();

	virtual void GroupDatasToChar(CDataGroup *pDatas);//��ģ����ͼ���ݸ�ֵ���������߽���
	virtual void CharToGroupDatas(CDataGroup *pDatas);//���������߽���������ݸ�ֵ��ģ����ͼ����
	void UpdateEdit_IrValueUserPoint();//�����û��Զ�����ƶ�����ֵ
	virtual void OnDataSelChanged(QTableWidget *pGridCtrl, int nRow, int nCol);//20230731 wxy �����߶�


protected:
	void UpdateEditsDisEnable();//���±༭��ؼ��ķ�ʹ��״̬
	void ShowDatas_Table();//���߶���ʾ�������,�����߶���������
	void GetTestPointNumErrorBand();
	CCharacteristic* GetCurrentCharacter();//�����ƶ�orг���ƶ�

private slots:
	void on_m_chkLine2_clicked();
	void on_m_edtSet_Istart_editingFinished();
	void on_m_edtSet_Kstart_editingFinished();
	void on_m_edtSet_Ip1_editingFinished();
	void on_m_edtSet_K1_editingFinished();
	void on_m_edtSet_Ip2_editingFinished();
	void on_m_edtSet_K2_editingFinished();
	void on_m_onlineEdit_Changed();
	void slot_TestPointsErrorBandChanged();
	void slot_DiffCharChanged();
	void slot_IdValue_editingFinished();
	void slot_MaxIdEditingFinished();

	void slot_btnUserAdd(bool bState);
	void slot_btnUserClear(bool bState);
};

////////////////////////////////////////////////////////��ѹ���//////////////////////////////////////////////////////////////////////////////////////
class QCharEditWidget_Diff : public QWidget, public QCharEditWidgetBase, public CExBaseListGridOptrInterface
{
	Q_OBJECT

public:
	QCharEditWidget_Diff(QWidget *parent = 0);
	~QCharEditWidget_Diff();

	QCharEditGrid_DiffLine *m_pGridCharLine;

signals:
	void sig_CharChanged(CExBaseObject *,int);

private:
	Ui::QCharEditWidget_Diff ui;

	CDiffCharCal m_oDiffCharCal;
	
public:
	void InitUI();
	void InitConnect();
	void InitChar();
	void UpdateChar(BOOL bUpdateTable = FALSE,BOOL bCharTypeChanged = FALSE,BOOL bParasChanged = TRUE);//����2λ�Ƿ�����ƶ���г���ƶ��л�
	void InitDiffData();
	void InitUI_Unit();//���½��浥λ
	void EnableEdit(long nIndex);
	void DisableEdit(long nIndex);
	float SetParaI(QLineEdit* pEdit, float& fv);
	float SetParaK(QLineEdit* pEdit, float& fv);
	float SetLimit(float min,float max,float val);
	float CalLineK(CCharElementLined* pLine);

	void SetDiffFont(); //2022-10-31 sy  ��������

//	virtual void AddTestPoint(CExBaseList* pValue);
	virtual void OnLeftButtonDown();

	virtual void GroupDatasToChar(CDataGroup *pDatas);//��ģ����ͼ���ݸ�ֵ���������߽���
	virtual void CharToGroupDatas(CDataGroup *pDatas);//���������߽���������ݸ�ֵ��ģ����ͼ����
	void UpdateEdit_IrValueUserPoint();//�����û��Զ�����ƶ�����ֵ
	virtual void OnDataSelChanged(QTableWidget *pGridCtrl, int nRow, int nCol);
	
	QCharEditMainWidget* m_pMainWidget;//20230808 suyang �ദ����Ϊ������ ʹ��ȫ�ֱ������ö������

protected:
	void UpdateEditsDisEnable();//���±༭��ؼ��ķ�ʹ��״̬
	void ShowDatas_Table();//���߶���ʾ�������,�����߶���������
	void GetTestPointNumErrorBand();
	CCharacteristic* GetCurrentCharacter();//�����ƶ�orг���ƶ�
	bool IsNotHarm();

private slots:
    void on_m_chkStart_clicked();
    void on_m_chkLine1_clicked();
    void on_m_chkLine2_clicked();
    void on_m_chkLine3_clicked();
    void on_m_chkLineSd_clicked();
    void on_m_edtSet_Istart_editingFinished();
    void on_m_edtSet_Kstart_editingFinished();
    void on_m_edtSet_Ip1_editingFinished();
    void on_m_edtSet_K1_editingFinished();
    void on_m_edtSet_Ip2_editingFinished();
    void on_m_edtSet_K2_editingFinished();
    void on_m_edtSet_Ip3_editingFinished();
    void on_m_edtSet_K3_editingFinished();
    void on_m_edtSet_Isd_editingFinished();
	void on_m_onlineEdit_Changed();
	void slot_TestPointsErrorBandChanged();
	void slot_DiffCharChanged();
	void slot_IdValue_editingFinished();

	void slot_btnUserAdd(bool bState);
	void slot_btnUserClear(bool bState);

	void slot_radioNormal_Clicked();
	void slot_radioHarm_Clicked();
	void slot_CmbSettingMinAxisIndexChanged(int nIndex);
	void slot_CmbInSeIndexChanged(int nIndex);
	void slot_CmbHarmIndexChanged(int nIndex);
	void slot_InSet_editingFinished();
	void slot_HarmCoef_editingFinished();
};

//////////////////////////////////////////////////////ǣ����//////////////////////////////////////////////////////////////////////////////////////
class QCharEditWidget_ElecRailwayDiff : public QWidget, public QCharEditWidgetBase
{
	Q_OBJECT

public:
	QCharEditWidget_ElecRailwayDiff(QWidget *parent = 0);
	~QCharEditWidget_ElecRailwayDiff();

	QCharEditRadioNormalWidget *m_qCharRadioNormalWidget;
	QCharEditRadioHarmWidget *m_qCharRadioHarmWidget;
	QCharEditMainWidget* m_pMainWidget; 
	CDiffCharCal m_oDiffCharCal;

signals:
	void sig_CharChanged(CExBaseObject *,int);	

public:
	void InitUI();
	void InitConnect();
	void InitChar();
	void InitUI_Unit();//���½��浥λ
	void UpdateChar(BOOL bUpdateTable = FALSE,BOOL bCharTypeChanged = FALSE,BOOL bParasChanged = TRUE);//����2λ�Ƿ�����ƶ���г���ƶ��л�
	float SetParaI(QLineEdit* pEdit, float& fv);
	float SetParaK(QLineEdit* pEdit, float& fv);
	float SetLimit(float min,float max,float val);
	float CalLineK(CCharElementLined* pLine);

	void SetDiffFont(); //2022-10-31 sy  ��������
	virtual void OnLeftButtonDown();
	virtual void GroupDatasToChar(CDataGroup *pDatas);//��ģ����ͼ���ݸ�ֵ���������߽���
	virtual void CharToGroupDatas(CDataGroup *pDatas);//���������߽���������ݸ�ֵ��ģ����ͼ����

protected:
	void ShowDatas_Table();//���߶���ʾ�������,�����߶���������
	void GetTestPointNumErrorBand();
	CCharacteristic* GetCurrentCharacter();//�����ƶ�orг���ƶ�
	bool IsNotHarm();

private slots:
	void on_m_onlineEdit_Changed();
	void IdValue_NormalEditing(CString strIdValue);
	void ChangeMainWin_Char();
	void slot_TestPointsErrorBandChanged();
	void slot_DiffCharChanged();
	void slot_radioNormal_Clicked();
	void slot_radioHarm_Clicked();
	void slot_ChangeICMAxisName();
	void slot_UpdateChar(bool bUpdateTable,bool bCharTypeChanged,bool bParasChanged);
	void slot_ActiveSegment(CCharElement *pCurrSelElement);

public:
	CDataGroup *m_pDataGroup;
	long m_nCTPoint;//2023-07-13 wxy CT���� 1-һ��ָ���ѹ�� 0-����ָ���ѹ��
	long m_nTranSort;//2023-07-14 wxy ��ѹ��������ʽ

private:
	QVBoxLayout *m_mainQVBoxLayout;
	QHBoxLayout *m_QHBoxLayout;
	QWidget *m_QHBoxWidget;
	QRadioButton *m_radioNormal,*m_radioHarm;
	QStackedWidget *m_stackedWidget;
	
};

#endif // CharEditWidget_Diff_H
