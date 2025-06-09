#pragma once

#include "../../../Module/DataMngr/DvmDevice.h"
#include "SttCmdWzd_CmdDataset.h"
#include "GbWzdXItemBase.h"

class CGbMacroGenWzd : public CGbWzdXItemBase
{
public:
	CGbMacroGenWzd(void);
	virtual ~CGbMacroGenWzd(void);

public:
	virtual UINT GetClassID() {    return DVMCLASSID_GBMACROGENWZD;   }
	virtual BSTR GetXmlElementKey()  {      return CGbSmartGenWzdXmlRWKeys::CGbMacroGenWzdKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

	//2022-10-4  lijunqing ��ҳ�棬��Ҫ�����ϴε�ѡ���������Ч��
	//�����Ӵ˶������ڼ�¼�ͱ���Ĭ�ϵĶ���
	CString GetInitXmlFile();
	void OpenInitXmlFile();
	void SaveInitXmlFile();
	void InitGbMacroGenWzd(CGbMacroGenWzd *pSrc);

public:
	CSttCmdWzd_Step* GetFirstStep();
	void OnAtsGenerateItems_CmdWzd(CExBaseList *pCmdGrp);
	CSttCmdWzd_Step* GetRelatedStep(CSttCmdWzd_Step *pStep);   //����ͨѶǰ���裬���Ҷ�Ӧ��ͨѶ����

	void InitCmdWzdRef(CDataGroup *pRoot);
	void InitCmdWzdRefEx(CDataGroup *pA_Bft);
	BOOL IsLastSetp();  //�Ƿ������һ��
	BOOL IsFirstSetp(CSttCmdWzd_Step *pStep);  //�Ƿ��ǵ�һ��
	BOOL IsFirstSetp();  //�Ƿ��ǵ�һ��
	BOOL HasStepNeedShow();  //�Ƿ���Ҫ�û������Ĳ��裺���磺�Ķ�ֵ����ѹ�塢д���

	CSttCmdWzd_Step* GetNextStep();
	CSttCmdWzd_Step* GetPreStep();
	CSttCmdWzd_Step*CurrStep()	{	return m_pCurrSetpWzd;	}
	
	//�����β�bAdd_AFT�����ڱ���Ƿ���Ӳ��Ժ�ָ�������������ʱ����ѡ�ˡ����װ�ø���̬����������Ӳ��Ժ�ָ���������ӡ�����̬��
	void NextClick_Init(CDataGroup &oCommCmd, BOOL bAdd_AFT); 
	void NextClick_Finish(CDataGroup &oCommCmd);
	void InitGenerateItemsParas(CSttCmdWzd_Step *pCmdDatasets, CDataGroup *pA_Bft);

public:
	CDataGroup *m_pCmdGenParas;  //OnAtsGenerateItems_CmdWzd���صĲ�����root����
	CDataGroup *m_pCmdCfg;	   //ͨѶǰ��ͨѶ������
	CDataGroup *m_pMacroUIParas;   //���ɵ���Ŀ������أ�TestClass��ItemsName��  STT_CMD_PARA_MacroUIParas
	CDataGroup *m_pMacroUIAttrs;    //STT_CMD_PARA_TestMacroUI
	CDvmContents *m_pCharacteristic;

	CString m_strTestClass;
	CString m_strTestMacroUI;
	long m_nRepeatTimes;
	//shaolei 2023-6-21  �Ƿ���Ϊ���⡢����ȼ�
	long m_nRptTitle;
	long m_nTitleLevel;

	//����cmd-wzdָ���Ӧ������������򵼲��裬���������һ��
	CDataGroup m_oListCmdWzdStep;

	//ͨѶ�����򵼵ĵ�ǰ���裬ָ��һ��read��write��rigster�����ʼֵӦ��ΪROOT�ڵ�
	CSttCmdWzd_Step *m_pCurrSetpWzd;  

public:
	void InitCommCmdCfg();

	CDataGroup* GetCmdGenParas();
	CDataGroup* GetCmdCfg();
	CDataGroup* GetMacroUIParas();
	CDataGroup* GetMacroUIAttrs();
	CDvmContents* GetCharacteristic();

	//CDvmData* GetCmdCfgData(const CString &strCmdID);
	void AddDataToWzdCmd(const CString &strItemsID, const CString &strCommCmdID, const CString &strDatasetPath, CDvmData *pData);
	void AddDataToWzdCmd(const CString &strItemsID, const CString &strCommCmdID, const CString &strDatasetPath, CValue *pValue);
	void DeleteDataFromWzdCmd(const CString &strItemsID, const CString &strCommCmdID, const CString &strDatasetPath, const CString &strDataID);
	void UpdateDataToWzdCmdCfg(const CString &strItemsID, const CString &strCommCmdID, const CString &strDatasetPath, CDvmData *pDvmData);
	void DeleteAllDatasToWzdCmdCfg(const CString &strItemsID, const CString &strCommCmdID, const CString &strDatasetPath);
	void UpdateZoneIndexToWzdCmdCfg(const CString &strItemsID, const CString &strCommCmdID, const CString &strDatasetPath, int nZoneIndex);
	void UpdateDelayBftToWzdCmdCfg(const CString &strItemsID, const CString &strCommCmdID, const CString &strDatasetPath, const CString &strDelay);
	void UpdateDelayAftToWzdCmdCfg(const CString &strItemsID, const CString &strCommCmdID, const CString &strDatasetPath, const CString &strDelay);
	CDataGroup* FindGroup_Item(CDataGroup *pItemsGroup, const CString &strCommCmdID, const CString &strDatasetPath);
	CDataGroup* FindGroup_Dataset(const CString &strItemsID, const CString &strCommCmdID, const CString &strDatasetPath);
	CDvmData* FindData(const CString strDataID, const CString &strItemsID, const CString &strCommCmdID, const CString &strDatasetPath);
	CDvmData* FindData_ZoneIndex(const CString &strItemsID, const CString &strCommCmdID, const CString &strDatasetPath);
	CDvmData* FindData_DelayBftCmd(const CString &strItemsID, const CString &strCommCmdID, const CString &strDatasetPath);
	CDvmData* FindData_DelayAftCmd(const CString &strItemsID, const CString &strCommCmdID, const CString &strDatasetPath);

	void ClearEmptyCmdParas(const CString &strItemsID, const CString &strCommCmdID, const CString &strDatasetPath);
	void ClearAllCmdGenParas();  //���ͨѶ�������ò���
};

CGbMacroGenWzd* gb_wzd_curr_macro_gen();
