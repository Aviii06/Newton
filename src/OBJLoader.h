#pragma once

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include <GL/GLEW.h>

#include "VertexBuffer.h"
#include "common/types.h"
#include <glm/glm.hpp>

void loadOBJ(const std::string &file_name, Vector<Vertex> &vertices, Vector<unsigned int> &indices) {

    //Vertex portions
    std::vector<glm::fvec3> vertex_positions;
    std::vector<glm::fvec2> vertex_texcoords;
    std::vector<glm::fvec3> vertex_normals;

    //Face vectors
    std::vector<GLint> vertex_position_indicies;
    std::vector<GLint> vertex_texcoord_indicies;
    std::vector<GLint> vertex_normal_indicies;

    std::stringstream ss;
    std::ifstream in_file(file_name.c_str());
    std::string line = "";
    std::string prefix = "";
    glm::vec3 temp_vec3;
    glm::vec2 temp_vec2;
    GLint temp_glint = 0;

    //File open error check
    if (!in_file.is_open()) {
        throw "ERROR::OBJLOADER::Could not open file.";
    }

    //Read one line at a time
    while (std::getline(in_file, line)) {
        //Get the prefix of the line
        ss.clear();
        ss.str(line);
        ss >> prefix;

        if (prefix == "#") {

        } else if (prefix == "o") {

        } else if (prefix == "s") {

        } else if (prefix == "use_mtl") {

        } else if (prefix == "v")//Vertex position
        {
            ss >> temp_vec3.x >> temp_vec3.y >> temp_vec3.z;
            vertex_positions.push_back(temp_vec3);
        } else if (prefix == "vt") {
            ss >> temp_vec2.x >> temp_vec2.y;
            vertex_texcoords.push_back(temp_vec2);
        } else if (prefix == "vn") {
            ss >> temp_vec3.x >> temp_vec3.y >> temp_vec3.z;
            vertex_normals.push_back(temp_vec3);
        } else if (prefix == "f") {
            int counter = 0;
            while (ss >> temp_glint) {
                //Pushing indices into correct arrays
                if (counter == 0)
                    vertex_position_indicies.push_back(temp_glint);
                else if (counter == 1)
                    vertex_texcoord_indicies.push_back(temp_glint);
                else if (counter == 2)
                    vertex_normal_indicies.push_back(temp_glint);

                //Handling characters
                if (ss.peek() == '/') {
                    ++counter;
                    ss.ignore(1, '/');
                } else if (ss.peek() == ' ') {
                    counter = 0;
                    ss.ignore(1, ' ');
                }

                //Reset the counter
                if (counter > 2)
                    counter = 0;
            }
        }
    }

    vertices.resize(vertex_position_indicies.size(), Vertex());
    vertex_texcoord_indicies.resize(vertex_position_indicies.size(), GLint(0));
    vertex_normal_indicies.resize(vertex_position_indicies.size(), GLint(0));
    indices.resize(vertex_position_indicies.size(), GLint(0));

    for (size_t i = 0; i < vertices.size(); ++i) {
        if (vertex_texcoord_indicies[i] == 0) {
            vertices[i].texcoord = glm::fvec2(1.0, 0.0);
        } else {
            vertices[i].texcoord = vertex_texcoords[vertex_texcoord_indicies[i] - 1];
        }
        if (vertex_normal_indicies[i] == 0) {
            vertices[i].normal = glm::fvec3(1.0, 0.0, 0.0);
        } else {
            vertices[i].normal = vertex_normals[vertex_normal_indicies[i] - 1];
        }
        vertices[i].position = vertex_positions[vertex_position_indicies[i] - 1] * 100.0f;
        vertices[i].color = glm::vec3(1.f, 1.f, 1.f);
        indices[i] = i;
        vertices[i].isLit = 1.0f;
    }

    //DEBUG
    std::cout << "Nr of vertices: " << vertices.size() << "\n";

    //Loaded success
    std::cout << "OBJ file loaded!"
              << "\n";
}
