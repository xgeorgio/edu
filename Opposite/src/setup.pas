(*
   * * * * * * * * * * * * * * * * * * * * * * * *
   *                                             *
   *      ApplName:  OPPOSITE                    *
   *      FileName:  setup.pas                   *
   *   Description:  Settings dialog box         *
   *                                             *
   *        Author:  Harris Georgiou (c) 2000.   *
   *                                             *
   * * * * * * * * * * * * * * * * * * * * * * * *
*)


unit setup;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls, ComCtrls, ExtCtrls;

type
  TSetupForm = class(TForm)
    btnOk: TButton;
    btnCancel: TButton;
    GroupBox1: TGroupBox;
    GroupBox2: TGroupBox;
    RadioGroup1: TRadioGroup;
    selUser1: TRadioButton;
    selComp1: TRadioButton;
    selDiff1: TTrackBar;
    diff1: TLabel;
    RadioGroup2: TRadioGroup;
    selUser2: TRadioButton;
    selComp2: TRadioButton;
    selDiff2: TTrackBar;
    diff2: TLabel;
    lblDiff1: TLabel;
    lblDiff2: TLabel;

    procedure btnOkClick(Sender: TObject);
    procedure btnCancelClick(Sender: TObject);
    procedure selDiff1Change(Sender: TObject);
    procedure selDiff2Change(Sender: TObject);
    procedure FormShow(Sender: TObject);

    procedure setbackVariables;
    procedure updateIndicators;
    procedure syncLabels;
    procedure enableLevel1;
    procedure disableLevel1;
    procedure enableLevel2;
    procedure disableLevel2;
    procedure selComp1Click(Sender: TObject);
    procedure selUser1Click(Sender: TObject);
    procedure selComp2Click(Sender: TObject);
    procedure selUser2Click(Sender: TObject);

  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  SetupForm: TSetupForm;

implementation

uses Defines, opposite;

{$R *.DFM}

{... update game variables (main program) ...}
procedure TSetupForm.setbackVariables;
begin
    if (selUser1.Checked) then MainForm.playType[cBlack]:=cUserPlayer
    else
      begin
        MainForm.playType[cBlack]:=cComputerPlayer;
        MainForm.playLevel[cBlack]:=selDiff1.Position;
      end;

    if (selUser2.Checked) then MainForm.playType[cWhite]:=cUserPlayer
    else
      begin
        MainForm.playType[cWhite]:=cComputerPlayer;
        MainForm.playLevel[cWhite]:=selDiff2.Position;
      end;

    {... change player before scoreboard update (show last move) ...}
    MainForm.nextPlays:=(MainForm.nextPlays+1) mod 2;
    MainForm.DrawScore;
    MainForm.nextPlays:=(MainForm.nextPlays+1) mod 2;
end;

{... update form visuals ...}
procedure TSetupForm.updateIndicators;
begin
    selDiff1.Position:=MainForm.playLevel[cBlack];
    if (MainForm.playType[cBlack]=cUserPlayer) then
      begin selUser1.Checked:=true; disableLevel1; end
    else
      begin selComp1.Checked:=true; enableLevel1; end;

    selDiff2.Position:=MainForm.playLevel[cWhite];
    if (MainForm.playType[cWhite]=cUserPlayer) then
      begin selUser2.Checked:=true; disableLevel2; end
    else
      begin selComp2.Checked:=true; enableLevel2; end;
end;

{... synchronize level selectors with % indicators (with color select) ...}
procedure TSetupForm.syncLabels;
var
    str1 : String;
    greencolor, redcolor : LongInt;
    color : TColor;
begin
    greencolor:=((cMaxDepth-selDiff1.Position+1)*32-1);
    redcolor:=$FF-greencolor;
    color:=(greencolor*$FF)+redcolor;
    lblDiff1.Font.Color:=$0002000000+color;
    Str(selDiff1.Position*25,str1);
    lblDiff1.Caption:=str1+'%';

    greencolor:=((cMaxDepth-selDiff2.Position+1)*32-1);
    redcolor:=$FF-greencolor;
    color:=(greencolor*$FF)+redcolor;
    lblDiff2.Font.Color:=$0002000000+color;
    Str(selDiff2.Position*25,str1);
    lblDiff2.Caption:=str1+'%';
end;

{... disable computer-related selectors for Black player ...}
procedure TSetupForm.disableLevel1;
begin
    diff1.Enabled:=false;
    lblDiff1.Enabled:=false;
    selDiff1.Enabled:=false;
end;

{... enable computer-related selectors for Black player ...}
procedure TSetupForm.enableLevel1;
begin
    diff1.Enabled:=true;
    lblDiff1.Enabled:=true;
    selDiff1.Enabled:=true;
end;

{... disable computer-related selectors for White player ...}
procedure TSetupForm.disableLevel2;
begin
    diff2.Enabled:=false;
    lblDiff2.Enabled:=false;
    selDiff2.Enabled:=false;
end;

{... enable computer-related selectors for Black player ...}
procedure TSetupForm.enableLevel2;
begin
    diff2.Enabled:=true;
    lblDiff2.Enabled:=true;
    selDiff2.Enabled:=true;
end;

{... close form, send back selections ...}
procedure TSetupForm.btnOkClick(Sender: TObject);
begin
    setbackVariables;
    Hide;
end;

{... close form, discard any changes ...}
procedure TSetupForm.btnCancelClick(Sender: TObject);
begin
    Hide;
end;

{... syncronize level-1 selector with tag ...}
procedure TSetupForm.selDiff1Change(Sender: TObject);
begin
    syncLabels;
end;

{... synchronize level-2 selector with tag ...}
procedure TSetupForm.selDiff2Change(Sender: TObject);
begin
    syncLabels;
end;

{... restore form data ...}
procedure TSetupForm.FormShow(Sender: TObject);
begin
    updateIndicators;
    syncLabels;
end;

{... computer player-1 selected, enable levels  ...}
procedure TSetupForm.selComp1Click(Sender: TObject);
begin
    enableLevel1;
end;

{... user player-1 selected, disable levels ...}
procedure TSetupForm.selUser1Click(Sender: TObject);
begin
    disableLevel1;
end;

{... computer player-2 selected, enable levels ...}
procedure TSetupForm.selComp2Click(Sender: TObject);
begin
    enableLevel2;
end;

{... user player-2 selected, disable levels ...}
procedure TSetupForm.selUser2Click(Sender: TObject);
begin
    disableLevel2;
end;

end.
