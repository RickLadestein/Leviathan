#pragma once
#include "Leviathan/Graphics/Drawable.h"
#include "Leviathan/Graphics/Camera.h"
#include "Leviathan/Graphics/Buffers/FrameBuffer.h"
#include <memory>
#include <vector>
#include "glad/glad.h"
enum class FaceCullSide {
	FRONT = GL_FRONT,
	BACK = GL_BACK,
	FRONT_BACK = GL_FRONT_AND_BACK
};

enum class FrontFaceOrientation {
	CLOCKWISE = GL_CW,
	COUNTER_CLOCKWISE = GL_CCW
};

enum class BlendMode {
	ZERO = GL_ZERO,
	ONE = GL_ONE,
	SRC_COLOR = GL_SRC_COLOR,
	ONE_MINUS_SRC_COLOR = GL_ONE_MINUS_SRC_COLOR,
	DST_COLOR = GL_DST_COLOR,
	ONE_MINUS_DST_COLOR = GL_ONE_MINUS_DST_COLOR,
	SRC_ALPHA = GL_SRC_ALPHA,
	ONE_MINUS_SRC_ALPHA = GL_ONE_MINUS_SRC_ALPHA,
	DST_APLHA = GL_DST_ALPHA,
	ONE_MINUS_DST_ALPHA = GL_ONE_MINUS_DST_ALPHA,
	CONSTANT_COLOR = GL_CONSTANT_COLOR,
	ONE_MINUS_CONSTANT_COLOR = GL_ONE_MINUS_CONSTANT_ALPHA,
	CONSTANT_ALPHA = GL_CONSTANT_ALPHA,
	ONE_MINUS_CONSTANT_ALPHA = GL_ONE_MINUS_CONSTANT_ALPHA
};

class Renderer {
public:
	static void Render(Drawable& entity, std::weak_ptr<Camera> cam);
	static void Render(std::vector<Drawable>& entities, std::weak_ptr<Camera> cam);

	static void Render(Drawable& entity, std::weak_ptr<Camera> cam, std::weak_ptr<FrameBuffer> fbo);
	static void Render(std::vector<Drawable>& entities, std::weak_ptr<Camera> cam, std::weak_ptr<FrameBuffer> fbo);

	//Face culling
	static void SetFaceCulling(bool enabled);
	static void SetFaceCullSide(FaceCullSide side);
	static void SetFrontFaceCullingOrientation(FrontFaceOrientation orientation);
	static bool IsFaceCullingEnabled();
	static void ResetCulling();

	//Blend mode
	static void SetBlending(bool enabled);
	static void SetBlendMode(BlendMode src_factor, BlendMode dst_factor);
	static bool IsBlendingEnabled();
	static void ResetBlendMode();

};