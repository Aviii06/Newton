#pragma once

#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<vector>
#include<algorithm>

#include<GL/GLEW.h>

#include "../common/types.h"

void loadOBJ(const char* file_name, Vector<float>& pos, Vector<float>& texCoord, Vector<float> vertex_normals, Vector<unsigned int>& ind)
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

        else if ( prefix == "vn" )
        {
            float a,b,c;
			ss >> a >> b >> c;
			vertex_normals.push_back(a);
			vertex_normals.push_back(b);
			vertex_normals.push_back(c);
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
                
            else if (prefix == "f")
            {
                int counter = 0;
                while (ss >> temp_glint)
                {
                    //Pushing indices into correct arrays
                    if (counter == 0)
                        vertex_position_indicies.push_back(temp_glint);
                    else if (counter == 1)
                        vertex_texcoord_indicies.push_back(temp_glint);
                    else if (counter == 2)
                        vertex_normal_indicies.push_back(temp_glint);

                    //Handling characters
                    if (ss.peek() == '/')
                    {
                        ++counter;
                        ss.ignore(1, '/');
                    }
                    else if (ss.peek() == ' ')
                    {
                        ++counter;
                        ss.ignore(1, ' ');
                    }
                    //Reset the counter
                    if (counter > 2)
                        counter = 0;
                }	
            }

        }
    }
}
