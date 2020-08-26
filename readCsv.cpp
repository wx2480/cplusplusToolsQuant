#include<cstdlib>
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
private:
    std::string sep;
    std::string dataType;
};

int main()
{
    readCsv A;
    std::string read_path = "/home/xiaonan/cplus_wxn/20190606.csv";
    A.read_one(read_path);
    return 0;
}

readCsv::readCsv(std::string sep, std::string dataType):sep(sep),dataType(dataType){}

std::vector<std::vector<double> > readCsv::read_one(std::string read_path)
{
    std::ifstream infile(read_path.c_str());
    std::string values,value;
    std::istringstream iss;
    std::vector<std::vector<double> > ans;
    std::vector<double> line;
    
    double _value;
    
    while(infile.good())
    {
        std::getline(infile, values);
	iss.str(values);
	while(std::getline(iss, value, ','))
	{
	    _value = std::strtod(value.c_str(), NULL);
	    line.push_back(_value);
	}
	ans.push_back(line);
	
	line.clear();
	iss.clear();
    }
    /*
    for(int i=0;i<ans.size();i++)
    {
        for(int j=0;j<ans[i].size();j++)
	{
	    std::cout<<ans[i][j]<<"  ";
	}
	std::cout<<std::endl;
    }
    */
    return ans;
}

