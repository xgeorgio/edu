program SysTime;

uses
  Forms,
  Uptime in 'UPTIME.PAS' {Form1};

{$R *.RES}

begin
  Application.Title := 'Date/Time Reminder';
  Application.CreateForm(TForm1, Form1);
  Application.Run;
end.
