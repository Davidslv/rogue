/*
 * Defines for things used in mach_dep.c
 *
 * @(#)extern.h	4.35 (Berkeley) 02/05/99
 *
 * Rogue: Exploring the Dungeons of Doom
 * Copyright (C) 1980-1983, 1985, 1999 Michael Toy, Ken Arnold and Glenn Wichman
 * All rights reserved.
 *
 * See the file LICENSE.TXT for full copyright and licensing information.
 */


#ifdef HAVE_CONFIG_H
#ifdef PDCURSES
#undef HAVE_UNISTD_H
#undef HAVE_LIMITS_H
#undef HAVE_MEMORY_H
#undef HAVE_STRING_H
#endif
#include "config.h"
#elif defined(__DJGPP__)
#define HAVE_SYS_TYPES_H 1
#define HAVE_PROCESS_H 1
#define HAVE_PWD_H 1
#define HAVE_TERMIOS_H 1
#define HAVE_SETGID 1
#define HAVE_GETGID 1
#define HAVE_SETUID 1
#define HAVE_GETUID 1
#define HAVE_GETPASS 1
#define HAVE_SPAWNL 1
#define HAVE_ALARM 1
#define HAVE_ERASECHAR 1
#define HAVE_KILLCHAR 1
#elif defined(_WIN32)
#define HAVE_CURSES_H
#define HAVE_TERM_H
#define HAVE__SPAWNL
#define HAVE_SYS_TYPES_H
#define HAVE_PROCESS_H
#define HAVE_ERASECHAR 1
#define HAVE_KILLCHAR 1
#elif defined(__CYGWIN__)
#define HAVE_SYS_TYPES_H 1
#define HAVE_PWD_H 1
#define HAVE_PWD_H 1
#define HAVE_SYS_UTSNAME_H 1
#define HAVE_ARPA_INET_H 1
#define HAVE_UNISTD_H 1
#define HAVE_TERMIOS_H 1
#define HAVE_NCURSES_TERM_H 1
#define HAVE_ESCDELAY
#define HAVE_SETGID 1
#define HAVE_GETGID 1
#define HAVE_SETUID 1
#define HAVE_GETUID 1
#define HAVE_GETPASS 1
#define HAVE_GETPWUID 1
#define HAVE_WORKING_FORK 1
#define HAVE_ALARM 1
#define HAVE_SPAWNL 1
#define HAVE__SPAWNL 1
#define HAVE_ERASECHAR 1
#define HAVE_KILLCHAR 1
#else /* POSIX */
#define HAVE_SYS_TYPES_H 1
#define HAVE_PWD_H 1
#define HAVE_PWD_H 1
#define HAVE_SYS_UTSNAME_H 1
#define HAVE_ARPA_INET_H 1
#define HAVE_UNISTD_H 1
#define HAVE_TERMIOS_H 1
#define HAVE_TERM_H 1
#define HAVE_SETGID 1
#define HAVE_GETGID 1
#define HAVE_SETUID 1
#define HAVE_GETUID 1
#define HAVE_SETREUID 1
#define HAVE_SETREGID 1
#define HAVE_GETPASS 1
#define HAVE_GETPWUID 1
#define HAVE_WORKING_FORK 1
#define HAVE_ERASECHAR 1
#define HAVE_KILLCHAR 1
#ifndef _AIX
#define HAVE_GETLOADAVG 1
#endif
#define HAVE_ALARM 1
#endif

#ifdef __DJGPP__
#undef HAVE_GETPWUID /* DJGPP's limited version doesn't even work as documented */
#endif

/*
 * Don't change the constants, since they are used for sizes in many
 * places in the program.
 */

#include <stdlib.h>

#undef SIGTSTP

#define MAXSTR		1024	/* maximum length of strings */
#define MAXLINES	32	/* maximum number of screen lines used */
#define MAXCOLS		80	/* maximum number of screen columns used */

#define RN		(((seed = seed*11109+13849) >> 16) & 0xffff)
#ifdef CTRL
#undef CTRL
#endif
#define CTRL(c)		(c & 037)

/*
 * Now all the global variables
 */

extern bool	got_ltc, in_shell;
extern int	wizard;
extern char	fruit[], prbuf[], whoami[];
extern int orig_dsusp;
extern FILE	*scoreboard;

/*
 * Function types
 */

void    auto_save(int);
void	come_down();
void	doctor();
void	end_line();
void    endit(int sig);
void	fatal();
void	getltchars();
void	land();
void    leave(int);
void	my_exit();
void	nohaste();
void	playit();
void    playltchars(void);
void	print_disc(char);
void    quit(int);
void    resetltchars(void);
void	rollwand();
void	runners();
void	set_order();
void	sight();
void	stomach();
void	swander();
void	tstp(int ignored);
void	unconfuse();
void	unsee();
void	visuals();

char	add_line(char *fmt, char *arg);

char	*killname(char monst, bool doart);
char	*nothing(char type);
char	*type_name(int type);

#ifdef CHECKTIME
int	checkout();
#endif

int	md_chmod(char *filename, int mode);
char	*md_crypt(char *key, char *salt);
int	md_dsuspchar();
int	md_erasechar();
char	*md_gethomedir();
char	*md_getusername();
int	md_getuid();
char	*md_getpass(char *prompt);
int	md_getpid();
char	*md_getrealname(int uid);
void	md_init();
int	md_killchar();
void	md_normaluser();
void	md_raw_standout();
void	md_raw_standend();
int	md_readchar();
int	md_setdsuspchar(int c);
int	md_shellescape();
void	md_sleep(int s);
int	md_suspchar();
int	md_hasclreol();
int	md_unlink(char *file);
int	md_unlink_open_file(char *file, FILE *inf);
void md_tstpsignal();
void md_tstphold();
void md_tstpresume();
void md_ignoreallsignals();
void md_onsignal_autosave();
void md_onsignal_exit();
void md_onsignal_default();
int md_issymlink(char *sp);

