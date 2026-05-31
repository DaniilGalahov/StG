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

Principle of this method is in mixing of data-to-hide with data of picture utilizing smart math. Imagine you adding a salt to a water. It dissolves and become invisible, but it is still there. And you can extract it, if you, for example, evaporate water. This is what steganography does with data.

If you salted your water properly (i.e., not too hard), it's very difficult to determine (by eye) that it contains something else. Even more difficult to detect the presence of salt if you are adding it not to a pure water, but to a rich soup with vegetables, meat, spices and so on. Same way steganography hides the data in carrier. If amount of data to hide is not too big, it's extremely difficult to detect that an image carries something else.

Modern special steganalysis systems are able to detect *probability* of presence of hidden data in an image. Same way we can say "Salty!" if we try the soup. But we can not say *why* it's salty (because of salt or, for example, because of soy sauce).

To reduce possibility of such detection, **StG** app uses advanced methods of steganography. In a nutshell, the app analyzes carrier picture, determines zones where data hiding will be less visible, and hides data only there. Additionally, during hiding the app shuffles data in pseudo-random way, making it looks like a noise. Developing analogy with a soup, we each time inventing flavouring additive, perfectly matching natural taste of this specific soup.

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

This tab allows to embed data to carrier image.

- **Data file** field - displays (and allows to input) path to file with data you want to *embed*.
- **Carrier image file** field - displays (and allows to input) path to file of carrier image *into which you want to embed* data.
- **Password** field - allows to input your password (at least 8 symbols, with least one capital letter, one digit and one special symbol).
- **Encryption mode** combo box - displays selected AES mode and allows to select other available (*AES-128*, *AES-192* or *AES-256*).
- **Stego image file** field - displays (and allows to input) path to file of stego image (which is the *result of embedding operation*).
- **Embed** button - initialize embedding operation. Before embedding, system validates all parameters. If something is wrong, system will output a report in "Status" field in the lower left corner of the window.

*If data volume is too big for this carrier, system will report status "StGLib::Embed failed." In this case choose bigger carrier image.*

##### "Extract" tab

![User interface - extract](/images/GUI_Extract.png)

- **Stego image file** field - displays (and allows to input) path to file of stego image, which contains *encrypted data to extract*.
- **Password** field - allows to input your password (at least 8 symbols, with least one capital letter, one digit and one special symbol).
- **Encryption mode** combo box - displays selected AES mode and allows to select other available (*AES-128*, *AES-192* or *AES-256*).
- **Data file** field - displays (and allows to input) path to file with data (which is the *result of extracting operation*).
- **Extract** button - initialize extract operation. Before extracting, system validates all parameters. If something is wrong, system will output a report in "Status" field in the lower left corner of the window.

In fields **Data file**, **Carrier image file** and **Stego image file** of both tabs you can type the path to appropriate files by yourself or select it via GUI dialogue through *"Browse"* button near the end of the field.

*Notice: system does not touch any info in source files (read-only access), and does not allow to overwrite destination files.*

---
<a id="StG_development"></a>
### StG Framework

#### Purpose
This library provides open-source, fully-tested (code coverage by tests ~95%) implementation of advanced steganography with AES encryption for .png image files. Feel free to use it in your own projects (of course, following [License](/License.md) terms).

