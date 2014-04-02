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
