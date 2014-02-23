#pragma once

#include <stdint.h>

#define VC_MESSAGE_BASE (WM_USER + 256)

/*****************************************************
ʱ�䶨�壺1/1000000��
*****************************************************/
#ifndef AV_TIME_BASE_LL
#define AV_TIME_BASE_LL            	1000000ll
#endif

/*
struct Point
{
	int32_t X;
	int32_t Y;
};

struct Size
{
	int32_t Width;
	int32_t Height;
};

struct Rect
{
	int32_t X;
	int32_t Y;
	int32_t Width;
	int32_t Height;
};

struct PointF
{
	float X;
	float Y;
};

struct SizeF
{
	float Width;
	float Height;
};

struct RectF
{
	float X;
	float Y;
	float Width;
	float Height;
};
*/

/*****************************************************
// Resize Method
*****************************************************/
enum ResizeMethod
{
	ResizeMethod_LetterBox, // 0
	ResizeMethod_Crop, // 1
	ResizeMethod_Center, // 2
	ResizeMethod_Fill, // 3
};

/*****************************************************
��������
*****************************************************/
enum FillType
{
	FillType_Solid,
	FillType_Gradient,
	FillType_Picture,
};

/*****************************************************
��䷽��
*****************************************************/
enum FillDirect
{
	FillDirect_Top,
	FillDirect_Left,
	FillDirect_TopLeft,
	FillDirect_TopRight,
};


/*****************************************************
����ͼ��ĸ�ʽ
*****************************************************/
enum GrabFileType
{
	GrabFileType_PNG,
	GrabFileType_JPG,
	GrabFileType_BMP,
};

/*****************************************************
ˮӡ���뷽ʽ
*****************************************************/
enum LogoAlignment
{
    LogoAlignmentNear = 0, // ���λ�ã���ߣ��ϱ�
    LogoAlignmentCenter = 1, // ����
    LogoAlignmentFar = 2, // ��Զλ�ã��ұߣ��±�
	LogoAlignmentNone = 3 // ����
};


/*****************************************************
ȫ�ֵĲ�����ϵͳ������Ϣ����
*****************************************************/

struct VCGlobal
{
	// Ĭ�����·��
	wchar_t			m_OutputPath[MAX_PATH];

	// ����ת��������
	int32_t			m_Parallel;

	// ���췽ʽ����
	ResizeMethod	m_ResizeMethod;

	// ������Ĭ��Ϊ��ɫ����
	FillType		m_FillType; // �����������
	uint32_t		m_FillColor1; // ����ɫ1
	uint32_t		m_FillColor2; // ����ɫ2
	FillDirect		m_FillDirect; // ����ɫ��䷽��
	wchar_t			m_FillPicture[MAX_PATH]; // ͼƬ��·����������ΪͼƬʱ��Ч

	// ͼ��ץȡʱ��Ĭ�ϸ�ʽ
	GrabFileType	m_GrabFileType;

	// (����) ˮӡ
	wchar_t			m_LogoFile[MAX_PATH]; // ˮӡ�ļ�����:���Ϊ����������ö�����
	Size			m_LogoFileSize; // ԭʼͼƬ�ߴ�
	Rect			m_LogoRect; // ˮӡ�ļ���λ�ã������������λ�ã�X��Y��ֵ�ᱻ����
	int32_t			m_LogoAlpha; // ˮӡ�ļ���͸���ȣ�0-��͸����255-ȫ͸����ȡֵ��0��240֮��(>240û����)������ֵ��Ϊ��͸������
	int32_t			m_LogoHPosition; // ˮӡ��ˮƽλ�ö��뷽ʽ��LogoAlignment
	int32_t			m_LogoVPosition; // ˮӡ�Ĵ�ֱλ�ö��뷽ʽ��LogoAlignment
};

// ����VCGlobal���ֽ�������Ӧ�õ���������������Ӧ�ó�����Ľṹ�峤�Ⱥ͵ײ㶨��Ľṹ�峤���Ƿ�һ��
extern int32_t __stdcall VCGlobal_Size();

