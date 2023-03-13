/*
 * HFVExplorer
 * Copyright (C) 1997-1998 by Anygraaf Oy
 * Author: Lauri Pesonen, email: lpesonen@clinet.fi or lauri.pesonen@anygraaf.fi
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include <windows.h>
#include "charset.h"

static unsigned char ANSI2MAC[256] = {
	0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 
	0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 
	0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F, 
	0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F, 
	0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F, 
	0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5A, 0x5B, 0x5C, 0x5D, 0x5E, 0x5F, 
	0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F, 
	0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7A, 0x7B, 0x7C, 0x7D, 0x7E, 0x7F, 
	0xAD, 0xB0, 0xE2, 0xC4, 0xE3, 0xC9, 0xA0, 0xE0, 0xF6, 0xE4, 0xDE, 0xDC, 0xCE, 0xB2, 0xB3, 0xB6, 
	0xB7, 0xD4, 0xD5, 0xD2, 0xD3, 0xA5, 0xD0, 0xD1, 0xF7, 0xAA, 0xDF, 0xDD, 0xCF, 0xBA, 0xFD, 0xD9, 
	0xCA, 0xC1, 0xA2, 0xA3, 0xDB, 0xB4, 0xBD, 0xA4, 0xAC, 0xA9, 0xBB, 0xC7, 0xC2, 0xF0, 0xA8, 0xF8, 
	0xA1, 0xB1, 0xC3, 0xC5, 0xAB, 0xB5, 0xA6, 0xE1, 0xFC, 0xC6, 0xBC, 0xC8, 0xF9, 0xDA, 0xD7, 0xC0, 
	0xCB, 0xE7, 0xE5, 0xCC, 0x80, 0x81, 0xAE, 0x82, 0xE9, 0x83, 0xE6, 0xE8, 0xED, 0xEA, 0xEB, 0xEC, 
	0xF5, 0x84, 0xF1, 0xEE, 0xEF, 0xCD, 0x85, 0xFB, 0xAF, 0xF4, 0xF2, 0xF3, 0x86, 0xFA, 0xB8, 0xA7, 
	0x88, 0x87, 0x89, 0x8B, 0x8A, 0x8C, 0xBE, 0x8D, 0x8F, 0x8E, 0x90, 0x91, 0x93, 0x92, 0x94, 0x95, 
	0xFE, 0x96, 0x98, 0x97, 0x99, 0x9B, 0x9A, 0xD6, 0xBF, 0x9D, 0x9C, 0x9E, 0x9F, 0xFF, 0xB9, 0xD8, 
};

static unsigned char MAC2ANSI[256] = {
	0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 
	0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 
	0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F, 
	0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F, 
	0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F, 
	0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5A, 0x5B, 0x5C, 0x5D, 0x5E, 0x5F, 
	0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F, 
	0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7A, 0x7B, 0x7C, 0x7D, 0x7E, 0x7F, 
	0xC4, 0xC5, 0xC7, 0xC9, 0xD1, 0xD6, 0xDC, 0xE1, 0xE0, 0xE2, 0xE4, 0xE3, 0xE5, 0xE7, 0xE9, 0xE8, 
	0xEA, 0xEB, 0xED, 0xEC, 0xEE, 0xEF, 0xF1, 0xF3, 0xF2, 0xF4, 0xF6, 0xF5, 0xFA, 0xF9, 0xFB, 0xFC, 
	0x86, 0xB0, 0xA2, 0xA3, 0xA7, 0x95, 0xB6, 0xDF, 0xAE, 0xA9, 0x99, 0xB4, 0x90, 0x80, 0xC6, 0xD8, 
	0x81, 0xB1, 0x8D, 0x8E, 0xA5, 0xB5, 0x8F, 0x90, 0xDE, 0xFE, 0x9D, 0xAA, 0xBA, 0xA6, 0xE6, 0xF8, 
	0xBF, 0xA1, 0xAC, 0xB2, 0x83, 0xB3, 0xB9, 0xAB, 0xBB, 0x85, 0xA0, 0xC0, 0xC3, 0xD5, 0x8C, 0x9C, 

//0x96, 0x96, 0x93, 0x94, 0x91, 0x92, 0xF7, 0xBE, 0xFF, 0x9F, 0xBD, 0xA4, 0x8B, 0x9B, 0x8A, 0x9A, 
	0x96, 0x97, 0x93, 0x94, 0x91, 0x92, 0xF7, 0xBE, 0xFF, 0x9F, 0xBD, 0xA4, 0x8B, 0x9B, 0x8A, 0x9A, 

	0x87, 0xB7, 0x82, 0x84, 0x89, 0xC2, 0xCA, 0xC1, 0xCB, 0xC8, 0xCD, 0xCE, 0xCF, 0xCC, 0xD3, 0xD4, 
	0xAD, 0xD2, 0xDA, 0xDB, 0xD9, 0xD0, 0x88, 0x98, 0xAF, 0xBC, 0xDD, 0xD7, 0xB8, 0x9E, 0xF0, 0xFD, 
};

BOOL	is_font_sjis = FALSE; /* noda */

