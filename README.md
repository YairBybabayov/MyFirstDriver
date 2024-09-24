
# 🎉 My First Windows Driver: Beep Control! 🎉

## 🚀 Overview
Welcome to my very first Windows driver project! This program communicates directly with the **Beep Device** using **Windows NT kernel-level APIs**. Yes, you read that right—this isn't your everyday beep. We're going deep into the system and manually controlling the sound using **device drivers**. Get ready for some awesome kernel-level magic! 😎

## 🖥️ What Does It Do?
This project opens a handle to the **Beep Device** (`\Device\Beep`), and using **low-level system functions**, sends a command to the device to produce a **beep at 800 Hz for 3 seconds**. Before the magic happens, the program displays a message box that gives you the option to brace yourself for the sound or cancel the operation.

Imagine the power—you control the beep at its core. 🎶🔊

## 📜 Features
- **Kernel Interaction**: Direct communication with the Windows NT Kernel's Beep device.
- **User Prompt**: A handy message box that warns you before the beep (with an option to cancel if you're not ready!).
- **Customizable Sound**: Modify the frequency and duration to your liking. Ever wanted a beep that lasts for 10 seconds at 1000 Hz? You can do it!
  
## 💻 How It Works
The magic behind this project lies in how we interact with the **Windows NT kernel** using some powerful functions like `NtOpenFile` and `DeviceIoControl`. Here's a breakdown of the action:
1. **Opening the Beep Device**: We use `NtOpenFile` to grab a handle to the `\Device\Beep` device.
2. **User Confirmation**: We show a message box with "OK" or "Cancel". If you hit "OK," get ready to hear the sound of awesomeness.
3. **Beep Command**: The program sends a **BEEP_SET_PARAMETERS** structure via `DeviceIoControl` to make the beep happen. Customize it by adjusting the frequency and duration.
4. **Handle Closure**: Once the beep is done, the device handle is closed, and everything is neatly wrapped up.

## 📚 Code Breakdown
```c
// Beep Device Access
HANDLE hDevice;
UNICODE_STRING devName;
RtlInitUnicodeString(&devName, DD_BEEP_DEVICE_NAME_U);

// Device Attributes Setup
OBJECT_ATTRIBUTES devAttr;
InitializeObjectAttributes(&devAttr, &devName, 0, NULL, NULL);

// Open Handle to Beep Device
IO_STATUS_BLOCK ioStatus;
NTSTATUS status = NtOpenFile(&hDevice, GENERIC_WRITE, &devAttr, &ioStatus, 0, 0);

// If successful, show the prompt and beep!
if (status == 0) {
    MessageBoxW(NULL, L"Get Ready For The Beep", L"driver test", MB_OKCANCEL | MB_ICONEXCLAMATION);

    BEEP_SET_PARAMETERS note;
    note.Frequency = 800;
    note.Duration = 3000;

    DWORD ret;
    DeviceIoControl(hDevice, IOCTL_BEEP_SET, &note, sizeof(note), NULL, 0, &ret, NULL);

    CloseHandle(hDevice);
}
```

## 🔧 Build Instructions
To build and run this project on **Windows**, follow these steps:

1. Clone the repository (or download the files):
   ```bash
   git clone <your-repo-url>
   ```
2. Open your favorite C++ IDE (I recommend **Visual Studio**).
3. Build the project, ensuring you link against **ntdll.dll** for the kernel functions:
   ```c
   #pragma comment(lib, "ntdll")
   ```
4. Run the executable and prepare to experience the power of **driver programming**.

## 🤯 Next Steps
Want to extend this project? Here are some fun ideas:
- Change the beep frequency and duration dynamically based on user input!
- Explore more **DeviceIoControl** commands and control other devices!
- Integrate this into a bigger project that interacts with multiple system drivers!

## 🎉 Conclusion
This project marks the beginning of my journey into **driver development**. From controlling the system beep to exploring the depths of the Windows kernel, the possibilities are endless. Let this beep be the first of many!

Let’s make some noise, the right way! 💻🔊
