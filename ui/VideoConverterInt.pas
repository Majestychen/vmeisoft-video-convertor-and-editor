{$WARN SYMBOL_PLATFORM OFF}
{$MINENUMSIZE 4}
unit VideoConverterInt;

interface

uses
    Winapi.Windows, Winapi.Messages, System.SysUtils, System.Variants, System.Classes, Vcl.Graphics, Vcl.Controls, Vcl.Forms,
    Vcl.Dialogs, Vcl.ImgList, Vcl.Menus, Vcl.StdCtrls, Vcl.ExtCtrls, Vcl.OleCtrls, SHDocVw, Vcl.ComCtrls, Vcl.Buttons;

function VCGlobal_Size(): Integer; stdcall;
function MediaInfo_Size(): Integer; stdcall;
function VCItem_Size(): Integer; stdcall;

const
    VC_MESSAGE_BASE = (WM_USER + 256);

    (* ****************************************************
      ʱ�䶨�壺1/1000000��
      **************************************************** *)
const
    AV_TIME_BASE_LL: Int64 = 1000000;

type
    CPoint = Record
        X, Y: Integer;
    end;

    CSize = Record
        Width, Height: Integer;
    end;

    CRect = Record
        X, Y, Width, Height: Integer;
    end;

    CPointF = Record
        X, Y: Single;
    end;

    CSizeF = Record
        Width, Height: Single;
    end;

    CRectF = Record
        X, Y, Width, Height: Single;
    end;

    (* ****************************************************
      // Resize Method
      **************************************************** *)
const
    ResizeMethod_LetterBox = 0; // 0
    ResizeMethod_Crop      = 1; // 1
    ResizeMethod_Center    = 2; // 2
    ResizeMethod_Fill      = 3; // 3

    (* ***************************************************
      ��������
      *************************************************** *)
const
    FillType_Solid    = 0;
    FillType_Gradient = 1;
    FillType_Picture  = 2;

    (* ****************************************************
      ��䷽��
      **************************************************** *)
const
    FillDirect_Top      = 0;
    FillDirect_Left     = 1;
    FillDirect_TopLeft  = 2;
    FillDirect_TopRight = 3;

    (* ****************************************************
      ͼƬ����
      **************************************************** *)
const
    GrabFileType_PNG = 0;
    GrabFileType_JPG = 1;
    GrabFileType_BMP = 2;

    (* ****************************************************
      ˮӡ���뷽ʽ
      **************************************************** *)
const
    LogoAlignmentNear   = 0; // ���λ�ã���ߣ��ϱ�
    LogoAlignmentCenter = 1; // ����
    LogoAlignmentFar    = 2; // ��Զλ�ã��ұߣ��±�
    LogoAlignmentNone   = 3; // ����

    (* ****************************************************
      ȫ�ֵĲ�����ϵͳ������Ϣ����
      **************************************************** *)
type
    TFilePath = Array [0 .. MAX_PATH - 1] of WideChar;

    VCGlobal = record

        // Ĭ�����·��
        m_OutputPath: TFilePath;

        // ����ת��������
        m_Parallel: Int32;

        // ���췽ʽ����
        m_ResizeMethod: Integer;

        // ������Ĭ��Ϊ��ɫ����
        m_FillType: Integer;      // �����������
        m_FillColor1: Int32;      // ����ɫ1
        m_FillColor2: Int32;      // ����ɫ2
        m_FillDirect: Integer;    // ����ɫ��䷽��
        m_FillPicture: TFilePath; // ͼƬ��·����������ΪͼƬʱ��Ч

        // ͼ��ץȡʱ��Ĭ�ϸ�ʽ
        m_GrabFileType: Integer;

        // (����) ˮӡ
        m_LogoFile: TFilePath; // ˮӡ�ļ�����:���Ϊ����������ö�����
        m_LogoFileSize: CSize; // ԭʼͼƬ�ߴ�
        m_LogoRect: CRect;     // ˮӡ�ļ���λ��
        m_LogoAlpha: Int32;    // ˮӡ�ļ���͸���ȣ�0-��͸����100-ȫ͸����ȡֵ��1��99֮�䣬����ֵ��Ϊ��͸������
        m_LogoHPosition: Int32;
        m_LogoVPosition: Int32;

    end;

    PVCGlobal = ^VCGlobal;

    // ����ȫ�ֲ�����ָ��
