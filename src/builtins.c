/*
   psh/builtins.c - builtins caller file of the psh

   Copyright 2013 wuyve.
   Copyright 2017 Zhang Maiyun.
*/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "builtin.h"
#include "libpsh/util.h"
#include "libpsh/xmalloc.h"

extern int last_command_status;
extern char *argv0;

static int builtin_unsupported(int argc, char **argv);
static int builtin_about_handler(int argc, char **argv);
static int builtin_getstat_handler(int argc, char **argv);

/* List of all builtins, sorted by name */
const struct builtin builtins[] = {{".", &builtin_unsupported},
                                   {":", &builtin_true},
                                   {"about", &builtin_about_handler},
                                   {"alias", &builtin_unsupported},
                                   {"bg", &builtin_unsupported},
                                   {"bind", &builtin_unsupported},
                                   {"break", &builtin_unsupported},
                                   {"builtin", &builtin_builtin},
                                   {"case", &builtin_unsupported},
                                   {"cd", &builtin_cd},
                                   {"chdir", &builtin_cd},
                                   {"command", &builtin_unsupported},
                                   {"continue", &builtin_unsupported},
                                   {"declare", &builtin_unsupported},
                                   {"do", &builtin_unsupported},
                                   {"done", &builtin_unsupported},
                                   {"echo", &builtin_echo},
                                   {"elif", &builtin_unsupported},
                                   {"else", &builtin_unsupported},
                                   {"esac", &builtin_unsupported},
                                   {"eval", &builtin_unsupported},
                                   {"exec", &builtin_exec},
                                   {"exit", &builtin_exit},
                                   {"export", &builtin_unsupported},
                                   {"false", &builtin_false},
                                   {"fc", &builtin_unsupported},
                                   {"fg", &builtin_unsupported},
                                   {"fi", &builtin_unsupported},
                                   {"for", &builtin_unsupported},
                                   {"getopts", &builtin_unsupported},
                                   {"getstat", &builtin_getstat_handler},
                                   {"hash", &builtin_unsupported},
                                   {"history", &builtin_history},
                                   {"if", &builtin_unsupported},
                                   {"jobid", &builtin_unsupported},
                                   {"jobs", &builtin_unsupported},
                                   {"local", &builtin_unsupported},
                                   {"logout", &builtin_exit},
                                   {"popd", &builtin_unsupported},
                                   {"pushd", &builtin_unsupported},
                                   {"pwd", &builtin_pwd},
                                   {"quit", &builtin_exit},
                                   {"read", &builtin_unsupported},
                                   {"readonly", &builtin_unsupported},
                                   {"return", &builtin_unsupported},
                                   {"set", &builtin_unsupported},
                                   {"setvar", &builtin_unsupported},
                                   {"shift", &builtin_unsupported},
                                   {"source", &builtin_unsupported},
                                   {"test", &builtin_unsupported},
                                   {"then", &builtin_unsupported},
                                   {"times", &builtin_unsupported},
                                   {"trap", &builtin_unsupported},
                                   {"true", &builtin_true},
                                   {"type", &builtin_unsupported},
                                   {"ulimit", &builtin_unsupported},
                                   {"umask", &builtin_unsupported},
                                   {"unalias", &builtin_unsupported},
                                   {"unset", &builtin_unsupported},
                                   {"until", &builtin_unsupported},
                                   {"wait", &builtin_unsupported},
                                   {"which", &builtin_unsupported},
                                   {"while", &builtin_unsupported}};

int get_argc(char **argv)
{
    int argc = 0;
    for (; argv[argc]; ++argc)
        ;
    return argc;
}

static int builtin_unsupported(int argc, char **argv)
{
    OUT2E("%s: %s: Not supported, coming soon\n", argv0, argv[0]);
    return 127;
}

static int builtin_about_handler(int argc, char **argv)
{
    printf("psh is a not fully implemented shell in UNIX.\n");
    return 0;
}

static int builtin_getstat_handler(int argc, char **argv)
{
    printf("%d\n", last_command_status);
    return 0;
}

int compare_builtin(const void *key, const void *cur)
{
    const struct builtin *bkey = (const struct builtin *)key;
    const struct builtin *builtin = (const struct builtin *)cur;
    return strcmp(bkey->name, builtin->name);
}

builtin_function find_builtin(char *name)
{
    struct builtin *key = xmalloc(sizeof(struct builtin));
    struct builtin *result;

    key->name = name;
    result = (struct builtin *)bsearch(
        key, builtins, sizeof(builtins) / sizeof(struct builtin),
        sizeof(struct builtin), &compare_builtin);

    xfree(key);

    return result != NULL ? result->proc : (builtin_function)0;
}