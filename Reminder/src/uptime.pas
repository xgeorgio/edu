unit Uptime;

interface

uses
  SysUtils, WinTypes, WinProcs, Messages, Classes, Graphics, Controls,
  Forms, StdCtrls, ExtCtrls, ComCtrls;

const
    copyright_str = 'Date/Time Reminder v1.5 - Harris Georgiou (c) 2001';
    inifile_str = 'dtr.ini';

type
  TForm1 = class(TForm)
    Timer1: TTimer;
    Panel1: TPanel;
    Panel10: TPanel;
    Panel13: TPanel;
    TimePick: TDateTimePicker;
    btnUpdate: TButton;
    btnSave: TButton;
    DatePick: TDateTimePicker;
    function read_aptm : Boolean;
    function write_aptm : Boolean;
    procedure resetForm;
    procedure updateForm;
    procedure reset(Sender: TObject);
    procedure update1(Sender: TObject);
    procedure updateAptm;
    procedure btnUpdateClick(Sender: TObject);
    procedure TimePickChange(Sender: TObject);
    procedure btnSaveClick(Sender: TObject);
    procedure DatePickChange(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form1: TForm1;
  dd, hh, mm, ss : LongInt;
  ticks : LongInt;
  dt_curr, dt_aptm, dt_diff : TDateTime;


implementation

{$R *.DFM}

procedure TForm1.updateForm;
var   tstr  :  string;
begin
    dt_curr := Now;
    dt_diff := dt_aptm-dt_curr;

    if (dt_diff<0) then
      begin Form1.Panel10.Caption:='Elapsed time:'; dt_diff:=-dt_diff; end
    else Form1.Panel10.Caption:='Remaining time:';

    ticks:=Round(dt_diff*LongInt(24*3600));

    dd:=ticks div LongInt(24*3600);
    ticks:=ticks mod LongInt(24*3600);

    hh:=ticks div LongInt(3600);
    ticks:=ticks mod LongInt(3600);

    mm:=ticks div LongInt(60);
    ticks:=ticks mod LongInt(60);

    ss:=ticks;

    tstr:=Concat(IntToStr(dd),'d ');
    tstr:=Concat(tstr,IntToStr(hh),'h ');
    tstr:=Concat(tstr,IntToStr(mm),'m ');
    tstr:=Concat(tstr,IntToStr(ss),'s ');

    Form1.Panel1.Caption:=tstr;
end;

procedure TForm1.resetForm;
begin
    Form1.Panel13.Caption:=copyright_str;

    if (read_aptm) then btnSave.Enabled:=false
    else  btnSave.Enabled:=true;

    DatePick.DateTime:=dt_aptm;
    TimePick.Time:=DatePick.Time;
    btnUpdate.Enabled:=False;
end;


function TForm1.write_aptm : Boolean;
var
  inifile : TextFile;
  dt_str : String;
begin
    {$I-}
    AssignFile(inifile,inifile_str);
    Rewrite(inifile);
    dt_str:=DateTimeToStr(dt_aptm);
    Writeln(inifile,dt_str);
    CloseFile(inifile);
    {$I+}

    if (IOResult=0) then write_aptm:=true
    else  write_aptm:=false;
end;


function TForm1.read_aptm : Boolean;
var
  inifile : TextFile;
  dt_str : String;
begin
  {$I-}
  AssignFile(inifile,inifile_str);
  System.Reset(inifile);
  Readln(inifile,dt_str);
  CloseFile(inifile);
  {$I+}

  if (IOResult=0) then
    begin dt_aptm:=StrToDateTime(dt_str); read_aptm:=true; end
  else
    begin dt_aptm:=Now; read_aptm:=false; end
end;

{--- event handlers ---}

procedure TForm1.reset(Sender: TObject);
begin
     resetForm;
     updateForm;
end;

procedure TForm1.update1(Sender: TObject);
begin
    updateForm;
end;

procedure TForm1.updateAptm;
begin
    DatePick.Time:=TimePick.Time;
    dt_aptm:=DatePick.DateTime;
    btnSave.Enabled:=true;
    updateForm;
end;

procedure TForm1.btnUpdateClick(Sender: TObject);
begin
    updateAptm;
    btnUpdate.Enabled:=False;
end;

procedure TForm1.TimePickChange(Sender: TObject);
begin
    btnUpdate.Enabled:=True;
end;

procedure TForm1.btnSaveClick(Sender: TObject);
begin
    if (write_aptm) then btnSave.Enabled:=false;
    updateForm;
end;

procedure TForm1.DatePickChange(Sender: TObject);
begin
    btnUpdate.Enabled:=True;
end;

end.
