{$WARN SYMBOL_PLATFORM OFF}
{$MINENUMSIZE 4}
unit SubtitleInt;

interface

uses
    Winapi.Windows, Winapi.Messages, System.Types, System.SysUtils, System.Variants, System.Classes, Vcl.Graphics, Vcl.Controls, Vcl.Forms,
    Vcl.Dialogs, Vcl.ImgList, Vcl.Menus, Vcl.StdCtrls, Vcl.ExtCtrls, Vcl.OleCtrls, SHDocVw, Vcl.ComCtrls, Vcl.Buttons,
    VideoConverterInt;

const
    // *********************************************
    // Ч������
    // *********************************************
    IID_Subtitle_None: TGUID = '{00000000-0000-0000-0000-000000000000}';
    // ���뵭��Ч��
    IID_Subtitle_Fade: TGUID = '{D7377569-F21B-4FA9-999D-B57B19B32047}';
    // �õ�ƬЧ��
    IID_Subtitle_Slide: TGUID = '{A0EF4D22-3DF0-4C8C-A6BB-674E194E1256}';

const
    SubtitleEffectIDs: Array [0 .. 2] of TGUID = (
      '{00000000-0000-0000-0000-000000000000}',
      '{D7377569-F21B-4FA9-999D-B57B19B32047}',
      '{A0EF4D22-3DF0-4C8C-A6BB-674E194E1256}'
      );

const
    // �õ�ƬЧ������
    SLIDE_DIRECTION_LEFT         = 0;
    SLIDE_DIRECTION_TOP          = 1;
    SLIDE_DIRECTION_RIGHT        = 2;
    SLIDE_DIRECTION_BOTTOM       = 3;
    SLIDE_DIRECTION_LEFT_TOP     = 4;
    SLIDE_DIRECTION_RIGHT_TOP    = 5;
    SLIDE_DIRECTION_LEFT_BOTTOM  = 6;
    SLIDE_DIRECTION_RIGHT_BOTTOM = 7;

    (* ********************************************
      // ���뷽ʽ
      ******************************************** *)
const
    SubtitleAlignmentNear   = 0;
    SubtitleAlignmentCenter = 1;
    SubtitleAlignmentFar    = 2;
    SubtitleAlignmentNone   = 3;

type
    SubtitleAlignment = Integer;

    (* ********************************************
      // ��ɫ����
      ******************************************** *)
type
    ColorRef = record
        case Integer of
            0: (Color: Integer;);
            1:
                (
                  B, G, R, A: BYTE;
                );
    end;

const
    SubtitleSpeeds: array [0 .. 2] of Int64 = (500000, 1000000, 2000000);

    (* ********************************************
      // �������壬��GdiPlus��ͬ
      ******************************************** *)
    // �������
const
    FontStyleRegular   = 0;
    FontStyleBold      = 1;
    FontStyleItalic    = 2;
    FontStyleUnderline = 4;
    FontStyleStrikeout = 8;

    (* ********************************************
      // ��Ļ����
      ******************************************** *)
const
    MAX_SUBTITLE_LINE_SIZE = 256;
    MAX_SUBTITLE_FONT_SIZE = 32;

