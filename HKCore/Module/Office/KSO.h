#pragma once

namespace KSO
{
	
	// Adjustments ��װ��

	class Adjustments : public COleDispatchDriver
	{
	public:
		Adjustments(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		Adjustments(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		Adjustments(const Adjustments& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// Adjustments ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Count()
		{
			long result;
			InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		float get_Item(long Index)
		{
			float result;
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, parms, Index);
			return result;
		}
		void put_Item(long Index, float newValue)
		{
			static BYTE parms[] = VTS_I4 VTS_R4 ;
			InvokeHelper(0x0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, Index, newValue);
		}
	};

	// AnswerWizard ��װ��
	class AnswerWizard : public COleDispatchDriver
	{
	public:
		AnswerWizard(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		AnswerWizard(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		AnswerWizard(const AnswerWizard& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// AnswerWizard ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x60030000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Files()
		{
			LPDISPATCH result;
			InvokeHelper(0x60030001, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		void ClearFileList()
		{
			InvokeHelper(0x60030002, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void ResetFileList()
		{
			InvokeHelper(0x60030003, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
	};

	// AnswerWizardFiles ��װ��
	class AnswerWizardFiles : public COleDispatchDriver
	{
	public:
		AnswerWizardFiles(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		AnswerWizardFiles(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		AnswerWizardFiles(const AnswerWizardFiles& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// AnswerWizardFiles ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x60030000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		CString get_Item(long Index)
		{
			CString result;
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms, Index);
			return result;
		}
		long get_Count()
		{
			long result;
			InvokeHelper(0x60030002, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void Add(LPCTSTR FileName)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x60030003, DISPATCH_METHOD, VT_EMPTY, NULL, parms, FileName);
		}
		void Delete(LPCTSTR FileName)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x60030004, DISPATCH_METHOD, VT_EMPTY, NULL, parms, FileName);
		}
	};

	// Assistant ��װ��
	class Assistant : public COleDispatchDriver
	{
	public:
		Assistant(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		Assistant(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		Assistant(const Assistant& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// Assistant ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x60030000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		void Move(long xLeft, long yTop)
		{
			static BYTE parms[] = VTS_I4 VTS_I4 ;
			InvokeHelper(0x60030001, DISPATCH_METHOD, VT_EMPTY, NULL, parms, xLeft, yTop);
		}
		void put_Top(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60030002, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_Top()
		{
			long result;
			InvokeHelper(0x60030002, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_Left(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60030004, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_Left()
		{
			long result;
			InvokeHelper(0x60030004, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void Help()
		{
			InvokeHelper(0x60030006, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		long StartWizard(BOOL On, LPCTSTR Callback, long PrivateX, VARIANT& Animation, VARIANT& CustomTeaser, VARIANT& Top, VARIANT& Left, VARIANT& Bottom, VARIANT& Right)
		{
			long result;
			static BYTE parms[] = VTS_BOOL VTS_BSTR VTS_I4 VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT ;
			InvokeHelper(0x60030007, DISPATCH_METHOD, VT_I4, (void*)&result, parms, On, Callback, PrivateX, &Animation, &CustomTeaser, &Top, &Left, &Bottom, &Right);
			return result;
		}
		void EndWizard(long WizardID, BOOL varfSuccess, VARIANT& Animation)
		{
			static BYTE parms[] = VTS_I4 VTS_BOOL VTS_VARIANT ;
			InvokeHelper(0x60030008, DISPATCH_METHOD, VT_EMPTY, NULL, parms, WizardID, varfSuccess, &Animation);
		}
		void ActivateWizard(long WizardID, long act, VARIANT& Animation)
		{
			static BYTE parms[] = VTS_I4 VTS_I4 VTS_VARIANT ;
			InvokeHelper(0x60030009, DISPATCH_METHOD, VT_EMPTY, NULL, parms, WizardID, act, &Animation);
		}
		void ResetTips()
		{
			InvokeHelper(0x6003000a, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		LPDISPATCH get_NewBalloon()
		{
			LPDISPATCH result;
			InvokeHelper(0x6003000b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_BalloonError()
		{
			long result;
			InvokeHelper(0x6003000c, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		BOOL get_Visible()
		{
			BOOL result;
			InvokeHelper(0x6003000d, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_Visible(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x6003000d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_Animation()
		{
			long result;
			InvokeHelper(0x6003000f, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_Animation(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x6003000f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_Reduced()
		{
			BOOL result;
			InvokeHelper(0x60030011, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_Reduced(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x60030011, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		void put_AssistWithHelp(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x60030013, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_AssistWithHelp()
		{
			BOOL result;
			InvokeHelper(0x60030013, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_AssistWithWizards(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x60030015, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_AssistWithWizards()
		{
			BOOL result;
			InvokeHelper(0x60030015, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_AssistWithAlerts(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x60030017, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_AssistWithAlerts()
		{
			BOOL result;
			InvokeHelper(0x60030017, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_MoveWhenInTheWay(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x60030019, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_MoveWhenInTheWay()
		{
			BOOL result;
			InvokeHelper(0x60030019, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_Sounds(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x6003001b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_Sounds()
		{
			BOOL result;
			InvokeHelper(0x6003001b, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_FeatureTips(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x6003001d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_FeatureTips()
		{
			BOOL result;
			InvokeHelper(0x6003001d, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_MouseTips(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x6003001f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_MouseTips()
		{
			BOOL result;
			InvokeHelper(0x6003001f, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_KeyboardShortcutTips(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x60030021, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_KeyboardShortcutTips()
		{
			BOOL result;
			InvokeHelper(0x60030021, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_HighPriorityTips(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x60030023, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_HighPriorityTips()
		{
			BOOL result;
			InvokeHelper(0x60030023, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_TipOfDay(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x60030025, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_TipOfDay()
		{
			BOOL result;
			InvokeHelper(0x60030025, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_GuessHelp(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x60030027, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_GuessHelp()
		{
			BOOL result;
			InvokeHelper(0x60030027, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_SearchWhenProgramming(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x60030029, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_SearchWhenProgramming()
		{
			BOOL result;
			InvokeHelper(0x60030029, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		CString get_Item()
		{
			CString result;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		CString get_FileName()
		{
			CString result;
			InvokeHelper(0x6003002c, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_FileName(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x6003002c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_Name()
		{
			CString result;
			InvokeHelper(0x6003002e, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		BOOL get_On()
		{
			BOOL result;
			InvokeHelper(0x6003002f, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_On(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x6003002f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long DoAlert(LPCTSTR bstrAlertTitle, LPCTSTR bstrAlertText, long alb, long alc, long ald, long alq, BOOL varfSysAlert)
		{
			long result;
			static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_BOOL ;
			InvokeHelper(0x60030031, DISPATCH_METHOD, VT_I4, (void*)&result, parms, bstrAlertTitle, bstrAlertText, alb, alc, ald, alq, varfSysAlert);
			return result;
		}
	};

	// Axes ��װ��
	class Axes : public COleDispatchDriver
	{
	public:
		Axes(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		Axes(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		Axes(const Axes& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// Axes ����
	public:
		long get_Count()
		{
			long result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Item(long Type, long AxisGroup)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I4 VTS_I4 ;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, Type, AxisGroup);
			return result;
		}
		LPUNKNOWN get__NewEnum()
		{
			LPUNKNOWN result;
			InvokeHelper(0x60020002, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x94, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x95, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get__Default(long Type, long AxisGroup)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I4 VTS_I4 ;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, Type, AxisGroup);
			return result;
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x96, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
	};

	// Balloon ��װ��
	class Balloon : public COleDispatchDriver
	{
	public:
		Balloon(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		Balloon(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		Balloon(const Balloon& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// Balloon ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x60030000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Checkboxes()
		{
			LPDISPATCH result;
			InvokeHelper(0x60030001, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Labels()
		{
			LPDISPATCH result;
			InvokeHelper(0x60030002, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		void put_BalloonType(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60030003, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_BalloonType()
		{
			long result;
			InvokeHelper(0x60030003, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_Icon(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60030005, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_Icon()
		{
			long result;
			InvokeHelper(0x60030005, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_Heading(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x60030007, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_Heading()
		{
			CString result;
			InvokeHelper(0x60030007, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_Text(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x60030009, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_Text()
		{
			CString result;
			InvokeHelper(0x60030009, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_Mode(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x6003000b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_Mode()
		{
			long result;
			InvokeHelper(0x6003000b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_Animation(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x6003000d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_Animation()
		{
			long result;
			InvokeHelper(0x6003000d, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_Button(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x6003000f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_Button()
		{
			long result;
			InvokeHelper(0x6003000f, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_Callback(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x60030011, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_Callback()
		{
			CString result;
			InvokeHelper(0x60030011, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_Private(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60030013, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_Private()
		{
			long result;
			InvokeHelper(0x60030013, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void SetAvoidRectangle(long Left, long Top, long Right, long Bottom)
		{
			static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4 ;
			InvokeHelper(0x60030015, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Left, Top, Right, Bottom);
		}
		CString get_Name()
		{
			CString result;
			InvokeHelper(0x60030016, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		long Show()
		{
			long result;
			InvokeHelper(0x60030017, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
			return result;
		}
		void Close()
		{
			InvokeHelper(0x60030018, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
	};

	// BalloonCheckbox ��װ��
	class BalloonCheckbox : public COleDispatchDriver
	{
	public:
		BalloonCheckbox(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		BalloonCheckbox(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		BalloonCheckbox(const BalloonCheckbox& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// BalloonCheckbox ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		CString get_Item()
		{
			CString result;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		CString get_Name()
		{
			CString result;
			InvokeHelper(0x60030001, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x60030002, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		void put_Checked(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x60030003, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_Checked()
		{
			BOOL result;
			InvokeHelper(0x60030003, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_Text(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x60030005, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_Text()
		{
			CString result;
			InvokeHelper(0x60030005, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
	};

	// BalloonCheckboxes ��װ��
	class BalloonCheckboxes : public COleDispatchDriver
	{
	public:
		BalloonCheckboxes(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		BalloonCheckboxes(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		BalloonCheckboxes(const BalloonCheckboxes& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// BalloonCheckboxes ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		CString get_Name()
		{
			CString result;
			InvokeHelper(0x60030000, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x60030001, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Item(long Index)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, Index);
			return result;
		}
		long get_Count()
		{
			long result;
			InvokeHelper(0x60030003, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_Count(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60030003, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		LPUNKNOWN get__NewEnum()
		{
			LPUNKNOWN result;
			InvokeHelper(0xfffffffc, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
			return result;
		}
	};

	// BalloonLabel ��װ��
	class BalloonLabel : public COleDispatchDriver
	{
	public:
		BalloonLabel(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		BalloonLabel(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		BalloonLabel(const BalloonLabel& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// BalloonLabel ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		CString get_Item()
		{
			CString result;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		CString get_Name()
		{
			CString result;
			InvokeHelper(0x60030001, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x60030002, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		void put_Text(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x60030003, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_Text()
		{
			CString result;
			InvokeHelper(0x60030003, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
	};

	// BalloonLabels ��װ��
	class BalloonLabels : public COleDispatchDriver
	{
	public:
		BalloonLabels(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		BalloonLabels(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		BalloonLabels(const BalloonLabels& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// BalloonLabels ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		CString get_Name()
		{
			CString result;
			InvokeHelper(0x60030000, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x60030001, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Item(long Index)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, Index);
			return result;
		}
		long get_Count()
		{
			long result;
			InvokeHelper(0x60030003, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_Count(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60030003, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		LPUNKNOWN get__NewEnum()
		{
			LPUNKNOWN result;
			InvokeHelper(0xfffffffc, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
			return result;
		}
	};


	// BulletFormat2 ��װ��
	class BulletFormat2 : public COleDispatchDriver
	{
	public:
		BulletFormat2(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		BulletFormat2(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		BulletFormat2(const BulletFormat2& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// BulletFormat2 ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Character()
		{
			long result;
			InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_Character(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		LPDISPATCH get_Font()
		{
			LPDISPATCH result;
			InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Number()
		{
			long result;
			InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void Picture(LPCTSTR FileName)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x5, DISPATCH_METHOD, VT_EMPTY, NULL, parms, FileName);
		}
		float get_RelativeSize()
		{
			float result;
			InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
			return result;
		}
		void put_RelativeSize(float newValue)
		{
			static BYTE parms[] = VTS_R4 ;
			InvokeHelper(0x6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_StartValue()
		{
			long result;
			InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_StartValue(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_Style()
		{
			long result;
			InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_Style(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_Type()
		{
			long result;
			InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_Type(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x9, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_UseTextColor()
		{
			long result;
			InvokeHelper(0xa, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_UseTextColor(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0xa, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_UseTextFont()
		{
			long result;
			InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_UseTextFont(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0xb, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_Visible()
		{
			long result;
			InvokeHelper(0xc, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_Visible(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0xc, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
	};

	// CalloutFormat ��װ��
	class CalloutFormat : public COleDispatchDriver
	{
	public:
		CalloutFormat(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		CalloutFormat(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CalloutFormat(const CalloutFormat& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// CalloutFormat ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		void AutomaticLength()
		{
			InvokeHelper(0xa, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void CustomDrop(float Drop)
		{
			static BYTE parms[] = VTS_R4 ;
			InvokeHelper(0xb, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Drop);
		}
		void CustomLength(float Length)
		{
			static BYTE parms[] = VTS_R4 ;
			InvokeHelper(0xc, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Length);
		}
		void PresetDrop(long DropType)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0xd, DISPATCH_METHOD, VT_EMPTY, NULL, parms, DropType);
		}
		long get_Accent()
		{
			long result;
			InvokeHelper(0x64, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_Accent(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x64, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_Angle()
		{
			long result;
			InvokeHelper(0x65, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_Angle(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x65, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_AutoAttach()
		{
			long result;
			InvokeHelper(0x66, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_AutoAttach(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x66, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_AutoLength()
		{
			long result;
			InvokeHelper(0x67, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		long get_Border()
		{
			long result;
			InvokeHelper(0x68, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_Border(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x68, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		float get_Drop()
		{
			float result;
			InvokeHelper(0x69, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
			return result;
		}
		long get_DropType()
		{
			long result;
			InvokeHelper(0x6a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		float get_Gap()
		{
			float result;
			InvokeHelper(0x6b, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
			return result;
		}
		void put_Gap(float newValue)
		{
			static BYTE parms[] = VTS_R4 ;
			InvokeHelper(0x6b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		float get_Length()
		{
			float result;
			InvokeHelper(0x6c, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
			return result;
		}
		long get_Type()
		{
			long result;
			InvokeHelper(0x6d, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_Type(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x6d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
	};

	
	// CanvasShapes ��װ��
	class CanvasShapes : public COleDispatchDriver
	{
	public:
		CanvasShapes(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		CanvasShapes(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CanvasShapes(const CanvasShapes& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// CanvasShapes ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Count()
		{
			long result;
			InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH Item(VARIANT& Index)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x0, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, &Index);
			return result;
		}
		LPUNKNOWN get__NewEnum()
		{
			LPUNKNOWN result;
			InvokeHelper(0xfffffffc, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH AddCallout(long Type, float Left, float Top, float Width, float Height)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I4 VTS_R4 VTS_R4 VTS_R4 VTS_R4 ;
			InvokeHelper(0xa, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, Type, Left, Top, Width, Height);
			return result;
		}
		LPDISPATCH AddConnector(long Type, float BeginX, float BeginY, float EndX, float EndY)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I4 VTS_R4 VTS_R4 VTS_R4 VTS_R4 ;
			InvokeHelper(0xb, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, Type, BeginX, BeginY, EndX, EndY);
			return result;
		}
		LPDISPATCH AddCurve(VARIANT& SafeArrayOfPoints)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0xc, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, &SafeArrayOfPoints);
			return result;
		}
		LPDISPATCH AddLabel(long Orientation, float Left, float Top, float Width, float Height)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I4 VTS_R4 VTS_R4 VTS_R4 VTS_R4 ;
			InvokeHelper(0xd, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, Orientation, Left, Top, Width, Height);
			return result;
		}
		LPDISPATCH AddLine(float BeginX, float BeginY, float EndX, float EndY)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_R4 VTS_R4 VTS_R4 VTS_R4 ;
			InvokeHelper(0xe, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, BeginX, BeginY, EndX, EndY);
			return result;
		}
		LPDISPATCH AddPicture(LPCTSTR FileName, long LinkToFile, long SaveWithDocument, float Left, float Top, float Width, float Height)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_BSTR VTS_I4 VTS_I4 VTS_R4 VTS_R4 VTS_R4 VTS_R4 ;
			InvokeHelper(0xf, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, FileName, LinkToFile, SaveWithDocument, Left, Top, Width, Height);
			return result;
		}
		LPDISPATCH AddPolyline(VARIANT& SafeArrayOfPoints)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x10, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, &SafeArrayOfPoints);
			return result;
		}
		LPDISPATCH AddShape(long Type, float Left, float Top, float Width, float Height)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I4 VTS_R4 VTS_R4 VTS_R4 VTS_R4 ;
			InvokeHelper(0x11, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, Type, Left, Top, Width, Height);
			return result;
		}
		LPDISPATCH AddTextEffect(long PresetTextEffect, LPCTSTR Text, LPCTSTR FontName, float FontSize, long FontBold, long FontItalic, float Left, float Top)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I4 VTS_BSTR VTS_BSTR VTS_R4 VTS_I4 VTS_I4 VTS_R4 VTS_R4 ;
			InvokeHelper(0x12, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, PresetTextEffect, Text, FontName, FontSize, FontBold, FontItalic, Left, Top);
			return result;
		}
		LPDISPATCH AddTextbox(long Orientation, float Left, float Top, float Width, float Height)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I4 VTS_R4 VTS_R4 VTS_R4 VTS_R4 ;
			InvokeHelper(0x13, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, Orientation, Left, Top, Width, Height);
			return result;
		}
		LPDISPATCH BuildFreeform(long EditingType, float X1, float Y1)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I4 VTS_R4 VTS_R4 ;
			InvokeHelper(0x14, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, EditingType, X1, Y1);
			return result;
		}
		LPDISPATCH Range(VARIANT& Index)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x15, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, &Index);
			return result;
		}
		void SelectAll()
		{
			InvokeHelper(0x16, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		LPDISPATCH get_Background()
		{
			LPDISPATCH result;
			InvokeHelper(0x64, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
	};

	// ChartFillFormat ��װ��
	class ChartFillFormat : public COleDispatchDriver
	{
	public:
		ChartFillFormat(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		ChartFillFormat(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		ChartFillFormat(const ChartFillFormat& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// ChartFillFormat ����
	public:
		void OneColorGradient(long Style, long Variant, float Degree)
		{
			static BYTE parms[] = VTS_I4 VTS_I4 VTS_R4 ;
			InvokeHelper(0x60020000, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Style, Variant, Degree);
		}
		void TwoColorGradient(long Style, long Variant)
		{
			static BYTE parms[] = VTS_I4 VTS_I4 ;
			InvokeHelper(0x60020001, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Style, Variant);
		}
		void PresetTextured(long PresetTexture)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60020002, DISPATCH_METHOD, VT_EMPTY, NULL, parms, PresetTexture);
		}
		void Solid()
		{
			InvokeHelper(0x60020003, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void Patterned(long Pattern)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60020004, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Pattern);
		}
		void UserPicture(VARIANT& PictureFile, VARIANT& PictureFormat, VARIANT& PictureStackUnit, VARIANT& PicturePlacement)
		{
			static BYTE parms[] = VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT ;
			InvokeHelper(0x60020005, DISPATCH_METHOD, VT_EMPTY, NULL, parms, &PictureFile, &PictureFormat, &PictureStackUnit, &PicturePlacement);
		}
		void UserTextured(LPCTSTR TextureFile)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x60020006, DISPATCH_METHOD, VT_EMPTY, NULL, parms, TextureFile);
		}
		void PresetGradient(long Style, long Variant, long PresetGradientType)
		{
			static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 ;
			InvokeHelper(0x60020007, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Style, Variant, PresetGradientType);
		}
		LPUNKNOWN get_BackColor()
		{
			LPUNKNOWN result;
			InvokeHelper(0x60020008, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
			return result;
		}
		LPUNKNOWN get_ForeColor()
		{
			LPUNKNOWN result;
			InvokeHelper(0x60020009, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
			return result;
		}
		long get_GradientColorType()
		{
			long result;
			InvokeHelper(0x6002000a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		float get_GradientDegree()
		{
			float result;
			InvokeHelper(0x6002000b, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
			return result;
		}
		long get_GradientStyle()
		{
			long result;
			InvokeHelper(0x6002000c, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		long get_GradientVariant()
		{
			long result;
			InvokeHelper(0x6002000d, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		long get_Pattern()
		{
			long result;
			InvokeHelper(0x6002000e, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		long get_PresetGradientType()
		{
			long result;
			InvokeHelper(0x6002000f, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		long get_PresetTexture()
		{
			long result;
			InvokeHelper(0x60020010, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		CString get_TextureName()
		{
			CString result;
			InvokeHelper(0x60020011, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		long get_TextureType()
		{
			long result;
			InvokeHelper(0x60020012, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		long get_Type()
		{
			long result;
			InvokeHelper(0x60020013, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_Visible(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60020014, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_Visible()
		{
			long result;
			InvokeHelper(0x60020014, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x94, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x95, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x96, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
	};

	// ChartFont ��װ��
	class ChartFont : public COleDispatchDriver
	{
	public:
		ChartFont(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		ChartFont(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		ChartFont(const ChartFont& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// ChartFont ����
	public:
		void put_Background(VARIANT& newValue)
		{
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, &newValue);
		}
		VARIANT get_Background()
		{
			VARIANT result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		void put_Bold(VARIANT& newValue)
		{
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x60020002, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, &newValue);
		}
		VARIANT get_Bold()
		{
			VARIANT result;
			InvokeHelper(0x60020002, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		void put_Color(VARIANT& newValue)
		{
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x60020004, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, &newValue);
		}
		VARIANT get_Color()
		{
			VARIANT result;
			InvokeHelper(0x60020004, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		void put_ColorIndex(VARIANT& newValue)
		{
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x60020006, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, &newValue);
		}
		VARIANT get_ColorIndex()
		{
			VARIANT result;
			InvokeHelper(0x60020006, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		void put_FontStyle(VARIANT& newValue)
		{
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x60020008, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, &newValue);
		}
		VARIANT get_FontStyle()
		{
			VARIANT result;
			InvokeHelper(0x60020008, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		void put_Italic(VARIANT& newValue)
		{
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x6002000a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, &newValue);
		}
		VARIANT get_Italic()
		{
			VARIANT result;
			InvokeHelper(0x6002000a, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		void put_Name(VARIANT& newValue)
		{
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x6002000c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, &newValue);
		}
		VARIANT get_Name()
		{
			VARIANT result;
			InvokeHelper(0x6002000c, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		void put_OutlineFont(VARIANT& newValue)
		{
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x6002000e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, &newValue);
		}
		VARIANT get_OutlineFont()
		{
			VARIANT result;
			InvokeHelper(0x6002000e, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		void put_Shadow(VARIANT& newValue)
		{
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x60020010, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, &newValue);
		}
		VARIANT get_Shadow()
		{
			VARIANT result;
			InvokeHelper(0x60020010, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		void put_Size(VARIANT& newValue)
		{
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x60020012, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, &newValue);
		}
		VARIANT get_Size()
		{
			VARIANT result;
			InvokeHelper(0x60020012, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		void put_StrikeThrough(VARIANT& newValue)
		{
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x60020014, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, &newValue);
		}
		VARIANT get_StrikeThrough()
		{
			VARIANT result;
			InvokeHelper(0x60020014, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		void put_Subscript(VARIANT& newValue)
		{
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x60020016, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, &newValue);
		}
		VARIANT get_Subscript()
		{
			VARIANT result;
			InvokeHelper(0x60020016, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		void put_Superscript(VARIANT& newValue)
		{
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x60020018, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, &newValue);
		}
		VARIANT get_Superscript()
		{
			VARIANT result;
			InvokeHelper(0x60020018, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		void put_Underline(VARIANT& newValue)
		{
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x6002001a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, &newValue);
		}
		VARIANT get_Underline()
		{
			VARIANT result;
			InvokeHelper(0x6002001a, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x94, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x95, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x96, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
	};

	// ChartGroups ��װ��
	class ChartGroups : public COleDispatchDriver
	{
	public:
		ChartGroups(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		ChartGroups(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		ChartGroups(const ChartGroups& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// ChartGroups ����
	public:
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x96, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Count()
		{
			long result;
			InvokeHelper(0x76, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH Item(VARIANT& Index)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0xaa, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, &Index);
			return result;
		}
		LPUNKNOWN _NewEnum()
		{
			LPUNKNOWN result;
			InvokeHelper(0xfffffffc, DISPATCH_METHOD, VT_UNKNOWN, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x94, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x95, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
	};

	// ColorFormat ��װ��
	class ColorFormat : public COleDispatchDriver
	{
	public:
		ColorFormat(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		ColorFormat(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		ColorFormat(const ColorFormat& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// ColorFormat ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_RGB()
		{
			long result;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_RGB(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_SchemeColor()
		{
			long result;
			InvokeHelper(0x64, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_SchemeColor(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x64, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_Type()
		{
			long result;
			InvokeHelper(0x65, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		float get_TintAndShade()
		{
			float result;
			InvokeHelper(0x67, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
			return result;
		}
		void put_TintAndShade(float newValue)
		{
			static BYTE parms[] = VTS_R4 ;
			InvokeHelper(0x67, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_ObjectThemeColor()
		{
			long result;
			InvokeHelper(0x68, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_ObjectThemeColor(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x68, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		float get_Brightness()
		{
			float result;
			InvokeHelper(0x69, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
			return result;
		}
		void put_Brightness(float newValue)
		{
			static BYTE parms[] = VTS_R4 ;
			InvokeHelper(0x69, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
	};

	// CommandBar ��װ��
	class CommandBar : public COleDispatchDriver
	{
	public:
		CommandBar(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		CommandBar(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CommandBar(const CommandBar& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// CommandBar ����
	public:
		LPDISPATCH get_accParent()
		{
			LPDISPATCH result;
			InvokeHelper(0xffffec78, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_accChildCount()
		{
			long result;
			InvokeHelper(0xffffec77, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_accChild(VARIANT& varChild)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0xffffec76, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, &varChild);
			return result;
		}
		CString get_accName(VARIANT& varChild)
		{
			CString result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0xffffec75, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms, &varChild);
			return result;
		}
		CString get_accValue(VARIANT& varChild)
		{
			CString result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0xffffec74, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms, &varChild);
			return result;
		}
		CString get_accDescription(VARIANT& varChild)
		{
			CString result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0xffffec73, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms, &varChild);
			return result;
		}
		VARIANT get_accRole(VARIANT& varChild)
		{
			VARIANT result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0xffffec72, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, parms, &varChild);
			return result;
		}
		VARIANT get_accState(VARIANT& varChild)
		{
			VARIANT result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0xffffec71, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, parms, &varChild);
			return result;
		}
		CString get_accHelp(VARIANT& varChild)
		{
			CString result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0xffffec70, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms, &varChild);
			return result;
		}
		long get_accHelpTopic(BSTR * pszHelpFile, VARIANT& varChild)
		{
			long result;
			static BYTE parms[] = VTS_PBSTR VTS_VARIANT ;
			InvokeHelper(0xffffec6f, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms, pszHelpFile, &varChild);
			return result;
		}
		CString get_accKeyboardShortcut(VARIANT& varChild)
		{
			CString result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0xffffec6e, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms, &varChild);
			return result;
		}
		VARIANT get_accFocus()
		{
			VARIANT result;
			InvokeHelper(0xffffec6d, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		VARIANT get_accSelection()
		{
			VARIANT result;
			InvokeHelper(0xffffec6c, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		CString get_accDefaultAction(VARIANT& varChild)
		{
			CString result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0xffffec6b, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms, &varChild);
			return result;
		}
		void accSelect(long flagsSelect, VARIANT& varChild)
		{
			static BYTE parms[] = VTS_I4 VTS_VARIANT ;
			InvokeHelper(0xffffec6a, DISPATCH_METHOD, VT_EMPTY, NULL, parms, flagsSelect, &varChild);
		}
		void accLocation(long * pxLeft, long * pyTop, long * pcxWidth, long * pcyHeight, VARIANT& varChild)
		{
			static BYTE parms[] = VTS_PI4 VTS_PI4 VTS_PI4 VTS_PI4 VTS_VARIANT ;
			InvokeHelper(0xffffec69, DISPATCH_METHOD, VT_EMPTY, NULL, parms, pxLeft, pyTop, pcxWidth, pcyHeight, &varChild);
		}
		VARIANT accNavigate(long navDir, VARIANT& varStart)
		{
			VARIANT result;
			static BYTE parms[] = VTS_I4 VTS_VARIANT ;
			InvokeHelper(0xffffec68, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms, navDir, &varStart);
			return result;
		}
		VARIANT accHitTest(long xLeft, long yTop)
		{
			VARIANT result;
			static BYTE parms[] = VTS_I4 VTS_I4 ;
			InvokeHelper(0xffffec67, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms, xLeft, yTop);
			return result;
		}
		void accDoDefaultAction(VARIANT& varChild)
		{
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0xffffec66, DISPATCH_METHOD, VT_EMPTY, NULL, parms, &varChild);
		}
		void put_accName(VARIANT& varChild, LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_VARIANT VTS_BSTR ;
			InvokeHelper(0xffffec75, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, &varChild, newValue);
		}
		void put_accValue(VARIANT& varChild, LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_VARIANT VTS_BSTR ;
			InvokeHelper(0xffffec74, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, &varChild, newValue);
		}
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60030000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60030001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		BOOL get_BuiltIn()
		{
			BOOL result;
			InvokeHelper(0x60040000, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		CString get_Context()
		{
			CString result;
			InvokeHelper(0x60040001, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_Context(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x60040001, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		LPDISPATCH get_Controls()
		{
			LPDISPATCH result;
			InvokeHelper(0x60040003, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		void Delete()
		{
			InvokeHelper(0x60040004, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		BOOL get_Enabled()
		{
			BOOL result;
			InvokeHelper(0x60040005, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_Enabled(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x60040005, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		LPDISPATCH FindControl(VARIANT& Type, VARIANT& Id, VARIANT& Tag, VARIANT& Visible, VARIANT& Recursive)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT ;
			InvokeHelper(0x60040007, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, &Type, &Id, &Tag, &Visible, &Recursive);
			return result;
		}
		long get_Height()
		{
			long result;
			InvokeHelper(0x60040008, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_Height(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60040008, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_Index()
		{
			long result;
			InvokeHelper(0x6004000a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		long get_InstanceId()
		{
			long result;
			InvokeHelper(0x6004000b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		long get_Left()
		{
			long result;
			InvokeHelper(0x6004000c, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_Left(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x6004000c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_Name()
		{
			CString result;
			InvokeHelper(0x6004000e, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_Name(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x6004000e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_NameLocal()
		{
			CString result;
			InvokeHelper(0x60040010, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_NameLocal(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x60040010, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x60040012, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Position()
		{
			long result;
			InvokeHelper(0x60040013, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_Position(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60040013, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_RowIndex()
		{
			long result;
			InvokeHelper(0x60040015, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_RowIndex(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60040015, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_Protection()
		{
			long result;
			InvokeHelper(0x60040017, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_Protection(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60040017, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		void Reset()
		{
			InvokeHelper(0x60040019, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void ShowPopup(VARIANT& x, VARIANT& y)
		{
			static BYTE parms[] = VTS_VARIANT VTS_VARIANT ;
			InvokeHelper(0x6004001a, DISPATCH_METHOD, VT_EMPTY, NULL, parms, &x, &y);
		}
		long get_Top()
		{
			long result;
			InvokeHelper(0x6004001b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_Top(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x6004001b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_Type()
		{
			long result;
			InvokeHelper(0x6004001d, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		BOOL get_Visible()
		{
			BOOL result;
			InvokeHelper(0x6004001e, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_Visible(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x6004001e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_Width()
		{
			long result;
			InvokeHelper(0x60040020, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_Width(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60040020, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_AdaptiveMenu()
		{
			BOOL result;
			InvokeHelper(0x60040022, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_AdaptiveMenu(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x60040022, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_Id()
		{
			long result;
			InvokeHelper(0x60040024, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		VARIANT get_InstanceIdPtr()
		{
			VARIANT result;
			InvokeHelper(0x60040025, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
	};

	// _CommandBarActiveX ��װ��
	class _CommandBarActiveX : public COleDispatchDriver
	{
	public:
		_CommandBarActiveX(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		_CommandBarActiveX(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		_CommandBarActiveX(const _CommandBarActiveX& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// _CommandBarActiveX ����
	public:
		LPDISPATCH get_accParent()
		{
			LPDISPATCH result;
			InvokeHelper(0xffffec78, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_accChildCount()
		{
			long result;
			InvokeHelper(0xffffec77, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_accChild(VARIANT& varChild)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0xffffec76, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, &varChild);
			return result;
		}
		CString get_accName(VARIANT& varChild)
		{
			CString result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0xffffec75, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms, &varChild);
			return result;
		}
		CString get_accValue(VARIANT& varChild)
		{
			CString result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0xffffec74, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms, &varChild);
			return result;
		}
		CString get_accDescription(VARIANT& varChild)
		{
			CString result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0xffffec73, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms, &varChild);
			return result;
		}
		VARIANT get_accRole(VARIANT& varChild)
		{
			VARIANT result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0xffffec72, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, parms, &varChild);
			return result;
		}
		VARIANT get_accState(VARIANT& varChild)
		{
			VARIANT result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0xffffec71, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, parms, &varChild);
			return result;
		}
		CString get_accHelp(VARIANT& varChild)
		{
			CString result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0xffffec70, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms, &varChild);
			return result;
		}
		long get_accHelpTopic(BSTR * pszHelpFile, VARIANT& varChild)
		{
			long result;
			static BYTE parms[] = VTS_PBSTR VTS_VARIANT ;
			InvokeHelper(0xffffec6f, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms, pszHelpFile, &varChild);
			return result;
		}
		CString get_accKeyboardShortcut(VARIANT& varChild)
		{
			CString result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0xffffec6e, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms, &varChild);
			return result;
		}
		VARIANT get_accFocus()
		{
			VARIANT result;
			InvokeHelper(0xffffec6d, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		VARIANT get_accSelection()
		{
			VARIANT result;
			InvokeHelper(0xffffec6c, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		CString get_accDefaultAction(VARIANT& varChild)
		{
			CString result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0xffffec6b, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms, &varChild);
			return result;
		}
		void accSelect(long flagsSelect, VARIANT& varChild)
		{
			static BYTE parms[] = VTS_I4 VTS_VARIANT ;
			InvokeHelper(0xffffec6a, DISPATCH_METHOD, VT_EMPTY, NULL, parms, flagsSelect, &varChild);
		}
		void accLocation(long * pxLeft, long * pyTop, long * pcxWidth, long * pcyHeight, VARIANT& varChild)
		{
			static BYTE parms[] = VTS_PI4 VTS_PI4 VTS_PI4 VTS_PI4 VTS_VARIANT ;
			InvokeHelper(0xffffec69, DISPATCH_METHOD, VT_EMPTY, NULL, parms, pxLeft, pyTop, pcxWidth, pcyHeight, &varChild);
		}
		VARIANT accNavigate(long navDir, VARIANT& varStart)
		{
			VARIANT result;
			static BYTE parms[] = VTS_I4 VTS_VARIANT ;
			InvokeHelper(0xffffec68, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms, navDir, &varStart);
			return result;
		}
		VARIANT accHitTest(long xLeft, long yTop)
		{
			VARIANT result;
			static BYTE parms[] = VTS_I4 VTS_I4 ;
			InvokeHelper(0xffffec67, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms, xLeft, yTop);
			return result;
		}
		void accDoDefaultAction(VARIANT& varChild)
		{
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0xffffec66, DISPATCH_METHOD, VT_EMPTY, NULL, parms, &varChild);
		}
		void put_accName(VARIANT& varChild, LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_VARIANT VTS_BSTR ;
			InvokeHelper(0xffffec75, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, &varChild, newValue);
		}
		void put_accValue(VARIANT& varChild, LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_VARIANT VTS_BSTR ;
			InvokeHelper(0xffffec74, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, &varChild, newValue);
		}
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60030000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60030001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		BOOL get_BeginGroup()
		{
			BOOL result;
			InvokeHelper(0x60040000, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_BeginGroup(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x60040000, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_BuiltIn()
		{
			BOOL result;
			InvokeHelper(0x60040002, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		CString get_Caption()
		{
			CString result;
			InvokeHelper(0x60040003, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_Caption(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x60040003, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		LPDISPATCH get_Control()
		{
			LPDISPATCH result;
			InvokeHelper(0x60040005, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH Copy(VARIANT& Bar, VARIANT& Before)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_VARIANT VTS_VARIANT ;
			InvokeHelper(0x60040006, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, &Bar, &Before);
			return result;
		}
		void Delete(VARIANT& Temporary)
		{
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x60040007, DISPATCH_METHOD, VT_EMPTY, NULL, parms, &Temporary);
		}
		CString get_DescriptionText()
		{
			CString result;
			InvokeHelper(0x60040008, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_DescriptionText(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x60040008, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_Enabled()
		{
			BOOL result;
			InvokeHelper(0x6004000a, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_Enabled(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x6004000a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		void Execute()
		{
			InvokeHelper(0x6004000c, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		long get_Height()
		{
			long result;
			InvokeHelper(0x6004000d, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_Height(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x6004000d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_HelpContextId()
		{
			long result;
			InvokeHelper(0x6004000f, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_HelpContextId(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x6004000f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_HelpFile()
		{
			CString result;
			InvokeHelper(0x60040011, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_HelpFile(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x60040011, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_Id()
		{
			long result;
			InvokeHelper(0x60040013, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		long get_Index()
		{
			long result;
			InvokeHelper(0x60040014, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		long get_InstanceId()
		{
			long result;
			InvokeHelper(0x60040015, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH Move(VARIANT& Bar, VARIANT& Before)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_VARIANT VTS_VARIANT ;
			InvokeHelper(0x60040016, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, &Bar, &Before);
			return result;
		}
		long get_Left()
		{
			long result;
			InvokeHelper(0x60040017, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		long get_OLEUsage()
		{
			long result;
			InvokeHelper(0x60040018, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_OLEUsage(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60040018, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_OnAction()
		{
			CString result;
			InvokeHelper(0x6004001a, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_OnAction(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x6004001a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x6004001c, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		CString get_Parameter()
		{
			CString result;
			InvokeHelper(0x6004001d, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_Parameter(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x6004001d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_Priority()
		{
			long result;
			InvokeHelper(0x6004001f, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_Priority(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x6004001f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		void Reset()
		{
			InvokeHelper(0x60040021, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void SetFocus()
		{
			InvokeHelper(0x60040022, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		CString get_Tag()
		{
			CString result;
			InvokeHelper(0x60040023, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_Tag(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x60040023, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_TooltipText()
		{
			CString result;
			InvokeHelper(0x60040025, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_TooltipText(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x60040025, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_Top()
		{
			long result;
			InvokeHelper(0x60040027, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		long get_Type()
		{
			long result;
			InvokeHelper(0x60040028, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		BOOL get_Visible()
		{
			BOOL result;
			InvokeHelper(0x60040029, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_Visible(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x60040029, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_Width()
		{
			long result;
			InvokeHelper(0x6004002b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_Width(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x6004002b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_IsPriorityDropped()
		{
			BOOL result;
			InvokeHelper(0x6004002d, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void Reserved1()
		{
			InvokeHelper(0x6004002e, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void Reserved2()
		{
			InvokeHelper(0x6004002f, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void Reserved3()
		{
			InvokeHelper(0x60040030, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void Reserved4()
		{
			InvokeHelper(0x60040031, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void Reserved5()
		{
			InvokeHelper(0x60040032, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void Reserved6()
		{
			InvokeHelper(0x60040033, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void Reserved7()
		{
			InvokeHelper(0x60040034, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		CString get_ControlCLSID()
		{
			CString result;
			InvokeHelper(0x60050000, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_ControlCLSID(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x60050000, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		LPUNKNOWN get_QueryControlInterface(LPCTSTR bstrIid)
		{
			LPUNKNOWN result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x60050002, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, parms, bstrIid);
			return result;
		}
		void SetInnerObjectFactory(LPUNKNOWN pUnk)
		{
			static BYTE parms[] = VTS_UNKNOWN ;
			InvokeHelper(0x60050003, DISPATCH_METHOD, VT_EMPTY, NULL, parms, pUnk);
		}
		void EnsureControl()
		{
			InvokeHelper(0x60050004, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void put_InitWith(LPUNKNOWN newValue)
		{
			static BYTE parms[] = VTS_UNKNOWN ;
			InvokeHelper(0x60050005, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		VARIANT get_InstanceIdPtr()
		{
			VARIANT result;
			InvokeHelper(0x60050006, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
	};

	// _CommandBarButton ��װ��
	class _CommandBarButton : public COleDispatchDriver
	{
	public:
		_CommandBarButton(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		_CommandBarButton(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		_CommandBarButton(const _CommandBarButton& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// _CommandBarButton ����
	public:
		LPDISPATCH get_accParent()
		{
			LPDISPATCH result;
			InvokeHelper(0xffffec78, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_accChildCount()
		{
			long result;
			InvokeHelper(0xffffec77, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_accChild(VARIANT& varChild)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0xffffec76, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, &varChild);
			return result;
		}
		CString get_accName(VARIANT& varChild)
		{
			CString result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0xffffec75, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms, &varChild);
			return result;
		}
		CString get_accValue(VARIANT& varChild)
		{
			CString result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0xffffec74, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms, &varChild);
			return result;
		}
		CString get_accDescription(VARIANT& varChild)
		{
			CString result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0xffffec73, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms, &varChild);
			return result;
		}
		VARIANT get_accRole(VARIANT& varChild)
		{
			VARIANT result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0xffffec72, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, parms, &varChild);
			return result;
		}
		VARIANT get_accState(VARIANT& varChild)
		{
			VARIANT result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0xffffec71, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, parms, &varChild);
			return result;
		}
		CString get_accHelp(VARIANT& varChild)
		{
			CString result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0xffffec70, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms, &varChild);
			return result;
		}
		long get_accHelpTopic(BSTR * pszHelpFile, VARIANT& varChild)
		{
			long result;
			static BYTE parms[] = VTS_PBSTR VTS_VARIANT ;
			InvokeHelper(0xffffec6f, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms, pszHelpFile, &varChild);
			return result;
		}
		CString get_accKeyboardShortcut(VARIANT& varChild)
		{
			CString result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0xffffec6e, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms, &varChild);
			return result;
		}
		VARIANT get_accFocus()
		{
			VARIANT result;
			InvokeHelper(0xffffec6d, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		VARIANT get_accSelection()
		{
			VARIANT result;
			InvokeHelper(0xffffec6c, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		CString get_accDefaultAction(VARIANT& varChild)
		{
			CString result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0xffffec6b, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms, &varChild);
			return result;
		}
		void accSelect(long flagsSelect, VARIANT& varChild)
		{
			static BYTE parms[] = VTS_I4 VTS_VARIANT ;
			InvokeHelper(0xffffec6a, DISPATCH_METHOD, VT_EMPTY, NULL, parms, flagsSelect, &varChild);
		}
		void accLocation(long * pxLeft, long * pyTop, long * pcxWidth, long * pcyHeight, VARIANT& varChild)
		{
			static BYTE parms[] = VTS_PI4 VTS_PI4 VTS_PI4 VTS_PI4 VTS_VARIANT ;
			InvokeHelper(0xffffec69, DISPATCH_METHOD, VT_EMPTY, NULL, parms, pxLeft, pyTop, pcxWidth, pcyHeight, &varChild);
		}
		VARIANT accNavigate(long navDir, VARIANT& varStart)
		{
			VARIANT result;
			static BYTE parms[] = VTS_I4 VTS_VARIANT ;
			InvokeHelper(0xffffec68, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms, navDir, &varStart);
			return result;
		}
		VARIANT accHitTest(long xLeft, long yTop)
		{
			VARIANT result;
			static BYTE parms[] = VTS_I4 VTS_I4 ;
			InvokeHelper(0xffffec67, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms, xLeft, yTop);
			return result;
		}
		void accDoDefaultAction(VARIANT& varChild)
		{
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0xffffec66, DISPATCH_METHOD, VT_EMPTY, NULL, parms, &varChild);
		}
		void put_accName(VARIANT& varChild, LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_VARIANT VTS_BSTR ;
			InvokeHelper(0xffffec75, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, &varChild, newValue);
		}
		void put_accValue(VARIANT& varChild, LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_VARIANT VTS_BSTR ;
			InvokeHelper(0xffffec74, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, &varChild, newValue);
		}
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60030000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60030001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		BOOL get_BeginGroup()
		{
			BOOL result;
			InvokeHelper(0x60040000, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_BeginGroup(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x60040000, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_BuiltIn()
		{
			BOOL result;
			InvokeHelper(0x60040002, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		CString get_Caption()
		{
			CString result;
			InvokeHelper(0x60040003, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_Caption(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x60040003, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		LPDISPATCH get_Control()
		{
			LPDISPATCH result;
			InvokeHelper(0x60040005, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH Copy(VARIANT& Bar, VARIANT& Before)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_VARIANT VTS_VARIANT ;
			InvokeHelper(0x60040006, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, &Bar, &Before);
			return result;
		}
		void Delete(VARIANT& Temporary)
		{
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x60040007, DISPATCH_METHOD, VT_EMPTY, NULL, parms, &Temporary);
		}
		CString get_DescriptionText()
		{
			CString result;
			InvokeHelper(0x60040008, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_DescriptionText(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x60040008, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_Enabled()
		{
			BOOL result;
			InvokeHelper(0x6004000a, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_Enabled(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x6004000a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		void Execute()
		{
			InvokeHelper(0x6004000c, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		long get_Height()
		{
			long result;
			InvokeHelper(0x6004000d, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_Height(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x6004000d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_HelpContextId()
		{
			long result;
			InvokeHelper(0x6004000f, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_HelpContextId(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x6004000f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_HelpFile()
		{
			CString result;
			InvokeHelper(0x60040011, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_HelpFile(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x60040011, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_Id()
		{
			long result;
			InvokeHelper(0x60040013, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		long get_Index()
		{
			long result;
			InvokeHelper(0x60040014, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		long get_InstanceId()
		{
			long result;
			InvokeHelper(0x60040015, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH Move(VARIANT& Bar, VARIANT& Before)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_VARIANT VTS_VARIANT ;
			InvokeHelper(0x60040016, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, &Bar, &Before);
			return result;
		}
		long get_Left()
		{
			long result;
			InvokeHelper(0x60040017, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		long get_OLEUsage()
		{
			long result;
			InvokeHelper(0x60040018, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_OLEUsage(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60040018, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_OnAction()
		{
			CString result;
			InvokeHelper(0x6004001a, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_OnAction(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x6004001a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x6004001c, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		CString get_Parameter()
		{
			CString result;
			InvokeHelper(0x6004001d, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_Parameter(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x6004001d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_Priority()
		{
			long result;
			InvokeHelper(0x6004001f, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_Priority(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x6004001f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		void Reset()
		{
			InvokeHelper(0x60040021, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void SetFocus()
		{
			InvokeHelper(0x60040022, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		CString get_Tag()
		{
			CString result;
			InvokeHelper(0x60040023, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_Tag(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x60040023, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_TooltipText()
		{
			CString result;
			InvokeHelper(0x60040025, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_TooltipText(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x60040025, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_Top()
		{
			long result;
			InvokeHelper(0x60040027, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		long get_Type()
		{
			long result;
			InvokeHelper(0x60040028, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		BOOL get_Visible()
		{
			BOOL result;
			InvokeHelper(0x60040029, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_Visible(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x60040029, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_Width()
		{
			long result;
			InvokeHelper(0x6004002b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_Width(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x6004002b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_IsPriorityDropped()
		{
			BOOL result;
			InvokeHelper(0x6004002d, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void Reserved1()
		{
			InvokeHelper(0x6004002e, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void Reserved2()
		{
			InvokeHelper(0x6004002f, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void Reserved3()
		{
			InvokeHelper(0x60040030, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void Reserved4()
		{
			InvokeHelper(0x60040031, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void Reserved5()
		{
			InvokeHelper(0x60040032, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void Reserved6()
		{
			InvokeHelper(0x60040033, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void Reserved7()
		{
			InvokeHelper(0x60040034, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		BOOL get_BuiltInFace()
		{
			BOOL result;
			InvokeHelper(0x60050000, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_BuiltInFace(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x60050000, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		void CopyFace()
		{
			InvokeHelper(0x60050002, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		long get_FaceId()
		{
			long result;
			InvokeHelper(0x60050003, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_FaceId(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60050003, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		void PasteFace()
		{
			InvokeHelper(0x60050005, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		CString get_ShortcutText()
		{
			CString result;
			InvokeHelper(0x60050006, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_ShortcutText(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x60050006, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_State()
		{
			long result;
			InvokeHelper(0x60050008, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_State(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60050008, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_Style()
		{
			long result;
			InvokeHelper(0x6005000a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_Style(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x6005000a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_HyperlinkType()
		{
			long result;
			InvokeHelper(0x6005000c, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_HyperlinkType(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x6005000c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		LPDISPATCH get_Picture()
		{
			LPDISPATCH result;
			InvokeHelper(0x6005000e, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		void put_Picture(LPDISPATCH newValue)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x6005000e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		LPDISPATCH get_Mask()
		{
			LPDISPATCH result;
			InvokeHelper(0x60050010, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		void put_Mask(LPDISPATCH newValue)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x60050010, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		VARIANT get_InstanceIdPtr()
		{
			VARIANT result;
			InvokeHelper(0x60050012, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
	};

	// _CommandBarButtonEvents ��װ��
	class _CommandBarButtonEvents : public COleDispatchDriver
	{
	public:
		_CommandBarButtonEvents(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		_CommandBarButtonEvents(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		_CommandBarButtonEvents(const _CommandBarButtonEvents& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// _CommandBarButtonEvents ����
	public:
		void Click(LPDISPATCH Ctrl, BOOL * CancelDefault)
		{
			static BYTE parms[] = VTS_DISPATCH VTS_PBOOL ;
			InvokeHelper(0x1, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Ctrl, CancelDefault);
		}
	};

	// _CommandBarComboBox ��װ��
	class _CommandBarComboBox : public COleDispatchDriver
	{
	public:
		_CommandBarComboBox(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		_CommandBarComboBox(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		_CommandBarComboBox(const _CommandBarComboBox& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// _CommandBarComboBox ����
	public:
		LPDISPATCH get_accParent()
		{
			LPDISPATCH result;
			InvokeHelper(0xffffec78, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_accChildCount()
		{
			long result;
			InvokeHelper(0xffffec77, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_accChild(VARIANT& varChild)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0xffffec76, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, &varChild);
			return result;
		}
		CString get_accName(VARIANT& varChild)
		{
			CString result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0xffffec75, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms, &varChild);
			return result;
		}
		CString get_accValue(VARIANT& varChild)
		{
			CString result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0xffffec74, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms, &varChild);
			return result;
		}
		CString get_accDescription(VARIANT& varChild)
		{
			CString result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0xffffec73, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms, &varChild);
			return result;
		}
		VARIANT get_accRole(VARIANT& varChild)
		{
			VARIANT result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0xffffec72, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, parms, &varChild);
			return result;
		}
		VARIANT get_accState(VARIANT& varChild)
		{
			VARIANT result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0xffffec71, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, parms, &varChild);
			return result;
		}
		CString get_accHelp(VARIANT& varChild)
		{
			CString result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0xffffec70, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms, &varChild);
			return result;
		}
		long get_accHelpTopic(BSTR * pszHelpFile, VARIANT& varChild)
		{
			long result;
			static BYTE parms[] = VTS_PBSTR VTS_VARIANT ;
			InvokeHelper(0xffffec6f, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms, pszHelpFile, &varChild);
			return result;
		}
		CString get_accKeyboardShortcut(VARIANT& varChild)
		{
			CString result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0xffffec6e, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms, &varChild);
			return result;
		}
		VARIANT get_accFocus()
		{
			VARIANT result;
			InvokeHelper(0xffffec6d, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		VARIANT get_accSelection()
		{
			VARIANT result;
			InvokeHelper(0xffffec6c, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		CString get_accDefaultAction(VARIANT& varChild)
		{
			CString result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0xffffec6b, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms, &varChild);
			return result;
		}
		void accSelect(long flagsSelect, VARIANT& varChild)
		{
			static BYTE parms[] = VTS_I4 VTS_VARIANT ;
			InvokeHelper(0xffffec6a, DISPATCH_METHOD, VT_EMPTY, NULL, parms, flagsSelect, &varChild);
		}
		void accLocation(long * pxLeft, long * pyTop, long * pcxWidth, long * pcyHeight, VARIANT& varChild)
		{
			static BYTE parms[] = VTS_PI4 VTS_PI4 VTS_PI4 VTS_PI4 VTS_VARIANT ;
			InvokeHelper(0xffffec69, DISPATCH_METHOD, VT_EMPTY, NULL, parms, pxLeft, pyTop, pcxWidth, pcyHeight, &varChild);
		}
		VARIANT accNavigate(long navDir, VARIANT& varStart)
		{
			VARIANT result;
			static BYTE parms[] = VTS_I4 VTS_VARIANT ;
			InvokeHelper(0xffffec68, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms, navDir, &varStart);
			return result;
		}
		VARIANT accHitTest(long xLeft, long yTop)
		{
			VARIANT result;
			static BYTE parms[] = VTS_I4 VTS_I4 ;
			InvokeHelper(0xffffec67, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms, xLeft, yTop);
			return result;
		}
		void accDoDefaultAction(VARIANT& varChild)
		{
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0xffffec66, DISPATCH_METHOD, VT_EMPTY, NULL, parms, &varChild);
		}
		void put_accName(VARIANT& varChild, LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_VARIANT VTS_BSTR ;
			InvokeHelper(0xffffec75, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, &varChild, newValue);
		}
		void put_accValue(VARIANT& varChild, LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_VARIANT VTS_BSTR ;
			InvokeHelper(0xffffec74, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, &varChild, newValue);
		}
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60030000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60030001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		BOOL get_BeginGroup()
		{
			BOOL result;
			InvokeHelper(0x60040000, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_BeginGroup(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x60040000, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_BuiltIn()
		{
			BOOL result;
			InvokeHelper(0x60040002, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		CString get_Caption()
		{
			CString result;
			InvokeHelper(0x60040003, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_Caption(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x60040003, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		LPDISPATCH get_Control()
		{
			LPDISPATCH result;
			InvokeHelper(0x60040005, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH Copy(VARIANT& Bar, VARIANT& Before)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_VARIANT VTS_VARIANT ;
			InvokeHelper(0x60040006, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, &Bar, &Before);
			return result;
		}
		void Delete(VARIANT& Temporary)
		{
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x60040007, DISPATCH_METHOD, VT_EMPTY, NULL, parms, &Temporary);
		}
		CString get_DescriptionText()
		{
			CString result;
			InvokeHelper(0x60040008, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_DescriptionText(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x60040008, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_Enabled()
		{
			BOOL result;
			InvokeHelper(0x6004000a, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_Enabled(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x6004000a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		void Execute()
		{
			InvokeHelper(0x6004000c, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		long get_Height()
		{
			long result;
			InvokeHelper(0x6004000d, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_Height(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x6004000d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_HelpContextId()
		{
			long result;
			InvokeHelper(0x6004000f, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_HelpContextId(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x6004000f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_HelpFile()
		{
			CString result;
			InvokeHelper(0x60040011, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_HelpFile(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x60040011, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_Id()
		{
			long result;
			InvokeHelper(0x60040013, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		long get_Index()
		{
			long result;
			InvokeHelper(0x60040014, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		long get_InstanceId()
		{
			long result;
			InvokeHelper(0x60040015, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH Move(VARIANT& Bar, VARIANT& Before)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_VARIANT VTS_VARIANT ;
			InvokeHelper(0x60040016, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, &Bar, &Before);
			return result;
		}
		long get_Left()
		{
			long result;
			InvokeHelper(0x60040017, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		long get_OLEUsage()
		{
			long result;
			InvokeHelper(0x60040018, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_OLEUsage(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60040018, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_OnAction()
		{
			CString result;
			InvokeHelper(0x6004001a, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_OnAction(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x6004001a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x6004001c, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		CString get_Parameter()
		{
			CString result;
			InvokeHelper(0x6004001d, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_Parameter(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x6004001d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_Priority()
		{
			long result;
			InvokeHelper(0x6004001f, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_Priority(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x6004001f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		void Reset()
		{
			InvokeHelper(0x60040021, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void SetFocus()
		{
			InvokeHelper(0x60040022, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		CString get_Tag()
		{
			CString result;
			InvokeHelper(0x60040023, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_Tag(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x60040023, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_TooltipText()
		{
			CString result;
			InvokeHelper(0x60040025, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_TooltipText(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x60040025, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_Top()
		{
			long result;
			InvokeHelper(0x60040027, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		long get_Type()
		{
			long result;
			InvokeHelper(0x60040028, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		BOOL get_Visible()
		{
			BOOL result;
			InvokeHelper(0x60040029, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_Visible(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x60040029, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_Width()
		{
			long result;
			InvokeHelper(0x6004002b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_Width(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x6004002b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_IsPriorityDropped()
		{
			BOOL result;
			InvokeHelper(0x6004002d, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void Reserved1()
		{
			InvokeHelper(0x6004002e, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void Reserved2()
		{
			InvokeHelper(0x6004002f, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void Reserved3()
		{
			InvokeHelper(0x60040030, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void Reserved4()
		{
			InvokeHelper(0x60040031, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void Reserved5()
		{
			InvokeHelper(0x60040032, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void Reserved6()
		{
			InvokeHelper(0x60040033, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void Reserved7()
		{
			InvokeHelper(0x60040034, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void AddItem(LPCTSTR Text, VARIANT& Index)
		{
			static BYTE parms[] = VTS_BSTR VTS_VARIANT ;
			InvokeHelper(0x60050000, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Text, &Index);
		}
		void Clear()
		{
			InvokeHelper(0x60050001, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		long get_DropDownLines()
		{
			long result;
			InvokeHelper(0x60050002, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_DropDownLines(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60050002, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_DropDownWidth()
		{
			long result;
			InvokeHelper(0x60050004, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_DropDownWidth(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60050004, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_List(long Index)
		{
			CString result;
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60050006, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms, Index);
			return result;
		}
		void put_List(long Index, LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_I4 VTS_BSTR ;
			InvokeHelper(0x60050006, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, Index, newValue);
		}
		long get_ListCount()
		{
			long result;
			InvokeHelper(0x60050008, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		long get_ListHeaderCount()
		{
			long result;
			InvokeHelper(0x60050009, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_ListHeaderCount(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60050009, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_ListIndex()
		{
			long result;
			InvokeHelper(0x6005000b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_ListIndex(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x6005000b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		void RemoveItem(long Index)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x6005000d, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Index);
		}
		long get_Style()
		{
			long result;
			InvokeHelper(0x6005000e, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_Style(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x6005000e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_Text()
		{
			CString result;
			InvokeHelper(0x60050010, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_Text(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x60050010, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		VARIANT get_InstanceIdPtr()
		{
			VARIANT result;
			InvokeHelper(0x60050012, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
	};

	// _CommandBarComboBoxEvents ��װ��
	class _CommandBarComboBoxEvents : public COleDispatchDriver
	{
	public:
		_CommandBarComboBoxEvents(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		_CommandBarComboBoxEvents(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		_CommandBarComboBoxEvents(const _CommandBarComboBoxEvents& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// _CommandBarComboBoxEvents ����
	public:
		void Change(LPDISPATCH Ctrl)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x1, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Ctrl);
		}
	};

	// CommandBarControl ��װ��
	class CommandBarControl : public COleDispatchDriver
	{
	public:
		CommandBarControl(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		CommandBarControl(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CommandBarControl(const CommandBarControl& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// CommandBarControl ����
	public:
		LPDISPATCH get_accParent()
		{
			LPDISPATCH result;
			InvokeHelper(0xffffec78, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_accChildCount()
		{
			long result;
			InvokeHelper(0xffffec77, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_accChild(VARIANT& varChild)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0xffffec76, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, &varChild);
			return result;
		}
		CString get_accName(VARIANT& varChild)
		{
			CString result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0xffffec75, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms, &varChild);
			return result;
		}
		CString get_accValue(VARIANT& varChild)
		{
			CString result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0xffffec74, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms, &varChild);
			return result;
		}
		CString get_accDescription(VARIANT& varChild)
		{
			CString result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0xffffec73, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms, &varChild);
			return result;
		}
		VARIANT get_accRole(VARIANT& varChild)
		{
			VARIANT result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0xffffec72, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, parms, &varChild);
			return result;
		}
		VARIANT get_accState(VARIANT& varChild)
		{
			VARIANT result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0xffffec71, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, parms, &varChild);
			return result;
		}
		CString get_accHelp(VARIANT& varChild)
		{
			CString result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0xffffec70, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms, &varChild);
			return result;
		}
		long get_accHelpTopic(BSTR * pszHelpFile, VARIANT& varChild)
		{
			long result;
			static BYTE parms[] = VTS_PBSTR VTS_VARIANT ;
			InvokeHelper(0xffffec6f, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms, pszHelpFile, &varChild);
			return result;
		}
		CString get_accKeyboardShortcut(VARIANT& varChild)
		{
			CString result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0xffffec6e, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms, &varChild);
			return result;
		}
		VARIANT get_accFocus()
		{
			VARIANT result;
			InvokeHelper(0xffffec6d, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		VARIANT get_accSelection()
		{
			VARIANT result;
			InvokeHelper(0xffffec6c, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		CString get_accDefaultAction(VARIANT& varChild)
		{
			CString result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0xffffec6b, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms, &varChild);
			return result;
		}
		void accSelect(long flagsSelect, VARIANT& varChild)
		{
			static BYTE parms[] = VTS_I4 VTS_VARIANT ;
			InvokeHelper(0xffffec6a, DISPATCH_METHOD, VT_EMPTY, NULL, parms, flagsSelect, &varChild);
		}
		void accLocation(long * pxLeft, long * pyTop, long * pcxWidth, long * pcyHeight, VARIANT& varChild)
		{
			static BYTE parms[] = VTS_PI4 VTS_PI4 VTS_PI4 VTS_PI4 VTS_VARIANT ;
			InvokeHelper(0xffffec69, DISPATCH_METHOD, VT_EMPTY, NULL, parms, pxLeft, pyTop, pcxWidth, pcyHeight, &varChild);
		}
		VARIANT accNavigate(long navDir, VARIANT& varStart)
		{
			VARIANT result;
			static BYTE parms[] = VTS_I4 VTS_VARIANT ;
			InvokeHelper(0xffffec68, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms, navDir, &varStart);
			return result;
		}
		VARIANT accHitTest(long xLeft, long yTop)
		{
			VARIANT result;
			static BYTE parms[] = VTS_I4 VTS_I4 ;
			InvokeHelper(0xffffec67, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms, xLeft, yTop);
			return result;
		}
		void accDoDefaultAction(VARIANT& varChild)
		{
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0xffffec66, DISPATCH_METHOD, VT_EMPTY, NULL, parms, &varChild);
		}
		void put_accName(VARIANT& varChild, LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_VARIANT VTS_BSTR ;
			InvokeHelper(0xffffec75, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, &varChild, newValue);
		}
		void put_accValue(VARIANT& varChild, LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_VARIANT VTS_BSTR ;
			InvokeHelper(0xffffec74, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, &varChild, newValue);
		}
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60030000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60030001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		BOOL get_BeginGroup()
		{
			BOOL result;
			InvokeHelper(0x60040000, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_BeginGroup(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x60040000, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_BuiltIn()
		{
			BOOL result;
			InvokeHelper(0x60040002, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		CString get_Caption()
		{
			CString result;
			InvokeHelper(0x60040003, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_Caption(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x60040003, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		LPDISPATCH get_Control()
		{
			LPDISPATCH result;
			InvokeHelper(0x60040005, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH Copy(VARIANT& Bar, VARIANT& Before)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_VARIANT VTS_VARIANT ;
			InvokeHelper(0x60040006, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, &Bar, &Before);
			return result;
		}
		void Delete(VARIANT& Temporary)
		{
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x60040007, DISPATCH_METHOD, VT_EMPTY, NULL, parms, &Temporary);
		}
		CString get_DescriptionText()
		{
			CString result;
			InvokeHelper(0x60040008, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_DescriptionText(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x60040008, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_Enabled()
		{
			BOOL result;
			InvokeHelper(0x6004000a, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_Enabled(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x6004000a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		void Execute()
		{
			InvokeHelper(0x6004000c, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		long get_Height()
		{
			long result;
			InvokeHelper(0x6004000d, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_Height(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x6004000d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_HelpContextId()
		{
			long result;
			InvokeHelper(0x6004000f, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_HelpContextId(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x6004000f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_HelpFile()
		{
			CString result;
			InvokeHelper(0x60040011, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_HelpFile(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x60040011, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_Id()
		{
			long result;
			InvokeHelper(0x60040013, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		long get_Index()
		{
			long result;
			InvokeHelper(0x60040014, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		long get_InstanceId()
		{
			long result;
			InvokeHelper(0x60040015, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH Move(VARIANT& Bar, VARIANT& Before)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_VARIANT VTS_VARIANT ;
			InvokeHelper(0x60040016, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, &Bar, &Before);
			return result;
		}
		long get_Left()
		{
			long result;
			InvokeHelper(0x60040017, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		long get_OLEUsage()
		{
			long result;
			InvokeHelper(0x60040018, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_OLEUsage(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60040018, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_OnAction()
		{
			CString result;
			InvokeHelper(0x6004001a, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_OnAction(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x6004001a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x6004001c, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		CString get_Parameter()
		{
			CString result;
			InvokeHelper(0x6004001d, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_Parameter(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x6004001d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_Priority()
		{
			long result;
			InvokeHelper(0x6004001f, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_Priority(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x6004001f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		void Reset()
		{
			InvokeHelper(0x60040021, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void SetFocus()
		{
			InvokeHelper(0x60040022, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		CString get_Tag()
		{
			CString result;
			InvokeHelper(0x60040023, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_Tag(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x60040023, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_TooltipText()
		{
			CString result;
			InvokeHelper(0x60040025, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_TooltipText(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x60040025, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_Top()
		{
			long result;
			InvokeHelper(0x60040027, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		long get_Type()
		{
			long result;
			InvokeHelper(0x60040028, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		BOOL get_Visible()
		{
			BOOL result;
			InvokeHelper(0x60040029, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_Visible(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x60040029, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_Width()
		{
			long result;
			InvokeHelper(0x6004002b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_Width(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x6004002b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_IsPriorityDropped()
		{
			BOOL result;
			InvokeHelper(0x6004002d, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void Reserved1()
		{
			InvokeHelper(0x6004002e, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void Reserved2()
		{
			InvokeHelper(0x6004002f, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void Reserved3()
		{
			InvokeHelper(0x60040030, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void Reserved4()
		{
			InvokeHelper(0x60040031, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void Reserved5()
		{
			InvokeHelper(0x60040032, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void Reserved6()
		{
			InvokeHelper(0x60040033, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void Reserved7()
		{
			InvokeHelper(0x60040034, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
	};

	// CommandBarControls ��װ��
	class CommandBarControls : public COleDispatchDriver
	{
	public:
		CommandBarControls(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		CommandBarControls(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CommandBarControls(const CommandBarControls& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// CommandBarControls ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH Add(VARIANT& Type, VARIANT& Id, VARIANT& Parameter, VARIANT& Before, VARIANT& Temporary)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT ;
			InvokeHelper(0x60030000, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, &Type, &Id, &Parameter, &Before, &Temporary);
			return result;
		}
		long get_Count()
		{
			long result;
			InvokeHelper(0x60030001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Item(VARIANT& Index)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, &Index);
			return result;
		}
		LPUNKNOWN get__NewEnum()
		{
			LPUNKNOWN result;
			InvokeHelper(0xfffffffc, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x60030004, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
	};

	// CommandBarPopup ��װ��
	class CommandBarPopup : public COleDispatchDriver
	{
	public:
		CommandBarPopup(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		CommandBarPopup(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CommandBarPopup(const CommandBarPopup& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// CommandBarPopup ����
	public:
		LPDISPATCH get_accParent()
		{
			LPDISPATCH result;
			InvokeHelper(0xffffec78, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_accChildCount()
		{
			long result;
			InvokeHelper(0xffffec77, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_accChild(VARIANT& varChild)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0xffffec76, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, &varChild);
			return result;
		}
		CString get_accName(VARIANT& varChild)
		{
			CString result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0xffffec75, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms, &varChild);
			return result;
		}
		CString get_accValue(VARIANT& varChild)
		{
			CString result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0xffffec74, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms, &varChild);
			return result;
		}
		CString get_accDescription(VARIANT& varChild)
		{
			CString result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0xffffec73, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms, &varChild);
			return result;
		}
		VARIANT get_accRole(VARIANT& varChild)
		{
			VARIANT result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0xffffec72, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, parms, &varChild);
			return result;
		}
		VARIANT get_accState(VARIANT& varChild)
		{
			VARIANT result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0xffffec71, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, parms, &varChild);
			return result;
		}
		CString get_accHelp(VARIANT& varChild)
		{
			CString result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0xffffec70, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms, &varChild);
			return result;
		}
		long get_accHelpTopic(BSTR * pszHelpFile, VARIANT& varChild)
		{
			long result;
			static BYTE parms[] = VTS_PBSTR VTS_VARIANT ;
			InvokeHelper(0xffffec6f, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms, pszHelpFile, &varChild);
			return result;
		}
		CString get_accKeyboardShortcut(VARIANT& varChild)
		{
			CString result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0xffffec6e, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms, &varChild);
			return result;
		}
		VARIANT get_accFocus()
		{
			VARIANT result;
			InvokeHelper(0xffffec6d, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		VARIANT get_accSelection()
		{
			VARIANT result;
			InvokeHelper(0xffffec6c, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		CString get_accDefaultAction(VARIANT& varChild)
		{
			CString result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0xffffec6b, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms, &varChild);
			return result;
		}
		void accSelect(long flagsSelect, VARIANT& varChild)
		{
			static BYTE parms[] = VTS_I4 VTS_VARIANT ;
			InvokeHelper(0xffffec6a, DISPATCH_METHOD, VT_EMPTY, NULL, parms, flagsSelect, &varChild);
		}
		void accLocation(long * pxLeft, long * pyTop, long * pcxWidth, long * pcyHeight, VARIANT& varChild)
		{
			static BYTE parms[] = VTS_PI4 VTS_PI4 VTS_PI4 VTS_PI4 VTS_VARIANT ;
			InvokeHelper(0xffffec69, DISPATCH_METHOD, VT_EMPTY, NULL, parms, pxLeft, pyTop, pcxWidth, pcyHeight, &varChild);
		}
		VARIANT accNavigate(long navDir, VARIANT& varStart)
		{
			VARIANT result;
			static BYTE parms[] = VTS_I4 VTS_VARIANT ;
			InvokeHelper(0xffffec68, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms, navDir, &varStart);
			return result;
		}
		VARIANT accHitTest(long xLeft, long yTop)
		{
			VARIANT result;
			static BYTE parms[] = VTS_I4 VTS_I4 ;
			InvokeHelper(0xffffec67, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms, xLeft, yTop);
			return result;
		}
		void accDoDefaultAction(VARIANT& varChild)
		{
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0xffffec66, DISPATCH_METHOD, VT_EMPTY, NULL, parms, &varChild);
		}
		void put_accName(VARIANT& varChild, LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_VARIANT VTS_BSTR ;
			InvokeHelper(0xffffec75, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, &varChild, newValue);
		}
		void put_accValue(VARIANT& varChild, LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_VARIANT VTS_BSTR ;
			InvokeHelper(0xffffec74, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, &varChild, newValue);
		}
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60030000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60030001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		BOOL get_BeginGroup()
		{
			BOOL result;
			InvokeHelper(0x60040000, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_BeginGroup(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x60040000, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_BuiltIn()
		{
			BOOL result;
			InvokeHelper(0x60040002, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		CString get_Caption()
		{
			CString result;
			InvokeHelper(0x60040003, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_Caption(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x60040003, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		LPDISPATCH get_Control()
		{
			LPDISPATCH result;
			InvokeHelper(0x60040005, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH Copy(VARIANT& Bar, VARIANT& Before)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_VARIANT VTS_VARIANT ;
			InvokeHelper(0x60040006, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, &Bar, &Before);
			return result;
		}
		void Delete(VARIANT& Temporary)
		{
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x60040007, DISPATCH_METHOD, VT_EMPTY, NULL, parms, &Temporary);
		}
		CString get_DescriptionText()
		{
			CString result;
			InvokeHelper(0x60040008, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_DescriptionText(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x60040008, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_Enabled()
		{
			BOOL result;
			InvokeHelper(0x6004000a, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_Enabled(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x6004000a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		void Execute()
		{
			InvokeHelper(0x6004000c, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		long get_Height()
		{
			long result;
			InvokeHelper(0x6004000d, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_Height(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x6004000d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_HelpContextId()
		{
			long result;
			InvokeHelper(0x6004000f, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_HelpContextId(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x6004000f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_HelpFile()
		{
			CString result;
			InvokeHelper(0x60040011, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_HelpFile(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x60040011, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_Id()
		{
			long result;
			InvokeHelper(0x60040013, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		long get_Index()
		{
			long result;
			InvokeHelper(0x60040014, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		long get_InstanceId()
		{
			long result;
			InvokeHelper(0x60040015, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH Move(VARIANT& Bar, VARIANT& Before)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_VARIANT VTS_VARIANT ;
			InvokeHelper(0x60040016, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, &Bar, &Before);
			return result;
		}
		long get_Left()
		{
			long result;
			InvokeHelper(0x60040017, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		long get_OLEUsage()
		{
			long result;
			InvokeHelper(0x60040018, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_OLEUsage(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60040018, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_OnAction()
		{
			CString result;
			InvokeHelper(0x6004001a, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_OnAction(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x6004001a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x6004001c, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		CString get_Parameter()
		{
			CString result;
			InvokeHelper(0x6004001d, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_Parameter(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x6004001d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_Priority()
		{
			long result;
			InvokeHelper(0x6004001f, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_Priority(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x6004001f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		void Reset()
		{
			InvokeHelper(0x60040021, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void SetFocus()
		{
			InvokeHelper(0x60040022, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		CString get_Tag()
		{
			CString result;
			InvokeHelper(0x60040023, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_Tag(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x60040023, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_TooltipText()
		{
			CString result;
			InvokeHelper(0x60040025, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_TooltipText(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x60040025, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_Top()
		{
			long result;
			InvokeHelper(0x60040027, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		long get_Type()
		{
			long result;
			InvokeHelper(0x60040028, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		BOOL get_Visible()
		{
			BOOL result;
			InvokeHelper(0x60040029, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_Visible(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x60040029, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_Width()
		{
			long result;
			InvokeHelper(0x6004002b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_Width(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x6004002b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_IsPriorityDropped()
		{
			BOOL result;
			InvokeHelper(0x6004002d, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void Reserved1()
		{
			InvokeHelper(0x6004002e, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void Reserved2()
		{
			InvokeHelper(0x6004002f, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void Reserved3()
		{
			InvokeHelper(0x60040030, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void Reserved4()
		{
			InvokeHelper(0x60040031, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void Reserved5()
		{
			InvokeHelper(0x60040032, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void Reserved6()
		{
			InvokeHelper(0x60040033, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void Reserved7()
		{
			InvokeHelper(0x60040034, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		LPDISPATCH get_CommandBar()
		{
			LPDISPATCH result;
			InvokeHelper(0x60050000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Controls()
		{
			LPDISPATCH result;
			InvokeHelper(0x60050001, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_OLEMenuGroup()
		{
			long result;
			InvokeHelper(0x60050002, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_OLEMenuGroup(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60050002, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		VARIANT get_InstanceIdPtr()
		{
			VARIANT result;
			InvokeHelper(0x60050004, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
	};

	// _CommandBars ��װ��
	class _CommandBars : public COleDispatchDriver
	{
	public:
		_CommandBars(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		_CommandBars(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		_CommandBars(const _CommandBars& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// _CommandBars ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_ActionControl()
		{
			LPDISPATCH result;
			InvokeHelper(0x60030000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_ActiveMenuBar()
		{
			LPDISPATCH result;
			InvokeHelper(0x60030001, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH Add(VARIANT& Name, VARIANT& Position, VARIANT& MenuBar, VARIANT& Temporary)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT ;
			InvokeHelper(0x60030002, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, &Name, &Position, &MenuBar, &Temporary);
			return result;
		}
		long get_Count()
		{
			long result;
			InvokeHelper(0x60030003, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		BOOL get_DisplayTooltips()
		{
			BOOL result;
			InvokeHelper(0x60030004, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_DisplayTooltips(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x60030004, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_DisplayKeysInTooltips()
		{
			BOOL result;
			InvokeHelper(0x60030006, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_DisplayKeysInTooltips(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x60030006, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		LPDISPATCH FindControl(VARIANT& Type, VARIANT& Id, VARIANT& Tag, VARIANT& Visible)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT ;
			InvokeHelper(0x60030008, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, &Type, &Id, &Tag, &Visible);
			return result;
		}
		LPDISPATCH get_Item(VARIANT& Index)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, &Index);
			return result;
		}
		BOOL get_LargeButtons()
		{
			BOOL result;
			InvokeHelper(0x6003000a, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_LargeButtons(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x6003000a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_MenuAnimationStyle()
		{
			long result;
			InvokeHelper(0x6003000c, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_MenuAnimationStyle(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x6003000c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		LPUNKNOWN get__NewEnum()
		{
			LPUNKNOWN result;
			InvokeHelper(0xfffffffc, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x6003000f, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		void ReleaseFocus()
		{
			InvokeHelper(0x60030010, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		long get_IdsString(long ids, BSTR * pbstrName)
		{
			long result;
			static BYTE parms[] = VTS_I4 VTS_PBSTR ;
			InvokeHelper(0x60030011, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms, ids, pbstrName);
			return result;
		}
		long get_TmcGetName(long tmc, BSTR * pbstrName)
		{
			long result;
			static BYTE parms[] = VTS_I4 VTS_PBSTR ;
			InvokeHelper(0x60030012, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms, tmc, pbstrName);
			return result;
		}
		BOOL get_AdaptiveMenus()
		{
			BOOL result;
			InvokeHelper(0x60030013, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_AdaptiveMenus(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x60030013, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		LPDISPATCH FindControls(VARIANT& Type, VARIANT& Id, VARIANT& Tag, VARIANT& Visible)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT ;
			InvokeHelper(0x60030015, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, &Type, &Id, &Tag, &Visible);
			return result;
		}
		LPDISPATCH AddEx(VARIANT& TbidOrName, VARIANT& Position, VARIANT& MenuBar, VARIANT& Temporary, VARIANT& TbtrProtection)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT ;
			InvokeHelper(0x60030016, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, &TbidOrName, &Position, &MenuBar, &Temporary, &TbtrProtection);
			return result;
		}
		BOOL get_DisplayFonts()
		{
			BOOL result;
			InvokeHelper(0x60030017, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_DisplayFonts(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x60030017, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_DisableCustomize()
		{
			BOOL result;
			InvokeHelper(0x60030019, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_DisableCustomize(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x60030019, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_DisableAskAQuestionDropdown()
		{
			BOOL result;
			InvokeHelper(0x6003001b, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_DisableAskAQuestionDropdown(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x6003001b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		void ExecuteMso(LPCTSTR idMso)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x6003001d, DISPATCH_METHOD, VT_EMPTY, NULL, parms, idMso);
		}
		BOOL GetEnabledMso(LPCTSTR idMso)
		{
			BOOL result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x6003001e, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, idMso);
			return result;
		}
		BOOL GetVisibleMso(LPCTSTR idMso)
		{
			BOOL result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x6003001f, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, idMso);
			return result;
		}
		BOOL GetPressedMso(LPCTSTR idMso)
		{
			BOOL result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x60030020, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, idMso);
			return result;
		}
		CString GetLabelMso(LPCTSTR idMso)
		{
			CString result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x60030021, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, idMso);
			return result;
		}
		CString GetScreentipMso(LPCTSTR idMso)
		{
			CString result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x60030022, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, idMso);
			return result;
		}
		CString GetSupertipMso(LPCTSTR idMso)
		{
			CString result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x60030023, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, idMso);
			return result;
		}
		LPDISPATCH GetImageMso(LPCTSTR idMso, long Width, long Height)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_BSTR VTS_I4 VTS_I4 ;
			InvokeHelper(0x60030024, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, idMso, Width, Height);
			return result;
		}
		void CommitRenderingTransaction(long hwnd)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60030025, DISPATCH_METHOD, VT_EMPTY, NULL, parms, hwnd);
		}
	};

	// _CommandBarsEvents ��װ��
	class _CommandBarsEvents : public COleDispatchDriver
	{
	public:
		_CommandBarsEvents(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		_CommandBarsEvents(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		_CommandBarsEvents(const _CommandBarsEvents& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// _CommandBarsEvents ����
	public:
		void OnUpdate()
		{
			InvokeHelper(0x1, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
	};

	// ConnectorFormat ��װ��
	class ConnectorFormat : public COleDispatchDriver
	{
	public:
		ConnectorFormat(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		ConnectorFormat(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		ConnectorFormat(const ConnectorFormat& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// ConnectorFormat ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		void BeginConnect(LPDISPATCH ConnectedShape, long ConnectionSite)
		{
			static BYTE parms[] = VTS_DISPATCH VTS_I4 ;
			InvokeHelper(0xa, DISPATCH_METHOD, VT_EMPTY, NULL, parms, ConnectedShape, ConnectionSite);
		}
		void BeginDisconnect()
		{
			InvokeHelper(0xb, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void EndConnect(LPDISPATCH ConnectedShape, long ConnectionSite)
		{
			static BYTE parms[] = VTS_DISPATCH VTS_I4 ;
			InvokeHelper(0xc, DISPATCH_METHOD, VT_EMPTY, NULL, parms, ConnectedShape, ConnectionSite);
		}
		void EndDisconnect()
		{
			InvokeHelper(0xd, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		long get_BeginConnected()
		{
			long result;
			InvokeHelper(0x64, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_BeginConnectedShape()
		{
			LPDISPATCH result;
			InvokeHelper(0x65, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_BeginConnectionSite()
		{
			long result;
			InvokeHelper(0x66, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		long get_EndConnected()
		{
			long result;
			InvokeHelper(0x67, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_EndConnectedShape()
		{
			LPDISPATCH result;
			InvokeHelper(0x68, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_EndConnectionSite()
		{
			long result;
			InvokeHelper(0x69, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		long get_Type()
		{
			long result;
			InvokeHelper(0x6a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_Type(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x6a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
	};

	// ContactCard ��װ��
	class ContactCard : public COleDispatchDriver
	{
	public:
		ContactCard(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		ContactCard(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		ContactCard(const ContactCard& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// ContactCard ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void Close()
		{
			InvokeHelper(0x1, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void Show(long CardStyle, long RectangleLeft, long RectangleRight, long RectangleTop, long RectangleBottom, long HorizontalPosition, BOOL ShowWithDelay)
		{
			static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_BOOL ;
			InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, parms, CardStyle, RectangleLeft, RectangleRight, RectangleTop, RectangleBottom, HorizontalPosition, ShowWithDelay);
		}
	};

	// Crop ��װ��
	class Crop : public COleDispatchDriver
	{
	public:
		Crop(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		Crop(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		Crop(const Crop& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// Crop ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		float get_PictureOffsetX()
		{
			float result;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
			return result;
		}
		void put_PictureOffsetX(float newValue)
		{
			static BYTE parms[] = VTS_R4 ;
			InvokeHelper(0x0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		float get_PictureOffsetY()
		{
			float result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
			return result;
		}
		void put_PictureOffsetY(float newValue)
		{
			static BYTE parms[] = VTS_R4 ;
			InvokeHelper(0x1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		float get_PictureWidth()
		{
			float result;
			InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
			return result;
		}
		void put_PictureWidth(float newValue)
		{
			static BYTE parms[] = VTS_R4 ;
			InvokeHelper(0x2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		float get_PictureHeight()
		{
			float result;
			InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
			return result;
		}
		void put_PictureHeight(float newValue)
		{
			static BYTE parms[] = VTS_R4 ;
			InvokeHelper(0x3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		float get_ShapeLeft()
		{
			float result;
			InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
			return result;
		}
		void put_ShapeLeft(float newValue)
		{
			static BYTE parms[] = VTS_R4 ;
			InvokeHelper(0x5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		float get_ShapeTop()
		{
			float result;
			InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
			return result;
		}
		void put_ShapeTop(float newValue)
		{
			static BYTE parms[] = VTS_R4 ;
			InvokeHelper(0x6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		float get_ShapeWidth()
		{
			float result;
			InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
			return result;
		}
		void put_ShapeWidth(float newValue)
		{
			static BYTE parms[] = VTS_R4 ;
			InvokeHelper(0x7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		float get_ShapeHeight()
		{
			float result;
			InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
			return result;
		}
		void put_ShapeHeight(float newValue)
		{
			static BYTE parms[] = VTS_R4 ;
			InvokeHelper(0x8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
	};

	// _CustomTaskPane ��װ��
	class _CustomTaskPane : public COleDispatchDriver
	{
	public:
		_CustomTaskPane(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		_CustomTaskPane(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		_CustomTaskPane(const _CustomTaskPane& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// _CustomTaskPane ����
	public:
		CString get_Title()
		{
			CString result;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Window()
		{
			LPDISPATCH result;
			InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		BOOL get_Visible()
		{
			BOOL result;
			InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_Visible(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		LPDISPATCH get_ContentControl()
		{
			LPDISPATCH result;
			InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Height()
		{
			long result;
			InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_Height(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_Width()
		{
			long result;
			InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_Width(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_DockPosition()
		{
			long result;
			InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_DockPosition(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_DockPositionRestrict()
		{
			long result;
			InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_DockPositionRestrict(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		void Delete()
		{
			InvokeHelper(0x9, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
	};

	// _CustomTaskPaneEvents ��װ��
	class _CustomTaskPaneEvents : public COleDispatchDriver
	{
	public:
		_CustomTaskPaneEvents(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		_CustomTaskPaneEvents(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		_CustomTaskPaneEvents(const _CustomTaskPaneEvents& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// _CustomTaskPaneEvents ����
	public:
		void VisibleStateChange(LPDISPATCH CustomTaskPaneInst)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x1, DISPATCH_METHOD, VT_EMPTY, NULL, parms, CustomTaskPaneInst);
		}
		void DockPositionStateChange(LPDISPATCH CustomTaskPaneInst)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, parms, CustomTaskPaneInst);
		}
	};
	
	// CustomTaskPaneEvents ��װ��
	class CustomTaskPaneEvents : public COleDispatchDriver
	{
	public:
		CustomTaskPaneEvents(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		CustomTaskPaneEvents(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CustomTaskPaneEvents(const CustomTaskPaneEvents& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// CustomTaskPaneEvents ����
	public:
		void VisibleStateChange(LPDISPATCH CustomTaskPaneInst)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x1, DISPATCH_METHOD, VT_EMPTY, NULL, parms, CustomTaskPaneInst);
		}
		void DockPositionStateChange(LPDISPATCH CustomTaskPaneInst)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, parms, CustomTaskPaneInst);
		}
	};

	// CustomXMLNode ��װ��
	class CustomXMLNode : public COleDispatchDriver
	{
	public:
		CustomXMLNode(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		CustomXMLNode(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CustomXMLNode(const CustomXMLNode& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// CustomXMLNode ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x60030000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Attributes()
		{
			LPDISPATCH result;
			InvokeHelper(0x60030001, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		CString get_BaseName()
		{
			CString result;
			InvokeHelper(0x60030002, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_ChildNodes()
		{
			LPDISPATCH result;
			InvokeHelper(0x60030003, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_FirstChild()
		{
			LPDISPATCH result;
			InvokeHelper(0x60030004, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_LastChild()
		{
			LPDISPATCH result;
			InvokeHelper(0x60030005, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		CString get_NamespaceURI()
		{
			CString result;
			InvokeHelper(0x60030006, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_NextSibling()
		{
			LPDISPATCH result;
			InvokeHelper(0x60030007, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_NodeType()
		{
			long result;
			InvokeHelper(0x60030008, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		CString get_NodeValue()
		{
			CString result;
			InvokeHelper(0x60030009, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_NodeValue(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x60030009, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		LPDISPATCH get_OwnerDocument()
		{
			LPDISPATCH result;
			InvokeHelper(0x6003000b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_OwnerPart()
		{
			LPDISPATCH result;
			InvokeHelper(0x6003000c, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_PreviousSibling()
		{
			LPDISPATCH result;
			InvokeHelper(0x6003000d, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_ParentNode()
		{
			LPDISPATCH result;
			InvokeHelper(0x6003000e, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		CString get_Text()
		{
			CString result;
			InvokeHelper(0x6003000f, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_Text(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x6003000f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_XPath()
		{
			CString result;
			InvokeHelper(0x60030011, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		CString get_XML()
		{
			CString result;
			InvokeHelper(0x60030012, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void AppendChildNode(LPCTSTR Name, LPCTSTR NamespaceURI, long NodeType, LPCTSTR NodeValue)
		{
			static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_I4 VTS_BSTR ;
			InvokeHelper(0x60030013, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Name, NamespaceURI, NodeType, NodeValue);
		}
		void AppendChildSubtree(LPCTSTR XML)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x60030014, DISPATCH_METHOD, VT_EMPTY, NULL, parms, XML);
		}
		void Delete()
		{
			InvokeHelper(0x60030015, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		BOOL HasChildNodes()
		{
			BOOL result;
			InvokeHelper(0x60030016, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void InsertNodeBefore(LPCTSTR Name, LPCTSTR NamespaceURI, long NodeType, LPCTSTR NodeValue, LPDISPATCH NextSibling)
		{
			static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_I4 VTS_BSTR VTS_DISPATCH ;
			InvokeHelper(0x60030017, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Name, NamespaceURI, NodeType, NodeValue, NextSibling);
		}
		void InsertSubtreeBefore(LPCTSTR XML, LPDISPATCH NextSibling)
		{
			static BYTE parms[] = VTS_BSTR VTS_DISPATCH ;
			InvokeHelper(0x60030018, DISPATCH_METHOD, VT_EMPTY, NULL, parms, XML, NextSibling);
		}
		void RemoveChild(LPDISPATCH Child)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x60030019, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Child);
		}
		void ReplaceChildNode(LPDISPATCH OldNode, LPCTSTR Name, LPCTSTR NamespaceURI, long NodeType, LPCTSTR NodeValue)
		{
			static BYTE parms[] = VTS_DISPATCH VTS_BSTR VTS_BSTR VTS_I4 VTS_BSTR ;
			InvokeHelper(0x6003001a, DISPATCH_METHOD, VT_EMPTY, NULL, parms, OldNode, Name, NamespaceURI, NodeType, NodeValue);
		}
		void ReplaceChildSubtree(LPCTSTR XML, LPDISPATCH OldNode)
		{
			static BYTE parms[] = VTS_BSTR VTS_DISPATCH ;
			InvokeHelper(0x6003001b, DISPATCH_METHOD, VT_EMPTY, NULL, parms, XML, OldNode);
		}
		LPDISPATCH SelectNodes(LPCTSTR XPath)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x6003001c, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, XPath);
			return result;
		}
		LPDISPATCH SelectSingleNode(LPCTSTR XPath)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x6003001d, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, XPath);
			return result;
		}
	};

	// CustomXMLNodes ��װ��
	class CustomXMLNodes : public COleDispatchDriver
	{
	public:
		CustomXMLNodes(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		CustomXMLNodes(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CustomXMLNodes(const CustomXMLNodes& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// CustomXMLNodes ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x60030000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Count()
		{
			long result;
			InvokeHelper(0x60030001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Item(long Index)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, Index);
			return result;
		}
		LPUNKNOWN get__NewEnum()
		{
			LPUNKNOWN result;
			InvokeHelper(0xfffffffc, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
			return result;
		}
	};

	// _CustomXMLPart ��װ��
	class _CustomXMLPart : public COleDispatchDriver
	{
	public:
		_CustomXMLPart(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		_CustomXMLPart(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		_CustomXMLPart(const _CustomXMLPart& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// _CustomXMLPart ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x60030000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_DocumentElement()
		{
			LPDISPATCH result;
			InvokeHelper(0x60030001, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		CString get_Id()
		{
			CString result;
			InvokeHelper(0x60030002, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		CString get_NamespaceURI()
		{
			CString result;
			InvokeHelper(0x60030003, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_SchemaCollection()
		{
			LPDISPATCH result;
			InvokeHelper(0x60030004, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		void put_SchemaCollection(LPDISPATCH newValue)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x60030004, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		LPDISPATCH get_NamespaceManager()
		{
			LPDISPATCH result;
			InvokeHelper(0x60030006, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		CString get_XML()
		{
			CString result;
			InvokeHelper(0x60030007, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void AddNode(LPDISPATCH Parent, LPCTSTR Name, LPCTSTR NamespaceURI, LPDISPATCH NextSibling, long NodeType, LPCTSTR NodeValue)
		{
			static BYTE parms[] = VTS_DISPATCH VTS_BSTR VTS_BSTR VTS_DISPATCH VTS_I4 VTS_BSTR ;
			InvokeHelper(0x60030008, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Parent, Name, NamespaceURI, NextSibling, NodeType, NodeValue);
		}
		void Delete()
		{
			InvokeHelper(0x60030009, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		BOOL Load(LPCTSTR FilePath)
		{
			BOOL result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x6003000a, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, FilePath);
			return result;
		}
		BOOL LoadXML(LPCTSTR XML)
		{
			BOOL result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x6003000b, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, XML);
			return result;
		}
		LPDISPATCH SelectNodes(LPCTSTR XPath)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x6003000c, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, XPath);
			return result;
		}
		LPDISPATCH SelectSingleNode(LPCTSTR XPath)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x6003000d, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, XPath);
			return result;
		}
		LPDISPATCH get_Errors()
		{
			LPDISPATCH result;
			InvokeHelper(0x6003000e, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		BOOL get_BuiltIn()
		{
			BOOL result;
			InvokeHelper(0x6003000f, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
	};

	// _CustomXMLPartEvents ��װ��
	class _CustomXMLPartEvents : public COleDispatchDriver
	{
	public:
		_CustomXMLPartEvents(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		_CustomXMLPartEvents(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		_CustomXMLPartEvents(const _CustomXMLPartEvents& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// _CustomXMLPartEvents ����
	public:
		void NodeAfterInsert(LPDISPATCH NewNode, BOOL InUndoRedo)
		{
			static BYTE parms[] = VTS_DISPATCH VTS_BOOL ;
			InvokeHelper(0x1, DISPATCH_METHOD, VT_EMPTY, NULL, parms, NewNode, InUndoRedo);
		}
		void NodeAfterDelete(LPDISPATCH OldNode, LPDISPATCH OldParentNode, LPDISPATCH OldNextSibling, BOOL InUndoRedo)
		{
			static BYTE parms[] = VTS_DISPATCH VTS_DISPATCH VTS_DISPATCH VTS_BOOL ;
			InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, parms, OldNode, OldParentNode, OldNextSibling, InUndoRedo);
		}
		void NodeAfterReplace(LPDISPATCH OldNode, LPDISPATCH NewNode, BOOL InUndoRedo)
		{
			static BYTE parms[] = VTS_DISPATCH VTS_DISPATCH VTS_BOOL ;
			InvokeHelper(0x3, DISPATCH_METHOD, VT_EMPTY, NULL, parms, OldNode, NewNode, InUndoRedo);
		}
	};

	// _CustomXMLParts ��װ��
	class _CustomXMLParts : public COleDispatchDriver
	{
	public:
		_CustomXMLParts(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		_CustomXMLParts(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		_CustomXMLParts(const _CustomXMLParts& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// _CustomXMLParts ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x60030000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Count()
		{
			long result;
			InvokeHelper(0x60030001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Item(VARIANT& Index)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, &Index);
			return result;
		}
		LPDISPATCH Add(LPCTSTR XML, VARIANT& SchemaCollection)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_BSTR VTS_VARIANT ;
			InvokeHelper(0x60030003, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, XML, &SchemaCollection);
			return result;
		}
		LPDISPATCH SelectByID(LPCTSTR Id)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x60030004, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, Id);
			return result;
		}
		LPDISPATCH SelectByNamespace(LPCTSTR NamespaceURI)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x60030005, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, NamespaceURI);
			return result;
		}
		LPUNKNOWN get__NewEnum()
		{
			LPUNKNOWN result;
			InvokeHelper(0xfffffffc, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
			return result;
		}
	};

	// _CustomXMLPartsEvents ��װ��
	class _CustomXMLPartsEvents : public COleDispatchDriver
	{
	public:
		_CustomXMLPartsEvents(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		_CustomXMLPartsEvents(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		_CustomXMLPartsEvents(const _CustomXMLPartsEvents& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// _CustomXMLPartsEvents ����
	public:
		void PartAfterAdd(LPDISPATCH NewPart)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x1, DISPATCH_METHOD, VT_EMPTY, NULL, parms, NewPart);
		}
		void PartBeforeDelete(LPDISPATCH OldPart)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, parms, OldPart);
		}
		void PartAfterLoad(LPDISPATCH Part)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x3, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Part);
		}
	};

	// CustomXMLPrefixMapping ��װ��
	class CustomXMLPrefixMapping : public COleDispatchDriver
	{
	public:
		CustomXMLPrefixMapping(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		CustomXMLPrefixMapping(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CustomXMLPrefixMapping(const CustomXMLPrefixMapping& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// CustomXMLPrefixMapping ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x60030000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		CString get_Prefix()
		{
			CString result;
			InvokeHelper(0x60030001, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		CString get_NamespaceURI()
		{
			CString result;
			InvokeHelper(0x60030002, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
	};

	// CustomXMLPrefixMappings ��װ��
	class CustomXMLPrefixMappings : public COleDispatchDriver
	{
	public:
		CustomXMLPrefixMappings(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		CustomXMLPrefixMappings(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CustomXMLPrefixMappings(const CustomXMLPrefixMappings& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// CustomXMLPrefixMappings ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x60030000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Count()
		{
			long result;
			InvokeHelper(0x60030001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Item(VARIANT& Index)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, &Index);
			return result;
		}
		void AddNamespace(LPCTSTR Prefix, LPCTSTR NamespaceURI)
		{
			static BYTE parms[] = VTS_BSTR VTS_BSTR ;
			InvokeHelper(0x60030003, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Prefix, NamespaceURI);
		}
		CString LookupNamespace(LPCTSTR Prefix)
		{
			CString result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x60030004, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, Prefix);
			return result;
		}
		CString LookupPrefix(LPCTSTR NamespaceURI)
		{
			CString result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x60030005, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, NamespaceURI);
			return result;
		}
		LPUNKNOWN get__NewEnum()
		{
			LPUNKNOWN result;
			InvokeHelper(0xfffffffc, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
			return result;
		}
	};

	// CustomXMLSchema ��װ��
	class CustomXMLSchema : public COleDispatchDriver
	{
	public:
		CustomXMLSchema(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		CustomXMLSchema(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CustomXMLSchema(const CustomXMLSchema& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// CustomXMLSchema ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x60030000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		CString get_Location()
		{
			CString result;
			InvokeHelper(0x60030001, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		CString get_NamespaceURI()
		{
			CString result;
			InvokeHelper(0x60030002, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void Delete()
		{
			InvokeHelper(0x60030003, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void Reload()
		{
			InvokeHelper(0x60030004, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
	};

	// _CustomXMLSchemaCollection ��װ��
	class _CustomXMLSchemaCollection : public COleDispatchDriver
	{
	public:
		_CustomXMLSchemaCollection(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		_CustomXMLSchemaCollection(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		_CustomXMLSchemaCollection(const _CustomXMLSchemaCollection& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// _CustomXMLSchemaCollection ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x60030000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Count()
		{
			long result;
			InvokeHelper(0x60030001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Item(VARIANT& Index)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, &Index);
			return result;
		}
		CString get_NamespaceURI(long Index)
		{
			CString result;
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60030003, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms, Index);
			return result;
		}
		LPDISPATCH Add(LPCTSTR NamespaceURI, LPCTSTR Alias, LPCTSTR FileName, BOOL InstallForAllUsers)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR VTS_BOOL ;
			InvokeHelper(0x60030004, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, NamespaceURI, Alias, FileName, InstallForAllUsers);
			return result;
		}
		void AddCollection(LPDISPATCH SchemaCollection)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x60030005, DISPATCH_METHOD, VT_EMPTY, NULL, parms, SchemaCollection);
		}
		BOOL Validate()
		{
			BOOL result;
			InvokeHelper(0x60030006, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		LPUNKNOWN get__NewEnum()
		{
			LPUNKNOWN result;
			InvokeHelper(0xfffffffc, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
			return result;
		}
	};

	// CustomXMLValidationError ��װ��
	class CustomXMLValidationError : public COleDispatchDriver
	{
	public:
		CustomXMLValidationError(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		CustomXMLValidationError(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CustomXMLValidationError(const CustomXMLValidationError& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// CustomXMLValidationError ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x60030000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		CString get_Name()
		{
			CString result;
			InvokeHelper(0x60030001, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Node()
		{
			LPDISPATCH result;
			InvokeHelper(0x60030002, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		CString get_Text()
		{
			CString result;
			InvokeHelper(0x60030003, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		long get_Type()
		{
			long result;
			InvokeHelper(0x60030004, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void Delete()
		{
			InvokeHelper(0x60030005, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		long get_ErrorCode()
		{
			long result;
			InvokeHelper(0x60030006, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
	};

	// CustomXMLValidationErrors ��װ��
	class CustomXMLValidationErrors : public COleDispatchDriver
	{
	public:
		CustomXMLValidationErrors(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		CustomXMLValidationErrors(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CustomXMLValidationErrors(const CustomXMLValidationErrors& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// CustomXMLValidationErrors ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x60030000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Count()
		{
			long result;
			InvokeHelper(0x60030001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Item(long Index)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, Index);
			return result;
		}
		void Add(LPDISPATCH Node, LPCTSTR ErrorName, LPCTSTR ErrorText, BOOL ClearedOnUpdate)
		{
			static BYTE parms[] = VTS_DISPATCH VTS_BSTR VTS_BSTR VTS_BOOL ;
			InvokeHelper(0x60030003, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Node, ErrorName, ErrorText, ClearedOnUpdate);
		}
		LPUNKNOWN get__NewEnum()
		{
			LPUNKNOWN result;
			InvokeHelper(0xfffffffc, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
			return result;
		}
	};

	// DiagramNode ��װ��
	class DiagramNode : public COleDispatchDriver
	{
	public:
		DiagramNode(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		DiagramNode(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		DiagramNode(const DiagramNode& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// DiagramNode ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH AddNode(long Pos, long NodeType)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I4 VTS_I4 ;
			InvokeHelper(0xa, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, Pos, NodeType);
			return result;
		}
		void Delete()
		{
			InvokeHelper(0xb, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void MoveNode(LPDISPATCH TargetNode, long Pos)
		{
			static BYTE parms[] = VTS_DISPATCH VTS_I4 ;
			InvokeHelper(0xc, DISPATCH_METHOD, VT_EMPTY, NULL, parms, TargetNode, Pos);
		}
		void ReplaceNode(LPDISPATCH TargetNode)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0xd, DISPATCH_METHOD, VT_EMPTY, NULL, parms, TargetNode);
		}
		void SwapNode(LPDISPATCH TargetNode, BOOL SwapChildren)
		{
			static BYTE parms[] = VTS_DISPATCH VTS_BOOL ;
			InvokeHelper(0xe, DISPATCH_METHOD, VT_EMPTY, NULL, parms, TargetNode, SwapChildren);
		}
		LPDISPATCH CloneNode(BOOL CopyChildren, LPDISPATCH TargetNode, long Pos)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_BOOL VTS_DISPATCH VTS_I4 ;
			InvokeHelper(0xf, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, CopyChildren, TargetNode, Pos);
			return result;
		}
		void TransferChildren(LPDISPATCH ReceivingNode)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x10, DISPATCH_METHOD, VT_EMPTY, NULL, parms, ReceivingNode);
		}
		LPDISPATCH NextNode()
		{
			LPDISPATCH result;
			InvokeHelper(0x11, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH PrevNode()
		{
			LPDISPATCH result;
			InvokeHelper(0x12, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x64, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Children()
		{
			LPDISPATCH result;
			InvokeHelper(0x65, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Shape()
		{
			LPDISPATCH result;
			InvokeHelper(0x66, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Root()
		{
			LPDISPATCH result;
			InvokeHelper(0x67, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Diagram()
		{
			LPDISPATCH result;
			InvokeHelper(0x68, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Layout()
		{
			long result;
			InvokeHelper(0x69, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_Layout(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x69, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		LPDISPATCH get_TextShape()
		{
			LPDISPATCH result;
			InvokeHelper(0x6a, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
	};

	// DiagramNodeChildren ��װ��
	class DiagramNodeChildren : public COleDispatchDriver
	{
	public:
		DiagramNodeChildren(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		DiagramNodeChildren(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		DiagramNodeChildren(const DiagramNodeChildren& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// DiagramNodeChildren ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPUNKNOWN get__NewEnum()
		{
			LPUNKNOWN result;
			InvokeHelper(0xfffffffc, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH Item(VARIANT& Index)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x0, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, &Index);
			return result;
		}
		LPDISPATCH AddNode(VARIANT& Index, long NodeType)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_VARIANT VTS_I4 ;
			InvokeHelper(0xa, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, &Index, NodeType);
			return result;
		}
		void SelectAll()
		{
			InvokeHelper(0xb, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x64, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Count()
		{
			long result;
			InvokeHelper(0x65, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_FirstChild()
		{
			LPDISPATCH result;
			InvokeHelper(0x67, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_LastChild()
		{
			LPDISPATCH result;
			InvokeHelper(0x68, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
	};

	// DiagramNodes ��װ��
	class DiagramNodes : public COleDispatchDriver
	{
	public:
		DiagramNodes(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		DiagramNodes(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		DiagramNodes(const DiagramNodes& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// DiagramNodes ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPUNKNOWN get__NewEnum()
		{
			LPUNKNOWN result;
			InvokeHelper(0xfffffffc, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH Item(VARIANT& Index)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x0, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, &Index);
			return result;
		}
		void SelectAll()
		{
			InvokeHelper(0xa, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x64, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Count()
		{
			long result;
			InvokeHelper(0x65, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
	};

	// DocumentInspector ��װ��
	class DocumentInspector : public COleDispatchDriver
	{
	public:
		DocumentInspector(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		DocumentInspector(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		DocumentInspector(const DocumentInspector& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// DocumentInspector ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		CString get_Name()
		{
			CString result;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		CString get_Description()
		{
			CString result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void Inspect(long * Status, BSTR * Results)
		{
			static BYTE parms[] = VTS_PI4 VTS_PBSTR ;
			InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Status, Results);
		}
		void Fix(long * Status, BSTR * Results)
		{
			static BYTE parms[] = VTS_PI4 VTS_PBSTR ;
			InvokeHelper(0x3, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Status, Results);
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
	};

	// DocumentInspectors ��װ��
	class DocumentInspectors : public COleDispatchDriver
	{
	public:
		DocumentInspectors(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		DocumentInspectors(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		DocumentInspectors(const DocumentInspectors& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// DocumentInspectors ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPUNKNOWN get__NewEnum()
		{
			LPUNKNOWN result;
			InvokeHelper(0xfffffffc, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Item(long Index)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, Index);
			return result;
		}
		long get_Count()
		{
			long result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
	};

	// DocumentLibraryVersion ��װ��
	class DocumentLibraryVersion : public COleDispatchDriver
	{
	public:
		DocumentLibraryVersion(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		DocumentLibraryVersion(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		DocumentLibraryVersion(const DocumentLibraryVersion& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// DocumentLibraryVersion ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		VARIANT get_Modified()
		{
			VARIANT result;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		long get_Index()
		{
			long result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		CString get_ModifiedBy()
		{
			CString result;
			InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		CString get_Comments()
		{
			CString result;
			InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void Delete()
		{
			InvokeHelper(0x5, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		LPDISPATCH Open()
		{
			LPDISPATCH result;
			InvokeHelper(0x6, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH Restore()
		{
			LPDISPATCH result;
			InvokeHelper(0x7, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
	};

	// DocumentLibraryVersions ��װ��
	class DocumentLibraryVersions : public COleDispatchDriver
	{
	public:
		DocumentLibraryVersions(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		DocumentLibraryVersions(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		DocumentLibraryVersions(const DocumentLibraryVersions& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// DocumentLibraryVersions ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Item(long lIndex)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, lIndex);
			return result;
		}
		long get_Count()
		{
			long result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		BOOL get_IsVersioningEnabled()
		{
			BOOL result;
			InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		LPUNKNOWN get__NewEnum()
		{
			LPUNKNOWN result;
			InvokeHelper(0xfffffffc, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
			return result;
		}
	};

	// EffectParameter ��װ��
	class EffectParameter : public COleDispatchDriver
	{
	public:
		EffectParameter(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		EffectParameter(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		EffectParameter(const EffectParameter& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// EffectParameter ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		CString get_Name()
		{
			CString result;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		VARIANT get_Value()
		{
			VARIANT result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		void put_Value(VARIANT& newValue)
		{
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, &newValue);
		}
	};

	// EffectParameters ��װ��
	class EffectParameters : public COleDispatchDriver
	{
	public:
		EffectParameters(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		EffectParameters(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		EffectParameters(const EffectParameters& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// EffectParameters ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Item(VARIANT& Index)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, &Index);
			return result;
		}
		long get_Count()
		{
			long result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPUNKNOWN get__NewEnum()
		{
			LPUNKNOWN result;
			InvokeHelper(0xfffffffc, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
			return result;
		}
	};

	// EncryptionProvider ��װ��
	class EncryptionProvider : public COleDispatchDriver
	{
	public:
		EncryptionProvider(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		EncryptionProvider(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		EncryptionProvider(const EncryptionProvider& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// EncryptionProvider ����
	public:
		VARIANT GetProviderDetail(long encprovdet)
		{
			VARIANT result;
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60020000, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms, encprovdet);
			return result;
		}
		long NewSession(LPUNKNOWN ParentWindow)
		{
			long result;
			static BYTE parms[] = VTS_UNKNOWN ;
			InvokeHelper(0x60020001, DISPATCH_METHOD, VT_I4, (void*)&result, parms, ParentWindow);
			return result;
		}
		long Authenticate(LPUNKNOWN ParentWindow, LPUNKNOWN EncryptionData, unsigned long * PermissionsMask)
		{
			long result;
			static BYTE parms[] = VTS_UNKNOWN VTS_UNKNOWN VTS_PUI4 ;
			InvokeHelper(0x60020002, DISPATCH_METHOD, VT_I4, (void*)&result, parms, ParentWindow, EncryptionData, PermissionsMask);
			return result;
		}
		long CloneSession(long SessionHandle)
		{
			long result;
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60020003, DISPATCH_METHOD, VT_I4, (void*)&result, parms, SessionHandle);
			return result;
		}
		void EndSession(long SessionHandle)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60020004, DISPATCH_METHOD, VT_EMPTY, NULL, parms, SessionHandle);
		}
		long Save(long SessionHandle, LPUNKNOWN EncryptionData)
		{
			long result;
			static BYTE parms[] = VTS_I4 VTS_UNKNOWN ;
			InvokeHelper(0x60020005, DISPATCH_METHOD, VT_I4, (void*)&result, parms, SessionHandle, EncryptionData);
			return result;
		}
		void EncryptStream(long SessionHandle, LPCTSTR StreamName, LPUNKNOWN UnencryptedStream, LPUNKNOWN EncryptedStream)
		{
			static BYTE parms[] = VTS_I4 VTS_BSTR VTS_UNKNOWN VTS_UNKNOWN ;
			InvokeHelper(0x60020006, DISPATCH_METHOD, VT_EMPTY, NULL, parms, SessionHandle, StreamName, UnencryptedStream, EncryptedStream);
		}
		void DecryptStream(long SessionHandle, LPCTSTR StreamName, LPUNKNOWN EncryptedStream, LPUNKNOWN UnencryptedStream)
		{
			static BYTE parms[] = VTS_I4 VTS_BSTR VTS_UNKNOWN VTS_UNKNOWN ;
			InvokeHelper(0x60020007, DISPATCH_METHOD, VT_EMPTY, NULL, parms, SessionHandle, StreamName, EncryptedStream, UnencryptedStream);
		}
		void ShowSettings(long SessionHandle, LPUNKNOWN ParentWindow, BOOL ReadOnly, BOOL * Remove)
		{
			static BYTE parms[] = VTS_I4 VTS_UNKNOWN VTS_BOOL VTS_PBOOL ;
			InvokeHelper(0x60020008, DISPATCH_METHOD, VT_EMPTY, NULL, parms, SessionHandle, ParentWindow, ReadOnly, Remove);
		}
	};

	// FileDialog ��װ��
	class FileDialog : public COleDispatchDriver
	{
	public:
		FileDialog(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		FileDialog(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		FileDialog(const FileDialog& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// FileDialog ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x60030000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Filters()
		{
			LPDISPATCH result;
			InvokeHelper(0x60030001, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_FilterIndex()
		{
			long result;
			InvokeHelper(0x60030002, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_FilterIndex(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60030002, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_Title()
		{
			CString result;
			InvokeHelper(0x60030004, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_Title(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x60030004, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_ButtonName()
		{
			CString result;
			InvokeHelper(0x60030006, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_ButtonName(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x60030006, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_AllowMultiSelect()
		{
			BOOL result;
			InvokeHelper(0x60030008, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_AllowMultiSelect(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x60030008, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_InitialView()
		{
			long result;
			InvokeHelper(0x6003000a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_InitialView(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x6003000a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_InitialFileName()
		{
			CString result;
			InvokeHelper(0x6003000c, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_InitialFileName(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x6003000c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		LPDISPATCH get_SelectedItems()
		{
			LPDISPATCH result;
			InvokeHelper(0x6003000e, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_DialogType()
		{
			long result;
			InvokeHelper(0x6003000f, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		CString get_Item()
		{
			CString result;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		long Show()
		{
			long result;
			InvokeHelper(0x60030011, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
			return result;
		}
		void Execute()
		{
			InvokeHelper(0x60030012, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
	};

	// FileDialogFilter ��װ��
	class FileDialogFilter : public COleDispatchDriver
	{
	public:
		FileDialogFilter(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		FileDialogFilter(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		FileDialogFilter(const FileDialogFilter& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// FileDialogFilter ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x60030000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		CString get_Extensions()
		{
			CString result;
			InvokeHelper(0x60030001, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		CString get_Description()
		{
			CString result;
			InvokeHelper(0x60030002, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
	};

	// FileDialogFilters ��װ��
	class FileDialogFilters : public COleDispatchDriver
	{
	public:
		FileDialogFilters(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		FileDialogFilters(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		FileDialogFilters(const FileDialogFilters& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// FileDialogFilters ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x60030000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPUNKNOWN get__NewEnum()
		{
			LPUNKNOWN result;
			InvokeHelper(0xfffffffc, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
			return result;
		}
		long get_Count()
		{
			long result;
			InvokeHelper(0x60030002, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH Item(long Index)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x0, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, Index);
			return result;
		}
		void Delete(VARIANT& filter)
		{
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x60030004, DISPATCH_METHOD, VT_EMPTY, NULL, parms, &filter);
		}
		void Clear()
		{
			InvokeHelper(0x60030005, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		LPDISPATCH Add(LPCTSTR Description, LPCTSTR Extensions, VARIANT& Position)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_VARIANT ;
			InvokeHelper(0x60030006, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, Description, Extensions, &Position);
			return result;
		}
	};

	// FileDialogSelectedItems ��װ��
	class FileDialogSelectedItems : public COleDispatchDriver
	{
	public:
		FileDialogSelectedItems(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		FileDialogSelectedItems(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		FileDialogSelectedItems(const FileDialogSelectedItems& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// FileDialogSelectedItems ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x60030000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPUNKNOWN get__NewEnum()
		{
			LPUNKNOWN result;
			InvokeHelper(0xfffffffc, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
			return result;
		}
		long get_Count()
		{
			long result;
			InvokeHelper(0x60030002, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		CString Item(long Index)
		{
			CString result;
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x0, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, Index);
			return result;
		}
	};

	// FileSearch ��װ��
	class FileSearch : public COleDispatchDriver
	{
	public:
		FileSearch(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		FileSearch(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		FileSearch(const FileSearch& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// FileSearch ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		BOOL get_SearchSubFolders()
		{
			BOOL result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_SearchSubFolders(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_MatchTextExactly()
		{
			BOOL result;
			InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_MatchTextExactly(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_MatchAllWordForms()
		{
			BOOL result;
			InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_MatchAllWordForms(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_FileName()
		{
			CString result;
			InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_FileName(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_FileType()
		{
			long result;
			InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_FileType(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_LastModified()
		{
			long result;
			InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_LastModified(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_TextOrProperty()
		{
			CString result;
			InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_TextOrProperty(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_LookIn()
		{
			CString result;
			InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_LookIn(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long Execute(long SortBy, long SortOrder, BOOL AlwaysAccurate)
		{
			long result;
			static BYTE parms[] = VTS_I4 VTS_I4 VTS_BOOL ;
			InvokeHelper(0x9, DISPATCH_METHOD, VT_I4, (void*)&result, parms, SortBy, SortOrder, AlwaysAccurate);
			return result;
		}
		void NewSearch()
		{
			InvokeHelper(0xa, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		LPDISPATCH get_FoundFiles()
		{
			LPDISPATCH result;
			InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_PropertyTests()
		{
			LPDISPATCH result;
			InvokeHelper(0xc, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_SearchScopes()
		{
			LPDISPATCH result;
			InvokeHelper(0xd, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_SearchFolders()
		{
			LPDISPATCH result;
			InvokeHelper(0xe, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_FileTypes()
		{
			LPDISPATCH result;
			InvokeHelper(0x10, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		void RefreshScopes()
		{
			InvokeHelper(0x11, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
	};

	// FileTypes ��װ��
	class FileTypes : public COleDispatchDriver
	{
	public:
		FileTypes(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		FileTypes(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		FileTypes(const FileTypes& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// FileTypes ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		long get_Item(long Index)
		{
			long result;
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms, Index);
			return result;
		}
		long get_Count()
		{
			long result;
			InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void Add(long FileType)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x3, DISPATCH_METHOD, VT_EMPTY, NULL, parms, FileType);
		}
		void Remove(long Index)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x4, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Index);
		}
		LPUNKNOWN get__NewEnum()
		{
			LPUNKNOWN result;
			InvokeHelper(0xfffffffc, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
			return result;
		}
	};

	// FillFormat ��װ��
	class FillFormat : public COleDispatchDriver
	{
	public:
		FillFormat(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		FillFormat(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		FillFormat(const FillFormat& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// FillFormat ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		void Background()
		{
			InvokeHelper(0xa, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void OneColorGradient(long Style, long Variant, float Degree)
		{
			static BYTE parms[] = VTS_I4 VTS_I4 VTS_R4 ;
			InvokeHelper(0xb, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Style, Variant, Degree);
		}
		void Patterned(long Pattern)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0xc, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Pattern);
		}
		void PresetGradient(long Style, long Variant, long PresetGradientType)
		{
			static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 ;
			InvokeHelper(0xd, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Style, Variant, PresetGradientType);
		}
		void PresetTextured(long PresetTexture)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0xe, DISPATCH_METHOD, VT_EMPTY, NULL, parms, PresetTexture);
		}
		void Solid()
		{
			InvokeHelper(0xf, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void TwoColorGradient(long Style, long Variant)
		{
			static BYTE parms[] = VTS_I4 VTS_I4 ;
			InvokeHelper(0x10, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Style, Variant);
		}
		void UserPicture(LPCTSTR PictureFile)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x11, DISPATCH_METHOD, VT_EMPTY, NULL, parms, PictureFile);
		}
		void UserTextured(LPCTSTR TextureFile)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x12, DISPATCH_METHOD, VT_EMPTY, NULL, parms, TextureFile);
		}
		LPDISPATCH get_BackColor()
		{
			LPDISPATCH result;
			InvokeHelper(0x64, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		void put_BackColor(LPDISPATCH newValue)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x64, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		LPDISPATCH get_ForeColor()
		{
			LPDISPATCH result;
			InvokeHelper(0x65, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		void put_ForeColor(LPDISPATCH newValue)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x65, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_GradientColorType()
		{
			long result;
			InvokeHelper(0x66, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		float get_GradientDegree()
		{
			float result;
			InvokeHelper(0x67, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
			return result;
		}
		long get_GradientStyle()
		{
			long result;
			InvokeHelper(0x68, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		long get_GradientVariant()
		{
			long result;
			InvokeHelper(0x69, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		long get_Pattern()
		{
			long result;
			InvokeHelper(0x6a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		long get_PresetGradientType()
		{
			long result;
			InvokeHelper(0x6b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		long get_PresetTexture()
		{
			long result;
			InvokeHelper(0x6c, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		CString get_TextureName()
		{
			CString result;
			InvokeHelper(0x6d, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		long get_TextureType()
		{
			long result;
			InvokeHelper(0x6e, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		float get_Transparency()
		{
			float result;
			InvokeHelper(0x6f, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
			return result;
		}
		void put_Transparency(float newValue)
		{
			static BYTE parms[] = VTS_R4 ;
			InvokeHelper(0x6f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_Type()
		{
			long result;
			InvokeHelper(0x70, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		long get_Visible()
		{
			long result;
			InvokeHelper(0x71, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_Visible(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x71, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		LPDISPATCH get_GradientStops()
		{
			LPDISPATCH result;
			InvokeHelper(0x72, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		float get_TextureOffsetX()
		{
			float result;
			InvokeHelper(0x73, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
			return result;
		}
		void put_TextureOffsetX(float newValue)
		{
			static BYTE parms[] = VTS_R4 ;
			InvokeHelper(0x73, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		float get_TextureOffsetY()
		{
			float result;
			InvokeHelper(0x74, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
			return result;
		}
		void put_TextureOffsetY(float newValue)
		{
			static BYTE parms[] = VTS_R4 ;
			InvokeHelper(0x74, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_TextureAlignment()
		{
			long result;
			InvokeHelper(0x75, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_TextureAlignment(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x75, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		float get_TextureHorizontalScale()
		{
			float result;
			InvokeHelper(0x76, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
			return result;
		}
		void put_TextureHorizontalScale(float newValue)
		{
			static BYTE parms[] = VTS_R4 ;
			InvokeHelper(0x76, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		float get_TextureVerticalScale()
		{
			float result;
			InvokeHelper(0x77, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
			return result;
		}
		void put_TextureVerticalScale(float newValue)
		{
			static BYTE parms[] = VTS_R4 ;
			InvokeHelper(0x77, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_TextureTile()
		{
			long result;
			InvokeHelper(0x78, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_TextureTile(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x78, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_RotateWithObject()
		{
			long result;
			InvokeHelper(0x79, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_RotateWithObject(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x79, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		LPDISPATCH get_PictureEffects()
		{
			LPDISPATCH result;
			InvokeHelper(0x7a, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		float get_GradientAngle()
		{
			float result;
			InvokeHelper(0x7b, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
			return result;
		}
		void put_GradientAngle(float newValue)
		{
			static BYTE parms[] = VTS_R4 ;
			InvokeHelper(0x7b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
	};

	// Font2 ��װ��
	class Font2 : public COleDispatchDriver
	{
	public:
		Font2(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		Font2(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		Font2(const Font2& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// Font2 ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Bold()
		{
			long result;
			InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_Bold(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_Italic()
		{
			long result;
			InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_Italic(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_Strike()
		{
			long result;
			InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_Strike(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_Caps()
		{
			long result;
			InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_Caps(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_AutorotateNumbers()
		{
			long result;
			InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_AutorotateNumbers(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		float get_BaselineOffset()
		{
			float result;
			InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
			return result;
		}
		void put_BaselineOffset(float newValue)
		{
			static BYTE parms[] = VTS_R4 ;
			InvokeHelper(0x7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		float get_Kerning()
		{
			float result;
			InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
			return result;
		}
		void put_Kerning(float newValue)
		{
			static BYTE parms[] = VTS_R4 ;
			InvokeHelper(0x8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		float get_Size()
		{
			float result;
			InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
			return result;
		}
		void put_Size(float newValue)
		{
			static BYTE parms[] = VTS_R4 ;
			InvokeHelper(0x9, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		float get_Spacing()
		{
			float result;
			InvokeHelper(0xa, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
			return result;
		}
		void put_Spacing(float newValue)
		{
			static BYTE parms[] = VTS_R4 ;
			InvokeHelper(0xa, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_UnderlineStyle()
		{
			long result;
			InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_UnderlineStyle(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0xb, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_Allcaps()
		{
			long result;
			InvokeHelper(0xc, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_Allcaps(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0xc, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_DoubleStrikeThrough()
		{
			long result;
			InvokeHelper(0xd, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_DoubleStrikeThrough(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0xd, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_Equalize()
		{
			long result;
			InvokeHelper(0xe, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_Equalize(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0xe, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		LPDISPATCH get_Fill()
		{
			LPDISPATCH result;
			InvokeHelper(0xf, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Glow()
		{
			LPDISPATCH result;
			InvokeHelper(0x10, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Reflection()
		{
			LPDISPATCH result;
			InvokeHelper(0x11, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Line()
		{
			LPDISPATCH result;
			InvokeHelper(0x12, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Shadow()
		{
			LPDISPATCH result;
			InvokeHelper(0x13, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Highlight()
		{
			LPDISPATCH result;
			InvokeHelper(0x14, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_UnderlineColor()
		{
			LPDISPATCH result;
			InvokeHelper(0x15, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Smallcaps()
		{
			long result;
			InvokeHelper(0x16, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_Smallcaps(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x16, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_SoftEdgeFormat()
		{
			long result;
			InvokeHelper(0x17, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_SoftEdgeFormat(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x17, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_StrikeThrough()
		{
			long result;
			InvokeHelper(0x18, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_StrikeThrough(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x18, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_Subscript()
		{
			long result;
			InvokeHelper(0x19, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_Subscript(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x19, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_Superscript()
		{
			long result;
			InvokeHelper(0x1a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_Superscript(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x1a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_WordArtformat()
		{
			long result;
			InvokeHelper(0x1b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_WordArtformat(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x1b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_Embeddable()
		{
			long result;
			InvokeHelper(0x1c, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		long get_Embedded()
		{
			long result;
			InvokeHelper(0x1d, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		CString get_Name()
		{
			CString result;
			InvokeHelper(0x1e, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_Name(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x1e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_NameAscii()
		{
			CString result;
			InvokeHelper(0x1f, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_NameAscii(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x1f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_NameComplexScript()
		{
			CString result;
			InvokeHelper(0x20, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_NameComplexScript(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x20, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_NameFarEast()
		{
			CString result;
			InvokeHelper(0x21, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_NameFarEast(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x21, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_NameOther()
		{
			CString result;
			InvokeHelper(0x22, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_NameOther(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x22, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
	};

	// FoundFiles ��װ��
	class FoundFiles : public COleDispatchDriver
	{
	public:
		FoundFiles(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		FoundFiles(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		FoundFiles(const FoundFiles& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// FoundFiles ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		CString get_Item(long Index)
		{
			CString result;
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms, Index);
			return result;
		}
		long get_Count()
		{
			long result;
			InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPUNKNOWN get__NewEnum()
		{
			LPUNKNOWN result;
			InvokeHelper(0xfffffffc, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
			return result;
		}
	};

	// FreeformBuilder ��װ��
	class FreeformBuilder : public COleDispatchDriver
	{
	public:
		FreeformBuilder(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		FreeformBuilder(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		FreeformBuilder(const FreeformBuilder& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// FreeformBuilder ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		void AddNodes(long SegmentType, long EditingType, float X1, float Y1, float X2, float Y2, float X3, float Y3)
		{
			static BYTE parms[] = VTS_I4 VTS_I4 VTS_R4 VTS_R4 VTS_R4 VTS_R4 VTS_R4 VTS_R4 ;
			InvokeHelper(0xa, DISPATCH_METHOD, VT_EMPTY, NULL, parms, SegmentType, EditingType, X1, Y1, X2, Y2, X3, Y3);
		}
		LPDISPATCH ConvertToShape()
		{
			LPDISPATCH result;
			InvokeHelper(0xb, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
	};

	// GlowFormat ��װ��
	class GlowFormat : public COleDispatchDriver
	{
	public:
		GlowFormat(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		GlowFormat(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		GlowFormat(const GlowFormat& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// GlowFormat ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		float get_Radius()
		{
			float result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
			return result;
		}
		void put_Radius(float newValue)
		{
			static BYTE parms[] = VTS_R4 ;
			InvokeHelper(0x1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		LPDISPATCH get_Color()
		{
			LPDISPATCH result;
			InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		float get_Transparency()
		{
			float result;
			InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
			return result;
		}
		void put_Transparency(float newValue)
		{
			static BYTE parms[] = VTS_R4 ;
			InvokeHelper(0x3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
	};

	// GradientStop ��װ��
	class GradientStop : public COleDispatchDriver
	{
	public:
		GradientStop(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		GradientStop(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		GradientStop(const GradientStop& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// GradientStop ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Color()
		{
			LPDISPATCH result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		float get_Position()
		{
			float result;
			InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
			return result;
		}
		void put_Position(float newValue)
		{
			static BYTE parms[] = VTS_R4 ;
			InvokeHelper(0x2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		float get_Transparency()
		{
			float result;
			InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
			return result;
		}
		void put_Transparency(float newValue)
		{
			static BYTE parms[] = VTS_R4 ;
			InvokeHelper(0x3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
	};

	// GradientStops ��װ��
	class GradientStops : public COleDispatchDriver
	{
	public:
		GradientStops(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		GradientStops(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		GradientStops(const GradientStops& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// GradientStops ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Item(long Index)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, Index);
			return result;
		}
		long get_Count()
		{
			long result;
			InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPUNKNOWN get__NewEnum()
		{
			LPUNKNOWN result;
			InvokeHelper(0xfffffffc, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
			return result;
		}
		void Delete(long Index)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0xa, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Index);
		}
		void Insert(long RGB, float Position, float Transparency, long Index)
		{
			static BYTE parms[] = VTS_I4 VTS_R4 VTS_R4 VTS_I4 ;
			InvokeHelper(0xb, DISPATCH_METHOD, VT_EMPTY, NULL, parms, RGB, Position, Transparency, Index);
		}
		void Insert2(long RGB, float Position, float Transparency, long Index, float Brightness)
		{
			static BYTE parms[] = VTS_I4 VTS_R4 VTS_R4 VTS_I4 VTS_R4 ;
			InvokeHelper(0xc, DISPATCH_METHOD, VT_EMPTY, NULL, parms, RGB, Position, Transparency, Index, Brightness);
		}
	};

	// GridLines ��װ��
	class GridLines : public COleDispatchDriver
	{
	public:
		GridLines(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		GridLines(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		GridLines(const GridLines& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// GridLines ����
	public:
		CString get_Name()
		{
			CString result;
			InvokeHelper(0x6e, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		VARIANT Select()
		{
			VARIANT result;
			InvokeHelper(0xeb, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x96, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Border()
		{
			LPDISPATCH result;
			InvokeHelper(0x80, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		VARIANT Delete()
		{
			VARIANT result;
			InvokeHelper(0x75, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Format()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020005, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x94, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x95, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
	};

	// GroupShapes ��װ��
	class GroupShapes : public COleDispatchDriver
	{
	public:
		GroupShapes(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		GroupShapes(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		GroupShapes(const GroupShapes& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// GroupShapes ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Count()
		{
			long result;
			InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH Item(VARIANT& Index)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x0, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, &Index);
			return result;
		}
		LPUNKNOWN get__NewEnum()
		{
			LPUNKNOWN result;
			InvokeHelper(0xfffffffc, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH Range(VARIANT& Index)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0xa, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, &Index);
			return result;
		}
	};

	// HTMLProject ��װ��
	class HTMLProject : public COleDispatchDriver
	{
	public:
		HTMLProject(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		HTMLProject(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		HTMLProject(const HTMLProject& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// HTMLProject ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		long get_State()
		{
			long result;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void RefreshProject(BOOL Refresh)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x1, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Refresh);
		}
		void RefreshDocument(BOOL Refresh)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Refresh);
		}
		LPDISPATCH get_HTMLProjectItems()
		{
			LPDISPATCH result;
			InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		void Open(long OpenKind)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x5, DISPATCH_METHOD, VT_EMPTY, NULL, parms, OpenKind);
		}
	};

	// HTMLProjectItem ��װ��
	class HTMLProjectItem : public COleDispatchDriver
	{
	public:
		HTMLProjectItem(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		HTMLProjectItem(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		HTMLProjectItem(const HTMLProjectItem& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// HTMLProjectItem ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		CString get_Name()
		{
			CString result;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		BOOL get_IsOpen()
		{
			BOOL result;
			InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void LoadFromFile(LPCTSTR FileName)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x5, DISPATCH_METHOD, VT_EMPTY, NULL, parms, FileName);
		}
		void Open(long OpenKind)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x6, DISPATCH_METHOD, VT_EMPTY, NULL, parms, OpenKind);
		}
		void SaveCopyAs(LPCTSTR FileName)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x7, DISPATCH_METHOD, VT_EMPTY, NULL, parms, FileName);
		}
		CString get_Text()
		{
			CString result;
			InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_Text(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0xa, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
	};

	// HTMLProjectItems ��װ��
	class HTMLProjectItems : public COleDispatchDriver
	{
	public:
		HTMLProjectItems(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		HTMLProjectItems(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		HTMLProjectItems(const HTMLProjectItems& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// HTMLProjectItems ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH Item(VARIANT * Index)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_PVARIANT ;
			InvokeHelper(0x0, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, Index);
			return result;
		}
		long get_Count()
		{
			long result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPUNKNOWN get__NewEnum()
		{
			LPUNKNOWN result;
			InvokeHelper(0xfffffffc, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
	};
	
	// IAccessible ��װ��
	class IAccessible : public COleDispatchDriver
	{
	public:
		IAccessible(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		IAccessible(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		IAccessible(const IAccessible& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// IAccessible ����
	public:
		LPDISPATCH get_accParent()
		{
			LPDISPATCH result;
			InvokeHelper(0xffffec78, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_accChildCount()
		{
			long result;
			InvokeHelper(0xffffec77, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_accChild(VARIANT& varChild)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0xffffec76, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, &varChild);
			return result;
		}
		CString get_accName(VARIANT& varChild)
		{
			CString result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0xffffec75, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms, &varChild);
			return result;
		}
		CString get_accValue(VARIANT& varChild)
		{
			CString result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0xffffec74, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms, &varChild);
			return result;
		}
		CString get_accDescription(VARIANT& varChild)
		{
			CString result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0xffffec73, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms, &varChild);
			return result;
		}
		VARIANT get_accRole(VARIANT& varChild)
		{
			VARIANT result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0xffffec72, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, parms, &varChild);
			return result;
		}
		VARIANT get_accState(VARIANT& varChild)
		{
			VARIANT result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0xffffec71, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, parms, &varChild);
			return result;
		}
		CString get_accHelp(VARIANT& varChild)
		{
			CString result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0xffffec70, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms, &varChild);
			return result;
		}
		long get_accHelpTopic(BSTR * pszHelpFile, VARIANT& varChild)
		{
			long result;
			static BYTE parms[] = VTS_PBSTR VTS_VARIANT ;
			InvokeHelper(0xffffec6f, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms, pszHelpFile, &varChild);
			return result;
		}
		CString get_accKeyboardShortcut(VARIANT& varChild)
		{
			CString result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0xffffec6e, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms, &varChild);
			return result;
		}
		VARIANT get_accFocus()
		{
			VARIANT result;
			InvokeHelper(0xffffec6d, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		VARIANT get_accSelection()
		{
			VARIANT result;
			InvokeHelper(0xffffec6c, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		CString get_accDefaultAction(VARIANT& varChild)
		{
			CString result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0xffffec6b, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms, &varChild);
			return result;
		}
		void accSelect(long flagsSelect, VARIANT& varChild)
		{
			static BYTE parms[] = VTS_I4 VTS_VARIANT ;
			InvokeHelper(0xffffec6a, DISPATCH_METHOD, VT_EMPTY, NULL, parms, flagsSelect, &varChild);
		}
		void accLocation(long * pxLeft, long * pyTop, long * pcxWidth, long * pcyHeight, VARIANT& varChild)
		{
			static BYTE parms[] = VTS_PI4 VTS_PI4 VTS_PI4 VTS_PI4 VTS_VARIANT ;
			InvokeHelper(0xffffec69, DISPATCH_METHOD, VT_EMPTY, NULL, parms, pxLeft, pyTop, pcxWidth, pcyHeight, &varChild);
		}
		VARIANT accNavigate(long navDir, VARIANT& varStart)
		{
			VARIANT result;
			static BYTE parms[] = VTS_I4 VTS_VARIANT ;
			InvokeHelper(0xffffec68, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms, navDir, &varStart);
			return result;
		}
		VARIANT accHitTest(long xLeft, long yTop)
		{
			VARIANT result;
			static BYTE parms[] = VTS_I4 VTS_I4 ;
			InvokeHelper(0xffffec67, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms, xLeft, yTop);
			return result;
		}
		void accDoDefaultAction(VARIANT& varChild)
		{
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0xffffec66, DISPATCH_METHOD, VT_EMPTY, NULL, parms, &varChild);
		}
		void put_accName(VARIANT& varChild, LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_VARIANT VTS_BSTR ;
			InvokeHelper(0xffffec75, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, &varChild, newValue);
		}
		void put_accValue(VARIANT& varChild, LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_VARIANT VTS_BSTR ;
			InvokeHelper(0xffffec74, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, &varChild, newValue);
		}
	};
	
	// IAssistance ��װ��
	class IAssistance : public COleDispatchDriver
	{
	public:
		IAssistance(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		IAssistance(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		IAssistance(const IAssistance& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// IAssistance ����
	public:
		void ShowHelp(LPCTSTR HelpId, LPCTSTR Scope)
		{
			static BYTE parms[] = VTS_BSTR VTS_BSTR ;
			InvokeHelper(0x60020000, DISPATCH_METHOD, VT_EMPTY, NULL, parms, HelpId, Scope);
		}
		void SearchHelp(LPCTSTR Query, LPCTSTR Scope)
		{
			static BYTE parms[] = VTS_BSTR VTS_BSTR ;
			InvokeHelper(0x60020001, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Query, Scope);
		}
		void SetDefaultContext(LPCTSTR HelpId)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x60020002, DISPATCH_METHOD, VT_EMPTY, NULL, parms, HelpId);
		}
		void ClearDefaultContext(LPCTSTR HelpId)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x60020003, DISPATCH_METHOD, VT_EMPTY, NULL, parms, HelpId);
		}
	};
	
	// IBlogExtensibility ��װ��
	class IBlogExtensibility : public COleDispatchDriver
	{
	public:
		IBlogExtensibility(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		IBlogExtensibility(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		IBlogExtensibility(const IBlogExtensibility& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// IBlogExtensibility ����
	public:
		void BlogProviderProperties(BSTR * BlogProvider, BSTR * FriendlyName, long * CategorySupport, BOOL * Padding)
		{
			static BYTE parms[] = VTS_PBSTR VTS_PBSTR VTS_PI4 VTS_PBOOL ;
			InvokeHelper(0x1, DISPATCH_METHOD, VT_EMPTY, NULL, parms, BlogProvider, FriendlyName, CategorySupport, Padding);
		}
		void SetupBlogAccount(LPCTSTR Account, long ParentWindow, LPDISPATCH Document, BOOL NewAccount, BOOL * ShowPictureUI)
		{
			static BYTE parms[] = VTS_BSTR VTS_I4 VTS_DISPATCH VTS_BOOL VTS_PBOOL ;
			InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Account, ParentWindow, Document, NewAccount, ShowPictureUI);
		}
		void GetUserBlogs(LPCTSTR Account, long ParentWindow, LPDISPATCH Document, SAFEARRAY * * BlogNames, SAFEARRAY * * BlogIDs, SAFEARRAY * * BlogURLs)
		{
			static BYTE parms[] = VTS_BSTR VTS_I4 VTS_DISPATCH VTS_UNKNOWN VTS_UNKNOWN VTS_UNKNOWN ;
			InvokeHelper(0x3, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Account, ParentWindow, Document, BlogNames, BlogIDs, BlogURLs);
		}
		void GetRecentPosts(LPCTSTR Account, long ParentWindow, LPDISPATCH Document, SAFEARRAY * * PostTitles, SAFEARRAY * * PostDates, SAFEARRAY * * PostIDs)
		{
			static BYTE parms[] = VTS_BSTR VTS_I4 VTS_DISPATCH VTS_UNKNOWN VTS_UNKNOWN VTS_UNKNOWN ;
			InvokeHelper(0x4, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Account, ParentWindow, Document, PostTitles, PostDates, PostIDs);
		}
		void Open(LPCTSTR Account, LPCTSTR PostID, long ParentWindow, BSTR * xHTML, BSTR * Title, BSTR * DatePosted, SAFEARRAY * * Categories)
		{
			static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_I4 VTS_PBSTR VTS_PBSTR VTS_PBSTR VTS_UNKNOWN ;
			InvokeHelper(0x5, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Account, PostID, ParentWindow, xHTML, Title, DatePosted, Categories);
		}
		void GetCategories(LPCTSTR Account, long ParentWindow, LPDISPATCH Document, SAFEARRAY * * Categories)
		{
			static BYTE parms[] = VTS_BSTR VTS_I4 VTS_DISPATCH VTS_UNKNOWN ;
			InvokeHelper(0x8, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Account, ParentWindow, Document, Categories);
		}
	};
	
	// IBlogPictureExtensibility ��װ��
	class IBlogPictureExtensibility : public COleDispatchDriver
	{
	public:
		IBlogPictureExtensibility(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		IBlogPictureExtensibility(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		IBlogPictureExtensibility(const IBlogPictureExtensibility& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// IBlogPictureExtensibility ����
	public:
		void BlogPictureProviderProperties(BSTR * BlogPictureProvider, BSTR * FriendlyName)
		{
			static BYTE parms[] = VTS_PBSTR VTS_PBSTR ;
			InvokeHelper(0x1, DISPATCH_METHOD, VT_EMPTY, NULL, parms, BlogPictureProvider, FriendlyName);
		}
		void CreatePictureAccount(LPCTSTR Account, LPCTSTR BlogProvider, long ParentWindow, LPDISPATCH Document)
		{
			static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_I4 VTS_DISPATCH ;
			InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Account, BlogProvider, ParentWindow, Document);
		}
		void PublishPicture(LPCTSTR Account, long ParentWindow, LPDISPATCH Document, LPUNKNOWN Image, BSTR * PictureURI, long ImageType)
		{
			static BYTE parms[] = VTS_BSTR VTS_I4 VTS_DISPATCH VTS_UNKNOWN VTS_PBSTR VTS_I4 ;
			InvokeHelper(0x3, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Account, ParentWindow, Document, Image, PictureURI, ImageType);
		}
	};
	
	// ICommandBarButtonEvents ��װ��
	class ICommandBarButtonEvents : public COleDispatchDriver
	{
	public:
		ICommandBarButtonEvents(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		ICommandBarButtonEvents(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		ICommandBarButtonEvents(const ICommandBarButtonEvents& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// ICommandBarButtonEvents ����
	public:
		void Click(LPDISPATCH Ctrl, BOOL * CancelDefault)
		{
			static BYTE parms[] = VTS_DISPATCH VTS_PBOOL ;
			InvokeHelper(0x1, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Ctrl, CancelDefault);
		}
	};
	
	// ICommandBarComboBoxEvents ��װ��
	class ICommandBarComboBoxEvents : public COleDispatchDriver
	{
	public:
		ICommandBarComboBoxEvents(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		ICommandBarComboBoxEvents(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		ICommandBarComboBoxEvents(const ICommandBarComboBoxEvents& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// ICommandBarComboBoxEvents ����
	public:
		void Change(LPDISPATCH Ctrl)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x1, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Ctrl);
		}
	};
	
	// ICommandBarsEvents ��װ��
	class ICommandBarsEvents : public COleDispatchDriver
	{
	public:
		ICommandBarsEvents(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		ICommandBarsEvents(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		ICommandBarsEvents(const ICommandBarsEvents& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// ICommandBarsEvents ����
	public:
		void OnUpdate()
		{
			InvokeHelper(0x1, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
	};
	
	// ICTPFactory ��װ��
	class ICTPFactory : public COleDispatchDriver
	{
	public:
		ICTPFactory(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		ICTPFactory(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		ICTPFactory(const ICTPFactory& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// ICTPFactory ����
	public:
		LPDISPATCH CreateCTP(LPCTSTR CTPAxID, LPCTSTR CTPTitle, VARIANT& CTPParentWindow)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_VARIANT ;
			InvokeHelper(0x1, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, CTPAxID, CTPTitle, &CTPParentWindow);
			return result;
		}
	};
	
	// ICustomTaskPaneConsumer ��װ��
	class ICustomTaskPaneConsumer : public COleDispatchDriver
	{
	public:
		ICustomTaskPaneConsumer(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		ICustomTaskPaneConsumer(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		ICustomTaskPaneConsumer(const ICustomTaskPaneConsumer& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// ICustomTaskPaneConsumer ����
	public:
		void CTPFactoryAvailable(LPDISPATCH CTPFactoryInst)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x1, DISPATCH_METHOD, VT_EMPTY, NULL, parms, CTPFactoryInst);
		}
	};
	
	// ICustomXMLPartEvents ��װ��
	class ICustomXMLPartEvents : public COleDispatchDriver
	{
	public:
		ICustomXMLPartEvents(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		ICustomXMLPartEvents(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		ICustomXMLPartEvents(const ICustomXMLPartEvents& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// ICustomXMLPartEvents ����
	public:
		void NodeAfterInsert(LPDISPATCH NewNode, BOOL InUndoRedo)
		{
			static BYTE parms[] = VTS_DISPATCH VTS_BOOL ;
			InvokeHelper(0x1, DISPATCH_METHOD, VT_EMPTY, NULL, parms, NewNode, InUndoRedo);
		}
		void NodeAfterDelete(LPDISPATCH OldNode, LPDISPATCH OldParentNode, LPDISPATCH OldNextSibling, BOOL InUndoRedo)
		{
			static BYTE parms[] = VTS_DISPATCH VTS_DISPATCH VTS_DISPATCH VTS_BOOL ;
			InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, parms, OldNode, OldParentNode, OldNextSibling, InUndoRedo);
		}
		void NodeAfterReplace(LPDISPATCH OldNode, LPDISPATCH NewNode, BOOL InUndoRedo)
		{
			static BYTE parms[] = VTS_DISPATCH VTS_DISPATCH VTS_BOOL ;
			InvokeHelper(0x3, DISPATCH_METHOD, VT_EMPTY, NULL, parms, OldNode, NewNode, InUndoRedo);
		}
	};
	
	// ICustomXMLPartsEvents ��װ��
	class ICustomXMLPartsEvents : public COleDispatchDriver
	{
	public:
		ICustomXMLPartsEvents(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		ICustomXMLPartsEvents(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		ICustomXMLPartsEvents(const ICustomXMLPartsEvents& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// ICustomXMLPartsEvents ����
	public:
		void PartAfterAdd(LPDISPATCH NewPart)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x1, DISPATCH_METHOD, VT_EMPTY, NULL, parms, NewPart);
		}
		void PartBeforeDelete(LPDISPATCH OldPart)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, parms, OldPart);
		}
		void PartAfterLoad(LPDISPATCH Part)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x3, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Part);
		}
	};
	
	// IFind ��װ��
	class IFind : public COleDispatchDriver
	{
	public:
		IFind(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		IFind(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		IFind(const IFind& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// IFind ����
	public:
		CString get_SearchPath()
		{
			CString result;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		CString get_Name()
		{
			CString result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		BOOL get_SubDir()
		{
			BOOL result;
			InvokeHelper(0x60020002, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		CString get_Title()
		{
			CString result;
			InvokeHelper(0x60020003, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		CString get_Author()
		{
			CString result;
			InvokeHelper(0x60020004, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		CString get_Keywords()
		{
			CString result;
			InvokeHelper(0x60020005, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		CString get_Subject()
		{
			CString result;
			InvokeHelper(0x60020006, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		long get_Options()
		{
			long result;
			InvokeHelper(0x60020007, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		BOOL get_MatchCase()
		{
			BOOL result;
			InvokeHelper(0x60020008, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		CString get_Text()
		{
			CString result;
			InvokeHelper(0x60020009, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		BOOL get_PatternMatch()
		{
			BOOL result;
			InvokeHelper(0x6002000a, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		VARIANT get_DateSavedFrom()
		{
			VARIANT result;
			InvokeHelper(0x6002000b, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		VARIANT get_DateSavedTo()
		{
			VARIANT result;
			InvokeHelper(0x6002000c, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		CString get_SavedBy()
		{
			CString result;
			InvokeHelper(0x6002000d, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		VARIANT get_DateCreatedFrom()
		{
			VARIANT result;
			InvokeHelper(0x6002000e, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		VARIANT get_DateCreatedTo()
		{
			VARIANT result;
			InvokeHelper(0x6002000f, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		long get_View()
		{
			long result;
			InvokeHelper(0x60020010, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		long get_SortBy()
		{
			long result;
			InvokeHelper(0x60020011, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		long get_ListBy()
		{
			long result;
			InvokeHelper(0x60020012, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		long get_SelectedFile()
		{
			long result;
			InvokeHelper(0x60020013, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Results()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020014, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long Show()
		{
			long result;
			InvokeHelper(0x60020015, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_SearchPath(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		void put_Name(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		void put_SubDir(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x60020002, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		void put_Title(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x60020003, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		void put_Author(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x60020004, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		void put_Keywords(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x60020005, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		void put_Subject(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x60020006, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		void put_Options(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60020007, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		void put_MatchCase(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x60020008, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		void put_Text(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x60020009, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		void put_PatternMatch(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x6002000a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		void put_DateSavedFrom(VARIANT& newValue)
		{
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x6002000b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, &newValue);
		}
		void put_DateSavedTo(VARIANT& newValue)
		{
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x6002000c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, &newValue);
		}
		void put_SavedBy(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x6002000d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		void put_DateCreatedFrom(VARIANT& newValue)
		{
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x6002000e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, &newValue);
		}
		void put_DateCreatedTo(VARIANT& newValue)
		{
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x6002000f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, &newValue);
		}
		void put_View(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60020010, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		void put_SortBy(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60020011, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		void put_ListBy(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60020012, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		void put_SelectedFile(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60020013, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		void Execute()
		{
			InvokeHelper(0x6002002a, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void Load(LPCTSTR bstrQueryName)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x6002002b, DISPATCH_METHOD, VT_EMPTY, NULL, parms, bstrQueryName);
		}
		void Save(LPCTSTR bstrQueryName)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x6002002c, DISPATCH_METHOD, VT_EMPTY, NULL, parms, bstrQueryName);
		}
		void Delete(LPCTSTR bstrQueryName)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x6002002d, DISPATCH_METHOD, VT_EMPTY, NULL, parms, bstrQueryName);
		}
		long get_FileType()
		{
			long result;
			InvokeHelper(0x6002002e, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_FileType(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x6002002e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
	};
	
	// ILicAgent ��װ��
	class ILicAgent : public COleDispatchDriver
	{
	public:
		ILicAgent(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		ILicAgent(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		ILicAgent(const ILicAgent& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// ILicAgent ����
	public:
		unsigned long Initialize(unsigned long dwBPC, unsigned long dwMode, LPCTSTR bstrLicSource)
		{
			unsigned long result;
			static BYTE parms[] = VTS_UI4 VTS_UI4 VTS_BSTR ;
			InvokeHelper(0x1, DISPATCH_METHOD, VT_UI4, (void*)&result, parms, dwBPC, dwMode, bstrLicSource);
			return result;
		}
		CString GetFirstName()
		{
			CString result;
			InvokeHelper(0x3, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void SetFirstName(LPCTSTR bstrNewVal)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x4, DISPATCH_METHOD, VT_EMPTY, NULL, parms, bstrNewVal);
		}
		CString GetLastName()
		{
			CString result;
			InvokeHelper(0x5, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void SetLastName(LPCTSTR bstrNewVal)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x6, DISPATCH_METHOD, VT_EMPTY, NULL, parms, bstrNewVal);
		}
		CString GetOrgName()
		{
			CString result;
			InvokeHelper(0x7, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void SetOrgName(LPCTSTR bstrNewVal)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x8, DISPATCH_METHOD, VT_EMPTY, NULL, parms, bstrNewVal);
		}
		CString GetEmail()
		{
			CString result;
			InvokeHelper(0x9, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void SetEmail(LPCTSTR bstrNewVal)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0xa, DISPATCH_METHOD, VT_EMPTY, NULL, parms, bstrNewVal);
		}
		CString GetPhone()
		{
			CString result;
			InvokeHelper(0xb, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void SetPhone(LPCTSTR bstrNewVal)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0xc, DISPATCH_METHOD, VT_EMPTY, NULL, parms, bstrNewVal);
		}
		CString GetAddress1()
		{
			CString result;
			InvokeHelper(0xd, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void SetAddress1(LPCTSTR bstrNewVal)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0xe, DISPATCH_METHOD, VT_EMPTY, NULL, parms, bstrNewVal);
		}
		CString GetCity()
		{
			CString result;
			InvokeHelper(0xf, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void SetCity(LPCTSTR bstrNewVal)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x10, DISPATCH_METHOD, VT_EMPTY, NULL, parms, bstrNewVal);
		}
		CString GetState()
		{
			CString result;
			InvokeHelper(0x11, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void SetState(LPCTSTR bstrNewVal)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x12, DISPATCH_METHOD, VT_EMPTY, NULL, parms, bstrNewVal);
		}
		CString GetCountryCode()
		{
			CString result;
			InvokeHelper(0x13, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void SetCountryCode(LPCTSTR bstrNewVal)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x14, DISPATCH_METHOD, VT_EMPTY, NULL, parms, bstrNewVal);
		}
		CString GetCountryDesc()
		{
			CString result;
			InvokeHelper(0x15, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void SetCountryDesc(LPCTSTR bstrNewVal)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x16, DISPATCH_METHOD, VT_EMPTY, NULL, parms, bstrNewVal);
		}
		CString GetZip()
		{
			CString result;
			InvokeHelper(0x17, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void SetZip(LPCTSTR bstrNewVal)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x18, DISPATCH_METHOD, VT_EMPTY, NULL, parms, bstrNewVal);
		}
		unsigned long GetIsoLanguage()
		{
			unsigned long result;
			InvokeHelper(0x19, DISPATCH_METHOD, VT_UI4, (void*)&result, NULL);
			return result;
		}
		void SetIsoLanguage(unsigned long dwNewVal)
		{
			static BYTE parms[] = VTS_UI4 ;
			InvokeHelper(0x1a, DISPATCH_METHOD, VT_EMPTY, NULL, parms, dwNewVal);
		}
		CString GetMSUpdate()
		{
			CString result;
			InvokeHelper(0x20, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void SetMSUpdate(LPCTSTR bstrNewVal)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x21, DISPATCH_METHOD, VT_EMPTY, NULL, parms, bstrNewVal);
		}
		CString GetMSOffer()
		{
			CString result;
			InvokeHelper(0x22, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void SetMSOffer(LPCTSTR bstrNewVal)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x23, DISPATCH_METHOD, VT_EMPTY, NULL, parms, bstrNewVal);
		}
		CString GetOtherOffer()
		{
			CString result;
			InvokeHelper(0x24, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void SetOtherOffer(LPCTSTR bstrNewVal)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x25, DISPATCH_METHOD, VT_EMPTY, NULL, parms, bstrNewVal);
		}
		CString GetAddress2()
		{
			CString result;
			InvokeHelper(0x26, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void SetAddress2(LPCTSTR bstrNewVal)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x27, DISPATCH_METHOD, VT_EMPTY, NULL, parms, bstrNewVal);
		}
		unsigned long CheckSystemClock()
		{
			unsigned long result;
			InvokeHelper(0x28, DISPATCH_METHOD, VT_UI4, (void*)&result, NULL);
			return result;
		}
		DATE GetExistingExpiryDate()
		{
			DATE result;
			InvokeHelper(0x29, DISPATCH_METHOD, VT_DATE, (void*)&result, NULL);
			return result;
		}
		DATE GetNewExpiryDate()
		{
			DATE result;
			InvokeHelper(0x2a, DISPATCH_METHOD, VT_DATE, (void*)&result, NULL);
			return result;
		}
		CString GetBillingFirstName()
		{
			CString result;
			InvokeHelper(0x2b, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void SetBillingFirstName(LPCTSTR bstrNewVal)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x2c, DISPATCH_METHOD, VT_EMPTY, NULL, parms, bstrNewVal);
		}
		CString GetBillingLastName()
		{
			CString result;
			InvokeHelper(0x2d, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void SetBillingLastName(LPCTSTR bstrNewVal)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x2e, DISPATCH_METHOD, VT_EMPTY, NULL, parms, bstrNewVal);
		}
		CString GetBillingPhone()
		{
			CString result;
			InvokeHelper(0x2f, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void SetBillingPhone(LPCTSTR bstrNewVal)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x30, DISPATCH_METHOD, VT_EMPTY, NULL, parms, bstrNewVal);
		}
		CString GetBillingAddress1()
		{
			CString result;
			InvokeHelper(0x31, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void SetBillingAddress1(LPCTSTR bstrNewVal)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x32, DISPATCH_METHOD, VT_EMPTY, NULL, parms, bstrNewVal);
		}
		CString GetBillingAddress2()
		{
			CString result;
			InvokeHelper(0x33, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void SetBillingAddress2(LPCTSTR bstrNewVal)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x34, DISPATCH_METHOD, VT_EMPTY, NULL, parms, bstrNewVal);
		}
		CString GetBillingCity()
		{
			CString result;
			InvokeHelper(0x35, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void SetBillingCity(LPCTSTR bstrNewVal)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x36, DISPATCH_METHOD, VT_EMPTY, NULL, parms, bstrNewVal);
		}
		CString GetBillingState()
		{
			CString result;
			InvokeHelper(0x37, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void SetBillingState(LPCTSTR bstrNewVal)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x38, DISPATCH_METHOD, VT_EMPTY, NULL, parms, bstrNewVal);
		}
		CString GetBillingCountryCode()
		{
			CString result;
			InvokeHelper(0x39, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void SetBillingCountryCode(LPCTSTR bstrNewVal)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x3a, DISPATCH_METHOD, VT_EMPTY, NULL, parms, bstrNewVal);
		}
		CString GetBillingZip()
		{
			CString result;
			InvokeHelper(0x3b, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void SetBillingZip(LPCTSTR bstrNewVal)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x3c, DISPATCH_METHOD, VT_EMPTY, NULL, parms, bstrNewVal);
		}
		unsigned long SaveBillingInfo(long bSave)
		{
			unsigned long result;
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x3d, DISPATCH_METHOD, VT_UI4, (void*)&result, parms, bSave);
			return result;
		}
		long IsCCRenewalCountry(LPCTSTR bstrCountryCode)
		{
			long result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x40, DISPATCH_METHOD, VT_I4, (void*)&result, parms, bstrCountryCode);
			return result;
		}
		CString GetVATLabel(LPCTSTR bstrCountryCode)
		{
			CString result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x41, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, bstrCountryCode);
			return result;
		}
		DATE GetCCRenewalExpiryDate()
		{
			DATE result;
			InvokeHelper(0x42, DISPATCH_METHOD, VT_DATE, (void*)&result, NULL);
			return result;
		}
		void SetVATNumber(LPCTSTR bstrVATNumber)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x43, DISPATCH_METHOD, VT_EMPTY, NULL, parms, bstrVATNumber);
		}
		void SetCreditCardType(LPCTSTR bstrCCCode)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x44, DISPATCH_METHOD, VT_EMPTY, NULL, parms, bstrCCCode);
		}
		void SetCreditCardNumber(LPCTSTR bstrCCNumber)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x45, DISPATCH_METHOD, VT_EMPTY, NULL, parms, bstrCCNumber);
		}
		void SetCreditCardExpiryYear(unsigned long dwCCYear)
		{
			static BYTE parms[] = VTS_UI4 ;
			InvokeHelper(0x46, DISPATCH_METHOD, VT_EMPTY, NULL, parms, dwCCYear);
		}
		void SetCreditCardExpiryMonth(unsigned long dwCCMonth)
		{
			static BYTE parms[] = VTS_UI4 ;
			InvokeHelper(0x47, DISPATCH_METHOD, VT_EMPTY, NULL, parms, dwCCMonth);
		}
		unsigned long GetCreditCardCount()
		{
			unsigned long result;
			InvokeHelper(0x48, DISPATCH_METHOD, VT_UI4, (void*)&result, NULL);
			return result;
		}
		CString GetCreditCardCode(unsigned long dwIndex)
		{
			CString result;
			static BYTE parms[] = VTS_UI4 ;
			InvokeHelper(0x49, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, dwIndex);
			return result;
		}
		CString GetCreditCardName(unsigned long dwIndex)
		{
			CString result;
			static BYTE parms[] = VTS_UI4 ;
			InvokeHelper(0x4a, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, dwIndex);
			return result;
		}
		CString GetVATNumber()
		{
			CString result;
			InvokeHelper(0x4b, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		CString GetCreditCardType()
		{
			CString result;
			InvokeHelper(0x4c, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		CString GetCreditCardNumber()
		{
			CString result;
			InvokeHelper(0x4d, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		unsigned long GetCreditCardExpiryYear()
		{
			unsigned long result;
			InvokeHelper(0x4e, DISPATCH_METHOD, VT_UI4, (void*)&result, NULL);
			return result;
		}
		unsigned long GetCreditCardExpiryMonth()
		{
			unsigned long result;
			InvokeHelper(0x4f, DISPATCH_METHOD, VT_UI4, (void*)&result, NULL);
			return result;
		}
		long GetDisconnectOption()
		{
			long result;
			InvokeHelper(0x50, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
			return result;
		}
		void SetDisconnectOption(long bNewVal)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x51, DISPATCH_METHOD, VT_EMPTY, NULL, parms, bNewVal);
		}
		void AsyncProcessHandshakeRequest(long bReviseCustInfo)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x52, DISPATCH_METHOD, VT_EMPTY, NULL, parms, bReviseCustInfo);
		}
		void AsyncProcessNewLicenseRequest()
		{
			InvokeHelper(0x53, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void AsyncProcessReissueLicenseRequest()
		{
			InvokeHelper(0x54, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void AsyncProcessRetailRenewalLicenseRequest()
		{
			InvokeHelper(0x55, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void AsyncProcessReviseCustInfoRequest()
		{
			InvokeHelper(0x56, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void AsyncProcessCCRenewalPriceRequest()
		{
			InvokeHelper(0x57, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void AsyncProcessCCRenewalLicenseRequest()
		{
			InvokeHelper(0x58, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		unsigned long GetAsyncProcessReturnCode()
		{
			unsigned long result;
			InvokeHelper(0x5a, DISPATCH_METHOD, VT_UI4, (void*)&result, NULL);
			return result;
		}
		long IsUpgradeAvailable()
		{
			long result;
			InvokeHelper(0x5b, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
			return result;
		}
		void WantUpgrade(long bWantUpgrade)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x5c, DISPATCH_METHOD, VT_EMPTY, NULL, parms, bWantUpgrade);
		}
		void AsyncProcessDroppedLicenseRequest()
		{
			InvokeHelper(0x5d, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		CString GenerateInstallationId()
		{
			CString result;
			InvokeHelper(0x5e, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		unsigned long DepositConfirmationId(LPCTSTR bstrVal)
		{
			unsigned long result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x5f, DISPATCH_METHOD, VT_UI4, (void*)&result, parms, bstrVal);
			return result;
		}
		long VerifyCheckDigits(LPCTSTR bstrCIDIID)
		{
			long result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x60, DISPATCH_METHOD, VT_I4, (void*)&result, parms, bstrCIDIID);
			return result;
		}
		DATE GetCurrentExpiryDate()
		{
			DATE result;
			InvokeHelper(0x61, DISPATCH_METHOD, VT_DATE, (void*)&result, NULL);
			return result;
		}
		void CancelAsyncProcessRequest(long bIsLicenseRequest)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x62, DISPATCH_METHOD, VT_EMPTY, NULL, parms, bIsLicenseRequest);
		}
		CString GetCurrencyDescription(unsigned long dwCurrencyIndex)
		{
			CString result;
			static BYTE parms[] = VTS_UI4 ;
			InvokeHelper(0x64, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, dwCurrencyIndex);
			return result;
		}
		unsigned long GetPriceItemCount()
		{
			unsigned long result;
			InvokeHelper(0x65, DISPATCH_METHOD, VT_UI4, (void*)&result, NULL);
			return result;
		}
		CString GetPriceItemLabel(unsigned long dwIndex)
		{
			CString result;
			static BYTE parms[] = VTS_UI4 ;
			InvokeHelper(0x66, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, dwIndex);
			return result;
		}
		CString GetPriceItemValue(unsigned long dwCurrencyIndex, unsigned long dwIndex)
		{
			CString result;
			static BYTE parms[] = VTS_UI4 VTS_UI4 ;
			InvokeHelper(0x67, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, dwCurrencyIndex, dwIndex);
			return result;
		}
		CString GetInvoiceText()
		{
			CString result;
			InvokeHelper(0x68, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		CString GetBackendErrorMsg()
		{
			CString result;
			InvokeHelper(0x69, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		unsigned long GetCurrencyOption()
		{
			unsigned long result;
			InvokeHelper(0x6a, DISPATCH_METHOD, VT_UI4, (void*)&result, NULL);
			return result;
		}
		void SetCurrencyOption(unsigned long dwCurrencyOption)
		{
			static BYTE parms[] = VTS_UI4 ;
			InvokeHelper(0x6b, DISPATCH_METHOD, VT_EMPTY, NULL, parms, dwCurrencyOption);
		}
		CString GetEndOfLifeHtmlText()
		{
			CString result;
			InvokeHelper(0x6c, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		unsigned long DisplaySSLCert()
		{
			unsigned long result;
			InvokeHelper(0x6d, DISPATCH_METHOD, VT_UI4, (void*)&result, NULL);
			return result;
		}
	};
	
	// ILicValidator ��װ��
	class ILicValidator : public COleDispatchDriver
	{
	public:
		ILicValidator(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		ILicValidator(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		ILicValidator(const ILicValidator& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// ILicValidator ����
	public:
		VARIANT get_Products()
		{
			VARIANT result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		long get_Selection()
		{
			long result;
			InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_Selection(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
	};
	
	// ILicWizExternal ��װ��
	class ILicWizExternal : public COleDispatchDriver
	{
	public:
		ILicWizExternal(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		ILicWizExternal(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		ILicWizExternal(const ILicWizExternal& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// ILicWizExternal ����
	public:
		void PrintHtmlDocument(LPUNKNOWN punkHtmlDoc)
		{
			static BYTE parms[] = VTS_UNKNOWN ;
			InvokeHelper(0x1, DISPATCH_METHOD, VT_EMPTY, NULL, parms, punkHtmlDoc);
		}
		void InvokeDateTimeApplet()
		{
			InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		CString FormatDate(DATE date, LPCTSTR pFormat)
		{
			CString result;
			static BYTE parms[] = VTS_DATE VTS_BSTR ;
			InvokeHelper(0x3, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, date, pFormat);
			return result;
		}
		void ShowHelp(VARIANT * pvarId)
		{
			static BYTE parms[] = VTS_PVARIANT ;
			InvokeHelper(0x4, DISPATCH_METHOD, VT_EMPTY, NULL, parms, pvarId);
		}
		void Terminate()
		{
			InvokeHelper(0x5, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void DisableVORWReminder(long BPC)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x6, DISPATCH_METHOD, VT_EMPTY, NULL, parms, BPC);
		}
		CString SaveReceipt(LPCTSTR bstrReceipt)
		{
			CString result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x7, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, bstrReceipt);
			return result;
		}
		void OpenInDefaultBrowser(LPCTSTR bstrUrl)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x8, DISPATCH_METHOD, VT_EMPTY, NULL, parms, bstrUrl);
		}
		long MsoAlert(LPCTSTR bstrText, LPCTSTR bstrButtons, LPCTSTR bstrIcon)
		{
			long result;
			static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR ;
			InvokeHelper(0x9, DISPATCH_METHOD, VT_I4, (void*)&result, parms, bstrText, bstrButtons, bstrIcon);
			return result;
		}
		long DepositPidKey(LPCTSTR bstrKey, long fMORW)
		{
			long result;
			static BYTE parms[] = VTS_BSTR VTS_I4 ;
			InvokeHelper(0xa, DISPATCH_METHOD, VT_I4, (void*)&result, parms, bstrKey, fMORW);
			return result;
		}
		void WriteLog(LPCTSTR bstrMessage)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0xb, DISPATCH_METHOD, VT_EMPTY, NULL, parms, bstrMessage);
		}
		void ResignDpc(LPCTSTR bstrProductCode)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0xc, DISPATCH_METHOD, VT_EMPTY, NULL, parms, bstrProductCode);
		}
		void ResetPID()
		{
			InvokeHelper(0xd, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void SetDialogSize(long dx, long dy)
		{
			static BYTE parms[] = VTS_I4 VTS_I4 ;
			InvokeHelper(0xe, DISPATCH_METHOD, VT_EMPTY, NULL, parms, dx, dy);
		}
		long VerifyClock(long lMode)
		{
			long result;
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0xf, DISPATCH_METHOD, VT_I4, (void*)&result, parms, lMode);
			return result;
		}
		void SortSelectOptions(LPDISPATCH pdispSelect)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x10, DISPATCH_METHOD, VT_EMPTY, NULL, parms, pdispSelect);
		}
		void InternetDisconnect()
		{
			InvokeHelper(0x11, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		long GetConnectedState()
		{
			long result;
			InvokeHelper(0x12, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
			return result;
		}
		long get_Context()
		{
			long result;
			InvokeHelper(0x14, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Validator()
		{
			LPDISPATCH result;
			InvokeHelper(0x15, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_LicAgent()
		{
			LPDISPATCH result;
			InvokeHelper(0x16, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		CString get_CountryInfo()
		{
			CString result;
			InvokeHelper(0x17, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_WizardVisible(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x18, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		void put_WizardTitle(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x19, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_AnimationEnabled()
		{
			long result;
			InvokeHelper(0x1a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_CurrentHelpId(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x1b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_OfficeOnTheWebUrl()
		{
			CString result;
			InvokeHelper(0x1c, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
	};

	// IMsoAxis ��װ��
	class IMsoAxis : public COleDispatchDriver
	{
	public:
		IMsoAxis(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		IMsoAxis(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		IMsoAxis(const IMsoAxis& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// IMsoAxis ����
	public:
		BOOL get_AxisBetweenCategories()
		{
			BOOL result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_AxisBetweenCategories(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_AxisGroup()
		{
			long result;
			InvokeHelper(0x60020002, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_AxisTitle()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020003, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		VARIANT get_CategoryNames()
		{
			VARIANT result;
			InvokeHelper(0x60020004, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		void put_CategoryNames(VARIANT& newValue)
		{
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x60020004, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, &newValue);
		}
		long get_Crosses()
		{
			long result;
			InvokeHelper(0x60020006, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_Crosses(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60020006, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		double get_CrossesAt()
		{
			double result;
			InvokeHelper(0x60020008, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
			return result;
		}
		void put_CrossesAt(double newValue)
		{
			static BYTE parms[] = VTS_R8 ;
			InvokeHelper(0x60020008, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		VARIANT Delete()
		{
			VARIANT result;
			InvokeHelper(0x6002000a, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		BOOL get_HasMajorGridlines()
		{
			BOOL result;
			InvokeHelper(0x6002000b, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_HasMajorGridlines(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x6002000b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_HasMinorGridlines()
		{
			BOOL result;
			InvokeHelper(0x6002000d, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_HasMinorGridlines(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x6002000d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_HasTitle()
		{
			BOOL result;
			InvokeHelper(0x6002000f, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_HasTitle(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x6002000f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		LPDISPATCH get_MajorGridlines()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020011, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_MajorTickMark()
		{
			long result;
			InvokeHelper(0x60020012, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_MajorTickMark(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60020012, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		double get_MajorUnit()
		{
			double result;
			InvokeHelper(0x60020014, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
			return result;
		}
		void put_MajorUnit(double newValue)
		{
			static BYTE parms[] = VTS_R8 ;
			InvokeHelper(0x60020014, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		double get_LogBase()
		{
			double result;
			InvokeHelper(0x60020016, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
			return result;
		}
		void put_LogBase(double newValue)
		{
			static BYTE parms[] = VTS_R8 ;
			InvokeHelper(0x60020016, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_TickLabelSpacingIsAuto()
		{
			BOOL result;
			InvokeHelper(0x60020018, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_TickLabelSpacingIsAuto(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x60020018, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_MajorUnitIsAuto()
		{
			BOOL result;
			InvokeHelper(0x6002001a, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_MajorUnitIsAuto(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x6002001a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		double get_MaximumScale()
		{
			double result;
			InvokeHelper(0x6002001c, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
			return result;
		}
		void put_MaximumScale(double newValue)
		{
			static BYTE parms[] = VTS_R8 ;
			InvokeHelper(0x6002001c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_MaximumScaleIsAuto()
		{
			BOOL result;
			InvokeHelper(0x6002001e, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_MaximumScaleIsAuto(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x6002001e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		double get_MinimumScale()
		{
			double result;
			InvokeHelper(0x60020020, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
			return result;
		}
		void put_MinimumScale(double newValue)
		{
			static BYTE parms[] = VTS_R8 ;
			InvokeHelper(0x60020020, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_MinimumScaleIsAuto()
		{
			BOOL result;
			InvokeHelper(0x60020022, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_MinimumScaleIsAuto(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x60020022, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		LPDISPATCH get_MinorGridlines()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020024, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_MinorTickMark()
		{
			long result;
			InvokeHelper(0x60020025, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_MinorTickMark(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60020025, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		double get_MinorUnit()
		{
			double result;
			InvokeHelper(0x60020027, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
			return result;
		}
		void put_MinorUnit(double newValue)
		{
			static BYTE parms[] = VTS_R8 ;
			InvokeHelper(0x60020027, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_MinorUnitIsAuto()
		{
			BOOL result;
			InvokeHelper(0x60020029, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_MinorUnitIsAuto(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x60020029, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_ReversePlotOrder()
		{
			BOOL result;
			InvokeHelper(0x6002002b, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_ReversePlotOrder(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x6002002b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_ScaleType()
		{
			long result;
			InvokeHelper(0x6002002d, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_ScaleType(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x6002002d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		VARIANT Select()
		{
			VARIANT result;
			InvokeHelper(0x6002002f, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		long get_TickLabelPosition()
		{
			long result;
			InvokeHelper(0x60020030, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_TickLabelPosition(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60020030, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		LPDISPATCH get_TickLabels()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020032, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_TickLabelSpacing()
		{
			long result;
			InvokeHelper(0x60020033, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_TickLabelSpacing(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60020033, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_TickMarkSpacing()
		{
			long result;
			InvokeHelper(0x60020035, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_TickMarkSpacing(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60020035, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_Type()
		{
			long result;
			InvokeHelper(0x60020037, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_Type(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60020037, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_BaseUnit()
		{
			long result;
			InvokeHelper(0x60020039, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_BaseUnit(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60020039, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_BaseUnitIsAuto()
		{
			BOOL result;
			InvokeHelper(0x6002003b, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_BaseUnitIsAuto(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x6002003b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_MajorUnitScale()
		{
			long result;
			InvokeHelper(0x6002003d, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_MajorUnitScale(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x6002003d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_MinorUnitScale()
		{
			long result;
			InvokeHelper(0x6002003f, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_MinorUnitScale(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x6002003f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_CategoryType()
		{
			long result;
			InvokeHelper(0x60020041, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_CategoryType(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60020041, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		double get_Left()
		{
			double result;
			InvokeHelper(0x60020043, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
			return result;
		}
		double get_Top()
		{
			double result;
			InvokeHelper(0x60020044, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
			return result;
		}
		double get_Width()
		{
			double result;
			InvokeHelper(0x60020045, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
			return result;
		}
		double get_Height()
		{
			double result;
			InvokeHelper(0x60020046, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
			return result;
		}
		long get_DisplayUnit()
		{
			long result;
			InvokeHelper(0x60020047, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_DisplayUnit(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60020047, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		double get_DisplayUnitCustom()
		{
			double result;
			InvokeHelper(0x60020049, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
			return result;
		}
		void put_DisplayUnitCustom(double newValue)
		{
			static BYTE parms[] = VTS_R8 ;
			InvokeHelper(0x60020049, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_HasDisplayUnitLabel()
		{
			BOOL result;
			InvokeHelper(0x6002004b, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_HasDisplayUnitLabel(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x6002004b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		LPDISPATCH get_DisplayUnitLabel()
		{
			LPDISPATCH result;
			InvokeHelper(0x6002004d, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Border()
		{
			LPDISPATCH result;
			InvokeHelper(0x6002004e, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		CString get_Name()
		{
			CString result;
			InvokeHelper(0x6002004f, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Format()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020050, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x94, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x95, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x96, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
	};
	
	// IMsoAxisTitle ��װ��
	class IMsoAxisTitle : public COleDispatchDriver
	{
	public:
		IMsoAxisTitle(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		IMsoAxisTitle(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		IMsoAxisTitle(const IMsoAxisTitle& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// IMsoAxisTitle ����
	public:
		void put_Caption(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_Caption()
		{
			CString result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Characters(VARIANT& Start, VARIANT& Length)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_VARIANT VTS_VARIANT ;
			InvokeHelper(0x60020002, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, &Start, &Length);
			return result;
		}
		LPDISPATCH get_Font()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020003, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		void put_HorizontalAlignment(VARIANT& newValue)
		{
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x60020004, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, &newValue);
		}
		VARIANT get_HorizontalAlignment()
		{
			VARIANT result;
			InvokeHelper(0x60020004, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		double get_Left()
		{
			double result;
			InvokeHelper(0x60020006, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
			return result;
		}
		void put_Left(double newValue)
		{
			static BYTE parms[] = VTS_R8 ;
			InvokeHelper(0x60020006, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		void put_Orientation(VARIANT& newValue)
		{
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x60020008, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, &newValue);
		}
		VARIANT get_Orientation()
		{
			VARIANT result;
			InvokeHelper(0x60020008, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		BOOL get_Shadow()
		{
			BOOL result;
			InvokeHelper(0x6002000a, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_Shadow(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x6002000a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		void put_Text(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x6002000c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_Text()
		{
			CString result;
			InvokeHelper(0x6002000c, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		double get_Top()
		{
			double result;
			InvokeHelper(0x6002000e, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
			return result;
		}
		void put_Top(double newValue)
		{
			static BYTE parms[] = VTS_R8 ;
			InvokeHelper(0x6002000e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		void put_VerticalAlignment(VARIANT& newValue)
		{
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x60020010, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, &newValue);
		}
		VARIANT get_VerticalAlignment()
		{
			VARIANT result;
			InvokeHelper(0x60020010, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		long get_ReadingOrder()
		{
			long result;
			InvokeHelper(0x60020012, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_ReadingOrder(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60020012, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		void put_AutoScaleFont(VARIANT& newValue)
		{
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x60020014, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, &newValue);
		}
		VARIANT get_AutoScaleFont()
		{
			VARIANT result;
			InvokeHelper(0x60020014, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Interior()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020016, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Fill()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020017, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		VARIANT Delete()
		{
			VARIANT result;
			InvokeHelper(0x60020018, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Border()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020019, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		CString get_Name()
		{
			CString result;
			InvokeHelper(0x6002001a, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x6002001b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		VARIANT Select()
		{
			VARIANT result;
			InvokeHelper(0x6002001c, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		BOOL get_IncludeInLayout()
		{
			BOOL result;
			InvokeHelper(0x972, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_IncludeInLayout(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x972, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_Position()
		{
			long result;
			InvokeHelper(0x687, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_Position(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x687, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		LPDISPATCH get_Format()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020021, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		double get_Height()
		{
			double result;
			InvokeHelper(0x60020022, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x94, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x95, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		double get_Width()
		{
			double result;
			InvokeHelper(0x60020025, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
			return result;
		}
		void put_Formula(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x60020026, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_Formula()
		{
			CString result;
			InvokeHelper(0x60020026, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_FormulaR1C1(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x60020028, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_FormulaR1C1()
		{
			CString result;
			InvokeHelper(0x60020028, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_FormulaLocal(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x6002002a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_FormulaLocal()
		{
			CString result;
			InvokeHelper(0x6002002a, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_FormulaR1C1Local(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x6002002c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_FormulaR1C1Local()
		{
			CString result;
			InvokeHelper(0x6002002c, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
	};
	
	// IMsoBorder ��װ��
	class IMsoBorder : public COleDispatchDriver
	{
	public:
		IMsoBorder(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		IMsoBorder(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		IMsoBorder(const IMsoBorder& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// IMsoBorder ����
	public:
		void put_Color(VARIANT& newValue)
		{
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, &newValue);
		}
		VARIANT get_Color()
		{
			VARIANT result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		void put_ColorIndex(VARIANT& newValue)
		{
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x60020002, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, &newValue);
		}
		VARIANT get_ColorIndex()
		{
			VARIANT result;
			InvokeHelper(0x60020002, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		void put_LineStyle(VARIANT& newValue)
		{
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x60020004, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, &newValue);
		}
		VARIANT get_LineStyle()
		{
			VARIANT result;
			InvokeHelper(0x60020004, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		void put_Weight(VARIANT& newValue)
		{
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x60020006, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, &newValue);
		}
		VARIANT get_Weight()
		{
			VARIANT result;
			InvokeHelper(0x60020006, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x94, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x95, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x96, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
	};
	
	// IMsoCharacters ��װ��
	class IMsoCharacters : public COleDispatchDriver
	{
	public:
		IMsoCharacters(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		IMsoCharacters(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		IMsoCharacters(const IMsoCharacters& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// IMsoCharacters ����
	public:
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x96, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		CString get_Caption()
		{
			CString result;
			InvokeHelper(0x8b, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_Caption(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x8b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_Count()
		{
			long result;
			InvokeHelper(0x76, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		VARIANT Delete()
		{
			VARIANT result;
			InvokeHelper(0x75, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Font()
		{
			LPDISPATCH result;
			InvokeHelper(0x92, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		VARIANT Insert(LPCTSTR bstr)
		{
			VARIANT result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0xfc, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms, bstr);
			return result;
		}
		CString get_Text()
		{
			CString result;
			InvokeHelper(0x8a, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_Text(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x8a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_PhoneticCharacters()
		{
			CString result;
			InvokeHelper(0x5f2, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_PhoneticCharacters(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x5f2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x94, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x95, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
	};
	
	// IMsoChart ��װ��
	class IMsoChart : public COleDispatchDriver
	{
	public:
		IMsoChart(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		IMsoChart(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		IMsoChart(const IMsoChart& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// IMsoChart ����
	public:
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x96, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		void put_HasTitle(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_HasTitle()
		{
			BOOL result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_ChartTitle()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020003, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_DepthPercent()
		{
			long result;
			InvokeHelper(0x60020004, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_DepthPercent(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60020004, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_Elevation()
		{
			long result;
			InvokeHelper(0x60020006, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_Elevation(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60020006, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_GapDepth()
		{
			long result;
			InvokeHelper(0x60020008, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_GapDepth(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60020008, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_HeightPercent()
		{
			long result;
			InvokeHelper(0x6002000a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_HeightPercent(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x6002000a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_Perspective()
		{
			long result;
			InvokeHelper(0x6002000c, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_Perspective(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x6002000c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		VARIANT get_RightAngleAxes()
		{
			VARIANT result;
			InvokeHelper(0x6002000e, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		void put_RightAngleAxes(VARIANT& newValue)
		{
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x6002000e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, &newValue);
		}
		VARIANT get_Rotation()
		{
			VARIANT result;
			InvokeHelper(0x60020010, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		void put_Rotation(VARIANT& newValue)
		{
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x60020010, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, &newValue);
		}
		void put_DisplayBlanksAs(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60020012, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_DisplayBlanksAs()
		{
			long result;
			InvokeHelper(0x60020012, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_ProtectData(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x60020014, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_ProtectData()
		{
			BOOL result;
			InvokeHelper(0x60020014, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_ProtectFormatting(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x60020016, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_ProtectFormatting()
		{
			BOOL result;
			InvokeHelper(0x60020016, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_ProtectGoalSeek(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x60020018, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_ProtectGoalSeek()
		{
			BOOL result;
			InvokeHelper(0x60020018, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_ProtectSelection(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x6002001a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_ProtectSelection()
		{
			BOOL result;
			InvokeHelper(0x6002001a, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_ProtectChartObjects(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x6002001c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_ProtectChartObjects()
		{
			BOOL result;
			InvokeHelper(0x6002001c, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void UnProtect(VARIANT& Password)
		{
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x6002001e, DISPATCH_METHOD, VT_EMPTY, NULL, parms, &Password);
		}
		void Protect(VARIANT& Password, VARIANT& DrawingObjects, VARIANT& Contents, VARIANT& Scenarios, VARIANT& UserInterfaceOnly)
		{
			static BYTE parms[] = VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT ;
			InvokeHelper(0x6002001f, DISPATCH_METHOD, VT_EMPTY, NULL, parms, &Password, &DrawingObjects, &Contents, &Scenarios, &UserInterfaceOnly);
		}
		LPDISPATCH get_ChartGroups(VARIANT * pvarIndex, VARIANT& varIgallery)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_PVARIANT VTS_VARIANT ;
			InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, pvarIndex, &varIgallery);
			return result;
		}
		LPDISPATCH SeriesCollection(VARIANT& Index)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x44, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, &Index);
			return result;
		}
		void _ApplyDataLabels(long Type, VARIANT& IMsoLegendKey, VARIANT& AutoText, VARIANT& HasLeaderLines)
		{
			static BYTE parms[] = VTS_I4 VTS_VARIANT VTS_VARIANT VTS_VARIANT ;
			InvokeHelper(0x97, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Type, &IMsoLegendKey, &AutoText, &HasLeaderLines);
		}
		long get_SubType()
		{
			long result;
			InvokeHelper(0x6d, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_SubType(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x6d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_Type()
		{
			long result;
			InvokeHelper(0x6c, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_Type(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x6c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		LPDISPATCH get_Corners()
		{
			LPDISPATCH result;
			InvokeHelper(0x4f, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		void ApplyDataLabels(long Type, VARIANT& IMsoLegendKey, VARIANT& AutoText, VARIANT& HasLeaderLines, VARIANT& ShowSeriesName, VARIANT& ShowCategoryName, VARIANT& ShowValue, VARIANT& ShowPercentage, VARIANT& ShowBubbleSize, VARIANT& Separator)
		{
			static BYTE parms[] = VTS_I4 VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT ;
			InvokeHelper(0x782, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Type, &IMsoLegendKey, &AutoText, &HasLeaderLines, &ShowSeriesName, &ShowCategoryName, &ShowValue, &ShowPercentage, &ShowBubbleSize, &Separator);
		}
		long get_ChartType()
		{
			long result;
			InvokeHelper(0x578, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_ChartType(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x578, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_HasDataTable()
		{
			BOOL result;
			InvokeHelper(0x574, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_HasDataTable(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x574, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		void ApplyCustomType(long ChartType, VARIANT& TypeName)
		{
			static BYTE parms[] = VTS_I4 VTS_VARIANT ;
			InvokeHelper(0x579, DISPATCH_METHOD, VT_EMPTY, NULL, parms, ChartType, &TypeName);
		}
		void GetChartElement(long x, long y, long * ElementID, long * Arg1, long * Arg2)
		{
			static BYTE parms[] = VTS_I4 VTS_I4 VTS_PI4 VTS_PI4 VTS_PI4 ;
			InvokeHelper(0x581, DISPATCH_METHOD, VT_EMPTY, NULL, parms, x, y, ElementID, Arg1, Arg2);
		}
		void SetSourceData(LPCTSTR Source, VARIANT& PlotBy)
		{
			static BYTE parms[] = VTS_BSTR VTS_VARIANT ;
			InvokeHelper(0x585, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Source, &PlotBy);
		}
		long get_PlotBy()
		{
			long result;
			InvokeHelper(0xca, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_PlotBy(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0xca, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_HasLegend()
		{
			BOOL result;
			InvokeHelper(0x35, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_HasLegend(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x35, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		LPDISPATCH get_Legend()
		{
			LPDISPATCH result;
			InvokeHelper(0x54, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH Axes(VARIANT& Type, long AxisGroup)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_VARIANT VTS_I4 ;
			InvokeHelper(0x60020035, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, &Type, AxisGroup);
			return result;
		}
		void put_HasAxis(VARIANT& axisType, VARIANT& AxisGroup, VARIANT& newValue)
		{
			static BYTE parms[] = VTS_VARIANT VTS_VARIANT VTS_VARIANT ;
			InvokeHelper(0x60020036, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, &axisType, &AxisGroup, &newValue);
		}
		VARIANT get_HasAxis(VARIANT& axisType, VARIANT& AxisGroup)
		{
			VARIANT result;
			static BYTE parms[] = VTS_VARIANT VTS_VARIANT ;
			InvokeHelper(0x60020036, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, parms, &axisType, &AxisGroup);
			return result;
		}
		LPDISPATCH get_Walls(BOOL fBackWall)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x60020038, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, fBackWall);
			return result;
		}
		LPDISPATCH get_Floor()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020039, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_PlotArea()
		{
			LPDISPATCH result;
			InvokeHelper(0x6002003a, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		BOOL get_PlotVisibleOnly()
		{
			BOOL result;
			InvokeHelper(0x5c, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_PlotVisibleOnly(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x5c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		LPDISPATCH get_ChartArea()
		{
			LPDISPATCH result;
			InvokeHelper(0x6002003d, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		void AutoFormat(long rGallery, VARIANT& varFormat)
		{
			static BYTE parms[] = VTS_I4 VTS_VARIANT ;
			InvokeHelper(0x6002003e, DISPATCH_METHOD, VT_EMPTY, NULL, parms, rGallery, &varFormat);
		}
		BOOL get_AutoScaling()
		{
			BOOL result;
			InvokeHelper(0x6002003f, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_AutoScaling(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x6002003f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		void SetBackgroundPicture(LPCTSTR bstr)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x60020041, DISPATCH_METHOD, VT_EMPTY, NULL, parms, bstr);
		}
		void ChartWizard(VARIANT& varSource, VARIANT& varGallery, VARIANT& varFormat, VARIANT& varPlotBy, VARIANT& varCategoryLabels, VARIANT& varSeriesLabels, VARIANT& varHasLegend, VARIANT& varTitle, VARIANT& varCategoryTitle, VARIANT& varValueTitle, VARIANT& varExtraTitle)
		{
			static BYTE parms[] = VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT ;
			InvokeHelper(0x60020042, DISPATCH_METHOD, VT_EMPTY, NULL, parms, &varSource, &varGallery, &varFormat, &varPlotBy, &varCategoryLabels, &varSeriesLabels, &varHasLegend, &varTitle, &varCategoryTitle, &varValueTitle, &varExtraTitle);
		}
		void CopyPicture(long Appearance, long Format, long Size)
		{
			static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 ;
			InvokeHelper(0x60020043, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Appearance, Format, Size);
		}
		LPDISPATCH get_DataTable()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020044, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		VARIANT Evaluate(VARIANT& varName, long LocaleID, long * ObjType)
		{
			VARIANT result;
			static BYTE parms[] = VTS_VARIANT VTS_I4 VTS_PI4 ;
			InvokeHelper(0x60020045, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms, &varName, LocaleID, ObjType);
			return result;
		}
		VARIANT _Evaluate(VARIANT& varName, long LocaleID)
		{
			VARIANT result;
			static BYTE parms[] = VTS_VARIANT VTS_I4 ;
			InvokeHelper(0x60020046, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms, &varName, LocaleID);
			return result;
		}
		void Paste(VARIANT& varType)
		{
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x60020047, DISPATCH_METHOD, VT_EMPTY, NULL, parms, &varType);
		}
		long get_BarShape()
		{
			long result;
			InvokeHelper(0x60020048, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_BarShape(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60020048, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL Export(LPCTSTR bstr, VARIANT& varFilterName, VARIANT& varInteractive)
		{
			BOOL result;
			static BYTE parms[] = VTS_BSTR VTS_VARIANT VTS_VARIANT ;
			InvokeHelper(0x6002004a, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, bstr, &varFilterName, &varInteractive);
			return result;
		}
		void SetDefaultChart(VARIANT& varName)
		{
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x6002004b, DISPATCH_METHOD, VT_EMPTY, NULL, parms, &varName);
		}
		void ApplyChartTemplate(LPCTSTR bstrFileName)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x6002004c, DISPATCH_METHOD, VT_EMPTY, NULL, parms, bstrFileName);
		}
		void SaveChartTemplate(LPCTSTR bstrFileName)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x6002004d, DISPATCH_METHOD, VT_EMPTY, NULL, parms, bstrFileName);
		}
		LPDISPATCH get_SideWall()
		{
			LPDISPATCH result;
			InvokeHelper(0x949, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_BackWall()
		{
			LPDISPATCH result;
			InvokeHelper(0x94a, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		VARIANT get_ChartStyle()
		{
			VARIANT result;
			InvokeHelper(0x9a1, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		void put_ChartStyle(VARIANT& newValue)
		{
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x9a1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, &newValue);
		}
		void ClearToMatchStyle()
		{
			InvokeHelper(0x9a2, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		LPDISPATCH get_PivotLayout()
		{
			LPDISPATCH result;
			InvokeHelper(0x716, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		BOOL get_HasPivotFields()
		{
			BOOL result;
			InvokeHelper(0x717, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_HasPivotFields(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x717, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		void RefreshPivotTable()
		{
			InvokeHelper(0x60020056, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void put_ShowDataLabelsOverMaximum(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x60020057, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_ShowDataLabelsOverMaximum()
		{
			BOOL result;
			InvokeHelper(0x60020057, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void ApplyLayout(long Layout, VARIANT& varChartType)
		{
			static BYTE parms[] = VTS_I4 VTS_VARIANT ;
			InvokeHelper(0x9a4, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Layout, &varChartType);
		}
		LPDISPATCH get_Selection()
		{
			LPDISPATCH result;
			InvokeHelper(0x6002005a, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		void Refresh()
		{
			InvokeHelper(0x6002005b, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void SetElement(long RHS)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x6002005c, DISPATCH_METHOD, VT_EMPTY, NULL, parms, RHS);
		}
		LPDISPATCH get_ChartData()
		{
			LPDISPATCH result;
			InvokeHelper(0x6002005d, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Format()
		{
			LPDISPATCH result;
			InvokeHelper(0x6002005e, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Shapes()
		{
			LPDISPATCH result;
			InvokeHelper(0x6002005f, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x94, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x95, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Area3DGroup()
		{
			LPDISPATCH result;
			InvokeHelper(0x11, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH AreaGroups(VARIANT& Index)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x9, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, &Index);
			return result;
		}
		LPDISPATCH get_Bar3DGroup()
		{
			LPDISPATCH result;
			InvokeHelper(0x12, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH BarGroups(VARIANT& Index)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0xa, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, &Index);
			return result;
		}
		LPDISPATCH get_Column3DGroup()
		{
			LPDISPATCH result;
			InvokeHelper(0x13, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH ColumnGroups(VARIANT& Index)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0xb, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, &Index);
			return result;
		}
		LPDISPATCH get_Line3DGroup()
		{
			LPDISPATCH result;
			InvokeHelper(0x14, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH LineGroups(VARIANT& Index)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0xc, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, &Index);
			return result;
		}
		LPDISPATCH get_Pie3DGroup()
		{
			LPDISPATCH result;
			InvokeHelper(0x15, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH PieGroups(VARIANT& Index)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0xd, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, &Index);
			return result;
		}
		LPDISPATCH DoughnutGroups(VARIANT& Index)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0xe, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, &Index);
			return result;
		}
		LPDISPATCH RadarGroups(VARIANT& Index)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0xf, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, &Index);
			return result;
		}
		LPDISPATCH get_SurfaceGroup()
		{
			LPDISPATCH result;
			InvokeHelper(0x16, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH XYGroups(VARIANT& Index)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x10, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, &Index);
			return result;
		}
		VARIANT Delete()
		{
			VARIANT result;
			InvokeHelper(0x75, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		VARIANT Copy()
		{
			VARIANT result;
			InvokeHelper(0x227, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		VARIANT Select(VARIANT& Replace)
		{
			VARIANT result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0xeb, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms, &Replace);
			return result;
		}
		BOOL get_ShowReportFilterFieldButtons()
		{
			BOOL result;
			InvokeHelper(0x60020073, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_ShowReportFilterFieldButtons(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x60020073, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_ShowLegendFieldButtons()
		{
			BOOL result;
			InvokeHelper(0x60020075, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_ShowLegendFieldButtons(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x60020075, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_ShowAxisFieldButtons()
		{
			BOOL result;
			InvokeHelper(0x60020077, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_ShowAxisFieldButtons(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x60020077, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_ShowValueFieldButtons()
		{
			BOOL result;
			InvokeHelper(0x60020079, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_ShowValueFieldButtons(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x60020079, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_ShowAllFieldButtons()
		{
			BOOL result;
			InvokeHelper(0x6002007b, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_ShowAllFieldButtons(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x6002007b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		void put_ProtectChartSheetFormatting(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x6002007d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		LPDISPATCH FullSeriesCollection(VARIANT& Index)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0xec, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, &Index);
			return result;
		}
		void put_CategoryLabelLevel(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0xed, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_CategoryLabelLevel()
		{
			long result;
			InvokeHelper(0xed, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_SeriesNameLevel(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0xee, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_SeriesNameLevel()
		{
			long result;
			InvokeHelper(0xee, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		BOOL get_HasHiddenContent()
		{
			BOOL result;
			InvokeHelper(0xef, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void DeleteHiddenContent()
		{
			InvokeHelper(0xf0, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		VARIANT get_ChartColor()
		{
			VARIANT result;
			InvokeHelper(0x9a3, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		void put_ChartColor(VARIANT& newValue)
		{
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x9a3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, &newValue);
		}
		void ClearToMatchColorStyle()
		{
			InvokeHelper(0x9a5, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
	};
	
	// IMsoChartArea ��װ��
	class IMsoChartArea : public COleDispatchDriver
	{
	public:
		IMsoChartArea(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		IMsoChartArea(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		IMsoChartArea(const IMsoChartArea& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// IMsoChartArea ����
	public:
		CString get_Name()
		{
			CString result;
			InvokeHelper(0x6e, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		VARIANT Select()
		{
			VARIANT result;
			InvokeHelper(0xeb, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x96, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Border()
		{
			LPDISPATCH result;
			InvokeHelper(0x80, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		VARIANT Clear()
		{
			VARIANT result;
			InvokeHelper(0x6f, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		VARIANT ClearContents()
		{
			VARIANT result;
			InvokeHelper(0x71, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		VARIANT Copy()
		{
			VARIANT result;
			InvokeHelper(0x227, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Font()
		{
			LPDISPATCH result;
			InvokeHelper(0x92, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		BOOL get_Shadow()
		{
			BOOL result;
			InvokeHelper(0x67, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_Shadow(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x67, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		VARIANT ClearFormats()
		{
			VARIANT result;
			InvokeHelper(0x70, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		double get_Height()
		{
			double result;
			InvokeHelper(0x7b, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
			return result;
		}
		void put_Height(double newValue)
		{
			static BYTE parms[] = VTS_R8 ;
			InvokeHelper(0x7b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		LPDISPATCH get_Interior()
		{
			LPDISPATCH result;
			InvokeHelper(0x81, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Fill()
		{
			LPDISPATCH result;
			InvokeHelper(0x67f, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		double get_Left()
		{
			double result;
			InvokeHelper(0x7f, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
			return result;
		}
		void put_Left(double newValue)
		{
			static BYTE parms[] = VTS_R8 ;
			InvokeHelper(0x7f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		double get_Top()
		{
			double result;
			InvokeHelper(0x7e, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
			return result;
		}
		void put_Top(double newValue)
		{
			static BYTE parms[] = VTS_R8 ;
			InvokeHelper(0x7e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		double get_Width()
		{
			double result;
			InvokeHelper(0x7a, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
			return result;
		}
		void put_Width(double newValue)
		{
			static BYTE parms[] = VTS_R8 ;
			InvokeHelper(0x7a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		VARIANT get_AutoScaleFont()
		{
			VARIANT result;
			InvokeHelper(0x5f5, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		void put_AutoScaleFont(VARIANT& newValue)
		{
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x5f5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, &newValue);
		}
		LPDISPATCH get_Format()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020017, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		BOOL get_RoundedCorners()
		{
			BOOL result;
			InvokeHelper(0x60020018, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_RoundedCorners(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x60020018, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x94, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x95, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
	};
	
	// IMsoChartData ��װ��
	class IMsoChartData : public COleDispatchDriver
	{
	public:
		IMsoChartData(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		IMsoChartData(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		IMsoChartData(const IMsoChartData& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// IMsoChartData ����
	public:
		LPDISPATCH get_Workbook()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		void Activate()
		{
			InvokeHelper(0x60020001, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		BOOL get_IsLinked()
		{
			BOOL result;
			InvokeHelper(0x60020002, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void BreakLink()
		{
			InvokeHelper(0x60020003, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void ActivateChartDataWindow()
		{
			InvokeHelper(0x60020004, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
	};
	
	// IMsoChartFormat ��װ��
	class IMsoChartFormat : public COleDispatchDriver
	{
	public:
		IMsoChartFormat(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		IMsoChartFormat(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		IMsoChartFormat(const IMsoChartFormat& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// IMsoChartFormat ����
	public:
		LPDISPATCH get_Fill()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Glow()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Line()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020002, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020003, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_PictureFormat()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020004, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Shadow()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020005, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_SoftEdge()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020006, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_TextFrame2()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020007, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_ThreeD()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020008, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x94, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x95, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Adjustments()
		{
			LPDISPATCH result;
			InvokeHelper(0xc8, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_AutoShapeType()
		{
			long result;
			InvokeHelper(0xc9, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_AutoShapeType(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0xc9, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
	};
	
	// IMsoChartGroup ��װ��
	class IMsoChartGroup : public COleDispatchDriver
	{
	public:
		IMsoChartGroup(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		IMsoChartGroup(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		IMsoChartGroup(const IMsoChartGroup& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// IMsoChartGroup ����
	public:
		void put_AxisGroup(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_AxisGroup()
		{
			long result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_DoughnutHoleSize(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60020002, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_DoughnutHoleSize()
		{
			long result;
			InvokeHelper(0x60020002, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_DownBars()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020004, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_DropLines()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020005, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		void put_FirstSliceAngle(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60020006, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_FirstSliceAngle()
		{
			long result;
			InvokeHelper(0x60020006, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_GapWidth(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60020008, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_GapWidth()
		{
			long result;
			InvokeHelper(0x60020008, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_HasDropLines(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x6002000a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_HasDropLines()
		{
			BOOL result;
			InvokeHelper(0x6002000a, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_HasHiLoLines(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x6002000c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_HasHiLoLines()
		{
			BOOL result;
			InvokeHelper(0x6002000c, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_HasRadarAxisLabels(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x6002000e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_HasRadarAxisLabels()
		{
			BOOL result;
			InvokeHelper(0x6002000e, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_HasSeriesLines(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x60020010, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_HasSeriesLines()
		{
			BOOL result;
			InvokeHelper(0x60020010, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_HasUpDownBars(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x60020012, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_HasUpDownBars()
		{
			BOOL result;
			InvokeHelper(0x60020012, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_HiLoLines()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020014, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Index()
		{
			long result;
			InvokeHelper(0x60020015, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_Overlap(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60020016, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_Overlap()
		{
			long result;
			InvokeHelper(0x60020016, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_RadarAxisLabels()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020018, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH SeriesCollection(VARIANT& Index)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x60020019, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, &Index);
			return result;
		}
		LPDISPATCH get_SeriesLines()
		{
			LPDISPATCH result;
			InvokeHelper(0x6002001a, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		void put_SubType(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x6002001b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_SubType()
		{
			long result;
			InvokeHelper(0x6002001b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_Type(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x6002001d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_Type()
		{
			long result;
			InvokeHelper(0x6002001d, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_UpBars()
		{
			LPDISPATCH result;
			InvokeHelper(0x6002001f, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		void put_VaryByCategories(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x60020020, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_VaryByCategories()
		{
			BOOL result;
			InvokeHelper(0x60020020, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		long get_SizeRepresents()
		{
			long result;
			InvokeHelper(0x60020022, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_SizeRepresents(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60020022, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		void put_BubbleScale(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60020024, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_BubbleScale()
		{
			long result;
			InvokeHelper(0x60020024, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_ShowNegativeBubbles(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x60020026, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_ShowNegativeBubbles()
		{
			BOOL result;
			InvokeHelper(0x60020026, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_SplitType(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60020028, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_SplitType()
		{
			long result;
			InvokeHelper(0x60020028, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		VARIANT get_SplitValue()
		{
			VARIANT result;
			InvokeHelper(0x6002002a, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		void put_SplitValue(VARIANT& newValue)
		{
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x6002002a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, &newValue);
		}
		long get_SecondPlotSize()
		{
			long result;
			InvokeHelper(0x6002002c, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_SecondPlotSize(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x6002002c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_Has3DShading()
		{
			BOOL result;
			InvokeHelper(0x6002002e, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_Has3DShading(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x6002002e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x94, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x95, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x96, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH CategoryCollection(VARIANT& Index)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x97, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, &Index);
			return result;
		}
		LPDISPATCH FullCategoryCollection(VARIANT& Index)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x98, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, &Index);
			return result;
		}
	};
	
	// IMsoChartTitle ��װ��
	class IMsoChartTitle : public COleDispatchDriver
	{
	public:
		IMsoChartTitle(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		IMsoChartTitle(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		IMsoChartTitle(const IMsoChartTitle& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// IMsoChartTitle ����
	public:
		void put_Caption(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_Caption()
		{
			CString result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Characters(VARIANT& Start, VARIANT& Length)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_VARIANT VTS_VARIANT ;
			InvokeHelper(0x60020002, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, &Start, &Length);
			return result;
		}
		LPDISPATCH get_Font()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020003, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		void put_HorizontalAlignment(VARIANT& newValue)
		{
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x60020004, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, &newValue);
		}
		VARIANT get_HorizontalAlignment()
		{
			VARIANT result;
			InvokeHelper(0x60020004, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		double get_Left()
		{
			double result;
			InvokeHelper(0x60020006, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
			return result;
		}
		void put_Left(double newValue)
		{
			static BYTE parms[] = VTS_R8 ;
			InvokeHelper(0x60020006, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		void put_Orientation(VARIANT& newValue)
		{
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x60020008, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, &newValue);
		}
		VARIANT get_Orientation()
		{
			VARIANT result;
			InvokeHelper(0x60020008, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		BOOL get_Shadow()
		{
			BOOL result;
			InvokeHelper(0x6002000a, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_Shadow(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x6002000a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		void put_Text(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x6002000c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_Text()
		{
			CString result;
			InvokeHelper(0x6002000c, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		double get_Top()
		{
			double result;
			InvokeHelper(0x6002000e, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
			return result;
		}
		void put_Top(double newValue)
		{
			static BYTE parms[] = VTS_R8 ;
			InvokeHelper(0x6002000e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		void put_VerticalAlignment(VARIANT& newValue)
		{
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x60020010, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, &newValue);
		}
		VARIANT get_VerticalAlignment()
		{
			VARIANT result;
			InvokeHelper(0x60020010, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		long get_ReadingOrder()
		{
			long result;
			InvokeHelper(0x60020012, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_ReadingOrder(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60020012, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		void put_AutoScaleFont(VARIANT& newValue)
		{
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x60020014, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, &newValue);
		}
		VARIANT get_AutoScaleFont()
		{
			VARIANT result;
			InvokeHelper(0x60020014, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Interior()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020016, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Fill()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020017, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		VARIANT Delete()
		{
			VARIANT result;
			InvokeHelper(0x60020018, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Border()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020019, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		CString get_Name()
		{
			CString result;
			InvokeHelper(0x6002001a, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x6002001b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		VARIANT Select()
		{
			VARIANT result;
			InvokeHelper(0x6002001c, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		BOOL get_IncludeInLayout()
		{
			BOOL result;
			InvokeHelper(0x972, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_IncludeInLayout(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x972, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_Position()
		{
			long result;
			InvokeHelper(0x687, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_Position(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x687, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		LPDISPATCH get_Format()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020021, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		double get_Height()
		{
			double result;
			InvokeHelper(0x60020022, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x94, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x95, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		double get_Width()
		{
			double result;
			InvokeHelper(0x60020025, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
			return result;
		}
		void put_Formula(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x60020026, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_Formula()
		{
			CString result;
			InvokeHelper(0x60020026, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_FormulaR1C1(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x60020028, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_FormulaR1C1()
		{
			CString result;
			InvokeHelper(0x60020028, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_FormulaLocal(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x6002002a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_FormulaLocal()
		{
			CString result;
			InvokeHelper(0x6002002a, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_FormulaR1C1Local(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x6002002c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_FormulaR1C1Local()
		{
			CString result;
			InvokeHelper(0x6002002c, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
	};
	
	// IMsoContactCard ��װ��
	class IMsoContactCard : public COleDispatchDriver
	{
	public:
		IMsoContactCard(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		IMsoContactCard(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		IMsoContactCard(const IMsoContactCard& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// IMsoContactCard ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		CString get_Address()
		{
			CString result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		long get_AddressType()
		{
			long result;
			InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		long get_CardType()
		{
			long result;
			InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
	};
	
	// IMsoCorners ��װ��
	class IMsoCorners : public COleDispatchDriver
	{
	public:
		IMsoCorners(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		IMsoCorners(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		IMsoCorners(const IMsoCorners& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// IMsoCorners ����
	public:
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x96, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		CString get_Name()
		{
			CString result;
			InvokeHelper(0x6e, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		VARIANT Select()
		{
			VARIANT result;
			InvokeHelper(0xeb, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x94, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x95, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
	};
	
	// IMsoDataTable ��װ��
	class IMsoDataTable : public COleDispatchDriver
	{
	public:
		IMsoDataTable(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		IMsoDataTable(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		IMsoDataTable(const IMsoDataTable& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// IMsoDataTable ����
	public:
		void put_ShowLegendKey(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_ShowLegendKey()
		{
			BOOL result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_HasBorderHorizontal(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x60020002, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_HasBorderHorizontal()
		{
			BOOL result;
			InvokeHelper(0x60020002, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_HasBorderVertical(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x60020004, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_HasBorderVertical()
		{
			BOOL result;
			InvokeHelper(0x60020004, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_HasBorderOutline(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x60020006, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_HasBorderOutline()
		{
			BOOL result;
			InvokeHelper(0x60020006, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Border()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020008, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Font()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020009, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		void Select()
		{
			InvokeHelper(0x6002000a, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void Delete()
		{
			InvokeHelper(0x6002000b, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x6002000c, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		VARIANT get_AutoScaleFont()
		{
			VARIANT result;
			InvokeHelper(0x6002000d, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		void put_AutoScaleFont(VARIANT& newValue)
		{
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x6002000d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, &newValue);
		}
		LPDISPATCH get_Format()
		{
			LPDISPATCH result;
			InvokeHelper(0x6002000f, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x94, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x95, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
	};
	
	// MsoDebugOptions ��װ��
	class MsoDebugOptions : public COleDispatchDriver
	{
	public:
		MsoDebugOptions(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		MsoDebugOptions(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		MsoDebugOptions(const MsoDebugOptions& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// MsoDebugOptions ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		long get_FeatureReports()
		{
			long result;
			InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_FeatureReports(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_OutputToDebugger()
		{
			BOOL result;
			InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_OutputToDebugger(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_OutputToFile()
		{
			BOOL result;
			InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_OutputToFile(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_OutputToMessageBox()
		{
			BOOL result;
			InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_OutputToMessageBox(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		LPUNKNOWN get_UnitTestManager()
		{
			LPUNKNOWN result;
			InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
			return result;
		}
		void AddIgnoredAssertTag(LPCTSTR bstrTagToIgnore)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x9, DISPATCH_METHOD, VT_EMPTY, NULL, parms, bstrTagToIgnore);
		}
		void RemoveIgnoredAssertTag(LPCTSTR bstrTagToIgnore)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0xa, DISPATCH_METHOD, VT_EMPTY, NULL, parms, bstrTagToIgnore);
		}
	};
	
	// MsoDebugOptions_UT ��װ��
	class MsoDebugOptions_UT : public COleDispatchDriver
	{
	public:
		MsoDebugOptions_UT(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		MsoDebugOptions_UT(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		MsoDebugOptions_UT(const MsoDebugOptions_UT& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// MsoDebugOptions_UT ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		CString get_Name()
		{
			CString result;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		CString get_CollectionName()
		{
			CString result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH Run()
		{
			LPDISPATCH result;
			InvokeHelper(0x2, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
	};
	
	// MsoDebugOptions_UTManager ��װ��
	class MsoDebugOptions_UTManager : public COleDispatchDriver
	{
	public:
		MsoDebugOptions_UTManager(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		MsoDebugOptions_UTManager(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		MsoDebugOptions_UTManager(const MsoDebugOptions_UTManager& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// MsoDebugOptions_UTManager ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_UnitTests()
		{
			LPDISPATCH result;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		void NotifyStartOfTestSuiteRun()
		{
			InvokeHelper(0x1, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void NotifyEndOfTestSuiteRun()
		{
			InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		BOOL get_ReportErrors()
		{
			BOOL result;
			InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_ReportErrors(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
	};
	
	// MsoDebugOptions_UTRunResult ��װ��
	class MsoDebugOptions_UTRunResult : public COleDispatchDriver
	{
	public:
		MsoDebugOptions_UTRunResult(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		MsoDebugOptions_UTRunResult(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		MsoDebugOptions_UTRunResult(const MsoDebugOptions_UTRunResult& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// MsoDebugOptions_UTRunResult ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		BOOL get_Passed()
		{
			BOOL result;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		CString get_ErrorString()
		{
			CString result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
	};
	
	// MsoDebugOptions_UTs ��װ��
	class MsoDebugOptions_UTs : public COleDispatchDriver
	{
	public:
		MsoDebugOptions_UTs(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		MsoDebugOptions_UTs(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		MsoDebugOptions_UTs(const MsoDebugOptions_UTs& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// MsoDebugOptions_UTs ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Item(long Index)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, Index);
			return result;
		}
		long get_Count()
		{
			long result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPUNKNOWN get__NewEnum()
		{
			LPUNKNOWN result;
			InvokeHelper(0xfffffffc, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH GetUnitTestsInCollection(LPCTSTR bstrCollectionName)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x2, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, bstrCollectionName);
			return result;
		}
		LPDISPATCH GetUnitTest(LPCTSTR bstrCollectionName, LPCTSTR bstrUnitTestName)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_BSTR VTS_BSTR ;
			InvokeHelper(0x3, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, bstrCollectionName, bstrUnitTestName);
			return result;
		}
		LPDISPATCH GetMatchingUnitTestsInCollection(LPCTSTR bstrCollectionName, LPCTSTR bstrUnitTestNameFilter)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_BSTR VTS_BSTR ;
			InvokeHelper(0x4, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, bstrCollectionName, bstrUnitTestNameFilter);
			return result;
		}
	};
	
	// IMsoDiagram ��װ��
	class IMsoDiagram : public COleDispatchDriver
	{
	public:
		IMsoDiagram(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		IMsoDiagram(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		IMsoDiagram(const IMsoDiagram& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// IMsoDiagram ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x64, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Nodes()
		{
			LPDISPATCH result;
			InvokeHelper(0x65, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Type()
		{
			long result;
			InvokeHelper(0x66, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		long get_AutoLayout()
		{
			long result;
			InvokeHelper(0x67, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_AutoLayout(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x67, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_Reverse()
		{
			long result;
			InvokeHelper(0x68, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_Reverse(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x68, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_AutoFormat()
		{
			long result;
			InvokeHelper(0x69, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_AutoFormat(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x69, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		void Convert(long Type)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0xa, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Type);
		}
		void FitText()
		{
			InvokeHelper(0xb, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
	};
	
	// IMsoDispCagNotifySink ��װ��
	class IMsoDispCagNotifySink : public COleDispatchDriver
	{
	public:
		IMsoDispCagNotifySink(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		IMsoDispCagNotifySink(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		IMsoDispCagNotifySink(const IMsoDispCagNotifySink& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// IMsoDispCagNotifySink ����
	public:
		void InsertClip(LPUNKNOWN pClipMoniker, LPUNKNOWN pItemMoniker)
		{
			static BYTE parms[] = VTS_UNKNOWN VTS_UNKNOWN ;
			InvokeHelper(0x1, DISPATCH_METHOD, VT_EMPTY, NULL, parms, pClipMoniker, pItemMoniker);
		}
		void WindowIsClosing()
		{
			InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
	};
	
	// IMsoDisplayUnitLabel ��װ��
	class IMsoDisplayUnitLabel : public COleDispatchDriver
	{
	public:
		IMsoDisplayUnitLabel(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		IMsoDisplayUnitLabel(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		IMsoDisplayUnitLabel(const IMsoDisplayUnitLabel& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// IMsoDisplayUnitLabel ����
	public:
		void put_Caption(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_Caption()
		{
			CString result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Characters(VARIANT& Start, VARIANT& Length)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_VARIANT VTS_VARIANT ;
			InvokeHelper(0x60020002, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, &Start, &Length);
			return result;
		}
		LPDISPATCH get_Font()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020003, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		void put_HorizontalAlignment(VARIANT& newValue)
		{
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x60020004, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, &newValue);
		}
		VARIANT get_HorizontalAlignment()
		{
			VARIANT result;
			InvokeHelper(0x60020004, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		double get_Left()
		{
			double result;
			InvokeHelper(0x60020006, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
			return result;
		}
		void put_Left(double newValue)
		{
			static BYTE parms[] = VTS_R8 ;
			InvokeHelper(0x60020006, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		void put_Orientation(VARIANT& newValue)
		{
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x60020008, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, &newValue);
		}
		VARIANT get_Orientation()
		{
			VARIANT result;
			InvokeHelper(0x60020008, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		BOOL get_Shadow()
		{
			BOOL result;
			InvokeHelper(0x6002000a, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_Shadow(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x6002000a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		void put_Text(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x6002000c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_Text()
		{
			CString result;
			InvokeHelper(0x6002000c, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		double get_Top()
		{
			double result;
			InvokeHelper(0x6002000e, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
			return result;
		}
		void put_Top(double newValue)
		{
			static BYTE parms[] = VTS_R8 ;
			InvokeHelper(0x6002000e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		void put_VerticalAlignment(VARIANT& newValue)
		{
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x60020010, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, &newValue);
		}
		VARIANT get_VerticalAlignment()
		{
			VARIANT result;
			InvokeHelper(0x60020010, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		long get_ReadingOrder()
		{
			long result;
			InvokeHelper(0x60020012, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_ReadingOrder(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60020012, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		void put_AutoScaleFont(VARIANT& newValue)
		{
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x60020014, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, &newValue);
		}
		VARIANT get_AutoScaleFont()
		{
			VARIANT result;
			InvokeHelper(0x60020014, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Interior()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020016, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Fill()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020017, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		VARIANT Delete()
		{
			VARIANT result;
			InvokeHelper(0x60020018, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Border()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020019, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		CString get_Name()
		{
			CString result;
			InvokeHelper(0x6002001a, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x6002001b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		VARIANT Select()
		{
			VARIANT result;
			InvokeHelper(0x6002001c, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		BOOL get_IncludeInLayout()
		{
			BOOL result;
			InvokeHelper(0x972, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_IncludeInLayout(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x972, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_Position()
		{
			long result;
			InvokeHelper(0x687, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_Position(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x687, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		LPDISPATCH get_Format()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020021, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		double get_Height()
		{
			double result;
			InvokeHelper(0x60020022, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x94, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x95, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		double get_Width()
		{
			double result;
			InvokeHelper(0x60020025, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
			return result;
		}
		void put_Formula(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x60020026, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_Formula()
		{
			CString result;
			InvokeHelper(0x60020026, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_FormulaR1C1(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x60020028, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_FormulaR1C1()
		{
			CString result;
			InvokeHelper(0x60020028, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_FormulaLocal(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x6002002a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_FormulaLocal()
		{
			CString result;
			InvokeHelper(0x6002002a, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_FormulaR1C1Local(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x6002002c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_FormulaR1C1Local()
		{
			CString result;
			InvokeHelper(0x6002002c, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
	};
	
	// IMsoDownBars ��װ��
	class IMsoDownBars : public COleDispatchDriver
	{
	public:
		IMsoDownBars(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		IMsoDownBars(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		IMsoDownBars(const IMsoDownBars& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// IMsoDownBars ����
	public:
		CString get_Name()
		{
			CString result;
			InvokeHelper(0x6e, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		VARIANT Select()
		{
			VARIANT result;
			InvokeHelper(0xeb, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x96, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Border()
		{
			LPDISPATCH result;
			InvokeHelper(0x80, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		VARIANT Delete()
		{
			VARIANT result;
			InvokeHelper(0x75, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Interior()
		{
			LPDISPATCH result;
			InvokeHelper(0x81, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Fill()
		{
			LPDISPATCH result;
			InvokeHelper(0x67f, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Format()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020007, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x94, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x95, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
	};
	
	// IMsoDropLines ��װ��
	class IMsoDropLines : public COleDispatchDriver
	{
	public:
		IMsoDropLines(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		IMsoDropLines(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		IMsoDropLines(const IMsoDropLines& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// IMsoDropLines ����
	public:
		CString get_Name()
		{
			CString result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void Select()
		{
			InvokeHelper(0x60020001, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020002, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Border()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020003, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		void Delete()
		{
			InvokeHelper(0x60020004, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		LPDISPATCH get_Format()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020005, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x94, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x95, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
	};
	
	// IMsoEnvelopeVB ��װ��
	class IMsoEnvelopeVB : public COleDispatchDriver
	{
	public:
		IMsoEnvelopeVB(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		IMsoEnvelopeVB(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		IMsoEnvelopeVB(const IMsoEnvelopeVB& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// IMsoEnvelopeVB ����
	public:
		CString get_Introduction()
		{
			CString result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_Introduction(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		LPDISPATCH get_Item()
		{
			LPDISPATCH result;
			InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_CommandBars()
		{
			LPDISPATCH result;
			InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
	};
	
	// IMsoEnvelopeVBEvents ��װ��
	class IMsoEnvelopeVBEvents : public COleDispatchDriver
	{
	public:
		IMsoEnvelopeVBEvents(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		IMsoEnvelopeVBEvents(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		IMsoEnvelopeVBEvents(const IMsoEnvelopeVBEvents& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// IMsoEnvelopeVBEvents ����
	public:
		void EnvelopeShow()
		{
			InvokeHelper(0x1, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void EnvelopeHide()
		{
			InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
	};
	
	// IMsoEServicesDialog ��װ��
	class IMsoEServicesDialog : public COleDispatchDriver
	{
	public:
		IMsoEServicesDialog(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		IMsoEServicesDialog(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		IMsoEServicesDialog(const IMsoEServicesDialog& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// IMsoEServicesDialog ����
	public:
		void Close(BOOL ApplyWebComponentChanges)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x60020000, DISPATCH_METHOD, VT_EMPTY, NULL, parms, ApplyWebComponentChanges);
		}
		void AddTrustedDomain(LPCTSTR Domain)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x60020001, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Domain);
		}
		CString get_ApplicationName()
		{
			CString result;
			InvokeHelper(0x60020002, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020003, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_WebComponent()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020004, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_ClipArt()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020005, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
	};
	
	// IMsoFloor ��װ��
	class IMsoFloor : public COleDispatchDriver
	{
	public:
		IMsoFloor(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		IMsoFloor(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		IMsoFloor(const IMsoFloor& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// IMsoFloor ����
	public:
		CString get_Name()
		{
			CString result;
			InvokeHelper(0x6e, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		VARIANT Select()
		{
			VARIANT result;
			InvokeHelper(0xeb, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x96, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Border()
		{
			LPDISPATCH result;
			InvokeHelper(0x80, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		VARIANT ClearFormats()
		{
			VARIANT result;
			InvokeHelper(0x70, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Interior()
		{
			LPDISPATCH result;
			InvokeHelper(0x81, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Fill()
		{
			LPDISPATCH result;
			InvokeHelper(0x67f, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		VARIANT get_PictureType()
		{
			VARIANT result;
			InvokeHelper(0xa1, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		void put_PictureType(VARIANT& newValue)
		{
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0xa1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, &newValue);
		}
		void Paste()
		{
			InvokeHelper(0xd3, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		long get_Thickness()
		{
			long result;
			InvokeHelper(0x973, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_Thickness(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x973, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		LPDISPATCH get_Format()
		{
			LPDISPATCH result;
			InvokeHelper(0x6002000c, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x94, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x95, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
	};
	
	// IMsoHiLoLines ��װ��
	class IMsoHiLoLines : public COleDispatchDriver
	{
	public:
		IMsoHiLoLines(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		IMsoHiLoLines(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		IMsoHiLoLines(const IMsoHiLoLines& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// IMsoHiLoLines ����
	public:
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		CString get_Name()
		{
			CString result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void Select()
		{
			InvokeHelper(0x60020002, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		LPDISPATCH get_Border()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020003, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		void Delete()
		{
			InvokeHelper(0x60020004, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		LPDISPATCH get_Format()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020005, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x94, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x95, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
	};
	
	// IMsoHyperlinks ��װ��
	class IMsoHyperlinks : public COleDispatchDriver
	{
	public:
		IMsoHyperlinks(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		IMsoHyperlinks(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		IMsoHyperlinks(const IMsoHyperlinks& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}
	};
	
	// IMsoInterior ��װ��
	class IMsoInterior : public COleDispatchDriver
	{
	public:
		IMsoInterior(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		IMsoInterior(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		IMsoInterior(const IMsoInterior& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// IMsoInterior ����
	public:
		void put_Color(VARIANT& newValue)
		{
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, &newValue);
		}
		VARIANT get_Color()
		{
			VARIANT result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		void put_ColorIndex(VARIANT& newValue)
		{
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x60020002, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, &newValue);
		}
		VARIANT get_ColorIndex()
		{
			VARIANT result;
			InvokeHelper(0x60020002, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		void put_InvertIfNegative(VARIANT& newValue)
		{
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x60020004, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, &newValue);
		}
		VARIANT get_InvertIfNegative()
		{
			VARIANT result;
			InvokeHelper(0x60020004, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		void put_Pattern(VARIANT& newValue)
		{
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x60020006, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, &newValue);
		}
		VARIANT get_Pattern()
		{
			VARIANT result;
			InvokeHelper(0x60020006, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		void put_PatternColor(VARIANT& newValue)
		{
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x60020008, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, &newValue);
		}
		VARIANT get_PatternColor()
		{
			VARIANT result;
			InvokeHelper(0x60020008, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		void put_PatternColorIndex(VARIANT& newValue)
		{
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x6002000a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, &newValue);
		}
		VARIANT get_PatternColorIndex()
		{
			VARIANT result;
			InvokeHelper(0x6002000a, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x94, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x95, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x96, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
	};

	// IMsoLeaderLines ��װ��
	class IMsoLeaderLines : public COleDispatchDriver
	{
	public:
		IMsoLeaderLines(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		IMsoLeaderLines(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		IMsoLeaderLines(const IMsoLeaderLines& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// IMsoLeaderLines ����
	public:
		void Select()
		{
			InvokeHelper(0xeb, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		LPDISPATCH get_Border()
		{
			LPDISPATCH result;
			InvokeHelper(0x80, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		void Delete()
		{
			InvokeHelper(0x75, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		LPDISPATCH get_Format()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020003, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x94, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x95, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x96, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
	};
	
	// IMsoLegend ��װ��
	class IMsoLegend : public COleDispatchDriver
	{
	public:
		IMsoLegend(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		IMsoLegend(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		IMsoLegend(const IMsoLegend& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// IMsoLegend ����
	public:
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x96, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		CString get_Name()
		{
			CString result;
			InvokeHelper(0x6e, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		VARIANT Select()
		{
			VARIANT result;
			InvokeHelper(0xeb, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Border()
		{
			LPDISPATCH result;
			InvokeHelper(0x80, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		VARIANT Delete()
		{
			VARIANT result;
			InvokeHelper(0x75, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Font()
		{
			LPDISPATCH result;
			InvokeHelper(0x92, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH LegendEntries(VARIANT& Index)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0xad, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, &Index);
			return result;
		}
		long get_Position()
		{
			long result;
			InvokeHelper(0x85, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_Position(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x85, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_Shadow()
		{
			BOOL result;
			InvokeHelper(0x67, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_Shadow(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x67, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		VARIANT Clear()
		{
			VARIANT result;
			InvokeHelper(0x6f, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		double get_Height()
		{
			double result;
			InvokeHelper(0x7b, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
			return result;
		}
		void put_Height(double newValue)
		{
			static BYTE parms[] = VTS_R8 ;
			InvokeHelper(0x7b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		LPDISPATCH get_Interior()
		{
			LPDISPATCH result;
			InvokeHelper(0x81, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Fill()
		{
			LPDISPATCH result;
			InvokeHelper(0x67f, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		double get_Left()
		{
			double result;
			InvokeHelper(0x7f, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
			return result;
		}
		void put_Left(double newValue)
		{
			static BYTE parms[] = VTS_R8 ;
			InvokeHelper(0x7f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		double get_Top()
		{
			double result;
			InvokeHelper(0x7e, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
			return result;
		}
		void put_Top(double newValue)
		{
			static BYTE parms[] = VTS_R8 ;
			InvokeHelper(0x7e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		double get_Width()
		{
			double result;
			InvokeHelper(0x7a, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
			return result;
		}
		void put_Width(double newValue)
		{
			static BYTE parms[] = VTS_R8 ;
			InvokeHelper(0x7a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		VARIANT get_AutoScaleFont()
		{
			VARIANT result;
			InvokeHelper(0x5f5, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		void put_AutoScaleFont(VARIANT& newValue)
		{
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x5f5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, &newValue);
		}
		BOOL get_IncludeInLayout()
		{
			BOOL result;
			InvokeHelper(0x972, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_IncludeInLayout(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x972, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		LPDISPATCH get_Format()
		{
			LPDISPATCH result;
			InvokeHelper(0x6002001a, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x94, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x95, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
	};
	
	// IMsoPlotArea ��װ��
	class IMsoPlotArea : public COleDispatchDriver
	{
	public:
		IMsoPlotArea(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		IMsoPlotArea(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		IMsoPlotArea(const IMsoPlotArea& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// IMsoPlotArea ����
	public:
		CString get_Name()
		{
			CString result;
			InvokeHelper(0x6e, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		VARIANT Select()
		{
			VARIANT result;
			InvokeHelper(0xeb, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x96, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Border()
		{
			LPDISPATCH result;
			InvokeHelper(0x80, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		VARIANT ClearFormats()
		{
			VARIANT result;
			InvokeHelper(0x70, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		double get_Height()
		{
			double result;
			InvokeHelper(0x7b, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
			return result;
		}
		void put_Height(double newValue)
		{
			static BYTE parms[] = VTS_R8 ;
			InvokeHelper(0x7b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		LPDISPATCH get_Interior()
		{
			LPDISPATCH result;
			InvokeHelper(0x81, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Fill()
		{
			LPDISPATCH result;
			InvokeHelper(0x67f, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		double get_Left()
		{
			double result;
			InvokeHelper(0x7f, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
			return result;
		}
		void put_Left(double newValue)
		{
			static BYTE parms[] = VTS_R8 ;
			InvokeHelper(0x7f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		double get_Top()
		{
			double result;
			InvokeHelper(0x7e, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
			return result;
		}
		void put_Top(double newValue)
		{
			static BYTE parms[] = VTS_R8 ;
			InvokeHelper(0x7e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		double get_Width()
		{
			double result;
			InvokeHelper(0x7a, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
			return result;
		}
		void put_Width(double newValue)
		{
			static BYTE parms[] = VTS_R8 ;
			InvokeHelper(0x7a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		double get_InsideLeft()
		{
			double result;
			InvokeHelper(0x683, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
			return result;
		}
		void put_InsideLeft(double newValue)
		{
			static BYTE parms[] = VTS_R8 ;
			InvokeHelper(0x683, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		double get_InsideTop()
		{
			double result;
			InvokeHelper(0x684, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
			return result;
		}
		void put_InsideTop(double newValue)
		{
			static BYTE parms[] = VTS_R8 ;
			InvokeHelper(0x684, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		double get_InsideWidth()
		{
			double result;
			InvokeHelper(0x685, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
			return result;
		}
		void put_InsideWidth(double newValue)
		{
			static BYTE parms[] = VTS_R8 ;
			InvokeHelper(0x685, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		double get_InsideHeight()
		{
			double result;
			InvokeHelper(0x686, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
			return result;
		}
		void put_InsideHeight(double newValue)
		{
			static BYTE parms[] = VTS_R8 ;
			InvokeHelper(0x686, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_Position()
		{
			long result;
			InvokeHelper(0x687, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_Position(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x687, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		LPDISPATCH get_Format()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020019, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x94, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x95, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
	};
	
	// IMsoSeriesLines ��װ��
	class IMsoSeriesLines : public COleDispatchDriver
	{
	public:
		IMsoSeriesLines(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		IMsoSeriesLines(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		IMsoSeriesLines(const IMsoSeriesLines& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// IMsoSeriesLines ����
	public:
		CString get_Name()
		{
			CString result;
			InvokeHelper(0x6e, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		VARIANT Select()
		{
			VARIANT result;
			InvokeHelper(0xeb, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x96, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Border()
		{
			LPDISPATCH result;
			InvokeHelper(0x80, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		VARIANT Delete()
		{
			VARIANT result;
			InvokeHelper(0x75, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Format()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020005, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x94, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x95, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
	};
	
	// IMsoTickLabels ��װ��
	class IMsoTickLabels : public COleDispatchDriver
	{
	public:
		IMsoTickLabels(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		IMsoTickLabels(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		IMsoTickLabels(const IMsoTickLabels& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// IMsoTickLabels ����
	public:
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		VARIANT Delete()
		{
			VARIANT result;
			InvokeHelper(0x60020001, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Font()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020002, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		CString get_Name()
		{
			CString result;
			InvokeHelper(0x60020003, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		CString get_NumberFormat()
		{
			CString result;
			InvokeHelper(0x60020004, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_NumberFormat(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x60020004, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_NumberFormatLinked()
		{
			BOOL result;
			InvokeHelper(0x60020006, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_NumberFormatLinked(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x60020006, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		VARIANT get_NumberFormatLocal()
		{
			VARIANT result;
			InvokeHelper(0x60020008, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		void put_NumberFormatLocal(VARIANT& newValue)
		{
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x60020008, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, &newValue);
		}
		long get_Orientation()
		{
			long result;
			InvokeHelper(0x6002000a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_Orientation(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x6002000a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		VARIANT Select()
		{
			VARIANT result;
			InvokeHelper(0x6002000c, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		long get_ReadingOrder()
		{
			long result;
			InvokeHelper(0x6002000d, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_ReadingOrder(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x6002000d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		VARIANT get_AutoScaleFont()
		{
			VARIANT result;
			InvokeHelper(0x6002000f, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		void put_AutoScaleFont(VARIANT& newValue)
		{
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x6002000f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, &newValue);
		}
		long get_Depth()
		{
			long result;
			InvokeHelper(0x60020011, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		long get_Offset()
		{
			long result;
			InvokeHelper(0x60020012, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_Offset(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60020012, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_Alignment()
		{
			long result;
			InvokeHelper(0x60020014, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_Alignment(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60020014, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_MultiLevel()
		{
			BOOL result;
			InvokeHelper(0x60020016, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_MultiLevel(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x60020016, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		LPDISPATCH get_Format()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020018, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x94, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x95, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
	};
	
	// IMsoUpBars ��װ��
	class IMsoUpBars : public COleDispatchDriver
	{
	public:
		IMsoUpBars(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		IMsoUpBars(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		IMsoUpBars(const IMsoUpBars& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// IMsoUpBars ����
	public:
		CString get_Name()
		{
			CString result;
			InvokeHelper(0x6e, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		VARIANT Select()
		{
			VARIANT result;
			InvokeHelper(0xeb, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x96, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Border()
		{
			LPDISPATCH result;
			InvokeHelper(0x80, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		VARIANT Delete()
		{
			VARIANT result;
			InvokeHelper(0x75, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Interior()
		{
			LPDISPATCH result;
			InvokeHelper(0x81, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Fill()
		{
			LPDISPATCH result;
			InvokeHelper(0x67f, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Format()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020007, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x94, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x95, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
	};
	
	// IMsoWalls ��װ��
	class IMsoWalls : public COleDispatchDriver
	{
	public:
		IMsoWalls(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		IMsoWalls(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		IMsoWalls(const IMsoWalls& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// IMsoWalls ����
	public:
		CString get_Name()
		{
			CString result;
			InvokeHelper(0x6e, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		VARIANT Select()
		{
			VARIANT result;
			InvokeHelper(0xeb, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x96, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Border()
		{
			LPDISPATCH result;
			InvokeHelper(0x80, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		VARIANT ClearFormats()
		{
			VARIANT result;
			InvokeHelper(0x70, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Interior()
		{
			LPDISPATCH result;
			InvokeHelper(0x81, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Fill()
		{
			LPDISPATCH result;
			InvokeHelper(0x67f, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		VARIANT get_PictureType()
		{
			VARIANT result;
			InvokeHelper(0xa1, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		void put_PictureType(VARIANT& newValue)
		{
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0xa1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, &newValue);
		}
		void Paste()
		{
			InvokeHelper(0xd3, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		VARIANT get_PictureUnit()
		{
			VARIANT result;
			InvokeHelper(0xa2, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		void put_PictureUnit(VARIANT& newValue)
		{
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0xa2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, &newValue);
		}
		long get_Thickness()
		{
			long result;
			InvokeHelper(0x973, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_Thickness(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x973, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		LPDISPATCH get_Format()
		{
			LPDISPATCH result;
			InvokeHelper(0x6002000e, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x94, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x95, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
	};
	
	// IFoundFiles ��װ��
	class IFoundFiles : public COleDispatchDriver
	{
	public:
		IFoundFiles(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		IFoundFiles(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		IFoundFiles(const IFoundFiles& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// IFoundFiles ����
	public:
		CString get_Item(long Index)
		{
			CString result;
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms, Index);
			return result;
		}
		long get_Count()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPUNKNOWN get__NewEnum()
		{
			LPUNKNOWN result;
			InvokeHelper(0xfffffffc, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
			return result;
		}
	};
	
	// LanguageSettings ��װ��
	class LanguageSettings : public COleDispatchDriver
	{
	public:
		LanguageSettings(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		LanguageSettings(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		LanguageSettings(const LanguageSettings& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// LanguageSettings ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		long get_LanguageID(long Id)
		{
			long result;
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms, Id);
			return result;
		}
		BOOL get_LanguagePreferredForEditing(long lid)
		{
			BOOL result;
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms, lid);
			return result;
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
	};
	
	// LineFormat ��װ��
	class LineFormat : public COleDispatchDriver
	{
	public:
		LineFormat(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		LineFormat(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		LineFormat(const LineFormat& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// LineFormat ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_BackColor()
		{
			LPDISPATCH result;
			InvokeHelper(0x64, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		void put_BackColor(LPDISPATCH newValue)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x64, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_BeginArrowheadLength()
		{
			long result;
			InvokeHelper(0x65, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_BeginArrowheadLength(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x65, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_BeginArrowheadStyle()
		{
			long result;
			InvokeHelper(0x66, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_BeginArrowheadStyle(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x66, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_BeginArrowheadWidth()
		{
			long result;
			InvokeHelper(0x67, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_BeginArrowheadWidth(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x67, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_DashStyle()
		{
			long result;
			InvokeHelper(0x68, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_DashStyle(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x68, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_EndArrowheadLength()
		{
			long result;
			InvokeHelper(0x69, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_EndArrowheadLength(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x69, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_EndArrowheadStyle()
		{
			long result;
			InvokeHelper(0x6a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_EndArrowheadStyle(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x6a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_EndArrowheadWidth()
		{
			long result;
			InvokeHelper(0x6b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_EndArrowheadWidth(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x6b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		LPDISPATCH get_ForeColor()
		{
			LPDISPATCH result;
			InvokeHelper(0x6c, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		void put_ForeColor(LPDISPATCH newValue)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x6c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_Pattern()
		{
			long result;
			InvokeHelper(0x6d, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_Pattern(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x6d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_Style()
		{
			long result;
			InvokeHelper(0x6e, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_Style(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x6e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		float get_Transparency()
		{
			float result;
			InvokeHelper(0x6f, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
			return result;
		}
		void put_Transparency(float newValue)
		{
			static BYTE parms[] = VTS_R4 ;
			InvokeHelper(0x6f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_Visible()
		{
			long result;
			InvokeHelper(0x70, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_Visible(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x70, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		float get_Weight()
		{
			float result;
			InvokeHelper(0x71, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
			return result;
		}
		void put_Weight(float newValue)
		{
			static BYTE parms[] = VTS_R4 ;
			InvokeHelper(0x71, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_InsetPen()
		{
			long result;
			InvokeHelper(0x72, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_InsetPen(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x72, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
	};
	
	// MetaProperties ��װ��
	class MetaProperties : public COleDispatchDriver
	{
	public:
		MetaProperties(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		MetaProperties(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		MetaProperties(const MetaProperties& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// MetaProperties ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Item(VARIANT& Index)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, &Index);
			return result;
		}
		LPDISPATCH GetItemByInternalName(LPCTSTR InternalName)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x1, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, InternalName);
			return result;
		}
		long get_Count()
		{
			long result;
			InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		CString Validate()
		{
			CString result;
			InvokeHelper(0x3, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		CString get_ValidationError()
		{
			CString result;
			InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		CString get_SchemaXml()
		{
			CString result;
			InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		LPUNKNOWN get__NewEnum()
		{
			LPUNKNOWN result;
			InvokeHelper(0xfffffffc, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
			return result;
		}
	};

	// MetaProperty ��װ��
	class MetaProperty : public COleDispatchDriver
	{
	public:
		MetaProperty(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		MetaProperty(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		MetaProperty(const MetaProperty& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// MetaProperty ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		VARIANT get_Value()
		{
			VARIANT result;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		void put_Value(VARIANT& newValue)
		{
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, &newValue);
		}
		CString get_Name()
		{
			CString result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		CString get_Id()
		{
			CString result;
			InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		BOOL get_IsReadOnly()
		{
			BOOL result;
			InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		BOOL get_IsRequired()
		{
			BOOL result;
			InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		long get_Type()
		{
			long result;
			InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		CString Validate()
		{
			CString result;
			InvokeHelper(0x6, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		CString get_ValidationError()
		{
			CString result;
			InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
	};
	
	// NewFile ��װ��
	class NewFile : public COleDispatchDriver
	{
	public:
		NewFile(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		NewFile(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		NewFile(const NewFile& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// NewFile ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		BOOL Add(LPCTSTR FileName, VARIANT& Section, VARIANT& DisplayName, VARIANT& Action)
		{
			BOOL result;
			static BYTE parms[] = VTS_BSTR VTS_VARIANT VTS_VARIANT VTS_VARIANT ;
			InvokeHelper(0x1, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, FileName, &Section, &DisplayName, &Action);
			return result;
		}
		BOOL Remove(LPCTSTR FileName, VARIANT& Section, VARIANT& DisplayName, VARIANT& Action)
		{
			BOOL result;
			static BYTE parms[] = VTS_BSTR VTS_VARIANT VTS_VARIANT VTS_VARIANT ;
			InvokeHelper(0x2, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, FileName, &Section, &DisplayName, &Action);
			return result;
		}
	};
	
	// ODSOColumn ��װ��
	class ODSOColumn : public COleDispatchDriver
	{
	public:
		ODSOColumn(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		ODSOColumn(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		ODSOColumn(const ODSOColumn& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// ODSOColumn ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		long get_Index()
		{
			long result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		CString get_Name()
		{
			CString result;
			InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		CString get_Value()
		{
			CString result;
			InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
	};
	
	// ODSOColumns ��װ��
	class ODSOColumns : public COleDispatchDriver
	{
	public:
		ODSOColumns(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		ODSOColumns(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		ODSOColumns(const ODSOColumns& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// ODSOColumns ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		long get_Count()
		{
			long result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH Item(VARIANT& varIndex)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x60030002, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, &varIndex);
			return result;
		}
	};
	
	// ODSOFilter ��װ��
	class ODSOFilter : public COleDispatchDriver
	{
	public:
		ODSOFilter(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		ODSOFilter(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		ODSOFilter(const ODSOFilter& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// ODSOFilter ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		long get_Index()
		{
			long result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		CString get_Column()
		{
			CString result;
			InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_Column(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_Comparison()
		{
			long result;
			InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_Comparison(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_CompareTo()
		{
			CString result;
			InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_CompareTo(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_Conjunction()
		{
			long result;
			InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_Conjunction(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
	};
	
	// ODSOFilters ��װ��
	class ODSOFilters : public COleDispatchDriver
	{
	public:
		ODSOFilters(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		ODSOFilters(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		ODSOFilters(const ODSOFilters& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// ODSOFilters ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		long get_Count()
		{
			long result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH Item(long Index)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60030002, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, Index);
			return result;
		}
		void Add(LPCTSTR Column, long Comparison, long Conjunction, LPCTSTR bstrCompareTo, BOOL DeferUpdate)
		{
			static BYTE parms[] = VTS_BSTR VTS_I4 VTS_I4 VTS_BSTR VTS_BOOL ;
			InvokeHelper(0x60030003, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Column, Comparison, Conjunction, bstrCompareTo, DeferUpdate);
		}
		void Delete(long Index, BOOL DeferUpdate)
		{
			static BYTE parms[] = VTS_I4 VTS_BOOL ;
			InvokeHelper(0x60030004, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Index, DeferUpdate);
		}
	};
	
	// OfficeDataSourceObject ��װ��
	class OfficeDataSourceObject : public COleDispatchDriver
	{
	public:
		OfficeDataSourceObject(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		OfficeDataSourceObject(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		OfficeDataSourceObject(const OfficeDataSourceObject& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// OfficeDataSourceObject ����
	public:
		CString get_ConnectString()
		{
			CString result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_ConnectString(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_Table()
		{
			CString result;
			InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_Table(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_DataSource()
		{
			CString result;
			InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_DataSource(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		LPDISPATCH get_Columns()
		{
			LPDISPATCH result;
			InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_RowCount()
		{
			long result;
			InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Filters()
		{
			LPDISPATCH result;
			InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long Move(long MsoMoveRow, long RowNbr)
		{
			long result;
			static BYTE parms[] = VTS_I4 VTS_I4 ;
			InvokeHelper(0x60020009, DISPATCH_METHOD, VT_I4, (void*)&result, parms, MsoMoveRow, RowNbr);
			return result;
		}
		void Open(LPCTSTR bstrSrc, LPCTSTR bstrConnect, LPCTSTR bstrTable, long fOpenExclusive, long fNeverPrompt)
		{
			static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 VTS_I4 ;
			InvokeHelper(0x6002000a, DISPATCH_METHOD, VT_EMPTY, NULL, parms, bstrSrc, bstrConnect, bstrTable, fOpenExclusive, fNeverPrompt);
		}
		void SetSortOrder(LPCTSTR SortField1, BOOL SortAscending1, LPCTSTR SortField2, BOOL SortAscending2, LPCTSTR SortField3, BOOL SortAscending3)
		{
			static BYTE parms[] = VTS_BSTR VTS_BOOL VTS_BSTR VTS_BOOL VTS_BSTR VTS_BOOL ;
			InvokeHelper(0x6002000b, DISPATCH_METHOD, VT_EMPTY, NULL, parms, SortField1, SortAscending1, SortField2, SortAscending2, SortField3, SortAscending3);
		}
		void ApplyFilter()
		{
			InvokeHelper(0x6002000c, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
	};
	
	// OfficeTheme ��װ��
	class OfficeTheme : public COleDispatchDriver
	{
	public:
		OfficeTheme(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		OfficeTheme(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		OfficeTheme(const OfficeTheme& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// OfficeTheme ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_ThemeColorScheme()
		{
			LPDISPATCH result;
			InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_ThemeFontScheme()
		{
			LPDISPATCH result;
			InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_ThemeEffectScheme()
		{
			LPDISPATCH result;
			InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
	};
	
	// ParagraphFormat2 ��װ��
	class ParagraphFormat2 : public COleDispatchDriver
	{
	public:
		ParagraphFormat2(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		ParagraphFormat2(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		ParagraphFormat2(const ParagraphFormat2& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// ParagraphFormat2 ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Alignment()
		{
			long result;
			InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_Alignment(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_BaselineAlignment()
		{
			long result;
			InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_BaselineAlignment(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		LPDISPATCH get_Bullet()
		{
			LPDISPATCH result;
			InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_FarEastLineBreakLevel()
		{
			long result;
			InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_FarEastLineBreakLevel(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		float get_FirstLineIndent()
		{
			float result;
			InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
			return result;
		}
		void put_FirstLineIndent(float newValue)
		{
			static BYTE parms[] = VTS_R4 ;
			InvokeHelper(0x6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_HangingPunctuation()
		{
			long result;
			InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_HangingPunctuation(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_IndentLevel()
		{
			long result;
			InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_IndentLevel(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		float get_LeftIndent()
		{
			float result;
			InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
			return result;
		}
		void put_LeftIndent(float newValue)
		{
			static BYTE parms[] = VTS_R4 ;
			InvokeHelper(0x9, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_LineRuleAfter()
		{
			long result;
			InvokeHelper(0xa, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_LineRuleAfter(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0xa, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_LineRuleBefore()
		{
			long result;
			InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_LineRuleBefore(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0xb, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_LineRuleWithin()
		{
			long result;
			InvokeHelper(0xc, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_LineRuleWithin(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0xc, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		float get_RightIndent()
		{
			float result;
			InvokeHelper(0xd, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
			return result;
		}
		void put_RightIndent(float newValue)
		{
			static BYTE parms[] = VTS_R4 ;
			InvokeHelper(0xd, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		float get_SpaceAfter()
		{
			float result;
			InvokeHelper(0xe, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
			return result;
		}
		void put_SpaceAfter(float newValue)
		{
			static BYTE parms[] = VTS_R4 ;
			InvokeHelper(0xe, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		float get_SpaceBefore()
		{
			float result;
			InvokeHelper(0xf, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
			return result;
		}
		void put_SpaceBefore(float newValue)
		{
			static BYTE parms[] = VTS_R4 ;
			InvokeHelper(0xf, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		float get_SpaceWithin()
		{
			float result;
			InvokeHelper(0x10, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
			return result;
		}
		void put_SpaceWithin(float newValue)
		{
			static BYTE parms[] = VTS_R4 ;
			InvokeHelper(0x10, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		LPDISPATCH get_TabStops()
		{
			LPDISPATCH result;
			InvokeHelper(0x11, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_TextDirection()
		{
			long result;
			InvokeHelper(0x12, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_TextDirection(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x12, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_WordWrap()
		{
			long result;
			InvokeHelper(0x13, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_WordWrap(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x13, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
	};
	
	// Permission ��װ��
	class Permission : public COleDispatchDriver
	{
	public:
		Permission(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		Permission(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		Permission(const Permission& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// Permission ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Item(VARIANT& Index)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, &Index);
			return result;
		}
		long get_Count()
		{
			long result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		BOOL get_EnableTrustedBrowser()
		{
			BOOL result;
			InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_EnableTrustedBrowser(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		LPDISPATCH Add(LPCTSTR UserId, VARIANT& Permission, VARIANT& ExpirationDate)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_BSTR VTS_VARIANT VTS_VARIANT ;
			InvokeHelper(0x3, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, UserId, &Permission, &ExpirationDate);
			return result;
		}
		void ApplyPolicy(LPCTSTR FileName)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x4, DISPATCH_METHOD, VT_EMPTY, NULL, parms, FileName);
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		void RemoveAll()
		{
			InvokeHelper(0x6, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		BOOL get_Enabled()
		{
			BOOL result;
			InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_Enabled(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_RequestPermissionURL()
		{
			CString result;
			InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_RequestPermissionURL(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_PolicyName()
		{
			CString result;
			InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		CString get_PolicyDescription()
		{
			CString result;
			InvokeHelper(0xa, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		BOOL get_StoreLicenses()
		{
			BOOL result;
			InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_StoreLicenses(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0xb, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_DocumentAuthor()
		{
			CString result;
			InvokeHelper(0xc, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_DocumentAuthor(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0xc, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_PermissionFromPolicy()
		{
			BOOL result;
			InvokeHelper(0xd, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		LPUNKNOWN get__NewEnum()
		{
			LPUNKNOWN result;
			InvokeHelper(0xfffffffc, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
			return result;
		}
	};
	
	// PickerDialog ��װ��
	class PickerDialog : public COleDispatchDriver
	{
	public:
		PickerDialog(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		PickerDialog(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		PickerDialog(const PickerDialog& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// PickerDialog ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		CString get_DataHandlerId()
		{
			CString result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_DataHandlerId(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_Title()
		{
			CString result;
			InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_Title(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		LPDISPATCH get_Properties()
		{
			LPDISPATCH result;
			InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH CreatePickerResults()
		{
			LPDISPATCH result;
			InvokeHelper(0x4, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH Show(BOOL IsMultiSelect, LPDISPATCH ExistingResults)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_BOOL VTS_DISPATCH ;
			InvokeHelper(0x5, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, IsMultiSelect, ExistingResults);
			return result;
		}
		LPDISPATCH Resolve(LPCTSTR TokenText, long duplicateDlgMode)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_BSTR VTS_I4 ;
			InvokeHelper(0x6, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, TokenText, duplicateDlgMode);
			return result;
		}
	};
	
	// PickerField ��װ��
	class PickerField : public COleDispatchDriver
	{
	public:
		PickerField(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		PickerField(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		PickerField(const PickerField& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// PickerField ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		CString get_Name()
		{
			CString result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		long get_Type()
		{
			long result;
			InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		BOOL get_IsHidden()
		{
			BOOL result;
			InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
	};
	
	// PickerFields ��װ��
	class PickerFields : public COleDispatchDriver
	{
	public:
		PickerFields(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		PickerFields(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		PickerFields(const PickerFields& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// PickerFields ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Item(long Index)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, Index);
			return result;
		}
		long get_Count()
		{
			long result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPUNKNOWN get__NewEnum()
		{
			LPUNKNOWN result;
			InvokeHelper(0xfffffffc, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
			return result;
		}
	};
	
	// PickerProperty ��װ��
	class PickerProperty : public COleDispatchDriver
	{
	public:
		PickerProperty(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		PickerProperty(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		PickerProperty(const PickerProperty& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// PickerProperty ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		CString get_Id()
		{
			CString result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		VARIANT get_Value()
		{
			VARIANT result;
			InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		long get_Type()
		{
			long result;
			InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
	};
	
	// PickerProperties ��װ��
	class PickerProperties : public COleDispatchDriver
	{
	public:
		PickerProperties(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		PickerProperties(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		PickerProperties(const PickerProperties& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// PickerProperties ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Item(long Index)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, Index);
			return result;
		}
		long get_Count()
		{
			long result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH Add(LPCTSTR Id, LPCTSTR Value, long Type)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_I4 ;
			InvokeHelper(0x2, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, Id, Value, Type);
			return result;
		}
		void Remove(LPCTSTR Id)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x3, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Id);
		}
		LPUNKNOWN get__NewEnum()
		{
			LPUNKNOWN result;
			InvokeHelper(0xfffffffc, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
			return result;
		}
	};
	
	// PickerResult ��װ��
	class PickerResult : public COleDispatchDriver
	{
	public:
		PickerResult(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		PickerResult(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		PickerResult(const PickerResult& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// PickerResult ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		CString get_Id()
		{
			CString result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		CString get_DisplayName()
		{
			CString result;
			InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_DisplayName(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_Type()
		{
			CString result;
			InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_Type(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_SIPId()
		{
			CString result;
			InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_SIPId(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		VARIANT get_ItemData()
		{
			VARIANT result;
			InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		void put_ItemData(VARIANT& newValue)
		{
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, &newValue);
		}
		VARIANT get_SubItems()
		{
			VARIANT result;
			InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		void put_SubItems(VARIANT& newValue)
		{
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, &newValue);
		}
		VARIANT get_DuplicateResults()
		{
			VARIANT result;
			InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Fields()
		{
			LPDISPATCH result;
			InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		void put_Fields(LPDISPATCH newValue)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
	};
	
	// PickerResults ��װ��
	class PickerResults : public COleDispatchDriver
	{
	public:
		PickerResults(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		PickerResults(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		PickerResults(const PickerResults& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// PickerResults ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Item(long Index)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, Index);
			return result;
		}
		long get_Count()
		{
			long result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH Add(LPCTSTR Id, LPCTSTR DisplayName, LPCTSTR Type, LPCTSTR SIPId, VARIANT& ItemData, VARIANT& SubItems)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_VARIANT VTS_VARIANT ;
			InvokeHelper(0x2, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, Id, DisplayName, Type, SIPId, &ItemData, &SubItems);
			return result;
		}
		LPUNKNOWN get__NewEnum()
		{
			LPUNKNOWN result;
			InvokeHelper(0xfffffffc, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
			return result;
		}
	};
	
	// PictureEffect ��װ��
	class PictureEffect : public COleDispatchDriver
	{
	public:
		PictureEffect(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		PictureEffect(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		PictureEffect(const PictureEffect& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// PictureEffect ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		long get_Type()
		{
			long result;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_Position(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_Position()
		{
			long result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void Delete()
		{
			InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		LPDISPATCH get_EffectParameters()
		{
			LPDISPATCH result;
			InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		void put_Visible(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_Visible()
		{
			long result;
			InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
	};
	
	// PictureEffects ��װ��
	class PictureEffects : public COleDispatchDriver
	{
	public:
		PictureEffects(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		PictureEffects(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		PictureEffects(const PictureEffects& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// PictureEffects ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Item(long Index)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, Index);
			return result;
		}
		long get_Count()
		{
			long result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPUNKNOWN get__NewEnum()
		{
			LPUNKNOWN result;
			InvokeHelper(0xfffffffc, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH Insert(long EffectType, long Position)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I4 VTS_I4 ;
			InvokeHelper(0x2, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, EffectType, Position);
			return result;
		}
		void Delete(long Index)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x3, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Index);
		}
	};
	
	// PictureFormat ��װ��
	class PictureFormat : public COleDispatchDriver
	{
	public:
		PictureFormat(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		PictureFormat(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		PictureFormat(const PictureFormat& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// PictureFormat ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		void IncrementBrightness(float Increment)
		{
			static BYTE parms[] = VTS_R4 ;
			InvokeHelper(0xa, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Increment);
		}
		void IncrementContrast(float Increment)
		{
			static BYTE parms[] = VTS_R4 ;
			InvokeHelper(0xb, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Increment);
		}
		float get_Brightness()
		{
			float result;
			InvokeHelper(0x64, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
			return result;
		}
		void put_Brightness(float newValue)
		{
			static BYTE parms[] = VTS_R4 ;
			InvokeHelper(0x64, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_ColorType()
		{
			long result;
			InvokeHelper(0x65, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_ColorType(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x65, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		float get_Contrast()
		{
			float result;
			InvokeHelper(0x66, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
			return result;
		}
		void put_Contrast(float newValue)
		{
			static BYTE parms[] = VTS_R4 ;
			InvokeHelper(0x66, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		float get_CropBottom()
		{
			float result;
			InvokeHelper(0x67, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
			return result;
		}
		void put_CropBottom(float newValue)
		{
			static BYTE parms[] = VTS_R4 ;
			InvokeHelper(0x67, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		float get_CropLeft()
		{
			float result;
			InvokeHelper(0x68, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
			return result;
		}
		void put_CropLeft(float newValue)
		{
			static BYTE parms[] = VTS_R4 ;
			InvokeHelper(0x68, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		float get_CropRight()
		{
			float result;
			InvokeHelper(0x69, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
			return result;
		}
		void put_CropRight(float newValue)
		{
			static BYTE parms[] = VTS_R4 ;
			InvokeHelper(0x69, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		float get_CropTop()
		{
			float result;
			InvokeHelper(0x6a, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
			return result;
		}
		void put_CropTop(float newValue)
		{
			static BYTE parms[] = VTS_R4 ;
			InvokeHelper(0x6a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_TransparencyColor()
		{
			long result;
			InvokeHelper(0x6b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_TransparencyColor(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x6b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_TransparentBackground()
		{
			long result;
			InvokeHelper(0x6c, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_TransparentBackground(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x6c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		LPDISPATCH get_Crop()
		{
			LPDISPATCH result;
			InvokeHelper(0x6d, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
	};
	
	// PolicyItem ��װ��
	class PolicyItem : public COleDispatchDriver
	{
	public:
		PolicyItem(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		PolicyItem(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		PolicyItem(const PolicyItem& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// PolicyItem ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		CString get_Id()
		{
			CString result;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		CString get_Name()
		{
			CString result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		CString get_Description()
		{
			CString result;
			InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		CString get_Data()
		{
			CString result;
			InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
	};
	
	// PropertyTest ��װ��
	class PropertyTest : public COleDispatchDriver
	{
	public:
		PropertyTest(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		PropertyTest(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		PropertyTest(const PropertyTest& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// PropertyTest ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		CString get_Name()
		{
			CString result;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		long get_Condition()
		{
			long result;
			InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		VARIANT get_Value()
		{
			VARIANT result;
			InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		VARIANT get_SecondValue()
		{
			VARIANT result;
			InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		long get_Connector()
		{
			long result;
			InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
	};
	
	// PropertyTests ��װ��
	class PropertyTests : public COleDispatchDriver
	{
	public:
		PropertyTests(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		PropertyTests(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		PropertyTests(const PropertyTests& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// PropertyTests ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Item(long Index)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, Index);
			return result;
		}
		long get_Count()
		{
			long result;
			InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void Add(LPCTSTR Name, long Condition, VARIANT& Value, VARIANT& SecondValue, long Connector)
		{
			static BYTE parms[] = VTS_BSTR VTS_I4 VTS_VARIANT VTS_VARIANT VTS_I4 ;
			InvokeHelper(0x5, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Name, Condition, &Value, &SecondValue, Connector);
		}
		void Remove(long Index)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x6, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Index);
		}
		LPUNKNOWN get__NewEnum()
		{
			LPUNKNOWN result;
			InvokeHelper(0xfffffffc, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
			return result;
		}
	};
	
	// ReflectionFormat ��װ��
	class ReflectionFormat : public COleDispatchDriver
	{
	public:
		ReflectionFormat(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		ReflectionFormat(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		ReflectionFormat(const ReflectionFormat& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// ReflectionFormat ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		long get_Type()
		{
			long result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_Type(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		float get_Transparency()
		{
			float result;
			InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
			return result;
		}
		void put_Transparency(float newValue)
		{
			static BYTE parms[] = VTS_R4 ;
			InvokeHelper(0x2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		float get_Size()
		{
			float result;
			InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
			return result;
		}
		void put_Size(float newValue)
		{
			static BYTE parms[] = VTS_R4 ;
			InvokeHelper(0x3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		float get_Offset()
		{
			float result;
			InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
			return result;
		}
		void put_Offset(float newValue)
		{
			static BYTE parms[] = VTS_R4 ;
			InvokeHelper(0x4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		float get_Blur()
		{
			float result;
			InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
			return result;
		}
		void put_Blur(float newValue)
		{
			static BYTE parms[] = VTS_R4 ;
			InvokeHelper(0x5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
	};
	
	// IRibbonControl ��װ��
	class IRibbonControl : public COleDispatchDriver
	{
	public:
		IRibbonControl(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		IRibbonControl(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		IRibbonControl(const IRibbonControl& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// IRibbonControl ����
	public:
		CString get_Id()
		{
			CString result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Context()
		{
			LPDISPATCH result;
			InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		CString get_Tag()
		{
			CString result;
			InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
	};
	
	// IRibbonExtensibility ��װ��
	class IRibbonExtensibility : public COleDispatchDriver
	{
	public:
		IRibbonExtensibility(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		IRibbonExtensibility(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		IRibbonExtensibility(const IRibbonExtensibility& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// IRibbonExtensibility ����
	public:
		CString GetCustomUI(LPCTSTR RibbonID)
		{
			CString result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x1, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, RibbonID);
			return result;
		}
	};
	
	// IRibbonUI ��װ��
	class IRibbonUI : public COleDispatchDriver
	{
	public:
		IRibbonUI(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		IRibbonUI(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		IRibbonUI(const IRibbonUI& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// IRibbonUI ����
	public:
		void Invalidate()
		{
			InvokeHelper(0x1, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void InvalidateControl(LPCTSTR ControlID)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, parms, ControlID);
		}
		void InvalidateControlMso(LPCTSTR ControlID)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x3, DISPATCH_METHOD, VT_EMPTY, NULL, parms, ControlID);
		}
		void ActivateTab(LPCTSTR ControlID)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x4, DISPATCH_METHOD, VT_EMPTY, NULL, parms, ControlID);
		}
		void ActivateTabMso(LPCTSTR ControlID)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x5, DISPATCH_METHOD, VT_EMPTY, NULL, parms, ControlID);
		}
		void ActivateTabQ(LPCTSTR ControlID, LPCTSTR Namespace)
		{
			static BYTE parms[] = VTS_BSTR VTS_BSTR ;
			InvokeHelper(0x6, DISPATCH_METHOD, VT_EMPTY, NULL, parms, ControlID, Namespace);
		}
	};

	// Ruler2 ��װ��
	class Ruler2 : public COleDispatchDriver
	{
	public:
		Ruler2(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		Ruler2(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		Ruler2(const Ruler2& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// Ruler2 ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Levels()
		{
			LPDISPATCH result;
			InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_TabStops()
		{
			LPDISPATCH result;
			InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
	};
	
	// RulerLevel2 ��װ��
	class RulerLevel2 : public COleDispatchDriver
	{
	public:
		RulerLevel2(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		RulerLevel2(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		RulerLevel2(const RulerLevel2& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// RulerLevel2 ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		float get_FirstMargin()
		{
			float result;
			InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
			return result;
		}
		void put_FirstMargin(float newValue)
		{
			static BYTE parms[] = VTS_R4 ;
			InvokeHelper(0x2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		float get_LeftMargin()
		{
			float result;
			InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
			return result;
		}
		void put_LeftMargin(float newValue)
		{
			static BYTE parms[] = VTS_R4 ;
			InvokeHelper(0x3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
	};
	
	// RulerLevels2 ��װ��
	class RulerLevels2 : public COleDispatchDriver
	{
	public:
		RulerLevels2(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		RulerLevels2(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		RulerLevels2(const RulerLevels2& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// RulerLevels2 ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Count()
		{
			long result;
			InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH Item(VARIANT& Index)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x0, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, &Index);
			return result;
		}
		LPUNKNOWN get__NewEnum()
		{
			LPUNKNOWN result;
			InvokeHelper(0xfffffffc, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
			return result;
		}
	};
	
	// ScopeFolder ��װ��

	class ScopeFolder : public COleDispatchDriver
	{
	public:
		ScopeFolder(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		ScopeFolder(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		ScopeFolder(const ScopeFolder& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// ScopeFolder ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		CString get_Name()
		{
			CString result;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		CString get_Path()
		{
			CString result;
			InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_ScopeFolders()
		{
			LPDISPATCH result;
			InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		void AddToSearchFolders()
		{
			InvokeHelper(0x4, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
	};
	
	// ScopeFolders ��װ��

	class ScopeFolders : public COleDispatchDriver
	{
	public:
		ScopeFolders(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		ScopeFolders(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		ScopeFolders(const ScopeFolders& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// ScopeFolders ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Item(long Index)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, Index);
			return result;
		}
		long get_Count()
		{
			long result;
			InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPUNKNOWN get__NewEnum()
		{
			LPUNKNOWN result;
			InvokeHelper(0xfffffffc, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
			return result;
		}
	};
	
	// Script ��װ��

	class Script : public COleDispatchDriver
	{
	public:
		Script(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		Script(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		Script(const Script& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// Script ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x60030000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		CString get_Extended()
		{
			CString result;
			InvokeHelper(0x60030001, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_Extended(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x60030001, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_Id()
		{
			CString result;
			InvokeHelper(0x60030003, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_Id(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x60030003, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_Language()
		{
			long result;
			InvokeHelper(0x60030005, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_Language(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60030005, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_Location()
		{
			long result;
			InvokeHelper(0x60030007, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void Delete()
		{
			InvokeHelper(0x60030008, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		LPDISPATCH get_Shape()
		{
			LPDISPATCH result;
			InvokeHelper(0x60030009, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		CString get_ScriptText()
		{
			CString result;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_ScriptText(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
	};
	
	// Scripts ��װ��
	class Scripts : public COleDispatchDriver
	{
	public:
		Scripts(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		Scripts(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		Scripts(const Scripts& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// Scripts ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x60030000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Count()
		{
			long result;
			InvokeHelper(0x60030001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPUNKNOWN get__NewEnum()
		{
			LPUNKNOWN result;
			InvokeHelper(0xfffffffc, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH Item(VARIANT& Index)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x0, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, &Index);
			return result;
		}
		LPDISPATCH Add(LPDISPATCH Anchor, long Location, long Language, LPCTSTR Id, LPCTSTR Extended, LPCTSTR ScriptText)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_DISPATCH VTS_I4 VTS_I4 VTS_BSTR VTS_BSTR VTS_BSTR ;
			InvokeHelper(0x60030004, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, Anchor, Location, Language, Id, Extended, ScriptText);
			return result;
		}
		void Delete()
		{
			InvokeHelper(0x60030005, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
	};
	
	// SearchFolders ��װ��
	class SearchFolders : public COleDispatchDriver
	{
	public:
		SearchFolders(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		SearchFolders(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		SearchFolders(const SearchFolders& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// SearchFolders ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Item(long Index)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, Index);
			return result;
		}
		long get_Count()
		{
			long result;
			InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void Add(LPDISPATCH ScopeFolder)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x3, DISPATCH_METHOD, VT_EMPTY, NULL, parms, ScopeFolder);
		}
		void Remove(long Index)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x4, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Index);
		}
		LPUNKNOWN get__NewEnum()
		{
			LPUNKNOWN result;
			InvokeHelper(0xfffffffc, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
			return result;
		}
	};
	
	// SearchScope ��װ��
	class SearchScope : public COleDispatchDriver
	{
	public:
		SearchScope(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		SearchScope(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		SearchScope(const SearchScope& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// SearchScope ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		long get_Type()
		{
			long result;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_ScopeFolder()
		{
			LPDISPATCH result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
	};
	
	// SearchScopes ��װ��
	class SearchScopes : public COleDispatchDriver
	{
	public:
		SearchScopes(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		SearchScopes(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		SearchScopes(const SearchScopes& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// SearchScopes ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Item(long Index)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, Index);
			return result;
		}
		long get_Count()
		{
			long result;
			InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPUNKNOWN get__NewEnum()
		{
			LPUNKNOWN result;
			InvokeHelper(0xfffffffc, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
			return result;
		}
	};
	
	// ServerPolicy ��װ��
	class ServerPolicy : public COleDispatchDriver
	{
	public:
		ServerPolicy(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		ServerPolicy(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		ServerPolicy(const ServerPolicy& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// ServerPolicy ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Item(VARIANT& Index)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, &Index);
			return result;
		}
		CString get_Id()
		{
			CString result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		CString get_Name()
		{
			CString result;
			InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		CString get_Description()
		{
			CString result;
			InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		CString get_Statement()
		{
			CString result;
			InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		long get_Count()
		{
			long result;
			InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		BOOL get_BlockPreview()
		{
			BOOL result;
			InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
	};
	
	// ShadowFormat ��װ��
	class ShadowFormat : public COleDispatchDriver
	{
	public:
		ShadowFormat(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		ShadowFormat(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		ShadowFormat(const ShadowFormat& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// ShadowFormat ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		void IncrementOffsetX(float Increment)
		{
			static BYTE parms[] = VTS_R4 ;
			InvokeHelper(0xa, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Increment);
		}
		void IncrementOffsetY(float Increment)
		{
			static BYTE parms[] = VTS_R4 ;
			InvokeHelper(0xb, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Increment);
		}
		LPDISPATCH get_ForeColor()
		{
			LPDISPATCH result;
			InvokeHelper(0x64, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		void put_ForeColor(LPDISPATCH newValue)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x64, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_Obscured()
		{
			long result;
			InvokeHelper(0x65, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_Obscured(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x65, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		float get_OffsetX()
		{
			float result;
			InvokeHelper(0x66, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
			return result;
		}
		void put_OffsetX(float newValue)
		{
			static BYTE parms[] = VTS_R4 ;
			InvokeHelper(0x66, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		float get_OffsetY()
		{
			float result;
			InvokeHelper(0x67, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
			return result;
		}
		void put_OffsetY(float newValue)
		{
			static BYTE parms[] = VTS_R4 ;
			InvokeHelper(0x67, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		float get_Transparency()
		{
			float result;
			InvokeHelper(0x68, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
			return result;
		}
		void put_Transparency(float newValue)
		{
			static BYTE parms[] = VTS_R4 ;
			InvokeHelper(0x68, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_Type()
		{
			long result;
			InvokeHelper(0x69, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_Type(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x69, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_Visible()
		{
			long result;
			InvokeHelper(0x6a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_Visible(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x6a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_Style()
		{
			long result;
			InvokeHelper(0x6b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_Style(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x6b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		float get_Blur()
		{
			float result;
			InvokeHelper(0x6c, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
			return result;
		}
		void put_Blur(float newValue)
		{
			static BYTE parms[] = VTS_R4 ;
			InvokeHelper(0x6c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		float get_Size()
		{
			float result;
			InvokeHelper(0x6d, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
			return result;
		}
		void put_Size(float newValue)
		{
			static BYTE parms[] = VTS_R4 ;
			InvokeHelper(0x6d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_RotateWithShape()
		{
			long result;
			InvokeHelper(0x6e, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_RotateWithShape(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x6e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
	};
	
	// Shape ��װ��
	class Shape : public COleDispatchDriver
	{
	public:
		Shape(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		Shape(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		Shape(const Shape& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// Shape ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		void Apply()
		{
			InvokeHelper(0xa, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void Delete()
		{
			InvokeHelper(0xb, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		LPDISPATCH Duplicate()
		{
			LPDISPATCH result;
			InvokeHelper(0xc, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		void Flip(long FlipCmd)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0xd, DISPATCH_METHOD, VT_EMPTY, NULL, parms, FlipCmd);
		}
		void IncrementLeft(float Increment)
		{
			static BYTE parms[] = VTS_R4 ;
			InvokeHelper(0xe, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Increment);
		}
		void IncrementRotation(float Increment)
		{
			static BYTE parms[] = VTS_R4 ;
			InvokeHelper(0xf, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Increment);
		}
		void IncrementTop(float Increment)
		{
			static BYTE parms[] = VTS_R4 ;
			InvokeHelper(0x10, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Increment);
		}
		void PickUp()
		{
			InvokeHelper(0x11, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void RerouteConnections()
		{
			InvokeHelper(0x12, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void ScaleHeight(float Factor, long RelativeToOriginalSize, long fScale)
		{
			static BYTE parms[] = VTS_R4 VTS_I4 VTS_I4 ;
			InvokeHelper(0x13, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Factor, RelativeToOriginalSize, fScale);
		}
		void ScaleWidth(float Factor, long RelativeToOriginalSize, long fScale)
		{
			static BYTE parms[] = VTS_R4 VTS_I4 VTS_I4 ;
			InvokeHelper(0x14, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Factor, RelativeToOriginalSize, fScale);
		}
		void Select(VARIANT& Replace)
		{
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x15, DISPATCH_METHOD, VT_EMPTY, NULL, parms, &Replace);
		}
		void SetShapesDefaultProperties()
		{
			InvokeHelper(0x16, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		LPDISPATCH Ungroup()
		{
			LPDISPATCH result;
			InvokeHelper(0x17, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		void ZOrder(long ZOrderCmd)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x18, DISPATCH_METHOD, VT_EMPTY, NULL, parms, ZOrderCmd);
		}
		LPDISPATCH get_Adjustments()
		{
			LPDISPATCH result;
			InvokeHelper(0x64, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_AutoShapeType()
		{
			long result;
			InvokeHelper(0x65, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_AutoShapeType(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x65, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_BlackWhiteMode()
		{
			long result;
			InvokeHelper(0x66, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_BlackWhiteMode(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x66, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		LPDISPATCH get_Callout()
		{
			LPDISPATCH result;
			InvokeHelper(0x67, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_ConnectionSiteCount()
		{
			long result;
			InvokeHelper(0x68, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		long get_Connector()
		{
			long result;
			InvokeHelper(0x69, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_ConnectorFormat()
		{
			LPDISPATCH result;
			InvokeHelper(0x6a, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Fill()
		{
			LPDISPATCH result;
			InvokeHelper(0x6b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_GroupItems()
		{
			LPDISPATCH result;
			InvokeHelper(0x6c, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		float get_Height()
		{
			float result;
			InvokeHelper(0x6d, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
			return result;
		}
		void put_Height(float newValue)
		{
			static BYTE parms[] = VTS_R4 ;
			InvokeHelper(0x6d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_HorizontalFlip()
		{
			long result;
			InvokeHelper(0x6e, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		float get_Left()
		{
			float result;
			InvokeHelper(0x6f, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
			return result;
		}
		void put_Left(float newValue)
		{
			static BYTE parms[] = VTS_R4 ;
			InvokeHelper(0x6f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		LPDISPATCH get_Line()
		{
			LPDISPATCH result;
			InvokeHelper(0x70, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_LockAspectRatio()
		{
			long result;
			InvokeHelper(0x71, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_LockAspectRatio(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x71, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_Name()
		{
			CString result;
			InvokeHelper(0x73, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_Name(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x73, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		LPDISPATCH get_Nodes()
		{
			LPDISPATCH result;
			InvokeHelper(0x74, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		float get_Rotation()
		{
			float result;
			InvokeHelper(0x75, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
			return result;
		}
		void put_Rotation(float newValue)
		{
			static BYTE parms[] = VTS_R4 ;
			InvokeHelper(0x75, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		LPDISPATCH get_PictureFormat()
		{
			LPDISPATCH result;
			InvokeHelper(0x76, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Shadow()
		{
			LPDISPATCH result;
			InvokeHelper(0x77, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_TextEffect()
		{
			LPDISPATCH result;
			InvokeHelper(0x78, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_TextFrame()
		{
			LPDISPATCH result;
			InvokeHelper(0x79, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_ThreeD()
		{
			LPDISPATCH result;
			InvokeHelper(0x7a, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		float get_Top()
		{
			float result;
			InvokeHelper(0x7b, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
			return result;
		}
		void put_Top(float newValue)
		{
			static BYTE parms[] = VTS_R4 ;
			InvokeHelper(0x7b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_Type()
		{
			long result;
			InvokeHelper(0x7c, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		long get_VerticalFlip()
		{
			long result;
			InvokeHelper(0x7d, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		VARIANT get_Vertices()
		{
			VARIANT result;
			InvokeHelper(0x7e, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		long get_Visible()
		{
			long result;
			InvokeHelper(0x7f, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_Visible(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x7f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		float get_Width()
		{
			float result;
			InvokeHelper(0x80, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
			return result;
		}
		void put_Width(float newValue)
		{
			static BYTE parms[] = VTS_R4 ;
			InvokeHelper(0x80, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_ZOrderPosition()
		{
			long result;
			InvokeHelper(0x81, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Script()
		{
			LPDISPATCH result;
			InvokeHelper(0x82, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		CString get_AlternativeText()
		{
			CString result;
			InvokeHelper(0x83, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_AlternativeText(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x83, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_HasDiagram()
		{
			long result;
			InvokeHelper(0x84, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Diagram()
		{
			LPDISPATCH result;
			InvokeHelper(0x85, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_HasDiagramNode()
		{
			long result;
			InvokeHelper(0x86, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_DiagramNode()
		{
			LPDISPATCH result;
			InvokeHelper(0x87, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Child()
		{
			long result;
			InvokeHelper(0x88, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_ParentGroup()
		{
			LPDISPATCH result;
			InvokeHelper(0x89, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_CanvasItems()
		{
			LPDISPATCH result;
			InvokeHelper(0x8a, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Id()
		{
			long result;
			InvokeHelper(0x8b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void CanvasCropLeft(float Increment)
		{
			static BYTE parms[] = VTS_R4 ;
			InvokeHelper(0x8c, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Increment);
		}
		void CanvasCropTop(float Increment)
		{
			static BYTE parms[] = VTS_R4 ;
			InvokeHelper(0x8d, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Increment);
		}
		void CanvasCropRight(float Increment)
		{
			static BYTE parms[] = VTS_R4 ;
			InvokeHelper(0x8e, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Increment);
		}
		void CanvasCropBottom(float Increment)
		{
			static BYTE parms[] = VTS_R4 ;
			InvokeHelper(0x8f, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Increment);
		}
		void put_RTF(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x90, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		LPDISPATCH get_TextFrame2()
		{
			LPDISPATCH result;
			InvokeHelper(0x91, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		void Cut()
		{
			InvokeHelper(0x92, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void Copy()
		{
			InvokeHelper(0x93, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		long get_HasChart()
		{
			long result;
			InvokeHelper(0x94, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Chart()
		{
			LPDISPATCH result;
			InvokeHelper(0x95, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_ShapeStyle()
		{
			long result;
			InvokeHelper(0x96, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_ShapeStyle(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x96, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_BackgroundStyle()
		{
			long result;
			InvokeHelper(0x97, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_BackgroundStyle(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x97, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		LPDISPATCH get_SoftEdge()
		{
			LPDISPATCH result;
			InvokeHelper(0x98, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Glow()
		{
			LPDISPATCH result;
			InvokeHelper(0x99, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Reflection()
		{
			LPDISPATCH result;
			InvokeHelper(0x9a, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_HasSmartArt()
		{
			long result;
			InvokeHelper(0x9b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_SmartArt()
		{
			LPDISPATCH result;
			InvokeHelper(0x9c, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		void ConvertTextToSmartArt(LPDISPATCH Layout)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x9d, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Layout);
		}
		CString get_Title()
		{
			CString result;
			InvokeHelper(0x9e, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_Title(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x9e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
	};
	
	// Shapes ��װ��
	class Shapes : public COleDispatchDriver
	{
	public:
		Shapes(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		Shapes(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		Shapes(const Shapes& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// Shapes ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Count()
		{
			long result;
			InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH Item(VARIANT& Index)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x0, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, &Index);
			return result;
		}
		LPUNKNOWN get__NewEnum()
		{
			LPUNKNOWN result;
			InvokeHelper(0xfffffffc, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH AddCallout(long Type, float Left, float Top, float Width, float Height)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I4 VTS_R4 VTS_R4 VTS_R4 VTS_R4 ;
			InvokeHelper(0xa, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, Type, Left, Top, Width, Height);
			return result;
		}
		LPDISPATCH AddConnector(long Type, float BeginX, float BeginY, float EndX, float EndY)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I4 VTS_R4 VTS_R4 VTS_R4 VTS_R4 ;
			InvokeHelper(0xb, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, Type, BeginX, BeginY, EndX, EndY);
			return result;
		}
		LPDISPATCH AddCurve(VARIANT& SafeArrayOfPoints)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0xc, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, &SafeArrayOfPoints);
			return result;
		}
		LPDISPATCH AddLabel(long Orientation, float Left, float Top, float Width, float Height)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I4 VTS_R4 VTS_R4 VTS_R4 VTS_R4 ;
			InvokeHelper(0xd, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, Orientation, Left, Top, Width, Height);
			return result;
		}
		LPDISPATCH AddLine(float BeginX, float BeginY, float EndX, float EndY)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_R4 VTS_R4 VTS_R4 VTS_R4 ;
			InvokeHelper(0xe, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, BeginX, BeginY, EndX, EndY);
			return result;
		}
		LPDISPATCH AddPicture(LPCTSTR FileName, long LinkToFile, long SaveWithDocument, float Left, float Top, float Width, float Height)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_BSTR VTS_I4 VTS_I4 VTS_R4 VTS_R4 VTS_R4 VTS_R4 ;
			InvokeHelper(0xf, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, FileName, LinkToFile, SaveWithDocument, Left, Top, Width, Height);
			return result;
		}
		LPDISPATCH AddPolyline(VARIANT& SafeArrayOfPoints)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x10, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, &SafeArrayOfPoints);
			return result;
		}
		LPDISPATCH AddShape(long Type, float Left, float Top, float Width, float Height)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I4 VTS_R4 VTS_R4 VTS_R4 VTS_R4 ;
			InvokeHelper(0x11, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, Type, Left, Top, Width, Height);
			return result;
		}
		LPDISPATCH AddTextEffect(long PresetTextEffect, LPCTSTR Text, LPCTSTR FontName, float FontSize, long FontBold, long FontItalic, float Left, float Top)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I4 VTS_BSTR VTS_BSTR VTS_R4 VTS_I4 VTS_I4 VTS_R4 VTS_R4 ;
			InvokeHelper(0x12, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, PresetTextEffect, Text, FontName, FontSize, FontBold, FontItalic, Left, Top);
			return result;
		}
		LPDISPATCH AddTextbox(long Orientation, float Left, float Top, float Width, float Height)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I4 VTS_R4 VTS_R4 VTS_R4 VTS_R4 ;
			InvokeHelper(0x13, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, Orientation, Left, Top, Width, Height);
			return result;
		}
		LPDISPATCH BuildFreeform(long EditingType, float X1, float Y1)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I4 VTS_R4 VTS_R4 ;
			InvokeHelper(0x14, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, EditingType, X1, Y1);
			return result;
		}
		LPDISPATCH Range(VARIANT& Index)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x15, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, &Index);
			return result;
		}
		void SelectAll()
		{
			InvokeHelper(0x16, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		LPDISPATCH get_Background()
		{
			LPDISPATCH result;
			InvokeHelper(0x64, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Default()
		{
			LPDISPATCH result;
			InvokeHelper(0x65, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH AddDiagram(long Type, float Left, float Top, float Width, float Height)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I4 VTS_R4 VTS_R4 VTS_R4 VTS_R4 ;
			InvokeHelper(0x17, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, Type, Left, Top, Width, Height);
			return result;
		}
		LPDISPATCH AddCanvas(float Left, float Top, float Width, float Height)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_R4 VTS_R4 VTS_R4 VTS_R4 ;
			InvokeHelper(0x19, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, Left, Top, Width, Height);
			return result;
		}
		LPDISPATCH AddChart(long Type, float Left, float Top, float Width, float Height)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I4 VTS_R4 VTS_R4 VTS_R4 VTS_R4 ;
			InvokeHelper(0x1a, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, Type, Left, Top, Width, Height);
			return result;
		}
		LPDISPATCH AddTable(long NumRows, long NumColumns, float Left, float Top, float Width, float Height)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I4 VTS_I4 VTS_R4 VTS_R4 VTS_R4 VTS_R4 ;
			InvokeHelper(0x1b, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, NumRows, NumColumns, Left, Top, Width, Height);
			return result;
		}
		LPDISPATCH AddSmartArt(LPDISPATCH Layout, float Left, float Top, float Width, float Height)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_DISPATCH VTS_R4 VTS_R4 VTS_R4 VTS_R4 ;
			InvokeHelper(0x1c, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, Layout, Left, Top, Width, Height);
			return result;
		}
		LPDISPATCH AddChart2(long Style, long Type, float Left, float Top, float Width, float Height, BOOL NewLayout)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I4 VTS_I4 VTS_R4 VTS_R4 VTS_R4 VTS_R4 VTS_BOOL ;
			InvokeHelper(0x1d, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, Style, Type, Left, Top, Width, Height, NewLayout);
			return result;
		}
		LPDISPATCH AddPicture2(LPCTSTR FileName, long LinkToFile, long SaveWithDocument, float Left, float Top, float Width, float Height, long Compress)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_BSTR VTS_I4 VTS_I4 VTS_R4 VTS_R4 VTS_R4 VTS_R4 VTS_I4 ;
			InvokeHelper(0x1e, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, FileName, LinkToFile, SaveWithDocument, Left, Top, Width, Height, Compress);
			return result;
		}
	};
	
	// ShapeNode ��װ��
	class ShapeNode : public COleDispatchDriver
	{
	public:
		ShapeNode(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		ShapeNode(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		ShapeNode(const ShapeNode& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// ShapeNode ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_EditingType()
		{
			long result;
			InvokeHelper(0x64, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		VARIANT get_Points()
		{
			VARIANT result;
			InvokeHelper(0x65, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		long get_SegmentType()
		{
			long result;
			InvokeHelper(0x66, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
	};
	
	// ShapeNodes ��װ��
	class ShapeNodes : public COleDispatchDriver
	{
	public:
		ShapeNodes(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		ShapeNodes(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		ShapeNodes(const ShapeNodes& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// ShapeNodes ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Count()
		{
			long result;
			InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH Item(VARIANT& Index)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x0, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, &Index);
			return result;
		}
		LPUNKNOWN get__NewEnum()
		{
			LPUNKNOWN result;
			InvokeHelper(0xfffffffc, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
			return result;
		}
		void Delete(long Index)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0xb, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Index);
		}
		void Insert(long Index, long SegmentType, long EditingType, float X1, float Y1, float X2, float Y2, float X3, float Y3)
		{
			static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_R4 VTS_R4 VTS_R4 VTS_R4 VTS_R4 VTS_R4 ;
			InvokeHelper(0xc, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Index, SegmentType, EditingType, X1, Y1, X2, Y2, X3, Y3);
		}
		void SetEditingType(long Index, long EditingType)
		{
			static BYTE parms[] = VTS_I4 VTS_I4 ;
			InvokeHelper(0xd, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Index, EditingType);
		}
		void SetPosition(long Index, float X1, float Y1)
		{
			static BYTE parms[] = VTS_I4 VTS_R4 VTS_R4 ;
			InvokeHelper(0xe, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Index, X1, Y1);
		}
		void SetSegmentType(long Index, long SegmentType)
		{
			static BYTE parms[] = VTS_I4 VTS_I4 ;
			InvokeHelper(0xf, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Index, SegmentType);
		}
	};
	
	// ShapeRange ��װ��
	class ShapeRange : public COleDispatchDriver
	{
	public:
		ShapeRange(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		ShapeRange(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		ShapeRange(const ShapeRange& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// ShapeRange ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Count()
		{
			long result;
			InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH Item(VARIANT& Index)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x0, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, &Index);
			return result;
		}
		LPUNKNOWN get__NewEnum()
		{
			LPUNKNOWN result;
			InvokeHelper(0xfffffffc, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
			return result;
		}
		void Align(long AlignCmd, long RelativeTo)
		{
			static BYTE parms[] = VTS_I4 VTS_I4 ;
			InvokeHelper(0xa, DISPATCH_METHOD, VT_EMPTY, NULL, parms, AlignCmd, RelativeTo);
		}
		void Apply()
		{
			InvokeHelper(0xb, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void Delete()
		{
			InvokeHelper(0xc, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void Distribute(long DistributeCmd, long RelativeTo)
		{
			static BYTE parms[] = VTS_I4 VTS_I4 ;
			InvokeHelper(0xd, DISPATCH_METHOD, VT_EMPTY, NULL, parms, DistributeCmd, RelativeTo);
		}
		LPDISPATCH Duplicate()
		{
			LPDISPATCH result;
			InvokeHelper(0xe, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		void Flip(long FlipCmd)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0xf, DISPATCH_METHOD, VT_EMPTY, NULL, parms, FlipCmd);
		}
		void IncrementLeft(float Increment)
		{
			static BYTE parms[] = VTS_R4 ;
			InvokeHelper(0x10, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Increment);
		}
		void IncrementRotation(float Increment)
		{
			static BYTE parms[] = VTS_R4 ;
			InvokeHelper(0x11, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Increment);
		}
		void IncrementTop(float Increment)
		{
			static BYTE parms[] = VTS_R4 ;
			InvokeHelper(0x12, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Increment);
		}
		LPDISPATCH Group()
		{
			LPDISPATCH result;
			InvokeHelper(0x13, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		void PickUp()
		{
			InvokeHelper(0x14, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		LPDISPATCH Regroup()
		{
			LPDISPATCH result;
			InvokeHelper(0x15, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		void RerouteConnections()
		{
			InvokeHelper(0x16, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void ScaleHeight(float Factor, long RelativeToOriginalSize, long fScale)
		{
			static BYTE parms[] = VTS_R4 VTS_I4 VTS_I4 ;
			InvokeHelper(0x17, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Factor, RelativeToOriginalSize, fScale);
		}
		void ScaleWidth(float Factor, long RelativeToOriginalSize, long fScale)
		{
			static BYTE parms[] = VTS_R4 VTS_I4 VTS_I4 ;
			InvokeHelper(0x18, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Factor, RelativeToOriginalSize, fScale);
		}
		void Select(VARIANT& Replace)
		{
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x19, DISPATCH_METHOD, VT_EMPTY, NULL, parms, &Replace);
		}
		void SetShapesDefaultProperties()
		{
			InvokeHelper(0x1a, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		LPDISPATCH Ungroup()
		{
			LPDISPATCH result;
			InvokeHelper(0x1b, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		void ZOrder(long ZOrderCmd)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x1c, DISPATCH_METHOD, VT_EMPTY, NULL, parms, ZOrderCmd);
		}
		LPDISPATCH get_Adjustments()
		{
			LPDISPATCH result;
			InvokeHelper(0x64, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_AutoShapeType()
		{
			long result;
			InvokeHelper(0x65, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_AutoShapeType(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x65, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_BlackWhiteMode()
		{
			long result;
			InvokeHelper(0x66, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_BlackWhiteMode(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x66, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		LPDISPATCH get_Callout()
		{
			LPDISPATCH result;
			InvokeHelper(0x67, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_ConnectionSiteCount()
		{
			long result;
			InvokeHelper(0x68, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		long get_Connector()
		{
			long result;
			InvokeHelper(0x69, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_ConnectorFormat()
		{
			LPDISPATCH result;
			InvokeHelper(0x6a, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Fill()
		{
			LPDISPATCH result;
			InvokeHelper(0x6b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_GroupItems()
		{
			LPDISPATCH result;
			InvokeHelper(0x6c, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		float get_Height()
		{
			float result;
			InvokeHelper(0x6d, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
			return result;
		}
		void put_Height(float newValue)
		{
			static BYTE parms[] = VTS_R4 ;
			InvokeHelper(0x6d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_HorizontalFlip()
		{
			long result;
			InvokeHelper(0x6e, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		float get_Left()
		{
			float result;
			InvokeHelper(0x6f, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
			return result;
		}
		void put_Left(float newValue)
		{
			static BYTE parms[] = VTS_R4 ;
			InvokeHelper(0x6f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		LPDISPATCH get_Line()
		{
			LPDISPATCH result;
			InvokeHelper(0x70, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_LockAspectRatio()
		{
			long result;
			InvokeHelper(0x71, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_LockAspectRatio(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x71, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_Name()
		{
			CString result;
			InvokeHelper(0x73, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_Name(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x73, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		LPDISPATCH get_Nodes()
		{
			LPDISPATCH result;
			InvokeHelper(0x74, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		float get_Rotation()
		{
			float result;
			InvokeHelper(0x75, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
			return result;
		}
		void put_Rotation(float newValue)
		{
			static BYTE parms[] = VTS_R4 ;
			InvokeHelper(0x75, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		LPDISPATCH get_PictureFormat()
		{
			LPDISPATCH result;
			InvokeHelper(0x76, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Shadow()
		{
			LPDISPATCH result;
			InvokeHelper(0x77, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_TextEffect()
		{
			LPDISPATCH result;
			InvokeHelper(0x78, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_TextFrame()
		{
			LPDISPATCH result;
			InvokeHelper(0x79, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_ThreeD()
		{
			LPDISPATCH result;
			InvokeHelper(0x7a, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		float get_Top()
		{
			float result;
			InvokeHelper(0x7b, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
			return result;
		}
		void put_Top(float newValue)
		{
			static BYTE parms[] = VTS_R4 ;
			InvokeHelper(0x7b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_Type()
		{
			long result;
			InvokeHelper(0x7c, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		long get_VerticalFlip()
		{
			long result;
			InvokeHelper(0x7d, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		VARIANT get_Vertices()
		{
			VARIANT result;
			InvokeHelper(0x7e, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		long get_Visible()
		{
			long result;
			InvokeHelper(0x7f, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_Visible(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x7f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		float get_Width()
		{
			float result;
			InvokeHelper(0x80, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
			return result;
		}
		void put_Width(float newValue)
		{
			static BYTE parms[] = VTS_R4 ;
			InvokeHelper(0x80, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_ZOrderPosition()
		{
			long result;
			InvokeHelper(0x81, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Script()
		{
			LPDISPATCH result;
			InvokeHelper(0x82, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		CString get_AlternativeText()
		{
			CString result;
			InvokeHelper(0x83, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_AlternativeText(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x83, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_HasDiagram()
		{
			long result;
			InvokeHelper(0x84, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Diagram()
		{
			LPDISPATCH result;
			InvokeHelper(0x85, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_HasDiagramNode()
		{
			long result;
			InvokeHelper(0x86, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_DiagramNode()
		{
			LPDISPATCH result;
			InvokeHelper(0x87, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Child()
		{
			long result;
			InvokeHelper(0x88, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_ParentGroup()
		{
			LPDISPATCH result;
			InvokeHelper(0x89, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_CanvasItems()
		{
			LPDISPATCH result;
			InvokeHelper(0x8a, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Id()
		{
			long result;
			InvokeHelper(0x8b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void CanvasCropLeft(float Increment)
		{
			static BYTE parms[] = VTS_R4 ;
			InvokeHelper(0x8c, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Increment);
		}
		void CanvasCropTop(float Increment)
		{
			static BYTE parms[] = VTS_R4 ;
			InvokeHelper(0x8d, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Increment);
		}
		void CanvasCropRight(float Increment)
		{
			static BYTE parms[] = VTS_R4 ;
			InvokeHelper(0x8e, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Increment);
		}
		void CanvasCropBottom(float Increment)
		{
			static BYTE parms[] = VTS_R4 ;
			InvokeHelper(0x8f, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Increment);
		}
		void put_RTF(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x90, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		LPDISPATCH get_TextFrame2()
		{
			LPDISPATCH result;
			InvokeHelper(0x91, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		void Cut()
		{
			InvokeHelper(0x92, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void Copy()
		{
			InvokeHelper(0x93, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		long get_HasChart()
		{
			long result;
			InvokeHelper(0x94, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Chart()
		{
			LPDISPATCH result;
			InvokeHelper(0x95, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_ShapeStyle()
		{
			long result;
			InvokeHelper(0x96, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_ShapeStyle(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x96, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_BackgroundStyle()
		{
			long result;
			InvokeHelper(0x97, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_BackgroundStyle(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x97, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		LPDISPATCH get_SoftEdge()
		{
			LPDISPATCH result;
			InvokeHelper(0x98, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Glow()
		{
			LPDISPATCH result;
			InvokeHelper(0x99, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Reflection()
		{
			LPDISPATCH result;
			InvokeHelper(0x9a, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		CString get_Title()
		{
			CString result;
			InvokeHelper(0x9b, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_Title(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x9b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		void MergeShapes(long MergeCmd, LPDISPATCH PrimaryShape)
		{
			static BYTE parms[] = VTS_I4 VTS_DISPATCH ;
			InvokeHelper(0x9c, DISPATCH_METHOD, VT_EMPTY, NULL, parms, MergeCmd, PrimaryShape);
		}
	};
	
	// SharedWorkspace ��װ��
	class SharedWorkspace : public COleDispatchDriver
	{
	public:
		SharedWorkspace(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		SharedWorkspace(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		SharedWorkspace(const SharedWorkspace& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// SharedWorkspace ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		CString get_Name()
		{
			CString result;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_Name(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		LPDISPATCH get_Members()
		{
			LPDISPATCH result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Tasks()
		{
			LPDISPATCH result;
			InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Files()
		{
			LPDISPATCH result;
			InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Folders()
		{
			LPDISPATCH result;
			InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Links()
		{
			LPDISPATCH result;
			InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		void Refresh()
		{
			InvokeHelper(0x6, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void CreateNew(VARIANT& URL, VARIANT& Name)
		{
			static BYTE parms[] = VTS_VARIANT VTS_VARIANT ;
			InvokeHelper(0x7, DISPATCH_METHOD, VT_EMPTY, NULL, parms, &URL, &Name);
		}
		void Delete()
		{
			InvokeHelper(0x8, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		CString get_URL()
		{
			CString result;
			InvokeHelper(0xa, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		BOOL get_Connected()
		{
			BOOL result;
			InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		VARIANT get_LastRefreshed()
		{
			VARIANT result;
			InvokeHelper(0xc, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		CString get_SourceURL()
		{
			CString result;
			InvokeHelper(0xd, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_SourceURL(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0xd, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		void RemoveDocument()
		{
			InvokeHelper(0xe, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void Disconnect()
		{
			InvokeHelper(0xf, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
	};
	
	// SharedWorkspaceFile ��װ��
	class SharedWorkspaceFile : public COleDispatchDriver
	{
	public:
		SharedWorkspaceFile(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		SharedWorkspaceFile(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		SharedWorkspaceFile(const SharedWorkspaceFile& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// SharedWorkspaceFile ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		CString get_URL()
		{
			CString result;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		CString get_CreatedBy()
		{
			CString result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		VARIANT get_CreatedDate()
		{
			VARIANT result;
			InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		CString get_ModifiedBy()
		{
			CString result;
			InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		VARIANT get_ModifiedDate()
		{
			VARIANT result;
			InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		void Delete()
		{
			InvokeHelper(0x5, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
	};
	
	// SharedWorkspaceFiles ��װ��
	class SharedWorkspaceFiles : public COleDispatchDriver
	{
	public:
		SharedWorkspaceFiles(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		SharedWorkspaceFiles(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		SharedWorkspaceFiles(const SharedWorkspaceFiles& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// SharedWorkspaceFiles ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPUNKNOWN get__NewEnum()
		{
			LPUNKNOWN result;
			InvokeHelper(0xfffffffc, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Item(long Index)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, Index);
			return result;
		}
		long get_Count()
		{
			long result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH Add(LPCTSTR FileName, VARIANT& ParentFolder, VARIANT& OverwriteIfFileAlreadyExists, VARIANT& KeepInSync)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_BSTR VTS_VARIANT VTS_VARIANT VTS_VARIANT ;
			InvokeHelper(0x2, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, FileName, &ParentFolder, &OverwriteIfFileAlreadyExists, &KeepInSync);
			return result;
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		BOOL get_ItemCountExceeded()
		{
			BOOL result;
			InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
	};
	
	// SharedWorkspaceFolder ��װ��
	class SharedWorkspaceFolder : public COleDispatchDriver
	{
	public:
		SharedWorkspaceFolder(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		SharedWorkspaceFolder(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		SharedWorkspaceFolder(const SharedWorkspaceFolder& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// SharedWorkspaceFolder ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		CString get_FolderName()
		{
			CString result;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void Delete(VARIANT& DeleteEventIfFolderContainsFiles)
		{
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x1, DISPATCH_METHOD, VT_EMPTY, NULL, parms, &DeleteEventIfFolderContainsFiles);
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
	};
	
	// SharedWorkspaceFolders ��װ��
	class SharedWorkspaceFolders : public COleDispatchDriver
	{
	public:
		SharedWorkspaceFolders(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		SharedWorkspaceFolders(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		SharedWorkspaceFolders(const SharedWorkspaceFolders& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// SharedWorkspaceFolders ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPUNKNOWN get__NewEnum()
		{
			LPUNKNOWN result;
			InvokeHelper(0xfffffffc, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Item(long Index)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, Index);
			return result;
		}
		long get_Count()
		{
			long result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH Add(LPCTSTR FolderName, VARIANT& ParentFolder)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_BSTR VTS_VARIANT ;
			InvokeHelper(0x2, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, FolderName, &ParentFolder);
			return result;
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		BOOL get_ItemCountExceeded()
		{
			BOOL result;
			InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
	};
	
	// SharedWorkspaceLink ��װ��
	class SharedWorkspaceLink : public COleDispatchDriver
	{
	public:
		SharedWorkspaceLink(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		SharedWorkspaceLink(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		SharedWorkspaceLink(const SharedWorkspaceLink& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// SharedWorkspaceLink ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		CString get_URL()
		{
			CString result;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_URL(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_Description()
		{
			CString result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_Description(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_Notes()
		{
			CString result;
			InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_Notes(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_CreatedBy()
		{
			CString result;
			InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		VARIANT get_CreatedDate()
		{
			VARIANT result;
			InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		CString get_ModifiedBy()
		{
			CString result;
			InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		VARIANT get_ModifiedDate()
		{
			VARIANT result;
			InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		void Save()
		{
			InvokeHelper(0x7, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void Delete()
		{
			InvokeHelper(0x8, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
	};
	
	// SharedWorkspaceLinks ��װ��
	class SharedWorkspaceLinks : public COleDispatchDriver
	{
	public:
		SharedWorkspaceLinks(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		SharedWorkspaceLinks(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		SharedWorkspaceLinks(const SharedWorkspaceLinks& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// SharedWorkspaceLinks ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPUNKNOWN get__NewEnum()
		{
			LPUNKNOWN result;
			InvokeHelper(0xfffffffc, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Item(long Index)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, Index);
			return result;
		}
		long get_Count()
		{
			long result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH Add(LPCTSTR URL, VARIANT& Description, VARIANT& Notes)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_BSTR VTS_VARIANT VTS_VARIANT ;
			InvokeHelper(0x2, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, URL, &Description, &Notes);
			return result;
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		BOOL get_ItemCountExceeded()
		{
			BOOL result;
			InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
	};
	
	// SharedWorkspaceMember ��װ��
	class SharedWorkspaceMember : public COleDispatchDriver
	{
	public:
		SharedWorkspaceMember(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		SharedWorkspaceMember(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		SharedWorkspaceMember(const SharedWorkspaceMember& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// SharedWorkspaceMember ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		CString get_DomainName()
		{
			CString result;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		CString get_Name()
		{
			CString result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		CString get_Email()
		{
			CString result;
			InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void Delete()
		{
			InvokeHelper(0x3, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		CString get_Id()
		{
			CString result;
			InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
	};
	
	// SharedWorkspaceMembers ��װ��
	class SharedWorkspaceMembers : public COleDispatchDriver
	{
	public:
		SharedWorkspaceMembers(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		SharedWorkspaceMembers(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		SharedWorkspaceMembers(const SharedWorkspaceMembers& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// SharedWorkspaceMembers ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPUNKNOWN get__NewEnum()
		{
			LPUNKNOWN result;
			InvokeHelper(0xfffffffc, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Item(long Index)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, Index);
			return result;
		}
		long get_Count()
		{
			long result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH Add(LPCTSTR Email, LPCTSTR DomainName, LPCTSTR DisplayName, VARIANT& Role)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR VTS_VARIANT ;
			InvokeHelper(0x2, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, Email, DomainName, DisplayName, &Role);
			return result;
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		BOOL get_ItemCountExceeded()
		{
			BOOL result;
			InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
	};
	
	// SharedWorkspaceTask ��װ��
	class SharedWorkspaceTask : public COleDispatchDriver
	{
	public:
		SharedWorkspaceTask(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		SharedWorkspaceTask(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		SharedWorkspaceTask(const SharedWorkspaceTask& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// SharedWorkspaceTask ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		CString get_Title()
		{
			CString result;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_Title(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_AssignedTo()
		{
			CString result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_AssignedTo(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_Status()
		{
			long result;
			InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_Status(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_Priority()
		{
			long result;
			InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_Priority(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_Description()
		{
			CString result;
			InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_Description(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		VARIANT get_DueDate()
		{
			VARIANT result;
			InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		void put_DueDate(VARIANT& newValue)
		{
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, &newValue);
		}
		CString get_CreatedBy()
		{
			CString result;
			InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		VARIANT get_CreatedDate()
		{
			VARIANT result;
			InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		CString get_ModifiedBy()
		{
			CString result;
			InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		VARIANT get_ModifiedDate()
		{
			VARIANT result;
			InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		void Save()
		{
			InvokeHelper(0xa, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void Delete()
		{
			InvokeHelper(0xb, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0xc, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
	};
	
	// SharedWorkspaceTasks ��װ��
	class SharedWorkspaceTasks : public COleDispatchDriver
	{
	public:
		SharedWorkspaceTasks(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		SharedWorkspaceTasks(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		SharedWorkspaceTasks(const SharedWorkspaceTasks& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// SharedWorkspaceTasks ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Item(long Index)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, Index);
			return result;
		}
		long get_Count()
		{
			long result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH Add(LPCTSTR Title, VARIANT& Status, VARIANT& Priority, VARIANT& Assignee, VARIANT& Description, VARIANT& DueDate)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_BSTR VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT ;
			InvokeHelper(0x2, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, Title, &Status, &Priority, &Assignee, &Description, &DueDate);
			return result;
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		BOOL get_ItemCountExceeded()
		{
			BOOL result;
			InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		LPUNKNOWN get__NewEnum()
		{
			LPUNKNOWN result;
			InvokeHelper(0xfffffffc, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
			return result;
		}
	};
	
	// Signature ��װ��
	class Signature : public COleDispatchDriver
	{
	public:
		Signature(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		Signature(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		Signature(const Signature& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// Signature ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		CString get_Signer()
		{
			CString result;
			InvokeHelper(0x60030000, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		CString get_Issuer()
		{
			CString result;
			InvokeHelper(0x60030001, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		VARIANT get_ExpireDate()
		{
			VARIANT result;
			InvokeHelper(0x60030002, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		BOOL get_IsValid()
		{
			BOOL result;
			InvokeHelper(0x60030003, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		BOOL get_AttachCertificate()
		{
			BOOL result;
			InvokeHelper(0x60030004, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_AttachCertificate(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x60030004, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		void Delete()
		{
			InvokeHelper(0x60030006, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x60030007, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		BOOL get_IsCertificateExpired()
		{
			BOOL result;
			InvokeHelper(0x60030008, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		BOOL get_IsCertificateRevoked()
		{
			BOOL result;
			InvokeHelper(0x60030009, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		VARIANT get_SignDate()
		{
			VARIANT result;
			InvokeHelper(0x6003000a, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		BOOL get_IsSigned()
		{
			BOOL result;
			InvokeHelper(0x6003000b, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void Sign(VARIANT& varSigImg, VARIANT& varDelSuggSigner, VARIANT& varDelSuggSignerLine2, VARIANT& varDelSuggSignerEmail)
		{
			static BYTE parms[] = VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT ;
			InvokeHelper(0x6003000c, DISPATCH_METHOD, VT_EMPTY, NULL, parms, &varSigImg, &varDelSuggSigner, &varDelSuggSignerLine2, &varDelSuggSignerEmail);
		}
		LPDISPATCH get_Details()
		{
			LPDISPATCH result;
			InvokeHelper(0x6003000d, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		void ShowDetails()
		{
			InvokeHelper(0x6003000e, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		BOOL get_CanSetup()
		{
			BOOL result;
			InvokeHelper(0x6003000f, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Setup()
		{
			LPDISPATCH result;
			InvokeHelper(0x60030010, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		BOOL get_IsSignatureLine()
		{
			BOOL result;
			InvokeHelper(0x60030011, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_SignatureLineShape()
		{
			LPDISPATCH result;
			InvokeHelper(0x60030012, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_SortHint()
		{
			long result;
			InvokeHelper(0x60030013, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
	};
	
	// SignatureInfo ��װ��
	class SignatureInfo : public COleDispatchDriver
	{
	public:
		SignatureInfo(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		SignatureInfo(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		SignatureInfo(const SignatureInfo& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// SignatureInfo ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		BOOL get_ReadOnly()
		{
			BOOL result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		CString get_SignatureProvider()
		{
			CString result;
			InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		CString get_SignatureText()
		{
			CString result;
			InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_SignatureText(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		LPDISPATCH get_SignatureImage()
		{
			LPDISPATCH result;
			InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		void put_SignatureImage(LPDISPATCH newValue)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_SignatureComment()
		{
			CString result;
			InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_SignatureComment(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		VARIANT GetSignatureDetail(long sigdet)
		{
			VARIANT result;
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x6, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms, sigdet);
			return result;
		}
		VARIANT GetCertificateDetail(long certdet)
		{
			VARIANT result;
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x7, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms, certdet);
			return result;
		}
		long get_ContentVerificationResults()
		{
			long result;
			InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		long get_CertificateVerificationResults()
		{
			long result;
			InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		BOOL get_IsValid()
		{
			BOOL result;
			InvokeHelper(0xa, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		BOOL get_IsCertificateExpired()
		{
			BOOL result;
			InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		BOOL get_IsCertificateRevoked()
		{
			BOOL result;
			InvokeHelper(0xc, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		BOOL get_IsCertificateUntrusted()
		{
			BOOL result;
			InvokeHelper(0xd, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void ShowSignatureCertificate(LPUNKNOWN ParentWindow)
		{
			static BYTE parms[] = VTS_UNKNOWN ;
			InvokeHelper(0xe, DISPATCH_METHOD, VT_EMPTY, NULL, parms, ParentWindow);
		}
		void SelectSignatureCertificate(LPUNKNOWN ParentWindow)
		{
			static BYTE parms[] = VTS_UNKNOWN ;
			InvokeHelper(0xf, DISPATCH_METHOD, VT_EMPTY, NULL, parms, ParentWindow);
		}
		void SelectCertificateDetailByThumbprint(LPCTSTR bstrThumbprint)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x10, DISPATCH_METHOD, VT_EMPTY, NULL, parms, bstrThumbprint);
		}
	};
	
	// SignatureProvider ��װ��
	class SignatureProvider : public COleDispatchDriver
	{
	public:
		SignatureProvider(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		SignatureProvider(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		SignatureProvider(const SignatureProvider& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// SignatureProvider ����
	public:
		LPDISPATCH GenerateSignatureLineImage(long siglnimg, LPDISPATCH psigsetup, LPDISPATCH psiginfo, LPUNKNOWN XmlDsigStream)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I4 VTS_DISPATCH VTS_DISPATCH VTS_UNKNOWN ;
			InvokeHelper(0x60020000, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, siglnimg, psigsetup, psiginfo, XmlDsigStream);
			return result;
		}
		void ShowSignatureSetup(LPUNKNOWN ParentWindow, LPDISPATCH psigsetup)
		{
			static BYTE parms[] = VTS_UNKNOWN VTS_DISPATCH ;
			InvokeHelper(0x60020001, DISPATCH_METHOD, VT_EMPTY, NULL, parms, ParentWindow, psigsetup);
		}
		void ShowSigningCeremony(LPUNKNOWN ParentWindow, LPDISPATCH psigsetup, LPDISPATCH psiginfo)
		{
			static BYTE parms[] = VTS_UNKNOWN VTS_DISPATCH VTS_DISPATCH ;
			InvokeHelper(0x60020002, DISPATCH_METHOD, VT_EMPTY, NULL, parms, ParentWindow, psigsetup, psiginfo);
		}
		void SignXmlDsig(LPUNKNOWN QueryContinue, LPDISPATCH psigsetup, LPDISPATCH psiginfo, LPUNKNOWN XmlDsigStream)
		{
			static BYTE parms[] = VTS_UNKNOWN VTS_DISPATCH VTS_DISPATCH VTS_UNKNOWN ;
			InvokeHelper(0x60020003, DISPATCH_METHOD, VT_EMPTY, NULL, parms, QueryContinue, psigsetup, psiginfo, XmlDsigStream);
		}
		void NotifySignatureAdded(LPUNKNOWN ParentWindow, LPDISPATCH psigsetup, LPDISPATCH psiginfo)
		{
			static BYTE parms[] = VTS_UNKNOWN VTS_DISPATCH VTS_DISPATCH ;
			InvokeHelper(0x60020004, DISPATCH_METHOD, VT_EMPTY, NULL, parms, ParentWindow, psigsetup, psiginfo);
		}
		void VerifyXmlDsig(LPUNKNOWN QueryContinue, LPDISPATCH psigsetup, LPDISPATCH psiginfo, LPUNKNOWN XmlDsigStream, long * pcontverres, long * pcertverres)
		{
			static BYTE parms[] = VTS_UNKNOWN VTS_DISPATCH VTS_DISPATCH VTS_UNKNOWN VTS_PI4 VTS_PI4 ;
			InvokeHelper(0x60020005, DISPATCH_METHOD, VT_EMPTY, NULL, parms, QueryContinue, psigsetup, psiginfo, XmlDsigStream, pcontverres, pcertverres);
		}
		void ShowSignatureDetails(LPUNKNOWN ParentWindow, LPDISPATCH psigsetup, LPDISPATCH psiginfo, LPUNKNOWN XmlDsigStream, long * pcontverres, long * pcertverres)
		{
			static BYTE parms[] = VTS_UNKNOWN VTS_DISPATCH VTS_DISPATCH VTS_UNKNOWN VTS_PI4 VTS_PI4 ;
			InvokeHelper(0x60020006, DISPATCH_METHOD, VT_EMPTY, NULL, parms, ParentWindow, psigsetup, psiginfo, XmlDsigStream, pcontverres, pcertverres);
		}
		VARIANT GetProviderDetail(long sigprovdet)
		{
			VARIANT result;
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60020007, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms, sigprovdet);
			return result;
		}
		SAFEARRAY * HashStream(LPUNKNOWN QueryContinue, LPUNKNOWN Stream)
		{
			static BYTE parms[] = VTS_UNKNOWN VTS_UNKNOWN ;
			InvokeHelper(0x60020008, DISPATCH_METHOD, VT_EMPTY, NULL, parms, QueryContinue, Stream);
		}
	};
	
	// SignatureSet ��װ��
	class SignatureSet : public COleDispatchDriver
	{
	public:
		SignatureSet(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		SignatureSet(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		SignatureSet(const SignatureSet& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// SignatureSet ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPUNKNOWN get__NewEnum()
		{
			LPUNKNOWN result;
			InvokeHelper(0xfffffffc, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
			return result;
		}
		long get_Count()
		{
			long result;
			InvokeHelper(0x60030001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Item(long iSig)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, iSig);
			return result;
		}
		LPDISPATCH Add()
		{
			LPDISPATCH result;
			InvokeHelper(0x60030003, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		void Commit()
		{
			InvokeHelper(0x60030004, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x60030005, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH AddNonVisibleSignature(VARIANT& varSigProv)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x60030006, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, &varSigProv);
			return result;
		}
		BOOL get_CanAddSignatureLine()
		{
			BOOL result;
			InvokeHelper(0x60030007, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH AddSignatureLine(VARIANT& varSigProv)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x60030008, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, &varSigProv);
			return result;
		}
		long get_Subset()
		{
			long result;
			InvokeHelper(0x60030009, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_Subset(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x60030009, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		void put_ShowSignaturesPane(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x6003000b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
	};
	
	// SignatureSetup ��װ��
	class SignatureSetup : public COleDispatchDriver
	{
	public:
		SignatureSetup(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		SignatureSetup(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		SignatureSetup(const SignatureSetup& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// SignatureSetup ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		BOOL get_ReadOnly()
		{
			BOOL result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		CString get_Id()
		{
			CString result;
			InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		CString get_SignatureProvider()
		{
			CString result;
			InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		CString get_SuggestedSigner()
		{
			CString result;
			InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_SuggestedSigner(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_SuggestedSignerLine2()
		{
			CString result;
			InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_SuggestedSignerLine2(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_SuggestedSignerEmail()
		{
			CString result;
			InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_SuggestedSignerEmail(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_SigningInstructions()
		{
			CString result;
			InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_SigningInstructions(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_AllowComments()
		{
			BOOL result;
			InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_AllowComments(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		BOOL get_ShowSignDate()
		{
			BOOL result;
			InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
			return result;
		}
		void put_ShowSignDate(BOOL newValue)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x9, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_AdditionalXml()
		{
			CString result;
			InvokeHelper(0xa, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_AdditionalXml(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0xa, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
	};
	
	// SmartArt ��װ��
	class SmartArt : public COleDispatchDriver
	{
	public:
		SmartArt(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		SmartArt(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		SmartArt(const SmartArt& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// SmartArt ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_AllNodes()
		{
			LPDISPATCH result;
			InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Nodes()
		{
			LPDISPATCH result;
			InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Layout()
		{
			LPDISPATCH result;
			InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		void put_Layout(LPDISPATCH newValue)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		LPDISPATCH get_QuickStyle()
		{
			LPDISPATCH result;
			InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		void put_QuickStyle(LPDISPATCH newValue)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		LPDISPATCH get_Color()
		{
			LPDISPATCH result;
			InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		void put_Color(LPDISPATCH newValue)
		{
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_Reverse()
		{
			long result;
			InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_Reverse(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		void Reset()
		{
			InvokeHelper(0x8, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
	};
	
	// SmartArtColor ��װ��
	class SmartArtColor : public COleDispatchDriver
	{
	public:
		SmartArtColor(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		SmartArtColor(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		SmartArtColor(const SmartArtColor& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// SmartArtColor ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		CString get_Id()
		{
			CString result;
			InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		CString get_Name()
		{
			CString result;
			InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		CString get_Description()
		{
			CString result;
			InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		CString get_Category()
		{
			CString result;
			InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
	};
	
	// SmartArtColors ��װ��
	class SmartArtColors : public COleDispatchDriver
	{
	public:
		SmartArtColors(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		SmartArtColors(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		SmartArtColors(const SmartArtColors& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// SmartArtColors ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPUNKNOWN get__NewEnum()
		{
			LPUNKNOWN result;
			InvokeHelper(0xfffffffc, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Item(VARIANT& Index)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, &Index);
			return result;
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Count()
		{
			long result;
			InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
	};
	
	// SmartArtLayout ��װ��
	class SmartArtLayout : public COleDispatchDriver
	{
	public:
		SmartArtLayout(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		SmartArtLayout(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		SmartArtLayout(const SmartArtLayout& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// SmartArtLayout ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		CString get_Id()
		{
			CString result;
			InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		CString get_Name()
		{
			CString result;
			InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		CString get_Description()
		{
			CString result;
			InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		CString get_Category()
		{
			CString result;
			InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
	};
	
	// SmartArtLayouts ��װ��
	class SmartArtLayouts : public COleDispatchDriver
	{
	public:
		SmartArtLayouts(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		SmartArtLayouts(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		SmartArtLayouts(const SmartArtLayouts& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// SmartArtLayouts ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPUNKNOWN get__NewEnum()
		{
			LPUNKNOWN result;
			InvokeHelper(0xfffffffc, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Item(VARIANT& Index)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, &Index);
			return result;
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Count()
		{
			long result;
			InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
	};
	
	// SmartArtNode ��װ��
	class SmartArtNode : public COleDispatchDriver
	{
	public:
		SmartArtNode(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		SmartArtNode(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		SmartArtNode(const SmartArtNode& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// SmartArtNode ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH AddNode(long Position, long Type)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I4 VTS_I4 ;
			InvokeHelper(0x2, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, Position, Type);
			return result;
		}
		void Delete()
		{
			InvokeHelper(0x3, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void Promote()
		{
			InvokeHelper(0x4, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void Demote()
		{
			InvokeHelper(0x5, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		long get_OrgChartLayout()
		{
			long result;
			InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_OrgChartLayout(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		LPDISPATCH get_Shapes()
		{
			LPDISPATCH result;
			InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_TextFrame2()
		{
			LPDISPATCH result;
			InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		void Larger()
		{
			InvokeHelper(0x9, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void Smaller()
		{
			InvokeHelper(0xa, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		long get_Level()
		{
			long result;
			InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		long get_Hidden()
		{
			long result;
			InvokeHelper(0xc, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Nodes()
		{
			LPDISPATCH result;
			InvokeHelper(0xd, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_ParentNode()
		{
			LPDISPATCH result;
			InvokeHelper(0xe, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Type()
		{
			long result;
			InvokeHelper(0xf, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void ReorderUp()
		{
			InvokeHelper(0x10, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void ReorderDown()
		{
			InvokeHelper(0x11, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
	};
	
	// SmartArtNodes ��װ��

	class SmartArtNodes : public COleDispatchDriver
	{
	public:
		SmartArtNodes(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		SmartArtNodes(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		SmartArtNodes(const SmartArtNodes& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// SmartArtNodes ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPUNKNOWN get__NewEnum()
		{
			LPUNKNOWN result;
			InvokeHelper(0xfffffffc, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Item(VARIANT& Index)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, &Index);
			return result;
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Count()
		{
			long result;
			InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH Add()
		{
			LPDISPATCH result;
			InvokeHelper(0x3, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
	};
	
	// SmartArtQuickStyle ��װ��
	class SmartArtQuickStyle : public COleDispatchDriver
	{
	public:
		SmartArtQuickStyle(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		SmartArtQuickStyle(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		SmartArtQuickStyle(const SmartArtQuickStyle& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// SmartArtQuickStyle ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		CString get_Id()
		{
			CString result;
			InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		CString get_Name()
		{
			CString result;
			InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		CString get_Description()
		{
			CString result;
			InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		CString get_Category()
		{
			CString result;
			InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
	};
	
	// SmartArtQuickStyles ��װ��
	class SmartArtQuickStyles : public COleDispatchDriver
	{
	public:
		SmartArtQuickStyles(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		SmartArtQuickStyles(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		SmartArtQuickStyles(const SmartArtQuickStyles& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// SmartArtQuickStyles ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPUNKNOWN get__NewEnum()
		{
			LPUNKNOWN result;
			InvokeHelper(0xfffffffc, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Item(VARIANT& Index)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, &Index);
			return result;
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Count()
		{
			long result;
			InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
	};
	
	// SmartDocument ��װ��
	class SmartDocument : public COleDispatchDriver
	{
	public:
		SmartDocument(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		SmartDocument(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		SmartDocument(const SmartDocument& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// SmartDocument ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		CString get_SolutionID()
		{
			CString result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_SolutionID(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_SolutionURL()
		{
			CString result;
			InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_SolutionURL(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		void PickSolution(BOOL ConsiderAllSchemas)
		{
			static BYTE parms[] = VTS_BOOL ;
			InvokeHelper(0x3, DISPATCH_METHOD, VT_EMPTY, NULL, parms, ConsiderAllSchemas);
		}
		void RefreshPane()
		{
			InvokeHelper(0x4, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
	};
	
	// SoftEdgeFormat ��װ��
	class SoftEdgeFormat : public COleDispatchDriver
	{
	public:
		SoftEdgeFormat(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		SoftEdgeFormat(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		SoftEdgeFormat(const SoftEdgeFormat& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// SoftEdgeFormat ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		long get_Type()
		{
			long result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_Type(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		float get_Radius()
		{
			float result;
			InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
			return result;
		}
		void put_Radius(float newValue)
		{
			static BYTE parms[] = VTS_R4 ;
			InvokeHelper(0x2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
	};
	
	// Sync ��װ��
	class Sync : public COleDispatchDriver
	{
	public:
		Sync(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		Sync(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		Sync(const Sync& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// Sync ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		long get_Status()
		{
			long result;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		CString get_WorkspaceLastChangedBy()
		{
			CString result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		VARIANT get_LastSyncTime()
		{
			VARIANT result;
			InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		long get_ErrorType()
		{
			long result;
			InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void GetUpdate()
		{
			InvokeHelper(0x6, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void PutUpdate()
		{
			InvokeHelper(0x7, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void OpenVersion(long SyncVersionType)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x8, DISPATCH_METHOD, VT_EMPTY, NULL, parms, SyncVersionType);
		}
		void ResolveConflict(long SyncConflictResolution)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x9, DISPATCH_METHOD, VT_EMPTY, NULL, parms, SyncConflictResolution);
		}
		void Unsuspend()
		{
			InvokeHelper(0xa, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0xe, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
	};
	
	// TabStop2 ��װ��
	class TabStop2 : public COleDispatchDriver
	{
	public:
		TabStop2(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		TabStop2(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		TabStop2(const TabStop2& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// TabStop2 ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		void Clear()
		{
			InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		float get_Position()
		{
			float result;
			InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
			return result;
		}
		void put_Position(float newValue)
		{
			static BYTE parms[] = VTS_R4 ;
			InvokeHelper(0x3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_Type()
		{
			long result;
			InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_Type(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
	};
	
	// TabStops2 ��װ��
	class TabStops2 : public COleDispatchDriver
	{
	public:
		TabStops2(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		TabStops2(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		TabStops2(const TabStops2& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// TabStops2 ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH Item(VARIANT& Index)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x0, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, &Index);
			return result;
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH Add(long Type, float Position)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I4 VTS_R4 ;
			InvokeHelper(0x2, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, Type, Position);
			return result;
		}
		long get_Count()
		{
			long result;
			InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		float get_DefaultSpacing()
		{
			float result;
			InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
			return result;
		}
		void put_DefaultSpacing(float newValue)
		{
			static BYTE parms[] = VTS_R4 ;
			InvokeHelper(0x4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		LPUNKNOWN get__NewEnum()
		{
			LPUNKNOWN result;
			InvokeHelper(0xfffffffc, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
			return result;
		}
	};
	
	// TextColumn2 ��װ��
	class TextColumn2 : public COleDispatchDriver
	{
	public:
		TextColumn2(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		TextColumn2(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		TextColumn2(const TextColumn2& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// TextColumn2 ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		long get_Number()
		{
			long result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_Number(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		float get_Spacing()
		{
			float result;
			InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
			return result;
		}
		void put_Spacing(float newValue)
		{
			static BYTE parms[] = VTS_R4 ;
			InvokeHelper(0x2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_TextDirection()
		{
			long result;
			InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_TextDirection(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
	};
	
	// TextEffectFormat ��װ��
	class TextEffectFormat : public COleDispatchDriver
	{
	public:
		TextEffectFormat(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		TextEffectFormat(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		TextEffectFormat(const TextEffectFormat& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// TextEffectFormat ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		void ToggleVerticalText()
		{
			InvokeHelper(0xa, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		long get_Alignment()
		{
			long result;
			InvokeHelper(0x64, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_Alignment(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x64, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_FontBold()
		{
			long result;
			InvokeHelper(0x65, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_FontBold(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x65, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_FontItalic()
		{
			long result;
			InvokeHelper(0x66, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_FontItalic(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x66, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_FontName()
		{
			CString result;
			InvokeHelper(0x67, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_FontName(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x67, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		float get_FontSize()
		{
			float result;
			InvokeHelper(0x68, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
			return result;
		}
		void put_FontSize(float newValue)
		{
			static BYTE parms[] = VTS_R4 ;
			InvokeHelper(0x68, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_KernedPairs()
		{
			long result;
			InvokeHelper(0x69, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_KernedPairs(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x69, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_NormalizedHeight()
		{
			long result;
			InvokeHelper(0x6a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_NormalizedHeight(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x6a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_PresetShape()
		{
			long result;
			InvokeHelper(0x6b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_PresetShape(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x6b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_PresetTextEffect()
		{
			long result;
			InvokeHelper(0x6c, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_PresetTextEffect(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x6c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_RotatedChars()
		{
			long result;
			InvokeHelper(0x6d, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_RotatedChars(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x6d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_Text()
		{
			CString result;
			InvokeHelper(0x6e, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_Text(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x6e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		float get_Tracking()
		{
			float result;
			InvokeHelper(0x6f, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
			return result;
		}
		void put_Tracking(float newValue)
		{
			static BYTE parms[] = VTS_R4 ;
			InvokeHelper(0x6f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
	};

	// TextFrame ��װ��

	class TextFrame : public COleDispatchDriver
	{
	public:
		TextFrame(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		TextFrame(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		TextFrame(const TextFrame& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// TextFrame ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		float get_MarginBottom()
		{
			float result;
			InvokeHelper(0x64, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
			return result;
		}
		void put_MarginBottom(float newValue)
		{
			static BYTE parms[] = VTS_R4 ;
			InvokeHelper(0x64, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		float get_MarginLeft()
		{
			float result;
			InvokeHelper(0x65, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
			return result;
		}
		void put_MarginLeft(float newValue)
		{
			static BYTE parms[] = VTS_R4 ;
			InvokeHelper(0x65, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		float get_MarginRight()
		{
			float result;
			InvokeHelper(0x66, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
			return result;
		}
		void put_MarginRight(float newValue)
		{
			static BYTE parms[] = VTS_R4 ;
			InvokeHelper(0x66, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		float get_MarginTop()
		{
			float result;
			InvokeHelper(0x67, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
			return result;
		}
		void put_MarginTop(float newValue)
		{
			static BYTE parms[] = VTS_R4 ;
			InvokeHelper(0x67, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_Orientation()
		{
			long result;
			InvokeHelper(0x68, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_Orientation(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x68, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
	};
	
	// TextFrame2 ��װ��
	class TextFrame2 : public COleDispatchDriver
	{
	public:
		TextFrame2(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		TextFrame2(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		TextFrame2(const TextFrame2& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// TextFrame2 ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		float get_MarginBottom()
		{
			float result;
			InvokeHelper(0x64, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
			return result;
		}
		void put_MarginBottom(float newValue)
		{
			static BYTE parms[] = VTS_R4 ;
			InvokeHelper(0x64, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		float get_MarginLeft()
		{
			float result;
			InvokeHelper(0x65, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
			return result;
		}
		void put_MarginLeft(float newValue)
		{
			static BYTE parms[] = VTS_R4 ;
			InvokeHelper(0x65, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		float get_MarginRight()
		{
			float result;
			InvokeHelper(0x66, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
			return result;
		}
		void put_MarginRight(float newValue)
		{
			static BYTE parms[] = VTS_R4 ;
			InvokeHelper(0x66, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		float get_MarginTop()
		{
			float result;
			InvokeHelper(0x67, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
			return result;
		}
		void put_MarginTop(float newValue)
		{
			static BYTE parms[] = VTS_R4 ;
			InvokeHelper(0x67, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_Orientation()
		{
			long result;
			InvokeHelper(0x68, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_Orientation(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x68, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_HorizontalAnchor()
		{
			long result;
			InvokeHelper(0x69, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_HorizontalAnchor(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x69, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_VerticalAnchor()
		{
			long result;
			InvokeHelper(0x6a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_VerticalAnchor(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x6a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_PathFormat()
		{
			long result;
			InvokeHelper(0x6b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_PathFormat(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x6b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_WarpFormat()
		{
			long result;
			InvokeHelper(0x6c, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_WarpFormat(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x6c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_WordArtformat()
		{
			long result;
			InvokeHelper(0x6d, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_WordArtformat(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x6d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_WordWrap()
		{
			long result;
			InvokeHelper(0x6e, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_WordWrap(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x6e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_AutoSize()
		{
			long result;
			InvokeHelper(0x6f, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_AutoSize(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x6f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		LPDISPATCH get_ThreeD()
		{
			LPDISPATCH result;
			InvokeHelper(0x70, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_HasText()
		{
			long result;
			InvokeHelper(0x71, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_TextRange()
		{
			LPDISPATCH result;
			InvokeHelper(0x72, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Column()
		{
			LPDISPATCH result;
			InvokeHelper(0x73, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Ruler()
		{
			LPDISPATCH result;
			InvokeHelper(0x74, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		void DeleteText()
		{
			InvokeHelper(0x75, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		long get_NoTextRotation()
		{
			long result;
			InvokeHelper(0x76, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_NoTextRotation(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x76, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
	};
	
	// TextRange2 ��װ��
	class TextRange2 : public COleDispatchDriver
	{
	public:
		TextRange2(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		TextRange2(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		TextRange2(const TextRange2& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// TextRange2 ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		CString get_Text()
		{
			CString result;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_Text(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_Count()
		{
			long result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH Item(VARIANT& Index)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x2, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, &Index);
			return result;
		}
		LPUNKNOWN get__NewEnum()
		{
			LPUNKNOWN result;
			InvokeHelper(0xfffffffc, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Paragraphs(long Start, long Length)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I4 VTS_I4 ;
			InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, Start, Length);
			return result;
		}
		LPDISPATCH get_Sentences(long Start, long Length)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I4 VTS_I4 ;
			InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, Start, Length);
			return result;
		}
		LPDISPATCH get_Words(long Start, long Length)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I4 VTS_I4 ;
			InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, Start, Length);
			return result;
		}
		LPDISPATCH get_Characters(long Start, long Length)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I4 VTS_I4 ;
			InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, Start, Length);
			return result;
		}
		LPDISPATCH get_Lines(long Start, long Length)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I4 VTS_I4 ;
			InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, Start, Length);
			return result;
		}
		LPDISPATCH get_Runs(long Start, long Length)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I4 VTS_I4 ;
			InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, Start, Length);
			return result;
		}
		LPDISPATCH get_ParagraphFormat()
		{
			LPDISPATCH result;
			InvokeHelper(0xa, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Font()
		{
			LPDISPATCH result;
			InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Length()
		{
			long result;
			InvokeHelper(0xc, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		long get_Start()
		{
			long result;
			InvokeHelper(0xd, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		float get_BoundLeft()
		{
			float result;
			InvokeHelper(0xe, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
			return result;
		}
		float get_BoundTop()
		{
			float result;
			InvokeHelper(0xf, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
			return result;
		}
		float get_BoundWidth()
		{
			float result;
			InvokeHelper(0x10, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
			return result;
		}
		float get_BoundHeight()
		{
			float result;
			InvokeHelper(0x11, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH TrimText()
		{
			LPDISPATCH result;
			InvokeHelper(0x12, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH InsertAfter(LPCTSTR NewText)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x13, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, NewText);
			return result;
		}
		LPDISPATCH InsertBefore(LPCTSTR NewText)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x14, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, NewText);
			return result;
		}
		LPDISPATCH InsertSymbol(LPCTSTR FontName, long CharNumber, long Unicode)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_BSTR VTS_I4 VTS_I4 ;
			InvokeHelper(0x15, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, FontName, CharNumber, Unicode);
			return result;
		}
		void Select()
		{
			InvokeHelper(0x16, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void Cut()
		{
			InvokeHelper(0x17, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void Copy()
		{
			InvokeHelper(0x18, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void Delete()
		{
			InvokeHelper(0x19, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		LPDISPATCH Paste()
		{
			LPDISPATCH result;
			InvokeHelper(0x1a, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH PasteSpecial(long Format)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x1b, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, Format);
			return result;
		}
		void ChangeCase(long Type)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x1c, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Type);
		}
		void AddPeriods()
		{
			InvokeHelper(0x1d, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void RemovePeriods()
		{
			InvokeHelper(0x1e, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		LPDISPATCH Find(LPCTSTR FindWhat, long After, long MatchCase, long WholeWords)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_BSTR VTS_I4 VTS_I4 VTS_I4 ;
			InvokeHelper(0x1f, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, FindWhat, After, MatchCase, WholeWords);
			return result;
		}
		LPDISPATCH Replace(LPCTSTR FindWhat, LPCTSTR ReplaceWhat, long After, long MatchCase, long WholeWords)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_I4 VTS_I4 VTS_I4 ;
			InvokeHelper(0x20, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, FindWhat, ReplaceWhat, After, MatchCase, WholeWords);
			return result;
		}
		void RotatedBounds(float * X1, float * Y1, float * X2, float * Y2, float * X3, float * Y3, float * x4, float * y4)
		{
			static BYTE parms[] = VTS_PR4 VTS_PR4 VTS_PR4 VTS_PR4 VTS_PR4 VTS_PR4 VTS_PR4 VTS_PR4 ;
			InvokeHelper(0x21, DISPATCH_METHOD, VT_EMPTY, NULL, parms, X1, Y1, X2, Y2, X3, Y3, x4, y4);
		}
		long get_LanguageID()
		{
			long result;
			InvokeHelper(0x22, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_LanguageID(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x22, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		void RtlRun()
		{
			InvokeHelper(0x23, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void LtrRun()
		{
			InvokeHelper(0x24, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		LPDISPATCH get_MathZones(long Start, long Length)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I4 VTS_I4 ;
			InvokeHelper(0x25, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, Start, Length);
			return result;
		}
		LPDISPATCH InsertChartField(long ChartFieldType, LPCTSTR Formula, long Position)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I4 VTS_BSTR VTS_I4 ;
			InvokeHelper(0x26, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, ChartFieldType, Formula, Position);
			return result;
		}
	};
	
	// ThemeColor ��װ��
	class ThemeColor : public COleDispatchDriver
	{
	public:
		ThemeColor(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		ThemeColor(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		ThemeColor(const ThemeColor& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// ThemeColor ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		long get_RGB()
		{
			long result;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_RGB(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_ThemeColorSchemeIndex()
		{
			long result;
			InvokeHelper(0x60030003, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
	};
	
	// ThemeColorScheme ��װ��
	class ThemeColorScheme : public COleDispatchDriver
	{
	public:
		ThemeColorScheme(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		ThemeColorScheme(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		ThemeColorScheme(const ThemeColorScheme& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// ThemeColorScheme ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Count()
		{
			long result;
			InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH Colors(long Index)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x0, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, Index);
			return result;
		}
		LPUNKNOWN get__NewEnum()
		{
			LPUNKNOWN result;
			InvokeHelper(0xfffffffc, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
			return result;
		}
		void Load(LPCTSTR FileName)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x3, DISPATCH_METHOD, VT_EMPTY, NULL, parms, FileName);
		}
		void Save(LPCTSTR FileName)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x4, DISPATCH_METHOD, VT_EMPTY, NULL, parms, FileName);
		}
		long GetCustomColor(LPCTSTR Name)
		{
			long result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x5, DISPATCH_METHOD, VT_I4, (void*)&result, parms, Name);
			return result;
		}
	};
	
	// ThemeEffectScheme ��װ��
	class ThemeEffectScheme : public COleDispatchDriver
	{
	public:
		ThemeEffectScheme(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		ThemeEffectScheme(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		ThemeEffectScheme(const ThemeEffectScheme& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// ThemeEffectScheme ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		void Load(LPCTSTR FileName)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, parms, FileName);
		}
	};
	
	// ThemeFont ��װ��
	class ThemeFont : public COleDispatchDriver
	{
	public:
		ThemeFont(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		ThemeFont(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		ThemeFont(const ThemeFont& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// ThemeFont ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		CString get_Name()
		{
			CString result;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_Name(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
	};
	
	// ThemeFonts ��װ��
	class ThemeFonts : public COleDispatchDriver
	{
	public:
		ThemeFonts(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		ThemeFonts(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		ThemeFonts(const ThemeFonts& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// ThemeFonts ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Count()
		{
			long result;
			InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH Item(long Index)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x0, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, Index);
			return result;
		}
		LPUNKNOWN get__NewEnum()
		{
			LPUNKNOWN result;
			InvokeHelper(0xfffffffc, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
			return result;
		}
	};
	
	// ThemeFontScheme ��װ��
	class ThemeFontScheme : public COleDispatchDriver
	{
	public:
		ThemeFontScheme(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		ThemeFontScheme(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		ThemeFontScheme(const ThemeFontScheme& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// ThemeFontScheme ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		void Load(LPCTSTR FileName)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, parms, FileName);
		}
		void Save(LPCTSTR FileName)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x3, DISPATCH_METHOD, VT_EMPTY, NULL, parms, FileName);
		}
		LPDISPATCH get_MinorFont()
		{
			LPDISPATCH result;
			InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_MajorFont()
		{
			LPDISPATCH result;
			InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
	};
	
	// ThreeDFormat ��װ��
	class ThreeDFormat : public COleDispatchDriver
	{
	public:
		ThreeDFormat(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		ThreeDFormat(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		ThreeDFormat(const ThreeDFormat& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// ThreeDFormat ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		void IncrementRotationX(float Increment)
		{
			static BYTE parms[] = VTS_R4 ;
			InvokeHelper(0xa, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Increment);
		}
		void IncrementRotationY(float Increment)
		{
			static BYTE parms[] = VTS_R4 ;
			InvokeHelper(0xb, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Increment);
		}
		void ResetRotation()
		{
			InvokeHelper(0xc, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void SetThreeDFormat(long PresetThreeDFormat)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0xd, DISPATCH_METHOD, VT_EMPTY, NULL, parms, PresetThreeDFormat);
		}
		void SetExtrusionDirection(long PresetExtrusionDirection)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0xe, DISPATCH_METHOD, VT_EMPTY, NULL, parms, PresetExtrusionDirection);
		}
		float get_Depth()
		{
			float result;
			InvokeHelper(0x64, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
			return result;
		}
		void put_Depth(float newValue)
		{
			static BYTE parms[] = VTS_R4 ;
			InvokeHelper(0x64, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		LPDISPATCH get_ExtrusionColor()
		{
			LPDISPATCH result;
			InvokeHelper(0x65, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_ExtrusionColorType()
		{
			long result;
			InvokeHelper(0x66, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_ExtrusionColorType(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x66, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_Perspective()
		{
			long result;
			InvokeHelper(0x67, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_Perspective(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x67, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_PresetExtrusionDirection()
		{
			long result;
			InvokeHelper(0x68, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		long get_PresetLightingDirection()
		{
			long result;
			InvokeHelper(0x69, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_PresetLightingDirection(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x69, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_PresetLightingSoftness()
		{
			long result;
			InvokeHelper(0x6a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_PresetLightingSoftness(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x6a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_PresetMaterial()
		{
			long result;
			InvokeHelper(0x6b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_PresetMaterial(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x6b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_PresetThreeDFormat()
		{
			long result;
			InvokeHelper(0x6c, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		float get_RotationX()
		{
			float result;
			InvokeHelper(0x6d, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
			return result;
		}
		void put_RotationX(float newValue)
		{
			static BYTE parms[] = VTS_R4 ;
			InvokeHelper(0x6d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		float get_RotationY()
		{
			float result;
			InvokeHelper(0x6e, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
			return result;
		}
		void put_RotationY(float newValue)
		{
			static BYTE parms[] = VTS_R4 ;
			InvokeHelper(0x6e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_Visible()
		{
			long result;
			InvokeHelper(0x6f, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_Visible(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x6f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		void SetPresetCamera(long PresetCamera)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0xf, DISPATCH_METHOD, VT_EMPTY, NULL, parms, PresetCamera);
		}
		void IncrementRotationZ(float Increment)
		{
			static BYTE parms[] = VTS_R4 ;
			InvokeHelper(0x10, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Increment);
		}
		void IncrementRotationHorizontal(float Increment)
		{
			static BYTE parms[] = VTS_R4 ;
			InvokeHelper(0x11, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Increment);
		}
		void IncrementRotationVertical(float Increment)
		{
			static BYTE parms[] = VTS_R4 ;
			InvokeHelper(0x12, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Increment);
		}
		long get_PresetLighting()
		{
			long result;
			InvokeHelper(0x70, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_PresetLighting(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x70, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		float get_Z()
		{
			float result;
			InvokeHelper(0x71, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
			return result;
		}
		void put_Z(float newValue)
		{
			static BYTE parms[] = VTS_R4 ;
			InvokeHelper(0x71, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_BevelTopType()
		{
			long result;
			InvokeHelper(0x72, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_BevelTopType(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x72, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		float get_BevelTopInset()
		{
			float result;
			InvokeHelper(0x73, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
			return result;
		}
		void put_BevelTopInset(float newValue)
		{
			static BYTE parms[] = VTS_R4 ;
			InvokeHelper(0x73, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		float get_BevelTopDepth()
		{
			float result;
			InvokeHelper(0x74, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
			return result;
		}
		void put_BevelTopDepth(float newValue)
		{
			static BYTE parms[] = VTS_R4 ;
			InvokeHelper(0x74, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_BevelBottomType()
		{
			long result;
			InvokeHelper(0x75, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_BevelBottomType(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x75, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		float get_BevelBottomInset()
		{
			float result;
			InvokeHelper(0x76, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
			return result;
		}
		void put_BevelBottomInset(float newValue)
		{
			static BYTE parms[] = VTS_R4 ;
			InvokeHelper(0x76, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		float get_BevelBottomDepth()
		{
			float result;
			InvokeHelper(0x77, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
			return result;
		}
		void put_BevelBottomDepth(float newValue)
		{
			static BYTE parms[] = VTS_R4 ;
			InvokeHelper(0x77, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_PresetCamera()
		{
			long result;
			InvokeHelper(0x78, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		float get_RotationZ()
		{
			float result;
			InvokeHelper(0x79, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
			return result;
		}
		void put_RotationZ(float newValue)
		{
			static BYTE parms[] = VTS_R4 ;
			InvokeHelper(0x79, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		float get_ContourWidth()
		{
			float result;
			InvokeHelper(0x7a, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
			return result;
		}
		void put_ContourWidth(float newValue)
		{
			static BYTE parms[] = VTS_R4 ;
			InvokeHelper(0x7a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		LPDISPATCH get_ContourColor()
		{
			LPDISPATCH result;
			InvokeHelper(0x7b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		float get_FieldOfView()
		{
			float result;
			InvokeHelper(0x7c, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
			return result;
		}
		void put_FieldOfView(float newValue)
		{
			static BYTE parms[] = VTS_R4 ;
			InvokeHelper(0x7c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_ProjectText()
		{
			long result;
			InvokeHelper(0x7d, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_ProjectText(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x7d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		float get_LightAngle()
		{
			float result;
			InvokeHelper(0x7e, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
			return result;
		}
		void put_LightAngle(float newValue)
		{
			static BYTE parms[] = VTS_R4 ;
			InvokeHelper(0x7e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
	};
	
	// UserPermission ��װ��
	class UserPermission : public COleDispatchDriver
	{
	public:
		UserPermission(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		UserPermission(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		UserPermission(const UserPermission& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// UserPermission ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		CString get_UserId()
		{
			CString result;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		long get_Permission()
		{
			long result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_Permission(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		VARIANT get_ExpirationDate()
		{
			VARIANT result;
			InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
			return result;
		}
		void put_ExpirationDate(VARIANT& newValue)
		{
			static BYTE parms[] = VTS_VARIANT ;
			InvokeHelper(0x2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, &newValue);
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		void Remove()
		{
			InvokeHelper(0x4, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
	};
	
	// WebComponent ��װ��
	class WebComponent : public COleDispatchDriver
	{
	public:
		WebComponent(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		WebComponent(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		WebComponent(const WebComponent& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// WebComponent ����
	public:
		LPDISPATCH get_Shape()
		{
			LPDISPATCH result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		CString get_URL()
		{
			CString result;
			InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_URL(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_HTML()
		{
			CString result;
			InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_HTML(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_Name()
		{
			CString result;
			InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_Name(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_Width()
		{
			long result;
			InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_Width(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_Height()
		{
			long result;
			InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_Height(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		void SetPlaceHolderGraphic(LPCTSTR PlaceHolderGraphic)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x7, DISPATCH_METHOD, VT_EMPTY, NULL, parms, PlaceHolderGraphic);
		}
		void Commit()
		{
			InvokeHelper(0x8, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		void Revert()
		{
			InvokeHelper(0x9, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
	};
	
	// WebComponentFormat ��װ��
	class WebComponentFormat : public COleDispatchDriver
	{
	public:
		WebComponentFormat(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		WebComponentFormat(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		WebComponentFormat(const WebComponentFormat& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// WebComponentFormat ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Parent()
		{
			LPDISPATCH result;
			InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		CString get_URL()
		{
			CString result;
			InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_URL(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_HTML()
		{
			CString result;
			InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_HTML(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_Name()
		{
			CString result;
			InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_Name(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_Width()
		{
			long result;
			InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_Width(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_Height()
		{
			long result;
			InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_Height(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_PreviewGraphic()
		{
			CString result;
			InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_PreviewGraphic(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		void LaunchPropertiesWindow()
		{
			InvokeHelper(0x9, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
	};
	
	// WebComponentProperties ��װ��
	class WebComponentProperties : public COleDispatchDriver
	{
	public:
		WebComponentProperties(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		WebComponentProperties(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		WebComponentProperties(const WebComponentProperties& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// WebComponentProperties ����
	public:
		LPDISPATCH get_Shape()
		{
			LPDISPATCH result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		CString get_Name()
		{
			CString result;
			InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_Name(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_URL()
		{
			CString result;
			InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_URL(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_HTML()
		{
			CString result;
			InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_HTML(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_PreviewGraphic()
		{
			CString result;
			InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_PreviewGraphic(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_PreviewHTML()
		{
			CString result;
			InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_PreviewHTML(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_Width()
		{
			long result;
			InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_Width(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		long get_Height()
		{
			long result;
			InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		void put_Height(long newValue)
		{
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_Tag()
		{
			CString result;
			InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_Tag(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x9, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
	};
	
	// WebComponentWindowExternal ��װ��
	class WebComponentWindowExternal : public COleDispatchDriver
	{
	public:
		WebComponentWindowExternal(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		WebComponentWindowExternal(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		WebComponentWindowExternal(const WebComponentWindowExternal& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// WebComponentWindowExternal ����
	public:
		long get_InterfaceVersion()
		{
			long result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		CString get_ApplicationName()
		{
			CString result;
			InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		long get_ApplicationVersion()
		{
			long result;
			InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		void CloseWindow()
		{
			InvokeHelper(0x5, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
		}
		LPDISPATCH get_WebComponent()
		{
			LPDISPATCH result;
			InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
	};
	
	// WebPageFont ��װ��
	class WebPageFont : public COleDispatchDriver
	{
	public:
		WebPageFont(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		WebPageFont(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		WebPageFont(const WebPageFont& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// WebPageFont ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		CString get_ProportionalFont()
		{
			CString result;
			InvokeHelper(0xa, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_ProportionalFont(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0xa, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		float get_ProportionalFontSize()
		{
			float result;
			InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
			return result;
		}
		void put_ProportionalFontSize(float newValue)
		{
			static BYTE parms[] = VTS_R4 ;
			InvokeHelper(0xb, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		CString get_FixedWidthFont()
		{
			CString result;
			InvokeHelper(0xc, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		void put_FixedWidthFont(LPCTSTR newValue)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0xc, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
		float get_FixedWidthFontSize()
		{
			float result;
			InvokeHelper(0xd, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
			return result;
		}
		void put_FixedWidthFontSize(float newValue)
		{
			static BYTE parms[] = VTS_R4 ;
			InvokeHelper(0xd, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
		}
	};
	
	// WebPageFonts ��װ��
	class WebPageFonts : public COleDispatchDriver
	{
	public:
		WebPageFonts(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		WebPageFonts(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		WebPageFonts(const WebPageFonts& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// WebPageFonts ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		long get_Count()
		{
			long result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Item(long Index)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, Index);
			return result;
		}
		LPUNKNOWN get__NewEnum()
		{
			LPUNKNOWN result;
			InvokeHelper(0xfffffffc, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
			return result;
		}
	};
	
	// WorkflowTask ��װ��
	class WorkflowTask : public COleDispatchDriver
	{
	public:
		WorkflowTask(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		WorkflowTask(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		WorkflowTask(const WorkflowTask& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// WorkflowTask ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		CString get_Id()
		{
			CString result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		CString get_ListID()
		{
			CString result;
			InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		CString get_WorkflowID()
		{
			CString result;
			InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		CString get_Name()
		{
			CString result;
			InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		CString get_Description()
		{
			CString result;
			InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		CString get_AssignedTo()
		{
			CString result;
			InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		CString get_CreatedBy()
		{
			CString result;
			InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		DATE get_DueDate()
		{
			DATE result;
			InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_DATE, (void*)&result, NULL);
			return result;
		}
		DATE get_CreatedDate()
		{
			DATE result;
			InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_DATE, (void*)&result, NULL);
			return result;
		}
		long Show()
		{
			long result;
			InvokeHelper(0xa, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
			return result;
		}
	};
	
	// WorkflowTasks ��װ��
	class WorkflowTasks : public COleDispatchDriver
	{
	public:
		WorkflowTasks(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		WorkflowTasks(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		WorkflowTasks(const WorkflowTasks& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// WorkflowTasks ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Item(long Index)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, Index);
			return result;
		}
		long get_Count()
		{
			long result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPUNKNOWN get__NewEnum()
		{
			LPUNKNOWN result;
			InvokeHelper(0xfffffffc, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
			return result;
		}
	};
	
	// WorkflowTemplate ��װ��
	class WorkflowTemplate : public COleDispatchDriver
	{
	public:
		WorkflowTemplate(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		WorkflowTemplate(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		WorkflowTemplate(const WorkflowTemplate& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// WorkflowTemplate ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		CString get_Id()
		{
			CString result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		CString get_Name()
		{
			CString result;
			InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		CString get_Description()
		{
			CString result;
			InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		CString get_DocumentLibraryName()
		{
			CString result;
			InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		CString get_DocumentLibraryURL()
		{
			CString result;
			InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		long Show()
		{
			long result;
			InvokeHelper(0x6, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
			return result;
		}
	};
	
	// WorkflowTemplates ��װ��
	class WorkflowTemplates : public COleDispatchDriver
	{
	public:
		WorkflowTemplates(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
		WorkflowTemplates(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		WorkflowTemplates(const WorkflowTemplates& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// WorkflowTemplates ����
	public:
		LPDISPATCH get_Application()
		{
			LPDISPATCH result;
			InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long get_Creator()
		{
			long result;
			InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH get_Item(long Index)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, Index);
			return result;
		}
		long get_Count()
		{
			long result;
			InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPUNKNOWN get__NewEnum()
		{
			LPUNKNOWN result;
			InvokeHelper(0xfffffffc, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
			return result;
		}
	};

}