#### Requirements
- Windows-based OS (Developed on Win 10)
- [Visual Studio Community](https://visualstudio.microsoft.com/vs/community/) 2022 Version 17.14.33 (May 2026)
	- Microsoft.Component.MSBuild
	- Visual C++ 2022 (package ***"Desktop development with C++"*** in VS Installer)
		- Microsoft.VisualStudio.Component.VC.Redist.14.Latest
		- Microsoft.VisualStudio.Component.VC.CLI.Support
	- C# Tools 4.14.0 (package   in VS Installer)
		- Microsoft.Net.Component.4.8.SDK
		- Microsoft.Net.Component.4.8.TargetingPack
- [OpenCV 4.12.0](https://github.com/opencv/opencv/releases/download/4.12.0/opencv-4.12.0-windows.exe)
- [Rijndael AESLib](https://github.com/DaniilGalahov/Rijndael-AESLib)

#### IDE/SDK configuration
For installation of all required components you need to open **Visual Studio Installer -> Workloads**, and install next packages:
- ***Desktop development with C++***
- ***.NET desktop development***

After this, you need to open **Visual Studio Installer -> Individual components**, and there install next components:
- ***.NET Framework 4.8 SDK***
- ***.NET Framework 4.8 targeting pack***
- ***C++/CLI support for v143 build tools (Latest)***

#### Deployment
- Deploy OpenCV
	- Download [OpenCV 4.12.0](https://github.com/opencv/opencv/releases/download/4.12.0/opencv-4.12.0-windows.exe).
	- Extract it into `C:\opencv`.
	- Add the bin directory of your OpenCV installation (e.g., `C:\opencv\build\x64\vc16\bin`) to your *system* `Path` [variable](https://en.wikipedia.org/wiki/PATH_(variable)#DOS,_OS/2,_and_Windows).
- Prepare folder structure
	- Create root folder of the project.
	- Inside this folder, create subfolders `AES` and `STG`.
- Clone Rijndael AESLib repo to `AES` folder using:
`git clone https://github.com/DaniilGalahov/Rijndael-AESLib.git`
- Clone this repo to `StG` folder using:
`git clone https://github.com/DaniilGalahov/StG.git`
- Open it in Visual Studio
- Rebuild solution (typically *Ctrl+Alt+F7*)

Now you are ready to work.

#### Contents
This repository provides:
- Static C++ library **StGLib**, implementing core steganography functional (embedding and extracting with adaptive embedding and randomized selection)
- C++/CLI interface **StGBridge**, providing access to StGLib functional from C#-based apps
- C ABI **StGABI**, providing access to StGLib functional from any managed language (Java, Python, Rust, TypeScript, you name it)

#### Connecting to third-party project
Library made to be versalite and easy for usage, so to connect it to other project, you should follow standard library integration procedure.

**To use in C++ project:**
- add StGLib and AESLib in list of projects of your solution through *Add... -> Existing project...*.
- add references to StGLib and AESLib in project *References*.
- in your project settings, open *C/C++ -> General -> Additional Include Directories*, and add there:
	- include directory of StGLib (your `StG\StGLib`).
	- include directory of Rijndael AESLib (your `AES\AESLib`).
	- include directory of OpenCV (`C:\opencv\build\include`).

**To use in C# project:**
- add StGBridge in list of projects of your solution through *Add... -> Existing project...*.
- add reference to StGBridge in your project.

**To use with other programming languages**, follow the standard library integration procedure for selected language. For example, in Python you can use [ctypes](https://docs.python.org/3/library/ctypes.html) library.

#### Coding

##### C++
1. Include `std::vector` (you will need it for work with library) and library header itself
``` c++
#include <vector>
#include "StGLib.h"
```

2. Define helper functions
```
std::vector<uint8_t> LoadBytesFromFile(std::string filePath)
{
	//reads data from file (via ifstream or any other way) and converts it into array of bytes
}

std::vector<uint8_t> ToBytes(std::string str)
{
	//converts std::string into array of bytes
}
```

3. To embed data
``` c++
	std::vector<uint8_t> carrierImageBytes = LoadBytesFromFile(carrierFilePath); //load carrier image file as an array of bytes
	std::vector<uint8_t> dataBytes = LoadBytesFromFile(dataFilePath); //load data file as an array of bytes
	std::vector<uint8_t> passwordBytes = ToBytes(password); //converts password string into array of bytes
	std::vector<uint8_t> stegoImageBytes; //prepare array of bytes for stego image
	int result = StGLib::Embed(stegoImageBytes, carrierImageBytes, dataBytes, passwordBytes); //embed data to carrier using password as a salt for embedding
```
**Note:** `StGLib::Embed()` will return `-1` in case if carrier has not enough volume for given data. 

4. To extract data
``` c++
	std::vector<uint8_t> stegoImageBytes = LoadFromFile(stegoFilePath);
	std::vector<uint8_t> passwordBytes = ToBytes(password);
	std::vector<uint8_t> dataBytes;
	int result = StGLib::Extract(dataBytes, stegoImageBytes, passwordBytes);
```

##### C#
1. Use `System` and `StGBridge`
``` c#
using System;
using StGBridge;
```

2. To embed data
``` c#
	Byte[] dataBytes = File.ReadAllBytes(dataFilePath); //read everything from data file into array of bytes
	Byte[] carrierBytes = File.ReadAllBytes(carrierFilePath); //read everything from carrier image file into array of bytes
	Byte[] passwordBytes = Encoding.UTF8.GetBytes(password); //converting password string into array of bytes
	try
	{
		Byte[] stegoBytes = StGBridge.StG.Embed(carrierBytes, dataBytes, passwordBytes); //embedding data to carrier
	}
	catch (Exception ex)
	{
		//system will throw exception in case if carrier has not enough volume for given data
	}
```
3. To extract data
``` c#
	Byte[] stegoBytes = File.ReadAllBytes(stegoFilePath);
	Byte[] passwordBytes = Encoding.UTF8.GetBytes(password);
	Byte[] dataBytes = StGBridge.StG.Extract(stegoBytes, passwordBytes);
```