type
    SubtitleDefault = record
        m_FontName: Array [0 .. MAX_SUBTITLE_FONT_SIZE - 1] of WideChar; // ��������
        m_FontSize: Integer;                                             // ����ߴ�
        m_FontStyle: Integer;                                            // ������
        m_FontColor: ColorRef;                                           // ������ɫ��0xAARRGGBB
        m_BorderColor: ColorRef;                                         // �߿���ɫ��0xAARRGGBB
        m_ShadowColor: ColorRef;                                         // ��Ӱ��ɫ��0xAARRGGBB

        m_Entrance: TGUID;        // ����Ч�������ΪGUID_NULL, ����Ч��
        m_EntranceParam: Integer; // ��������� SLIDE_DIRECTION_
        m_EntranceTime: Int64;    // ����ʱ����ʱ��ԽС���ٶ�Խ��
        m_EntranceOnce: BOOL;     // ͬ��һ��Ч��һ��ִ��
        m_Exit: TGUID;            // �˳�Ч�������ΪGUID_NULL, ����Ч��
        m_ExitParam: Integer;     // �˳������� SLIDE_DIRECTION_
        m_ExitTime: Int64;        // �˳�ʱ����ʱ��ԽС���ٶ�Խ��
        m_ExitOnce: BOOL;         // ͬ��һ��Ч��һ��ִ��

        m_Alignment: SubtitleAlignment; // ���뷽ʽ

        m_HPosition: SubtitleAlignment; // ˮƽλ��
        m_VPosition: SubtitleAlignment; // ��ֱλ��
        m_LineSpace: Integer;           // �м��
        m_Postion: TPoint;              // ����λ�ã����SubtitleAlignment = SubtitleAlignmentNone
    end;

    PSubtitleDefault = ^SubtitleDefault;

    CSubtitleLine = record
        m_index: Integer;
        m_Title: Array [0 .. MAX_SUBTITLE_LINE_SIZE - 1] of WideChar;

        m_FontName: Array [0 .. MAX_SUBTITLE_FONT_SIZE - 1] of WideChar; // ��������
        m_FontSize: Integer;                                             // ����ߴ�
        m_FontStyle: Integer;                                            // ������
        m_FontColor: ColorRef;                                           // ������ɫ��0xAARRGGBB
        m_BorderColor: ColorRef;                                         // �߿���ɫ��0xAARRGGBB
        m_ShadowColor: ColorRef;                                         // ��Ӱ��ɫ��0xAARRGGBB

        m_Entrance: TGUID;        // ����Ч�������ΪGUID_NULL, ����Ч��
        m_EntranceParam: Integer; // ��������� SLIDE_DIRECTION_
        m_EntranceTime: Int64;    // ����ʱ����ʱ��ԽС���ٶ�Խ��
        m_EntranceOnce: BOOL;     // ͬ��һ��Ч��һ��ִ��
        m_Exit: TGUID;            // �˳�Ч�������ΪGUID_NULL, ����Ч��
        m_ExitParam: Integer;     // �˳������� SLIDE_DIRECTION_
        m_ExitTime: Int64;        // �˳�ʱ����ʱ��ԽС���ٶ�Խ��
        m_ExitOnce: BOOL;         // ͬ��һ��Ч��һ��ִ��
        m_Alignment: SubtitleAlignment;

        // �ڲ�����
        m_EntranceStart: Int64;
        m_EntranceStop: Int64;
        m_ExitStart: Int64;
        m_ExitStop: Int64;
        m_Bounds: CRectF;
        m_Position: CPointF;
        m_PointStart: CPointF;
        m_PointStop: CPointF;

    end;

    PSubtitleLine = ^CSubtitleLine;

    (* ********************************************
      // ��Ļ
      ******************************************** *)
    CSubtitleItem = record
        m_index: Integer;                // ��ʱ������
        m_Count: Integer;                // �ı�����
        m_Lines: Array of PSubtitleLine; // Items
        m_StartTime: Int64;              // ��ʼʱ��
        m_Duration: Int64;               // ʱ��
        m_HPosition: SubtitleAlignment;  // ˮƽλ��
        m_VPosition: SubtitleAlignment;  // ��ֱλ��
        m_LineSpace: Integer;            // �м��
        m_Postion: TPoint;               // ����λ�ã����SubtitleAlignment = SubtitleAlignmentNone
    end;

    PSubtitleItem = ^CSubtitleItem;

    (* ********************************************
      // ��Ļ
      ******************************************** *)

    CSubtitle = record
        m_Count: Integer;                // ��Ļ����
        m_Items: Array of PSubtitleItem; // ��Ļ��Ŀ
        m_FrameBase: BOOL;               // �Ƿ����FRAME
    end;

    PSubtitle = ^CSubtitle;

    (* ********************************************
      // �ṹ�����
      ******************************************** *)
function SubtitleDefault_Size(): Integer; stdcall;
function CSubtitleLine_Size(): Integer; stdcall;
function CSubtitleItem_Size(): Integer; stdcall;
function CSubtitle_Size(): Integer; stdcall;
function SubtitleGetDefault(): PSubtitleDefault; stdcall;

(* ********************************************
  // �ӿں���
  ******************************************** *)
// ������Ļ�ļ�
// ���ʧ�ܷ���0���ɹ�������Ļ����Ŀ����
// �������ɹ��������ԭ�ȵ���Ļ;ʧ�ܽ�����ԭ������Ļ
function SubtitleImport(Info: Pointer; szFileName: PWideChar): PSubtitle; stdcall;

// ��ȡ��Ļ��Ϣ
function SubtitleGet(Info: Pointer): PSubtitle; stdcall;

// �����Ļ
// ���û����Ļ�ᴴ��һ���յ���Ļ
function SubtitleAddItem(subtitle: PSubtitle): PSubtitleItem; stdcall;

// �����Ļ������Ŀ
// ���û����Ļ�ᴴ��һ���յ���Ļ
function SubtitleAddLine(item: PSubtitleItem): PSubtitleLine; stdcall;

// ɾ����Ļ��Ŀ
procedure SubtitleDelete(subtitle: PSubtitle; index: Integer); stdcall;

// ɾ����ĻLine
procedure SubtitleDeleteLine(item: PSubtitleItem; index: Integer); stdcall;

// ��������޸���ʱ�䣬���밴ʱ�䣨��ʼʱ�䣩����
procedure SubtitleSort(subtitle: PSubtitle); stdcall;

(* ********************************************
  // �ӿں���������
  ******************************************** *)
const
    // ���������֮���������¼�
    // ���û��m_TransitionInFilter��m_TransitionOutFilter�����ᴥ������¼�
    // wParam:CSubtitlePlayer��ָ��
    // lParam:δ����
    CM_SUBTITLE_PLAYER_END = (WM_USER + 1);

    // ����һ��Subtitle�Ĳ��Ŵ���
