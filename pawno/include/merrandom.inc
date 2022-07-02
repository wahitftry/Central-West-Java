/* MerRandom 2.1 Pawn Include
 * Scripted by Cyber_Punk © 2009-2010
 * Thanks to Tannz0rz for C++ Coaching :P
 * Huge Thanks to Agner Fog for his Mersenne Twister Assembly code!!! 
 * This file is provided as is (no warranties).
 */
#if defined _merrandom_included
  #endinput
#endif
#define _merrandom_included
#pragma library merrandom

native MRandom(max); // Get an integer in the range 0 to n (for n < 2^32-1)
native MRandRange(min, max); // Get an integer in a specified range
native MRandFloatRange(Float:min, Float:max, &Float:result); // Get a float in the range *return it in a Float variable...
