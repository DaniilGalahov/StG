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
        const string PASSWORD = "People are like water - they will always find a way.";

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
            Byte[] data = File.ReadAllBytes("..\\..\\..\\files\\message.txt");
            Byte[] password = Encoding.UTF8.GetBytes(PASSWORD);
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
            Byte[] data = File.ReadAllBytes("..\\..\\..\\files\\message.txt");
            Byte[] password = Encoding.UTF8.GetBytes(PASSWORD);
            AESBridge.Mode mode = AESBridge.Mode.AES256;
            Byte[] encryptedData = DataProcessor.Encrypt(data, password, mode);
            Byte[] resultData = DataProcessor.Decrypt(encryptedData, password, mode);
            MD5 md5 = MD5.Create();
            string hashData = BitConverter.ToString(md5.ComputeHash(data));
            string hashResultData = BitConverter.ToString(md5.ComputeHash(resultData));
            Assert.AreEqual(hashData, hashResultData);
        }

        [TestMethod]
        public void TestEmbed()
        {
            Byte[] dataBytes = File.ReadAllBytes("..\\..\\..\\files\\message.txt");
            Byte[] carrierImageBytes = File.ReadAllBytes("..\\..\\..\\files\\input.png");
            Byte[] passwordBytes = Encoding.UTF8.GetBytes(PASSWORD);
            Byte[] stegoImageBytes = DataProcessor.Embed(dataBytes, carrierImageBytes, passwordBytes);
            Byte[] expectedBytes = File.ReadAllBytes("..\\..\\..\\files\\output.png");
            Assert.AreEqual(expectedBytes.Length, stegoImageBytes.Length);
            Random random = new Random();
            int randomIdx = random.Next(0, expectedBytes.Length);
            Assert.AreEqual(expectedBytes[randomIdx], stegoImageBytes[randomIdx]);
        }

        [TestMethod]
        public void TestExtract()
        {
            Byte[] stegoImageBytes = File.ReadAllBytes("..\\..\\..\\files\\output.png");
            Byte[] passwordBytes = Encoding.UTF8.GetBytes(PASSWORD);
            Byte[] dataBytes = DataProcessor.Extract(stegoImageBytes, passwordBytes);
            Byte[] expectedBytes = File.ReadAllBytes("..\\..\\..\\files\\message.txt");
            Assert.AreEqual(expectedBytes.Length, dataBytes.Length);
            Random random = new Random();
            int randomIdx = random.Next(0, expectedBytes.Length);
            Assert.AreEqual(expectedBytes[randomIdx], dataBytes[randomIdx]);
        }
    }
}
