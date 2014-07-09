/**
 * Copyright (C) 2014 bitpick
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 3
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 **/


#ifndef DUMP_H_
#define DUMP_H_
 
/*
 * @param	addr	address of data to dump
 * @param	len	length of data to dump in bytes
 * @param	show_real_address	'false'	for relative address listing starting at 0x00
 * 					'true'	for real address listing starting at @addr
 * @param   show_ascii  'true' to show ASCII output
 */ 
void dump_hex(void *addr, size_t len, bool show_real_address, bool show_ascii);
 
#endif