function vcGetGlobal(): PVCGlobal; stdcall;

(* ****************************************************
  ���������ȫ��
  **************************************************** *)
type
    CodecOptions = record

        m_Format: array [0 .. 63] of WideChar;  // ����ļ���ʽ: �������
        m_Target: array [0 .. 63] of WideChar;  // ����
        m_ExtName: array [0 .. 63] of WideChar; // ��չ���ƺ�׺

        m_VideoCodec: array [0 .. 63] of WideChar; // ��Ƶ����������
        m_VideoBitrate: Int32;                     // �����ı����ʣ����Ϊ0����ΪVBR
        m_FrameNum, m_FrameDen: Integer;           // ������֡��
        m_VideoWidth, m_VideoHeight: Integer;      // ��Ƶ�Ŀ�͸�
        m_VideoDisable: Int32;                     // ��������Ƶ����������Ƶ

        m_AudioCodec: array [0 .. 63] of WideChar; // ��Ƶ����������
        m_AudioBitrate: Int32;                     // �����ı����ʣ����Ϊ0����ΪVBR
        m_AudioSampleRate: Int32;                  // �����Ĳ�����
        m_AudioChannels: Int32;                    // ������ͨ������
        m_AudioDisable: Int32;                     // ��������Ƶ����������Ƶ

        m_Pause: BOOL;
    end;

    PCodecOptions = ^CodecOptions;

    // ����CodecOptions���ֽ�������Ӧ�õ���������������Ӧ�ó�����Ľṹ�峤�Ⱥ͵ײ㶨��Ľṹ�峤���Ƿ�һ��
function CodecOptions_Size(): Integer; stdcall;

// ����ȫ�ֱ��������ָ��
function vcGetCodecOptions(): PCodecOptions; stdcall;

(* ****************************************************
  ý����Ϣ����
  **************************************************** *)
const

    MediaStat_None                = 0;  //
    MediaStat_Importing           = 10; // ���ڵ���ý����Ϣ
    MediaStat_Error_File          = 11; // ����ý����Ϣ����
    MediaStat_Check_Media         = 12; // �Ѿ��ɹ���ȡý����Ϣ�����ڼ��ý���ļ���Ӧ���������
    MediaStat_Thumbnail_Generated = 13; // �Ѿ��ɹ���������ͼ
    MediaStat_Complete            = 14; // ���

type
    MediaInfo = record

        m_ID: TGUID;     // Ψһ��ʶ
        m_Status: Int32; //

        m_szFileName: TFilePath; // �ļ�·��

        m_Duration: Int64;                             // ����
        m_StreamDuration: Int64;                       // ������
        m_FormtDesc: array [0 .. 128 - 1] of WideChar; // �ļ���ʽ

        m_bVideoStream: Int32;                          // �Ƿ������Ƶ
        m_VideoCodec: array [0 .. 128 - 1] of WideChar; // ��Ƶ����������
        m_VideoStartPts: Int64;                         // * �ڲ�����
        m_Width: Int32;                                 // ��Ƶ��
        m_Height: Int32;                                // ��Ƶ��
        m_CodecWidth: Int32;                            // ��Ƶ��
        m_CodecHeight: Int32;                           // ��Ƶ��
        m_FrameRateNum: Int32;                          // ֡��
        m_FrameRateDen: Int32;                          // ֡��
        m_PixelFormat: Int32;                           // * �ڲ�����
        m_VideoBitrate: Integer;                        // ��Ƶ������
        m_VideoDuration: Int64;                         // ��Ƶ����

        m_bAudioStream: Int32;                          // �Ƿ������Ƶ
        m_AudioCodec: array [0 .. 128 - 1] of WideChar; // ��Ƶ����������
        m_AudioStartPts: Int64;                         // *(�ڲ�ʹ��) ��Ƶ��ʼʱ��
        m_SampleRate: Int32;                            // ��Ƶ����
        m_nChannel: Int32;                              // ��Ƶͨ������
        m_channel_layout: Int64;                        // * �ڲ�����
        m_SampleFormat: Int32;                          // * �ڲ�����
        m_AudioBitrate: Integer;                        // ��Ƶ������
        m_AudioDuration: Int64;                         // ��Ƶ����
        m_IsPlanar: Int32;                              // �ڲ�����

        // ����
        m_Demo: TFilePath; // ʾ��ͼ:BMP

        // �ļ���Ϣ
        m_ftCreationTime: FILETIME;  // ����ʱ��
        m_liFileSize: LARGE_INTEGER; // �ļ���С
        m_History: FILETIME;         // ��Ϣ����ʱ��

        // �ڲ�����
        m_AudioTmpFile: array [0 .. 7] of TFilePath;
        m_AudioLength: Int64;

    end;

    PMediaInfo = ^MediaInfo;

    (* ****************************************************
      ת����Ŀ����
      **************************************************** *)
