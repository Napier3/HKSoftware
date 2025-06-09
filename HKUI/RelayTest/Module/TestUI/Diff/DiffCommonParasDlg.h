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
	void AutoCalcKpx();//计算平衡系数
	bool isinf(double x) {  
		return x == std::numeric_limits<double>::infinity() || x == -std::numeric_limits<double>::infinity();  
	}//2024.10.17 zhangyq

private slots:

	void on_m_txtPrepareTime_editingFinished();       //准备时间(s)
	void on_m_txtPreFaultTime_editingFinished();		//故障前时间(s)
	void on_m_txtFaultTime_editingFinished();		//故障时间裕度(s)
	void on_m_txtTimeAfter_editingFinished();         //动作后持续时间(s)
	void on_m_cmbKPSetMode_currentIndexChanged(int index);						//各侧平衡系数
	void slot_m_txtSn_editingFinished();				//变压器额定容量(MVA)					
	void slot_m_txtHUn_editingFinished();				//高压侧额定电压(kV)					
	void slot_m_txtMUn_editingFinished();				//中压侧额定电压(kV)				
	void slot_m_txtLUn_editingFinished();				//低压侧额定电压(kV)					
	void slot_m_txtCTPh_editingFinished();				//高压侧CT一次值(A)					
	void slot_m_txtCTPm_editingFinished();				//中压侧CT一次值(A)					
	void slot_m_txtCTPl_editingFinished();				//低压侧CT一次值(A) 					
	void slot_m_txtCTSh_editingFinished();				//高压侧CT二次值(A)					
	void slot_m_txtCTSm_editingFinished();				//中压侧CT二次值(A)				
	void slot_m_txtCTSl_editingFinished();				//低压侧CT二次值(A)				
	void on_m_txtKphSet_editingFinished();			//高压侧差动平衡系数
	void on_m_txtKpmSet_editingFinished();			//中压侧差动平衡系数				
	void on_m_txtKplSet_editingFinished();			//低压侧差动平衡系数				
	void slot_m_cmbWindH_currentIndexChanged(int index);				//高压侧绕组接线型式					
	void slot_m_cmbWindM_currentIndexChanged(int index);				//中压侧绕组接线型式						
	void slot_m_cmbWindL_currentIndexChanged(int index);				//低压侧绕组接线型式
	void slot_m_cmbPhCorrectMode_currentIndexChanged(int index);		//校正选择				
	void slot_m_cmbAdoptWind_currentIndexChanged(int index);			//测试绕组	
	void on_m_cmbTransGroupMode1_currentIndexChanged(int index);	//高-中绕组钟点数		
	void on_m_cmbTransGroupMode2_currentIndexChanged(int index);	//高-低绕组钟点数				
	void slot_m_cmbJXFactor_currentIndexChanged(int index);			//平衡系数计算			
	void on_m_cmbSearchMode_currentIndexChanged(int index);		//搜索方法				
	void on_m_cmbCTPoint_currentIndexChanged(int index);			//CT极性			
	void on_m_cmbIrEquation_currentIndexChanged(int index);		//制动方程					
	void on_m_txtK_editingFinished();	//K1				
	void on_m_txtK2_editingFinished();	//K2					
	void on_m_cmbEarthing_currentIndexChanged(int index);			//接地					
	void on_m_txtStep_editingFinished();				//测试精度				
	void on_m_txtVg1_editingFinished();				//Ua、Ub、Uc(V)			
	void on_m_txtVg2_editingFinished();				//Ua2、Ub2、Uc2(V)

	void on_m_btnOK_clicked();
	void on_m_btnCancel_clicked();
private:
    Ui::QDiffCommonParasDlg *ui;
	CExBaseList *m_pParas;
	CSttDiffCurrCalculatTool m_oDiffCalTool;
	CSttMacroTest m_oSttMacroTest_Inner;
	
	int m_nModify;
	float m_fKph;//高压侧差动平衡系数
	float m_fKpm;//中压侧差动平衡系数
	float m_fKpl;//低压侧差动平衡系数
	int		m_nInSel;	//基准电流选择 0-高侧二次额定电流 1-设定值 2-各侧二次额定电流 平台模板没有，恒为0 用以计算INOM
	float	m_fIbase;	//基准电流设定值
	BOOL	m_bMinAxis;	//定制整定方式 0-有名值 1-标幺值 平台模板没有，恒为1
	int		m_nConnectMode;	//测试绕组之间角差（钟点数）0-11 12点、1点--11点  11 即平台的变压器接线组别
	int		m_nPhase;		//故障相别	

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
