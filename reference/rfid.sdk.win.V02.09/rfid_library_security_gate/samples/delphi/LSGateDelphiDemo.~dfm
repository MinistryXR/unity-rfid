object MainForm: TMainForm
  Left = 515
  Top = 82
  BorderIcons = [biSystemMenu]
  BorderStyle = bsDialog
  Caption = 'Library-gate Demo(Delphi)'
  ClientHeight = 576
  ClientWidth = 787
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object NetworkGroup: TGroupBox
    Left = 24
    Top = 16
    Width = 289
    Height = 57
    Caption = 'Network parameters'
    TabOrder = 0
    object IPLabel: TLabel
      Left = 16
      Top = 24
      Width = 63
      Height = 13
      Caption = 'IP Address'#65306
    end
    object IPMaskEdit: TMaskEdit
      Left = 88
      Top = 24
      Width = 172
      Height = 21
      AutoSelect = False
      EditMask = '999.999.999.999;1; '
      MaxLength = 15
      TabOrder = 0
      Text = '   .   .   .   '
    end
  end
  object OpenBtn: TButton
    Left = 344
    Top = 32
    Width = 81
    Height = 33
    Caption = 'Open'
    TabOrder = 1
    OnClick = OpenBtnClick
  end
  object CloseBtn: TButton
    Left = 456
    Top = 32
    Width = 81
    Height = 33
    Caption = 'Close'
    TabOrder = 2
    OnClick = CloseBtnClick
  end
  object GetDevInfoBtn: TButton
    Left = 568
    Top = 32
    Width = 145
    Height = 33
    Caption = 'Get Device Information'
    TabOrder = 3
    OnClick = GetDevInfoBtnClick
  end
  object MainPageCtrl: TPageControl
    Left = 24
    Top = 88
    Width = 689
    Height = 449
    ActivePage = EventRecordPage
    TabOrder = 4
    object CommandPage: TTabSheet
      Caption = 'Command'
      object PeopleFlowGroup: TGroupBox
        Left = 16
        Top = 16
        Width = 273
        Height = 113
        Caption = 'The People Flow'
        TabOrder = 0
        object PeopleFlowIn: TLabel
          Left = 144
          Top = 40
          Width = 12
          Height = 13
          Caption = 'In:'
        end
        object PeopleFlowOut: TLabel
          Left = 144
          Top = 64
          Width = 20
          Height = 13
          Caption = 'Out:'
        end
        object PeopleFlowInNum: TLabel
          Left = 184
          Top = 40
          Width = 6
          Height = 13
          Caption = '0'
        end
        object PeopleFlowOutNum: TLabel
          Left = 184
          Top = 64
          Width = 6
          Height = 13
          Caption = '0'
        end
        object GetPeopleFlowBtn: TButton
          Left = 16
          Top = 24
          Width = 113
          Height = 33
          Caption = 'Get People Flow'
          TabOrder = 0
          OnClick = GetPeopleFlowBtnClick
        end
        object ClearPeopleFlowBtn: TButton
          Left = 16
          Top = 72
          Width = 113
          Height = 33
          Caption = 'Clear People Flow'
          TabOrder = 1
          OnClick = ClearPeopleFlowBtnClick
        end
      end
      object ReverseDirectionBtn: TButton
        Left = 312
        Top = 32
        Width = 113
        Height = 33
        Caption = 'Reverse Direction'
        TabOrder = 1
        OnClick = ReverseDirectionBtnClick
      end
      object SystemTimeGroup: TGroupBox
        Left = 16
        Top = 136
        Width = 417
        Height = 89
        Caption = 'System Time'
        TabOrder = 2
        object CurrentSystemTimeLabel: TLabel
          Left = 256
          Top = 40
          Width = 3
          Height = 13
        end
        object SetSystemTimeBtn: TButton
          Left = 16
          Top = 32
          Width = 97
          Height = 33
          Caption = 'Set System Time'
          TabOrder = 0
          OnClick = SetSystemTimeBtnClick
        end
        object GetSystemTimeBtn: TButton
          Left = 128
          Top = 32
          Width = 97
          Height = 33
          Caption = 'Get System Time'
          TabOrder = 1
          OnClick = GetSystemTimeBtnClick
        end
      end
    end
    object EventRecordPage: TTabSheet
      Caption = 'Event Record'
      ImageIndex = 1
      object EventRecordListLabel: TLabel
        Left = 24
        Top = 24
        Width = 88
        Height = 13
        Caption = 'Event Record List:'
      end
      object EventRecordErrorLabel: TLabel
        Left = 544
        Top = 136
        Width = 25
        Height = 13
        Caption = 'Error:'
      end
      object EventRecordCountLabel: TLabel
        Left = 544
        Top = 376
        Width = 6
        Height = 13
        Caption = '0'
      end
      object RecordList: TListView
        Left = 24
        Top = 48
        Width = 497
        Height = 369
        Columns = <>
        TabOrder = 0
      end
      object EventRecordStartBtn: TButton
        Left = 560
        Top = 40
        Width = 89
        Height = 25
        Caption = 'Start'
        TabOrder = 1
        OnClick = EventRecordStartBtnClick
      end
      object EventRecordStopBtn: TButton
        Left = 560
        Top = 72
        Width = 89
        Height = 25
        Caption = 'Stop'
        TabOrder = 2
        OnClick = EventRecordStopBtnClick
      end
      object EventRecordClearBtn: TButton
        Left = 560
        Top = 104
        Width = 89
        Height = 25
        Caption = 'Clear'
        TabOrder = 3
        OnClick = EventRecordClearBtnClick
      end
      object EventRecordMemo: TMemo
        Left = 544
        Top = 152
        Width = 121
        Height = 217
        Lines.Strings = (
          'EventRecordMemo')
        TabOrder = 4
      end
    end
  end
end
