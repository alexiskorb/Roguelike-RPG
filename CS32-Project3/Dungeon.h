#ifndef DUNGEON_INCLUDED
#define DUNGEON_INCLUDED

#include "utilities.h"
#include <string>
#include <list>
#include <vector>
using namespace std;

class Player;
class Actor;
class Weapon;
class GameObject;
struct Exit;
struct Room;

class Dungeon
{
public:
	Dungeon(int goblinSmellDistance);
	//Constructor
	~Dungeon();
	//Destructor

	string playerTurn(char command);
	//The player will increase its health by one (up to its max hit points) 10% of the time. 
	//If the player is asleep, an empty string is returned and the player's sleep time is decremented.
	//The function has the Player take action according to the command given. If the command is:
	//		an arrow key, h, j, k, or l, the Player moves in the correct direction if it can or attacks a monster in that direction.
	//		g, the player picks up a GameObject at its position if there is one there.	
	//		w, the screen displays the inventory and allows the user to wield a different weapon
	//		r, the screen displays the inventory and allows the user to read a scroll
	//		i, the screen displays the inventory
	//		>, the Player descends a level if the Player is standing on a staircase
	//		q, m_gameOver is set to true
	//		c, the Player's strength is set to 9 and the max hit points and current hit points are set to 50
	//		something else, then nothing happens
	//The returned string explains the effects of the player's action.

	string monsterTurn();
	//The function tells all the monsters to make a move. 
	//This means that monsters will attack the player if they are adjacent to the player
	//and will move according to the rules for each monster.

	bool gameOver() { return m_gameOver; }		//Indicates whether the game is over
	bool quit() { return m_quit; }				//Indicates whether the game was quit using the 'q' command
	void display();								//Clears the screen and displays the Dungeon and everything in it
private:
	int m_level;				//Dungeon level
	char m_grid[18][70];		//Contains characters at different locations that represent the type of object at that location in the Dungeon
	bool m_gameOver;			//True if the game is over, false otherwise
	bool m_quit;				//True if the game was quit using the 'q' command, false otherwise
	int m_goblinSmellDistance;	//The smelling range of all Goblins in the Dungeon
	Player* m_player;			//The Player in the dungeon
	Exit* m_exit;				//The staircase or golden idol
	list<Actor*> m_monsters;	//All of the Actors in the Dungeon except for the Player
	list<GameObject*> m_scrolls;	//All of the scrolls in the Dungeon
	list<Weapon*> m_weapons;		//All of the weapons in the Dungeon

	string movePlayer(char direction);	
	//If direction is ARROW_UP, ARROW_DOWN, ARROW_RIGHT, or ARROW_LEFT,
	//then the Player is moved in the corresponding direction as long as its path is not blocked by a wall or monster.
	//If the Player was told to move into a monster, the player attacks the monster instead of moving.
	//If the direction is a different character, then the Player does nothing and an empty string is returned.
	//A string is returned, detailing the effects of the attack. It is empty if no attack took place.
	void clearRooms();
	//Removes all of the GameObject and Actor symbol from m_grid. The walls, Exit, and open spaces remain as they are.
	//The space where a GameObject or Actor symbol used to be is set to ' '. 
	void getEmptyLocation(int &row, int &col) const;
	//It assumes there is at least one empty location (indicated by a ' ') in m_grid.
	//After the call, "row" and "col" give the position of an empty location in m_grid. 
	void Dungeon::addRoom(vector<Room>& rooms);
	//Adds a non-overlapping Room to rooms. 
	//It also draws the Room onto m_grid (meaning it sets every point in the Room to ' ' in m_grid).
	//It draws a corridor from this new Room to the closest Room in rooms.
	void drawRoom(Room r1);
	//It sets every point in the Room (as defined by the Room's length, width, and location) to ' ' in m_grid.
	void generateLevel(int level);
	//A new level is generated at a depth of "level".
	//New rooms and corridors are drawn into m_grid.
	//The monsters, scrolls, staircases, and/or golden idols in the Dungeon from before are deleted.
	//New monsters, scrolls, staircases, and/or golden idols are placed in the Dungeon.
	//The Player is placed at a random location in the Dungeon.
};

struct Room
{
public: 
	int m_row;		//Row of the room's top left corner
	int m_col;		//Column of the room's top left corner
	int m_length;	//Vertical length of the room
	int m_width;	//Horizontal width of the room
};

#endif DUNGEON_INCLUDED