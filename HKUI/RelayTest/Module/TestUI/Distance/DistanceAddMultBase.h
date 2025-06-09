#ifndef QDISTANCEADDMULTBASE_H
#define QDISTANCEADDMULTBASE_H

#include <QDialog>
#include "../../../Module/DataMngr/DvmData.h"
#include "../../../Module/DataMngr/DataGroup.h"

#include "../../UI/SttTestCntrFrameApi.h"
#include "../Distance/DistanceResultEstimateDlg.h"
#include "../Distance/SttMultiMacroDistanceParasDefine.h"


#define TIPS_DISPLAY_TIME	3000
#define ADDMULT_PAGESHOWITEM_HEIGHT 22

class QDistanceAddMultBase : public QDialog
{
    Q_OBJECT
public:
    explicit QDistanceAddMultBase(QWidget *parent = 0);
    virtual ~QDistanceAddMultBase();
protected:
	CDataGroup* m_pDistanceparas;
	CDataGroup* m_pInitParas;//界面显示最初参数 点击取消后使用
	int m_nTipsTime;//页面提示计时ID
	CDataType *m_pDataTypeLL;//LL类型对应区段
	CDataType *m_pDataTypeLN;//LN类型对应区段

	virtual void CheckAllPresence();
	void CheckForPresence(CString strID);
	virtual void MinCheckLeastOne();//获取数据后检查界面相关显示

	virtual void SetValueToPage(CDvmData *pData);
	virtual void GetPageToValue(CDvmData *pData);
	virtual void InitUI();
	virtual void UpdateCharacteristicParas();//设置特性曲线相关数据到参数链表
	virtual void UpdateAddMultPageShow(int nZone,bool bLN);//根据曲线区段(参数1) 是否为LN类型(参数2) 更新界面显示
	virtual void InitPageShowByParas();//设置特性曲线相关数据后更新界面下拉框显示数据

	CString CheckDataMinMax(CString strValue,CString strID,float nMax,float nMin,int nAfterPoint);
	CString CheckDataMinMax(CString strValue,float nMax,float nMin,int nAfterPoint);

	CString GetZsetByZAng(CString strZAng, int nZone, CString strFault);//根据阻抗角 区段 曲线故障类型获取焦点对应阻抗定值20241010 luozibing
	void UpdateErrorLogicValue(int nindex, int nZoneValue);//根据cmb选中Index[参数1]与区段值[参数2] 设置误差类型20241024 luozibing
	CString GetZAngIDByZoneValue(int nZone,CString strFault);//根据区段值[参数1]与故障类型[参数2]获取角阻抗对应id
public:
	void GetDatas(CDataGroup *pParas);
	void SetDatas(CDataGroup *pParas);
};

extern CFont *g_pSttGlobalFont;
extern bool Stt_Global_IsSetting(QObject *pObject);		//20240805 huangliang 

#endif // QDISTANCEADDMULTBASE_H
