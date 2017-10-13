#!/bin/bash

FILES=/nfs/2016/r/rbozhko/Desktop/projects/lem_in_final/maps/*

for f in $FILES
do
	echo $f
	../lem-in < $f
	../lem-in.dms < $f
done
