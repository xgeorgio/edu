{
     ################################################
     ##    B.I.P. - Basic Image Processor, v1.0    ##
     ##                                            ##
     ##    File:  SPLASH.PAS                       ##
     ##    Description: Splash screen file         ##
     ##                                            ##
     ##    Harris Georgiou (c) 1999                ##
     ################################################
}


unit splash;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  ExtCtrls, StdCtrls;

type
  TSplashForm = class(TForm)
    Timer1: TTimer;
    Image1: TImage;
    procedure hidesplash(Sender: TObject);
    procedure showsplash(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  SplashForm: TSplashForm;

implementation

{$R *.DFM}

procedure TSplashForm.hidesplash(Sender: TObject);
begin
    Close;
end;

procedure TSplashForm.showsplash(Sender: TObject);
begin
    Show;
end;

end.