// ����ȫ�ֲ�����ָ��
extern VCGlobal* __stdcall vcGetGlobal();

/*****************************************************
���������ȫ��
*****************************************************/
struct CodecOptions
{
	wchar_t			m_Format[64]; // ����ļ���ʽ: �������
	wchar_t			m_Target[64]; // ����
	wchar_t			m_ExtName[64]; // ��չ���ƺ�׺

	wchar_t			m_VideoCodec[64]; // ��Ƶ����������
	int32_t			m_VideoBitrate; // �����ı����ʣ����Ϊ0����ΪVBR
	int32_t			m_FrameNum, m_FrameDen; // ������֡��
	int32_t			m_VideoWidth, m_VideoHeight; // ��Ƶ�Ŀ�͸�
	int32_t			m_VideoDisable; // ��������Ƶ����������Ƶ

	wchar_t			m_AudioCodec[64]; // ��Ƶ����������
	int32_t			m_AudioBitrate; // �����ı����ʣ����Ϊ0����ΪVBR
	int32_t			m_AudioSampleRate; // �����Ĳ�����
	int32_t			m_AudioChannels; // ������ͨ������
	int32_t			m_AudioDisable; // ��������Ƶ����������Ƶ

	volatile BOOL	m_Pause; // ���Ϊ��0���ᵼ��ת����ͣ����������ֹͣ�����ܻ���ʱһ����
};

// ����CodecOptions���ֽ�������Ӧ�õ���������������Ӧ�ó�����Ľṹ�峤�Ⱥ͵ײ㶨��Ľṹ�峤���Ƿ�һ��
extern int32_t __stdcall CodecOptions_Size();

// ����ȫ�ֱ��������ָ��
extern CodecOptions* __stdcall vcGetCodecOptions();

/*****************************************************
ý����Ϣ����
*****************************************************/
// ״̬
enum MediaStat
{
	MediaStat_None = 0, // 
	MediaStat_Importing = 10, // ���ڵ���ý����Ϣ
	MediaStat_Error_File = 11, // ����ý����Ϣ����
	MediaStat_Check_Media = 12, // �Ѿ��ɹ���ȡý����Ϣ�����ڼ��ý���ļ���Ӧ���������
	MediaStat_Thumbnail_Generated = 13, // �Ѿ��ɹ���������ͼ
	MediaStat_Complete = 14, // ���
};

struct MediaInfo
{
	GUID			m_Id; // Ψһ��ʶ
	MediaStat		m_Status; // 

	// �ļ�����Ϣ
	wchar_t			m_szFileName[MAX_PATH]; // �ļ�·��

	int64_t			m_Duration; // �ܳ���
	int64_t			m_StreamDuration; // *(�ڲ�ʹ��) ������
	wchar_t			m_FormtDesc[128]; // �ļ���ʽ

	// ��Ƶ��Ϣ
	int32_t			m_bVideoStream; // �Ƿ������Ƶ
	wchar_t			m_VideoCodec[128]; // ��Ƶ��ʽ����
	int64_t			m_VideoStartPts; // *(�ڲ�ʹ��) ��Ƶ��ʼʱ��
	int32_t			m_Width; // ��Ƶ��
	int32_t			m_Height;// ��Ƶ��
	int32_t			m_CodecWidth; // ��Ƶ��
	int32_t			m_CodecHeight;// ��Ƶ��
	int32_t			m_FrameRateNum; // ֡��
	int32_t			m_FrameRateDen; // ֡��
	int32_t			m_PixelFormat; // * �ڲ�����
	int32_t			m_VideoBitRate; // ��Ƶ������
	int64_t			m_VideoDuration; // ��Ƶ����

