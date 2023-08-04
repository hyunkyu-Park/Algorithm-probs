//https://blog.uniony.me/swea/7091/

//7091 은기의 아주 큰 그림

#include <iostream>
using namespace std;

#define MAXN 2000
#define HASH_SIZE (1 << 30)
#define DIV (HASH_SIZE - 1)

int H, W, N, M;

int myPic[MAXN][MAXN], samPic[MAXN][MAXN];
int samHash[MAXN][MAXN], tmp[MAXN][MAXN];

int CalcMul(int num, int shift) {
    unsigned long long rev = 1;
    for(int i = 1; i < num; i++) {
        rev = (rev << shift) + rev;
    }
    return (int) (rev & DIV);
}

int GetHash(int* piv, int num, int shift) {
    unsigned long long hash = 0;
    for(int i = 0; i < num; i++) {
        hash = (hash << shift) + hash + *piv++;
    }
    return (int) (hash & DIV);
}

int GetNext(int prev, int sub, int mul, int add, int shift) {
    unsigned long long hash = prev - (sub * mul);
    hash = (hash << shift) + hash + add;
    return (int) (hash & DIV);
}

int main(int argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
	int test_case;
	int T;
	cin>>T;

	for(test_case = 1; test_case <= T; ++test_case)
	{
        cin >> H >> W >> N >> M;

        //그림 인풋
        for(int h = 0; h < H; h++) for(int w = 0; w < W; w++) {
            char a;
            cin >> a;
            if(a == 'o'){
                myPic[h][w] = 1;
            } 
            else{
                 myPic[h][w] = 0;
            }
        }
        for(int n = 0; n < N; n++) for(int m = 0; m < M; m++) {
            char a;
            cin >> a;
            if(a == 'o'){
                samPic[n][m] = 1;
            } 
            else {
                samPic[n][m] = 0;
            }
        }

        // Get My Hash
        for(int i = 0; i < H; i++) {
            tmp[0][i] = GetHash(myPic[i], W, 4);
        }
        int myHash = GetHash(tmp[0], H, 5);

        // Get Sam Hash
        int mulC = CalcMul(W, 4);
        int mulR = CalcMul(H, 5);
        for(int i = 0; i < N; i++) {
            tmp[0][i] = GetHash(samPic[i], W, 4);
            for(int j = 1; j < M - W + 1; j++) {
                tmp[j][i] = GetNext(tmp[j-1][i], samPic[i][j-1], mulC, samPic[i][j+W-1], 4);
            }
        }
        for(int i = 0; i < M - W + 1; i++) { //선생님 그림의 열
            samHash[0][i] = GetHash(tmp[i], H, 5);
            for(int j = 1; j < N - H + 1; j++) { //선생님 그림의 행
                samHash[j][i] = GetNext(samHash[j-1][i], tmp[i][j-1], mulR, tmp[i][j+H-1], 5);
            }
        }

        // Compare
        int cnt = 0;
        for(int i = 0; i < N - H + 1; i++){
            for(int j = 0; j < M - W + 1; j++){
                if(samHash[i][j] == myHash) cnt++;
            }
        } 
        cout << '#' << test_case << ' ' << cnt << '\n';
    }
    return 0;
}