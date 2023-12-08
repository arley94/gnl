## 💡 About the project

> _The aim of this project is coding a function that returns one line at a time from a file descriptor, and we can only read up to BUFFER_SIZE bytes at a time from the file descriptor. BUFFER_SIZE is specified at compilation time._

	Doing this project help to understand how files are opened, read and closed in an OS, and how they are interpreted by a programming language for further analysis.

## 🛠️ Usage

```C
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"

int	main(void)
{
	int		fd;
	char	*line;
	
	fd = open("example.txt", O_RDONLY);
	if (fd == -1)
		printf("error opening file\n");
	while (line = get_next_line(fd))
	{
		printf("%s\n");
		free(line);
	}
	close(fd);
	return (0);
}
```