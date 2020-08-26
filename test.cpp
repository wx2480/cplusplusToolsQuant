#include<vector>
#include<cstdlib>
#include<ctime>
#include<iostream>

using namespace std;

double maxDrawdown(vector<double> netWorth)
{
    double pre = netWorth[0];
    double maxNetWorth = netWorth[0];
    double ans = 0, now, drawdown;
    for(int i=1;i<netWorth.size();i++)
    {
        now = netWorth[i];
        if(now >= pre)
	{
	    maxNetWorth = (now>maxNetWorth)?now:maxNetWorth;
	    pre = now;
	}
	else
	{
	    drawdown = 1 - now/maxNetWorth;
	    ans = (ans>drawdown)?ans:drawdown;
	    pre = now;
	}
	cout<<i<<" "<<ans<<endl;
    }
    return ans;
}
/*
int main()
{
    vector<double> netWorth;
    srand((unsigned)time(NULL));
    double r;
    for(int i=0;i<10;i++)
    {   
        r = rand()/static_cast<double>(RAND_MAX);
        if(i == 0)
            netWorth.push_back(r - 0.5);
	else
	    netWorth.push_back(r - 0.5 + netWorth[i-1]);
    }
    cout<<maxDrawdown(netWorth)<<endl;
    return 0;
}
*/