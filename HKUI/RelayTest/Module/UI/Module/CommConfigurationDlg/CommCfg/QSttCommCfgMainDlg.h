#ifndef QSttCommCfgMainDlg_H
#define QSttCommCfgMainDlg_H

#include <QDialog>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QPushButton>
#include <QComboBox>
#include <QLabel>
#include <QStringList>
#include <QGridLayout>
#include <QTimerEvent>
#include <QLineEdit>
#include "SttCommCfgDeviceAttrsGrid.h"
#include "../../../../../../Module/DataMngr/DvmData.h"
#include "../../../../../../Module/DataMngr/DvmDevice.h"
#include "../../ScrollCtrl/ScrollComboBox.h"
#include "../../../../SmartTestInterface/QT/PpSttIotEngineClientWidgetMain.h"

#define CFMDLG_COMBO_TYPE_PPXMLFILE 1
#define CFMDLG_COMBO_TYPE_DVMFILE 2

class QSttCommCfgMainDlg: public QDialog ,public CPpSttIotEngineClientInterface
{
	Q_OBJECT
public:
	QSttCommCfgMainDlg(QWidget *parent = 0);
	virtual ~QSttCommCfgMainDlg();
	void initUI();                 //初始化UI
	void SetDialogFont();          //设置通讯配置Dialog字体
	void InitDatas();              //初始化数据
	void SetComboItemIndex(int iComboType);          //设置通讯配置DialogCombo选中项
	void UpdateConnectStateUI(long nHasConnected);   //更新连接按钮文本
	QStringList* ScanDataDir(CString strScanPath, CString fileSuffix); //扫描文件路径获取点表-规约文件
	void OpenPpSttCommConfigFile(int iModType, CString& upStrPpXmlFile, CString& upStrDvmFile); //打开配置文件
	void SavePpSttCommConfigFile(int iModType, CString& upStrPpXmlFile, CString& upStrDvmFile); //保存配置文件
	void ParseProtolTmplXmlFile(CString upStrPpXmlFile);  //解析规约文件Xml内容
	void SaveSerialTableProtolFile(CString strPpXmlFile); //保存规约文件串口内容
	void SaveNetTableProtolFile(CString strPpXmlFile);    //保存规约文件网口内容
	void SaveTcpclientDataToCfgXml();                     //保存规约文件网口的TcpClient数据
	// 点击确定/连接 将所有内容保存 2014-01-31 yuanting
	bool SaveAll();

	CDvmData *m_pPpxmlFileData;                      //xml配置文件
	CString m_strProproTemplatePath;                 //规约文件全路径
	QLabel *m_pLabelProtolType;                      //规约Label
	QLabel *m_pLabelPointXmlType;                    //点表Label
	QScrollComboBox *m_pProproTemplate_ComboBox;     //规约模板选择框
	QScrollComboBox *m_pPointFile_ComboBox;          //点表文件选择框
	QPushButton *m_pConnect_PushButton;              //连接按钮
	QPushButton *m_pOK_PushButton;                   //确定按钮
	QPushButton *m_pCancel_PushButton;               //取消按钮

	SttCCommCfgDeviceAttrsGrid *m_pCommCfgDevcieAttrsGrid;   //装置配置对话框表格

	CDvmDevice *m_pDevAddrDvmDevice;            //装置地址解析文件
	CString m_strDevAddrPintPath;               //首地址对应的点表路径
	BOOL m_bNetTableSave;						//网口类型表格保存标志
	BOOL m_bSerialTableSave;					 //串口类型表格保存标志
	long m_nConnectStateIndex;//该标记用于联机使用,在创建设备连接时,返回的结果里有连接状态,第一次连接状态标记设备创建成功,实际连接状态需要几s后返回
	//2014-01-31 yuanting  判断是否需要保存 连接的时候
	bool m_bIsSaveFlag;


	virtual void OnCommCommandMsg(WPARAM wParam,LPARAM lParam);   //通讯回调Command函数
	virtual void OnEngineSystemMessage(WPARAM wParam, LPARAM lParam); //通讯回调Engine函数
public slots:
	void slot_ProtolTempateComboChanged(int index);   //规约模板Combo切换槽函数
	void slot_PointFileComboChanged(int index);      //点表文件Combo切换槽函数
	void slot_ConnectClicked();   //连接按钮槽函数
	void slot_OKClicked();        //确定按钮槽函数
	void slot_CancelClicked();     //取消按钮槽函数
	void slot_ChangedDevAddr(long lRes);   //首地址修改的槽函数
	void slot_ChangedNetTable();          //网络类型表格的槽函数
	void slot_ChangedSerialTable();       //串口类型表格的槽函数
};

CString  Global_GetProtolTemplPath();       //获取规约模板文件全路径
CString Global_GetPointTbFilePath();	    //获取点表文件全路径
void Global_SetLinuxDevIP(CString strIP, CString strMask);  //设置linux IP
CDvmData* Global_OpenPpxmlFile(CString srFilePath);         //解析规约文件xml

#endif // QSttCommCfgMainDlg_H
