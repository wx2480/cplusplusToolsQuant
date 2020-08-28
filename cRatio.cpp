#include<cmath>
#include<cstdlib>
#include<ctime>
#include<fstream>
#include<iostream>
#include<sstream>
#include<string>
#include<vector>

class utils
{
public:
    double corr(const std::vector<double> &x, const std::vector<double> &y);
    double corr(const std::vector<double> &x, const std::vector<double> &y, const std::vector<double> &weight);
    std::vector<double> corr_mat(const std::vector<std::vector<double> > &x, const std::vector<std::vector<double> > &y);
    std::vector<double> corr_mat(const std::vector<std::vector<double> > &x, const std::vector<std::vector<double> > &y, const std::vector<std::vector<double> > &weight);
};

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

class backTest
{
public:
    backTest(){};
    ~backTest(){};
    
    std::vector<std::vector<double> > ic_test(const std::vector<int> &time, const std::vector<int> &code, const std::vector<std::vector<double> > &values, const std::vector<std::vector<double> > &ret);
    void set_rf(const double &r){rf = r;}
    double get_rf(){return rf;}
    
    void set_fee(const double &f){fee = f;}
    double get_fee(){return fee;}
    
private:
    double rf = 0.03;
    double fee = 0.00025;
};

/*
 ***************
 *    main     *
 ***************
*/

