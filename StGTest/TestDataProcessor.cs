using Microsoft.VisualStudio.TestTools.UnitTesting;
using System;
using System.IO;
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
    }
}
