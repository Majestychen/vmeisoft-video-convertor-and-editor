#include "stdafx.h"
#include "VideoConverter.h"
#include "SubtitleInt.h"
#include "Subtitle.h"
#include "SubtitleReader.h"

SubtitleDefault g_subtitle_default = 
{
	L"Arial", //m_FontName[32];		// ��������
	24, //m_FontSize; // ����ߴ�
	FontStyleBold, //m_FontStyle; // ������
	0xFFFFFFFF,//m_FontColor; // ������ɫ��0xAARRGGBB
	0xFF000000,//m_BorderColor; // �߿���ɫ��0xAARRGGBB
	0x60808080, // ��Ӱ��ɫ��0xAARRGGBB
	
	{}, //m_Entrance; // ����Ч�������ΪGUID_NULL, ����Ч��
	0, //m_EntranceParam; // ��������� SLIDE_DIRECTION_
	AV_TIME_BASE_LL, //m_EntranceTime;	// ����ʱ����ʱ��ԽС���ٶ�Խ��
	FALSE, // ͬ��һ��Ч��һ��ִ��
	
	{}, //m_Exit; // �˳�Ч�������ΪGUID_NULL, ����Ч��
	0, //m_ExitParam; // �˳������� SLIDE_DIRECTION_
	AV_TIME_BASE_LL, //m_ExitTime; // �˳�ʱ����ʱ��ԽС���ٶ�Խ��
	FALSE, // ͬ��һ��Ч��һ��ִ��

    SubtitleAlignmentCenter,// m_Alignment; // ���뷽ʽ�����У��ұ�

	SubtitleAlignmentCenter,//m_HPosition; // ˮƽλ��
	SubtitleAlignmentFar,//m_VPosition; // ��ֱλ��
	0,//m_LineSpace; // �м��
	Point()//m_Postion; // ����λ�ã����SubtitleAlignment = SubtitleAlignmentNone
};

int32_t __stdcall CSubtitleLine_Size()
{
	return sizeof(CSubtitleLine);
}

int32_t __stdcall CSubtitleItem_Size()
{
	return sizeof(CSubtitleItem);
}

int32_t __stdcall CSubtitle_Size()
{
	return sizeof(CSubtitle);
}

int32_t _stdcall SubtitleDefault_Size()
{
	return sizeof(SubtitleDefault);
}

SubtitleDefault* SubtitleGetDefault()
{
	return &g_subtitle_default;
}

CSubtitle*__stdcall SubtitleImport(ClipInfo *Info, wchar_t *szFileName)
{
	CSubtitle *subtitle = LoadTextSubtitle(szFileName);
	if (subtitle == NULL) return NULL;
	Info->SetSubtitle(subtitle);
	return subtitle;
}

CSubtitle* __stdcall SubtitleGet(ClipInfo *Info)
{
	return Info->GetSubtitle();
}

CSubtitleItem* __stdcall SubtitleAddItem(CSubtitle *subtitle)
{
	return subtitle->NewItem();
}

CSubtitleLine* __stdcall SubtitleAddLine(CSubtitleItem *item)
{
	return item->NewLine();
}

void __stdcall SubtitleDelete(CSubtitle *subtitle, int32_t index)
{
	subtitle->DeleteItem(index);
}

void __stdcall SubtitleDeleteLine(CSubtitleItem *item, int32_t index)
{
	item->DeleteLine(index);
}

void __stdcall SubtitleSort(CSubtitle *subtitle)
{
	subtitle->SortItem();
}

CSubtitlePlayer* __stdcall SubtitleCreatePlayer(HWND hwndParent, HWND hwndMessage, CSubtitleItem *subtitle)
{
	CSubtitlePlayer *player = new CSubtitlePlayer(hwndParent, hwndMessage, subtitle);
	if (player->Initialize() != S_OK)
	{
		delete player;
		return NULL;
	}
	else
	{
		return player;
	}
}

void __stdcall SubtitlePlay(CSubtitlePlayer* player)
{
	player->Play();
}

void __stdcall SubtitlePlayEx(CSubtitlePlayer* player, int32_t index, BOOL IsExitEffect)
{
	player->PlayEx(index, IsExitEffect);
}

void __stdcall SubtitleRedraw(CSubtitlePlayer* player)
{
	player->Redraw();
}

void __stdcall SubtitleSetFocus(CSubtitlePlayer* player, int32_t index)
{
	player->SetFocus(index);
}

void __stdcall SubtitleDestroyPlayer(CSubtitlePlayer* player)
{
	delete player;
}
