#pragma once

void place_string_on_screen(char screen[80], int x, char text[80], int size)
{
	bool writing_spaces = false;

	for (int i = 0; i < size; i++)
	{
		if (text[i] == '\0')
			writing_spaces = true;
		if (writing_spaces)
			screen[x + i] = ' ';
		else
			screen[x + i] = text[i];
	}
}