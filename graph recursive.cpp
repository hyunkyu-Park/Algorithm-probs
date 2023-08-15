//coordinates can be moved in 2 ways

//(a, b) = (a, a+b)
//(a, b) = (a+b, b)

//start, end coordinates are given
//check if its possible to reach the end

//example 1:
//(1,4), (5, 9)

//(1,4) -> (5,4) -> (5,9) Possible.


//example 2:
//(1,2), (3,6)

//(1, 2) -> (1,3) -> (1,4) ->(1,5) -> (1,6) -> (7,6) not possible
//(1, 2) -> (3,2) -> (3,5) -> (3,8) not possible

#include <iostream>

bool flag;
void my_function(int a, int b, int c, int d){
    if(a > c || b>d) {
        return;
    }

    if(a ==b && c==d){
        flag =true;
    }

    my_function(a+b, b, c, d);
    my_function(a, a+b, c, d);
}

int main(){
    int a, b, c, d;
    
    my_function(a, b, c, d);
    
    if (flag) {
        std::cout << "Yes" << "\n";
    } else {
        std::cout << "No" << "\n";
    }
    
}