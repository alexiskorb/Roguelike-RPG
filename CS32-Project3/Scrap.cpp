/*
/*
bool Goblin::search(char grid[][70], list<Actor*> monsters, Actor* player, int row, int col, int smellDist, int& dir, int steps)
{

	if (smellDist <= 0)
	{
		return false;
	}
	if (player->getRow() == row && player->getCol() == col)
	{
		return true;
	}
	if (grid[row][col] == '#'|| grid[row][col] == 'V')
	{
		return false;
	}
	else
	{
		grid[row][col] = 'V';
	}
	for (list<Actor*>::iterator p = monsters.begin(); p != monsters.end(); p++)
	{
		if ((*p)->getRow() == row && (*p)->getCol() == col)
		{
			return false;
		}
	}
	if (smellDist == m_smellDistance)
	{
		int stepsUp = 0;
		int stepsDown = 0;
		int stepsRight = 0;
		int stepsLeft = 0;
		if (!search(grid, monsters, player, row - 1, col, smellDist - 1, dir, stepsUp)){
			stepsUp = 100;
		}
		if (!search(grid, monsters, player, row + 1, col, smellDist - 1, dir, stepsDown)){
			stepsDown = 100;
		}
		if (!search(grid, monsters, player, row, col + 1, smellDist - 1, dir, stepsRight)){
			stepsRight = 100;
		}
		if (!search(grid, monsters, player, row, col - 1, smellDist - 1, dir, stepsLeft)){
			stepsLeft = 100;
		}
		if (stepsUp == 100 && stepsDown == 100 && stepsRight == 100 && stepsLeft == 100)
		{
			return false;
		}
		else
		{
			if (stepsUp < stepsDown){
				if (stepsRight < stepsLeft)				{
					if (stepsUp < stepsRight){
						dir = 0;
					}
					else{
						dir = 2;
					}
				}
				else{
					if (stepsUp < stepsLeft){
						dir = 0;
					}
					else{
						dir = 3;
					}
				}
			}
			else{
				if (stepsRight < stepsLeft){
					if (stepsDown < stepsRight){
						dir = 1;
					}
					else{
						dir = 2;
					}
				}
				else{
					if (stepsDown < stepsLeft){
						dir = 1;
					}
					else{
						dir = 3;
					}
				}
			}
			return true;
		}
	}
	else
	{
		steps++;
		return (search(grid, monsters, player, row - 1, col, smellDist - 1, dir, steps) || search(grid, monsters, player, row + 1, col, smellDist - 1, dir, steps)
			|| search(grid, monsters, player, row, col + 1, smellDist - 1, dir, steps) || search(grid, monsters, player, row, col - 1, smellDist - 1, dir, steps));
	}
}

int Goblin::search(char modGrid[][70], Actor* player, int row, int col, int smellDist, int dir, int& steps)
{
	switch (dir)
	{
	case 0:
		row = row - 1;
		break;
	case 1:
		row = row + 1;
		break;
	case 2:
		col = col + 1;
		break;
	case 3:
		col = col - 1;
		break;
	}
	if (modGrid[row][col] == '#')
	{
		return -1;
	}
	if (smellDist <= 0)
	{
		return -1;
	}
	if (player->getRow() == row && player->getCol() == col)
	{
		return dir;
	}
	if (search);

switch (direction)
	{
	case ARROW_UP:
		for (list<Actor*>::iterator p = m_monsters.begin(); p != m_monsters.end(); p++)
		{
			if (row == (*p)->getRow() && col == (*p)->getCol()){
				string msg = m_player->attack(*p);
				string name = (*p)->getName();
				if (msg == "dealing a final blow.\n")
				{
					m_monsters.erase(p);
				}
				msg = "Player " + m_player->getWeapon()->action() + " " + name + " " + msg;
				return msg;
			}
		}
		if (m_grid[row][col] != '#'){
			m_player->setRow(row);
		}
		break;
	case ARROW_DOWN:
		for (list<Actor*>::iterator p = m_monsters.begin(); p != m_monsters.end(); p++)
		{
			if ((row + 1) == (*p)->getRow() && col == (*p)->getCol()){
				string msg = m_player->attack(*p);
				string name = (*p)->getName();
				if (msg == "dealing a final blow.\n")
				{
					m_monsters.erase(p);
				}
				msg = "Player " + m_player->getWeapon()->action() + " " + name + " " + msg;
				return msg;
			}
		}
		if (m_grid[row + 1][col] != '#'){
			m_player->setRow(row + 1);
		}
		break;
	case ARROW_RIGHT:
		for (list<Actor*>::iterator p = m_monsters.begin(); p != m_monsters.end(); p++)
		{
			if (row == (*p)->getRow() && (col + 1) == (*p)->getCol()){
				string msg = m_player->attack(*p);
				string name = (*p)->getName();
				if (msg == "dealing a final blow.\n")
				{
					m_monsters.erase(p);
				}
				msg = "Player " + m_player->getWeapon()->action() + " " + name + " " + msg;
				return msg;
			}
		}
		if (m_grid[row][col + 1] != '#'){
			m_player->setCol(col + 1);
		}
		break;
	case ARROW_LEFT:
		for (list<Actor*>::iterator p = m_monsters.begin(); p != m_monsters.end(); p++)
		{
			if (row == (*p)->getRow() && (col - 1) == (*p)->getCol()){
				string msg = m_player->attack(*p);
				string name = (*p)->getName();
				if (msg == "dealing a final blow.\n")
				{
					m_monsters.erase(p);
				}
				msg = "Player " + m_player->getWeapon()->action() + " " + name + " " + msg;
				return msg; if (msg == "dealing a final blow.\n")
				{
					m_monsters.erase(p);
				}
				msg = "Player " + m_player->getWeapon()->action() + " " + (*p)->getName() + " " + msg;
				return msg;
			}
		}
		if (m_grid[row][col - 1] != '#'){
			m_player->setCol(col - 1);
		}
		break;
	}
	return "";

string Snakewoman::move(const char grid[][70], list<Actor*> monsters, Actor* player)
{
	string msg = Actor::move(grid, monsters, player);
	if (msg == "")
	{
		int rowDist = player->getRow() - getRow();
		int colDist = player->getCol() - getCol();
		if (abs(rowDist) + abs(colDist) <= 3)
		{
			bool canMoveRow = true;
			bool canMoveCol = true;
			int tempRow = getRow();
			int tempCol = getCol();
			if (abs(rowDist) > 0){
				tempRow += rowDist / abs(rowDist);
			}
			else{
				canMoveRow = false;
			}
			if (abs(colDist) > 0){
				tempCol += colDist / abs(colDist);
			}
			else{
				canMoveCol = false;
			}
			if (grid[tempRow][getCol()] == '#'){
				canMoveRow = false;
			}
			if (grid[getRow()][tempCol] == '#')
			{
				canMoveCol = false;
			}
			for (list<Actor*>::iterator p = monsters.begin(); p != monsters.end(); p++)
			{
				if ((*p)->getRow() == tempRow && (*p)->getCol() == getCol())
				{
					canMoveRow = false;
				}
				if ((*p)->getRow() == getRow() && (*p)->getCol() == tempCol)
				{
					canMoveCol = false;
				}
			}
			if (canMoveCol){
				setCol(tempCol);
			}
			else if (canMoveRow){
				setRow(tempRow);
			}
		}
	}
	return msg;
}


string Dungeon::monsterTurn()
{
	clearRooms();
	for (list<Actor*>::iterator p = m_monsters.begin(); p != m_monsters.end(); p++)
	{
		m_grid[(*p)->getRow][(*p)->getCol] = (*p)->getSymbol;
	}
	string msg = "";
	int count = 0;
	for (list<Actor*>::iterator p = m_monsters.begin(); p != m_monsters.end(); p++, count++)
	{
		Actor* currentMonster = *p;
		list<Actor*> otherMonsters = m_monsters;
		list<Actor*>::iterator q = otherMonsters.begin();
		for (int i = 0; i < count; i++)
		{
			q++;
		}
		otherMonsters.erase(q);
		msg += currentMonster->move(m_grid, otherMonsters, m_player);
	}
	if (m_player->getHitPts() <= 0){
		m_gameOver = true;
	}
	return msg;
}


Room Dungeon::generateRoom(int row, int col)
{
	Room r1;
	//Set the room's m_row to "row" or to the closest valid integer
	if (row < 1){
		r1.m_row = 1;
	}
	else if (row > 16){
		r1.m_row = 16;
	}
	else{
		r1.m_row = row;
	}
	//Set the room's m_col to "col" or to the closest valid integer
	if (col < 1){
		r1.m_col = 1;
	}
	else if (col > 68){
		r1.m_col = 68;
	}
	else{
		r1.m_col = col;
	}
	//Set the length between 4-6 and the width between 6-14
	r1.m_length = randInt(2) + 4;
	r1.m_width = randInt(8) + 6;
	//Adjust the length and width if the room is near the edge of the grid and would be out of bounds
	if (r1.m_row + r1.m_length >= 17){
		r1.m_length = 17 - r1.m_row;
	}
	if (r1.m_col + r1.m_width >= 69){
		r1.m_width = 69 - r1.m_col;
	}
	return r1;
}

Room Dungeon::addRoom(Room rPrev, int lastDir, int &nextDir)
{
	Room rNext;				//The room to be added
	int direction = randInt(4);
	if (trueWithProbability(0.2)){
		direction = 1;
	}
	while (lastDir + direction == 3 || (rPrev.m_row < 6 && direction == 0) || (rPrev.m_row + rPrev.m_length > 13 && direction == 3)
		|| (rPrev.m_col < 10 && direction == 2) || (rPrev.m_col + rPrev.m_width > 60 && direction == 1))
	{
		direction = randInt(4);
	}

	if (rPrev.m_row == 1){
		direction = 3;
	}
	if (rPrev.m_row == 16){
		direction = 0;
	}
	if (rPrev.m_col == 1){
		direction = 1;
	}
	if (rPrev.m_col == 69){
		direction = 2;
	}

	nextDir = direction;
	//Adding the room to the right/left

	//Adding the room to the right
	if (direction == 1){
		//Get a random point on the correct edge of the previous room 
		int startRow = rPrev.m_row + randInt(rPrev.m_length);
		int startCol = rPrev.m_col + rPrev.m_width;
		//Add in a corridor of length 4-8
		int i = 0, j = 0;
		for (i = 0; i < 1 && (startRow + i < 17); i++){
			for (j = 0; j < randInt(6) + 4 && (startCol + j < 69); j++){
				m_grid[startRow + i][startCol + j] = ' ';
			}
		}
		//Create a room at the end point of the corridor
		rNext = generateRoom(startRow + i - 1, startCol + j - 1);
		int rand = randInt(rNext.m_length);
		//Adjust the room so that the corridor attaches to a random point on its edge
		if (rNext.m_row - rand > 0){
			rNext.m_row -= rand;
		}
		else{
			rNext.m_row = 1;
		}
	}
	//Adding the room to the left
	else if (direction == 2)
	{
		//Get a random point on the correct edge of the previous room 
		int startRow = rPrev.m_row + randInt(rPrev.m_length);
		int startCol = rPrev.m_col;
		//Add in a corridor of length 4-8
		int i = 0, j = 0;
		for (i = 0; i < 1 && (startRow + i < 17); i++){
			for (j = 0; j < randInt(6) + 4 && (startCol - j > 0); j++){
				m_grid[startRow + i][startCol - j] = ' ';
			}
		}
		//Create a room at the end point of the corridor
		rNext = generateRoom(startRow + i - 1, startCol - j + 1);
		//Adjust the room so that the corridor attaches to a random point on its edge
		int rand = randInt(rNext.m_length);
		if (rNext.m_row - rand > 0){
			rNext.m_row -= rand;
		}
		else{
			rNext.m_row = 1;
		}
		//Adjust the room so that the corridor is attached to the correct edge
		if (rNext.m_col - rNext.m_width > 0){
			rNext.m_col -= rNext.m_width;
		}
		else{
			rNext.m_col = 1;
			rNext.m_width = 1 > (startCol - j + 1) ? 1 : (startCol - j + 1);
		}
	}
	//Adding the room above/below 
	//Adding the room above the current room
	else if (direction == 0){
		//Get a random point on the correct edge of the previous room 
		int startRow = rPrev.m_row;
		int startCol = rPrev.m_col + randInt(rPrev.m_width);
		//Add in a corridor of length 3-7
		int i = 0, j = 0;
		for (i = 0; i < randInt(4) + 3 && (startRow - i > 0); i++){
			for (j = 0; j < 1 && (startCol + j < 69); j++){
				m_grid[startRow - i][startCol + j] = ' ';
			}
		}
		//Create a room at the end point of the corridor
		rNext = generateRoom(startRow - i + 1, startCol + j - 1);
		//Adjust the room so that the corridor attaches to the correct edge
		if (rNext.m_row - rNext.m_length > 0){
			rNext.m_row -= rNext.m_length;
		}
		else{
			rNext.m_row = 1;
			rNext.m_length = 1 > (startRow - i + 1) ? 1 : (startRow - i + 1);
		}
		//Adjust the room so that the corridor attaches to a random point on its edge
		int rand = randInt(rNext.m_width);
		if (rNext.m_col - rand > 0){
			rNext.m_col -= rand;
		}
		else{
			rNext.m_col = 1;
		}
	}
	//Adding a room below the current room
	else{
		//Get a random point on the correct edge of the previous room 
		int startRow = rPrev.m_row + rPrev.m_length;
		int startCol = rPrev.m_col + randInt(rPrev.m_width);
		//Add in a corridor of length 3-7
		int i = 0, j = 0;
		for (i = 0; i < randInt(4) + 3 && (startRow + i < 17); i++){
			for (j = 0; j < 1 && (startCol + j < 69); j++){
				m_grid[startRow + i][startCol + j] = ' ';
			}
		}
		//Create a room at the end point of the corridor
		rNext = generateRoom(startRow + i - 1, startCol + j - 1);
		//Adjust the room so that the corridor attaches to a random point on its edge
		int rand = randInt(rNext.m_width);
		if (rNext.m_col - rand > 0){
			rNext.m_col -= rand;
		}
		else{
			rNext.m_col = 1;
		}
	}

	//Draw the room and return it
	drawRoom(rNext);
	return rNext;
}
void Dungeon::generateLevel(int level)
{
	//Clear out old monsters and items
	m_monsters.clear();
	m_scrolls.clear();
	m_weapons.clear();
	//Reset the grid to all '#'
	for (int i = 0; i < 18; i++){
		for (int j = 0; j < 70; j++){
			m_grid[i][j] = '#';
		}
	}
	//Number of rooms in the level
	int numRooms = randInt(2) + 5;
	//Create and draw a starting room on the left side of the map
	int row = randInt(10) + 1;
	int col = randInt(20) + 1;
	Room r1 = generateRoom(row, col);
	drawRoom(r1);
	int lastDir = 2;
	//Add in the rest of the rooms
	for (int i = 1; i < numRooms; i++)
	{
		r1 = addRoom(r1, lastDir, lastDir);
	}
	//Place the staircase or idol	
	getEmptyLocation(row, col);
	m_exit->m_row = row;
	m_exit->m_col = col;
	if (level != 4){
		m_exit->m_symbol = '>';
	}
	else{
		m_exit->m_symbol = '&';
	}
	//Place the player
	getEmptyLocation(row, col);
	m_player->setRow(row);
	m_player->setCol(col);
	//Place the monsters
	int numMonsters = 2 + randInt(5 * (m_level + 1));
	for (int i = 0; i < numMonsters; i++)
	{
		int row, col;
		getEmptyLocation(row, col);
		int rand;
		if (m_level < 2){
			rand = randInt(2);
		}
		else if (m_level < 3){
			rand = randInt(3);
		}
		else{
			rand = randInt(4);
		}
		switch (rand)
		{
		case 0:
			m_monsters.push_back(new Snakewoman(row, col));
			break;
		case 1:
			m_monsters.push_back(new Goblin(row, col, m_goblinSmellDistance));
			break;
		case 2:
			m_monsters.push_back(new Bogeyman(row, col));
			break;
		case 3:
			m_monsters.push_back(new Dragon(row, col));
			break;
		}
	}
	//Place the items
	for (int i = 0; i < randInt(2) + 2; i++)
	{
		int row, col;
		getEmptyLocation(row, col);
		int rand = randInt(7);
		switch (rand)
		{
		case 0:
			m_weapons.push_back(new Mace(row, col));
			break;
		case 1:
			m_weapons.push_back(new ShortSword(row, col));
			break;
		case 2:
			m_weapons.push_back(new LongSword(row, col));
			break;
		case 3:
			m_scrolls.push_back(new ArmorScroll(row, col));
			break;
		case 4:
			m_scrolls.push_back(new StrScroll(row, col));
			break;
		case 5:
			m_scrolls.push_back(new HealthScroll(row, col));
			break;
		case 6:
			m_scrolls.push_back(new DexScroll(row, col));
			break;
		}
	}
}


Room Dungeon::addRoom(Room rPrev)
{
	Room rNext;				//The room to be added
	bool moveUp = false;
	bool moveRight = false;
	//IF a room is on the lower half of the map, add a room above it instead of below it
	if (rPrev.m_row + rPrev.m_length / 2 > 9){
		moveUp = true;
	}
	//If a room is on the left half of the map, add a room to the right of it instead of to the left
	if (rPrev.m_col + rPrev.m_width / 2 < 35){
		moveRight = true;
	}

	//Determines whether we add a room to the right/left or above/below
	int rand = randInt(2);
	//Forces a room to be added to the right/left or above/below if the room is near the edge of the map
	if (rPrev.m_row < 3 || rPrev.m_row > 14){
		rand = 1;
	}
	if (rPrev.m_col < 15 || rPrev.m_col > 45){
		rand = 0;
	}
	//Adding the room to the right/left
	if (rand == 0){
		//Adding the room to the right
		if (moveRight){
			//Get a random point on the correct edge of the previous room 
			int startRow = rPrev.m_row + randInt(rPrev.m_length);
			int startCol = rPrev.m_col + rPrev.m_width;
			//Add in a corridor of length 4-8
			int i, j;
			for (i = 0; i < 1 && (startRow + i < 17); i++){
				for (j = 0; j < randInt(6) + 4 && (startCol + j < 69); j++){
					m_grid[startRow + i][startCol + j] = ' ';
				}
			}
			//Create a room at the end point of the corridor
			rNext = generateRoom(startRow + i - 1, startCol + j - 1);
			int rand = randInt(rNext.m_length);
			//Adjust the room so that the corridor attaches to a random point on its edge
			if (rNext.m_row - rand > 0){
				rNext.m_row -= rand;
			}
			else{
				rNext.m_row = 1;
			}
		}
		//Adding the room to the left
		else{
			//Get a random point on the correct edge of the previous room 
			int startRow = rPrev.m_row + randInt(rPrev.m_length);
			int startCol = rPrev.m_col;
			//Add in a corridor of length 4-8
			int i, j;
			for (i = 0; i < 1 && (startRow + i < 17); i++){
				for (j = 0; j < randInt(6) + 4 && (startCol - j > 0); j++){
					m_grid[startRow + i][startCol - j] = ' ';
				}
			}
			//Create a room at the end point of the corridor
			rNext = generateRoom(startRow + i - 1, startCol + 1 - j);
			//Adjust the room so that the corridor attaches to a random point on its edge
			int rand = randInt(rNext.m_length);
			if (rNext.m_row - rand > 0){
				rNext.m_row -= rand;
			}
			else{
				rNext.m_row = 1;
			}
			//Adjust the room so that the corridor is attached to the correct edge
			if (rNext.m_col - rNext.m_length > 0){
				rNext.m_col -= rNext.m_length;
			}
			else{
				rNext.m_col = 1;
			}
		}
	}
	//Adding the room above/below 
	else{
		//Adding the room above the current room
		if (moveUp){
			//Get a random point on the correct edge of the previous room 
			int startRow = rPrev.m_row;
			int startCol = rPrev.m_col + randInt(rPrev.m_width);
			//Add in a corridor of length 3-7
			int i, j;
			for (i = 0; i < randInt(4) + 3 && (startRow - i > 0); i++){
				for (j = 0; j < 1 && (startCol + j < 69); j++){
					m_grid[startRow - i][startCol + j] = ' ';
				}
			}
			//Create a room at the end point of the corridor
			rNext = generateRoom(startRow - i + 1, startCol + j - 1);
			//Adjust the room so that the corridor attaches to a random point on its edge
			if (rNext.m_row - rNext.m_length > 0){
				rNext.m_row -= rNext.m_length;
			}
			else{
				rNext.m_row = 1;
			}
			//Adjust the room so that the corridor attaches to a random point on its edge
			int rand = randInt(rNext.m_width);
			if (rNext.m_col - rand > 0){
				rNext.m_col -= rand;
			}
			else{
				rNext.m_col = 1;
			}
		}
		//Adding a room below the current room
		else{
			//Get a random point on the correct edge of the previous room 
			int startRow = rPrev.m_row + rPrev.m_length;
			int startCol = rPrev.m_col + randInt(rPrev.m_width);
			//Add in a corridor of length 3-7
			int i, j;
			for (i = 0; i < randInt(4) + 3 && (startRow + i < 17); i++){
				for (j = 0; j < 1 && (startCol + j < 69); j++){
					m_grid[startRow + i][startCol + j] = ' ';
				}
			}
			//Create a room at the end point of the corridor
			rNext = generateRoom(startRow + i - 1, startCol + j - 1);
			//Adjust the room so that the corridor attaches to a random point on its edge
			int rand = randInt(rNext.m_width);
			if (rNext.m_col - rand > 0){
				rNext.m_col -= rand;
			}
			else{
				rNext.m_col = 1;
			}
		}
	}
	//Draw the room and return it
	drawRoom(rNext);
	return rNext;
}





/*Room Dungeon::generateRoom(int row, int col)
{
	Room r1; 
	r1.m_length = randInt(4) + 4;
	r1.m_width = randInt(8) + (11 - r1.m_length/2);
	r1.m_row = randInt(16 - r1.m_length) + 1;
	switch (rowMod)
	{
	case 0:
		r1.m_row = randInt(6) + 1;
		break;
	case 1:
		r1.m_row = randInt(10 - r1.m_length) + 7;
		break;
	}
	switch (colMod)
	{
	case 0:
		r1.m_col = randInt(5) + 1; //1 - 6
		break;
	case 1:
		r1.m_col = randInt(5) + 16; // 6 - 17
		break;
	case 2:
		r1.m_col = randInt(5) + 33; //25 - 52
		break;
	case 3:
		r1.m_col = randInt(5) + (62 - r1.m_width);  //33 - 55
		break;
	case 4: 
		r1.m_col = randInt(8) + 8;
		break;
	case 5:
		r1.m_col = randInt(8) + 20;
		break;
	case 6:
		r1.m_col = randInt(8) + 36;
		break;
	case 7:
		r1.m_col = randInt(8) + (59 - r1.m_width);
	}
	return r1;
}*/