const
    // ״̬
    ClipStat_None              = 0;  //
    ClipStat_Ready_For_Convert = 20; // һ��״̬
    ClipStat_Wait_For_Convert  = 21; // �ȴ�ת��������
    ClipStat_Start_Convert     = 22; // ��ʼת��
    ClipStat_Converting        = 23; // ����ת����Ӧ���������
    ClipStat_Converted         = 24; // ת��������
    ClipStat_Failed            = 25; // ת��ʧ�ܣ�
    ClipStat_Abort             = 26; // ת����ȡ����

type
    AudioTrack = record
        m_Media: PMediaInfo; // ý����Ϣ
        m_MediaStart: Int64; // ��ʼʱ�䣺ý�����
        m_MediaStop: Int64;  // ����ʱ�䣺ý����У����Ϊ0��ʾֱ������
        m_Start: Int64;      // ��ʼʱ�䣺�������Ƶ
        m_Stop: Int64;       // ����ʱ�䣺�������Ƶ
        m_Volume: Int32;     // �������ã�1-150; <100:���������� 100:ԭʼ������ >100�Ŵ����������ܻᵼ�����⣩
    end;

    PAudioTrack = ^AudioTrack;

    VCItem = record

        m_ID: TGUID;
        m_Name: Array [0 .. 255] of WideChar;
        m_OutFile: TFilePath; // ����ļ�·��

        m_MediaInfo: PMediaInfo;
        m_AudioTrack: Array [0 .. 2] of AudioTrack;

        // Clip / Trim
        m_ClipStart: Int64; // ��ʼʱ��
        m_ClipStop: Int64;  // ����ʱ�䣬���Ϊ0��ʾ���ŵ���β

        // Speed
        m_Speed: Int32; // 0-ԭʼ�ٶȲ��ţ� >0: ����1/100���ٶȣ���100Ϊ�������ٶȣ� <0; ����1/100���ٶȣ���-50Ϊ1/2���ٶȣ�����<=100

        // ��Ϣ����
        m_Status: Int32;     // Item��״̬
        m_hwndMessage: HWND; // ���ڽ���״̬�ı����Ϣ�Ĵ���
        m_Time: Int64;       // �������
        m_Duration: Int64;   // ��������
        m_UserData: Pointer; // �û��Զ������ݣ����Դ���κ�����

    end;

    PVCItem = ^VCItem;
    (* ****************************************************
      ��Ϣ����
      **************************************************** *)

    // ����״̬�ı�
    // wParam:ָ��VCItem��ָ��
    // lParam:��״̬
const
    VC_ITEM_STAT_CHANGED = (VC_MESSAGE_BASE + 1);

    (* ****************************************************
      ��ʼ��
      **************************************************** *)
function vcInitialize(): HRESULT; stdcall; // ������������֮ǰ�������Ӧ�ñ�����
procedure vcUninitialize(); stdcall;       // Ӧ�ó����˳�֮ǰӦ�ñ�����

(* ****************************************************
  ����ý��
  **************************************************** *)

// ����״̬�����ı�
// wParam:û��ʹ��
// lParam:״̬��MediaStat
const
    VC_IMPORT_STATUS = (VC_MESSAGE_BASE + 1);

    // ������
    // hwndMessage:������Ϣ�Ĵ��ڣ���Ϣ�ο�ǰ��Ķ���
    // szFile:�ļ�·��
    // ������
    // �ú����������أ����Զ��ͬʱ�������ļ��� ��̨���е��롣
    // ��ο���ϢVC_ITEM_STAT_CHANGED
    // ���ȶ����� m_Time / m_Duration
function vcImportMediaInfo(hwndMessage: HWND; szFile: PWideChar): PMediaInfo; stdcall;

// ��ֹ����
procedure vcImportAbort(info: PMediaInfo); stdcall;

