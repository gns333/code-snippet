#include <stdio.h>

#define ERR_CODE(XX)     \
        XX(ENOMEM, "no memory") \
        XX(EFILE, "file not found")     \
        XX(EBLOCK, "block")

#define XX(type, msg)   type,
enum {
	ERR_CODE(XX)
};
#undef XX

#define XX(type, msg)   #type,
const char * typeMap[] = {
	ERR_CODE(XX)
};
#undef XX

#define XX(type, msg)   msg,
const char * msgMap[] = {
	ERR_CODE(XX)
};
#undef XX

int main(int argc, const char *argv[])
{
	int i;
	for (i = 0; i < sizeof(msgMap) / sizeof(msgMap[0]); i++) {
		printf("%s, %s\n", typeMap[i], msgMap[i]);
	}
	printf("%s\n", msgMap[ENOMEM]);
	return 0;
}
