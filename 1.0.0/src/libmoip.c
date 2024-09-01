#include "../lib/moip.h"

// ini list node functions
// Some of the functions below are simplifications of functions earlier

void inisect_init(struct inisect *obj, const char *name, const char *what)
{
	strncpy(obj->section, name, namebuf);
	strncpy(obj->buffer,  what, bufsize);
	return;
}

// Simple pointers
struct inisect *inifile_begin(struct inifile *obj) { return obj->first; }
struct inisect *inifile_end  (struct inifile *obj) { return nullptr; }
// This is designed to be used to iterate through the list
struct inisect *inifile_next (struct inisect *obj) { return obj->next; }

void inifile_init(struct inifile *obj, const char *name)
{
	obj->first = nullptr;
	obj->last = nullptr;

	strncpy(obj->name, name, namebuf);
	return;
}

void inifile_insert(struct inifile *obj, struct inisect *where, const char *name, const char *what)
{
	// Assign memory to a section, with a name and string
	// "what" is assumed to be a null-terminated string, so
	// strlen is used to determine length
	struct inisect *newsect = (struct inisect *)malloc(sizeof(*newsect));
	inisect_init(newsect, name, what);

	// Determine previous and next links based on location
	newsect->prev = where ? where->prev : obj->last;
	newsect->next = where;

	// Assigning the new section while checking for edge cases
	if(newsect->prev)	newsect->prev->next = newsect;
	if(where)		where->prev = newsect;
	if(where == obj->first)	obj->first = newsect;
	if(!where)		obj->last = newsect;

	obj->sectcount++;
	return;
}

void inifile_erase(struct inifile *obj, struct inisect *what)
{
	// Making aliases for later simplification
	struct inisect *prev = what->prev;
	struct inisect *next = what->next;

	// Detaching, reassigning, and checking for edge cases
	if(prev)		prev->next = next;
	if(next) 		next->prev = prev;
	if(what == obj->first) 	obj->first = next;
	if(what == obj->last) 	obj->last = prev;

	// Finally free the memory, innermost memory first
	free(what);
	return;
}

// The aforementioned simplifications, these are what the user will be expected to use.
// Again, "what" is assumed to be a null-terminated string
void inifile_push_front(struct inifile *obj, const char *name, const char *what) { inifile_insert(obj, inifile_begin(obj), name, what); return; }
void inifile_push_back(struct inifile *obj, const char *name, const char *what)  { inifile_insert(obj, inifile_end(obj),   name, what); return; }
void inifile_pop_front(struct inifile *obj)					 { inifile_erase (obj, inifile_begin(obj));		return; }
void inifile_pop_back(struct inifile *obj)					 { inifile_erase (obj, inifile_end(obj));		return; }

void inifile_clear(struct inifile *obj)
{
	while(obj->first) inifile_erase(obj, obj->first);
	return;
}

// This acts as a C++ destructor, freeing all memory associated with a file
void inifile_done(struct inifile *obj) { inifile_clear(obj); return; }


// .ini file mainipulation
// debug information is printed as comments, so that the current file is not mangled,
// same with the printing function for .ini files below
void inisect_print(FILE *output, struct inisect *obj, bool verbose)
{
	FILE *out = (output == nullptr) ? stdout : output;

	fprintf(out, "[%s]\n%s\n\n", obj->section, obj->buffer);

	// Check if section is properly linked
	if(verbose)
	{
		fprintf(out, "; previous section listed as \"[%s]\"\n", obj->prev->section);
		fprintf(out, "; next section listed as \"[%s]\"\n\n", 	obj->next->section);
	}

	return;
}

void inifile_print(FILE *output, struct inifile *obj, bool verbose)
{
	FILE *out = (output == nullptr) ? stdout : output;

	// Printing file information
	if(verbose)
	{
		fprintf(out, "; inifile->name = \"%s\"\n",	   obj->name);
		fprintf(out, "; inifile->sectcount = %ld\n\n", obj->sectcount);
	}

	struct inisect *i;
	for(i = inifile_begin(obj); i != inifile_end(obj); i = inifile_next(i))
	{
		inisect_print(out, i, verbose);
	}

	return;
}
