#pragma once

#include <iostream>
#include <sstream>

#include "renderer/IndexBuffer.h"
#include "renderer/Mesh.h"
#include "renderer/Renderer.h"
#include "renderer/Shader.h"
#include "renderer/shapes/Shape.h"
#include "renderer/Texture.h"
#include "renderer/VertexArray.h"
#include "renderer/VertexBuffer.h"
#include "renderer/Camera.h"
#include "renderer/PointLight.h"
#include "renderer/shapes/Quad3d.h"
#include "renderer/Renderer2D.h"
#include "renderer/Renderer3D.h"

#include "Editor/Window.h"
#include "Editor/Application.h"

#include "inputs/InputHandler.h"

#include "confs/Config.h"

#include "inputs/InputHandler.h"

#include "confs/Config.h"

#include "utils/Timer.h"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/glm/glm.hpp"

Application* Application::s_Instance = nullptr;