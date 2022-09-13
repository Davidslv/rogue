/*
 * This file contains misc functions for dealing with armor
 * @(#)armor.c	4.14 (Berkeley) 02/05/99
 *
 * Rogue: Exploring the Dungeons of Doom
 * Copyright (C) 1980-1983, 1985, 1999 Michael Toy, Ken Arnold and Glenn Wichman
 * All rights reserved.
 *
 * See the file LICENSE.TXT for full copyright and licensing information.
 */

#include <curses.h>
#include "rogue.h"

/*
 * wear:
 *	The player wants to wear something, so let him/her put it on.
 */
void
wear()
{
    register THING *obj;
    register char *sp;

    if ((obj = get_item("wear", ARMOR)) == NULL)
	return;
    if (cur_armor != NULL)
    {
	addmsg("you are already wearing some");
	if (!terse)
	    addmsg(".  You'll have to take it off first");
	endmsg();
	after = FALSE;
	return;
    }
    if (obj->o_type != ARMOR)
    {
	msg("you can't wear that");
	return;
    }
    waste_time();
    obj->o_flags |= ISKNOW;
    sp = inv_name(obj, TRUE);
    cur_armor = obj;
    if (!terse)
	addmsg("you are now ");
    msg("wearing %s", sp);
}

/*
 * take_off:
 *	Get the armor off of the players back
 */
void
take_off()
{
    register THING *obj;

    if ((obj = cur_armor) == NULL)
    {
	after = FALSE;
	if (terse)
		msg("not wearing armor");
	else
		msg("you aren't wearing any armor");
	return;
    }
    if (!dropcheck(cur_armor))
	return;
    cur_armor = NULL;
    if (terse)
	addmsg("was");
    else
	addmsg("you used to be");
    msg(" wearing %c) %s", obj->o_packch, inv_name(obj, TRUE));
}

/*
 * waste_time:
 *	Do nothing but let other things happen
 */
void
waste_time()
{
    do_daemons(BEFORE);
    do_fuses(BEFORE);
    do_daemons(AFTER);
    do_fuses(AFTER);
}
