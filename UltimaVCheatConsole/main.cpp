/*
	Ultima 5 Cheat Console
	Set stats for all characters,
	and amounts of useful items/equipment
*/

#include <iostream> // cout, cin
#include <string> // string
#include <fstream> // file in/out

// Using namepspace is bad practice,
//		but this is not commercial software
using namespace std;

// Function prototypes
size_t menu(); // Prints menu and gets selected operation
void getStats(int, bool, string&); // Asks for what stats the user wants
void writeStats(string&, int, int, int, int, int, int, int); // Does the write to the .GAM file
void getInventory(string&); // Asks for what items the player wants

int main()
{
	string filepath; // Variable for the filepath, form of (C:\\OLDGAMES\\Ultima_5)
	cout << "Welcome to my Ultima V hack!\n"
		<< "Two thingstttttt:\n"
		<< "	1. You must have an already existing character.\n"
		<< "		Please create a character by talking with the gypsy first.\n"
		<< "	2. Raising str, int, and dex above 30 could cause problems.\n"
		<< "		This is because the game was not meant to raise them above 30.\n"
		<< "		Going higher than that might cause you to actually perform worse!\n\n"
		<< "Enter the filepath of the folder where \"ULTIMA.EXE\" is located: ";
	getline(cin, filepath); // Get filepath input
	filepath += "\\SAVED.GAM"; // Add the name of the .GAM file

	while (true) // Infinite loop because menu will decide when to exit
	{
		size_t choice = menu(); // Get menu choice
		switch (choice)
		{
			// Change stats for chosen character
			// getStats( <starting offset for that character, <not all character flag>, <pass filepath>)

		case 1: // Player Character
			getStats(14, false, filepath);
			break;
		case 2: // Shamino
			getStats(46, false, filepath);
			break;
		case 3: // Iolo
			getStats(78, false, filepath);
			break;
		case 4: // Mariah
			getStats(110, false, filepath);
			break;
		case 5: // Geoffrey
			getStats(142, false, filepath);
			break;
		case 6: // Jaana
			getStats(174, false, filepath);
			break;
		case 7: // Julia
			getStats(206, false, filepath);
			break;
		case 8: // Dupre
			getStats(238, false, filepath);
			break;
		case 9: // Katrina
			getStats(270, false, filepath);
			break;
		case 10: // Sentri
			getStats(302, false, filepath);
			break;
		case 11: // Gwenno
			getStats(334, false, filepath);
			break;
		case 12: // Johne
			getStats(366, false, filepath);
			break;
		case 13: // Gorn
			getStats(398, false, filepath);
			break;
		case 14: // Maxwell
			getStats(430, false, filepath);
			break;
		case 15: // Toshi
			getStats(462, false, filepath);
			break;
		case 16: // Saduj
			getStats(494, false, filepath);
			break;
		case 17:// Get stats and apply to all characters
			getStats(14, true, filepath);
			break;
		case 18:
			// Get requested inventory
			getInventory(filepath);
			break;
		case 19:
			// Exit
			exit(0);
		default:
			// Error, should never get here
			cout << "ERROR SWITCH STATEMENT!\n";
		}
	}
}

size_t menu() // Gets menu choice
{
	size_t choice;
	cout << "*****************************************\n"
		<< "Edit stats for:\n"
		<< "    1. Player Character\n"
		<< "    2. Shamino\n"
		<< "    3. Iolo\n"
		<< "    4. Mariah\n"
		<< "    5. Geoffrey\n"
		<< "    6. Jaana\n"
		<< "    7. Julia\n"
		<< "    8. Dupre\n"
		<< "    9. Katrina\n"
		<< "   10. Sentri\n"
		<< "   11. Gwenno\n"
		<< "   12. Johne\n"
		<< "   13. Gorn\n"
		<< "   14. Maxwell\n"
		<< "   15. Toshi\n"
		<< "   16. Saduj\n"
		<< "   17. <EVERYONE>\n"
		<< "18. Edit the player character inventory\n"
		<< "19. Exit\n"
		<< "*****************************************\n"
		<< "Enter choice:  ";
	cin >> choice;
	cout << "------------------\n";
	return choice;
}

