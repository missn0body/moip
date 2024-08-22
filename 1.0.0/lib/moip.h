#ifndef ini__list__h
#define ini__list__h

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*
	An implementation of a bidirectional linked list, with
	some inspiration from an implementation made by Joel Yliluoma
	https://bisqwit.iki.fi/story/howto/cpp/lesson1/

	Made by anson in 2024, see LICENSE for related details
*/

#include <stdlib.h>
#include <string.h>

// Universal constants
constexpr short namebuf = 255;
constexpr short bufsize = 255;

// ini list functions and structures
struct inisect
{
	char section[namebuf + 1];
	char buffer [bufsize + 1];

	struct inisect *prev;
	struct inisect *next;
};

struct inifile
{
	char name[namebuf + 1];

	size_t sectcount;
	struct inisect *first;
	struct inisect *last;
};

void inisect_init		(struct inisect *, const char *, const char *);

struct inisect *inifile_begin	(struct inifile *);
struct inisect *inifile_end	(struct inifile *);
struct inisect *inifile_next	(struct inisect *);

void inifile_init		(struct inifile *, const char *);
void inifile_insert		(struct inifile *, struct inisect *, const char *, const char *);
void inifile_erase		(struct inifile *, struct inisect *);
void inifile_push_front		(struct inifile *, const char *, const char *);
void inifile_push_back		(struct inifile *, const char *, const char *);
void inifile_pop_front		(struct inifile *);
void inifile_pop_back		(struct inifile *);
void inifile_clear		(struct inifile *);
void inifile_done		(struct inifile *);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* ini__list__h */
