#!/bin/bash

guipid=0
players=$3

[ -z "$players" ] && players=20

# function sigint () {
#   echo
#   echo 'Interrupt!'
#   test $guipid -ne 0 && kill $guipid
#   exit 1
# }
# trap sigint INT

echo "Init IPC ..."
$1 config.txt &
sleep 1

echo "Starting GUI ..."
$2 &
guipid=$!
sleep 0.1

echo "Launching $players players ..."
while test $players -gt 1
do
  $1 &
  players=`expr $players - 1`
#  sleep 0.1
done

echo "Waiting to be killed ..."
while :; do
sleep 666
done
