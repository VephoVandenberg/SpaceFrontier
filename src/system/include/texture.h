#pragma once


namespace GAME_NAMESPACE
{
	namespace System
	{
		class Texture
		{
		public:
			Texture(const char* tPath);
			Texture(Texture&& texture);
			Texture& operator=(Texture&& texture);

			~Texture();

			void bind();
			void unbind();
				
			Texture() = default;
			Texture(const Texture& texture) = default;

			Texture& operator=(const Texture&) = delete;

		private:
			friend class ResourceManager;

			unsigned int ID;
			int m_width;
			int m_height;
			int m_nrChannels;

			bool m_isActive;
		};
	}
}
