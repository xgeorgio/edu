{
     ################################################
     ##    B.I.P. - Basic Image Processor, v1.0    ##
     ##                                            ##
     ##    File:  SDIAPP.PAS                       ##
     ##    Description: Main program file          ##
     ##                                            ##
     ##    Harris Georgiou (c) 1999                ##
     ################################################
}


program Sdiapp;

uses
  Forms,
  SDIMAIN in 'SDIMAIN.pas' {SDIAppForm},
  About in 'ABOUT.PAS' {AboutBox},
  Histo in 'Histo.pas' {HistForm},
  mask in 'mask.pas' {MaskForm},
  splash in 'splash.pas' {SplashForm};

{$R *.RES}

begin
  Application.Initialize;
  Application.Title := 'B.I.P. - Basic Image Processor';
  Application.CreateForm(TSDIAppForm, SDIAppForm);
  Application.CreateForm(TAboutBox, AboutBox);
  Application.CreateForm(THistForm, HistForm);
  Application.CreateForm(TMaskForm, MaskForm);
  Application.CreateForm(TSplashForm, SplashForm);
  Application.Run;
end.
 
