#include <cstddef>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* print files in current directory in reverse order */
#include <dirent.h>
#include <iostream>

int myfilter(const struct dirent *entry)
{
    /* man 3 scandir says "entries for which filter()
     * returns nonzero are stored".
     *
     * Since file names in Linux are multibyte strings,
     * we use mbstowcs() to find out the length
     * of the filename in characters.
     *
     * Note: strlen() tells the filename length in bytes,
     *       not characters!
    */

    bool result = false;
    const size_t len = mbstowcs(NULL, entry->d_name, 0);

    std::string fn = entry->d_name;
    if (fn.substr(fn.find_last_of(".") + 1) == "dat")
    {
        std::cout << "Yes..." << fn << std::endl;
        result = true;
    }
    else
    {
        std::cout << "No..." << std::endl;
    }

    return result;
}

int main(void)
{
    struct dirent **namelist;
    int n;

    n = scandir(".", &namelist, myfilter, alphasort);
    if (n < 0)
        perror("scandir");
    else {
        while (n--) {
            printf("%s\n", namelist[n]->d_name);
            free(namelist[n]);
        }
        free(namelist);
    }

    return 0;
}
