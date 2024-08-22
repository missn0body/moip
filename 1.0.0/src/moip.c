#include <stdio.h>

#include "../lib/moip.h"

int main(void)
{
	struct inifile fileobj;
	struct inisect *i;

	inifile_init(&fileobj, "testfile");
	inifile_push_back(&fileobj, "section", "helloworld");
	inifile_push_back(&fileobj, "section", "helloworld");

	for(i = inifile_begin(&fileobj); i != inifile_end(&fileobj); i = inifile_next(i))
	{
		printf("[%s]\n%s\n\n", i->section, i->buffer);
	}

	inifile_done(&fileobj);
	exit(EXIT_SUCCESS);
}
