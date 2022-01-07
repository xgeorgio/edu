program Systime;

uses
  Forms,
  Uptime in 'UPTIME.PAS' {Form1};

{$R *.RES}

begin
  Application.Title := 'System Uptime';
  Application.CreateForm(TForm1, Form1);
  Application.Run;
end.
