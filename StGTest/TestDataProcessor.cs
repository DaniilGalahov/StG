using Microsoft.VisualStudio.TestTools.UnitTesting;
using System;
using System.IO;
using System.Security.Cryptography;
using System.Text;
using StG;

namespace StGTest
{
    [TestClass]
    public class TestDataProcessor
    {
        [TestMethod]
        public void TestSanity()
        {
            Assert.IsTrue(true);
        }

        [TestMethod]
        public void TestCompress()
        {
            Byte[] dataBytes = File.ReadAllBytes("..\\..\\..\\files\\message.txt");
            Byte[] compressedDataBytes = DataProcessor.Compress(dataBytes);
            Assert.IsTrue(compressedDataBytes.Length < dataBytes.Length);
        }

        [TestMethod]
        public void TestDecompress()
        {
            Byte[] dataBytes = File.ReadAllBytes("..\\..\\..\\files\\message.txt");
            Byte[] compressedDataBytes = DataProcessor.Compress(dataBytes);
            Byte[] resultBytes = DataProcessor.Decompress(compressedDataBytes);
            Assert.AreEqual(dataBytes.Length, resultBytes.Length);

            Random random = new Random();
            int randomIdx = random.Next(0, dataBytes.Length);
            Assert.AreEqual(dataBytes[randomIdx], resultBytes[randomIdx]);
        }

        [TestMethod]
        public void TestEncrypt()
        {
            Byte[] data = Encoding.UTF8.GetBytes("A very secret message");
            Byte[] password = Encoding.UTF8.GetBytes("Reliable_32_byte_key_for_AES-256");
            AESBridge.Mode mode = AESBridge.Mode.AES256;
            Byte[] encryptedData = DataProcessor.Encrypt(data, password, mode);
            MD5 md5 = MD5.Create();
            string hashData = BitConverter.ToString(md5.ComputeHash(data));
            string hashEncryptedData = BitConverter.ToString(md5.ComputeHash(encryptedData));
            Assert.AreNotEqual(hashData, hashEncryptedData);
        }

        [TestMethod]
        public void TestDecrypt()
        {
            Byte[] data = Encoding.UTF8.GetBytes("A very secret message");
            Byte[] password = Encoding.UTF8.GetBytes("Reliable_32_byte_key_for_AES-256");
            AESBridge.Mode mode = AESBridge.Mode.AES256;
            Byte[] encryptedData = DataProcessor.Encrypt(data, password, mode);
            Byte[] resultData = DataProcessor.Decrypt(encryptedData, password, mode);
            MD5 md5 = MD5.Create();
            string hashData = BitConverter.ToString(md5.ComputeHash(data));
            string hashResultData = BitConverter.ToString(md5.ComputeHash(resultData));
            Assert.AreEqual(hashData, hashResultData);
        }
    }
}
