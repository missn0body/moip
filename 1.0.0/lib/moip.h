#ifndef ini__list__h
#define ini__list__h

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*
	A configuration file handling/creation library, using
	an implementation of a bidirectional linked list, with
	some inspiration from an implementation made by Joel Yliluoma
	https://bisqwit.iki.fi/story/howto/cpp/lesson1/

	Made by anson in 2024, see LICENSE for related details
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Universal constants
constexpr short namebuf = 255;
constexpr short bufsize = 255;

// ini list functions and structures
typedef struct inisect
{
	char section[namebuf + 1];
	char buffer [bufsize + 1];

	struct inisect *prev;
	struct inisect *next;
} inisect;

struct inifile
{
	char name[namebuf + 1];

	size_t sectcount;
	struct inisect *first;
	struct inisect *last;
};

// .ini section creation
void inisect_init		(struct inisect *, const char *, const char *);

// .ini section referencing
struct inisect *inifile_begin	(struct inifile *);
struct inisect *inifile_end	(struct inifile *);
struct inisect *inifile_next	(struct inisect *);

// .ini file creation
void inifile_init		(struct inifile *, const char *);

// linked list related functions
void inifile_insert		(struct inifile *, struct inisect *, const char *, const char *);
void inifile_erase		(struct inifile *, struct inisect *);
void inifile_push_front		(struct inifile *, const char *, const char *);
void inifile_push_back		(struct inifile *, const char *, const char *);
void inifile_pop_front		(struct inifile *);
void inifile_pop_back		(struct inifile *);
void inifile_clear		(struct inifile *);
void inifile_done		(struct inifile *);

// .ini file manipulation
void inisect_print		(FILE *, struct inisect *, bool);
void inifile_print		(FILE *, struct inifile *, bool);
void inifile_operate		(struct inifile *, void (*functor)(struct inisect *));

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* ini__list__h */
