/// *************************************************************************
///                              ʹ��˵��
///     ���Դ�����Ǳ�����д��MFC�ؼ��� (PFX pushall studio MFC foundation
/// classes) �е�һ���֣������类���ڱ�����д��һ������༭���LiteEdit�У�
/// ������õ��˺ܶ����ѵĿ϶������˶�֧�� LiteEdit�����ѱ�ʾ����ĸм���Ӧ
/// �ܶ����ѵ�Ҫ���Լ����ǵ���л��Ҷ� LiteEdit��֧�֣��������ڹ���LiteEdit
/// ��ʹ�õı༭�ؼ�PfxEditCtrl��Դ���룬�����Ҫʹ����ݴ��룬����Ҫͬ����
/// ��ʹ��Э�飬����㲻ͬ���벻Ҫʹ����ݴ��롣
///                                                     by �½���2005-11-07
///                                                 Email: pushall@21cn.com
/// *************************************************************************
///                              ���Э��
/// 1) ���˱���ǩ��Ȩ��ʼ�����ļ��б����������ݡ�
/// 2) Ŀǰ��ݴ���İ汾���˳�Ϊ 1.2�棬������˱�д����ݴ�����°汾����
///        �°汾ͬ���������ڱ�Э�飬����û������Ҫ�����°汾�Ĵ��룬ͬʱ��
///        �汾�İ�Ȩ���κ�����¶��鱾�����У����Ǳ�������������
/// 3) ������д�����LiteEdit��ȻҲʹ��������ؼ���LiteEdit���ܱ�Э�����ơ�
/// 4) �����Ϊʹ����ݴ���������������κε���ʧ�����˲����κ����Ρ�
/// 5) ��������⸴�ơ�ʹ�á��޸ġ�������ݴ��롣
/// 6) ����Խ���ݴ���������ĸ��˵ġ���˾����ҵ�ġ���ѵġ���ҵ�ĵȸ�����
///       ʽ��Ӧ���С�
/// 7) ������޸�����ݴ��룬����Բ�������������㹫���������޸ĺ�İ汾��
///       ��Ȩ�������С�
/// *************************************************************************

/////////////////////////////////////////////////////////////////////////////
// BUG
// 2005-10-10
// ����������
//     ��һЩ�ڰ״�ӡ������ͼ��ʾ��ɫ�ı�ʱ�����޷���ʾ��ע�����BUG ���Ѿ�
//     ��ʱ��ȥ������ʹ�õ������Լ�ȥ�������
//
// ���������
//     ������Ϊ�ڰ״�ӡ������ɫ�ϲ�֧��ѡ�����ɫ������������쵽��16ɫ��
//     256ɫ����Ļ��ʾģʽ��Ҳ��ͬ�������⡣
//
// ����취��
//     ����һ��ɫ���Դ�ӡ���Ƿ�֧��ĳ��ɫ���м�飬����ƥ�����ɫ��������
//
// ��������
//     2005-11-07������õ������
//
// �����޸�
// 2005-11-07
//      2005-10-10��2005-11-07���¶�CPfxEditHash��CPfxEditTypeInfo��
//      CPfxEditPrintInfo��CPfxEditAlloc��CPfxEditHeap��CPfxEditData������
//      �˵�����ʹ������ͳһ���ڴ����Դ��ΪCPfxEditTypeInfo��
//      CPfxEditPrintInfo������ɫ������
/////////////////////////////////////////////////////////////////////////////
#pragma once
#include <afxole.h>
#include <afxplex_.h>

/////////////////////////////////////////////////////////////////////////////
namespace CPfx 
{ // Pushall Studio MFC Foundation classes - by ChenJianChu

	/////////////////////////////////////////////////////////////////////////////
	// �������Ҫ����ΪUNICODE�棬����Ҫ�޸�һЩ�õ�PFX_EC_MAX_MB_LEN�ĵط���
	// ��û���Թ���_UNICODEģʽ�±��룬���Ѿ�Ϊ��_UNICODEģʽ�±�����׼����
	// #ifdef _UNICODE
	// #error CPfxEditCtrl NOT SUPPORT UNICODE!
	// #endif

	/////////////////////////////////////////////////////////////////////////////
	class CPfxEditDoc;
	class CPfxEditView;


#define PfxEditView_use_CView

#ifdef PfxEditView_use_CView
#define PfxEditViewPRentClass CView
#endif

#ifdef PfxEditView_use_CEdit
#define PfxEditViewPRentClass CEdit
#endif

#ifdef PfxEditView_use_CStatic
#define PfxEditViewPRentClass CStatic
#endif

	/////////////////////////////////////////////////////////////////////////////
#define PFX_EC_SIZEOF(x)         (sizeof(x) / sizeof(x[0]))
#define PFX_EC_SIZEOF_NO_NULL(x) ((sizeof(x) / sizeof(x[0])) - 1)
#define PFX_EC_ROUND(x, y)       ((((static_cast<size_t>(x)) + (static_cast<size_t>(y) - 1)) / (static_cast<size_t>(y))) * static_cast<size_t>(y))
#define PFX_EC_ROUND4(x)         (PFX_EC_ROUND(x, 4))

	/////////////////////////////////////////////////////////////////////////////
	// Ĭ����ɫ���á�
#define PFX_EC_CLR_RULER                      (COLORREF)::GetSysColor(COLOR_WINDOWTEXT)
#define PFX_EC_CLR_LINE_NUMBER                (COLORREF)::GetSysColor(COLOR_WINDOWTEXT)
#define PFX_EC_CLR_TEXT                       (COLORREF)::GetSysColor(COLOR_WINDOWTEXT)
#define PFX_EC_CLR_TEXT_SELECTED              (COLORREF)::GetSysColor(COLOR_HIGHLIGHTTEXT)
#define PFX_EC_CLR_WHITESPACE                 (COLORREF)0xFFCC66
#define PFX_EC_CLR_LINE_COMMENT1              (COLORREF)RGB(0, 128, 0)
#define PFX_EC_CLR_LINE_COMMENT2              (COLORREF)RGB(0, 128, 0)
#define PFX_EC_CLR_BLOCK_COMMENT1             (COLORREF)RGB(0, 128, 0)
#define PFX_EC_CLR_BLOCK_COMMENT2             (COLORREF)RGB(0, 128, 0)
#define PFX_EC_CLR_QUOTED_STRING1             (COLORREF)RGB(128, 128, 128)
#define PFX_EC_CLR_QUOTED_STRING2             (COLORREF)RGB(128, 128, 128)
#define PFX_EC_CLR_BK_TEXT                    (COLORREF)::GetSysColor(COLOR_WINDOW)
#define PFX_EC_CLR_BK_TEXT_SELECTED           (COLORREF)::GetSysColor(COLOR_HIGHLIGHT)
#define PFX_EC_CLR_BK_RULER                   (COLORREF)::GetSysColor(COLOR_3DFACE)
#define PFX_EC_CLR_BK_LINE_NUMBER             (COLORREF)::GetSysColor(COLOR_3DFACE)
#define PFX_EC_CLR_BK_BOOKMARK                (COLORREF)0xFFCC66
#define PFX_EC_CLR_BK_ACTIVE_LINE             (COLORREF)0x00FFFF

	/////////////////////////////////////////////////////////////////////////////
	// Ŀǰ��֧��GB18030��VC7�е�MB_LEN_MAX����5����ᵼ�²�������������
	const LONG PFX_EC_MAX_MB_LEN                  = 2;
	const LONG PFX_EC_MAX_TAB_SIZE                = 64;
	const LONG PFX_EC_MAX_LINE_LENGTH             = 8192;

	const LONG PFX_EC_TASKMEM_CONST_SIZE          = 4096 * 8; // 32K
	const LONG PFX_EC_TASKMEM_ALLOC_SIZE          = 4096 * 4; // 16K

	/////////////////////////////////////////////////////////////////////////////
	// ����/�ָ�������
	const WORD PFX_EC_UNDO_UNKNOWN                = 0;
	const WORD PFX_EC_UNDO_TYPING                 = 1;
	const WORD PFX_EC_UNDO_REMOVE                 = 2;
	const WORD PFX_EC_UNDO_INSERT                 = 3;
	const WORD PFX_EC_UNDO_CUT                    = 4;
	const WORD PFX_EC_UNDO_PASTE                  = 5;
	const WORD PFX_EC_UNDO_REPLACE                = 6;
	const WORD PFX_EC_UNDO_REPLACE_ALL            = 7;
	const WORD PFX_EC_UNDO_DRAGDROP_COPY          = 8;
	const WORD PFX_EC_UNDO_DRAGDROP_MOVE          = 9;
	const WORD PFX_EC_UNDO_CASE_LOWER             = 10;
	const WORD PFX_EC_UNDO_CASE_UPPER             = 11;
	const WORD PFX_EC_UNDO_CASE_INVERT            = 12;
	const WORD PFX_EC_UNDO_CASE_CAPITALIZE        = 13;
	const WORD PFX_EC_UNDO_SPACES_TO_TABS         = 14;
	const WORD PFX_EC_UNDO_SPACES_TO_TABS_LEADING = 15;
	const WORD PFX_EC_UNDO_TABS_TO_SPACES         = 16;
	const WORD PFX_EC_UNDO_TRIM_TRAILING_SPACES   = 17;

	/////////////////////////////////////////////////////////////////////////////
	// �ļ�ת����
	const LONG PFX_EC_FILE_CONVERTER_AUTO_DETECT  = 0;
	const LONG PFX_EC_FILE_CONVERTER_ANSI         = 1;
	const LONG PFX_EC_FILE_CONVERTER_UTF8         = 2;
	const LONG PFX_EC_FILE_CONVERTER_UNICODE      = 3;
	const LONG PFX_EC_FILE_CONVERTER_UNICODE_BIG_ENDIAN = 4;

	/////////////////////////////////////////////////////////////////////////////
	// �ĵ���ʽ
	const LONG PFX_EC_LINE_BREAK_TYPE_DOS         = 0;
	const LONG PFX_EC_LINE_BREAK_TYPE_UNIX        = 1;
	const LONG PFX_EC_LINE_BREAK_TYPE_MAC         = 2;

	const LONG PFX_EC_LINE_BREAK_SIZE_DOS         = 2;
	const LONG PFX_EC_LINE_BREAK_SIZE_UNIX        = 1;
	const LONG PFX_EC_LINE_BREAK_SIZE_MAC         = 1;

	/////////////////////////////////////////////////////////////////////////////
	// ���б�־
	const LONG PFX_EC_WRAP_NONE                   = 0;
	const LONG PFX_EC_WRAP_WINDOWEDGE             = 1;
	const LONG PFX_EC_WRAP_COLUMNS                = 2;

	/////////////////////////////////////////////////////////////////////////////
	// ճ����ʽ
	const LONG PFX_EC_PASTE_NORMAL                = 0;
	const LONG PFX_EC_PASTE_COLUMN_ALIGN          = 1;
	const LONG PFX_EC_PASTE_COLUMN_APPEND         = 2;

	/////////////////////////////////////////////////////////////////////////////
	// ��ӡ��Χ
	const LONG PFX_EC_PRINT_PAGES_ALL             = 0;
	const LONG PFX_EC_PRINT_PAGES_ODD             = 1;
	const LONG PFX_EC_PRINT_PAGES_EVEN            = 2;

	/////////////////////////////////////////////////////////////////////////////
	// ��ӡҳü�ͽ�ע�Ĳ�����Ҫ����һ����&������ʹ�á�&&����
	// ��ǰҳ��
#define PFX_EC_PRINT_MACRO_CURRENT_PAGE       _T("&p")

	// ��ҳ����
#define PFX_EC_PRINT_MACRO_TOTAL_PAGES        _T("&P")

	// �ļ�����
#define PFX_EC_PRINT_MACRO_FILE_NAME          _T("&f")

	// ·������
#define PFX_EC_PRINT_MACRO_PATH_NAME          _T("&F")

	// ���ڡ�
#define PFX_EC_PRINT_MACRO_DATE               _T("&D")

	// ʱ�䡣
#define PFX_EC_PRINT_MACRO_TIME               _T("&T")

	// �Ʊ����
#define PFX_EC_PRINT_MACRO_TAB                _T("&t")

	// �س����С�
#define PFX_EC_PRINT_MACRO_CRLF               _T("&b")

	// ������롣
#define PFX_EC_PRINT_MACRO_ALIGN_LEFT         _T("&l")

	// ���Ҷ��롣
#define PFX_EC_PRINT_MACRO_ALIGN_RIGHT        _T("&r")

	// ���ж��롣
#define PFX_EC_PRINT_MACRO_ALIGN_CENTER       _T("&c")

	/////////////////////////////////////////////////////////////////////////////
	// �¼�֪ͨ��Ϣ����ο�CPfxEditDoc::OnEvent()������
	// ��Ϣ��PFX_EN_READ_ONLY_DOCUMENT
	// �������ĵ�ֻ�������޸ġ�
	// ������LPARAM = ������
	const LONG PFX_EN_READ_ONLY_DOCUMENT          = 0x0001;

	// ��Ϣ��PFX_EN_SEARCH_PASSED_END_OF_FILE
	// �����������Ѵﾡͷ��������ĩβ��ͷ����
	// ������LPARAM = EOFԽ��ĩβ������Խ����ͷ��
	const LONG PFX_EN_SEARCH_PASSED_EOF           = 0x0002;

	// ��Ϣ��PFX_EN_WORD_WRAPPING
	// ���������ڼ����Զ����С�
	// ������LPARAM = �Ѿ���ɵİٷֱȡ�
	// ���أ�����0���㻻�У����ط�����ֹ���м��㡣
	const LONG PFX_EN_WORD_WRAPPING               = 0x0003;

	/////////////////////////////////////////////////////////////////////////////
	// ������Ϣ
	// �ؼ��ڲ�����
	const LONG PFX_EE_INTERNAL_ERROR              = 0x0100;

	// ϵͳδ֪����
	const LONG PFX_EE_UNKNOWN_ERROR               = 0x0101;

	// ��Ϣ��PFX_EE_OUT_OF_MEMORY
	// ������ϵͳ�ڴ治�㡣
	// ������LPARAM = 0��
	// ���أ����ԡ�
	const LONG PFX_EE_OUT_OF_MEMORY               = 0x0102;

	// ��Ϣ��PFX_EE_OUT_OF_RESOURCE
	// ������ϵͳ��Դ���㡣
	// ������LPARAM = 0��
	// ���أ����ԡ�
	const LONG PFX_EE_OUT_OF_RESOURCE             = 0x0103;

	// ��Ϣ��PFX_EE_CONVERT_ERR_ON_LOADING
	// ������װ���ļ�ʱ���ַ���ת������
	// ������LPARAM = 0��
	// ���أ����ԡ�
	const LONG PFX_EE_CONVERT_ERR_ON_LOADING      = 0x0104;

	// ��Ϣ��PFX_EE_CONVERT_ERR_ON_SAVING
	// �����������ļ�ʱ���ַ���ת������
	// ������LPARAM = 0��
	// ���أ����ԡ�
	const LONG PFX_EE_CONVERT_ERR_ON_SAVING       = 0x0105;

	/////////////////////////////////////////////////////////////////////////////
	// CPfxEditAlloc ����CRT���ڵľ�̬�ڴ��������
	class CPfxEditAlloc
	{
	public:
		class CAllocator
		{
		public:
			struct CNode
			{
				CNode*         pNext;
			};

			struct CPlex
			{
				size_t         nUsed;
				CPlex*         pNext;
				CPlex*         pPrev;
				CNode*         pNodeFree;
				void*          data() { return this + 1; }
			};

			size_t         m_nMaxUnits;  // ÿ���ڴ�����ܷ���ĵ�Ԫ����
			size_t         m_nUnitSize;  // ��Ԫ��С���ֽڣ���
			size_t         m_nBlockSize; // ÿ���ڴ�Ĵ�С���ֽڣ���
			size_t         m_nBlocks;    // ��ǰ���ж��ٿ��ڴ档
			CPlex*         m_pBlocks;    // �ڴ����ͷ��˫������
		public:
			CAllocator(size_t nUnitSize, size_t nMaxUnits = 64);
			~CAllocator() { FreeAll(); }
		public:
			void*          Alloc();
			void           Free(void* lp);
			void           FreeAll();
			size_t         GetUnitSize() { return m_nUnitSize; }
#ifdef _DEBUG
			void           Dump(CDumpContext& dc) const;
#endif
		};

		CAllocator     m_b1; // 8
		CAllocator     m_b2; // 16
		CAllocator     m_b3; // 24
		CAllocator     m_b4; // 32
		CAllocator     m_b5; // 64
		CAllocator     m_b6; // 128
		CAllocator     m_b7; // 256
		CAllocator     m_b8; // 512

	public:
		CPfxEditAlloc();
		~CPfxEditAlloc();

	public:
		void*          Alloc(size_t cb);
		void           Free(void* lp);
		void           FreeAll();
	};

	/////////////////////////////////////////////////////////////////////////////
	// CPfxEditHeap ���ڶ�ջ�ϵĶ�̬�ڴ��������
	class CPfxEditHeap
	{
	public:
		class CAllocator
		{
			class CNode
			{
			public:
				size_t         nRef;
				size_t         nSize;
				CNode*         pNext;
				CNode*         pPrev;
				void*          data() { return reinterpret_cast<void*>(this + 1); }
			};
			CNode*         m_pNodes;
			size_t         m_nNodes;
		public:
			CAllocator()   { m_pNodes = NULL; m_nNodes = 0; }
			~CAllocator()  { FreeAll(); }
		public:
			LPVOID         Alloc(size_t cb);
			void           Free(void* lp);
			void           FreeAll();
		};

	public:
		// ��ǰ�û�Ҫ��Ļ�������С��
		size_t         m_nDataSize;

		// ��ǰʵ�ʷ���Ļ�������С(m_nBufferSize >= m_nDataSize)��
		size_t         m_nBufferSize;

		// ��������ַ��
		void*          m_pBuffer;

	public:
		CPfxEditHeap()  { m_pBuffer = NULL; m_nBufferSize = m_nDataSize = 0; }
		~CPfxEditHeap() { Free(); }

	public:
		// ��ȡ��������ַ��
		void*          GetBuffer() const { return m_pBuffer; }

		// ��ȡ����Ļ�������С��ʹ�������С���Լӿ��ٶȡ�
		size_t         GetBufferConstSize() const { return PFX_EC_TASKMEM_CONST_SIZE; }

		// ���䡣
		void*          Alloc(size_t cb);

		// ���µ�����������С����ԭ�������ݸ��Ƶ��µĻ������С�
		void*          ReAlloc(size_t cb);

		// �ͷš�
		void           Free();
	};