function SubtitleCreatePlayer(hwndParent, hwndMessage: HWND; item: PSubtitleItem): Pointer; stdcall;

// ����
procedure SubtitlePlay(player: Pointer); stdcall;
procedure SubtitlePlayEx(player: Pointer; index: Integer; IsExitEffect: BOOL); stdcall;

// �ػ�
procedure SubtitleRedraw(player: Pointer); stdcall;

// ���ý���
procedure SubtitleSetFocus(player: Pointer; index: Integer); stdcall;

// �ͷŲ�����
procedure SubtitleDestroyPlayer(player: Pointer); stdcall;

function GetSubtitleEffectIndex(id: TGUID): Integer;
function GetSubtitleSpeedIndex(speed: Int64): Integer;

function FontStyleFromMask(mask: Integer): TFontStyles;
function FontStyleToMask(FontStyles: TFontStyles): Integer;

function SubtitleFind(szVideoFile: PWideChar): Integer; stdcall;
function SubtitleFindGetPath(index:Integer): PWideChar; stdcall;
function SubtitleFindGetName(index:Integer): PWideChar; stdcall;
procedure SubtitleFindFree(); stdcall;

implementation

uses Defines;

function SubtitleDefault_Size; external DLL_NAME name 'SubtitleDefault_Size';
function CSubtitleLine_Size; external DLL_NAME name 'CSubtitleLine_Size';
function CSubtitleItem_Size; external DLL_NAME name 'CSubtitleItem_Size';
function CSubtitle_Size; external DLL_NAME name 'CSubtitle_Size';
function SubtitleGetDefault; external DLL_NAME name 'SubtitleGetDefault';

function SubtitleImport; external DLL_NAME name 'SubtitleImport';
function SubtitleGet; external DLL_NAME name 'SubtitleGet';
function SubtitleAddItem; external DLL_NAME name 'SubtitleAddItem';
function SubtitleAddLine; external DLL_NAME name 'SubtitleAddLine';
procedure SubtitleDelete; external DLL_NAME name 'SubtitleDelete';
procedure SubtitleDeleteLine; external DLL_NAME name 'SubtitleDeleteLine';
procedure SubtitleSort; external DLL_NAME name 'SubtitleSort';

function SubtitleCreatePlayer; external DLL_NAME name 'SubtitleCreatePlayer';
procedure SubtitlePlay; external DLL_NAME name 'SubtitlePlay';
procedure SubtitlePlayEx; external DLL_NAME name 'SubtitlePlayEx';
procedure SubtitleRedraw; external DLL_NAME name 'SubtitleRedraw';
procedure SubtitleSetFocus; external DLL_NAME name 'SubtitleSetFocus';
procedure SubtitleDestroyPlayer; external DLL_NAME name 'SubtitleDestroyPlayer';
procedure SubtitleDestroyPlayerEx; external DLL_NAME name 'SubtitleDestroyPlayerEx';

function SubtitleFind; external DLL_NAME name 'SubtitleFind';
function SubtitleFindGetPath; external DLL_NAME name 'SubtitleFindGetPath';
function SubtitleFindGetName; external DLL_NAME name 'SubtitleFindGetName';
procedure SubtitleFindFree; external DLL_NAME name 'SubtitleFindFree';

function GetSubtitleEffectIndex(id: TGUID): Integer;
var
    i: Integer;
begin
    Result := -1;
    for i := 0 to 2 do
    begin
        if SubtitleEffectIDs[i] = id then
        begin
            Result := i;
            exit;
        end;
    end;
end;

function GetSubtitleSpeedIndex(speed: Int64): Integer;
var
    i: Integer;
begin
    Result := 1;
    if speed = 0 then exit;
    for i := 0 to 2 do
    begin
        if SubtitleSpeeds[i] = speed then
        begin
            Result := i;
            exit;
        end;
    end;
    if speed < SubtitleSpeeds[0] then
    begin
        Result := 0;
        exit;
    end;
    if speed > SubtitleSpeeds[2] then
    begin
        Result := 2;
        exit;
    end;
end;

function FontStyleFromMask(mask: Integer): TFontStyles;
begin
    Result := [];
    if ((mask and FontStyleBold) <> 0) then Result := Result + [fsBold];
    if ((mask and FontStyleItalic) <> 0) then Result := Result + [fsItalic];
    if ((mask and FontStyleUnderline) <> 0) then Result := Result + [fsUnderline];
    if ((mask and FontStyleStrikeout) <> 0) then Result := Result + [fsStrikeout];
end;

function FontStyleToMask(FontStyles: TFontStyles): Integer;
begin
    Result := 0;
    if fsBold in FontStyles then Result := Result or FontStyleBold;
    if fsItalic in FontStyles then Result := Result or FontStyleItalic;
    if fsUnderline in FontStyles then Result := Result or FontStyleUnderline;
    if fsStrikeout in FontStyles then Result := Result or FontStyleStrikeout;
end;

end.
