//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//XLanguageResourceBase.h  CXLanguageResourceBase

#pragma once

#include "XLanguageGlobal.h"
#include "XLanguage.h"


class CXLanguageResourceBase : public CXLanguage
{
public:
	CXLanguageResourceBase();
	virtual ~CXLanguageResourceBase();
	
	void InitLangFileForDebug(const CString &strModule);

private:
	CXLanguage m_oXLangRsBase;

protected:
	CXLanguage *m_pXLangRsExe;

public:
	CXLangItem* rs_AddString(const CString &strID, CString *pstrString);
	CXLangItem* rs_AddString2(const CString &strID, const CString &strString);

	virtual void InitLangRsByFile();
	virtual void InitLangRsByFileEx(CXLanguage *pXLangRef, const CString &strFile);
	virtual void SaveXLangRsFile();

	virtual void RegisterLanguageResource();
	void LanguageChange(CString strFile,CXLanguage *pXLangRef);//20250122 suyang ���������滻�����������û�е�

	//2023-2-28  lijunqing LINUX QT�£�����ģʽ�����⣬��û���ñ���ģʽ��ʱ��ȫ�־�̬�����������룬�������Ӵ˺���
	virtual void InitLangTxt();

};

	extern  CString  g_strXLangRsBaseFile;
	extern  CString g_sLangID_Chinese;
	extern  CString g_sLangID_English;

	extern  CString g_sLangID_File;
	extern  CString g_sLangTxt_File;
	extern  CString g_sLangID_FileNew;
	extern  CString g_sLangTxt_FileNew;
	extern  CString g_sLangID_FileNewTip;
	extern  CString g_sLangTxt_FileNewTip;
	extern  CString g_sLangID_FileOpen;
	extern  CString g_sLangTxt_FileOpen;
	extern  CString g_sLangID_Save;
	extern  CString g_sLangTxt_Save;
	extern  CString g_sLangID_SaveTip;
	extern  CString g_sLangTxt_SaveTip;
	extern  CString g_sLangID_SaveAs;
	extern  CString g_sLangTxt_SaveAs;
	extern  CString g_sLangID_SaveAsTip;
	extern  CString g_sLangTxt_SaveAsTip;
	extern  CString g_sLangID_Print;
	extern  CString g_sLangTxt_Print;
	extern  CString g_sLangID_FileClose;
	extern  CString g_sLangTxt_FileClose;
	extern  CString g_sLangID_Clipboard;
	extern  CString g_sLangTxt_Clipboard;
	extern  CString g_sLangID_Copy;
	extern  CString g_sLangTxt_Copy;
	extern  CString g_sLangID_View;
	extern  CString g_sLangTxt_View;
	extern  CString g_sLangID_SelAll;
	extern  CString g_sLangTxt_SelAll;
	extern  CString g_sLangID_PasteData;
	extern  CString g_sLangTxt_PasteData;
	extern  CString g_sLangID_Paste;
	extern  CString g_sLangTxt_Paste;
	extern  CString g_sLangID_PasteTip;
	extern  CString g_sLangTxt_PasteTip;
	extern  CString g_sLangID_Cut;
	extern  CString g_sLangTxt_Cut;
	extern  CString g_sLangID_Delete;
	extern  CString g_sLangTxt_Delete;
	extern  CString g_sLangID_OK;
	extern  CString g_sLangTxt_OK;
	extern  CString g_sLangID_Cancel;
	extern  CString g_sLangTxt_Cancel;
	extern  CString g_sLangID_AppExit;
	extern  CString g_sLangTxt_AppExit;
	extern  CString g_sLangID_AppExitTip;
	extern  CString g_sLangTxt_AppExitTip;
	extern  CString g_sLangID_Help;
	extern  CString g_sLangTxt_Help;
	extern  CString g_sLangID_HelpAbout;
	extern  CString g_sLangTxt_HelpAbout;
	extern  CString g_sLangID_Back;
	extern  CString g_sLangTxt_Back;
	//
	extern  CString g_sLangID_Name;
	extern  CString g_sLangTxt_Name;
	extern  CString g_sLangID_Index;
	extern  CString g_sLangTxt_Index;
	extern  CString g_sLangID_Type;
	extern  CString g_sLangTxt_Type;
	extern  CString g_sLangID_History;
	extern  CString g_sLangTxt_History;
	extern  CString g_sLangID_Open;
	extern  CString g_sLangTxt_Open;
	extern  CString g_sLangID_Location;
	extern  CString g_sLangTxt_Location;
	extern  CString g_sLangID_Path;
	extern  CString g_sLangTxt_Path;
	extern  CString g_sLangID_ModifiedTime;//�޸�ʱ��
	extern  CString g_sLangTxt_ModifiedTime;
	extern  CString g_sLangID_Size;        //��С��KB��
	extern  CString g_sLangTxt_Size;

	extern  CString g_sLangID_Folder;        //�ļ���
	extern  CString g_sLangTxt_Folder;
	extern  CString g_sLangID_SureDeleItem;        //ȷ��Ҫɾ���� %d ����Ŀ��?
	extern  CString g_sLangTxt_SureDeleItem;
	extern  CString g_sLangID_SureDelete;        //ɾ��ȷ��
	extern  CString g_sLangTxt_SureDelete;
	extern  CString g_sLangID_SureAgain;        //ɾ�����޷��ָ������ٴ�ȷ��
	extern  CString g_sLangTxt_SureAgain;
	extern  CString g_sLangID_DeleteFail;        //�ļ����ڱ�ʹ�ã�ɾ��ʧ��
	extern  CString g_sLangTxt_DeleteFail;
	extern  CString g_sLangID_FileDeleteFail;        //ɾ���ļ�ʧ��
	extern  CString g_sLangTxt_FileDeleteFail;
	extern  CString g_sLangID_DeleteFailFold;        //�ļ����а������ڱ�ʹ�õ��ļ���ɾ��ʧ��
	extern  CString g_sLangTxt_DeleteFailFold;
	extern  CString g_sLangID_FolderDeleteFail;        //ɾ���ļ���ʧ��
	extern  CString g_sLangTxt_FolderDeleteFail;
	extern  CString g_sLangID_FoldAlrOpen;        //���ļ������ѱ��򿪵��ļ�
	extern  CString g_sLangTxt_FoldAlrOpen;
	extern  CString g_sLangID_ModifiedFail;        //�޸��ļ�������ʧ��
	extern  CString g_sLangTxt_ModifiedFail;
	extern  CString g_sLangID_FileOpened;        //���ļ��ѱ���
	extern  CString g_sLangTxt_FileOpened;

	extern  CString g_sLangID_SerNumber;    //���
	extern  CString g_sLangTxt_SerNumber;
	extern  CString g_sLangID_MinTime;    //��С����
	extern  CString g_sLangTxt_MinTime;
	extern  CString g_sLangID_MaxTime;    //������
	extern  CString g_sLangTxt_MaxTime;

	extern  CString g_sLangID_Filter;     //����
	extern  CString g_sLangTxt_Filter;
	extern  CString g_sLangID_CinKeyDb;   //�ϲ��ļ�
	extern  CString g_sLangTxt_CinKeyDb;
	extern  CString g_sLangID_BaseKeyNew;
	extern  CString g_sLangTxt_BaseKeyNew;
	extern  CString g_sLangID_MultiKeyNew;
	extern  CString g_sLangTxt_MultiKeyNew;
	extern  CString g_sLangID_DeleteKey;
	extern  CString g_sLangTxt_DeleteKey;
	extern  CString g_sLangID_SelectSameKey;
	extern  CString g_sLangTxt_SelectSameKey;
	extern  CString g_sLangID_AnalyzeKey;
	extern  CString g_sLangTxt_AnalyzeKey;
	extern  CString g_sLangID_AnalyzeKeyUnsu;       //�ؼ���ƥ�䲻�ɹ�
	extern  CString g_sLangTxt_AnalyzeKeyUnsu;
	extern  CString g_sLangID_AnalyzeKeySu;
	extern  CString g_sLangTxt_AnalyzeKeySu;        //�ؼ���ƥ��ɹ�
	extern  CString g_sLangID_DeleteKeyObj;         //ѡ��ɾ������
	extern  CString g_sLangTxt_DeleteKeyObj;

	extern  CString g_sLangID_Data;//����
	extern  CString g_sLangTxt_Data;
	extern  CString g_sLangID_OperIns;//��ҵָ����
	extern  CString g_sLangTxt_OperIns;
	extern  CString g_sLangID_PromptMessage;//��ʾ��Ϣ
	extern  CString g_sLangTxt_PromptMessage;
	extern  CString g_sLangID_PleaseChoose;//���� %s ��ѡ��%s
	extern  CString g_sLangTxt_PleaseChoose;
	extern  CString g_sLangID_FileAlrExi;//�ļ� %s �Ѿ�����
	extern  CString g_sLangTxt_FileAlrExi;
	extern  CString g_sLangID_StandardFileName;//��׼�ļ���
	extern  CString g_sLangTxt_StandardFileName;
	extern  CString g_sLangID_ManagSave;//%s ����---����
	extern  CString g_sLangTxt_ManagSave;
	extern  CString g_sLangID_ManagOpen;//%s ����---��
	extern  CString g_sLangTxt_ManagOpen;
	extern  CString g_sLangID_FileExYN;//%s �ļ��Ѿ����ڣ��Ƿ񸲸�?
	extern  CString g_sLangTxt_FileExYN;
	extern  CString g_sLangID_FileDupliName;//�ļ�����
	extern  CString g_sLangTxt_FileDupliName;
	extern  CString g_sLangID_AlrOpenFail;//%s �Ѿ����򿪣��ļ�����ʧ��
	extern  CString g_sLangTxt_AlrOpenFail;
	extern  CString g_sLangID_FileCoverFail;//�ļ�����ʧ��
	extern  CString g_sLangTxt_FileCoverFail;

	extern  CString g_sLangID_AddDirectory;//���Ŀ¼
	extern  CString g_sLangTxt_AddDirectory;
	extern  CString g_sLangID_ImportDirectory;//����Ŀ¼
	extern  CString g_sLangTxt_ImportDirectory;
	extern  CString g_sLangID_ExportDirectory;//����Ŀ¼
	extern  CString g_sLangTxt_ExportDirectory;
	extern  CString g_sLangID_CopyFile;//�����ļ�
	extern  CString g_sLangTxt_CopyFile;
	extern  CString g_sLangID_PasteFile;//ճ���ļ�
	extern  CString g_sLangTxt_PasteFile;
	extern  CString g_sLangID_DeleteFile;//ɾ���ļ�
	extern  CString g_sLangTxt_DeleteFile;
	extern  CString g_sLangID_FileRename;//�޸��ļ�����
	extern  CString g_sLangTxt_FileRename;
	extern  CString g_sLangID_ImportFile;//�����ļ�
	extern  CString g_sLangTxt_ImportFile;
	extern  CString g_sLangID_ExportFile;//�����ļ�
	extern  CString g_sLangTxt_ExportFile;
	extern  CString g_sLangID_DeleteDirectory;//ɾ��Ŀ¼
	extern  CString g_sLangTxt_DeleteDirectory;
	extern  CString g_sLangID_DirectoryRename;//�޸�Ŀ¼����
	extern  CString g_sLangTxt_DirectoryRename;
	extern  CString g_sLangID_FileCover;//�����ļ�
	extern  CString g_sLangTxt_FileCover;
	extern  CString g_sLangID_ExiSaNameFileCov;//����ͬ���Ƶ��ļ���%s��,������
	extern  CString g_sLangTxt_ExiSaNameFileCov;
	extern  CString g_sLangID_ExiFileOvwt;//�ļ���%s���Ѿ�����,������
	extern  CString g_sLangTxt_ExiFileOvwt;
	extern  CString g_sLangID_Message;//��ʾ
	extern  CString g_sLangTxt_Message;
	extern  CString g_sLangID_SureDeleFile;//��ȷʵҪɾ���ļ���%s����
	extern  CString g_sLangTxt_SureDeleFile;
	extern  CString g_sLangID_ExiSaNameFile;//����ͬ���Ƶ��ļ��С�%s��
	extern  CString g_sLangTxt_ExiSaNameFile;
	extern  CString g_sLangID_ExiSmNmFile3;//����ͬ���Ƶ��ļ���%s��
	extern  CString g_sLangTxt_ExiSmNmFile3;
	extern  CString g_sLangID_ExiSmNmFile2;//�ļ��С�%s������ͬ���Ƶ��ļ���%s��
	extern  CString g_sLangTxt_ExiSmNmFile2;
	extern  CString g_sLangID_ChoImpFile;//ѡ����������ļ���
	extern  CString g_sLangTxt_ChoImpFile;
	extern  CString g_sLangID_ExpFileFin;//����Ŀ���ļ��С�%s�����
	extern  CString g_sLangTxt_ExpFileFin;
	extern  CString g_sLangID_TargFolderExist;//Ŀ���ļ��С�%s���Ѿ�����
	extern  CString g_sLangTxt_TargFolderExist;
	extern  CString g_sLangID_ChoFoldExDir;//ѡ�������ļ��е���Ŀ��Ŀ¼
	extern  CString g_sLangTxt_ChoFoldExDir;
	extern  CString g_sLangID_SureDeleFold;//ȷʵҪɾ���ļ��С�%s����
	extern  CString g_sLangTxt_SureDeleFold;
	extern  CString g_sLangID_DeleFold;//ɾ���ļ��н�ɾ�����ļ��м����µ�ȫ���ļ����ļ��С�\r\nȷʵҪɾ���ļ��С�%s����
	extern  CString g_sLangTxt_DeleFold;
	extern  CString g_sLangID_FoldCoverFold;//�ļ��С�%s���������ļ��л����ļ�\r\n����ɾ�����ļ��л����ļ���Ȼ����ɾ��Ŀ¼
	extern  CString g_sLangTxt_FoldCoverFold;
	extern  CString g_sLangID_ConfigFileManag;//�����ļ�����
	extern  CString g_sLangTxt_ConfigFileManag;

	extern  CString g_sLangID_AtsPubFileManag;
	extern  CString g_sLangTxt_AtsPubFileManag;
	extern  CString g_sLangID_AddPubFile;
	extern  CString g_sLangTxt_AddPubFile;
	extern  CString g_sLangID_ModifyPubFile;
	extern  CString g_sLangTxt_ModifyPubFile;
	extern  CString g_sLangID_DeletePubFile;
	extern  CString g_sLangTxt_DeletePubFile;

	extern  CString g_sLangID_TraProtocol;
	extern  CString g_sLangTxt_TraProtocol;
	extern  CString g_sLangID_61850Protocol;
	extern  CString g_sLangTxt_61850Protocol;
	extern  CString g_sLangID_None;
	extern  CString g_sLangTxt_None;


	//���ϡ�ͨ�á��������
	extern  CString g_sLangID_FaultParameter;
	extern  CString g_sLangTxt_FaultParameter;
	extern  CString g_sLangID_GeneralParameter;
	extern  CString g_sLangTxt_GeneralParameter;
	extern  CString g_sLangID_ResultParameter;
	extern  CString g_sLangTxt_ResultParameter;
	extern  CString g_sLangID_AppBaseParameter;
	extern  CString g_sLangTxt_AppBaseParameter;

	extern  CString g_sLangID_ArbitrElement;//����Ԫ��
	extern  CString g_sLangTxt_ArbitrElement;
	extern  CString g_sLangID_SpecifiedElement;//ָ����Ԫ��
	extern  CString g_sLangTxt_SpecifiedElement;
	extern  CString g_sLangID_SequDefinElemIn;//���ж����е�Ԫ��
	extern  CString g_sLangTxt_SequDefinElemIn;
	extern  CString g_sLangID_SequDefinElemOut;//���ж���֮���Ԫ��
	extern  CString g_sLangTxt_SequDefinElemOut;
	extern  CString g_sLangID_ReferElements;//����Ԫ��
	extern  CString g_sLangTxt_ReferElements;
	extern  CString g_sLangID_Values;//ֵ
	extern  CString g_sLangTxt_Values;
	extern  CString g_sLangID_Time;//ʱ��
	extern  CString g_sLangTxt_Time;
	extern  CString g_sLangID_Integer;//����
	extern  CString g_sLangTxt_Integer;
	extern  CString g_sLangID_FloatNumber;//������
	extern  CString g_sLangTxt_FloatNumber;
	extern  CString g_sLangID_CharacterString;//�ַ���
	extern  CString g_sLangTxt_CharacterString;
	extern  CString g_sLangID_Equal;//����
	extern  CString g_sLangTxt_Equal;
	extern  CString g_sLangID_LessThan;//С��
	extern  CString g_sLangTxt_LessThan;
	extern  CString g_sLangID_LessOrEqual;//С�ڵ���
	extern  CString g_sLangTxt_LessOrEqual;
	extern  CString g_sLangID_MoreThan;//����
	extern  CString g_sLangTxt_MoreThan;
	extern  CString g_sLangID_MoreOrEqual;//���ڵ���
	extern  CString g_sLangTxt_MoreOrEqual;
	extern  CString g_sLangID_NotEqual;//������
	extern  CString g_sLangTxt_NotEqual;
	extern  CString g_sLangID_CharStringIncl;//�ַ�������
	extern  CString g_sLangTxt_CharStringIncl;
	extern  CString g_sLangID_CharStringNIncl;//�ַ���������
	extern  CString g_sLangTxt_CharStringNIncl;
	extern  CString g_sLangID_NumberRange;//��ֵ��Χ
	extern  CString g_sLangTxt_NumberRange;
	extern  CString g_sLangID_BoundNumRange;//��ֵ��Χ���߽�
	extern  CString g_sLangTxt_BoundNumRange;
	extern  CString g_sLangID_DataVarAss;//���ݱ�����ֵ
	extern  CString g_sLangTxt_DataVarAss;
	extern  CString g_sLangID_PropertyID;//����ID
	extern  CString g_sLangTxt_PropertyID;
	extern  CString g_sLangID_DataType;//��������
	extern  CString g_sLangTxt_DataType;
	extern  CString g_sLangID_FunctionalSymbol;//��������
	extern  CString g_sLangTxt_FunctionalSymbol;
	extern  CString g_sLangID_Data2;//����2
	extern  CString g_sLangTxt_Data2;
	extern  CString g_sLangID_ResultVariable;//�������
	extern  CString g_sLangTxt_ResultVariable;
	extern  CString g_sLangID_GnrtFileNm;//��������ļ�����
	extern  CString g_sLangTxt_GnrtFileNm;
	extern  CString g_sLangID_OrgnFileNm;//ԭ�ļ�����
	extern  CString g_sLangTxt_OrgnFileNm;
	extern  CString g_sLangID_TgetFileNm;//Ŀ���ļ�����
	extern  CString g_sLangTxt_TgetFileNm;
	extern  CString g_sLangID_OverWrite;  //����      
	extern  CString g_sLangTxt_OverWrite;
	extern  CString g_sLangID_FilePasteOprt;  //�ļ�ճ������������      
	extern  CString g_sLangTxt_FilePasteOprt;
	extern  CString g_sLangID_SelFolder;  //ѡ���ļ���      
	extern  CString g_sLangTxt_SelFolder;
	extern  CString g_sLangID_FileName;  //�ļ���      
	extern  CString g_sLangTxt_FileName;
	extern  CString g_sLangID_NewFolder;  //�½��ļ���      
	extern  CString g_sLangTxt_NewFolder;
	extern  CString g_sLangID_FolderNmMdf;  //�ļ��������޸�     
	extern  CString g_sLangTxt_FolderNmMdf;
	//
	extern  CString g_sLangID_NotAuthorized;      
	extern  CString g_sLangTxt_NotAuthorized;