	/////////////////////////////////////////////////////////////////////////////
	// CPfxEditHash
	const LONG PFX_EC_KEYWORD_MAP_HASH_TABLE_SIZE = 256; // HASH����
	const LONG PFX_EC_KEYWORD_MAP_MAX_KEYWORD_LEN = 256; // ���������﷨�ؼ��ֳ��ȣ���������ֵ�����ض�

	class CPfxEditHash
	{
#pragma pack(push, 1)
		class CAssoc
		{
		public:
			CAssoc*        pNext;
			LONG           nKeyClass;
			LONG           cchKey;
			TCHAR          szKey[1];
		};
#pragma pack(pop)

		class CAssocInfo
		{
		public:
			UINT           nHash;
			LPCTSTR        pszKey;
			LONG           cchKey;
			CAssoc*        pAssoc;
		};

	public:
		CPfxEditHash();
		~CPfxEditHash();

	public:
		// �ҵ�����COLOR INDEX�����򷵻�-1��
		LONG           Lookup(LPCTSTR pszKey, LONG cch);
		LONG           GetCount() const;

		BOOL           IsMatchCase() const;
		void           SetMatchCase(BOOL bCase);

		void           SetAt(LONG nKeyClass, LPCTSTR pszKey);
		void           RemoveAt(LPCTSTR pszKey);
		void           RemoveAll();

	protected:
		BOOL           m_bMatchCase; // �ؼ����Ƿ���Ҫƥ���Сд��
		LONG           m_nCount; // �ؼ�����Ŀ��
		CAssoc*        m_arrHashTable[PFX_EC_KEYWORD_MAP_HASH_TABLE_SIZE];
		TCHAR          m_szKeyLower[PFX_EC_KEYWORD_MAP_MAX_KEYWORD_LEN + 1];

	protected:
		// Hash��ֵ����
		UINT           HashKey(LPCTSTR pKey, LONG cch) const;
		BOOL           GetAssocAt(LPCTSTR pKey, LONG cch, CAssocInfo& retVal);
	};

	__forceinline UINT     CPfxEditHash::HashKey(LPCTSTR pKey, LONG cch) const
	{
		UINT nHash = 0;
		LPCTSTR lp = pKey + min(cch, PFX_EC_KEYWORD_MAP_HASH_TABLE_SIZE);
		while (pKey < lp)
		{
			nHash = (nHash << 5) + nHash + *pKey++;
		}
		return (nHash % PFX_EC_KEYWORD_MAP_HASH_TABLE_SIZE);
	}

	__forceinline LONG     CPfxEditHash::Lookup(LPCTSTR pszKey, LONG cch)
	{
		CAssocInfo i;
		return (GetAssocAt(pszKey, cch, i) ? i.pAssoc->nKeyClass : -1);
	}

	inline BOOL            CPfxEditHash::IsMatchCase() const    { return m_bMatchCase; }
	inline LONG            CPfxEditHash::GetCount() const       { return m_nCount; }
	inline void            CPfxEditHash::SetMatchCase(BOOL bOn) { m_bMatchCase = bOn; }

	/////////////////////////////////////////////////////////////////////////////
	// ��������ɫ����֮��Ӧ�����ƣ����磺
	// {
	//   {RGB(0, 255, 0), _T("��ǩ��ɫ")},
	//   {RGB(0, 0, 255), _T("C++�ؼ���")}, 
	// };
	// ʹ������ṹ�бȽϴ������ԣ������Ժ������չ�������ԣ�����ĳ��KeyClass
	// ʹ�ô��壬б��ȶ�������������ӳ�Ա��
	class CPfxEditKeyClass
	{
	public:
		bool           m_bEmpty;
		COLORREF       m_color;
		CString        m_strClassName;
	public:
		CPfxEditKeyClass() { SetEmpty(); }
		CPfxEditKeyClass(LPCTSTR pszClassName, COLORREF color)
		{
			m_bEmpty = false;
			m_color = color;
			m_strClassName = pszClassName;
		}
	public:
		BOOL           IsEmpty() const { return m_bEmpty; }
		BOOL           IsClass(LPCTSTR pszClassName) const
		{
			return ((pszClassName != NULL)
				&& (IsEmpty())
				&& (m_strClassName == pszClassName));
		}
		void           SetEmpty() 
		{ 
			m_bEmpty = true;
			m_color = CLR_INVALID; 
			m_strClassName.Empty(); 
		}
		CPfxEditKeyClass& operator=(const CPfxEditKeyClass& src)
		{
			m_bEmpty = src.m_bEmpty;
			m_color = src.m_color;
			m_strClassName = src.m_strClassName;
			return *this;
		}
		bool operator==(const CPfxEditKeyClass& src)
		{
			return (((m_bEmpty && src.m_bEmpty) || (!m_bEmpty && !src.m_bEmpty))
				&& (m_color == src.m_color)
				&& (m_strClassName == src.m_strClassName));
		}
		bool operator!=(const CPfxEditKeyClass& src)
		{
			return (((m_bEmpty && !src.m_bEmpty) || (!m_bEmpty && src.m_bEmpty))
				|| (m_color != src.m_color)
				|| (m_strClassName != src.m_strClassName));
		}
	};

	class CPfxEditMarkerPair // ���Ǳ䳤�Ƚṹ�塣
	{
	public:
		LPCTSTR        pszOn;
		LONG           cchOn;

		WCHAR          wLowerOn;
		WCHAR          wUpperOn;

		LPCTSTR        pszOff;
		LONG           cchOff;

		WCHAR          wLowerOff;
		WCHAR          wUpperOff;

		CPfxEditMarkerPair*   pNext;
		CPfxEditMarkerPair*   pPrev;

		TCHAR          szKey[sizeof(int)];
	};

	enum EPfxEditPredefinedKeyClass
	{
		kcLineNumber = 0,
		kcRuler,
		kcText,
		kcTextSelected,
		kcWhitespace,
		kcBkText,
		kcBkLineNumber,
		kcBkRuler,
		kcBkTextSelected,
		kcBkActiveLine,
		kcBkBookmark,
		kcHeaderAndFooter,

		kcQuotedString1,
		kcQuotedString2,
		kcLineComment1,
		kcLineComment2,
		kcBlockComment1,
		kcBlockComment2,

		kcPredefinedKeyClassNumber = 18,
		kcKeyClassArraySize = 36,
		kcUserCustomKeyClassNumber = (kcKeyClassArraySize - kcPredefinedKeyClassNumber),
	};

	enum EPfxEditMarkerPair
	{
		// ��ע�͡�
		mpLineComment1 = 0,
		mpLineComment2,

		// ��ע�Ϳ�ʼ�ͽ�����ʶ��
		mpBlockComment1,
		mpBlockComment2,

		// �����ַ����Ŀ�ʼ�ͽ�����ʶ��
		mpQuotedString1,
		mpQuotedString2,

		// ��Ա�ʶ�������硰{}������[]������()���ȡ�
		mpBraceStrings,

		mpMarkerPairNumber = 0x07,
	};

	/////////////////////////////////////////////////////////////////////////////
	// CPfxEditTypeInfo �����﷨��Ϣ��
	class CPfxEditTypeInfo
	{
	public:
		class CKeyClassArray
		{
		public:
			CPfxEditKeyClass m_arrClasses[kcKeyClassArraySize];

		public:
			CKeyClassArray();
			~CKeyClassArray();

		public:
			// �жϸ������������Ƿ�����Ч�Ĺؼ����顣
			BOOL           IsValidClass(LONG nIndex) const
			{
				return (nIndex >= 0) 
					&& (nIndex < PFX_EC_SIZEOF(m_arrClasses));
			}

			COLORREF       GetClassColor(LONG nIndex) const
			{
				ASSERT(IsValidClass(nIndex));
				return m_arrClasses[nIndex].m_color;
			}

			void           SetClassColor(LONG nIndex, COLORREF color)
			{
				ASSERT(IsValidClass(nIndex));
				m_arrClasses[nIndex].m_color = color;
			}

			// ��ȡ�ؼ��ַ�����Ϣ��
			POSITION       GetClassFirst() const;
			void           GetClassNext(POSITION& rPosition, CPfxEditKeyClass& theClass) const;

			// ��ӹؼ���-��ɫ����ԣ������ѱ���������š�
			LONG           SetClass(const CPfxEditKeyClass& theClass);

			LPCTSTR        GetClassName(LONG nIndex) const;
			void           SetClassName(LONG nIndex, LPCTSTR pszClassName);

			// ɾ��һ��Ԫ��
			void           RemoveClass(LONG nIndex);
			void           RemoveClass(LPCTSTR pszClassName);

			// ���ơ�
			CKeyClassArray& operator=(const CKeyClassArray& src);
		};

		class CMarkerPairArr
		{
		public:
			CPfxEditMarkerPair* m_arrMarkers[mpMarkerPairNumber];
		public:
			CMarkerPairArr();
			~CMarkerPairArr();
		public:
			BOOL           IsValidMarker(LONG nIndex) const
			{
				return (nIndex >= 0) 
					&& (nIndex < PFX_EC_SIZEOF(m_arrMarkers));
			}

			CPfxEditMarkerPair* GetMarker(EPfxEditMarkerPair id) const
			{
				return (IsValidMarker(id) ? m_arrMarkers[id] : NULL);
			}

			// ȫ���ͷš�
			void           RemoveAll();

			// �ͷ�һ�ڵ�����
			void           FreeMarkerChain(CPfxEditMarkerPair* pMarker);

			// ����һ�ڵ�����
			CPfxEditMarkerPair* CopyMarkerChain(CPfxEditMarkerPair* pMarker);

			// �����½ڵ㡣
			CPfxEditMarkerPair* CreateMarker(LPCTSTR pszOn, LPCTSTR pszOff);

			// ���ơ�
			CMarkerPairArr& operator=(const CMarkerPairArr& src);
		};

	public:
		CPfxEditTypeInfo();
		virtual        ~CPfxEditTypeInfo();

	public:
		BOOL           m_bDrawHilighted;
		BOOL           m_bDrawRuler;
		BOOL           m_bDrawLineNumber;
		BOOL           m_bDrawLineBreak;
		BOOL           m_bDrawWhitespace;

		BOOL           m_bEnableDragDrop;
		BOOL           m_bExpandTabToSpaceChars;
		BOOL           m_bHomeKeyGotoFirstNonWhitespaceChar;
		BOOL           m_bSyncTextBkColorWithSystem;
		BOOL           m_bSyncActiveLineBkColorWithTextBkColor;

		// �Ʊ���ĳ��ȡ�
		LONG           m_nTabSize;

		// �Զ��������ȡ�
		LONG           m_nIndentSize;

		// ���з�����
		LONG           m_nWrapStyle;

		// ���п�ȡ�
		LONG           m_nWrapWidth;

		// �ؼ�������ɫ��ӳ���
		CPfxEditHash   m_mapKeywords;

		// �ؼ�������Ϣ����ɫ����
		CKeyClassArray m_arrKeyClasses;

		// ����ַ�����
		CMarkerPairArr m_arrMarkerPair;

		// ת���ַ���
		WCHAR          m_wEscape;

		// ���ʶ������
		WCHAR          m_arrDelimiters[64];

	public:
		CPfxEditTypeInfo& operator=(const CPfxEditTypeInfo& src);

		// ��ȡ���ʶ������
		CString        GetDelimiters() const;
		static LPCTSTR GetDelimitersDefault();

		BOOL           IsEscape(WCHAR wc) const;
		BOOL           IsMatchCase() const;
		BOOL           IsDrawHilighted() const;

		void           SetDrawHilighted(BOOL bOn);

		// ���ùؼ����Ƿ�Ϊƥ���Сд��
		void           SetMatchCase(BOOL bCase);

		// ���õ��ʶ������
		void           SetDelimiters(LPCTSTR pszDelimiters);

		// ����ת���ַ�������C++��˵��_T("\\")����
		void           SetEscape(LPCTSTR pszEscape);

		// ************�ؼ�������Ϣ����ɫ����
		// �жϸ������������Ƿ�����Ч�Ĺؼ����顣
		BOOL           IsValidKeyClass(LONG nIndex) const;

		// ��ȡ�ؼ��ַ�����Ϣ��
		POSITION       GetKeyClassFirst() const;
		void           GetKeyClassNext(POSITION& rPosition, CPfxEditKeyClass& theClass) const;

		// ��ӹؼ���-��ɫ����ԣ������ѱ���������š�
		LONG           SetKeyClass(const CPfxEditKeyClass& theClass);

		void           RemoveKeyClass(LONG nIndex);
		void           RemoveKeyClass(LPCTSTR pszClassName);

		COLORREF       GetKeyClassColor(LONG Index) const;
		void           SetKeyClassColor(LONG nIndex, COLORREF color);

		LPCTSTR        GetKeyClassName(LONG nIndex) const;
		void           SetKeyClassName(LONG nIndex, LPCTSTR pszClassName);

		// ************�ؼ��ֹ���
		// ��ȡ�ؼ���������
		LONG           GetKeywordCount() const;

		// ��ӹؼ��֣���ɫ����������SetKeyClass()�ķǸ�������ֵ��
		void           SetKeyword(LONG nKeyClass, LPCTSTR pszKeyword);

		// ************�﷨������Ϣ��
		BOOL           HasMarkerPair(EPfxEditMarkerPair id) const;

		// ������Ա�ʶ�������硰{}������[]������()���ȡ�
		CPfxEditMarkerPair* GetMarkerPair(EPfxEditMarkerPair id) const;
		void           SetMarkerPair(EPfxEditMarkerPair id, LPCTSTR pszOn, LPCTSTR pszOff);
		void           AppendMarkerPair(EPfxEditMarkerPair id, LPCTSTR pszOn, LPCTSTR pszOff);
	};

	inline BOOL            CPfxEditTypeInfo::IsMatchCase() const        
	{ return m_mapKeywords.IsMatchCase(); }
	inline BOOL            CPfxEditTypeInfo::IsDrawHilighted() const    
	{ return m_bDrawHilighted; }
	inline BOOL            CPfxEditTypeInfo::IsEscape(WCHAR wc) const   
	{ return (wc == m_wEscape); }
	inline LPCTSTR         CPfxEditTypeInfo::GetDelimitersDefault()     
	{ return _T(",.?!;:/<>(){}[]\"\'"); }
	inline void            CPfxEditTypeInfo::SetMatchCase(BOOL bOn)     
	{ m_mapKeywords.SetMatchCase(bOn); }
	inline void            CPfxEditTypeInfo::SetDrawHilighted(BOOL bOn) 
	{ m_bDrawHilighted = bOn; }

	inline LONG            CPfxEditTypeInfo::GetKeywordCount() const 
	{ return m_mapKeywords.GetCount(); }
	inline void            CPfxEditTypeInfo::SetKeyword(LONG nKeyClass, LPCTSTR pszKeyword)
	{ m_mapKeywords.SetAt(nKeyClass, pszKeyword); }

	inline BOOL            CPfxEditTypeInfo::IsValidKeyClass(LONG nIndex) const
	{ return m_arrKeyClasses.IsValidClass(nIndex); }
	inline POSITION        CPfxEditTypeInfo::GetKeyClassFirst() const
	{ return m_arrKeyClasses.GetClassFirst(); }
	inline void            CPfxEditTypeInfo::GetKeyClassNext(POSITION& rPosition, CPfxEditKeyClass& theClass) const
	{ return m_arrKeyClasses.GetClassNext(rPosition, theClass); }
	inline LONG            CPfxEditTypeInfo::SetKeyClass(const CPfxEditKeyClass& theClass)
	{ return m_arrKeyClasses.SetClass(theClass); }
	inline void            CPfxEditTypeInfo::RemoveKeyClass(LONG nIndex)
	{ m_arrKeyClasses.RemoveClass(nIndex); }
	inline void            CPfxEditTypeInfo::RemoveKeyClass(LPCTSTR pszClassName)
	{ m_arrKeyClasses.RemoveClass(pszClassName); }
	inline COLORREF        CPfxEditTypeInfo::GetKeyClassColor(LONG nIndex) const
	{ ASSERT(IsValidKeyClass(nIndex)); return m_arrKeyClasses.GetClassColor(nIndex); }
	inline void            CPfxEditTypeInfo::SetKeyClassColor(LONG nIndex, COLORREF color)
	{ ASSERT(IsValidKeyClass(nIndex)); m_arrKeyClasses.SetClassColor(nIndex, color); }
	inline LPCTSTR         CPfxEditTypeInfo::GetKeyClassName(LONG nIndex) const
	{ ASSERT(IsValidKeyClass(nIndex)); return m_arrKeyClasses.GetClassName(nIndex); }
	inline void            CPfxEditTypeInfo::SetKeyClassName(LONG nIndex, LPCTSTR pszClassName)
	{ ASSERT(IsValidKeyClass(nIndex)); m_arrKeyClasses.SetClassName(nIndex, pszClassName); }

	inline BOOL            CPfxEditTypeInfo::HasMarkerPair(EPfxEditMarkerPair id) const
	{ return m_arrMarkerPair.GetMarker(id) != NULL; }
	inline CPfxEditMarkerPair* CPfxEditTypeInfo::GetMarkerPair(EPfxEditMarkerPair id) const
	{ return m_arrMarkerPair.GetMarker(id); }

	/////////////////////////////////////////////////////////////////////////////
	// CPfxEditPrintInfo �����ӡ��Ϣ��
	class CPfxEditPrintInfo
	{
	public:
		// ���β����Ƿ����ڴ�ӡԤ�����ο�����
		BOOL           m_bPreview;

		// �Ƿ��ӡ�﷨������ֻ�е���ǰ�ĵ��ǳ����ļ�����Ч��
		BOOL           m_bPrintHilighted;

		// �����кţ���ѡ���ã���
		BOOL           m_bPrintLineNumber;

		// ��ӡ����ָ��ߡ�
		BOOL           m_bPrintHeaderSeparator;

		// ��ӡ��ע�ָ��ߡ�
		BOOL           m_bPrintFooterSeparator;

		// ��ӡ������Ļ��ʾDC�������಻Ӧ�޸���������Ա�����ԡ�
		CDC*           m_pdcPrinter;
		CDC*           m_pdcDisplay;

		// ��ʾ���塣
		CFont*         m_pFontDisplay;

		// �Զ����У���ѡ���ã��μ�SetWrapStyle()����
		LONG           m_nWrapStyle;

		// ��ӡȫ����ֻ��ӡ����ҳ��ż��ҳ����ѡ���ã���
		LONG           m_nPrintRange;

		// �Ӹ�ҳ��ʼ��ӡ������һ���ο�ֵ������ֵ�ǴӴ�ӡ�Ի��򷵻صģ����
		// ���õ���ֵ��������Ч��Χ���ó�Ա���滻��Чֵ����ѡ���ã���
		LONG           m_nFromPage; 

