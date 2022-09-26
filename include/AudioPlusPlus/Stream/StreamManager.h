#pragma once
#include <AudioPlusPlus/Stream/Stream.h>
#include <unordered_map>

namespace AudioPlusPlus
{
	/**
	 * @brief      Class to manage the streams.
	 */
	class StreamManager
	{
		public:
			StreamManager(StreamManager const&) = delete;
			void operator=(StreamManager const&) = delete;

			/**
			 * @brief      Gets the StreamManager singleton instance.
			 *
			 * @return     The StreamManager instance.
			 */
			static StreamManager& Get();

			/**
			 * @brief      Get a Stream from the given name.
			 *
			 * @param[in]  name  The name of the Stream.
			 *
			 * @return     The Stream.
			 */
			Stream* GetStream(const std::string& name);

			/**
			 * @brief      Create a new Stream with a given name.
			 *
			 * @param[in]  name  The name of the Stream.
			 *
			 * @return     The created Stream.
			 */
			Stream* NewStream(const std::string& name);

			/**
			 * @brief      Deletes a Stream from the StreamManager.
			 *
			 * @param[in]  name  The name of the Stream.
			 *
			 * @return     Error code.
			 */
			int DeleteStream(const std::string& name);

			/**
			 * @brief      Delets a Stream from the StreamManager.
			 *
			 * @param      stream  The Stream.
			 *
			 * @return     Error code.
			 */
			int DeleteStream(Stream* stream);

		private:
			StreamManager();
			~StreamManager();

			/** Map of the Streams */
			std::unordered_map<std::string, Stream*> streams;
	};
}