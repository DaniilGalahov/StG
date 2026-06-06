using System;
using System.IO;
using System.IO.Compression;
using AESBridge;
using StGBridge;

namespace StG
{
    internal class DataProcessor
    {
        Byte[] Zip(Byte[] dataBytes)
        {
            MemoryStream dataStream = new MemoryStream();
            using (dataStream)
            {
                dataStream.Write(dataBytes, 0, dataBytes.Length);
                dataStream.Position = 0;
            }

            MemoryStream zippedDataStream = new MemoryStream();
            using (zippedDataStream)
            {
                using (GZipStream compressor = new GZipStream(zippedDataStream, CompressionMode.Compress))
                {
                    dataStream.CopyTo(compressor);
                }
            }

            Byte[] zippedDataBytes = zippedDataStream.ToArray();

            dataStream.Close();
            zippedDataStream.Close();

            return zippedDataBytes;
        }
    }
}
