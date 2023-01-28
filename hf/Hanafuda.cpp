#include "game.h"
#include "model.h"
#include "view.h"


int main()
{
	View view{};
	Model model{};	
	Game game{ view, model };

	game.Begin();
}