// 	extern  CString g_sLangID_AuthorizedUserUnit;//��Ȩ���У�%s      ��Ȩ�û���λ��%s     ��Ȩ�û�����%s      
// 	extern  CString g_sLangTxt_AuthorizedUserUnit;
	extern  CString g_sLangID_NotAuthorized2;      
	extern  CString g_sLangTxt_NotAuthorized2;
	extern  CString g_sLangID_Close; //�ر�
	extern  CString g_sLangTxt_Close;
	extern  CString g_sLangID_DataSets; //���ݼ�
	extern  CString g_sLangTxt_DataSets;
	extern  CString g_sLangID_EquipDataModel; //�豸����ģ��
	extern  CString g_sLangTxt_EquipDataModel;
	extern  CString g_sLangID_DevAtrbDefin; //�豸���Զ���
	extern  CString g_sLangTxt_DevAtrbDefin;
	extern  CString g_sLangID_LogicdevCPU; //�߼��豸(CPU)
	extern  CString g_sLangTxt_LogicdevCPU;
	extern  CString g_sLangID_LogicDevice; //�߼��豸
	extern  CString g_sLangTxt_LogicDevice;
	extern  CString g_sLangID_LogicDeviceMap; //�߼��豸MAP
	extern  CString g_sLangTxt_LogicDeviceMap;
	extern  CString g_sLangID_DataSetsMap; //���ݼ�
	extern  CString g_sLangTxt_DataSetsMap;
	extern  CString g_sLangID_ParaTypeGroup; //�������͡�%s���������һ��
	extern  CString g_sLangTxt_ParaTypeGroup;
	extern  CString g_sLangID_NoParaTypeGroup; //�����ڲ�������Ϊ��%s������
	extern  CString g_sLangTxt_NoParaTypeGroup;
	extern  CString g_sLangID_DevDataFile; //�豸����ģ���ļ�(*.xml)|*.xml||
	extern  CString g_sLangTxt_DevDataFile;
	extern  CString g_sLangID_RightsReserved; //��Ȩ���У�
	extern  CString g_sLangTxt_RightsReserved;
	extern  CString g_sLangID_LicensedTo; //��Ȩ����
	extern  CString g_sLangTxt_LicensedTo;
	extern  CString g_sLangID_DataTypeUnExist; //Row=%d  Col=%d  �������Ͷ��󲻴���
	extern  CString g_sLangTxt_DataTypeUnExist;
	extern  CString g_sLangID_Sizes; //��
	extern  CString g_sLangTxt_Sizes;
	extern  CString g_sLangID_SourceDataObject; //Դ���ݶ���
	extern  CString g_sLangTxt_SourceDataObject;
	extern  CString g_sLangID_MatchDataObject; //ƥ�����ݶ���
	extern  CString g_sLangTxt_MatchDataObject;
	extern  CString g_sLangID_SelMatchDataObject; //ѡ��ƥ������ݶ���
	extern  CString g_sLangTxt_SelMatchDataObject;
    //Sentinel LDK
	extern  CString g_sLangID_USBKey; //�������Ȩ���ܹ���
	extern  CString g_sLangTxt_USBKey;
	extern  CString g_sLangID_USBKeyUpdate; //��Ȩ���ܹ���������汾���ͣ��������������
	extern  CString g_sLangTxt_USBKeyUpdate;
	extern  CString g_sLangID_NoUSBkey; //û�а�װ��Ȩ���ܹ����������밲װ��������
	extern  CString g_sLangTxt_NoUSBkey;
	extern  CString g_sLangID_SystemError; //ϵͳ����
	extern  CString g_sLangTxt_SystemError;
	extern  CString g_sLangID_SystemError2; //ϵͳ����HASP_INV_HND��Invalid login handle passed to function
	extern  CString g_sLangTxt_SystemError2;
	extern  CString g_sLangID_SystemError3; //ϵͳ����HASP_INV_FILEID��Specified File ID not recognized by API
	extern  CString g_sLangTxt_SystemError3;
	extern  CString g_sLangID_SystemError4; //ϵͳ����HASP_MEM_RANGE��Request exceeds memory range of a Sentinel file
	extern  CString g_sLangTxt_SystemError4;
