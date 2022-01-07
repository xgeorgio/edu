object SetupForm: TSetupForm
  Left = 192
  Top = 107
  BorderIcons = [biSystemMenu]
  BorderStyle = bsDialog
  Caption = 'Game Settings'
  ClientHeight = 283
  ClientWidth = 450
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  FormStyle = fsStayOnTop
  OldCreateOrder = False
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object GroupBox1: TGroupBox
    Left = 8
    Top = 8
    Width = 209
    Height = 209
    Caption = 'Player: BLACK'
    TabOrder = 2
    object diff1: TLabel
      Left = 24
      Top = 136
      Width = 72
      Height = 13
      Caption = 'Difficulty Level:'
    end
    object lblDiff1: TLabel
      Left = 104
      Top = 136
      Width = 14
      Height = 13
      Caption = '0%'
    end
    object RadioGroup1: TRadioGroup
      Left = 24
      Top = 32
      Width = 153
      Height = 81
      TabOrder = 0
    end
    object selUser1: TRadioButton
      Left = 48
      Top = 56
      Width = 97
      Height = 17
      Caption = 'Human Player'
      Checked = True
      TabOrder = 1
      TabStop = True
      OnClick = selUser1Click
    end
    object selComp1: TRadioButton
      Left = 48
      Top = 80
      Width = 105
      Height = 17
      Caption = 'Computer Player'
      TabOrder = 2
      OnClick = selComp1Click
    end
    object selDiff1: TTrackBar
      Left = 16
      Top = 152
      Width = 169
      Height = 33
      Max = 4
      Min = 1
      Orientation = trHorizontal
      PageSize = 1
      Frequency = 1
      Position = 1
      SelEnd = 0
      SelStart = 0
      TabOrder = 3
      ThumbLength = 17
      TickMarks = tmBottomRight
      TickStyle = tsAuto
      OnChange = selDiff1Change
    end
  end
  object btnOk: TButton
    Left = 112
    Top = 240
    Width = 81
    Height = 33
    Caption = '&OK'
    TabOrder = 0
    OnClick = btnOkClick
  end
  object btnCancel: TButton
    Left = 256
    Top = 240
    Width = 81
    Height = 33
    Cancel = True
    Caption = '&Cancel'
    TabOrder = 1
    OnClick = btnCancelClick
  end
  object GroupBox2: TGroupBox
    Left = 232
    Top = 8
    Width = 209
    Height = 209
    Caption = 'Player: WHITE'
    TabOrder = 3
    object diff2: TLabel
      Left = 24
      Top = 136
      Width = 72
      Height = 13
      Caption = 'Difficulty Level:'
    end
    object lblDiff2: TLabel
      Left = 104
      Top = 136
      Width = 14
      Height = 13
      Caption = '0%'
    end
    object RadioGroup2: TRadioGroup
      Left = 24
      Top = 32
      Width = 161
      Height = 81
      TabOrder = 0
    end
    object selUser2: TRadioButton
      Left = 40
      Top = 56
      Width = 121
      Height = 17
      Caption = 'Human Player'
      TabOrder = 1
      OnClick = selUser2Click
    end
    object selComp2: TRadioButton
      Left = 40
      Top = 80
      Width = 129
      Height = 17
      Caption = 'Computer Player'
      Checked = True
      TabOrder = 2
      TabStop = True
      OnClick = selComp2Click
    end
    object selDiff2: TTrackBar
      Left = 16
      Top = 152
      Width = 177
      Height = 25
      Max = 4
      Min = 1
      Orientation = trHorizontal
      PageSize = 1
      Frequency = 1
      Position = 1
      SelEnd = 0
      SelStart = 0
      TabOrder = 3
      ThumbLength = 17
      TickMarks = tmBottomRight
      TickStyle = tsAuto
      OnChange = selDiff2Change
    end
  end
end
