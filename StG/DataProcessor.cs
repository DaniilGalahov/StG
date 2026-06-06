using System;
using System.IO;
using System.Text;

namespace StG
{
    public static class DataProcessor
    {
        public static void Embed
        (
            string dataFilePath,

            bool compress,

            bool encrypt,
            int encryptionMode,
            string encryptionPassword,

            bool useEncryptionPasswordForStego,

            string carrierImageFilePath,
            string stegoPassword,
            int blockSize,
            double treshold,

            string stegoImageFilePath
        )
        {
            Byte[] dataBytes = File.ReadAllBytes(dataFilePath);

            if (compress)
            {
                dataBytes = Functions.Compress(dataBytes);
            }

            Byte[] encryptionPasswordBytes = Encoding.UTF8.GetBytes(encryptionPassword);
            if (encrypt)
            {
                dataBytes = Functions.Encrypt(dataBytes, encryptionPasswordBytes, (AESBridge.Mode)encryptionMode);
            }

            Byte[] carrierImageBytes = File.ReadAllBytes(carrierImageFilePath);

            Byte[] stegoPasswordBytes = Encoding.UTF8.GetBytes(stegoPassword);
            if (useEncryptionPasswordForStego)
            {
                stegoPasswordBytes = encryptionPasswordBytes;
            }

            try
            {
                Byte[] stegoImageBytes = Functions.Embed(dataBytes, carrierImageBytes, stegoPasswordBytes, blockSize, treshold);
                File.WriteAllBytes(stegoImageFilePath, stegoImageBytes);
            }
            catch (Exception ex)
            {
                throw new Exception(ex.Message + " Carrier stegocapacity insufficient.");
            }
        }

        public static void Extract
        (
            string stegoImageFilePath,
            string stegoPassword,
            int blockSize,
            double treshold,

            bool useStegoPasswordForEncryption,

            bool encrypted,
            int encryptionMode,
            string encryptionPassword,

            bool compressed,

            string dataFilePath
        )
        {
            Byte[] stegoImageBytes = File.ReadAllBytes(stegoImageFilePath);
            Byte[] stegoPasswordBytes = Encoding.UTF8.GetBytes(stegoPassword);

            Byte[] dataBytes = Functions.Extract(stegoImageBytes, stegoPasswordBytes, blockSize, treshold);

            if (encrypted)
            {
                Byte[] encryptionPasswordBytes = Encoding.UTF8.GetBytes(encryptionPassword);
                if (useStegoPasswordForEncryption)
                {
                    encryptionPasswordBytes = stegoPasswordBytes;
                }

                dataBytes = Functions.Decrypt(dataBytes, encryptionPasswordBytes, (AESBridge.Mode)encryptionMode);
            }

            if (compressed)
            {
                dataBytes = Functions.Decompress(dataBytes);
            }

            File.WriteAllBytes(dataFilePath, dataBytes);
        }
    }
}
