using AESBridge;
using System;
using System.IO;
using System.Security.Cryptography;
using System.Text;

namespace StG
{
    public static class DataProcessor
    {
        public static void Embed
        (
            string dataFilePath,
            string carrierImageFilePath,
            string stegoImageFilePath,
            int encryptionMode,
            string encryptionPassword,
            string stegoPassword,

            int blockSize = 8,
            double treshold = 0.7
        )
        {
            Byte[] dataBytes = File.ReadAllBytes(dataFilePath);
            Byte[] compressedDataBytes = Functions.Compress(dataBytes);
            Byte[] encryptionPasswordBytes = Encoding.UTF8.GetBytes(encryptionPassword);
            Byte[] encryptedDataBytes = Functions.Encrypt(compressedDataBytes, encryptionPasswordBytes, (AESBridge.Mode)encryptionMode);
            Byte[] carrierImageBytes = File.ReadAllBytes(carrierImageFilePath);
            Byte[] stegoPasswordBytes = Encoding.UTF8.GetBytes(stegoPassword);
            try
            {
                Byte[] stegoImageBytes = Functions.Embed(encryptedDataBytes, carrierImageBytes, stegoPasswordBytes, blockSize, treshold);

                compressedDataBytes = null;
                encryptedDataBytes = null;
                carrierImageBytes = null;

                Byte[] ecEncryptedDataBytes = Functions.Extract(stegoImageBytes, stegoPasswordBytes, blockSize, treshold);
                Byte[] ecCompressedDataBytes = Functions.Decrypt(ecEncryptedDataBytes, encryptionPasswordBytes, (AESBridge.Mode)encryptionMode);
                Byte[] ecDataBytes = Functions.Decompress(ecCompressedDataBytes);

                MD5 md5 = MD5.Create();
                string hashData = BitConverter.ToString(md5.ComputeHash(dataBytes));
                string hashECData = BitConverter.ToString(md5.ComputeHash(ecDataBytes));
                if(hashData == hashECData)
                {
                    File.WriteAllBytes(stegoImageFilePath, stegoImageBytes);
                }
                else
                {
                    throw new Exception("Embedding failed, try other carrier.");
                }
            }
            catch (Exception ex)
            {
                throw new Exception(ex.Message + " Carrier stegocapacity insufficient.");
            }
        }

        public static void Extract
        (
            string stegoImageFilePath,
            string dataFilePath,
            int encryptionMode,
            string encryptionPassword,
            string stegoPassword,

            int blockSize = 8,
            double treshold = 0.7            
        )
        {
            Byte[] stegoImageBytes = File.ReadAllBytes(stegoImageFilePath);
            Byte[] stegoPasswordBytes = Encoding.UTF8.GetBytes(stegoPassword);
            Byte[] encryptedDataBytes = Functions.Extract(stegoImageBytes, stegoPasswordBytes, blockSize, treshold);
            Byte[] encryptionPasswordBytes = Encoding.UTF8.GetBytes(encryptionPassword);
            Byte[] compressedDataBytes = Functions.Decrypt(encryptedDataBytes, encryptionPasswordBytes, (AESBridge.Mode)encryptionMode);
            Byte[] dataBytes = Functions.Decompress(compressedDataBytes);
            File.WriteAllBytes(dataFilePath, dataBytes);
        }
    }
}
