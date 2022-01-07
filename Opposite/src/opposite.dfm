object MainForm: TMainForm
  Left = 43
  Top = 18
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = 'OPPOSITE'
  ClientHeight = 484
  ClientWidth = 674
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Menu = MainMenu1
  OldCreateOrder = False
  Position = poDesktopCenter
  OnCreate = FormCreate
  OnPaint = FormPaint
  PixelsPerInch = 96
  TextHeight = 13
  object Bevel1: TBevel
    Left = 16
    Top = 16
    Width = 433
    Height = 433
  end
  object Grid: TImage
    Left = 32
    Top = 32
    Width = 400
    Height = 400
    OnMouseDown = GridMouseDown
    OnMouseMove = GridMouseMove
  end
  object StatusLine: TPanel
    Left = 0
    Top = 467
    Width = 674
    Height = 17
    Align = alBottom
    Alignment = taLeftJustify
    BevelOuter = bvLowered
    TabOrder = 0
  end
  object Tag1: TGroupBox
    Left = 464
    Top = 16
    Width = 193
    Height = 97
    Caption = 'Score'
    TabOrder = 1
    object Label1: TLabel
      Left = 32
      Top = 32
      Width = 44
      Height = 13
      Caption = 'BLACK:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clNavy
      Font.Height = -12
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label2: TLabel
      Left = 32
      Top = 56
      Width = 46
      Height = 13
      Caption = 'WHITE:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWhite
      Font.Height = -12
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object scoreBlack: TLabel
      Left = 88
      Top = 32
      Width = 8
      Height = 13
      Caption = '0'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clNavy
      Font.Height = -12
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object scoreWhite: TLabel
      Left = 88
      Top = 56
      Width = 8
      Height = 13
      Caption = '0'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWhite
      Font.Height = -12
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object lblPlay1: TLabel
      Left = 112
      Top = 32
      Width = 50
      Height = 13
      Caption = '(computer)'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clNavy
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object lblPlay2: TLabel
      Left = 112
      Top = 56
      Width = 50
      Height = 13
      Caption = '(computer)'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWhite
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
  end
  object Tag2: TGroupBox
    Left = 464
    Top = 120
    Width = 193
    Height = 105
    Caption = 'Statistics'
    TabOrder = 2
    object statR1: TLabel
      Left = 15
      Top = 24
      Width = 74
      Height = 13
      Alignment = taRightJustify
      Caption = 'Rounds played:'
    end
    object statM1: TLabel
      Left = 20
      Top = 40
      Width = 69
      Height = 13
      Alignment = taRightJustify
      Caption = 'Moves played:'
    end
    object StatRounds: TLabel
      Left = 96
      Top = 24
      Width = 6
      Height = 13
      Caption = '0'
    end
    object statMoves: TLabel
      Left = 96
      Top = 40
      Width = 6
      Height = 13
      Caption = '0'
    end
    object Label3: TLabel
      Left = 21
      Top = 72
      Width = 68
      Height = 13
      Alignment = taRightJustify
      Caption = 'Last changed:'
    end
    object statChanged: TLabel
      Left = 96
      Top = 72
      Width = 6
      Height = 13
      Caption = '0'
    end
    object Label4: TLabel
      Left = 44
      Top = 56
      Width = 45
      Height = 13
      Alignment = taRightJustify
      Caption = 'Last play:'
    end
    object statLast: TLabel
      Left = 96
      Top = 56
      Width = 24
      Height = 13
      Caption = 'none'
    end
  end
  object GroupBox1: TGroupBox
    Left = 464
    Top = 240
    Width = 193
    Height = 209
    Caption = 'Game Instructions'
    TabOrder = 3
    object Memo1: TMemo
      Left = 16
      Top = 24
      Width = 161
      Height = 177
      BorderStyle = bsNone
      Color = clInactiveBorder
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      Lines.Strings = (
        'Place your pawns (black) next to '
        'your opponent'#39's (white) to convert '
        'all titles between two of your '
        'pawns on the grid, in horizontal, '
        'vertical or diagonal directions. If '
        'no such move exists, the player '
        'looses the current turn.'
        'Only moves that result in at least '
        'one conversion are allowed. '
        'Winner is the first player to '
        'convert all enemy pawns or the '
        'one that has the largest number of '
        'pawns on the grid.')
      ParentFont = False
      TabOrder = 0
    end
  end
  object MainMenu1: TMainMenu
    Left = 448
    Top = 112
    object N1: TMenuItem
      Caption = '&Game'
      object N3: TMenuItem
        Caption = '&New'
        OnClick = N3Click
      end
      object Settings1: TMenuItem
        Caption = '&Settings'
        OnClick = Settings1Click
      end
      object N4: TMenuItem
        Caption = '-'
      end
      object N5: TMenuItem
        Caption = 'E&xit'
        OnClick = N5Click
      end
    end
    object N2: TMenuItem
      Caption = '&Help'
      object N7: TMenuItem
        Caption = '&About'
        OnClick = N7Click
      end
    end
  end
end
