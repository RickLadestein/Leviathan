#include "Renderer.h"
#include "Leviathan/Graphics/Shader.h"
#include "Leviathan/Graphics/Texture.h"

#include <iostream>

#ifdef LEVIATHAN_DEBUG
	#define DEBUG() (__debugbreak()) 
#else
	#define DEBUG() (0)
#endif

using Leviathan::Graphics::Drawable;
using Leviathan::Graphics::Texture;
using Leviathan::Graphics::ShaderProgram;
using Leviathan::Graphics::Buffers::VertexBuffer;
using Leviathan::Graphics::Buffers::FrameBuffer;

namespace Leviathan {
	bool FacecullingEnabled = false;
	bool BlendingEnabled = false;
	const char* texes[8] = {"texture0", "texture1", "texture2" , "texture3", "texture4", "texture5", "texture6", "texture7" };
	void Renderer::Render(Drawable& entity, std::weak_ptr<Camera> cam)
	{
		if (!entity.GetVertexBuffer()->buffers_ready) {
			std::cout << "Could not load model because buffers were not initialised" << std::endl;
			return;
		}
		std::shared_ptr<ShaderProgram> shader = entity.getShader().lock();
		VertexBuffer* vb = entity.GetVertexBuffer();
		MultiTexture* mtex = entity.getTexture();
		std::shared_ptr<Camera> camera = cam.lock();

		if (shader && camera) {
			mtex->Bind();
			shader->bind();

			for (int i = 0; i < MAX_MULTITEX_TEXTURES; i++) {
				shader->setUniform(texes[i], i);
			}

			shader->setUniform("projection", camera->GetProjectionMatrix());
			shader->setUniform("view", camera->GetViewMatrix());
			shader->setUniform("model", entity.GetModelMatrix());
			shader->setUniform("time", glfwGetTime());
			vb->Bind();

			glDrawArrays(GL_TRIANGLES, 0, vb->element_count);
			shader->unbind();
			mtex->Unbind();
			vb->Unbind();
			return;

		}
		else {
			if (!shader) {
				std::cout << "Could not render because shader did not exist" << std::endl;
			}
			if (!camera) {
				std::cout << "Could not render because camera did not exist" << std::endl;
			}
			DEBUG();
		}
	}

	void Renderer::Render(std::vector<Drawable>& entities, std::weak_ptr<Camera> cam)
	{
		auto it = entities.begin();
		while (it != entities.end()) {
			Render(*it, cam);
			it++;
		}
	}

	void Renderer::Render(Drawable& entity, std::weak_ptr<Camera> cam, std::weak_ptr<FrameBuffer> fbo)
	{
		std::shared_ptr<FrameBuffer> buff = fbo.lock();
		if (buff) {
			buff->Bind();
			Render(entity, cam);
			buff->Unbind();
		}
		else {
			std::cout << "Could not render entity: framebuffer was not initialized" << std::endl;
			__debugbreak();
			DEBUG();
		}
	}

	void Renderer::Render(std::vector<Drawable>& entities, std::weak_ptr<Camera> cam, std::weak_ptr<FrameBuffer> fbo)
	{
		std::shared_ptr<FrameBuffer> buff = fbo.lock();
		if (buff) {
			buff->Bind();
			Render(entities, cam);
			buff->Unbind();
		}
		else {
			std::cout << "Could not render entities: framebuffer was not initialized" << std::endl;
			DEBUG();
		}
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
}