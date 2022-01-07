{
     ################################################
     ##    B.I.P. - Basic Image Processor, v1.0    ##
     ##                                            ##
     ##    File:  HISTO.PAS                        ##
     ##    Description: Histogram support unit     ##
     ##                                            ##
     ##    Harris Georgiou (c) 1999                ##
     ################################################
}


unit Histo;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  ExtCtrls;

type
  THistForm = class(TForm)
    HistImage: TImage;
    procedure DisableHistogram(Sender: TObject; var Action: TCloseAction);
    procedure CalculateHistogram(Sender: TObject);
    procedure ResizeHistogram(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  HistForm: THistForm;

procedure hist_calculate;
procedure hist_updatewin;

implementation

uses SDIMAIN;

{$R *.DFM}

var
    chist : Integer;
    updated : Boolean;
    MaxHist : LongInt;

procedure THistForm.DisableHistogram(Sender: TObject;
  var Action: TCloseAction);
begin
    SDIAppForm.ShowHistogram1.Enabled:=TRUE;
    SDIAppForm.HideHistogram1.Enabled:=FALSE;
    HistForm.Hide;
end;

procedure THistForm.CalculateHistogram(Sender: TObject);
begin
    hist_calculate;     {...calculate histogram...}
    hist_updatewin;     {...update histogram window...}
end;

procedure THistForm.ResizeHistogram(Sender: TObject);
begin
    hist_updatewin;  {...update histogram window...}
end;

{... Histogram: Calculate ...}
procedure hist_calculate;
var
    x, y, chist : Integer;
    Pix : PByteArray;
begin
    Screen.Cursor:=crAppStart;

    MaxHist:=1;
    for chist:=0 to MaxImgColor-1 do
      histogram[chist]:=0;

    with SDIAppForm.Image.Picture do
    begin
      for y:=0 to Bitmap.Height-1 do
      begin
        Pix:=Bitmap.ScanLine[y];
        for x:=0 to Bitmap.Width-1 do
        begin
          Inc(histogram[Pix[x]]);
        end;
      end;
    end;

    if (SDIAppForm.RelHist.Checked) then
      begin   {...show relative histogram...}
         for chist:=0 to MaxImgColor-1 do
            if histogram[chist]>MaxHist then MaxHist:=histogram[chist];
      end
    else
      begin   {...show absolute histogram...}
         with SDIAppForm.Image.Picture do MaxHist:=Bitmap.Height*Bitmap.Width;
         if (MaxHist<1) then MaxHist:=1;
      end;

    if (HistForm.Visible) then    {...update histogram window, if visible...}
      begin hist_updatewin; updated:=true; end
    else updated:=false;

    Screen.Cursor:=crDefault;
end;

{... Histogram: Update window ...}
procedure hist_updatewin;
begin
    if (HistForm.Visible<>true) then exit;  {...update only if visible...}

    Screen.Cursor:=crAppStart;
    HistForm.HistImage.Canvas.brush.style := bsSolid;

    HistForm.HistImage.Canvas.brush.color := clWhite;
    HistForm.HistImage.Canvas.FillRect(Rect(0,
      0,HistForm.HistImage.Width,HistForm.HistImage.Height));

    HistForm.HistImage.Canvas.brush.color := clBlack;

    chist:=1;
    while (chist<=MaxImgColor) do
    begin
        HistForm.HistImage.Canvas.FillRect(Rect(
          chist*HistForm.HistImage.Picture.Bitmap.Width div (MaxImgColor+1),
          HistForm.HistImage.Picture.Bitmap.Height-(histogram[chist-1]*HistForm.HistImage.Picture.Bitmap.Height div MaxHist),
          (chist+1)*HistForm.HistImage.Picture.Bitmap.Width div (MaxImgColor+1),
          HistForm.HistImage.Picture.Bitmap.Height));
        Inc(chist);
    end;
    updated:=true;
    Screen.Cursor:=crDefault;
end;

end.
