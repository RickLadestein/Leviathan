#include "StencilBuffer.h"

bool StencilBufferEnabled = false;
/**
 * @brief Tells OpenGL how to update the stencil buffer whenever the fragment passes or fails the stencil test
 * @param stencil_fail Defines what is supposed to happen when stencil test fails
 * @param depth_fail Defines what is supposed to happen when stencil test passes but depth test fails
 * @param depth_pass Defines what is supposed to happen when stencil and buffer both pass
*/
void StencilBuffer::SetStencilOperation(StencilOp stencil_fail, StencilOp depth_fail, StencilOp depth_pass)
{
	glStencilOp((GLenum)stencil_fail, (GLenum)depth_fail, (GLenum)depth_pass);
}

/**
	 * @brief This tells OpenGL that whenever the stencil value of a fragment is equal (GL_EQUAL) to the
	 * reference value 1, the fragment passes the test and is drawn, otherwise discarded.
	 * @param func 	Sets the stencil test function that determines whether a fragment passes or is discarded.
	 * @param ref	Specifies the reference value for the stencil test. The stencil buffer's content is compared to this value.
	 * @param mask	Specifies a mask that is ANDed with both the reference value and the stored stencil value before the test compares them. Initially set to all 1s.
	 */
void StencilBuffer::SetStencilFunc(StencilFunc func, GLint ref, GLuint mask)
{
	glStencilFunc((GLenum)func, ref, mask);
}

/**
 * @brief Tells OpenGL to permit writing to the stencil buffer
 * @param write Sets the write permission to specified boolean
*/
void StencilBuffer::SetStencilWritePerm(bool write)
{
	if (write)
		glStencilMask(0xFF);
	else
		glStencilMask(0x0);
	return;
}

/**
 * @brief Gets the stencil buffer enabled bool
 * @return Is stencil buffer enabled boolean
*/
bool StencilBuffer::IsEnabled()
{
	return StencilBufferEnabled;
}


/**
 * @brief Enables Stencil Buffer
*/
void StencilBuffer::Enable() {
	StencilBufferEnabled = true;
	glEnable(GL_DEPTH_TEST);
}

/**
 * @brief Disables Stencil Buffer
*/
void StencilBuffer::Disable() {
	StencilBufferEnabled = false;
	glDisable(GL_DEPTH_TEST);
}

void StencilBuffer::Reset()
{
	SetStencilOperation(StencilOp::KEEP, StencilOp::KEEP, StencilOp::KEEP);
	SetStencilFunc(StencilFunc::ALWAYS, 1, 0xFF);
	SetStencilWritePerm(true);
}

