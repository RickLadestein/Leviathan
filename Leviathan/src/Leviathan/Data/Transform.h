#pragma once
#include "Leviathan/Util/Math.h"

namespace Leviathan::Data {
	struct Transform {
	public:
		Transform() {
			position = glm::vec3(0.0f);
			rotation = glm::vec3(0.0f);
			scale = glm::vec3(1.0f);

			oldposition = glm::vec3(0.0f);
			oldrotation = glm::vec3(0.0f);
			oldscale = glm::vec3(10.0f);

			oldmatrix = glm::mat4(1.0f);
		}

		glm::vec3 position;
		glm::vec3 rotation;
		glm::vec3 scale;

		void Translate(glm::vec3& trans) {
			position += trans;
		}

		void Rotate(glm::vec3& rot) {
			rotation += rot;
			//NormalizeRotation();
		}

		void Scale(glm::vec3& scl) {
			scale *= scl;
		}

		glm::mat4 GetTransformMatrix() {
			if (CheckForUpdate()) {
				//NormalizeRotation();
				oldmatrix = glm::mat4(1.0f);
				glm::mat4 rot = glm::mat4(1.0f);
				glm::mat4 scl = glm::mat4(1.0f);
				glm::mat4 tr = glm::mat4(1.0f);

				glm::quat finalOrientation = EulerAnglesToQuaternion(rotation);
				rot = glm::toMat4(finalOrientation);
				scl = glm::scale(scl, this->scale);
				tr = glm::translate(tr, this->position);
				oldmatrix = tr*(rot * scl);
			}
			return oldmatrix;
		}

	private:
		glm::vec3 oldposition;
		glm::vec3 oldrotation;
		glm::vec3 oldscale;
		glm::mat4 oldmatrix;

		bool CheckForUpdate() {
			bool updateneeded = false;
			if (glm::length(oldposition - position) != 0) {
				oldposition = position;
				oldrotation = rotation;
				oldscale = scale;
				updateneeded = true;
			} else if (glm::length(oldrotation - rotation) != 0) {
				oldposition = position;
				oldrotation = rotation;
				oldscale = scale;
				updateneeded = true;
			}else if (glm::length(oldscale - scale) != 0) {
				oldposition = position;
				oldrotation = rotation;
				oldscale = scale;
				updateneeded = true;
			}
			return updateneeded;
		}

		void NormalizeRotation() {
			float x = glm::degrees(glm::acos(glm::cos(glm::radians(rotation.x))));
			float y = glm::degrees(glm::acos(glm::cos(glm::radians(rotation.y))));
			float z = glm::degrees(glm::acos(glm::cos(glm::radians(rotation.z))));
			this->rotation = glm::vec3(x, y, z);
		}
	};
}