{
     ################################################
     ##    B.I.P. - Basic Image Processor, v1.0    ##
     ##                                            ##
     ##    File:  SDIMAIN.PAS                      ##
     ##    Description: Main support unit          ##
     ##                                            ##
     ##    Harris Georgiou (c) 1999                ##
     ################################################
}


unit Sdimain;

interface

uses Windows, Classes, Graphics, Forms, Controls, Menus,
  Dialogs, StdCtrls, Buttons, ExtCtrls, ComCtrls, ImgList, StdActns,
  ActnList, ToolWin, ExtDlgs, SysUtils, Math;

const
   MaxImgValue = 256;         {...image pixel true value range...}
   MaxImgColor = 256;         {...image pixel display color range...}

   GenMaskNone  = 0;
   GenMaskEdge  = 1;
   GenMaskSharp = 2;

type
  TSDIAppForm = class(TForm)
    ToolBar1: TToolBar;
    ToolButton1: TToolButton;
    ToolButton2: TToolButton;
    ActionList1: TActionList;
    FileOpen1: TAction;
    FileSaveAs1: TAction;
    FileExit1: TAction;
    HelpAbout1: TAction;
    StatusBar: TStatusBar;
    ImageList1: TImageList;
    MainMenu1: TMainMenu;
    File1: TMenuItem;
    FileOpenItem: TMenuItem;
    FileSaveAsItem: TMenuItem;
    N1: TMenuItem;
    FileExitItem: TMenuItem;
    Help1: TMenuItem;
    HelpAboutItem: TMenuItem;
    Histogram1: TMenuItem;
    ShowHistogram1: TMenuItem;
    HideHistogram1: TMenuItem;
    N2: TMenuItem;
    Equalize1: TMenuItem;
    Normalize1: TMenuItem;
    N3: TMenuItem;
    AutoHist: TMenuItem;
    Image: TImage;
    OpenPictureDialog1: TOpenPictureDialog;
    SavePictureDialog1: TSavePictureDialog;
    FileCloseItem: TMenuItem;
    Update1: TMenuItem;
    Threshold1: TMenuItem;
    Manual1: TMenuItem;
    RelHist: TMenuItem;
    Optimal1: TMenuItem;
    Sharpening1: TMenuItem;
    Standard1: TMenuItem;
    Robert1: TMenuItem;
    Sobel1: TMenuItem;
    Edges1: TMenuItem;
    Sobel2: TMenuItem;
    Standard2: TMenuItem;
    Robert2: TMenuItem;
    N4: TMenuItem;
    Generic2: TMenuItem;
    N5: TMenuItem;
    Generic1: TMenuItem;
    FileClose1: TAction;
    ToolButton3: TToolButton;
    procedure FileOpen1Execute(Sender: TObject);
    procedure FileSave1Execute(Sender: TObject);
    procedure FileExit1Execute(Sender: TObject);
    procedure HelpAbout1Execute(Sender: TObject);
    procedure ShowHistogram1Click(Sender: TObject);
    procedure HideHistogram1Click(Sender: TObject);
    procedure initialize(Sender: TObject);
    procedure ToggleCheck(Sender: TObject);
    procedure FileClose1Execute(Sender: TObject);
    procedure Update1Click(Sender: TObject);
    procedure Manual1Click(Sender: TObject);
    procedure RelHistClick(Sender: TObject);
    procedure Equalize1Click(Sender: TObject);
    procedure Normalize1Click(Sender: TObject);
    procedure Optimal1Click(Sender: TObject);
    procedure Standard1Click(Sender: TObject);
    procedure Robert1Click(Sender: TObject);
    procedure Sobel1Click(Sender: TObject);
    procedure Sobel2Click(Sender: TObject);
    procedure Standard2Click(Sender: TObject);
    procedure Robert2Click(Sender: TObject);
    procedure Generic2Click(Sender: TObject);
    procedure Generic1Click(Sender: TObject);
    procedure ToolButton3Click(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

  THistArray = array [0..MaxImgColor-1] of LongInt;

var
  SDIAppForm: TSDIAppForm;
  histogram, lut : THistArray;          {...histogram & CDF arrays...}
  blankbmp, bmpfile : TBitmap;
  modified : Boolean;
  maskval : array [0..2] of array [0..2] of Integer;
  maskcf, maskbs : Integer;
  genmaskaction : Integer;

procedure FileSave;
procedure menus_enable;
procedure menus_disable;
function normdistr0( x : Extended ) : Extended;
procedure dogenericmask;
procedure genericedge;
procedure genericsharp;

implementation

uses About, Histo, Mask, Splash;

{$R *.DFM}

procedure TSDIAppForm.FileOpen1Execute(Sender: TObject);
var
   Done: Boolean;
begin
   OpenPictureDialog1.DefaultExt := GraphicExtension(TBitmap);
   OpenPictureDialog1.FileName := GraphicFileMask(TBitmap);
   OpenPictureDialog1.Filter := GraphicFilter(TBitmap);
   OpenPictureDialog1.Options := [ofFileMustExist, ofHideReadOnly ];

   Done:=false;

   while not Done do
   begin
     if OpenPictureDialog1.Execute then
     begin
       if not (ofExtensionDifferent in OpenPictureDialog1.Options) then
         begin
          bmpfile.LoadFromFile(OpenPictureDialog1.FileName);
          if (bmpfile.PixelFormat<>pf8bit) then
          begin
              MessageDlg('Image depth not 8-bit',mtError,[mbOK],0);
              Continue
          end
          else    {...valid file selected...}
              Done := True;  modified:=false;
              menus_enable;
              SDIAppForm.Image.Picture.Bitmap.Assign(bmpfile);
          end
       else   {...invalid file format...}
          begin
              MessageDlg('Image must be 8-bit grayscale bitmap',mtError,[mbOK],0);
              Continue
          end
     end
     else {...user cancelled...}
       Done := True
   end;

   if (AutoHist.Checked) then hist_calculate;
end;

procedure TSDIAppForm.FileSave1Execute(Sender: TObject);
begin
    FileSave;
end;

procedure FileSave;
var
   Done: Boolean;
begin
  with SDIAppForm do
  begin
   SavePictureDialog1.DefaultExt := GraphicExtension(TBitmap);
   SavePictureDialog1.FileName := GraphicFileMask(TBitmap);
   SavePictureDialog1.Filter := GraphicFilter(TBitmap);
   SavePictureDialog1.Options := [ ofOverwritePrompt, ofHideReadOnly, ofEnableSizing ];

   Done:=false;

   while not Done do
   begin
     if SavePictureDialog1.Execute then
     begin
       if not (ofExtensionDifferent in OpenPictureDialog1.Options) then
         begin
          SDIAppForm.Image.Picture.Bitmap.SaveToFile(SavePictureDialog1.FileName);
          Done := True;  modified:=false;   {...reset "modified" flag...}
         end
       else   {...invalid file format (force .BMP extension)...}
          begin
              MessageDlg('Image must be 8-bit grayscale bitmap',mtError,[mbOK],0);
              Continue
          end
     end
     else {...user cancelled...}
       Done := True;
   end;
  end;
end;

procedure TSDIAppForm.FileExit1Execute(Sender: TObject);
var
    resp : Word;
begin
   if (modified) then
   begin
      resp:=MessageDlg('Image has been changed. Save now?',mtWarning,[mbYes,mbNo,mbCancel],0);
      if ((resp<>mrYes)and(resp<>mrNo)) then Exit;   {cancel exit command}

      if (resp=mrYes) then FileSave;
   end;

   bmpfile.Free;
   blankbmp.Free;
   Close;
end;

procedure TSDIAppForm.HelpAbout1Execute(Sender: TObject);
begin
  AboutBox.ShowModal;
end;

procedure TSDIAppForm.ShowHistogram1Click(Sender: TObject);
begin
    if (HistForm.Visible<>TRUE) then
    begin
        ShowHistogram1.Enabled:=FALSE;
        HideHistogram1.Enabled:=TRUE;
        HistForm.Show;
    end;
end;

procedure TSDIAppForm.HideHistogram1Click(Sender: TObject);
begin
    if (HistForm.Visible<>FALSE) then
    begin
        ShowHistogram1.Enabled:=TRUE;
        HideHistogram1.Enabled:=FALSE;
        HistForm.Hide;
    end;
end;

procedure TSDIAppForm.initialize(Sender: TObject);
begin
    {...set initial state for application...}

    HideHistogram1.Enabled:=FALSE;
    Update1.Enabled:=false;
    menus_disable;

    genmaskaction:=GenMaskNone;
    maskcf:=1;

    bmpfile:=TBitmap.Create;
    blankbmp:=TBitmap.Create;
    modified:=false;
end;

procedure TSDIAppForm.ToggleCheck(Sender: TObject);
begin
    with AutoHist do Checked:=not Checked;
    with Update1 do Enabled:=not Enabled;
end;

procedure TSDIAppForm.FileClose1Execute(Sender: TObject);
var
   resp : Word;
begin
    if (modified) then
    begin
       resp:=MessageDlg('Image has been changed. Save now?',mtConfirmation,[mbYes,mbNo,mbCancel],0);
       if ((resp<>mrYes)and(resp<>mrNo)) then Exit;   {cancel close command}

       if (resp=mrYes) then FileSave
       else if (resp=mrNo) then modified:=false;   {...reset "modified" flag...}
    end;

    SDIAppForm.Image.Picture.Bitmap.Assign(blankbmp);
    hist_calculate;   {...reset histogram...}
    menus_disable;
end;

procedure TSDIAppForm.Update1Click(Sender: TObject);
begin
    hist_calculate;
end;

{... Thresholding: Manual ...}
procedure TSDIAppForm.Manual1Click(Sender: TObject);
var
  thrsStr: string;
  thrs, errcode : Integer;
  OK, resp, valid  :  Boolean;
  x, y : Integer;
  Pix : PByteArray;
begin
    {...read threshold value...}
    OK:=false;  resp:=false;  thrs:=0;
    while (not OK) do
    begin
        resp:=InputQuery('Manual Threshold', 'Give threshold value (0-255)', thrsStr);
        if (resp) then
          begin
            {$R-}
            Val(thrsStr,thrs,errcode);
            {$R+}
            valid:=(errcode=0)and((thrs>=0)and(thrs<=255));
            if (not valid) then MessageDlg('Error: Invalid threshold value',mtWarning,[mbOk],0)
            else  OK:=true;   {...user input completed OK...}
          end
        else  OK:=true;   {...cancel selected...}
    end;

    if (not resp) then Exit;    {...exit if action is cancelled...}

    Screen.Cursor:=crAppStart;

    {...execute thresholding...}
    with bmpfile do
    begin
      for y:=0 to Height-1 do
      begin
        Pix:=ScanLine[y];
        for x:=0 to Width-1 do
        begin
          if (Pix[x]<=thrs) then Pix[x]:=0
          else  Pix[x]:=MaxImgColor-1;
        end;
      end;
    end;

    SDIAppForm.Image.Picture.Bitmap.Assign(bmpfile);
    Screen.Cursor:=crDefault;
    modified:=true;
    if (AutoHist.Checked) then hist_calculate;
end;

procedure menus_enable;
begin
    SDIAppForm.Equalize1.Enabled:=true;
    SDIAppForm.Normalize1.Enabled:=true;
    SDIAppForm.ToolButton2.Enabled:=true;
    SDIAppForm.ToolButton3.Enabled:=true;
    SDIAppForm.FileCloseItem.Enabled:=true;
    SDIAppForm.FileSaveAsItem.Enabled:=true;
    SDIAppForm.Threshold1.Enabled:=true;
    SDIAppForm.Sharpening1.Enabled:=true;
    SDIAppForm.Edges1.Enabled:=true;
end;

procedure menus_disable;
begin
    SDIAppForm.Equalize1.Enabled:=false;
    SDIAppForm.Normalize1.Enabled:=false;
    SDIAppForm.ToolButton2.Enabled:=false;
    SDIAppForm.ToolButton3.Enabled:=false;
    SDIAppForm.FileCloseItem.Enabled:=false;
    SDIAppForm.FileSaveAsItem.Enabled:=false;
    SDIAppForm.Threshold1.Enabled:=false;
    SDIAppForm.Sharpening1.Enabled:=false;
    SDIAppForm.Edges1.Enabled:=false;
end;

procedure TSDIAppForm.RelHistClick(Sender: TObject);
begin
    with RelHist do Checked:=not Checked;
    hist_calculate;
end;

{... Histogram: Equallization ...}
procedure TSDIAppForm.Equalize1Click(Sender: TObject);
var
    x, y, c : Integer;
    Pix : PByteArray;
    neq : Real;
    ch : THistArray;
    p, max : Byte;
begin
    hist_calculate;    {...use current histogram...}
    Screen.Cursor:=crAppStart;

    {...initialize...}
    neq:=1.0*bmpfile.Width*bmpfile.Height/MaxImgColor;

    {...calculate maximum histogram value...}
    max:=0;
    for y:=0 to bmpfile.Height-1 do
      begin
        Pix:=bmpfile.ScanLine[y];
        for x:=0 to bmpfile.Width-1 do
            if (Pix[x]>max) then max:=Pix[x];
      end;

    {...perform histogram CDF...}
    ch[0]:=histogram[0];
    for c:=1 to MaxImgColor-1 do ch[c]:=ch[c-1]+histogram[c];

    for y:=0 to bmpfile.Height-1 do
      begin
        Pix:=bmpfile.ScanLine[y];
        for x:=0 to bmpfile.Width-1 do
          begin
          c:=Floor(ch[Pix[x]]/neq+0.5)-1;    {...-1 prevents value 256 byte overflow...}
          if (c<0) then p:=0 else p:=c;
          Pix[x]:=p;
          end;
      end;

    SDIAppForm.Image.Picture.Bitmap.Assign(bmpfile);
    Screen.Cursor:=crDefault;
    modified:=true;
    if (AutoHist.Checked) then hist_calculate;
end;

{... Histogram: Normalization ...}
procedure TSDIAppForm.Normalize1Click(Sender: TObject);
var
    x, y : Integer;
    Pix : PByteArray;
    pmax, pmin, prange : Byte;
begin
    Screen.Cursor:=crAppStart;

    {...calculate minimum and maximum histogram values...}
    pmax:=0;  pmin:=MaxImgColor-1;
    for y:=0 to bmpfile.Height-1 do
      begin
        Pix:=bmpfile.ScanLine[y];
        for x:=0 to bmpfile.Width-1 do
          begin
          if (Pix[x]>pmax) then pmax:=Pix[x];
          if (Pix[x]<pmin) then pmin:=Pix[x];
          end;
      end;

      prange:=pmax-pmin;
      if (prange<=0) then prange:=1;

    {...perform image normalization...}
    for y:=0 to bmpfile.Height-1 do
      begin
        Pix:=bmpfile.ScanLine[y];
        for x:=0 to bmpfile.Width-1 do
          Pix[x]:=(MaxImgColor-1)*(Pix[x]-pmin) div prange;
      end;

    SDIAppForm.Image.Picture.Bitmap.Assign(bmpfile);
    Screen.Cursor:=crDefault;
    modified:=true;
    if (AutoHist.Checked) then hist_calculate;
end;

{...standard Gaussian distribution function (m=0, s=1)...}
function normdistr0( x : Extended ) : Extended;
begin
     normdistr0:=1/Sqrt(2*Pi*1.0)*Exp(-Sqr(x-0.0)/(2*1.0));
end;

{... Thresholding: Optimal ...}
procedure TSDIAppForm.Optimal1Click(Sender: TObject);
var
    x, y, T, c : Integer;
    Pix : PByteArray;
    P1, P2, m1, m2, s1, s2, minerr : Extended;
    err : array [0..MaxImgColor-1] of Extended;
    N : LongInt;
    strT : String;
    ch : THistArray;
begin
    Screen.Cursor:=crAppStart;

    N:=bmpfile.Width*bmpfile.Height;
    for T:=0 to MaxImgColor-1 do err[T]:=0;

    {...create histogram CDF...}
    ch[0]:=histogram[0];
    for c:=1 to MaxImgColor-1 do ch[c]:=ch[c-1]+histogram[c];

    for T:=1 to MaxImgColor-1 do
    begin
       {...calculate P1 and P2...}
       P1:=ch[T-1]/N;  P2:=1-P1;

       {...calculate m1 and m2...}
       m1:=0;
       for c:=0 to T-1 do m1:=m1+c*histogram[c];
       if (ch[T-1]>0) then m1:=m1/ch[T-1];

       {Str(m1,strT);  strT:=Concat('Mean value #1 estimation: ',strT);
       Application.MessageBox(PChar(strT),'Completed',MB_OKCANCEL+MB_DEFBUTTON1);}

       m2:=0;
       for c:=T to MaxImgColor-1 do m2:=m2+c*histogram[c];
       if (N-ch[T-1]>0) then m2:=m2/(N-ch[T-1]);

       {Str(m2,strT);  strT:=Concat('Mean value #2 estimation: ',strT);
       Application.MessageBox(PChar(strT),'Completed',MB_OKCANCEL+MB_DEFBUTTON1);}

       {...calculate s1 and s2...}
       s1:=0;
       for c:=0 to T-1 do
          if (ch[T-1]>0) then s1:=s1+Sqr(c*histogram[c]/ch[T-1]-m1) else s1:=s1+Sqr(m1);
       if (ch[T-1]-1>0) then s1:=s1/(ch[T-1]-1);

       {Str(s1,strT);  strT:=Concat('Variance value #1 estimation: ',strT);
       Application.MessageBox(PChar(strT),'Completed',MB_OKCANCEL+MB_DEFBUTTON1);}

       s2:=0;
       for c:=T to MaxImgColor-1 do
          if (N-ch[T-1]-1>0) then s2:=s2+Sqr(c*histogram[c]/(N-ch[T-1])-m2) else s2:=s2+Sqr(m2);
       if (N-ch[T-1]-1>0) then s2:=s2/(N-ch[T-1]-1);

       {Str(s2,strT);  strT:=Concat('Variance value #2 estimation: ',strT);
       Application.MessageBox(PChar(strT),'Completed',MB_OKCANCEL+MB_DEFBUTTON1);}

       if (s1<=0) then s1:=1;
       if (s2<=0) then s2:=1;

       {...calculate histogram interpolation error...}
       err[T]:=0;
       for c:=0 to MaxImgColor-1 do
           err[T]:=err[T]+Sqr(histogram[c]/N-(P1*normdistr0((c-m1)/Sqrt(s1))+P2*normdistr0((c-m2)/Sqrt(s2))));
       err[T]:=err[T]/MaxImgColor;

       {Str(err[T],strT);  strT:=Concat('Mean error estimation: ',strT);
       Application.MessageBox(PChar(strT),'Completed',MB_OKCANCEL+MB_DEFBUTTON1);}
    end;

    {...find threshold with best fit...}
    T:=1;  minerr:=err[T];
    for c:=2 to MaxImgColor-1 do
        if (err[c]<minerr) then begin T:=c; minerr:=err[c]; end;

    {ProgressBox.finishGauge;}
    {Str(minerr,strT);  strT:=Concat('Minimum error estimation: ',strT);
    Application.MessageBox(PChar(strT),'Completed',MB_OKCANCEL+MB_DEFBUTTON1);}

    Str(T,strT);  strT:=Concat('Optimal threshold estimated at: ',strT);
    Application.MessageBox(PChar(strT),'Completed',MB_OKCANCEL+MB_DEFBUTTON1);

    with bmpfile do
    begin
      for y:=0 to Height-1 do
      begin
        Pix:=ScanLine[y];
        for x:=0 to Width-1 do
        begin
          if (Pix[x]<T) then Pix[x]:=0
          else  Pix[x]:=MaxImgColor-1;
        end;
      end;
    end;

    SDIAppForm.Image.Picture.Bitmap.Assign(bmpfile);
    Screen.Cursor:=crDefault;
    modified:=true;
    if (AutoHist.Checked) then hist_calculate;
end;

{... Sharpening: Standard ...}
procedure TSDIAppForm.Standard1Click(Sender: TObject);
var
    x, y, grad, maxgrad, errcode, thrs : Integer;
    Pix, Pixp1, Gpix : PByteArray;
    gradbmp : TBitmap;
    OK, resp, valid  :  Boolean;
    thrsStr : String;
begin
    {...read threshold value...}
    OK:=false;  resp:=false;  thrs:=0;
    while (not OK) do
    begin
        resp:=InputQuery('Standard Sharpening', 'Give threshold value (0-255)', thrsStr);
        if (resp) then
          begin
            {$R-}
            Val(thrsStr,thrs,errcode);
            {$R+}
            valid:=(errcode=0)and((thrs>=0)and(thrs<=255));
            if (not valid) then MessageDlg('Error: Invalid threshold value',mtWarning,[mbOk],0)
            else  OK:=true;   {...user input completed OK...}
          end
        else  OK:=true;   {...cancel selected...}
    end;

    if (not resp) then Exit;    {...exit if action is cancelled...}

    Screen.Cursor:=crAppStart;

    {...create gradient bitmap space...}
    gradbmp:=TBitmap.Create;
    gradbmp.Assign(bmpfile);

    {...calculate gradient upper bound...}
    maxgrad:=0;
    for y:=0 to bmpfile.Height-2 do
    begin
      Pix:=bmpfile.ScanLine[y];  Pixp1:=bmpfile.ScanLine[y+1];
      for x:=0 to bmpfile.Width-2 do
      begin
        grad:=Abs(Pix[x]-Pix[x+1])+Abs(Pix[x]-Pixp1[x]);
        if (grad>maxgrad) then maxgrad:=grad;
      end;
    end;

    {...construct raw (positive) gradient image...}
    for y:=0 to bmpfile.Height-2 do
    begin
      Pix:=bmpfile.ScanLine[y];  Pixp1:=bmpfile.ScanLine[y+1];
      Gpix:=gradbmp.ScanLine[y];
      for x:=0 to bmpfile.Width-2 do
      begin
        {...gradient function is 'Standard'...}
        grad:=Floor((Abs(Pix[x]-Pix[x+1])+Abs(Pix[x]-Pixp1[x]))/maxgrad*(MaxImgColor-1));
        if (grad>=thrs) then Gpix[x]:=grad else Gpix[x]:=Pix[x];
      end;
    end;

    {...copy right & bottom unused lines...}
    for y:=0 to gradbmp.Height-2 do
      begin
        Pix:=bmpfile.ScanLine[y];
        Gpix:=gradbmp.ScanLine[y];
        Gpix[gradbmp.Width-1]:=Pix[gradbmp.Width-1];
      end;

    Pix:=bmpfile.ScanLine[bmpfile.Height-1];
    Gpix:=gradbmp.ScanLine[gradbmp.Height-1];
    for x:=0 to gradbmp.Width-1 do Gpix[x]:=Pix[x];

    SDIAppForm.Image.Picture.Bitmap.Assign(gradbmp);
    Screen.Cursor:=crDefault;
    modified:=true;
    if (AutoHist.Checked) then hist_calculate;
end;

{... Sharpening: Robert ...}
procedure TSDIAppForm.Robert1Click(Sender: TObject);
var
    x, y, grad, maxgrad, errcode, thrs : Integer;
    Pix, Pixp1, Gpix : PByteArray;
    gradbmp : TBitmap;
    OK, resp, valid  :  Boolean;
    thrsStr : String;
begin
    {...read threshold value...}
    OK:=false;  resp:=false;  thrs:=0;
    while (not OK) do
    begin
        resp:=InputQuery('Robert Sharpening', 'Give threshold value (0-255)', thrsStr);
        if (resp) then
          begin
            {$R-}
            Val(thrsStr,thrs,errcode);
            {$R+}
            valid:=(errcode=0)and((thrs>=0)and(thrs<=255));
            if (not valid) then MessageDlg('Error: Invalid threshold value',mtWarning,[mbOk],0)
            else  OK:=true;   {...user input completed OK...}
          end
        else  OK:=true;   {...cancel selected...}
    end;

    if (not resp) then Exit;    {...exit if action is cancelled...}

    Screen.Cursor:=crAppStart;

    {...create gradient bitmap space...}
    gradbmp:=TBitmap.Create;
    gradbmp.Assign(bmpfile);

    {...calculate gradient upper bound...}
    maxgrad:=0;
    for y:=0 to bmpfile.Height-2 do
    begin
      Pix:=bmpfile.ScanLine[y];  Pixp1:=bmpfile.ScanLine[y+1];
      for x:=0 to bmpfile.Width-2 do
      begin
        {...gradient function is 'Robert'...}
        grad:=Abs(Pix[x]-Pixp1[x+1])+Abs(Pix[x+1]-Pixp1[x]);
        if (grad>maxgrad) then maxgrad:=grad;
      end;
    end;

    {...construct raw (positive) gradient image...}
    for y:=0 to bmpfile.Height-2 do
    begin
      Pix:=bmpfile.ScanLine[y];  Pixp1:=bmpfile.ScanLine[y+1];
      Gpix:=gradbmp.ScanLine[y];
      for x:=0 to bmpfile.Width-2 do
      begin
        {...gradient function is 'Robert'...}
        grad:=Floor((Abs(Pix[x]-Pixp1[x+1])+Abs(Pix[x+1]-Pixp1[x]))/maxgrad*(MaxImgColor-1));
        if (grad>=thrs) then Gpix[x]:=grad else Gpix[x]:=Pix[x];
      end;
    end;

    {...copy right & bottom unused lines...}
    for y:=0 to gradbmp.Height-2 do
      begin
        Pix:=bmpfile.ScanLine[y];
        Gpix:=gradbmp.ScanLine[y];
        Gpix[gradbmp.Width-1]:=Pix[gradbmp.Width-1];
      end;

    Pix:=bmpfile.ScanLine[bmpfile.Height-1];
    Gpix:=gradbmp.ScanLine[gradbmp.Height-1];
    for x:=0 to gradbmp.Width-1 do Gpix[x]:=Pix[x];

    SDIAppForm.Image.Picture.Bitmap.Assign(gradbmp);
    Screen.Cursor:=crDefault;
    modified:=true;
    if (AutoHist.Checked) then hist_calculate;
end;

{... Sharpening: Sobel ...}
procedure TSDIAppForm.Sobel1Click(Sender: TObject);
var
    x, y, grad, maxgrad, mingrad, thrs, errcode : Integer;
    Pix, Pixp1, Pixp2, Gpix : PByteArray;
    gradbmp : TBitmap;
    {tmpstr : String;}
    OK, resp, valid  :  Boolean;
    thrsStr : String;
begin
    {...read threshold value...}
    OK:=false;  resp:=false;  thrs:=0;
    while (not OK) do
    begin
        resp:=InputQuery('Sobel Sharpening', 'Give threshold value (0-255)', thrsStr);
        if (resp) then
          begin
            {$R-}
            Val(thrsStr,thrs,errcode);
            {$R+}
            valid:=(errcode=0)and((thrs>=0)and(thrs<=255));
            if (not valid) then MessageDlg('Error: Invalid threshold value',mtWarning,[mbOk],0)
            else  OK:=true;   {...user input completed OK...}
          end
        else  OK:=true;   {...cancel selected...}
    end;

    if (not resp) then Exit;    {...exit if action is cancelled...}

    Screen.Cursor:=crAppStart;

    {...create gradient bitmap space...}
    gradbmp:=TBitmap.Create;
    gradbmp.Assign(bmpfile);

    {...calculate gradient upper bound...}
    maxgrad:=0;  mingrad:=10000;
    for y:=0 to bmpfile.Height-3 do
    begin
      Pix:=bmpfile.ScanLine[y];
      Pixp1:=bmpfile.ScanLine[y+1];
      Pixp2:=bmpfile.ScanLine[y+2];
      for x:=0 to bmpfile.Width-3 do
      begin
        {...gradient function is 'Sobel'...}
        grad:=Abs(Pix[x]-Pix[x+2])+2*Abs(Pixp1[x]-Pixp1[x+2])+Abs(Pixp2[x]-Pixp2[x+2])
             +Abs(Pix[x]-Pixp2[x])+2*Abs(Pix[x+1]-Pixp2[x+1])+Abs(Pix[x+2]-Pixp2[x+2]);
        if (grad>maxgrad) then maxgrad:=grad;
        if (grad<mingrad) then mingrad:=grad;
      end;
    end;

    {Str(mingrad,tmpstr); tmpstr:=Concat('mingrad = ',tmpstr);
    MessageDlg(tmpstr,mtWarning,[mbOk],0);
    Str(maxgrad,tmpstr); tmpstr:=Concat('maxgrad = ',tmpstr);
    MessageDlg(tmpstr,mtWarning,[mbOk],0);}

    {...construct raw (positive) gradient image...}
    for y:=0 to bmpfile.Height-3 do
    begin
      Pix:=bmpfile.ScanLine[y];
      Pixp1:=bmpfile.ScanLine[y+1];
      Pixp2:=bmpfile.ScanLine[y+2];
      Gpix:=gradbmp.ScanLine[y];
      for x:=0 to bmpfile.Width-3 do
      begin
        {...gradient function is 'Sobel'...}
        grad:=Abs(Pix[x]-Pix[x+2])+2*Abs(Pixp1[x]-Pixp1[x+2])+Abs(Pixp2[x]-Pixp2[x+2])
             +Abs(Pix[x]-Pixp2[x])+2*Abs(Pix[x+1]-Pixp2[x+1])+Abs(Pix[x+2]-Pixp2[x+2]);
        {if ((grad<mingrad)or(grad>maxgrad)) then
        begin
            Str(grad,tmpstr); tmpstr:=Concat('Error: grad = ',tmpstr);
            MessageDlg(tmpstr,mtWarning,[mbOk],0);
        end
        else begin}
        grad:=Floor(((grad-mingrad)/(maxgrad-mingrad))*(MaxImgColor-1));
        if (grad>=thrs) then Gpix[x]:=grad else Gpix[x]:=Pix[x];
      end; {end;}
    end;

    {...remove right & bottom unused lines...}
    for y:=0 to gradbmp.Height-3 do
      begin
        Pix:=bmpfile.ScanLine[y];
        Gpix:=gradbmp.ScanLine[y];
        Gpix[gradbmp.Width-2]:=Pix[bmpfile.Width-2];
        Gpix[gradbmp.Width-1]:=Pix[bmpfile.Width-1];
      end;

    Gpix:=gradbmp.ScanLine[gradbmp.Height-2];
    Pix:=bmpfile.ScanLine[bmpfile.Height-2];
    for x:=0 to gradbmp.Width-1 do Gpix[x]:=Pix[x];

    Gpix:=gradbmp.ScanLine[gradbmp.Height-1];
    Pix:=bmpfile.ScanLine[bmpfile.Height-1];
    for x:=0 to gradbmp.Width-1 do Gpix[x]:=Pix[x];

    SDIAppForm.Image.Picture.Bitmap.Assign(gradbmp);
    Screen.Cursor:=crDefault;
    modified:=true;
    if (AutoHist.Checked) then hist_calculate;
end;

{... Edges: Standard ...}
procedure TSDIAppForm.Standard2Click(Sender: TObject);
var
    x, y, grad, maxgrad : Integer;
    Pix, Pixp1, Gpix : PByteArray;
    gradbmp : TBitmap;
begin
    Screen.Cursor:=crAppStart;

    {...create gradient bitmap space...}
    gradbmp:=TBitmap.Create;
    gradbmp.Assign(bmpfile);

    {...calculate gradient upper bound...}
    maxgrad:=0;
    for y:=0 to bmpfile.Height-2 do
    begin
      Pix:=bmpfile.ScanLine[y];  Pixp1:=bmpfile.ScanLine[y+1];
      for x:=0 to bmpfile.Width-2 do
      begin
        grad:=Abs(Pix[x]-Pix[x+1])+Abs(Pix[x]-Pixp1[x]);
        if (grad>maxgrad) then maxgrad:=grad;
      end;
    end;

    {...construct raw (positive) gradient image...}
    for y:=0 to bmpfile.Height-2 do
    begin
      Pix:=bmpfile.ScanLine[y];  Pixp1:=bmpfile.ScanLine[y+1];
      Gpix:=gradbmp.ScanLine[y];
      for x:=0 to bmpfile.Width-2 do
      begin
        {...gradient function is 'Standard'...}
        Gpix[x]:=Floor((Abs(Pix[x]-Pix[x+1])+Abs(Pix[x]-Pixp1[x]))/maxgrad*(MaxImgColor-1));
      end;
    end;

    {...copy right & bottom unused lines...}
    for y:=0 to gradbmp.Height-2 do
      begin
        Gpix:=gradbmp.ScanLine[y];
        Gpix[gradbmp.Width-1]:=0;
      end;

    Gpix:=gradbmp.ScanLine[gradbmp.Height-1];
    for x:=0 to gradbmp.Width-1 do Gpix[x]:=0;

    SDIAppForm.Image.Picture.Bitmap.Assign(gradbmp);
    Screen.Cursor:=crDefault;
    modified:=true;
    if (AutoHist.Checked) then hist_calculate;
end;

{... Edges: Robert ...}
procedure TSDIAppForm.Robert2Click(Sender: TObject);
var
    x, y, grad, maxgrad : Integer;
    Pix, Pixp1, Gpix : PByteArray;
    gradbmp : TBitmap;
begin
    Screen.Cursor:=crAppStart;

    {...create gradient bitmap space...}
    gradbmp:=TBitmap.Create;
    gradbmp.Assign(bmpfile);

    {...calculate gradient upper bound...}
    maxgrad:=0;
    for y:=0 to bmpfile.Height-2 do
    begin
      Pix:=bmpfile.ScanLine[y];  Pixp1:=bmpfile.ScanLine[y+1];
      for x:=0 to bmpfile.Width-2 do
      begin
        {...gradient function is 'Robert'...}
        grad:=Abs(Pix[x]-Pixp1[x+1])+Abs(Pix[x+1]-Pixp1[x]);
        if (grad>maxgrad) then maxgrad:=grad;
      end;
    end;

    {...construct raw (positive) gradient image...}
    for y:=0 to bmpfile.Height-2 do
    begin
      Pix:=bmpfile.ScanLine[y];  Pixp1:=bmpfile.ScanLine[y+1];
      Gpix:=gradbmp.ScanLine[y];
      for x:=0 to bmpfile.Width-2 do
      begin
        {...gradient function is 'Robert'...}
        Gpix[x]:=Floor((Abs(Pix[x]-Pixp1[x+1])+Abs(Pix[x+1]-Pixp1[x]))/maxgrad*(MaxImgColor-1));
      end;
    end;

    {...copy right & bottom unused lines...}
    for y:=0 to gradbmp.Height-2 do
      begin
        Gpix:=gradbmp.ScanLine[y];
        Gpix[gradbmp.Width-1]:=0;
      end;

    Gpix:=gradbmp.ScanLine[gradbmp.Height-1];
    for x:=0 to gradbmp.Width-1 do Gpix[x]:=0;

    SDIAppForm.Image.Picture.Bitmap.Assign(gradbmp);
    Screen.Cursor:=crDefault;
    modified:=true;
    if (AutoHist.Checked) then hist_calculate;
end;

{... Edges: Sobel ...}
procedure TSDIAppForm.Sobel2Click(Sender: TObject);
var
    x, y, grad, maxgrad, mingrad : Integer;
    Pix, Pixp1, Pixp2, Gpix : PByteArray;
    gradbmp : TBitmap;
    {tmpstr : String;
    errcode : Integer;}
begin
    Screen.Cursor:=crAppStart;

    {...create gradient bitmap space...}
    gradbmp:=TBitmap.Create;
    gradbmp.Assign(bmpfile);

    {...calculate gradient upper bound...}
    maxgrad:=0;  mingrad:=10000;
    for y:=0 to bmpfile.Height-3 do
    begin
      Pix:=bmpfile.ScanLine[y];
      Pixp1:=bmpfile.ScanLine[y+1];
      Pixp2:=bmpfile.ScanLine[y+2];
      for x:=0 to bmpfile.Width-3 do
      begin
        {...gradient function is 'Sobel'...}
        grad:=Abs(Pix[x]-Pix[x+2])+2*Abs(Pixp1[x]-Pixp1[x+2])+Abs(Pixp2[x]-Pixp2[x+2])
             +Abs(Pix[x]-Pixp2[x])+2*Abs(Pix[x+1]-Pixp2[x+1])+Abs(Pix[x+2]-Pixp2[x+2]);
        if (grad>maxgrad) then maxgrad:=grad;
        if (grad<mingrad) then mingrad:=grad;
      end;
    end;

    {Str(mingrad,tmpstr); tmpstr:=Concat('mingrad = ',tmpstr);
    MessageDlg(tmpstr,mtWarning,[mbOk],0);
    Str(maxgrad,tmpstr); tmpstr:=Concat('maxgrad = ',tmpstr);
    MessageDlg(tmpstr,mtWarning,[mbOk],0);}

    {...construct raw (positive) gradient image...}
    for y:=0 to bmpfile.Height-3 do
    begin
      Pix:=bmpfile.ScanLine[y];
      Pixp1:=bmpfile.ScanLine[y+1];
      Pixp2:=bmpfile.ScanLine[y+2];
      Gpix:=gradbmp.ScanLine[y];
      for x:=0 to bmpfile.Width-3 do
      begin
        {...gradient function is 'Sobel'...}
        grad:=Abs(Pix[x]-Pix[x+2])+2*Abs(Pixp1[x]-Pixp1[x+2])+Abs(Pixp2[x]-Pixp2[x+2])
             +Abs(Pix[x]-Pixp2[x])+2*Abs(Pix[x+1]-Pixp2[x+1])+Abs(Pix[x+2]-Pixp2[x+2]);
        {if ((grad<mingrad)or(grad>maxgrad)) then
        begin
            Str(grad,tmpstr); tmpstr:=Concat('Error: grad = ',tmpstr);
            MessageDlg(tmpstr,mtWarning,[mbOk],0);
        end
        else} Gpix[x]:=Floor(((grad-mingrad)/(maxgrad-mingrad))*(MaxImgColor-1));
      end;
    end;

    {...remove right & bottom unused lines...}
    for y:=0 to gradbmp.Height-3 do
      begin
        Gpix:=gradbmp.ScanLine[y];
        Gpix[gradbmp.Width-2]:=0;
        Gpix[gradbmp.Width-1]:=0;
      end;

    Gpix:=gradbmp.ScanLine[gradbmp.Height-2];
    for x:=0 to gradbmp.Width-1 do Gpix[x]:=0;

    Gpix:=gradbmp.ScanLine[gradbmp.Height-1];
    for x:=0 to gradbmp.Width-1 do Gpix[x]:=0;

    SDIAppForm.Image.Picture.Bitmap.Assign(gradbmp);
    Screen.Cursor:=crDefault;
    modified:=true;
    if (AutoHist.Checked) then hist_calculate;
end;

{... Edges: Generic (mask) ...}
procedure genericedge;
var
    x, y, mx, my : Integer;
    grad, maxgrad, mingrad : Integer;
    Pix : array [0..2] of PByteArray;
    Gpix : PByteArray;
    gradbmp : TBitmap;
    {tmpstr : String;
    errcode : Integer;}
begin
    Screen.Cursor:=crAppStart;

    {...create gradient bitmap space...}
    gradbmp:=TBitmap.Create;
    gradbmp.Assign(bmpfile);

    {...calculate gradient upper bound...}
    maxgrad:=0;  mingrad:=10000;
    for y:=0 to bmpfile.Height-3 do
    begin
      Pix[0]:=bmpfile.ScanLine[y];
      Pix[1]:=bmpfile.ScanLine[y+1];
      Pix[2]:=bmpfile.ScanLine[y+2];
      for x:=0 to bmpfile.Width-3 do
      begin
        {...gradient function is 'Generic mask'...}
        grad:=0;
        for my:=0 to 2 do
            for mx:=0 to 2 do
                grad:=grad+(maskval[my][mx]*Pix[my][x+mx]+maskbs) div maskcf;

        if (grad>maxgrad) then maxgrad:=grad;
        if (grad<mingrad) then mingrad:=grad;
      end;
    end;

    {Str(mingrad,tmpstr); tmpstr:=Concat('mingrad = ',tmpstr);
    MessageDlg(tmpstr,mtWarning,[mbOk],0);
    Str(maxgrad,tmpstr); tmpstr:=Concat('maxgrad = ',tmpstr);
    MessageDlg(tmpstr,mtWarning,[mbOk],0);}

    {...construct raw (positive) gradient image...}
    for y:=0 to bmpfile.Height-3 do
    begin
      Pix[0]:=bmpfile.ScanLine[y];
      Pix[1]:=bmpfile.ScanLine[y+1];
      Pix[2]:=bmpfile.ScanLine[y+2];
      Gpix:=gradbmp.ScanLine[y];
      for x:=0 to bmpfile.Width-3 do
      begin
        {...gradient function is 'Generic mask'...}
        grad:=0;
        for my:=0 to 2 do
            for mx:=0 to 2 do
                grad:=grad+(maskval[my][mx]*Pix[my][x+mx]+maskbs) div maskcf;

        {if ((grad<mingrad)or(grad>maxgrad)) then
        begin
            Str(grad,tmpstr); tmpstr:=Concat('Error: grad = ',tmpstr);
            MessageDlg(tmpstr,mtWarning,[mbOk],0);
        end
        else}  Gpix[x]:=Floor(((grad-mingrad)/(maxgrad-mingrad))*(MaxImgColor-1));
      end;
    end;

    {...remove right & bottom unused lines...}
    {for y:=0 to gradbmp.Height-3 do
      begin
        Gpix:=gradbmp.ScanLine[y];
        Gpix[gradbmp.Width-2]:=0;
        Gpix[gradbmp.Width-1]:=0;
      end;

    Gpix:=gradbmp.ScanLine[gradbmp.Height-2];
    for x:=0 to gradbmp.Width-1 do Gpix[x]:=0;

    Gpix:=gradbmp.ScanLine[gradbmp.Height-1];
    for x:=0 to gradbmp.Width-1 do Gpix[x]:=0;}

    SDIAppForm.Image.Picture.Bitmap.Assign(gradbmp);
    Screen.Cursor:=crDefault;
    modified:=true;
    if (SDIAppForm.AutoHist.Checked) then hist_calculate;
end;

{... Sharpening: Generic (mask) ...}
procedure genericsharp;
var
    x, y, mx, my : Integer;
    grad, maxgrad, mingrad, errcode, thrs : Integer;
    Pix : array [0..2] of PByteArray;
    Gpix : PByteArray;
    gradbmp : TBitmap;
    {tmpstr : String;
    errcode : Integer;}
    OK, resp, valid  :  Boolean;
    thrsStr : String;
begin
    {...read threshold value...}
    OK:=false;  resp:=false;  thrs:=0;
    while (not OK) do
    begin
        resp:=InputQuery('Generic Sharpening', 'Give threshold value (0-255)', thrsStr);
        if (resp) then
          begin
            {$R-}
            Val(thrsStr,thrs,errcode);
            {$R+}
            valid:=(errcode=0)and((thrs>=0)and(thrs<=255));
            if (not valid) then MessageDlg('Error: Invalid threshold value',mtWarning,[mbOk],0)
            else  OK:=true;   {...user input completed OK...}
          end
        else  OK:=true;   {...cancel selected...}
    end;

    if (not resp) then Exit;    {...exit if action is cancelled...}

    Screen.Cursor:=crAppStart;

    {...create gradient bitmap space...}
    gradbmp:=TBitmap.Create;
    gradbmp.Assign(bmpfile);

    {...calculate gradient upper bound...}
    maxgrad:=0;  mingrad:=10000;
    for y:=0 to bmpfile.Height-3 do
    begin
      Pix[0]:=bmpfile.ScanLine[y];
      Pix[1]:=bmpfile.ScanLine[y+1];
      Pix[2]:=bmpfile.ScanLine[y+2];
      for x:=0 to bmpfile.Width-3 do
      begin
        {...gradient function is 'Generic mask'...}
        grad:=0;
        for my:=0 to 2 do
            for mx:=0 to 2 do
                grad:=grad+(maskval[my][mx]*Pix[my][x+mx]+maskbs) div maskcf;

        if (grad>maxgrad) then maxgrad:=grad;
        if (grad<mingrad) then mingrad:=grad;
      end;
    end;

    {Str(mingrad,tmpstr); tmpstr:=Concat('mingrad = ',tmpstr);
    MessageDlg(tmpstr,mtWarning,[mbOk],0);
    Str(maxgrad,tmpstr); tmpstr:=Concat('maxgrad = ',tmpstr);
    MessageDlg(tmpstr,mtWarning,[mbOk],0);}

    {...construct raw (positive) gradient image...}
    for y:=0 to bmpfile.Height-3 do
    begin
      Pix[0]:=bmpfile.ScanLine[y];
      Pix[1]:=bmpfile.ScanLine[y+1];
      Pix[2]:=bmpfile.ScanLine[y+2];
      Gpix:=gradbmp.ScanLine[y];
      for x:=0 to bmpfile.Width-3 do
      begin
        {...gradient function is 'Generic mask'...}
        grad:=0;
        for my:=0 to 2 do
            for mx:=0 to 2 do
                grad:=grad+(maskval[my][mx]*Pix[my][x+mx]+maskbs) div maskcf;

        {if ((grad<mingrad)or(grad>maxgrad)) then
        begin
            Str(grad,tmpstr); tmpstr:=Concat('Error: grad = ',tmpstr);
            MessageDlg(tmpstr,mtWarning,[mbOk],0);
        end
        else}
        grad:=Floor(((grad-mingrad)/(maxgrad-mingrad))*(MaxImgColor-1));
        if (grad>=thrs) then Gpix[x]:=grad else Gpix[x]:=Pix[0][x];
      end;
    end;

    {...remove right & bottom unused lines...}
    {for y:=0 to gradbmp.Height-3 do
      begin
        Gpix:=gradbmp.ScanLine[y];
        Gpix[gradbmp.Width-2]:=0;
        Gpix[gradbmp.Width-1]:=0;
      end;

    Gpix:=gradbmp.ScanLine[gradbmp.Height-2];
    for x:=0 to gradbmp.Width-1 do Gpix[x]:=0;

    Gpix:=gradbmp.ScanLine[gradbmp.Height-1];
    for x:=0 to gradbmp.Width-1 do Gpix[x]:=0;}

    SDIAppForm.Image.Picture.Bitmap.Assign(gradbmp);
    Screen.Cursor:=crDefault;
    modified:=true;
    if (SDIAppForm.AutoHist.Checked) then hist_calculate;
end;

procedure dogenericmask;
begin
    if (genmaskaction=GenMaskEdge) then genericedge
    else if (genmaskaction=GenMaskSharp) then genericsharp
    else  Exit;
end;

procedure TSDIAppForm.Generic1Click(Sender: TObject);
begin
    {...read mask values & execute...}
    genmaskaction:=GenMaskSharp;
    MaskForm.Show;
end;

procedure TSDIAppForm.Generic2Click(Sender: TObject);
begin
    {...read mask values & execute...}
    genmaskaction:=GenMaskEdge;
    MaskForm.Show;
end;

{..."close" button on toolbar...}
procedure TSDIAppForm.ToolButton3Click(Sender: TObject);
var
   resp : Word;
begin
    if (modified) then
    begin
       resp:=MessageDlg('Image has been changed. Save now?',mtConfirmation,[mbYes,mbNo,mbCancel],0);
       if ((resp<>mrYes)and(resp<>mrNo)) then Exit;   {cancel close command}

       if (resp=mrYes) then FileSave
       else if (resp=mrNo) then modified:=false;   {...reset "modified" flag...}
    end;

    SDIAppForm.Image.Picture.Bitmap.Assign(blankbmp);
    hist_calculate;
    menus_disable;
end;

end.
