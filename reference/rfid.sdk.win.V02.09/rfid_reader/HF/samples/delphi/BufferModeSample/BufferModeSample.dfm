object Form1: TForm1
  Left = 439
  Top = 163
  Width = 745
  Height = 468
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
    Left = 32
    Top = 0
    Width = 681
    Height = 201
    Caption = 'GroupBox1'
    TabOrder = 4
    object StaticText1: TStaticText
      Left = 8
      Top = 24
      Width = 42
      Height = 17
      Caption = 'Reader:'
      TabOrder = 0
    end
    object StaticText2: TStaticText
      Left = 168
      Top = 24
      Width = 49
      Height = 17
      Caption = 'Interface:'
      TabOrder = 1
    end
    object ComboBoxInterface: TComboBox
      Left = 224
      Top = 24
      Width = 89
      Height = 21
      ItemHeight = 13
      TabOrder = 2
      Text = 'ComboBoxInterface'
    end
    object GroupBox2: TGroupBox
      Left = 16
      Top = 56
      Width = 201
      Height = 129
      Caption = 'Serial ports'
      TabOrder = 3
      object StaticText3: TStaticText
        Left = 16
        Top = 24
        Width = 40
        Height = 17
        Caption = 'COM'#65306
        TabOrder = 0
      end
      object ComboBoxCOMName: TComboBox
        Left = 56
        Top = 24
        Width = 97
        Height = 21
        ItemHeight = 13
        TabOrder = 1
        Text = 'ComboBoxCOMName'
      end
      object StaticText4: TStaticText
        Left = 16
        Top = 56
        Width = 32
        Height = 17
        Caption = 'Baud:'
        TabOrder = 2
      end
      object ComboBoxBaud: TComboBox
        Left = 56
        Top = 56
        Width = 97
        Height = 21
        ItemHeight = 13
        TabOrder = 3
        Text = 'ComboBoxBaud'
      end
      object ComboBoxFrame: TComboBox
        Left = 56
        Top = 88
        Width = 97
        Height = 21
        ItemHeight = 13
        TabOrder = 4
        Text = 'ComboBoxFrame'
      end
      object StaticText5: TStaticText
        Left = 16
        Top = 88
        Width = 36
        Height = 17
        Caption = 'Frame:'
        TabOrder = 5
      end
    end
    object GroupBox3: TGroupBox
      Left = 240
      Top = 72
      Width = 233
      Height = 97
      Caption = 'Net'
      TabOrder = 4
      object StaticText6: TStaticText
        Left = 8
        Top = 24
        Width = 17
        Height = 17
        Caption = 'IP:'
        TabOrder = 0
      end
      object StaticText7: TStaticText
        Left = 8
        Top = 64
        Width = 26
        Height = 17
        Caption = 'Port:'
        TabOrder = 1
      end
      object EditIP: TEdit
        Left = 40
        Top = 24
        Width = 129
        Height = 21
        TabOrder = 2
        Text = '192.168.0.222'
      end
      object EditPort: TEdit
        Left = 40
        Top = 56
        Width = 129
        Height = 21
        TabOrder = 3
        Text = '9909'
      end
    end
    object GroupBox4: TGroupBox
      Left = 488
      Top = 72
      Width = 177
      Height = 97
      Caption = 'Bluetooth'
      TabOrder = 5
      object StaticText8: TStaticText
        Left = 8
        Top = 24
        Width = 35
        Height = 17
        Caption = 'Name:'
        TabOrder = 0
      end
      object ComboBoxBluetoothName: TComboBox
        Left = 56
        Top = 24
        Width = 105
        Height = 21
        ItemHeight = 13
        TabOrder = 1
        Text = 'ComboBoxBluetoothName'
        OnChange = ComboBoxBluetoothNameChange
      end
      object StaticText9: TStaticText
        Left = 8
        Top = 56
        Width = 29
        Height = 17
        Caption = 'Addr:'
        TabOrder = 2
      end
      object EditBluetoothAddr: TEdit
        Left = 56
        Top = 56
        Width = 113
        Height = 21
        TabOrder = 3
        Text = 'EditBluetoothAddr'
      end
    end
  end
  object ComboBoxReader: TComboBox
    Left = 80
    Top = 24
    Width = 97
    Height = 21
    ItemHeight = 13
    TabOrder = 0
    Text = 'ComboBoxReader'
  end
  object ButtonOpen: TButton
    Left = 368
    Top = 16
    Width = 97
    Height = 33
    Caption = 'Open'
    TabOrder = 1
    OnClick = ButtonOpenClick
  end
  object ButtonClose: TButton
    Left = 480
    Top = 16
    Width = 97
    Height = 33
    Caption = 'Close'
    TabOrder = 2
    OnClick = ButtonCloseClick
  end
  object buttonSetTime: TButton
    Left = 592
    Top = 16
    Width = 105
    Height = 33
    Caption = 'Set Time'
    TabOrder = 3
    OnClick = buttonSetTimeClick
  end
  object ListView1: TListView
    Left = 32
    Top = 224
    Width = 537
    Height = 169
    Columns = <
      item
        Caption = 'Record'
        Width = 500
      end>
    TabOrder = 5
    ViewStyle = vsReport
  end
  object Button1: TButton
    Left = 584
    Top = 232
    Width = 121
    Height = 33
    Caption = 'Get Record'
    TabOrder = 6
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 584
    Top = 280
    Width = 121
    Height = 33
    Caption = 'Stop'
    TabOrder = 7
    OnClick = Button2Click
  end
  object Button3: TButton
    Left = 584
    Top = 328
    Width = 121
    Height = 33
    Caption = 'Clear Record'
    TabOrder = 8
    OnClick = Button3Click
  end
end
