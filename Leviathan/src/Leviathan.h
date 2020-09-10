#pragma once
//Core components
#define LEVIATHAN_DEBUG

#include "Leviathan/Core.h"
#include "Leviathan/Core/Event.h"
#include "Leviathan/Core/Application.h"
#include "Leviathan/Core/Window.h"
#include "Leviathan/Core/Renderer.h"

//Data components
#include "Leviathan/Data/Image.h"
#include "Leviathan/Data/Structures.h"

//Graphics components
#include "Leviathan/Graphics/Drawable.h"
#include "Leviathan/Graphics/Shader.h"
#include "Leviathan/Graphics/Texture.h"
#include "Leviathan/Graphics/Buffers/VertexBuffer.h"
#include "Leviathan/Graphics/Buffers/StencilBuffer.h"
#include "Leviathan/Graphics/Buffers/DepthBuffer.h"
#include "Leviathan/Graphics/Buffers/FrameBuffer.h"
#include "Leviathan/Graphics/Camera.h"
#include "Leviathan/Graphics/Mesh.h"

//Input components
#include "Leviathan/Input/Keyboard.h"
#include "Leviathan/Input/Mouse.h"

//Util components
#include "Leviathan/Util/Filemanager.h"
#include "Leviathan/Util/Delegate/Delegate.h"
#include "Leviathan/Util/Delegate/MultiDelegate.h"