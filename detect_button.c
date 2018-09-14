#include "Headers/detect_button.h"

extern UserEquipment user_equipment;

void detect_button()
{
    while (true)
    {
        int c;
        while (true)
        {
            system("/bin/stty cbreak"); 
            c = getchar();
            if (c == 'a')
                user_equipment.is_requesting_download = true;
                
            system("/bin/stty -cbreak");
        }
    }
}