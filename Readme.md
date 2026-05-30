# StG

![StG logo](/images/Logo.png)

## Summary
This repository includes:
- **StG** - simple steganography application, allows to encrypt/decrypt and embed/extract data to/from images, utilizing AES encryption and advanced steganography algorithms.
- **StGLib** - C++ OpenCV-based implementation of +/-1 LSB steganography algorithm with adaptive embedding and randomized selection.
- **StGBridge** - C++/CLI interface library for usage StGLib in C#-based apps.
- **StGABI** - C ABI .dll for usage StGLib with any managed language (Python, Java, Rust, Go, whatever you need).

## Usage
This section separated to two subsections - usage of [StG app](#StG_usage) and development with [StG framework](#StG_development).

---
<a id="StG_usage"></a>
### StG

#### Purpose
This app provides advanced steganography functions, especially:
- encrypt data with AES and embed encrypted data into `.png` image.
- extract encrypted data from `.png` image and decrypt it with AES.

For AES ciphering the app is using software from [this repository](https://github.com/DaniilGalahov/Rijndael-AESLib).

#### In simple words
This app allows to hide data into `.png` image and then extract it from there utilizing method names *steganography*. 

Principle of this method is in mixing of data to hide with data of picture utilizing smart math. Imagine you adding a salt to a water. It dissolves and become invisible, but it is still there. And you can extract it, if you, for example, evaporate water. This is what steganography does with data.

If you "salted" your "water" properly (i.e., not too hard), it's very difficult to determine that your water contains something else. Same way steganography hides the data in carrier. If amount of data to hide is not too big, it's extremely difficult to detect that an image carry something else.

Modern special steganalysis systems are able to detect *probability* of presence of steganographed data in an image. To reduce possibility of such detection, **StG** app uses advanced methods of steganography. In a nutshell, the app analyzes carrier picture, determines zones where data hiding will be less visible, and hides data only there. Additionally, during hiding the app shuffles data in pseudo-random way, making it looks like a noise.

Beside this **StG** provides additional level of protection. Before embedding, it encrypts data with AES encryption system (most advanced encryption standard in the world). This way, even if the attacker will detect the presence of steganographed data, he will not be able to decrypt it - without a password it is just a random noise. There is no methods to decipher AES.

#### Important notices
1. Data-to-carrier ratio for typical pictures is about 1.5%. I.e., **picture size of 1Mb can contains roughly 15kb of hidden data**.
2. Best choice for carrier pictures - **colorful and natural pictures with enough details**. Real photos with cosy interiors or beautiful landscapes will be the best option.
3. **WARNING!!!** "Under the hood" **StG** contains **military grade** encrypting system. If you forget (or lost) the password, **NO ONE** will be able to decrypt your information! Brute-force time for deciphering AES-256 (even using quantum computers!) exceeds time of heat death of Universe.

#### Specifications
- **Available encryption standards:** AES-128, AES-192, AES-256
- **Steganography method:** +/-1 LSB, adaptive embedding, randomized selection
- **Carrier format:** .png
- **D/C ratio:** 0.015

#### Download
Latest version of StG app can be downloaded [here](https://github.com/DaniilGalahov/StG/releases)

#### User interface
User interface of the app allows to: 
- choose the operation
- set up data file, carrier image file and stego image file paths and parameters of encrypting/decrypting
- initialize operation
- receive feedback from the app

##### "Embed" tab

![User interface - embed](/images/GUI_Embed.png)

- **Data file** field - displays (and allows to input) path to file with data you want to *embed*.
- **Carrier image file** field - displays (and allows to input) path to file of carrier image *into which you want to embed* data.
- **Password** field - allows to input your password (at least 8 symbols, with least one capital letter, one digit and one special symbol).
- **Encryption mode** combo box - displays selected AES mode and allows to select other available (*AES-128*, *AES-192* or *AES-256*).
- **Stego image file** field - displays (and allows to input) path to file of stego image (which is the *result of embedding operation*).

##### "Extract" tab

![User interface - extract](/images/GUI_Extact.png)

- **Stego image file** field - displays (and allows to input) path to file of stego image, which contains *encrypted data to extract*.
- **Password** field - allows to input your password (at least 8 symbols, with least one capital letter, one digit and one special symbol).
- **Encryption mode** combo box - displays selected AES mode and allows to select other available (*AES-128*, *AES-192* or *AES-256*).
- **Data file** field - displays (and allows to input) path to file with data (which is the *result of extracting operation*).

In fields **Data file**, **Carrier image file** and **Stego image file** you can type the path to appropriate files by yourself or select it via GUI dialogue through *"Browse"* button near the end of the field.

*Notice: system does not touch any info in source files (read-only access), and does not allow to overwrite destination files.*

---
<a id="StG_development"></a>
### StG Framework