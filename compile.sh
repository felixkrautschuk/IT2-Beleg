#!/bin/sh

echo "Content-type: text/html"
echo ""

# compile the program
gcc gauss.c -o gauss.cgi
chmod 755 gauss.cgi

# show some info on the screen
echo "Die Datei wurde ordnungsgemäß kompiliert. "

echo "Bitte klicken Sie <a href='http://www.benchr.de/IT2/index.html'>hier</a> um das Programm auszuführen."
