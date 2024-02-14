/* Emacs style mode select   -*- C++ -*-
 *-----------------------------------------------------------------------------
 *
 *
 *  PrBoom: a Doom port merged with LxDoom and LSDLDoom
 *  based on BOOM, a modified and improved DOOM engine
 *  Copyright (C) 1999 by
 *  id Software, Chi Hoang, Lee Killough, Jim Flynn, Rand Phares, Ty Halderman
 *  Copyright (C) 1999-2000 by
 *  Jess Haas, Nicolas Kalkhof, Colin Phipps, Florian Schulze
 *  Copyright 2005, 2006 by
 *  Florian Schulze, Colin Phipps, Neil Stevens, Andrey Budko
 *
 *  This program is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  as published by the Free Software Foundation; either version 2
 *  of the License, or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
 *  02111-1307, USA.
 *
 * DESCRIPTION:
 *  External non-system-specific stuff, like storing config settings,
 *  simple file handling, and saving screnshots.
 *
 *-----------------------------------------------------------------------------*/

#ifndef __M_MISC__
#define __M_MISC__

#include "doomtype.h"
//
// MISC
//

boolean M_WriteFile(char const *name, void *source, int length);

int M_ReadFile(char const *name, byte **buffer);

void M_ScreenShot(void);
void M_DoScreenShot(const char *); // cph

void M_LoadDefaults(void);

void M_SaveDefaults(void);

struct default_s *M_LookupDefault(const char *name); /* killough 11/98 */

// phares 4/21/98:
// Moved from m_misc.c so m_menu.c could see it.

// CPhipps - struct to hold a value in a config file
// Cannot be a union, as it must be initialised
typedef struct default_s {
  const char *name;
  /* cph -
   * The location struct holds the pointer to the variable holding the
   *  setting. For int's we do nothing special.
   * For strings, the string may actually be stored on our heap with Z_Strdup()
   *  or may be statically allocated. BUT we don't want the rest of the program
   *  to be able to modify them, so all such pointers to strings are const.
   *  But, any such string stored on our heap may need to be free'd, and in that
   *  case we keep a non-const pointer around ("owned_value") for such
   *  instances.
   */
  struct {
    int *pi;
    const char **ppsz;
    // If non-NULL then the pointed-to string is "owned" by this default_t,
    // (this "owned" string will be the same string pointed to by *ppsz, and
    // should likely be free'd if *ppsz changes to point to a different string)
    char *owned_value;
  } location;
  struct {
    int i;
    const char *psz;
  } defaultvalue; // CPhipps - default value
  // Limits (for an int)
  int minvalue; // jff 3/3/98 minimum allowed value
  int maxvalue; // jff 3/3/98 maximum allowed value
  enum {
    def_none,             // Dummy entry
    def_str,              // A string
    def_int,              // Integer
    def_hex,              // Integer (write in hex)
    def_bool = def_int,   // Boolean
    def_key = def_hex,    // Key code (byte)
    def_mouseb = def_int, // Mouse button
    def_colour = def_hex  // Colour (256 colour palette entry)
  } type;                 // CPhipps - type of entry
  int setupscreen;        // phares 4/19/98: setup screen where this appears
  int *current;           /* cph - MBF-like pointer to current value */
  // cph - removed the help strings from the config file
  // const char* help;       // jff 3/3/98 description of parameter
  // CPhipps - remove unused "lousy hack" code
  struct setup_menu_s *setup_menu; /* Xref to setup menu item, if any */
} default_t;

// Document this
// The caller of this function must guarantee that the value pointed to by
// 'string' will outlive the value pointed to by 'default'
void M_AssignStringValue(default_t *setting, const char *string);
// Document this
void M_AssignStringValueAndTakeOwnership(default_t *setting, char *string);

#define IS_STRING(dv) ((dv).type == def_str)
// CPhipps - What is the max. key code that X will send us?
#define MAX_KEY 65536
#define MAX_MOUSEB 2

#define UL (-123456789) /* magic number for no min or max for parameter */

#endif
