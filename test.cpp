#include<cmath>
#include<cstdlib>
#include<ctime>
#include<fstream>
#include<iostream>
#include<sstream>
#include<string>
#include<vector>
#include"cRatio.h"

/*
 ***************
 *    main     *
 ***************
*/

int main(int argc, char** argv)
{
    std::time_t start = std::time(0);
    /*
    std::vector<double> netWorth;
    
    cRatio calRatio(std::strtod(argv[1], NULL));
    
    std::srand((unsigned)time(NULL));
    
    for(int i=0;i<100;i++)
    {   
        r = std::rand()/static_cast<double>(RAND_MAX);
        if(i == 0)
            netWorth.push_back(1);
	else
	    netWorth.push_back((r*0.4+0.8) * netWorth[i-1]);
    }
    
    
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
    */
    std::time_t end = std::time(0);
    
    std::cout<<"cost time: "<<end - start<<std::endl;
    
    return 0;
}