// ��ȡ����
// ���ذٷֱ�
function vcImportGetProgress(info: PMediaInfo): Int32; stdcall;

(* ****************************************************
  ��ITEM�Ĳ���
  **************************************************** *)

function vcCreateItem(hwndMessage: HWND; info: PMediaInfo): PVCItem; stdcall;
procedure vcDeleteItem(item: PVCItem); stdcall; // ɾ����ɾ�����������ı�

(* ****************************************************
  ��Ƶ����
  **************************************************** *)
const
    // ���Ž����¼�
    // wParam:Item
    // lParam:��ǰ���ȣ���λΪ��
    VC_VIDEO_RENDER_PROGRESS = (VC_MESSAGE_BASE + 10);

    // ��������¼�
    // wParam:Item
    // lParam:δ����
    VC_VIDEO_RENDER_END = (VC_MESSAGE_BASE + 11);

    // ����ģʽ����
type
    VideoPlayerMode =
      (
      VC_VIDEO_RENDER_MODE_SOURCE, // ����ԭʼ����Ƶ
      VC_VIDEO_RENDER_MODE_DEST    // ����ת�����Ч��
      );

    // ����
    // �Զ�����
function vcCreateVideoPlayer(hwndParent, hwndMessage: HWND; item: Pointer; Mode: VideoPlayerMode): Pointer; stdcall;

// ���浱ǰͼ���ļ�:�ļ���ʽ������m_GrabFileType
function vcVideoPlayerGrab(player: Pointer; szFile: PWideChar): HRESULT; stdcall;

// ���ٲ��Ŵ���
procedure vcVideoPlayerDestroy(player: Pointer); stdcall;

// ���µ������Ŵ���
// �첽ִ��
procedure vcVideoPlayerResize(player: Pointer); stdcall;

// ���ÿ�ʼʱ��ͽ���ʱ��
// ��������ԭʼ��Ƶʱ��Ч
procedure vcVideoPlayerStartStop(player: Pointer; start, stop: Int64); stdcall;

// ��������ͣ
// ������ŵ���β��vcVideoPlayerResume����ͷ��ʼ����
// �첽ִ��
procedure vcVideoPlayerResume(player: Pointer); stdcall;
procedure vcVideoPlayerPause(player: Pointer); stdcall;

// Seek
// vcVideoPlayerSeekStart / vcVideoPlayerSeekStop: ���ڿ��������Ĳ��ŵ��Ż������ֻ��һ���Ե�SEEK�����ֱ�ӵ���vcVideoPlayerSeekTo
// Seek֮������ͣ״̬
// �첽ִ��
procedure vcVideoPlayerSeekTo(player: Pointer; pts: Int64); stdcall;
function vcVideoPlayerCurrentTime(player: Pointer): Int64; stdcall;

// ʹ�����к���Ӧ������ͣ
procedure vcVideoPlayerNextFrame(player: Pointer); stdcall; // ��һ֡
procedure vcVideoPlayerPreTime(player: Pointer); stdcall;   // ��һ��
procedure vcVideoPlayerNextTime(player: Pointer); stdcall;  // ��һ��

procedure vcVideoPlayerForceRedraw(player: Pointer); stdcall;

// *****************************************************
// ��Ƶ������
// �������������Ǳ����������ĺ���ʹ����Ч, ������ֱ���޸�
// ������ڲ���״̬��Ӧ�ò��ᣩ������ֱ���޸�VCItem�Ĳ���
// ******************************************************

// ���ñ�������
// index �������1����2
// �����¼���ļ���Ӧ����������ɺ�ɾ����ǰ��¼���ļ�:MediaInfoFree
// ���info=NULL, ��ζ��ɾ����������
procedure vcVideoPlayerSetMusic(player: Pointer; index: Int32; info: PMediaInfo); stdcall;

// ��������
procedure vcVideoPlayerSetVolume(player: Pointer; index: Int32; Volume: Int32); stdcall;

(* ****************************************************
  ��ʼת��
  **************************************************** *)

procedure vcReadyForConvert(); stdcall;

// ��ʼת��
// ת���Ľ�����m_ConvertTime�ж���
// ���m_Parallel != 1 �����ļ���ͬʱ����
// ת��δ����֮ǰ�������޸��κβ���
// ��ο���ϢVC_ITEM_STAT_CHANGED
// ���ȶ����� m_Time / m_Duration
function vcStartConvert(item: PVCItem): HRESULT; stdcall;

