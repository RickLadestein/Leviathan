#include "DepthBuffer.h"

bool DepthBufferEnabled = false;
namespace Leviathan::Graphics::Buffers {
	/**
	 * @brief Sets the comparision operator used for comparing new depth values with the current values in the depth buffer
	 * @param func Specifies the depth comparison function
	*/
	void DepthBuffer::SetDepthFunction(DepthFunc func)
	{
		glDepthFunc((GLenum)func);
	}

	/**
	 * @brief Enables depth buffer
	*/
	void DepthBuffer::Enable()
	{
		DepthBufferEnabled = true;
		glEnable(GL_DEPTH_TEST);
	}

	/**
	 * @brief Disables depth buffer
	*/
	void DepthBuffer::Disable()
	{
		DepthBufferEnabled = false;
		glDisable(GL_DEPTH_TEST);
	}

	/**
	 * @brief Gets the depth buffer enabled bool
	 * @return Is depth buffer enabled boolean
	*/
	bool DepthBuffer::IsEnabled()
	{
		return DepthBufferEnabled;
	}

	/**
	 * @brief Resets the depth buffer parameters to OpenGL defaults
	*/
	void DepthBuffer::Reset()
	{
		SetDepthFunction(DepthFunc::ALWAYS);
	}
}
