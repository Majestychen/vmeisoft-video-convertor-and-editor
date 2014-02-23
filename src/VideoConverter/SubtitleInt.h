#pragma once

struct ClipInfo;

/*********************************************
// Ч������
*********************************************/

// ���뵭��Ч��
// IN: ���룬OUT������
// {D7377569-F21B-4FA9-999D-B57B19B32047}
static const GUID IID_Subtitle_Fade = 
{ 0xd7377569, 0xf21b, 0x4fa9, { 0x99, 0x9d, 0xb5, 0x7b, 0x19, 0xb3, 0x20, 0x47 } };

// �õ�ƬЧ��
// IN������ 
// OUT���˳� 
// {A0EF4D22-3DF0-4C8C-A6BB-674E194E1256}
static const GUID IID_Subtitle_Slide = 
{ 0xa0ef4d22, 0x3df0, 0x4c8c, { 0xa6, 0xbb, 0x67, 0x4e, 0x19, 0x4e, 0x12, 0x56 } };

// �õ�ƬЧ������
#define SLIDE_DIRECTION_LEFT			0
#define SLIDE_DIRECTION_TOP				1
#define SLIDE_DIRECTION_RIGHT			2
#define SLIDE_DIRECTION_BOTTOM			3
#define SLIDE_DIRECTION_LEFT_TOP		4
#define SLIDE_DIRECTION_RIGHT_TOP		5
#define SLIDE_DIRECTION_LEFT_BOTTOM		6
#define SLIDE_DIRECTION_RIGHT_BOTTOM	7

/*********************************************
// ���뷽ʽ
*********************************************/
enum SubtitleAlignment
{
    SubtitleAlignmentNear = 0,
    SubtitleAlignmentCenter = 1,
    SubtitleAlignmentFar = 2,
	SubtitleAlignmentNone = 3 // ��ʱ��֧��
};

/*********************************************
// ��ɫ����
*********************************************/
union ColorRef
{
	uint32_t Color;
	struct
	{
		uint8_t B, G, R, A;
	};
};

/*********************************************
// �������壬��GdiPlus��ͬ
*********************************************/
#if 0
// �������
enum FontStyle
{
    FontStyleRegular    = 0,
    FontStyleBold       = 1,
    FontStyleItalic     = 2,
    //FontStyleBoldItalic = 3,
    FontStyleUnderline  = 4,
    FontStyleStrikeout  = 8
};
#endif


struct SubtitleDefault
{
	//  ��ʾЧ��Ĭ�ϲ���
	wchar_t				m_FontName[32]; // ��������
	int32_t					m_FontSize; // ����ߴ�
	uint32_t			m_FontStyle; // ������
	ColorRef			m_FontColor; // ������ɫ��0xAARRGGBB
	ColorRef			m_BorderColor; // �߿���ɫ��0xAARRGGBB
	ColorRef			m_ShadowColor; // ��Ӱ��ɫ��0xAARRGGBB

	// ����Ч��Ĭ�ϲ���
	GUID				m_Entrance; // ����Ч�������ΪGUID_NULL, ����Ч��
	int32_t				m_EntranceParam; // ��������� SLIDE_DIRECTION_
	int64_t				m_EntranceTime;	// ����ʱ����ʱ��ԽС���ٶ�Խ��
	BOOL				m_EntranceOnce; // ����һ��Ч��һ��ִ��
	GUID				m_Exit; // �˳�Ч�������ΪGUID_NULL, ����Ч��
	int32_t					m_ExitParam; // �˳������� SLIDE_DIRECTION_
	int64_t				m_ExitTime; // �˳�ʱ����ʱ��ԽС���ٶ�Խ��
	BOOL				m_ExitOnce; // ����һ��Ч��һ��ִ��

	// ���뷽ʽĬ�ϲ���
    SubtitleAlignment	m_Alignment; // ���뷽ʽ�����У��ұ�

	// ItemĬ�ϲ���
    SubtitleAlignment	m_HPosition; // ˮƽλ��
    SubtitleAlignment	m_VPosition; // ��ֱλ��
	int32_t				m_LineSpace; // �м��
	Point				m_Postion; // ����λ�ã����SubtitleAlignment = SubtitleAlignmentNone

};

extern int32_t _stdcall SubtitleDefault_Size();
extern SubtitleDefault* SubtitleGetDefault();

#define MAX_SUBTITLE_LINE_SIZE		256

/*********************************************
// ��Ļ
*********************************************/
class CSubtitleLine
{
public:
	int32_t				m_index; // ��ʱ������
	wchar_t				m_Title[MAX_SUBTITLE_LINE_SIZE]; // �ı�����

	// ����
	wchar_t				m_FontName[32]; // ��������
	int32_t				m_FontSize; // ����ߴ�
	uint32_t			m_FontStyle; // ������
	ColorRef			m_FontColor; // ������ɫ��0xAARRGGBB
	ColorRef			m_BorderColor; // �߿���ɫ��0xAARRGGBB
	ColorRef			m_ShadowColor; // ��Ӱ��ɫ��0xAARRGGBB

	// Ч��
	GUID				m_Entrance; // ����Ч�������ΪGUID_NULL, ����Ч��
	int32_t				m_EntranceParam; // ��������� SLIDE_DIRECTION_
	int64_t				m_EntranceTime;	// ����ʱ����ʱ��ԽС���ٶ�Խ��
	BOOL				m_EntranceOnce; // ����һ��Ч��һ��ִ��
	GUID				m_Exit; // �˳�Ч�������ΪGUID_NULL, ����Ч��
	int32_t				m_ExitParam; // �˳������� SLIDE_DIRECTION_
	int64_t				m_ExitTime; // �˳�ʱ����ʱ��ԽС���ٶ�Խ��
	BOOL				m_ExitOnce; // ����һ��Ч��һ��ִ��

