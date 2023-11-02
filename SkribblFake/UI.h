#pragma once
#include "PlayerService.h"
// #include "WordService.h"

class UI
{
private:
	PlayerService m_ps;
	// WordService m_ws;
public:
	// constructorul clasei UI imbina service-urile in constructor
	// dupa implementarea WordService ar veni:
	// UI(PlayerService ps, WordService ws);
	UI(PlayerService ps);

	// un meniu probabil..
	void show_menu();
	// se poate implementa o consola de model unde putem face diverse operatii (mai vedem)
	void run_console();
};