		// ����ҳ����������һ���ο�ֵ������ֵ�ǴӴ�ӡ�Ի��򷵻صģ��������
		// ����ֵ���������ֵ���ó�Ա���滻�����ֵ����ѡ���ã���
		LONG           m_nToPage;

		// ҳü�����ĵľ��롣
		LONG           m_nSpacingHeaderAndText;

		// ҳ�������ĵľ��롣
		LONG           m_nSpacingFooterAndText;

		// ϵͳ����ʱ�䣨��ѡ���ã���
		SYSTEMTIME     m_time;

		// ��ӡֽ�ɴ�ӡ��Χ���߼���Ԫ���ο�����
		CRect          m_rectDraw;

		// �ı�����������λ���߼���Ԫ����ѡ���ã���
		CRect          m_rectMargin;

		// ��ӡ�ο����壬Ĭ�ϵ���������ʾ���壬������������µ�����ݱ�����
		// ��������ɾ��������Ϊ������Ļ��ʾ�õ����塣��������಻�޸�������
		// CPfxEditView ����ݴ�ӡDC����ʾDC֮��ı�����������ӡ���塣�����
		// �������Լ�������ݱ�����˸�����ݱ��������಻Ӧ�ñ�������壬��
		// ΪCPfxEditViewһ��ӡ��Ͼ�ɾ�������壨��ѡ���ã���
		CFont          m_fontText;

		// ����ͽ�ע���壬����NULLʱʹ�ô�ӡ���壬���������ָ���µ������
		// ����CPfxEditViewһ��ӡ��Ͼ�ɾ�������壨��ѡ���ã���
		CFont          m_fontHeaderAndFooter; 

		// ���ڻ���ˮƽ�ָ��ߣ�������NULL�򲻻��ơ�CPfxEditView һ��ӡ��Ͼ�
		// ɾ������Դ����ѡ���ã���
		CPen           m_penSeparateLine;

		// ���ڻ��Ʊ߿򣬽�����NULL�򲻻��ƣ�CPfxEditView һ��ӡ��Ͼ�ɾ����
		// ��Դ����ѡ���ã���
		CPen           m_penMargin;

		// �����ʽ���ַ�������ѡ���ã���
		CString        m_strHeader;

		// ��ע��ʽ���ַ�������ѡ���ã���
		CString        m_strFooter;

		// �ļ�������ѡ���ã���
		CString        m_strPathName;

		CPfxEditKeyClass m_arrKeyClasses[kcKeyClassArraySize];
		COLORREF       COLOR(LONG nIndex) const { return m_arrKeyClasses[nIndex].m_color; }

	public:
		// ��ӡDC����ʾDC�����ű���ϵ����
		FLOAT          m_fRatioX;
		FLOAT          m_fRatioY;

		// ��ӡ���ڵ�ǰ������ÿˮƽӢ��������߼���Ԫ����
		FLOAT          m_fLogUnitsPerInchX;

		// ��ӡ���ڵ�ǰ������ÿ��ֱӢ��������߼���Ԫ����
		FLOAT          m_fLogUnitsPerInchY;

		// ��ӡ���ڵ�ǰ������ÿˮƽCM�������߼���Ԫ����
		FLOAT          m_fLogUnitsPerCmX;

		// ��ӡ���ڵ�ǰ������ÿ��ֱCM�������߼���Ԫ����
		FLOAT          m_fLogUnitsPerCmY;

	public:
		CPfxEditPrintInfo();
		virtual        ~CPfxEditPrintInfo();

	public:
		BOOL           IsPreview() const;
		BOOL           IsPrintHilighted() const;
		BOOL           IsPrintHeader() const;
		BOOL           IsPrintFooter() const;
		BOOL           IsPrintMargin() const;
		BOOL           IsPrintLineNumber() const;
		BOOL           IsPrintHeaderSeparator() const;
		BOOL           IsPrintFooterSeparator() const;

		// ֱ��ʹ�����е�������Ϊ��ӡ���塣
		BOOL           SetPrinterFont(CFont* pFont);

		// ��ӳ����ʾ����ķ���������ӡ���塣
		BOOL           SetMapDisplayFont();

		void           SetDC(CDC* pdcDisplay, CDC* pdcPrinter);

		void           SetPrintPagesAll();
		void           SetPrintPagesEven();
		void           SetPrintPagesOdd();

		// ��ʾDC�߼���Ԫӳ��ɴ�ӡDC�߼���Ԫ��
		LONG           PrinterLogicUnitFromDisplayX(LONG x);
		LONG           PrinterLogicUnitFromDisplayY(LONG y);

		void           PrinterLogicUnitFromDisplay(CRect& rect);
		void           PrinterLogicUnitFromDisplay(CPoint& rpt);

		// ��Ӣ��ת�����߼���Ԫ��
		LONG           PrinterLogicUnitFromInchX(FLOAT fInch);
		LONG           PrinterLogicUnitFromInchY(FLOAT fInch);

		// ������ת�����߼���Ԫ��
		LONG           PrinterLogicUnitFromCmX(FLOAT fCM);
		LONG           PrinterLogicUnitFromCmY(FLOAT fCM);

		HGDIOBJ        FontText() const;
		HGDIOBJ        FontHeaderAndFooter() const;
		HGDIOBJ        PenSeparateLine() const;
		HGDIOBJ        PenMargin() const;

		CFont*         GetFontText() const;
		CFont*         GetFontHeaderAndFooter() const;
		CPen*          GetPenSeparateLine() const;
		CPen*          GetPenMargin() const;
	};

	inline BOOL            CPfxEditPrintInfo::IsPreview() const             { return m_bPreview; }
	inline BOOL            CPfxEditPrintInfo::IsPrintHilighted() const      { return m_bPrintHilighted; }
	inline BOOL            CPfxEditPrintInfo::IsPrintHeader() const         { return !m_strHeader.IsEmpty(); }
	inline BOOL            CPfxEditPrintInfo::IsPrintFooter() const         { return !m_strFooter.IsEmpty(); }
	inline BOOL            CPfxEditPrintInfo::IsPrintMargin() const         { return m_penMargin.GetSafeHandle() != NULL; }
	inline BOOL            CPfxEditPrintInfo::IsPrintLineNumber() const     { return m_bPrintLineNumber; }
	inline BOOL            CPfxEditPrintInfo::IsPrintHeaderSeparator()const { return m_bPrintHeaderSeparator; }
	inline BOOL            CPfxEditPrintInfo::IsPrintFooterSeparator()const { return m_bPrintFooterSeparator; }

	inline void            CPfxEditPrintInfo::SetPrintPagesAll()            { m_nPrintRange = PFX_EC_PRINT_PAGES_ALL; }
	inline void            CPfxEditPrintInfo::SetPrintPagesEven()           { m_nPrintRange = PFX_EC_PRINT_PAGES_EVEN; }
	inline void            CPfxEditPrintInfo::SetPrintPagesOdd()            { m_nPrintRange = PFX_EC_PRINT_PAGES_ODD; }

	inline CFont*          CPfxEditPrintInfo::GetFontText() const           { return const_cast<CFont*>(&m_fontText); }
	inline CFont*          CPfxEditPrintInfo::GetFontHeaderAndFooter()const { return const_cast<CFont*>(&m_fontHeaderAndFooter); }
	inline CPen*           CPfxEditPrintInfo::GetPenSeparateLine() const    { return const_cast<CPen*>(&m_penSeparateLine); }
	inline CPen*           CPfxEditPrintInfo::GetPenMargin() const          { return const_cast<CPen*>(&m_penMargin); }

	inline HGDIOBJ         CPfxEditPrintInfo::FontText() const              { return (HGDIOBJ)m_fontText; }
	inline HGDIOBJ         CPfxEditPrintInfo::FontHeaderAndFooter() const   { return (HGDIOBJ)m_fontHeaderAndFooter; }
	inline HGDIOBJ         CPfxEditPrintInfo::PenSeparateLine() const       { return (HGDIOBJ)m_penSeparateLine; }
	inline HGDIOBJ         CPfxEditPrintInfo::PenMargin() const             { return (HGDIOBJ)m_penMargin; }

#pragma warning (disable: 4244)
	inline LONG            CPfxEditPrintInfo::PrinterLogicUnitFromDisplayX(LONG x)   { ASSERT(m_fRatioX != 0); return (LONG)(m_fRatioX * x); }
	inline LONG            CPfxEditPrintInfo::PrinterLogicUnitFromDisplayY(LONG y)   { ASSERT(m_fRatioY != 0); return (LONG)(m_fRatioY * y); }
	inline LONG            CPfxEditPrintInfo::PrinterLogicUnitFromInchX(FLOAT fInch) { return (LONG)(fInch * m_fLogUnitsPerInchX); }
	inline LONG            CPfxEditPrintInfo::PrinterLogicUnitFromInchY(FLOAT fInch) { return (LONG)(fInch * m_fLogUnitsPerInchY); }
	inline LONG            CPfxEditPrintInfo::PrinterLogicUnitFromCmX(FLOAT fCM)     { return (LONG)(fCM * m_fLogUnitsPerCmX); }
	inline LONG            CPfxEditPrintInfo::PrinterLogicUnitFromCmY(FLOAT fCM)     { return (LONG)(fCM * m_fLogUnitsPerCmY); }
#pragma warning (default: 4244) 

	/////////////////////////////////////////////////////////////////////////////
	// CPfxEditData
	class CPfxEditData
	{
	public:
		CPfxEditData();
		~CPfxEditData();
	public:
		LONG           m_nCharWidthTab;        // �����ַ�TAB�ַ���ȡ�
		LONG           m_nCharWidthSpace;      // �����ַ��ո��ַ���ȡ�     
		LONG           m_nCharWidthLineBreak;  // �����ַ����⻻�з���ȡ�
		LONG           m_nCharWidthMaxNum;     // �����ַ�����������ַ���ȡ�
		LONG           m_nCharWidthAve;        // �����ַ�ƽ����ȡ�
		LONG           m_nCharWidthMax;        // �����ַ�����ȡ�
		LONG           m_nCharHeight;          // �����ַ��߶ȡ�

		LONG           m_nLineHeight;          // �и� = (m_nCharHeight + m_nSpacingLines)
		LONG           m_nSpacingLines;        // �м�ࡣ
		LONG           m_nSpacingLineNumberAndText; // �к������������ļ�ࡣ

		LONG           m_nRulerCharHeight;     // ����ַ��߶ȡ�
		LONG           m_nRulerCharWidthAve;   // ����ַ�ƽ����ȡ�
		LONG           m_nRulerHeight;         // ��߸߶ȡ�

		CSize          m_sizeCaret;            // ��ǰ������ųߴ硣

		// ����������ʶ�Ƿ����ʵʩ�п�ճ������������ڼ����嵱ǰ�ľݱ�����
		// ������ǰ������������CPfxEditView����ȥ�ģ����Խ����п�ճ��������
		// �Ͳ��У�����һ����Ҫɾ���þݱ���
		HGLOBAL        m_hDataClipboardCopied;
		DWORD          m_nDataClipboardCopied; // ���Ƶ�����������ݴ�С��

		// OLE�Ϸžݱ��ı�ʶ��������ʶ���ݶ���������š���CPfxEditView�ڣ�
		// ��ñ�ʶ����ָʾ�Ƿ�����п������
		HGLOBAL        m_hDataDragDropCopied;

		HFONT          m_hFontText;            // ������Դ��������ɾ����

		HCURSOR        m_hCurText;             // ���ڱ༭����
		HCURSOR        m_hCurLineNumber;       // �����кš�
		HCURSOR        m_hCurColSelect;        // ָʾ���Խ����п������
		HCURSOR        m_hCurStandard;         // ϵͳ��׼��ꡣ

		CPfxEditAlloc  m_alloc;
		CPfxEditHeap::CAllocator m_heap;
		CPfxEditTypeInfo m_defTypeInfo;

		DWORD          m_arrLeadByte[UCHAR_MAX]; // Ϊ�����ݶ�׼ʹ��DWORD��

	public:
		void*          MemAlloc(size_t cb) { return m_alloc.Alloc(cb); }
		void           MemFree(void* lp) { return m_alloc.Free(lp); }
	};
	extern CPfxEditData PFX_EC_DATA;

	/////////////////////////////////////////////////////////////////////////////
	// CPfxEditLineInfo
	class CPfxEditLineInfo
	{
	public:
		// �б�־��ָʾ�����Ƿ�����ǩ���Ƿ������еȡ�
		DWORD          dwFlags;

		// �����кš�
		LONG           nIndex;

		// �߼��С���������У��������㣬��������У������ڸ����е�һ���ַ�
		// ���������׵��߼�ƫ����������TAB��չ����
		LONG           nFirstChar;

		// �г��ȣ������������û������������nActLen��
		LONG           nLen;

		// ����������������У��������У��ĳ��ȣ�������������ǵ����е���ƫ
		// ������
		LONG           nActLen;

		// һ����ѡ���ı�����ʼ���յ�λ�ã�nSelTo���ܳ������г��ȣ�����ѡ��
		// ���ݰ������з���
		LONG           nSelFrom;
		LONG           nSelTo;

		// ָ�����ݵ�ָ�롣
		LPTSTR         pData;

		// �л��������ڵ��ڴ���ָ�롣
		// ע�⣺�������ڴ����ģ��ʹ�ã�����������㲻Ӧ��ʹ�á�
		LPVOID         pMemBlock;
	};

	/////////////////////////////////////////////////////////////////////////////
	// CPfxEditUndoInfo
	class CPfxEditUndoInfo
	{
	public:
		// �������͡�
		WORD           fAction;

		// �������ơ�
		WORD           fUndoName;

		// X���ڴ��������׼�����ַ�ƫ������Y���ھ����кš�
		POINT          ptFrom;
		POINT          ptTo;

		// �������ĳ��ȡ�
		LONG           nLen;

		// ����ǲ�����������ǻ�������ָ�룬����Ӧ��ΪNULL��
		LPTSTR         pData;

		// ����ǲ�����������ǻ����������ڴ���ָ�룬����Ӧ��ΪNULL��
		// ע�⣺�������ڴ����ģ��ʹ�ã�����������㲻Ӧ��ʹ�á�
		LPVOID         pMemBlock;
	};

	/////////////////////////////////////////////////////////////////////////////
	// CPfxEditDoc
	class CPfxEditDoc : public CDocument
	{
	protected:
		struct CPfxEditDocMemBlock
		{
			// �ж���TCHAR�ռ䱻������
			LONG           nUnused;

			// �������Ŀռ�ﵽ�����Ŀʱ��Ҫִ��ѹ��������
			LONG           nMaxUnused;

			// ʣ�����TCHAR�ռ���á�
			LONG           nRemain;

			// ���ڴ���ܵĳ���
			LONG           nLength;

			// ʣ��Ŀ��ÿռ�ָ�롣
			LPTSTR         pRemain;

			// �������һ�顣
			CPfxEditDocMemBlock* pNext;

			// �������һ�顣
			CPfxEditDocMemBlock* pPrev;
		};

		struct CPfxEditDocLineInfo
		{
			// �����鵥Ԫ����
			LONG           nli;

			// ������ʣ����õĵ�Ԫ����
			LONG           nliRemain;

			// ���Ҫ��������Ϣ����ĳ��ȣ�ÿ��Ӧ�����ӵ���Ŀ��
			LONG           nliGrowBy;

			// ����������ָ�롣
			CPfxEditLineInfo*    pli;

			// �ڴ��ָ�롣
			CPfxEditDocMemBlock* pmb;
		};

		struct CPfxEditDocUndoInfo
		{
			// ��ǰ���õĵ�Ԫ����
			LONG           nui;

			// ��ǰʣ��ĵ�Ԫ����
			LONG           nuiRemain;

			// ÿ�����ӵĻ��������ȡ�
			LONG           nuiGrowBy;

			// ���UNDO������
			LONG           nuiMax;

			// ��ǰUNDOλ�á�
			LONG           nPosCur;

			// ���Ϊ�ĵ�δ�޸�״̬��UNDOλ�á�
			LONG           nPosUnmodified;

			// UNDO���ơ�
			WORD           nGroupName;

			// ����������
			BYTE           nGroupLockCount;

			// �Ƿ���һUNDO��ĵ�һ����¼��
			BOOL           bGroupBegin;

			// UNDO������ָ�롣
			CPfxEditUndoInfo*    pui;

			// �ڴ��ָ�롣
			CPfxEditDocMemBlock* pmb;
		};

		class CPfxEditDocFile
		{
			HANDLE         m_hMapping;
			LONG           m_nMappingSize;
			LPVOID         m_pMappingAddress;
		public:
			CPfxEditDocFile();
			~CPfxEditDocFile();

		public:
			BOOL           MapFile(HANDLE hFile, LONG nSize);
			BOOL           MapMemory(LONG nSize) { return MapFile((HANDLE)0xFFFFFFFF, nSize); }

			LONG           GetSize() const       { return m_nMappingSize; }
			LPVOID         GetBuffer() const     { return m_pMappingAddress; }
			void           SetSize(LONG nSize)   { if ((nSize >= 0) && (nSize < m_nMappingSize)) { m_nMappingSize = nSize; }}
			void           Close();

			BOOL LoadString(const CString &strText);
			BOOL WriteString(CString &strText);
		};

		class CPfxEditDocUtf8Converter
		{
		public:
			// �������Ļ������Ƿ�����ȷ��UTF8�������ݡ�
			BOOL           IsUtf8FromUnicode(LPCSTR pUtf8, LONG cch) const;

			// ��ȡ������UTF8�ַ����ȡ�
			LONG           Utf8CharSize(BYTE b) const
			{
				// �����ֽڴ�������ʾһ���ַ�. �õ��ĸ���ȡ���ڸ��ַ��� Unicode �е����. 
				// U+00000000-U+0000007F: 0xxxxxxx 
				// U+00000080-U+000007FF: 110xxxxx 10xxxxxx 
				// U+00000800-U+0000FFFF: 1110xxxx 10xxxxxx 10xxxxxx 
				// U+00010000-U+001FFFFF: 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx 
				// U+00200000-U+03FFFFFF: 111110xx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 
				// U+04000000-U+7FFFFFFF: 1111110x 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx

				// U+00000000-U+0000007F: 0xxx-xxxx 
				// 0000-0000->0111-1111 = 0x00->0x7F
				if (b <= 0x7F)
				{
					return 1;
				}
				// U+00000080-U+000007FF: 110x-xxxx
				// 1100-0000->1101-1111 = 0xC0->0xDF
				else if ((b >= 0xC0) && (b <= 0xDF))
				{
					return 2;
				}
				// U+00000800-U+0000FFFF: 1110-xxxx
				// 1110-0000->1110-1111 = 0xE0->0xEF
				else if ((b >= 0xE0) && (b <= 0xEF))
				{
					return 3;
				}
				else // ��֧��UCS4���룡
				{
					return 0;
				}
			}

