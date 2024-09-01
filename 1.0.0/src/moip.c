#include "../lib/moip.h"

// TODO divise some sort of key-value pair structure that can be expandable
// TODO implement functions to search a file for specific keys to check their values
// TODO have inifile create look-up tables for easy indexing of keys and values

int main(void)
{
	struct inifile fileobj;

	inifile_init(&fileobj, "testfile");
	inifile_push_back(&fileobj, "section", "helloworld");
	inifile_push_back(&fileobj, "section", "helloworld");

	inifile_print(nullptr, &fileobj, true);

	inifile_done(&fileobj);
	exit(EXIT_SUCCESS);
}
