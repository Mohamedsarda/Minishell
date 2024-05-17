a=$(pgrep minishell | tr -d '\n')
while TRUE
do leaks $a
sleep 1
done;