			// ��UTF8�ַ�ת��ΪUNICODEʱ����Ļ��������ȣ���λ���ַ�����
			LONG           Utf8ToUnicodeCharSize(BYTE b) const
			{
				UNUSED(b);
				return 1; // ��֧��UCS4��
			}

			// ��UTF8�ַ�ת��ΪUNICODE�ַ����߼�����Ҫ���������������
			LONG           Utf8ToUnicode(LPCSTR pUtf8, LONG cchUtf8, LPWSTR pUnicode, LONG cchUnicode) const;

			// ��UNICODE�ַ�ת��ΪUTF8�ַ�����Ļ��������ȣ���λ���ֽڣ���
			LONG           UnicodeToUtf8CharSize(WORD w) const
			{
				// �����ֽڴ�������ʾһ���ַ�. �õ��ĸ���ȡ���ڸ��ַ��� Unicode �е����. 
				// U+00000000-U+0000007F: 0xxxxxxx 
				// U+00000080-U+000007FF: 110xxxxx 10xxxxxx 
				// U+00000800-U+0000FFFF: 1110xxxx 10xxxxxx 10xxxxxx 
				// U+00010000-U+001FFFFF: 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx 
				// U+00200000-U+03FFFFFF: 111110xx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 
				// U+04000000-U+7FFFFFFF: 1111110x 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
				if (w < 0x0080)
				{
					return 1; // ANSI CHAR
				}

				if (w < 0x0800)
				{
					return 2;
				}
				else
				{
					return 3;
				}
			}

			// ��UNICODE�ַ�ת��ΪUTF8�ַ����߼�����Ҫ���������������
			LONG           UnicodeToUtf8(LPCWSTR pUnicode, LONG cchUnicode, LPSTR pUtf8, LONG cchUtf8) const;
		};

		/////////////////////////////////////////////////////////////////////
		DECLARE_DYNCREATE(CPfxEditDoc)
	protected:
		CPfxEditDoc();           // protected constructor used by dynamic creation

		// Attributes
	public:
		BOOL           IsCanUndo() const;
		BOOL           IsCanRedo() const;
		BOOL           IsCanReload() const;
		BOOL           IsReadOnly() const;

		BOOL           IsValidLine(LONG nLine) const;
		BOOL           IsValidChar(LONG nLine, LONG nChar) const;

	public:
		LONG           GetValidLine(LONG nLine) const;
		LONG           GetValidChar(LONG nLine, LONG nChar) const;

		LONG           GetOpenConverter() const;
		LONG           GetFileConverter() const;

		LONG           GetLineBreakSize() const;
		LONG           GetLineBreakType() const;

		LONG           GetBookmarkCount() const;
		LONG           GetDocSize() const;
		LONG           GetLineCount() const;
		LONG           GetLineUpperBound() const;

		LONG           GetLineLength(LONG nLine) const;
		LONG           GetLineData(LONG nLine, LPTSTR pBuffer, LONG nBufMax) const;

		LONG           GetUndoName() const;
		LONG           GetRedoName() const;

		// Operations
	public:
		void           SetReadOnly(BOOL bOn);
		void           SetLineBreakType(LONG nType);

		void           SetFileConverter(LONG nConverter);
		void           SetOpenConverter(LONG nConverter);

		BOOL           SetTypeInfoPtr(CPfxEditTypeInfo* pTypeInfo);
		const          CPfxEditTypeInfo* GetTypeInfoPtr() const;

		BOOL           Reload();
		void           UpdateAllViews(BOOL bRecalcWrap);

		// Overrides
	protected:
		// ClassWizard generated virtual function overrides
		//{{AFX_VIRTUAL(CPfxEditDoc)
	public:
		virtual void   Serialize(CArchive& ar); // overridden for document i/o
		virtual void   DeleteContents();
		virtual void   SetModifiedFlag(BOOL bModified);
		virtual void   OnChangedViewList();
		virtual void   OnChangedViewList(PfxEditViewPRentClass *pView);
		virtual BOOL   OnNewDocument();
		virtual BOOL   OnOpenDocument(LPCTSTR pszPathName);
		virtual BOOL   OnSaveDocument(LPCTSTR pszPathName);

		virtual BOOL   OnOpenDocFromString(const CString &strText);
		virtual BOOL   OnSaveDocToString(CString &strText);

		//}}AFX_VIRTUAL

		// �༭�ؼ��ͣ������ࣩʹ���߽����¼�������Ϣ��
		// UINT nCode    - ��ο�PFX_EN_XX��Ϣ
		// LPARAM lParam - ���nCode��Ϣ��صĸ��Ӳ�����
		virtual LONG   OnEvent(UINT nCode, LPARAM lParam);

		// ������﷨�����༭�����Ը����ļ�����װ���﷨��ص����õȡ�
		virtual BOOL   OnInitDocument(LPCTSTR pszPathName);

		// Implementation
	public:
		virtual        ~CPfxEditDoc();

#ifdef _DEBUG
		virtual void   AssertValid() const;
		virtual void   Dump(CDumpContext& dc) const;
#endif

	protected:
		BOOL           m_bDrawRuler;       // �Ƿ���ʾ��ߡ�
		BOOL           m_bDrawLineNumber;  // �Ƿ���ʾ�кš�
		BOOL           m_bDrawWhitespace;  // �Ƿ���ʾ�հ��ַ���
		BOOL           m_bDrawLineBreak;   // �Ƿ���ƻ��з���
		BOOL           m_bReadOnly;        // �ĵ��Ƿ�Ϊֻ����

		// �������������л����UNDO���������Ƿ��Ѿ���������������ִ��ѹ����
		// �����������������һ���������У����硰ȫ���滻�������������һ��
		// �ϴ����������Ƶ����ִ�л�����ѹ�����ض��ᵼ���ٶȺ���������ѹ��
		// �����������Ժ���С�
		BOOL           m_bLockedBufferCompact;

		// ��ֹ���н�����Ϣ���ݸ�OnEvent()��
		BOOL           m_bLockedWordWrapEvent;

		LONG           m_nLineLastParsed;  // �﷨����ʱ���һ���ѷ������С�

		// �﷨����ʱ���һ�ѷ����е����б��½��ı༭������������
		LONG           m_nLineLastParsedButCanceled;

		LONG           m_nWrapStyle;       // ���з�����
		LONG           m_nWrapWidth;       // ���п�ȡ�

		LONG           m_nLineBreakSize;   // ���з��ĳ��ȣ���λ��TCHAR��
		LONG           m_nLineBreakType;   // ���з�������DOS��Mac��Unix����ʵ���ĵ������͡�

		LONG           m_nOpenConverter;   // ��ʱ�ļ�ת������
		LONG           m_nSaveConverter;   // ����ʱ�ļ�ת������

		// �ĵ�������
		LONG           m_nBookmarks;       // �ĵ��е�ǰ����ǩ����
		LONG           m_nDocLineCount;    // ����������
		LONG           m_nDocSize;         // �ĵ���ǰ��С����λ��TCHAR��

		CRect          m_rectIndent;       // �ı���������������Ŀǰ������left��top��

	protected:
		// ���ֻ����������ͼ�����ҽ�����������ͼ�Ĳ���������һ�С�֮���Խ�
		// ��ʹ�����ֲ��֣�����Ϊ�漰���ı��������⣬ʹ��һ�����л���������
		// �������ì�ܡ�
		// |======================|
		// |                      |
		// | ��ͼ1                |
		// |                      |
		// |======================|
		// |                      |
		// | ��ͼ2                |
		// |                      |
		// |======================|
		CPfxEditView*       m_arrViews[2];
		CPfxEditDocLineInfo m_clsLine;
		CPfxEditDocUndoInfo m_clsUndo;

	protected:
		BOOL           IsDrawRuler() const;
		BOOL           IsDrawLineNumber() const;

		BOOL           IsDrawLineBreak() const;
		BOOL           IsDrawWhitespace() const;

		BOOL           IsWrapping() const;
		BOOL           IsWrapAtWindowEdge() const;
		BOOL           IsWrapAfterColumns() const;

		LONG           GetWrapStyle() const;
		LONG           GetWrapWidth() const;

		LONG           GetLineBreakSizeFromTypeA(LONG nType) const;
		LPCSTR         GetLineBreakDataFromTypeA(LONG nType) const;

		LONG           GetLineBreakSizeFromTypeW(LONG nType) const;
		LPCWSTR        GetLineBreakDataFromTypeW(LONG nType) const;

#ifndef _UNICODE
#define GetLineBreakSizeFromType GetLineBreakSizeFromTypeA
#define GetLineBreakDataFromType GetLineBreakDataFromTypeA
#else
#define GetLineBreakSizeFromType GetLineBreakSizeFromTypeW
#define GetLineBreakDataFromType GetLineBreakDataFromTypeW
#endif

	protected: 
		// �¼�֪ͨ��Ϣ...
		LONG           EventSendMsg(UINT nCode, LPARAM lParam);

		// ���쳣����ת���ɴ�����롣
		DWORD          EventCodeFromException(CException* e) const;

	protected: // �ı���Ϣ����...
		BOOL           TextIsSOL(const CPoint& rpt) const;
		BOOL           TextIsEOL(const CPoint& rpt) const;
		BOOL           TextIsSOF(const CPoint& rpt) const;
		BOOL           TextIsEOF(const CPoint& rpt) const;
		BOOL           TextIsFirstLine(LONG nLine) const;
		BOOL           TextIsLastLine(LONG nLine) const;
		BOOL           TextIsValidLine(LONG nLine) const;
		BOOL           TextIsValidChar(LONG nLine, LONG nChar) const;

		LONG           TextVerifyLine(LONG nLine) const;
		LONG           TextVerifyChar(LONG nLine, LONG nChar) const;

		CPfxEditLineInfo* TextGetLineAt(LONG nIndex) const;
		LONG           TextGetLineLength(LONG nLine) const;
		LPTSTR         TextGetLineData(LONG nLine) const;
		DWORD          TextGetLineCookies(LONG nLine) const;
		LONG           TextGetLineSubLines(LONG nLine) const;
		LONG           TextGetLineCount() const;
		LONG           TextGetLineUpperBound() const;
		LONG           TextGetBlockSize(const CPoint& rptFrom, const CPoint& rptTo, LONG nLineBreakType);
		LONG           TextGetBlockData(const CPoint& rptFrom, const CPoint& rptTo, LPTSTR pBuffer, LONG nBufMax, LONG nLineBreakType);

		LONG           TextGetThisMainLine(LONG nLine) const;
		LONG           TextGetPrevMainLine(LONG nLine) const;
		LONG           TextGetNextMainLine(LONG nLine) const;

		// �ı�����ת��...
		void           TextAbsLineToSubLine(CPoint& rpt) const;
		void           TextAbsLineToMainLine(CPoint& rpt) const;
		LONG           TextAbsLineToOffset(const CPoint& rpt) const;

		void           TextMainLineToAbsLine(CPoint& rpt) const;
		void           TextMainLineToSubLine(CPoint& rpt) const;
		LONG           TextMainLineToOffset(const CPoint& rpt) const;

		void           TextSubLineToAbsLine(CPoint& rpt) const;
		void           TextSubLineToMainLine(CPoint& rpt) const;
		LONG           TextSubLineToOffset(const CPoint& rpt) const;

		void           TextOffsetToAbsLine(LONG nOffset, CPoint& rpt) const;
		void           TextOffsetToSubLine(LONG nOffset, CPoint& rpt) const;
		void           TextOffsetToMainLine(LONG nOffset, CPoint& rpt) const;

		// ����PfxEditCtrlΨһ�����ݲ����ɾ��������
		void           TextInsertChars(CPoint& rpt, LPCTSTR pData, LONG cch, CPfxEditView* pView);
		void           TextRemoveChars(CPoint& rptFrom, CPoint& rptTo, CPfxEditView* pView);

	protected:
		CPfxEditLineInfo* TextInsertLine(LONG nIndex, LONG nCount = 1);
		void           TextInsertLine(LONG nIndex, LPCTSTR pLine, LONG nLen, DWORD dwFlags);

		void           TextRemoveLine(LONG nIndex, LONG nCount = 1);
		void           TextRemoveLine(LONG nIndex);

		void           TextUpdateDocSize(LONG cchChanged);
		void           TextUpdateLineIndex(LONG nFromLine, LONG nBaseIndex);
		void           TextUpdateLineInfo(CPfxEditLineInfo* pliHead, LONG nFirstModifiedLine, LONG nModifiedLines, LONG nAdjustedLines, CPoint& rptCurPos);

		void           TextGetBuffer(CPfxEditLineInfo* pli, LONG nNewLen);
		void           TextConstructEmptyLineInfo(CPfxEditLineInfo* pli, LONG nCount = 1) const;

	protected: // �����ָ�����...
		void           UndoRemove(CPfxEditUndoInfo* pui, CPoint& rptRetPos, BOOL bRedo);
		void           UndoInsert(CPfxEditUndoInfo* pui, CPoint& rptRetPos, BOOL bRedo);

		void           UndoAddInsert(CPoint ptFrom, CPoint ptTo);
		void           UndoAddRemove(CPoint ptFrom, CPoint ptTo);

		void           UndoSetGroup(BOOL bBegin, WORD fUndoName);
		void           UndoSetUnmodified();

		void           UndoGetBuffer(CPfxEditUndoInfo* pui, LONG nLen);
		WORD           UndoGetFlags(WORD wDefaultFlags);

		LONG           UndoGetCount() const;
		LONG           UndoGetRedoCount() const;

		CPfxEditUndoInfo* UndoAddRecord();
		CPfxEditUndoInfo* UndoGetInfo() const;
		CPfxEditUndoInfo* UndoGetRedoInfo() const;

	protected: // �ֲ�����ع���...
		void           BufferLineCleanup();
		void           BufferLineGetSpace(LONG nLen, TCHAR** ppBuffer, CPfxEditDocMemBlock** ppMemBlock);
		void           BufferLineCompact(CPfxEditDocMemBlock* pCurMemBlock, LONG nNewUnused);
		void           BufferLineRemoveBlock(CPfxEditDocMemBlock* pMemBlock);
		CPfxEditDocMemBlock* BufferLineAllocBlock(LONG nBlockSize);

		void           BufferUndoCleanup();
		void           BufferUndoGetSpace(LONG nLen, TCHAR** ppBuffer, CPfxEditDocMemBlock** ppMemBlock);
		void           BufferUndoCompact(CPfxEditDocMemBlock* pCurMemBlock, LONG nNewUnused);
		void           BufferUndoRemoveBlock(CPfxEditDocMemBlock* pMemBlock);
		CPfxEditDocMemBlock* BufferUndoAllocBlock(LONG nBlockSize);

	protected: // ����װ�غͱ���...
		BOOL           FileIsAnsi(LPCSTR pData, LONG cch) const;
		BOOL           FileIsUtf8(LPCSTR pData, LONG cch) const;
		BOOL           FileIsUnicode(LPCSTR pData, LONG cch) const;
		BOOL           FileIsUnicodeBigEndian(LPCSTR pData, LONG cch) const;
		LONG           FileGetConverterType(LPCSTR pData, LONG cch) const;

		void           FileLoadAnsi(CPfxEditDocFile& file); // throw (CMemoryException)
		void           FileLoadUtf8(CPfxEditDocFile& file); // throw (CMemoryException)
		void           FileLoadUnicode(CPfxEditDocFile& file); // throw (CMemoryException)
		void           FileLoadUnicodeBigEndian(CPfxEditDocFile& file); // throw (CMemoryException)

		void           FileSaveAnsi(CArchive& ar); // throw (CMemoryException)
		void           FileSaveUtf8(CArchive& ar); // throw (CMemoryException)
		void           FileSaveUnicode(CArchive& ar); // throw (CMemoryException)
		void           FileSaveUnicodeBigEndian(CArchive& ar); // throw (CMemoryException)

	protected:
		void           SetLockBufferCompact(BOOL bOn);
		void           SetLockWordWrapEvent(BOOL bOn);

		BOOL           IsLockedBufferCompact() const;
		BOOL           IsLockedWordWrapEvent() const;

		// Generated message map functions
	protected:
		//{{AFX_MSG(CPfxEditDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//}}AFX_MSG
		DECLARE_MESSAGE_MAP()
		friend class   CPfxEditView;
	};

	/////////////////////////////////////////////////////////////////////////////
	inline BOOL            CPfxEditDoc::TextIsSOL(const CPoint& rpt) const { ASSERT(TextIsValidLine(rpt.y)); return (rpt.x == 0); }
	inline BOOL            CPfxEditDoc::TextIsEOL(const CPoint& rpt) const { ASSERT(TextIsValidLine(rpt.y)); return (rpt.x >= TextGetLineAt(rpt.y)->nLen); }
	inline BOOL            CPfxEditDoc::TextIsSOF(const CPoint& rpt) const { ASSERT(TextIsValidLine(rpt.y)); return ((rpt.y == 0) && (rpt.x == 0)); }
	inline BOOL            CPfxEditDoc::TextIsEOF(const CPoint& rpt) const { ASSERT(TextIsValidLine(rpt.y)); return ((rpt.y == TextGetLineUpperBound()) && (rpt.x == TextGetLineAt(rpt.y)->nLen)); }

	inline BOOL            CPfxEditDoc::TextIsValidLine(LONG nLine) const  { ASSERT(TextGetLineCount() > 0); return ((nLine >= 0) && (nLine < TextGetLineCount())); }
	inline BOOL            CPfxEditDoc::TextIsValidChar(LONG nLine, LONG nChar) const { ASSERT(TextIsValidLine(nLine)); return ((nChar >= 0) && (nChar <= TextGetLineAt(nLine)->nLen)); }
	inline BOOL            CPfxEditDoc::TextIsFirstLine(LONG nLine) const  { ASSERT(TextIsValidLine(nLine)); return (nLine == 0); }
	inline BOOL            CPfxEditDoc::TextIsLastLine(LONG nLine) const   { ASSERT(TextIsValidLine(nLine)); return (nLine >= TextGetLineUpperBound()); }

	inline LONG            CPfxEditDoc::TextGetLineCount() const           { return m_clsLine.nli; }
	inline LONG            CPfxEditDoc::TextGetLineUpperBound() const      { return m_clsLine.nli - 1; }
	inline LONG            CPfxEditDoc::TextGetLineLength(LONG nLine) const{ ASSERT(TextIsValidLine(nLine)); return TextGetLineAt(nLine)->nLen; }
	inline LPTSTR          CPfxEditDoc::TextGetLineData(LONG nLine) const  { ASSERT(TextIsValidLine(nLine)); return TextGetLineAt(nLine)->pData; }
	inline DWORD           CPfxEditDoc::TextGetLineCookies(LONG nLine) const { ASSERT(TextIsValidLine(nLine)); return TextGetLineAt(nLine)->dwFlags; }
	inline CPfxEditLineInfo* CPfxEditDoc::TextGetLineAt(LONG nIndex) const 
	{ 
		//ASSERT(nIndex >= 0 && nIndex < m_clsLine.nli); 

		if (nIndex >= 0 && nIndex < m_clsLine.nli)
		{
			return &m_clsLine.pli[nIndex]; 
		}
		else
		{
			return NULL;
		}
	}

