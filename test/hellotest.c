#include <unistd.h>
#include <sys/syscall.h>

#define hello() remap_file_pages(0,0,0,0,0)

int main()
{
	hello();
	return 0;
}
