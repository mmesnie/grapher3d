/*
 * Please see README for copying information. 
 */

#include <stdio.h>
#include "globals.h"

/* Version Number */

char VERSION[50] = "3.2";
#define EMAIL "michael.p.mesnier@comcast.net"

int widgets(FILE **output) {

  fprintf(*output, "set START 1\n");
  fprintf(*output, "set POLYGONS %i \n", POLYGONS);
  fprintf(*output, "set FRAME %i\n", FRAME);
  fprintf(*output, "set PLOT_TYPE %i\n", POLYGONS);
  fprintf(*output, "set HOME $env(HOME)\n");
  fprintf(*output, "set NOTIFY 1\n");
  fprintf(*output, "set connectDots 1\n");

  /* Mail */

  fprintf(*output, "proc mail {notify} {\n");
  fprintf(*output, "global HOME\n");
  #ifdef hpux
  fprintf(*output, "set handle [open \"|mailx -s Grapher3d%s %s\" w];\n", VERSION, EMAIL);
  #else
  fprintf(*output, "set handle [open \"|mail -s Grapher3D%s %s\" w];\n", VERSION, EMAIL);
  #endif
  fprintf(*output, "puts $handle \"Version:      %s\";\n", VERSION);
  fprintf(*output, "puts $handle \"Architecture: %s\";\n", ARCH);
  fprintf(*output, "puts $handle \"Notify:       $notify\";\n");
  fprintf(*output, "close $handle;\n");
  fprintf(*output, "exec touch $HOME/.grapher3d-%s\n", VERSION);
  fprintf(*output, "}\n");

  /* Register */

  fprintf(*output, "proc register {} {\n");
  fprintf(*output, "toplevel .register \n");
  fprintf(*output, "wm title .register \" \"\n");
  fprintf(*output, "wm iconname .register Grapher3D\n");
  fprintf(*output, "frame .register.frame1 -relief groove -bd 2\n");
  fprintf(*output, "label .register.frame1.label -text \"");
  fprintf(*output, "Please register your release of Grapher3D.  By clicking \\\"register,\\\" you\n");
  fprintf(*output, "will e-mail %s and be added to the registration list.\n", EMAIL);
  fprintf(*output, "This registration enables me to notify you of new releases and see how\n");
  fprintf(*output, "widely this application is being used.  Thanks.\"\n");
  fprintf(*output, "pack .register.frame1.label\n");
  fprintf(*output, "frame .register.frame2 -relief groove -bd 2\n");
  fprintf(*output, "button .register.frame2.register -width 10 -text register -command {mail $NOTIFY; destroy .register}\n");
  fprintf(*output, "button .register.frame2.cancel -width 10 -text cancel -command {destroy .register}\n");
  fprintf(*output, "checkbutton .register.notify -variable NOTIFY -relief raised -bd 2 -text {Notify me of new releases.}\n");
  fprintf(*output, "pack .register.frame2.register .register.frame2.cancel -side left\n");
  fprintf(*output, "pack .register.frame1 -padx 2m -pady 2m\n");
  fprintf(*output, "pack .register.notify -padx 2m -pady 2m\n");
  fprintf(*output, "pack .register.frame2 -padx 2m -pady 2m\n");
  fprintf(*output, "}\n");

  /* About */

  fprintf(*output, "proc about {} {\n");
  fprintf(*output, "global START\n");
  fprintf(*output, "global HOME\n");
  fprintf(*output, "if {[winfo exists .about]} {\n");
  fprintf(*output, "raise .about\n");
  fprintf(*output, "wm deiconify .about\n");
  fprintf(*output, "return 0\n");
  fprintf(*output, "}\n");
  fprintf(*output, "toplevel .about \n");
  fprintf(*output, "wm title .about \" \"\n");
  fprintf(*output, "wm iconname .about Grapher3D\n");
  fprintf(*output, "frame .about.frame -relief groove -bd 2\n");
  fprintf(*output, "set REGISTERED [file exists $HOME/.grapher3d-%s]\n", VERSION);
  fprintf(*output, "if {$START && !$REGISTERED} {\n");
  fprintf(*output, "set COMMAND {destroy .about; register} \n");
  fprintf(*output, "set START 0 \n");
  fprintf(*output, "} else {\n");
  fprintf(*output, "set COMMAND {destroy .about} }\n");
  fprintf(*output, "button .about.ok -bg grey -text OK -command $COMMAND\n");
  fprintf(*output, "label .about.frame.title  -text \"Grapher3D, Version %s\"\n", VERSION);
  fprintf(*output, "label .about.frame.name   -text \"Michael P. Mesnier\"\n");
  fprintf(*output, "label .about.frame.email   -text \"michael.p.mesnier@comcast.net\"\n");
  fprintf(*output, "label .about.frame.copy   -text \"Copyright (c) 1994-2000\"\n");
  fprintf(*output, "pack .about.frame.title .about.frame.name .about.frame.copy -fill both -expand 1\n");
  fprintf(*output, "pack .about.ok -side bottom -padx 2m -pady 1m -fill x\n");
  fprintf(*output, "pack .about.frame -padx 2m -pady 1m -fill both -expand 1\n");
  
  fprintf(*output, "set TOP .about\n");
  fprintf(*output, "wm withdraw $TOP\n");
  fprintf(*output, "update idletasks\n");
  fprintf(*output, "set x [expr [winfo screenwidth $TOP]/2 - [winfo reqwidth $TOP]/2 - [winfo vrootx [winfo parent $TOP]]]\n");
  fprintf(*output, "set y [expr [winfo screenheight $TOP]/2 - [winfo reqheight $TOP]/2  - [winfo vrooty [winfo parent $TOP]]]\n");
  //fprintf(*output, "wm geom $TOP +$x+$y\n");
  fprintf(*output, "wm deiconify $TOP\n");
  fprintf(*output, "focus $TOP\n");
  fprintf(*output, "}\n");

  /* Globals */

  fprintf(*output, "set xrot [expr 45]\n");
  fprintf(*output, "set yrot [expr 0]\n");
  fprintf(*output, "set zrot [expr 45]\n");
  fprintf(*output, "set IR   [expr 5]\n");
  fprintf(*output, "set AXIS 0\n");
  fprintf(*output, "set minx [expr -3.14]\n");
  fprintf(*output, "set maxx [expr  3.14]\n");
  fprintf(*output, "set miny [expr -3.14]\n");
  fprintf(*output, "set maxy [expr  3.14]\n");
  fprintf(*output, "set I    [expr  0.1]\n");
  fprintf(*output, "set COLOR blue\n");
  fprintf(*output, "set BACKGROUND black\n");
  fprintf(*output, "set POINT_COLOR red\n");
  fprintf(*output, "set LINE_COLOR grey\n");
  fprintf(*output, "set f sin(x+y)\n");
  fprintf(*output, "set data_file \"\"\n");
  fprintf(*output, "set ZOOM [expr 30.0]\n");
  fprintf(*output, "set IZ   [expr 2.0]\n");
  fprintf(*output, "set EXAG [expr 1.0]\n");
  fprintf(*output, "set IE   [expr 1.0]\n");
  fprintf(*output, "set RES 10\n");
  fprintf(*output, "set IRES  1\n");

  /* Root window */

  fprintf(*output, "wm title . \"Grapher3D %s\"\n", VERSION);
  fprintf(*output, "wm iconname . Grapher3D\n");
  fprintf(*output, "bind . <Button-1> {controls}\n");
  fprintf(*output, "bind . <Button-2> {controls}\n");
  fprintf(*output, "bind . <Button-3> {controls}\n");
  fprintf(*output, "canvas .canvas -bg black -height 300 -width 300\n");
  fprintf(*output, "pack .canvas -fill both -expand 1\n");

  /* Controls */

  fprintf(*output, "proc controls {} {\n");
  fprintf(*output, "if {[winfo exists .controls]} {\n");
  fprintf(*output, "  raise .controls;\n");
  fprintf(*output, "  wm deiconify .controls;\n");
  fprintf(*output, "  return;\n");
  fprintf(*output, "}\n");
  fprintf(*output, "toplevel .controls\n");
  fprintf(*output, "wm title .controls \"Grapher3D %s\"\n", VERSION);
  fprintf(*output, "wm iconname .controls Grapher3D\n");
  fprintf(*output, "wm maxsize .controls 1024 1024\n");

  fprintf(*output, "frame .controls.mbar -relief raised -bd 2\n");
  fprintf(*output, "menubutton .controls.mbar.file -text File -underline 0 -menu .controls.mbar.file.menu\n");
  fprintf(*output, "menubutton .controls.mbar.functions -text \"Examples\" -underline 0 -menu .controls.mbar.functions.menu\n");
  fprintf(*output, "menubutton .controls.mbar.options -text \"Options\" -underline 0 -menu .controls.mbar.options.menu\n");
  fprintf(*output, "button .controls.mbar.help -relief flat -text Help -command help\n");
  fprintf(*output, "menu .controls.mbar.file.menu -bg grey\n");
  fprintf(*output, "menu .controls.mbar.functions.menu -bg grey\n");
  fprintf(*output, "menu .controls.mbar.options.menu -bg grey\n");
  fprintf(*output, ".controls.mbar.file.menu add command -label \"About Grapher3D\" -command {about}\n");
  fprintf(*output, ".controls.mbar.file.menu add command -label Close -command {destroy .controls}\n");
  fprintf(*output, ".controls.mbar.file.menu add command -label Quit -command {puts q;flush stdout;destroy .}\n");
  fprintf(*output, "pack .controls.mbar.file -side left\n");
  fprintf(*output, "pack .controls.mbar.functions -side left\n");
  fprintf(*output, "pack .controls.mbar.options -side left\n");
  fprintf(*output, "pack .controls.mbar.help -side right\n");

  /* Options menu */

  fprintf(*output, ".controls.mbar.options.menu add checkbutton -label \"Connect Dots\" -variable connectDots -command {if {$connectDots==1} {puts \"C\n*\"} else {puts \"c\n*\"}; flush stdout}\n");
  fprintf(*output, ".controls.mbar.options.menu add checkbutton -label \"Axis\" -variable AXIS -command {if {$AXIS} {puts \"a\n*\"} else {puts \"b\n*\"}; flush stdout}\n");
  fprintf(*output, ".controls.mbar.options.menu add radiobutton -label \"Wire frame\" -variable PLOT_TYPE -value %i -command apply\n", FRAME);
  fprintf(*output, ".controls.mbar.options.menu add radiobutton -label Polygons -variable PLOT_TYPE -value %i -command apply\n", POLYGONS);
  fprintf(*output, ".controls.mbar.options.menu add command -label Colors -command {colors}\n");

  /* Domain Entries */
 
  fprintf(*output, "frame .controls.frame9\n");
  fprintf(*output, "frame .controls.frame9.domain\n");
  fprintf(*output, "frame .controls.frame9.domain.x\n");
  fprintf(*output, "frame .controls.frame9.domain.y\n");
  fprintf(*output, "entry .controls.frame9.domain.x.minx -textvariable minx -width 6 -bg grey -relief sunken\n");
  fprintf(*output, "bind .controls.frame9.domain.x.minx <Return> apply \n");
  fprintf(*output, "label .controls.frame9.domain.x.label -text \"< x <\"\n");
  fprintf(*output, "entry .controls.frame9.domain.x.maxx -textvariable maxx -width 6 -bg grey -relief sunken\n");
  fprintf(*output, "bind .controls.frame9.domain.x.maxx <Return> apply \n");
  fprintf(*output, "entry .controls.frame9.domain.y.miny -textvariable miny -width 6 -bg grey -relief sunken\n");
  fprintf(*output, "bind .controls.frame9.domain.y.miny <Return> apply \n");
  fprintf(*output, "label .controls.frame9.domain.y.label -text \"< y <\"\n");
  fprintf(*output, "entry .controls.frame9.domain.y.maxy -textvariable maxy -width 6 -bg grey -relief sunken\n");
  fprintf(*output, "bind .controls.frame9.domain.y.maxy <Return> apply \n");
  fprintf(*output, "pack .controls.frame9.domain.x.minx .controls.frame9.domain.x.label .controls.frame9.domain.x.maxx -side left\n");
  fprintf(*output, "pack .controls.frame9.domain.y.miny .controls.frame9.domain.y.label .controls.frame9.domain.y.maxy -side left\n");
  fprintf(*output, "pack .controls.frame9.domain.x .controls.frame9.domain.y -side left -padx 2m\n");
  fprintf(*output, "pack .controls.frame9.domain -side left -padx 3m\n");

  /* Axis Rotation */

  fprintf(*output, "frame .controls.frame1 -relief sunken -bd 3\n");
  fprintf(*output, "frame .controls.frame1.framex\n");
  fprintf(*output, "frame .controls.frame1.framey\n");
  fprintf(*output, "frame .controls.frame1.framez\n");
  fprintf(*output, "frame .controls.frame1.framet\n");
  fprintf(*output, "button .controls.frame1.framex.x1 -text \"x+\" -bg grey -width 8 -command {set xrot [expr $xrot + $IR];puts x$xrot; set xrot [expr fmod($xrot, 360)];puts *;flush stdout}\n");
  fprintf(*output, "button .controls.frame1.framex.x2 -text \"x-\" -bg grey -width 8 -command {set xrot [expr $xrot - $IR];puts x$xrot; set xrot [expr fmod($xrot, 360)];puts *;flush stdout}\n");
  fprintf(*output, "entry .controls.frame1.framex.xval -relief sunken -width 8 -bg grey -textvariable xrot\n");
  fprintf(*output, "bind .controls.frame1.framex.xval <Return> {puts x$xrot; puts *;flush stdout} \n");
  fprintf(*output, "button .controls.frame1.framey.y1 -text \"y+\" -bg grey -width 8 -command {set yrot [expr $yrot + $IR];puts y$yrot; set yrot [expr fmod($yrot, 360)];puts *;flush stdout}\n");
  fprintf(*output, "button .controls.frame1.framey.y2 -text \"y-\" -bg grey -width 8 -command {set yrot [expr $yrot - $IR];puts y$yrot; set yrot [expr fmod($yrot, 360)];puts *;flush stdout}\n");
  fprintf(*output, "entry .controls.frame1.framey.yval -relief sunken -width 8 -bg grey -textvariable yrot\n");
  fprintf(*output, "bind .controls.frame1.framey.yval <Return> {puts y$yrot; puts *;flush stdout} \n");
  fprintf(*output, "button .controls.frame1.framez.z1 -text \"z+\" -bg grey -width 8 -command {set zrot [expr $zrot + $IR];puts z$zrot; set zrot [expr fmod($zrot, 360)];puts *;flush stdout}\n");
  fprintf(*output, "button .controls.frame1.framez.z2 -text \"z-\" -bg grey -width 8 -command {set zrot [expr $zrot - $IR];puts z$zrot; set zrot [expr fmod($zrot, 360)];puts *;flush stdout}\n");
  fprintf(*output, "entry .controls.frame1.framez.zval -relief sunken -width 8 -bg grey -textvariable zrot\n");
  fprintf(*output, "bind .controls.frame1.framez.zval <Return> {puts z$zrot; puts *;flush stdout} \n");
  fprintf(*output, "button .controls.frame1.framet.topo -text \"topographical\" -bg grey -command {set xrot [expr 0.0];set yrot $xrot;set zrot $xrot;puts t;puts *;flush stdout}\n");
  fprintf(*output, "pack .controls.frame1.framet.topo -fill both -expand 1\n");
  fprintf(*output, "pack .controls.frame1.framex.x1 .controls.frame1.framex.x2 .controls.frame1.framex.xval -side left -fill both -expand 1\n");
  fprintf(*output, "pack .controls.frame1.framey.y1 .controls.frame1.framey.y2 .controls.frame1.framey.yval -side left -fill both -expand 1\n");
  fprintf(*output, "pack .controls.frame1.framez.z1 .controls.frame1.framez.z2 .controls.frame1.framez.zval -side left -fill both -expand 1\n");
  fprintf(*output, "pack .controls.frame1.framex .controls.frame1.framey .controls.frame1.framez .controls.frame1.framet -fill both -expand 1\n");

  /* zoom, exag, res */

  fprintf(*output, "frame .controls.frame2 -relief sunken -bd 3\n");
  fprintf(*output, "frame .controls.frame2.framezoom\n");
  fprintf(*output, "frame .controls.frame2.frameres \n");
  fprintf(*output, "frame .controls.frame2.frameexag\n");
  fprintf(*output, "button .controls.frame2.framezoom.zoom1 -bg grey -text \"zoom +\" -width 8 -command {set ZOOM [expr $ZOOM +$IZ];puts Z$ZOOM;puts *; flush stdout}\n");
  fprintf(*output, "button .controls.frame2.framezoom.zoom2 -bg grey -text \"zoom -\" -width 8 -command {set ZOOM [expr $ZOOM -$IZ];puts Z$ZOOM;puts *; flush stdout}\n");
  fprintf(*output, "entry  .controls.frame2.framezoom.entry -relief sunken -width 8 -bg grey -textvariable ZOOM\n");
  fprintf(*output, "bind   .controls.frame2.framezoom.entry <Return> {puts Z$ZOOM; puts *; flush stdout} \n");
  fprintf(*output, "button .controls.frame2.frameres.res1 -bg grey -text \"res. +\" -width 8 -command {incr RES $IRES;puts R$RES;puts *; flush stdout}\n");
  fprintf(*output, "button .controls.frame2.frameres.res2 -bg grey -text \"res. -\" -width 8 -command {if {[expr $RES - $IRES] >= 2} {incr RES -$IRES};puts R$RES;puts *; flush stdout}\n");
  fprintf(*output, "entry  .controls.frame2.frameres.entry -relief sunken -width 8 -bg grey -textvariable RES\n");
  fprintf(*output, "bind   .controls.frame2.frameres.entry <Return> {puts R$RES; puts *; flush stdout} \n");
  fprintf(*output, "button .controls.frame2.frameexag.exag1 -bg grey -text \"exag. +\" -width 8 -command {set EXAG [expr $EXAG +$IE];puts E$EXAG;puts *; flush stdout}\n");
  fprintf(*output, "button .controls.frame2.frameexag.exag2 -bg grey -text \"exag. -\" -width 8 -command {set EXAG [expr $EXAG -$IE];puts E$EXAG;puts *; flush stdout}\n");
  fprintf(*output, "entry  .controls.frame2.frameexag.entry -relief sunken -width 8 -bg grey -textvariable EXAG\n");
  fprintf(*output, "bind   .controls.frame2.frameexag.entry <Return> {puts E$EXAG; puts *; flush stdout} \n");
  fprintf(*output, "pack .controls.frame2.framezoom.zoom1 .controls.frame2.framezoom.zoom2 .controls.frame2.framezoom.entry -side left -fill both -expand 1\n");
  fprintf(*output, "pack .controls.frame2.frameres.res1 .controls.frame2.frameres.res2 .controls.frame2.frameres.entry -side left -fill both -expand 1\n");
  fprintf(*output, "pack .controls.frame2.frameexag.exag1 .controls.frame2.frameexag.exag2 .controls.frame2.frameexag.entry -side left -fill both -expand 1\n");
  fprintf(*output, "pack .controls.frame2.framezoom .controls.frame2.frameres .controls.frame2.frameexag -fill both -expand 1\n");

  /* Domain Shifting */

  fprintf(*output, "frame .controls.shift -relief sunken -bd 3\n");
  fprintf(*output, "frame .controls.shift.shift1 \n");
  fprintf(*output, "frame .controls.shift.shift2 \n");
  fprintf(*output, "button .controls.shift.shift1.7 -text \"x+\" -bg grey -width 4 -command {set minx [expr $minx + $I];set maxx [expr $maxx + $I];domainshift}\n");
  fprintf(*output, "button .controls.shift.shift1.8 -text \"x-\" -bg grey -width 4 -command  {set minx [expr $minx - $I];set maxx [expr $maxx - $I];domainshift}\n");
  fprintf(*output, "button .controls.shift.shift1.9 -text \"y+\" -bg grey -width 4 -command  {set miny [expr $miny + $I];set maxy [expr $maxy + $I];domainshift}\n");
  fprintf(*output, "button .controls.shift.shift1.0 -text \"y-\" -bg grey -width 4 -command  {set miny [expr $miny - $I];set maxy [expr $maxy - $I];domainshift}\n");
  fprintf(*output, "button .controls.shift.shift2.a -text \"x+y+\" -bg grey -width 4 -command {set minx [expr $minx + $I];set maxx [expr $maxx + $I]; set miny [expr $miny + $I];set maxy [expr $maxy + $I];domainshift}\n");
  fprintf(*output, "button .controls.shift.shift2.b -text \"x-y-\" -bg grey -width 4 -command {set minx [expr $minx - $I];set maxx [expr $maxx - $I]; set miny [expr $miny - $I];set maxy [expr $maxy - $I];domainshift}\n");
  fprintf(*output, "button .controls.shift.shift2.d -text \"x+y-\" -bg grey -width 4 -command {set minx [expr $minx + $I];set maxx [expr $maxx + $I]; set miny [expr $miny - $I];set maxy [expr $maxy - $I];domainshift}\n");
  fprintf(*output, "button .controls.shift.shift2.e -text \"x-y+\" -bg grey -width 4 -command {set minx [expr $minx - $I];set maxx [expr $maxx - $I]; set miny [expr $miny + $I];set maxy [expr $maxy + $I];domainshift}\n");
  fprintf(*output, "pack .controls.shift.shift1.7 .controls.shift.shift1.8 .controls.shift.shift1.9 .controls.shift.shift1.0 -side left -fill both -expand 1\n");
  fprintf(*output, "pack .controls.shift.shift2.a .controls.shift.shift2.d .controls.shift.shift2.e .controls.shift.shift2.b -side left -fill both -expand 1\n");
  fprintf(*output, "pack .controls.shift.shift1 .controls.shift.shift2 -fill both -expand 1\n");


  /*Function Section*/
 
  fprintf(*output, "frame .controls.frame7\n");
  fprintf(*output, "frame .controls.frame7.function \n");
  fprintf(*output, "label .controls.frame7.function.label -text \"Function f(x,y)\"\n");
  fprintf(*output, "entry .controls.frame7.function.entry -relief sunken -width 20 -bg grey -textvariable f \n");
  fprintf(*output, "bind  .controls.frame7.function.entry <Return> apply\n");
  fprintf(*output, "frame .controls.frame7.points \n");
  fprintf(*output, "label .controls.frame7.points.label -text \"Data File:\"\n");
  fprintf(*output, "entry .controls.frame7.points.entry -relief sunken -width 20 -bg grey -textvariable data_file \n");
  fprintf(*output, "bind  .controls.frame7.points.entry <Return> apply\n");
  fprintf(*output, "pack .controls.frame7.function.label\n");
  fprintf(*output, "pack .controls.frame7.function.entry -fill x -expand 1\n");
  fprintf(*output, "pack .controls.frame7.function -side left -fill both -expand 1 -padx 3m\n");
  fprintf(*output, "pack .controls.frame7.points.label\n");
  fprintf(*output, "pack .controls.frame7.points.entry -fill x -expand 1\n");
  fprintf(*output, "pack .controls.frame7.points -side left -fill both -expand 1 -padx 3m\n");

  /* Example Functions */

  fprintf(*output, ".controls.mbar.functions.menu add command -label \"sin(x+y)\" -command {set f sin(x+y);set data_file \"\";set minx [expr -3.14];set maxx [expr 3.14];set miny [expr -3.14]; set maxy [expr 3.14]; set COLOR blue; set RES 10; set EXAG 1; set ZOOM 30; set xrot [expr 45]; set yrot [expr 0]; set zrot [expr 45]; apply}\n");
  fprintf(*output, ".controls.mbar.functions.menu add command -label \"sqrt(x*x-y*y)\" -command {set data_file \"\";set f sqrt(x*x-y*y);set minx [expr -3.14];set maxx [expr 3.14];set miny [expr -3.14]; set maxy [expr 3.14]; set COLOR blue; set RES 10; set EXAG 2; set ZOOM 20; set xrot [expr 45]; set yrot [expr 0]; set zrot [expr 45]; apply}\n");
  fprintf(*output, ".controls.mbar.functions.menu add command -label \"ln(x*x+y*y)\" -command {set data_file \"\";set f ln(x*x+y*y);set minx [expr -3]; set maxx [expr 3]; set miny [expr -3]; set maxy [expr 3]; set COLOR blue; set RES 10; set EXAG 3; set ZOOM 20; set xrot [expr 45]; set yrot [expr 0]; set zrot [expr 45]; apply}\n");
  fprintf(*output, ".controls.mbar.functions.menu add command -label \"x*x-y*y\" -command {set f x*x-y*y;set data_file \"\";set minx [expr -2]; set maxx [expr 2]; set miny [expr -2]; set maxy [expr 2]; set COLOR blue; set EXAG 1; set RES 10; set ZOOM 30; set xrot [expr 45]; set yrot [expr 0]; set zrot [expr 45]; apply}\n");
  fprintf(*output, ".controls.mbar.functions.menu add command -label \"cos(exp(x)*exp(y))\" -command {set f cos(exp(x)*exp(y));set data_file \"\";set minx [expr -3]; set maxx [expr 3]; set miny [expr -3]; set COLOR blue; set ZOOM 30; set RES 10; set EXAG 2; set maxy [expr 3]; set xrot [expr 45]; set yrot [expr 0]; set zrot [expr 45];apply}\n");
  fprintf(*output, ".controls.mbar.functions.menu add command -label \"abs(cos(x))\" -command {set f abs(cos(x));set data_file \"\";set minx [expr -3.14];set maxx [expr 3.14];set miny [expr -3.14]; set COLOR blue; set ZOOM 30; set EXAG 3; set RES 10;set maxy [expr 3.14]; set xrot [expr 45]; set yrot [expr 0]; set zrot [expr 45];apply}\n");
  fprintf(*output, ".controls.mbar.functions.menu add command -label \"Cube\" -command {set f \"\";set data_file \"./cube.dat\"; set COLOR blue; set ZOOM 30; set xrot [expr 45]; set yrot [expr 0]; set zrot [expr 45];apply}\n");

  /* Labels */

  fprintf(*output, "label .controls.transformations -text \"Transformations\"\n");
  fprintf(*output, "label .controls.domain          -text \"Domain\"\n");

  /* Final Geometry */

  fprintf(*output, "pack .controls.mbar -fill x\n");     /* menu */
  fprintf(*output, "pack .controls.frame7\n");           /* function */
  fprintf(*output, "pack .controls.transformations\n");  /* transformations label */
  fprintf(*output, "pack .controls.frame1 -fill x\n");   /* rotations */
  fprintf(*output, "pack .controls.frame2 -fill x\n");   /* zoom+, etc. */
  fprintf(*output, "pack .controls.domain\n");           /* domain label */
  fprintf(*output, "pack .controls.frame9\n");           /* domain */
  fprintf(*output, "pack .controls.shift  -fill x\n");   /* domain shift */

  /* Center in middle of screen */

  fprintf(*output, "set TOP .controls\n");
  fprintf(*output, "wm withdraw $TOP\n");
  fprintf(*output, "update idletasks\n");
  fprintf(*output, "set x [expr [winfo screenwidth $TOP]/2 - [winfo reqwidth $TOP]/2 - [winfo vrootx [winfo parent $TOP]]]\n");
  fprintf(*output, "set y [expr [winfo screenheight $TOP]/2 - [winfo reqheight $TOP]/2  - [winfo vrooty [winfo parent $TOP]]]\n");
  //fprintf(*output, "wm geom $TOP +$x+$y\n");
  fprintf(*output, "wm deiconify $TOP\n");
  fprintf(*output, "focus $TOP\n");
  fprintf(*output, "}\n");

  /* Apply stuff */

  fprintf(*output, "proc apply {} {\n");
  fprintf(*output, "global f;global COLOR;global BACKGROUND;global RES\n");
  fprintf(*output, "global POINT_COLOR\n");
  fprintf(*output, "global PLOT_TYPE\n");
  fprintf(*output, "global LINE_COLOR; global AXIS\n");
  fprintf(*output, "global minx;global maxx;global miny;global maxy\n");
  fprintf(*output, "global ZOOM;global EXAG;global data_file\n");
  fprintf(*output, "global xrot;global yrot;global zrot\n");
  fprintf(*output, "set data_file [string trim $data_file]\n");
  fprintf(*output, "if {$AXIS} {\n"); 
  fprintf(*output, "puts a\n"); 
  fprintf(*output, "} else {\n"); 
  fprintf(*output, "puts b\n"); 
  fprintf(*output, "}\n"); 
  fprintf(*output, "if {[string length $data_file]} {\n");
  fprintf(*output, "puts \"F$data_file\"\n");
  fprintf(*output, "puts \"$POINT_COLOR\"\n");
  fprintf(*output, "puts \"$LINE_COLOR\"\n");
  fprintf(*output, "set ZOOM [string trim $ZOOM]\n");
  fprintf(*output, "puts $ZOOM\n"); 
  fprintf(*output, "puts $xrot\n"); 
  fprintf(*output, "puts $yrot\n"); 
  fprintf(*output, "puts $zrot\n"); 
  fprintf(*output, "} else {\n");
  fprintf(*output, "puts \"G\"\n");
  fprintf(*output, "}\n");
  fprintf(*output, "regsub -all \" \" $f \"\" f\n");
  fprintf(*output, "if {[string length $f]} {\n");
  fprintf(*output, "puts f$f\n"); 
  fprintf(*output, "puts l$minx\n"); 
  fprintf(*output, "puts m$maxx\n"); 
  fprintf(*output, "puts n$miny\n"); 
  fprintf(*output, "puts o$maxy\n"); 
  fprintf(*output, "set COLOR [string trim $COLOR]\n");
  fprintf(*output, "puts c$COLOR\n"); 
  fprintf(*output, "set RES [string trim $RES]\n");
  fprintf(*output, "puts $RES\n"); 
  fprintf(*output, "set EXAG [string trim $EXAG]\n");
  fprintf(*output, "puts $EXAG\n"); 
  fprintf(*output, "set ZOOM [string trim $ZOOM]\n");
  fprintf(*output, "puts $ZOOM\n"); 
  fprintf(*output, "puts $xrot\n"); 
  fprintf(*output, "puts $yrot\n"); 
  fprintf(*output, "puts $zrot\n"); 
  fprintf(*output, "set geom [wm geometry .]\n"); 
  fprintf(*output, "puts $geom\n"); 
  fprintf(*output, "} else {\n");
  fprintf(*output, "puts \"g\"\n");
  fprintf(*output, "}\n");
  fprintf(*output, "puts $PLOT_TYPE\n"); 
  fprintf(*output, "puts *\n");
  fprintf(*output, "flush stdout\n"); 
  fprintf(*output, "set BACKGROUND [string trim $BACKGROUND]\n"); 
  fprintf(*output, ".canvas configure -bg $BACKGROUND\n"); 
  fprintf(*output, "}\n");

  /* Domain Shifting */

  fprintf(*output, "proc domainshift {} {\n");
  fprintf(*output, "global minx maxx miny maxy\n");
  fprintf(*output, "puts D$minx;flush stdout\n"); 
  fprintf(*output, "puts $maxx;flush stdout\n"); 
  fprintf(*output, "puts $miny;flush stdout\n"); 
  fprintf(*output, "puts $maxy;flush stdout\n"); 
  fprintf(*output, "puts *\n");
  fprintf(*output, "}\n");

  /* Error subroutine */

  fprintf(*output, "proc Error {TEXT} {\n");
  fprintf(*output, "  global Global\n");
  fprintf(*output, "  set count 0\n");
  fprintf(*output, "  while {[winfo exists .error$count]} {\n");
  fprintf(*output, "    incr count\n");
  fprintf(*output, "  }\n");
  
  fprintf(*output, "  set TOP .error$count\n");
  fprintf(*output, "  toplevel $TOP\n");
  fprintf(*output, "  wm title $TOP Error\n");
  fprintf(*output, "  label $TOP.label -text $TEXT\n");
  fprintf(*output, "  set COMMAND \"destroy $TOP\"\n");
  fprintf(*output, "  button $TOP.button -text ok -command $COMMAND\n");
  fprintf(*output, "  pack $TOP.label $TOP.button -padx 2m -pady 2m\n");
  fprintf(*output, "  wm withdraw $TOP\n");
  fprintf(*output, "  update idletasks\n");
  fprintf(*output, "  set x [expr [winfo screenwidth $TOP]/2 - [winfo reqwidth $TOP]/2 - [winfo vrootx [winfo parent $TOP]]]\n");
  fprintf(*output, "  set y [expr [winfo screenheight $TOP]/2 - [winfo reqheight $TOP]/2  - [winfo vrooty [winfo parent $TOP]]]\n");
  //fprintf(*output, "  wm geom $TOP +$x+$y\n");
  fprintf(*output, "  wm deiconify $TOP\n");
  fprintf(*output, "  grab $TOP\n");
  fprintf(*output, "  focus $TOP\n");
  fprintf(*output, "}\n");


  /* Colors */

  fprintf(*output, "proc colors {} {\n");
  fprintf(*output, "  if {[winfo exists .color]} {\n");
  fprintf(*output, "    raise .color\n");
  fprintf(*output, "    wm deiconify .color\n");
  fprintf(*output, "    return 0\n");
  fprintf(*output, "  }\n");
  fprintf(*output, "  toplevel .color\n");
  fprintf(*output, "  wm title .color \" \"\n");
  fprintf(*output, "  wm iconname .color Grapher3D\n");
  fprintf(*output, "  frame .color.f\n");
  fprintf(*output, "  frame .color.b\n");
  fprintf(*output, "  frame .color.p\n");
  fprintf(*output, "  frame .color.l\n");
  fprintf(*output, "  label .color.f.label -width 12 -text Foreground -anchor w\n");
  fprintf(*output, "  entry .color.f.entry -relief sunken -width 12 -bg grey -textvariable COLOR\n");
  fprintf(*output, "  bind .color.f.entry <Return> apply \n");
  fprintf(*output, "  label .color.b.label -width 12 -text Background -anchor w\n");
  fprintf(*output, "  entry .color.b.entry -relief sunken -width 12 -bg grey -textvariable BACKGROUND\n");
  fprintf(*output, "  bind .color.b.entry <Return> apply \n");
  fprintf(*output, "  label .color.p.label -width 12 -text Points -anchor w\n");
  fprintf(*output, "  entry .color.p.entry -relief sunken -width 12 -bg grey -textvariable POINT_COLOR\n");
  fprintf(*output, "  bind .color.p.entry <Return> apply \n");

  fprintf(*output, "  label .color.l.label -width 12 -text Lines -anchor w\n");
  fprintf(*output, "  entry .color.l.entry -relief sunken -width 12 -bg grey -textvariable LINE_COLOR\n");
  fprintf(*output, "  bind .color.l.entry <Return> apply \n");
  fprintf(*output, "  pack .color.f.label .color.f.entry -side left\n");
  fprintf(*output, "  pack .color.b.label .color.b.entry -side left\n");
  fprintf(*output, "  pack .color.p.label .color.p.entry -side left\n");
  fprintf(*output, "  pack .color.l.label .color.l.entry -side left\n");
  fprintf(*output, "  pack .color.f .color.b .color.p .color.l \n");
  fprintf(*output, "}\n");


  /* Help */

  fprintf(*output, "proc help {} {\n");
  fprintf(*output, "if {[winfo exists .help]} {\n");
  fprintf(*output, "raise .help\n");
  fprintf(*output, "wm deiconify .help\n");
  fprintf(*output, "return 0\n");
  fprintf(*output, "}\n");
  fprintf(*output, "set TEXT \"\n");
  fprintf(*output, "                 Grapher3D, Version %s \n", VERSION);
  fprintf(*output, "\n");
  fprintf(*output, "                   Michael P. Mesnier\n");
  fprintf(*output, "   \n");
  fprintf(*output, "       Copyright (c) 1994-2000.  All rights reserved. \n");
  fprintf(*output, "   \n");
  fprintf(*output, "                    ***Disclaimer***\n");
  fprintf(*output, "   \n");
  fprintf(*output, "   This application comes with no express or implied\n");
  fprintf(*output, "   warranty as to its fitness for any particular purpose.\n");
  fprintf(*output, "   In no event shall the author be held responsible for\n");
  fprintf(*output, "   any damages resulting from the use of this application.\n");
  fprintf(*output, "\n");
  fprintf(*output, "   Please send comments to michael.p.mesnier@comcast.net.\n");
  fprintf(*output, "   \n");
  fprintf(*output, "   i. Abstract\n");
  fprintf(*output, "   \n");
  fprintf(*output, "   Grapher3D generates surfaces of two variable functions\n");
  fprintf(*output, "   allowing users to view these surfaces from any three\n");
  fprintf(*output, "   dimensional position.  Dynamic axis rotation and domain\n");
  fprintf(*output, "   shifting help better illustrate the nature of a surface.\n\n");
  fprintf(*output, "   I. Transformations\n\n");
  fprintf(*output, "   x+/x-, y+/y-, z+/z- rotate the respective axis by PI/32.\n");
  fprintf(*output, "   topographical resets all rotations values to zero.\n");
  fprintf(*output, "   res+/res- modify the surface resolution.\n");
  fprintf(*output, "   zoom+/zoom- zoom in/out of the scene.\n");
  fprintf(*output, "   exag+/exag- exaggerate the z value f(x,y).\n\n");
  fprintf(*output, "   You can enter exact values in the entries provided.\n\n");
  fprintf(*output, "   Note: A change in the resolution and/or exaggeration\n");
  fprintf(*output, "         will not affect data read in from a file.\n");
  fprintf(*output, "   \n");
  fprintf(*output, "   III. Domain Shifts\n");
  fprintf(*output, "   \n");
  fprintf(*output, "   Shifting a surface along its domain will better\n");
  fprintf(*output, "   illustrate the nature of a function, and for\n");
  fprintf(*output, "   lower resolution surfaces, create interesting surface\n");
  fprintf(*output, "   animations (if you click fast). The domain of f(x,y)\n");
  fprintf(*output, "   is simply the xy plane.  The eight shifting commands\n");
  fprintf(*output, "   (x+, x-, y+, y-, x+y+, x+y-, x-y+, x-y-) allow you to\n");
  fprintf(*output, "   shift the domain to locations within this plane. You can\n");
  fprintf(*output, "   also enter exact domain values in the entries provided.\n");
  fprintf(*output, "\n");
  fprintf(*output, "   V. Creating a Surface\n");
  fprintf(*output, "\n");
  fprintf(*output, "   Binary operations:           \n");
  fprintf(*output, "\n");
  fprintf(*output, "   +  addition\n");
  fprintf(*output, "   -  subtraction\n");
  fprintf(*output, "   *  multiplication\n");
  fprintf(*output, "   /  division \n");
  fprintf(*output, "   ^  exponentiation\n");
  fprintf(*output, "\n");
  fprintf(*output, "   Unary operations:\n");
  fprintf(*output, "\n");
  fprintf(*output, "   sin, cos tan exp, ln, - (negation), abs, sqrt.\n");
  fprintf(*output, "   \n");
  fprintf(*output, "   Click \\\"Examples\\\" to see a few example functions.\n");
  fprintf(*output, "   \n");
  fprintf(*output, "   You can also enter an arbitrary set of 3D points.  These \n");
  fprintf(*output, "   points are read in from a file with the following format:\n");
  fprintf(*output, " \n");
  fprintf(*output, "   x1 y1 z1\n");
  fprintf(*output, "   x2 y2 z2\n");
  fprintf(*output, "   x3 y3 z3\n");
  fprintf(*output, "      .\n");
  fprintf(*output, "      .\n");
  fprintf(*output, "      .\n");
  fprintf(*output, "   xn yn zn\n");
  fprintf(*output, "\n");
  fprintf(*output, "   These data points will be plotted in order, optionally\n");
  fprintf(*output, "   connected with lines - like connect the dots.  Included\n");
  fprintf(*output, "   with this release of Grapher3D is the example file\n");
  fprintf(*output, "   cube.dat. Click \\\"Cube\\\" under the \\\"Examples menu,\\\" to load\n");
  fprintf(*output, "   the file, or input your own data file in the entry.\n");
  fprintf(*output, "   provided.\n\n");
  fprintf(*output, "   To plot only the points, delete the function from the\n");
  fprintf(*output, "   entry Function f(x,y). Similarly, to stop plotting your\n");
  fprintf(*output, "   3D points, erase the filename from the \\\"Data File:\\\"\n");
  fprintf(*output, "   entry.\"\n");
  fprintf(*output, "toplevel .help\n");
  fprintf(*output, "wm title .help \" \"\n");
  fprintf(*output, "wm iconname .help Grapher3D\n");
  fprintf(*output, "frame .help.frame\n");
  fprintf(*output, "button .help.ok -bg grey -text OK -command {destroy .help}\n");
  fprintf(*output, "text .help.frame.text -yscrollcommand \".help.frame.scroll set\" -relief sunken -width 60 -bd 2\n");
  fprintf(*output, "scrollbar .help.frame.scroll -relief sunken -bg grey -command \".help.frame.text yview\"\n");
  fprintf(*output, "pack .help.frame.scroll -side right -fill y -padx 1m \n");
  fprintf(*output, "pack .help.frame.text -side right -fill both -expand 1 -padx 1m \n");
  fprintf(*output, "pack .help.ok -side bottom -fill x -padx 1m -pady 1m\n");
  fprintf(*output, "pack .help.frame -padx 1m -pady 1m -fill both -expand 1\n");
  fprintf(*output, ".help.frame.text insert end $TEXT\n");
  
  fprintf(*output, "set TOP .help\n");
  fprintf(*output, "wm withdraw $TOP\n");
  fprintf(*output, "update idletasks\n");
  fprintf(*output, "set x [expr [winfo screenwidth $TOP]/2 - [winfo reqwidth $TOP]/2 - [winfo vrootx [winfo parent $TOP]]]\n");
  fprintf(*output, "set y [expr [winfo screenheight $TOP]/2 - [winfo reqheight $TOP]/2  - [winfo vrooty [winfo parent $TOP]]]\n");
  //fprintf(*output, "wm geom $TOP +$x+$y\n");
  fprintf(*output, "wm deiconify $TOP\n");
  fprintf(*output, "focus $TOP\n");
  fprintf(*output, "}\n");


  /* Startup */

  fprintf(*output, "about\n");
  fprintf(*output, "apply\n");
  fflush(*output);
  return 0;
}
