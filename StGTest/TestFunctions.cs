using Microsoft.VisualStudio.TestTools.UnitTesting;
using System;
using System.IO;
using System.Security.Cryptography;
using System.Text;
using StG;

namespace StGTest
{
    [TestClass]
    public class TestFunctions
    {
        const string DATA_FILE_PATH = "..\\..\\..\\files\\data.txt";
        const string CARRIER_FILE_PATH = "..\\..\\..\\files\\carrier.png";
        const string STEGO_FILE_PATH = "..\\..\\..\\files\\stego.png";

        const int EMBEDDING_BLOCK_SIZE = 2; //2 for small pictures (128x128), 8 for generic photos
        const double EMBEDDING_TRESHOLD = 0.35; //for test purposes only! Use at least 0.5 for practical applications

        const string PASSWORD = "People are like water - they will always find a way.";

        [TestMethod]
        public void TestSanity()
        {
            Assert.IsTrue(true);
        }

        [TestMethod]
        public void TestCompress()
        {
            Byte[] dataBytes = File.ReadAllBytes(DATA_FILE_PATH);
            Byte[] compressedDataBytes = Functions.Compress(dataBytes);
            Assert.IsTrue(compressedDataBytes.Length < dataBytes.Length);
        }

        [TestMethod]
        public void TestDecompress()
        {
            Byte[] dataBytes = File.ReadAllBytes(DATA_FILE_PATH);
            Byte[] compressedDataBytes = Functions.Compress(dataBytes);
            Byte[] resultBytes = Functions.Decompress(compressedDataBytes);
            Assert.AreEqual(dataBytes.Length, resultBytes.Length);
            Random random = new Random();
            int randomIdx = random.Next(0, dataBytes.Length);
            Assert.AreEqual(dataBytes[randomIdx], resultBytes[randomIdx]);
        }

        [TestMethod]
        public void TestEncrypt()
        {
            Byte[] data = File.ReadAllBytes(DATA_FILE_PATH);
            Byte[] password = Encoding.UTF8.GetBytes(PASSWORD);
            AESBridge.Mode mode = AESBridge.Mode.AES256;
            Byte[] encryptedData = Functions.Encrypt(data, password, mode);
            MD5 md5 = MD5.Create();
            string hashData = BitConverter.ToString(md5.ComputeHash(data));
            string hashEncryptedData = BitConverter.ToString(md5.ComputeHash(encryptedData));
            Assert.AreNotEqual(hashData, hashEncryptedData);
        }

        [TestMethod]
        public void TestDecrypt()
        {
            Byte[] data = File.ReadAllBytes(DATA_FILE_PATH);
            Byte[] password = Encoding.UTF8.GetBytes(PASSWORD);
            AESBridge.Mode mode = AESBridge.Mode.AES256;
            Byte[] encryptedData = Functions.Encrypt(data, password, mode);
            Byte[] resultData = Functions.Decrypt(encryptedData, password, mode);
            MD5 md5 = MD5.Create();
            string hashData = BitConverter.ToString(md5.ComputeHash(data));
            string hashResultData = BitConverter.ToString(md5.ComputeHash(resultData));
            Assert.AreEqual(hashData, hashResultData);
        }

        [TestMethod]
        public void TestEmbed()
        {
            Byte[] dataBytes = File.ReadAllBytes(DATA_FILE_PATH);
            Byte[] carrierImageBytes = File.ReadAllBytes(CARRIER_FILE_PATH);
            Byte[] passwordBytes = Encoding.UTF8.GetBytes(PASSWORD);
            Byte[] stegoImageBytes = Functions.Embed(dataBytes, carrierImageBytes, passwordBytes, EMBEDDING_BLOCK_SIZE, EMBEDDING_TRESHOLD);
            Byte[] expectedBytes = File.ReadAllBytes(STEGO_FILE_PATH);
            Assert.AreEqual(expectedBytes.Length, stegoImageBytes.Length);
            Random random = new Random();
            int randomIdx = random.Next(0, expectedBytes.Length);
            Assert.AreEqual(expectedBytes[randomIdx], stegoImageBytes[randomIdx]);
        }

        [TestMethod]
        public void TestExtract()
        {
            Byte[] stegoImageBytes = File.ReadAllBytes(STEGO_FILE_PATH);
            Byte[] passwordBytes = Encoding.UTF8.GetBytes(PASSWORD);
            Byte[] dataBytes = Functions.Extract(stegoImageBytes, passwordBytes, EMBEDDING_BLOCK_SIZE, EMBEDDING_TRESHOLD);
            Byte[] expectedBytes = File.ReadAllBytes(DATA_FILE_PATH);
            Assert.AreEqual(expectedBytes.Length, dataBytes.Length);
            Random random = new Random();
            int randomIdx = random.Next(0, expectedBytes.Length);
            Assert.AreEqual(expectedBytes[randomIdx], dataBytes[randomIdx]);
        }
    }
}
