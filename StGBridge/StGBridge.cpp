#include "StGBridge.h"

namespace
{
    static std::vector<uint8_t> ToNative(cli::array<System::Byte>^ a)
    {
        std::vector<unsigned char> v;
        if (a != nullptr && a->Length > 0)
        {
            v.resize(a->Length);
            pin_ptr<System::Byte> p = &a[0];
            std::memcpy(v.data(), p, a->Length);
        }
        return v;
    }

    static cli::array<System::Byte>^ ToManaged(const std::vector<uint8_t>& v)
    {
        auto a = gcnew cli::array<System::Byte>(static_cast<int>(v.size()));
        if (!v.empty())
        {
            pin_ptr<System::Byte> p = &a[0];
            std::memcpy(p, v.data(), v.size());
        }
        return a;
    }
}

cli::array<System::Byte>^ StGBridge::StGNative::Embed
(
	cli::array<System::Byte>^ dataBytes,
	cli::array<System::Byte>^ carrierImageBytes,
	cli::array<System::Byte>^ passwordBytes,
	int blockSize,
	double treshold
)
{
	try
	{
		std::vector<uint8_t> nativeCarrierImageBytes = ToNative(carrierImageBytes);
		std::vector<uint8_t> nativeDataBytes = ToNative(dataBytes);
		std::vector<uint8_t> nativePasswordBytes = ToNative(passwordBytes);
		std::vector<uint8_t> nativeStegoImageBytes;
		int result = StGLib::Embed(nativeStegoImageBytes, nativeDataBytes, nativeCarrierImageBytes, nativePasswordBytes, blockSize, treshold);

		if (result != 0)
		{
			throw gcnew Exception("StGLib::Embed failed.");
		}

		return ToManaged(nativeStegoImageBytes);
	}
	catch (const std::exception& exception)
	{
		throw gcnew Exception
		(
			gcnew String(exception.what())
		);
	}
}

cli::array<System::Byte>^ StGBridge::StGNative::Extract
(
	cli::array<System::Byte>^ stegoImageBytes,
	cli::array<System::Byte>^ passwordBytes,
	int blockSize,
	double treshold
)
{
	try
	{
		std::vector<uint8_t> nativeDataBytes;

		std::vector<uint8_t> nativeStegoImageBytes = ToNative(stegoImageBytes);
		std::vector<uint8_t> nativePasswordBytes = ToNative(passwordBytes);
		int result = StGLib::Extract(nativeDataBytes, nativeStegoImageBytes, nativePasswordBytes, blockSize, treshold);

		if (result != 0)
		{
			throw gcnew Exception("StGLib::Extract failed.");
		}

		return ToManaged(nativeDataBytes);
	}
	catch (const std::exception& exception)
	{
		throw gcnew Exception
		(
			gcnew String(exception.what())
		);
	}
}