	inline LONG            CPfxEditDoc::UndoGetCount() const               { return m_clsUndo.nPosCur; }
	inline LONG            CPfxEditDoc::UndoGetRedoCount() const           { return (m_clsUndo.nui - m_clsUndo.nPosCur); }
	inline void            CPfxEditDoc::UndoSetUnmodified()                { m_clsUndo.nPosUnmodified = m_clsUndo.nPosCur; }

	inline BOOL            CPfxEditDoc::IsWrapping() const                 { return (m_nWrapStyle != PFX_EC_WRAP_NONE); }
	inline BOOL            CPfxEditDoc::IsWrapAtWindowEdge() const         { return (m_nWrapStyle == PFX_EC_WRAP_WINDOWEDGE); }
	inline BOOL            CPfxEditDoc::IsWrapAfterColumns() const         { return (m_nWrapStyle == PFX_EC_WRAP_COLUMNS); }

	inline BOOL            CPfxEditDoc::IsDrawLineBreak() const            { return m_bDrawLineBreak; }
	inline BOOL            CPfxEditDoc::IsDrawWhitespace() const           { return m_bDrawWhitespace; }
	inline BOOL            CPfxEditDoc::IsDrawRuler() const                { return m_bDrawRuler; }
	inline BOOL            CPfxEditDoc::IsDrawLineNumber() const           { return m_bDrawLineNumber; }

	inline BOOL            CPfxEditDoc::IsCanUndo() const                  { return !IsReadOnly() && (UndoGetCount() > 0); }
	inline BOOL            CPfxEditDoc::IsCanRedo() const                  { return !IsReadOnly() && (UndoGetRedoCount() > 0); }
	inline BOOL            CPfxEditDoc::IsCanReload() const                { return !GetPathName().IsEmpty(); }

	inline BOOL            CPfxEditDoc::IsReadOnly() const                 { return m_bReadOnly; }

	inline BOOL            CPfxEditDoc::IsLockedBufferCompact() const      { return m_bLockedBufferCompact; }
	inline BOOL            CPfxEditDoc::IsLockedWordWrapEvent() const      { return m_bLockedWordWrapEvent; }

	inline LONG            CPfxEditDoc::GetWrapStyle() const               { return m_nWrapStyle; }
	inline LONG            CPfxEditDoc::GetWrapWidth() const               { return m_nWrapWidth; }
	inline LONG            CPfxEditDoc::GetLineBreakSize() const           { return m_nLineBreakSize; }
	inline LONG            CPfxEditDoc::GetLineBreakType() const           { return m_nLineBreakType; }
	inline LONG            CPfxEditDoc::GetOpenConverter() const           { return m_nOpenConverter; }
	inline LONG            CPfxEditDoc::GetFileConverter() const           { return m_nSaveConverter; }

	inline LONG            CPfxEditDoc::GetBookmarkCount() const           { return m_nBookmarks; }
	inline LONG            CPfxEditDoc::GetDocSize() const                 { return m_nDocSize; }
	inline LONG            CPfxEditDoc::GetLineCount() const               { return m_nDocLineCount; }
	inline LONG            CPfxEditDoc::GetLineUpperBound() const          { return m_nDocLineCount - 1; }

	inline void            CPfxEditDoc::SetLockBufferCompact(BOOL bOn)     { m_bLockedBufferCompact = bOn; }
	inline void            CPfxEditDoc::SetLockWordWrapEvent(BOOL bOn)     { m_bLockedWordWrapEvent = bOn; }

	inline void            CPfxEditDoc::SetReadOnly(BOOL bOn)              { m_bReadOnly = bOn; }
	inline void            CPfxEditDoc::SetOpenConverter(LONG nConverter)
	{
		ASSERT((nConverter == PFX_EC_FILE_CONVERTER_AUTO_DETECT)
			|| (nConverter == PFX_EC_FILE_CONVERTER_ANSI)
			|| (nConverter == PFX_EC_FILE_CONVERTER_UTF8)
			|| (nConverter == PFX_EC_FILE_CONVERTER_UNICODE)
			|| (nConverter == PFX_EC_FILE_CONVERTER_UNICODE_BIG_ENDIAN));
		m_nOpenConverter = nConverter;
	}

	inline void            CPfxEditDoc::SetFileConverter(LONG nConverter)
	{
		ASSERT((nConverter == PFX_EC_FILE_CONVERTER_ANSI)
			|| (nConverter == PFX_EC_FILE_CONVERTER_UTF8)
			|| (nConverter == PFX_EC_FILE_CONVERTER_UNICODE)
			|| (nConverter == PFX_EC_FILE_CONVERTER_UNICODE_BIG_ENDIAN));
		m_nSaveConverter = nConverter;
	}
	/////////////////////////////////////////////////////////////////////////////
	// CPfxEditView
	/////////////////////////////////////////////////////////////////////////////
	// �������ڲ�ʹ�õķ��Ŷ��塣
	const TCHAR PFX_EC_CHR_CR                     = ('\r');
	const TCHAR PFX_EC_CHR_LF                     = ('\n');
	const TCHAR PFX_EC_CHR_TAB                    = ('\t');
	const TCHAR PFX_EC_CHR_SPACE                  = (VK_SPACE);

	/////////////////////////////////////////////////////////////////////////////
	const LONG PFX_EC_INVALID_LINE                = -1;
	const LONG PFX_EC_INVALID_CHAR                = -1;
	const LONG PFX_EC_INVALID_SELECT              = -1;

	/////////////////////////////////////////////////////////////////////////////
	// λ��ת����־(HT Hit Test)
	const LONG PFX_EC_HT_ERROR                    = 0;
	const LONG PFX_EC_HT_RULER                    = 1;
	const LONG PFX_EC_HT_LINE_NUMBER              = 2;
	const LONG PFX_EC_HT_TEXT                     = 3;

	/////////////////////////////////////////////////////////////////////////////
	// ѡ��ģʽ(SM Selection Mode)
	const LONG PFX_EC_SM_NORMAL                   = 0;
	const LONG PFX_EC_SM_WORD                     = 1;
	const LONG PFX_EC_SM_COLUMN                   = 2;

	/////////////////////////////////////////////////////////////////////////////
	// ���±�־(UT Update Type)
	const DWORD PFX_EC_UT_LINES                   = 0x00000001L; // ����ˢ��ָ�����С�
	const DWORD PFX_EC_UT_LAYOUT                  = 0x00000002L; // �������²��֡�
	const DWORD PFX_EC_UT_HORZ                    = 0x00000004L; // ˢ��ָ�����к����¼���ˮƽ��������
	const DWORD PFX_EC_UT_VERT                    = 0x00000008L; // ˢ��ָ�����к����¼��㴹ֱ��������
	const DWORD PFX_EC_UT_ALL                     = 0x00000010L; // ��Ҫ���¼��㲼�ֺ�ȫ��ˢ�¡�

	/////////////////////////////////////////////////////////////////////////////
	// ����/�ָ�����(UF Undo Flags)
	const WORD  PFX_EC_UF_UNKNOWN                 = 0x0000;
	const WORD  PFX_EC_UF_BEGIN_GROUP             = 0x0001;
	const WORD  PFX_EC_UF_GROUP                   = 0x0002;
	const WORD  PFX_EC_UF_INSERT                  = 0x0004;
	const WORD  PFX_EC_UF_REMOVE                  = 0x0008;

	/////////////////////////////////////////////////////////////////////////////
	// �б�־(LF Line Flags)
	const DWORD PFX_EC_LF_NONE                    = 0x00000000L;
	const DWORD PFX_EC_LF_SUBLINE                 = 0x00010000L;
	const DWORD PFX_EC_LF_HARDRETURN              = 0x00020000L;
	const DWORD PFX_EC_LF_BOOKMARK                = 0x00040000L;

	const DWORD PFX_EC_LF_COOKIE_NONE             = 0x00000000L;
	const DWORD PFX_EC_LF_COOKIE_QUOTED_STRING1   = 0x01000000L;
	const DWORD PFX_EC_LF_COOKIE_QUOTED_STRING2   = 0x02000000L;
	const DWORD PFX_EC_LF_COOKIE_LINE_COMMENT1    = 0x04000000L;
	const DWORD PFX_EC_LF_COOKIE_LINE_COMMENT2    = 0x08000000L;
	const DWORD PFX_EC_LF_COOKIE_BLOCK_COMMENT1   = 0x10000000L;
	const DWORD PFX_EC_LF_COOKIE_BLOCK_COMMENT2   = 0x20000000L;
	const DWORD PFX_EC_LF_COOKIE_ALL              = 0x3F000000L;

	/////////////////////////////////////////////////////////////////////////////
#define PFX_EC_IS_EMPTY_LINE(pli)             (NULL == pli->pData)
#define PFX_EC_IS_EMPTY_UNDO(pui)             (NULL == pui->pData)
#define PFX_EC_IS_SUBLINE(pli)                (pli->dwFlags & PFX_EC_LF_SUBLINE)
#define PFX_EC_IS_DRAW_BOOKMARK(pli)          (pli->dwFlags & PFX_EC_LF_BOOKMARK)
#define PFX_EC_IS_DRAW_HARDRETURN(pli)        (pli->dwFlags & PFX_EC_LF_HARDRETURN)
#define PFX_EC_IS_KEY_DOWN(k)                 (::GetKeyState(k) & 0x8000)

#ifdef _MBCS
#define PFX_EC_IS_LEAD_BYTE(c)                (PFX_EC_DATA.m_arrLeadByte[static_cast<BYTE>(c)])
#else
#define PFX_EC_IS_LEAD_BYTE(c)                (false)
#endif

	/////////////////////////////////////////////////////////////////////////////


	class CPfxEditView : public PfxEditViewPRentClass
	{
	protected:
		class CPfxEditViewFindReplace
		{
		public:
			// ƥ���Сд��
			BOOL           bMatchCase;

			// ƥ�������ַ�����
			BOOL           bMatchWholeWord;

			// ƥ�������ʽ��
			BOOL           bRegExp;

			// ������ʹ�ã�����������
			BOOL           bDirectDown;

			// ������ʹ�ã��ҵ��ĵ���ͷʱ�Ƿ���ơ�
			BOOL           bWrapAtEndOfFile;

			// ������ʹ�ã�ȫ����ǣ�ִ�иò����������ָ��λ�ô��ĵ���ʼ������
			// ��β�������ҵ����б�ǣ��������ڲ��Ҳ����ĳ�Ա��
			BOOL           bMarkAll;

			// ���滻ʹ�ã��Ƿ���ѡ��Χ���滻�����������滻�����ĳ�Ա�������
			// ��Ա����ΪTRUE�������ptFrom��ptTo������Χ��ѡ��Χ�ڣ������ǰ
			// û��ѡ��Χ�����ʧ�ܡ�
			BOOL           bInSelection;

			// ���滻ʹ�ã��Ƿ���Բ��Ҷ���ptFrom��ptTo��������pszReplaceWith
			// �滻�������ֲ���������Ҫִ�в��ҡ�
			BOOL           bIgnoreFindWhat;

			// Ҫ�����ַ�������ĳ��ȣ���λ��TCHAR�����������-1�����������Զ����㡣
			LONG           cchFindWhat;

			// �����������������NULL��β��Ӧ�ø������ȣ�����ٶ���NULL��β��
			LPCTSTR        pszFindWhat;

			// �滻�ַ����ĳ��ȣ�����-1�����������Զ����㡣
			LONG           cchReplaceWith;

			// �滻�������������NULL��β��Ӧ�ø������ȣ�����ٶ���NULL��β��
			LPCTSTR        pszReplaceWith;

			// ָ����������ʼλ�á�
			CPoint         ptFrom;

			// �����Ľ���λ�á�
			CPoint         ptTo;

			// ����ת����Сд�Ļ�������
			CString        strCaseBuffer;
		};

		class CPfxEditViewPrintContext : public CPfxEditPrintInfo
		{
		public:
			LONG           m_nCharWidthTab;
			LONG           m_nCharWidthSpace;
			LONG           m_nCharWidthMax;

			LONG           m_nTabSize;

			LONG           m_nFontHeight;
			LONG           m_nLineHeight;
			LONG           m_nHeaderAndFooterLineHeight;

			// �м�ࡣ
			LONG           m_nSpacingLines;

			LONG           m_nTotalPages;
			LONG           m_nMaxLines;
			LONG           m_nLinesPerPage;

			// �﷨������ӡʱ���һ�Ѿ����������С�
			LONG           m_nLineLastParsed;

			LONG           m_nCurPage;
			LONG           m_nCurPageFirstLine;
			LONG           m_nCurPageLastLine;

			LONG           m_nWidthSeparateLine;
			LONG           m_nWidthMarginLine;

			// ����ʱ���ڴ��Ͳ����ͱ���Ƶ��ʹ��SetTextColor()��
			COLORREF       m_clrCurText;

			// ��ǰ�ı�����ɫ��
			COLORREF       m_clrCurTextBkgnd;

			CRect          m_rectLine;
			CPoint         m_ptCurPos;

			// ��ӡ����

			// �������򣬲���ӡ����ʱ���ڿա�
			CRect          m_rectHeader;

			// ��ע���򣬲���ӡ��עʱ���ڿա�
			CRect          m_rectFooter;

			// ��������
			CRect          m_rectText;

			// �к����򣬲���ӡ�к�ʱ���ڿա�
			CRect          m_rectLineNumber;

			// ָ���������ݵ�����Ϣ��������
			CPfxEditHeap   m_cHeap;
		};

		class CPfxEditViewPaintContext
		{
		public:
			// ��ǰ���ı���������ꡣ
			CPoint         m_ptCurPos;

			BOOL           m_bDrawRuler;
			BOOL           m_bDrawLineNumber;
			BOOL           m_bDrawWhitespace;
			BOOL           m_bDrawLineBreak;

			LONG           m_nFirstUpdateLine;
			LONG           m_nLastUpdateLine;

			LONG           m_nCharWidthSpace;
			LONG           m_nCharWidthTab;
			LONG           m_nCharWidthMax;
			LONG           m_nCharWidthLineBreak;

			LONG           m_nTabSize;
			LONG           m_nFontHeight;
			LONG           m_nLineHeight;

			LONG           m_nSpacingLines;
			LONG           m_nTextHorzOffset;

			CRect          m_rectUpdate;
			CRect          m_rectRuler;
			CRect          m_rectLineNumber;
			CRect          m_rectText;
			CRect          m_rectColSelect;
			CRect          m_rectIndent;

			CSize          m_sizeBitmap;

			CPen           m_penNormal;
			CPen           m_penSelect;
			CPen*          m_pPenWhitespace;

			// ��ǰ��ǰ����ɫ������Ƶ��ʹ��SetTextColor()����
			COLORREF       m_clrCurText;

			// ��ǰ�ı�����ɫ��
			COLORREF       m_clrCurTextBkgnd;

			// ��ɫ��Ŀǰ��Ϊֻʹ����ɫ���ԣ����Լ򵥵���COLORREF���飬
			// ����Ժ�֧�ִ���/б�����������Զ���һ���µĽṹ�����
			// ��Ϣ������Ҫ�ñ�׼��CPfxEditKeyClass����Ϊ�����ܴ�
			COLORREF       m_arrColors[kcKeyClassArraySize];
			COLORREF       COLOR(LONG nIndex) const { return m_arrColors[nIndex]; }
		};

		class CPfxEditViewWrapLineHint
		{
		public:
			// ��ʾDC���ӡDC��
			HDC            m_hDC;

			// ����ַ���ȡ�
			LONG           m_nCharWidthMax;

			// TAB�ַ���ȡ�
			LONG           m_nCharWidthTab;

			// �ո��ַ���ȡ�
			LONG           m_nCharWidthSpace;

			// �Ʊ����ȡ�
			LONG           m_nTabSize;

			// ���PFX_EC_WRAP_WINDOWEDGE�����߼���Ԫ���������
			// PFX_EC_WRAP_COLUMNS����������
			LONG           m_nWidth;

			// �������к��������ڵ���������
			LONG           m_nliCur;

			// ��ǰ��CPfxEditLineInfo��СΪ��λ����󻺳������ȡ�
			LONG           m_nliMax;

			// ����ռ䲻�㣬ÿ�����ӵ���CPfxEditLineInfo��СΪ��λ��������
			LONG           m_nGrowBy;
		};

		// ������ַ��Ǹ��ֱ�ʶ�����׸��ַ����������ڹ����ַ���ʱ̽�⡣
		class CPfxEditViewMarkerChar
		{
		public:
			WCHAR          m_cLowerQuotedString1;
			WCHAR          m_cUpperQuotedString1;
			WCHAR          m_cLowerQuotedString2;
			WCHAR          m_cUpperQuotedString2;
			WCHAR          m_cLowerLineComment1;
			WCHAR          m_cUpperLineComment1;
			WCHAR          m_cLowerLineComment2;
			WCHAR          m_cUpperLineComment2;
			WCHAR          m_cLowerBlockComment1;
			WCHAR          m_cUpperBlockComment1;
			WCHAR          m_cLowerBlockComment2;
			WCHAR          m_cUpperBlockComment2;
		};

		class CPfxEditViewBraceHint
		{
		public:
			// EditMatchBraceʹ�á�
			BOOL           m_bMatchCase;  // �����Ƿ�ƥ���Сд��
			BOOL           m_bDirectDown; // ������������
			CString        m_strOn;       // �������������ϵ�ON����
			CString        m_strOff;      // �������������ϵ�OFF����
			CPoint         m_ptFindStart; // ���ؾ�������λ�õĿ�ʼ�����㡣

			// MatchBraceGetString()��MatchBraceGetHint()ʹ�á�
			LONG           m_nMaxBraceString; // ���BRACE�ַ������ȡ�
			CString        m_strBrace;    // ���ش�����STRING��
			CPoint         m_ptStrStart;  // �����������λ�õ�STRING��㡣
			CPoint         m_ptStrEnd;    // �����������λ�õ�STRING�յ㡣
		};

		// ���ڹ���UNDO/REDO��������Ҫ�������趨һ��UNDO��ı߽硣
		class CPfxEditViewUndoManager
		{
		public:
			CPfxEditView*   m_pOwner;
		public:
			CPfxEditViewUndoManager(CPfxEditView* pOwner, WORD fUndoName)
			{
				ASSERT_VALID(pOwner);
				m_pOwner = pOwner;
				m_pOwner->SetUndoGroup(true, fUndoName);
			}

