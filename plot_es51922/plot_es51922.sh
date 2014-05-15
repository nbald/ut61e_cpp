#!/bin/sh

if [ $# -gt 0 ] # we got args

    # run gnuplot, call gpt.plt and pass argv[1...9] to the gnuplot script
    then echo "call \"gpt.plt\" \"$1\" \"$2\" \"$3\" \"$4\" \"$5\" \"$6\" \"$7\" \"$8\" \"$9\"" | gnuplot 

    else echo "usage: $0 some_es51922_logfile.log"
fi

