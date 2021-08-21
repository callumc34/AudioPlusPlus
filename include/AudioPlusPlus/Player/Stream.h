#pragma once
#include <portaudio.h>

namespace AudioPlusPlus
{
	class Stream
	{
		public:
			Stream();
			~Stream();

			PaStream* Get();

			PaError Start();
			PaError Stop();
			PaError Close();

		private:
			PaStream* stream = 0;
	};
}