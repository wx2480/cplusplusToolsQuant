#ifndef _cRatio_H
#define _cRatio_H
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
#endif