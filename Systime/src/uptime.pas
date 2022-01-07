unit Uptime;

interface

uses
  SysUtils, WinTypes, WinProcs, Messages, Classes, Graphics, Controls,
  Forms, StdCtrls, ExtCtrls;

const
    copyright_str = 'System UpTime, v1.5 - Harris Georgiou (c) 2001.';

type
  TForm1 = class(TForm)
    Timer1: TTimer;
    Panel1: TPanel;
    Panel4: TPanel;
    Panel5: TPanel;
    Panel10: TPanel;
    Panel11: TPanel;
    Panel12: TPanel;
    Panel13: TPanel;
    Bevel1: TBevel;
    procedure resetForm;
    procedure updateForm;
    procedure reset(Sender: TObject);
    procedure updateTime(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form1: TForm1;
  starttag, difftag  :  TDateTime;
  dd, dd1, hh, mm, ss, ms : LongInt;
  memload : Word;
  ticks, memsize : LongInt;

implementation

{$R *.DFM}

procedure TForm1.updateForm;
var
    tstr  :  string;
    meminfo : MEMORYSTATUS;
begin
    ticks:=GetTickCount;

    dd:=ticks div (LongInt(24*3600)*1000);
    if (dd<dd1) then
        begin Inc(dd1); dd:=dd+dd1*49; end;
    ticks:=ticks mod (LongInt(24*3600)*1000);
    hh:=ticks div (LongInt(3600)*1000);
    ticks:=ticks mod (LongInt(3600)*1000);
    mm:=ticks div (LongInt(60)*1000);
    ticks:=ticks mod (LongInt(60)*1000);
    ss:=ticks div (1000);
    ticks:=ticks mod (1000);
    ms:=ticks;

    tstr:=Concat(IntToStr(dd),'d ');
    tstr:=Concat(tstr,IntToStr(hh),'h ');
    tstr:=Concat(tstr,IntToStr(mm),'m ');
    tstr:=Concat(tstr,IntToStr(ss),'s ');
    {tstr:=Concat(tstr,IntToStr(ms),'ms ');}

    meminfo.dwLength:=SizeOf(MEMORYSTATUS);
    GlobalMemoryStatus(meminfo);
    memload:=meminfo.dwMemoryLoad;
    memsize:=meminfo.dwTotalPhys;

    Form1.Panel5.Caption:=Concat(IntToStr(memsize div 1024),'K');
    Form1.Panel12.Caption:=Concat(IntToStr(memload),'%');
    Form1.Panel1.Caption:=tstr;
end;

procedure TForm1.resetForm;
begin
    starttag:=Now;  dd1:=0;
    Form1.Panel13.Caption:=copyright_str;
end;

{--- event handlers ---}

procedure TForm1.reset(Sender: TObject);
begin
     resetForm;
     updateForm;
end;

procedure TForm1.updateTime(Sender: TObject);
begin
    updateForm;
end;

end.
