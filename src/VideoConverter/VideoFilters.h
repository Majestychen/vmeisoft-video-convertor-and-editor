#pragma once
#include "VideoConverter.h"

/* ****************************************
ClipInfo = VCItem
**************************************** */
#ifndef VIDEOCONVERTER_EXPORTS
typedef VCItem ClipInfo;
#endif

/*****************************************************
 ���ȡ��Աȶ�Ч��
*****************************************************/

#define BRIGHTNESS_CONTRAST_NAME		L"Brightness Contrast"

// {D6423C0E-B608-43AF-AEE0-C2056AC17FAD}
static const GUID IID_BrightnessContrast = 
{ 0xd6423c0e, 0xb608, 0x43af, { 0xae, 0xe0, 0xc2, 0x5, 0x6a, 0xc1, 0x7f, 0xad } };

#ifndef VIDEOCONVERTER_EXPORTS
struct BrightnessContrastParams
{
	int32_t	m_Brightness;	// ����: -255~255
	int32_t	m_Contrast;		// �Աȶ�: -100~100
};
#endif

/*****************************************************
 ɫ�������Ͷȡ�����
*****************************************************/
// XP ��֧��

#define H_S_L_NAME		L"Hue Saturation Lightness"

// {D6327042-655F-4DA2-8627-E15383B20E22}
static const GUID IID_HueSaturationLightness = 
{ 0xd6327042, 0x655f, 0x4da2, { 0x86, 0x27, 0xe1, 0x53, 0x83, 0xb2, 0xe, 0x22 } };

#ifndef VIDEOCONVERTER_EXPORTS
struct HueSaturationLightnessParams
{
	int32_t m_Hue;			// ɫ�����ڣ�-180~180
	int32_t	m_Saturation;	// ���Ͷȵ��ڣ�-100~100
	int32_t	m_Lightness;	// ���ȵ��ڣ�-100~100 (����?)
};
#endif

/*****************************************************
 CROP
*****************************************************/

#define CROP_NAME		L"Crop"

// Crop ��ԭʼ��Ƶ�Ļ����Ͻ���CROP
// {747E1814-D829-4CEE-9390-2B944735FB55}
static const GUID IID_Crop = 
{ 0x747e1814, 0xd829, 0x4cee, { 0x93, 0x90, 0x2b, 0x94, 0x47, 0x35, 0xfb, 0x55 } };

#ifndef VIDEOCONVERTER_EXPORTS
struct Crop
{
	Rect m_Crop; // Crop�ķ�Χ�������Χ��ԭʼ��Ƶ��ͬ�����Ч����Ч�������Ȼ��߸߶�Ϊ0�����Ч����Ч
};
#endif

//*****************************************************
// �ر�֧��
//*****************************************************
// �����ڲ���ԭʼ��Ƶ��ʱ�����ʹ������ĺ���
// ������Ч�����й������������SetVideoEffect������CROP

// ��CROP�ı�ʱ,����Ϣ�ᷢ��������CVideoPlayerʱ����Ϣ���մ���
// wParam: X | (Width << 16); X = wParam & 0xFFFF, Width = (wParam >> 16) & 0xFFFF
// lParam: Y | (Height << 16); Y = lParam & 0xFFFF, Height = (lParam >> 16) & 0xFFFF
#define VC_VIDEO_PLAYER_CROP		(VC_MESSAGE_BASE + 20)

// ����Cropģʽ
// hwndMessage:���ڽ���Crop�ı����Ϣ�����ΪNULL���򲻸ı���Ϣ����
// crop:Crop��λ��
extern void __stdcall vcVideoPlayerCrop(CVideoPlayer *player, Rect* crop); 

// ֹͣCrop
extern void __stdcall vcVideoPlayerCropStop(CVideoPlayer *player); 

/*****************************************************
 ��ת
 *****************************************************/

#define ROTATE_FLIP_NAME		L"Rotate & Flip"

// {990E4AFB-26C4-4E41-A64D-B19025C54883}
static const GUID IID_RotateFlip = 
{ 0x990e4afb, 0x26c4, 0x4e41, { 0xa6, 0x4d, 0xb1, 0x90, 0x25, 0xc5, 0x48, 0x83 } };

#define RotateNone_FlipNone			0 // ��
#define Rotate90_FlipNone			1 // ��ת90��
#define Rotate180_FlipNone			2 // ��ת180��
#define Rotate270_FlipNone			3 // ��ת270��
#define RotateNone_FlipX			4 // ���·�ת
#define Rotate90_FlipX				5 // ��ת90�ȣ��������·�ת
#define Rotate180_FlipX				6 // ��ת180�ȣ��������·�ת
#define Rotate270_FlipX				7 // ��ת270�ȣ��������·�ת
#define RotateNone_FlipY			Rotate180_FlipX        // ���ҷ�ת
#define Rotate90_FlipY				Rotate270_FlipX		   // ��ת90�ȣ��������ҷ�ת
#define Rotate180_FlipY				RotateNone_FlipX	   // ��ת180�ȣ��������ҷ�ת
#define Rotate270_FlipY				Rotate90_FlipX		   // ��ת270�ȣ��������ҷ�ת
#define RotateNone_FlipXY			Rotate180_FlipNone	   // ���ҷ�ת���������ҷ�ת
#define Rotate90_FlipXY				Rotate270_FlipNone	   // ��ת90�ȣ��������·�ת��Ȼ�������ҷ�ת
#define Rotate180_FlipXY			RotateNone_FlipNone	   // ��ת180�ȣ��������·�ת��Ȼ�������ҷ�ת
#define Rotate270_FlipXY			Rotate90_FlipNone	   // ��ת270�ȣ��������·�ת��Ȼ�������ҷ�ת

#ifndef VIDEOCONVERTER_EXPORTS
struct RotateFlip
{
	int32_t m_RotateFlip; // ��ת�Ƕȶ��壬���Ϊ0�����Ч����Ч
};
#endif

//*****************************************************
// �ر�֧��
//*****************************************************
#define Rotate_Left					10 // ��ת90��
#define Rotate_Right				11 // ��ת-90��
#define Flip_Horizontal 			20 // ���ҷ�ת
#define Flip_Vertical				21 // ���·�ת

extern int32_t __stdcall CalcRotateFlip(int32_t Value, int32_t nRotateFlip); // ��ת��Ƶ��������ת����
extern wchar_t *__stdcall RotateFlipString(int32_t RotateFlip); // ��ȡ������Ϣ

/*****************************************************
  �ӿں���
*****************************************************/
// item:ָ��VCItem��ָ��
// id:Ч��ID
// value:Ч������ָ��
// size:��������
extern HRESULT __stdcall vcGetVideoEffect(ClipInfo *item, GUID id, void *Parameters, int32_t cbSize); // ��ȡЧ������
extern HRESULT __stdcall vcSetVideoEffect(ClipInfo *item, GUID id, void *Parameters, int32_t cbSize); // ����Ч������

// ��ȡĬ�ϲ���
extern HRESULT __stdcall vcGetVideoEffectDefaultValue(GUID id, void *Parameters, int32_t cbSize); // ����Ч������

