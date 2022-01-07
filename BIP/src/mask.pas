{
     ################################################
     ##    B.I.P. - Basic Image Processor, v1.0    ##
     ##                                            ##
     ##    File:  MASK.PAS                         ##
     ##    Description: Masks support unit         ##
     ##                                            ##
     ##    Harris Georgiou (c) 1999                ##
     ################################################
}


unit mask;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls, Buttons, SDIMAIN;

type
  TMaskForm = class(TForm)
    mask11: TEdit;
    mask21: TEdit;
    mask31: TEdit;
    mask12: TEdit;
    mask22: TEdit;
    mask32: TEdit;
    mask13: TEdit;
    mask23: TEdit;
    mask33: TEdit;
    maskcoeff: TEdit;
    maskbias: TEdit;
    mask: TGroupBox;
    maskd: TGroupBox;
    maskb: TGroupBox;
    BitBtn1: TBitBtn;
    BitBtn2: TBitBtn;
    procedure BitBtn2Click(Sender: TObject);
    procedure BitBtn1Click(Sender: TObject);
    procedure showmask(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  MaskForm: TMaskForm;

implementation

{$R *.DFM}

procedure TMaskForm.BitBtn2Click(Sender: TObject);
begin
    {...cancel mask input...}
    Close;
end;

procedure TMaskForm.BitBtn1Click(Sender: TObject);
var
    errcode : Integer;
begin
    {...read & store mask input...}
    Val(mask11.Text,maskval[0][0],errcode);
    Val(mask12.Text,maskval[0][1],errcode);
    Val(mask13.Text,maskval[0][2],errcode);
    Val(mask21.Text,maskval[1][0],errcode);
    Val(mask22.Text,maskval[1][1],errcode);
    Val(mask23.Text,maskval[1][2],errcode);
    Val(mask31.Text,maskval[2][0],errcode);
    Val(mask32.Text,maskval[2][1],errcode);
    Val(mask33.Text,maskval[2][2],errcode);

    if (maskcf=0) then maskcf:=1;
    Val(maskcoeff.Text,maskcf,errcode);
    Val(maskbias.Text,maskbs,errcode);

    {...execute with current mask...}
    Close;
    dogenericmask;
end;

procedure TMaskForm.showmask(Sender: TObject);
var
    tmpstr : String;
begin
    {...retrieve & show current mask...}
    Str(maskval[0][0],tmpstr); mask11.Text:=tmpstr;
    Str(maskval[0][1],tmpstr); mask12.Text:=tmpstr;
    Str(maskval[0][2],tmpstr); mask13.Text:=tmpstr;
    Str(maskval[1][0],tmpstr); mask21.Text:=tmpstr;
    Str(maskval[1][1],tmpstr); mask22.Text:=tmpstr;
    Str(maskval[1][2],tmpstr); mask23.Text:=tmpstr;
    Str(maskval[2][0],tmpstr); mask31.Text:=tmpstr;
    Str(maskval[2][1],tmpstr); mask32.Text:=tmpstr;
    Str(maskval[2][2],tmpstr); mask33.Text:=tmpstr;

    Str(maskcf,tmpstr); maskcoeff.Text:=tmpstr;
    Str(maskbs,tmpstr); maskbias.Text:=tmpstr;
end;

end.
