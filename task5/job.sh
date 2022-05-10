#!/bin/bash

#PBS -l walltime=00:01:00,nodes=1:ppn=3
#PBS -N main_p
#PBS -q batch

cd $PBS_O_WORKDIR
./main_p 5