	// ��Ƶ��Ϣ
	int32_t			m_bAudioStream; // �Ƿ������Ƶ
	wchar_t			m_AudioCodec[128]; // ��Ƶ��ʽ����
	int64_t			m_AudioStartPts; // *(�ڲ�ʹ��) ��Ƶ��ʼʱ��
	int32_t			m_SampleRate; // ��Ƶ����
	int32_t			m_nChannel; // ��Ƶͨ������
	uint64_t		m_channel_layout; // *(�ڲ�ʹ��) ��Ƶͨ�����з�ʽ
	int32_t			m_SampleFormat; // *(�ڲ�ʹ��)��Ƶ��ʽ
	int32_t			m_AudioBitRate; // ��Ƶ������
	int64_t			m_AudioDuration; // ��Ƶ����
	int32_t			m_IsPlanar; // *(�ڲ�ʹ��)��Ƶ�Ƿ�Ϊƽ��ģʽ

	// ����
	wchar_t			m_Demo[MAX_PATH]; // ʾ��ͼ:BMP

	//�ļ���Ϣ
	FILETIME		m_ftCreationTime; // ����ʱ��
	LARGE_INTEGER	m_liFileSize; // �ļ���С
	FILETIME		m_History; // ��Ϣ����ʱ��

	// �ڲ�����
	wchar_t			m_AudioTmpFile[8][MAX_PATH];
	int64_t			m_AudioLength; // Samples

};

// ����MediaInfo���ֽ�������Ӧ�õ���������������Ӧ�ó�����Ľṹ�峤�Ⱥ͵ײ㶨��Ľṹ�峤���Ƿ�һ��
extern int32_t __stdcall MediaInfo_Size();


/*****************************************************
ת����Ŀ����
*****************************************************/

// ״̬
enum VCItemStat
{
	ClipStat_None = 0, // 
	ClipStat_Ready_For_Convert = 20, // һ��״̬
	ClipStat_Wait_For_Convert = 21, // �ȴ�ת��������
	ClipStat_Start_Convert = 22, // ��ʼת��
	ClipStat_Converting = 23, // ����ת����Ӧ���������
	ClipStat_Converted = 24, // ת��������
	ClipStat_Failed = 25, // ת��ʧ�ܣ�
	ClipStat_Abort = 26 // ת����ȡ����
};


// ������Ƶ���м���ʱ��Ӧ�õ�����ʼʱ��ͽ���ʱ��
struct AudioTrack
{
	struct MediaInfo* m_Media; // ý����Ϣ
	int64_t m_MediaStart; // ��ʼʱ�䣺�����ý���ļ��ļ���
	int64_t m_MediaStop; // ����ʱ�䣺�����ý���ļ��ļ��У����Ϊ0��ʾֱ������
	int64_t m_Start; // ��ʼʱ�䣺�������Ƶ
	int64_t m_Stop; // ����ʱ�䣺�������Ƶ
	int32_t	m_Volume; // �������ã�1-150; <100:���������� 100:ԭʼ������ >100�Ŵ����������ܻᵼ�����⣩

public:
	AudioTrack();
};

struct VCItem
{
	// ������
	GUID				m_ID; // Ψһ��ʶ
	wchar_t				m_Name[256]; // ����
	wchar_t				m_OutFile[MAX_PATH]; // ����ļ�·��

	// ý����Ϣ:��Ƶ����
	struct MediaInfo*	m_MediaInfo;

	// ��Ƶ���֣��������Ƶ�༭����Ч
	// !!!! ���һ�����������Ƶ��û����Ƶ�����ò�����Ч����ʼʱ��ͽ���ʱ��ᱻ���ԣ����Ǻ���Ƶͬ������m_Media=m_MediaInfo
	// ���������������
	// �������¼��
	// ���ж������ʱӦ������ÿ�����������
	struct AudioTrack	m_AudioTrack[3]; // ���֧���������죬����ԭʼ�����������ܳ�����������

	// Clip / Trim
	int64_t				m_ClipStart; // ��ʼʱ��
	int64_t				m_ClipStop; // ����ʱ�䣬���Ϊ0��ʾ���ŵ���β

	// Speed
	int32_t				m_Speed; // 0-ԭʼ�ٶȲ��ţ� >0: ����1/100���ٶȣ���100Ϊ�������ٶȣ� <0; ����1/100���ٶȣ���-50Ϊ1/2���ٶȣ�����<=100

