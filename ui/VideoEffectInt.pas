{$WARN SYMBOL_PLATFORM OFF}
unit VideoEffectInt;

interface

uses
    Winapi.Windows, Winapi.Messages, System.SysUtils, System.Variants, System.Classes, Vcl.Graphics, Vcl.Controls, Vcl.Forms,
    Vcl.Dialogs, Vcl.ImgList, Vcl.Menus, Vcl.StdCtrls, Vcl.ExtCtrls, Vcl.OleCtrls, SHDocVw, Vcl.ComCtrls, Vcl.Buttons,
    VideoConverterInt;

type
    PClipInfo = PVCItem;

    (* ****************************************************
      ���ȡ��Աȶ�Ч��
      **************************************************** *)

const
    BRIGHTNESS_CONTRAST_NAME = 'Brightness Contrast';

const
    // {D6423C0E-B608-43AF-AEE0-C2056AC17FAD}
    IID_BrightnessContrast: TGUID = '{D6423C0E-B608-43AF-AEE0-C2056AC17FAD}';

type
    BrightnessContrastParams = record
        m_Brightness: Int32; // ����: -255~255
        m_Contrast: Int32;   // �Աȶ�: -100~100
    end;

    (* ****************************************************
      ɫ�������Ͷȡ�����
      **************************************************** *)
    // XP ��֧��

const
    H_S_L_NAME = 'Hue Saturation Lightness';

    // {D6327042-655F-4DA2-8627-E15383B20E22}
    IID_HueSaturationLightness: TGUID = '{D6327042-655F-4DA2-8627-E15383B20E22}';

type
    HueSaturationLightnessParams = record
        m_Hue: Int32;        // ɫ�����ڣ�-180~180
        m_Saturation: Int32; // ���Ͷȵ��ڣ�-100~100
        m_Lightness: Int32;  // ���ȵ��ڣ�-100~100 (����?)
    end;

    (* ****************************************************
      CROP
      **************************************************** *)

const
    CROP_NAME = 'Crop';

    // Crop ��ԭʼ��Ƶ�Ļ����Ͻ���CROP
    // {747E1814-D829-4CEE-9390-2B944735FB55}
    IID_Crop: TGUID = '{747E1814-D829-4CEE-9390-2B944735FB55}';

    // *****************************************************
    // �ر�֧��
    // *****************************************************
    // �����ڲ���ԭʼ��Ƶ��ʱ�����ʹ������ĺ���
    // ������Ч�����й������������SetVideoEffect������CROP
    // ��CROP�ı�ʱ
    // wParam: X | (Width << 16); X = wParam & 0xFFFF, Width = (wParam >> 16) & 0xFFFF
    // lParam: Y | (Height << 16); Y = lParam & 0xFFFF, Height = (lParam >> 16) & 0xFFFF
    VC_VIDEO_PLAYER_CROP = (VC_MESSAGE_BASE + 20);

procedure vcVideoPlayerCrop(player: Pointer; var crop: CRect); stdcall;
procedure vcVideoPlayerCropStop(player: Pointer); stdcall;

(* ****************************************************
  ��ת
  **************************************************** *)
const
    ROTATE_FLIP_NAME = 'Rotate & Flip';

    // {990E4AFB-26C4-4E41-A64D-B19025C54883}
    IID_RotateFlip: TGUID = '{990E4AFB-26C4-4E41-A64D-B19025C54883}';

    RotateNone_FlipNone = 0;                   // ��
    Rotate90_FlipNone   = 1;                   // ��ת90��
    Rotate180_FlipNone  = 2;                   // ��ת180��
    Rotate270_FlipNone  = 3;                   // ��ת270��
    RotateNone_FlipX    = 4;                   // ���·�ת
    Rotate90_FlipX      = 5;                   // ��ת90�ȣ��������·�ת
    Rotate180_FlipX     = 6;                   // ��ת180�ȣ��������·�ת
    Rotate270_FlipX     = 7;                   // ��ת270�ȣ��������·�ת
    RotateNone_FlipY    = Rotate180_FlipX;     // ���ҷ�ת
    Rotate90_FlipY      = Rotate270_FlipX;     // ��ת90�ȣ��������ҷ�ת
    Rotate180_FlipY     = RotateNone_FlipX;    // ��ת180�ȣ��������ҷ�ת
    Rotate270_FlipY     = Rotate90_FlipX;      // ��ת270�ȣ��������ҷ�ת
    RotateNone_FlipXY   = Rotate180_FlipNone;  // ���ҷ�ת���������ҷ�ת
    Rotate90_FlipXY     = Rotate270_FlipNone;  // ��ת90�ȣ��������·�ת��Ȼ�������ҷ�ת
    Rotate180_FlipXY    = RotateNone_FlipNone; // ��ת180�ȣ��������·�ת��Ȼ�������ҷ�ת
    Rotate270_FlipXY    = Rotate90_FlipNone;   // ��ת270�ȣ��������·�ת��Ȼ�������ҷ�ת

    // *****************************************************
    // �ر�֧��
    // *****************************************************
    Rotate_Left     = 10; // ��ת90��
    Rotate_Right    = 11; // ��ת-90��
    Flip_Horizontal = 20; // ���ҷ�ת
    Flip_Vertical   = 21; // ���·�ת

function CalcRotateFlip(value, nRotateFlip: Integer): Integer; stdcall; // ��ת��Ƶ��������ת����
function RotateFlipString(nRotateFlip: Integer): PWideChar; stdcall;    // ��ȡ������Ϣ

(* ****************************************************
  �ӿں���
  **************************************************** *)
// item:ָ��VCItem��ָ��
// id:Ч��ID
// value:Ч������ָ��
// size:��������
function vcGetVideoEffect(item: PClipInfo; id: TGUID; Parameters: Pointer; cbSize: Integer): HRESULT; stdcall; // ��ȡЧ������
function vcSetVideoEffect(item: PClipInfo; id: TGUID; Parameters: Pointer; cbSize: Integer): HRESULT; stdcall; // ����Ч������

// ��ȡĬ�ϲ���
function vcGetVideoEffectDefaultValue(id: TGUID; Parameters: Pointer; cbSize: Integer): HRESULT; stdcall; // ����Ч������

implementation

uses Defines;

procedure vcVideoPlayerCrop; external DLL_NAME name 'vcVideoPlayerCrop';
procedure vcVideoPlayerCropStop; external DLL_NAME name 'vcVideoPlayerCropStop';

function CalcRotateFlip; external DLL_NAME name 'CalcRotateFlip';
function RotateFlipString; external DLL_NAME name 'RotateFlipString';

function vcGetVideoEffect; external DLL_NAME name 'vcGetVideoEffect';
function vcSetVideoEffect; external DLL_NAME name 'vcSetVideoEffect';
function vcGetVideoEffectDefaultValue; external DLL_NAME name 'vcGetVideoEffectDefaultValue';

end.
