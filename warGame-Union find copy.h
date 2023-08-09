#include <unordered_map>
#include <list>
#include <string>

using namespace std;

int InputN;
int parent[8625]; //linked information for each monarch. Each monarch is connected to itself initially
//attack api is called maximum 8000 times and max map size is 25*25 => 8000+(25*25) = 8625


list <int> UnionList[625]; //max map size is 25*25 
list <int> EnemyList[625]; //max map size is 25*25 


int Find(int x) {
	if (x == parent[x])
		return x;
	else
		return parent[x] = Find(parent[x]); //'parent[x] =' this part is path compression
}


void Union(int x, int y) {
	x = Find(x);
	y = Find(y);
	if (x != y) { //if x and y are not alliance
		parent[y] = x;
		UnionList[x].splice(UnionList[x].end(), UnionList[y]);
		EnemyList[x].splice(EnemyList[x].end(), EnemyList[y]);

        //splice: member function of list
        //void splice(const_iterator pos, list& other);
        //connect all elements of other at the pos is pointing to

        //line 29: connect all alliances of y at the end of x's alliances
        //line 30: connect all enemies of y at the end of x's enemies
	}
}


int IsSameUnion(int x, int y) {
	x = Find(x);
	y = Find(y);
	if (x == y) //If x and y are allies
		return 1;
	else
		return 0;
}


int IsEnemy(int x, int y) {
	x = Find(x);
	y = Find(y);
	for (auto enemy : EnemyList[x]) { 
		if (Find(enemy) == y) return 1; //if x and y are enemies
	}
	return 0;
}


void MakeEnemy(int x, int y) { //make x and y are enemies
	x = Find(x);
	y = Find(y);
	if (x == y) return;
	if (IsEnemy(x, y)) return;
	EnemyList[x].push_back(y);
	EnemyList[y].push_back(x);
}


struct SNationInfo
{
	int x;
	int y;
	int sol; //soldiers
};

SNationInfo Nation[8625];
int NationIndex[26][26];

unordered_map <string, int> NationMap; //change monarch's name to int

int NactionCount; //number of nations to set id value


void init(int N, int mSoldier[25][25], char mMonarch[25][25][11])
{
	InputN = N;
	int index = 0;
	NationMap.clear();
	for (int j = 0; j < N; j++) {
		for (int i = 0; i < N; i++) {
			NationMap[mMonarch[j][i]] = index;


			NationIndex[j][i] = index;


			Nation[index].sol = mSoldier[j][i];
			Nation[index].x = i;
			Nation[index].y = j;
			parent[index] = index;


			UnionList[index].clear();
			EnemyList[index].clear();


			UnionList[index].push_back(index); //connect oneself in the union(alliance) list


			index++;
		}
	}


	NactionCount = N * N;
}


void destroy()
{


}

// The allies of mMonarchA form an alliance with those of mMonarchB
// If mMonarchA is mMonarchB or they are already allies return -1
// If any of alliance of mMonarchA is enemies with alliance of mMonarchB return -2
// else, they form an alliance and return 1

// Each monarch's name consists of lowercase alphabetic characters and is a string of not less than 4 but not more than 10.
// Its guaranteed that mMonarchA and mMonarchB are monarch

// Parameters
// mMonarchA : name of monarch (4 ≤ length ≤ 10)
// mMonarchB : name of monarch (4 ≤ length ≤ 10)

// Returns
// if they are already allies: -1
// if they have enemies: -2
// success: 1
int ally(char mMonarchA[11], char mMonarchB[11])
{
	int a = NationMap[mMonarchA];
	int b = NationMap[mMonarchB];


	if (IsSameUnion(a, b)) {
		return -1;
	}
	if (IsEnemy(a, b)) {
		return -2;
	}


	Union(a, b);
	return 1;
}

// mMonarchA and its alliances attack mMonarchB
// Attack is conducted by mGeneral

// if mMonarchA and mMonarchB are allies return -1, no battle happens
// If mMonarchA's territory or allied territory is not adjacent to monarch B's territory, it returns -2, and no battle takes place.

// when battle takes place, all allies of A and B are become enemies.

// when battle takes place, all allies, including monarch A, who is adjacent to monarch B's territory,
// send half of their soldiers to attack together.
// All of monarch B's allies adjacent to monarch B's territory also send half of their soldiers
// to B's territory to help defend them.
// The decimal point is discarded when calculating the sending soldiers.
// even if the number of attack soldiers is 0, battle takes place

// In battle, soldiers fight one-on-one with their opponents and die together.

// the result of the battle is decided by left soldiers
// if attack side is left, attack is success. return 1
// if there are any soldiers left on the defense side, or if all soldiers are dead. return 0
// the general is not counted as a soldier