// 	extern  CString g_sLangID_RightReservedS; //��Ȩ���У�%s
// 	extern  CString g_sLangTxt_RightReservedS;
	extern  CString g_sLangID_SystemDevelop; //ϵͳ������%s
	extern  CString g_sLangTxt_SystemDevelop;
	extern  CString g_sLangID_ClientUnit; //�ͻ���λ��%s
	extern  CString g_sLangTxt_ClientUnit;
	extern  CString g_sLangID_UserName; //ʹ���û���%s
	extern  CString g_sLangTxt_UserName;
	extern  CString g_sLangID_ServerLicense; //��������Ȩ
	extern  CString g_sLangTxt_ServerLicense;
	extern  CString g_sLangID_ServerLicense2; //�ӷ�������ȡ��Ȩ��Ϣ�����Ժ�....
	extern  CString g_sLangTxt_ServerLicense2;
	extern  CString g_sLangID_LicenseCommun; //����Ȩ������ͨ�ų�ʱ����ȷ���������Ӻͷ�����������ȷ��
	extern  CString g_sLangTxt_LicenseCommun;
	//TestMacro
	extern  CString g_sLangID_TestInstSel; 
	extern  CString g_sLangTxt_TestInstSel;
	extern  CString g_sLangID_AddScriptFail; //���ع��ܽű��ļ�[%s]ʧ��
	extern  CString g_sLangTxt_AddScriptFail;
	extern  CString g_sLangID_TestFctnUnExist; //���Թ���\"%s\"������
	extern  CString g_sLangTxt_TestFctnUnExist;
	extern  CString g_sLangID_IEC61850SetFile; //IEC61850�����ļ�
	extern  CString g_sLangTxt_IEC61850SetFile;
	extern  CString g_sLangID_ComtradeFile; //ComtradeFile
	extern  CString g_sLangTxt_ComtradeFile;
	extern  CString g_sLangID_TestFctnFile; //���Թ��ܱ�׼�ļ�
	extern  CString g_sLangTxt_TestFctnFile;
	extern  CString g_sLangID_CommunStraFile; //ͨѶ��׼�ļ�
	extern  CString g_sLangTxt_CommunStraFile;
	extern  CString g_sLangID_Number2; //���/��Ŀ��
	extern  CString g_sLangTxt_Number2;
	extern  CString g_sLangID_ALreadyExist; //��%s���ڡ�%s���Ѿ�����
	extern  CString g_sLangTxt_ALreadyExist;
	extern  CString g_sLangID_MdtInsert;    //����
	extern  CString g_sLangTxt_MdtInsert;
	extern  CString g_sLangID_UpMove;    //����
	extern  CString g_sLangTxt_UpMove;
	extern  CString g_sLangID_DownMove;    //����
	extern  CString g_sLangTxt_DownMove;
	extern  CString g_sLangID_Unit;
	extern  CString g_sLangTxt_Unit;
	extern  CString g_sLangID_MinValue;//��Сֵ
	extern  CString g_sLangTxt_MinValue;
	extern  CString g_sLangID_MaxValue;//���ֵ
	extern  CString g_sLangTxt_MaxValue;
	extern  CString g_sLangID_Step;//����
	extern  CString g_sLangTxt_Step;
	extern  CString g_sLangID_Nonstandard;//�Ǳ�
	extern  CString g_sLangTxt_Nonstandard;
	extern  CString g_sLangID_StatePower;//�����Ͼ��Զ����ɷ����޹�˾
	extern  CString g_sLangTxt_StatePower;
	extern  CString g_sLangID_Aphase;//A��
	extern  CString g_sLangTxt_Aphase;
	extern  CString g_sLangID_Bphase;//B��
	extern  CString g_sLangTxt_Bphase;
	extern  CString g_sLangID_Cphase;//C��
	extern  CString g_sLangTxt_Cphase;
	extern  CString g_sLangID_ABphase;//AB��
	extern  CString g_sLangTxt_ABphase;
	extern  CString g_sLangID_BCphase;//BC��
	extern  CString g_sLangTxt_BCphase;
	extern  CString g_sLangID_CAphase;//CA��
	extern  CString g_sLangTxt_CAphase;
	extern  CString g_sLangID_Application;//Ӧ�ó��������ɵı���Ӧ�ó���
	extern  CString g_sLangTxt_Application;
	extern  CString g_sLangID_FixedValueRegion;
	extern  CString g_sLangTxt_FixedValueRegion;
	extern  CString g_sLangID_CloseTip;
	extern  CString g_sLangTxt_CloseTip;
	extern  CString g_sLangID_Modify; //�޸�
	extern  CString g_sLangTxt_Modify;
	extern  CString g_sLangID_ItemPrtcFile; //�豸����ļ�(*.xml)|*.xml||
	extern  CString g_sLangTxt_ItemPrtcFile;
	extern  CString g_sLangID_SelDevDaModFile;//ѡ���豸����ģ���ļ�
	extern  CString g_sLangTxt_SelDevDaModFile;
	extern  CString g_sLangID_TemDataFileChange; //ģ���豸����ģ���滻ӳ�������ļ�
	extern  CString g_sLangTxt_TemDataFileChange;
	extern  CString g_sLangID_ConServerFail; //���ӷ�������%s����%d��ʧ��
	extern  CString g_sLangTxt_ConServerFail;
	extern CString g_sLangID_ConServerSucc;//= _T("sConServerSucc");
	extern CString g_sLangTxt_ConServerSucc;//= _T("���ӷ�������%s����%d���ɹ�");
	extern  CString g_sLangID_UserUnExist; //�û���������
	extern  CString g_sLangTxt_UserUnExist;
	extern  CString g_sLangID_PasswordIncorrect; //���벻��ȷ
	extern  CString g_sLangTxt_PasswordIncorrect;
	extern  CString g_sLangID_LoginError; //��¼����
	extern  CString g_sLangTxt_LoginError;
	extern  CString g_sLangID_StopTest; //ֹͣ����
	extern  CString g_sLangTxt_StopTest;
	extern  CString g_sLangID_StartTest;//ֹͣ���ԣ�ֹͣ����
	extern  CString g_sLangTxt_StartTest;
	extern  CString g_sLangID_ExportReport;    //��������
	extern  CString g_sLangTxt_ExportReport;
	extern  CString g_sLangID_ExportReportBatch;    //��������
	extern  CString g_sLangTxt_ExportReportBatch;
	extern  CString g_sLangID_StatusBar; 
	extern  CString g_sLangTxt_StatusBar;
	extern  CString g_sLangID_TestStop2;//�����豸ʧ�ܣ�������ֹ
	extern  CString g_sLangTxt_TestStop2;
	extern  CString g_sLangID_DataOpreation;//���ݲ���
	extern  CString g_sLangTxt_DataOpreation;

	extern  CString g_sLangID_OpenTip;
	extern  CString g_sLangTxt_OpenTip;
	extern  CString g_sLangID_ModelTestTip;//��ʼ���ԣ���ʼ�����������豸����ģ��
	extern  CString g_sLangTxt_ModelTestTip;
	extern  CString g_sLangID_DevModelTestTip;//װ��ģ�Ͳ��ԣ���װ��ö������ģ�ͣ�Ȼ����в���
	extern  CString g_sLangTxt_DevModelTestTip;
	extern  CString g_sLangID_StopTestTip;//ֹͣ���ԣ�ֹͣ����
	extern  CString g_sLangTxt_StopTestTip;
	extern  CString g_sLangID_ExportReportTip;//�������棬��������
	extern  CString g_sLangTxt_ExportReportTip;
	extern  CString g_sLangID_SaveFileTip;//�����ļ��������豸����ģ��ӳ���ϵ�ļ�
	extern  CString g_sLangTxt_SaveFileTip;
	extern  CString g_sLangID_OutputBarTip;//�л����������ʾ�����������
	extern  CString g_sLangTxt_OutputBarTip;
	extern  CString g_sLangID_StatusBarTip;//�л�״̬������ʾ������״̬��
	extern  CString g_sLangTxt_StatusBarTip;
	extern  CString g_sLangID_CompareDataTip;//�Ƚ�ID���Ƚ�ID
	extern  CString g_sLangTxt_CompareDataTip;
	extern  CString g_sLangID_AboutTip;//���ڣ���ʾ������Ϣ���汾�źͰ�Ȩ
	extern  CString g_sLangTxt_AboutTip;
	extern  CString g_sLangID_TestMain;//������ҳ(&H)
	extern  CString g_sLangTxt_TestMain;
	extern  CString g_sLangID_ModelTest;//ģ�Ͳ���
	extern  CString g_sLangTxt_ModelTest;
	extern  CString g_sLangID_ProtocolTest;//��Լ����
	extern  CString g_sLangTxt_ProtocolTest;
	extern  CString g_sLangID_ModelFileTest;//ģ���ļ�����
	extern  CString g_sLangTxt_ModelFileTest;	
	extern  CString g_sLangID_DevModelTest;//װ��ģ�Ͳ���
	extern  CString g_sLangTxt_DevModelTest;
	extern  CString g_sLangID_ResultOpera;//�������
	extern  CString g_sLangTxt_ResultOpera;
	extern  CString g_sLangID_SaveFile;//����ӳ���ļ�
	extern  CString g_sLangTxt_SaveFile;
	extern  CString g_sLangID_OutputBar;//�����
	extern  CString g_sLangTxt_OutputBar;
	extern  CString g_sLangID_CompareData;//�Ƚ�����ID
	extern  CString g_sLangTxt_CompareData;
	extern  CString g_sLangID_CmpDataNameFull;//��������ȫ�ַ����Ƚ�
	extern  CString g_sLangTxt_CmpDataNameFull;
	extern  CString g_sLangID_Browse;//���
	extern  CString g_sLangTxt_Browse;
	extern  CString g_sLangID_Home;//��ҳ(&H)
	extern  CString g_sLangTxt_Home;
	extern  CString g_sLangID_CreatDataMap;//��������ӳ��
	extern  CString g_sLangTxt_CreatDataMap;
	extern  CString g_sLangID_DeleteDataMap;//ɾ������ӳ��
	extern  CString g_sLangTxt_DeleteDataMap;
	extern  CString g_sLangID_CreatDataMap2;//��������ӳ��
	extern  CString g_sLangTxt_CreatDataMap2;
	extern  CString g_sLangID_DeleteDataMap2;//ɾ������ӳ��
	extern  CString g_sLangTxt_DeleteDataMap2;
	extern  CString g_sLangID_SelStdDataFile;//��ѡ���׼�豸����ģ���ļ�
	extern  CString g_sLangTxt_SelStdDataFile;
	extern  CString g_sLangID_DataSetNoOnly;//���ݼ���%s����Ψһ
	extern  CString g_sLangTxt_DataSetNoOnly;
	extern  CString g_sLangID_User;
	extern  CString g_sLangTxt_User;
	extern  CString g_sLangID_Module;
	extern  CString g_sLangTxt_Module;
	extern  CString g_sLangID_RemotePort;
	extern  CString g_sLangTxt_RemotePort;
	extern  CString g_sLangID_LocalPort;
	extern  CString g_sLangTxt_LocalPort;
	extern  CString g_sLangID_State;
	extern  CString g_sLangTxt_State;
	extern  CString g_sLangID_ServerWorkPath;
	extern  CString g_sLangTxt_ServerWorkPath;

	extern  CString g_sLangID_New;
	extern  CString g_sLangTxt_New;
	extern  CString g_sLangID_TemNew;
	extern  CString g_sLangTxt_TemNew;
	extern  CString g_sLangID_NewTip;
	extern  CString g_sLangTxt_NewTip;
	extern  CString g_sLangID_OpenTips;
	extern  CString g_sLangTxt_OpenTips;
	extern  CString g_sLangID_SaveTips;
	extern  CString g_sLangTxt_SaveTips;
	extern  CString g_sLangID_SaveAsTips;
	extern  CString g_sLangTxt_SaveAsTips;
	extern  CString g_sLangID_RecentFile;
	extern  CString g_sLangTxt_RecentFile;

	extern  CString g_sLangID_TemplateDef;
	extern  CString g_sLangTxt_TemplateDef;
	extern  CString g_sLangID_TemplateProperty;
	extern  CString g_sLangTxt_TemplateProperty;
	extern  CString g_sLangID_CommDef;
	extern  CString g_sLangTxt_CommDef;
	extern  CString g_sLangID_InitDef;
	extern  CString g_sLangTxt_InitDef;
	extern  CString g_sLangID_Exist;
	extern  CString g_sLangTxt_Exist;
	extern  CString g_sLangID_NoDataNotInsert;
	extern  CString g_sLangTxt_NoDataNotInsert;
	extern  CString g_sLangID_Attention;
	extern  CString g_sLangTxt_Attention;
	extern  CString g_sLangID_KeySameId;
	extern  CString g_sLangTxt_KeySameId;

	extern  CString g_sLangID_InitiaErrors;  //��ʼ������
	extern  CString g_sLangTxt_InitiaErrors;
	extern  CString g_sLangID_OtherStart;  //�Է�û������
	extern  CString g_sLangTxt_OtherStart;
	extern  CString g_sLangID_OtherClose;  //�Է��Ѿ��ر�
	extern  CString g_sLangTxt_OtherClose;
	extern  CString g_sLangID_ConnectRefuse;  //���ӵĳ��Ա��ܾ�
	extern  CString g_sLangTxt_ConnectRefuse;
	extern  CString g_sLangID_AttemptOperate;  //��һ�����׽����ϳ�����һ������
	extern  CString g_sLangTxt_AttemptOperate;
	extern  CString g_sLangID_SpecificUse;  //�ض��ĵ�ַ����ʹ����
	extern  CString g_sLangTxt_SpecificUse;
	extern  CString g_sLangID_ConnectionClosed;  //�����������ӱ��ر�
	extern  CString g_sLangTxt_ConnectionClosed;
	extern  CString g_sLangID_GenericError;  //һ�����
	extern  CString g_sLangTxt_GenericError;
	extern  CString g_sLangID_Add;       //���
	extern  CString g_sLangTxt_Add;
	extern  CString g_sLangID_NoDataChangeMsg;       //û��ע��ڵ�[%d]���ݸı���Ϣ
	extern  CString g_sLangTxt_NoDataChangeMsg;
	extern  CString g_sLangID_FileNameInclude;       //�ļ�����%s��������%s���ȷǷ��ַ�
	extern  CString g_sLangTxt_FileNameInclude;
	extern  CString g_sLangID_Add3;       
	extern  CString g_sLangTxt_Add3;
	extern  CString g_sLangID_Select;//ѡ��
	extern  CString g_sLangTxt_Select;
	extern  CString g_sLangID_Value;
	extern  CString g_sLangTxt_Value;
	extern  CString g_sLangID_DefaultValue;
	extern  CString g_sLangTxt_DefaultValue;

	extern  CString g_sLangID_PrtcTempFile;     //��Լģ���ļ�
	extern  CString g_sLangTxt_PrtcTempFile;
	extern  CString g_sLangID_PrtcProjectFile;     //��Լģ���ļ�
	extern  CString g_sLangTxt_PrtcProjectFile;
	extern  CString g_sLangID_ModelFile;//ģ���ļ�
	extern  CString g_sLangTxt_ModelFile;

	extern  CString g_sLangID_PrtcTempFileMagn;     //��Լģ���ļ�����
	extern  CString g_sLangTxt_PrtcTempFileMagn;
	extern  CString g_sLangID_Version;    
	extern  CString g_sLangTxt_Version;
	extern  CString g_sLangID_TimeLimit;     //ʱ��
	extern  CString g_sLangTxt_TimeLimit;
	extern  CString g_sLangID_ComparaObject;     //�Ƚ���
	extern  CString g_sLangTxt_ComparaObject;
	extern  CString g_sLangID_StandardValue;     //��׼ֵ
	extern  CString g_sLangTxt_StandardValue;
	extern  CString g_sLangID_TureValue;     //ʵ��ֵ
	extern  CString g_sLangTxt_TureValue;
	extern  CString g_sLangID_Property;     //����
	extern  CString g_sLangTxt_Property;
	extern  CString g_sLangID_UnStallWord;     //û�а�װWord
	extern  CString g_sLangTxt_UnStallWord;
	extern  CString g_sLangID_Title;     //���� %d
	extern  CString g_sLangTxt_Title;
	extern  CString g_sLangID_UserUnits;     //�û���λ��
	extern  CString g_sLangTxt_UserUnits;
	extern  CString g_sLangID_User2;     //�û���
	extern  CString g_sLangTxt_User2;
	extern  CString g_sLangID_Develop;     //������
	extern  CString g_sLangTxt_Develop;
	extern  CString g_sLangID_ReName;     //������
	extern  CString g_sLangTxt_ReName;
	extern  CString g_sLangID_Variable;     
	extern  CString g_sLangTxt_Variable;
	extern  CString g_sLangID_DeleteFloder;     //ɾ���ļ���
	extern  CString g_sLangTxt_DeleteFloder;
	extern  CString g_sLangID_SureDelFoldItem;     //ȷ��Ҫɾ���ļ��� %s ��������Ŀ��?
	extern  CString g_sLangTxt_SureDelFoldItem;
	extern  CString g_sLangID_Size2;     //��С
	extern  CString g_sLangTxt_Size2;
	extern  CString g_sLangID_ModiftyFileNameFail;     //�޸��ļ�����ʧ��
	extern  CString g_sLangTxt_ModiftyFileNameFail;


