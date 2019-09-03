object Kompresor: TKompresor
  Left = 206
  Top = 117
  Width = 595
  Height = 288
  Caption = 'RLH archiwizer'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Menu = menu_ik
  OldCreateOrder = False
  Position = poScreenCenter
  PixelsPerInch = 96
  TextHeight = 13
  object konsola: TMemo
    Left = 8
    Top = 8
    Width = 217
    Height = 217
    ReadOnly = True
    ScrollBars = ssVertical
    TabOrder = 0
  end
  object otworz: TButton
    Left = 232
    Top = 16
    Width = 75
    Height = 25
    Caption = 'Otw'#243'rz'
    TabOrder = 1
    OnClick = otworzClick
  end
  object zapisz: TButton
    Left = 232
    Top = 56
    Width = 75
    Height = 25
    Caption = 'Zapisz'
    TabOrder = 2
    OnClick = zapiszClick
  end
  object o_edycja: TEdit
    Left = 320
    Top = 16
    Width = 249
    Height = 24
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    ReadOnly = True
    TabOrder = 3
  end
  object z_edycja: TEdit
    Left = 320
    Top = 56
    Width = 249
    Height = 24
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    ReadOnly = True
    TabOrder = 4
  end
  object start: TButton
    Left = 496
    Top = 192
    Width = 75
    Height = 25
    Caption = 'Start'
    TabOrder = 5
    OnClick = startClick
  end
  object s_kompresji: TGroupBox
    Left = 408
    Top = 88
    Width = 161
    Height = 89
    Caption = 'Sposoby kompresji:'
    TabOrder = 6
    object lz78: TLabel
      Left = 40
      Top = 40
      Width = 78
      Height = 16
      Caption = 'Metoda LZ78'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object rle: TLabel
      Left = 40
      Top = 16
      Width = 75
      Height = 16
      Caption = 'Metoda RLE'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object huff: TLabel
      Left = 40
      Top = 64
      Width = 106
      Height = 16
      Caption = 'Metoda Huffmana'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object rle_zaznacz: TCheckBox
      Left = 16
      Top = 16
      Width = 17
      Height = 17
      Caption = 'rle_zaznacz'
      TabOrder = 0
    end
    object lz78_zaznacz: TCheckBox
      Left = 16
      Top = 40
      Width = 17
      Height = 17
      Caption = 'CheckBox1'
      TabOrder = 1
    end
    object huff_zaznacz: TCheckBox
      Left = 16
      Top = 64
      Width = 17
      Height = 17
      Caption = 'CheckBox1'
      TabOrder = 2
    end
  end
  object operacja: TGroupBox
    Left = 240
    Top = 88
    Width = 153
    Height = 89
    Caption = 'Operacja:'
    TabOrder = 7
    object kompresja: TRadioButton
      Left = 8
      Top = 24
      Width = 113
      Height = 17
      Caption = 'Kompresja'
      Checked = True
      TabOrder = 0
      TabStop = True
      OnClick = kompresjaClick
    end
    object dekompresja: TRadioButton
      Left = 8
      Top = 56
      Width = 113
      Height = 17
      Caption = 'Dekompresja'
      TabOrder = 1
      OnClick = dekompresjaClick
    end
  end
  object menu_ik: TMainMenu
    Left = 232
    Top = 192
    object zakoncz: TMenuItem
      Caption = 'Zako'#324'cz'
      OnClick = zakonczClick
    end
    object Pomoc1: TMenuItem
      Caption = 'Pomoc'
      OnClick = Pomoc1Click
    end
  end
  object otworz_ik: TOpenDialog
    Options = [ofHideReadOnly, ofFileMustExist, ofEnableSizing]
    Left = 272
    Top = 192
  end
  object zapisz_ik: TSaveDialog
    Left = 312
    Top = 192
  end
  object Timer1: TTimer
    Enabled = False
    OnTimer = OnTimerTimer
    Left = 352
    Top = 192
  end
end
