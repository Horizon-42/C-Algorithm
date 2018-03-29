#include <iostream>

#define Int unsigned long long int

using namespace std;
Int n=0, m=0;

bool is_odd(Int xy){
    if(xy==1)return true;
    Int l=1, h=xy, mid=0, s=0;
    while(l<h){
        mid=(l+h)/2;
        s=mid*mid;
        if(s==xy)
            return true;
        else if(s<xy)
            l=mid+1;
        else 
            h=mid-1;
    }
    return false;
}

int main(){
    cin>>n>>m;
    Int cnt=0;
    for(Int x=1; x<=n; ++x){
        for(Int y=1; y<=m; ++y){
            if(is_odd(x)&is_odd(y))
                cnt++;
        }
    }

    cout<<cnt;

    return 0;
}