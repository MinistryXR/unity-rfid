object Form1: TForm1
  Left = 195
  Top = 22
  Width = 909
  Height = 725
  Caption = 'Form1'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnCloseQuery = FormCloseQuery
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object PageControl2: TPageControl
    Left = 4
    Top = 272
    Width = 878
    Height = 409
    ActivePage = TabSheet1
    TabOrder = 0
    object TabSheet5: TTabSheet
      Caption = 'Inventory'
      object Label4: TLabel
        Left = 506
        Top = 264
        Width = 163
        Height = 32
        Caption = 'Total Count:'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -27
        Font.Name = 'Arial'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object Label5: TLabel
        Left = 514
        Top = 304
        Width = 121
        Height = 32
        AutoSize = False
        Caption = '0'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -27
        Font.Name = 'Arial'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object Button5: TButton
        Left = 503
        Top = 48
        Width = 97
        Height = 41
        Caption = 'Start Inventory'
        Enabled = False
        TabOrder = 0
        OnClick = Button5Click
      end
      object ListView1: TListView
        Left = 8
        Top = 4
        Width = 489
        Height = 349
        Columns = <
          item
            Caption = 'Tag Type'
            Width = 150
          end
          item
            Caption = 'Serial num'
            Width = 120
          end
          item
            Caption = 'DSFID'
          end
          item
            Caption = 'Antenna'
            Width = 80
          end
          item
            Caption = 'Read count'
            Width = 80
          end>
        GridLines = True
        TabOrder = 1
        ViewStyle = vsReport
      end
      object GroupBox2: TGroupBox
        Left = 503
        Top = 104
        Width = 193
        Height = 89
        Caption = 'ISO15693 parameters'
        TabOrder = 2
        object Label2: TLabel
          Left = 16
          Top = 64
          Width = 19
          Height = 13
          Caption = 'AFI:'
        end
        object Label3: TLabel
          Left = 88
          Top = 64
          Width = 17
          Height = 13
          Caption = 'hex'
        end
        object CheckBox2: TCheckBox
          Left = 16
          Top = 16
          Width = 89
          Height = 33
          Caption = 'Only new tag'
          TabOrder = 0
        end
        object CheckBox3: TCheckBox
          Left = 17
          Top = 42
          Width = 113
          Height = 17
          Caption = 'Match AFI'
          TabOrder = 1
        end
        object Edit3: TEdit
          Left = 41
          Top = 62
          Width = 40
          Height = 21
          ImeName = '??????? 2'
          TabOrder = 2
          Text = '00'
        end
      end
      object GroupBox5: TGroupBox
        Left = 706
        Top = 88
        Width = 129
        Height = 193
        Caption = 'Antenna Selection'
        TabOrder = 3
        object CheckListBox1: TCheckListBox
          Left = 8
          Top = 16
          Width = 105
          Height = 169
          ImeName = '??????? 2'
          ItemHeight = 13
          Items.Strings = (
            '')
          TabOrder = 0
        end
      end
    end
    object TabSheet6: TTabSheet
      Caption = 'ICODE SLIX'
      ImageIndex = 1
      object Label6: TLabel
        Left = 16
        Top = 16
        Width = 71
        Height = 13
        Caption = 'Address Mode:'
      end
      object Label7: TLabel
        Left = 208
        Top = 13
        Width = 22
        Height = 13
        Caption = 'UID:'
      end
      object Button16: TButton
        Left = 384
        Top = 8
        Width = 73
        Height = 25
        Caption = 'Connect'
        Enabled = False
        TabOrder = 0
        OnClick = Button16Click
      end
      object Button17: TButton
        Left = 472
        Top = 8
        Width = 81
        Height = 25
        Caption = 'Disconnect'
        Enabled = False
        TabOrder = 1
        OnClick = Button17Click
      end
      object ComboBox2: TComboBox
        Left = 92
        Top = 11
        Width = 109
        Height = 21
        Style = csDropDownList
        ImeName = '??????? 2'
        ItemHeight = 13
        ItemIndex = 1
        TabOrder = 2
        Text = 'Addressed Mode'
        Items.Strings = (
          'None Address Mode'
          'Addressed Mode'
          'Select Mode')
      end
      object ComboBox3: TComboBox
        Left = 240
        Top = 11
        Width = 129
        Height = 21
        ImeName = '??????? 2'
        ItemHeight = 13
        TabOrder = 3
      end
      object GroupBox3: TGroupBox
        Left = 16
        Top = 48
        Width = 633
        Height = 337
        Caption = 'Access'
        TabOrder = 4
        object Label8: TLabel
          Left = 22
          Top = 32
          Width = 54
          Height = 13
          Caption = 'Block data:'
        end
        object Label9: TLabel
          Left = 384
          Top = 32
          Width = 148
          Height = 13
          Caption = 'hex(Read: secure byte + block)'
        end
        object Label10: TLabel
          Left = 24
          Top = 64
          Width = 50
          Height = 13
          Caption = 'Start Addr:'
        end
        object Label11: TLabel
          Left = 19
          Top = 96
          Width = 55
          Height = 13
          Caption = 'Block Num:'
        end
        object Label12: TLabel
          Left = 24
          Top = 128
          Width = 19
          Height = 13
          Caption = 'AFI:'
        end
        object Label13: TLabel
          Left = 24
          Top = 160
          Width = 35
          Height = 13
          Caption = 'DSFID:'
        end
        object Label14: TLabel
          Left = 24
          Top = 192
          Width = 50
          Height = 13
          Caption = 'EAS Data:'
        end
        object Label15: TLabel
          Left = 152
          Top = 136
          Width = 17
          Height = 13
          Caption = 'hex'
        end
        object Label16: TLabel
          Left = 152
          Top = 160
          Width = 17
          Height = 13
          Caption = 'hex'
        end
        object Button13: TButton
          Left = 208
          Top = 272
          Width = 97
          Height = 25
          Caption = 'EAS alarm'
          Enabled = False
          TabOrder = 0
          OnClick = Button13Click
        end
        object Button14: TButton
          Left = 208
          Top = 192
          Width = 97
          Height = 33
          Caption = 'enable EAS'
          Enabled = False
          TabOrder = 1
          OnClick = Button14Click
        end
        object Button11: TButton
          Left = 512
          Top = 128
          Width = 81
          Height = 33
          Caption = 'get sys infor'
          Enabled = False
          TabOrder = 2
          OnClick = Button11Click
        end
        object Button10: TButton
          Left = 211
          Top = 96
          Width = 102
          Height = 25
          Caption = 'read multi blocks'
          Enabled = False
          TabOrder = 3
          OnClick = Button10Click
        end
        object Button9: TButton
          Left = 328
          Top = 64
          Width = 105
          Height = 25
          Caption = 'write multi block'
          Enabled = False
          TabOrder = 4
          OnClick = Button9Click
        end
        object Button12: TButton
          Left = 208
          Top = 128
          Width = 97
          Height = 25
          Caption = 'write AFI'
          Enabled = False
          TabOrder = 5
          OnClick = Button12Click
        end
        object Button15: TButton
          Left = 208
          Top = 231
          Width = 97
          Height = 33
          Caption = 'disable EAS'
          Enabled = False
          TabOrder = 6
          OnClick = Button15Click
        end
        object Button8: TButton
          Left = 208
          Top = 64
          Width = 105
          Height = 25
          Caption = 'lock multi block'
          Enabled = False
          TabOrder = 7
          OnClick = Button8Click
        end
        object Edit1: TEdit
          Left = 80
          Top = 32
          Width = 297
          Height = 21
          ImeName = '??????? 2'
          TabOrder = 8
        end
        object ComboBox4: TComboBox
          Left = 80
          Top = 64
          Width = 105
          Height = 21
          Style = csDropDownList
          ImeName = '??????? 2'
          ItemHeight = 13
          ItemIndex = 0
          TabOrder = 9
          Text = '0'
          Items.Strings = (
            '0'
            '1'
            '2'
            '3'
            '4'
            '5'
            '6'
            '7'
            '8'
            '9'
            '10'
            '11'
            '12'
            '13'
            '14'
            '15'
            '16'
            '17'
            '18'
            '19'
            '20'
            '21'
            '22'
            '23'
            '24'
            '25'
            '26'
            '27')
        end
        object ComboBox5: TComboBox
          Left = 80
          Top = 96
          Width = 105
          Height = 21
          Style = csDropDownList
          ImeName = '??????? 2'
          ItemHeight = 13
          ItemIndex = 0
          TabOrder = 10
          Text = '1'
          Items.Strings = (
            '1'
            '2'
            '3'
            '4'
            '5'
            '6'
            '7'
            '8')
        end
        object Button6: TButton
          Left = 333
          Top = 96
          Width = 132
          Height = 25
          Caption = 'Get block security status'
          Enabled = False
          TabOrder = 11
          OnClick = Button6Click
        end
        object Edit5: TEdit
          Left = 80
          Top = 128
          Width = 65
          Height = 21
          ImeName = '??????? 2'
          TabOrder = 12
          Text = '00'
        end
        object Edit6: TEdit
          Left = 80
          Top = 160
          Width = 65
          Height = 21
          ImeName = '??????? 2'
          TabOrder = 13
          Text = '00'
        end
        object Button7: TButton
          Left = 208
          Top = 161
          Width = 97
          Height = 25
          Caption = 'write DSFID'
          Enabled = False
          TabOrder = 14
          OnClick = Button7Click
        end
        object Memo1: TMemo
          Left = 80
          Top = 194
          Width = 121
          Height = 103
          ImeName = '??????? 2'
          TabOrder = 15
        end
        object GroupBox4: TGroupBox
          Left = 320
          Top = 128
          Width = 185
          Height = 193
          Caption = 'system information'
          TabOrder = 16
          object Label23: TLabel
            Left = 56
            Top = 24
            Width = 105
            Height = 25
            AutoSize = False
          end
          object Label17: TLabel
            Left = 8
            Top = 24
            Width = 22
            Height = 13
            Caption = 'UID:'
          end
          object Label18: TLabel
            Left = 8
            Top = 56
            Width = 19
            Height = 13
            Caption = 'AFI:'
          end
          object Label19: TLabel
            Left = 8
            Top = 88
            Width = 35
            Height = 13
            Caption = 'DSFID:'
          end
          object Label20: TLabel
            Left = 8
            Top = 115
            Width = 78
            Height = 13
            Caption = 'Bytes in a block:'
          end
          object Label21: TLabel
            Left = 8
            Top = 142
            Width = 84
            Height = 13
            Caption = 'Number of Blocks'
          end
          object Label22: TLabel
            Left = 8
            Top = 168
            Width = 61
            Height = 13
            Caption = 'IC reference:'
          end
          object Label24: TLabel
            Left = 37
            Top = 21
            Width = 129
            Height = 25
            AutoSize = False
          end
          object Label25: TLabel
            Left = 34
            Top = 53
            Width = 129
            Height = 25
            AutoSize = False
          end
          object Label26: TLabel
            Left = 50
            Top = 85
            Width = 129
            Height = 25
            AutoSize = False
          end
          object Label27: TLabel
            Left = 88
            Top = 109
            Width = 81
            Height = 25
            AutoSize = False
          end
          object Label28: TLabel
            Left = 96
            Top = 141
            Width = 81
            Height = 25
            AutoSize = False
          end
          object Label29: TLabel
            Left = 72
            Top = 165
            Width = 81
            Height = 25
            AutoSize = False
          end
        end
      end
    end
    object TabSheet7: TTabSheet
      Caption = 'Tag-it HF-I plus'
      ImageIndex = 2
      object Edit2: TEdit
        Left = 136
        Top = 64
        Width = 169
        Height = 21
        ImeName = '??????? 2'
        TabOrder = 0
        Text = 'Edit2'
      end
      object Button20: TButton
        Left = 24
        Top = 64
        Width = 89
        Height = 33
        Caption = 'read single block'
        TabOrder = 1
        OnClick = Button20Click
      end
      object Button18: TButton
        Left = 24
        Top = 16
        Width = 81
        Height = 33
        Caption = 'connect'
        TabOrder = 2
        OnClick = Button18Click
      end
      object Button19: TButton
        Left = 128
        Top = 16
        Width = 65
        Height = 33
        Caption = 'disconnect'
        TabOrder = 3
        OnClick = Button19Click
      end
      object Button22: TButton
        Left = 136
        Top = 96
        Width = 97
        Height = 33
        Caption = 'write single block'
        TabOrder = 4
        OnClick = Button22Click
      end
      object Button21: TButton
        Left = 24
        Top = 112
        Width = 89
        Height = 33
        Caption = 'read multi blocks'
        TabOrder = 5
        OnClick = Button21Click
      end
      object Button23: TButton
        Left = 24
        Top = 160
        Width = 97
        Height = 33
        Caption = 'get sys infor'
        TabOrder = 6
        OnClick = Button23Click
      end
      object Button25: TButton
        Left = 24
        Top = 200
        Width = 97
        Height = 33
        Caption = 'lock 2 blocks'
        TabOrder = 7
        OnClick = Button25Click
      end
      object Button24: TButton
        Left = 136
        Top = 140
        Width = 89
        Height = 33
        Caption = 'write 2 blocks'
        TabOrder = 8
        OnClick = Button24Click
      end
    end
    object TabSheet1: TTabSheet
      Caption = 'Mifare S50'
      ImageIndex = 3
      object Label39: TLabel
        Left = 80
        Top = 24
        Width = 22
        Height = 13
        Caption = 'UID:'
      end
      object Label40: TLabel
        Left = 32
        Top = 64
        Width = 71
        Height = 13
        Caption = 'Block Address:'
      end
      object Label41: TLabel
        Left = 61
        Top = 108
        Width = 44
        Height = 13
        Caption = 'Key type:'
      end
      object Label42: TLabel
        Left = 200
        Top = 104
        Width = 21
        Height = 13
        Caption = 'Key:'
      end
      object Label43: TLabel
        Left = 50
        Top = 154
        Width = 56
        Height = 13
        Caption = 'Block Data:'
      end
      object Label44: TLabel
        Left = 335
        Top = 107
        Width = 19
        Height = 13
        Caption = 'Hex'
      end
      object Label45: TLabel
        Left = 334
        Top = 154
        Width = 19
        Height = 13
        Caption = 'Hex'
      end
      object Button3: TButton
        Left = 240
        Top = 18
        Width = 73
        Height = 25
        Caption = 'Connect'
        TabOrder = 0
        OnClick = Button3Click
      end
      object Button27: TButton
        Left = 328
        Top = 18
        Width = 75
        Height = 25
        Caption = 'Disconnect'
        Enabled = False
        TabOrder = 1
        OnClick = Button27Click
      end
      object ComboBox13: TComboBox
        Left = 112
        Top = 64
        Width = 121
        Height = 21
        ItemHeight = 13
        ItemIndex = 0
        TabOrder = 2
        Text = '0'
        Items.Strings = (
          '0'
          '1'
          '2'
          '3'
          '4'
          '5'
          '6'
          '7'
          '8'
          '9'
          '10'
          '11'
          '12'
          '13'
          '14'
          '15'
          '16'
          '17'
          '18'
          '19'
          '20'
          '21'
          '22'
          '23'
          '24'
          '25'
          '26'
          '27'
          '28'
          '29'
          '30'
          '31')
      end
      object ComboBox14: TComboBox
        Left = 112
        Top = 104
        Width = 81
        Height = 21
        ItemHeight = 13
        ItemIndex = 0
        TabOrder = 3
        Text = 'Key A'
        Items.Strings = (
          'Key A'
          'Key B')
      end
      object Edit9: TEdit
        Left = 224
        Top = 104
        Width = 105
        Height = 21
        TabOrder = 4
        Text = 'FFFFFFFFFFFF'
      end
      object Button28: TButton
        Left = 363
        Top = 98
        Width = 78
        Height = 25
        Caption = 'Authenticate'
        TabOrder = 5
        OnClick = Button28Click
      end
      object Edit10: TEdit
        Left = 112
        Top = 152
        Width = 217
        Height = 21
        TabOrder = 6
        Text = '00000000000000000000000000000000'
      end
      object Button29: TButton
        Left = 365
        Top = 148
        Width = 76
        Height = 25
        Caption = 'Read'
        TabOrder = 7
        OnClick = Button29Click
      end
      object Button30: TButton
        Left = 453
        Top = 146
        Width = 73
        Height = 25
        Caption = 'Write'
        TabOrder = 8
        OnClick = Button30Click
      end
      object ComboBox15: TComboBox
        Left = 112
        Top = 24
        Width = 121
        Height = 21
        ItemHeight = 13
        TabOrder = 9
      end
    end
  end
  object GroupBox1: TGroupBox
    Left = 8
    Top = 8
    Width = 505
    Height = 257
    Caption = 'Open reader'
    TabOrder = 1
    object Label30: TLabel
      Left = 16
      Top = 23
      Width = 66
      Height = 13
      Caption = 'Reader types:'
    end
    object Label34: TLabel
      Left = 19
      Top = 48
      Width = 60
      Height = 13
      Caption = 'Comm types:'
    end
    object Button1: TButton
      Left = 256
      Top = 17
      Width = 89
      Height = 25
      Caption = 'open reader'
      TabOrder = 0
      OnClick = Button1Click
    end
    object Button2: TButton
      Left = 368
      Top = 16
      Width = 89
      Height = 25
      Caption = 'close reader'
      Enabled = False
      TabOrder = 1
      OnClick = Button2Click
    end
    object ComboBox6: TComboBox
      Left = 88
      Top = 20
      Width = 129
      Height = 21
      ImeName = '??????? 2'
      ItemHeight = 13
      TabOrder = 2
      OnChange = ComboBox6Change
    end
    object GroupBox7: TGroupBox
      Left = 17
      Top = 73
      Width = 184
      Height = 120
      Caption = 'Serial interface'
      TabOrder = 3
      object Label1: TLabel
        Left = 8
        Top = 28
        Width = 56
        Height = 13
        Caption = 'COM name:'
      end
      object Label37: TLabel
        Left = 24
        Top = 56
        Width = 28
        Height = 13
        Caption = 'Band:'
      end
      object Label38: TLabel
        Left = 16
        Top = 88
        Width = 32
        Height = 13
        Caption = 'Frame:'
      end
      object ComboBox1: TComboBox
        Left = 69
        Top = 24
        Width = 105
        Height = 21
        ImeName = '??????? 2'
        ItemHeight = 13
        TabOrder = 0
      end
      object ComboBox11: TComboBox
        Left = 64
        Top = 56
        Width = 105
        Height = 21
        ImeName = '??????? 2'
        ItemHeight = 13
        TabOrder = 1
      end
      object ComboBox12: TComboBox
        Left = 64
        Top = 88
        Width = 105
        Height = 21
        ImeName = '??????? 2'
        ItemHeight = 13
        TabOrder = 2
      end
    end
    object GroupBox8: TGroupBox
      Left = 256
      Top = 56
      Width = 225
      Height = 73
      Caption = 'USB Interface'
      TabOrder = 4
      object Label32: TLabel
        Left = 16
        Top = 24
        Width = 81
        Height = 13
        Caption = 'USB Open Type:'
      end
      object Label33: TLabel
        Left = 16
        Top = 48
        Width = 69
        Height = 13
        Caption = 'Serial Number:'
      end
      object ComboBox8: TComboBox
        Left = 102
        Top = 22
        Width = 115
        Height = 21
        Style = csDropDownList
        ImeName = '??????? 2'
        ItemHeight = 13
        ItemIndex = 0
        TabOrder = 0
        Text = 'None Addressed'
        OnChange = ComboBox8Change
        Items.Strings = (
          'None Addressed'
          'Serial Number')
      end
      object ComboBox9: TComboBox
        Left = 102
        Top = 46
        Width = 115
        Height = 21
        Style = csDropDownList
        ImeName = '??????? 2'
        ItemHeight = 13
        TabOrder = 1
      end
    end
    object ComboBox10: TComboBox
      Left = 88
      Top = 46
      Width = 129
      Height = 21
      Style = csDropDownList
      ImeName = '??????? 2'
      ItemHeight = 13
      TabOrder = 5
      OnChange = ComboBox10Change
      Items.Strings = (
        'COM'
        'USB'
        'NET')
    end
    object GroupBox9: TGroupBox
      Left = 16
      Top = 200
      Width = 465
      Height = 49
      Caption = 'LAN'
      TabOrder = 6
      object Label35: TLabel
        Left = 8
        Top = 24
        Width = 53
        Height = 13
        Caption = 'Remote IP:'
      end
      object Label36: TLabel
        Left = 264
        Top = 22
        Width = 62
        Height = 13
        Caption = 'Remote Port:'
      end
      object Edit4: TEdit
        Left = 331
        Top = 19
        Width = 81
        Height = 21
        ImeName = '??????? 2'
        TabOrder = 0
        Text = '9909'
      end
      object Edit7: TEdit
        Left = 68
        Top = 18
        Width = 141
        Height = 21
        ImeName = '??????? 2'
        TabOrder = 1
        Text = '192.168.0.222'
      end
    end
  end
  object GroupBox6: TGroupBox
    Left = 544
    Top = 8
    Width = 305
    Height = 105
    TabOrder = 2
    object Label31: TLabel
      Left = 136
      Top = 28
      Width = 66
      Height = 13
      Caption = 'Antenna num:'
    end
    object Button26: TButton
      Left = 16
      Top = 20
      Width = 113
      Height = 33
      Caption = 'Set access antenna'
      Enabled = False
      TabOrder = 0
      OnClick = Button26Click
    end
    object ComboBox7: TComboBox
      Left = 208
      Top = 28
      Width = 81
      Height = 21
      Style = csDropDownList
      ImeName = '??????? 2'
      ItemHeight = 13
      TabOrder = 1
    end
    object Button4: TButton
      Left = 16
      Top = 64
      Width = 113
      Height = 33
      Caption = 'Get device info'
      Enabled = False
      TabOrder = 2
      OnClick = Button4Click
    end
  end
end
