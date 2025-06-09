#ifndef DIFFCOMMONPARASDLG_H
#define DIFFCOMMONPARASDLG_H

#include <QDialog>
//#include "../SttTestCntrFrameBase.h"

#include "SttMultiMacroDiffParasDefine.h"
#include "../../../../Module/DataMngr/DataGroup.h"
#include "../../SttCmd/GuideBook/SttMacroTest.h"
#include <math.h> 
#include <limits>
#include "../../SttTestBase/SttDiffCurrCalculatTool.h"

namespace Ui {
class QDiffCommonParasDlg;
}
class QDiffCommonParasDlg : public QDialog
{
    Q_OBJECT

public:
    explicit QDiffCommonParasDlg(QWidget *parent = 0);
    ~QDiffCommonParasDlg();

	void GetDatas(CExBaseList *pParas);
	void SetDatas(CExBaseList *pParas);
	void UpdataAllCommonParas(CExBaseList *pParas);
    BOOL CheckItemsModify(CExBaseList *pAllItems);
	void AutoCalcKpx();//����ƽ��ϵ��
	bool isinf(double x) {  
		return x == std::numeric_limits<double>::infinity() || x == -std::numeric_limits<double>::infinity();  
	}//2024.10.17 zhangyq

private slots:

	void on_m_txtPrepareTime_editingFinished();       //׼��ʱ��(s)
	void on_m_txtPreFaultTime_editingFinished();		//����ǰʱ��(s)
	void on_m_txtFaultTime_editingFinished();		//����ʱ��ԣ��(s)
	void on_m_txtTimeAfter_editingFinished();         //���������ʱ��(s)
	void on_m_cmbKPSetMode_currentIndexChanged(int index);						//����ƽ��ϵ��
	void slot_m_txtSn_editingFinished();				//��ѹ�������(MVA)					
	void slot_m_txtHUn_editingFinished();				//��ѹ����ѹ(kV)					
	void slot_m_txtMUn_editingFinished();				//��ѹ����ѹ(kV)				
	void slot_m_txtLUn_editingFinished();				//��ѹ����ѹ(kV)					
	void slot_m_txtCTPh_editingFinished();				//��ѹ��CTһ��ֵ(A)					
	void slot_m_txtCTPm_editingFinished();				//��ѹ��CTһ��ֵ(A)					
	void slot_m_txtCTPl_editingFinished();				//��ѹ��CTһ��ֵ(A) 					
	void slot_m_txtCTSh_editingFinished();				//��ѹ��CT����ֵ(A)					
	void slot_m_txtCTSm_editingFinished();				//��ѹ��CT����ֵ(A)				
	void slot_m_txtCTSl_editingFinished();				//��ѹ��CT����ֵ(A)				
	void on_m_txtKphSet_editingFinished();			//��ѹ��ƽ��ϵ��
	void on_m_txtKpmSet_editingFinished();			//��ѹ��ƽ��ϵ��				
	void on_m_txtKplSet_editingFinished();			//��ѹ��ƽ��ϵ��				
	void slot_m_cmbWindH_currentIndexChanged(int index);				//��ѹ�����������ʽ					
	void slot_m_cmbWindM_currentIndexChanged(int index);				//��ѹ�����������ʽ						
	void slot_m_cmbWindL_currentIndexChanged(int index);				//��ѹ�����������ʽ
	void slot_m_cmbPhCorrectMode_currentIndexChanged(int index);		//У��ѡ��				
	void slot_m_cmbAdoptWind_currentIndexChanged(int index);			//��������	
	void on_m_cmbTransGroupMode1_currentIndexChanged(int index);	//��-�������ӵ���		
	void on_m_cmbTransGroupMode2_currentIndexChanged(int index);	//��-�������ӵ���				
	void slot_m_cmbJXFactor_currentIndexChanged(int index);			//ƽ��ϵ������			
	void on_m_cmbSearchMode_currentIndexChanged(int index);		//��������				
	void on_m_cmbCTPoint_currentIndexChanged(int index);			//CT����			
	void on_m_cmbIrEquation_currentIndexChanged(int index);		//�ƶ�����					
	void on_m_txtK_editingFinished();	//K1				
	void on_m_txtK2_editingFinished();	//K2					
	void on_m_cmbEarthing_currentIndexChanged(int index);			//�ӵ�					
	void on_m_txtStep_editingFinished();				//���Ծ���				
	void on_m_txtVg1_editingFinished();				//Ua��Ub��Uc(V)			
	void on_m_txtVg2_editingFinished();				//Ua2��Ub2��Uc2(V)

	void on_m_btnOK_clicked();
	void on_m_btnCancel_clicked();
private:
    Ui::QDiffCommonParasDlg *ui;
	CExBaseList *m_pParas;
	CSttDiffCurrCalculatTool m_oDiffCalTool;
	CSttMacroTest m_oSttMacroTest_Inner;
	
	int m_nModify;
	float m_fKph;//��ѹ��ƽ��ϵ��
	float m_fKpm;//��ѹ��ƽ��ϵ��
	float m_fKpl;//��ѹ��ƽ��ϵ��
	int		m_nInSel;	//��׼����ѡ�� 0-�߲���ζ���� 1-�趨ֵ 2-������ζ���� ƽ̨ģ��û�У���Ϊ0 ���Լ���INOM
	float	m_fIbase;	//��׼�����趨ֵ
	BOOL	m_bMinAxis;	//����������ʽ 0-����ֵ 1-����ֵ ƽ̨ģ��û�У���Ϊ1
	int		m_nConnectMode;	//��������֮��ǲ�ӵ�����0-11 12�㡢1��--11��  11 ��ƽ̨�ı�ѹ���������
	int		m_nPhase;		//�������	

	void SetValueToPage(CSttMacroTestParaData *pData);
	void GetPageToValue(CSttMacroTestParaData *pData);
	void InitUI();
	void CheckAllPresence(CExBaseList *pParas);
	void ConnectAutoCalcKpx_SigSlot();
	void DisConnectAutoCalcKpx_SigSlot();
};
CString CheckDataMinMax(CString strValue,float nMax,float nMin,int nAfterPoint);
void CheckForPresence(CExBaseList *pParas,CString strID);
void CheckRxValue(CString &strR,CString &strX,CString strZSetting,CString strZAng);
void CheckZSettingAndZAng(CString strR,CString strX,CString &strZSetting,CString &strZAng);
#endif // DIFFCOMMONPARASDLG_H
