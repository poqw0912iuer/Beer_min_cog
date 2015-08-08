object Form1: TForm1
  Left = 102
  Top = 264
  BorderStyle = bsSingle
  Caption = 'Beer-min-cog'
  ClientHeight = 724
  ClientWidth = 1231
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Label2: TLabel
    Left = 656
    Top = 8
    Width = 25
    Height = 13
    Caption = 'steps'
  end
  object Label6: TLabel
    Left = 448
    Top = 40
    Width = 50
    Height = 13
    Caption = 'Population'
  end
  object Label7: TLabel
    Left = 448
    Top = 64
    Width = 38
    Height = 13
    Caption = 'Cr. Porb'
  end
  object Label8: TLabel
    Left = 448
    Top = 88
    Width = 46
    Height = 13
    Caption = 'Mut. Prob'
  end
  object Label9: TLabel
    Left = 448
    Top = 112
    Width = 57
    Height = 13
    Caption = 'Gneerations'
  end
  object Label4: TLabel
    Left = 560
    Top = 40
    Width = 93
    Height = 23
    Caption = 'Run no. '
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -21
    Font.Name = 'Neuropol'
    Font.Style = []
    ParentFont = False
  end
  object Label3: TLabel
    Left = 560
    Top = 72
    Width = 91
    Height = 23
    Caption = 'Fitnes = '
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -21
    Font.Name = 'Neuropol'
    Font.Style = []
    ParentFont = False
  end
  object Edit2: TEdit
    Left = 512
    Top = 40
    Width = 41
    Height = 21
    TabOrder = 0
    Text = '40'
  end
  object Button2: TButton
    Left = 560
    Top = 8
    Width = 89
    Height = 25
    Caption = 'Visualise'
    TabOrder = 1
    OnClick = Button2Click
  end
  object Button3: TButton
    Left = 448
    Top = 8
    Width = 105
    Height = 25
    Caption = 'Solve'
    TabOrder = 2
    OnClick = Button3Click
  end
  object Edit3: TEdit
    Left = 512
    Top = 64
    Width = 41
    Height = 21
    TabOrder = 3
    Text = '0,80'
  end
  object Edit4: TEdit
    Left = 512
    Top = 88
    Width = 41
    Height = 21
    TabOrder = 4
    Text = '0,30'
  end
  object GroupBox1: TGroupBox
    Left = 0
    Top = 0
    Width = 257
    Height = 161
    Caption = 'Selection Mechanisms'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 5
    object Label10: TLabel
      Left = 144
      Top = 64
      Width = 13
      Height = 13
      Caption = 'T='
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object RadioButton1: TRadioButton
      Left = 8
      Top = 128
      Width = 161
      Height = 17
      Caption = 'Fitness Proportionate scaling'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
      OnClick = RadioButton1Click
    end
    object RadioButton2: TRadioButton
      Left = 8
      Top = 32
      Width = 113
      Height = 17
      Caption = 'Sigma scaling'
      Checked = True
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 1
      TabStop = True
      OnClick = RadioButton2Click
    end
    object RadioButton3: TRadioButton
      Left = 8
      Top = 64
      Width = 113
      Height = 17
      Caption = 'Boltzman scaling'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 2
      OnClick = RadioButton3Click
    end
    object RadioButton4: TRadioButton
      Left = 8
      Top = 96
      Width = 113
      Height = 17
      Caption = 'Rank selection'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 3
      OnClick = RadioButton4Click
    end
    object Edit5: TEdit
      Left = 160
      Top = 64
      Width = 33
      Height = 21
      Enabled = False
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 4
      Text = '40'
    end
  end
  object GroupBox2: TGroupBox
    Left = 264
    Top = 0
    Width = 177
    Height = 81
    Caption = 'Selection Protocols'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 6
    object RadioButton6: TRadioButton
      Left = 8
      Top = 24
      Width = 161
      Height = 17
      Caption = 'Full Generational replacement'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
    end
    object RadioButton7: TRadioButton
      Left = 8
      Top = 48
      Width = 113
      Height = 17
      Caption = 'Over Production'
      Checked = True
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 1
      TabStop = True
    end
  end
  object Edit8: TEdit
    Left = 512
    Top = 112
    Width = 41
    Height = 21
    TabOrder = 7
    Text = '20'
  end
  object Edit9: TEdit
    Left = 688
    Top = 8
    Width = 41
    Height = 21
    TabOrder = 8
    Text = '20'
  end
  object Button5: TButton
    Left = 448
    Top = 136
    Width = 105
    Height = 25
    Caption = 'Plot'
    Enabled = False
    TabOrder = 9
    OnClick = Button5Click
  end
  object TrackBar1: TTrackBar
    Left = 560
    Top = 120
    Width = 257
    Height = 41
    Max = 20
    Min = 1
    Orientation = trHorizontal
    ParentShowHint = False
    Frequency = 1
    Position = 1
    SelEnd = 0
    SelStart = 0
    ShowHint = False
    TabOrder = 10
    TickMarks = tmBoth
    TickStyle = tsAuto
    OnChange = TrackBar1Change
  end
  object StringGrid1: TStringGrid
    Left = 968
    Top = 0
    Width = 257
    Height = 721
    ColCount = 11
    DefaultColWidth = 22
    DefaultRowHeight = 17
    RowCount = 38
    TabOrder = 11
    ColWidths = (
      22
      48
      22
      22
      22
      22
      22
      22
      22
      22
      22)
  end
  object Button1: TButton
    Left = 784
    Top = 40
    Width = 75
    Height = 25
    Caption = 'Button1'
    TabOrder = 12
    OnClick = Button1Click
  end
end
