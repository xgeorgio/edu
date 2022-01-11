{ Game Of Life, v1.2
  Harris Georgiou (c) 1993
}

{============================================================================}


program gol;

uses crt;

const
      dimsize = 44;                         { maximu dimension of the game matrix }
      EXIST = '*';  EMPTY = ' ';            { constants for each 'person' }
      BORN = 2;  SURV = 1;  DIE = 0;        { constants for each 'fture' }

type
      index   =  1..dimsize;                { matrix index for 'last' and 'next' }
      person  =  char;                      { =  EXIST, EMPTY }
      place   =  array[ index , index ] of person;   { game matrix }

var
      last         :  place;            { previous game matrix }
      next         :  place;            { next game matrix }
      generations  :  Integer;          { total generations (-1) }
      currentgenr  :  Integer;          { current generation }
      totalpersons :  Word;             { person counter per generation }
      future       :  Integer;          { temp variable for outcome }
      i, j         :  index;            { temp indices }
      origmode     :  Integer;          { keep original text mode }
      cont1, cont2 :  Boolean;          { continue flags }


{----------------------------- PROCEDURES ---------------------------}



{input seed generation via user input}
procedure kbrdinput( var arr : place; var totalprs : Word );
var
     x, y   :   Byte;

begin
     totalprs:=0;
     while (TRUE) do
          begin
          writeln('Give position coordinates - ( dim: ',dimsize,'x',dimsize,' )');
          write('(give: 0,0 for finish)   >  ');
          highvideo;
          readln( x, y );
          normvideo;
          if ( (x=0) and (y=0) ) then Break                                     { check for finish }
             else if ( (x>dimsize) or (y>dimsize) or (x<1) or (y<1) ) then      { check valid ranges }
                  begin
                  sound( 550 ); delay( 300 ); nosound;
                  writeln('ERROR: Coordinates out of bounds.');
                  Continue;
                  end
                  else
                      begin
                      arr[ x, y ] := EXIST;                                     { else store position }
                      Inc( totalprs );
                      end;
          end;

          writeln;
          writeln('Generation seeding is completed...');

end;




{input seed generation via test file}
procedure fileinput( var arr : place; var totalprs : Word );
var
     x, y        :   Byte;
     filename    :   String[128];
     filehd      :   Text;
     ioerr       :   Integer;

begin
     totalprs:=0;
     write('Give full path to seed generation text file: ');
     highvideo;
     readln( filename );
     normvideo;
     writeln;
     assign( filehd, filename );
{$I-}
     Reset( filehd );
     ioerr:=IOResult;
{$I+}
     if ioerr<>0 then                                                           { check for file I/O error on open }
         begin
         sound( 550 ); delay( 300 ); nosound;
         writeln('ERROR: File ',filename,' cannot be opened.');
         writeln('                              Error code: ',ioerr);
         writeln;
         textmode(origmode);                    { restore text mode }
         writeln(' Exiting...');
         Halt(1);
         end;

     writeln('Reading seed generation from file: ',filename);

     while ( not EOF(filehd) ) do                                               { main file input process }
          begin
          while ( not EOLn(filehd) ) do
               begin
               Read( filehd, x, y );
               if not ( (x>dimsize) or (y>dimsize) or (x<1) or (y<1) ) then
                  begin
                  arr[ x, y ] := EXIST;
                  Inc( totalprs );
                  end;
               end;
          if ( not EOF(filehd) ) then readln( filehd );
          end;

     writeln('File reading completed...');
     Close( filehd );

end;




{input seed generation via randomization}
procedure randinput( var arr : place; var totalprs : Word );
var
     x, y      :   Byte;
     c, epil   :   Integer;

begin
     totalprs:=0;
     while (TRUE) do
          begin
          write('Give total number of seeding positions: ');
          highvideo;
          readln( epil );
          normvideo;
          if (epil<=0) then Continue else Break;
          end;

     Randomize;
     for c:=1 to epil do
         begin
         x := Random( dimsize-1 ) + 1;
         y := Random( dimsize-1 ) + 1;
         if (arr[x,y]=EMPTY) then
             begin
             arr[ x, y ] := EXIST;
             Inc( totalprs );
             end;
         end;

     writeln('Random seeding completed...');

end;




{input seed generation - main procedure}
procedure inputgeneration( var arr : place; var geners : Integer; var totalprs : Word );
var
     inpmode   :    Integer;

