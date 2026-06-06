#pragma once
#include <vector>
#include "StGLib.h"

using namespace System;

namespace StGBridge
{
	public ref class StGNative sealed
	{
	public:
		static cli::array<System::Byte>^ Embed
		(
			cli::array<System::Byte>^ carrierImageBytes,
			cli::array<System::Byte>^ dataBytes,
			cli::array<System::Byte>^ passwordBytes
		);

		static cli::array<System::Byte>^ Extract
		(
			cli::array<System::Byte>^ stegoImageBytes,
			cli::array<System::Byte>^ passwordBytes
		);
	};
}
