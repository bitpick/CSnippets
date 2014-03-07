/**
 * Copyright (C) 2014  bitpick
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 3
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#ifndef SECURESTRING_H_
#define SECURESTRING_H_

#include <stdint.h>

/*
 * @brief	secure string structure and funktions,
 * 			keeping trac on references and secure way to free resources
 */
typedef struct _secstring {
	char*		str;
	uint32_t	len;
	uint32_t	refcount;
} *secstring;


/* 
 * @brief	init new secure string
 * if cstr is NULL will init string with 0x00 value len times
 */
secstring secstring_init( const char* cstr, uint32_t len );

// @brief	publish reference usage
secstring secstring_reference( secstring s );

// @brief	release reference - will free resources if reference count reaches 0
void secstring_release( secstring s );

// @brief	create copy of sstring
secstring secstring_clone( const secstring s );

#endif
