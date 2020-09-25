
#include "../../TaTeTi_Libs/TA-TE-TI/Juego.h"
int main() 
{
	HWND h;
	HMENU sm;
	int i, j, c;
	LPTSTR buf;
	// get the handle to the console
	h = GetConsoleWindow();
	// get handle to the System Menu
	sm = GetSystemMenu(h, 0);
	// how many items are there?
	c = GetMenuItemCount(sm);
	j = -1;
	buf = (TCHAR*)malloc(256 * sizeof(TCHAR));
	for (i = 0; i < c; i++) {
		// find the one we want
		GetMenuString(sm, i, buf, 255, MF_BYPOSITION);
		if (!strcmp(buf, "&Close")) {
			j = i;
			break;
		}
	}
	// if found, remove that menu item
	if (j >= 0)
		RemoveMenu(sm, j, MF_BYPOSITION);

	Juego* juego = new Juego(10, 5);
	juego->UpdateUsuario();
	juego->DestruirUsuario();
	if (juego != NULL)
	{
		delete juego;
	}
	cin.get();
	return 0;
}