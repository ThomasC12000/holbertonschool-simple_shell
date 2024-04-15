#!/bin/bash

pid_max=$(cat /proc/sys/kernel/pid_max);
echo "PID max possible : $pid_max";
