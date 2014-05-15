#  this file is based on "/bin/graph" by Steffen Vogel from "dmmut61e-0.01.tar.gz" 

#set title "es51922"
set auto x

#set terminal x11
set terminal x11 enhanced font "arial,15"
set terminal x11 title "es51922 data plot"
set terminal x11 noraise



input_file = "../20.log"
input_file = "$0"

unset label
set datafile separator ";"
last_unit =  system("tail -1 \"".input_file."\" | cut -d \";\" -f 7 -s")
set ylabel last_unit

last_value =  system("tail -1 \"".input_file."\"  | cut -d \";\" -f 3 -s")

last_acdc =  system("tail -1 \"".input_file."\"  | cut -d \";\" -f 8 -s")

last_ma =  system("tail -1 \"".input_file."\"  | cut -d \";\" -f 9 -s")

set label last_value." ".last_unit." ".last_acdc." ".last_ma at character 1,1

set xdata time

set border
set grid


set multiplot layout 2,1
 

set xlabel "time"
plot "< cat \"".input_file."\" | tail -n 10000 | awk '{if( NR%2 ){print}}'  " using ($$1/1000):($$3) notitle smooth unique

set xlabel "time"
plot "< cat \"".input_file."\" | tail -n 480 " using ($$1/1000):($$3) notitle smooth unique

unset multiplot

!sleep 3
reread
