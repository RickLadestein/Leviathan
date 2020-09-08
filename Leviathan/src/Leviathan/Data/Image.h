#pragma once
#include "Leviathan/Core.h"
#include "Leviathan/Util/FileManager.h"
#include <memory>
#include <string>
namespace leviathan {
	class Image {
	public:
		Image(int width, int height, int channels, unsigned char* data);
		~Image();

		void GetDimensions(int* width, int* height);
		inline int GetChannelCount() { return this->channels; };
		inline unsigned char* GetDataPtr() { return this->data; };

		Image() = delete;
		Image(const Image&) = delete;
		Image& operator=(const Image&) = delete;

		static std::shared_ptr<Image> Load(std::string folder_id, std::string file);
		static unsigned char* Load(std::string folder_id, std::string file, int* width, int* height, int* channels);
	private:
		int width, height, channels;
		unsigned char* data;
	};
}