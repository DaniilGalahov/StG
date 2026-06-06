using System;
using System.IO;
using System.IO.Compression;
using AESBridge;
using StGBridge;

namespace StG
{
    public static class DataProcessor
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
    }
}