			~CPfxEditViewUndoManager()
			{
				m_pOwner->SetUndoGroup(false, PFX_EC_UNDO_UNKNOWN);
			}
		};

		// ��������ʱ��Ĳ�����
		class CPfxEditViewWorkingState
		{
			LONG           m_nWrapStyle;
			LONG           m_nWrapWidth;
			CPfxEditView*  m_pOwner;
			BOOL           m_bWrapRestore;
		public:
			CPfxEditViewWorkingState(CPfxEditView* pOwner, BOOL bCompactBuffer)
			{
				ASSERT_VALID(pOwner);
				m_pOwner = (bCompactBuffer ? pOwner : NULL);
				if (m_pOwner != NULL)
				{
					m_bWrapRestore = pOwner->IsWrapping();
					if (m_bWrapRestore)
					{
						m_nWrapStyle = pOwner->GetWrapStyle();
						m_nWrapWidth = pOwner->GetWrapWidth();
						pOwner->SetViewWrapping(PFX_EC_WRAP_NONE, 0);
					}

					pOwner->SetLockBufferCompact(true);
					pOwner->SetLockWordWrapEvent(true);
				}
			}

			~CPfxEditViewWorkingState()
			{
				if (m_pOwner != NULL)
				{
					if (m_bWrapRestore)
					{
						m_pOwner->SetViewWrapping(m_nWrapStyle, m_nWrapWidth);
					}

					m_pOwner->SetLockBufferCompact(false);
					m_pOwner->SetLockWordWrapEvent(false);
				}
			}
		};

		class CPfxEditViewClipboard  
		{
		public:
			CPfxEditViewClipboard(CWnd* pOwner, UINT uFormat, BOOL bGet = true);
			~CPfxEditViewClipboard();

		public:
			void        GetClipboardData(CString &strData);
			LPCTSTR        GetClipboardData();

			LPTSTR         GetBuffer(LONG nBufLen, BOOL bAppend);
			char*         GetBuffer2(LONG nBufLen, BOOL bAppend);
			BOOL           SetClipboardData();

			BOOL           Open();
			void           Close();
			BOOL           UnLock(HGLOBAL hGlobal);

			HGLOBAL        Detach();
			BOOL           Attach(HGLOBAL hGlobal);

			LPTSTR         Lock(HGLOBAL hGlobal)
			{
				ASSERT(hGlobal != NULL);
				return static_cast<LPTSTR>(::GlobalLock(hGlobal));
			}
			char*         Lock2(HGLOBAL hGlobal)
			{
				ASSERT(hGlobal != NULL);
				return static_cast<char*>(::GlobalLock(hGlobal));
			}
			HGLOBAL        GetHandle()
			{
				return m_hCBData;
			}

		protected:
			HWND           m_hWndOwner;
			HGLOBAL        m_hCBData;
			UINT           m_uFormat;
			BOOL           m_bOpened;
			BOOL           m_bForGet;
		};

		class CPfxEditViewDataSource : public COleDataSource
		{
			CPfxEditView*   m_pOwner;
			// Constructors
		public:
			CPfxEditViewDataSource(CPfxEditView* pOwner)
			{
				ASSERT_VALID(pOwner);
				m_pOwner = pOwner;
				pOwner->SetDragging(true);
				pOwner->SetDragDropHandled(false);
			}
		public:
			// Operations

			// Overides
			virtual BOOL   OnRenderGlobalData(LPFORMATETC lpFormatEtc, HGLOBAL* phGlobal);

			// Implementation
		public:
			virtual        ~CPfxEditViewDataSource();

#ifdef _DEBUG
			virtual void   AssertValid() const;
			virtual void   Dump(CDumpContext& dc) const;
#endif
		};

		/////////////////////////////////////////////////////////////////////
		//DECLARE_DYNCREATE(CPfxEditView)

	public:
		static CPfxEditView* CeatePfxEditView()
		{
			return new CPfxEditView();
		}

		static void FreePfxEditView(CPfxEditView *pView)
		{
			delete pView;
		}
	protected:
		CPfxEditView(); // protected constructor used by dynamic creation
		CDocument *m_pDocument;

	public:
		virtual BOOL   OnOpenDocFromString(const CString &strText);
		virtual BOOL   OnSaveDocToString(CString &strText);
		void     CharsInsert(const CString &strText);
		BOOL     IsModified();

		// Attributes
	public:
		// �Ƿ��﷨������ʽ��ʾ��
		BOOL           IsDrawHilighted() const;

		// �Ƿ���ʾ��ߡ�
		BOOL           IsDrawRuler() const;

		// �Ƿ���ʾ�кš�
		BOOL           IsDrawLineNumber() const;

		// �Ƿ���ʾ�հ��ַ���
		BOOL           IsDrawWhitespace() const;

		// �Ƿ���ʾ���з���
		BOOL           IsDrawLineBreak() const;

		// ָ�����Ƿ�����ǩ��
		BOOL           IsDrawBookmark(LONG nLine = -1) const;

		// ������ɫ�Ƿ���ϵͳͬ����
		BOOL           IsSyncTextBkColorWithSystem() const;

		// ��б�����ɫ�Ƿ����ı�������ɫͬ�������س���ʾ����
		BOOL           IsSyncActiveLineBkColorWithTextBkColor() const;

		// �Ƿ���ѡ���ı���
		BOOL           IsTextSelected() const;

		// �Ƿ���Գ�����
		BOOL           IsCanUndo() const;

		// �Ƿ���Իָ���
		BOOL           IsCanRedo() const;

		// �Ƿ����ɾ����
		BOOL           IsCanDelete() const;

		// �Ƿ���Լ��С�
		BOOL           IsCanCut() const;

		// �Ƿ���Ը��ơ�
		BOOL           IsCanCopy() const;

		// �ж��Ƿ����ճ����
		BOOL           IsCanPaste() const;

		// �ж��Ƿ�����п�ճ����
		BOOL           IsCanColumnPaste() const;

		// �ж��Ƿ�����п�ѡ��
		BOOL           IsCanColumnSelect() const;

		BOOL           IsWrapping() const;
		BOOL           IsWrapAtWindowEdge() const;
		BOOL           IsWrapAfterColumns() const;

		BOOL           IsOverride() const;
		BOOL           IsReadOnly() const;
		BOOL           IsColumnSelect() const;

		BOOL           IsExpandTabToSpaceChars() const;
		BOOL           IsDragDropEnabled() const;
		BOOL           IsHomeKeyGotoFirstNonWhitespaceChar() const;
		BOOL           IsFirstSiblingView() const;

		// ����ָ�����ַ��Ƿ��ǵ��ʶ������
		BOOL           IsDelimiter(WCHAR wc) const;
		BOOL           IsDelimiter(LPCTSTR pCur, LPCTSTR pEnd) const;

		// ����ָ�����ַ��Ƿ��ǿհ��ַ���
		BOOL           IsWhitespace(WCHAR wc) const;

	public:
		LONG           GetLineCount() const;
		LONG           GetLineUpperBound() const;
		LONG           GetLineLength(LONG nLine) const;
		LONG           GetLineData(LONG nLine, LPTSTR pBuffer, LONG nBufMax) const;

		LONG           GetUndoName() const;
		LONG           GetRedoName() const;

		LONG           GetDocSize() const;
		LONG           GetTabSize() const;

		LONG           GetCurrentChar() const;

		// ��ȡ��ǰ�ı༭λ�á�
		CPoint         GetCurrentPosition(BOOL bLogicalPos = false) const;

		// ��ȡ��ǰѡ��Χ��
		BOOL           GetSelRange(CPoint& rptFrom, CPoint& rptTo) const;

		// ���п�ѡ��ʱ�����������з���Ȼ������ѡ���ı����Ƶ�������ʱȴ��Ҫ
		// �������з����������Ҫ���û���ӳѡ���Сʱ�� bCopyBufferSize����
		// ΪFALSE�����ڻ�ȡ����ѡ���ı��Ļ�������Сʱ�轫bCopyBufferSize��
		// ��ΪTRUE��bCopyBufferSizeֻӰ���п�ѡ������ѡ�������������ӣ�
		// ��ִ�и��Ʋ���ʱ�ж���Ҫ���ļ�����ռ����������ʱӦ��ʹ��
		// GetSelSize(PFX_EC_LINE_BREAK_TYPE_DOS, true)��
		LONG           GetSelSize(LONG nLineBreakType, BOOL bCopyBufferSize = false) const;

		LONG           GetSelData(LONG nLineBreakType, char* pBuffer, LONG nMaxBuf) const;

		// ��ȡ��ǰ���Զ��������á�
		LONG           GetWrapStyle() const;
		LONG           GetWrapWidth() const;

		// ��ȡ��ǰ�ĵ��Ļ��з����á�
		LONG           GetLineBreakSize() const;
		LONG           GetLineBreakType() const;

		// ����������ת���ɱ༭λ�ã��У��У���
		CPoint         TransViewPosToEditPos(CPoint pt) const;

		// ���༭λ�ã��У��У�ת���ɴ������ꡣ
		CPoint         TransEditPosToViewPos(CPoint pt) const;

		// ��һά���ַ�ƫ����ת��Ϊ��ά�ı༭λ�á�
		CPoint         TransCharOfsToEditPos(LONG nOffset) const;

		// ����ά�ı༭λ��ת��Ϊһά���ַ�ƫ������
		LONG           TransEditPosToCharOfs(CPoint pt) const;

		// Operations
	public:
		// ���ĵ�����Ϊֻ��������༭��
		void           SetReadOnly(BOOL bOn);

		// ���ĵ�����Ϊ�Ѿ��޸Ĺ���״̬���ڹر��ĵ�ʱ�������Ƿ񱣴档
		void           SetModifiedFlag(BOOL bChanged);

		// �����п�ѡ��ģʽ��
		void           SetColumnSelect();

		// �Ƿ���븲��ģʽ��
		void           SetOverride(BOOL bOn);

		// ���õ�ǰλ�á�
		void           SetCurrentPosition(LONG nLine, LONG nChar);

		// �����ĵ��Ļ��з����ͣ���Ӱ���ĵ�����ʱ�Ļ��з���ʽ��
		void           SetLineBreakType(LONG nLineBreakType);

		// �����Ƿ���ʾ���з���
		void           SetViewLineBreak(BOOL bOn);

		// �����Ƿ���ʾ�հ��ַ���
		void           SetViewWhitespace(BOOL bOn);

		// �����Ƿ���ʾ��ߡ�
		void           SetViewRuler(BOOL bOn);

		// �����Ƿ���ʾ�кš�
		void           SetViewLineNumber(BOOL bOn);

		// �����Ƿ�����Զ�����ģʽ��
		BOOL           SetViewWrapping(UINT nStyle, LONG nWidth);

		//�Զ���������ɫ
		void           SetKeyClassColor(LONG nIndex, COLORREF color);

	public:
		// ������
		BOOL           EditUndo();

		// �ָ���
		BOOL           EditRedo();

		// ���ơ�
		BOOL           EditCopy(BOOL bAppend);

		// ���С�
		BOOL           EditCut(BOOL bAppend);

		// ճ����
		BOOL           EditPaste(LONG nLine, LONG nChar, LONG nType = PFX_EC_PASTE_NORMAL);

		// ɾ����
		BOOL           EditRemove(LONG nFromLine, LONG nFromChar, LONG nToLine, LONG nToChar);

		// ���롣
		BOOL           EditInsert(LONG nLine, LONG nChar, LPCTSTR pData, LONG cch);

		// ѡ��
		BOOL           EditSelect(LONG nFromLine, LONG nFromChar, LONG nToLine, LONG nToChar);

		// ���ҡ�
		BOOL           EditFind(CPoint& rptFrom,       // [IN/OUT]��Χ��㡣
			CPoint& rptTo,          // [OUT]��Χ�յ㡣
			LPCTSTR pszFindWhat,    // ���Ҷ��󣬳�����cchFindWhat������
			LONG cchFindWhat,       // ���Ҷ���ĳ��ȣ��������-1��ʾ�ɺ����Զ����㳤�ȣ���ʱӦ��NULL��β��
			BOOL bMatchCase,        // �Ƿ�ƥ���Сд��
			BOOL bMatchWholeWord,   // �Ƿ񵥴�ƥ�䡣
			BOOL bRegExp,           // �Ƿ�ʹ��������ʽ����ʱ���Ե���ƥ�䣩��
			BOOL bDirectDown,       // �Ƿ����²��ҡ�
			BOOL bMarkAll,          // �Ƿ�����ǩ����ҵ��Ķ��������С�
			BOOL bWrapAtEndOfFile); // �Ƿ����ļ���ͷ�ۻأ���ֻ�������յ����ĵ���ͷ�������á�
		BOOL           EditFind(LPCTSTR pszFindWhat, BOOL bSelFind=TRUE); 

		// �滻��
		BOOL           EditReplace(CPoint& rptFrom,    // [IN/OUT]��Χ��㡣
			CPoint& rptTo,          // [IN/OUT]��Χ�յ㡣 
			LPCTSTR pszFindWhat,    // ���Ҷ��󣬳�����cchFindWhat������
			LONG cchFindWhat,       // ���Ҷ���ĳ��ȣ��������-1��ʾ�ɺ����Զ����㳤�ȣ���ʱӦ��NULL��β��
			LPCTSTR pszReplaceWith, // �滻���󣬳�����cchReplaceWith������
			LONG cchReplaceWith,    // �滻����ĳ��ȣ��������-1��ʾ�ɺ����Զ����㳤�ȣ���ʱӦ��NULL��β��
			BOOL bMatchCase,        // �Ƿ�ƥ���Сд��
			BOOL bMatchWholeWord,   // �Ƿ񵥴�ƥ�䡣
			BOOL bRegExp,           // �Ƿ�ʹ��������ʽ����ʱ���Ե���ƥ�䣩��
			BOOL bIgnoreFindWhat,   // �Ƿ���Բ��Ҷ������ָ����Χ�ڵ��ı�ֱ�����滻����ȡ����
			BOOL bInSelection);     // �Ƿ�ֻ��ѡ��Χ�ڽ��в����������յ㣬���û��ѡ��������ʧ�ܡ�

		// �����뵱ǰ�༭λ�����ڷ�����Եķ��ţ�����ƥ�����Ź��ܣ���ʶ����
		// ��CPfxEditTypeInfo�е� m_pBraceStringsָ����һ�����﷨�����ļ���
		// �롣
		BOOL           EditMatchBrace();

		// �ո��ַ�ת�����Ʊ����
		// BOOL bLeading �Ƿ�ֻ�����׵Ŀո�ת�������������ġ�
		BOOL           EditSpacesToTabs(BOOL bLeading);

		// �Ʊ��ת���ɿո��ַ���
		BOOL           EditTabsToSpaces();

		// ɾ����ĩ�հ��ַ���
		BOOL           EditTrimTrailingSpaces();

		// ��ȫ����ѡ��Χ�ڵ��ַ�ת����Сд���д��
		BOOL           EditCaseChange(BOOL bLower);

		// ��ȫ����ѡ��Χ�ڵ��ַ���ת��Сд��
		BOOL           EditCaseInvert();

		// ��ȫ����ѡ��Χ�ڵĵ�������ĸ��д��
		BOOL           EditCaseCapitalize();

		void           BookmarkToggle(BOOL bOn, LONG nLine = -1, BOOL bUpdate = true);
		LONG           BookmarkGetNext(LONG nLine, BOOL bWrap);
		LONG           BookmarkGetPrev(LONG nLine, BOOL bWrap);
		void           BookmarkClearAll();
		LONG           BookmarkGetCount() const;

	public:
		void   OnKeyChar(UINT nChar, UINT nRepCnt, UINT nFlags);
		void   OnKeyDownCall(UINT nChar, UINT nRepCnt, UINT nFlags);
		void   OnKeyUpCall(UINT nChar, UINT nRepCnt, UINT nFlags);

		// �������봦�����飬Ҳ������ͨ�ýӿ�ģ��������룬���в��������
		// �ڵ�ǰλ�ý��С�
		void           OnKeyChar(LPCTSTR pData, LONG cch);
		void           OnKeyTab();
		void           OnKeyReturn();
		void           OnKeyInsert();
		void           OnKeyBackSpace(BOOL bWord);
		void           OnKeyDelete(BOOL bWord);
		void           OnKeyHome(BOOL bSelect, BOOL bGotoSOF);
		void           OnKeyEnd(BOOL bSelect, BOOL bGotoEOF);
		void           OnKeyPageUp(BOOL bSelect);
		void           OnKeyPageDown(BOOL bSelect);
		void           OnKeyMoveUp(BOOL bSelect, BOOL bScroll);
		void           OnKeyMoveDown(BOOL bSelect, BOOL bScroll);
		void           OnKeyMoveLeft(BOOL bSelect, BOOL bWord);
		void           OnKeyMoveRight(BOOL bSelect, BOOL bWord);
	public:        
		// ��������CPfxEditView����ʾ���壬�ɵ����߸�������ˢ�¡�
		static BOOL    SetFont(HFONT hFont);

		// ���߼���Ԫ��ָ���м�࣬�ɵ����߸�������ˢ�¡�
		static void    SetSpacingLines(LONG nSpacing);

		// �����к������ĵľ��룬��λ���߼���λ���ɵ����߸�������ˢ�¡�
		static void    SetSpacingLineNumberAndText(LONG nSpacing);

		static HFONT   GetFont();
		static LONG    GetSpacingLines();
		static LONG    GetSpacingLineNumberAndText();
		static LONG    GetLineHeight();

		static BOOL    IsLeadByte(UINT c);

	protected:
		// ��ǰ�Ƿ������SetTracking()���������٣��������ѡ�����ʱ��
		BOOL           IsTracking() const;

		// �Ƿ���OLE�Ϸš�
		BOOL           IsDragging() const;

		// OLE�ϷŲ����Ƿ��Լ������ˣ����������������ڴ����ˡ�
		BOOL           IsDragDropHandled() const;

		// ����ָ����λ���Ƿ�����ѡ��Χ�ڡ�
		BOOL           IsInsideSelect(CPoint ptView) const;

		// ��ǰ�Ƿ���ȷ���п�ѡ��Χ��״̬��
		BOOL           IsColumnSelectTracking() const;

		// �ж��Ƿ�����п�ճ������OLE�Ϸ�ʱʵʩ�п��ƶ����ƣ���
		BOOL           IsDataColumnModeRendered(BOOL bDragDrop, HGLOBAL hGlobal) const;

		// �ڱ������ʱ���Ƿ���Ҫ���¼��㻻����Ϣ���� MDI���͵ĳ����У��û�
		// �����ڲ�ͬ�� MDI�Ӵ��ڳ������ͻ����Ƶ���Ļ��м�������������Ҫ
		// ��ʱ�������м��㣬�Ա���Ƶ�����ظ����������
		BOOL           IsDelayRecalcWrapping() const;