// Asks for the wanted stats, then passes them to the write function
void getStats(int offset, bool allCharacters, string& filepath)
{
	int str = 0, inte = 0, dex = 0; // str, int, dex stats
	int hp = 0, hm = 0; // current health and max health
	int exp = 0; // experience points
	while (str < 1 || str > 99) // Get str
	{
		cout << "Enter str (1 - 99): ";
		cin >> str;
	}
	while (inte < 1 || inte > 99) // Get int
	{
		cout << "Enter inte (1 - 99): ";
		cin >> inte;
	}
	while (dex < 1 || dex > 99) // Get dex
	{
		cout << "Enter dex (1 - 99): ";
		cin >> dex;
	}
	while (hp < 1 || hp > 999) // Get current health
	{
		cout << "Enter current health (1 - 999): ";
		cin >> hp;
	}
	while (hm < 1 || hm > 999) // Get max health
	{
		cout << "Enter max health (1-999): ";
		cin >> hm;
	}
	while (exp < 1 || exp > 9999) // Get experience points
	{
		cout << "Enter experience points (1-9999): ";
		cin >> exp;
	}

	if (!allCharacters) // Write to character, offset variable knows where to go
	{
		writeStats(filepath, offset, str, inte, dex, hp, hm, exp);
	}
	else // Write to ALL characters
	{
		for (int i = 0; i < 16; i++)
		{
			offset = 14 + (i * 32); // Go to next character
			writeStats(filepath, offset, str, inte, dex, hp, hm, exp); // Write that character
		}
	}
}

// Uses offset variable to find the right character, and then write the stats
void writeStats(string& filepath, int offset, int str, int inte, int dex, int hp, int hm, int exp)
{
	fstream f;
	f.open(filepath, ios::binary | ios::in | ios::out);

	f.seekg(offset); // str
	f.write((char*)&str, sizeof(char));

	f.seekg(offset + 1); // dex
	f.write((char*)&dex, sizeof(char));

	f.seekg(offset + 2); // int
	f.write((char*)&inte, sizeof(char));

	f.seekg(offset + 4); // current health
	f.write((char*)&hp, sizeof(unsigned short int));

	f.seekg(offset + 6); // max health
	f.write((char*)&hm, sizeof(unsigned short int));

	f.seekg(offset + 8); // experience
	f.write((char*)&exp, sizeof(unsigned short int));

	f.close();
}

// Ask for number of inventory and equipment items and write them to the inventory
void getInventory(string& filepath)
{
	//  gold, keys, skullkeys, gems, black badge, magic carpets, magix axes
	int gold, keys, skullkeys, gems, blkBadge, magicCrpt, mAxe;
	do
	{	// gold
		cout << "Enter gold (0 - 9999): ";
		cin >> gold;
	} while (gold < 0 || gold > 9999);
	do
	{	// keys
		cout << "Enter keys (0 - 100): ";
		cin >> keys;
	} while (keys < 0 || keys > 100);
	do
	{	// skull keys
		cout << "Enter skull keys (0 - 100): ";
		cin >> skullkeys;
	} while (skullkeys < 0 || skullkeys > 100);
	do
	{	// gems
		cout << "Enter gems (0 - 100): ";
		cin >> gems;
	} while (gems < 0 || gems > 100);
	do
	{	// black badge
		cout << "Enter Black Badge (0 or 1): ";
		cin >> blkBadge;
	} while (blkBadge < 0 || blkBadge > 1);
	do
	{	// magic carpets
		cout << "Enter magic carpets (0 - 2): ";
		cin >> magicCrpt;
	} while (magicCrpt < 0 || magicCrpt > 2);
	do
	{	// magic axes (16 such that each character can have one)
		cout << "Enter magic axes (0 - 16): ";
		cin >> mAxe;
	} while (mAxe < 0 || mAxe > 16);


	fstream f;
	f.open(filepath, ios::binary | ios::in | ios::out);

	f.seekg(516); // gold
	f.write((char*)&gold, sizeof(unsigned short int));

	f.seekg(518); // keys
	f.write((char*)&keys, sizeof(char));

	f.seekg(519); // gems
	f.write((char*)&gems, sizeof(char));

	f.seekg(522); // magic carpets
	f.write((char*)&magicCrpt, sizeof(char));

	f.seekg(523); // skull keys
	f.write((char*)&skullkeys, sizeof(char));

	f.seekg(536); // black badge
	f.write((char*)&blkBadge, sizeof(char));

	f.seekg(576); // magic axes
	f.write((char*)&mAxe, sizeof(char));

	f.close();
}