{
     ################################################
     ##    B.I.P. - Basic Image Processor, v1.0    ##
     ##                                            ##
     ##    File:  ABOUT.PAS                        ##
     ##    Description: Application info           ##
     ##                                            ##
     ##    Harris Georgiou (c) 1999                ##
     ################################################
}


unit About;

interface

uses Windows, Classes, Graphics, Forms, Controls, StdCtrls,
  Buttons, ExtCtrls;

type
  TAboutBox = class(TForm)
    Panel1: TPanel;
    OKButton: TButton;
    ProgramIcon: TImage;
    ProductName: TLabel;
    Version: TLabel;
    Copyright: TLabel;
    Comments: TLabel;
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  AboutBox: TAboutBox;

implementation

{$R *.DFM}

end.
 
