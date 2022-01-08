echo -------------------------------------
echo     Nano-Pascal Compiler Builder     
echo -------------------------------------
echo
echo WORKING: Creating parser header file...
bison -d parser.y
echo
echo WORKING: Updating parser header file...
cat parser_h.add parser.tab.h >parser_t.tmp
rm parser.tab.h
mv parser_t.tmp parser.tab.h
echo
echo WORKING: Creating scanner code...
flex scanner.l
echo
echo WORKING: Creating parser code...
bison parser.y
echo
echo WORKING: Building compiler binary...
gcc parser.tab.c lex.yy.c -o nano.bin 
echo
echo WORKING: Building compiler executable...
gcc npc.c -o npc
echo
echo Compiler executable "npc" has been successfully created.
echo For a simple usage description, type:
echo                     "npc -?"  or  "npc -h"
echo at the command prompt. For more details about compiler
echo functionality and messages, please read the documentation files.
echo

