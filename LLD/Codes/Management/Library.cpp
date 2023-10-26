#include <bits/stdc++.h>
using namespace std;

int solve(int n,int a,int b,int c)
{
    if(n==0)return 0;
    if(n<0)return -1;

    int x = solve(n-a,a,b,c);
    int y = solve(n-b,a,b,c);
    int z = solve(n-c,a,b,c);

    int res = max(x,max(y,z));

    return res;

}

int main()
{
    int n =7;
    int x= 5;
    int y= 2;
    int z= 2;

    int ans = solve(n,x,y,z);
    if(ans<0)cout<<0;
    cout<<ans;
    return 0;
}