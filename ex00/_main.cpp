#include <fstream>
#include <iostream>
#include <sstream>

int main()
{
    std::ifstream data("data.csv");
    std::string line;

    if(!data.is_open())
        return 1;

    while(!data.eof())
    {
        std::getline(data , line);

        if(line.empty())
            break;
        
        std::istringstream ss_line(line);

        std::string date ;
        std::string value;

        std::getline(ss_line , date , ',');
        std::getline(ss_line , value , ',');

        if(date.empty() || value.empty() || !ss_line.eof())
        {
            std::cout << "Error" << std::endl;
            continue;
        }

        std::string yyyy;
        std::string mm;
        std::string dd;

        std::istringstream ss_date(date);

        std::getline(ss_date , yyyy , '-');
        std::getline(ss_date , mm , '-');
        std::getline(ss_date , dd , '-');
        
        if(yyyy.empty() || mm.empty() || dd.empty() || !ss_date.eof())
        {
            std::cout << "Date_error" << std::endl;
            continue;
        }

        std::cout << "[" << yyyy << "/"<< mm << "/" << dd << "]" << " ~ " << value << std::endl;
    }

    return (0);
}