	protected:
		// ���ݴ��������ж�ָ���������Ǹ����֣��кš����ġ���ߣ�
		LONG           GetHitTestCode(CPoint pt) const;

		// ��������ȷ�������ˮƽ�������ֵ���ر���������·������
		// PAGEUP, PAGEDOWN�����봦��
		LONG           GetCaretReferPoint() const;

		// ��ȡ�ֵ���ͼ��ָ�룬û���ֵ���ͼ����NULL��
		CPfxEditView*  GetSiblingView() const;

		// ��ȡ��ǰ��һ�ɼ��С�
		LONG           GetFirstVisibleLine() const;

		// ��ȡ��ǰ���ɼ��У������������е��У������һ������ȫ��ʾ���У���
		LONG           GetLastVisibleLine() const;

		// ��ȡһ�����ı�������ʼ��ֱ�����ƫ�����������ڶ�λ�ı��Ͳ������
		// ��ֱλ�ã����м��Ϊ��ʱ�������㣬����Ϊ�㡣
		LONG           GetLineTextVertOffset() const;

	protected:
		// ���OLE�ϷŲ����Ѿ����Լ������ˡ�
		void           SetDragDropHandled(BOOL bOn);

		// �����Ҫ�ӳ����¼��㻻�У���OnSetFocus()�����¼��㣩��
		void           SetDelayRecalcWrapping(BOOL bOn);

		// ��ǿ�ʼ����OLE�Ϸ�״̬��
		void           SetDragging(BOOL bOn);

		// ��ǿ�ʼ������ꡣ
		void           SetTracking(BOOL bOn);

		// ��ǿ�ʼ�����п�ѡ��Χ��
		void           SetColumnSelectTracking(BOOL bOn);

		/////////////////////////////////////////////////////////////////////
		// ѡ��...
		CPoint         SelGetParam() const;

		// ѡ��ָ��λ�����ڵ��ʡ�
		void           SelWord(CPoint pt);

		// ѡ��ǰ�����С�
		void           SelLine(LONG nLine);

		// �ӵ�ǰλ��ѡ��ָ���㡣
		void           SelRange(CPoint pt);

		// �п�ѡ��
		void           SelRange(CRect& rect);

		// ȡ��ѡ��
		void           SelNone();

		// ȡ��ѡ����ɾ����ǰѡ�����ݡ�
		void           SelNoneAndRemoveSelected();

		// ȡ��ѡ�񲢸�����Ļ��
		void           SelNoneAndUpdateCurrentPosition(LONG nAction);

		/////////////////////////////////////////////////////////////////////
		// �ַ�����...
		// rptFrom����Ե�����λ�á�
		void           CharsInsert(CPoint& rptFrom,
			LPCTSTR pData,
			LONG cch,
			BOOL bUpdate);

		// rptFrom��rptTo����Ե�����λ�á�
		void           CharsRemove(CPoint& rptFrom,
			CPoint& rptTo,
			BOOL bUpdate);

		// rptFrom��rptTo����Ե�����λ�á�
		void           CharsReplace(CPoint& rptFrom,
			CPoint& rptTo,
			LPCTSTR pData,
			LONG cch,
			BOOL bUpdate);

		/////////////////////////////////////////////////////////////////////
		// ƥ���ʶ�������ŵ�...
		BOOL           MatchBraceGetString(CPoint pt, BOOL bPrevStr, CPfxEditViewBraceHint& hint);
		BOOL           MatchBraceGetHint(CPfxEditViewBraceHint& hint);
		BOOL           MatchBraceSearchUp(CPfxEditViewBraceHint& hint, CPoint& rpt);
		BOOL           MatchBraceSearchDown(CPfxEditViewBraceHint& hint, CPoint& rpt);

		/////////////////////////////////////////////////////////////////////
		// ��Сдת��...
		// �ı��Сд��
		BOOL           CaseChange(LONG nLine, LONG nStart, LONG nEnd, BOOL bLower);

		// ��ת��Сд��
		BOOL           CaseInvert(LONG nLine, LONG nStart, LONG nEnd);

		// ���ַ���д��
		BOOL           CaseCapitalize(LONG nLine, LONG nStart, LONG nEnd);

		/////////////////////////////////////////////////////////////////////
		// ���Ҫ�򻺳������ָ�����ո񣬼���û������ĳ��ȣ�������TAB������ո񣩡�
		LONG           FillBufferWithWhitespacesCalcBufferSize(LONG nStartLogChar,
			LONG nSpacesToFill);

		// ʹ�ÿո��TAB���ָ���Ļ�������
		void           FillBufferWithWhitespacesDoFill(LONG nStartLogChar,
			LONG nSpacesToFill,
			LPTSTR pBuffer,
			LONG nBufLen);

		/////////////////////////////////////////////////////////////////////
		// ����һ�ַ������ı���ȣ������������ڿ������ɶ��ٸ��ַ���������
		// �ı����굽�༭�����ת�������簴�����ʱȷ���������λ�á�
		void           CalcCharsToFit(LPCTSTR& rpCharRet,
			LONG& rxTextPos,
			CDC& dc,
			LPCTSTR pStart,
			LPCTSTR pEnd,
			LONG nTestPos,
			LONG nTestLen,
			LONG nLogChar) const;

		// ���һ�ַ�����ĳ��λ���Ƿ�����һMBCS�ַ����м䣬�Ա����ڸ���ָ��
		// �������ֽ�ʱ��MBCS�ַ���ǰ�벿���ơ�
		LONG           CalcCharsToCopy(LPCTSTR pData, LONG cch) const;

		// ������п�ͷ����һ���ǿհ��ַ�֮��Ŀհ�����
		LONG           CalcLeadingWhitespaces(CPoint pt) const;

		// ��һ�ַ�����ĳ��λ�ÿ�ʼ���㵽ָ���Ľ���λ�ã��ۼ�֮����߼��ַ�
		// ������TAB��չ����
		LONG           CalcLogicalChar(LPCTSTR pStart, LPCTSTR pEnd, LONG nTabSize, LONG nLogChar) const;

		// �����ַ����߼���Ԫ��ȣ����ؿ��ֵ��
		LONG           CalcStringWidth(LPCTSTR pData, LONG cch, LONG& nLogChar, CDC* pDC) const;

		// LONG nLine - ������λ�á�
		// LONG nLogCharToTest - �����߼��ַ�λ�ã�TAB��չ��ת���ɾ����ַ�λ�ã�ָ���дλ�ã���
		LONG           CalcAbsCharPosFromLogCharPos(LONG nLine, LONG nLogCharToTest) const;

		/////////////////////////////////////////////////////////////////////
		// ����ת��...
		LONG           TransLinePosToTextPos(LONG nLine) const;
		LONG           TransCharPosToTextPos(CPoint& rpt) const;
		LONG           TransTextPosToLinePos(LONG yTextPos) const;
		LONG           TransTextPosToCharPos(LONG nLine, LONG& rxTextPos) const;

		LONG           TransTextPosToViewPosX(LONG xTextPos) const;
		LONG           TransTextPosToViewPosY(LONG yTextPos) const;
		LONG           TransViewPosToTextPosX(LONG xViewPos) const;
		LONG           TransViewPosToTextPosY(LONG yViewPos) const;

		/////////////////////////////////////////////////////////////////////
		// ����У��...
		void           VerifyCurrentPosition(); // ��鵱ǰλ���Ƿ���Ч��
		void           VerifyPointerPosition(CPoint& rpt) const; // ���X�Ƿ���һ��MBCS�ַ����м䡣

		BOOL           EnsureVisible(LONG nLine, LONG xTextPos);
		void           EnsureVisibleAndUpdateCurrentPosition();
		void           EnsureVisibleAndSetAsCurrentPosition(CPoint pt);
		void           EnsureVisibleAndUpdateLines(LONG nLine, LONG xTextPos, LONG nFirstUpdateLine, LONG nLastUpdateLine);

		/////////////////////////////////////////////////////////////////////
		// ����...
		LONG           ScrollHorz(UINT nSBCode);
		LONG           ScrollVert(UINT nSBCode);

		/////////////////////////////////////////////////////////////////////
		// OLE�ϷŲ���...
		HGLOBAL        DragDropRender(BOOL bDragDrop, BOOL bAppend);
		BOOL           DragDropPaste(HGLOBAL hGlobal, CPoint pt);
		void           DragDropRemove(CPoint& rpt);

		/////////////////////////////////////////////////////////////////////
		// ճ��...
		void           PasteNormal(CPoint pt, LPCTSTR pData, LONG cch);
		void           PasteColumnAlign(CPoint pt, LPCTSTR pData, LONG cch);
		void           PasteColumnAppend(CPoint pt, LPCTSTR pData, LONG cch);

		/////////////////////////////////////////////////////////////////////
		// �����滻...
		BOOL           SearchPreFind(CPfxEditViewFindReplace& rFindReplace);
		BOOL           SearchDoFind(CPfxEditViewFindReplace& rFindReplace);
		BOOL           SearchFindMarkAll(CPfxEditViewFindReplace& rFindReplace);
		BOOL           SearchFindNormalUp(CPfxEditViewFindReplace& rFindReplace);
		BOOL           SearchFindNormalDown(CPfxEditViewFindReplace& rFindReplace);
		BOOL           SearchFindWholeWordUp(CPfxEditViewFindReplace& rFindReplace);
		BOOL           SearchFindWholeWordDown(CPfxEditViewFindReplace& rFindReplace);
		BOOL           SearchFindRegExp(CPfxEditViewFindReplace& rFindReplace);

		BOOL           SearchPreReplace(CPfxEditViewFindReplace& rFindReplace);
		BOOL           SearchDoReplace(CPfxEditViewFindReplace& rFindReplace);
		BOOL           SearchReplaceNormal(CPfxEditViewFindReplace& rFindReplace);
		BOOL           SearchReplaceWholeWord(CPfxEditViewFindReplace& rFindReplace);
		BOOL           SearchReplaceRegExp(CPfxEditViewFindReplace& rFindReplace);


		LPCTSTR        SearchFindNormalStringCase(LPCTSTR pData,
			LONG cch,
			LPCTSTR pszFindWhat,
			LONG cchFindWhat);

		LPCTSTR        SearchFindNormalStringNoCase(LPCTSTR pData,
			LONG cch,
			LPCTSTR pszFindWhat,
			LONG cchFindWhat);

		LPCTSTR        SearchFindWholeWordStringCase(LPCTSTR pStart,
			LPCTSTR pEnd,
			LPCTSTR pData,
			LONG cch,
			LPCTSTR pszFindWhat,
			LONG cchFindWhat);

		LPCTSTR        SearchFindWholeWordStringNoCase(LPCTSTR pStart,
			LPCTSTR pEnd,
			LPCTSTR pData,
			LONG cch,
			LPCTSTR pszFindWhat,
			LONG cchFindWhat);

		/////////////////////////////////////////////////////////////////////
		// λ���ƶ�...
		LPCTSTR        GetPrevCharPos(LPCTSTR pCur, LPCTSTR pStart) const;
		LPCTSTR        GetNextCharPos(LPCTSTR pCur, LPCTSTR pEnd) const;

		LPCTSTR        GetPrevWordPos(LPCTSTR pCur, LPCTSTR pStart) const;
		LPCTSTR        GetNextWordPos(LPCTSTR pCur, LPCTSTR pEnd) const;

		LPCTSTR        GetPrevNonWhitespacePos(LPCTSTR pCur, LPCTSTR pStart) const;
		LPCTSTR        GetNextNonWhitespacePos(LPCTSTR pCur, LPCTSTR pEnd) const;

		LPCTSTR        GetPrevDelimiterPos(LPCTSTR pCur, LPCTSTR pStart) const;
		LPCTSTR        GetNextDelimiterPos(LPCTSTR pCur, LPCTSTR pEnd) const;

		LONG           MoveLeft(CPoint& rpt, BOOL bWord, BOOL bCalcTextPos = true) const;
		LONG           MoveRight(CPoint& rpt, BOOL bWord, BOOL bCalcTextPos = true) const;

		/////////////////////////////////////////////////////////////////////
		// �﷨����...
		BOOL           ParserIsKeyword(LPCTSTR pData, LONG cch) const;

		BOOL           ParserIsEscape(WCHAR wc) const;

		BOOL           ParserIsEscapedLine(LPCTSTR pStart, LPCTSTR pEnd) const;

		// ���һ����λ���Ƿ�����ע�ͻ������ַ����ȿ�ķ�Χ�ڡ�
		// CPoint - �������λ�á�
		BOOL           ParserIsInsideBlock(CPoint pt) const;

		BOOL           ParserIsMarkerStart(LPCTSTR pStart,
			LPCTSTR pCur,
			LPCTSTR pEnd,
			CPfxEditMarkerPair* pMarker) const;

		BOOL           ParserIsMarkerClose(LPCTSTR pStart,
			LPCTSTR pCur,
			LPCTSTR pEnd,
			CPfxEditMarkerPair* pMarker) const;

		BOOL           ParserIsMarkerString(LPCTSTR pStart,
			LPCTSTR pCur,
			LPCTSTR pEnd,
			LPCTSTR pString,
			LONG nStrLen,
			BOOL bCase) const;

		void           ParserGetFirstCharOfMarkerStart(CPfxEditViewMarkerChar& mc) const;

		// ����ָ���鶨����������ֵ�λ�ã�����ڵ�ǰ�����Ҳ����򷵻�NULL��
		LPCTSTR        ParserGetMarkerCloseEndPosition(LPCTSTR pStart,
			LPCTSTR pCur,
			LPCTSTR pEnd,
			BOOL bCurrentAddressPointToMarkerStart,
			CPfxEditMarkerPair* pMarker) const;

		BOOL           ParserPreParse(LONG nLineToEndParse,
			LONG nLineUpperBound,
			LONG nLineLastParsedButCanceled,
			LONG& rnLineLastParsed,
			CPfxEditLineInfo* pliHead) const;

		// ����һ�е����ݷ��ط��������
		DWORD          ParserParseLine(LPCTSTR pData, LONG nLen, DWORD dwCookie) const;

		/////////////////////////////////////////////////////////////////////
		// ����...
		void           DrawRuler(CDC* pdcSrc,
			CDC* pdcMem,
			const CPfxEditViewPaintContext& pc);

		void           DrawLineNumber(LONG nLine,
			CDC* pDC,
			const CPfxEditViewPaintContext& pc);

		void           DrawLineBkgnd(LONG nLine,
			const CPfxEditLineInfo* pli,
			LONG x,
			CDC* pDC,
			const CPfxEditViewPaintContext& pc);

		void           DrawLineBreak(LONG nLine,
			const CPfxEditLineInfo* pli,
			CDC* pDC,
			CPfxEditViewPaintContext& pc);

	protected:
		void           DrawVisualEOL(CDC* pDC, LONG x, LONG y, LONG cx, LONG cy);
		void           DrawVisualEOF(CDC* pDC, LONG x, LONG y, LONG cx, LONG cy);
		void           DrawVisualTab(CDC* pDC, LONG x, LONG y, LONG cx, LONG cy);
		void           DrawVisualSpace(CDC* pDC, LONG x, LONG y, LONG cx, LONG cy);

	protected:
		// ��ͨ�ı�����...
		void           DrawPlainText(CDC* pdcSrc,
			CDC* pdcMem,
			CPfxEditViewPaintContext& pc);

		void           DrawPlainTextNormal(LPCTSTR pData,
			LONG nLen,
			LONG& rnLogChar,
			CDC* pDC,
			CPfxEditViewPaintContext& pc);

		void           DrawPlainTextSelection(LONG nLine,
			const CPfxEditLineInfo* pli,
			LONG& rnLogChar,
			CDC* pDC,
			CPfxEditViewPaintContext& pc);

		// �﷨��������...
		void           DrawHilighted(CDC* pdcSrc,
			CDC* pdcMem,
			CPfxEditViewPaintContext& pc);

		void           DrawHilightedNormal(LONG nLine,
			const CPfxEditLineInfo* pli,
			CDC* pDC,
			CPfxEditViewPaintContext& pc);

		void           DrawHilightedSelection(LONG nLine,
			const CPfxEditLineInfo* pli,
			CDC* pDC,
			CPfxEditViewPaintContext& pc);

		void           DrawHilightedString1(LPCTSTR pData,
			LONG nLen,
			CDC* pDC,
			CPfxEditViewPaintContext& pc);

		void           DrawHilightedString2(LPCTSTR pData,
			LONG nLen,
			LONG& rnLogChar,
			COLORREF color,
			CDC* pDC,
			CPfxEditViewPaintContext& pc);

		LPCTSTR        DrawHilightedStringBaseOnCookie(LPCTSTR pData,
			LONG nLen,
			LONG& rnLogChar,
			DWORD dwCookie,
			CDC* pDC,
			CPfxEditViewPaintContext& pc);

		/////////////////////////////////////////////////////////////////////
		// ��ӡ...
		void           PrintCalcLayout(CDC* pdcPrinter, CPfxEditViewPrintContext& pc);

		void           PrintFormatText(CDC* pdcPrinter, CPfxEditViewPrintContext& pc);

		void           PrintLineNumber(LONG nLine,
			CDC* pDC,
			CPfxEditViewPrintContext& pc);

		void           PrintMargin(const CRect& rectDraw,
			CDC* pDC,
			CPfxEditViewPrintContext& pc);

		void           PrintHeader(CDC* pDC, CPfxEditViewPrintContext& pc);

		void           PrintFooter(CDC* pDC, CPfxEditViewPrintContext& pc);

		void           PrintHeaderFooterText(const CString& strText,
			const CRect& rectDraw,
			CDC* pDC,
			CPfxEditViewPrintContext& pc);

		// ��ͨ�ı���ӡ...
		void           PrintPlainText(CDC* pDC, CPfxEditViewPrintContext& pc);

		void           PrintPlainTextLine(const CPfxEditLineInfo* pli,
			CDC* pDC,
			CPfxEditViewPrintContext& pc);

		// �﷨������ӡ...
		void           PrintHilighted(CDC* pDC, CPfxEditViewPrintContext& pc);

		void           PrintHilightedLine(const CPfxEditLineInfo* pli,
			CDC* pDC,
			CPfxEditViewPrintContext& pc);

		void           PrintHilightedString1(LPCTSTR pData,
			LONG nLen,
			CDC* pDC,
			CPfxEditViewPrintContext& pc);

		void           PrintHilightedString2(LPCTSTR pData,
			LONG nLen,
			LONG& rnLogChar,
			COLORREF color,
			CDC* pDC,
			CPfxEditViewPrintContext& pc);

		LPCTSTR        PrintHilightedStringBaseOnCookie(LPCTSTR pData,
			LONG nLen,
			LONG& rnLogChar,
			DWORD dwCookie,
			CDC* pDC,
			CPfxEditViewPrintContext& pc);

