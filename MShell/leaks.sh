#!/bin/bash
while TRUE
a=$(pgrep minishell | tr -d '\n')
do leaks $a
sleep 1
done;