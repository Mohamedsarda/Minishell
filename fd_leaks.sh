while TRUE
a=$(pgrep minishell | tr -d '\n')
do lsof -p $a
sleep 1
done;