#include "DataBase.h"

void populateDB(Storage& storage)
{
	std::vector<Player> players = {
		Player{-1,"Coco20", "amuitato", 0},
		Player{-1,"raul807", "parolasmechera", 0},
		Player{-1,"ronaldoGOAT_CR7", "amuitato2", 0},
		Player{-1,"vlad", "parolacomplexa", 0},
	};
	storage.insert_range(players.begin(), players.end());

	std::vector<Word> words = {
		Word{-1,"casa de marcat"},
		Word{-1,"Ferrari"},
		Word{-1,"sternocleidomastiodian"},
		Word{-1,"Cristiano Ronaldo"},
		Word{-1,"fasole frecata"},
		Word{-1,"paine"},
		Word{-1,"insula"},
		Word{-1,"ceafa de porc"},
		Word{-1,"KFC"},
		Word{-1,"Formula 1"},
		Word{-1,"Varza"},
		Word{-1,"OK"},
		Word{-1,"branza stricata"},
		Word{-1,"lapte de bivol"},
		Word{-1,"carnat urias"},
		Word{-1,"desert"},
		Word{-1,"tort de ciocolata"},
		Word{-1,"masline negre"},
	};
	storage.insert_range(words.begin(), words.end());
}
