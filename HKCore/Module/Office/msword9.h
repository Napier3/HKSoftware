#ifndef MSWORD_H__
#define MSWORD_H__
// Machine generated IDispatch wrapper class(es) created with ClassWizard
/////////////////////////////////////////////////////////////////////////////
// _Application wrapper class
namespace MSWord
{
	class _Application : public COleDispatchDriver
	{
	public:
		_Application() {}		// Calls COleDispatchDriver default constructor
		_Application(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		_Application(const _Application& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		CString GetName();
		LPDISPATCH GetDocuments();
		LPDISPATCH GetWindows();
		LPDISPATCH GetActiveDocument();
		LPDISPATCH GetActiveWindow();
		LPDISPATCH GetSelection();
		LPDISPATCH GetWordBasic();
		LPDISPATCH GetRecentFiles();
		LPDISPATCH GetNormalTemplate();
		LPDISPATCH GetSystem();
		LPDISPATCH GetAutoCorrect();
		LPDISPATCH GetFontNames();
		LPDISPATCH GetLandscapeFontNames();
		LPDISPATCH GetPortraitFontNames();
		LPDISPATCH GetLanguages();
		LPDISPATCH GetAssistant();
		LPDISPATCH GetBrowser();
		LPDISPATCH GetFileConverters();
		LPDISPATCH GetMailingLabel();
		LPDISPATCH GetDialogs();
		LPDISPATCH GetCaptionLabels();
		LPDISPATCH GetAutoCaptions();
		LPDISPATCH GetAddIns();
		BOOL GetVisible();
		void SetVisible(BOOL bNewValue);
		CString GetVersion();
		BOOL GetScreenUpdating();
		void SetScreenUpdating(BOOL bNewValue);
		BOOL GetPrintPreview();
		void SetPrintPreview(BOOL bNewValue);
		LPDISPATCH GetTasks();
		BOOL GetDisplayStatusBar();
		void SetDisplayStatusBar(BOOL bNewValue);
		BOOL GetSpecialMode();
		long GetUsableWidth();
		long GetUsableHeight();
		BOOL GetMathCoprocessorAvailable();
		BOOL GetMouseAvailable();
		VARIANT GetInternational(long Index);
		CString GetBuild();
		BOOL GetCapsLock();
		BOOL GetNumLock();
		CString GetUserName_();
		void SetUserName(LPCTSTR lpszNewValue);
		CString GetUserInitials();
		void SetUserInitials(LPCTSTR lpszNewValue);
		CString GetUserAddress();
		void SetUserAddress(LPCTSTR lpszNewValue);
		LPDISPATCH GetMacroContainer();
		BOOL GetDisplayRecentFiles();
		void SetDisplayRecentFiles(BOOL bNewValue);
		LPDISPATCH GetCommandBars();
		LPDISPATCH GetSynonymInfo(LPCTSTR Word, VARIANT* LanguageID);
		LPDISPATCH GetVbe();
		CString GetDefaultSaveFormat();
		void SetDefaultSaveFormat(LPCTSTR lpszNewValue);
		LPDISPATCH GetListGalleries();
		CString GetActivePrinter();
		void SetActivePrinter(LPCTSTR lpszNewValue);
		LPDISPATCH GetTemplates();
		LPDISPATCH GetCustomizationContext();
		void SetCustomizationContext(LPDISPATCH newValue);
		LPDISPATCH GetKeyBindings();
		LPDISPATCH GetKeysBoundTo(long KeyCategory, LPCTSTR Command, VARIANT* CommandParameter);
		LPDISPATCH GetFindKey(long KeyCode, VARIANT* KeyCode2);
		CString GetCaption();
		void SetCaption(LPCTSTR lpszNewValue);
		CString GetPath();
		BOOL GetDisplayScrollBars();
		void SetDisplayScrollBars(BOOL bNewValue);
		CString GetStartupPath();
		void SetStartupPath(LPCTSTR lpszNewValue);
		long GetBackgroundSavingStatus();
		long GetBackgroundPrintingStatus();
		long GetLeft();
		void SetLeft(long nNewValue);
		long GetTop();
		void SetTop(long nNewValue);
		long GetWidth();
		void SetWidth(long nNewValue);
		long GetHeight();
		void SetHeight(long nNewValue);
		long GetWindowState();
		void SetWindowState(long nNewValue);
		BOOL GetDisplayAutoCompleteTips();
		void SetDisplayAutoCompleteTips(BOOL bNewValue);
		LPDISPATCH GetOptions();
		long GetDisplayAlerts();
		void SetDisplayAlerts(long nNewValue);
		LPDISPATCH GetCustomDictionaries();
		CString GetPathSeparator();
		void SetStatusBar(LPCTSTR lpszNewValue);
		BOOL GetMAPIAvailable();
		BOOL GetDisplayScreenTips();
		void SetDisplayScreenTips(BOOL bNewValue);
		long GetEnableCancelKey();
		void SetEnableCancelKey(long nNewValue);
		BOOL GetUserControl();
		LPDISPATCH GetFileSearch();
		long GetMailSystem();
		CString GetDefaultTableSeparator();
		void SetDefaultTableSeparator(LPCTSTR lpszNewValue);
		BOOL GetShowVisualBasicEditor();
		void SetShowVisualBasicEditor(BOOL bNewValue);
		CString GetBrowseExtraFileTypes();
		void SetBrowseExtraFileTypes(LPCTSTR lpszNewValue);
		BOOL GetIsObjectValid(LPDISPATCH Object);
		LPDISPATCH GetHangulHanjaDictionaries();
		LPDISPATCH GetMailMessage();
		BOOL GetFocusInMailHeader();
		void Quit(VARIANT* SaveChanges, VARIANT* OriginalFormat, VARIANT* RouteDocument);
		void ScreenRefresh();
		void LookupNameProperties(LPCTSTR Name);
		void SubstituteFont(LPCTSTR UnavailableFont, LPCTSTR SubstituteFont);
		BOOL Repeat(VARIANT* Times);
		void DDEExecute(long Channel, LPCTSTR Command);
		long DDEInitiate(LPCTSTR App, LPCTSTR Topic);
		void DDEPoke(long Channel, LPCTSTR Item, LPCTSTR Data);
		CString DDERequest(long Channel, LPCTSTR Item);
		void DDETerminate(long Channel);
		void DDETerminateAll();
		long BuildKeyCode(long Arg1, VARIANT* Arg2, VARIANT* Arg3, VARIANT* Arg4);
		CString KeyString(long KeyCode, VARIANT* KeyCode2);
		void OrganizerCopy(LPCTSTR Source, LPCTSTR Destination, LPCTSTR Name, long Object);
		void OrganizerDelete(LPCTSTR Source, LPCTSTR Name, long Object);
		void OrganizerRename(LPCTSTR Source, LPCTSTR Name, LPCTSTR NewName, long Object);
		// method 'AddAddress' not emitted because of invalid return type or parameter type
		CString GetAddress(VARIANT* Name, VARIANT* AddressProperties, VARIANT* UseAutoText, VARIANT* DisplaySelectDialog, VARIANT* SelectDialog, VARIANT* CheckNamesDialog, VARIANT* RecentAddressesChoice, VARIANT* UpdateRecentAddresses);
		BOOL CheckGrammar(LPCTSTR String);
		BOOL CheckSpelling(LPCTSTR Word, VARIANT* CustomDictionary, VARIANT* IgnoreUppercase, VARIANT* MainDictionary, VARIANT* CustomDictionary2, VARIANT* CustomDictionary3, VARIANT* CustomDictionary4, VARIANT* CustomDictionary5, 
			VARIANT* CustomDictionary6, VARIANT* CustomDictionary7, VARIANT* CustomDictionary8, VARIANT* CustomDictionary9, VARIANT* CustomDictionary10);
		void ResetIgnoreAll();
		LPDISPATCH GetSpellingSuggestions(LPCTSTR Word, VARIANT* CustomDictionary, VARIANT* IgnoreUppercase, VARIANT* MainDictionary, VARIANT* SuggestionMode, VARIANT* CustomDictionary2, VARIANT* CustomDictionary3, VARIANT* CustomDictionary4, 
			VARIANT* CustomDictionary5, VARIANT* CustomDictionary6, VARIANT* CustomDictionary7, VARIANT* CustomDictionary8, VARIANT* CustomDictionary9, VARIANT* CustomDictionary10);
		void GoBack();
		void Help(VARIANT* HelpType);
		void AutomaticChange();
		void ShowMe();
		void HelpTool();
		LPDISPATCH NewWindow();
		void ListCommands(BOOL ListAllCommands);
		void ShowClipboard();
		void OnTime(VARIANT* When, LPCTSTR Name, VARIANT* Tolerance);
		void NextLetter();
		short MountVolume(LPCTSTR Zone, LPCTSTR Server, LPCTSTR Volume, VARIANT* User, VARIANT* UserPassword, VARIANT* VolumePassword);
		CString CleanString(LPCTSTR String);
		void SendFax();
		void ChangeFileOpenDirectory(LPCTSTR Path);
		void GoForward();
		void Move(long Left, long Top);
		void Resize(long Width, long Height);
		float InchesToPoints(float Inches);
		float CentimetersToPoints(float Centimeters);
		float MillimetersToPoints(float Millimeters);
		float PicasToPoints(float Picas);
		float LinesToPoints(float Lines);
		float PointsToInches(float Points);
		float PointsToCentimeters(float Points);
		float PointsToMillimeters(float Points);
		float PointsToPicas(float Points);
		float PointsToLines(float Points);
		void Activate();
		float PointsToPixels(float Points, VARIANT* fVertical);
		float PixelsToPoints(float Pixels, VARIANT* fVertical);
		void KeyboardLatin();
		void KeyboardBidi();
		void ToggleKeyboard();
		long Keyboard(long LangId);
		CString ProductCode();
		LPDISPATCH DefaultWebOptions();
		void SetDefaultTheme(LPCTSTR Name, long DocumentType);
		CString GetDefaultTheme(long DocumentType);
		LPDISPATCH GetEmailOptions();
		long GetLanguage();
		LPDISPATCH GetCOMAddIns();
		BOOL GetCheckLanguage();
		void SetCheckLanguage(BOOL bNewValue);
		LPDISPATCH GetLanguageSettings();
		LPDISPATCH GetAnswerWizard();
		long GetFeatureInstall();
		void SetFeatureInstall(long nNewValue);
		void PrintOut(VARIANT* Background, VARIANT* Append, VARIANT* Range, VARIANT* OutputFileName, VARIANT* From, VARIANT* To, VARIANT* Item, VARIANT* Copies, VARIANT* Pages, VARIANT* PageType, VARIANT* PrintToFile, VARIANT* Collate, 
			VARIANT* FileName, VARIANT* ActivePrinterMacGX, VARIANT* ManualDuplexPrint, VARIANT* PrintZoomColumn, VARIANT* PrintZoomRow, VARIANT* PrintZoomPaperWidth, VARIANT* PrintZoomPaperHeight);
		VARIANT Run(LPCTSTR MacroName, VARIANT* varg1, VARIANT* varg2, VARIANT* varg3, VARIANT* varg4, VARIANT* varg5, VARIANT* varg6, VARIANT* varg7, VARIANT* varg8, VARIANT* varg9, VARIANT* varg10, VARIANT* varg11, VARIANT* varg12, VARIANT* varg13, 
			VARIANT* varg14, VARIANT* varg15, VARIANT* varg16, VARIANT* varg17, VARIANT* varg18, VARIANT* varg19, VARIANT* varg20, VARIANT* varg21, VARIANT* varg22, VARIANT* varg23, VARIANT* varg24, VARIANT* varg25, VARIANT* varg26, VARIANT* varg27, 
			VARIANT* varg28, VARIANT* varg29, VARIANT* varg30);
	};
	/////////////////////////////////////////////////////////////////////////////
	// _Global wrapper class

	class _Global : public COleDispatchDriver
	{
	public:
		_Global() {}		// Calls COleDispatchDriver default constructor
		_Global(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		_Global(const _Global& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		CString GetName();
		LPDISPATCH GetDocuments();
		LPDISPATCH GetWindows();
		LPDISPATCH GetActiveDocument();
		LPDISPATCH GetActiveWindow();
		LPDISPATCH GetSelection();
		LPDISPATCH GetWordBasic();
		BOOL GetPrintPreview();
		void SetPrintPreview(BOOL bNewValue);
		LPDISPATCH GetRecentFiles();
		LPDISPATCH GetNormalTemplate();
		LPDISPATCH GetSystem();
		LPDISPATCH GetAutoCorrect();
		LPDISPATCH GetFontNames();
		LPDISPATCH GetLandscapeFontNames();
		LPDISPATCH GetPortraitFontNames();
		LPDISPATCH GetLanguages();
		LPDISPATCH GetAssistant();
		LPDISPATCH GetFileConverters();
		LPDISPATCH GetDialogs();
		LPDISPATCH GetCaptionLabels();
		LPDISPATCH GetAutoCaptions();
		LPDISPATCH GetAddIns();
		LPDISPATCH GetTasks();
		LPDISPATCH GetMacroContainer();
		LPDISPATCH GetCommandBars();
		LPDISPATCH GetSynonymInfo(LPCTSTR Word, VARIANT* LanguageID);
		LPDISPATCH GetVbe();
		LPDISPATCH GetListGalleries();
		CString GetActivePrinter();
		void SetActivePrinter(LPCTSTR lpszNewValue);
		LPDISPATCH GetTemplates();
		LPDISPATCH GetCustomizationContext();
		void SetCustomizationContext(LPDISPATCH newValue);
		LPDISPATCH GetKeyBindings();
		LPDISPATCH GetKeysBoundTo(long KeyCategory, LPCTSTR Command, VARIANT* CommandParameter);
		LPDISPATCH GetFindKey(long KeyCode, VARIANT* KeyCode2);
		LPDISPATCH GetOptions();
		LPDISPATCH GetCustomDictionaries();
		void SetStatusBar(LPCTSTR lpszNewValue);
		BOOL GetShowVisualBasicEditor();
		void SetShowVisualBasicEditor(BOOL bNewValue);
		BOOL GetIsObjectValid(LPDISPATCH Object);
		LPDISPATCH GetHangulHanjaDictionaries();
		BOOL Repeat(VARIANT* Times);
		void DDEExecute(long Channel, LPCTSTR Command);
		long DDEInitiate(LPCTSTR App, LPCTSTR Topic);
		void DDEPoke(long Channel, LPCTSTR Item, LPCTSTR Data);
		CString DDERequest(long Channel, LPCTSTR Item);
		void DDETerminate(long Channel);
		void DDETerminateAll();
		long BuildKeyCode(long Arg1, VARIANT* Arg2, VARIANT* Arg3, VARIANT* Arg4);
		CString KeyString(long KeyCode, VARIANT* KeyCode2);
		BOOL CheckSpelling(LPCTSTR Word, VARIANT* CustomDictionary, VARIANT* IgnoreUppercase, VARIANT* MainDictionary, VARIANT* CustomDictionary2, VARIANT* CustomDictionary3, VARIANT* CustomDictionary4, VARIANT* CustomDictionary5, 
			VARIANT* CustomDictionary6, VARIANT* CustomDictionary7, VARIANT* CustomDictionary8, VARIANT* CustomDictionary9, VARIANT* CustomDictionary10);
		LPDISPATCH GetSpellingSuggestions(LPCTSTR Word, VARIANT* CustomDictionary, VARIANT* IgnoreUppercase, VARIANT* MainDictionary, VARIANT* SuggestionMode, VARIANT* CustomDictionary2, VARIANT* CustomDictionary3, VARIANT* CustomDictionary4, 
			VARIANT* CustomDictionary5, VARIANT* CustomDictionary6, VARIANT* CustomDictionary7, VARIANT* CustomDictionary8, VARIANT* CustomDictionary9, VARIANT* CustomDictionary10);
		void Help(VARIANT* HelpType);
		LPDISPATCH NewWindow();
		CString CleanString(LPCTSTR String);
		void ChangeFileOpenDirectory(LPCTSTR Path);
		float InchesToPoints(float Inches);
		float CentimetersToPoints(float Centimeters);
		float MillimetersToPoints(float Millimeters);
		float PicasToPoints(float Picas);
		float LinesToPoints(float Lines);
		float PointsToInches(float Points);
		float PointsToCentimeters(float Points);
		float PointsToMillimeters(float Points);
		float PointsToPicas(float Points);
		float PointsToLines(float Points);
		float PointsToPixels(float Points, VARIANT* fVertical);
		float PixelsToPoints(float Pixels, VARIANT* fVertical);
		LPDISPATCH GetLanguageSettings();
		LPDISPATCH GetAnswerWizard();
	};
	/////////////////////////////////////////////////////////////////////////////
	// FontNames wrapper class

	class FontNames : public COleDispatchDriver
	{
	public:
		FontNames() {}		// Calls COleDispatchDriver default constructor
		FontNames(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		FontNames(const FontNames& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPUNKNOWN Get_NewEnum();
		long GetCount();
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		CString Item(long Index);
	};
	/////////////////////////////////////////////////////////////////////////////
	// Languages wrapper class

	class Languages : public COleDispatchDriver
	{
	public:
		Languages() {}		// Calls COleDispatchDriver default constructor
		Languages(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		Languages(const Languages& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPUNKNOWN Get_NewEnum();
		long GetCount();
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		LPDISPATCH Item(VARIANT* Index);
	};
	/////////////////////////////////////////////////////////////////////////////
	// Language wrapper class

	class Language : public COleDispatchDriver
	{
	public:
		Language() {}		// Calls COleDispatchDriver default constructor
		Language(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		Language(const Language& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		long GetId();
		CString GetNameLocal();
		CString GetName();
		LPDISPATCH GetActiveGrammarDictionary();
		LPDISPATCH GetActiveHyphenationDictionary();
		LPDISPATCH GetActiveSpellingDictionary();
		LPDISPATCH GetActiveThesaurusDictionary();
		CString GetDefaultWritingStyle();
		void SetDefaultWritingStyle(LPCTSTR lpszNewValue);
		VARIANT GetWritingStyleList();
		long GetSpellingDictionaryType();
		void SetSpellingDictionaryType(long nNewValue);
	};
	/////////////////////////////////////////////////////////////////////////////
	// Documents wrapper class

	class Documents : public COleDispatchDriver
	{
	public:
		Documents() {}		// Calls COleDispatchDriver default constructor
		Documents(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		Documents(const Documents& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPUNKNOWN Get_NewEnum();
		long GetCount();
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		LPDISPATCH Item(VARIANT* Index);
		void Close(VARIANT* SaveChanges, VARIANT* OriginalFormat, VARIANT* RouteDocument);
		void Save(VARIANT* NoPrompt, VARIANT* OriginalFormat);
		LPDISPATCH Add(VARIANT* Template, VARIANT* NewTemplate, VARIANT* DocumentType, VARIANT* Visible);
		LPDISPATCH Open(VARIANT* FileName, VARIANT* ConfirmConversions, VARIANT* ReadOnly, VARIANT* AddToRecentFiles, VARIANT* PasswordDocument, VARIANT* PasswordTemplate, VARIANT* Revert, VARIANT* WritePasswordDocument, 
			VARIANT* WritePasswordTemplate, VARIANT* Format, VARIANT* Encoding, VARIANT* Visible);
	};
	/////////////////////////////////////////////////////////////////////////////
	// _Document wrapper class

	class _Document : public COleDispatchDriver
	{
	public:
		_Document() {}		// Calls COleDispatchDriver default constructor
		_Document(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		_Document(const _Document& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		CString GetName();
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		LPDISPATCH GetBuiltInDocumentProperties();
		LPDISPATCH GetCustomDocumentProperties();
		CString GetPath();
		LPDISPATCH GetBookmarks();
		LPDISPATCH GetTables();
		LPDISPATCH GetFootnotes();
		LPDISPATCH GetEndnotes();
		LPDISPATCH GetComments();
		long GetType();
		BOOL GetAutoHyphenation();
		void SetAutoHyphenation(BOOL bNewValue);
		BOOL GetHyphenateCaps();
		void SetHyphenateCaps(BOOL bNewValue);
		long GetHyphenationZone();
		void SetHyphenationZone(long nNewValue);
		long GetConsecutiveHyphensLimit();
		void SetConsecutiveHyphensLimit(long nNewValue);
		LPDISPATCH GetSections();
		LPDISPATCH GetParagraphs();
		LPDISPATCH GetWords();
		LPDISPATCH GetSentences();
		LPDISPATCH GetCharacters();
		LPDISPATCH GetFields();
		LPDISPATCH GetFormFields();
		LPDISPATCH GetStyles();
		LPDISPATCH GetFrames();
		LPDISPATCH GetTablesOfFigures();
		LPDISPATCH GetVariables();
		LPDISPATCH GetMailMerge();
		LPDISPATCH GetEnvelope();
		CString GetFullName();
		LPDISPATCH GetRevisions();
		LPDISPATCH GetTablesOfContents();
		LPDISPATCH GetTablesOfAuthorities();
		LPDISPATCH GetPageSetup();
		void SetPageSetup(LPDISPATCH newValue);
		LPDISPATCH GetWindows();
		BOOL GetHasRoutingSlip();
		void SetHasRoutingSlip(BOOL bNewValue);
		LPDISPATCH GetRoutingSlip();
		BOOL GetRouted();
		LPDISPATCH GetTablesOfAuthoritiesCategories();
		LPDISPATCH GetIndexes();
		BOOL GetSaved();
		void SetSaved(BOOL bNewValue);
		LPDISPATCH GetContent();
		LPDISPATCH GetActiveWindow();
		long GetKind();
		void SetKind(long nNewValue);
		BOOL GetReadOnly();
		LPDISPATCH GetSubdocuments();
		BOOL GetIsMasterDocument();
		float GetDefaultTabStop();
		void SetDefaultTabStop(float newValue);
		BOOL GetEmbedTrueTypeFonts();
		void SetEmbedTrueTypeFonts(BOOL bNewValue);
		BOOL GetSaveFormsData();
		void SetSaveFormsData(BOOL bNewValue);
		BOOL GetReadOnlyRecommended();
		void SetReadOnlyRecommended(BOOL bNewValue);
		BOOL GetSaveSubsetFonts();
		void SetSaveSubsetFonts(BOOL bNewValue);
		BOOL GetCompatibility(long Type);
		void SetCompatibility(long Type, BOOL bNewValue);
		LPDISPATCH GetStoryRanges();
		LPDISPATCH GetCommandBars();
		BOOL GetIsSubdocument();
		long GetSaveFormat();
		long GetProtectionType();
		LPDISPATCH GetHyperlinks();
		LPDISPATCH GetShapes();
		LPDISPATCH GetListTemplates();
		LPDISPATCH GetLists();
		BOOL GetUpdateStylesOnOpen();
		void SetUpdateStylesOnOpen(BOOL bNewValue);
		VARIANT GetAttachedTemplate();
		void SetAttachedTemplate(VARIANT* newValue);
		LPDISPATCH GetInlineShapes();
		LPDISPATCH GetBackground();
		void SetBackground(LPDISPATCH newValue);
		BOOL GetGrammarChecked();
		void SetGrammarChecked(BOOL bNewValue);
		BOOL GetSpellingChecked();
		void SetSpellingChecked(BOOL bNewValue);
		BOOL GetShowGrammaticalErrors();
		void SetShowGrammaticalErrors(BOOL bNewValue);
		BOOL GetShowSpellingErrors();
		void SetShowSpellingErrors(BOOL bNewValue);
		LPDISPATCH GetVersions();
		BOOL GetShowSummary();
		void SetShowSummary(BOOL bNewValue);
		long GetSummaryViewMode();
		void SetSummaryViewMode(long nNewValue);
		long GetSummaryLength();
		void SetSummaryLength(long nNewValue);
		BOOL GetPrintFractionalWidths();
		void SetPrintFractionalWidths(BOOL bNewValue);
		BOOL GetPrintPostScriptOverText();
		void SetPrintPostScriptOverText(BOOL bNewValue);
		LPDISPATCH GetContainer();
		BOOL GetPrintFormsData();
		void SetPrintFormsData(BOOL bNewValue);
		LPDISPATCH GetListParagraphs();
		void SetPassword(LPCTSTR lpszNewValue);
		void SetWritePassword(LPCTSTR lpszNewValue);
		BOOL GetHasPassword();
		BOOL GetWriteReserved();
		CString GetActiveWritingStyle(VARIANT* LanguageID);
		void SetActiveWritingStyle(VARIANT* LanguageID, LPCTSTR lpszNewValue);
		BOOL GetUserControl();
		void SetUserControl(BOOL bNewValue);
		BOOL GetHasMailer();
		void SetHasMailer(BOOL bNewValue);
		LPDISPATCH GetMailer();
		LPDISPATCH GetReadabilityStatistics();
		LPDISPATCH GetGrammaticalErrors();
		LPDISPATCH GetSpellingErrors();
		LPDISPATCH GetVBProject();
		BOOL GetFormsDesign();
		CString Get_CodeName();
		void Set_CodeName(LPCTSTR lpszNewValue);
		CString GetCodeName();
		BOOL GetSnapToGrid();
		void SetSnapToGrid(BOOL bNewValue);
		BOOL GetSnapToShapes();
		void SetSnapToShapes(BOOL bNewValue);
		float GetGridDistanceHorizontal();
		void SetGridDistanceHorizontal(float newValue);
		float GetGridDistanceVertical();
		void SetGridDistanceVertical(float newValue);
		float GetGridOriginHorizontal();
		void SetGridOriginHorizontal(float newValue);
		float GetGridOriginVertical();
		void SetGridOriginVertical(float newValue);
		long GetGridSpaceBetweenHorizontalLines();
		void SetGridSpaceBetweenHorizontalLines(long nNewValue);
		long GetGridSpaceBetweenVerticalLines();
		void SetGridSpaceBetweenVerticalLines(long nNewValue);
		BOOL GetGridOriginFromMargin();
		void SetGridOriginFromMargin(BOOL bNewValue);
		BOOL GetKerningByAlgorithm();
		void SetKerningByAlgorithm(BOOL bNewValue);
		long GetJustificationMode();
		void SetJustificationMode(long nNewValue);
		long GetFarEastLineBreakLevel();
		void SetFarEastLineBreakLevel(long nNewValue);
		CString GetNoLineBreakBefore();
		void SetNoLineBreakBefore(LPCTSTR lpszNewValue);
		CString GetNoLineBreakAfter();
		void SetNoLineBreakAfter(LPCTSTR lpszNewValue);
		BOOL GetTrackRevisions();
		void SetTrackRevisions(BOOL bNewValue);
		BOOL GetPrintRevisions();
		void SetPrintRevisions(BOOL bNewValue);
		BOOL GetShowRevisions();
		void SetShowRevisions(BOOL bNewValue);
		void Close(VARIANT* SaveChanges, VARIANT* OriginalFormat, VARIANT* RouteDocument);
		void SaveAs(VARIANT* FileName, VARIANT* FileFormat, VARIANT* LockComments, VARIANT* Password, VARIANT* AddToRecentFiles, VARIANT* WritePassword, VARIANT* ReadOnlyRecommended, VARIANT* EmbedTrueTypeFonts, VARIANT* SaveNativePictureFormat, 
			VARIANT* SaveFormsData, VARIANT* SaveAsAOCELetter);
		void Repaginate();
		void FitToPages();
		void ManualHyphenation();
		void Select();
		void DataForm();
		void Route();
		void Save();
		void SendMail();
		LPDISPATCH Range(VARIANT* Start, VARIANT* End);
		void RunAutoMacro(long Which);
		void Activate();
		void PrintPreview();
		LPDISPATCH GoTo(VARIANT* What, VARIANT* Which, VARIANT* Count, VARIANT* Name);
		BOOL Undo(VARIANT* Times);
		BOOL Redo(VARIANT* Times);
		long ComputeStatistics(long Statistic, VARIANT* IncludeFootnotesAndEndnotes);
		void MakeCompatibilityDefault();
		void Protect(long Type, VARIANT* NoReset, VARIANT* Password);
		void Unprotect(VARIANT* Password);
		void EditionOptions(long Type, long Option, LPCTSTR Name, VARIANT* Format);
		void RunLetterWizard(VARIANT* LetterContent, VARIANT* WizardMode);
		LPDISPATCH GetLetterContent();
		void SetLetterContent(VARIANT* LetterContent);
		void CopyStylesFromTemplate(LPCTSTR Template);
		void UpdateStyles();
		void CheckGrammar();
		void CheckSpelling(VARIANT* CustomDictionary, VARIANT* IgnoreUppercase, VARIANT* AlwaysSuggest, VARIANT* CustomDictionary2, VARIANT* CustomDictionary3, VARIANT* CustomDictionary4, VARIANT* CustomDictionary5, VARIANT* CustomDictionary6, 
			VARIANT* CustomDictionary7, VARIANT* CustomDictionary8, VARIANT* CustomDictionary9, VARIANT* CustomDictionary10);
		void FollowHyperlink(VARIANT* Address, VARIANT* SubAddress, VARIANT* NewWindow, VARIANT* AddHistory, VARIANT* ExtraInfo, VARIANT* Method, VARIANT* HeaderInfo);
		void AddToFavorites();
		void Reload();
		LPDISPATCH AutoSummarize(VARIANT* Length, VARIANT* Mode, VARIANT* UpdateProperties);
		void RemoveNumbers(VARIANT* NumberType);
		void ConvertNumbersToText(VARIANT* NumberType);
		long CountNumberedItems(VARIANT* NumberType, VARIANT* Level);
		void Post();
		void ToggleFormsDesign();
		void Compare(LPCTSTR Name);
		void UpdateSummaryProperties();
		VARIANT GetCrossReferenceItems(VARIANT* ReferenceType);
		void AutoFormat();
		void ViewCode();
		void ViewPropertyBrowser();
		void ForwardMailer();
		void Reply();
		void ReplyAll();
		void SendMailer(VARIANT* FileFormat, VARIANT* Priority);
		void UndoClear();
		void PresentIt();
		void SendFax(LPCTSTR Address, VARIANT* Subject);
		void Merge(LPCTSTR FileName);
		void ClosePrintPreview();
		void CheckConsistency();
		LPDISPATCH CreateLetterContent(LPCTSTR DateFormat, BOOL IncludeHeaderFooter, LPCTSTR PageDesign, long LetterStyle, BOOL Letterhead, long LetterheadLocation, float LetterheadSize, LPCTSTR RecipientName, LPCTSTR RecipientAddress, 
			LPCTSTR Salutation, long SalutationType, LPCTSTR RecipientReference, LPCTSTR MailingInstructions, LPCTSTR AttentionLine, LPCTSTR Subject, LPCTSTR CCList, LPCTSTR ReturnAddress, LPCTSTR SenderName, LPCTSTR Closing, LPCTSTR SenderCompany, 
			LPCTSTR SenderJobTitle, LPCTSTR SenderInitials, long EnclosureNumber, VARIANT* InfoBlock, VARIANT* RecipientCode, VARIANT* RecipientGender, VARIANT* ReturnAddressShortForm, VARIANT* SenderCity, VARIANT* SenderCode, VARIANT* SenderGender, 
			VARIANT* SenderReference);
		void AcceptAllRevisions();
		void RejectAllRevisions();
		void DetectLanguage();
		void ApplyTheme(LPCTSTR Name);
		void RemoveTheme();
		void WebPagePreview();
		void ReloadAs(long Encoding);
		CString GetActiveTheme();
		CString GetActiveThemeDisplayName();
		LPDISPATCH GetEmail();
		LPDISPATCH GetScripts();
		BOOL GetLanguageDetected();
		void SetLanguageDetected(BOOL bNewValue);
		long GetFarEastLineBreakLanguage();
		void SetFarEastLineBreakLanguage(long nNewValue);
		LPDISPATCH GetFrameset();
		VARIANT GetClickAndTypeParagraphStyle();
		void SetClickAndTypeParagraphStyle(VARIANT* newValue);
		LPDISPATCH GetHTMLProject();
		LPDISPATCH GetWebOptions();
		long GetOpenEncoding();
		long GetSaveEncoding();
		void SetSaveEncoding(long nNewValue);
		BOOL GetOptimizeForWord97();
		void SetOptimizeForWord97(BOOL bNewValue);
		BOOL GetVBASigned();
		void PrintOut(VARIANT* Background, VARIANT* Append, VARIANT* Range, VARIANT* OutputFileName, VARIANT* From, VARIANT* To, VARIANT* Item, VARIANT* Copies, VARIANT* Pages, VARIANT* PageType, VARIANT* PrintToFile, VARIANT* Collate, 
			VARIANT* ActivePrinterMacGX, VARIANT* ManualDuplexPrint, VARIANT* PrintZoomColumn, VARIANT* PrintZoomRow, VARIANT* PrintZoomPaperWidth, VARIANT* PrintZoomPaperHeight);
	};
	/////////////////////////////////////////////////////////////////////////////
	// Template wrapper class

	class Template : public COleDispatchDriver
	{
	public:
		Template() {}		// Calls COleDispatchDriver default constructor
		Template(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		Template(const Template& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		CString GetName();
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		CString GetPath();
		LPDISPATCH GetAutoTextEntries();
		long GetLanguageID();
		void SetLanguageID(long nNewValue);
		BOOL GetSaved();
		void SetSaved(BOOL bNewValue);
		long GetType();
		CString GetFullName();
		LPDISPATCH GetBuiltInDocumentProperties();
		LPDISPATCH GetCustomDocumentProperties();
		LPDISPATCH GetListTemplates();
		long GetLanguageIDFarEast();
		void SetLanguageIDFarEast(long nNewValue);
		LPDISPATCH GetVBProject();
		BOOL GetKerningByAlgorithm();
		void SetKerningByAlgorithm(BOOL bNewValue);
		long GetJustificationMode();
		void SetJustificationMode(long nNewValue);
		long GetFarEastLineBreakLevel();
		void SetFarEastLineBreakLevel(long nNewValue);
		CString GetNoLineBreakBefore();
		void SetNoLineBreakBefore(LPCTSTR lpszNewValue);
		CString GetNoLineBreakAfter();
		void SetNoLineBreakAfter(LPCTSTR lpszNewValue);
		LPDISPATCH OpenAsDocument();
		void Save();
		long GetNoProofing();
		void SetNoProofing(long nNewValue);
		long GetFarEastLineBreakLanguage();
		void SetFarEastLineBreakLanguage(long nNewValue);
	};
	/////////////////////////////////////////////////////////////////////////////
	// Templates wrapper class

	class Templates : public COleDispatchDriver
	{
	public:
		Templates() {}		// Calls COleDispatchDriver default constructor
		Templates(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		Templates(const Templates& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		long GetCount();
		LPUNKNOWN Get_NewEnum();
		LPDISPATCH Item(VARIANT* Index);
	};
	/////////////////////////////////////////////////////////////////////////////
	// RoutingSlip wrapper class

	class RoutingSlip : public COleDispatchDriver
	{
	public:
		RoutingSlip() {}		// Calls COleDispatchDriver default constructor
		RoutingSlip(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		RoutingSlip(const RoutingSlip& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		CString GetSubject();
		void SetSubject(LPCTSTR lpszNewValue);
		CString GetMessage();
		void SetMessage(LPCTSTR lpszNewValue);
		long GetDelivery();
		void SetDelivery(long nNewValue);
		BOOL GetTrackStatus();
		void SetTrackStatus(BOOL bNewValue);
		long GetProtect();
		void SetProtect(long nNewValue);
		BOOL GetReturnWhenDone();
		void SetReturnWhenDone(BOOL bNewValue);
		long GetStatus();
		VARIANT GetRecipients(VARIANT* Index);
		void Reset();
		void AddRecipient(LPCTSTR Recipient);
	};
	/////////////////////////////////////////////////////////////////////////////
	// Bookmark wrapper class

	class Bookmark : public COleDispatchDriver
	{
	public:
		Bookmark() {}		// Calls COleDispatchDriver default constructor
		Bookmark(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		Bookmark(const Bookmark& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		CString GetName();
		LPDISPATCH GetRange();
		BOOL GetEmpty();
		long GetStart();
		void SetStart(long nNewValue);
		long GetEnd();
		void SetEnd(long nNewValue);
		BOOL GetColumn();
		long GetStoryType();
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		void Select();
		void Delete();
		LPDISPATCH Copy(LPCTSTR Name);
	};
	/////////////////////////////////////////////////////////////////////////////
	// Bookmarks wrapper class

	class Bookmarks : public COleDispatchDriver
	{
	public:
		Bookmarks() {}		// Calls COleDispatchDriver default constructor
		Bookmarks(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		Bookmarks(const Bookmarks& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPUNKNOWN Get_NewEnum();
		long GetCount();
		long GetDefaultSorting();
		void SetDefaultSorting(long nNewValue);
		BOOL GetShowHidden();
		void SetShowHidden(BOOL bNewValue);
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		LPDISPATCH Item(VARIANT* Index);
		LPDISPATCH Add(LPCTSTR Name, VARIANT* Range);
		BOOL Exists(LPCTSTR Name);
	};
	/////////////////////////////////////////////////////////////////////////////
	// Variable wrapper class

	class Variable : public COleDispatchDriver
	{
	public:
		Variable() {}		// Calls COleDispatchDriver default constructor
		Variable(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		Variable(const Variable& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		CString GetName();
		CString GetValue();
		void SetValue(LPCTSTR lpszNewValue);
		long GetIndex();
		void Delete();
	};
	/////////////////////////////////////////////////////////////////////////////
	// Variables wrapper class

	class Variables : public COleDispatchDriver
	{
	public:
		Variables() {}		// Calls COleDispatchDriver default constructor
		Variables(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		Variables(const Variables& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPUNKNOWN Get_NewEnum();
		long GetCount();
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		LPDISPATCH Item(VARIANT* Index);
		LPDISPATCH Add(LPCTSTR Name, VARIANT* Value);
	};
	/////////////////////////////////////////////////////////////////////////////
	// RecentFile wrapper class

	class RecentFile : public COleDispatchDriver
	{
	public:
		RecentFile() {}		// Calls COleDispatchDriver default constructor
		RecentFile(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		RecentFile(const RecentFile& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		CString GetName();
		long GetIndex();
		BOOL GetReadOnly();
		void SetReadOnly(BOOL bNewValue);
		CString GetPath();
		LPDISPATCH Open();
		void Delete();
	};
	/////////////////////////////////////////////////////////////////////////////
	// RecentFiles wrapper class

	class RecentFiles : public COleDispatchDriver
	{
	public:
		RecentFiles() {}		// Calls COleDispatchDriver default constructor
		RecentFiles(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		RecentFiles(const RecentFiles& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		LPUNKNOWN Get_NewEnum();
		long GetCount();
		long GetMaximum();
		void SetMaximum(long nNewValue);
		LPDISPATCH Item(long Index);
		LPDISPATCH Add(VARIANT* Document, VARIANT* ReadOnly);
	};
	/////////////////////////////////////////////////////////////////////////////
	// Window wrapper class

	class Window : public COleDispatchDriver
	{
	public:
		Window() {}		// Calls COleDispatchDriver default constructor
		Window(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		Window(const Window& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		LPDISPATCH GetActivePane();
		LPDISPATCH GetDocument();
		LPDISPATCH GetPanes();
		LPDISPATCH GetSelection();
		long GetLeft();
		void SetLeft(long nNewValue);
		long GetTop();
		void SetTop(long nNewValue);
		long GetWidth();
		void SetWidth(long nNewValue);
		long GetHeight();
		void SetHeight(long nNewValue);
		BOOL GetSplit();
		void SetSplit(BOOL bNewValue);
		long GetSplitVertical();
		void SetSplitVertical(long nNewValue);
		CString GetCaption();
		void SetCaption(LPCTSTR lpszNewValue);
		long GetWindowState();
		void SetWindowState(long nNewValue);
		BOOL GetDisplayRulers();
		void SetDisplayRulers(BOOL bNewValue);
		BOOL GetDisplayVerticalRuler();
		void SetDisplayVerticalRuler(BOOL bNewValue);
		LPDISPATCH GetView();
		long GetType();
		LPDISPATCH GetNext();
		LPDISPATCH GetPrevious();
		long GetWindowNumber();
		BOOL GetDisplayVerticalScrollBar();
		void SetDisplayVerticalScrollBar(BOOL bNewValue);
		BOOL GetDisplayHorizontalScrollBar();
		void SetDisplayHorizontalScrollBar(BOOL bNewValue);
		float GetStyleAreaWidth();
		void SetStyleAreaWidth(float newValue);
		BOOL GetDisplayScreenTips();
		void SetDisplayScreenTips(BOOL bNewValue);
		long GetHorizontalPercentScrolled();
		void SetHorizontalPercentScrolled(long nNewValue);
		long GetVerticalPercentScrolled();
		void SetVerticalPercentScrolled(long nNewValue);
		BOOL GetDocumentMap();
		void SetDocumentMap(BOOL bNewValue);
		BOOL GetActive();
		long GetDocumentMapPercentWidth();
		void SetDocumentMapPercentWidth(long nNewValue);
		long GetIndex();
		long GetIMEMode();
		void SetIMEMode(long nNewValue);
		void Activate();
		void Close(VARIANT* SaveChanges, VARIANT* RouteDocument);
		void LargeScroll(VARIANT* Down, VARIANT* Up, VARIANT* ToRight, VARIANT* ToLeft);
		void SmallScroll(VARIANT* Down, VARIANT* Up, VARIANT* ToRight, VARIANT* ToLeft);
		LPDISPATCH NewWindow();
		void PageScroll(VARIANT* Down, VARIANT* Up);
		void SetFocus();
		LPDISPATCH RangeFromPoint(long x, long y);
		void ScrollIntoView(LPDISPATCH obj, VARIANT* Start);
		void GetPoint(long* ScreenPixelsLeft, long* ScreenPixelsTop, long* ScreenPixelsWidth, long* ScreenPixelsHeight, LPDISPATCH obj);
		void PrintOut(VARIANT* Background, VARIANT* Append, VARIANT* Range, VARIANT* OutputFileName, VARIANT* From, VARIANT* To, VARIANT* Item, VARIANT* Copies, VARIANT* Pages, VARIANT* PageType, VARIANT* PrintToFile, VARIANT* Collate, 
			VARIANT* ActivePrinterMacGX, VARIANT* ManualDuplexPrint, VARIANT* PrintZoomColumn, VARIANT* PrintZoomRow, VARIANT* PrintZoomPaperWidth, VARIANT* PrintZoomPaperHeight);
		long GetUsableWidth();
		long GetUsableHeight();
		BOOL GetEnvelopeVisible();
		void SetEnvelopeVisible(BOOL bNewValue);
		BOOL GetDisplayRightRuler();
		void SetDisplayRightRuler(BOOL bNewValue);
		BOOL GetDisplayLeftScrollBar();
		void SetDisplayLeftScrollBar(BOOL bNewValue);
		BOOL GetVisible();
		void SetVisible(BOOL bNewValue);
	};
	/////////////////////////////////////////////////////////////////////////////
	// Windows wrapper class

	class Windows : public COleDispatchDriver
	{
	public:
		Windows() {}		// Calls COleDispatchDriver default constructor
		Windows(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		Windows(const Windows& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPUNKNOWN Get_NewEnum();
		long GetCount();
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		LPDISPATCH Item(VARIANT* Index);
		LPDISPATCH Add(VARIANT* Window);
		void Arrange(VARIANT* ArrangeStyle);
	};
	/////////////////////////////////////////////////////////////////////////////
	// Pane wrapper class

	class Pane : public COleDispatchDriver
	{
	public:
		Pane() {}		// Calls COleDispatchDriver default constructor
		Pane(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		Pane(const Pane& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		LPDISPATCH GetDocument();
		LPDISPATCH GetSelection();
		BOOL GetDisplayRulers();
		void SetDisplayRulers(BOOL bNewValue);
		BOOL GetDisplayVerticalRuler();
		void SetDisplayVerticalRuler(BOOL bNewValue);
		LPDISPATCH GetZooms();
		long GetIndex();
		LPDISPATCH GetView();
		LPDISPATCH GetNext();
		LPDISPATCH GetPrevious();
		long GetHorizontalPercentScrolled();
		void SetHorizontalPercentScrolled(long nNewValue);
		long GetVerticalPercentScrolled();
		void SetVerticalPercentScrolled(long nNewValue);
		long GetMinimumFontSize();
		void SetMinimumFontSize(long nNewValue);
		long GetBrowseWidth();
		void Activate();
		void Close();
		void LargeScroll(VARIANT* Down, VARIANT* Up, VARIANT* ToRight, VARIANT* ToLeft);
		void SmallScroll(VARIANT* Down, VARIANT* Up, VARIANT* ToRight, VARIANT* ToLeft);
		void AutoScroll(long Velocity);
		void PageScroll(VARIANT* Down, VARIANT* Up);
		void NewFrameset();
		void TOCInFrameset();
		LPDISPATCH GetFrameset();
	};
	/////////////////////////////////////////////////////////////////////////////
	// Panes wrapper class

	class Panes : public COleDispatchDriver
	{
	public:
		Panes() {}		// Calls COleDispatchDriver default constructor
		Panes(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		Panes(const Panes& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPUNKNOWN Get_NewEnum();
		long GetCount();
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		LPDISPATCH Item(long Index);
		LPDISPATCH Add(VARIANT* SplitVertical);
	};
	/////////////////////////////////////////////////////////////////////////////
	// Range wrapper class

	class Range : public COleDispatchDriver
	{
	public:
		Range() {}		// Calls COleDispatchDriver default constructor
		Range(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		Range(const Range& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		CString GetText();
		void SetText(LPCTSTR lpszNewValue);
		LPDISPATCH GetFormattedText();
		void SetFormattedText(LPDISPATCH newValue);
		long GetStart();
		void SetStart(long nNewValue);
		long GetEnd();
		void SetEnd(long nNewValue);
		LPDISPATCH GetFont();
		void SetFont(LPDISPATCH newValue);
		LPDISPATCH GetDuplicate();
		long GetStoryType();
		LPDISPATCH GetTables();
		LPDISPATCH GetWords();
		LPDISPATCH GetSentences();
		LPDISPATCH GetCharacters();
		LPDISPATCH GetFootnotes();
		LPDISPATCH GetEndnotes();
		LPDISPATCH GetComments();
		LPDISPATCH GetCells();
		LPDISPATCH GetSections();
		LPDISPATCH GetParagraphs();
		LPDISPATCH GetBorders();
		void SetBorders(LPDISPATCH newValue);
		LPDISPATCH GetShading();
		LPDISPATCH GetTextRetrievalMode();
		void SetTextRetrievalMode(LPDISPATCH newValue);
		LPDISPATCH GetFields();
		LPDISPATCH GetFormFields();
		LPDISPATCH GetFrames();
		LPDISPATCH GetParagraphFormat();
		void SetParagraphFormat(LPDISPATCH newValue);
		LPDISPATCH GetListFormat();
		LPDISPATCH GetBookmarks();
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		long GetBold();
		void SetBold(long nNewValue);
		long GetItalic();
		void SetItalic(long nNewValue);
		long GetUnderline();
		void SetUnderline(long nNewValue);
		long GetEmphasisMark();
		void SetEmphasisMark(long nNewValue);
		BOOL GetDisableCharacterSpaceGrid();
		void SetDisableCharacterSpaceGrid(BOOL bNewValue);
		LPDISPATCH GetRevisions();
		VARIANT GetStyle();
		void SetStyle(VARIANT* newValue);
		long GetStoryLength();
		long GetLanguageID();
		void SetLanguageID(long nNewValue);
		LPDISPATCH GetSynonymInfo();
		LPDISPATCH GetHyperlinks();
		LPDISPATCH GetListParagraphs();
		LPDISPATCH GetSubdocuments();
		BOOL GetGrammarChecked();
		void SetGrammarChecked(BOOL bNewValue);
		BOOL GetSpellingChecked();
		void SetSpellingChecked(BOOL bNewValue);
		long GetHighlightColorIndex();
		void SetHighlightColorIndex(long nNewValue);
		LPDISPATCH GetColumns();
		LPDISPATCH GetRows();
		BOOL GetIsEndOfRowMark();
		long GetBookmarkID();
		long GetPreviousBookmarkID();
		LPDISPATCH GetFind();
		LPDISPATCH GetPageSetup();
		void SetPageSetup(LPDISPATCH newValue);
		LPDISPATCH GetShapeRange();
		long GetCase();
		void SetCase(long nNewValue);
		VARIANT GetInformation(long Type);
		LPDISPATCH GetReadabilityStatistics();
		LPDISPATCH GetGrammaticalErrors();
		LPDISPATCH GetSpellingErrors();
		long GetOrientation();
		void SetOrientation(long nNewValue);
		LPDISPATCH GetInlineShapes();
		LPDISPATCH GetNextStoryRange();
		long GetLanguageIDFarEast();
		void SetLanguageIDFarEast(long nNewValue);
		long GetLanguageIDOther();
		void SetLanguageIDOther(long nNewValue);
		void Select();
		void SetRange(long Start, long End);
		void Collapse(VARIANT* Direction);
		void InsertBefore(LPCTSTR Text);
		void InsertAfter(LPCTSTR Text);
		LPDISPATCH Next(VARIANT* Unit, VARIANT* Count);
		LPDISPATCH Previous(VARIANT* Unit, VARIANT* Count);
		long StartOf(VARIANT* Unit, VARIANT* Extend);
		long EndOf(VARIANT* Unit, VARIANT* Extend);
		long Move(VARIANT* Unit, VARIANT* Count);
		long MoveStart(VARIANT* Unit, VARIANT* Count);
		long MoveEnd(VARIANT* Unit, VARIANT* Count);
		long MoveWhile(VARIANT* Cset, VARIANT* Count);
		long MoveStartWhile(VARIANT* Cset, VARIANT* Count);
		long MoveEndWhile(VARIANT* Cset, VARIANT* Count);
		long MoveUntil(VARIANT* Cset, VARIANT* Count);
		long MoveStartUntil(VARIANT* Cset, VARIANT* Count);
		long MoveEndUntil(VARIANT* Cset, VARIANT* Count);
		void Cut();
		void Copy();
		void Paste();
		void InsertBreak(VARIANT* Type);
		void InsertFile(LPCTSTR FileName, VARIANT* Range, VARIANT* ConfirmConversions, VARIANT* Link, VARIANT* Attachment);
		BOOL InStory(LPDISPATCH Range);
		BOOL InRange(LPDISPATCH Range);
		long Delete(VARIANT* Unit, VARIANT* Count);
		void WholeStory();
		long Expand(VARIANT* Unit);
		void InsertParagraph();
		void InsertParagraphAfter();
		void InsertSymbol(long CharacterNumber, VARIANT* Font, VARIANT* Unicode, VARIANT* Bias);
		void InsertCrossReference(VARIANT* ReferenceType, long ReferenceKind, VARIANT* ReferenceItem, VARIANT* InsertAsHyperlink, VARIANT* IncludePosition);
		void InsertCaption(VARIANT* Label, VARIANT* Title, VARIANT* TitleAutoText, VARIANT* Position);
		void CopyAsPicture();
		void SortAscending();
		void SortDescending();
		BOOL IsEqual(LPDISPATCH Range);
		float Calculate();
		LPDISPATCH GoTo(VARIANT* What, VARIANT* Which, VARIANT* Count, VARIANT* Name);
		LPDISPATCH GoToNext(long What);
		LPDISPATCH GoToPrevious(long What);
		void PasteSpecial(VARIANT* IconIndex, VARIANT* Link, VARIANT* Placement, VARIANT* DisplayAsIcon, VARIANT* DataType, VARIANT* IconFileName, VARIANT* IconLabel);
		void LookupNameProperties();
		long ComputeStatistics(long Statistic);
		void Relocate(long Direction);
		void CheckSynonyms();
		void SubscribeTo(LPCTSTR Edition, VARIANT* Format);
		void CreatePublisher(VARIANT* Edition, VARIANT* ContainsPICT, VARIANT* ContainsRTF, VARIANT* ContainsText);
		void InsertAutoText();
		void InsertDatabase(VARIANT* Format, VARIANT* Style, VARIANT* LinkToSource, VARIANT* Connection, VARIANT* SQLStatement, VARIANT* SQLStatement1, VARIANT* PasswordDocument, VARIANT* PasswordTemplate, VARIANT* WritePasswordDocument, 
			VARIANT* WritePasswordTemplate, VARIANT* DataSource, VARIANT* From, VARIANT* To, VARIANT* IncludeFields);
		void AutoFormat();
		void CheckGrammar();
		void CheckSpelling(VARIANT* CustomDictionary, VARIANT* IgnoreUppercase, VARIANT* AlwaysSuggest, VARIANT* CustomDictionary2, VARIANT* CustomDictionary3, VARIANT* CustomDictionary4, VARIANT* CustomDictionary5, VARIANT* CustomDictionary6, 
			VARIANT* CustomDictionary7, VARIANT* CustomDictionary8, VARIANT* CustomDictionary9, VARIANT* CustomDictionary10);
		LPDISPATCH GetSpellingSuggestions(VARIANT* CustomDictionary, VARIANT* IgnoreUppercase, VARIANT* MainDictionary, VARIANT* SuggestionMode, VARIANT* CustomDictionary2, VARIANT* CustomDictionary3, VARIANT* CustomDictionary4, 
			VARIANT* CustomDictionary5, VARIANT* CustomDictionary6, VARIANT* CustomDictionary7, VARIANT* CustomDictionary8, VARIANT* CustomDictionary9, VARIANT* CustomDictionary10);
		void InsertParagraphBefore();
		void NextSubdocument();
		void PreviousSubdocument();
		void ConvertHangulAndHanja(VARIANT* ConversionsMode, VARIANT* FastConversion, VARIANT* CheckHangulEnding, VARIANT* EnableRecentOrdering, VARIANT* CustomDictionary);
		void PasteAsNestedTable();
		void ModifyEnclosure(VARIANT* Style, VARIANT* Symbol, VARIANT* EnclosedText);
		void PhoneticGuide(LPCTSTR Text, long Alignment, long Raise, long FontSize, LPCTSTR FontName);
		void InsertDateTime(VARIANT* DateTimeFormat, VARIANT* InsertAsField, VARIANT* InsertAsFullWidth, VARIANT* DateLanguage, VARIANT* CalendarType);
		void Sort(VARIANT* ExcludeHeader, VARIANT* FieldNumber, VARIANT* SortFieldType, VARIANT* SortOrder, VARIANT* FieldNumber2, VARIANT* SortFieldType2, VARIANT* SortOrder2, VARIANT* FieldNumber3, VARIANT* SortFieldType3, VARIANT* SortOrder3, 
			VARIANT* SortColumn, VARIANT* Separator, VARIANT* CaseSensitive, VARIANT* BidiSort, VARIANT* IgnoreThe, VARIANT* IgnoreKashida, VARIANT* IgnoreDiacritics, VARIANT* IgnoreHe, VARIANT* LanguageID);
		void DetectLanguage();
		LPDISPATCH ConvertToTable(VARIANT* Separator, VARIANT* NumRows, VARIANT* NumColumns, VARIANT* InitialColumnWidth, VARIANT* Format, VARIANT* ApplyBorders, VARIANT* ApplyShading, VARIANT* ApplyFont, VARIANT* ApplyColor, 
			VARIANT* ApplyHeadingRows, VARIANT* ApplyLastRow, VARIANT* ApplyFirstColumn, VARIANT* ApplyLastColumn, VARIANT* AutoFit, VARIANT* AutoFitBehavior, VARIANT* DefaultTableBehavior);
		void TCSCConverter(long WdTCSCConverterDirection, BOOL CommonTerms, BOOL UseVariants);
		BOOL GetLanguageDetected();
		void SetLanguageDetected(BOOL bNewValue);
		float GetFitTextWidth();
		void SetFitTextWidth(float newValue);
		long GetHorizontalInVertical();
		void SetHorizontalInVertical(long nNewValue);
		long GetTwoLinesInOne();
		void SetTwoLinesInOne(long nNewValue);
		BOOL GetCombineCharacters();
		void SetCombineCharacters(BOOL bNewValue);
		long GetNoProofing();
		void SetNoProofing(long nNewValue);
		LPDISPATCH GetTopLevelTables();
		LPDISPATCH GetScripts();
		long GetCharacterWidth();
		void SetCharacterWidth(long nNewValue);
		long GetKana();
		void SetKana(long nNewValue);
		long GetBoldBi();
		void SetBoldBi(long nNewValue);
		long GetItalicBi();
		void SetItalicBi(long nNewValue);
		CString GetId();
		void SetId(LPCTSTR lpszNewValue);
	};
	/////////////////////////////////////////////////////////////////////////////
	// ListFormat wrapper class

	class ListFormat : public COleDispatchDriver
	{
	public:
		ListFormat() {}		// Calls COleDispatchDriver default constructor
		ListFormat(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		ListFormat(const ListFormat& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		long GetListLevelNumber();
		void SetListLevelNumber(long nNewValue);
		LPDISPATCH GetList();
		LPDISPATCH GetListTemplate();
		long GetListValue();
		BOOL GetSingleList();
		BOOL GetSingleListTemplate();
		long GetListType();
		CString GetListString();
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		long CanContinuePreviousList(LPDISPATCH ListTemplate);
		void RemoveNumbers(VARIANT* NumberType);
		void ConvertNumbersToText(VARIANT* NumberType);
		long CountNumberedItems(VARIANT* NumberType, VARIANT* Level);
		void ListOutdent();
		void ListIndent();
		void ApplyBulletDefault(VARIANT* DefaultListBehavior);
		void ApplyNumberDefault(VARIANT* DefaultListBehavior);
		void ApplyOutlineNumberDefault(VARIANT* DefaultListBehavior);
		void ApplyListTemplate(LPDISPATCH ListTemplate, VARIANT* ContinuePreviousList, VARIANT* ApplyTo, VARIANT* DefaultListBehavior);
	};
	/////////////////////////////////////////////////////////////////////////////
	// Find wrapper class

	class Find : public COleDispatchDriver
	{
	public:
		Find() {}		// Calls COleDispatchDriver default constructor
		Find(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		Find(const Find& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		BOOL GetForward();
		void SetForward(BOOL bNewValue);
		LPDISPATCH GetFont();
		void SetFont(LPDISPATCH newValue);
		BOOL GetFound();
		BOOL GetMatchAllWordForms();
		void SetMatchAllWordForms(BOOL bNewValue);
		BOOL GetMatchCase();
		void SetMatchCase(BOOL bNewValue);
		BOOL GetMatchWildcards();
		void SetMatchWildcards(BOOL bNewValue);
		BOOL GetMatchSoundsLike();
		void SetMatchSoundsLike(BOOL bNewValue);
		BOOL GetMatchWholeWord();
		void SetMatchWholeWord(BOOL bNewValue);
		BOOL GetMatchFuzzy();
		void SetMatchFuzzy(BOOL bNewValue);
		BOOL GetMatchByte();
		void SetMatchByte(BOOL bNewValue);
		LPDISPATCH GetParagraphFormat();
		void SetParagraphFormat(LPDISPATCH newValue);
		VARIANT GetStyle();
		void SetStyle(VARIANT* newValue);
		CString GetText();
		void SetText(LPCTSTR lpszNewValue);
		long GetLanguageID();
		void SetLanguageID(long nNewValue);
		long GetHighlight();
		void SetHighlight(long nNewValue);
		LPDISPATCH GetReplacement();
		LPDISPATCH GetFrame();
		long GetWrap();
		void SetWrap(long nNewValue);
		BOOL GetFormat();
		void SetFormat(BOOL bNewValue);
		long GetLanguageIDFarEast();
		void SetLanguageIDFarEast(long nNewValue);
		long GetLanguageIDOther();
		void SetLanguageIDOther(long nNewValue);
		BOOL GetCorrectHangulEndings();
		void SetCorrectHangulEndings(BOOL bNewValue);
		void ClearFormatting();
		void SetAllFuzzyOptions();
		void ClearAllFuzzyOptions();
		BOOL Execute(VARIANT* FindText, VARIANT* MatchCase, VARIANT* MatchWholeWord, VARIANT* MatchWildcards, VARIANT* MatchSoundsLike, VARIANT* MatchAllWordForms, VARIANT* Forward, VARIANT* Wrap, VARIANT* Format, VARIANT* ReplaceWith, 
			VARIANT* Replace, VARIANT* MatchKashida, VARIANT* MatchDiacritics, VARIANT* MatchAlefHamza, VARIANT* MatchControl);
		long GetNoProofing();
		void SetNoProofing(long nNewValue);
		BOOL GetMatchKashida();
		void SetMatchKashida(BOOL bNewValue);
		BOOL GetMatchDiacritics();
		void SetMatchDiacritics(BOOL bNewValue);
		BOOL GetMatchAlefHamza();
		void SetMatchAlefHamza(BOOL bNewValue);
		BOOL GetMatchControl();
		void SetMatchControl(BOOL bNewValue);
	};
	/////////////////////////////////////////////////////////////////////////////
	// Replacement wrapper class

	class Replacement : public COleDispatchDriver
	{
	public:
		Replacement() {}		// Calls COleDispatchDriver default constructor
		Replacement(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		Replacement(const Replacement& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		LPDISPATCH GetFont();
		void SetFont(LPDISPATCH newValue);
		LPDISPATCH GetParagraphFormat();
		void SetParagraphFormat(LPDISPATCH newValue);
		VARIANT GetStyle();
		void SetStyle(VARIANT* newValue);
		CString GetText();
		void SetText(LPCTSTR lpszNewValue);
		long GetLanguageID();
		void SetLanguageID(long nNewValue);
		long GetHighlight();
		void SetHighlight(long nNewValue);
		LPDISPATCH GetFrame();
		long GetLanguageIDFarEast();
		void SetLanguageIDFarEast(long nNewValue);
		void ClearFormatting();
		long GetNoProofing();
		void SetNoProofing(long nNewValue);
	};
	/////////////////////////////////////////////////////////////////////////////
	// Characters wrapper class

	class Characters : public COleDispatchDriver
	{
	public:
		Characters() {}		// Calls COleDispatchDriver default constructor
		Characters(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		Characters(const Characters& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPUNKNOWN Get_NewEnum();
		long GetCount();
		LPDISPATCH GetFirst();
		LPDISPATCH GetLast();
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		LPDISPATCH Item(long Index);
	};
	/////////////////////////////////////////////////////////////////////////////
	// Words wrapper class

	class Words : public COleDispatchDriver
	{
	public:
		Words() {}		// Calls COleDispatchDriver default constructor
		Words(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		Words(const Words& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPUNKNOWN Get_NewEnum();
		long GetCount();
		LPDISPATCH GetFirst();
		LPDISPATCH GetLast();
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		LPDISPATCH Item(long Index);
	};
	/////////////////////////////////////////////////////////////////////////////
	// Sentences wrapper class

	class Sentences : public COleDispatchDriver
	{
	public:
		Sentences() {}		// Calls COleDispatchDriver default constructor
		Sentences(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		Sentences(const Sentences& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPUNKNOWN Get_NewEnum();
		long GetCount();
		LPDISPATCH GetFirst();
		LPDISPATCH GetLast();
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		LPDISPATCH Item(long Index);
	};
	/////////////////////////////////////////////////////////////////////////////
	// Sections wrapper class

	class Sections : public COleDispatchDriver
	{
	public:
		Sections() {}		// Calls COleDispatchDriver default constructor
		Sections(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		Sections(const Sections& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPUNKNOWN Get_NewEnum();
		long GetCount();
		LPDISPATCH GetFirst();
		LPDISPATCH GetLast();
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		LPDISPATCH GetPageSetup();
		void SetPageSetup(LPDISPATCH newValue);
		LPDISPATCH Item(long Index);
		LPDISPATCH Add(VARIANT* Range, VARIANT* Start);
	};
	/////////////////////////////////////////////////////////////////////////////
	// Section wrapper class

	class Section : public COleDispatchDriver
	{
	public:
		Section() {}		// Calls COleDispatchDriver default constructor
		Section(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		Section(const Section& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetRange();
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		LPDISPATCH GetPageSetup();
		void SetPageSetup(LPDISPATCH newValue);
		LPDISPATCH GetHeaders();
		LPDISPATCH GetFooters();
		BOOL GetProtectedForForms();
		void SetProtectedForForms(BOOL bNewValue);
		long GetIndex();
		LPDISPATCH GetBorders();
		void SetBorders(LPDISPATCH newValue);
	};
	/////////////////////////////////////////////////////////////////////////////
	// Paragraphs wrapper class

	class Paragraphs : public COleDispatchDriver
	{
	public:
		Paragraphs() {}		// Calls COleDispatchDriver default constructor
		Paragraphs(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		Paragraphs(const Paragraphs& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPUNKNOWN Get_NewEnum();
		long GetCount();
		LPDISPATCH GetFirst();
		LPDISPATCH GetLast();
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		LPDISPATCH GetFormat();
		void SetFormat(LPDISPATCH newValue);
		LPDISPATCH GetTabStops();
		void SetTabStops(LPDISPATCH newValue);
		LPDISPATCH GetBorders();
		void SetBorders(LPDISPATCH newValue);
		VARIANT GetStyle();
		void SetStyle(VARIANT* newValue);
		long GetAlignment();
		void SetAlignment(long nNewValue);
		long GetKeepTogether();
		void SetKeepTogether(long nNewValue);
		long GetKeepWithNext();
		void SetKeepWithNext(long nNewValue);
		long GetPageBreakBefore();
		void SetPageBreakBefore(long nNewValue);
		long GetNoLineNumber();
		void SetNoLineNumber(long nNewValue);
		float GetRightIndent();
		void SetRightIndent(float newValue);
		float GetLeftIndent();
		void SetLeftIndent(float newValue);
		float GetFirstLineIndent();
		void SetFirstLineIndent(float newValue);
		float GetLineSpacing();
		void SetLineSpacing(float newValue);
		long GetLineSpacingRule();
		void SetLineSpacingRule(long nNewValue);
		float GetSpaceBefore();
		void SetSpaceBefore(float newValue);
		float GetSpaceAfter();
		void SetSpaceAfter(float newValue);
		long GetHyphenation();
		void SetHyphenation(long nNewValue);
		long GetWidowControl();
		void SetWidowControl(long nNewValue);
		LPDISPATCH GetShading();
		long GetFarEastLineBreakControl();
		void SetFarEastLineBreakControl(long nNewValue);
		long GetWordWrap();
		void SetWordWrap(long nNewValue);
		long GetHangingPunctuation();
		void SetHangingPunctuation(long nNewValue);
		long GetHalfWidthPunctuationOnTopOfLine();
		void SetHalfWidthPunctuationOnTopOfLine(long nNewValue);
		long GetAddSpaceBetweenFarEastAndAlpha();
		void SetAddSpaceBetweenFarEastAndAlpha(long nNewValue);
		long GetAddSpaceBetweenFarEastAndDigit();
		void SetAddSpaceBetweenFarEastAndDigit(long nNewValue);
		long GetBaseLineAlignment();
		void SetBaseLineAlignment(long nNewValue);
		long GetAutoAdjustRightIndent();
		void SetAutoAdjustRightIndent(long nNewValue);
		long GetDisableLineHeightGrid();
		void SetDisableLineHeightGrid(long nNewValue);
		long GetOutlineLevel();
		void SetOutlineLevel(long nNewValue);
		LPDISPATCH Item(long Index);
		LPDISPATCH Add(VARIANT* Range);
		void CloseUp();
		void OpenUp();
		void OpenOrCloseUp();
		void TabHangingIndent(short Count);
		void TabIndent(short Count);
		void Reset();
		void Space1();
		void Space15();
		void Space2();
		void IndentCharWidth(short Count);
		void IndentFirstLineCharWidth(short Count);
		void OutlinePromote();
		void OutlineDemote();
		void OutlineDemoteToBody();
		void Indent();
		void Outdent();
		float GetCharacterUnitRightIndent();
		void SetCharacterUnitRightIndent(float newValue);
		float GetCharacterUnitLeftIndent();
		void SetCharacterUnitLeftIndent(float newValue);
		float GetCharacterUnitFirstLineIndent();
		void SetCharacterUnitFirstLineIndent(float newValue);
		float GetLineUnitBefore();
		void SetLineUnitBefore(float newValue);
		float GetLineUnitAfter();
		void SetLineUnitAfter(float newValue);
		long GetReadingOrder();
		void SetReadingOrder(long nNewValue);
		long GetSpaceBeforeAuto();
		void SetSpaceBeforeAuto(long nNewValue);
		long GetSpaceAfterAuto();
		void SetSpaceAfterAuto(long nNewValue);
	};
	/////////////////////////////////////////////////////////////////////////////
	// Paragraph wrapper class

	class Paragraph : public COleDispatchDriver
	{
	public:
		Paragraph() {}		// Calls COleDispatchDriver default constructor
		Paragraph(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		Paragraph(const Paragraph& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetRange();
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		LPDISPATCH GetFormat();
		void SetFormat(LPDISPATCH newValue);
		LPDISPATCH GetTabStops();
		void SetTabStops(LPDISPATCH newValue);
		LPDISPATCH GetBorders();
		void SetBorders(LPDISPATCH newValue);
		LPDISPATCH GetDropCap();
		VARIANT GetStyle();
		void SetStyle(VARIANT* newValue);
		long GetAlignment();
		void SetAlignment(long nNewValue);
		long GetKeepTogether();
		void SetKeepTogether(long nNewValue);
		long GetKeepWithNext();
		void SetKeepWithNext(long nNewValue);
		long GetPageBreakBefore();
		void SetPageBreakBefore(long nNewValue);
		long GetNoLineNumber();
		void SetNoLineNumber(long nNewValue);
		float GetRightIndent();
		void SetRightIndent(float newValue);
		float GetLeftIndent();
		void SetLeftIndent(float newValue);
		float GetFirstLineIndent();
		void SetFirstLineIndent(float newValue);
		float GetLineSpacing();
		void SetLineSpacing(float newValue);
		long GetLineSpacingRule();
		void SetLineSpacingRule(long nNewValue);
		float GetSpaceBefore();
		void SetSpaceBefore(float newValue);
		float GetSpaceAfter();
		void SetSpaceAfter(float newValue);
		long GetHyphenation();
		void SetHyphenation(long nNewValue);
		long GetWidowControl();
		void SetWidowControl(long nNewValue);
		LPDISPATCH GetShading();
		long GetFarEastLineBreakControl();
		void SetFarEastLineBreakControl(long nNewValue);
		long GetWordWrap();
		void SetWordWrap(long nNewValue);
		long GetHangingPunctuation();
		void SetHangingPunctuation(long nNewValue);
		long GetHalfWidthPunctuationOnTopOfLine();
		void SetHalfWidthPunctuationOnTopOfLine(long nNewValue);
		long GetAddSpaceBetweenFarEastAndAlpha();
		void SetAddSpaceBetweenFarEastAndAlpha(long nNewValue);
		long GetAddSpaceBetweenFarEastAndDigit();
		void SetAddSpaceBetweenFarEastAndDigit(long nNewValue);
		long GetBaseLineAlignment();
		void SetBaseLineAlignment(long nNewValue);
		long GetAutoAdjustRightIndent();
		void SetAutoAdjustRightIndent(long nNewValue);
		long GetDisableLineHeightGrid();
		void SetDisableLineHeightGrid(long nNewValue);
		long GetOutlineLevel();
		void SetOutlineLevel(long nNewValue);
		void CloseUp();
		void OpenUp();
		void OpenOrCloseUp();
		void TabHangingIndent(short Count);
		void TabIndent(short Count);
		void Reset();
		void Space1();
		void Space15();
		void Space2();
		void IndentCharWidth(short Count);
		void IndentFirstLineCharWidth(short Count);
		LPDISPATCH Next(VARIANT* Count);
		LPDISPATCH Previous(VARIANT* Count);
		void OutlinePromote();
		void OutlineDemote();
		void OutlineDemoteToBody();
		void Indent();
		void Outdent();
		float GetCharacterUnitRightIndent();
		void SetCharacterUnitRightIndent(float newValue);
		float GetCharacterUnitLeftIndent();
		void SetCharacterUnitLeftIndent(float newValue);
		float GetCharacterUnitFirstLineIndent();
		void SetCharacterUnitFirstLineIndent(float newValue);
		float GetLineUnitBefore();
		void SetLineUnitBefore(float newValue);
		float GetLineUnitAfter();
		void SetLineUnitAfter(float newValue);
		long GetReadingOrder();
		void SetReadingOrder(long nNewValue);
		CString GetId();
		void SetId(LPCTSTR lpszNewValue);
		long GetSpaceBeforeAuto();
		void SetSpaceBeforeAuto(long nNewValue);
		long GetSpaceAfterAuto();
		void SetSpaceAfterAuto(long nNewValue);
	};
	/////////////////////////////////////////////////////////////////////////////
	// DropCap wrapper class

	class DropCap : public COleDispatchDriver
	{
	public:
		DropCap() {}		// Calls COleDispatchDriver default constructor
		DropCap(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		DropCap(const DropCap& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		long GetPosition();
		void SetPosition(long nNewValue);
		CString GetFontName();
		void SetFontName(LPCTSTR lpszNewValue);
		long GetLinesToDrop();
		void SetLinesToDrop(long nNewValue);
		float GetDistanceFromText();
		void SetDistanceFromText(float newValue);
		void Clear();
		void Enable();
	};
	/////////////////////////////////////////////////////////////////////////////
	// TabStops wrapper class

	class TabStops : public COleDispatchDriver
	{
	public:
		TabStops() {}		// Calls COleDispatchDriver default constructor
		TabStops(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		TabStops(const TabStops& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPUNKNOWN Get_NewEnum();
		long GetCount();
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		LPDISPATCH Item(VARIANT* Index);
		LPDISPATCH Add(float Position, VARIANT* Alignment, VARIANT* Leader);
		void ClearAll();
		LPDISPATCH Before(float Position);
		LPDISPATCH After(float Position);
	};
	/////////////////////////////////////////////////////////////////////////////
	// TabStop wrapper class

	class TabStop : public COleDispatchDriver
	{
	public:
		TabStop() {}		// Calls COleDispatchDriver default constructor
		TabStop(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		TabStop(const TabStop& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		long GetAlignment();
		void SetAlignment(long nNewValue);
		long GetLeader();
		void SetLeader(long nNewValue);
		float GetPosition();
		void SetPosition(float newValue);
		BOOL GetCustomTab();
		LPDISPATCH GetNext();
		LPDISPATCH GetPrevious();
		void Clear();
	};
	/////////////////////////////////////////////////////////////////////////////
	// _ParagraphFormat wrapper class

	class _ParagraphFormat : public COleDispatchDriver
	{
	public:
		_ParagraphFormat() {}		// Calls COleDispatchDriver default constructor
		_ParagraphFormat(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		_ParagraphFormat(const _ParagraphFormat& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		LPDISPATCH GetDuplicate();
		VARIANT GetStyle();
		void SetStyle(VARIANT* newValue);
		long GetAlignment();
		void SetAlignment(long nNewValue);
		long GetKeepTogether();
		void SetKeepTogether(long nNewValue);
		long GetKeepWithNext();
		void SetKeepWithNext(long nNewValue);
		long GetPageBreakBefore();
		void SetPageBreakBefore(long nNewValue);
		long GetNoLineNumber();
		void SetNoLineNumber(long nNewValue);
		float GetRightIndent();
		void SetRightIndent(float newValue);
		float GetLeftIndent();
		void SetLeftIndent(float newValue);
		float GetFirstLineIndent();
		void SetFirstLineIndent(float newValue);
		float GetLineSpacing();
		void SetLineSpacing(float newValue);
		long GetLineSpacingRule();
		void SetLineSpacingRule(long nNewValue);
		float GetSpaceBefore();
		void SetSpaceBefore(float newValue);
		float GetSpaceAfter();
		void SetSpaceAfter(float newValue);
		long GetHyphenation();
		void SetHyphenation(long nNewValue);
		long GetWidowControl();
		void SetWidowControl(long nNewValue);
		long GetFarEastLineBreakControl();
		void SetFarEastLineBreakControl(long nNewValue);
		long GetWordWrap();
		void SetWordWrap(long nNewValue);
		long GetHangingPunctuation();
		void SetHangingPunctuation(long nNewValue);
		long GetHalfWidthPunctuationOnTopOfLine();
		void SetHalfWidthPunctuationOnTopOfLine(long nNewValue);
		long GetAddSpaceBetweenFarEastAndAlpha();
		void SetAddSpaceBetweenFarEastAndAlpha(long nNewValue);
		long GetAddSpaceBetweenFarEastAndDigit();
		void SetAddSpaceBetweenFarEastAndDigit(long nNewValue);
		long GetBaseLineAlignment();
		void SetBaseLineAlignment(long nNewValue);
		long GetAutoAdjustRightIndent();
		void SetAutoAdjustRightIndent(long nNewValue);
		long GetDisableLineHeightGrid();
		void SetDisableLineHeightGrid(long nNewValue);
		LPDISPATCH GetTabStops();
		void SetTabStops(LPDISPATCH newValue);
		LPDISPATCH GetBorders();
		void SetBorders(LPDISPATCH newValue);
		LPDISPATCH GetShading();
		long GetOutlineLevel();
		void SetOutlineLevel(long nNewValue);
		void CloseUp();
		void OpenUp();
		void OpenOrCloseUp();
		void TabHangingIndent(short Count);
		void TabIndent(short Count);
		void Reset();
		void Space1();
		void Space15();
		void Space2();
		void IndentCharWidth(short Count);
		void IndentFirstLineCharWidth(short Count);
		float GetCharacterUnitRightIndent();
		void SetCharacterUnitRightIndent(float newValue);
		float GetCharacterUnitLeftIndent();
		void SetCharacterUnitLeftIndent(float newValue);
		float GetCharacterUnitFirstLineIndent();
		void SetCharacterUnitFirstLineIndent(float newValue);
		float GetLineUnitBefore();
		void SetLineUnitBefore(float newValue);
		float GetLineUnitAfter();
		void SetLineUnitAfter(float newValue);
		long GetReadingOrder();
		void SetReadingOrder(long nNewValue);
		long GetSpaceBeforeAuto();
		void SetSpaceBeforeAuto(long nNewValue);
		long GetSpaceAfterAuto();
		void SetSpaceAfterAuto(long nNewValue);
	};
	/////////////////////////////////////////////////////////////////////////////
	// _Font wrapper class

	class _Font : public COleDispatchDriver
	{
	public:
		_Font() {}		// Calls COleDispatchDriver default constructor
		_Font(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		_Font(const _Font& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		LPDISPATCH GetDuplicate();
		long GetBold();
		void SetBold(long nNewValue);
		long GetItalic();
		void SetItalic(long nNewValue);
		long GetHidden();
		void SetHidden(long nNewValue);
		long GetSmallCaps();
		void SetSmallCaps(long nNewValue);
		long GetAllCaps();
		void SetAllCaps(long nNewValue);
		long GetStrikeThrough();
		void SetStrikeThrough(long nNewValue);
		long GetDoubleStrikeThrough();
		void SetDoubleStrikeThrough(long nNewValue);
		long GetColorIndex();
		void SetColorIndex(long nNewValue);
		long GetSubscript();
		void SetSubscript(long nNewValue);
		long GetSuperscript();
		void SetSuperscript(long nNewValue);
		long GetUnderline();
		void SetUnderline(long nNewValue);
		float GetSize();
		void SetSize(float newValue);
		CString GetName();
		void SetName(LPCTSTR lpszNewValue);
		long GetPosition();
		void SetPosition(long nNewValue);
		float GetSpacing();
		void SetSpacing(float newValue);
		long GetScaling();
		void SetScaling(long nNewValue);
		long GetShadow();
		void SetShadow(long nNewValue);
		long GetOutline();
		void SetOutline(long nNewValue);
		long GetEmboss();
		void SetEmboss(long nNewValue);
		float GetKerning();
		void SetKerning(float newValue);
		long GetEngrave();
		void SetEngrave(long nNewValue);
		long GetAnimation();
		void SetAnimation(long nNewValue);
		LPDISPATCH GetBorders();
		void SetBorders(LPDISPATCH newValue);
		LPDISPATCH GetShading();
		long GetEmphasisMark();
		void SetEmphasisMark(long nNewValue);
		BOOL GetDisableCharacterSpaceGrid();
		void SetDisableCharacterSpaceGrid(BOOL bNewValue);
		CString GetNameFarEast();
		void SetNameFarEast(LPCTSTR lpszNewValue);
		CString GetNameAscii();
		void SetNameAscii(LPCTSTR lpszNewValue);
		CString GetNameOther();
		void SetNameOther(LPCTSTR lpszNewValue);
		void Grow();
		void Shrink();
		void Reset();
		void SetAsTemplateDefault();
		long GetColor();
		void SetColor(long nNewValue);
		long GetBoldBi();
		void SetBoldBi(long nNewValue);
		long GetItalicBi();
		void SetItalicBi(long nNewValue);
		float GetSizeBi();
		void SetSizeBi(float newValue);
		CString GetNameBi();
		void SetNameBi(LPCTSTR lpszNewValue);
		long GetColorIndexBi();
		void SetColorIndexBi(long nNewValue);
		long GetDiacriticColor();
		void SetDiacriticColor(long nNewValue);
		long GetUnderlineColor();
		void SetUnderlineColor(long nNewValue);
	};
	/////////////////////////////////////////////////////////////////////////////
	// Table wrapper class

	class Table : public COleDispatchDriver
	{
	public:
		Table() {}		// Calls COleDispatchDriver default constructor
		Table(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		Table(const Table& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetRange();
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		LPDISPATCH GetColumns();
		LPDISPATCH GetRows();
		LPDISPATCH GetBorders();
		void SetBorders(LPDISPATCH newValue);
		LPDISPATCH GetShading();
		BOOL GetUniform();
		long GetAutoFormatType();
		void Select();
		void Delete();
		void SortAscending();
		void SortDescending();
		void AutoFormat(VARIANT* Format, VARIANT* ApplyBorders, VARIANT* ApplyShading, VARIANT* ApplyFont, VARIANT* ApplyColor, VARIANT* ApplyHeadingRows, VARIANT* ApplyLastRow, VARIANT* ApplyFirstColumn, VARIANT* ApplyLastColumn, VARIANT* AutoFit);
		void UpdateAutoFormat();
		LPDISPATCH Cell(long Row, long Column);
		LPDISPATCH Split(VARIANT* BeforeRow);
		LPDISPATCH ConvertToText(VARIANT* Separator, VARIANT* NestedTables);
		void AutoFitBehavior(long Behavior);
		void Sort(VARIANT* ExcludeHeader, VARIANT* FieldNumber, VARIANT* SortFieldType, VARIANT* SortOrder, VARIANT* FieldNumber2, VARIANT* SortFieldType2, VARIANT* SortOrder2, VARIANT* FieldNumber3, VARIANT* SortFieldType3, VARIANT* SortOrder3, 
			VARIANT* CaseSensitive, VARIANT* BidiSort, VARIANT* IgnoreThe, VARIANT* IgnoreKashida, VARIANT* IgnoreDiacritics, VARIANT* IgnoreHe, VARIANT* LanguageID);
		LPDISPATCH GetTables();
		long GetNestingLevel();
		BOOL GetAllowPageBreaks();
		void SetAllowPageBreaks(BOOL bNewValue);
		BOOL GetAllowAutoFit();
		void SetAllowAutoFit(BOOL bNewValue);
		float GetPreferredWidth();
		void SetPreferredWidth(float newValue);
		long GetPreferredWidthType();
		void SetPreferredWidthType(long nNewValue);
		float GetTopPadding();
		void SetTopPadding(float newValue);
		float GetBottomPadding();
		void SetBottomPadding(float newValue);
		float GetLeftPadding();
		void SetLeftPadding(float newValue);
		float GetRightPadding();
		void SetRightPadding(float newValue);
		float GetSpacing();
		void SetSpacing(float newValue);
		long GetTableDirection();
		void SetTableDirection(long nNewValue);
		CString GetId();
		void SetId(LPCTSTR lpszNewValue);
	};
	/////////////////////////////////////////////////////////////////////////////
	// Row wrapper class

	class Row : public COleDispatchDriver
	{
	public:
		Row() {}		// Calls COleDispatchDriver default constructor
		Row(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		Row(const Row& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetRange();
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		long GetAllowBreakAcrossPages();
		void SetAllowBreakAcrossPages(long nNewValue);
		long GetAlignment();
		void SetAlignment(long nNewValue);
		long GetHeadingFormat();
		void SetHeadingFormat(long nNewValue);
		float GetSpaceBetweenColumns();
		void SetSpaceBetweenColumns(float newValue);
		float GetHeight();
		void SetHeight(float newValue);
		long GetHeightRule();
		void SetHeightRule(long nNewValue);
		float GetLeftIndent();
		void SetLeftIndent(float newValue);
		BOOL GetIsLast();
		BOOL GetIsFirst();
		long GetIndex();
		LPDISPATCH GetCells();
		LPDISPATCH GetBorders();
		void SetBorders(LPDISPATCH newValue);
		LPDISPATCH GetShading();
		LPDISPATCH GetNext();
		LPDISPATCH GetPrevious();
		void Select();
		void Delete();
		void SetLeftIndent(float LeftIndent, long RulerStyle);
		void SetHeight(float RowHeight, long HeightRule);
		LPDISPATCH ConvertToText(VARIANT* Separator, VARIANT* NestedTables);
		long GetNestingLevel();
		CString GetId();
		void SetId(LPCTSTR lpszNewValue);
	};
	/////////////////////////////////////////////////////////////////////////////
	// Column wrapper class

	class Column : public COleDispatchDriver
	{
	public:
		Column() {}		// Calls COleDispatchDriver default constructor
		Column(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		Column(const Column& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		float GetWidth();
		void SetWidth(float newValue);
		BOOL GetIsFirst();
		BOOL GetIsLast();
		long GetIndex();
		LPDISPATCH GetCells();
		LPDISPATCH GetBorders();
		void SetBorders(LPDISPATCH newValue);
		LPDISPATCH GetShading();
		LPDISPATCH GetNext();
		LPDISPATCH GetPrevious();
		void Select();
		void Delete();
		void SetWidth(float ColumnWidth, long RulerStyle);
		void AutoFit();
		void Sort(VARIANT* ExcludeHeader, VARIANT* SortFieldType, VARIANT* SortOrder, VARIANT* CaseSensitive, VARIANT* BidiSort, VARIANT* IgnoreThe, VARIANT* IgnoreKashida, VARIANT* IgnoreDiacritics, VARIANT* IgnoreHe, VARIANT* LanguageID);
		long GetNestingLevel();
		float GetPreferredWidth();
		void SetPreferredWidth(float newValue);
		long GetPreferredWidthType();
		void SetPreferredWidthType(long nNewValue);
	};
	/////////////////////////////////////////////////////////////////////////////
	// Cell wrapper class

	class Cell : public COleDispatchDriver
	{
	public:
		Cell() {}		// Calls COleDispatchDriver default constructor
		Cell(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		Cell(const Cell& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetRange();
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		long GetRowIndex();
		long GetColumnIndex();
		float GetWidth();
		void SetWidth(float newValue);
		float GetHeight();
		void SetHeight(float newValue);
		long GetHeightRule();
		void SetHeightRule(long nNewValue);
		long GetVerticalAlignment();
		void SetVerticalAlignment(long nNewValue);
		LPDISPATCH GetColumn();
		LPDISPATCH GetRow();
		LPDISPATCH GetNext();
		LPDISPATCH GetPrevious();
		LPDISPATCH GetShading();
		LPDISPATCH GetBorders();
		void SetBorders(LPDISPATCH newValue);
		void Select();
		void Delete(VARIANT* ShiftCells);
		void Formula(VARIANT* Formula, VARIANT* NumFormat);
		void SetWidth(float ColumnWidth, long RulerStyle);
		void SetHeight(VARIANT* RowHeight, long HeightRule);
		void Merge(LPDISPATCH MergeTo);
		void Split(VARIANT* NumRows, VARIANT* NumColumns);
		void AutoSum();
		LPDISPATCH GetTables();
		long GetNestingLevel();
		BOOL GetWordWrap();
		void SetWordWrap(BOOL bNewValue);
		float GetPreferredWidth();
		void SetPreferredWidth(float newValue);
		BOOL GetFitText();
		void SetFitText(BOOL bNewValue);
		float GetTopPadding();
		void SetTopPadding(float newValue);
		float GetBottomPadding();
		void SetBottomPadding(float newValue);
		float GetLeftPadding();
		void SetLeftPadding(float newValue);
		float GetRightPadding();
		void SetRightPadding(float newValue);
		CString GetId();
		void SetId(LPCTSTR lpszNewValue);
		long GetPreferredWidthType();
		void SetPreferredWidthType(long nNewValue);
	};
	/////////////////////////////////////////////////////////////////////////////
	// Tables wrapper class

	class Tables : public COleDispatchDriver
	{
	public:
		Tables() {}		// Calls COleDispatchDriver default constructor
		Tables(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		Tables(const Tables& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPUNKNOWN Get_NewEnum();
		long GetCount();
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		LPDISPATCH Item(long Index);
		LPDISPATCH Add(LPDISPATCH Range, long NumRows, long NumColumns, VARIANT* DefaultTableBehavior, VARIANT* AutoFitBehavior);
		long GetNestingLevel();
	};
	/////////////////////////////////////////////////////////////////////////////
	// Rows wrapper class

	class Rows : public COleDispatchDriver
	{
	public:
		Rows() {}		// Calls COleDispatchDriver default constructor
		Rows(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		Rows(const Rows& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPUNKNOWN Get_NewEnum();
		long GetCount();
		long GetAllowBreakAcrossPages();
		void SetAllowBreakAcrossPages(long nNewValue);
		long GetAlignment();
		void SetAlignment(long nNewValue);
		long GetHeadingFormat();
		void SetHeadingFormat(long nNewValue);
		float GetSpaceBetweenColumns();
		void SetSpaceBetweenColumns(float newValue);
		float GetHeight();
		void SetHeight(float newValue);
		long GetHeightRule();
		void SetHeightRule(long nNewValue);
		float GetLeftIndent();
		void SetLeftIndent(float newValue);
		LPDISPATCH GetFirst();
		LPDISPATCH GetLast();
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		LPDISPATCH GetBorders();
		void SetBorders(LPDISPATCH newValue);
		LPDISPATCH GetShading();
		LPDISPATCH Item(long Index);
		LPDISPATCH Add(VARIANT* BeforeRow);
		void Select();
		void Delete();
		void SetLeftIndent(float LeftIndent, long RulerStyle);
		void SetHeight(float RowHeight, long HeightRule);
		void DistributeHeight();
		LPDISPATCH ConvertToText(VARIANT* Separator, VARIANT* NestedTables);
		long GetWrapAroundText();
		void SetWrapAroundText(long nNewValue);
		float GetDistanceTop();
		void SetDistanceTop(float newValue);
		float GetDistanceBottom();
		void SetDistanceBottom(float newValue);
		float GetDistanceLeft();
		void SetDistanceLeft(float newValue);
		float GetDistanceRight();
		void SetDistanceRight(float newValue);
		float GetHorizontalPosition();
		void SetHorizontalPosition(float newValue);
		float GetVerticalPosition();
		void SetVerticalPosition(float newValue);
		long GetRelativeHorizontalPosition();
		void SetRelativeHorizontalPosition(long nNewValue);
		long GetRelativeVerticalPosition();
		void SetRelativeVerticalPosition(long nNewValue);
		long GetAllowOverlap();
		void SetAllowOverlap(long nNewValue);
		long GetNestingLevel();
		long GetTableDirection();
		void SetTableDirection(long nNewValue);
	};
	/////////////////////////////////////////////////////////////////////////////
	// Columns wrapper class

	class Columns : public COleDispatchDriver
	{
	public:
		Columns() {}		// Calls COleDispatchDriver default constructor
		Columns(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		Columns(const Columns& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPUNKNOWN Get_NewEnum();
		long GetCount();
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		LPDISPATCH GetFirst();
		LPDISPATCH GetLast();
		float GetWidth();
		void SetWidth(float newValue);
		LPDISPATCH GetBorders();
		void SetBorders(LPDISPATCH newValue);
		LPDISPATCH GetShading();
		LPDISPATCH Item(long Index);
		LPDISPATCH Add(VARIANT* BeforeColumn);
		void Select();
		void Delete();
		void SetWidth(float ColumnWidth, long RulerStyle);
		void AutoFit();
		void DistributeWidth();
		long GetNestingLevel();
		float GetPreferredWidth();
		void SetPreferredWidth(float newValue);
		long GetPreferredWidthType();
		void SetPreferredWidthType(long nNewValue);
	};
	/////////////////////////////////////////////////////////////////////////////
	// Cells wrapper class

	class Cells : public COleDispatchDriver
	{
	public:
		Cells() {}		// Calls COleDispatchDriver default constructor
		Cells(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		Cells(const Cells& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPUNKNOWN Get_NewEnum();
		long GetCount();
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		float GetWidth();
		void SetWidth(float newValue);
		float GetHeight();
		void SetHeight(float newValue);
		long GetHeightRule();
		void SetHeightRule(long nNewValue);
		long GetVerticalAlignment();
		void SetVerticalAlignment(long nNewValue);
		LPDISPATCH GetBorders();
		void SetBorders(LPDISPATCH newValue);
		LPDISPATCH GetShading();
		LPDISPATCH Item(long Index);
		LPDISPATCH Add(VARIANT* BeforeCell);
		void Delete(VARIANT* ShiftCells);
		void SetWidth(float ColumnWidth, long RulerStyle);
		void SetHeight(VARIANT* RowHeight, long HeightRule);
		void Merge();
		void Split(VARIANT* NumRows, VARIANT* NumColumns, VARIANT* MergeBeforeSplit);
		void DistributeHeight();
		void DistributeWidth();
		void AutoFit();
		long GetNestingLevel();
		float GetPreferredWidth();
		void SetPreferredWidth(float newValue);
		long GetPreferredWidthType();
		void SetPreferredWidthType(long nNewValue);
	};
	/////////////////////////////////////////////////////////////////////////////
	// AutoCorrect wrapper class

	class AutoCorrect : public COleDispatchDriver
	{
	public:
		AutoCorrect() {}		// Calls COleDispatchDriver default constructor
		AutoCorrect(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		AutoCorrect(const AutoCorrect& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		BOOL GetCorrectDays();
		void SetCorrectDays(BOOL bNewValue);
		BOOL GetCorrectInitialCaps();
		void SetCorrectInitialCaps(BOOL bNewValue);
		BOOL GetCorrectSentenceCaps();
		void SetCorrectSentenceCaps(BOOL bNewValue);
		BOOL GetReplaceText();
		void SetReplaceText(BOOL bNewValue);
		LPDISPATCH GetEntries();
		LPDISPATCH GetFirstLetterExceptions();
		BOOL GetFirstLetterAutoAdd();
		void SetFirstLetterAutoAdd(BOOL bNewValue);
		LPDISPATCH GetTwoInitialCapsExceptions();
		BOOL GetTwoInitialCapsAutoAdd();
		void SetTwoInitialCapsAutoAdd(BOOL bNewValue);
		BOOL GetCorrectCapsLock();
		void SetCorrectCapsLock(BOOL bNewValue);
		BOOL GetCorrectHangulAndAlphabet();
		void SetCorrectHangulAndAlphabet(BOOL bNewValue);
		LPDISPATCH GetHangulAndAlphabetExceptions();
		BOOL GetHangulAndAlphabetAutoAdd();
		void SetHangulAndAlphabetAutoAdd(BOOL bNewValue);
		BOOL GetReplaceTextFromSpellingChecker();
		void SetReplaceTextFromSpellingChecker(BOOL bNewValue);
		BOOL GetOtherCorrectionsAutoAdd();
		void SetOtherCorrectionsAutoAdd(BOOL bNewValue);
		LPDISPATCH GetOtherCorrectionsExceptions();
		BOOL GetCorrectKeyboardSetting();
		void SetCorrectKeyboardSetting(BOOL bNewValue);
	};
	/////////////////////////////////////////////////////////////////////////////
	// AutoCorrectEntries wrapper class

	class AutoCorrectEntries : public COleDispatchDriver
	{
	public:
		AutoCorrectEntries() {}		// Calls COleDispatchDriver default constructor
		AutoCorrectEntries(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		AutoCorrectEntries(const AutoCorrectEntries& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		LPUNKNOWN Get_NewEnum();
		long GetCount();
		LPDISPATCH Item(VARIANT* Index);
		LPDISPATCH Add(LPCTSTR Name, LPCTSTR Value);
		LPDISPATCH AddRichText(LPCTSTR Name, LPDISPATCH Range);
	};
	/////////////////////////////////////////////////////////////////////////////
	// AutoCorrectEntry wrapper class

	class AutoCorrectEntry : public COleDispatchDriver
	{
	public:
		AutoCorrectEntry() {}		// Calls COleDispatchDriver default constructor
		AutoCorrectEntry(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		AutoCorrectEntry(const AutoCorrectEntry& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		long GetIndex();
		CString GetName();
		void SetName(LPCTSTR lpszNewValue);
		CString GetValue();
		void SetValue(LPCTSTR lpszNewValue);
		BOOL GetRichText();
		void Delete();
		void Apply(LPDISPATCH Range);
	};
	/////////////////////////////////////////////////////////////////////////////
	// FirstLetterExceptions wrapper class

	class FirstLetterExceptions : public COleDispatchDriver
	{
	public:
		FirstLetterExceptions() {}		// Calls COleDispatchDriver default constructor
		FirstLetterExceptions(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		FirstLetterExceptions(const FirstLetterExceptions& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		LPUNKNOWN Get_NewEnum();
		long GetCount();
		LPDISPATCH Item(VARIANT* Index);
		LPDISPATCH Add(LPCTSTR Name);
	};
	/////////////////////////////////////////////////////////////////////////////
	// FirstLetterException wrapper class

	class FirstLetterException : public COleDispatchDriver
	{
	public:
		FirstLetterException() {}		// Calls COleDispatchDriver default constructor
		FirstLetterException(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		FirstLetterException(const FirstLetterException& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		long GetIndex();
		CString GetName();
		void Delete();
	};
	/////////////////////////////////////////////////////////////////////////////
	// TwoInitialCapsExceptions wrapper class

	class TwoInitialCapsExceptions : public COleDispatchDriver
	{
	public:
		TwoInitialCapsExceptions() {}		// Calls COleDispatchDriver default constructor
		TwoInitialCapsExceptions(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		TwoInitialCapsExceptions(const TwoInitialCapsExceptions& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		LPUNKNOWN Get_NewEnum();
		long GetCount();
		LPDISPATCH Item(VARIANT* Index);
		LPDISPATCH Add(LPCTSTR Name);
	};
	/////////////////////////////////////////////////////////////////////////////
	// TwoInitialCapsException wrapper class

	class TwoInitialCapsException : public COleDispatchDriver
	{
	public:
		TwoInitialCapsException() {}		// Calls COleDispatchDriver default constructor
		TwoInitialCapsException(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		TwoInitialCapsException(const TwoInitialCapsException& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		long GetIndex();
		CString GetName();
		void Delete();
	};
	/////////////////////////////////////////////////////////////////////////////
	// Footnotes wrapper class

	class Footnotes : public COleDispatchDriver
	{
	public:
		Footnotes() {}		// Calls COleDispatchDriver default constructor
		Footnotes(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		Footnotes(const Footnotes& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPUNKNOWN Get_NewEnum();
		long GetCount();
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		long GetLocation();
		void SetLocation(long nNewValue);
		long GetNumberStyle();
		void SetNumberStyle(long nNewValue);
		long GetStartingNumber();
		void SetStartingNumber(long nNewValue);
		long GetNumberingRule();
		void SetNumberingRule(long nNewValue);
		LPDISPATCH GetSeparator();
		LPDISPATCH GetContinuationSeparator();
		LPDISPATCH GetContinuationNotice();
		LPDISPATCH Item(long Index);
		LPDISPATCH Add(LPDISPATCH Range, VARIANT* Reference, VARIANT* Text);
		void Convert();
		void SwapWithEndnotes();
		void ResetSeparator();
		void ResetContinuationSeparator();
		void ResetContinuationNotice();
	};
	/////////////////////////////////////////////////////////////////////////////
	// Endnotes wrapper class

	class Endnotes : public COleDispatchDriver
	{
	public:
		Endnotes() {}		// Calls COleDispatchDriver default constructor
		Endnotes(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		Endnotes(const Endnotes& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPUNKNOWN Get_NewEnum();
		long GetCount();
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		long GetLocation();
		void SetLocation(long nNewValue);
		long GetNumberStyle();
		void SetNumberStyle(long nNewValue);
		long GetStartingNumber();
		void SetStartingNumber(long nNewValue);
		long GetNumberingRule();
		void SetNumberingRule(long nNewValue);
		LPDISPATCH GetSeparator();
		LPDISPATCH GetContinuationSeparator();
		LPDISPATCH GetContinuationNotice();
		LPDISPATCH Item(long Index);
		LPDISPATCH Add(LPDISPATCH Range, VARIANT* Reference, VARIANT* Text);
		void Convert();
		void SwapWithFootnotes();
		void ResetSeparator();
		void ResetContinuationSeparator();
		void ResetContinuationNotice();
	};
	/////////////////////////////////////////////////////////////////////////////
	// Comments wrapper class

	class Comments : public COleDispatchDriver
	{
	public:
		Comments() {}		// Calls COleDispatchDriver default constructor
		Comments(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		Comments(const Comments& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPUNKNOWN Get_NewEnum();
		long GetCount();
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		CString GetShowBy();
		void SetShowBy(LPCTSTR lpszNewValue);
		LPDISPATCH Item(long Index);
		LPDISPATCH Add(LPDISPATCH Range, VARIANT* Text);
	};
	/////////////////////////////////////////////////////////////////////////////
	// Footnote wrapper class

	class Footnote : public COleDispatchDriver
	{
	public:
		Footnote() {}		// Calls COleDispatchDriver default constructor
		Footnote(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		Footnote(const Footnote& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		LPDISPATCH GetRange();
		LPDISPATCH GetReference();
		long GetIndex();
		void Delete();
	};
	/////////////////////////////////////////////////////////////////////////////
	// Endnote wrapper class

	class Endnote : public COleDispatchDriver
	{
	public:
		Endnote() {}		// Calls COleDispatchDriver default constructor
		Endnote(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		Endnote(const Endnote& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		LPDISPATCH GetRange();
		LPDISPATCH GetReference();
		long GetIndex();
		void Delete();
	};
	/////////////////////////////////////////////////////////////////////////////
	// Comment wrapper class

	class Comment : public COleDispatchDriver
	{
	public:
		Comment() {}		// Calls COleDispatchDriver default constructor
		Comment(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		Comment(const Comment& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		LPDISPATCH GetRange();
		LPDISPATCH GetReference();
		LPDISPATCH GetScope();
		long GetIndex();
		CString GetAuthor();
		void SetAuthor(LPCTSTR lpszNewValue);
		CString GetInitial();
		void SetInitial(LPCTSTR lpszNewValue);
		BOOL GetShowTip();
		void SetShowTip(BOOL bNewValue);
		void Delete();
	};
	/////////////////////////////////////////////////////////////////////////////
	// Borders wrapper class

	class Borders : public COleDispatchDriver
	{
	public:
		Borders() {}		// Calls COleDispatchDriver default constructor
		Borders(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		Borders(const Borders& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		LPUNKNOWN Get_NewEnum();
		long GetCount();
		long GetEnable();
		void SetEnable(long nNewValue);
		long GetDistanceFromTop();
		void SetDistanceFromTop(long nNewValue);
		BOOL GetShadow();
		void SetShadow(BOOL bNewValue);
		long GetInsideLineStyle();
		void SetInsideLineStyle(long nNewValue);
		long GetOutsideLineStyle();
		void SetOutsideLineStyle(long nNewValue);
		long GetInsideLineWidth();
		void SetInsideLineWidth(long nNewValue);
		long GetOutsideLineWidth();
		void SetOutsideLineWidth(long nNewValue);
		long GetInsideColorIndex();
		void SetInsideColorIndex(long nNewValue);
		long GetOutsideColorIndex();
		void SetOutsideColorIndex(long nNewValue);
		long GetDistanceFromLeft();
		void SetDistanceFromLeft(long nNewValue);
		long GetDistanceFromBottom();
		void SetDistanceFromBottom(long nNewValue);
		long GetDistanceFromRight();
		void SetDistanceFromRight(long nNewValue);
		BOOL GetAlwaysInFront();
		void SetAlwaysInFront(BOOL bNewValue);
		BOOL GetSurroundHeader();
		void SetSurroundHeader(BOOL bNewValue);
		BOOL GetSurroundFooter();
		void SetSurroundFooter(BOOL bNewValue);
		BOOL GetJoinBorders();
		void SetJoinBorders(BOOL bNewValue);
		BOOL GetHasHorizontal();
		BOOL GetHasVertical();
		long GetDistanceFrom();
		void SetDistanceFrom(long nNewValue);
		BOOL GetEnableFirstPageInSection();
		void SetEnableFirstPageInSection(BOOL bNewValue);
		BOOL GetEnableOtherPagesInSection();
		void SetEnableOtherPagesInSection(BOOL bNewValue);
		LPDISPATCH Item(long Index);
		void ApplyPageBordersToAllSections();
		long GetInsideColor();
		void SetInsideColor(long nNewValue);
		long GetOutsideColor();
		void SetOutsideColor(long nNewValue);
	};
	/////////////////////////////////////////////////////////////////////////////
	// Border wrapper class

	class Border : public COleDispatchDriver
	{
	public:
		Border() {}		// Calls COleDispatchDriver default constructor
		Border(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		Border(const Border& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		BOOL GetVisible();
		void SetVisible(BOOL bNewValue);
		long GetColorIndex();
		void SetColorIndex(long nNewValue);
		BOOL GetInside();
		long GetLineStyle();
		void SetLineStyle(long nNewValue);
		long GetLineWidth();
		void SetLineWidth(long nNewValue);
		long GetArtStyle();
		void SetArtStyle(long nNewValue);
		long GetArtWidth();
		void SetArtWidth(long nNewValue);
		long GetColor();
		void SetColor(long nNewValue);
	};
	/////////////////////////////////////////////////////////////////////////////
	// Shading wrapper class

	class Shading : public COleDispatchDriver
	{
	public:
		Shading() {}		// Calls COleDispatchDriver default constructor
		Shading(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		Shading(const Shading& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		long GetForegroundPatternColorIndex();
		void SetForegroundPatternColorIndex(long nNewValue);
		long GetBackgroundPatternColorIndex();
		void SetBackgroundPatternColorIndex(long nNewValue);
		long GetTexture();
		void SetTexture(long nNewValue);
		long GetForegroundPatternColor();
		void SetForegroundPatternColor(long nNewValue);
		long GetBackgroundPatternColor();
		void SetBackgroundPatternColor(long nNewValue);
	};
	/////////////////////////////////////////////////////////////////////////////
	// TextRetrievalMode wrapper class

	class TextRetrievalMode : public COleDispatchDriver
	{
	public:
		TextRetrievalMode() {}		// Calls COleDispatchDriver default constructor
		TextRetrievalMode(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		TextRetrievalMode(const TextRetrievalMode& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		long GetViewType();
		void SetViewType(long nNewValue);
		LPDISPATCH GetDuplicate();
		BOOL GetIncludeHiddenText();
		void SetIncludeHiddenText(BOOL bNewValue);
		BOOL GetIncludeFieldCodes();
		void SetIncludeFieldCodes(BOOL bNewValue);
	};
	/////////////////////////////////////////////////////////////////////////////
	// AutoTextEntries wrapper class

	class AutoTextEntries : public COleDispatchDriver
	{
	public:
		AutoTextEntries() {}		// Calls COleDispatchDriver default constructor
		AutoTextEntries(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		AutoTextEntries(const AutoTextEntries& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		LPUNKNOWN Get_NewEnum();
		long GetCount();
		LPDISPATCH Item(VARIANT* Index);
		LPDISPATCH Add(LPCTSTR Name, LPDISPATCH Range);
		LPDISPATCH AppendToSpike(LPDISPATCH Range);
	};
	/////////////////////////////////////////////////////////////////////////////
	// AutoTextEntry wrapper class

	class AutoTextEntry : public COleDispatchDriver
	{
	public:
		AutoTextEntry() {}		// Calls COleDispatchDriver default constructor
		AutoTextEntry(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		AutoTextEntry(const AutoTextEntry& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		long GetIndex();
		CString GetName();
		void SetName(LPCTSTR lpszNewValue);
		CString GetStyleName();
		CString GetValue();
		void SetValue(LPCTSTR lpszNewValue);
		void Delete();
		LPDISPATCH Insert(LPDISPATCH Where, VARIANT* RichText);
	};
	/////////////////////////////////////////////////////////////////////////////
	// System wrapper class

	class System : public COleDispatchDriver
	{
	public:
		System() {}		// Calls COleDispatchDriver default constructor
		System(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		System(const System& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		CString GetOperatingSystem();
		CString GetProcessorType();
		CString GetVersion();
		long GetFreeDiskSpace();
		long GetCountry();
		CString GetLanguageDesignation();
		long GetHorizontalResolution();
		long GetVerticalResolution();
		CString GetProfileString(LPCTSTR Section, LPCTSTR Key);
		void SetProfileString(LPCTSTR Section, LPCTSTR Key, LPCTSTR lpszNewValue);
		CString GetPrivateProfileString(LPCTSTR FileName, LPCTSTR Section, LPCTSTR Key);
		void SetPrivateProfileString(LPCTSTR FileName, LPCTSTR Section, LPCTSTR Key, LPCTSTR lpszNewValue);
		BOOL GetMathCoprocessorInstalled();
		CString GetComputerType();
		CString GetMacintoshName();
		BOOL GetQuickDrawInstalled();
		long GetCursor();
		void SetCursor(long nNewValue);
		void MSInfo();
		void Connect(LPCTSTR Path, VARIANT* Drive, VARIANT* Password);
	};
	/////////////////////////////////////////////////////////////////////////////
	// OLEFormat wrapper class

	class OLEFormat : public COleDispatchDriver
	{
	public:
		OLEFormat() {}		// Calls COleDispatchDriver default constructor
		OLEFormat(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		OLEFormat(const OLEFormat& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		CString GetClassType();
		void SetClassType(LPCTSTR lpszNewValue);
		BOOL GetDisplayAsIcon();
		void SetDisplayAsIcon(BOOL bNewValue);
		CString GetIconName();
		void SetIconName(LPCTSTR lpszNewValue);
		CString GetIconPath();
		long GetIconIndex();
		void SetIconIndex(long nNewValue);
		CString GetIconLabel();
		void SetIconLabel(LPCTSTR lpszNewValue);
		CString GetLabel();
		LPDISPATCH GetObject();
		CString GetProgID();
		void Activate();
		void Edit();
		void Open();
		void DoVerb(VARIANT* VerbIndex);
		void ConvertTo(VARIANT* ClassType, VARIANT* DisplayAsIcon, VARIANT* IconFileName, VARIANT* IconIndex, VARIANT* IconLabel);
		void ActivateAs(LPCTSTR ClassType);
	};
	/////////////////////////////////////////////////////////////////////////////
	// LinkFormat wrapper class

	class LinkFormat : public COleDispatchDriver
	{
	public:
		LinkFormat() {}		// Calls COleDispatchDriver default constructor
		LinkFormat(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		LinkFormat(const LinkFormat& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		BOOL GetAutoUpdate();
		void SetAutoUpdate(BOOL bNewValue);
		CString GetSourceName();
		CString GetSourcePath();
		BOOL GetLocked();
		void SetLocked(BOOL bNewValue);
		long GetType();
		CString GetSourceFullName();
		void SetSourceFullName(LPCTSTR lpszNewValue);
		BOOL GetSavePictureWithDocument();
		void SetSavePictureWithDocument(BOOL bNewValue);
		void BreakLink();
		void Update();
	};
	/////////////////////////////////////////////////////////////////////////////
	// _OLEControl wrapper class

	class _OLEControl : public COleDispatchDriver
	{
	public:
		_OLEControl() {}		// Calls COleDispatchDriver default constructor
		_OLEControl(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		_OLEControl(const _OLEControl& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		float GetLeft();
		void SetLeft(float newValue);
		float GetTop();
		void SetTop(float newValue);
		float GetHeight();
		void SetHeight(float newValue);
		float GetWidth();
		void SetWidth(float newValue);
		CString GetName();
		void SetName(LPCTSTR lpszNewValue);
		LPDISPATCH GetAutomation();
		void Select();
		void Copy();
		void Cut();
		void Delete();
		void Activate();
	};
	/////////////////////////////////////////////////////////////////////////////
	// Fields wrapper class

	/////////////////////////////////////////////////////////////////////////////
	// Browser wrapper class

	class Browser : public COleDispatchDriver
	{
	public:
		Browser() {}		// Calls COleDispatchDriver default constructor
		Browser(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		Browser(const Browser& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		long GetTarget();
		void SetTarget(long nNewValue);
		void Next();
		void Previous();
	};
	/////////////////////////////////////////////////////////////////////////////
	// Styles wrapper class

	class Styles : public COleDispatchDriver
	{
	public:
		Styles() {}		// Calls COleDispatchDriver default constructor
		Styles(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		Styles(const Styles& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		LPUNKNOWN Get_NewEnum();
		long GetCount();
		LPDISPATCH Item(VARIANT* Index);
		LPDISPATCH Add(LPCTSTR Name, VARIANT* Type);
	};
	/////////////////////////////////////////////////////////////////////////////
	// Style wrapper class

	class Style : public COleDispatchDriver
	{
	public:
		Style() {}		// Calls COleDispatchDriver default constructor
		Style(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		Style(const Style& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		CString GetNameLocal();
		void SetNameLocal(LPCTSTR lpszNewValue);
		VARIANT GetBaseStyle();
		void SetBaseStyle(VARIANT* newValue);
		CString GetDescription();
		long GetType();
		BOOL GetBuiltIn();
		VARIANT GetNextParagraphStyle();
		void SetNextParagraphStyle(VARIANT* newValue);
		BOOL GetInUse();
		LPDISPATCH GetShading();
		LPDISPATCH GetBorders();
		void SetBorders(LPDISPATCH newValue);
		LPDISPATCH GetParagraphFormat();
		void SetParagraphFormat(LPDISPATCH newValue);
		LPDISPATCH GetFont();
		void SetFont(LPDISPATCH newValue);
		LPDISPATCH GetFrame();
		long GetLanguageID();
		void SetLanguageID(long nNewValue);
		BOOL GetAutomaticallyUpdate();
		void SetAutomaticallyUpdate(BOOL bNewValue);
		LPDISPATCH GetListTemplate();
		long GetListLevelNumber();
		long GetLanguageIDFarEast();
		void SetLanguageIDFarEast(long nNewValue);
		void Delete();
		void LinkToListTemplate(LPDISPATCH ListTemplate, VARIANT* ListLevelNumber);
		long GetNoProofing();
		void SetNoProofing(long nNewValue);
	};
	/////////////////////////////////////////////////////////////////////////////
	// Frames wrapper class

	class Frames : public COleDispatchDriver
	{
	public:
		Frames() {}		// Calls COleDispatchDriver default constructor
		Frames(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		Frames(const Frames& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		LPUNKNOWN Get_NewEnum();
		long GetCount();
		LPDISPATCH Item(long Index);
		LPDISPATCH Add(LPDISPATCH Range);
		void Delete();
	};
	/////////////////////////////////////////////////////////////////////////////
	// Frame wrapper class

	class Frame : public COleDispatchDriver
	{
	public:
		Frame() {}		// Calls COleDispatchDriver default constructor
		Frame(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		Frame(const Frame& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		long GetHeightRule();
		void SetHeightRule(long nNewValue);
		long GetWidthRule();
		void SetWidthRule(long nNewValue);
		float GetHorizontalDistanceFromText();
		void SetHorizontalDistanceFromText(float newValue);
		float GetHeight();
		void SetHeight(float newValue);
		float GetHorizontalPosition();
		void SetHorizontalPosition(float newValue);
		BOOL GetLockAnchor();
		void SetLockAnchor(BOOL bNewValue);
		long GetRelativeHorizontalPosition();
		void SetRelativeHorizontalPosition(long nNewValue);
		long GetRelativeVerticalPosition();
		void SetRelativeVerticalPosition(long nNewValue);
		float GetVerticalDistanceFromText();
		void SetVerticalDistanceFromText(float newValue);
		float GetVerticalPosition();
		void SetVerticalPosition(float newValue);
		float GetWidth();
		void SetWidth(float newValue);
		BOOL GetTextWrap();
		void SetTextWrap(BOOL bNewValue);
		LPDISPATCH GetShading();
		LPDISPATCH GetBorders();
		void SetBorders(LPDISPATCH newValue);
		LPDISPATCH GetRange();
		void Delete();
		void Select();
		void Copy();
		void Cut();
	};
	/////////////////////////////////////////////////////////////////////////////
	// FormFields wrapper class

	class FormFields : public COleDispatchDriver
	{
	public:
		FormFields() {}		// Calls COleDispatchDriver default constructor
		FormFields(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		FormFields(const FormFields& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		long GetCount();
		BOOL GetShaded();
		void SetShaded(BOOL bNewValue);
		LPUNKNOWN Get_NewEnum();
		LPDISPATCH Item(VARIANT* Index);
		LPDISPATCH Add(LPDISPATCH Range, long Type);
	};
	/////////////////////////////////////////////////////////////////////////////
	// FormField wrapper class

	class FormField : public COleDispatchDriver
	{
	public:
		FormField() {}		// Calls COleDispatchDriver default constructor
		FormField(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		FormField(const FormField& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		long GetType();
		CString GetName();
		void SetName(LPCTSTR lpszNewValue);
		CString GetEntryMacro();
		void SetEntryMacro(LPCTSTR lpszNewValue);
		CString GetExitMacro();
		void SetExitMacro(LPCTSTR lpszNewValue);
		BOOL GetOwnHelp();
		void SetOwnHelp(BOOL bNewValue);
		BOOL GetOwnStatus();
		void SetOwnStatus(BOOL bNewValue);
		CString GetHelpText();
		void SetHelpText(LPCTSTR lpszNewValue);
		CString GetStatusText();
		void SetStatusText(LPCTSTR lpszNewValue);
		BOOL GetEnabled();
		void SetEnabled(BOOL bNewValue);
		CString GetResult();
		void SetResult(LPCTSTR lpszNewValue);
		LPDISPATCH GetTextInput();
		LPDISPATCH GetCheckBox();
		LPDISPATCH GetDropDown();
		LPDISPATCH GetNext();
		LPDISPATCH GetPrevious();
		BOOL GetCalculateOnExit();
		void SetCalculateOnExit(BOOL bNewValue);
		LPDISPATCH GetRange();
		void Select();
		void Copy();
		void Cut();
		void Delete();
	};
	/////////////////////////////////////////////////////////////////////////////
	// TextInput wrapper class

	class TextInput : public COleDispatchDriver
	{
	public:
		TextInput() {}		// Calls COleDispatchDriver default constructor
		TextInput(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		TextInput(const TextInput& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		BOOL GetValid();
		CString GetDefault();
		void SetDefault(LPCTSTR lpszNewValue);
		long GetType();
		CString GetFormat();
		long GetWidth();
		void SetWidth(long nNewValue);
		void Clear();
		void EditType(long Type, VARIANT* Default, VARIANT* Format, VARIANT* Enabled);
	};
	/////////////////////////////////////////////////////////////////////////////
	// CheckBox wrapper class

	class CheckBox : public COleDispatchDriver
	{
	public:
		CheckBox() {}		// Calls COleDispatchDriver default constructor
		CheckBox(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CheckBox(const CheckBox& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		BOOL GetValid();
		BOOL GetAutoSize();
		void SetAutoSize(BOOL bNewValue);
		float GetSize();
		void SetSize(float newValue);
		BOOL GetDefault();
		void SetDefault(BOOL bNewValue);
		BOOL GetValue();
		void SetValue(BOOL bNewValue);
	};
	/////////////////////////////////////////////////////////////////////////////
	// DropDown wrapper class

	class DropDown : public COleDispatchDriver
	{
	public:
		DropDown() {}		// Calls COleDispatchDriver default constructor
		DropDown(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		DropDown(const DropDown& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		BOOL GetValid();
		long GetDefault();
		void SetDefault(long nNewValue);
		long GetValue();
		void SetValue(long nNewValue);
		LPDISPATCH GetListEntries();
	};
	/////////////////////////////////////////////////////////////////////////////
	// ListEntries wrapper class

	class ListEntries : public COleDispatchDriver
	{
	public:
		ListEntries() {}		// Calls COleDispatchDriver default constructor
		ListEntries(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		ListEntries(const ListEntries& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		LPUNKNOWN Get_NewEnum();
		long GetCount();
		LPDISPATCH Item(VARIANT* Index);
		LPDISPATCH Add(LPCTSTR Name, VARIANT* Index);
		void Clear();
	};
	/////////////////////////////////////////////////////////////////////////////
	// ListEntry wrapper class

	class ListEntry : public COleDispatchDriver
	{
	public:
		ListEntry() {}		// Calls COleDispatchDriver default constructor
		ListEntry(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		ListEntry(const ListEntry& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		long GetIndex();
		CString GetName();
		void SetName(LPCTSTR lpszNewValue);
		void Delete();
	};
	/////////////////////////////////////////////////////////////////////////////
	// TablesOfFigures wrapper class

	class TablesOfFigures : public COleDispatchDriver
	{
	public:
		TablesOfFigures() {}		// Calls COleDispatchDriver default constructor
		TablesOfFigures(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		TablesOfFigures(const TablesOfFigures& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		LPUNKNOWN Get_NewEnum();
		long GetCount();
		long GetFormat();
		void SetFormat(long nNewValue);
		LPDISPATCH Item(long Index);
		LPDISPATCH MarkEntry(LPDISPATCH Range, VARIANT* Entry, VARIANT* EntryAutoText, VARIANT* TableID, VARIANT* Level);
		LPDISPATCH Add(LPDISPATCH Range, VARIANT* Caption, VARIANT* IncludeLabel, VARIANT* UseHeadingStyles, VARIANT* UpperHeadingLevel, VARIANT* LowerHeadingLevel, VARIANT* UseFields, VARIANT* TableID, VARIANT* RightAlignPageNumbers, 
			VARIANT* IncludePageNumbers, VARIANT* AddedStyles, VARIANT* UseHyperlinks, VARIANT* HidePageNumbersInWeb);
	};
	/////////////////////////////////////////////////////////////////////////////
	// TableOfFigures wrapper class

	class TableOfFigures : public COleDispatchDriver
	{
	public:
		TableOfFigures() {}		// Calls COleDispatchDriver default constructor
		TableOfFigures(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		TableOfFigures(const TableOfFigures& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		CString GetCaption();
		void SetCaption(LPCTSTR lpszNewValue);
		BOOL GetIncludeLabel();
		void SetIncludeLabel(BOOL bNewValue);
		BOOL GetRightAlignPageNumbers();
		void SetRightAlignPageNumbers(BOOL bNewValue);
		BOOL GetUseHeadingStyles();
		void SetUseHeadingStyles(BOOL bNewValue);
		long GetLowerHeadingLevel();
		void SetLowerHeadingLevel(long nNewValue);
		long GetUpperHeadingLevel();
		void SetUpperHeadingLevel(long nNewValue);
		BOOL GetIncludePageNumbers();
		void SetIncludePageNumbers(BOOL bNewValue);
		LPDISPATCH GetRange();
		BOOL GetUseFields();
		void SetUseFields(BOOL bNewValue);
		CString GetTableID();
		void SetTableID(LPCTSTR lpszNewValue);
		LPDISPATCH GetHeadingStyles();
		long GetTabLeader();
		void SetTabLeader(long nNewValue);
		void Delete();
		void UpdatePageNumbers();
		void Update();
		BOOL GetUseHyperlinks();
		void SetUseHyperlinks(BOOL bNewValue);
		BOOL GetHidePageNumbersInWeb();
		void SetHidePageNumbersInWeb(BOOL bNewValue);
	};
	/////////////////////////////////////////////////////////////////////////////
	// MailMerge wrapper class

	class MailMerge : public COleDispatchDriver
	{
	public:
		MailMerge() {}		// Calls COleDispatchDriver default constructor
		MailMerge(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		MailMerge(const MailMerge& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		long GetMainDocumentType();
		void SetMainDocumentType(long nNewValue);
		long GetState();
		long GetDestination();
		void SetDestination(long nNewValue);
		LPDISPATCH GetDataSource();
		LPDISPATCH GetFields();
		long GetViewMailMergeFieldCodes();
		void SetViewMailMergeFieldCodes(long nNewValue);
		BOOL GetSuppressBlankLines();
		void SetSuppressBlankLines(BOOL bNewValue);
		BOOL GetMailAsAttachment();
		void SetMailAsAttachment(BOOL bNewValue);
		CString GetMailAddressFieldName();
		void SetMailAddressFieldName(LPCTSTR lpszNewValue);
		CString GetMailSubject();
		void SetMailSubject(LPCTSTR lpszNewValue);
		void CreateDataSource(VARIANT* Name, VARIANT* PasswordDocument, VARIANT* WritePasswordDocument, VARIANT* HeaderRecord, VARIANT* MSQuery, VARIANT* SQLStatement, VARIANT* SQLStatement1, VARIANT* Connection, VARIANT* LinkToSource);
		void CreateHeaderSource(LPCTSTR Name, VARIANT* PasswordDocument, VARIANT* WritePasswordDocument, VARIANT* HeaderRecord);
		void OpenDataSource(LPCTSTR Name, VARIANT* Format, VARIANT* ConfirmConversions, VARIANT* ReadOnly, VARIANT* LinkToSource, VARIANT* AddToRecentFiles, VARIANT* PasswordDocument, VARIANT* PasswordTemplate, VARIANT* Revert, 
			VARIANT* WritePasswordDocument, VARIANT* WritePasswordTemplate, VARIANT* Connection, VARIANT* SQLStatement, VARIANT* SQLStatement1);
		void OpenHeaderSource(LPCTSTR Name, VARIANT* Format, VARIANT* ConfirmConversions, VARIANT* ReadOnly, VARIANT* AddToRecentFiles, VARIANT* PasswordDocument, VARIANT* PasswordTemplate, VARIANT* Revert, VARIANT* WritePasswordDocument, 
			VARIANT* WritePasswordTemplate);
		void Execute(VARIANT* Pause);
		void Check();
		void EditDataSource();
		void EditHeaderSource();
		void EditMainDocument();
		void UseAddressBook(LPCTSTR Type);
	};
	/////////////////////////////////////////////////////////////////////////////
	// MailMergeFields wrapper class

	class MailMergeFields : public COleDispatchDriver
	{
	public:
		MailMergeFields() {}		// Calls COleDispatchDriver default constructor
		MailMergeFields(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		MailMergeFields(const MailMergeFields& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		LPUNKNOWN Get_NewEnum();
		long GetCount();
		LPDISPATCH Item(long Index);
		LPDISPATCH Add(LPDISPATCH Range, LPCTSTR Name);
		LPDISPATCH AddAsk(LPDISPATCH Range, LPCTSTR Name, VARIANT* Prompt, VARIANT* DefaultAskText, VARIANT* AskOnce);
		LPDISPATCH AddFillIn(LPDISPATCH Range, VARIANT* Prompt, VARIANT* DefaultFillInText, VARIANT* AskOnce);
		LPDISPATCH AddIf(LPDISPATCH Range, LPCTSTR MergeField, long Comparison, VARIANT* CompareTo, VARIANT* TrueAutoText, VARIANT* TrueText, VARIANT* FalseAutoText, VARIANT* FalseText);
		LPDISPATCH AddMergeRec(LPDISPATCH Range);
		LPDISPATCH AddMergeSeq(LPDISPATCH Range);
		LPDISPATCH AddNext(LPDISPATCH Range);
		LPDISPATCH AddNextIf(LPDISPATCH Range, LPCTSTR MergeField, long Comparison, VARIANT* CompareTo);
		LPDISPATCH AddSet(LPDISPATCH Range, LPCTSTR Name, VARIANT* ValueText, VARIANT* ValueAutoText);
		LPDISPATCH AddSkipIf(LPDISPATCH Range, LPCTSTR MergeField, long Comparison, VARIANT* CompareTo);
	};
	/////////////////////////////////////////////////////////////////////////////
	// MailMergeField wrapper class

	class MailMergeField : public COleDispatchDriver
	{
	public:
		MailMergeField() {}		// Calls COleDispatchDriver default constructor
		MailMergeField(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		MailMergeField(const MailMergeField& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		long GetType();
		BOOL GetLocked();
		void SetLocked(BOOL bNewValue);
		LPDISPATCH GetCode();
		void SetCode(LPDISPATCH newValue);
		LPDISPATCH GetNext();
		LPDISPATCH GetPrevious();
		void Select();
		void Copy();
		void Cut();
		void Delete();
	};
	/////////////////////////////////////////////////////////////////////////////
	// MailMergeDataSource wrapper class

	class MailMergeDataSource : public COleDispatchDriver
	{
	public:
		MailMergeDataSource() {}		// Calls COleDispatchDriver default constructor
		MailMergeDataSource(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		MailMergeDataSource(const MailMergeDataSource& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		CString GetName();
		CString GetHeaderSourceName();
		long GetType();
		long GetHeaderSourceType();
		CString GetConnectString();
		CString GetQueryString();
		void SetQueryString(LPCTSTR lpszNewValue);
		long GetActiveRecord();
		void SetActiveRecord(long nNewValue);
		long GetFirstRecord();
		void SetFirstRecord(long nNewValue);
		long GetLastRecord();
		void SetLastRecord(long nNewValue);
		LPDISPATCH GetFieldNames();
		LPDISPATCH GetDataFields();
		BOOL FindRecord(LPCTSTR FindText, LPCTSTR Field);
	};
	/////////////////////////////////////////////////////////////////////////////
	// MailMergeFieldNames wrapper class

	class MailMergeFieldNames : public COleDispatchDriver
	{
	public:
		MailMergeFieldNames() {}		// Calls COleDispatchDriver default constructor
		MailMergeFieldNames(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		MailMergeFieldNames(const MailMergeFieldNames& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		LPUNKNOWN Get_NewEnum();
		long GetCount();
		LPDISPATCH Item(VARIANT* Index);
	};
	/////////////////////////////////////////////////////////////////////////////
	// MailMergeFieldName wrapper class

	class MailMergeFieldName : public COleDispatchDriver
	{
	public:
		MailMergeFieldName() {}		// Calls COleDispatchDriver default constructor
		MailMergeFieldName(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		MailMergeFieldName(const MailMergeFieldName& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		CString GetName();
		long GetIndex();
	};
	/////////////////////////////////////////////////////////////////////////////
	// MailMergeDataFields wrapper class

	class MailMergeDataFields : public COleDispatchDriver
	{
	public:
		MailMergeDataFields() {}		// Calls COleDispatchDriver default constructor
		MailMergeDataFields(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		MailMergeDataFields(const MailMergeDataFields& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		LPUNKNOWN Get_NewEnum();
		long GetCount();
		LPDISPATCH Item(VARIANT* Index);
	};
	/////////////////////////////////////////////////////////////////////////////
	// MailMergeDataField wrapper class

	class MailMergeDataField : public COleDispatchDriver
	{
	public:
		MailMergeDataField() {}		// Calls COleDispatchDriver default constructor
		MailMergeDataField(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		MailMergeDataField(const MailMergeDataField& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		CString GetValue();
		CString GetName();
		long GetIndex();
	};
	/////////////////////////////////////////////////////////////////////////////
	// Envelope wrapper class

	class Envelope : public COleDispatchDriver
	{
	public:
		Envelope() {}		// Calls COleDispatchDriver default constructor
		Envelope(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		Envelope(const Envelope& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		LPDISPATCH GetAddress();
		LPDISPATCH GetReturnAddress();
		BOOL GetDefaultPrintBarCode();
		void SetDefaultPrintBarCode(BOOL bNewValue);
		BOOL GetDefaultPrintFIMA();
		void SetDefaultPrintFIMA(BOOL bNewValue);
		float GetDefaultHeight();
		void SetDefaultHeight(float newValue);
		float GetDefaultWidth();
		void SetDefaultWidth(float newValue);
		CString GetDefaultSize();
		void SetDefaultSize(LPCTSTR lpszNewValue);
		BOOL GetDefaultOmitReturnAddress();
		void SetDefaultOmitReturnAddress(BOOL bNewValue);
		long GetFeedSource();
		void SetFeedSource(long nNewValue);
		float GetAddressFromLeft();
		void SetAddressFromLeft(float newValue);
		float GetAddressFromTop();
		void SetAddressFromTop(float newValue);
		float GetReturnAddressFromLeft();
		void SetReturnAddressFromLeft(float newValue);
		float GetReturnAddressFromTop();
		void SetReturnAddressFromTop(float newValue);
		LPDISPATCH GetAddressStyle();
		LPDISPATCH GetReturnAddressStyle();
		long GetDefaultOrientation();
		void SetDefaultOrientation(long nNewValue);
		BOOL GetDefaultFaceUp();
		void SetDefaultFaceUp(BOOL bNewValue);
		void Insert(VARIANT* ExtractAddress, VARIANT* Address, VARIANT* AutoText, VARIANT* OmitReturnAddress, VARIANT* ReturnAddress, VARIANT* ReturnAutoText, VARIANT* PrintBarCode, VARIANT* PrintFIMA, VARIANT* Size, VARIANT* Height, VARIANT* Width, 
			VARIANT* FeedSource, VARIANT* AddressFromLeft, VARIANT* AddressFromTop, VARIANT* ReturnAddressFromLeft, VARIANT* ReturnAddressFromTop, VARIANT* DefaultFaceUp, VARIANT* DefaultOrientation);
		void PrintOut(VARIANT* ExtractAddress, VARIANT* Address, VARIANT* AutoText, VARIANT* OmitReturnAddress, VARIANT* ReturnAddress, VARIANT* ReturnAutoText, VARIANT* PrintBarCode, VARIANT* PrintFIMA, VARIANT* Size, VARIANT* Height, 
			VARIANT* Width, VARIANT* FeedSource, VARIANT* AddressFromLeft, VARIANT* AddressFromTop, VARIANT* ReturnAddressFromLeft, VARIANT* ReturnAddressFromTop, VARIANT* DefaultFaceUp, VARIANT* DefaultOrientation);
		void UpdateDocument();
	};
	/////////////////////////////////////////////////////////////////////////////
	// MailingLabel wrapper class

	class MailingLabel : public COleDispatchDriver
	{
	public:
		MailingLabel() {}		// Calls COleDispatchDriver default constructor
		MailingLabel(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		MailingLabel(const MailingLabel& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		BOOL GetDefaultPrintBarCode();
		void SetDefaultPrintBarCode(BOOL bNewValue);
		long GetDefaultLaserTray();
		void SetDefaultLaserTray(long nNewValue);
		LPDISPATCH GetCustomLabels();
		CString GetDefaultLabelName();
		void SetDefaultLabelName(LPCTSTR lpszNewValue);
		LPDISPATCH CreateNewDocument(VARIANT* Name, VARIANT* Address, VARIANT* AutoText, VARIANT* ExtractAddress, VARIANT* LaserTray);
		void PrintOut(VARIANT* Name, VARIANT* Address, VARIANT* ExtractAddress, VARIANT* LaserTray, VARIANT* SingleLabel, VARIANT* Row, VARIANT* Column);
	};
	/////////////////////////////////////////////////////////////////////////////
	// CustomLabels wrapper class

	class CustomLabels : public COleDispatchDriver
	{
	public:
		CustomLabels() {}		// Calls COleDispatchDriver default constructor
		CustomLabels(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CustomLabels(const CustomLabels& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		LPUNKNOWN Get_NewEnum();
		long GetCount();
		LPDISPATCH Item(VARIANT* Index);
		LPDISPATCH Add(LPCTSTR Name, VARIANT* DotMatrix);
	};
	/////////////////////////////////////////////////////////////////////////////
	// CustomLabel wrapper class

	class CustomLabel : public COleDispatchDriver
	{
	public:
		CustomLabel() {}		// Calls COleDispatchDriver default constructor
		CustomLabel(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CustomLabel(const CustomLabel& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		long GetIndex();
		CString GetName();
		void SetName(LPCTSTR lpszNewValue);
		float GetTopMargin();
		void SetTopMargin(float newValue);
		float GetSideMargin();
		void SetSideMargin(float newValue);
		float GetHeight();
		void SetHeight(float newValue);
		float GetWidth();
		void SetWidth(float newValue);
		float GetVerticalPitch();
		void SetVerticalPitch(float newValue);
		float GetHorizontalPitch();
		void SetHorizontalPitch(float newValue);
		long GetNumberAcross();
		void SetNumberAcross(long nNewValue);
		long GetNumberDown();
		void SetNumberDown(long nNewValue);
		BOOL GetDotMatrix();
		long GetPageSize();
		void SetPageSize(long nNewValue);
		BOOL GetValid();
		void Delete();
	};
	/////////////////////////////////////////////////////////////////////////////
	// TablesOfContents wrapper class

	class TablesOfContents : public COleDispatchDriver
	{
	public:
		TablesOfContents() {}		// Calls COleDispatchDriver default constructor
		TablesOfContents(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		TablesOfContents(const TablesOfContents& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		LPUNKNOWN Get_NewEnum();
		long GetCount();
		long GetFormat();
		void SetFormat(long nNewValue);
		LPDISPATCH Item(long Index);
		LPDISPATCH MarkEntry(LPDISPATCH Range, VARIANT* Entry, VARIANT* EntryAutoText, VARIANT* TableID, VARIANT* Level);
		LPDISPATCH Add(LPDISPATCH Range, VARIANT* UseHeadingStyles, VARIANT* UpperHeadingLevel, VARIANT* LowerHeadingLevel, VARIANT* UseFields, VARIANT* TableID, VARIANT* RightAlignPageNumbers, VARIANT* IncludePageNumbers, VARIANT* AddedStyles, 
			VARIANT* UseHyperlinks, VARIANT* HidePageNumbersInWeb);
	};
	/////////////////////////////////////////////////////////////////////////////
	// TableOfContents wrapper class

	class TableOfContents : public COleDispatchDriver
	{
	public:
		TableOfContents() {}		// Calls COleDispatchDriver default constructor
		TableOfContents(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		TableOfContents(const TableOfContents& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		BOOL GetUseHeadingStyles();
		void SetUseHeadingStyles(BOOL bNewValue);
		BOOL GetUseFields();
		void SetUseFields(BOOL bNewValue);
		long GetUpperHeadingLevel();
		void SetUpperHeadingLevel(long nNewValue);
		long GetLowerHeadingLevel();
		void SetLowerHeadingLevel(long nNewValue);
		CString GetTableID();
		void SetTableID(LPCTSTR lpszNewValue);
		LPDISPATCH GetHeadingStyles();
		BOOL GetRightAlignPageNumbers();
		void SetRightAlignPageNumbers(BOOL bNewValue);
		BOOL GetIncludePageNumbers();
		void SetIncludePageNumbers(BOOL bNewValue);
		LPDISPATCH GetRange();
		long GetTabLeader();
		void SetTabLeader(long nNewValue);
		void Delete();
		void UpdatePageNumbers();
		void Update();
		BOOL GetUseHyperlinks();
		void SetUseHyperlinks(BOOL bNewValue);
		BOOL GetHidePageNumbersInWeb();
		void SetHidePageNumbersInWeb(BOOL bNewValue);
	};
	/////////////////////////////////////////////////////////////////////////////
	// TablesOfAuthorities wrapper class

	class TablesOfAuthorities : public COleDispatchDriver
	{
	public:
		TablesOfAuthorities() {}		// Calls COleDispatchDriver default constructor
		TablesOfAuthorities(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		TablesOfAuthorities(const TablesOfAuthorities& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		LPUNKNOWN Get_NewEnum();
		long GetCount();
		long GetFormat();
		void SetFormat(long nNewValue);
		LPDISPATCH Item(long Index);
		LPDISPATCH Add(LPDISPATCH Range, VARIANT* Category, VARIANT* Bookmark, VARIANT* Passim, VARIANT* KeepEntryFormatting, VARIANT* Separator, VARIANT* IncludeSequenceName, VARIANT* EntrySeparator, VARIANT* PageRangeSeparator, 
			VARIANT* IncludeCategoryHeader, VARIANT* PageNumberSeparator);
		void NextCitation(LPCTSTR ShortCitation);
		LPDISPATCH MarkCitation(LPDISPATCH Range, LPCTSTR ShortCitation, VARIANT* LongCitation, VARIANT* LongCitationAutoText, VARIANT* Category);
		void MarkAllCitations(LPCTSTR ShortCitation, VARIANT* LongCitation, VARIANT* LongCitationAutoText, VARIANT* Category);
	};
	/////////////////////////////////////////////////////////////////////////////
	// TableOfAuthorities wrapper class

	class TableOfAuthorities : public COleDispatchDriver
	{
	public:
		TableOfAuthorities() {}		// Calls COleDispatchDriver default constructor
		TableOfAuthorities(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		TableOfAuthorities(const TableOfAuthorities& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		BOOL GetPassim();
		void SetPassim(BOOL bNewValue);
		BOOL GetKeepEntryFormatting();
		void SetKeepEntryFormatting(BOOL bNewValue);
		long GetCategory();
		void SetCategory(long nNewValue);
		CString GetBookmark();
		void SetBookmark(LPCTSTR lpszNewValue);
		CString GetSeparator();
		void SetSeparator(LPCTSTR lpszNewValue);
		CString GetIncludeSequenceName();
		void SetIncludeSequenceName(LPCTSTR lpszNewValue);
		CString GetEntrySeparator();
		void SetEntrySeparator(LPCTSTR lpszNewValue);
		CString GetPageRangeSeparator();
		void SetPageRangeSeparator(LPCTSTR lpszNewValue);
		BOOL GetIncludeCategoryHeader();
		void SetIncludeCategoryHeader(BOOL bNewValue);
		CString GetPageNumberSeparator();
		void SetPageNumberSeparator(LPCTSTR lpszNewValue);
		LPDISPATCH GetRange();
		long GetTabLeader();
		void SetTabLeader(long nNewValue);
		void Delete();
		void Update();
	};
	/////////////////////////////////////////////////////////////////////////////
	// Dialogs wrapper class

	class Dialogs : public COleDispatchDriver
	{
	public:
		Dialogs() {}		// Calls COleDispatchDriver default constructor
		Dialogs(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		Dialogs(const Dialogs& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		LPUNKNOWN Get_NewEnum();
		long GetCount();
		LPDISPATCH Item(long Index);
	};
	/////////////////////////////////////////////////////////////////////////////
	// Dialog wrapper class

	class Dialog : public COleDispatchDriver
	{
	public:
		Dialog() {}		// Calls COleDispatchDriver default constructor
		Dialog(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		Dialog(const Dialog& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		long GetDefaultTab();
		void SetDefaultTab(long nNewValue);
		long GetType();
		long Show(VARIANT* TimeOut);
		long Display(VARIANT* TimeOut);
		void Execute();
		void Update();
		CString GetCommandName();
	};
	/////////////////////////////////////////////////////////////////////////////
	// PageSetup wrapper class

	class PageSetup : public COleDispatchDriver
	{
	public:
		PageSetup() {}		// Calls COleDispatchDriver default constructor
		PageSetup(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		PageSetup(const PageSetup& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		float GetTopMargin();
		void SetTopMargin(float newValue);
		float GetBottomMargin();
		void SetBottomMargin(float newValue);
		float GetLeftMargin();
		void SetLeftMargin(float newValue);
		float GetRightMargin();
		void SetRightMargin(float newValue);
		float GetGutter();
		void SetGutter(float newValue);
		float GetPageWidth();
		void SetPageWidth(float newValue);
		float GetPageHeight();
		void SetPageHeight(float newValue);
		long GetOrientation();
		void SetOrientation(long nNewValue);
		long GetFirstPageTray();
		void SetFirstPageTray(long nNewValue);
		long GetOtherPagesTray();
		void SetOtherPagesTray(long nNewValue);
		long GetVerticalAlignment();
		void SetVerticalAlignment(long nNewValue);
		long GetMirrorMargins();
		void SetMirrorMargins(long nNewValue);
		float GetHeaderDistance();
		void SetHeaderDistance(float newValue);
		float GetFooterDistance();
		void SetFooterDistance(float newValue);
		long GetSectionStart();
		void SetSectionStart(long nNewValue);
		long GetOddAndEvenPagesHeaderFooter();
		void SetOddAndEvenPagesHeaderFooter(long nNewValue);
		long GetDifferentFirstPageHeaderFooter();
		void SetDifferentFirstPageHeaderFooter(long nNewValue);
		long GetSuppressEndnotes();
		void SetSuppressEndnotes(long nNewValue);
		LPDISPATCH GetLineNumbering();
		void SetLineNumbering(LPDISPATCH newValue);
		LPDISPATCH GetTextColumns();
		void SetTextColumns(LPDISPATCH newValue);
		long GetPaperSize();
		void SetPaperSize(long nNewValue);
		BOOL GetTwoPagesOnOne();
		void SetTwoPagesOnOne(BOOL bNewValue);
		float GetCharsLine();
		void SetCharsLine(float newValue);
		float GetLinesPage();
		void SetLinesPage(float newValue);
		BOOL GetShowGrid();
		void SetShowGrid(BOOL bNewValue);
		void TogglePortrait();
		void SetAsTemplateDefault();
		long GetGutterStyle();
		void SetGutterStyle(long nNewValue);
		long GetSectionDirection();
		void SetSectionDirection(long nNewValue);
		long GetLayoutMode();
		void SetLayoutMode(long nNewValue);
		long GetGutterPos();
		void SetGutterPos(long nNewValue);
	};
	/////////////////////////////////////////////////////////////////////////////
	// LineNumbering wrapper class

	class LineNumbering : public COleDispatchDriver
	{
	public:
		LineNumbering() {}		// Calls COleDispatchDriver default constructor
		LineNumbering(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		LineNumbering(const LineNumbering& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		long GetRestartMode();
		void SetRestartMode(long nNewValue);
		long GetStartingNumber();
		void SetStartingNumber(long nNewValue);
		float GetDistanceFromText();
		void SetDistanceFromText(float newValue);
		long GetCountBy();
		void SetCountBy(long nNewValue);
		long GetActive();
		void SetActive(long nNewValue);
	};
	/////////////////////////////////////////////////////////////////////////////
	// TextColumns wrapper class

	class TextColumns : public COleDispatchDriver
	{
	public:
		TextColumns() {}		// Calls COleDispatchDriver default constructor
		TextColumns(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		TextColumns(const TextColumns& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPUNKNOWN Get_NewEnum();
		long GetCount();
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		long GetEvenlySpaced();
		void SetEvenlySpaced(long nNewValue);
		long GetLineBetween();
		void SetLineBetween(long nNewValue);
		float GetWidth();
		void SetWidth(float newValue);
		float GetSpacing();
		void SetSpacing(float newValue);
		LPDISPATCH Item(long Index);
		LPDISPATCH Add(VARIANT* Width, VARIANT* Spacing, VARIANT* EvenlySpaced);
		void SetCount(long NumColumns);
		long GetFlowDirection();
		void SetFlowDirection(long nNewValue);
	};
	/////////////////////////////////////////////////////////////////////////////
	// TextColumn wrapper class

	class TextColumn : public COleDispatchDriver
	{
	public:
		TextColumn() {}		// Calls COleDispatchDriver default constructor
		TextColumn(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		TextColumn(const TextColumn& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		float GetWidth();
		void SetWidth(float newValue);
		float GetSpaceAfter();
		void SetSpaceAfter(float newValue);
	};
	/////////////////////////////////////////////////////////////////////////////
	// Selection wrapper class

	class Selection : public COleDispatchDriver
	{
	public:
		Selection() {}		// Calls COleDispatchDriver default constructor
		Selection(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		Selection(const Selection& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		CString GetText();
		void SetText(LPCTSTR lpszNewValue);
		LPDISPATCH GetFormattedText();
		void SetFormattedText(LPDISPATCH newValue);
		long GetStart();
		void SetStart(long nNewValue);
		long GetEnd();
		void SetEnd(long nNewValue);
		LPDISPATCH GetFont();
		void SetFont(LPDISPATCH newValue);
		long GetType();
		long GetStoryType();
		VARIANT GetStyle();
		void SetStyle(VARIANT* newValue);
		LPDISPATCH GetTables();
		LPDISPATCH GetWords();
		LPDISPATCH GetSentences();
		LPDISPATCH GetCharacters();
		LPDISPATCH GetFootnotes();
		LPDISPATCH GetEndnotes();
		LPDISPATCH GetComments();
		LPDISPATCH GetCells();
		LPDISPATCH GetSections();
		LPDISPATCH GetParagraphs();
		LPDISPATCH GetBorders();
		void SetBorders(LPDISPATCH newValue);
		LPDISPATCH GetShading();
		LPDISPATCH GetFields();
		LPDISPATCH GetFormFields();
		LPDISPATCH GetFrames();
		LPDISPATCH GetParagraphFormat();
		void SetParagraphFormat(LPDISPATCH newValue);
		LPDISPATCH GetPageSetup();
		void SetPageSetup(LPDISPATCH newValue);
		LPDISPATCH GetBookmarks();
		long GetStoryLength();
		long GetLanguageID();
		void SetLanguageID(long nNewValue);
		long GetLanguageIDFarEast();
		void SetLanguageIDFarEast(long nNewValue);
		long GetLanguageIDOther();
		void SetLanguageIDOther(long nNewValue);
		LPDISPATCH GetHyperlinks();
		LPDISPATCH GetColumns();
		LPDISPATCH GetRows();
		LPDISPATCH GetHeaderFooter();
		BOOL GetIsEndOfRowMark();
		long GetBookmarkID();
		long GetPreviousBookmarkID();
		LPDISPATCH GetFind();
		LPDISPATCH GetRange();
		VARIANT GetInformation(long Type);
		long GetFlags();
		void SetFlags(long nNewValue);
		BOOL GetActive();
		BOOL GetStartIsActive();
		void SetStartIsActive(BOOL bNewValue);
		BOOL GetIPAtEndOfLine();
		BOOL GetExtendMode();
		void SetExtendMode(BOOL bNewValue);
		BOOL GetColumnSelectMode();
		void SetColumnSelectMode(BOOL bNewValue);
		long GetOrientation();
		void SetOrientation(long nNewValue);
		LPDISPATCH GetInlineShapes();
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		LPDISPATCH GetDocument();
		LPDISPATCH GetShapeRange();
		void Select();
		void SetRange(long Start, long End);
		void Collapse(VARIANT* Direction);
		void InsertBefore(LPCTSTR Text);
		void InsertAfter(LPCTSTR Text);
		LPDISPATCH Next(VARIANT* Unit, VARIANT* Count);
		LPDISPATCH Previous(VARIANT* Unit, VARIANT* Count);
		long StartOf(VARIANT* Unit, VARIANT* Extend);
		long EndOf(VARIANT* Unit, VARIANT* Extend);
		long Move(VARIANT* Unit, VARIANT* Count);
		long MoveStart(VARIANT* Unit, VARIANT* Count);
		long MoveEnd(VARIANT* Unit, VARIANT* Count);
		long MoveWhile(VARIANT* Cset, VARIANT* Count);
		long MoveStartWhile(VARIANT* Cset, VARIANT* Count);
		long MoveEndWhile(VARIANT* Cset, VARIANT* Count);
		long MoveUntil(VARIANT* Cset, VARIANT* Count);
		long MoveStartUntil(VARIANT* Cset, VARIANT* Count);
		long MoveEndUntil(VARIANT* Cset, VARIANT* Count);
		void Cut();
		void Copy();
		void Paste();
		void InsertBreak(VARIANT* Type);
		void InsertFile(LPCTSTR FileName, VARIANT* Range, VARIANT* ConfirmConversions, VARIANT* Link, VARIANT* Attachment);
		BOOL InStory(LPDISPATCH Range);
		BOOL InRange(LPDISPATCH Range);
		long Delete(VARIANT* Unit, VARIANT* Count);
		long Expand(VARIANT* Unit);
		void InsertParagraph();
		void InsertParagraphAfter();
		void InsertSymbol(long CharacterNumber, VARIANT* Font, VARIANT* Unicode, VARIANT* Bias);
		void InsertCrossReference(VARIANT* ReferenceType, long ReferenceKind, VARIANT* ReferenceItem, VARIANT* InsertAsHyperlink, VARIANT* IncludePosition);
		void InsertCaption(VARIANT* Label, VARIANT* Title, VARIANT* TitleAutoText, VARIANT* Position);
		void CopyAsPicture();
		void SortAscending();
		void SortDescending();
		BOOL IsEqual(LPDISPATCH Range);
		float Calculate();
		LPDISPATCH GoTo(VARIANT* What, VARIANT* Which, VARIANT* Count, VARIANT* Name);
		LPDISPATCH GoToNext(long What);
		LPDISPATCH GoToPrevious(long What);
		void PasteSpecial(VARIANT* IconIndex, VARIANT* Link, VARIANT* Placement, VARIANT* DisplayAsIcon, VARIANT* DataType, VARIANT* IconFileName, VARIANT* IconLabel);
		LPDISPATCH PreviousField();
		LPDISPATCH NextField();
		void InsertParagraphBefore();
		void InsertCells(VARIANT* ShiftCells);
		void Extend(VARIANT* Character);
		void Shrink();
		long MoveLeft(VARIANT* Unit, VARIANT* Count, VARIANT* Extend);
		long MoveRight(VARIANT* Unit, VARIANT* Count, VARIANT* Extend);
		long MoveUp(VARIANT* Unit, VARIANT* Count, VARIANT* Extend);
		long MoveDown(VARIANT* Unit, VARIANT* Count, VARIANT* Extend);
		long HomeKey(VARIANT* Unit, VARIANT* Extend);
		long EndKey(VARIANT* Unit, VARIANT* Extend);
		void EscapeKey();
		void TypeText(LPCTSTR Text);
		void CopyFormat();
		void PasteFormat();
		void TypeParagraph();
		void TypeBackspace();
		void NextSubdocument();
		void PreviousSubdocument();
		void SelectColumn();
		void SelectCurrentFont();
		void SelectCurrentAlignment();
		void SelectCurrentSpacing();
		void SelectCurrentIndent();
		void SelectCurrentTabs();
		void SelectCurrentColor();
		void CreateTextbox();
		void WholeStory();
		void SelectRow();
		void SplitTable();
		void InsertRows(VARIANT* NumRows);
		void InsertColumns();
		void InsertFormula(VARIANT* Formula, VARIANT* NumberFormat);
		LPDISPATCH NextRevision(VARIANT* Wrap);
		LPDISPATCH PreviousRevision(VARIANT* Wrap);
		void PasteAsNestedTable();
		LPDISPATCH CreateAutoTextEntry(LPCTSTR Name, LPCTSTR StyleName);
		void DetectLanguage();
		void SelectCell();
		void InsertRowsBelow(VARIANT* NumRows);
		void InsertColumnsRight();
		void InsertRowsAbove(VARIANT* NumRows);
		void RtlRun();
		void LtrRun();
		void BoldRun();
		void ItalicRun();
		void RtlPara();
		void LtrPara();
		void InsertDateTime(VARIANT* DateTimeFormat, VARIANT* InsertAsField, VARIANT* InsertAsFullWidth, VARIANT* DateLanguage, VARIANT* CalendarType);
		void Sort(VARIANT* ExcludeHeader, VARIANT* FieldNumber, VARIANT* SortFieldType, VARIANT* SortOrder, VARIANT* FieldNumber2, VARIANT* SortFieldType2, VARIANT* SortOrder2, VARIANT* FieldNumber3, VARIANT* SortFieldType3, VARIANT* SortOrder3, 
			VARIANT* SortColumn, VARIANT* Separator, VARIANT* CaseSensitive, VARIANT* BidiSort, VARIANT* IgnoreThe, VARIANT* IgnoreKashida, VARIANT* IgnoreDiacritics, VARIANT* IgnoreHe, VARIANT* LanguageID);
		LPDISPATCH ConvertToTable(VARIANT* Separator, VARIANT* NumRows, VARIANT* NumColumns, VARIANT* InitialColumnWidth, VARIANT* Format, VARIANT* ApplyBorders, VARIANT* ApplyShading, VARIANT* ApplyFont, VARIANT* ApplyColor, 
			VARIANT* ApplyHeadingRows, VARIANT* ApplyLastRow, VARIANT* ApplyFirstColumn, VARIANT* ApplyLastColumn, VARIANT* AutoFit, VARIANT* AutoFitBehavior, VARIANT* DefaultTableBehavior);
		long GetNoProofing();
		void SetNoProofing(long nNewValue);
		LPDISPATCH GetTopLevelTables();
		BOOL GetLanguageDetected();
		void SetLanguageDetected(BOOL bNewValue);
		float GetFitTextWidth();
		void SetFitTextWidth(float newValue);
	};
	/////////////////////////////////////////////////////////////////////////////
	// TablesOfAuthoritiesCategories wrapper class

	class TablesOfAuthoritiesCategories : public COleDispatchDriver
	{
	public:
		TablesOfAuthoritiesCategories() {}		// Calls COleDispatchDriver default constructor
		TablesOfAuthoritiesCategories(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		TablesOfAuthoritiesCategories(const TablesOfAuthoritiesCategories& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		LPUNKNOWN Get_NewEnum();
		long GetCount();
		LPDISPATCH Item(VARIANT* Index);
	};
	/////////////////////////////////////////////////////////////////////////////
	// TableOfAuthoritiesCategory wrapper class

	class TableOfAuthoritiesCategory : public COleDispatchDriver
	{
	public:
		TableOfAuthoritiesCategory() {}		// Calls COleDispatchDriver default constructor
		TableOfAuthoritiesCategory(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		TableOfAuthoritiesCategory(const TableOfAuthoritiesCategory& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		CString GetName();
		void SetName(LPCTSTR lpszNewValue);
		long GetIndex();
	};
	/////////////////////////////////////////////////////////////////////////////
	// CaptionLabels wrapper class

	class CaptionLabels : public COleDispatchDriver
	{
	public:
		CaptionLabels() {}		// Calls COleDispatchDriver default constructor
		CaptionLabels(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CaptionLabels(const CaptionLabels& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		LPUNKNOWN Get_NewEnum();
		long GetCount();
		LPDISPATCH Item(VARIANT* Index);
		LPDISPATCH Add(LPCTSTR Name);
	};
	/////////////////////////////////////////////////////////////////////////////
	// CaptionLabel wrapper class

	class CaptionLabel : public COleDispatchDriver
	{
	public:
		CaptionLabel() {}		// Calls COleDispatchDriver default constructor
		CaptionLabel(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CaptionLabel(const CaptionLabel& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		CString GetName();
		BOOL GetBuiltIn();
		long GetId();
		BOOL GetIncludeChapterNumber();
		void SetIncludeChapterNumber(BOOL bNewValue);
		long GetNumberStyle();
		void SetNumberStyle(long nNewValue);
		long GetChapterStyleLevel();
		void SetChapterStyleLevel(long nNewValue);
		long GetSeparator();
		void SetSeparator(long nNewValue);
		long GetPosition();
		void SetPosition(long nNewValue);
		void Delete();
	};
	/////////////////////////////////////////////////////////////////////////////
	// AutoCaptions wrapper class

	class AutoCaptions : public COleDispatchDriver
	{
	public:
		AutoCaptions() {}		// Calls COleDispatchDriver default constructor
		AutoCaptions(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		AutoCaptions(const AutoCaptions& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		LPUNKNOWN Get_NewEnum();
		long GetCount();
		LPDISPATCH Item(VARIANT* Index);
		void CancelAutoInsert();
	};
	/////////////////////////////////////////////////////////////////////////////
	// AutoCaption wrapper class

	class AutoCaption : public COleDispatchDriver
	{
	public:
		AutoCaption() {}		// Calls COleDispatchDriver default constructor
		AutoCaption(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		AutoCaption(const AutoCaption& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		CString GetName();
		BOOL GetAutoInsert();
		void SetAutoInsert(BOOL bNewValue);
		long GetIndex();
		VARIANT GetCaptionLabel();
		void SetCaptionLabel(VARIANT* newValue);
	};
	/////////////////////////////////////////////////////////////////////////////
	// Indexes wrapper class

	class Indexes : public COleDispatchDriver
	{
	public:
		Indexes() {}		// Calls COleDispatchDriver default constructor
		Indexes(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		Indexes(const Indexes& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		LPUNKNOWN Get_NewEnum();
		long GetCount();
		long GetFormat();
		void SetFormat(long nNewValue);
		LPDISPATCH Item(long Index);
		LPDISPATCH MarkEntry(LPDISPATCH Range, VARIANT* Entry, VARIANT* EntryAutoText, VARIANT* CrossReference, VARIANT* CrossReferenceAutoText, VARIANT* BookmarkName, VARIANT* Bold, VARIANT* Italic, VARIANT* Reading);
		void MarkAllEntries(LPDISPATCH Range, VARIANT* Entry, VARIANT* EntryAutoText, VARIANT* CrossReference, VARIANT* CrossReferenceAutoText, VARIANT* BookmarkName, VARIANT* Bold, VARIANT* Italic);
		void AutoMarkEntries(LPCTSTR ConcordanceFileName);
		LPDISPATCH Add(LPDISPATCH Range, VARIANT* HeadingSeparator, VARIANT* RightAlignPageNumbers, VARIANT* Type, VARIANT* NumberOfColumns, VARIANT* AccentedLetters, VARIANT* SortBy, VARIANT* IndexLanguage);
	};
	/////////////////////////////////////////////////////////////////////////////
	// Index wrapper class

	class Index : public COleDispatchDriver
	{
	public:
		Index() {}		// Calls COleDispatchDriver default constructor
		Index(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		Index(const Index& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		long GetHeadingSeparator();
		void SetHeadingSeparator(long nNewValue);
		BOOL GetRightAlignPageNumbers();
		void SetRightAlignPageNumbers(BOOL bNewValue);
		long GetType();
		void SetType(long nNewValue);
		long GetNumberOfColumns();
		void SetNumberOfColumns(long nNewValue);
		LPDISPATCH GetRange();
		long GetTabLeader();
		void SetTabLeader(long nNewValue);
		BOOL GetAccentedLetters();
		void SetAccentedLetters(BOOL bNewValue);
		long GetSortBy();
		void SetSortBy(long nNewValue);
		long GetFilter();
		void SetFilter(long nNewValue);
		void Delete();
		void Update();
		long GetIndexLanguage();
		void SetIndexLanguage(long nNewValue);
	};
	/////////////////////////////////////////////////////////////////////////////
	// AddIn wrapper class

	class AddIn : public COleDispatchDriver
	{
	public:
		AddIn() {}		// Calls COleDispatchDriver default constructor
		AddIn(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		AddIn(const AddIn& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		CString GetName();
		long GetIndex();
		CString GetPath();
		BOOL GetInstalled();
		void SetInstalled(BOOL bNewValue);
		BOOL GetCompiled();
		BOOL GetAutoload();
		void Delete();
	};
	/////////////////////////////////////////////////////////////////////////////
	// AddIns wrapper class

	class AddIns : public COleDispatchDriver
	{
	public:
		AddIns() {}		// Calls COleDispatchDriver default constructor
		AddIns(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		AddIns(const AddIns& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		LPUNKNOWN Get_NewEnum();
		long GetCount();
		LPDISPATCH Item(VARIANT* Index);
		LPDISPATCH Add(LPCTSTR FileName, VARIANT* Install);
		void Unload(BOOL RemoveFromList);
	};
	/////////////////////////////////////////////////////////////////////////////
	// Revisions wrapper class

	class Revisions : public COleDispatchDriver
	{
	public:
		Revisions() {}		// Calls COleDispatchDriver default constructor
		Revisions(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		Revisions(const Revisions& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		LPUNKNOWN Get_NewEnum();
		long GetCount();
		LPDISPATCH Item(long Index);
		void AcceptAll();
		void RejectAll();
	};
	/////////////////////////////////////////////////////////////////////////////
	// Revision wrapper class

	class Revision : public COleDispatchDriver
	{
	public:
		Revision() {}		// Calls COleDispatchDriver default constructor
		Revision(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		Revision(const Revision& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		CString GetAuthor();
		DATE GetDate();
		LPDISPATCH GetRange();
		long GetType();
		long GetIndex();
		void Accept();
		void Reject();
	};
	/////////////////////////////////////////////////////////////////////////////
	// Task wrapper class

	class Task : public COleDispatchDriver
	{
	public:
		Task() {}		// Calls COleDispatchDriver default constructor
		Task(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		Task(const Task& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		CString GetName();
		long GetLeft();
		void SetLeft(long nNewValue);
		long GetTop();
		void SetTop(long nNewValue);
		long GetWidth();
		void SetWidth(long nNewValue);
		long GetHeight();
		void SetHeight(long nNewValue);
		long GetWindowState();
		void SetWindowState(long nNewValue);
		BOOL GetVisible();
		void SetVisible(BOOL bNewValue);
		void Activate(VARIANT* Wait);
		void Close();
		void Move(long Left, long Top);
		void Resize(long Width, long Height);
		void SendWindowMessage(long Message, long wParam, long lParam);
	};
	/////////////////////////////////////////////////////////////////////////////
	// Tasks wrapper class

	class Tasks : public COleDispatchDriver
	{
	public:
		Tasks() {}		// Calls COleDispatchDriver default constructor
		Tasks(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		Tasks(const Tasks& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		LPUNKNOWN Get_NewEnum();
		long GetCount();
		LPDISPATCH Item(VARIANT* Index);
		BOOL Exists(LPCTSTR Name);
		void ExitWindows_();
	};
	/////////////////////////////////////////////////////////////////////////////
	// HeadersFooters wrapper class

	class HeadersFooters : public COleDispatchDriver
	{
	public:
		HeadersFooters() {}		// Calls COleDispatchDriver default constructor
		HeadersFooters(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		HeadersFooters(const HeadersFooters& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		LPUNKNOWN Get_NewEnum();
		long GetCount();
		LPDISPATCH Item(long Index);
	};
	/////////////////////////////////////////////////////////////////////////////
	// HeaderFooter wrapper class

	class HeaderFooter : public COleDispatchDriver
	{
	public:
		HeaderFooter() {}		// Calls COleDispatchDriver default constructor
		HeaderFooter(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		HeaderFooter(const HeaderFooter& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		LPDISPATCH GetRange();
		long GetIndex();
		BOOL GetIsHeader();
		BOOL GetExists();
		void SetExists(BOOL bNewValue);
		LPDISPATCH GetPageNumbers();
		BOOL GetLinkToPrevious();
		void SetLinkToPrevious(BOOL bNewValue);
		LPDISPATCH GetShapes();
	};
	/////////////////////////////////////////////////////////////////////////////
	// PageNumbers wrapper class

	class PageNumbers : public COleDispatchDriver
	{
	public:
		PageNumbers() {}		// Calls COleDispatchDriver default constructor
		PageNumbers(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		PageNumbers(const PageNumbers& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		LPUNKNOWN Get_NewEnum();
		long GetCount();
		long GetNumberStyle();
		void SetNumberStyle(long nNewValue);
		BOOL GetIncludeChapterNumber();
		void SetIncludeChapterNumber(BOOL bNewValue);
		long GetHeadingLevelForChapter();
		void SetHeadingLevelForChapter(long nNewValue);
		long GetChapterPageSeparator();
		void SetChapterPageSeparator(long nNewValue);
		BOOL GetRestartNumberingAtSection();
		void SetRestartNumberingAtSection(BOOL bNewValue);
		long GetStartingNumber();
		void SetStartingNumber(long nNewValue);
		BOOL GetShowFirstPageNumber();
		void SetShowFirstPageNumber(BOOL bNewValue);
		LPDISPATCH Item(long Index);
		LPDISPATCH Add(VARIANT* PageNumberAlignment, VARIANT* FirstPage);
		BOOL GetDoubleQuote();
		void SetDoubleQuote(BOOL bNewValue);
	};
	/////////////////////////////////////////////////////////////////////////////
	// PageNumber wrapper class

	class PageNumber : public COleDispatchDriver
	{
	public:
		PageNumber() {}		// Calls COleDispatchDriver default constructor
		PageNumber(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		PageNumber(const PageNumber& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		long GetIndex();
		long GetAlignment();
		void SetAlignment(long nNewValue);
		void Select();
		void Copy();
		void Cut();
		void Delete();
	};
	/////////////////////////////////////////////////////////////////////////////
	// Subdocuments wrapper class

	class Subdocuments : public COleDispatchDriver
	{
	public:
		Subdocuments() {}		// Calls COleDispatchDriver default constructor
		Subdocuments(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		Subdocuments(const Subdocuments& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		long GetCount();
		LPUNKNOWN Get_NewEnum();
		BOOL GetExpanded();
		void SetExpanded(BOOL bNewValue);
		LPDISPATCH Item(long Index);
		LPDISPATCH AddFromFile(VARIANT* Name, VARIANT* ConfirmConversions, VARIANT* ReadOnly, VARIANT* PasswordDocument, VARIANT* PasswordTemplate, VARIANT* Revert, VARIANT* WritePasswordDocument, VARIANT* WritePasswordTemplate);
		LPDISPATCH AddFromRange(LPDISPATCH Range);
		void Merge(VARIANT* FirstSubdocument, VARIANT* LastSubdocument);
		void Delete();
		void Select();
	};
	/////////////////////////////////////////////////////////////////////////////
	// Subdocument wrapper class

	class Subdocument : public COleDispatchDriver
	{
	public:
		Subdocument() {}		// Calls COleDispatchDriver default constructor
		Subdocument(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		Subdocument(const Subdocument& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		BOOL GetLocked();
		void SetLocked(BOOL bNewValue);
		LPDISPATCH GetRange();
		CString GetName();
		CString GetPath();
		BOOL GetHasFile();
		long GetLevel();
		void Delete();
		void Split(LPDISPATCH Range);
		LPDISPATCH Open();
	};
	/////////////////////////////////////////////////////////////////////////////
	// HeadingStyles wrapper class

	class HeadingStyles : public COleDispatchDriver
	{
	public:
		HeadingStyles() {}		// Calls COleDispatchDriver default constructor
		HeadingStyles(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		HeadingStyles(const HeadingStyles& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		LPUNKNOWN Get_NewEnum();
		long GetCount();
		LPDISPATCH Item(long Index);
		LPDISPATCH Add(VARIANT* Style, short Level);
	};
	/////////////////////////////////////////////////////////////////////////////
	// HeadingStyle wrapper class

	class HeadingStyle : public COleDispatchDriver
	{
	public:
		HeadingStyle() {}		// Calls COleDispatchDriver default constructor
		HeadingStyle(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		HeadingStyle(const HeadingStyle& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		VARIANT GetStyle();
		void SetStyle(VARIANT* newValue);
		short GetLevel();
		void SetLevel(short nNewValue);
		void Delete();
	};
	/////////////////////////////////////////////////////////////////////////////
	// StoryRanges wrapper class

	class StoryRanges : public COleDispatchDriver
	{
	public:
		StoryRanges() {}		// Calls COleDispatchDriver default constructor
		StoryRanges(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		StoryRanges(const StoryRanges& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPUNKNOWN Get_NewEnum();
		long GetCount();
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		LPDISPATCH Item(long Index);
	};
	/////////////////////////////////////////////////////////////////////////////
	// ListLevel wrapper class

	class ListLevel : public COleDispatchDriver
	{
	public:
		ListLevel() {}		// Calls COleDispatchDriver default constructor
		ListLevel(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		ListLevel(const ListLevel& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		long GetIndex();
		CString GetNumberFormat();
		void SetNumberFormat(LPCTSTR lpszNewValue);
		long GetTrailingCharacter();
		void SetTrailingCharacter(long nNewValue);
		long GetNumberStyle();
		void SetNumberStyle(long nNewValue);
		float GetNumberPosition();
		void SetNumberPosition(float newValue);
		long GetAlignment();
		void SetAlignment(long nNewValue);
		float GetTextPosition();
		void SetTextPosition(float newValue);
		float GetTabPosition();
		void SetTabPosition(float newValue);
		long GetStartAt();
		void SetStartAt(long nNewValue);
		CString GetLinkedStyle();
		void SetLinkedStyle(LPCTSTR lpszNewValue);
		LPDISPATCH GetFont();
		void SetFont(LPDISPATCH newValue);
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		long GetResetOnHigher();
		void SetResetOnHigher(long nNewValue);
	};
	/////////////////////////////////////////////////////////////////////////////
	// ListLevels wrapper class

	class ListLevels : public COleDispatchDriver
	{
	public:
		ListLevels() {}		// Calls COleDispatchDriver default constructor
		ListLevels(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		ListLevels(const ListLevels& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPUNKNOWN Get_NewEnum();
		long GetCount();
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		LPDISPATCH Item(long Index);
	};
	/////////////////////////////////////////////////////////////////////////////
	// ListTemplate wrapper class

	class ListTemplate : public COleDispatchDriver
	{
	public:
		ListTemplate() {}		// Calls COleDispatchDriver default constructor
		ListTemplate(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		ListTemplate(const ListTemplate& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		BOOL GetOutlineNumbered();
		void SetOutlineNumbered(BOOL bNewValue);
		CString GetName();
		void SetName(LPCTSTR lpszNewValue);
		LPDISPATCH GetListLevels();
		LPDISPATCH Convert(VARIANT* Level);
	};
	/////////////////////////////////////////////////////////////////////////////
	// ListTemplates wrapper class

	class ListTemplates : public COleDispatchDriver
	{
	public:
		ListTemplates() {}		// Calls COleDispatchDriver default constructor
		ListTemplates(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		ListTemplates(const ListTemplates& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPUNKNOWN Get_NewEnum();
		long GetCount();
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		LPDISPATCH Item(VARIANT* Index);
		LPDISPATCH Add(VARIANT* OutlineNumbered, VARIANT* Name);
	};
	/////////////////////////////////////////////////////////////////////////////
	// ListParagraphs wrapper class

	class ListParagraphs : public COleDispatchDriver
	{
	public:
		ListParagraphs() {}		// Calls COleDispatchDriver default constructor
		ListParagraphs(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		ListParagraphs(const ListParagraphs& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPUNKNOWN Get_NewEnum();
		long GetCount();
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		LPDISPATCH Item(long Index);
	};
	/////////////////////////////////////////////////////////////////////////////
	// List wrapper class

	class List : public COleDispatchDriver
	{
	public:
		List() {}		// Calls COleDispatchDriver default constructor
		List(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		List(const List& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetRange();
		LPDISPATCH GetListParagraphs();
		BOOL GetSingleListTemplate();
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		void ConvertNumbersToText(VARIANT* NumberType);
		void RemoveNumbers(VARIANT* NumberType);
		long CountNumberedItems(VARIANT* NumberType, VARIANT* Level);
		long CanContinuePreviousList(LPDISPATCH ListTemplate);
		void ApplyListTemplate(LPDISPATCH ListTemplate, VARIANT* ContinuePreviousList, VARIANT* DefaultListBehavior);
	};
	/////////////////////////////////////////////////////////////////////////////
	// Lists wrapper class

	class Lists : public COleDispatchDriver
	{
	public:
		Lists() {}		// Calls COleDispatchDriver default constructor
		Lists(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		Lists(const Lists& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPUNKNOWN Get_NewEnum();
		long GetCount();
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		LPDISPATCH Item(long Index);
	};
	/////////////////////////////////////////////////////////////////////////////
	// ListGallery wrapper class

	class ListGallery : public COleDispatchDriver
	{
	public:
		ListGallery() {}		// Calls COleDispatchDriver default constructor
		ListGallery(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		ListGallery(const ListGallery& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetListTemplates();
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		BOOL GetModified(long Index);
		void Reset(long Index);
	};
	/////////////////////////////////////////////////////////////////////////////
	// ListGalleries wrapper class

	class ListGalleries : public COleDispatchDriver
	{
	public:
		ListGalleries() {}		// Calls COleDispatchDriver default constructor
		ListGalleries(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		ListGalleries(const ListGalleries& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPUNKNOWN Get_NewEnum();
		long GetCount();
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		LPDISPATCH Item(long Index);
	};
	/////////////////////////////////////////////////////////////////////////////
	// KeyBindings wrapper class

	class KeyBindings : public COleDispatchDriver
	{
	public:
		KeyBindings() {}		// Calls COleDispatchDriver default constructor
		KeyBindings(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		KeyBindings(const KeyBindings& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		LPUNKNOWN Get_NewEnum();
		long GetCount();
		LPDISPATCH GetContext();
		LPDISPATCH Item(long Index);
		LPDISPATCH Add(long KeyCategory, LPCTSTR Command, long KeyCode, VARIANT* KeyCode2, VARIANT* CommandParameter);
		void ClearAll();
		LPDISPATCH Key(long KeyCode, VARIANT* KeyCode2);
	};
	/////////////////////////////////////////////////////////////////////////////
	// KeysBoundTo wrapper class

	class KeysBoundTo : public COleDispatchDriver
	{
	public:
		KeysBoundTo() {}		// Calls COleDispatchDriver default constructor
		KeysBoundTo(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		KeysBoundTo(const KeysBoundTo& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		LPUNKNOWN Get_NewEnum();
		long GetCount();
		long GetKeyCategory();
		CString GetCommand();
		CString GetCommandParameter();
		LPDISPATCH GetContext();
		LPDISPATCH Item(long Index);
		LPDISPATCH Key(long KeyCode, VARIANT* KeyCode2);
	};
	/////////////////////////////////////////////////////////////////////////////
	// KeyBinding wrapper class

	class KeyBinding : public COleDispatchDriver
	{
	public:
		KeyBinding() {}		// Calls COleDispatchDriver default constructor
		KeyBinding(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		KeyBinding(const KeyBinding& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		CString GetCommand();
		CString GetKeyString();
		BOOL GetProtected();
		long GetKeyCategory();
		long GetKeyCode();
		long GetKeyCode2();
		CString GetCommandParameter();
		LPDISPATCH GetContext();
		void Clear();
		void Disable();
		void Execute();
		void Rebind(long KeyCategory, LPCTSTR Command, VARIANT* CommandParameter);
	};
	/////////////////////////////////////////////////////////////////////////////
	// FileConverter wrapper class

	class FileConverter : public COleDispatchDriver
	{
	public:
		FileConverter() {}		// Calls COleDispatchDriver default constructor
		FileConverter(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		FileConverter(const FileConverter& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		CString GetFormatName();
		CString GetClassName();
		long GetSaveFormat();
		long GetOpenFormat();
		BOOL GetCanSave();
		BOOL GetCanOpen();
		CString GetPath();
		CString GetName();
		CString GetExtensions();
	};
	/////////////////////////////////////////////////////////////////////////////
	// FileConverters wrapper class

	class FileConverters : public COleDispatchDriver
	{
	public:
		FileConverters() {}		// Calls COleDispatchDriver default constructor
		FileConverters(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		FileConverters(const FileConverters& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		long GetCount();
		LPUNKNOWN Get_NewEnum();
		long GetConvertMacWordChevrons();
		void SetConvertMacWordChevrons(long nNewValue);
		LPDISPATCH Item(VARIANT* Index);
	};
	/////////////////////////////////////////////////////////////////////////////
	// SynonymInfo wrapper class

	class SynonymInfo : public COleDispatchDriver
	{
	public:
		SynonymInfo() {}		// Calls COleDispatchDriver default constructor
		SynonymInfo(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		SynonymInfo(const SynonymInfo& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		CString GetWord();
		BOOL GetFound();
		long GetMeaningCount();
		VARIANT GetMeaningList();
		VARIANT GetPartOfSpeechList();
		VARIANT GetSynonymList(VARIANT* Meaning);
		VARIANT GetAntonymList();
		VARIANT GetRelatedExpressionList();
		VARIANT GetRelatedWordList();
	};
	/////////////////////////////////////////////////////////////////////////////
	// Hyperlinks wrapper class

	class Hyperlinks : public COleDispatchDriver
	{
	public:
		Hyperlinks() {}		// Calls COleDispatchDriver default constructor
		Hyperlinks(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		Hyperlinks(const Hyperlinks& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		long GetCount();
		LPUNKNOWN Get_NewEnum();
		LPDISPATCH Item(VARIANT* Index);
		LPDISPATCH Add(LPDISPATCH Anchor, VARIANT* Address, VARIANT* SubAddress, VARIANT* ScreenTip, VARIANT* TextToDisplay, VARIANT* Target);
	};
	/////////////////////////////////////////////////////////////////////////////
	// Hyperlink wrapper class

	class Hyperlink : public COleDispatchDriver
	{
	public:
		Hyperlink() {}		// Calls COleDispatchDriver default constructor
		Hyperlink(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		Hyperlink(const Hyperlink& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		CString GetName();
		long GetType();
		LPDISPATCH GetRange();
		LPDISPATCH GetShape();
		BOOL GetExtraInfoRequired();
		void Delete();
		void Follow(VARIANT* NewWindow, VARIANT* AddHistory, VARIANT* ExtraInfo, VARIANT* Method, VARIANT* HeaderInfo);
		void AddToFavorites();
		void CreateNewDocument(LPCTSTR FileName, BOOL EditNow, BOOL Overwrite);
		CString GetAddress();
		void SetAddress(LPCTSTR lpszNewValue);
		CString GetSubAddress();
		void SetSubAddress(LPCTSTR lpszNewValue);
		CString GetEmailSubject();
		void SetEmailSubject(LPCTSTR lpszNewValue);
		CString GetScreenTip();
		void SetScreenTip(LPCTSTR lpszNewValue);
		CString GetTextToDisplay();
		void SetTextToDisplay(LPCTSTR lpszNewValue);
		CString GetTarget();
		void SetTarget(LPCTSTR lpszNewValue);
	};
	/////////////////////////////////////////////////////////////////////////////
	// Shapes wrapper class

	class Shapes : public COleDispatchDriver
	{
	public:
		Shapes() {}		// Calls COleDispatchDriver default constructor
		Shapes(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		Shapes(const Shapes& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		long GetCount();
		LPUNKNOWN Get_NewEnum();
		LPDISPATCH Item(VARIANT* Index);
		LPDISPATCH AddCallout(long Type, float Left, float Top, float Width, float Height, VARIANT* Anchor);
		LPDISPATCH AddCurve(VARIANT* SafeArrayOfPoints, VARIANT* Anchor);
		LPDISPATCH AddLabel(long Orientation, float Left, float Top, float Width, float Height, VARIANT* Anchor);
		LPDISPATCH AddLine(float BeginX, float BeginY, float EndX, float EndY, VARIANT* Anchor);
		LPDISPATCH AddPicture(LPCTSTR FileName, VARIANT* LinkToFile, VARIANT* SaveWithDocument, VARIANT* Left, VARIANT* Top, VARIANT* Width, VARIANT* Height, VARIANT* Anchor);
		LPDISPATCH AddPolyline(VARIANT* SafeArrayOfPoints, VARIANT* Anchor);
		LPDISPATCH AddShape(long Type, float Left, float Top, float Width, float Height, VARIANT* Anchor);
		LPDISPATCH AddTextEffect(long PresetTextEffect, LPCTSTR Text, LPCTSTR FontName, float FontSize, long FontBold, long FontItalic, float Left, float Top, VARIANT* Anchor);
		LPDISPATCH AddTextbox(long Orientation, float Left, float Top, float Width, float Height, VARIANT* Anchor);
		LPDISPATCH BuildFreeform(long EditingType, float X1, float Y1);
		LPDISPATCH Range(VARIANT* Index);
		void SelectAll();
		LPDISPATCH AddOLEObject(VARIANT* ClassType, VARIANT* FileName, VARIANT* LinkToFile, VARIANT* DisplayAsIcon, VARIANT* IconFileName, VARIANT* IconIndex, VARIANT* IconLabel, VARIANT* Left, VARIANT* Top, VARIANT* Width, VARIANT* Height, 
			VARIANT* Anchor);
		LPDISPATCH AddOLEControl(VARIANT* ClassType, VARIANT* Left, VARIANT* Top, VARIANT* Width, VARIANT* Height, VARIANT* Anchor);
	};
	/////////////////////////////////////////////////////////////////////////////
	// ShapeRange wrapper class

	class ShapeRange : public COleDispatchDriver
	{
	public:
		ShapeRange() {}		// Calls COleDispatchDriver default constructor
		ShapeRange(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		ShapeRange(const ShapeRange& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		long GetCount();
		LPUNKNOWN Get_NewEnum();
		LPDISPATCH GetAdjustments();
		long GetAutoShapeType();
		void SetAutoShapeType(long nNewValue);
		LPDISPATCH GetCallout();
		LPDISPATCH GetFill();
		LPDISPATCH GetGroupItems();
		float GetHeight();
		void SetHeight(float newValue);
		long GetHorizontalFlip();
		float GetLeft();
		void SetLeft(float newValue);
		LPDISPATCH GetLine();
		long GetLockAspectRatio();
		void SetLockAspectRatio(long nNewValue);
		CString GetName();
		void SetName(LPCTSTR lpszNewValue);
		LPDISPATCH GetNodes();
		float GetRotation();
		void SetRotation(float newValue);
		LPDISPATCH GetPictureFormat();
		LPDISPATCH GetShadow();
		LPDISPATCH GetTextEffect();
		LPDISPATCH GetTextFrame();
		LPDISPATCH GetThreeD();
		float GetTop();
		void SetTop(float newValue);
		long GetType();
		long GetVerticalFlip();
		VARIANT GetVertices();
		long GetVisible();
		void SetVisible(long nNewValue);
		float GetWidth();
		void SetWidth(float newValue);
		long GetZOrderPosition();
		LPDISPATCH GetHyperlink();
		long GetRelativeHorizontalPosition();
		void SetRelativeHorizontalPosition(long nNewValue);
		long GetRelativeVerticalPosition();
		void SetRelativeVerticalPosition(long nNewValue);
		long GetLockAnchor();
		void SetLockAnchor(long nNewValue);
		LPDISPATCH GetWrapFormat();
		LPDISPATCH GetAnchor();
		LPDISPATCH Item(VARIANT* Index);
		void Align(long Align, long RelativeTo);
		void Apply();
		void Delete();
		void Distribute(long Distribute, long RelativeTo);
		LPDISPATCH Duplicate();
		void Flip(long FlipCmd);
		void IncrementLeft(float Increment);
		void IncrementRotation(float Increment);
		void IncrementTop(float Increment);
		LPDISPATCH Group();
		void PickUp();
		LPDISPATCH Regroup();
		void ScaleHeight(float Factor, long RelativeToOriginalSize, long Scale);
		void ScaleWidth(float Factor, long RelativeToOriginalSize, long Scale);
		void Select(VARIANT* Replace);
		void SetShapesDefaultProperties();
		LPDISPATCH Ungroup();
		void ZOrder(long ZOrderCmd);
		LPDISPATCH ConvertToFrame();
		LPDISPATCH ConvertToInlineShape();
		void Activate();
		CString GetAlternativeText();
		void SetAlternativeText(LPCTSTR lpszNewValue);
	};
	/////////////////////////////////////////////////////////////////////////////
	// GroupShapes wrapper class

	class GroupShapes : public COleDispatchDriver
	{
	public:
		GroupShapes() {}		// Calls COleDispatchDriver default constructor
		GroupShapes(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		GroupShapes(const GroupShapes& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		long GetCount();
		LPUNKNOWN Get_NewEnum();
		LPDISPATCH Item(VARIANT* Index);
	};
	/////////////////////////////////////////////////////////////////////////////
	// Shape wrapper class

	class Shape : public COleDispatchDriver
	{
	public:
		Shape() {}		// Calls COleDispatchDriver default constructor
		Shape(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		Shape(const Shape& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		LPDISPATCH GetAdjustments();
		long GetAutoShapeType();
		void SetAutoShapeType(long nNewValue);
		LPDISPATCH GetCallout();
		LPDISPATCH GetFill();
		LPDISPATCH GetGroupItems();
		float GetHeight();
		void SetHeight(float newValue);
		long GetHorizontalFlip();
		float GetLeft();
		void SetLeft(float newValue);
		LPDISPATCH GetLine();
		long GetLockAspectRatio();
		void SetLockAspectRatio(long nNewValue);
		CString GetName();
		void SetName(LPCTSTR lpszNewValue);
		LPDISPATCH GetNodes();
		float GetRotation();
		void SetRotation(float newValue);
		LPDISPATCH GetPictureFormat();
		LPDISPATCH GetShadow();
		LPDISPATCH GetTextEffect();
		LPDISPATCH GetTextFrame();
		LPDISPATCH GetThreeD();
		float GetTop();
		void SetTop(float newValue);
		long GetType();
		long GetVerticalFlip();
		VARIANT GetVertices();
		long GetVisible();
		void SetVisible(long nNewValue);
		float GetWidth();
		void SetWidth(float newValue);
		long GetZOrderPosition();
		LPDISPATCH GetHyperlink();
		long GetRelativeHorizontalPosition();
		void SetRelativeHorizontalPosition(long nNewValue);
		long GetRelativeVerticalPosition();
		void SetRelativeVerticalPosition(long nNewValue);
		long GetLockAnchor();
		void SetLockAnchor(long nNewValue);
		LPDISPATCH GetWrapFormat();
		LPDISPATCH GetOLEFormat();
		LPDISPATCH GetAnchor();
		LPDISPATCH GetLinkFormat();
		void Apply();
		void Delete();
		LPDISPATCH Duplicate();
		void Flip(long FlipCmd);
		void IncrementLeft(float Increment);
		void IncrementRotation(float Increment);
		void IncrementTop(float Increment);
		void PickUp();
		void ScaleHeight(float Factor, long RelativeToOriginalSize, long Scale);
		void ScaleWidth(float Factor, long RelativeToOriginalSize, long Scale);
		void Select(VARIANT* Replace);
		void SetShapesDefaultProperties();
		LPDISPATCH Ungroup();
		void ZOrder(long ZOrderCmd);
		LPDISPATCH ConvertToInlineShape();
		LPDISPATCH ConvertToFrame();
		void Activate();
		CString GetAlternativeText();
		void SetAlternativeText(LPCTSTR lpszNewValue);
		LPDISPATCH GetScript();
	};
	/////////////////////////////////////////////////////////////////////////////
	// TextFrame wrapper class

	class TextFrame : public COleDispatchDriver
	{
	public:
		TextFrame() {}		// Calls COleDispatchDriver default constructor
		TextFrame(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		TextFrame(const TextFrame& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		float GetMarginBottom();
		void SetMarginBottom(float newValue);
		float GetMarginLeft();
		void SetMarginLeft(float newValue);
		float GetMarginRight();
		void SetMarginRight(float newValue);
		float GetMarginTop();
		void SetMarginTop(float newValue);
		long GetOrientation();
		void SetOrientation(long nNewValue);
		LPDISPATCH GetTextRange();
		LPDISPATCH GetContainingRange();
		LPDISPATCH GetNext();
		void SetNext(LPDISPATCH newValue);
		LPDISPATCH GetPrevious();
		void SetPrevious(LPDISPATCH newValue);
		BOOL GetOverflowing();
		long GetHasText();
		void BreakForwardLink();
		BOOL ValidLinkTarget(LPDISPATCH TargetTextFrame);
	};
	/////////////////////////////////////////////////////////////////////////////
	// _LetterContent wrapper class

	class _LetterContent : public COleDispatchDriver
	{
	public:
		_LetterContent() {}		// Calls COleDispatchDriver default constructor
		_LetterContent(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		_LetterContent(const _LetterContent& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		LPDISPATCH GetDuplicate();
		CString GetDateFormat();
		void SetDateFormat(LPCTSTR lpszNewValue);
		BOOL GetIncludeHeaderFooter();
		void SetIncludeHeaderFooter(BOOL bNewValue);
		CString GetPageDesign();
		void SetPageDesign(LPCTSTR lpszNewValue);
		long GetLetterStyle();
		void SetLetterStyle(long nNewValue);
		BOOL GetLetterhead();
		void SetLetterhead(BOOL bNewValue);
		long GetLetterheadLocation();
		void SetLetterheadLocation(long nNewValue);
		float GetLetterheadSize();
		void SetLetterheadSize(float newValue);
		CString GetRecipientName();
		void SetRecipientName(LPCTSTR lpszNewValue);
		CString GetRecipientAddress();
		void SetRecipientAddress(LPCTSTR lpszNewValue);
		CString GetSalutation();
		void SetSalutation(LPCTSTR lpszNewValue);
		long GetSalutationType();
		void SetSalutationType(long nNewValue);
		CString GetRecipientReference();
		void SetRecipientReference(LPCTSTR lpszNewValue);
		CString GetMailingInstructions();
		void SetMailingInstructions(LPCTSTR lpszNewValue);
		CString GetAttentionLine();
		void SetAttentionLine(LPCTSTR lpszNewValue);
		CString GetSubject();
		void SetSubject(LPCTSTR lpszNewValue);
		long GetEnclosureNumber();
		void SetEnclosureNumber(long nNewValue);
		CString GetCCList();
		void SetCCList(LPCTSTR lpszNewValue);
		CString GetReturnAddress();
		void SetReturnAddress(LPCTSTR lpszNewValue);
		CString GetSenderName();
		void SetSenderName(LPCTSTR lpszNewValue);
		CString GetClosing();
		void SetClosing(LPCTSTR lpszNewValue);
		CString GetSenderCompany();
		void SetSenderCompany(LPCTSTR lpszNewValue);
		CString GetSenderJobTitle();
		void SetSenderJobTitle(LPCTSTR lpszNewValue);
		CString GetSenderInitials();
		void SetSenderInitials(LPCTSTR lpszNewValue);
		BOOL GetInfoBlock();
		void SetInfoBlock(BOOL bNewValue);
		CString GetRecipientCode();
		void SetRecipientCode(LPCTSTR lpszNewValue);
		long GetRecipientGender();
		void SetRecipientGender(long nNewValue);
		CString GetReturnAddressShortForm();
		void SetReturnAddressShortForm(LPCTSTR lpszNewValue);
		CString GetSenderCity();
		void SetSenderCity(LPCTSTR lpszNewValue);
		CString GetSenderCode();
		void SetSenderCode(LPCTSTR lpszNewValue);
		long GetSenderGender();
		void SetSenderGender(long nNewValue);
		CString GetSenderReference();
		void SetSenderReference(LPCTSTR lpszNewValue);
	};
	/////////////////////////////////////////////////////////////////////////////
	// View wrapper class

	class View : public COleDispatchDriver
	{
	public:
		View() {}		// Calls COleDispatchDriver default constructor
		View(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		View(const View& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		long GetType();
		void SetType(long nNewValue);
		BOOL GetFullScreen();
		void SetFullScreen(BOOL bNewValue);
		BOOL GetDraft();
		void SetDraft(BOOL bNewValue);
		BOOL GetShowAll();
		void SetShowAll(BOOL bNewValue);
		BOOL GetShowFieldCodes();
		void SetShowFieldCodes(BOOL bNewValue);
		BOOL GetMailMergeDataView();
		void SetMailMergeDataView(BOOL bNewValue);
		BOOL GetMagnifier();
		void SetMagnifier(BOOL bNewValue);
		BOOL GetShowFirstLineOnly();
		void SetShowFirstLineOnly(BOOL bNewValue);
		BOOL GetShowFormat();
		void SetShowFormat(BOOL bNewValue);
		LPDISPATCH GetZoom();
		BOOL GetShowObjectAnchors();
		void SetShowObjectAnchors(BOOL bNewValue);
		BOOL GetShowTextBoundaries();
		void SetShowTextBoundaries(BOOL bNewValue);
		BOOL GetShowHighlight();
		void SetShowHighlight(BOOL bNewValue);
		BOOL GetShowDrawings();
		void SetShowDrawings(BOOL bNewValue);
		BOOL GetShowTabs();
		void SetShowTabs(BOOL bNewValue);
		BOOL GetShowSpaces();
		void SetShowSpaces(BOOL bNewValue);
		BOOL GetShowParagraphs();
		void SetShowParagraphs(BOOL bNewValue);
		BOOL GetShowHyphens();
		void SetShowHyphens(BOOL bNewValue);
		BOOL GetShowHiddenText();
		void SetShowHiddenText(BOOL bNewValue);
		BOOL GetWrapToWindow();
		void SetWrapToWindow(BOOL bNewValue);
		BOOL GetShowPicturePlaceHolders();
		void SetShowPicturePlaceHolders(BOOL bNewValue);
		BOOL GetShowBookmarks();
		void SetShowBookmarks(BOOL bNewValue);
		long GetFieldShading();
		void SetFieldShading(long nNewValue);
		BOOL GetShowAnimation();
		void SetShowAnimation(BOOL bNewValue);
		BOOL GetTableGridlines();
		void SetTableGridlines(BOOL bNewValue);
		long GetEnlargeFontsLessThan();
		void SetEnlargeFontsLessThan(long nNewValue);
		BOOL GetShowMainTextLayer();
		void SetShowMainTextLayer(BOOL bNewValue);
		long GetSeekView();
		void SetSeekView(long nNewValue);
		long GetSplitSpecial();
		void SetSplitSpecial(long nNewValue);
		long GetBrowseToWindow();
		void SetBrowseToWindow(long nNewValue);
		BOOL GetShowOptionalBreaks();
		void SetShowOptionalBreaks(BOOL bNewValue);
		void CollapseOutline(VARIANT* Range);
		void ExpandOutline(VARIANT* Range);
		void ShowAllHeadings();
		void ShowHeading(long Level);
		void PreviousHeaderFooter();
		void NextHeaderFooter();
	};
	/////////////////////////////////////////////////////////////////////////////
	// Zoom wrapper class

	class Zoom : public COleDispatchDriver
	{
	public:
		Zoom() {}		// Calls COleDispatchDriver default constructor
		Zoom(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		Zoom(const Zoom& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		long GetPercentage();
		void SetPercentage(long nNewValue);
		long GetPageFit();
		void SetPageFit(long nNewValue);
		long GetPageRows();
		void SetPageRows(long nNewValue);
		long GetPageColumns();
		void SetPageColumns(long nNewValue);
	};
	/////////////////////////////////////////////////////////////////////////////
	// Zooms wrapper class

	class Zooms : public COleDispatchDriver
	{
	public:
		Zooms() {}		// Calls COleDispatchDriver default constructor
		Zooms(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		Zooms(const Zooms& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		LPDISPATCH Item(long Index);
	};
	/////////////////////////////////////////////////////////////////////////////
	// InlineShape wrapper class

	class InlineShape : public COleDispatchDriver
	{
	public:
		InlineShape() {}		// Calls COleDispatchDriver default constructor
		InlineShape(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		InlineShape(const InlineShape& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		LPDISPATCH GetBorders();
		void SetBorders(LPDISPATCH newValue);
		LPDISPATCH GetRange();
		LPDISPATCH GetLinkFormat();
		LPDISPATCH GetField();
		LPDISPATCH GetOLEFormat();
		long GetType();
		LPDISPATCH GetHyperlink();
		float GetHeight();
		void SetHeight(float newValue);
		float GetWidth();
		void SetWidth(float newValue);
		float GetScaleHeight();
		void SetScaleHeight(float newValue);
		float GetScaleWidth();
		void SetScaleWidth(float newValue);
		long GetLockAspectRatio();
		void SetLockAspectRatio(long nNewValue);
		LPDISPATCH GetLine();
		LPDISPATCH GetFill();
		LPDISPATCH GetPictureFormat();
		void SetPictureFormat(LPDISPATCH newValue);
		void Activate();
		void Reset();
		void Delete();
		void Select();
		LPDISPATCH ConvertToShape();
		LPDISPATCH GetHorizontalLineFormat();
		LPDISPATCH GetScript();
		LPDISPATCH GetTextEffect();
		void SetTextEffect(LPDISPATCH newValue);
		CString GetAlternativeText();
		void SetAlternativeText(LPCTSTR lpszNewValue);
	};
	/////////////////////////////////////////////////////////////////////////////
	// InlineShapes wrapper class

	class InlineShapes : public COleDispatchDriver
	{
	public:
		InlineShapes() {}		// Calls COleDispatchDriver default constructor
		InlineShapes(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		InlineShapes(const InlineShapes& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		long GetCount();
		LPUNKNOWN Get_NewEnum();
		LPDISPATCH Item(long Index);
		LPDISPATCH AddPicture(LPCTSTR FileName, VARIANT* LinkToFile, VARIANT* SaveWithDocument, VARIANT* Range);
		LPDISPATCH AddOLEObject(VARIANT* ClassType, VARIANT* FileName, VARIANT* LinkToFile, VARIANT* DisplayAsIcon, VARIANT* IconFileName, VARIANT* IconIndex, VARIANT* IconLabel, VARIANT* Range);
		LPDISPATCH AddOLEControl(VARIANT* ClassType, VARIANT* Range);
		LPDISPATCH New(LPDISPATCH Range);
		LPDISPATCH AddHorizontalLine(LPCTSTR FileName, VARIANT* Range);
		LPDISPATCH AddHorizontalLineStandard(VARIANT* Range);
		LPDISPATCH AddPictureBullet(LPCTSTR FileName, VARIANT* Range);
	};
	/////////////////////////////////////////////////////////////////////////////
	// SpellingSuggestions wrapper class

	class SpellingSuggestions : public COleDispatchDriver
	{
	public:
		SpellingSuggestions() {}		// Calls COleDispatchDriver default constructor
		SpellingSuggestions(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		SpellingSuggestions(const SpellingSuggestions& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		LPUNKNOWN Get_NewEnum();
		long GetCount();
		long GetSpellingErrorType();
		LPDISPATCH Item(long Index);
	};
	/////////////////////////////////////////////////////////////////////////////
	// SpellingSuggestion wrapper class

	class SpellingSuggestion : public COleDispatchDriver
	{
	public:
		SpellingSuggestion() {}		// Calls COleDispatchDriver default constructor
		SpellingSuggestion(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		SpellingSuggestion(const SpellingSuggestion& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		CString GetName();
	};
	/////////////////////////////////////////////////////////////////////////////
	// Dictionaries wrapper class

	class Dictionaries : public COleDispatchDriver
	{
	public:
		Dictionaries() {}		// Calls COleDispatchDriver default constructor
		Dictionaries(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		Dictionaries(const Dictionaries& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		LPUNKNOWN Get_NewEnum();
		long GetCount();
		long GetMaximum();
		LPDISPATCH GetActiveCustomDictionary();
		void SetActiveCustomDictionary(LPDISPATCH newValue);
		LPDISPATCH Item(VARIANT* Index);
		LPDISPATCH Add(LPCTSTR FileName);
		void ClearAll();
	};
	/////////////////////////////////////////////////////////////////////////////
	// HangulHanjaConversionDictionaries wrapper class

	class HangulHanjaConversionDictionaries : public COleDispatchDriver
	{
	public:
		HangulHanjaConversionDictionaries() {}		// Calls COleDispatchDriver default constructor
		HangulHanjaConversionDictionaries(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		HangulHanjaConversionDictionaries(const HangulHanjaConversionDictionaries& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		LPUNKNOWN Get_NewEnum();
		long GetCount();
		long GetMaximum();
		LPDISPATCH GetActiveCustomDictionary();
		void SetActiveCustomDictionary(LPDISPATCH newValue);
		LPDISPATCH GetBuiltinDictionary();
		LPDISPATCH Item(VARIANT* Index);
		LPDISPATCH Add(LPCTSTR FileName);
		void ClearAll();
	};
	/////////////////////////////////////////////////////////////////////////////
	// Dictionary wrapper class

	class Dictionary : public COleDispatchDriver
	{
	public:
		Dictionary() {}		// Calls COleDispatchDriver default constructor
		Dictionary(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		Dictionary(const Dictionary& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		CString GetName();
		CString GetPath();
		long GetLanguageID();
		void SetLanguageID(long nNewValue);
		BOOL GetReadOnly();
		long GetType();
		BOOL GetLanguageSpecific();
		void SetLanguageSpecific(BOOL bNewValue);
		void Delete();
	};
	/////////////////////////////////////////////////////////////////////////////
	// ReadabilityStatistics wrapper class

	class ReadabilityStatistics : public COleDispatchDriver
	{
	public:
		ReadabilityStatistics() {}		// Calls COleDispatchDriver default constructor
		ReadabilityStatistics(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		ReadabilityStatistics(const ReadabilityStatistics& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		LPUNKNOWN Get_NewEnum();
		long GetCount();
		LPDISPATCH Item(VARIANT* Index);
	};
	/////////////////////////////////////////////////////////////////////////////
	// ReadabilityStatistic wrapper class

	class ReadabilityStatistic : public COleDispatchDriver
	{
	public:
		ReadabilityStatistic() {}		// Calls COleDispatchDriver default constructor
		ReadabilityStatistic(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		ReadabilityStatistic(const ReadabilityStatistic& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		CString GetName();
		float GetValue();
	};
	/////////////////////////////////////////////////////////////////////////////
	// Versions wrapper class

	class Versions : public COleDispatchDriver
	{
	public:
		Versions() {}		// Calls COleDispatchDriver default constructor
		Versions(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		Versions(const Versions& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		LPUNKNOWN Get_NewEnum();
		long GetCount();
		long GetAutoVersion();
		void SetAutoVersion(long nNewValue);
		LPDISPATCH Item(long Index);
		void Save(VARIANT* Comment);
	};
	/////////////////////////////////////////////////////////////////////////////
	// Version wrapper class

	class Version : public COleDispatchDriver
	{
	public:
		Version() {}		// Calls COleDispatchDriver default constructor
		Version(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		Version(const Version& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		CString GetSavedBy();
		CString GetComment();
		DATE GetDate();
		long GetIndex();
		void Delete();
		LPDISPATCH Open();
	};
	/////////////////////////////////////////////////////////////////////////////
	// Options wrapper class

	class Options : public COleDispatchDriver
	{
	public:
		Options() {}		// Calls COleDispatchDriver default constructor
		Options(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		Options(const Options& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		BOOL GetAllowAccentedUppercase();
		void SetAllowAccentedUppercase(BOOL bNewValue);
		BOOL GetWPHelp();
		void SetWPHelp(BOOL bNewValue);
		BOOL GetWPDocNavKeys();
		void SetWPDocNavKeys(BOOL bNewValue);
		BOOL GetPagination();
		void SetPagination(BOOL bNewValue);
		BOOL GetBlueScreen();
		void SetBlueScreen(BOOL bNewValue);
		BOOL GetEnableSound();
		void SetEnableSound(BOOL bNewValue);
		BOOL GetConfirmConversions();
		void SetConfirmConversions(BOOL bNewValue);
		BOOL GetUpdateLinksAtOpen();
		void SetUpdateLinksAtOpen(BOOL bNewValue);
		BOOL GetSendMailAttach();
		void SetSendMailAttach(BOOL bNewValue);
		long GetMeasurementUnit();
		void SetMeasurementUnit(long nNewValue);
		long GetButtonFieldClicks();
		void SetButtonFieldClicks(long nNewValue);
		BOOL GetShortMenuNames();
		void SetShortMenuNames(BOOL bNewValue);
		BOOL GetRTFInClipboard();
		void SetRTFInClipboard(BOOL bNewValue);
		BOOL GetUpdateFieldsAtPrint();
		void SetUpdateFieldsAtPrint(BOOL bNewValue);
		BOOL GetPrintProperties();
		void SetPrintProperties(BOOL bNewValue);
		BOOL GetPrintFieldCodes();
		void SetPrintFieldCodes(BOOL bNewValue);
		BOOL GetPrintComments();
		void SetPrintComments(BOOL bNewValue);
		BOOL GetPrintHiddenText();
		void SetPrintHiddenText(BOOL bNewValue);
		BOOL GetEnvelopeFeederInstalled();
		BOOL GetUpdateLinksAtPrint();
		void SetUpdateLinksAtPrint(BOOL bNewValue);
		BOOL GetPrintBackground();
		void SetPrintBackground(BOOL bNewValue);
		BOOL GetPrintDrawingObjects();
		void SetPrintDrawingObjects(BOOL bNewValue);
		CString GetDefaultTray();
		void SetDefaultTray(LPCTSTR lpszNewValue);
		long GetDefaultTrayID();
		void SetDefaultTrayID(long nNewValue);
		BOOL GetCreateBackup();
		void SetCreateBackup(BOOL bNewValue);
		BOOL GetAllowFastSave();
		void SetAllowFastSave(BOOL bNewValue);
		BOOL GetSavePropertiesPrompt();
		void SetSavePropertiesPrompt(BOOL bNewValue);
		BOOL GetSaveNormalPrompt();
		void SetSaveNormalPrompt(BOOL bNewValue);
		long GetSaveInterval();
		void SetSaveInterval(long nNewValue);
		BOOL GetBackgroundSave();
		void SetBackgroundSave(BOOL bNewValue);
		long GetInsertedTextMark();
		void SetInsertedTextMark(long nNewValue);
		long GetDeletedTextMark();
		void SetDeletedTextMark(long nNewValue);
		long GetRevisedLinesMark();
		void SetRevisedLinesMark(long nNewValue);
		long GetInsertedTextColor();
		void SetInsertedTextColor(long nNewValue);
		long GetDeletedTextColor();
		void SetDeletedTextColor(long nNewValue);
		long GetRevisedLinesColor();
		void SetRevisedLinesColor(long nNewValue);
		CString GetDefaultFilePath(long Path);
		void SetDefaultFilePath(long Path, LPCTSTR lpszNewValue);
		BOOL GetOvertype();
		void SetOvertype(BOOL bNewValue);
		BOOL GetReplaceSelection();
		void SetReplaceSelection(BOOL bNewValue);
		BOOL GetAllowDragAndDrop();
		void SetAllowDragAndDrop(BOOL bNewValue);
		BOOL GetAutoWordSelection();
		void SetAutoWordSelection(BOOL bNewValue);
		BOOL GetINSKeyForPaste();
		void SetINSKeyForPaste(BOOL bNewValue);
		BOOL GetSmartCutPaste();
		void SetSmartCutPaste(BOOL bNewValue);
		BOOL GetTabIndentKey();
		void SetTabIndentKey(BOOL bNewValue);
		CString GetPictureEditor();
		void SetPictureEditor(LPCTSTR lpszNewValue);
		BOOL GetAnimateScreenMovements();
		void SetAnimateScreenMovements(BOOL bNewValue);
		long GetRevisedPropertiesMark();
		void SetRevisedPropertiesMark(long nNewValue);
		long GetRevisedPropertiesColor();
		void SetRevisedPropertiesColor(long nNewValue);
		BOOL GetSnapToGrid();
		void SetSnapToGrid(BOOL bNewValue);
		BOOL GetSnapToShapes();
		void SetSnapToShapes(BOOL bNewValue);
		float GetGridDistanceHorizontal();
		void SetGridDistanceHorizontal(float newValue);
		float GetGridDistanceVertical();
		void SetGridDistanceVertical(float newValue);
		float GetGridOriginHorizontal();
		void SetGridOriginHorizontal(float newValue);
		float GetGridOriginVertical();
		void SetGridOriginVertical(float newValue);
		BOOL GetInlineConversion();
		void SetInlineConversion(BOOL bNewValue);
		BOOL GetIMEAutomaticControl();
		void SetIMEAutomaticControl(BOOL bNewValue);
		BOOL GetAutoFormatApplyHeadings();
		void SetAutoFormatApplyHeadings(BOOL bNewValue);
		BOOL GetAutoFormatApplyLists();
		void SetAutoFormatApplyLists(BOOL bNewValue);
		BOOL GetAutoFormatApplyBulletedLists();
		void SetAutoFormatApplyBulletedLists(BOOL bNewValue);
		BOOL GetAutoFormatApplyOtherParas();
		void SetAutoFormatApplyOtherParas(BOOL bNewValue);
		BOOL GetAutoFormatReplaceQuotes();
		void SetAutoFormatReplaceQuotes(BOOL bNewValue);
		BOOL GetAutoFormatReplaceSymbols();
		void SetAutoFormatReplaceSymbols(BOOL bNewValue);
		BOOL GetAutoFormatReplaceOrdinals();
		void SetAutoFormatReplaceOrdinals(BOOL bNewValue);
		BOOL GetAutoFormatReplaceFractions();
		void SetAutoFormatReplaceFractions(BOOL bNewValue);
		BOOL GetAutoFormatReplacePlainTextEmphasis();
		void SetAutoFormatReplacePlainTextEmphasis(BOOL bNewValue);
		BOOL GetAutoFormatPreserveStyles();
		void SetAutoFormatPreserveStyles(BOOL bNewValue);
		BOOL GetAutoFormatAsYouTypeApplyHeadings();
		void SetAutoFormatAsYouTypeApplyHeadings(BOOL bNewValue);
		BOOL GetAutoFormatAsYouTypeApplyBorders();
		void SetAutoFormatAsYouTypeApplyBorders(BOOL bNewValue);
		BOOL GetAutoFormatAsYouTypeApplyBulletedLists();
		void SetAutoFormatAsYouTypeApplyBulletedLists(BOOL bNewValue);
		BOOL GetAutoFormatAsYouTypeApplyNumberedLists();
		void SetAutoFormatAsYouTypeApplyNumberedLists(BOOL bNewValue);
		BOOL GetAutoFormatAsYouTypeReplaceQuotes();
		void SetAutoFormatAsYouTypeReplaceQuotes(BOOL bNewValue);
		BOOL GetAutoFormatAsYouTypeReplaceSymbols();
		void SetAutoFormatAsYouTypeReplaceSymbols(BOOL bNewValue);
		BOOL GetAutoFormatAsYouTypeReplaceOrdinals();
		void SetAutoFormatAsYouTypeReplaceOrdinals(BOOL bNewValue);
		BOOL GetAutoFormatAsYouTypeReplaceFractions();
		void SetAutoFormatAsYouTypeReplaceFractions(BOOL bNewValue);
		BOOL GetAutoFormatAsYouTypeReplacePlainTextEmphasis();
		void SetAutoFormatAsYouTypeReplacePlainTextEmphasis(BOOL bNewValue);
		BOOL GetAutoFormatAsYouTypeFormatListItemBeginning();
		void SetAutoFormatAsYouTypeFormatListItemBeginning(BOOL bNewValue);
		BOOL GetAutoFormatAsYouTypeDefineStyles();
		void SetAutoFormatAsYouTypeDefineStyles(BOOL bNewValue);
		BOOL GetAutoFormatPlainTextWordMail();
		void SetAutoFormatPlainTextWordMail(BOOL bNewValue);
		BOOL GetAutoFormatAsYouTypeReplaceHyperlinks();
		void SetAutoFormatAsYouTypeReplaceHyperlinks(BOOL bNewValue);
		BOOL GetAutoFormatReplaceHyperlinks();
		void SetAutoFormatReplaceHyperlinks(BOOL bNewValue);
		long GetDefaultHighlightColorIndex();
		void SetDefaultHighlightColorIndex(long nNewValue);
		long GetDefaultBorderLineStyle();
		void SetDefaultBorderLineStyle(long nNewValue);
		BOOL GetCheckSpellingAsYouType();
		void SetCheckSpellingAsYouType(BOOL bNewValue);
		BOOL GetCheckGrammarAsYouType();
		void SetCheckGrammarAsYouType(BOOL bNewValue);
		BOOL GetIgnoreInternetAndFileAddresses();
		void SetIgnoreInternetAndFileAddresses(BOOL bNewValue);
		BOOL GetShowReadabilityStatistics();
		void SetShowReadabilityStatistics(BOOL bNewValue);
		BOOL GetIgnoreUppercase();
		void SetIgnoreUppercase(BOOL bNewValue);
		BOOL GetIgnoreMixedDigits();
		void SetIgnoreMixedDigits(BOOL bNewValue);
		BOOL GetSuggestFromMainDictionaryOnly();
		void SetSuggestFromMainDictionaryOnly(BOOL bNewValue);
		BOOL GetSuggestSpellingCorrections();
		void SetSuggestSpellingCorrections(BOOL bNewValue);
		long GetDefaultBorderLineWidth();
		void SetDefaultBorderLineWidth(long nNewValue);
		BOOL GetCheckGrammarWithSpelling();
		void SetCheckGrammarWithSpelling(BOOL bNewValue);
		long GetDefaultOpenFormat();
		void SetDefaultOpenFormat(long nNewValue);
		BOOL GetPrintDraft();
		void SetPrintDraft(BOOL bNewValue);
		BOOL GetPrintReverse();
		void SetPrintReverse(BOOL bNewValue);
		BOOL GetMapPaperSize();
		void SetMapPaperSize(BOOL bNewValue);
		BOOL GetAutoFormatAsYouTypeApplyTables();
		void SetAutoFormatAsYouTypeApplyTables(BOOL bNewValue);
		BOOL GetAutoFormatApplyFirstIndents();
		void SetAutoFormatApplyFirstIndents(BOOL bNewValue);
		BOOL GetAutoFormatMatchParentheses();
		void SetAutoFormatMatchParentheses(BOOL bNewValue);
		BOOL GetAutoFormatReplaceFarEastDashes();
		void SetAutoFormatReplaceFarEastDashes(BOOL bNewValue);
		BOOL GetAutoFormatDeleteAutoSpaces();
		void SetAutoFormatDeleteAutoSpaces(BOOL bNewValue);
		BOOL GetAutoFormatAsYouTypeApplyFirstIndents();
		void SetAutoFormatAsYouTypeApplyFirstIndents(BOOL bNewValue);
		BOOL GetAutoFormatAsYouTypeApplyDates();
		void SetAutoFormatAsYouTypeApplyDates(BOOL bNewValue);
		BOOL GetAutoFormatAsYouTypeApplyClosings();
		void SetAutoFormatAsYouTypeApplyClosings(BOOL bNewValue);
		BOOL GetAutoFormatAsYouTypeMatchParentheses();
		void SetAutoFormatAsYouTypeMatchParentheses(BOOL bNewValue);
		BOOL GetAutoFormatAsYouTypeReplaceFarEastDashes();
		void SetAutoFormatAsYouTypeReplaceFarEastDashes(BOOL bNewValue);
		BOOL GetAutoFormatAsYouTypeDeleteAutoSpaces();
		void SetAutoFormatAsYouTypeDeleteAutoSpaces(BOOL bNewValue);
		BOOL GetAutoFormatAsYouTypeInsertClosings();
		void SetAutoFormatAsYouTypeInsertClosings(BOOL bNewValue);
		BOOL GetAutoFormatAsYouTypeAutoLetterWizard();
		void SetAutoFormatAsYouTypeAutoLetterWizard(BOOL bNewValue);
		BOOL GetAutoFormatAsYouTypeInsertOvers();
		void SetAutoFormatAsYouTypeInsertOvers(BOOL bNewValue);
		BOOL GetDisplayGridLines();
		void SetDisplayGridLines(BOOL bNewValue);
		BOOL GetMatchFuzzyCase();
		void SetMatchFuzzyCase(BOOL bNewValue);
		BOOL GetMatchFuzzyByte();
		void SetMatchFuzzyByte(BOOL bNewValue);
		BOOL GetMatchFuzzyHiragana();
		void SetMatchFuzzyHiragana(BOOL bNewValue);
		BOOL GetMatchFuzzySmallKana();
		void SetMatchFuzzySmallKana(BOOL bNewValue);
		BOOL GetMatchFuzzyDash();
		void SetMatchFuzzyDash(BOOL bNewValue);
		BOOL GetMatchFuzzyIterationMark();
		void SetMatchFuzzyIterationMark(BOOL bNewValue);
		BOOL GetMatchFuzzyKanji();
		void SetMatchFuzzyKanji(BOOL bNewValue);
		BOOL GetMatchFuzzyOldKana();
		void SetMatchFuzzyOldKana(BOOL bNewValue);
		BOOL GetMatchFuzzyProlongedSoundMark();
		void SetMatchFuzzyProlongedSoundMark(BOOL bNewValue);
		BOOL GetMatchFuzzyDZ();
		void SetMatchFuzzyDZ(BOOL bNewValue);
		BOOL GetMatchFuzzyBV();
		void SetMatchFuzzyBV(BOOL bNewValue);
		BOOL GetMatchFuzzyTC();
		void SetMatchFuzzyTC(BOOL bNewValue);
		BOOL GetMatchFuzzyHF();
		void SetMatchFuzzyHF(BOOL bNewValue);
		BOOL GetMatchFuzzyZJ();
		void SetMatchFuzzyZJ(BOOL bNewValue);
		BOOL GetMatchFuzzyAY();
		void SetMatchFuzzyAY(BOOL bNewValue);
		BOOL GetMatchFuzzyKiKu();
		void SetMatchFuzzyKiKu(BOOL bNewValue);
		BOOL GetMatchFuzzyPunctuation();
		void SetMatchFuzzyPunctuation(BOOL bNewValue);
		BOOL GetMatchFuzzySpace();
		void SetMatchFuzzySpace(BOOL bNewValue);
		BOOL GetApplyFarEastFontsToAscii();
		void SetApplyFarEastFontsToAscii(BOOL bNewValue);
		BOOL GetConvertHighAnsiToFarEast();
		void SetConvertHighAnsiToFarEast(BOOL bNewValue);
		BOOL GetPrintOddPagesInAscendingOrder();
		void SetPrintOddPagesInAscendingOrder(BOOL bNewValue);
		BOOL GetPrintEvenPagesInAscendingOrder();
		void SetPrintEvenPagesInAscendingOrder(BOOL bNewValue);
		long GetDefaultBorderColorIndex();
		void SetDefaultBorderColorIndex(long nNewValue);
		BOOL GetEnableMisusedWordsDictionary();
		void SetEnableMisusedWordsDictionary(BOOL bNewValue);
		BOOL GetAllowCombinedAuxiliaryForms();
		void SetAllowCombinedAuxiliaryForms(BOOL bNewValue);
		BOOL GetHangulHanjaFastConversion();
		void SetHangulHanjaFastConversion(BOOL bNewValue);
		BOOL GetCheckHangulEndings();
		void SetCheckHangulEndings(BOOL bNewValue);
		BOOL GetEnableHangulHanjaRecentOrdering();
		void SetEnableHangulHanjaRecentOrdering(BOOL bNewValue);
		long GetMultipleWordConversionsMode();
		void SetMultipleWordConversionsMode(long nNewValue);
		void SetWPHelpOptions(VARIANT* CommandKeyHelp, VARIANT* DocNavigationKeys, VARIANT* MouseSimulation, VARIANT* DemoGuidance, VARIANT* DemoSpeed, VARIANT* HelpType);
		long GetDefaultBorderColor();
		void SetDefaultBorderColor(long nNewValue);
		BOOL GetAllowPixelUnits();
		void SetAllowPixelUnits(BOOL bNewValue);
		BOOL GetUseCharacterUnit();
		void SetUseCharacterUnit(BOOL bNewValue);
		BOOL GetAllowCompoundNounProcessing();
		void SetAllowCompoundNounProcessing(BOOL bNewValue);
		BOOL GetAutoKeyboardSwitching();
		void SetAutoKeyboardSwitching(BOOL bNewValue);
		long GetDocumentViewDirection();
		void SetDocumentViewDirection(long nNewValue);
		long GetArabicNumeral();
		void SetArabicNumeral(long nNewValue);
		long GetMonthNames();
		void SetMonthNames(long nNewValue);
		long GetCursorMovement();
		void SetCursorMovement(long nNewValue);
		long GetVisualSelection();
		void SetVisualSelection(long nNewValue);
		BOOL GetShowDiacritics();
		void SetShowDiacritics(BOOL bNewValue);
		BOOL GetShowControlCharacters();
		void SetShowControlCharacters(BOOL bNewValue);
		BOOL GetAddControlCharacters();
		void SetAddControlCharacters(BOOL bNewValue);
		BOOL GetAddBiDirectionalMarksWhenSavingTextFile();
		void SetAddBiDirectionalMarksWhenSavingTextFile(BOOL bNewValue);
		BOOL GetStrictInitialAlefHamza();
		void SetStrictInitialAlefHamza(BOOL bNewValue);
		BOOL GetStrictFinalYaa();
		void SetStrictFinalYaa(BOOL bNewValue);
		long GetHebrewMode();
		void SetHebrewMode(long nNewValue);
		long GetArabicMode();
		void SetArabicMode(long nNewValue);
		BOOL GetAllowClickAndTypeMouse();
		void SetAllowClickAndTypeMouse(BOOL bNewValue);
		BOOL GetUseGermanSpellingReform();
		void SetUseGermanSpellingReform(BOOL bNewValue);
		long GetInterpretHighAnsi();
		void SetInterpretHighAnsi(long nNewValue);
		BOOL GetAddHebDoubleQuote();
		void SetAddHebDoubleQuote(BOOL bNewValue);
		BOOL GetUseDiffDiacColor();
		void SetUseDiffDiacColor(BOOL bNewValue);
		long GetDiacriticColorVal();
		void SetDiacriticColorVal(long nNewValue);
		BOOL GetOptimizeForWord97byDefault();
		void SetOptimizeForWord97byDefault(BOOL bNewValue);
	};
	/////////////////////////////////////////////////////////////////////////////
	// MailMessage wrapper class

	class MailMessage : public COleDispatchDriver
	{
	public:
		MailMessage() {}		// Calls COleDispatchDriver default constructor
		MailMessage(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		MailMessage(const MailMessage& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		void CheckName();
		void Delete();
		void DisplayMoveDialog();
		void DisplayProperties();
		void DisplaySelectNamesDialog();
		void Forward();
		void GoToNext();
		void GoToPrevious();
		void Reply();
		void ReplyAll();
		void ToggleHeader();
	};
	/////////////////////////////////////////////////////////////////////////////
	// ProofreadingErrors wrapper class

	class ProofreadingErrors : public COleDispatchDriver
	{
	public:
		ProofreadingErrors() {}		// Calls COleDispatchDriver default constructor
		ProofreadingErrors(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		ProofreadingErrors(const ProofreadingErrors& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		LPUNKNOWN Get_NewEnum();
		long GetCount();
		long GetType();
		LPDISPATCH Item(long Index);
	};
	/////////////////////////////////////////////////////////////////////////////
	// Mailer wrapper class

	class Mailer : public COleDispatchDriver
	{
	public:
		Mailer() {}		// Calls COleDispatchDriver default constructor
		Mailer(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		Mailer(const Mailer& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		VARIANT GetBCCRecipients();
		void SetBCCRecipients(VARIANT* newValue);
		VARIANT GetCCRecipients();
		void SetCCRecipients(VARIANT* newValue);
		VARIANT GetRecipients();
		void SetRecipients(VARIANT* newValue);
		VARIANT GetEnclosures();
		void SetEnclosures(VARIANT* newValue);
		CString GetSender();
		DATE GetSendDateTime();
		BOOL GetReceived();
		CString GetSubject();
		void SetSubject(LPCTSTR lpszNewValue);
	};
	/////////////////////////////////////////////////////////////////////////////
	// WrapFormat wrapper class

	class WrapFormat : public COleDispatchDriver
	{
	public:
		WrapFormat() {}		// Calls COleDispatchDriver default constructor
		WrapFormat(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		WrapFormat(const WrapFormat& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		long GetType();
		void SetType(long nNewValue);
		long GetSide();
		void SetSide(long nNewValue);
		float GetDistanceTop();
		void SetDistanceTop(float newValue);
		float GetDistanceBottom();
		void SetDistanceBottom(float newValue);
		float GetDistanceLeft();
		void SetDistanceLeft(float newValue);
		float GetDistanceRight();
		void SetDistanceRight(float newValue);
		long GetAllowOverlap();
		void SetAllowOverlap(long nNewValue);
	};
	/////////////////////////////////////////////////////////////////////////////
	// HangulAndAlphabetExceptions wrapper class

	class HangulAndAlphabetExceptions : public COleDispatchDriver
	{
	public:
		HangulAndAlphabetExceptions() {}		// Calls COleDispatchDriver default constructor
		HangulAndAlphabetExceptions(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		HangulAndAlphabetExceptions(const HangulAndAlphabetExceptions& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		LPUNKNOWN Get_NewEnum();
		long GetCount();
		LPDISPATCH Item(VARIANT* Index);
		LPDISPATCH Add(LPCTSTR Name);
	};
	/////////////////////////////////////////////////////////////////////////////
	// HangulAndAlphabetException wrapper class

	class HangulAndAlphabetException : public COleDispatchDriver
	{
	public:
		HangulAndAlphabetException() {}		// Calls COleDispatchDriver default constructor
		HangulAndAlphabetException(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		HangulAndAlphabetException(const HangulAndAlphabetException& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		long GetIndex();
		CString GetName();
		void Delete();
	};
	/////////////////////////////////////////////////////////////////////////////
	// Adjustments wrapper class

	class Adjustments : public COleDispatchDriver
	{
	public:
		Adjustments() {}		// Calls COleDispatchDriver default constructor
		Adjustments(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		Adjustments(const Adjustments& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		long GetCount();
		float GetItem(long Index);
		void SetItem(long Index, float newValue);
	};
	/////////////////////////////////////////////////////////////////////////////
	// CalloutFormat wrapper class

	class CalloutFormat : public COleDispatchDriver
	{
	public:
		CalloutFormat() {}		// Calls COleDispatchDriver default constructor
		CalloutFormat(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CalloutFormat(const CalloutFormat& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		long GetAccent();
		void SetAccent(long nNewValue);
		long GetAngle();
		void SetAngle(long nNewValue);
		long GetAutoAttach();
		void SetAutoAttach(long nNewValue);
		long GetAutoLength();
		long GetBorder();
		void SetBorder(long nNewValue);
		float GetDrop();
		long GetDropType();
		float GetGap();
		void SetGap(float newValue);
		float GetLength();
		long GetType();
		void SetType(long nNewValue);
		void AutomaticLength();
		void CustomDrop(float Drop);
		void CustomLength(float Length);
		void PresetDrop(long DropType);
	};
	/////////////////////////////////////////////////////////////////////////////
	// ColorFormat wrapper class

	class ColorFormat : public COleDispatchDriver
	{
	public:
		ColorFormat() {}		// Calls COleDispatchDriver default constructor
		ColorFormat(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		ColorFormat(const ColorFormat& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		long GetRgb();
		void SetRgb(long nNewValue);
		long GetType();
	};
	/////////////////////////////////////////////////////////////////////////////
	// ConnectorFormat wrapper class

	class ConnectorFormat : public COleDispatchDriver
	{
	public:
		ConnectorFormat() {}		// Calls COleDispatchDriver default constructor
		ConnectorFormat(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		ConnectorFormat(const ConnectorFormat& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		long GetBeginConnected();
		LPDISPATCH GetBeginConnectedShape();
		long GetBeginConnectionSite();
		long GetEndConnected();
		LPDISPATCH GetEndConnectedShape();
		long GetEndConnectionSite();
		LPDISPATCH GetParent();
		long GetType();
		void SetType(long nNewValue);
		void BeginConnect(LPDISPATCH* ConnectedShape, long ConnectionSite);
		void BeginDisconnect();
		void EndConnect(LPDISPATCH* ConnectedShape, long ConnectionSite);
		void EndDisconnect();
	};
	/////////////////////////////////////////////////////////////////////////////
	// FillFormat wrapper class

	class FillFormat : public COleDispatchDriver
	{
	public:
		FillFormat() {}		// Calls COleDispatchDriver default constructor
		FillFormat(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		FillFormat(const FillFormat& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		LPDISPATCH GetBackColor();
		LPDISPATCH GetForeColor();
		long GetGradientColorType();
		float GetGradientDegree();
		long GetGradientStyle();
		long GetGradientVariant();
		long GetPattern();
		long GetPresetGradientType();
		long GetPresetTexture();
		CString GetTextureName();
		long GetTextureType();
		float GetTransparency();
		void SetTransparency(float newValue);
		long GetType();
		long GetVisible();
		void SetVisible(long nNewValue);
		void OneColorGradient(long Style, long Variant, float Degree);
		void Patterned(long Pattern);
		void PresetGradient(long Style, long Variant, long PresetGradientType);
		void PresetTextured(long PresetTexture);
		void Solid();
		void TwoColorGradient(long Style, long Variant);
		void UserPicture(LPCTSTR PictureFile);
		void UserTextured(LPCTSTR TextureFile);
	};
	/////////////////////////////////////////////////////////////////////////////
	// FreeformBuilder wrapper class

	class FreeformBuilder : public COleDispatchDriver
	{
	public:
		FreeformBuilder() {}		// Calls COleDispatchDriver default constructor
		FreeformBuilder(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		FreeformBuilder(const FreeformBuilder& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		void AddNodes(long SegmentType, long EditingType, float X1, float Y1, float X2, float Y2, float X3, float Y3);
		LPDISPATCH ConvertToShape(VARIANT* Anchor);
	};
	/////////////////////////////////////////////////////////////////////////////
	// LineFormat wrapper class

	class LineFormat : public COleDispatchDriver
	{
	public:
		LineFormat() {}		// Calls COleDispatchDriver default constructor
		LineFormat(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		LineFormat(const LineFormat& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		LPDISPATCH GetBackColor();
		long GetBeginArrowheadLength();
		void SetBeginArrowheadLength(long nNewValue);
		long GetBeginArrowheadStyle();
		void SetBeginArrowheadStyle(long nNewValue);
		long GetBeginArrowheadWidth();
		void SetBeginArrowheadWidth(long nNewValue);
		long GetDashStyle();
		void SetDashStyle(long nNewValue);
		long GetEndArrowheadLength();
		void SetEndArrowheadLength(long nNewValue);
		long GetEndArrowheadStyle();
		void SetEndArrowheadStyle(long nNewValue);
		long GetEndArrowheadWidth();
		void SetEndArrowheadWidth(long nNewValue);
		LPDISPATCH GetForeColor();
		long GetPattern();
		void SetPattern(long nNewValue);
		long GetStyle();
		void SetStyle(long nNewValue);
		float GetTransparency();
		void SetTransparency(float newValue);
		long GetVisible();
		void SetVisible(long nNewValue);
		float GetWeight();
		void SetWeight(float newValue);
	};
	/////////////////////////////////////////////////////////////////////////////
	// PictureFormat wrapper class

	class PictureFormat : public COleDispatchDriver
	{
	public:
		PictureFormat() {}		// Calls COleDispatchDriver default constructor
		PictureFormat(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		PictureFormat(const PictureFormat& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		float GetBrightness();
		void SetBrightness(float newValue);
		long GetColorType();
		void SetColorType(long nNewValue);
		float GetContrast();
		void SetContrast(float newValue);
		float GetCropBottom();
		void SetCropBottom(float newValue);
		float GetCropLeft();
		void SetCropLeft(float newValue);
		float GetCropRight();
		void SetCropRight(float newValue);
		float GetCropTop();
		void SetCropTop(float newValue);
		long GetTransparencyColor();
		void SetTransparencyColor(long nNewValue);
		long GetTransparentBackground();
		void SetTransparentBackground(long nNewValue);
		void IncrementBrightness(float Increment);
		void IncrementContrast(float Increment);
	};
	/////////////////////////////////////////////////////////////////////////////
	// ShadowFormat wrapper class

	class ShadowFormat : public COleDispatchDriver
	{
	public:
		ShadowFormat() {}		// Calls COleDispatchDriver default constructor
		ShadowFormat(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		ShadowFormat(const ShadowFormat& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		LPDISPATCH GetForeColor();
		long GetObscured();
		void SetObscured(long nNewValue);
		float GetOffsetX();
		void SetOffsetX(float newValue);
		float GetOffsetY();
		void SetOffsetY(float newValue);
		float GetTransparency();
		void SetTransparency(float newValue);
		long GetType();
		void SetType(long nNewValue);
		long GetVisible();
		void SetVisible(long nNewValue);
		void IncrementOffsetX(float Increment);
		void IncrementOffsetY(float Increment);
	};
	/////////////////////////////////////////////////////////////////////////////
	// ShapeNode wrapper class

	class ShapeNode : public COleDispatchDriver
	{
	public:
		ShapeNode() {}		// Calls COleDispatchDriver default constructor
		ShapeNode(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		ShapeNode(const ShapeNode& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		long GetEditingType();
		VARIANT GetPoints();
		long GetSegmentType();
	};
	/////////////////////////////////////////////////////////////////////////////
	// ShapeNodes wrapper class

	class ShapeNodes : public COleDispatchDriver
	{
	public:
		ShapeNodes() {}		// Calls COleDispatchDriver default constructor
		ShapeNodes(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		ShapeNodes(const ShapeNodes& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		long GetCount();
		LPUNKNOWN Get_NewEnum();
		void Delete(long Index);
		LPDISPATCH Item(VARIANT* Index);
		void SetEditingType(long Index, long EditingType);
		void SetPosition(long Index, float X1, float Y1);
		void SetSegmentType(long Index, long SegmentType);
		void Insert(long Index, long SegmentType, long EditingType, float X1, float Y1, float X2, float Y2, float X3, float Y3);
	};
	/////////////////////////////////////////////////////////////////////////////
	// TextEffectFormat wrapper class

	class TextEffectFormat : public COleDispatchDriver
	{
	public:
		TextEffectFormat() {}		// Calls COleDispatchDriver default constructor
		TextEffectFormat(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		TextEffectFormat(const TextEffectFormat& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		long GetAlignment();
		void SetAlignment(long nNewValue);
		long GetFontBold();
		void SetFontBold(long nNewValue);
		long GetFontItalic();
		void SetFontItalic(long nNewValue);
		CString GetFontName();
		void SetFontName(LPCTSTR lpszNewValue);
		float GetFontSize();
		void SetFontSize(float newValue);
		long GetKernedPairs();
		void SetKernedPairs(long nNewValue);
		long GetNormalizedHeight();
		void SetNormalizedHeight(long nNewValue);
		long GetPresetShape();
		void SetPresetShape(long nNewValue);
		long GetPresetTextEffect();
		void SetPresetTextEffect(long nNewValue);
		long GetRotatedChars();
		void SetRotatedChars(long nNewValue);
		CString GetText();
		void SetText(LPCTSTR lpszNewValue);
		float GetTracking();
		void SetTracking(float newValue);
		void ToggleVerticalText();
	};
	/////////////////////////////////////////////////////////////////////////////
	// ThreeDFormat wrapper class

	class ThreeDFormat : public COleDispatchDriver
	{
	public:
		ThreeDFormat() {}		// Calls COleDispatchDriver default constructor
		ThreeDFormat(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		ThreeDFormat(const ThreeDFormat& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		float GetDepth();
		void SetDepth(float newValue);
		LPDISPATCH GetExtrusionColor();
		long GetExtrusionColorType();
		void SetExtrusionColorType(long nNewValue);
		long GetPerspective();
		void SetPerspective(long nNewValue);
		long GetPresetExtrusionDirection();
		long GetPresetLightingDirection();
		void SetPresetLightingDirection(long nNewValue);
		long GetPresetLightingSoftness();
		void SetPresetLightingSoftness(long nNewValue);
		long GetPresetMaterial();
		void SetPresetMaterial(long nNewValue);
		long GetPresetThreeDFormat();
		float GetRotationX();
		void SetRotationX(float newValue);
		float GetRotationY();
		void SetRotationY(float newValue);
		long GetVisible();
		void SetVisible(long nNewValue);
		void IncrementRotationX(float Increment);
		void IncrementRotationY(float Increment);
		void ResetRotation();
		void SetExtrusionDirection(long PresetExtrusionDirection);
		void SetThreeDFormat(long PresetThreeDFormat);
	};
	/////////////////////////////////////////////////////////////////////////////
	// ApplicationEvents wrapper class

	class ApplicationEvents : public COleDispatchDriver
	{
	public:
		ApplicationEvents() {}		// Calls COleDispatchDriver default constructor
		ApplicationEvents(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		ApplicationEvents(const ApplicationEvents& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
	};
	/////////////////////////////////////////////////////////////////////////////
	// DocumentEvents wrapper class

	class DocumentEvents : public COleDispatchDriver
	{
	public:
		DocumentEvents() {}		// Calls COleDispatchDriver default constructor
		DocumentEvents(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		DocumentEvents(const DocumentEvents& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		void New();
		void Open();
		void Close();
	};
	/////////////////////////////////////////////////////////////////////////////
	// OCXEvents wrapper class

	class OCXEvents : public COleDispatchDriver
	{
	public:
		OCXEvents() {}		// Calls COleDispatchDriver default constructor
		OCXEvents(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		OCXEvents(const OCXEvents& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		void GotFocus();
		void LostFocus();
	};
	/////////////////////////////////////////////////////////////////////////////
	// IApplicationEvents wrapper class

	class IApplicationEvents : public COleDispatchDriver
	{
	public:
		IApplicationEvents() {}		// Calls COleDispatchDriver default constructor
		IApplicationEvents(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		IApplicationEvents(const IApplicationEvents& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		void Quit();
		void DocumentChange();
	};
	/////////////////////////////////////////////////////////////////////////////
	// IApplicationEvents2 wrapper class

	class IApplicationEvents2 : public COleDispatchDriver
	{
	public:
		IApplicationEvents2() {}		// Calls COleDispatchDriver default constructor
		IApplicationEvents2(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		IApplicationEvents2(const IApplicationEvents2& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		void Quit();
		void DocumentChange();
		void DocumentOpen(LPDISPATCH Doc);
		void DocumentBeforeClose(LPDISPATCH Doc, BOOL* Cancel);
		void DocumentBeforePrint(LPDISPATCH Doc, BOOL* Cancel);
		void DocumentBeforeSave(LPDISPATCH Doc, BOOL* SaveAsUI, BOOL* Cancel);
		void NewDocument(LPDISPATCH Doc);
		void WindowActivate(LPDISPATCH Doc, LPDISPATCH Wn);
		void WindowDeactivate(LPDISPATCH Doc, LPDISPATCH Wn);
		void WindowSelectionChange(LPDISPATCH Sel);
		void WindowBeforeRightClick(LPDISPATCH Sel, BOOL* Cancel);
		void WindowBeforeDoubleClick(LPDISPATCH Sel, BOOL* Cancel);
	};
	/////////////////////////////////////////////////////////////////////////////
	// ApplicationEvents2 wrapper class

	class ApplicationEvents2 : public COleDispatchDriver
	{
	public:
		ApplicationEvents2() {}		// Calls COleDispatchDriver default constructor
		ApplicationEvents2(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		ApplicationEvents2(const ApplicationEvents2& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		void Quit();
		void DocumentChange();
		void DocumentOpen(LPDISPATCH Doc);
		void DocumentBeforeClose(LPDISPATCH Doc, BOOL* Cancel);
		void DocumentBeforePrint(LPDISPATCH Doc, BOOL* Cancel);
		void DocumentBeforeSave(LPDISPATCH Doc, BOOL* SaveAsUI, BOOL* Cancel);
		void NewDocument(LPDISPATCH Doc);
		void WindowActivate(LPDISPATCH Doc, LPDISPATCH Wn);
		void WindowDeactivate(LPDISPATCH Doc, LPDISPATCH Wn);
		void WindowSelectionChange(LPDISPATCH Sel);
		void WindowBeforeRightClick(LPDISPATCH Sel, BOOL* Cancel);
		void WindowBeforeDoubleClick(LPDISPATCH Sel, BOOL* Cancel);
	};
	/////////////////////////////////////////////////////////////////////////////
	// EmailAuthor wrapper class

	class EmailAuthor : public COleDispatchDriver
	{
	public:
		EmailAuthor() {}		// Calls COleDispatchDriver default constructor
		EmailAuthor(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		EmailAuthor(const EmailAuthor& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		LPDISPATCH GetStyle();
	};
	/////////////////////////////////////////////////////////////////////////////
	// EmailOptions wrapper class

	class EmailOptions : public COleDispatchDriver
	{
	public:
		EmailOptions() {}		// Calls COleDispatchDriver default constructor
		EmailOptions(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		EmailOptions(const EmailOptions& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		BOOL GetUseThemeStyle();
		void SetUseThemeStyle(BOOL bNewValue);
		CString GetMarkCommentsWith();
		void SetMarkCommentsWith(LPCTSTR lpszNewValue);
		BOOL GetMarkComments();
		void SetMarkComments(BOOL bNewValue);
		LPDISPATCH GetEmailSignature();
		LPDISPATCH GetComposeStyle();
		LPDISPATCH GetReplyStyle();
		CString GetThemeName();
		void SetThemeName(LPCTSTR lpszNewValue);
	};
	/////////////////////////////////////////////////////////////////////////////
	// EmailSignature wrapper class

	class EmailSignature : public COleDispatchDriver
	{
	public:
		EmailSignature() {}		// Calls COleDispatchDriver default constructor
		EmailSignature(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		EmailSignature(const EmailSignature& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		CString GetNewMessageSignature();
		void SetNewMessageSignature(LPCTSTR lpszNewValue);
		CString GetReplyMessageSignature();
		void SetReplyMessageSignature(LPCTSTR lpszNewValue);
	};
	/////////////////////////////////////////////////////////////////////////////
	// Email wrapper class

	class Email : public COleDispatchDriver
	{
	public:
		Email() {}		// Calls COleDispatchDriver default constructor
		Email(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		Email(const Email& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		LPDISPATCH GetCurrentEmailAuthor();
	};
	/////////////////////////////////////////////////////////////////////////////
	// HorizontalLineFormat wrapper class

	class HorizontalLineFormat : public COleDispatchDriver
	{
	public:
		HorizontalLineFormat() {}		// Calls COleDispatchDriver default constructor
		HorizontalLineFormat(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		HorizontalLineFormat(const HorizontalLineFormat& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		float GetPercentWidth();
		void SetPercentWidth(float newValue);
		BOOL GetNoShade();
		void SetNoShade(BOOL bNewValue);
		long GetAlignment();
		void SetAlignment(long nNewValue);
		long GetWidthType();
		void SetWidthType(long nNewValue);
	};
	/////////////////////////////////////////////////////////////////////////////
	// Frameset wrapper class

	class Frameset : public COleDispatchDriver
	{
	public:
		Frameset() {}		// Calls COleDispatchDriver default constructor
		Frameset(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		Frameset(const Frameset& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		LPUNKNOWN Get_NewEnum();
		LPDISPATCH GetParentFrameset();
		long GetType();
		long GetWidthType();
		void SetWidthType(long nNewValue);
		long GetHeightType();
		void SetHeightType(long nNewValue);
		long GetWidth();
		void SetWidth(long nNewValue);
		long GetHeight();
		void SetHeight(long nNewValue);
		long GetChildFramesetCount();
		LPDISPATCH GetChildFramesetItem(long Index);
		float GetFramesetBorderWidth();
		void SetFramesetBorderWidth(float newValue);
		long GetFramesetBorderColor();
		void SetFramesetBorderColor(long nNewValue);
		long GetFrameScrollbarType();
		void SetFrameScrollbarType(long nNewValue);
		BOOL GetFrameResizable();
		void SetFrameResizable(BOOL bNewValue);
		CString GetFrameName();
		void SetFrameName(LPCTSTR lpszNewValue);
		BOOL GetFrameDisplayBorders();
		void SetFrameDisplayBorders(BOOL bNewValue);
		CString GetFrameDefaultURL();
		void SetFrameDefaultURL(LPCTSTR lpszNewValue);
		BOOL GetFrameLinkToFile();
		void SetFrameLinkToFile(BOOL bNewValue);
		LPDISPATCH AddNewFrame(long Where);
		void Delete();
	};
	/////////////////////////////////////////////////////////////////////////////
	// DefaultWebOptions wrapper class

	class DefaultWebOptions : public COleDispatchDriver
	{
	public:
		DefaultWebOptions() {}		// Calls COleDispatchDriver default constructor
		DefaultWebOptions(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		DefaultWebOptions(const DefaultWebOptions& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		BOOL GetOptimizeForBrowser();
		void SetOptimizeForBrowser(BOOL bNewValue);
		long GetBrowserLevel();
		void SetBrowserLevel(long nNewValue);
		BOOL GetRelyOnCSS();
		void SetRelyOnCSS(BOOL bNewValue);
		BOOL GetOrganizeInFolder();
		void SetOrganizeInFolder(BOOL bNewValue);
		BOOL GetUpdateLinksOnSave();
		void SetUpdateLinksOnSave(BOOL bNewValue);
		BOOL GetUseLongFileNames();
		void SetUseLongFileNames(BOOL bNewValue);
		BOOL GetCheckIfOfficeIsHTMLEditor();
		void SetCheckIfOfficeIsHTMLEditor(BOOL bNewValue);
		BOOL GetCheckIfWordIsDefaultHTMLEditor();
		void SetCheckIfWordIsDefaultHTMLEditor(BOOL bNewValue);
		BOOL GetRelyOnVML();
		void SetRelyOnVML(BOOL bNewValue);
		BOOL GetAllowPNG();
		void SetAllowPNG(BOOL bNewValue);
		long GetScreenSize();
		void SetScreenSize(long nNewValue);
		long GetPixelsPerInch();
		void SetPixelsPerInch(long nNewValue);
		long GetEncoding();
		void SetEncoding(long nNewValue);
		BOOL GetAlwaysSaveInDefaultEncoding();
		void SetAlwaysSaveInDefaultEncoding(BOOL bNewValue);
		LPDISPATCH GetFonts();
		CString GetFolderSuffix();
	};
	/////////////////////////////////////////////////////////////////////////////
	// WebOptions wrapper class

	class WebOptions : public COleDispatchDriver
	{
	public:
		WebOptions() {}		// Calls COleDispatchDriver default constructor
		WebOptions(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		WebOptions(const WebOptions& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		BOOL GetOptimizeForBrowser();
		void SetOptimizeForBrowser(BOOL bNewValue);
		long GetBrowserLevel();
		void SetBrowserLevel(long nNewValue);
		BOOL GetRelyOnCSS();
		void SetRelyOnCSS(BOOL bNewValue);
		BOOL GetOrganizeInFolder();
		void SetOrganizeInFolder(BOOL bNewValue);
		BOOL GetUseLongFileNames();
		void SetUseLongFileNames(BOOL bNewValue);
		BOOL GetRelyOnVML();
		void SetRelyOnVML(BOOL bNewValue);
		BOOL GetAllowPNG();
		void SetAllowPNG(BOOL bNewValue);
		long GetScreenSize();
		void SetScreenSize(long nNewValue);
		long GetPixelsPerInch();
		void SetPixelsPerInch(long nNewValue);
		long GetEncoding();
		void SetEncoding(long nNewValue);
		CString GetFolderSuffix();
		void UseDefaultFolderSuffix();
	};
	/////////////////////////////////////////////////////////////////////////////
	// OtherCorrectionsExceptions wrapper class

	class OtherCorrectionsExceptions : public COleDispatchDriver
	{
	public:
		OtherCorrectionsExceptions() {}		// Calls COleDispatchDriver default constructor
		OtherCorrectionsExceptions(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		OtherCorrectionsExceptions(const OtherCorrectionsExceptions& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		LPUNKNOWN Get_NewEnum();
		long GetCount();
		LPDISPATCH Item(VARIANT* Index);
		LPDISPATCH Add(LPCTSTR Name);
	};
	/////////////////////////////////////////////////////////////////////////////
	// OtherCorrectionsException wrapper class

	class OtherCorrectionsException : public COleDispatchDriver
	{
	public:
		OtherCorrectionsException() {}		// Calls COleDispatchDriver default constructor
		OtherCorrectionsException(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		OtherCorrectionsException(const OtherCorrectionsException& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
	public:

	// Operations
	public:
		LPDISPATCH GetApplication();
		long GetCreator();
		LPDISPATCH GetParent();
		long GetIndex();
		CString GetName();
		void Delete();
	};

	
enum WdMailSystem
{
    wdNoMailSystem = 0,
    wdMAPI = 1,
    wdPowerTalk = 2,
    wdMAPIandPowerTalk = 3
};

enum WdTemplateType
{
    wdNormalTemplate = 0,
    wdGlobalTemplate = 1,
    wdAttachedTemplate = 2
};

enum WdContinue
{
    wdContinueDisabled = 0,
    wdResetList = 1,
    wdContinueList = 2
};

enum WdIMEMode
{
    wdIMEModeNoControl = 0,
    wdIMEModeOn = 1,
    wdIMEModeOff = 2,
    wdIMEModeHiragana = 4,
    wdIMEModeKatakana = 5,
    wdIMEModeKatakanaHalf = 6,
    wdIMEModeAlphaFull = 7,
    wdIMEModeAlpha = 8,
    wdIMEModeHangulFull = 9,
    wdIMEModeHangul = 10
};

enum WdBaselineAlignment
{
    wdBaselineAlignTop = 0,
    wdBaselineAlignCenter = 1,
    wdBaselineAlignBaseline = 2,
    wdBaselineAlignFarEast50 = 3,
    wdBaselineAlignAuto = 4
};

enum WdIndexFilter
{
    wdIndexFilterNone = 0,
    wdIndexFilterAiueo = 1,
    wdIndexFilterAkasatana = 2,
    wdIndexFilterChosung = 3,
    wdIndexFilterLow = 4,
    wdIndexFilterMedium = 5,
    wdIndexFilterFull = 6
};

enum WdIndexSortBy
{
    wdIndexSortByStroke = 0,
    wdIndexSortBySyllable = 1
};

enum WdJustificationMode
{
    wdJustificationModeExpand = 0,
    wdJustificationModeCompress = 1,
    wdJustificationModeCompressKana = 2
};

enum WdFarEastLineBreakLevel
{
    wdFarEastLineBreakLevelNormal = 0,
    wdFarEastLineBreakLevelStrict = 1,
    wdFarEastLineBreakLevelCustom = 2
};

enum WdMultipleWordConversionsMode
{
    wdHangulToHanja = 0,
    wdHanjaToHangul = 1
};

enum WdColorIndex
{
    wdAuto = 0,
    wdBlack = 1,
    wdBlue = 2,
    wdTurquoise = 3,
    wdBrightGreen = 4,
    wdPink = 5,
    wdRed = 6,
    wdYellow = 7,
    wdWhite = 8,
    wdDarkBlue = 9,
    wdTeal = 10,
    wdGreen = 11,
    wdViolet = 12,
    wdDarkRed = 13,
    wdDarkYellow = 14,
    wdGray50 = 15,
    wdGray25 = 16,
    wdByAuthor = -1,
    wdNoHighlight = 0
};

enum WdTextureIndex
{
    wdTextureNone = 0,
    wdTexture2Pt5Percent = 25,
    wdTexture5Percent = 50,
    wdTexture7Pt5Percent = 75,
    wdTexture10Percent = 100,
    wdTexture12Pt5Percent = 125,
    wdTexture15Percent = 150,
    wdTexture17Pt5Percent = 175,
    wdTexture20Percent = 200,
    wdTexture22Pt5Percent = 225,
    wdTexture25Percent = 250,
    wdTexture27Pt5Percent = 275,
    wdTexture30Percent = 300,
    wdTexture32Pt5Percent = 325,
    wdTexture35Percent = 350,
    wdTexture37Pt5Percent = 375,
    wdTexture40Percent = 400,
    wdTexture42Pt5Percent = 425,
    wdTexture45Percent = 450,
    wdTexture47Pt5Percent = 475,
    wdTexture50Percent = 500,
    wdTexture52Pt5Percent = 525,
    wdTexture55Percent = 550,
    wdTexture57Pt5Percent = 575,
    wdTexture60Percent = 600,
    wdTexture62Pt5Percent = 625,
    wdTexture65Percent = 650,
    wdTexture67Pt5Percent = 675,
    wdTexture70Percent = 700,
    wdTexture72Pt5Percent = 725,
    wdTexture75Percent = 750,
    wdTexture77Pt5Percent = 775,
    wdTexture80Percent = 800,
    wdTexture82Pt5Percent = 825,
    wdTexture85Percent = 850,
    wdTexture87Pt5Percent = 875,
    wdTexture90Percent = 900,
    wdTexture92Pt5Percent = 925,
    wdTexture95Percent = 950,
    wdTexture97Pt5Percent = 975,
    wdTextureSolid = 1000,
    wdTextureDarkHorizontal = -1,
    wdTextureDarkVertical = -2,
    wdTextureDarkDiagonalDown = -3,
    wdTextureDarkDiagonalUp = -4,
    wdTextureDarkCross = -5,
    wdTextureDarkDiagonalCross = -6,
    wdTextureHorizontal = -7,
    wdTextureVertical = -8,
    wdTextureDiagonalDown = -9,
    wdTextureDiagonalUp = -10,
    wdTextureCross = -11,
    wdTextureDiagonalCross = -12
};

enum WdUnderline
{
    wdUnderlineNone = 0,
    wdUnderlineSingle = 1,
    wdUnderlineWords = 2,
    wdUnderlineDouble = 3,
    wdUnderlineDotted = 4,
    wdUnderlineThick = 6,
    wdUnderlineDash = 7,
    wdUnderlineDotDash = 9,
    wdUnderlineDotDotDash = 10,
    wdUnderlineWavy = 11,
    wdUnderlineWavyHeavy = 27,
    wdUnderlineDottedHeavy = 20,
    wdUnderlineDashHeavy = 23,
    wdUnderlineDotDashHeavy = 25,
    wdUnderlineDotDotDashHeavy = 26,
    wdUnderlineDashLong = 39,
    wdUnderlineDashLongHeavy = 55,
    wdUnderlineWavyDouble = 43
};

enum WdEmphasisMark
{
    wdEmphasisMarkNone = 0,
    wdEmphasisMarkOverSolidCircle = 1,
    wdEmphasisMarkOverComma = 2,
    wdEmphasisMarkOverWhiteCircle = 3,
    wdEmphasisMarkUnderSolidCircle = 4
};

enum WdInternationalIndex
{
    wdListSeparator = 17,
    wdDecimalSeparator = 18,
    wdThousandsSeparator = 19,
    wdCurrencyCode = 20,
    wd24HourClock = 21,
    wdInternationalAM = 22,
    wdInternationalPM = 23,
    wdTimeSeparator = 24,
    wdDateSeparator = 25,
    wdProductLanguageID = 26
};

enum WdAutoMacros
{
    wdAutoExec = 0,
    wdAutoNew = 1,
    wdAutoOpen = 2,
    wdAutoClose = 3,
    wdAutoExit = 4,
    wdAutoSync = 5
};

enum WdCaptionPosition
{
    wdCaptionPositionAbove = 0,
    wdCaptionPositionBelow = 1
};

enum WdCountry
{
    wdUS = 1,
    wdCanada = 2,
    wdLatinAmerica = 3,
    wdNetherlands = 31,
    wdFrance = 33,
    wdSpain = 34,
    wdItaly = 39,
    wdUK = 44,
    wdDenmark = 45,
    wdSweden = 46,
    wdNorway = 47,
    wdGermany = 49,
    wdPeru = 51,
    wdMexico = 52,
    wdArgentina = 54,
    wdBrazil = 55,
    wdChile = 56,
    wdVenezuela = 58,
    wdJapan = 81,
    wdTaiwan = 886,
    wdChina = 86,
    wdKorea = 82,
    wdFinland = 358,
    wdIceland = 354
};

enum WdHeadingSeparator
{
    wdHeadingSeparatorNone = 0,
    wdHeadingSeparatorBlankLine = 1,
    wdHeadingSeparatorLetter = 2,
    wdHeadingSeparatorLetterLow = 3,
    wdHeadingSeparatorLetterFull = 4
};

enum WdSeparatorType
{
    wdSeparatorHyphen = 0,
    wdSeparatorPeriod = 1,
    wdSeparatorColon = 2,
    wdSeparatorEmDash = 3,
    wdSeparatorEnDash = 4
};

enum WdPageNumberAlignment
{
    wdAlignPageNumberLeft = 0,
    wdAlignPageNumberCenter = 1,
    wdAlignPageNumberRight = 2,
    wdAlignPageNumberInside = 3,
    wdAlignPageNumberOutside = 4
};

enum WdBorderType
{
    wdBorderTop = -1,
    wdBorderLeft = -2,
    wdBorderBottom = -3,
    wdBorderRight = -4,
    wdBorderHorizontal = -5,
    wdBorderVertical = -6,
    wdBorderDiagonalDown = -7,
    wdBorderDiagonalUp = -8
};

enum WdBorderTypeHID
{
    emptyenum = 0
};

enum WdFramePosition
{
    wdFrameTop = -999999,
    wdFrameLeft = -999998,
    wdFrameBottom = -999997,
    wdFrameRight = -999996,
    wdFrameCenter = -999995,
    wdFrameInside = -999994,
    wdFrameOutside = -999993
};

enum WdAnimation
{
    wdAnimationNone = 0,
    wdAnimationLasVegasLights = 1,
    wdAnimationBlinkingBackground = 2,
    wdAnimationSparkleText = 3,
    wdAnimationMarchingBlackAnts = 4,
    wdAnimationMarchingRedAnts = 5,
    wdAnimationShimmer = 6
};

enum WdCharacterCase
{
    wdNextCase = -1,
    wdLowerCase = 0,
    wdUpperCase = 1,
    wdTitleWord = 2,
    wdTitleSentence = 4,
    wdToggleCase = 5,
    wdHalfWidth = 6,
    wdFullWidth = 7,
    wdKatakana = 8,
    wdHiragana = 9
};

enum WdCharacterCaseHID
{
//  emptyenum = 0
};

enum WdSummaryMode
{
    wdSummaryModeHighlight = 0,
    wdSummaryModeHideAllButSummary = 1,
    wdSummaryModeInsert = 2,
    wdSummaryModeCreateNew = 3
};

enum WdSummaryLength
{
    wd10Sentences = -2,
    wd20Sentences = -3,
    wd100Words = -4,
    wd500Words = -5,
    wd10Percent = -6,
    wd25Percent = -7,
    wd50Percent = -8,
    wd75Percent = -9
};

enum WdStyleType
{
    wdStyleTypeParagraph = 1,
    wdStyleTypeCharacter = 2,
    wdStyleTypeTable = 3,
    wdStyleTypeList = 4
};

enum WdUnits
{
    wdCharacter = 1,
    wdWord = 2,
    wdSentence = 3,
    wdParagraph = 4,
    wdLine = 5,
    wdStory = 6,
    wdScreen = 7,
    wdSection = 8,
    wdColumn = 9,
    wdRow = 10,
    wdWindow = 11,
    wdCell = 12,
    wdCharacterFormatting = 13,
    wdParagraphFormatting = 14,
    wdTable = 15,
    wdItem = 16
};

enum WdGoToItem
{
    wdGoToBookmark = -1,
    wdGoToSection = 0,
    wdGoToPage = 1,
    wdGoToTable = 2,
    wdGoToLine = 3,
    wdGoToFootnote = 4,
    wdGoToEndnote = 5,
    wdGoToComment = 6,
    wdGoToField = 7,
    wdGoToGraphic = 8,
    wdGoToObject = 9,
    wdGoToEquation = 10,
    wdGoToHeading = 11,
    wdGoToPercent = 12,
    wdGoToSpellingError = 13,
    wdGoToGrammaticalError = 14,
    wdGoToProofreadingError = 15
};

enum WdGoToDirection
{
    wdGoToFirst = 1,
    wdGoToLast = -1,
    wdGoToNext = 2,
    wdGoToRelative = 2,
    wdGoToPrevious = 3,
    wdGoToAbsolute = 1
};

enum WdCollapseDirection
{
    wdCollapseStart = 1,
    wdCollapseEnd = 0
};

enum WdRowHeightRule
{
    wdRowHeightAuto = 0,
    wdRowHeightAtLeast = 1,
    wdRowHeightExactly = 2
};

enum WdFrameSizeRule
{
    wdFrameAuto = 0,
    wdFrameAtLeast = 1,
    wdFrameExact = 2
};

enum WdInsertCells
{
    wdInsertCellsShiftRight = 0,
    wdInsertCellsShiftDown = 1,
    wdInsertCellsEntireRow = 2,
    wdInsertCellsEntireColumn = 3
};

enum WdDeleteCells
{
    wdDeleteCellsShiftLeft = 0,
    wdDeleteCellsShiftUp = 1,
    wdDeleteCellsEntireRow = 2,
    wdDeleteCellsEntireColumn = 3
};

enum WdListApplyTo
{
    wdListApplyToWholeList = 0,
    wdListApplyToThisPointForward = 1,
    wdListApplyToSelection = 2
};

enum WdAlertLevel
{
    wdAlertsNone = 0,
    wdAlertsMessageBox = -2,
    wdAlertsAll = -1
};

enum WdCursorType
{
    wdCursorWait = 0,
    wdCursorIBeam = 1,
    wdCursorNormal = 2,
    wdCursorNorthwestArrow = 3
};

enum WdEnableCancelKey
{
    wdCancelDisabled = 0,
    wdCancelInterrupt = 1
};

enum WdRulerStyle
{
    wdAdjustNone = 0,
    wdAdjustProportional = 1,
    wdAdjustFirstColumn = 2,
    wdAdjustSameWidth = 3
};

enum WdParagraphAlignment
{
    wdAlignParagraphLeft = 0,
    wdAlignParagraphCenter = 1,
    wdAlignParagraphRight = 2,
    wdAlignParagraphJustify = 3,
    wdAlignParagraphDistribute = 4,
    wdAlignParagraphJustifyMed = 5,
    wdAlignParagraphJustifyHi = 7,
    wdAlignParagraphJustifyLow = 8,
    wdAlignParagraphThaiJustify = 9
};

enum WdParagraphAlignmentHID
{
//  emptyenum = 0
};

enum WdListLevelAlignment
{
    wdListLevelAlignLeft = 0,
    wdListLevelAlignCenter = 1,
    wdListLevelAlignRight = 2
};

enum WdRowAlignment
{
    wdAlignRowLeft = 0,
    wdAlignRowCenter = 1,
    wdAlignRowRight = 2
};

enum WdTabAlignment
{
    wdAlignTabLeft = 0,
    wdAlignTabCenter = 1,
    wdAlignTabRight = 2,
    wdAlignTabDecimal = 3,
    wdAlignTabBar = 4,
    wdAlignTabList = 6
};

enum WdVerticalAlignment
{
    wdAlignVerticalTop = 0,
    wdAlignVerticalCenter = 1,
    wdAlignVerticalJustify = 2,
    wdAlignVerticalBottom = 3
};

enum WdCellVerticalAlignment
{
    wdCellAlignVerticalTop = 0,
    wdCellAlignVerticalCenter = 1,
    wdCellAlignVerticalBottom = 3
};

enum WdTrailingCharacter
{
    wdTrailingTab = 0,
    wdTrailingSpace = 1,
    wdTrailingNone = 2
};

enum WdListGalleryType
{
    wdBulletGallery = 1,
    wdNumberGallery = 2,
    wdOutlineNumberGallery = 3
};

enum WdListNumberStyle
{
    wdListNumberStyleArabic = 0,
    wdListNumberStyleUppercaseRoman = 1,
    wdListNumberStyleLowercaseRoman = 2,
    wdListNumberStyleUppercaseLetter = 3,
    wdListNumberStyleLowercaseLetter = 4,
    wdListNumberStyleOrdinal = 5,
    wdListNumberStyleCardinalText = 6,
    wdListNumberStyleOrdinalText = 7,
    wdListNumberStyleKanji = 10,
    wdListNumberStyleKanjiDigit = 11,
    wdListNumberStyleAiueoHalfWidth = 12,
    wdListNumberStyleIrohaHalfWidth = 13,
    wdListNumberStyleArabicFullWidth = 14,
    wdListNumberStyleKanjiTraditional = 16,
    wdListNumberStyleKanjiTraditional2 = 17,
    wdListNumberStyleNumberInCircle = 18,
    wdListNumberStyleAiueo = 20,
    wdListNumberStyleIroha = 21,
    wdListNumberStyleArabicLZ = 22,
    wdListNumberStyleBullet = 23,
    wdListNumberStyleGanada = 24,
    wdListNumberStyleChosung = 25,
    wdListNumberStyleGBNum1 = 26,
    wdListNumberStyleGBNum2 = 27,
    wdListNumberStyleGBNum3 = 28,
    wdListNumberStyleGBNum4 = 29,
    wdListNumberStyleZodiac1 = 30,
    wdListNumberStyleZodiac2 = 31,
    wdListNumberStyleZodiac3 = 32,
    wdListNumberStyleTradChinNum1 = 33,
    wdListNumberStyleTradChinNum2 = 34,
    wdListNumberStyleTradChinNum3 = 35,
    wdListNumberStyleTradChinNum4 = 36,
    wdListNumberStyleSimpChinNum1 = 37,
    wdListNumberStyleSimpChinNum2 = 38,
    wdListNumberStyleSimpChinNum3 = 39,
    wdListNumberStyleSimpChinNum4 = 40,
    wdListNumberStyleHanjaRead = 41,
    wdListNumberStyleHanjaReadDigit = 42,
    wdListNumberStyleHangul = 43,
    wdListNumberStyleHanja = 44,
    wdListNumberStyleHebrew1 = 45,
    wdListNumberStyleArabic1 = 46,
    wdListNumberStyleHebrew2 = 47,
    wdListNumberStyleArabic2 = 48,
    wdListNumberStyleHindiLetter1 = 49,
    wdListNumberStyleHindiLetter2 = 50,
    wdListNumberStyleHindiArabic = 51,
    wdListNumberStyleHindiCardinalText = 52,
    wdListNumberStyleThaiLetter = 53,
    wdListNumberStyleThaiArabic = 54,
    wdListNumberStyleThaiCardinalText = 55,
    wdListNumberStyleVietCardinalText = 56,
    wdListNumberStyleLowercaseRussian = 58,
    wdListNumberStyleUppercaseRussian = 59,
    wdListNumberStylePictureBullet = 249,
    wdListNumberStyleLegal = 253,
    wdListNumberStyleLegalLZ = 254,
    wdListNumberStyleNone = 255
};

enum WdListNumberStyleHID
{
//  emptyenum = 0
};

enum WdNoteNumberStyle
{
    wdNoteNumberStyleArabic = 0,
    wdNoteNumberStyleUppercaseRoman = 1,
    wdNoteNumberStyleLowercaseRoman = 2,
    wdNoteNumberStyleUppercaseLetter = 3,
    wdNoteNumberStyleLowercaseLetter = 4,
    wdNoteNumberStyleSymbol = 9,
    wdNoteNumberStyleArabicFullWidth = 14,
    wdNoteNumberStyleKanji = 10,
    wdNoteNumberStyleKanjiDigit = 11,
    wdNoteNumberStyleKanjiTraditional = 16,
    wdNoteNumberStyleNumberInCircle = 18,
    wdNoteNumberStyleHanjaRead = 41,
    wdNoteNumberStyleHanjaReadDigit = 42,
    wdNoteNumberStyleTradChinNum1 = 33,
    wdNoteNumberStyleTradChinNum2 = 34,
    wdNoteNumberStyleSimpChinNum1 = 37,
    wdNoteNumberStyleSimpChinNum2 = 38,
    wdNoteNumberStyleHebrewLetter1 = 45,
    wdNoteNumberStyleArabicLetter1 = 46,
    wdNoteNumberStyleHebrewLetter2 = 47,
    wdNoteNumberStyleArabicLetter2 = 48,
    wdNoteNumberStyleHindiLetter1 = 49,
    wdNoteNumberStyleHindiLetter2 = 50,
    wdNoteNumberStyleHindiArabic = 51,
    wdNoteNumberStyleHindiCardinalText = 52,
    wdNoteNumberStyleThaiLetter = 53,
    wdNoteNumberStyleThaiArabic = 54,
    wdNoteNumberStyleThaiCardinalText = 55,
    wdNoteNumberStyleVietCardinalText = 56
};

enum WdNoteNumberStyleHID
{
//  emptyenum = 0
};

enum WdCaptionNumberStyle
{
    wdCaptionNumberStyleArabic = 0,
    wdCaptionNumberStyleUppercaseRoman = 1,
    wdCaptionNumberStyleLowercaseRoman = 2,
    wdCaptionNumberStyleUppercaseLetter = 3,
    wdCaptionNumberStyleLowercaseLetter = 4,
    wdCaptionNumberStyleArabicFullWidth = 14,
    wdCaptionNumberStyleKanji = 10,
    wdCaptionNumberStyleKanjiDigit = 11,
    wdCaptionNumberStyleKanjiTraditional = 16,
    wdCaptionNumberStyleNumberInCircle = 18,
    wdCaptionNumberStyleGanada = 24,
    wdCaptionNumberStyleChosung = 25,
    wdCaptionNumberStyleZodiac1 = 30,
    wdCaptionNumberStyleZodiac2 = 31,
    wdCaptionNumberStyleHanjaRead = 41,
    wdCaptionNumberStyleHanjaReadDigit = 42,
    wdCaptionNumberStyleTradChinNum2 = 34,
    wdCaptionNumberStyleTradChinNum3 = 35,
    wdCaptionNumberStyleSimpChinNum2 = 38,
    wdCaptionNumberStyleSimpChinNum3 = 39,
    wdCaptionNumberStyleHebrewLetter1 = 45,
    wdCaptionNumberStyleArabicLetter1 = 46,
    wdCaptionNumberStyleHebrewLetter2 = 47,
    wdCaptionNumberStyleArabicLetter2 = 48,
    wdCaptionNumberStyleHindiLetter1 = 49,
    wdCaptionNumberStyleHindiLetter2 = 50,
    wdCaptionNumberStyleHindiArabic = 51,
    wdCaptionNumberStyleHindiCardinalText = 52,
    wdCaptionNumberStyleThaiLetter = 53,
    wdCaptionNumberStyleThaiArabic = 54,
    wdCaptionNumberStyleThaiCardinalText = 55,
    wdCaptionNumberStyleVietCardinalText = 56
};

enum WdCaptionNumberStyleHID
{
//  emptyenum = 0
};

enum WdPageNumberStyle
{
    wdPageNumberStyleArabic = 0,
    wdPageNumberStyleUppercaseRoman = 1,
    wdPageNumberStyleLowercaseRoman = 2,
    wdPageNumberStyleUppercaseLetter = 3,
    wdPageNumberStyleLowercaseLetter = 4,
    wdPageNumberStyleArabicFullWidth = 14,
    wdPageNumberStyleKanji = 10,
    wdPageNumberStyleKanjiDigit = 11,
    wdPageNumberStyleKanjiTraditional = 16,
    wdPageNumberStyleNumberInCircle = 18,
    wdPageNumberStyleHanjaRead = 41,
    wdPageNumberStyleHanjaReadDigit = 42,
    wdPageNumberStyleTradChinNum1 = 33,
    wdPageNumberStyleTradChinNum2 = 34,
    wdPageNumberStyleSimpChinNum1 = 37,
    wdPageNumberStyleSimpChinNum2 = 38,
    wdPageNumberStyleHebrewLetter1 = 45,
    wdPageNumberStyleArabicLetter1 = 46,
    wdPageNumberStyleHebrewLetter2 = 47,
    wdPageNumberStyleArabicLetter2 = 48,
    wdPageNumberStyleHindiLetter1 = 49,
    wdPageNumberStyleHindiLetter2 = 50,
    wdPageNumberStyleHindiArabic = 51,
    wdPageNumberStyleHindiCardinalText = 52,
    wdPageNumberStyleThaiLetter = 53,
    wdPageNumberStyleThaiArabic = 54,
    wdPageNumberStyleThaiCardinalText = 55,
    wdPageNumberStyleVietCardinalText = 56,
    wdPageNumberStyleNumberInDash = 57
};

enum WdPageNumberStyleHID
{
//  emptyenum = 0
};

enum WdStatistic
{
    wdStatisticWords = 0,
    wdStatisticLines = 1,
    wdStatisticPages = 2,
    wdStatisticCharacters = 3,
    wdStatisticParagraphs = 4,
    wdStatisticCharactersWithSpaces = 5,
    wdStatisticFarEastCharacters = 6
};

enum WdStatisticHID
{
//  emptyenum = 0
};

enum WdBuiltInProperty
{
    wdPropertyTitle = 1,
    wdPropertySubject = 2,
    wdPropertyAuthor = 3,
    wdPropertyKeywords = 4,
    wdPropertyComments = 5,
    wdPropertyTemplate = 6,
    wdPropertyLastAuthor = 7,
    wdPropertyRevision = 8,
    wdPropertyAppName = 9,
    wdPropertyTimeLastPrinted = 10,
    wdPropertyTimeCreated = 11,
    wdPropertyTimeLastSaved = 12,
    wdPropertyVBATotalEdit = 13,
    wdPropertyPages = 14,
    wdPropertyWords = 15,
    wdPropertyCharacters = 16,
    wdPropertySecurity = 17,
    wdPropertyCategory = 18,
    wdPropertyFormat = 19,
    wdPropertyManager = 20,
    wdPropertyCompany = 21,
    wdPropertyBytes = 22,
    wdPropertyLines = 23,
    wdPropertyParas = 24,
    wdPropertySlides = 25,
    wdPropertyNotes = 26,
    wdPropertyHiddenSlides = 27,
    wdPropertyMMClips = 28,
    wdPropertyHyperlinkBase = 29,
    wdPropertyCharsWSpaces = 30
};

enum WdLineSpacing
{
    wdLineSpaceSingle = 0,
    wdLineSpace1pt5 = 1,
    wdLineSpaceDouble = 2,
    wdLineSpaceAtLeast = 3,
    wdLineSpaceExactly = 4,
    wdLineSpaceMultiple = 5
};

enum WdNumberType
{
    wdNumberParagraph = 1,
    wdNumberListNum = 2,
    wdNumberAllNumbers = 3
};

enum WdListType
{
    wdListNoNumbering = 0,
    wdListListNumOnly = 1,
    wdListBullet = 2,
    wdListSimpleNumbering = 3,
    wdListOutlineNumbering = 4,
    wdListMixedNumbering = 5,
    wdListPictureBullet = 6
};

enum WdStoryType
{
    wdMainTextStory = 1,
    wdFootnotesStory = 2,
    wdEndnotesStory = 3,
    wdCommentsStory = 4,
    wdTextFrameStory = 5,
    wdEvenPagesHeaderStory = 6,
    wdPrimaryHeaderStory = 7,
    wdEvenPagesFooterStory = 8,
    wdPrimaryFooterStory = 9,
    wdFirstPageHeaderStory = 10,
    wdFirstPageFooterStory = 11,
    wdFootnoteSeparatorStory = 12,
    wdFootnoteContinuationSeparatorStory = 13,
    wdFootnoteContinuationNoticeStory = 14,
    wdEndnoteSeparatorStory = 15,
    wdEndnoteContinuationSeparatorStory = 16,
    wdEndnoteContinuationNoticeStory = 17
};

enum WdSaveFormat
{
    wdFormatDocument = 0,
    wdFormatTemplate = 1,
    wdFormatText = 2,
    wdFormatTextLineBreaks = 3,
    wdFormatDOSText = 4,
    wdFormatDOSTextLineBreaks = 5,
    wdFormatRTF = 6,
    wdFormatUnicodeText = 7,
    wdFormatEncodedText = 7,
    wdFormatHTML = 8,
    wdFormatWebArchive = 9,
    wdFormatFilteredHTML = 10,
    wdFormatXML = 11
};

enum WdOpenFormat
{
    wdOpenFormatAuto = 0,
    wdOpenFormatDocument = 1,
    wdOpenFormatTemplate = 2,
    wdOpenFormatRTF = 3,
    wdOpenFormatText = 4,
    wdOpenFormatUnicodeText = 5,
    wdOpenFormatEncodedText = 5,
    wdOpenFormatAllWord = 6,
    wdOpenFormatWebPages = 7,
    wdOpenFormatXML = 8
};

enum WdHeaderFooterIndex
{
    wdHeaderFooterPrimary = 1,
    wdHeaderFooterFirstPage = 2,
    wdHeaderFooterEvenPages = 3
};

enum WdTocFormat
{
    wdTOCTemplate = 0,
    wdTOCClassic = 1,
    wdTOCDistinctive = 2,
    wdTOCFancy = 3,
    wdTOCModern = 4,
    wdTOCFormal = 5,
    wdTOCSimple = 6
};

enum WdTofFormat
{
    wdTOFTemplate = 0,
    wdTOFClassic = 1,
    wdTOFDistinctive = 2,
    wdTOFCentered = 3,
    wdTOFFormal = 4,
    wdTOFSimple = 5
};

enum WdToaFormat
{
    wdTOATemplate = 0,
    wdTOAClassic = 1,
    wdTOADistinctive = 2,
    wdTOAFormal = 3,
    wdTOASimple = 4
};

enum WdLineStyle
{
    wdLineStyleNone = 0,
    wdLineStyleSingle = 1,
    wdLineStyleDot = 2,
    wdLineStyleDashSmallGap = 3,
    wdLineStyleDashLargeGap = 4,
    wdLineStyleDashDot = 5,
    wdLineStyleDashDotDot = 6,
    wdLineStyleDouble = 7,
    wdLineStyleTriple = 8,
    wdLineStyleThinThickSmallGap = 9,
    wdLineStyleThickThinSmallGap = 10,
    wdLineStyleThinThickThinSmallGap = 11,
    wdLineStyleThinThickMedGap = 12,
    wdLineStyleThickThinMedGap = 13,
    wdLineStyleThinThickThinMedGap = 14,
    wdLineStyleThinThickLargeGap = 15,
    wdLineStyleThickThinLargeGap = 16,
    wdLineStyleThinThickThinLargeGap = 17,
    wdLineStyleSingleWavy = 18,
    wdLineStyleDoubleWavy = 19,
    wdLineStyleDashDotStroked = 20,
    wdLineStyleEmboss3D = 21,
    wdLineStyleEngrave3D = 22,
    wdLineStyleOutset = 23,
    wdLineStyleInset = 24
};

enum WdLineWidth
{
    wdLineWidth025pt = 2,
    wdLineWidth050pt = 4,
    wdLineWidth075pt = 6,
    wdLineWidth100pt = 8,
    wdLineWidth150pt = 12,
    wdLineWidth225pt = 18,
    wdLineWidth300pt = 24,
    wdLineWidth450pt = 36,
    wdLineWidth600pt = 48
};

enum WdBreakType
{
    wdSectionBreakNextPage = 2,
    wdSectionBreakContinuous = 3,
    wdSectionBreakEvenPage = 4,
    wdSectionBreakOddPage = 5,
    wdLineBreak = 6,
    wdPageBreak = 7,
    wdColumnBreak = 8,
    wdLineBreakClearLeft = 9,
    wdLineBreakClearRight = 10,
    wdTextWrappingBreak = 11
};

enum WdTabLeader
{
    wdTabLeaderSpaces = 0,
    wdTabLeaderDots = 1,
    wdTabLeaderDashes = 2,
    wdTabLeaderLines = 3,
    wdTabLeaderHeavy = 4,
    wdTabLeaderMiddleDot = 5
};

enum WdTabLeaderHID
{
//  emptyenum = 0
};

enum WdMeasurementUnits
{
    wdInches = 0,
    wdCentimeters = 1,
    wdMillimeters = 2,
    wdPoints = 3,
    wdPicas = 4
};

enum WdMeasurementUnitsHID
{
//  emptyenum = 0
};

enum WdDropPosition
{
    wdDropNone = 0,
    wdDropNormal = 1,
    wdDropMargin = 2
};

enum WdNumberingRule
{
    wdRestartContinuous = 0,
    wdRestartSection = 1,
    wdRestartPage = 2
};

enum WdFootnoteLocation
{
    wdBottomOfPage = 0,
    wdBeneathText = 1
};

enum WdEndnoteLocation
{
    wdEndOfSection = 0,
    wdEndOfDocument = 1
};

enum WdSortSeparator
{
    wdSortSeparateByTabs = 0,
    wdSortSeparateByCommas = 1,
    wdSortSeparateByDefaultTableSeparator = 2
};

enum WdTableFieldSeparator
{
    wdSeparateByParagraphs = 0,
    wdSeparateByTabs = 1,
    wdSeparateByCommas = 2,
    wdSeparateByDefaultListSeparator = 3
};

enum WdSortFieldType
{
    wdSortFieldAlphanumeric = 0,
    wdSortFieldNumeric = 1,
    wdSortFieldDate = 2,
    wdSortFieldSyllable = 3,
    wdSortFieldJapanJIS = 4,
    wdSortFieldStroke = 5,
    wdSortFieldKoreaKS = 6
};

enum WdSortFieldTypeHID
{
//  emptyenum = 0
};

enum WdSortOrder
{
    wdSortOrderAscending = 0,
    wdSortOrderDescending = 1
};

enum WdTableFormat
{
    wdTableFormatNone = 0,
    wdTableFormatSimple1 = 1,
    wdTableFormatSimple2 = 2,
    wdTableFormatSimple3 = 3,
    wdTableFormatClassic1 = 4,
    wdTableFormatClassic2 = 5,
    wdTableFormatClassic3 = 6,
    wdTableFormatClassic4 = 7,
    wdTableFormatColorful1 = 8,
    wdTableFormatColorful2 = 9,
    wdTableFormatColorful3 = 10,
    wdTableFormatColumns1 = 11,
    wdTableFormatColumns2 = 12,
    wdTableFormatColumns3 = 13,
    wdTableFormatColumns4 = 14,
    wdTableFormatColumns5 = 15,
    wdTableFormatGrid1 = 16,
    wdTableFormatGrid2 = 17,
    wdTableFormatGrid3 = 18,
    wdTableFormatGrid4 = 19,
    wdTableFormatGrid5 = 20,
    wdTableFormatGrid6 = 21,
    wdTableFormatGrid7 = 22,
    wdTableFormatGrid8 = 23,
    wdTableFormatList1 = 24,
    wdTableFormatList2 = 25,
    wdTableFormatList3 = 26,
    wdTableFormatList4 = 27,
    wdTableFormatList5 = 28,
    wdTableFormatList6 = 29,
    wdTableFormatList7 = 30,
    wdTableFormatList8 = 31,
    wdTableFormat3DEffects1 = 32,
    wdTableFormat3DEffects2 = 33,
    wdTableFormat3DEffects3 = 34,
    wdTableFormatContemporary = 35,
    wdTableFormatElegant = 36,
    wdTableFormatProfessional = 37,
    wdTableFormatSubtle1 = 38,
    wdTableFormatSubtle2 = 39,
    wdTableFormatWeb1 = 40,
    wdTableFormatWeb2 = 41,
    wdTableFormatWeb3 = 42
};

enum WdTableFormatApply
{
    wdTableFormatApplyBorders = 1,
    wdTableFormatApplyShading = 2,
    wdTableFormatApplyFont = 4,
    wdTableFormatApplyColor = 8,
    wdTableFormatApplyAutoFit = 16,
    wdTableFormatApplyHeadingRows = 32,
    wdTableFormatApplyLastRow = 64,
    wdTableFormatApplyFirstColumn = 128,
    wdTableFormatApplyLastColumn = 256
};

enum WdLanguageID
{
    wdLanguageNone = 0,
    wdNoProofing = 1024,
    wdAfrikaans = 1078,
    wdAlbanian = 1052,
    wdAmharic = 1118,
    wdArabicAlgeria = 5121,
    wdArabicBahrain = 15361,
    wdArabicEgypt = 3073,
    wdArabicIraq = 2049,
    wdArabicJordan = 11265,
    wdArabicKuwait = 13313,
    wdArabicLebanon = 12289,
    wdArabicLibya = 4097,
    wdArabicMorocco = 6145,
    wdArabicOman = 8193,
    wdArabicQatar = 16385,
    wdArabic = 1025,
    wdArabicSyria = 10241,
    wdArabicTunisia = 7169,
    wdArabicUAE = 14337,
    wdArabicYemen = 9217,
    wdArmenian = 1067,
    wdAssamese = 1101,
    wdAzeriCyrillic = 2092,
    wdAzeriLatin = 1068,
    wdBasque = 1069,
    wdByelorussian = 1059,
    wdBengali = 1093,
    wdBulgarian = 1026,
    wdBurmese = 1109,
    wdCatalan = 1027,
    wdCherokee = 1116,
    wdChineseHongKongSAR = 3076,
    wdChineseMacaoSAR = 5124,
    wdSimplifiedChinese = 2052,
    wdChineseSingapore = 4100,
    wdTraditionalChinese = 1028,
    wdCroatian = 1050,
    wdCzech = 1029,
    wdDanish = 1030,
    wdDivehi = 1125,
    wdBelgianDutch = 2067,
    wdDutch = 1043,
    wdDzongkhaBhutan = 2129,
    wdEdo = 1126,
    wdEnglishAUS = 3081,
    wdEnglishBelize = 10249,
    wdEnglishCanadian = 4105,
    wdEnglishCaribbean = 9225,
    wdEnglishIreland = 6153,
    wdEnglishJamaica = 8201,
    wdEnglishNewZealand = 5129,
    wdEnglishPhilippines = 13321,
    wdEnglishSouthAfrica = 7177,
    wdEnglishTrinidadTobago = 11273,
    wdEnglishUK = 2057,
    wdEnglishUS = 1033,
    wdEnglishZimbabwe = 12297,
    wdEnglishIndonesia = 14345,
    wdEstonian = 1061,
    wdFaeroese = 1080,
    wdFarsi = 1065,
    wdFilipino = 1124,
    wdFinnish = 1035,
    wdFulfulde = 1127,
    wdBelgianFrench = 2060,
    wdFrenchCameroon = 11276,
    wdFrenchCanadian = 3084,
    wdFrenchCotedIvoire = 12300,
    wdFrench = 1036,
    wdFrenchLuxembourg = 5132,
    wdFrenchMali = 13324,
    wdFrenchMonaco = 6156,
    wdFrenchReunion = 8204,
    wdFrenchSenegal = 10252,
    wdFrenchMorocco = 14348,
    wdFrenchHaiti = 15372,
    wdSwissFrench = 4108,
    wdFrenchWestIndies = 7180,
    wdFrenchZaire = 9228,
    wdFrisianNetherlands = 1122,
    wdGaelicIreland = 2108,
    wdGaelicScotland = 1084,
    wdGalician = 1110,
    wdGeorgian = 1079,
    wdGermanAustria = 3079,
    wdGerman = 1031,
    wdGermanLiechtenstein = 5127,
    wdGermanLuxembourg = 4103,
    wdSwissGerman = 2055,
    wdGreek = 1032,
    wdGuarani = 1140,
    wdGujarati = 1095,
    wdHausa = 1128,
    wdHawaiian = 1141,
    wdHebrew = 1037,
    wdHindi = 1081,
    wdHungarian = 1038,
    wdIbibio = 1129,
    wdIcelandic = 1039,
    wdIgbo = 1136,
    wdIndonesian = 1057,
    wdInuktitut = 1117,
    wdItalian = 1040,
    wdSwissItalian = 2064,
    wdJapanese = 1041,
    wdKannada = 1099,
    wdKanuri = 1137,
    wdKashmiri = 1120,
    wdKazakh = 1087,
    wdKhmer = 1107,
    wdKirghiz = 1088,
    wdKonkani = 1111,
    wdKorean = 1042,
    wdKyrgyz = 1088,
    wdLao = 1108,
    wdLatin = 1142,
    wdLatvian = 1062,
    wdLithuanian = 1063,
    wdMacedonian = 1071,
    wdMalaysian = 1086,
    wdMalayBruneiDarussalam = 2110,
    wdMalayalam = 1100,
    wdMaltese = 1082,
    wdManipuri = 1112,
    wdMarathi = 1102,
    wdMongolian = 1104,
    wdNepali = 1121,
    wdNorwegianBokmol = 1044,
    wdNorwegianNynorsk = 2068,
    wdOriya = 1096,
    wdOromo = 1138,
    wdPashto = 1123,
    wdPolish = 1045,
    wdBrazilianPortuguese = 1046,
    wdPortuguese = 2070,
    wdPunjabi = 1094,
    wdRhaetoRomanic = 1047,
    wdRomanianMoldova = 2072,
    wdRomanian = 1048,
    wdRussianMoldova = 2073,
    wdRussian = 1049,
    wdSamiLappish = 1083,
    wdSanskrit = 1103,
    wdSerbianCyrillic = 3098,
    wdSerbianLatin = 2074,
    wdSinhalese = 1115,
    wdSindhi = 1113,
    wdSindhiPakistan = 2137,
    wdSlovak = 1051,
    wdSlovenian = 1060,
    wdSomali = 1143,
    wdSorbian = 1070,
    wdSpanishArgentina = 11274,
    wdSpanishBolivia = 16394,
    wdSpanishChile = 13322,
    wdSpanishColombia = 9226,
    wdSpanishCostaRica = 5130,
    wdSpanishDominicanRepublic = 7178,
    wdSpanishEcuador = 12298,
    wdSpanishElSalvador = 17418,
    wdSpanishGuatemala = 4106,
    wdSpanishHonduras = 18442,
    wdMexicanSpanish = 2058,
    wdSpanishNicaragua = 19466,
    wdSpanishPanama = 6154,
    wdSpanishParaguay = 15370,
    wdSpanishPeru = 10250,
    wdSpanishPuertoRico = 20490,
    wdSpanishModernSort = 3082,
    wdSpanish = 1034,
    wdSpanishUruguay = 14346,
    wdSpanishVenezuela = 8202,
    wdSesotho = 1072,
    wdSutu = 1072,
    wdSwahili = 1089,
    wdSwedishFinland = 2077,
    wdSwedish = 1053,
    wdSyriac = 1114,
    wdTajik = 1064,
    wdTamazight = 1119,
    wdTamazightLatin = 2143,
    wdTamil = 1097,
    wdTatar = 1092,
    wdTelugu = 1098,
    wdThai = 1054,
    wdTibetan = 1105,
    wdTigrignaEthiopic = 1139,
    wdTigrignaEritrea = 2163,
    wdTsonga = 1073,
    wdTswana = 1074,
    wdTurkish = 1055,
    wdTurkmen = 1090,
    wdUkrainian = 1058,
    wdUrdu = 1056,
    wdUzbekCyrillic = 2115,
    wdUzbekLatin = 1091,
    wdVenda = 1075,
    wdVietnamese = 1066,
    wdWelsh = 1106,
    wdXhosa = 1076,
    wdYi = 1144,
    wdYiddish = 1085,
    wdYoruba = 1130,
    wdZulu = 1077
};

enum WdFieldType
{
    wdFieldEmpty = -1,
    wdFieldRef = 3,
    wdFieldIndexEntry = 4,
    wdFieldFootnoteRef = 5,
    wdFieldSet = 6,
    wdFieldIf = 7,
    wdFieldIndex = 8,
    wdFieldTOCEntry = 9,
    wdFieldStyleRef = 10,
    wdFieldRefDoc = 11,
    wdFieldSequence = 12,
    wdFieldTOC = 13,
    wdFieldInfo = 14,
    wdFieldTitle = 15,
    wdFieldSubject = 16,
    wdFieldAuthor = 17,
    wdFieldKeyWord = 18,
    wdFieldComments = 19,
    wdFieldLastSavedBy = 20,
    wdFieldCreateDate = 21,
    wdFieldSaveDate = 22,
    wdFieldPrintDate = 23,
    wdFieldRevisionNum = 24,
    wdFieldEditTime = 25,
    wdFieldNumPages = 26,
    wdFieldNumWords = 27,
    wdFieldNumChars = 28,
    wdFieldFileName = 29,
    wdFieldTemplate = 30,
    wdFieldDate = 31,
    wdFieldTime = 32,
    wdFieldPage = 33,
    wdFieldExpression = 34,
    wdFieldQuote = 35,
    wdFieldInclude = 36,
    wdFieldPageRef = 37,
    wdFieldAsk = 38,
    wdFieldFillIn = 39,
    wdFieldData = 40,
    wdFieldNext = 41,
    wdFieldNextIf = 42,
    wdFieldSkipIf = 43,
    wdFieldMergeRec = 44,
    wdFieldDDE = 45,
    wdFieldDDEAuto = 46,
    wdFieldGlossary = 47,
    wdFieldPrint = 48,
    wdFieldFormula = 49,
    wdFieldGoToButton = 50,
    wdFieldMacroButton = 51,
    wdFieldAutoNumOutline = 52,
    wdFieldAutoNumLegal = 53,
    wdFieldAutoNum = 54,
    wdFieldImport = 55,
    wdFieldLink = 56,
    wdFieldSymbol = 57,
    wdFieldEmbed = 58,
    wdFieldMergeField = 59,
    wdFieldUserName = 60,
    wdFieldUserInitials = 61,
    wdFieldUserAddress = 62,
    wdFieldBarCode = 63,
    wdFieldDocVariable = 64,
    wdFieldSection = 65,
    wdFieldSectionPages = 66,
    wdFieldIncludePicture = 67,
    wdFieldIncludeText = 68,
    wdFieldFileSize = 69,
    wdFieldFormTextInput = 70,
    wdFieldFormCheckBox = 71,
    wdFieldNoteRef = 72,
    wdFieldTOA = 73,
    wdFieldTOAEntry = 74,
    wdFieldMergeSeq = 75,
    wdFieldPrivate = 77,
    wdFieldDatabase = 78,
    wdFieldAutoText = 79,
    wdFieldCompare = 80,
    wdFieldAddin = 81,
    wdFieldSubscriber = 82,
    wdFieldFormDropDown = 83,
    wdFieldAdvance = 84,
    wdFieldDocProperty = 85,
    wdFieldOCX = 87,
    wdFieldHyperlink = 88,
    wdFieldAutoTextList = 89,
    wdFieldListNum = 90,
    wdFieldHTMLActiveX = 91,
    wdFieldBidiOutline = 92,
    wdFieldAddressBlock = 93,
    wdFieldGreetingLine = 94,
    wdFieldShape = 95
};

enum WdBuiltinStyle
{
    wdStyleNormal = -1,
    wdStyleEnvelopeAddress = -37,
    wdStyleEnvelopeReturn = -38,
    wdStyleBodyText = -67,
    wdStyleHeading1 = -2,
    wdStyleHeading2 = -3,
    wdStyleHeading3 = -4,
    wdStyleHeading4 = -5,
    wdStyleHeading5 = -6,
    wdStyleHeading6 = -7,
    wdStyleHeading7 = -8,
    wdStyleHeading8 = -9,
    wdStyleHeading9 = -10,
    wdStyleIndex1 = -11,
    wdStyleIndex2 = -12,
    wdStyleIndex3 = -13,
    wdStyleIndex4 = -14,
    wdStyleIndex5 = -15,
    wdStyleIndex6 = -16,
    wdStyleIndex7 = -17,
    wdStyleIndex8 = -18,
    wdStyleIndex9 = -19,
    wdStyleTOC1 = -20,
    wdStyleTOC2 = -21,
    wdStyleTOC3 = -22,
    wdStyleTOC4 = -23,
    wdStyleTOC5 = -24,
    wdStyleTOC6 = -25,
    wdStyleTOC7 = -26,
    wdStyleTOC8 = -27,
    wdStyleTOC9 = -28,
    wdStyleNormalIndent = -29,
    wdStyleFootnoteText = -30,
    wdStyleCommentText = -31,
    wdStyleHeader = -32,
    wdStyleFooter = -33,
    wdStyleIndexHeading = -34,
    wdStyleCaption = -35,
    wdStyleTableOfFigures = -36,
    wdStyleFootnoteReference = -39,
    wdStyleCommentReference = -40,
    wdStyleLineNumber = -41,
    wdStylePageNumber = -42,
    wdStyleEndnoteReference = -43,
    wdStyleEndnoteText = -44,
    wdStyleTableOfAuthorities = -45,
    wdStyleMacroText = -46,
    wdStyleTOAHeading = -47,
    wdStyleList = -48,
    wdStyleListBullet = -49,
    wdStyleListNumber = -50,
    wdStyleList2 = -51,
    wdStyleList3 = -52,
    wdStyleList4 = -53,
    wdStyleList5 = -54,
    wdStyleListBullet2 = -55,
    wdStyleListBullet3 = -56,
    wdStyleListBullet4 = -57,
    wdStyleListBullet5 = -58,
    wdStyleListNumber2 = -59,
    wdStyleListNumber3 = -60,
    wdStyleListNumber4 = -61,
    wdStyleListNumber5 = -62,
    wdStyleTitle = -63,
    wdStyleClosing = -64,
    wdStyleSignature = -65,
    wdStyleDefaultParagraphFont = -66,
    wdStyleBodyTextIndent = -68,
    wdStyleListContinue = -69,
    wdStyleListContinue2 = -70,
    wdStyleListContinue3 = -71,
    wdStyleListContinue4 = -72,
    wdStyleListContinue5 = -73,
    wdStyleMessageHeader = -74,
    wdStyleSubtitle = -75,
    wdStyleSalutation = -76,
    wdStyleDate = -77,
    wdStyleBodyTextFirstIndent = -78,
    wdStyleBodyTextFirstIndent2 = -79,
    wdStyleNoteHeading = -80,
    wdStyleBodyText2 = -81,
    wdStyleBodyText3 = -82,
    wdStyleBodyTextIndent2 = -83,
    wdStyleBodyTextIndent3 = -84,
    wdStyleBlockQuotation = -85,
    wdStyleHyperlink = -86,
    wdStyleHyperlinkFollowed = -87,
    wdStyleStrong = -88,
    wdStyleEmphasis = -89,
    wdStyleNavPane = -90,
    wdStylePlainText = -91,
    wdStyleHtmlNormal = -95,
    wdStyleHtmlAcronym = -96,
    wdStyleHtmlAddress = -97,
    wdStyleHtmlCite = -98,
    wdStyleHtmlCode = -99,
    wdStyleHtmlDfn = -100,
    wdStyleHtmlKbd = -101,
    wdStyleHtmlPre = -102,
    wdStyleHtmlSamp = -103,
    wdStyleHtmlTt = -104,
    wdStyleHtmlVar = -105,
    wdStyleNormalTable = -106
};

enum WdWordDialogTab
{
    wdDialogToolsOptionsTabView = 204,
    wdDialogToolsOptionsTabGeneral = 203,
    wdDialogToolsOptionsTabEdit = 224,
    wdDialogToolsOptionsTabPrint = 208,
    wdDialogToolsOptionsTabSave = 209,
    wdDialogToolsOptionsTabProofread = 211,
    wdDialogToolsOptionsTabTrackChanges = 386,
    wdDialogToolsOptionsTabUserInfo = 213,
    wdDialogToolsOptionsTabCompatibility = 525,
    wdDialogToolsOptionsTabTypography = 739,
    wdDialogToolsOptionsTabFileLocations = 225,
    wdDialogToolsOptionsTabFuzzy = 790,
    wdDialogToolsOptionsTabHangulHanjaConversion = 786,
    wdDialogToolsOptionsTabBidi = 1029,
    wdDialogToolsOptionsTabSecurity = 1361,
    wdDialogFilePageSetupTabMargins = 150000,
    wdDialogFilePageSetupTabPaper = 150001,
    wdDialogFilePageSetupTabLayout = 150003,
    wdDialogFilePageSetupTabCharsLines = 150004,
    wdDialogInsertSymbolTabSymbols = 200000,
    wdDialogInsertSymbolTabSpecialCharacters = 200001,
    wdDialogNoteOptionsTabAllFootnotes = 300000,
    wdDialogNoteOptionsTabAllEndnotes = 300001,
    wdDialogInsertIndexAndTablesTabIndex = 400000,
    wdDialogInsertIndexAndTablesTabTableOfContents = 400001,
    wdDialogInsertIndexAndTablesTabTableOfFigures = 400002,
    wdDialogInsertIndexAndTablesTabTableOfAuthorities = 400003,
    wdDialogOrganizerTabStyles = 500000,
    wdDialogOrganizerTabAutoText = 500001,
    wdDialogOrganizerTabCommandBars = 500002,
    wdDialogOrganizerTabMacros = 500003,
    wdDialogFormatFontTabFont = 600000,
    wdDialogFormatFontTabCharacterSpacing = 600001,
    wdDialogFormatFontTabAnimation = 600002,
    wdDialogFormatBordersAndShadingTabBorders = 700000,
    wdDialogFormatBordersAndShadingTabPageBorder = 700001,
    wdDialogFormatBordersAndShadingTabShading = 700002,
    wdDialogToolsEnvelopesAndLabelsTabEnvelopes = 800000,
    wdDialogToolsEnvelopesAndLabelsTabLabels = 800001,
    wdDialogFormatParagraphTabIndentsAndSpacing = 1000000,
    wdDialogFormatParagraphTabTextFlow = 1000001,
    wdDialogFormatParagraphTabTeisai = 1000002,
    wdDialogFormatDrawingObjectTabColorsAndLines = 1200000,
    wdDialogFormatDrawingObjectTabSize = 1200001,
    wdDialogFormatDrawingObjectTabPosition = 1200002,
    wdDialogFormatDrawingObjectTabWrapping = 1200003,
    wdDialogFormatDrawingObjectTabPicture = 1200004,
    wdDialogFormatDrawingObjectTabTextbox = 1200005,
    wdDialogFormatDrawingObjectTabWeb = 1200006,
    wdDialogFormatDrawingObjectTabHR = 1200007,
    wdDialogToolsAutoCorrectExceptionsTabFirstLetter = 1400000,
    wdDialogToolsAutoCorrectExceptionsTabInitialCaps = 1400001,
    wdDialogToolsAutoCorrectExceptionsTabHangulAndAlphabet = 1400002,
    wdDialogToolsAutoCorrectExceptionsTabIac = 1400003,
    wdDialogFormatBulletsAndNumberingTabBulleted = 1500000,
    wdDialogFormatBulletsAndNumberingTabNumbered = 1500001,
    wdDialogFormatBulletsAndNumberingTabOutlineNumbered = 1500002,
    wdDialogLetterWizardTabLetterFormat = 1600000,
    wdDialogLetterWizardTabRecipientInfo = 1600001,
    wdDialogLetterWizardTabOtherElements = 1600002,
    wdDialogLetterWizardTabSenderInfo = 1600003,
    wdDialogToolsAutoManagerTabAutoCorrect = 1700000,
    wdDialogToolsAutoManagerTabAutoFormatAsYouType = 1700001,
    wdDialogToolsAutoManagerTabAutoText = 1700002,
    wdDialogToolsAutoManagerTabAutoFormat = 1700003,
    wdDialogToolsAutoManagerTabSmartTags = 1700004,
    wdDialogTablePropertiesTabTable = 1800000,
    wdDialogTablePropertiesTabRow = 1800001,
    wdDialogTablePropertiesTabColumn = 1800002,
    wdDialogTablePropertiesTabCell = 1800003,
    wdDialogEmailOptionsTabSignature = 1900000,
    wdDialogEmailOptionsTabStationary = 1900001,
    wdDialogEmailOptionsTabQuoting = 1900002,
    wdDialogWebOptionsBrowsers = 2000000,
    wdDialogWebOptionsGeneral = 2000000,
    wdDialogWebOptionsFiles = 2000001,
    wdDialogWebOptionsPictures = 2000002,
    wdDialogWebOptionsEncoding = 2000003,
    wdDialogWebOptionsFonts = 2000004,
    wdDialogToolsOptionsTabAcetate = 1266,
    wdDialogTemplates = 2100000,
    wdDialogTemplatesXMLSchema = 2100001,
    wdDialogTemplatesXMLExpansionPacks = 2100002,
    wdDialogTemplatesLinkedCSS = 2100003
};

enum WdWordDialogTabHID
{
    wdDialogFilePageSetupTabPaperSize = 150001,
    wdDialogFilePageSetupTabPaperSource = 150002
};

enum WdWordDialog
{
    wdDialogHelpAbout = 9,
    wdDialogHelpWordPerfectHelp = 10,
    wdDialogDocumentStatistics = 78,
    wdDialogFileNew = 79,
    wdDialogFileOpen = 80,
    wdDialogMailMergeOpenDataSource = 81,
    wdDialogMailMergeOpenHeaderSource = 82,
    wdDialogFileSaveAs = 84,
    wdDialogFileSummaryInfo = 86,
    wdDialogToolsTemplates = 87,
    wdDialogFilePrint = 88,
    wdDialogFilePrintSetup = 97,
    wdDialogFileFind = 99,
    wdDialogFormatAddrFonts = 103,
    wdDialogEditPasteSpecial = 111,
    wdDialogEditFind = 112,
    wdDialogEditReplace = 117,
    wdDialogEditStyle = 120,
    wdDialogEditLinks = 124,
    wdDialogEditObject = 125,
    wdDialogTableToText = 128,
    wdDialogTextToTable = 127,
    wdDialogTableInsertTable = 129,
    wdDialogTableInsertCells = 130,
    wdDialogTableInsertRow = 131,
    wdDialogTableDeleteCells = 133,
    wdDialogTableSplitCells = 137,
    wdDialogTableRowHeight = 142,
    wdDialogTableColumnWidth = 143,
    wdDialogToolsCustomize = 152,
    wdDialogInsertBreak = 159,
    wdDialogInsertSymbol = 162,
    wdDialogInsertPicture = 163,
    wdDialogInsertFile = 164,
    wdDialogInsertDateTime = 165,
    wdDialogInsertField = 166,
    wdDialogInsertMergeField = 167,
    wdDialogInsertBookmark = 168,
    wdDialogMarkIndexEntry = 169,
    wdDialogInsertIndex = 170,
    wdDialogInsertTableOfContents = 171,
    wdDialogInsertObject = 172,
    wdDialogToolsCreateEnvelope = 173,
    wdDialogFormatFont = 174,
    wdDialogFormatParagraph = 175,
    wdDialogFormatSectionLayout = 176,
    wdDialogFormatColumns = 177,
    wdDialogFileDocumentLayout = 178,
    wdDialogFilePageSetup = 178,
    wdDialogFormatTabs = 179,
    wdDialogFormatStyle = 180,
    wdDialogFormatDefineStyleFont = 181,
    wdDialogFormatDefineStylePara = 182,
    wdDialogFormatDefineStyleTabs = 183,
    wdDialogFormatDefineStyleFrame = 184,
    wdDialogFormatDefineStyleBorders = 185,
    wdDialogFormatDefineStyleLang = 186,
    wdDialogFormatPicture = 187,
    wdDialogToolsLanguage = 188,
    wdDialogFormatBordersAndShading = 189,
    wdDialogFormatFrame = 190,
    wdDialogToolsThesaurus = 194,
    wdDialogToolsHyphenation = 195,
    wdDialogToolsBulletsNumbers = 196,
    wdDialogToolsHighlightChanges = 197,
    wdDialogToolsRevisions = 197,
    wdDialogToolsCompareDocuments = 198,
    wdDialogTableSort = 199,
    wdDialogToolsOptionsGeneral = 203,
    wdDialogToolsOptionsView = 204,
    wdDialogToolsAdvancedSettings = 206,
    wdDialogToolsOptionsPrint = 208,
    wdDialogToolsOptionsSave = 209,
    wdDialogToolsOptionsSpellingAndGrammar = 211,
    wdDialogToolsOptionsUserInfo = 213,
    wdDialogToolsMacroRecord = 214,
    wdDialogToolsMacro = 215,
    wdDialogWindowActivate = 220,
    wdDialogFormatRetAddrFonts = 221,
    wdDialogOrganizer = 222,
    wdDialogToolsOptionsEdit = 224,
    wdDialogToolsOptionsFileLocations = 225,
    wdDialogToolsWordCount = 228,
    wdDialogControlRun = 235,
    wdDialogInsertPageNumbers = 294,
    wdDialogFormatPageNumber = 298,
    wdDialogCopyFile = 300,
    wdDialogFormatChangeCase = 322,
    wdDialogUpdateTOC = 331,
    wdDialogInsertDatabase = 341,
    wdDialogTableFormula = 348,
    wdDialogFormFieldOptions = 353,
    wdDialogInsertCaption = 357,
    wdDialogInsertCaptionNumbering = 358,
    wdDialogInsertAutoCaption = 359,
    wdDialogFormFieldHelp = 361,
    wdDialogInsertCrossReference = 367,
    wdDialogInsertFootnote = 370,
    wdDialogNoteOptions = 373,
    wdDialogToolsAutoCorrect = 378,
    wdDialogToolsOptionsTrackChanges = 386,
    wdDialogConvertObject = 392,
    wdDialogInsertAddCaption = 402,
    wdDialogConnect = 420,
    wdDialogToolsCustomizeKeyboard = 432,
    wdDialogToolsCustomizeMenus = 433,
    wdDialogToolsMergeDocuments = 435,
    wdDialogMarkTableOfContentsEntry = 442,
    wdDialogFileMacPageSetupGX = 444,
    wdDialogFilePrintOneCopy = 445,
    wdDialogEditFrame = 458,
    wdDialogMarkCitation = 463,
    wdDialogTableOfContentsOptions = 470,
    wdDialogInsertTableOfAuthorities = 471,
    wdDialogInsertTableOfFigures = 472,
    wdDialogInsertIndexAndTables = 473,
    wdDialogInsertFormField = 483,
    wdDialogFormatDropCap = 488,
    wdDialogToolsCreateLabels = 489,
    wdDialogToolsProtectDocument = 503,
    wdDialogFormatStyleGallery = 505,
    wdDialogToolsAcceptRejectChanges = 506,
    wdDialogHelpWordPerfectHelpOptions = 511,
    wdDialogToolsUnprotectDocument = 521,
    wdDialogToolsOptionsCompatibility = 525,
    wdDialogTableOfCaptionsOptions = 551,
    wdDialogTableAutoFormat = 563,
    wdDialogMailMergeFindRecord = 569,
    wdDialogReviewAfmtRevisions = 570,
    wdDialogViewZoom = 577,
    wdDialogToolsProtectSection = 578,
    wdDialogFontSubstitution = 581,
    wdDialogInsertSubdocument = 583,
    wdDialogNewToolbar = 586,
    wdDialogToolsEnvelopesAndLabels = 607,
    wdDialogFormatCallout = 610,
    wdDialogTableFormatCell = 612,
    wdDialogToolsCustomizeMenuBar = 615,
    wdDialogFileRoutingSlip = 624,
    wdDialogEditTOACategory = 625,
    wdDialogToolsManageFields = 631,
    wdDialogDrawSnapToGrid = 633,
    wdDialogDrawAlign = 634,
    wdDialogMailMergeCreateDataSource = 642,
    wdDialogMailMergeCreateHeaderSource = 643,
    wdDialogMailMerge = 676,
    wdDialogMailMergeCheck = 677,
    wdDialogMailMergeHelper = 680,
    wdDialogMailMergeQueryOptions = 681,
    wdDialogFileMacPageSetup = 685,
    wdDialogListCommands = 723,
    wdDialogEditCreatePublisher = 732,
    wdDialogEditSubscribeTo = 733,
    wdDialogEditPublishOptions = 735,
    wdDialogEditSubscribeOptions = 736,
    wdDialogFileMacCustomPageSetupGX = 737,
    wdDialogToolsOptionsTypography = 739,
    wdDialogToolsAutoCorrectExceptions = 762,
    wdDialogToolsOptionsAutoFormatAsYouType = 778,
    wdDialogMailMergeUseAddressBook = 779,
    wdDialogToolsHangulHanjaConversion = 784,
    wdDialogToolsOptionsFuzzy = 790,
    wdDialogEditGoToOld = 811,
    wdDialogInsertNumber = 812,
    wdDialogLetterWizard = 821,
    wdDialogFormatBulletsAndNumbering = 824,
    wdDialogToolsSpellingAndGrammar = 828,
    wdDialogToolsCreateDirectory = 833,
    wdDialogTableWrapping = 854,
    wdDialogFormatTheme = 855,
    wdDialogTableProperties = 861,
    wdDialogEmailOptions = 863,
    wdDialogCreateAutoText = 872,
    wdDialogToolsAutoSummarize = 874,
    wdDialogToolsGrammarSettings = 885,
    wdDialogEditGoTo = 896,
    wdDialogWebOptions = 898,
    wdDialogInsertHyperlink = 925,
    wdDialogToolsAutoManager = 915,
    wdDialogFileVersions = 945,
    wdDialogToolsOptionsAutoFormat = 959,
    wdDialogFormatDrawingObject = 960,
    wdDialogToolsOptions = 974,
    wdDialogFitText = 983,
    wdDialogEditAutoText = 985,
    wdDialogPhoneticGuide = 986,
    wdDialogToolsDictionary = 989,
    wdDialogFileSaveVersion = 1007,
    wdDialogToolsOptionsBidi = 1029,
    wdDialogFrameSetProperties = 1074,
    wdDialogTableTableOptions = 1080,
    wdDialogTableCellOptions = 1081,
    wdDialogIMESetDefault = 1094,
    wdDialogTCSCTranslator = 1156,
    wdDialogHorizontalInVertical = 1160,
    wdDialogTwoLinesInOne = 1161,
    wdDialogFormatEncloseCharacters = 1162,
    wdDialogConsistencyChecker = 1121,
    wdDialogToolsOptionsSmartTag = 1395,
    wdDialogFormatStylesCustom = 1248,
    wdDialogCSSLinks = 1261,
    wdDialogInsertWebComponent = 1324,
    wdDialogToolsOptionsEditCopyPaste = 1356,
    wdDialogToolsOptionsSecurity = 1361,
    wdDialogSearch = 1363,
    wdDialogShowRepairs = 1381,
    wdDialogMailMergeInsertAsk = 4047,
    wdDialogMailMergeInsertFillIn = 4048,
    wdDialogMailMergeInsertIf = 4049,
    wdDialogMailMergeInsertNextIf = 4053,
    wdDialogMailMergeInsertSet = 4054,
    wdDialogMailMergeInsertSkipIf = 4055,
    wdDialogMailMergeFieldMapping = 1304,
    wdDialogMailMergeInsertAddressBlock = 1305,
    wdDialogMailMergeInsertGreetingLine = 1306,
    wdDialogMailMergeInsertFields = 1307,
    wdDialogMailMergeRecipients = 1308,
    wdDialogMailMergeFindRecipient = 1326,
    wdDialogMailMergeSetDocumentType = 1339,
    wdDialogXMLElementAttributes = 1460,
    wdDialogSchemaLibrary = 1417,
    wdDialogPermission = 1469,
    wdDialogMyPermission = 1437,
    wdDialogXMLOptions = 1425,
    wdDialogFormattingRestrictions = 1427
};

enum WdWordDialogHID
{
//  emptyenum = 0
};

enum WdFieldKind
{
    wdFieldKindNone = 0,
    wdFieldKindHot = 1,
    wdFieldKindWarm = 2,
    wdFieldKindCold = 3
};

enum WdTextFormFieldType
{
    wdRegularText = 0,
    wdNumberText = 1,
    wdDateText = 2,
    wdCurrentDateText = 3,
    wdCurrentTimeText = 4,
    wdCalculationText = 5
};

enum WdChevronConvertRule
{
    wdNeverConvert = 0,
    wdAlwaysConvert = 1,
    wdAskToNotConvert = 2,
    wdAskToConvert = 3
};

enum WdMailMergeMainDocType
{
    wdNotAMergeDocument = -1,
    wdFormLetters = 0,
    wdMailingLabels = 1,
    wdEnvelopes = 2,
    wdCatalog = 3,
    wdEMail = 4,
    wdFax = 5,
    wdDirectory = 3
};

enum WdMailMergeState
{
    wdNormalDocument = 0,
    wdMainDocumentOnly = 1,
    wdMainAndDataSource = 2,
    wdMainAndHeader = 3,
    wdMainAndSourceAndHeader = 4,
    wdDataSource = 5
};

enum WdMailMergeDestination
{
    wdSendToNewDocument = 0,
    wdSendToPrinter = 1,
    wdSendToEmail = 2,
    wdSendToFax = 3
};

enum WdMailMergeActiveRecord
{
    wdNoActiveRecord = -1,
    wdNextRecord = -2,
    wdPreviousRecord = -3,
    wdFirstRecord = -4,
    wdLastRecord = -5,
    wdFirstDataSourceRecord = -6,
    wdLastDataSourceRecord = -7,
    wdNextDataSourceRecord = -8,
    wdPreviousDataSourceRecord = -9
};

enum WdMailMergeDefaultRecord
{
    wdDefaultFirstRecord = 1,
    wdDefaultLastRecord = -16
};

enum WdMailMergeDataSource
{
    wdNoMergeInfo = -1,
    wdMergeInfoFromWord = 0,
    wdMergeInfoFromAccessDDE = 1,
    wdMergeInfoFromExcelDDE = 2,
    wdMergeInfoFromMSQueryDDE = 3,
    wdMergeInfoFromODBC = 4,
    wdMergeInfoFromODSO = 5
};

enum WdMailMergeComparison
{
    wdMergeIfEqual = 0,
    wdMergeIfNotEqual = 1,
    wdMergeIfLessThan = 2,
    wdMergeIfGreaterThan = 3,
    wdMergeIfLessThanOrEqual = 4,
    wdMergeIfGreaterThanOrEqual = 5,
    wdMergeIfIsBlank = 6,
    wdMergeIfIsNotBlank = 7
};

enum WdBookmarkSortBy
{
    wdSortByName = 0,
    wdSortByLocation = 1
};

enum WdWindowState
{
    wdWindowStateNormal = 0,
    wdWindowStateMaximize = 1,
    wdWindowStateMinimize = 2
};

enum WdPictureLinkType
{
    wdLinkNone = 0,
    wdLinkDataInDoc = 1,
    wdLinkDataOnDisk = 2
};

enum WdLinkType
{
    wdLinkTypeOLE = 0,
    wdLinkTypePicture = 1,
    wdLinkTypeText = 2,
    wdLinkTypeReference = 3,
    wdLinkTypeInclude = 4,
    wdLinkTypeImport = 5,
    wdLinkTypeDDE = 6,
    wdLinkTypeDDEAuto = 7
};

enum WdWindowType
{
    wdWindowDocument = 0,
    wdWindowTemplate = 1
};

enum WdViewType
{
    wdNormalView = 1,
    wdOutlineView = 2,
    wdPrintView = 3,
    wdPrintPreview = 4,
    wdMasterView = 5,
    wdWebView = 6,
    wdReadingView = 7
};

enum WdSeekView
{
    wdSeekMainDocument = 0,
    wdSeekPrimaryHeader = 1,
    wdSeekFirstPageHeader = 2,
    wdSeekEvenPagesHeader = 3,
    wdSeekPrimaryFooter = 4,
    wdSeekFirstPageFooter = 5,
    wdSeekEvenPagesFooter = 6,
    wdSeekFootnotes = 7,
    wdSeekEndnotes = 8,
    wdSeekCurrentPageHeader = 9,
    wdSeekCurrentPageFooter = 10
};

enum WdSpecialPane
{
    wdPaneNone = 0,
    wdPanePrimaryHeader = 1,
    wdPaneFirstPageHeader = 2,
    wdPaneEvenPagesHeader = 3,
    wdPanePrimaryFooter = 4,
    wdPaneFirstPageFooter = 5,
    wdPaneEvenPagesFooter = 6,
    wdPaneFootnotes = 7,
    wdPaneEndnotes = 8,
    wdPaneFootnoteContinuationNotice = 9,
    wdPaneFootnoteContinuationSeparator = 10,
    wdPaneFootnoteSeparator = 11,
    wdPaneEndnoteContinuationNotice = 12,
    wdPaneEndnoteContinuationSeparator = 13,
    wdPaneEndnoteSeparator = 14,
    wdPaneComments = 15,
    wdPaneCurrentPageHeader = 16,
    wdPaneCurrentPageFooter = 17,
    wdPaneRevisions = 18
};

enum WdPageFit
{
    wdPageFitNone = 0,
    wdPageFitFullPage = 1,
    wdPageFitBestFit = 2,
    wdPageFitTextFit = 3
};

enum WdBrowseTarget
{
    wdBrowsePage = 1,
    wdBrowseSection = 2,
    wdBrowseComment = 3,
    wdBrowseFootnote = 4,
    wdBrowseEndnote = 5,
    wdBrowseField = 6,
    wdBrowseTable = 7,
    wdBrowseGraphic = 8,
    wdBrowseHeading = 9,
    wdBrowseEdit = 10,
    wdBrowseFind = 11,
    wdBrowseGoTo = 12
};

enum WdPaperTray
{
    wdPrinterDefaultBin = 0,
    wdPrinterUpperBin = 1,
    wdPrinterOnlyBin = 1,
    wdPrinterLowerBin = 2,
    wdPrinterMiddleBin = 3,
    wdPrinterManualFeed = 4,
    wdPrinterEnvelopeFeed = 5,
    wdPrinterManualEnvelopeFeed = 6,
    wdPrinterAutomaticSheetFeed = 7,
    wdPrinterTractorFeed = 8,
    wdPrinterSmallFormatBin = 9,
    wdPrinterLargeFormatBin = 10,
    wdPrinterLargeCapacityBin = 11,
    wdPrinterPaperCassette = 14,
    wdPrinterFormSource = 15
};

enum WdOrientation
{
    wdOrientPortrait = 0,
    wdOrientLandscape = 1
};

enum WdSelectionType
{
    wdNoSelection = 0,
    wdSelectionIP = 1,
    wdSelectionNormal = 2,
    wdSelectionFrame = 3,
    wdSelectionColumn = 4,
    wdSelectionRow = 5,
    wdSelectionBlock = 6,
    wdSelectionInlineShape = 7,
    wdSelectionShape = 8
};

enum WdCaptionLabelID
{
    wdCaptionFigure = -1,
    wdCaptionTable = -2,
    wdCaptionEquation = -3
};

enum WdReferenceType
{
    wdRefTypeNumberedItem = 0,
    wdRefTypeHeading = 1,
    wdRefTypeBookmark = 2,
    wdRefTypeFootnote = 3,
    wdRefTypeEndnote = 4
};

enum WdReferenceKind
{
    wdContentText = -1,
    wdNumberRelativeContext = -2,
    wdNumberNoContext = -3,
    wdNumberFullContext = -4,
    wdEntireCaption = 2,
    wdOnlyLabelAndNumber = 3,
    wdOnlyCaptionText = 4,
    wdFootnoteNumber = 5,
    wdEndnoteNumber = 6,
    wdPageNumber = 7,
    wdPosition = 15,
    wdFootnoteNumberFormatted = 16,
    wdEndnoteNumberFormatted = 17
};

enum WdIndexFormat
{
    wdIndexTemplate = 0,
    wdIndexClassic = 1,
    wdIndexFancy = 2,
    wdIndexModern = 3,
    wdIndexBulleted = 4,
    wdIndexFormal = 5,
    wdIndexSimple = 6
};

enum WdIndexType
{
    wdIndexIndent = 0,
    wdIndexRunin = 1
};

enum WdRevisionsWrap
{
    wdWrapNever = 0,
    wdWrapAlways = 1,
    wdWrapAsk = 2
};

enum WdRevisionType
{
    wdNoRevision = 0,
    wdRevisionInsert = 1,
    wdRevisionDelete = 2,
    wdRevisionProperty = 3,
    wdRevisionParagraphNumber = 4,
    wdRevisionDisplayField = 5,
    wdRevisionReconcile = 6,
    wdRevisionConflict = 7,
    wdRevisionStyle = 8,
    wdRevisionReplace = 9,
    wdRevisionParagraphProperty = 10,
    wdRevisionTableProperty = 11,
    wdRevisionSectionProperty = 12,
    wdRevisionStyleDefinition = 13
};

enum WdRoutingSlipDelivery
{
    wdOneAfterAnother = 0,
    wdAllAtOnce = 1
};

enum WdRoutingSlipStatus
{
    wdNotYetRouted = 0,
    wdRouteInProgress = 1,
    wdRouteComplete = 2
};

enum WdSectionStart
{
    wdSectionContinuous = 0,
    wdSectionNewColumn = 1,
    wdSectionNewPage = 2,
    wdSectionEvenPage = 3,
    wdSectionOddPage = 4
};

enum WdSaveOptions
{
    wdDoNotSaveChanges = 0,
    wdSaveChanges = -1,
    wdPromptToSaveChanges = -2
};

enum WdDocumentKind
{
    wdDocumentNotSpecified = 0,
    wdDocumentLetter = 1,
    wdDocumentEmail = 2
};

enum WdDocumentType
{
    wdTypeDocument = 0,
    wdTypeTemplate = 1,
    wdTypeFrameset = 2
};

enum WdOriginalFormat
{
    wdWordDocument = 0,
    wdOriginalDocumentFormat = 1,
    wdPromptUser = 2
};

enum WdRelocate
{
    wdRelocateUp = 0,
    wdRelocateDown = 1
};

enum WdInsertedTextMark
{
    wdInsertedTextMarkNone = 0,
    wdInsertedTextMarkBold = 1,
    wdInsertedTextMarkItalic = 2,
    wdInsertedTextMarkUnderline = 3,
    wdInsertedTextMarkDoubleUnderline = 4,
    wdInsertedTextMarkColorOnly = 5,
    wdInsertedTextMarkStrikeThrough = 6
};

enum WdRevisedLinesMark
{
    wdRevisedLinesMarkNone = 0,
    wdRevisedLinesMarkLeftBorder = 1,
    wdRevisedLinesMarkRightBorder = 2,
    wdRevisedLinesMarkOutsideBorder = 3
};

enum WdDeletedTextMark
{
    wdDeletedTextMarkHidden = 0,
    wdDeletedTextMarkStrikeThrough = 1,
    wdDeletedTextMarkCaret = 2,
    wdDeletedTextMarkPound = 3,
    wdDeletedTextMarkNone = 4,
    wdDeletedTextMarkBold = 5,
    wdDeletedTextMarkItalic = 6,
    wdDeletedTextMarkUnderline = 7,
    wdDeletedTextMarkDoubleUnderline = 8,
    wdDeletedTextMarkColorOnly = 9
};

enum WdRevisedPropertiesMark
{
    wdRevisedPropertiesMarkNone = 0,
    wdRevisedPropertiesMarkBold = 1,
    wdRevisedPropertiesMarkItalic = 2,
    wdRevisedPropertiesMarkUnderline = 3,
    wdRevisedPropertiesMarkDoubleUnderline = 4,
    wdRevisedPropertiesMarkColorOnly = 5,
    wdRevisedPropertiesMarkStrikeThrough = 6
};

enum WdFieldShading
{
    wdFieldShadingNever = 0,
    wdFieldShadingAlways = 1,
    wdFieldShadingWhenSelected = 2
};

enum WdDefaultFilePath
{
    wdDocumentsPath = 0,
    wdPicturesPath = 1,
    wdUserTemplatesPath = 2,
    wdWorkgroupTemplatesPath = 3,
    wdUserOptionsPath = 4,
    wdAutoRecoverPath = 5,
    wdToolsPath = 6,
    wdTutorialPath = 7,
    wdStartupPath = 8,
    wdProgramPath = 9,
    wdGraphicsFiltersPath = 10,
    wdTextConvertersPath = 11,
    wdProofingToolsPath = 12,
    wdTempFilePath = 13,
    wdCurrentFolderPath = 14,
    wdStyleGalleryPath = 15,
    wdBorderArtPath = 19
};

enum WdCompatibility
{
    wdNoTabHangIndent = 1,
    wdNoSpaceRaiseLower = 2,
    wdPrintColBlack = 3,
    wdWrapTrailSpaces = 4,
    wdNoColumnBalance = 5,
    wdConvMailMergeEsc = 6,
    wdSuppressSpBfAfterPgBrk = 7,
    wdSuppressTopSpacing = 8,
    wdOrigWordTableRules = 9,
    wdTransparentMetafiles = 10,
    wdShowBreaksInFrames = 11,
    wdSwapBordersFacingPages = 12,
    wdLeaveBackslashAlone = 13,
    wdExpandShiftReturn = 14,
    wdDontULTrailSpace = 15,
    wdDontBalanceSingleByteDoubleByteWidth = 16,
    wdSuppressTopSpacingMac5 = 17,
    wdSpacingInWholePoints = 18,
    wdPrintBodyTextBeforeHeader = 19,
    wdNoLeading = 20,
    wdNoSpaceForUL = 21,
    wdMWSmallCaps = 22,
    wdNoExtraLineSpacing = 23,
    wdTruncateFontHeight = 24,
    wdSubFontBySize = 25,
    wdUsePrinterMetrics = 26,
    wdWW6BorderRules = 27,
    wdExactOnTop = 28,
    wdSuppressBottomSpacing = 29,
    wdWPSpaceWidth = 30,
    wdWPJustification = 31,
    wdLineWrapLikeWord6 = 32,
    wdShapeLayoutLikeWW8 = 33,
    wdFootnoteLayoutLikeWW8 = 34,
    wdDontUseHTMLParagraphAutoSpacing = 35,
    wdDontAdjustLineHeightInTable = 36,
    wdForgetLastTabAlignment = 37,
    wdAutospaceLikeWW7 = 38,
    wdAlignTablesRowByRow = 39,
    wdLayoutRawTableWidth = 40,
    wdLayoutTableRowsApart = 41,
    wdUseWord97LineBreakingRules = 42,
    wdDontBreakWrappedTables = 43,
    wdDontSnapTextToGridInTableWithObjects = 44,
    wdSelectFieldWithFirstOrLastCharacter = 45,
    wdApplyBreakingRules = 46,
    wdDontWrapTextWithPunctuation = 47,
    wdDontUseAsianBreakRulesInGrid = 48,
    wdUseWord2002TableStyleRules = 49,
    wdGrowAutofit = 50
};

enum WdPaperSize
{
    wdPaper10x14 = 0,
    wdPaper11x17 = 1,
    wdPaperLetter = 2,
    wdPaperLetterSmall = 3,
    wdPaperLegal = 4,
    wdPaperExecutive = 5,
    wdPaperA3 = 6,
    wdPaperA4 = 7,
    wdPaperA4Small = 8,
    wdPaperA5 = 9,
    wdPaperB4 = 10,
    wdPaperB5 = 11,
    wdPaperCSheet = 12,
    wdPaperDSheet = 13,
    wdPaperESheet = 14,
    wdPaperFanfoldLegalGerman = 15,
    wdPaperFanfoldStdGerman = 16,
    wdPaperFanfoldUS = 17,
    wdPaperFolio = 18,
    wdPaperLedger = 19,
    wdPaperNote = 20,
    wdPaperQuarto = 21,
    wdPaperStatement = 22,
    wdPaperTabloid = 23,
    wdPaperEnvelope9 = 24,
    wdPaperEnvelope10 = 25,
    wdPaperEnvelope11 = 26,
    wdPaperEnvelope12 = 27,
    wdPaperEnvelope14 = 28,
    wdPaperEnvelopeB4 = 29,
    wdPaperEnvelopeB5 = 30,
    wdPaperEnvelopeB6 = 31,
    wdPaperEnvelopeC3 = 32,
    wdPaperEnvelopeC4 = 33,
    wdPaperEnvelopeC5 = 34,
    wdPaperEnvelopeC6 = 35,
    wdPaperEnvelopeC65 = 36,
    wdPaperEnvelopeDL = 37,
    wdPaperEnvelopeItaly = 38,
    wdPaperEnvelopeMonarch = 39,
    wdPaperEnvelopePersonal = 40,
    wdPaperCustom = 41
};

enum WdCustomLabelPageSize
{
    wdCustomLabelLetter = 0,
    wdCustomLabelLetterLS = 1,
    wdCustomLabelA4 = 2,
    wdCustomLabelA4LS = 3,
    wdCustomLabelA5 = 4,
    wdCustomLabelA5LS = 5,
    wdCustomLabelB5 = 6,
    wdCustomLabelMini = 7,
    wdCustomLabelFanfold = 8,
    wdCustomLabelVertHalfSheet = 9,
    wdCustomLabelVertHalfSheetLS = 10,
    wdCustomLabelHigaki = 11,
    wdCustomLabelHigakiLS = 12,
    wdCustomLabelB4JIS = 13
};

enum WdProtectionType
{
    wdNoProtection = -1,
    wdAllowOnlyRevisions = 0,
    wdAllowOnlyComments = 1,
    wdAllowOnlyFormFields = 2,
    wdAllowOnlyReading = 3
};

enum WdPartOfSpeech
{
    wdAdjective = 0,
    wdNoun = 1,
    wdAdverb = 2,
    wdVerb = 3,
    wdPronoun = 4,
    wdConjunction = 5,
    wdPreposition = 6,
    wdInterjection = 7,
    wdIdiom = 8,
    wdOther = 9
};

enum WdSubscriberFormats
{
    wdSubscriberBestFormat = 0,
    wdSubscriberRTF = 1,
    wdSubscriberText = 2,
    wdSubscriberPict = 4
};

enum WdEditionType
{
    wdPublisher = 0,
    wdSubscriber = 1
};

enum WdEditionOption
{
    wdCancelPublisher = 0,
    wdSendPublisher = 1,
    wdSelectPublisher = 2,
    wdAutomaticUpdate = 3,
    wdManualUpdate = 4,
    wdChangeAttributes = 5,
    wdUpdateSubscriber = 6,
    wdOpenSource = 7
};

enum WdRelativeHorizontalPosition
{
    wdRelativeHorizontalPositionMargin = 0,
    wdRelativeHorizontalPositionPage = 1,
    wdRelativeHorizontalPositionColumn = 2,
    wdRelativeHorizontalPositionCharacter = 3
};

enum WdRelativeVerticalPosition
{
    wdRelativeVerticalPositionMargin = 0,
    wdRelativeVerticalPositionPage = 1,
    wdRelativeVerticalPositionParagraph = 2,
    wdRelativeVerticalPositionLine = 3
};

enum WdHelpType
{
    wdHelp = 0,
    wdHelpAbout = 1,
    wdHelpActiveWindow = 2,
    wdHelpContents = 3,
    wdHelpExamplesAndDemos = 4,
    wdHelpIndex = 5,
    wdHelpKeyboard = 6,
    wdHelpPSSHelp = 7,
    wdHelpQuickPreview = 8,
    wdHelpSearch = 9,
    wdHelpUsingHelp = 10,
    wdHelpIchitaro = 11,
    wdHelpPE2 = 12,
    wdHelpHWP = 13
};

enum WdHelpTypeHID
{
//  emptyenum = 0
};

enum WdKeyCategory
{
    wdKeyCategoryNil = -1,
    wdKeyCategoryDisable = 0,
    wdKeyCategoryCommand = 1,
    wdKeyCategoryMacro = 2,
    wdKeyCategoryFont = 3,
    wdKeyCategoryAutoText = 4,
    wdKeyCategoryStyle = 5,
    wdKeyCategorySymbol = 6,
    wdKeyCategoryPrefix = 7
};

enum WdKey
{
    wdNoKey = 255,
    wdKeyShift = 256,
    wdKeyControl = 512,
    wdKeyCommand = 512,
    wdKeyAlt = 1024,
    wdKeyOption = 1024,
    wdKeyA = 65,
    wdKeyB = 66,
    wdKeyC = 67,
    wdKeyD = 68,
    wdKeyE = 69,
    wdKeyF = 70,
    wdKeyG = 71,
    wdKeyH = 72,
    wdKeyI = 73,
    wdKeyJ = 74,
    wdKeyK = 75,
    wdKeyL = 76,
    wdKeyM = 77,
    wdKeyN = 78,
    wdKeyO = 79,
    wdKeyP = 80,
    wdKeyQ = 81,
    wdKeyR = 82,
    wdKeyS = 83,
    wdKeyT = 84,
    wdKeyU = 85,
    wdKeyV = 86,
    wdKeyW = 87,
    wdKeyX = 88,
    wdKeyY = 89,
    wdKeyZ = 90,
    wdKey0 = 48,
    wdKey1 = 49,
    wdKey2 = 50,
    wdKey3 = 51,
    wdKey4 = 52,
    wdKey5 = 53,
    wdKey6 = 54,
    wdKey7 = 55,
    wdKey8 = 56,
    wdKey9 = 57,
    wdKeyBackspace = 8,
    wdKeyTab = 9,
    wdKeyNumeric5Special = 12,
    wdKeyReturn = 13,
    wdKeyPause = 19,
    wdKeyEsc = 27,
    wdKeySpacebar = 32,
    wdKeyPageUp = 33,
    wdKeyPageDown = 34,
    wdKeyEnd = 35,
    wdKeyHome = 36,
    wdKeyInsert = 45,
    wdKeyDelete = 46,
    wdKeyNumeric0 = 96,
    wdKeyNumeric1 = 97,
    wdKeyNumeric2 = 98,
    wdKeyNumeric3 = 99,
    wdKeyNumeric4 = 100,
    wdKeyNumeric5 = 101,
    wdKeyNumeric6 = 102,
    wdKeyNumeric7 = 103,
    wdKeyNumeric8 = 104,
    wdKeyNumeric9 = 105,
    wdKeyNumericMultiply = 106,
    wdKeyNumericAdd = 107,
    wdKeyNumericSubtract = 109,
    wdKeyNumericDecimal = 110,
    wdKeyNumericDivide = 111,
    wdKeyF1 = 112,
    wdKeyF2 = 113,
    wdKeyF3 = 114,
    wdKeyF4 = 115,
    wdKeyF5 = 116,
    wdKeyF6 = 117,
    wdKeyF7 = 118,
    wdKeyF8 = 119,
    wdKeyF9 = 120,
    wdKeyF10 = 121,
    wdKeyF11 = 122,
    wdKeyF12 = 123,
    wdKeyF13 = 124,
    wdKeyF14 = 125,
    wdKeyF15 = 126,
    wdKeyF16 = 127,
    wdKeyScrollLock = 145,
    wdKeySemiColon = 186,
    wdKeyEquals = 187,
    wdKeyComma = 188,
    wdKeyHyphen = 189,
    wdKeyPeriod = 190,
    wdKeySlash = 191,
    wdKeyBackSingleQuote = 192,
    wdKeyOpenSquareBrace = 219,
    wdKeyBackSlash = 220,
    wdKeyCloseSquareBrace = 221,
    wdKeySingleQuote = 222
};

enum WdOLEType
{
    wdOLELink = 0,
    wdOLEEmbed = 1,
    wdOLEControl = 2
};

enum WdOLEVerb
{
    wdOLEVerbPrimary = 0,
    wdOLEVerbShow = -1,
    wdOLEVerbOpen = -2,
    wdOLEVerbHide = -3,
    wdOLEVerbUIActivate = -4,
    wdOLEVerbInPlaceActivate = -5,
    wdOLEVerbDiscardUndoState = -6
};

enum WdOLEPlacement
{
    wdInLine = 0,
    wdFloatOverText = 1
};

enum WdEnvelopeOrientation
{
    wdLeftPortrait = 0,
    wdCenterPortrait = 1,
    wdRightPortrait = 2,
    wdLeftLandscape = 3,
    wdCenterLandscape = 4,
    wdRightLandscape = 5,
    wdLeftClockwise = 6,
    wdCenterClockwise = 7,
    wdRightClockwise = 8
};

enum WdLetterStyle
{
    wdFullBlock = 0,
    wdModifiedBlock = 1,
    wdSemiBlock = 2
};

enum WdLetterheadLocation
{
    wdLetterTop = 0,
    wdLetterBottom = 1,
    wdLetterLeft = 2,
    wdLetterRight = 3
};

enum WdSalutationType
{
    wdSalutationInformal = 0,
    wdSalutationFormal = 1,
    wdSalutationBusiness = 2,
    wdSalutationOther = 3
};

enum WdSalutationGender
{
    wdGenderFemale = 0,
    wdGenderMale = 1,
    wdGenderNeutral = 2,
    wdGenderUnknown = 3
};

enum WdMovementType
{
    wdMove = 0,
    wdExtend = 1
};

enum WdConstants
{
    wdUndefined = 9999999,
    wdToggle = 9999998,
    wdForward = 1073741823,
    wdBackward = -1073741823,
    wdAutoPosition = 0,
    wdFirst = 1,
    wdCreatorCode = 1297307460
};

enum WdPasteDataType
{
    wdPasteOLEObject = 0,
    wdPasteRTF = 1,
    wdPasteText = 2,
    wdPasteMetafilePicture = 3,
    wdPasteBitmap = 4,
    wdPasteDeviceIndependentBitmap = 5,
    wdPasteHyperlink = 7,
    wdPasteShape = 8,
    wdPasteEnhancedMetafile = 9,
    wdPasteHTML = 10
};

enum WdPrintOutItem
{
    wdPrintDocumentContent = 0,
    wdPrintProperties = 1,
    wdPrintComments = 2,
    wdPrintMarkup = 2,
    wdPrintStyles = 3,
    wdPrintAutoTextEntries = 4,
    wdPrintKeyAssignments = 5,
    wdPrintEnvelope = 6,
    wdPrintDocumentWithMarkup = 7
};

enum WdPrintOutPages
{
    wdPrintAllPages = 0,
    wdPrintOddPagesOnly = 1,
    wdPrintEvenPagesOnly = 2
};

enum WdPrintOutRange
{
    wdPrintAllDocument = 0,
    wdPrintSelection = 1,
    wdPrintCurrentPage = 2,
    wdPrintFromTo = 3,
    wdPrintRangeOfPages = 4
};

enum WdDictionaryType
{
    wdSpelling = 0,
    wdGrammar = 1,
    wdThesaurus = 2,
    wdHyphenation = 3,
    wdSpellingComplete = 4,
    wdSpellingCustom = 5,
    wdSpellingLegal = 6,
    wdSpellingMedical = 7,
    wdHangulHanjaConversion = 8,
    wdHangulHanjaConversionCustom = 9
};

enum WdDictionaryTypeHID
{
//  emptyenum = 0
};

enum WdSpellingWordType
{
    wdSpellword = 0,
    wdWildcard = 1,
    wdAnagram = 2
};

enum WdSpellingErrorType
{
    wdSpellingCorrect = 0,
    wdSpellingNotInDictionary = 1,
    wdSpellingCapitalization = 2
};

enum WdProofreadingErrorType
{
    wdSpellingError = 0,
    wdGrammaticalError = 1
};

enum WdInlineShapeType
{
    wdInlineShapeEmbeddedOLEObject = 1,
    wdInlineShapeLinkedOLEObject = 2,
    wdInlineShapePicture = 3,
    wdInlineShapeLinkedPicture = 4,
    wdInlineShapeOLEControlObject = 5,
    wdInlineShapeHorizontalLine = 6,
    wdInlineShapePictureHorizontalLine = 7,
    wdInlineShapeLinkedPictureHorizontalLine = 8,
    wdInlineShapePictureBullet = 9,
    wdInlineShapeScriptAnchor = 10,
    wdInlineShapeOWSAnchor = 11
};

enum WdArrangeStyle
{
    wdTiled = 0,
    wdIcons = 1
};

enum WdSelectionFlags
{
    wdSelStartActive = 1,
    wdSelAtEOL = 2,
    wdSelOvertype = 4,
    wdSelActive = 8,
    wdSelReplace = 16
};

enum WdAutoVersions
{
    wdAutoVersionOff = 0,
    wdAutoVersionOnClose = 1
};

enum WdOrganizerObject
{
    wdOrganizerObjectStyles = 0,
    wdOrganizerObjectAutoText = 1,
    wdOrganizerObjectCommandBars = 2,
    wdOrganizerObjectProjectItems = 3
};

enum WdFindMatch
{
    wdMatchParagraphMark = 65551,
    wdMatchTabCharacter = 9,
    wdMatchCommentMark = 5,
    wdMatchAnyCharacter = 65599,
    wdMatchAnyDigit = 65567,
    wdMatchAnyLetter = 65583,
    wdMatchCaretCharacter = 11,
    wdMatchColumnBreak = 14,
    wdMatchEmDash = 8212,
    wdMatchEnDash = 8211,
    wdMatchEndnoteMark = 65555,
    wdMatchField = 19,
    wdMatchFootnoteMark = 65554,
    wdMatchGraphic = 1,
    wdMatchManualLineBreak = 65551,
    wdMatchManualPageBreak = 65564,
    wdMatchNonbreakingHyphen = 30,
    wdMatchNonbreakingSpace = 160,
    wdMatchOptionalHyphen = 31,
    wdMatchSectionBreak = 65580,
    wdMatchWhiteSpace = 65655
};

enum WdFindWrap
{
    wdFindStop = 0,
    wdFindContinue = 1,
    wdFindAsk = 2
};

enum WdInformation
{
    wdActiveEndAdjustedPageNumber = 1,
    wdActiveEndSectionNumber = 2,
    wdActiveEndPageNumber = 3,
    wdNumberOfPagesInDocument = 4,
    wdHorizontalPositionRelativeToPage = 5,
    wdVerticalPositionRelativeToPage = 6,
    wdHorizontalPositionRelativeToTextBoundary = 7,
    wdVerticalPositionRelativeToTextBoundary = 8,
    wdFirstCharacterColumnNumber = 9,
    wdFirstCharacterLineNumber = 10,
    wdFrameIsSelected = 11,
    wdWithInTable = 12,
    wdStartOfRangeRowNumber = 13,
    wdEndOfRangeRowNumber = 14,
    wdMaximumNumberOfRows = 15,
    wdStartOfRangeColumnNumber = 16,
    wdEndOfRangeColumnNumber = 17,
    wdMaximumNumberOfColumns = 18,
    wdZoomPercentage = 19,
    wdSelectionMode = 20,
    wdCapsLock = 21,
    wdNumLock = 22,
    wdOverType = 23,
    wdRevisionMarking = 24,
    wdInFootnoteEndnotePane = 25,
    wdInCommentPane = 26,
    wdInHeaderFooter = 28,
    wdAtEndOfRowMarker = 31,
    wdReferenceOfType = 32,
    wdHeaderFooterType = 33,
    wdInMasterDocument = 34,
    wdInFootnote = 35,
    wdInEndnote = 36,
    wdInWordMail = 37,
    wdInClipboard = 38
};

enum WdWrapType
{
    wdWrapSquare = 0,
    wdWrapTight = 1,
    wdWrapThrough = 2,
    wdWrapNone = 3,
    wdWrapTopBottom = 4,
    wdWrapInline = 7
};

enum WdWrapSideType
{
    wdWrapBoth = 0,
    wdWrapLeft = 1,
    wdWrapRight = 2,
    wdWrapLargest = 3
};

enum WdOutlineLevel
{
    wdOutlineLevel1 = 1,
    wdOutlineLevel2 = 2,
    wdOutlineLevel3 = 3,
    wdOutlineLevel4 = 4,
    wdOutlineLevel5 = 5,
    wdOutlineLevel6 = 6,
    wdOutlineLevel7 = 7,
    wdOutlineLevel8 = 8,
    wdOutlineLevel9 = 9,
    wdOutlineLevelBodyText = 10
};

enum WdTextOrientation
{
    wdTextOrientationHorizontal = 0,
    wdTextOrientationUpward = 2,
    wdTextOrientationDownward = 3,
    wdTextOrientationVerticalFarEast = 1,
    wdTextOrientationHorizontalRotatedFarEast = 4
};

enum WdTextOrientationHID
{
//  emptyenum = 0
};

enum WdPageBorderArt
{
    wdArtApples = 1,
    wdArtMapleMuffins = 2,
    wdArtCakeSlice = 3,
    wdArtCandyCorn = 4,
    wdArtIceCreamCones = 5,
    wdArtChampagneBottle = 6,
    wdArtPartyGlass = 7,
    wdArtChristmasTree = 8,
    wdArtTrees = 9,
    wdArtPalmsColor = 10,
    wdArtBalloons3Colors = 11,
    wdArtBalloonsHotAir = 12,
    wdArtPartyFavor = 13,
    wdArtConfettiStreamers = 14,
    wdArtHearts = 15,
    wdArtHeartBalloon = 16,
    wdArtStars3D = 17,
    wdArtStarsShadowed = 18,
    wdArtStars = 19,
    wdArtSun = 20,
    wdArtEarth2 = 21,
    wdArtEarth1 = 22,
    wdArtPeopleHats = 23,
    wdArtSombrero = 24,
    wdArtPencils = 25,
    wdArtPackages = 26,
    wdArtClocks = 27,
    wdArtFirecrackers = 28,
    wdArtRings = 29,
    wdArtMapPins = 30,
    wdArtConfetti = 31,
    wdArtCreaturesButterfly = 32,
    wdArtCreaturesLadyBug = 33,
    wdArtCreaturesFish = 34,
    wdArtBirdsFlight = 35,
    wdArtScaredCat = 36,
    wdArtBats = 37,
    wdArtFlowersRoses = 38,
    wdArtFlowersRedRose = 39,
    wdArtPoinsettias = 40,
    wdArtHolly = 41,
    wdArtFlowersTiny = 42,
    wdArtFlowersPansy = 43,
    wdArtFlowersModern2 = 44,
    wdArtFlowersModern1 = 45,
    wdArtWhiteFlowers = 46,
    wdArtVine = 47,
    wdArtFlowersDaisies = 48,
    wdArtFlowersBlockPrint = 49,
    wdArtDecoArchColor = 50,
    wdArtFans = 51,
    wdArtFilm = 52,
    wdArtLightning1 = 53,
    wdArtCompass = 54,
    wdArtDoubleD = 55,
    wdArtClassicalWave = 56,
    wdArtShadowedSquares = 57,
    wdArtTwistedLines1 = 58,
    wdArtWaveline = 59,
    wdArtQuadrants = 60,
    wdArtCheckedBarColor = 61,
    wdArtSwirligig = 62,
    wdArtPushPinNote1 = 63,
    wdArtPushPinNote2 = 64,
    wdArtPumpkin1 = 65,
    wdArtEggsBlack = 66,
    wdArtCup = 67,
    wdArtHeartGray = 68,
    wdArtGingerbreadMan = 69,
    wdArtBabyPacifier = 70,
    wdArtBabyRattle = 71,
    wdArtCabins = 72,
    wdArtHouseFunky = 73,
    wdArtStarsBlack = 74,
    wdArtSnowflakes = 75,
    wdArtSnowflakeFancy = 76,
    wdArtSkyrocket = 77,
    wdArtSeattle = 78,
    wdArtMusicNotes = 79,
    wdArtPalmsBlack = 80,
    wdArtMapleLeaf = 81,
    wdArtPaperClips = 82,
    wdArtShorebirdTracks = 83,
    wdArtPeople = 84,
    wdArtPeopleWaving = 85,
    wdArtEclipsingSquares2 = 86,
    wdArtHypnotic = 87,
    wdArtDiamondsGray = 88,
    wdArtDecoArch = 89,
    wdArtDecoBlocks = 90,
    wdArtCirclesLines = 91,
    wdArtPapyrus = 92,
    wdArtWoodwork = 93,
    wdArtWeavingBraid = 94,
    wdArtWeavingRibbon = 95,
    wdArtWeavingAngles = 96,
    wdArtArchedScallops = 97,
    wdArtSafari = 98,
    wdArtCelticKnotwork = 99,
    wdArtCrazyMaze = 100,
    wdArtEclipsingSquares1 = 101,
    wdArtBirds = 102,
    wdArtFlowersTeacup = 103,
    wdArtNorthwest = 104,
    wdArtSouthwest = 105,
    wdArtTribal6 = 106,
    wdArtTribal4 = 107,
    wdArtTribal3 = 108,
    wdArtTribal2 = 109,
    wdArtTribal5 = 110,
    wdArtXIllusions = 111,
    wdArtZanyTriangles = 112,
    wdArtPyramids = 113,
    wdArtPyramidsAbove = 114,
    wdArtConfettiGrays = 115,
    wdArtConfettiOutline = 116,
    wdArtConfettiWhite = 117,
    wdArtMosaic = 118,
    wdArtLightning2 = 119,
    wdArtHeebieJeebies = 120,
    wdArtLightBulb = 121,
    wdArtGradient = 122,
    wdArtTriangleParty = 123,
    wdArtTwistedLines2 = 124,
    wdArtMoons = 125,
    wdArtOvals = 126,
    wdArtDoubleDiamonds = 127,
    wdArtChainLink = 128,
    wdArtTriangles = 129,
    wdArtTribal1 = 130,
    wdArtMarqueeToothed = 131,
    wdArtSharksTeeth = 132,
    wdArtSawtooth = 133,
    wdArtSawtoothGray = 134,
    wdArtPostageStamp = 135,
    wdArtWeavingStrips = 136,
    wdArtZigZag = 137,
    wdArtCrossStitch = 138,
    wdArtGems = 139,
    wdArtCirclesRectangles = 140,
    wdArtCornerTriangles = 141,
    wdArtCreaturesInsects = 142,
    wdArtZigZagStitch = 143,
    wdArtCheckered = 144,
    wdArtCheckedBarBlack = 145,
    wdArtMarquee = 146,
    wdArtBasicWhiteDots = 147,
    wdArtBasicWideMidline = 148,
    wdArtBasicWideOutline = 149,
    wdArtBasicWideInline = 150,
    wdArtBasicThinLines = 151,
    wdArtBasicWhiteDashes = 152,
    wdArtBasicWhiteSquares = 153,
    wdArtBasicBlackSquares = 154,
    wdArtBasicBlackDashes = 155,
    wdArtBasicBlackDots = 156,
    wdArtStarsTop = 157,
    wdArtCertificateBanner = 158,
    wdArtHandmade1 = 159,
    wdArtHandmade2 = 160,
    wdArtTornPaper = 161,
    wdArtTornPaperBlack = 162,
    wdArtCouponCutoutDashes = 163,
    wdArtCouponCutoutDots = 164
};

enum WdBorderDistanceFrom
{
    wdBorderDistanceFromText = 0,
    wdBorderDistanceFromPageEdge = 1
};

enum WdReplace
{
    wdReplaceNone = 0,
    wdReplaceOne = 1,
    wdReplaceAll = 2
};

enum WdFontBias
{
    wdFontBiasDontCare = 255,
    wdFontBiasDefault = 0,
    wdFontBiasFareast = 1
};


enum WdBrowserLevel
{
    wdBrowserLevelV4 = 0,
    wdBrowserLevelMicrosoftInternetExplorer5 = 1,
    wdBrowserLevelMicrosoftInternetExplorer6 = 2
};

enum WdEnclosureType
{
    wdEnclosureCircle = 0,
    wdEnclosureSquare = 1,
    wdEnclosureTriangle = 2,
    wdEnclosureDiamond = 3
};

enum WdEncloseStyle
{
    wdEncloseStyleNone = 0,
    wdEncloseStyleSmall = 1,
    wdEncloseStyleLarge = 2
};

enum WdHighAnsiText
{
    wdHighAnsiIsFarEast = 0,
    wdHighAnsiIsHighAnsi = 1,
    wdAutoDetectHighAnsiFarEast = 2
};

enum WdLayoutMode
{
    wdLayoutModeDefault = 0,
    wdLayoutModeGrid = 1,
    wdLayoutModeLineGrid = 2,
    wdLayoutModeGenko = 3
};

enum WdDocumentMedium
{
    wdEmailMessage = 0,
    wdDocument = 1,
    wdWebPage = 2
};

enum WdMailerPriority
{
    wdPriorityNormal = 1,
    wdPriorityLow = 2,
    wdPriorityHigh = 3
};

enum WdDocumentViewDirection
{
    wdDocumentViewRtl = 0,
    wdDocumentViewLtr = 1
};

enum WdArabicNumeral
{
    wdNumeralArabic = 0,
    wdNumeralHindi = 1,
    wdNumeralContext = 2,
    wdNumeralSystem = 3
};

enum WdMonthNames
{
    wdMonthNamesArabic = 0,
    wdMonthNamesEnglish = 1,
    wdMonthNamesFrench = 2
};

enum WdCursorMovement
{
    wdCursorMovementLogical = 0,
    wdCursorMovementVisual = 1
};

enum WdVisualSelection
{
    wdVisualSelectionBlock = 0,
    wdVisualSelectionContinuous = 1
};

enum WdTableDirection
{
    wdTableDirectionRtl = 0,
    wdTableDirectionLtr = 1
};

enum WdFlowDirection
{
    wdFlowLtr = 0,
    wdFlowRtl = 1
};

enum WdDiacriticColor
{
    wdDiacriticColorBidi = 0,
    wdDiacriticColorLatin = 1
};

enum WdGutterStyle
{
    wdGutterPosLeft = 0,
    wdGutterPosTop = 1,
    wdGutterPosRight = 2
};

enum WdGutterStyleOld
{
    wdGutterStyleLatin = -10,
    wdGutterStyleBidi = 2
};

enum WdSectionDirection
{
    wdSectionDirectionRtl = 0,
    wdSectionDirectionLtr = 1
};

enum WdDateLanguage
{
    wdDateLanguageBidi = 10,
    wdDateLanguageLatin = 1033
};

enum WdCalendarTypeBi
{
    wdCalendarTypeBidi = 99,
    wdCalendarTypeGregorian = 100
};

enum WdCalendarType
{
    wdCalendarWestern = 0,
    wdCalendarArabic = 1,
    wdCalendarHebrew = 2,
    wdCalendarChina = 3,
    wdCalendarJapan = 4,
    wdCalendarThai = 5,
    wdCalendarKorean = 6,
    wdCalendarSakaEra = 7
};

enum WdReadingOrder
{
    wdReadingOrderRtl = 0,
    wdReadingOrderLtr = 1
};

enum WdHebSpellStart
{
    wdFullScript = 0,
    wdPartialScript = 1,
    wdMixedScript = 2,
    wdMixedAuthorizedScript = 3
};

enum WdAraSpeller
{
    wdNone = 0,
    wdInitialAlef = 1,
    wdFinalYaa = 2,
    wdBoth = 3
};

enum WdColor
{
    wdColorAutomatic = -16777216,
    wdColorBlack = 0,
    wdColorBlue = 16711680,
    wdColorTurquoise = 16776960,
    wdColorBrightGreen = 65280,
    wdColorPink = 16711935,
    wdColorRed = 255,
    wdColorYellow = 65535,
    wdColorWhite = 16777215,
    wdColorDarkBlue = 8388608,
    wdColorTeal = 8421376,
    wdColorGreen = 32768,
    wdColorViolet = 8388736,
    wdColorDarkRed = 128,
    wdColorDarkYellow = 32896,
    wdColorBrown = 13209,
    wdColorOliveGreen = 13107,
    wdColorDarkGreen = 13056,
    wdColorDarkTeal = 6697728,
    wdColorIndigo = 10040115,
    wdColorOrange = 26367,
    wdColorBlueGray = 10053222,
    wdColorLightOrange = 39423,
    wdColorLime = 52377,
    wdColorSeaGreen = 6723891,
    wdColorAqua = 13421619,
    wdColorLightBlue = 16737843,
    wdColorGold = 52479,
    wdColorSkyBlue = 16763904,
    wdColorPlum = 6697881,
    wdColorRose = 13408767,
    wdColorTan = 10079487,
    wdColorLightYellow = 10092543,
    wdColorLightGreen = 13434828,
    wdColorLightTurquoise = 16777164,
    wdColorPaleBlue = 16764057,
    wdColorLavender = 16751052,
    wdColorGray05 = 15987699,
    wdColorGray10 = 15132390,
    wdColorGray125 = 14737632,
    wdColorGray15 = 14277081,
    wdColorGray20 = 13421772,
    wdColorGray25 = 12632256,
    wdColorGray30 = 11776947,
    wdColorGray35 = 10921638,
    wdColorGray375 = 10526880,
    wdColorGray40 = 10066329,
    wdColorGray45 = 9211020,
    wdColorGray50 = 8421504,
    wdColorGray55 = 7566195,
    wdColorGray60 = 6710886,
    wdColorGray625 = 6316128,
    wdColorGray65 = 5855577,
    wdColorGray70 = 5000268,
    wdColorGray75 = 4210752,
    wdColorGray80 = 3355443,
    wdColorGray85 = 2500134,
    wdColorGray875 = 2105376,
    wdColorGray90 = 1644825,
    wdColorGray95 = 789516
};

enum WdShapePosition
{
    wdShapeTop = -999999,
    wdShapeLeft = -999998,
    wdShapeBottom = -999997,
    wdShapeRight = -999996,
    wdShapeCenter = -999995,
    wdShapeInside = -999994,
    wdShapeOutside = -999993
};

enum WdTablePosition
{
    wdTableTop = -999999,
    wdTableLeft = -999998,
    wdTableBottom = -999997,
    wdTableRight = -999996,
    wdTableCenter = -999995,
    wdTableInside = -999994,
    wdTableOutside = -999993
};

enum WdDefaultListBehavior
{
    wdWord8ListBehavior = 0,
    wdWord9ListBehavior = 1,
    wdWord10ListBehavior = 2
};

enum WdDefaultTableBehavior
{
    wdWord8TableBehavior = 0,
    wdWord9TableBehavior = 1
};

enum WdAutoFitBehavior
{
    wdAutoFitFixed = 0,
    wdAutoFitContent = 1,
    wdAutoFitWindow = 2
};

enum WdPreferredWidthType
{
    wdPreferredWidthAuto = 1,
    wdPreferredWidthPercent = 2,
    wdPreferredWidthPoints = 3
};

enum WdFarEastLineBreakLanguageID
{
    wdLineBreakJapanese = 1041,
    wdLineBreakKorean = 1042,
    wdLineBreakSimplifiedChinese = 2052,
    wdLineBreakTraditionalChinese = 1028
};

enum WdViewTypeOld
{
    wdPageView = 3,
    wdOnlineView = 6
};

enum WdFramesetType
{
    wdFramesetTypeFrameset = 0,
    wdFramesetTypeFrame = 1
};

enum WdFramesetSizeType
{
    wdFramesetSizeTypePercent = 0,
    wdFramesetSizeTypeFixed = 1,
    wdFramesetSizeTypeRelative = 2
};

enum WdFramesetNewFrameLocation
{
    wdFramesetNewFrameAbove = 0,
    wdFramesetNewFrameBelow = 1,
    wdFramesetNewFrameRight = 2,
    wdFramesetNewFrameLeft = 3
};

enum WdScrollbarType
{
    wdScrollbarTypeAuto = 0,
    wdScrollbarTypeYes = 1,
    wdScrollbarTypeNo = 2
};

enum WdTwoLinesInOneType
{
    wdTwoLinesInOneNone = 0,
    wdTwoLinesInOneNoBrackets = 1,
    wdTwoLinesInOneParentheses = 2,
    wdTwoLinesInOneSquareBrackets = 3,
    wdTwoLinesInOneAngleBrackets = 4,
    wdTwoLinesInOneCurlyBrackets = 5
};

enum WdHorizontalInVerticalType
{
    wdHorizontalInVerticalNone = 0,
    wdHorizontalInVerticalFitInLine = 1,
    wdHorizontalInVerticalResizeLine = 2
};

enum WdHorizontalLineAlignment
{
    wdHorizontalLineAlignLeft = 0,
    wdHorizontalLineAlignCenter = 1,
    wdHorizontalLineAlignRight = 2
};

enum WdHorizontalLineWidthType
{
    wdHorizontalLinePercentWidth = -1,
    wdHorizontalLineFixedWidth = -2
};

enum WdPhoneticGuideAlignmentType
{
    wdPhoneticGuideAlignmentCenter = 0,
    wdPhoneticGuideAlignmentZeroOneZero = 1,
    wdPhoneticGuideAlignmentOneTwoOne = 2,
    wdPhoneticGuideAlignmentLeft = 3,
    wdPhoneticGuideAlignmentRight = 4,
    wdPhoneticGuideAlignmentRightVertical = 5
};

enum WdNewDocumentType
{
    wdNewBlankDocument = 0,
    wdNewWebPage = 1,
    wdNewEmailMessage = 2,
    wdNewFrameset = 3,
    wdNewXMLDocument = 4
};

enum WdKana
{
    wdKanaKatakana = 8,
    wdKanaHiragana = 9
};

enum WdCharacterWidth
{
    wdWidthHalfWidth = 6,
    wdWidthFullWidth = 7
};

enum WdNumberStyleWordBasicBiDi
{
    wdListNumberStyleBidi1 = 49,
    wdListNumberStyleBidi2 = 50,
    wdCaptionNumberStyleBidiLetter1 = 49,
    wdCaptionNumberStyleBidiLetter2 = 50,
    wdNoteNumberStyleBidiLetter1 = 49,
    wdNoteNumberStyleBidiLetter2 = 50,
    wdPageNumberStyleBidiLetter1 = 49,
    wdPageNumberStyleBidiLetter2 = 50
};

enum WdTCSCConverterDirection
{
    wdTCSCConverterDirectionSCTC = 0,
    wdTCSCConverterDirectionTCSC = 1,
    wdTCSCConverterDirectionAuto = 2
};

enum WdDisableFeaturesIntroducedAfter
{
    wd70 = 0,
    wd70FE = 1,
    wd80 = 2
};

enum WdWrapTypeMerged
{
    wdWrapMergeInline = 0,
    wdWrapMergeSquare = 1,
    wdWrapMergeTight = 2,
    wdWrapMergeBehind = 3,
    wdWrapMergeFront = 4,
    wdWrapMergeThrough = 5,
    wdWrapMergeTopBottom = 6
};

enum WdRecoveryType
{
    wdPasteDefault = 0,
    wdSingleCellText = 5,
    wdSingleCellTable = 6,
    wdListContinueNumbering = 7,
    wdListRestartNumbering = 8,
    wdTableInsertAsRows = 11,
    wdTableAppendTable = 10,
    wdTableOriginalFormatting = 12,
    wdChartPicture = 13,
    wdChart = 14,
    wdChartLinked = 15,
    wdFormatOriginalFormatting = 16,
    wdFormatSurroundingFormattingWithEmphasis = 20,
    wdFormatPlainText = 22,
    wdTableOverwriteCells = 23,
    wdListCombineWithExistingList = 24,
    wdListDontMerge = 25
};

enum WdLineEndingType
{
    wdCRLF = 0,
    wdCROnly = 1,
    wdLFOnly = 2,
    wdLFCR = 3,
    wdLSPS = 4
};

enum WdStyleSheetLinkType
{
    wdStyleSheetLinkTypeLinked = 0,
    wdStyleSheetLinkTypeImported = 1
};

enum WdStyleSheetPrecedence
{
    wdStyleSheetPrecedenceHigher = -1,
    wdStyleSheetPrecedenceLower = -2,
    wdStyleSheetPrecedenceHighest = 1,
    wdStyleSheetPrecedenceLowest = 0
};

enum WdEmailHTMLFidelity
{
    wdEmailHTMLFidelityLow = 1,
    wdEmailHTMLFidelityMedium = 2,
    wdEmailHTMLFidelityHigh = 3
};

enum WdMailMergeMailFormat
{
    wdMailFormatPlainText = 0,
    wdMailFormatHTML = 1
};

enum WdMappedDataFields
{
    wdUniqueIdentifier = 1,
    wdCourtesyTitle = 2,
    wdFirstName = 3,
    wdMiddleName = 4,
    wdLastName = 5,
    wdSuffix = 6,
    wdNickname = 7,
    wdJobTitle = 8,
    wdCompany = 9,
    wdAddress1 = 10,
    wdAddress2 = 11,
    wdCity = 12,
    wdState = 13,
    wdPostalCode = 14,
    wdCountryRegion = 15,
    wdBusinessPhone = 16,
    wdBusinessFax = 17,
    wdHomePhone = 18,
    wdHomeFax = 19,
    wdEmailAddress = 20,
    wdWebPageURL = 21,
    wdSpouseCourtesyTitle = 22,
    wdSpouseFirstName = 23,
    wdSpouseMiddleName = 24,
    wdSpouseLastName = 25,
    wdSpouseNickname = 26,
    wdRubyFirstName = 27,
    wdRubyLastName = 28,
    wdAddress3 = 29,
    wdDepartment = 30
};

enum WdConditionCode
{
    wdFirstRow = 0,
    wdLastRow = 1,
    wdOddRowBanding = 2,
    wdEvenRowBanding = 3,
    wdFirstColumn = 4,
    wdLastColumn = 5,
    wdOddColumnBanding = 6,
    wdEvenColumnBanding = 7,
    wdNECell = 8,
    wdNWCell = 9,
    wdSECell = 10,
    wdSWCell = 11
};

enum WdCompareTarget
{
    wdCompareTargetSelected = 0,
    wdCompareTargetCurrent = 1,
    wdCompareTargetNew = 2
};

enum WdMergeTarget
{
    wdMergeTargetSelected = 0,
    wdMergeTargetCurrent = 1,
    wdMergeTargetNew = 2
};

enum WdUseFormattingFrom
{
    wdFormattingFromCurrent = 0,
    wdFormattingFromSelected = 1,
    wdFormattingFromPrompt = 2
};

enum WdRevisionsView
{
    wdRevisionsViewFinal = 0,
    wdRevisionsViewOriginal = 1
};

enum WdRevisionsMode
{
    wdBalloonRevisions = 0,
    wdInLineRevisions = 1,
    wdMixedRevisions = 2
};

enum WdRevisionsBalloonWidthType
{
    wdBalloonWidthPercent = 0,
    wdBalloonWidthPoints = 1
};

enum WdRevisionsBalloonPrintOrientation
{
    wdBalloonPrintOrientationAuto = 0,
    wdBalloonPrintOrientationPreserve = 1,
    wdBalloonPrintOrientationForceLandscape = 2
};

enum WdRevisionsBalloonMargin
{
    wdLeftMargin = 0,
    wdRightMargin = 1
};

enum WdTaskPanes
{
    wdTaskPaneFormatting = 0,
    wdTaskPaneRevealFormatting = 1,
    wdTaskPaneMailMerge = 2,
    wdTaskPaneTranslate = 3,
    wdTaskPaneSearch = 4,
    wdTaskPaneXMLStructure = 5,
    wdTaskPaneDocumentProtection = 6,
    wdTaskPaneDocumentActions = 7,
    wdTaskPaneSharedWorkspace = 8,
    wdTaskPaneHelp = 9,
    wdTaskPaneResearch = 10,
    wdTaskPaneFaxService = 11,
    wdTaskPaneXMLDocument = 12,
    wdTaskPaneDocumentUpdates = 13
};

enum WdShowFilter
{
    wdShowFilterStylesAvailable = 0,
    wdShowFilterStylesInUse = 1,
    wdShowFilterStylesAll = 2,
    wdShowFilterFormattingInUse = 3,
    wdShowFilterFormattingAvailable = 4
};

enum WdMergeSubType
{
    wdMergeSubTypeOther = 0,
    wdMergeSubTypeAccess = 1,
    wdMergeSubTypeOAL = 2,
    wdMergeSubTypeOLEDBWord = 3,
    wdMergeSubTypeWorks = 4,
    wdMergeSubTypeOLEDBText = 5,
    wdMergeSubTypeOutlook = 6,
    wdMergeSubTypeWord = 7,
    wdMergeSubTypeWord2000 = 8
};

enum WdDocumentDirection
{
    wdLeftToRight = 0,
    wdRightToLeft = 1
};

enum WdLanguageID2000
{
    wdChineseHongKong = 3076,
    wdChineseMacao = 5124,
    wdEnglishTrinidad = 11273
};

enum WdRectangleType
{
    wdTextRectangle = 0,
    wdShapeRectangle = 1,
    wdMarkupRectangle = 2,
    wdMarkupRectangleButton = 3,
    wdPageBorderRectangle = 4,
    wdLineBetweenColumnRectangle = 5,
    wdSelection = 6,
    wdSystem = 7
};

enum WdLineType
{
    wdTextLine = 0,
    wdTableRow = 1
};

enum WdXMLNodeType
{
    wdXMLNodeElement = 1,
    wdXMLNodeAttribute = 2
};

enum WdXMLSelectionChangeReason
{
    wdXMLSelectionChangeReasonMove = 0,
    wdXMLSelectionChangeReasonInsert = 1,
    wdXMLSelectionChangeReasonDelete = 2
};

enum WdXMLNodeLevel
{
    wdXMLNodeLevelInline = 0,
    wdXMLNodeLevelParagraph = 1,
    wdXMLNodeLevelRow = 2,
    wdXMLNodeLevelCell = 3
};

enum WdSmartTagControlType
{
    wdControlSmartTag = 1,
    wdControlLink = 2,
    wdControlHelp = 3,
    wdControlHelpURL = 4,
    wdControlSeparator = 5,
    wdControlButton = 6,
    wdControlLabel = 7,
    wdControlImage = 8,
    wdControlCheckbox = 9,
    wdControlTextbox = 10,
    wdControlListbox = 11,
    wdControlCombo = 12,
    wdControlActiveX = 13,
    wdControlDocumentFragment = 14,
    wdControlDocumentFragmentURL = 15,
    wdControlRadioGroup = 16
};

enum WdEditorType
{
    wdEditorEveryone = -1,
    wdEditorOwners = -4,
    wdEditorEditors = -5,
    wdEditorCurrent = -6
};

enum WdXMLValidationStatus
{
    wdXMLValidationStatusOK = 0,
    wdXMLValidationStatusCustom = -1072898048
};


}

#endif