		void           PrintCheckColors(CPfxEditViewPrintContext& pc);
		virtual void   PrintReleaseResource();

		/////////////////////////////////////////////////////////////////////
		// �Զ����в���...
		// ��ָ�����߼���Ԫ�����С�
		void           WrapAtUnits(LONG nWidth);

		// ��ָ�������������С�
		void           WrapColumns(LONG nWidth);

		// �ָ������С�
		void           WrapRestore();

		LONG           WrapLineSingle(CPfxEditHeap& Heap, const CPfxEditLineInfo* pli);

		LONG           WrapLineMultiple(CPfxEditHeap& Heap,
			const CPfxEditLineInfo* pli,
			LONG nCount,
			LONG& rnLineToRemember);

		void           WrapLineAtUnits(CPfxEditHeap& Heap,
			const CPfxEditLineInfo* pli,
			CPfxEditViewWrapLineHint& wl);

		void           WrapLineColumns(CPfxEditHeap& Heap,
			const CPfxEditLineInfo* pli,
			CPfxEditViewWrapLineHint& wl);

		/////////////////////////////////////////////////////////////////////
		// ������...
		void           ScrollBarUpdate(LONG nBar);
		void           ScrollBarSetPos(LONG nBar, LONG nPos);

		//shaolei 20200203  ��ȡ��е��ַ�����
		long GetMaxLineLength(long &nMaxLineIndex);
		//shaolei 20200204 ��ȡ�ַ����
		long GetLineWidth(long nLineIndex);

		/////////////////////////////////////////////////////////////////////
		// �����...
		void           CaretRebuild();
		void           CaretDestroy();
		void           CaretSetPos(CPoint pt);

		/////////////////////////////////////////////////////////////////////
		// ���...
		void           UpdateCursor(CPoint pt);

		/////////////////////////////////////////////////////////////////////
		// ˢ��...
		void           UpdateAllViews(DWORD dwFlags,
			LONG nFirstUpdateLine,
			LONG nLastUpdateLine);

		void           UpdateThisView(CPfxEditView* pView,
			DWORD dwFlags,
			LONG nFirstUpdateLine,
			LONG nLastUpdateLine);

		void           UpdateLayout();
		void           UpdateCurrentPosition(LONG xTextPos,
			BOOL bUpdateCurCharPosition,
			BOOL bUpdateCaretReferPoint);

		void           UpdateLines(LONG nFirstUpdateLine, LONG nLastUpdateLine);
		void           UpdateLinesSelected(LONG nOldSelLineFrom, LONG nOldSelLineTo);

		// Overridable
	public:
		virtual BOOL   OnSetupPrintInfo(CPfxEditPrintInfo* pPrintInfo);

		//�ⲿ���õ�ˢ��ˮƽ������   shaolei  20200204
		void UpdateViewFormEx(CPfxEditView* pView, DWORD dwFlags=PFX_EC_UT_ALL)		{	UpdateAllViews(dwFlags, 0, -1);	}

		// Overrides
		// ClassWizard generated virtual function overrides
		//{{AFX_VIRTUAL(CPfxEditView)
	public:
		virtual void   OnDraw(CDC* pDC);  // overridden to draw this view
		virtual void   OnInitialUpdate();
		virtual BOOL   PreCreateWindow(CREATESTRUCT& cs);
		virtual        DROPEFFECT OnDragEnter(COleDataObject* pDataObject, DWORD dwKeyState, CPoint pt);
		virtual        DROPEFFECT OnDragOver(COleDataObject* pDataObject, DWORD dwKeyState, CPoint pt);
		virtual void   OnDragLeave();
		virtual BOOL   OnDrop(COleDataObject* pDataObject, DROPEFFECT dropEffect, CPoint pt);
		virtual BOOL   OnScroll(UINT nScrollCode, UINT nPos, BOOL bDoScroll = true);
	protected:
		virtual void   OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
		virtual BOOL   OnPreparePrinting(CPrintInfo* pInfo);
		virtual void   OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
		virtual void   OnPrint(CDC* pDC, CPrintInfo* pInfo);
		virtual void   OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
		//}}AFX_VIRTUAL
		void           OnInitialize();

		// Implementation
	protected:
		virtual        ~CPfxEditView();

#ifdef _DEBUG
		virtual void   AssertValid() const;
		virtual void   Dump(CDumpContext& dc) const;
#endif

	protected:
		COleDropTarget m_odt;                  // OLE�ϷŶ���
		CPfxEditDoc*   m_pdb;                  // CPfxEditDocָ��(DocBuffer)��
		CPfxEditTypeInfo* m_pti;               // �﷨����������Ϣ��
		CPfxEditViewPrintContext* m_ppc;       // ��ӡ������Ϣ��

		BOOL           m_bOverride;            // �Ƿ��ڸ���״̬��
		BOOL           m_bTrackingMouse;       // ���ڸ������λ�á�
		BOOL           m_bTrackingColSelect;   // ׷���п�ѡ��Χ��
		BOOL           m_bDragging;            // �Ϸű༭���ڽ��С�
		BOOL           m_bDragDropHandled;     // �Ϸ����ݱ��Լ����ա�
		BOOL           m_bDelayRecalcWrapping; // �ڼ����ʱ���Ƿ���Ҫ���¼��㻻�С�

		LONG           m_nSelMode;             // ѡ��ģʽ
		LONG           m_nSelSize;             // ��ѡ���ı��Ĵ�С����λ���ֽڣ���
		LONG           m_nSelLineFrom;         // ѡ�����ĵ�һ����š�
		LONG           m_nSelLineTo;           // ѡ�������������š�
		CRect          m_rectSelWordModeBaseRange;

		CPoint         m_ptFirstVisible;       // �׸��ɼ��㣬XΪ�߼���Ԫ��λ��YΪ�е�λ��
		CPoint         m_ptEditPos;            // ��ǰλ�ã�������TAB�ַ���չ���Ǿ���λ�á�
		CPoint         m_ptLogiPos;            // ��ǰλ�ã���ʶ��TAB��չ��
		CPoint         m_ptTextPos;            // ��ǰ�ı�λ�ã���λ���߼���Ԫ��
		CPoint         m_ptCaretRefer;         // ����λ�õĲο��㣬�ı������ꡣ

		// �ɼ�����
		// cx����ˮƽ�߼���Ԫ��
		// cy���ڿɼ���������������(�ı����߶� / �и�)��
		CSize          m_sizeVisible;           

		CRect          m_rectClient;           // �ͻ�����
		CRect          m_rectRuler;            // ��ʾ��ߵ�����
		CRect          m_rectText;             // ��ʾ�ı�������
		CRect          m_rectLineNumber;       // ��ʾ�кŵ�����
		CRect          m_rectColSelect;        // �п�ѡ��ʱ��׷������

	public:
		virtual BOOL out_PreTranslateMessage(MSG* pMsg);
		// Generated message map functions
	protected:
		void           SetUndoGroup(BOOL bBegin, WORD fUndoName);
		void           SetLockBufferCompact(BOOL bOn);
		void           SetLockWordWrapEvent(BOOL bOn);

		//{{AFX_MSG(CPfxEditView)
		afx_msg void   OnMouseMove(UINT nFlags, CPoint pt);
		afx_msg BOOL   OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
		afx_msg void   OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
		afx_msg void   OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
		afx_msg void   OnPaint();
		afx_msg void   OnSize(UINT nType, INT cx, INT cy);
		afx_msg void   OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
		afx_msg void   OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
		afx_msg void   OnSetFocus(CWnd* pOldWnd);
		afx_msg void   OnKillFocus(CWnd* pNewWnd);
		afx_msg void   OnCaptureChanged(CWnd *pWnd);
		afx_msg void   OnLButtonDown(UINT nFlags, CPoint pt);
		afx_msg void   OnLButtonUp(UINT nFlags, CPoint pt);
		afx_msg void   OnLButtonDblClk(UINT nFlags, CPoint pt);
		afx_msg INT    OnCreate(LPCREATESTRUCT lpCreateStruct);
		afx_msg void   OnRButtonDown(UINT nFlags, CPoint pt);
		afx_msg BOOL   OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
		afx_msg void   OnDestroy();
		//}}AFX_MSG
		afx_msg LRESULT OnIMEComposition(WPARAM wParam, LPARAM lParam);
		DECLARE_MESSAGE_MAP()

		// friend classes that call protected CPfxEditView overridables
		friend class   CPfxEditDoc;
		friend class   CPfxEditViewDataSource;
		friend class   CPfxEditViewUndoManager;
		friend class   CPfxEditViewWorkingState;
	};

	inline BOOL            CPfxEditView::IsLeadByte(UINT c)                 { return PFX_EC_IS_LEAD_BYTE(c); }
	inline BOOL            CPfxEditView::IsWhitespace(WCHAR wc) const       { return (wc == PFX_EC_CHR_SPACE) || (wc == PFX_EC_CHR_TAB); }
	inline BOOL            CPfxEditView::IsDelayRecalcWrapping() const      { return m_bDelayRecalcWrapping; }
	inline BOOL            CPfxEditView::IsFirstSiblingView() const         { ASSERT(m_pdb != NULL); return (this == m_pdb->m_arrViews[0]); }

	inline BOOL            CPfxEditView::IsWrapping() const                 { ASSERT(m_pdb != NULL); return m_pdb->IsWrapping(); }
	inline BOOL            CPfxEditView::IsWrapAtWindowEdge() const         { ASSERT(m_pdb != NULL); return m_pdb->IsWrapAtWindowEdge(); }
	inline BOOL            CPfxEditView::IsWrapAfterColumns() const         { ASSERT(m_pdb != NULL); return m_pdb->IsWrapAfterColumns(); }

	inline BOOL            CPfxEditView::IsDrawRuler() const                { ASSERT(m_pdb != NULL); return m_pdb->IsDrawRuler(); }
	inline BOOL            CPfxEditView::IsDrawLineNumber() const           { ASSERT(m_pdb != NULL); return m_pdb->IsDrawLineNumber(); }
	inline BOOL            CPfxEditView::IsDrawWhitespace() const           { ASSERT(m_pdb != NULL); return m_pdb->IsDrawWhitespace(); }
	inline BOOL            CPfxEditView::IsDrawLineBreak() const            { ASSERT(m_pdb != NULL); return m_pdb->IsDrawLineBreak(); }
	inline BOOL            CPfxEditView::IsDrawHilighted() const            { ASSERT(m_pti != NULL); return m_pti->IsDrawHilighted(); }

	inline BOOL            CPfxEditView::IsCanColumnSelect() const          { return !IsWrapping(); }
	inline BOOL            CPfxEditView::IsCanColumnPaste() const           { return (IsCanPaste() && !IsWrapping()); }
	inline BOOL            CPfxEditView::IsCanDelete() const                { ASSERT(m_pdb != NULL); return !IsReadOnly() && (m_pdb->GetDocSize() > 0); }
	inline BOOL            CPfxEditView::IsCanCopy() const                  { return IsTextSelected(); }
	inline BOOL            CPfxEditView::IsCanCut() const                   { return !IsReadOnly() && IsTextSelected(); }
	inline BOOL            CPfxEditView::IsCanPaste() const                 { return !IsReadOnly() && ::IsClipboardFormatAvailable(CF_TEXT); }
	inline BOOL            CPfxEditView::IsCanUndo() const                  { ASSERT(m_pdb != NULL); return m_pdb->IsCanUndo(); }
	inline BOOL            CPfxEditView::IsCanRedo() const                  { ASSERT(m_pdb != NULL); return m_pdb->IsCanRedo(); }

	inline BOOL            CPfxEditView::IsColumnSelect() const             { ASSERT(m_pdb != NULL); return (m_nSelMode == PFX_EC_SM_COLUMN) && (m_pdb->GetDocSize() > 0); }
	inline BOOL            CPfxEditView::IsOverride() const                 { return m_bOverride; }
	inline BOOL            CPfxEditView::IsReadOnly() const                 { ASSERT(m_pdb != NULL); return m_pdb->IsReadOnly(); }

	inline BOOL            CPfxEditView::IsTracking() const                 { return m_bTrackingMouse; }
	inline BOOL            CPfxEditView::IsColumnSelectTracking() const     { return m_bTrackingColSelect; }
	inline BOOL            CPfxEditView::IsDragging() const                 { return m_bDragging; } 
	inline BOOL            CPfxEditView::IsDragDropHandled() const          { return m_bDragDropHandled; }

	inline BOOL            CPfxEditView::IsTextSelected() const             { return m_nSelLineFrom != PFX_EC_INVALID_LINE; }
	inline BOOL            CPfxEditView::IsDragDropEnabled() const          { ASSERT(m_pti != NULL); return m_pti->m_bEnableDragDrop; }
	inline BOOL            CPfxEditView::IsExpandTabToSpaceChars() const    { ASSERT(m_pti != NULL); return m_pti->m_bExpandTabToSpaceChars; }
	inline BOOL            CPfxEditView::IsHomeKeyGotoFirstNonWhitespaceChar() const    { ASSERT(m_pti != NULL); return m_pti->m_bHomeKeyGotoFirstNonWhitespaceChar; }
	inline BOOL            CPfxEditView::IsSyncActiveLineBkColorWithTextBkColor() const { ASSERT(m_pti != NULL); return m_pti->m_bSyncActiveLineBkColorWithTextBkColor; }
	inline BOOL            CPfxEditView::IsSyncTextBkColorWithSystem() const{ ASSERT(m_pti != NULL); return m_pti->m_bSyncTextBkColorWithSystem; }

	inline LONG            CPfxEditView::GetCaretReferPoint() const         { return m_ptCaretRefer.x; }
	inline LONG            CPfxEditView::GetFirstVisibleLine() const        { return m_ptFirstVisible.y; }
	inline LONG            CPfxEditView::GetLastVisibleLine() const         { ASSERT(m_pdb != NULL); return m_pdb->TextVerifyLine(m_ptFirstVisible.y + m_sizeVisible.cy - 1); }

	inline LONG            CPfxEditView::GetUndoName() const                { ASSERT(m_pdb != NULL); return m_pdb->GetUndoName(); }
	inline LONG            CPfxEditView::GetRedoName() const                { ASSERT(m_pdb != NULL); return m_pdb->GetRedoName(); }

	inline LONG            CPfxEditView::GetDocSize() const                 { ASSERT(m_pdb != NULL); return m_pdb->GetDocSize(); }
	inline LONG            CPfxEditView::GetTabSize() const                 { ASSERT(m_pti != NULL); return m_pti->m_nTabSize; }

	inline LONG            CPfxEditView::GetLineCount() const               { ASSERT(m_pdb != NULL); return m_pdb->GetLineCount(); }
	inline LONG            CPfxEditView::GetLineUpperBound() const          { ASSERT(m_pdb != NULL); return m_pdb->GetLineUpperBound(); }

	inline LONG            CPfxEditView::GetLineLength(LONG nLine) const    { ASSERT(m_pdb != NULL); return m_pdb->GetLineLength(nLine); }
	inline LONG            CPfxEditView::GetLineData(LONG nLine, LPTSTR pBuffer, LONG nBufMax) const { ASSERT(m_pdb != NULL); return m_pdb->GetLineData(nLine, pBuffer, nBufMax); }

	inline LONG            CPfxEditView::GetWrapStyle() const               { ASSERT(m_pdb != NULL); return m_pdb->GetWrapStyle(); }
	inline LONG            CPfxEditView::GetWrapWidth() const               { ASSERT(m_pdb != NULL); return m_pdb->GetWrapWidth(); }

	inline LONG            CPfxEditView::GetLineBreakSize() const           { ASSERT(m_pdb != NULL); return m_pdb->GetLineBreakSize(); }
	inline LONG            CPfxEditView::GetLineBreakType() const           { ASSERT(m_pdb != NULL); return m_pdb->GetLineBreakType(); }

	inline HFONT           CPfxEditView::GetFont()                          { return PFX_EC_DATA.m_hFontText; }
	inline LONG            CPfxEditView::GetLineHeight()                    { return PFX_EC_DATA.m_nLineHeight; }
	inline LONG            CPfxEditView::GetSpacingLines()                  { return PFX_EC_DATA.m_nSpacingLines; }
	inline LONG            CPfxEditView::GetSpacingLineNumberAndText()      { return PFX_EC_DATA.m_nSpacingLineNumberAndText; }
	inline LONG            CPfxEditView::GetLineTextVertOffset() const      { return GetSpacingLines() / 2; }

	inline void            CPfxEditView::SetColumnSelect()                  { SetColumnSelectTracking(true); }
	inline void            CPfxEditView::SetColumnSelectTracking(BOOL bOn)  { m_bTrackingColSelect = bOn; }
	inline void            CPfxEditView::SetDragging(BOOL bOn)              { m_bDragging = bOn; } 
	inline void            CPfxEditView::SetDragDropHandled(BOOL bOn)       { m_bDragDropHandled = bOn; }
	inline void            CPfxEditView::SetDelayRecalcWrapping(BOOL bOn)   { m_bDelayRecalcWrapping = bOn; }
	inline void            CPfxEditView::SetOverride(BOOL bOn)              { m_bOverride = bOn; }
	inline void            CPfxEditView::SetReadOnly(BOOL bOn)              { ASSERT(m_pdb != NULL); m_pdb->SetReadOnly(bOn); } 
	inline void            CPfxEditView::SetModifiedFlag(BOOL bChanged)     { ASSERT(m_pdb != NULL); m_pdb->SetModifiedFlag(bChanged); } 
	inline void            CPfxEditView::SetLineBreakType(LONG nType)       { ASSERT(m_pdb != NULL); m_pdb->SetLineBreakType(nType); }

	inline void            CPfxEditView::SetLockBufferCompact(BOOL bOn)     { ASSERT(m_pdb != NULL); m_pdb->SetLockBufferCompact(bOn); }
	inline void            CPfxEditView::SetLockWordWrapEvent(BOOL bOn)     { ASSERT(m_pdb != NULL); m_pdb->SetLockWordWrapEvent(bOn); }
	inline void            CPfxEditView::SetUndoGroup(BOOL bBegin, WORD fUndoName) { ASSERT(m_pdb != NULL); m_pdb->UndoSetGroup(bBegin, fUndoName); }

	inline LONG            CPfxEditView::BookmarkGetCount() const           { ASSERT(m_pdb != NULL); return m_pdb->GetBookmarkCount(); }

	inline BOOL            CPfxEditView::ParserIsEscape(WCHAR wc) const     { ASSERT(m_pti != NULL); return m_pti->IsEscape(wc); }
	inline BOOL            CPfxEditView::ParserIsKeyword(LPCTSTR pData, LONG cch) const { ASSERT(m_pti != NULL); return (m_pti->m_mapKeywords.Lookup(pData, cch) != -1); }

	/////////////////////////////////////////////////////////////////////////////
} // namespace CPfx

//using namespace CPfx;