	// ��Ϣ����
	VCItemStat			m_Status; // Item��״̬
	HWND				m_hwndMessage; // ���ڽ���״̬�ı����Ϣ�Ĵ���
	volatile int64_t	m_Time; //  ��ǰ�Ѿ���ɵ�ʱ��
	int64_t				m_Duration; //  ת�����ʱ��
	void*				m_UserData; // �û��Զ������ݣ����Դ���κ�����
};

struct ClipInfo; //ClipInfo = VCItem;

/*****************************************************
��Ϣ����
*****************************************************/

// ����MediaInfo���ֽ�������Ӧ�õ���������������Ӧ�ó�����Ľṹ�峤�Ⱥ͵ײ㶨��Ľṹ�峤���Ƿ�һ��
extern int32_t __stdcall VCItem_Size();

/*****************************************************
��ʼ��
*****************************************************/
extern HRESULT __stdcall vcInitialize(); // ������������֮ǰ�������Ӧ�ñ�����
extern void __stdcall vcUninitialize(); // Ӧ�ó����˳�֮ǰӦ�ñ�����

/*****************************************************
����ý��
*****************************************************/

// ����״̬�����ı�
// wParam:û��ʹ��
// lParam:״̬��MediaStat
#define VC_IMPORT_STATUS	(VC_MESSAGE_BASE + 1)

// ������
//	hwndMessage:������Ϣ�Ĵ��ڣ���Ϣ�ο�ǰ��Ķ���
//  szFile:�ļ�·��
// ������
//	�ú����������أ����Զ��ͬʱ�������ļ��� ��̨���е��롣
//  ��ο���ϢVC_ITEM_STAT_CHANGED
//  ���ȶ����� m_Time / m_Duration
extern MediaInfo* __stdcall vcImportMediaInfo(HWND hwndMessage, wchar_t *szFile);

// �ͷ�ý����Ϣ
// ������Ҫ��¼����Ϣʹ��
extern void __stdcall MediaInfoFree(MediaInfo* info);

// ��ֹ����
class CMediaInfo; // CMediaInfo = MediaInfo
extern void __stdcall vcImportAbort(CMediaInfo *info);

// ��ȡ����
// ���ذٷֱ�
extern int __stdcall vcImportGetProgress(CMediaInfo *info);

/*****************************************************
��ITEM�Ĳ���
*****************************************************/
extern ClipInfo* __stdcall vcCreateItem(HWND hwndMessage, MediaInfo *info); // �½�һ��ת����Ŀ
extern void __stdcall vcDeleteItem(ClipInfo *item); // ɾ����ɾ�����������ı�


/*****************************************************
��Ƶ����
*****************************************************/

// ���Ž����¼�
// wParam:΢�� 1/AV_TIME_BASE_LL
// lParam:����
// ��ʱ��:lParam * AV_TIME_BASE_LL + wParam 
#define VC_VIDEO_RENDER_PROGRESS		(VC_MESSAGE_BASE + 10)

// ��������¼�
// wParam:δ����
// lParam:δ����
#define VC_VIDEO_RENDER_END				(VC_MESSAGE_BASE + 11)

// ����ģʽ����
enum VideoPlayerMode
{
	VC_VIDEO_RENDER_MODE_SOURCE, // ����ԭʼ����Ƶ
	VC_VIDEO_RENDER_MODE_DEST, // ����ת�����Ч��
};

// ����
// �Զ�����
class CVideoPlayer;
extern CVideoPlayer* __stdcall vcCreateVideoPlayer(HWND hwndParent, HWND hwndMessage, ClipInfo* item, VideoPlayerMode Mode);

// ���ٲ��Ŵ���
extern void __stdcall vcVideoPlayerDestroy(CVideoPlayer *player);

// ���浱ǰͼ���ļ�:�ļ���ʽ������m_GrabFileType
extern HRESULT __stdcall vcVideoPlayerGrab(CVideoPlayer *player, wchar_t *szFile);

// ���µ������Ŵ���
// �첽ִ��
extern void __stdcall vcVideoPlayerResize(CVideoPlayer *player);