//�����з�����
	extern CString g_sLangID_SCDFiles;
	extern CString g_sLangTxt_SCDFiles;           
	extern CString g_sLangID_RecordFiles;         
	extern CString g_sLangTxt_RecordFiles;
	extern CString g_sLangID_TemplateFiles;
	extern CString g_sLangTxt_TemplateFiles;
	extern CString g_sLangID_WorkspaceFiles;
	extern CString g_sLangTxt_WorkspaceFiles;
	extern CString g_sLangID_IEC61850SetFiles;
	extern CString g_sLangTxt_IEC61850SetFiles;
	extern CString g_sLangID_PcapFiles;
	extern CString g_sLangTxt_PcapFiles;
	extern CString g_sLangID_PrintScreen;
	extern CString g_sLangTxt_PrintScreen;
	extern CString g_sLangID_Others;
	extern CString g_sLangTxt_Others;
	extern CString g_sLangID_SavePcapFiles;
	extern CString g_sLangTxt_SavePcapFiles;	
	extern CString g_sLangID_SavePrintScreen;
	extern CString g_sLangTxt_SavePrintScreen;		
	extern CString g_sLangID_OtherTypeFiles;
	extern CString g_sLangTxt_OtherTypeFiles;




	extern  CString g_sLangID_Output;     
	extern  CString g_sLangTxt_Output;
	extern  CString g_sLangID_ConfirmDel;     
	extern  CString g_sLangTxt_ConfirmDel;
	extern  CString g_sLangID_NoSave;     
	extern  CString g_sLangTxt_NoSave;
	extern  CString g_sLangID_Increase;
	extern  CString g_sLangTxt_Increase;
	extern  CString g_sLangID_Decrease;
	extern  CString g_sLangTxt_Decrease;
	extern  CString g_sLangID_Export;      
	extern  CString g_sLangTxt_Export;
	extern  CString g_sLangID_Import;   
	extern  CString g_sLangTxt_Import;

	extern  CString g_sLangID_ClcltFmla;   
	extern  CString g_sLangTxt_ClcltFmla;

	extern  CString g_sLangID_GuideWizardFile;
	extern  CString g_sLangTxt_GuideWizardFile;

	extern  CString g_sLangID_IecConfigFile;//            = _T("sIecConfigFile");
	extern  CString g_sLangTxt_IecConfigFile;//           = _T("IEC61850�����ļ�");
	extern  CString g_sLangID_DvIecConfigFile;//            = _T("sDvIecConfigFile");
	extern  CString g_sLangTxt_DvIecConfigFile;//           = _T("�����豸������IEC61850�����ļ�����");
	extern  CString g_sLangID_DvIecConfigFileMngr;//            = _T("sDvIecConfigFileMngr");
	extern  CString g_sLangTxt_DvIecConfigFileMngr;//           = _T("�����豸������IEC61850�����ļ�����");

	extern  CString g_sLangID_NoTitle;//�ޱ���
	extern  CString g_sLangTxt_NoTitle;
	extern  CString g_sLangID_FileNotExist;//�ļ���%s��������
	extern  CString g_sLangTxt_FileNotExist;

	extern  CString g_sLangID_YunDownFileFaild;//���ƶ������ļ�ʧ��
	extern  CString g_sLangTxt_YunDownFileFaild;

	extern  CString g_sLangID_UpLoad; 
	extern  CString g_sLangTxt_UpLoad;
	extern  CString g_sLangID_DownLoad; 
	extern  CString g_sLangTxt_DownLoad;

	extern  CString g_sLangID_TestItemParEdit; //������Ŀ�����༭
	extern  CString g_sLangTxt_TestItemParEdit;
	extern  CString g_sLangID_ParaName; //��������
	extern  CString g_sLangTxt_ParaName;
	extern  CString g_sLangID_ParaValue; //����ֵ
	extern  CString g_sLangTxt_ParaValue;

	extern  CString g_sLangID_GlobalData;
	extern  CString g_sLangTxt_GlobalData;
	extern  CString g_sLangID_TestAppDef;
	extern  CString g_sLangTxt_TestAppDef;
	extern  CString g_sLangID_RepeatResultInfo;
	extern  CString g_sLangTxt_RepeatResultInfo;


	extern  CString g_sLangID_Login; 
	extern  CString g_sLangTxt_Login;
	extern  CString g_sLangID_Clear; 
	extern  CString g_sLangTxt_Clear;
	extern  CString g_sLangID_SyntaxCheck; 
	extern  CString g_sLangTxt_SyntaxCheck;
	extern  CString g_sLangID_SyntaxCheckTips; 
	extern  CString g_sLangTxt_SyntaxCheckTips;

	extern CString g_sLangID_OutputWnd;       //�������
	extern CString g_sLangTxt_OutputWnd;

	extern CString g_sLangID_DataSet;
	extern CString g_sLangTxt_DataSet;

	extern CString g_sLangID_Quit; 
	extern CString g_sLangTxt_Quit;
	extern CString g_sLangID_QuitTip; 
	extern CString g_sLangTxt_QuitTip;

    //2024-1-4  shaolei
    extern CString g_sLangID_Voltage;       //��ѹ
    extern CString g_sLangTxt_Voltage;
    extern CString g_sLangID_Current;       //����
    extern CString g_sLangTxt_Current;
    extern CString g_sLangID_ActivePower;       //�й�����
    extern CString g_sLangTxt_ActivePower;
    extern CString g_sLangID_ReactivePower;       //�޹�����
    extern CString g_sLangTxt_ReactivePower;
    extern CString g_sLangID_Frequency;       //Ƶ��
    extern CString g_sLangTxt_Frequency;
    extern CString g_sLangID_PowerFactor;       //��������
    extern CString g_sLangTxt_PowerFactor;


	extern CString g_sLangID_Native_StartOutput;
	extern CString g_sLangTxt_Native_StartOutput;		//��ʼ���
	//ʵ����CXLanguageResourceAtsBase�ж����ɾ��  zhouhj 2024.5.25
