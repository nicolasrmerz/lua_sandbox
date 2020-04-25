#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>

#define NUM_TRIALS 100000

//#include "mylua.h"

void error (lua_State *L, const char *fmt, ...)
{
    va_list argp;
    va_start(argp, fmt);
    vfprintf(stderr, fmt, argp);
    va_end(argp);
    lua_close(L);
    exit(EXIT_FAILURE);
}

int qlua_checkhook(lua_State *L, const char *hook)
{
    lua_getglobal(L, "CheckHook");
    lua_pushstring(L, hook);
    
    if(lua_pcall(L, 1, 1, 0) != 0)
        error(L, "error running function CheckHook: %s\n", lua_tostring(L, -1));

    if (!lua_isboolean(L, -1))
        error(L, "function must return a number");

    int res = lua_toboolean(L, -1);
    lua_pop(L, 1);
    return res;
}

void qlua_gethook(lua_State *L, const char *hook)
{
    lua_getglobal(L, "CallHook");
    lua_pushstring(L, hook);
}

void check_first_1(lua_State *L, const char *registered)
{
    if (qlua_checkhook(L, registered)) {
        qlua_gethook(L, registered);
        lua_pushinteger(L, 5);

        if(lua_pcall(L, 2, 0, 0) != 0)
            error(L, "error running function hook.test: %s\n", lua_tostring(L, -1));
    }

}

void all_at_once_1(lua_State *L, const char *registered)
{
    lua_getglobal(L, "CheckCallHook");
    lua_pushstring(L, registered);
    lua_pushinteger(L, 5);

    if(lua_pcall(L, 2, 0, 0) != 0)
        error(L, "error running function hook.test: %s\n", lua_tostring(L, -1));
}

void check_first_5(lua_State *L, const char *registered)
{
    if (qlua_checkhook(L, registered)) {
        qlua_gethook(L, registered);
        lua_pushinteger(L, 5);
        lua_pushinteger(L, 5);
        lua_pushinteger(L, 5);
        lua_pushinteger(L, 5);
        lua_pushinteger(L, 5);

        if(lua_pcall(L, 6, 0, 0) != 0)
            error(L, "error running function hook.test: %s\n", lua_tostring(L, -1));
    }

}

void all_at_once_5(lua_State *L, const char *registered)
{
    lua_getglobal(L, "CheckCallHook");
    lua_pushstring(L, registered);
    lua_pushinteger(L, 5);
    lua_pushinteger(L, 5);
    lua_pushinteger(L, 5);
    lua_pushinteger(L, 5);
    lua_pushinteger(L, 5);

    if(lua_pcall(L, 6, 0, 0) != 0)
        error(L, "error running function hook.test: %s\n", lua_tostring(L, -1));
}

int parse_and_push_args(lua_State *L, va_list argp, const char *fmt)
{
    const char *p;
    int i = 0;
    int a;
    char *s;

    for(p = fmt; *p != '\0'; p++) {
        if(*p != '%')
        {
           putchar(*p);
           continue;
        }
        switch(*++p) {
            case 'd':
                a = va_arg(argp, int);
                lua_pushinteger(L, a);
                break;
            case 's':
                s = va_arg(argp, char *);
                lua_pushstring(L, s);
                break;
            case '%':
                putchar('%');
                continue;
        }
        i++;
    }
    return i;
}

void check_first_vararg_5(lua_State *L, const char *hook, const char* fmt, ...)
{
    
    if (qlua_checkhook(L, hook)) {
        qlua_gethook(L, hook);
        va_list argp;

        va_start(argp, fmt);
        // +1 to compensate for pushing the name of the hook
        int num_args = parse_and_push_args(L, argp, fmt) + 1;
        va_end(argp);
        
        if(lua_pcall(L, num_args, 0, 0) != 0)
            error(L, "error running function hook.test: %s\n", lua_tostring(L, -1));
    }
}

void check_first_static_5(lua_State *L, const char *hook, int a, int b, int c, int d, int e)
{
    if (qlua_checkhook(L, hook)) {
        qlua_gethook(L, hook);
        lua_pushinteger(L, a);
        lua_pushinteger(L, b);
        lua_pushinteger(L, c);
        lua_pushinteger(L, d);
        lua_pushinteger(L, e);

        if(lua_pcall(L, 6, 0, 0) != 0)
            error(L, "error running function hook.test: %s\n", lua_tostring(L, -1));
    }
}

void time_trial(void (*fn)(lua_State*, const char *), lua_State *L, const char *hook)
{
    struct timeval start, end;
    int i;

    //start = clock();
    gettimeofday(&start, NULL);
    for(i = 0; i < NUM_TRIALS; i++)
        (*fn)(L, hook);
    gettimeofday(&end, NULL);
    long seconds = (end.tv_sec - start.tv_sec);
    long micros = ((seconds * 1000000) + end.tv_usec) - (start.tv_usec);
    
    printf("Time taken: %ld microseconds\n", micros);
}

int main() {
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);
    if(luaL_dofile(L, "init.lua") != 0)
        error(L, "error running init.lua: %s\n", lua_tostring(L, -1));
    if(luaL_dofile(L, "benchmark.lua"))
        error(L, "error running benchmark.lua: %s\n", lua_tostring(L, -1));

    /*
    time_trial(&check_first_1, L, "registered");
    time_trial(&all_at_once_1, L, "registered");
    time_trial(&check_first_5, L, "registered");
    time_trial(&all_at_once_5, L, "registered");

    time_trial(&check_first_1, L, "unregistered");
    time_trial(&all_at_once_1, L, "unregistered");
    time_trial(&check_first_5, L, "unregistered");
    time_trial(&all_at_once_5, L, "unregistered");
    */


    struct timeval start, end;
    int i, j;
    long seconds;
    long micros;

    long varsum = 0;
    long statsum = 0;

    for(j = 0; j < 100; j++) {
        gettimeofday(&start, NULL);
        for(i = 0; i < NUM_TRIALS; i++)
            check_first_vararg_5(L, "registered", "%d%d%d%d%d", 5, 5, 5, 5, 5);
        gettimeofday(&end, NULL);
        seconds = (end.tv_sec - start.tv_sec);
        micros = ((seconds * 1000000) + end.tv_usec) - (start.tv_usec);
        varsum += micros;


        gettimeofday(&start, NULL);
        for(i = 0; i < NUM_TRIALS; i++)
            check_first_static_5(L, "registered", 5, 5, 5, 5, 5);
        gettimeofday(&end, NULL);
        seconds = (end.tv_sec - start.tv_sec);
        micros = ((seconds * 1000000) + end.tv_usec) - (start.tv_usec);
        statsum += micros;
        
    }

    varsum /= 100;
    statsum /= 100;

    printf("Average for varargs: %ld microseconds\n", varsum);
    printf("Average for static: %ld microseconds\n", statsum);
    lua_close(L);

    return 0;
}

