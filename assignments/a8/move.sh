#! /bin/bash

for file in $(ls *o)
do
    mv $file objects
done
