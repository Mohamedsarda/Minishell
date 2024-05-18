#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int ft_strlen(char *result)
{
    int i =0;
    if(!result)
        return 0;
    while (result[i])
        i++;
    return i;
}

char    *ft_text(char *result, char *str, int *i)
{
    int j = *i;
    while(str[*i] && str[*i] != '$' && str[*i] != '\"' && str[*i] != '\'')
        (*i)++;
    char    *res = malloc(ft_strlen(result) + (*i - j) + 1);

    int c = 0;
    while (result != NULL && result[c])
    {
        res[c] = result[c];
        c++;
    }
    while(str[j] && str[j] != '$' && str[j] != '\"' && str[j] != '\'')
    {
        res[c] = str[j];
        c++;
        j++;
    }
    res[c] = '\0';
    free(result);
    return (res);
}

char	*get_only_key(char *str, int *i)
{
    int j = *i;
    int c = 0;
    while(str[*i] && ((str[*i] >= 'a' && str[*i] <= 'z') || (str[*i] >= 'A' && str[*i] <= 'Z') || (str[*i] >= '0' && str[*i] <= '9') || str[*i] == '_'))
            (*i)++;
    char    *res = malloc((*i - j) + 1);
	while(str[j] && ((str[j] >= 'a' && str[j] <= 'z') || (str[j] >= 'A' && str[j] <= 'Z') || (str[j] >= '0' && str[j] <= '9') || str[j] == '_'))
    {
        res[c] = str[j];
        c++;
        j++;
    }
    res[c] = '\0';
    return res;
}

char    *ft_expand(char *result, char *str, int *i)
{
    (*i)++;
    int j = *i;
    if(str[*i] == '\'' || str[*i] == '\"')
        return result;
    else if (str[*i] >= '0' && str[*i] <= '9')
        return ((*i)++, result);
    else
    {
        char	*key  = NULL;
		key = get_only_key(str, i);
        printf("key ==== [%s]\n", key);
        int len = (*i - j) + 1 + ft_strlen(result);
        char    *res = malloc(len);
        int c = 0;
        while (result != NULL && result[c])
        {
            res[c] = result[c];
            c++;
        }
        while(str[j] && ((str[j] >= 'a' && str[j] <= 'z') || (str[j] >= 'A' && str[j] <= 'Z') || (str[j] >= '0' && str[j] <= '9') || str[j] == '_'))
        {
            res[c] = str[j];
            c++;
            j++;
        }
        res[c] = '\0';
        free(result);
        return (res);
    }
    return result;
}

char    *handle_single(char *result, char *str, int *i)
{
    (*i)++;
    int j = *i;
    while (str[*i] && str[*i] != '\'')
        (*i)++;
    char    *res = malloc((*i - j) + 1 + ft_strlen(result));
    int c = 0;
    while (result != NULL && result[c])
    {
        res[c] = result[c];
        c++;
    }
    while(str[j] && str[j] != '\'')
    {
        res[c] = str[j];
        c++;
        j++;
    }
    res[c] = '\0';
    free(result);
    return (res);
}

char    *handle_double(char *result, char *str, int *i)
{
    (*i)++;
    int j = *i;
    while(str[*i] && str[*i] != '$' && str[*i] != '\"')
        (*i)++;
    char    *res = malloc(ft_strlen(result) + (*i - j) + 1);

    int c = 0;
    while (result != NULL && result[c])
    {
        res[c] = result[c];
        c++;
    }
    while(str[j] && str[j] != '$' && str[j] != '\"')
    {
        res[c] = str[j];
        c++;
        j++;
    }
    res[c] = '\0';
    free(result);
    return (res);
}

char    *all_expand(char *str)
{
    char    *result = NULL;
    int    i = 0;

    if(str[0] != '\'' && str[0] != '\"' && str[0] != '$')
    {
        result = ft_text(result, str, &i);
        printf("11111[%s] || [%s] || [%d] || [%c]\n", result, str, i, str[i]);
    }
    while(str[i])
    {
        if(str[i] && str[i] == '$')
        {
            result = ft_expand(result, str, &i);
            printf(" $ = [%s] || [%s] || [%d] || [%c]\n", result, str, i, str[i]);
        }
        if(str[i] && str[i] == '\'')
        {
            result = handle_single(result, str, &i);
            printf(" ' = [%s] || [%s] || [%d] || [%c]\n", result, str, i, str[i]);
            if(str[i])
                i++;
        }
        else if(str[i] && str[i] == '\"')
        {
            result = handle_double(result, str, &i);
            printf(" \" = [%s] || [%s] || [%d] || [%c]\n", result, str, i, str[i]);
            if(str[i])
                i++;
        }
        else
        {
            printf("text\n");
            result = ft_text(result, str, &i);
            printf("test = [%s] || [%s] || [%d] || [%c]\n", result, str, i, str[i]);
        }
    }
    return (result);
}
void f(void)
{
    system("leaks a.out");
}
int main(int ac, char **av)
{
    (void)ac;
    atexit(f);
    char    *command = strdup(av[1]);
    char    *last = all_expand(command);
    free(command);
    printf("%s\n", last);
    free(last);
    return 0;
}
