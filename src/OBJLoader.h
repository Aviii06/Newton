#pragma once

#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<vector>
#include<algorithm>

#include<GL/GLEW.h>

#include "../common/types.h"

void loadOBJ(const char* file_name, Vector<float>& pos, Vector<float>& texCoord, Vector<unsigned int>& ind)
{
    std::stringstream ss;
    std::ifstream in_file(file_name);

    if(!in_file.is_open())
    {
        std::cerr<<"Couldn't open the file\n";
    }

    std::string line;
    std::string prefix = "";
    GLint temp = 0;

    while(std::getline(in_file, line))
    {
        ss.clear();
        ss.str(line);
        ss >> prefix;

        if(prefix == "#")
        {

        }

        else if ( prefix == "v" )
        {
            float x,y,z;
            ss >> x >> y >> z;
            pos.push_back(x);
            pos.push_back(y);
            pos.push_back(z);
        }

        else if ( prefix == "f" )
        {
            // unsigned int a,b,c,d;
            // ss>>a>>b>>c>>d;
            // ind.push_back(a);
            // ind.push_back(b);
            // ind.push_back(c);
            //
            // ind.push_back(a);
            // ind.push_back(c);
            // ind.push_back(d);
            int counter = 0;
            // std::cout<<line<<"\n";
                
			while (ss >> temp)
			{
                ind.push_back(temp);
				if (ss.peek() == '/')
				{
					ss.ignore(1, '/');
				}
                if ( ss.peek() == '/')
                {
                    ss.ignore(1, '/');
                }
				if (ss.peek() == ' ')
				{
					ss.ignore(1, ' ');
				}

                std::cout<<temp<<" , ";
			}	

            std::cout<<" \n";
        }
    }
}
