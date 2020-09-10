#include "Renderer.h"
bool FacecullingEnabled = false;
bool BlendingEnabled = false;
void Renderer::Render(Drawable entity, std::weak_ptr<Camera> cam)
{
}

void Renderer::Render(std::vector<Drawable> entities, std::weak_ptr<Camera> cam)
{
}

void Renderer::Render(Drawable entity, std::weak_ptr<Camera> cam, void* fbo)
{
}

void Renderer::Render(std::vector<Drawable> entity, std::weak_ptr<Camera> cam, void* fbo)
{
}

#pragma region Culling
void Renderer::SetFaceCulling(bool enabled)
{
	if (enabled) {
		glEnable(GL_CULL_FACE);
	}
	else {
		glDisable(GL_CULL_FACE);
	}
	FacecullingEnabled = enabled;
}

void Renderer::SetFaceCullSide(FaceCullSide side)
{
	glCullFace((GLenum)side);
}

void Renderer::SetFrontFaceCullingOrientation(FrontFaceOrientation orientation)
{
	glFrontFace((GLenum)orientation);
}

bool Renderer::IsFaceCullingEnabled()
{
	return FacecullingEnabled;
}
void Renderer::ResetCulling()
{
	SetFaceCullSide(FaceCullSide::BACK);
	SetFrontFaceCullingOrientation(FrontFaceOrientation::COUNTER_CLOCKWISE);
}
#pragma endregion

#pragma region Blending
void Renderer::SetBlending(bool enabled)
{
	if (enabled)
		glEnable(GL_BLEND);
	else
		glDisable(GL_BLEND);
	BlendingEnabled = enabled;
}

void Renderer::SetBlendMode(BlendMode src_factor, BlendMode dst_factor)
{
	glBlendFunc((GLenum)src_factor, (GLenum)dst_factor);
}

bool Renderer::IsBlendingEnabled()
{
	return BlendingEnabled;
}

void Renderer::ResetBlendMode()
{
	SetBlendMode(BlendMode::ONE, BlendMode::ZERO);
}
#pragma endregion
