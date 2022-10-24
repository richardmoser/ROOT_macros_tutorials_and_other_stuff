/// \file
/// \ingroup Tutorials
/// Example of `rootlogon.C`.
/// The macro `rootlogon.C` in the current working directory, is executed when
/// `root` starts unless the option `-n` is used.
///
/// \macro_code
///
/// \author Rene Brun

{
printf("\033[31m\n");
printf("                                                     ___\n"
"                                                  ,o88888\n"
"                                               ,o8888888'\n"
"                         ,:o:o:oooo.        ,8O88Pd8888\"\n"
"                     ,.::.::o:ooooOoOoO. ,oO8O8Pd888'\"\n"
"                   ,.:.::o:ooOoOoOO8O8OOo.8OOPd8O8O\"\n"
"                  , ..:.::o:ooOoOOOO8OOOOo.FdO8O8\"\n"
"                 , ..:.::o:ooOoOO8O888O8O,COCOO\"\n"
"                , . ..:.::o:ooOoOOOO8OOOOCOCO\"\n"
"                 . ..:.::o:ooOoOoOO8O8OCCCC\"o\n"
"                    . ..:.::o:ooooOoCoCCC\"o:o\n"
"                    . ..:.::o:o:,cooooCo\"oo:o:\n"
"                 `   . . ..:.:cocoooo\"'o:o:::'\n"
"                 .`   . ..::ccccoc\"'o:o:o:::'\n"
"                :.:.    ,c:cccc\"':.:.:.:.:.'\n"
"              ..:.:\"'`::::c:\"'..:.:.:.:.:.'\n"
"            ...:.'.:.::::\"'    . . . . .'\n"
"           .. . ....:.\"' `   .  . . ''\n"
"         . . . ....\"'\n"
"         .. . .\"'     \n"
"        .\n"
"\n"
"\n                 Welcome to Dick's Sick ROOT Installation\n");



//printf("\033[33m  It is by caffeine alone I set my mind in motion. \n  It is by the beans of Java the thoughts acquire speed, \n  The hands acquire shaking,\n  The shaking becomes a warning. \n  It is by caffeine alone I set my mind in motion.\n\n");


    //printf("\033[33m\n\n“So, in the face of overwhelming odds, I'm left with only one option:\nI’m going to have to science the shit out of this.” \n");
    //printf("\033[37m\n    -- Mark Watney\n\n");



gROOT->ProcessLine(".L /home/rj/app/lib/libRadioScatter.so");
gROOT->ProcessLine("#include </home/rj/app/include/RadioScatter/RadioScatter.hh>");
gROOT->ProcessLine("#include </home/rj/app/include/RadioScatter/RSEventSummary.hh>");
gROOT->ProcessLine("#include </home/rj/app/include/RadioScatter/RadioScatterEvent.hh>");
gROOT->ProcessLine("#include </home/rj/app/include/RadioScatter/TUtilRadioScatter.hh>");


}