int main(int argc, char** argv)
{
    std::time_t start = std::time(0);
    
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
    
    readCsv A("\t");
    std::string read_path,read_path0;
    read_path = "/data/stock/newSystemData/rawdata/tickdata/tick_3s_csv/htsc_tick_3s_1.3.1/20190604/600519.csv";
    read_path0 = "/data/stock/newSystemData/rawdata/tickdata/tick_3s_csv/htsc_tick_3s_1.3.1/20190604/000858.csv";
    
    std::vector<std::vector<double> > data = A.read_one(read_path),data0 = A.read_one(read_path0);
    
    
    std::vector<double> time,ret,ret1,time1,weight,weight1,_ret;
    
    for(int i=0;i<data.size();i++)
    {
        if((data[i][1] >=93000000) && (data[i][1] <=150000000))
	{
            ret.push_back(data[i][7]);  //last
	    weight.push_back(data[i][5]);  //cumvol
	    time.push_back(data[i][1]);
	}
    }
    
    for(int i=0;i<data0.size();i++)
    {
        if((data[i][1] >=93000000) && (data[i][1] <=150000000))
	{
            ret1.push_back(data0[i][7]);  //last
	    weight1.push_back(data0[i][5]);  //cumvol
	    time1.push_back(data0[i][1]);
	}
    }
    
    
    
    std::cout<<ret.size()<<std::endl<<ret1.size()<<std::endl;
    backTest B;
    B.set_rf(0.035);
    utils tool;
    std::vector<double> b(5,1.0);
    std::cout<<"corr_weight: "<<tool.corr(ret,ret1,weight)<<std::endl;
    std::cout<<"corr: "<<tool.corr(ret,ret1)<<std::endl;
   
    std::cout<<"corr_mat: "<<tool.corr_mat(data,data)[4]<<std::endl;
    
    std::time_t end = std::time(0);
    std::cout<<"cost time: "<<end - start<<std::endl;
    
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
/*
double cRatio::sharpe(std::vector<double> netWorth, int periods, int tradingDays)
{
    double convert = sqrt(static_cast<double>(tradingDays) / static_cast<double>(periods));
    double xmean,x2mean,ret = 
    for(int i=0;i<netWorth.size();i++)
    {
        
    }
    
}
*/
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
	    if((values[i] == '\t') || (i == values.size() - 1))
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


// backTest
std::vector<std::vector<double> > backTest::ic_test(const std::vector<int> &time, const std::vector<int> &code, const std::vector<std::vector<double> > &values, const std::vector<std::vector<double> > &ret)
{
    std::vector<std::vector<double> > ans;
    
    for(int i=0; i<time.size();i++)
    {
        ;
    }
    return ans;
}

// utils
double utils::corr(const std::vector<double> &x, const std::vector<double> &y)
{
    double ans=0,mu_x=0,mu_y=0,x2=0,y2=0,xy=0,varx,vary;
    double n = x.size();
    
    if(n != y.size())
    {
        std::cout<<"the shape of x and y must be equal"<<std::endl;
	return NAN;
    }
    
    for(int i=0;i<n;i++)
    {
        if(isnan(x[i]) || isnan(y[i]))
	    continue;
        mu_x += x[i];
	mu_y += y[i];
	x2 += x[i] * x[i];
	y2 += y[i] * y[i];
	xy += x[i] * y[i];
    }
    varx = x2/n-mu_x*mu_x/n/n;
    vary = y2/n-mu_y*mu_y/n/n;
    if((varx==0) || (vary==0))
        ans = NAN;
    else
        ans = (xy / n - mu_x/n*mu_y/n) / sqrt(varx*vary);
    return ans;
}

double utils::corr(const std::vector<double> &x, const std::vector<double> &y, const std::vector<double> &weight)
{
    double ans=0,su_x=0,su_y=0,su_y2 =0,su_x2 = 0,su_xy=0,su_w=0,var_x,var_y,cov;
    int n = x.size();
    
    if(n != y.size())
    {
        std::cout<<"the shape of x and y must be equal"<<std::endl;
	return NAN;
    }
    
    for(int i=0;i<n;i++)
    {
        if(isnan(x[i]) || isnan(y[i]) || isnan(weight[i]))
	    continue;
        su_w += weight[i];
	su_x += weight[i]*x[i];
	su_y += weight[i]*y[i];
	su_x2 += weight[i]*x[i]*x[i];
	su_y2 += weight[i]*y[i]*y[i];
	su_xy += weight[i]*x[i]*y[i];
    }
    var_x = su_x2/su_w - su_x/su_w*su_x/su_w;
    var_y = su_y2/su_w - su_y/su_w*su_y/su_w;
    if((var_x==0) || (var_y==0))
        ans = NAN;
    else
        cov = su_xy/su_w - su_x*su_y/su_w/su_w;
        ans = cov/sqrt(var_x * var_y);
    
    return ans;
}

std::vector<double> utils::corr_mat(const std::vector<std::vector<double> > &x, const std::vector<std::vector<double> > &y)
{
    std::vector<double> ans;
    double correlation;
    for(int i=0;i<x.size();i++)
    {
        correlation = corr(x[i],y[i]);
        ans.push_back(correlation);
    }
    return ans;
}

std::vector<double> utils::corr_mat(const std::vector<std::vector<double> > &x, const std::vector<std::vector<double> > &y, const std::vector<std::vector<double> > &weight)
{
    std::vector<double> ans;
    double correlation;
    for(int i=0;i<x.size();i++)
    {
        correlation = corr(x[i],y[i],weight[i]);
        ans.push_back(correlation);
    }
    return ans;;
}














    // qilin yili bro's brilliant recursion algorithm to calculte the weighted corr
  /*
 cdef:
        unsigned int num = x.shape[0], i=0
        double wsum = 0,wsum1 = 0,mu_y = 0, var_y =0,mu_x = 0.0,var_x=0.0,cov_xy=0.0,corr,delta_x,delta_y,delta_x_w,delta_y_w,delta_x_ww1,delta_y_ww1

    for i in range(num):
        if isnan(y[i]) or isnan(x[i]) or isnan(w[i]):
            continue
        wsum1 = wsum
        wsum += w[i]
        delta_y = y[i] - mu_y
        delta_y_w = delta_y * w[i] / wsum
        delta_y_ww1 = delta_y_w * wsum1

        var_y += delta_y * delta_y_ww1
        mu_y += delta_y_w
                        
        delta_x = x[i] - mu_x
        delta_x_w = delta_x * w[i] / wsum
        var_x += delta_x * delta_x_w * wsum1
        mu_x += delta_x_w

        cov_xy += delta_x * delta_y_ww1

    corr = sqrt(var_y) * sqrt(var_x)
    if corr==0:
        corr = NAN
    else:
        corr = cov_xy / corr    
    return corr
 */