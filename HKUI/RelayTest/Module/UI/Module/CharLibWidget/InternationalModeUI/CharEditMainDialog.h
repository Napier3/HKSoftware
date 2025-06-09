#ifndef CharEditMainDialog_H
#define CharEditMainDialog_H

#include <QDialog>
#include <QItemDelegate>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include "../../../../../../Module/OSInterface/OSInterface.h"
#include "../QImpCharactWidget.h"
#include "../CharEditWidgetBase.h"
#include "../../../../XLangResource_Win.h"
#include "CharactEditWidget_Eng.h"


class QCharEditMainDialog : public QDialog
{
	Q_OBJECT
public:
	QCharEditMainDialog(QWidget* pParent = NULL);
	virtual ~QCharEditMainDialog();

public:
	QVBoxLayout *m_pCharEditMain_VBoxLayout;
	QGridLayout *m_pCharEdit_GridLayout;
	QHBoxLayout *m_pCharEditBottom_HLayout;
	QPushButton *m_pOk_Button;
	QPushButton *m_pCancel_Button;
	QPushButton *m_pImportChar_Button;//add wangtao 20241008 差动曲线编辑导入曲线按钮

	BOOL m_bSetting;

//	QStringList m_PeriodList;
//	QStringList m_ErrorPhaseList;
//	QList<QComboBox*> m_CmbListParaNo;
//	QList<QComboBox*> m_CmbListFaultPha;

	QCharactEditWidget_Eng* m_pImpCharactWidget;
//	CString m_strCharParasFile;//测试功能对应的特性曲线文件的路径,用于保存

	BOOL m_bCharChanged;
	CString m_strUI_ID;//界面功能ID

public:
	void UpdateZKFeature(CCharacteristic *pObj,BOOL bSetting);
	void UpdateCharAxisType(const CString& strAxis,BOOL bLockXY);
	void UpdateCharScriptByUIParas(CDataGroup *pCurrentUIParas);

	void GroupDatasToChar(CDataGroup *pDatas);//将模板视图数据赋值给特性曲线界面
	void CharToGroupDatas(CDataGroup *pDatas);//将特性曲线界面参数数据赋值给模板视图数据

	//2022-9-3  lijunqing
	void InitCharacteristics(CCharacteristics *pCharacteristics,CDataGroup *pParaDatas,const CString &strUI_ID);//参数1为界面参数功能ID
	void ShowCharacteristics(CCharacteristics *pCharacteristics);
//	CString GetCharLibID();
	void UpdateAxisDesc(const CString &strXAxisName, const CString &strYAxisName, 
		const CString &strAxisTitle,CString strUniuX,CString strUnitY);//更新坐标轴描述
	BOOL IsViewTestLines();
	void UI_SetActiveElement(CXDrawElement *pElement);
	CCharacteristics *GetCharacteristics_Inner();

protected:
	void CreateCharEditWidgetUI_ID();

//	CCharacteristicLib m_oCharEditCharacteristicsLib;
	QCharEditWidgetBase *m_pCharEditWidget;
	CCharacteristics *m_pCharacteristics_Inner;
	CCharacteristics *m_pCharacteristics_Exter;//外部传入的特性曲线指针,在点击确定后,将内部编辑好的曲线更新到外部

private:
//	void InitUI();
	void InitTableWidget();
	void InitCharactWidget();
	void InitConnect();

	void AddCharacter(CCharacteristic *pChar);
	CXDrawList* GetDrawListByID(const CString& strID);
	void RemoveCurrWidget();

signals:

public slots:
	void slot_UpdateDrawCharacters(CExBaseObject *pCharacteristic,int bCharChanged);//调用该槽函数可设置参数是否改变
	void slot_UpdateDrawCharacters(CExBaseObject *pCharacteristic);//调用该槽函数,默认参数已改变
	void slot_LeftButtonDown();
	void slot_OKClicked();
	void slot_CancelClicked();
	void slot_ImportCharClicked();//add wangtao 20241008 差动曲线编辑导入曲线按钮槽函数
};

#endif//!CharEditMainDialog_H