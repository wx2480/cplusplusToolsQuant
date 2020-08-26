#include<cmath>
#include<cstdlib>
#include<ctime>
#include<fstream>
#include<iostream>
#include<sstream>
#include<string>
#include<vector>


class readCsv
{
public:
    readCsv(std::string sep = ",", std::string dataType = "double");
    std::vector<std::vector<double> > read_one(std::string read_path);
    std::vector<std::vector<double> > read_all(std::string read_path);
    
private:
    std::string sep;
    std::string dataType;
};


/*
 ***************
 * declaration *
 ***************
*/

class cRatio
{
public:
    cRatio(double a);
    ~cRatio();
    
    double getRf();
    
    double maxDrawdown(std::vector<double> netWorth);
    double annualReturn(std::vector<double> netWorth, int tradingDays = 256);
    double sharpe(std::vector<double> netWorth, int periods, int tradingDays = 256);
    double modifiedSharpe(std::vector<double> netWorth);
    double calmar(std::vector<double> netWorth);
    double winRatio(std::vector<double> networth);
    double pcr(std::vector<double> netWorth);
    double sigma(std::vector<double> ret);

private:
    double r;
    
};

/*
 ***************
 *    main     *
 ***************
*/

int main(int argc, char** argv)
{
  
    std::vector<double> netWorth;
    
    cRatio calRatio(std::strtod(argv[1], NULL));
    /*
    std::srand((unsigned)time(NULL));
    
    for(int i=0;i<100;i++)
    {   
        r = std::rand()/static_cast<double>(RAND_MAX);
        if(i == 0)
            netWorth.push_back(1);
	else
	    netWorth.push_back((r*0.4+0.8) * netWorth[i-1]);
    }
    */
    
    readCsv A;
    std::string read_path = "/home/xiaonan/cplus_wxn/20190606.csv";
    std::vector<std::vector<double> > data = A.read_one(read_path);
    
    std::vector<double> ret;
    
    
    for(int i=0;i<data.size();i++)
    {
        ret.push_back(data[i][2]);
    }
    
    std::cout<<calRatio.sigma(ret)<<std::endl;
    std::cout<<"RiskFreeInterest:"<<calRatio.getRf()<<std::endl;
    
    return 0;
}

/*
 ******************
 * implementation *
 ******************
*/
// cRatio
cRatio::cRatio(double a):r(a){}

cRatio::~cRatio(){}

double cRatio::getRf()
{
    return r;
}

double cRatio::maxDrawdown(std::vector<double> netWorth)
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
    }
    return ans;
}

double cRatio::sigma(std::vector<double> ret)
{
    double mean=0,squareMean=0, ans, t;
    t = ret.size();
    for(int i=0;i<t;i++)
    {
        mean += ret[i];
	squareMean += ret[i] * ret[i];
    }
    ans = sqrt(squareMean/t - mean*mean/t/t);
    return ans;
}

// readCsv
readCsv::readCsv(std::string sep, std::string dataType):sep(sep),dataType(dataType){}

std::vector<std::vector<double> > readCsv::read_one(std::string read_path)
{
    std::ifstream infile(read_path.c_str());
    std::string values,value;
    std::istringstream iss;
    std::vector<std::vector<double> > ans;
    std::vector<double> line;
    
    double _value;
    
    while(std::getline(infile, values))
    {
        
	
	for(int i=0;i<values.size();i++)
	{
	    if((values[i] == ',') || (i == values.size() - 1))
	    {
	        _value = std::strtod(value.c_str(), NULL);
	        line.push_back(_value);
		value.clear();
	    }
	    else
	    {
	        value = value+values[i];
	    }
	    
	}
	ans.push_back(line);
	
	line.clear();
    }
    /*
    for(int i=0;i<ans.size();i++)
    {
        for(int j=0;j<ans[i].size();j++)
	{
	    std::cout<<ans[i][j]<<"  ";
	}
	std::cout<<ans[i].size()<<std::endl;
    }
    */
    return ans;
}

std::vector<std::vector<double> > readCsv::read_all(std::string read_path)
{
    
}