void mac_to_pc_charset( unsigned char *s )
{
	int i, len = strlen( (LPSTR)s );

	/* added by noda */
	if(!is_font_sjis){
		for(i=0; i<len; i++) {
			s[i] = MAC2ANSI[s[i]];
		}
	}
}

void pc_to_mac_charset( unsigned char *s )
{
	int i, len = strlen( (LPSTR)s);

	/* added by noda */
	if(!is_font_sjis){
		for(i=0; i<len; i++) {
			s[i] = ANSI2MAC[s[i]];
		}
	}
}


#ifdef ANCIENT_HISTORY
void mac_to_pc_charset( unsigned char *s )
{
	int i, len = strlen( (LPSTR)s);
	unsigned char ch;

	for(i=0; i<len; i++) {
		ch = s[i];
		switch( ch ) {
			case (unsigned char)0x80:
				ch = (unsigned char)0xC4; // �
				break;
			case (unsigned char)0x8A:
				ch = (unsigned char)0xE4; // �
				break;
			case (unsigned char)0x85:
				ch = (unsigned char)0xD6; // �
				break;
			case (unsigned char)0x9A:
				ch = (unsigned char)0xF6; // �
				break;
			case (unsigned char)0x81:
				ch = (unsigned char)0xC5; // �
				break;
			case (unsigned char)0x8C:
				ch = (unsigned char)0xE5; // �
				break;
			case (unsigned char)0x9F:
				ch = (unsigned char)0xFC; // �
				break;
			case (unsigned char)0xC4:
				ch = (unsigned char)0x83; // f
				break;
		}
		s[i] = ch;
	}
	// OemToChar( (char *)s, (char *)s );
}

// c7 e8
void pc_to_mac_charset( unsigned char *s )
{
	int i, len = strlen( (LPSTR)s);
	unsigned char ch;

	for(i=0; i<len; i++) {
		ch = s[i];
		switch( ch ) {
			case (unsigned char)0xC4:
				ch = (unsigned char)0x80; // �
				break;
			case (unsigned char)0xE4:
				ch = (unsigned char)0x8A; // �
				break;
			case (unsigned char)0xD6:
				ch = (unsigned char)0x85; // �
				break;
			case (unsigned char)0xF6:
				ch = (unsigned char)0x9A; // �
				break;
			case (unsigned char)0xC5:
				ch = (unsigned char)0x81; // �
				break;
			case (unsigned char)0xE5:
				ch = (unsigned char)0x8C; // �
				break;
			case (unsigned char)0xFC:
				ch = (unsigned char)0x9F; // �
				break;
			case (unsigned char)0x83:
				ch = (unsigned char)0xC4; // f
				break;
		}
		s[i] = ch;
	}
	// OemToChar( (char *)s, (char *)s );
	// CharToOem( (char *)s, (char *)s );
}
#endif