// ���ÿ�ʼʱ��ͽ���ʱ��
// ��������ԭʼ��Ƶʱ��Ч
extern void __stdcall vcVideoPlayerStartStop(CVideoPlayer *player, int64_t start, int64_t stop);

// ��������ͣ
// ������ŵ���β��vcVideoPlayerResume����ͷ��ʼ����
// �첽ִ��
extern void __stdcall vcVideoPlayerResume(CVideoPlayer *player);
extern void __stdcall vcVideoPlayerPause(CVideoPlayer *player);

// Seek֮������ͣ״̬
// �첽ִ��
extern void __stdcall vcVideoPlayerSeekTo(CVideoPlayer *player, int64_t pts);

// ʹ�����к����ᵼ����ͣ
extern void __stdcall vcVideoPlayerNextFrame(CVideoPlayer *player); // ��һ֡, ���ص�ǰ�������������-1��ʾʧ��
extern void __stdcall vcVideoPlayerNextTime(CVideoPlayer *player); // ��һ��, ���ص�ǰ�������������-1��ʾʧ��
extern void __stdcall vcVideoPlayerPreTime(CVideoPlayer *player); // ��һ��, ���ص�ǰ�������������-1��ʾʧ��

// ���ص�ǰ��ʱ�䣺1/AV_TIME_BASE_LL��
extern int64_t __stdcall vcVideoPlayerCurrentTime(CVideoPlayer *player);

// ǿ���ػ���
extern void __stdcall vcVideoPlayerForceRedraw(CVideoPlayer *player);


//*****************************************************
// ��Ƶ������
// �������������Ǳ����������ĺ���ʹ����Ч, ������ֱ���޸�
// ������ڲ���״̬��Ӧ�ò��ᣩ������ֱ���޸�VCItem�Ĳ���
//******************************************************

// ���ñ�������
// index �������1����2
// �����¼���ļ���Ӧ����������ɺ�ɾ����ǰ��¼���ļ�:MediaInfoFree
// ���info=NULL, ��ζ��ɾ����������
extern void __stdcall vcVideoPlayerSetMusic(CVideoPlayer *player, int32_t index, MediaInfo *info);

// ��������
extern void __stdcall vcVideoPlayerSetVolume(CVideoPlayer *player, int32_t index, int32_t Volume);

/*****************************************************
¼��֧��
*****************************************************/

// ����ʾ��
// wParam:δʹ��
// lParam:������0��100
#define VC_RECORDING_SAMPLE		(VC_MESSAGE_BASE + 40)

// �Ѿ�¼�Ƶĳ���
// wParam:1/1000000�룬���ʣ�ಿ��
// lParam:�Ѿ�¼�Ƶĳ���(��)
#define VC_RECORDING_DURATION	(VC_MESSAGE_BASE + 41)

class CAudioRecorder;
// ��ʼ¼��
// ���StartTime!=0, ����ǰ����侲��
extern CAudioRecorder* __stdcall AudioRecorderCreate(HWND hwndMessage); 
// ��ȡý����Ϣ
// ���Ҫ����¼����Ӧ�ó���Ӧ��ɾ����MediaInfoFree
extern MediaInfo* __stdcall AudioRecorderGetInfo(CAudioRecorder *recorder);
// ��ͣ¼��
extern void __stdcall AudioRecorderPause(CAudioRecorder *recorder);
// ����¼��
// �������Ƶͬ��¼�ƣ���ͣ�ᵼ����Ƶ����Ƶ��ͬ����Ӧ������Seek��Ƶ
extern void __stdcall AudioRecorderResume(CAudioRecorder *recorder);
// ����
extern void __stdcall AudioRecorderDestroy(CAudioRecorder *recorder);

// ����
// ���Ⱦ���
// bMute=0������������������¼�ƹ�����Ӧ�þ���������������˷�
extern HRESULT __stdcall SpeakerMute(int32_t bMute);

/*****************************************************
��ʼת��
*****************************************************/

// ��״̬�ı��Ƿ��ʹ���Ϣ
// wParam:ָ��VCItem��ָ��
// lParam:��״̬
#define VC_ITEM_STAT_CHANGED		(VC_MESSAGE_BASE + 1)

