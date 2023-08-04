//9843. 촛불 이벤트

#include <iostream>
#include <cstring>
#include <cmath>
 
#define endl "\n"
using namespace std;
 
long long N, Answer;
 
void Initialize() {}
 
void Input()
{
    cin >> N;
}
 
void Solution()
{
    long long Candidate = sqrt(N * 2);
    if (Candidate * (Candidate + 1) == N * 2) Answer = Candidate;
    else Answer = -1;
}
 
void Solve()
{
    int Tc; cin >> Tc;
    for (int T = 1; T <= Tc; T++)
    {
        Initialize();
        Input();
        Solution();
 
        cout << "#" << T << " " << Answer << endl;
    }
}
 
int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
 
    //freopen("Input.txt", "r", stdin);
    Solve();
 
    return 0;
}
