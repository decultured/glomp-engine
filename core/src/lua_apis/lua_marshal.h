/*
 * lmarshal.c
 * A Lua library for serializing and deserializing Lua values
 * Richard Hundt <richardhundt@gmail.com>
 *
 * License: MIT
 *
 * Copyright (c) 2010 Richard Hundt
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */
 
#ifndef glomp_lua_marshal_h
#define glomp_lua_marshal_h

#include <stdlib.h>
#include <string.h>
#include <stdint.h>


extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}


#define MAR_TREF 1
#define MAR_TVAL 2
#define MAR_TUSR 3

#define MAR_CHR 1
#define MAR_I32 4
#define MAR_I64 8

#define MAR_MAGIC 0x8e
#define SEEN_IDX  3

typedef struct mar_Buffer {
    size_t size;
    size_t seek;
    size_t head;
    char*  data;
} mar_Buffer;

static void buf_init(lua_State *L, mar_Buffer *buf);
static void buf_done(lua_State* L, mar_Buffer *buf);
static int buf_write(lua_State* L, const char* str, size_t len, mar_Buffer *buf);
static const char* buf_read(lua_State *L, mar_Buffer *buf, size_t *len);
static void mar_encode_value(lua_State *L, mar_Buffer *buf, int val, size_t *idx);
static int mar_encode_table(lua_State *L, mar_Buffer *buf, size_t *idx);

#define mar_incr_ptr(l) \
if (((*p)-buf)+(l) > len) luaL_error(L, "bad code"); (*p) += (l);

#define mar_next_len(l,T) \
if (((*p)-buf)+sizeof(T) > len) luaL_error(L, "bad code"); \
l = *(T*)*p; (*p) += sizeof(T);

static void mar_decode_value
(lua_State *L, const char *buf, size_t len, const char **p, size_t *idx);
static int mar_decode_table(lua_State *L, const char* buf, size_t len, size_t *idx);
static int mar_encode(lua_State* L);
static int mar_decode(lua_State* L);
static int mar_clone(lua_State* L);

int luaopen_marshal(lua_State *L);

#endif