begin
     clrscr;
     writeln('GAME OF LIFE');
     writeln('=========================');
     writeln('Game area size: ',dimsize,'x',dimsize);
     writeln('-------------------------');
     writeln;

     while (TRUE) do
          begin
          writeln('Initialize seed generation from: ');
          write('            (1)keyboard / (2)textfile / (3)random / (0)EXIT ? ');
          highvideo;
          readln( inpmode );
          lowvideo;
          writeln;
          if ( (inpmode<0) or (inpmode>3) ) then Continue else Break;
          end;

     case inpmode of                                                            
          0 :  begin
               clrscr;
               textmode(origmode);                            {restore text mode}
               writeln('Exiting...');
               Halt(0);
               end;
          1 :  kbrdinput( arr, totalprs );
          2 :  fileinput( arr, totalprs );
          3 :  randinput( arr, totalprs );
          end;

     writeln;
     write('Give number of generations to run (<0  ===>  infinite): ');
     highvideo;
     readln( geners );
     normvideo;

end;




{display current game area / generation}
procedure printgeneration( var arr : place; geners : Integer; totalprs : Word; var cont : Boolean );

var
     i, j   :   index;
     resp   :   String[10];

begin
     clrscr;
     write('RESULT:  Generation = ');
     highvideo;
     write( geners );
     lowvideo;
     write('  ,  Number of persons = ');
     highvideo;
     write( totalprs );
     lowvideo;
     writeln;

     writeln('===============================================================================');

     write('+');
     for i:=1 to dimsize do write('+');
     write('+');
     writeln;

     for i:=1 to dimsize do
         begin
         write('+');
         highvideo;
         for j:=1 to dimsize do write( arr[ j, i ]:1 );
         normvideo;
         write('+');
         writeln;
         end;

     write('+');
     for i:=1 to dimsize do write('+');
     write('+');
     writeln;

     write('Press ENTER to continue... ''Q'' <enter> to finish...');
     highvideo;
     readln( resp );
     normvideo;

     if ( (resp[1]='Q') or (resp[1]='q') ) then cont:=FALSE;

end;




{check matrix index}
function chkpoint( var arr : place;  i, j : index ) : Byte;
begin
     if (arr[ i, j ]=EXIST) then chkpoint:=1 else chkpoint:=0;
end;




{check neighbours, with out-of-range checking}
function checkplace( var arr : place;  i, j : index ) : Byte;
var
     x, y    :  Byte;
     count   :  Byte;
     chk     :  Boolean;

begin
     count:=0;
     for x:=i-1 to i+1 do
         begin
         for y:=j-1 to j+1 do
             begin
             chk := ( (x<1) or (y<1) or (x>dimsize) or (y>dimsize) or ((x=i) and (y=j)) );
             if (not chk) then count:=count+chkpoint( arr, x, y );
             end;
         end;
     checkplace := count;
end;




{generate next status based on current neighbours}
procedure newplace( var oldarr, newarr : place;  i, j : index; var prsfuture : Integer );
var
     n   :   Byte;

begin
     n := checkplace( last, i, j );

     if ( ((n<=1) or (n>=4)) and (oldarr[i,j]=EXIST) ) then
         begin
         newarr[i,j]:=EMPTY;
         prsfuture:=DIE;
         end
     else if ( (n=3) and (oldarr[i,j]=EMPTY) ) then
         begin
         newarr[i,j]:=EXIST;
         prsfuture:=BORN;
         end
     else
         begin
         newarr[i,j]:=oldarr[i,j];
         prsfuture:=SURV;
         end;

end;




{============================== MAIN PROGRAM =============================}


begin
     origmode:=Lastmode;                        {store original text mode}
     textmode(CO80+Font8x8);                    {new mode = colour 80x50 VGA (or 80x43 EGA)}

     while (TRUE) do
         begin
         cont1:=TRUE;
         for i:=1 to dimsize do
             for j:=1 to dimsize do
                 begin
                 last[i,j]:=EMPTY;                  
                 next[i,j]:=EMPTY;
                 end;

         generations:=0;                            
         totalpersons:=0;
         future:=SURV;

         inputgeneration( last, generations, totalpersons );        {initialize seed generation}
         printgeneration( last, 1, totalpersons, cont1 );           {display seed generation}
         if (not cont1) then Continue;

         currentgenr:=2;
         cont2:=TRUE;
         while ( (currentgenr <> generations+1) and (cont2) ) do
             begin

              for i:=1 to dimsize do
                 begin

                  for j:=1 to dimsize do
                     begin
                      newplace( last, next, i, j, future );         {check neighbours, update status}
                      case future of                                
                        BORN: Inc( totalpersons );
                        DIE : Dec( totalpersons );
                        end;
                     end;

                 end;

              for i:=1 to dimsize do
                   for j:=1 to dimsize do last[i,j]:=next[i,j];

              printgeneration( last, currentgenr, totalpersons, cont2 );           {display updated generation}
              if (not cont2) then cont1:=FALSE;

              Inc( currentgenr );

             end;

             if (not cont1) then Continue;

     end;

end.



{============================================================================}

