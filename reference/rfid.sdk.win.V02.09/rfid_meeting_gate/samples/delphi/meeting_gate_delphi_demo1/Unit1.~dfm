object Form1: TForm1
  Left = 325
  Top = 84
  Width = 658
  Height = 681
  Caption = 'Form1'
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
  object GroupBox1: TGroupBox
    Left = 8
    Top = 8
    Width = 481
    Height = 209
    TabOrder = 0
    object Label1: TLabel
      Left = 29
      Top = 26
      Width = 60
      Height = 13
      AutoSize = False
      Caption = 'Gate Type:'
    end
    object Label11: TLabel
      Left = 288
      Top = 28
      Width = 63
      Height = 13
      Caption = 'COMM Type:'
    end
    object GroupBox2: TGroupBox
      Left = 16
      Top = 64
      Width = 225
      Height = 129
      Caption = 'Serial parameter'
      TabOrder = 0
      object Label2: TLabel
        Left = 35
        Top = 25
        Width = 46
        Height = 13
        AutoSize = False
        Caption = 'Name:'
      end
      object Label12: TLabel
        Left = 19
        Top = 59
        Width = 54
        Height = 13
        Caption = 'Baud Rate:'
      end
      object Label13: TLabel
        Left = 32
        Top = 88
        Width = 32
        Height = 13
        Caption = 'Frame:'
      end
      object ComboBox2: TComboBox
        Left = 80
        Top = 24
        Width = 105
        Height = 21
        Style = csDropDownList
        ItemHeight = 13
        TabOrder = 0
      end
      object ComboBox7: TComboBox
        Left = 80
        Top = 56
        Width = 105
        Height = 21
        Style = csDropDownList
        ItemHeight = 13
        TabOrder = 1
      end
      object ComboBox8: TComboBox
        Left = 80
        Top = 88
        Width = 105
        Height = 21
        Style = csDropDownList
        ItemHeight = 13
        TabOrder = 2
      end
    end
    object GroupBox3: TGroupBox
      Left = 256
      Top = 64
      Width = 209
      Height = 65
      Caption = 'UDP parameter'
      TabOrder = 1
      object Label3: TLabel
        Left = 16
        Top = 24
        Width = 54
        Height = 13
        Caption = 'IP Address:'
      end
      object IPEdit: TEdit
        Left = 88
        Top = 24
        Width = 97
        Height = 21
        TabOrder = 0
        Text = '192.168.0.222'
      end
    end
    object ComboBox1: TComboBox
      Left = 88
      Top = 24
      Width = 145
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      TabOrder = 2
    end
    object ComboBox6: TComboBox
      Left = 360
      Top = 27
      Width = 81
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      TabOrder = 3
      OnChange = ComboBox6Change
    end
  end
  object Button1: TButton
    Left = 504
    Top = 24
    Width = 81
    Height = 33
    Caption = 'Open'
    TabOrder = 1
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 504
    Top = 69
    Width = 81
    Height = 33
    Caption = 'Close'
    Enabled = False
    TabOrder = 2
    OnClick = Button2Click
  end
  object Button3: TButton
    Left = 504
    Top = 112
    Width = 105
    Height = 33
    Caption = 'Get Device Inf'
    Enabled = False
    TabOrder = 3
    OnClick = Button3Click
  end
  object PageControl1: TPageControl
    Left = 8
    Top = 240
    Width = 625
    Height = 393
    ActivePage = TabSheet1
    TabOrder = 4
    object TabSheet1: TTabSheet
      Caption = 'Reports'
      object Label4: TLabel
        Left = 408
        Top = 160
        Width = 54
        Height = 13
        Caption = 'Log output:'
      end
      object ListView1: TListView
        Left = 16
        Top = 8
        Width = 361
        Height = 337
        Columns = <
          item
            Caption = 'UID'
            Width = 150
          end
          item
            Caption = 'Direction'
            Width = 100
          end>
        GridLines = True
        TabOrder = 0
        ViewStyle = vsReport
      end
      object Button4: TButton
        Left = 400
        Top = 32
        Width = 73
        Height = 33
        Caption = 'Start'
        Enabled = False
        TabOrder = 1
        OnClick = Button4Click
      end
      object Button5: TButton
        Left = 400
        Top = 72
        Width = 73
        Height = 33
        Caption = 'Stop'
        Enabled = False
        TabOrder = 2
        OnClick = Button5Click
      end
      object Button6: TButton
        Left = 400
        Top = 112
        Width = 73
        Height = 33
        Caption = 'Clear List'
        TabOrder = 3
        OnClick = Button6Click
      end
      object Memo1: TMemo
        Left = 408
        Top = 186
        Width = 193
        Height = 159
        ImeName = '??????? 2'
        Lines.Strings = (
          'Memo1')
        TabOrder = 4
      end
    end
    object TabSheet2: TTabSheet
      Caption = 'Output Control'
      ImageIndex = 1
      object Label5: TLabel
        Left = 24
        Top = 32
        Width = 101
        Height = 13
        Caption = 'Output port selection:'
      end
      object Label6: TLabel
        Left = 248
        Top = 48
        Width = 55
        Height = 13
        Caption = 'Active time:'
      end
      object Label7: TLabel
        Left = 256
        Top = 80
        Width = 53
        Height = 13
        Caption = 'Frequency:'
      end
      object Label8: TLabel
        Left = 248
        Top = 111
        Width = 47
        Height = 13
        Caption = 'Stop time:'
      end
      object Label9: TLabel
        Left = 448
        Top = 48
        Width = 38
        Height = 13
        Caption = '* 100ms'
      end
      object Label10: TLabel
        Left = 448
        Top = 112
        Width = 38
        Height = 13
        Caption = '* 100ms'
      end
      object CheckListBox1: TCheckListBox
        Left = 24
        Top = 48
        Width = 201
        Height = 201
        ImeName = '??????? 2'
        ItemHeight = 13
        TabOrder = 0
      end
      object ComboBox3: TComboBox
        Left = 328
        Top = 45
        Width = 113
        Height = 21
        Style = csDropDownList
        ImeName = '??????? 2'
        ItemHeight = 0
        TabOrder = 1
      end
      object ComboBox4: TComboBox
        Left = 328
        Top = 77
        Width = 113
        Height = 21
        Style = csDropDownList
        ImeName = '??????? 2'
        ItemHeight = 0
        TabOrder = 2
      end
      object ComboBox5: TComboBox
        Left = 328
        Top = 109
        Width = 113
        Height = 21
        Style = csDropDownList
        ImeName = '??????? 2'
        ItemHeight = 0
        TabOrder = 3
      end
      object Button7: TButton
        Left = 312
        Top = 152
        Width = 105
        Height = 41
        Caption = 'Set output'
        Enabled = False
        TabOrder = 4
        OnClick = Button7Click
      end
    end
  end
  object Button8: TButton
    Left = 504
    Top = 160
    Width = 105
    Height = 33
    Caption = 'Clear Buffer'
    Enabled = False
    TabOrder = 5
    OnClick = Button8Click
  end
end