// ȡ��ת����δת����ɵ��ļ����ᱻɾ��
procedure vcAbortConvert(item: PVCItem); stdcall;

(* ****************************************************
  ��ʼ�ϲ�
  **************************************************** *)

type
    MergeInfo = record
        m_Name: Array [0 .. 255] of WideChar; // ���ɵ��ļ�����
        m_OutFile: TFilePath;                 // ����ļ�ȫ·��
        m_hwndMessage: HWND;                  // ���ڽ���״̬�ı����Ϣ�Ĵ���
        m_Time: Int64;                        // ��ǰ�Ѿ���ɵ�ʱ��
        m_Duration: Int64;                    // ת�����ʱ��
    end;

    PMergeInfo = ^MergeInfo;

const
    // �ϲ����
    // wParam:ָ��VCItem��ָ��
    // lParam:���Ϊ��0��ʾʧ��
    VC_MERGE_COMPLETE = (VC_MESSAGE_BASE + 30);

function MergeInfo_Size(): Integer; stdcall;
function vcGetMergeInfo(): PMergeInfo; stdcall;

// ��ʼ�ϲ�
function vcStartMerge(var item: PVCItem; Count: Integer): HRESULT; stdcall;

// ȡ���ϲ���δת����ɵ��ļ����ᱻɾ��
procedure vcAbortMerge(); stdcall;

// ��������
function MakeMediaInfoString(info: PMediaInfo; var buffer: array of WideChar): PWideChar; stdcall;
function GetMediaString(info: PMediaInfo): String;
procedure CopyProfileSettings(); stdcall;
function GetCpuCoreCount(): Integer; stdcall;
procedure DraweBackgroundSample(buffer: PBYTE); stdcall;
procedure DrawLogoSample(buffer: PBYTE); stdcall;
procedure DrawResizeSample(buffer: PBYTE; item: PVCItem); stdcall;

procedure CreateHSBControl(hwndParent, hwndMessage: HWND; uiMessage: UINT; Color: DWORD); stdcall;
procedure CreateHSBControlEx(hwndParent, hwndMessage: HWND; uiMessage: UINT; Color: DWORD; xPos, yPos: Integer); stdcall;

(* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  ¼��֧��
  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *)
const
    // ����ʾ��
    // wParam:δʹ��
    // lParam:������0��100
    VC_RECORDING_SAMPLE = (VC_MESSAGE_BASE + 40);

    // �Ѿ�¼�Ƶĳ���
    // wParam:1/1000000�룬���ʣ�ಿ��
    // lParam:�Ѿ�¼�Ƶĳ���(��)
    VC_RECORDING_DURATION = (VC_MESSAGE_BASE + 41);

    // ��ʼ¼��
    // ���StartTime!=0, ����ǰ����侲��
function AudioRecorderCreate(hwndMessage: HWND): Pointer; stdcall;

// ��ȡý����Ϣ
// ���Ҫ����¼����Ӧ�ó���Ӧ��ɾ����MediaInfoFree
function AudioRecorderGetInfo(recorder: Pointer): PMediaInfo; stdcall;

// ��ͣ¼��
procedure AudioRecorderPause(recorder: Pointer); stdcall;

// ����¼��
// �������Ƶͬ��¼�ƣ���ͣ�ᵼ����Ƶ����Ƶ��ͬ����Ӧ������Seek��Ƶ
procedure AudioRecorderResume(recorder: Pointer); stdcall;

// ����
procedure AudioRecorderDestroy(recorder: Pointer); stdcall;

// ����
// ���Ⱦ���
// bMute=0������������������¼�ƹ�����Ӧ�þ���������������˷�
function SpeakerMute(bMute: Int32): HRESULT; stdcall;

implementation

uses Defines;

function VCGlobal_Size; external DLL_NAME name 'VCGlobal_Size';
function CodecOptions_Size; external DLL_NAME name 'CodecOptions_Size';
function MediaInfo_Size; external DLL_NAME name 'MediaInfo_Size';
function VCItem_Size; external DLL_NAME name 'VCItem_Size';

function vcGetGlobal; external DLL_NAME name 'vcGetGlobal';
function vcGetCodecOptions; external DLL_NAME name 'vcGetCodecOptions';