//***************************************************
// ��ת��δ����/δȡ��֮ǰ���ý����κ���ʽ���޸ģ����Խ���ɾ����
// ����ᵼ��δ֪���
//***************************************************

// �ڿ�ʼת��֮ǰ��������������
extern void __stdcall vcReadyForConvert(); 

// ��ʼת��
// ת���Ľ�����m_Time�ж���
// ���m_Parallel != 1 ��Ӧ������ļ���ͬʱ����
//  ��ο���ϢVC_ITEM_STAT_CHANGED
//  ���ȶ����� m_Time / m_Duration
extern HRESULT __stdcall vcStartConvert(ClipInfo *item); 

// ȡ��ת����δת����ɵ��ļ����ᱻɾ��
extern void __stdcall vcAbortConvert(ClipInfo *item); 

/*****************************************************
��ʼ�ϲ�
*****************************************************/

//***************************************************
// �ںϲ�δ����/δȡ��֮ǰ���ý����κ���ʽ���޸ĺ�ɾ����
// ����ᵼ��δ֪���
//***************************************************

struct MergeInfo
{
	wchar_t				m_Name[256]; // ���ɵ��ļ�����
	wchar_t				m_OutFile[MAX_PATH]; // ����ļ�ȫ·��
	HWND				m_hwndMessage; // ���ڽ��������Ϣ�Ĵ���
	volatile int64_t	m_Time; //  ��ǰ�Ѿ���ɵ�ʱ��
	int64_t				m_Duration; //  ת�����ʱ��
};

// ����CodecOptions���ֽ�������Ӧ�õ���������������Ӧ�ó�����Ľṹ�峤�Ⱥ͵ײ㶨��Ľṹ�峤���Ƿ�һ��
extern int32_t __stdcall MergeInfo_Size();

// ����ȫ�ֱ��������ָ��
extern MergeInfo* __stdcall vcGetMergeInfo();

// �ϲ����
// wParam:û��ʹ��
// lParam:���Ϊ��0��ʾʧ��; -99��ʾ��ȡ��
#define VC_MERGE_COMPLETE	(VC_MESSAGE_BASE + 30)

// ��ʼ�ϲ�
// items:ָ��item�����飻 ClipInfo **
// count:�ϲ��ĸ�������Ӧ��С��2
// szOutputFile: ����ļ�����
// hwndMessage��������Ϣ�Ĵ���
// Time, Duration:���ڴ������, Time-��ǰ�Ѿ�����ĳ��ȣ� Duration-�ܳ���
extern HRESULT __stdcall vcStartMerge(ClipInfo *items[], int32_t count); 

// ȡ���ϲ���δת����ɵ��ļ����ᱻɾ��
extern void __stdcall vcAbortMerge(); 

/*****************************************************
��������������
*****************************************************/
// ����ý���ļ���������Ϣ
// buffer: �ַ������壬������256�ַ�
extern wchar_t * __stdcall MakeMediaInfoString(MediaInfo* info, wchar_t *buffer);

// ��ѡ���Profile����Ϣ��䵽CodecOptions��
// ��ο�Profile�Ĳ���
extern void __stdcall CopyProfileSettings();

// ����һ�ű���ͼƬ
// buffer: CodecOptions.m_VideoWidth * CodecOptions.m_VideoHeight * 4�ֽ�
extern void __stdcall DraweBackgroundSample(uint8_t *buffer);

// ����ˮӡЧ��
extern void __stdcall DrawLogoSample(BYTE *Buffer);

// CPU������
extern int32_t __stdcall GetCpuCoreCount();

/*****************************************************
��������������
*****************************************************/
extern int32_t __stdcall GetMultipleInatance(); // ���ص�ǰ���е�ʵ������
extern HWND __stdcall GetMainWindowHandle(); // ��ȡ��һ��ʵ����������
extern void __stdcall SetMainWindowHandle(HWND hwndMain); // �������ʵ����������
extern void __stdcall WriteErrorLog(char *info); // д��־

