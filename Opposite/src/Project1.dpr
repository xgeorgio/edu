(*
   * * * * * * * * * * * * * * * * * * * * * * * *
   *                                             *
   *      ApplName:  OPPOSITE                    *
   *      FileName:  project1.pas                *
   *   Description:  Application file            *
   *                                             *
   *        Author:  Harris Georgiou (c) 2000.   *
   *       Contact:  mailto:xgeorgio@hol.gr      *
   *                                             *
   * * * * * * * * * * * * * * * * * * * * * * * *
*)


program Project1;

uses
  Forms,
  opposite in 'opposite.pas' {MainForm},
  about in 'about.pas' {AboutBox},
  setup in 'setup.pas' {SetupForm},
  Minimax in 'Minimax.pas',
  Defines in 'Defines.pas';

{$R *.RES}

begin
  Application.Initialize;
  Application.Title := 'OPPOSITE';
  Application.CreateForm(TMainForm, MainForm);
  Application.CreateForm(TAboutBox, AboutBox);
  Application.CreateForm(TSetupForm, SetupForm);
  Application.Run;
end.