// if attack is success, mMonarchB is excuted
// The territory ruled by B is destroyed and becomes a new territory with no alliance or hostility.
// mGeneral becomes new monarch of the territory and incorporated into the alliance of A, and the hostile relationship is the same as that of mMonarchA.

// Each monarch's name consists of lowercase alphabetic characters and is a string of not less than 4 but not more than 10.
// Its guaranteed that mMonarchA and mMonarchB are monarch, and mGenearl is not monarch.


// Parameters
// mMonarchA : Name of the attacking monarch (4 ≤ length ≤ 10)
// mMonarchB : the name of the monarch of the territory under attack (4 ≤ length ≤ 10)
// mGeneral : the name of the general commanding the attack (4 ≤ length ≤ 10) 

// Returns
// make a successful attack: return 1
// succeed in defending : return 0
// they are allies already: return -1
// there is no adjacent allies around the territory: return -2
int attack(char mMonarchA[11], char mMonarchB[11], char mGeneral[11])
{
	int a = NationMap[mMonarchA];
	int b = NationMap[mMonarchB];


	int bossA = Find(a);
	int bossB = Find(b);


	if (bossA == bossB) { //if they are allies
		return -1;
	}


	int sx = Nation[b].x - 1; //range of adjacent territories
	int ex = Nation[b].x + 1;
	int sy = Nation[b].y - 1;
	int ey = Nation[b].y + 1;


	if (sx < 0) sx = 0;
	if (sy < 0) sy = 0;
	if (ex > InputN - 1) ex = InputN - 1;
	if (ey > InputN - 1) ey = InputN - 1;


	int isThereEnemy = 0;
	for (int j = sy; j <= ey; j++) {
		for (int i = sx; i <= ex; i++) {
			if (bossA == Find(NationIndex[j][i])) { //check if there are allies in adjacent territories
				isThereEnemy = 1;
				j = InputN;
				break;
			}
		}
	}


	if (isThereEnemy == 0) {
		return -2;
	}


	MakeEnemy(bossA, bossB);//make x and y are enemies


	int totalSolA = 0;
	int totalSolB = Nation[b].sol;
	Nation[b].sol = 0;
	int moveNum;


	for (int j = sy; j <= ey; j++) {
		for (int i = sx; i <= ex; i++) {
			if (bossA == Find(NationIndex[j][i])) {
				moveNum = Nation[NationIndex[j][i]].sol / 2;
				Nation[NationIndex[j][i]].sol -= moveNum;
				totalSolA += moveNum;
			}
			else if (bossB == Find(NationIndex[j][i])) {
				moveNum = Nation[NationIndex[j][i]].sol / 2;
				Nation[NationIndex[j][i]].sol -= moveNum;
				totalSolB += moveNum;
			}
		}
	}


	if (totalSolB >= totalSolA) {//attack fail
		Nation[b].sol = totalSolB - totalSolA;
		return 0;
	}


	UnionList[bossB].remove(b); //remove b

	Nation[b].sol = totalSolA - totalSolB; //remaining soldiers
	Nation[NactionCount] = Nation[b]; //add new nation

	NationIndex[Nation[NactionCount].y][Nation[NactionCount].x] = NactionCount; //change the map

	NationMap[mGeneral] = NactionCount; //add new monarch in the hash

	parent[NactionCount] = bossA; //connect new monarch to the boss of A
	UnionList[bossA].push_back(NactionCount); //add new monarch to the alliance of A

	NactionCount++;
	return 1;
}



// recruit soldiers

// when mOption is 0
// Recruiting mNum soldiers in the territory of monarch B.
// returns the number of soldiers in the territory

// when mOption is 1
// Each of the territories of all alliances, including mMonarch, recruits mNum soldiers.
// Returns the number of soldiers in the alliance after recruiting soldiers.


// Each monarch's name consists of lowercase alphabetic characters and is a string of not less than 4 but not more than 10.
// Its guaranteed that mMonarch is monarch

// Parameters
// mMonarch : name of the monarch (4 ≤ length ≤ 10)   
// mNum : number of soldiers (1 ≤ mNum ≤ 200)
// mOption : condition

// Returns
// number of soldiers
int recruit(char mMonarch[11], int mNum, int mOption)
{
	int sum = 0;


	if (mOption == 0) {
		int a = NationMap[mMonarch];
		Nation[a].sol += mNum;
		sum = Nation[a].sol;
	}
	else {
		int boss = Find(NationMap[mMonarch]);
		for (auto nation : UnionList[boss]) {
			Nation[nation].sol += mNum;
			sum += Nation[nation].sol;
		}
	}
	return sum;
}