//     extern CString g_sLangID_TestComplete               ;//= _T("sTestComplete");
//     extern CString g_sLangTxt_TestComplete                  ;//= _T("�������");
    extern CString g_sLangID_Native_TestAnomalies;     //= _T("Native_TestAnomalies");
    extern CString g_sLangTxt_Native_TestAnomalies;    //= _T("�����쳣");
    extern CString g_sLangID_Native_RelieveTestAnomalies; //= _T("Native_RelieveTestAnomalies")
    extern CString g_sLangTxt_Native_RelieveTestAnomalies; //= _T("��������쳣")
    extern CString g_sLangID_Native_StateSwitch;        //= _T("Native_StateSwitch");
    extern CString g_sLangTxt_Native_StateSwitch;       //= _T("״̬�л�");
    extern CString g_sLangID_Native_SupDCSwitch;        //= _T("Native_SupDCSwitch");
    extern CString g_sLangTxt_Native_SupDCSwitch;       //= _T("����ֱ���л�");
    extern CString g_sLangID_Native_BinDisPlace;        // = _T("Native_BinDisPlace");
    extern CString g_sLangTxt_Native_BinDisPlace;       //= _T("�����λ");
    extern CString g_sLangID_Native_BoutDisPlace;       //= _T("Native_BoutDisPlace");
    extern CString g_sLangTxt_Native_BoutDisPlace;      //= _T("������λ");
    extern CString g_sLangID_Native_ParaUpdata;         //= _T("Native_ParaUpdata");
    extern CString g_sLangTxt_Native_ParaUpdata;        //= _T("��������");


	extern CString g_sLangID_Native_Port;		// = _T("Native_Port")
	extern CString g_sLangTxt_Native_Port;        //= _T("��");

	extern CString g_sLangID_TestInstrumentConfig;
	extern CString g_sLangTxt_TestInstrumentConfig;
	extern CString g_sLangID_ScanLANTestInstrument;
	extern CString g_sLangTxt_ScanLANTestInstrument;
	extern CString g_sLangID_DirectConfigRemoteInstrument;
	extern CString g_sLangTxt_DirectConfigRemoteInstrument;
	extern CString g_sLangID_ScanRemoteTestInstrument;
	extern CString g_sLangTxt_ScanRemoteTestInstrument;
	extern CString g_sLangID_Setup;
	extern CString g_sLangTxt_Setup;
	extern CString g_sLangID_Upgrade;
	extern CString g_sLangTxt_Upgrade;
	extern CString g_sLangID_EnablePUDA;
	extern CString g_sLangTxt_EnablePUDA;
	extern CString g_sLangID_EnableTestSvr;
	extern CString g_sLangTxt_EnableTestSvr;
	extern CString g_sLangID_TestInstrumentModel;
	extern CString g_sLangTxt_TestInstrumentModel;
	extern CString g_sLangID_TestInstrumentID;
	extern CString g_sLangTxt_TestInstrumentID;
	extern CString g_sLangID_CloudIP;
	extern CString g_sLangTxt_CloudIP;
	extern CString g_sLangID_CloudPort;
	extern CString g_sLangTxt_CloudPort;
	extern CString g_sLangID_TestInstrumentSerialNumber;
	extern CString g_sLangTxt_TestInstrumentSerialNumber;
	extern CString g_sLangID_Password;
	extern CString g_sLangTxt_Password;
	extern CString g_sLangID_Unit2;
	extern CString g_sLangTxt_Unit2;
	extern CString g_sLangID_Bind;
	extern CString g_sLangTxt_Bind;
	extern CString g_sLangID_Query;
	extern CString g_sLangTxt_Query;
	extern CString g_sLangID_TestInstrumentConnectionError;
	extern CString g_sLangTxt_TestInstrumentConnectionError;
	extern CString g_sLangID_CloudServerConnectionError;
	extern CString g_sLangTxt_CloudServerConnectionError;
	extern CString g_sLangID_IPIsEmpty;
	extern CString g_sLangTxt_IPIsEmpty;
	extern CString g_sLangID_ConnectionTestInstrumentFailed;
	extern CString g_sLangTxt_ConnectionTestInstrumentFailed;
	extern CString g_sLangID_MulticastInitSuccess;
	extern CString g_sLangTxt_MulticastInitSuccess;
	extern CString g_sLangID_MulticastInitFailed;
	extern CString g_sLangTxt_MulticastInitFailed;
	extern CString g_sLangID_MulticastInitBindSuccess;
	extern CString g_sLangTxt_MulticastInitBindSuccess;
	extern CString g_sLangID_Disconnection;
	extern CString g_sLangTxt_Disconnection;
	extern CString g_sLangID_CloudConnectionFailed;
	extern CString g_sLangTxt_CloudConnectionFailed;
	extern CString g_sLangID_TestInstrumentUserInfoError;
	extern CString g_sLangTxt_TestInstrumentUserInfoError;
	extern CString g_sLangID_Connect;
	extern CString g_sLangTxt_Connect;
	extern CString g_sLangID_StopScanning;
	extern CString g_sLangTxt_StopScanning;
	extern CString g_sLangID_Scanning;
	extern CString g_sLangTxt_Scanning;
	extern CString g_sLangID_NanjingEnergyCloud;
	extern CString g_sLangTxt_NanjingEnergyCloud;
	extern CString g_sLangID_TestInstrumentConfigFileNotFound;
	extern CString g_sLangTxt_TestInstrumentConfigFileNotFound;
	extern CString g_sLangID_OAClientInitFail;
	extern CString g_sLangTxt_OAClientInitFail;
    //2024-10-22  wuxinyi
	extern CString g_sLangID_ResultBar;//�����
	extern CString g_sLangTxt_ResultBar;
	extern CString g_sLangID_StatusLight;
	extern CString g_sLangTxt_StatusLight;
	extern CString g_sLangID_WinwordProcessWarning;
	extern CString g_sLangTxt_WinwordProcessWarning;
	extern CString g_sLangID_CloseProcessWarning;
	extern CString g_sLangTxt_CloseProcessWarning;
	//2024-11-08 zhouyangyong
	extern CString g_sLangID_NotSupportVoltGather;
	extern CString g_sLangTxt_NotSupportVoltGather;

	extern CString g_sLangID_CreatReplaySocket;
	extern CString g_sLangTxt_CreatReplaySocket;//�������Ĺ��ϻط�ͨ��......
	extern CString g_sLangID_CreatCapRcdSocket;
	extern CString g_sLangTxt_CreatCapRcdSocket;//��������¼��ͨ��......
	extern CString g_sLangID_ConnectOKWaitTest;
	extern CString g_sLangTxt_ConnectOKWaitTest;//������ɣ�׼����ʼ����......
	extern CString g_sLangID_RevReplayRequest;
	extern CString g_sLangTxt_RevReplayRequest;//�յ��ط���������
	extern CString g_sLangID_RevSendDataReply;
	extern CString g_sLangTxt_RevSendDataReply;//�յ��������ݿ�ʼӦ��
	extern CString g_sLangID_ReplayData;
	extern CString g_sLangTxt_ReplayData;//�ط�����
	extern CString g_sLangID_ReadyToSend;
	extern CString g_sLangTxt_ReadyToSend;//׼������
	extern CString g_sLangID_SentComplete;
	extern CString g_sLangTxt_SentComplete;//�ѷ������
	extern CString g_sLangID_SentAllReplayData;
	extern CString g_sLangTxt_SentAllReplayData;//�ط�����ȫ���������

 	//extern CString g_sLangID_Qualified;
 	//extern CString g_sLangTxt_Qualified;//�ϸ�
	//extern CString g_sLangID_Unqualified;
	//extern CString g_sLangTxt_Unqualified;//���ϸ�
	extern CString g_sLangID_ControlBlock;
	extern CString g_sLangTxt_ControlBlock;//���ƿ�
	extern CString g_sLangID_Packet;
	extern CString g_sLangTxt_Packet;//����
	extern CString g_sLangID_AxisUnitOmega;
	extern CString g_sLangTxt_AxisUnitOmega;//��
	extern CString g_sLangID_AxisUnitAng;
	extern CString g_sLangTxt_AxisUnitAng;//��
	extern CString g_sLangID_AxisUnitDeltaSmall;
	extern CString g_sLangTxt_AxisUnitDeltaSmall;//��
	//extern CString g_sLangID_Diff_Variation;            //_T("Diff_Variation")
	//extern CString g_sLangTxt_Diff_Variation;           //_T("��")
	extern CString g_sLangID_AxisUnitPhi;            //_T("AxisUnitPhi")
	extern CString g_sLangTxt_AxisUnitPhi;           //_T("��")