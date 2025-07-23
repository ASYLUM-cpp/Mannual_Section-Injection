# Manual Section Injection – PE Shellcode Lab 🔬

This was a small but insightful lab where I manually injected shellcode into a PE (Portable Executable) file by adding a new section. The goal was to:

- Inject shellcode into the PE file
- Redirect execution flow from the Original Entry Point (OEP) to the injected shellcode
- Restore the original state and return execution back to the OEP — making it look like nothing ever happened

---

## 🧩 Lab Walkthrough

### 🧪 Step 1: Creating the Target PE

- I wrote a simple `main.cpp` and compiled it to generate `main.exe`.
- Using **x32dbg**, I loaded `main.exe`, found the Entry Point (EP), and noted its address.
- Initially, I looked for a **code cave** to inject shellcode, but it was **not large enough** to hold the payload.

---

### 🧱 Step 2: Adding a New Section

Since the code cave wasn't sufficient, I had to **manually add a new section** using tools like:

- **CFF Explorer**
- **PE Editor**
- **Hex Workstation**

#### Key steps:
- Located the PE header using the magic bytes `50 45` ("PE").
- Appended empty bytes to the end of the PE to act as space for the new section.
- Noted the starting address and size of the newly added memory region.
- Modified the **section header table** to define the new section.
- Updated the PE header to reflect:
  - Increased number of sections (`offset 0x06`)
  - Updated image size (`offset 0x50`)
  - New section characteristics

#### Section Table Entry:

| Offset | Description |
|--------|-------------|
| +00    | Section Name |
| +08    | Virtual Size (Code Cave size) |
| +0C    | Virtual Address |
| +10    | Size of Raw Data |
| +14    | Pointer to Raw Data |
| +18–+22| Leave empty (Relocations & Line Numbers) |
| +24    | Characteristics (e.g., `0xE0000020` → RWX perms) |

---

### 🧠 Example Calculations:

- Number of Sections: Changed from `0D` → `0E`
- Image Size at offset `0x50`: Changed from `0x00011000` → `0x00012000` (aligned to `0x1000`)

---

## 🛠 Shellcode Handling

- Used **x32dbg** again to view the new section in memory.
- Pushed `AD` and `FD` flags to preserve the original CPU state before shellcode execution.
- Injected shellcode and restored CPU state afterward.
- Jumped back to the original Entry Point (OEP).

---

## ⚠️ Challenges Faced

1. **Insufficient Code Cave**:  
   The offsets included dynamic stack values and weren’t usable, so a new section was required.

2. **Shellcode Corruption**:  
   The shellcode accessed an uninitialized EAX register, leading to an exception.  
   I couldn’t fix it in time but plan to revisit this.

---

## 📚 Tools Used

- **CFF Explorer**
- **Hex Workstation**
- **x32dbg**
- **PE Editor**
- **Shellcode Generator (Metasploit Console)**

---

## 🚨 Disclaimer

This project is purely for **educational purposes**. It demonstrates low-level PE manipulation and reverse engineering, with the aim of understanding malware techniques and binary internals. Do **not** use this knowledge for malicious purposes.

---

## 📌 Future Improvements

- Add working shellcode (e.g., `MessageBox` or `calc.exe`) and record proper execution
- Automate section injection with a script
- Create a video or animation for LinkedIn

---

Thanks for reading! 🎯
