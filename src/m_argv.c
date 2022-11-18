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
 *  Some argument handling.
 *
 *-----------------------------------------------------------------------------*/

#include <string.h>
// CPhipps - include the correct header
#include "doomtype.h"
#include "m_argv.h"

int myargc;
const char **myargv;

//
// M_CheckParm
// Checks for the given parameter
// in the program's command line arguments.
// Returns the argument number (1 to argc-1)
// or 0 if not present
//

/*
All existing usages of this function call it with one of these args:

"-affinity"
  Set the process affinity mask, to address an SDL_mixer bug
    type: int

"-altdeath"
  Enables an alternate deathmatch mode. Overrides "-deathmatch" flag
    type: flag

"-autoshot"
  Enables the automatic taking of screenshots.
  First arg is the number of ticks between screenshots, second arg is the file
to write to. type: int, string

"-avg"
  Enables "Austin Virtual Gaming" mode where deathmatch games end after 20 min
  acts as if -timer 20 was used
    type: flag

"-bexout"
  Specifies path to file that we output to when processing a DEH or BEX file
  Alias for "-dehout"
    type: string

"-blockmap"
  Seems to determine that a thing called a 'blockmap' should be generated
instead of read as a lump type: flag

"-cerr"
  Controls which calls to lprintf actually make it to stderr
    type: string
      Disable all outputs and each character in the string matching a character
in "ICWEFDA" (ignoring case) enables printing for that type of message: Info,
Confirm, Warn, Error, Fatal, Debug, Always

"-checksum"
  Filepath to a file where a checksum should be written
    type: string (special case of "-" means "write checksum to stdout")

"-complevel"
  Sets some compatibility mode, which seems to only have valid values as defined
by the complevel_t enum, but I'm not sure. Oh, actually, this seems to be a
great resource on this topic:
https://doomwiki.org/wiki/PrBoom#Compatibility_modes_and_settings type: int

"-config"
  Full path to config file, which by default is something like boom.cfg, located
in the current working directory?  Maybe? type: string

"-cout"
  Controls which calls to lprintf actually make it to stdout
    type: string
      Disable all outputs and each character in the string matching a character
in "ICWEFDA" (ignoring case) enables printing for that type of message: Info,
Confirm, Warn, Error, Fatal, Debug, Always

"-deathmatch"
  Enables the usual deathmatch mode. Overriden by "-altdeath" flag
    type: flag

"-deh"
  Path to some .deh or .bex file?  without the extension?  This isn't clear
    type: string

"-dehout"
  Specifies path to file that we output to when processing a DEH or BEX file
  Alias for "-bexout"
    type: string

"-devparm"
  Enables "developer mode" (https://doom.fandom.com/wiki/Parameter#-devparm)
    type: flag

"-dog"
  Sets the number of dogs/helpers in some mode
  alias for "dogs"
    type: int

"-dogs"
  Sets the number of dogs/helpers in some mode
  alias for "dog"
    type: int

"-episode"
  Sets the episode on which to start the game
    type: char, a single digit

"-fast"
  ... not sure what this does, honestly.  Maybe this?
https://doom.fandom.com/wiki/Parameter#-fast type: flag

"-fastdemo"
  Like -timedemo, except that it runs as fast as possible.  Arg is the name of a
lump. type: string

"-ffmap"
  Fast forward the demo (play at max speed) until reaching map num (note that
this takes just a number, not a map name, so -ffmap 7 to go fast until MAP07 or
ExM7). type: int

"-file"
  Wad files/lump names
    type: multi-string (can have more than one value)

"-force_remove_slime_trails"
  If enabled, forcably "remove slime trails", which seems to be a manual attempt
at fixing some visual problem inherent in the game type: flag

"-forceoldbsp"
  Sets a boolean value that is similarly named....affect this has isn't clear to
me yet type: flag

"-frags"
  Sets the frag limit, I think?
    type: int

"-fullscreen"
  Sets whether or not fullscreen is used
  anti-alias for "-nofullscreen" (and "-nofullscreen" overrides)
    type: flag

"-geom"
  Sets the desired size of the window
  alias for "-geometry"
    type: string that matches the format string "%dx%d" (where this is
interpreted as width x height)

"-geometry"
  Sets the desired size of the window
  alias for "-geom"
    type: string that matches the format string "%dx%d" (where this is
interpreted as width x height)

"-height"
  Sets the desired height of the window
    type: int

"-iwad"
  Path to iwad file
    type: string

"-loadgame"
  Load a saved game. Arg value is the save slot to load from
    type: int

"-longtics"
  "Record a high resolution "Doom 1.91" demo." - from here:
https://www.chocolate-doom.org/wiki/index.php/Command_line_arguments#Demo_options
    type: flag

"-net"
  "Starts a network game using the UDP/IP protocol, by connecting to the machine
hostname via port number port. (The port number may be omitted, in which case
port 5030 is used.)" from here:
https://doomwiki.org/wiki/Source_port_parameters#-net_.3Chostname.3E_.3Cport.3E
    type: string
    format: hostname[:port]

"-noblit"
  Avoids blitting graphics data to the screen....but doesn't seem to be hooked
up to anything type: flag

"-nodeh"
  Disable automatic loading of Dehacked patches for certain IWAD files.
    type: flag

"-nodraw"
  Avoids drawing graphics all together
    type: flag

"-nofullscreen"
  Sets whether or not fullscreen is used
  anti-alias for "-fullscreen" (and "-nofullscreen" overrides)
    type: flag

"-nojoy"
  Disables joystick input.
    type: flag

"-noload"
  Starts a game without loading any of the default PWADs or executable patches
(defined within an in-game menu). from here:
https://doomwiki.org/wiki/Source_port_parameters#-noload type: flag

"-nomonsters"
  Disable all monsters
    type: flag

"-nomouse"
  Prevents mouse "grabbing". The default behavior is to grab the mouse
  from here: https://doomwiki.org/wiki/Source_port_parameters#-nomouse
    type: flag


"-nomusic"
  Disable background music
    type: flag

"-nosfx"
  Disable sound effects
    type: flag

"-nosound"
  Disable background music and sound effects
  alias for specifying both "-nomusic" and "-nosfx"
    type: flag

"-nowindow"
  Somewhat similar to "-fullscreen", the difference isn't clear to me yet
  anti-alias for "-window" (and "-nowindow" overrides)
    type: flag

"-playdemo"
  Play back the demo lump named by the value of this arg
    type: string

"-record"
  Record to a lump named by the value of this arg
    type: string

"-recordfrom"
  NOT FULLY IMPLEMENTED: two arg option that was meant to allow record from a
saved game from here: https://doom.fandom.com/wiki/Parameter#-recordfrom type:
(int string)

"-respawn"
  Allows monsters to respawn
    type: flag

"-save"
  Specifies a directory for storing saved games
    type: string

"-skill"
  Set the game skill, 1-5 (1: easiest, 5: hardest). A skill of 0 disables all
monsters. from here:
https://www.chocolate-doom.org/wiki/index.php/Command_line_arguments#Game_start_options
    type: char, a single digit, 1-5

"-solo-net"
  Allows beginning a game with cooperative gameplay rules while only a single
player is active. from here:
https://doomwiki.org/wiki/Source_port_parameters#-solo-net type: flag

"-timedemo"
  Play back the demo lump named by the value of this arg, and "determine the
framerate of the screen" more concrete details here:
https://doom.fandom.com/wiki/Parameter#-timedemo type: string

"-timer"
  Specifies the number of minutes before automatically exiting the level.
    type: int

"-turbo"
  Sets the players movement speed to some percent of its original value, from
10% to 400% type: int

"-vidmode"
  Sets the video mode to one of 5 possible values
    type: string

"-viewangle"
  Causes the player view to be rotated by a given  offset  (speci-fied in
45degree increments, in the range 0..7) from the way the player is facing. from
README.command-line.md type: int, clamped to the range 0-7

"-warp"
  Specifies either the start map or start episode/map, depending upon the game
mode set Alias for "-wart" type: (int, Optional<int>)

"-wart"
  Specifies either the start map or start episode/map, depending upon the game
mode set Alias for "-warp" type: (int, Optional<int>)

"-width"
  Sets the desired width of the window
    type: int

"-window"
  Somewhat similar to "-nofullscreen", the difference isn't clear to me yet
  anti-alias for "-nowindow" (and "-nowindow" overrides)
    type: flag

*/

int M_CheckParm(const char *check) {
  int i = myargc - 1; // start from the last arg
  while (i > 0) {
    if (!strcasecmp(check, myargv[i]))
      return i;
    i--; // and walk backwards
  }
  return 0;
}
