#include "Headers/detect_button.h"
#include <ncursesw/curses.h>
void detect_button()
{
    while (true)
    {
        int c;
        while (1)
        {
            system("/bin/stty cbreak"); 
            c = getchar();
            if (c == 'a')
                //TODO make flag
            system("/bin/stty -cbreak");
        }
    }
}