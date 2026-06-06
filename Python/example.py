#Example of usage StGABI.dll in Python (created with ChatGPT as co-programmer)
import os
import ctypes
from ctypes import CDLL, POINTER, c_uint8, c_size_t, c_int, c_double, c_void_p, byref, string_at

# Paths
os.add_dll_directory(r"C:\opencv\build\x64\vc16\bin")
dll_path = os.path.abspath(r"..\\x64\\Release\\StGABI.dll")

# Load the DLL
stgabi = CDLL(dll_path)

# Define function signatures
stgabi.Embed.argtypes = [
    POINTER(c_uint8), c_size_t,
    POINTER(c_uint8), c_size_t,
    POINTER(c_uint8), c_size_t,
    c_int, c_double,
    POINTER(POINTER(c_uint8)), POINTER(c_size_t)
]
stgabi.Embed.restype = c_int

stgabi.Extract.argtypes = [
    POINTER(c_uint8), c_size_t,
    POINTER(c_uint8), c_size_t,
    c_int, c_double,
    POINTER(POINTER(c_uint8)), POINTER(c_size_t)
]
stgabi.Extract.restype = c_int

stgabi.FreeMemory.argtypes = [c_void_p]
stgabi.FreeMemory.restype = None

embeddingBlockSize = 2 # 2 for small pictures (128x128), 8 for generic photos
embeddingTreshold = 0.35 # for test purposes only! Use at least 0.5 for practical applications

# Define helper functions
def read_bytes(path):
    with open(path, "rb") as f:
        return f.read()

def write_bytes(path, data):
    with open(path, "wb") as f:
        f.write(data)

def embed(data_path, carrier_path, password, stego_path):
    # Read file bytes
    carrier_bytes = read_bytes(carrier_path)
    data_bytes = read_bytes(data_path)

    # Prepare pointers
    carrier_ptr = (c_uint8 * len(carrier_bytes))(*carrier_bytes)
    data_ptr = (c_uint8 * len(data_bytes))(*data_bytes)
    password_ptr = (c_uint8 * len(password))(*password)

    stego_ptr = POINTER(c_uint8)()
    stego_size = c_size_t()

    # Call C ABI function
    res = stgabi.Embed(
        data_ptr, len(data_bytes),
        carrier_ptr, len(carrier_bytes),
        password_ptr, len(password),
        embeddingBlockSize, embeddingTreshold,
        byref(stego_ptr), byref(stego_size)
    )
    
    if res != 0:
        raise RuntimeError(f"Embed failed with code {res}")

    # Convert result to Python bytes
    stego_bytes = string_at(stego_ptr, stego_size.value)

    # Write bytes to stego
    write_bytes(stego_path, stego_bytes)

    # Free memory
    stgabi.FreeMemory(stego_ptr)

    print(f"Embedded data into {stego_path}")

def extract(stego_path, password, extracted_path):
    # Read file bytes
    stego_bytes = read_bytes(stego_path)

    # Prepare pointers
    stego_ptr = (c_uint8 * len(stego_bytes))(*stego_bytes)
    password_ptr = (c_uint8 * len(password))(*password)

    extracted_ptr = POINTER(c_uint8)()
    extracted_size = c_size_t()

    # Call C ABI function
    res = stgabi.Extract(
        stego_ptr, len(stego_bytes),
        password_ptr, len(password),
        embeddingBlockSize, embeddingTreshold,
        byref(extracted_ptr), byref(extracted_size)
    )

    if res != 0:
        raise RuntimeError(f"Extract failed with code {res}")

    # Convert result to Python bytes
    extracted_bytes = string_at(extracted_ptr, extracted_size.value)

    # Write bytes to result file
    write_bytes(extracted_path, extracted_bytes)

    # Free memory
    stgabi.FreeMemory(extracted_ptr)

    print(f"Extracted data to {extracted_path}")

# Example usage
files_dir = os.path.abspath(r"..\\files")
data_path = os.path.join(files_dir, "data.txt")
carrier_path = os.path.join(files_dir, "carrier.png")
stego_path = os.path.join(files_dir, "stego.png")
extracted_path = os.path.join(files_dir, "extracted.txt")

password = b"People are like water - they will always find a way."

embed(data_path, carrier_path, password, stego_path)

extract(stego_path, password, extracted_path)
