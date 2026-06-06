using System;
using System.IO;
using System.IO.Compression;
using AESBridge;
using StGBridge;

namespace StG
{
    public static class Functions
    {
        public static Byte[] Compress(Byte[] dataBytes)
        {
            using (var compressedDataStream = new MemoryStream())
            {
                using (var gZipStream = new GZipStream(compressedDataStream, CompressionMode.Compress))
                {
                    gZipStream.Write(dataBytes, 0, dataBytes.Length);
                    gZipStream.Close();
                    return compressedDataStream.ToArray();
                }
            }
        }

        public static Byte[] Decompress(Byte[] compressedDataBytes)
        {
            using (var compressedDataStream = new MemoryStream(compressedDataBytes))
            {
                using (var gZipStream = new GZipStream(compressedDataStream, CompressionMode.Decompress))
                {
                    using (var dataStream = new MemoryStream())
                    {
                        gZipStream.CopyTo(dataStream);
                        return dataStream.ToArray();
                    }
                }
            }
        }

        public static Byte[] Encrypt(Byte[] data, Byte[] password, Mode mode)
        {
            return AESBridge.AESNative.Encrypt(data, password, mode);
        }

        public static Byte[] Decrypt(Byte[] encryptedData, Byte[] password, Mode mode)
        {
            return AESBridge.AESNative.Decrypt(encryptedData, password, mode);
        }

        public static Byte[] Embed(Byte[] dataBytes, Byte[] carrierImageBytes, Byte[] passwordBytes, int blockSize = 8, double treshold=0.7)
        {
            return StGBridge.StGNative.Embed(dataBytes, carrierImageBytes, passwordBytes, blockSize, treshold);
        }

        public static Byte[] Extract(Byte[] stegoImageBytes, Byte[] passwordBytes, int blockSize = 8, double treshold = 0.7)
        {
            return StGBridge.StGNative.Extract(stegoImageBytes, passwordBytes, blockSize, treshold);
        }
    }
}