	// ����
    SubtitleAlignment	m_Alignment; // ���뷽ʽ�����У��ұ�

	// �ڲ�����
	int64_t				m_EntranceStart;
	int64_t				m_EntranceStop;
	int64_t				m_ExitStart;
	int64_t				m_ExitStop;
	RectF				m_Bounds;
	PointF				m_Position;
	PointF				m_PointStart;
	PointF				m_PointStop;

public:
	CSubtitleLine();

public:
	RectF CalcBounds();
	void CalcEffect(int64_t time, PointF &point, ColorRef &FontColor, ColorRef &BorderColor, ColorRef &ShadowColor);
};

extern int32_t __stdcall CSubtitleLine_Size();

/*********************************************
// ��Ļ
*********************************************/
class CSubtitleItem
{
public:
	int32_t				m_index; // ��ʱ������
	int32_t				m_Count; // ����
	CSubtitleLine**		m_Lines; // �ı�����
	int64_t				m_StartTime; // ��ʼʱ��
	int64_t				m_Duration; // ʱ��

public:
    SubtitleAlignment	m_HPosition; // ˮƽλ��
    SubtitleAlignment	m_VPosition; // ��ֱλ��
	int32_t				m_LineSpace; // �м��
	Point				m_Postion; // ����λ�ã����SubtitleAlignment = SubtitleAlignmentNone

public:
	CSubtitleItem();
	~CSubtitleItem();

public:
	void CalcParamters(int32_t viewWidth, int32_t viewHeight);

public:
	CSubtitleLine* NewLine();
	void AddItem(CSubtitleItem *item);
	void AddLine(wchar_t *Text); // Copy Text
	void DeleteLine(int32_t index);
	void DrawInto(Gdiplus::Graphics* graphics, int64_t pts, int32_t FocusIndex);
	inline void ConvertFrameToTime(int64_t num, int64_t den);
};

extern int32_t __stdcall CSubtitleItem_Size();

/*********************************************
// ��Ļ
*********************************************/

class CSubtitle
{
public:
	int32_t					m_Count; // ��Ļ����
	CSubtitleItem**			m_Items; // ��Ļ��Ŀ

public:
	// �ڲ�����
	BOOL					m_FrameBase; // �Ƿ����FRAME

public:
	CSubtitle();
	~CSubtitle();

public:
	CSubtitleItem* NewItem();
	void DeleteItem(int32_t index);
	void ConvertFrmaeToTime(int32_t num, int32_t den);

public:
	void SortItem();
	void CalcParamters(int32_t viewWidth, int32_t viewHeight);
	int32_t FirstItem(int64_t pte);
	void ConvertFrameToTime(int64_t num, int64_t den);
	void CheckTime(int64_t duration);
	void MergeTime();
};

extern int32_t __stdcall CSubtitle_Size();

/*********************************************
// �ӿں���
*********************************************/
// ������Ļ�ļ�
// �������ɹ��������ԭ�ȵ���Ļ;ʧ�ܽ�����ԭ������Ļ
// ���ص������Ļ��ʧ�ܷ���NULL
extern CSubtitle* __stdcall SubtitleImport(ClipInfo *Info, wchar_t *szFileName);

// ��ȡ��Ļ��Ϣ
extern CSubtitle* __stdcall SubtitleGet(ClipInfo *Info);

// �����Ļ������Ŀ
//  ���û����Ļ�ᴴ��һ���յ���Ļ
extern CSubtitleItem* __stdcall SubtitleAddItem(CSubtitle *subtitle);

// �����Ļ������Ŀ
//  ���û����Ļ�ᴴ��һ���յ���Ļ
extern CSubtitleLine* __stdcall SubtitleAddLine(CSubtitleItem *item);

// ɾ����Ļ��Ŀ
extern void __stdcall SubtitleDelete(CSubtitle *subtitle, int32_t index);

// ɾ����ĻLine
extern void __stdcall SubtitleDeleteLine(CSubtitleItem *item, int32_t index);

// ��������޸���ʱ�䣬���밴ʱ�䣨��ʼʱ�䣩����
extern void __stdcall SubtitleSort(CSubtitle *subtitle);

/*********************************************
// �ӿں���������
*********************************************/

// ���������֮���������¼�
// ���û��m_TransitionInFilter��m_TransitionOutFilter�����ᴥ������¼�
// wParam:CSubtitlePlayer��ָ��
// lParam:δ����
#define CM_SUBTITLE_PLAYER_END	(WM_USER + 1)

class CSubtitlePlayer;

// ����һ��Subtitle�Ĳ��Ŵ���
extern CSubtitlePlayer* __stdcall SubtitleCreatePlayer(HWND hwndParent, HWND hwndMessage, CSubtitleItem *item);

// ����
extern void __stdcall SubtitlePlay(CSubtitlePlayer* player);

// ����
extern void __stdcall SubtitlePlayEx(CSubtitlePlayer* player, int32_t index, BOOL IsExitEffect);

// �ػ�
extern void __stdcall SubtitleRedraw(CSubtitlePlayer* player);

// ���ý���
extern void __stdcall SubtitleSetFocus(CSubtitlePlayer* player, int32_t index);

// �ͷŲ�����
extern void __stdcall SubtitleDestroyPlayer(CSubtitlePlayer* player);
