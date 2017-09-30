#include <bits/stdc++.h>

#define ll long long
#define ull unsigned long long
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define be begin()
#define en end()
#define all(x) (x).begin(),(x).end()
#define alli(a, n, k) (a+k),(a+n+k)
#define REP(i, a, b, k) for(__typeof(a) i = a;i < b;i += k)
#define REPI(i, a, b, k) for(__typeof(a) i = a;i > b;i -= k)
#define REPITER(it, a) for(__typeof(a.begin()) it = a.begin();it != a.end(); ++it)

#define y0 sdkfaslhagaklsldk
#define y1 aasdfasdfasdf
#define yn askfhwqriuperikldjk
#define j1 assdgsdgasghsf
#define tm sdfjahlfasfh
#define lr asgasgash
#define norm asdfasdgasdgsd
#define have adsgagshdshfhds

#define eps 1e-6
#define pi 3.141592653589793

using namespace std;

template<class T> inline T gcd(T x, T y) { if (!y) return x; return gcd(y, x%y); }
template<class T> inline T mod(T x) { if(x < 0) return -x; else return x; }

typedef vector<int> VII;
typedef vector<ll> VLL;
typedef pair<int, int> PII;
typedef vector< pair<int, int> > VPII;
typedef vector< pair<int, PII > > VPPI;

const int MOD = 1e9 + 7;
const int INF = 1e9;
const int MAXR = 6;
const int MAXC = 7;

int evendr2[] = {-2, -2, -2, -1, -1, 0, 0, 1, 1, 1, 1, 2};
int evendc2[] = {0, 1, -1, 2, -2, -2, 2, -2, -1, 1, 2, 0};
int odddr2[] = {-2, -1, -1, -1, -1, 0, 0, 1, 2, 2, 2, 1};
int odddc2[] = {0, -1, 1, -2, 2, -2, 2, -2, 1, 0, -1, 2};
int evendr1[] = {-1, -1, -1, 0, 0, 1};
int evendc1[] = {-1, 0, 1, -1, 1, 0};
int odddr1[] = {-1, 0, 0, 1, 1, 1};
int odddc1[] = {0, -1, 1, -1, 0, 1};

bool isMovePossible(int grid[MAXR][MAXC], int playerId, PII current)
{
	int x = current.fi;
	int y = current.se;
	int x1, y1;
	if(x < 0 or x > MAXR-1 or y < 0 or y > MAXC-1 or grid[x][y] != playerId) return false;

	if(y % 2 == 0)
	{
		REP(i, 0, 6, 1)
		{
			x1 = x + evendr1[i];
			y1 = y + evendc1[i];
			if((0 <= x1 and x1 <= MAXR-1) and (0 <= y1 and y1 <= MAXC-1) and grid[x1][y1] == 0)
				return true;
		}
		REP(i, 0, 12, 1)
		{
			x1 = x + evendr2[i];
			y1 = y + evendc2[i];
			if((0 <= x1 and x1 <= MAXR-1) and (0 <= y1 and y1 <= MAXC-1) and grid[x1][y1] == 0)
				return true;
		}
	}
	else
	{
		REP(i, 0, 6, 1)
		{
			x1 = x + odddr1[i];
			y1 = y + odddc1[i];
			if((0 <= x1 and x1 <= MAXR-1) and (0 <= y1 and y1 <= MAXC-1) and grid[x1][y1] == 0)
				return true;
		}
		REP(i, 0, 12, 1)	{
			x1 = x + odddr2[i];
			y1 = y + odddc2[i];
			if((0 <= x1 and x1 <= MAXR-1) and (0 <= y1 and y1 <= MAXC-1) and grid[x1][y1] == 0)
				return true;
		}
	}
	return false;
}


VPII findPossibleStones(int grid[MAXR][MAXC], int playerId)
{
	VPII possibleStones;
	REP(i, 0, MAXR, 1)
	{
		REP(j, 0, MAXC, 1)
		{
			if(grid[i][j] == playerId)
			{
				if(isMovePossible(grid, playerId, mp(i, j)))
					possibleStones.pb(mp(i, j));
			}
		}
	}
	return possibleStones;
}

PII findPossibleMove(int grid[MAXR][MAXC], PII current)
{
	int x = current.fi;
	int y = current.se;
	int x1, y1;
	VPII possibleMoves;
	if(y % 2 == 0)
	{
		REP(i, 0, 6, 1)
		{
			x1 = x + evendr1[i];
			y1 = y + evendc1[i];
			if((0 <= x1 and x1 <= MAXR-1) and (0 <= y1 and y1 <= MAXC-1) and grid[x1][y1] == 0)
			{
				possibleMoves.pb(mp(x1, y1));
			}
		}
		REP(i, 0, 12, 1)
		{
			x1 = x + evendr2[i];
			y1 = y + evendc2[i];
			if((0 <= x1 and x1 <= MAXR-1) and (0 <= y1 and y1 <= MAXC-1) and grid[x1][y1] == 0)
			{
				possibleMoves.pb(mp(x1, y1));
			}
		}
	}
	else
	{
		REP(i, 0, 6, 1)
		{
			x1 = x + odddr1[i];
			y1 = y + odddc1[i];
			if((0 <= x1 and x1 <= MAXR-1) and (0 <= y1 and y1 <= MAXC-1) and grid[x1][y1] == 0)
			{
				possibleMoves.pb(mp(x1, y1));
			}
		}
		REP(i, 0, 12, 1)
		{
			x1 = x + odddr2[i];
			y1 = y + odddc2[i];
			if((0 <= x1 and x1 <= MAXR-1) and (0 <= y1 and y1 <= MAXC-1) and grid[x1][y1] == 0)
			{
				possibleMoves.pb(mp(x1, y1));
			}
		}
	}
	srand(time(NULL));
    int id = rand() % possibleMoves.size();
    return possibleMoves[id];
}


int main(int argc, char* argv[])
{
	if(argc == 2 or argc == 3) freopen(argv[1], "r", stdin);
	if(argc == 3) freopen(argv[2], "w", stdout);
	ios::sync_with_stdio(false);
	int grid[MAXR][MAXC];
	int move_count, playerId;
	REP(i, 0, MAXR, 1)
		REP(j, 0, MAXC, 1)
			cin >> grid[i][j];

	cin >> move_count >> playerId;
	VPII possibleStones = findPossibleStones(grid, playerId);
	srand(time(NULL));
    int id = rand() % possibleStones.size();
    PII move = findPossibleMove(grid, possibleStones[id]);
    cout << possibleStones[id].fi << ' ' << possibleStones[id].se<< endl;
    cout << move.fi << ' ' << move.se << endl;
	return 0;
}

