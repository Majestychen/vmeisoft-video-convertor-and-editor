#pragma once

#define ASPECT_4x3		1
#define ASPECT_16x9		2

#define GROUP_NONE		-1
#define GROUP_HD		0
#define GROUP_VIDEO		1
#define GROUP_DEVICE	2
#define GROUP_WEB		3
#define GROUP_APP		4
#define GROUP_AUDIO		5
#define GROUP_MAX		6

#define THUMBNAIL_WIDTH		48
#define THUMBNAIL_HEIGHT	48

#define VIDEO_RES_CUSTOM	-1

// �ֱ���
struct ProfileRes
{
	int					m_Width;
	int					m_Height;
};

// ֡��
struct ProfileFrameRate
{
	int					m_Num;
	int					m_Den;
};

// ��������ѡ����
struct ProfileCodec
{
	wchar_t				m_Name[32];
	wchar_t				m_Codec[32];
};

// ��Ƶ��ѡ����
struct ProfileVideo
{
	int					m_FixedSize;
	int					m_FixedBitRate;
	int					m_Aspect;

	int					m_cCodec;
	ProfileCodec*		m_Codec;
	int					m_DefaultCodec;

	int					m_cRes;
	ProfileRes*			m_Res;
	int					m_DefaultRes;

	int					m_cFrameRate;
	ProfileFrameRate*	m_FrameRate;
	int					m_DefaultFrameRate;

	int					m_cBitRate;
	int*				m_BitRate;
	int					m_DefaultBitRate;
};

extern int __stdcall ProfileVideo_Size();

// ��Ƶ��ѡ����
struct ProfileAudio
{
	int					m_FixedFormat;
	int					m_FixedBitRate;

	int					m_cCodec;
	ProfileCodec*		m_Codec;
	int					m_DefaultCodec;

	int					m_cSampleRate;
	int*				m_SampleRate;
	int					m_DefaultSampleRate;

	int					m_cChannel;
	int*				m_Channel;
	int					m_DefaultChannel;

	int					m_cBitRate;
	int*				m_BitRate;
	int					m_DefaultBitRate;
};

extern int __stdcall ProfileAudio_Size();

// ����Ŀ������
// ��ͬ����MP4����������ͨ��Ƶ��Ҳ������רΪiPod�����Ƶĸ�ʽ
struct ProfileTarget
{
	wchar_t				m_Name[64];
	wchar_t				m_Description[128];

	ProfileVideo		m_Video;
	ProfileAudio		m_Audio;
};

extern int __stdcall ProfileTarget_Size();

// Profile ���ýṹ��
struct ProfileTag
{
	GUID				m_Id;

	wchar_t				m_Name[256];
	wchar_t				m_Description[1024];
	wchar_t				m_Format[64];
	wchar_t				m_ExtName[16];

	int					m_cTarget;
	ProfileTarget*		m_Target;

	wchar_t				m_ImageFile[MAX_PATH];
	Gdiplus::Bitmap*	m_Bitmap;
};

extern int __stdcall ProfileTag_Size();

// �����������
struct ProfileSettings
{
	GUID			m_IdProfile;

	int				m_Group;
	int				m_Profile;
	int				m_Target;

	int				m_VCodec;
	int				m_Res;
	ProfileRes		m_ResCustom;
	int				m_FrameRate;
	int				m_VBitRate;

	int				m_ACodec;
	int				m_SampleRate;
	int				m_Channel;
	int				m_ABitRate;
};

extern int __stdcall ProfileSettings_Size();

// �ڲ�ʹ��
extern int				g_cAllProfile;
extern ProfileTag*		g_AllProfile;
extern int				g_cProfiles[GROUP_MAX];
extern ProfileTag*		g_Profiles[GROUP_MAX];
extern ProfileSettings	g_ProfileSettings;
extern HRESULT __stdcall LoadProfiles();

// ��ȡĬ�ϲ���
extern void __stdcall GetDefaultProfileSetting1(ProfileSettings &Settings, int nGroup);
extern void __stdcall GetDefaultProfileSetting2(ProfileSettings &Settings, int nGroup, int nProfile);
extern void __stdcall GetDefaultProfileSetting3(ProfileSettings &Settings, int nGroup, int nProfile, int nTarget);

// ��Ϣ��ȡ
extern int __stdcall GetProfofileCount(int nGroup); // Profile Count
extern ProfileTag* __stdcall GetProfile(int nGroup, int Profile); // Get Profile
extern ProfileTarget* __stdcall GetProfileTarget(int nGroup, int Profile, int Target); // Get Target

extern int __stdcall GetProfofileCountEx(ProfileSettings &Settings); // �������û�ȡ��ǰProfileTag������
extern ProfileTag* __stdcall GetProfileEx(ProfileSettings &Settings); // �������û�ȡ��ǰProfileTag
extern ProfileTarget* __stdcall GetProfileTargetEx(ProfileSettings &Settings); // �������û�ȡ��ǰProfileTarget
extern ProfileVideo* __stdcall GetProfileVideoEx(ProfileSettings &Settings); // �������û�ȡ��ǰProfileVideo
extern ProfileAudio* __stdcall GetProfileAudioEx(ProfileSettings &Settings); // �������û�ȡ��ǰProfileAudio
extern BOOL __stdcall IsFixedVideoSizeEx(ProfileSettings &Settings); // �������û�ǰ�Ƿ�֧���Զ���ߴ�(����ߴ磬��͸߱�����16�ı���)

extern ProfileTag* __stdcall FindProfile(GUID id); // ����ID����

extern void __stdcall DrawProfileThumbnail(ProfileTarget *Profile, HDC hdc, int x, int y); // ������ͼ

extern void __stdcall SetCustomRes(ProfileSettings &Settings, int Width, int Height); // �����û��Զ���ߴ�
