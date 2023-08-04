//사탕 분배

//A+B =C라고 할때
//4, 9, 13이면
//처음 사탕을 나눈 후에 8 5 13이 되고
//두번 째 나눈 후에는 3 10 13
//그 다음은 6 7 13이 된다.
//n회차 후의 사탕의 개수 => x * 2^n % 13
//다시 처음 사탕을 나눌때로 돌아가보면 4 * 2 % 13 = 8
//두번 째는 4 * 2^2 % 13 = 3
//그 다음은 4 * 2^3 % 13 = 6이 되는 걸 알 수 있다.


#include<iostream>
#include<cmath>

using namespace std;

long long x, y, total, ans;

long long int_pow(long long num, long long n){
    if(n==0) return 1;
    if(n==1) return num;
 
    if(n%2 ==0){ // even
        long long tmp = int_pow(num, n/2);
        
        return tmp * tmp % total;
    }
    else{ //odd
        long long tmp = int_pow(num, (n-1)/2);
        long long check2 = tmp * tmp * num;
        return tmp * tmp * num % total;
    }
}


int main(int argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
	int test_case;
	int T;

	cin>>T;

	for(test_case = 1; test_case <= T; ++test_case)
	{
        
        int N; 
        cin >> x >> y >>N;
        total = x+y;
        x = x*int_pow(2, N); //그냥 pow는 double값을 리턴하기 때문에 정수용 pow를 만들어줬다.
        y = y*int_pow(2, N);
        x %=total;
        y %= total;
        ans = min(x, y);
        cout << "#" << test_case << " " << ans << "\n";


	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}

