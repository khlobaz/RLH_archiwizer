object pasek: Tpasek
  Left = 821
  Top = 119
  BorderStyle = bsNone
  Caption = 'pasek'
  ClientHeight = 131
  ClientWidth = 424
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poOwnerFormCenter
  PixelsPerInch = 96
  TextHeight = 13
  object wspolczynnik: TLabel
    Left = 220
    Top = 88
    Width = 4
    Height = 16
    Caption = '-'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object uplynel: TLabel
    Left = 89
    Top = 64
    Width = 15
    Height = 16
    Caption = '-:--'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object koniec_z: TLabel
    Left = 89
    Top = 96
    Width = 15
    Height = 16
    Caption = '-:--'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object anuluj: TButton
    Left = 336
    Top = 96
    Width = 75
    Height = 25
    Caption = 'Anuluj'
    TabOrder = 0
    OnClick = anulujClick
  end
  object zadanie: TStaticText
    Left = 16
    Top = 8
    Width = 4
    Height = 4
    TabOrder = 1
  end
  object pasek_1: TProgressBar
    Left = 16
    Top = 32
    Width = 393
    Height = 19
    Min = 0
    Max = 100
    TabOrder = 2
  end
  object c_zadanie: TStaticText
    Left = 16
    Top = 8
    Width = 4
    Height = 4
    TabOrder = 3
  end
  object uplynelo: TStaticText
    Left = 16
    Top = 64
    Width = 61
    Height = 20
    Caption = 'Up'#322'yn'#281#322'o:'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 4
  end
  object ratio: TStaticText
    Left = 152
    Top = 64
    Width = 152
    Height = 20
    Caption = 'Wsp'#243#322'czynnik kompresji:'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 5
  end
  object koniec_za: TStaticText
    Left = 16
    Top = 96
    Width = 65
    Height = 20
    Caption = 'Koniec za:'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 6
  end
end
