#pragma once


namespace GAME_NAMESPACE
{
	namespace System
	{
		class Texture
		{
		public:
			Texture(const char* tPath);
			
			Texture() = default;
			~Texture() = default;
			Texture(const Texture&) = default;
			Texture& operator=(const Texture&) = default;

			void bind();

			Texture(const Texture&&) = delete;
			Texture& operator=(const Texture&&) = delete;

		private:
			unsigned int ID;
			int m_width;
			int m_height;
			int m_nrChannels;
		};
	}
}
