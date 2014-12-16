#!/bin/sh

echo "Content-type: text/html"
echo ""

# compile the program
gcc gauss.c -o gauss.cgi
chmod 755 gauss.cgi

# show some info on the screen
echo "Compiling finished.
"
echo "<a href='http://www.benchr.de/IT2/index.html'>Click here</a> to run the program."
