/* Deals with displaying things to screen in a formatted way
* Author: Luke Burton 140274882
* Date: 27/10/2017
*/
#pragma once
#include <Windows.h>
#include <iostream>
#include <string>

#include "Report.h"

using namespace std;

struct menuItem {
	string name;
	void* function;

};

class UserInterface
{
public:
	UserInterface();
	~UserInterface();


	/* Displays the given message in a bordered format */
	void display(string message); 

	/* Displays the main menu options */
	void mainMenu();

	inline void displayDivider() {
		cout << space << divider << space;
	}

	/*Display a cheeky spy*/
	inline void displaySpy() {
		cout << spy;
	}

	void displayReport(vector<Report<unsigned int>> report);



	/* Returns a string */
	string gatherString();

	/* Collects an integer entered by the user
	* Returns -1 if the user does not enter an integer
	*/
	int gatherInteger();
	

protected:
	string title =
		"***************************************************\n"
		"***************************************************\n"
		"|| ______     _                           _      ||\n"
		"|| | ___ \\   (_)                         ( )     ||\n"
		"|| | |_/ / __ _ ___  ___  _ __   ___ _ __|/ ___  ||\n"
		"|| |  __/ '__| / __|/ _ \\| '_ \\ / _ \\ '__| / __| ||\n"
		"|| | |  | |  | \\__ \\ (_) | | | |  __/ |    \\__ \\ ||\n"
		"|| \\_|  |_|  |_|___/\\___/|_| |_|\\___|_|    |___/ ||\n"
		"||                                               ||\n"
		"|| ______ _ _                                    ||\n"
		"|| |  _  (_) |                                   ||\n"
		"|| | | | |_| | ___ _ __ ___  _ __ ___   __ _     ||\n"
		"|| | | | | | |/ _ \\ '_ ` _ \\| '_ ` _ \\ / _` |    ||\n"
		"|| | |/ /| | |  __/ | | | | | | | | | | (_| |    ||\n"
		"|| |___/ |_|_|\\___|_| |_| |_|_| |_| |_|\\__,_|    ||\n"
		"||                                               ||\n";

	string space = "||                                               ||\n";
	string divider =
		"***************************************************\n"
		"***************************************************\n";

	string spy = 
		"                    .lxl;'.\n"
		"                    cNMWNKc\n"
		"                    .cdo:,."
		"                      ..';:clcc::;,'....\n"
		"                   .:dOKNWMMMMWNK0Okxdoc:,.\n"
		"                .cxKWMWXKOxxkkkkd;.;ooc;,...'..\n"
		"             .cx0KOkOOxoc. .dOOOx; ...    .okxxd;\n"
		"           .:dkxc'';kNK0k'  ....   .   ...  ....\n"
		"          .,ccc::xK0xdc''.   ''   .c.\n"
		"              .oXMMMXo,,co,  .,:;\n"
		"            .c0WMMMMMWOc:OXd::kNNk;\n"
		"          .:OWMMMMMMMMWO;cXMWWMMMMk.\n"
		"         'kNMMMWNNWMMMMN: ;0WMMMMMO.\n"
		"       .cKMMMW0oo0NMMMMX:  'xNMMMMK,\n"
		"      'xNMMWXkdx0XWMMMMX:   .lXMMMX;\n"
		"    .cKMMMNkx0WMMMMMMMMX:     ;OWMN:\n"
		"   'xNMMWOldNMMMMMMMMMMX:      .dNWl\n"
		" .lKWNXKl.cXMMMMMMMMMMMNc       .c0o.\n"
		".dNMNOl' 'OMMMMMMMMMMMMWl         ',\n"
		",KMMWNK:.oWMMMMMMMMMMMMWd.\n"
		".kMMMMWd:0MMMMMMMMMMMMMMk.\n"
		" lNMMMK:oNMMMMMMMMMMMMMM0'\n"
		" .OMXk;'kMMMMMMMMMMMMMMMX;\n"
		"  ,loo;cXMMMMMMMMMMMMMMMWo\n"
		"    .:,dWMMMMMMMMMMMMMMMMO.\n"
		"    .ll0MMMMMMMMMMMMMMMMMXc\n"
		"    'coXMMMMMMMMMMMMMMMMMWx.\n"
		".,..;:oNMMMMMMMMMMMMMMMMMMK;\n"
		".;ccc,dWMMMMMMMMMMMMMMMMMMWd.\n"
		"      :0NWMMMMMMMMMMMMMMMMM0'\n"
		"       ..;cdxxxkO00KKKKK00Od.\n"
		"           'cdxddxxxxxxxdo,\n"
		"  ..       .:ddk0NMMMMMMMM0,\n"
		"  'ol'.    ,0NKkxdxkKWMMMMWd.\n"
		"  'OWXOxdoxKWMMMMN0d;;d0WMMK;        .\n"
		" .xWKc,cxKNWWWWWN0d,   .;xNWk.     .cc.\n"
		" .OMO.   .';;;;;'.        ;ON0olookOo.\n"
		"  :KK;                     .kKxxxxl'\n"
		"   'od,                     .;.\n"
		"     ..\n";

	static const int optionNum = 5;
	string options[optionNum] = { "0. Exit", " 1. Manually Enter Strategy", "2. Generate Strategies", "3. Execute Tournament", "4. Execute Gang Tournament"};

	SMALL_RECT windowSize;
	HANDLE currentConsole;
};

