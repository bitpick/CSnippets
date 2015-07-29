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

#include "securestring.h"
#include <string.h>
#include <stdlib.h>


secstring secstring_init( const char* cstr, uint32_t len )
{
	if( len <= 0 )
		return NULL;
		
	secstring s = (secstring) malloc( sizeof( secstring ) );
	s->refcount = 1;
	if( cstr == NULL )
	{
		s->str = (char*) malloc( sizeof(char) * len );
		memcpy( s->str, 0, len );
	}
	else
	{
		s->str = (char*)strndup( cstr, len );
	}
	s->len = len;
	return s;
}


secstring secstring_reference( secstring s )
{
	if( s != NULL )
		s->refcount++;
	return s;
}


void secstring_release( secstring s )
{
	if(s == NULL)
		return;
		
	s->refcount--;
	if( s->refcount == 0 ) 
	{
		memset( s->str, 0, s->len );
		free( s );
		s->str = NULL;
	}
	s = NULL;
}


secstring secstring_clone( const secstring s )
{
	if( s != NULL )
	{
		secstring new_secstring = secstring_init( s->str, s->len );
		return new_secstring;
	}
	return NULL;
}
