#include <iostream>
#include <fstream>

#include "mgtv_library.h"

#include "managers/game_manager/game_manager.h"
#include "managers/file_manager/file_manager.h"

using namespace std;
using namespace pong_in_console;
using namespace mgtv_library::console;


int main()
{
	GameManager::run("PONG");




	return 0;
}
