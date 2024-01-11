#!/bin/bash
#this is a simple bash program
#this is being used for second bonus of assignment
echo "Hello World!"
#the program should read the code and ignore the comments
read -p "Enter number" number
if [ $number -gt 5 ];
then echo "Number>10"
else echo "Number<10"
fi
#program should execute the given lines
