#pragma once

void place_string_on_screen(char screen[80], int x, char text[80], int size)
{
	for (int i = 0; i < size; i++)
		screen[x + i] = text[i];
}