function vcInitialize; external DLL_NAME name 'vcInitialize';
procedure vcUninitialize; external DLL_NAME name 'vcUninitialize';

function vcImportMediaInfo; external DLL_NAME name 'vcImportMediaInfo';
procedure vcImportAbort; external DLL_NAME name 'vcImportAbort';
function vcImportGetProgress; external DLL_NAME name 'vcImportGetProgress';

function vcCreateItem; external DLL_NAME name 'vcCreateItem';
procedure vcDeleteItem; external DLL_NAME name 'vcDeleteItem';

function vcCreateVideoPlayer; external DLL_NAME name 'vcCreateVideoPlayer';
function vcVideoPlayerGrab; external DLL_NAME name 'vcVideoPlayerGrab';
procedure vcVideoPlayerDestroy; external DLL_NAME name 'vcVideoPlayerDestroy';
procedure vcVideoPlayerResize; external DLL_NAME name 'vcVideoPlayerResize';
procedure vcVideoPlayerStartStop; external DLL_NAME name 'vcVideoPlayerStartStop';
procedure vcVideoPlayerResume; external DLL_NAME name 'vcVideoPlayerResume';
procedure vcVideoPlayerPause; external DLL_NAME name 'vcVideoPlayerPause';
procedure vcVideoPlayerSeekStart; external DLL_NAME name 'vcVideoPlayerSeekStart';
procedure vcVideoPlayerSeekStop; external DLL_NAME name 'vcVideoPlayerSeekStop';
procedure vcVideoPlayerSeekTo; external DLL_NAME name 'vcVideoPlayerSeekTo';
procedure vcVideoPlayerNextFrame; external DLL_NAME name 'vcVideoPlayerNextFrame';
procedure vcVideoPlayerPreTime; external DLL_NAME name 'vcVideoPlayerPreTime';
procedure vcVideoPlayerNextTime; external DLL_NAME name 'vcVideoPlayerNextTime';
function vcVideoPlayerCurrentTime; external DLL_NAME name 'vcVideoPlayerCurrentTime';
procedure vcVideoPlayerForceRedraw; external DLL_NAME name 'vcVideoPlayerForceRedraw';

procedure vcVideoPlayerSetMusic; external DLL_NAME name 'vcVideoPlayerSetMusic';
procedure vcVideoPlayerSetVolume; external DLL_NAME name 'vcVideoPlayerSetVolume';

procedure vcReadyForConvert; external DLL_NAME name 'vcReadyForConvert';
function vcStartConvert; external DLL_NAME name 'vcStartConvert';
procedure vcAbortConvert; external DLL_NAME name 'vcAbortConvert';

function MergeInfo_Size; external DLL_NAME name 'MergeInfo_Size';
function vcGetMergeInfo; external DLL_NAME name 'vcGetMergeInfo';
function vcStartMerge; external DLL_NAME name 'vcStartMerge';
procedure vcAbortMerge; external DLL_NAME name 'vcAbortMerge';

function MakeMediaInfoString; external DLL_NAME name 'MakeMediaInfoString';
procedure CopyProfileSettings; external DLL_NAME name 'CopyProfileSettings';
function GetCpuCoreCount; external DLL_NAME name 'GetCpuCoreCount';
procedure DraweBackgroundSample; external DLL_NAME name 'DraweBackgroundSample';
procedure DrawLogoSample; external DLL_NAME name 'DrawLogoSample';
procedure DrawResizeSample; external DLL_NAME name 'DrawResizeSample';

procedure CreateHSBControl; external DLL_NAME name 'CreateHSBControl';
procedure CreateHSBControlEx; external DLL_NAME name 'CreateHSBControlEx';

function AudioRecorderCreate; external DLL_NAME name 'AudioRecorderCreate';
function AudioRecorderGetInfo; external DLL_NAME name 'AudioRecorderGetInfo';
procedure AudioRecorderPause; external DLL_NAME name 'AudioRecorderPause';
procedure AudioRecorderResume; external DLL_NAME name 'AudioRecorderResume';
procedure AudioRecorderDestroy; external DLL_NAME name 'AudioRecorderDestroy';
function SpeakerMute; external DLL_NAME name 'SpeakerMute';

function GetMediaString(info: PMediaInfo): String;
var
    buffer: Array [0 .. 1024 - 1] of WideChar;
begin
    Result := MakeMediaInfoString(info, buffer);
end;

end.
