# wait-exe

**Simple Wait Application**

This small C program provides a simple wait/sleep function, designed for use with **DataSpammer** or other scripts.
Since `cmd.exe` doesn’t support sleeping in **milliseconds**, this tool fills that gap.

### 🛠️ Compile with GCC:

```cmd
gcc -Os -s -o wait.exe wait.c \
    -ffunction-sections \
    -fdata-sections \
    -Wl,--gc-sections \
    -fno-ident \
    -fomit-frame-pointer \
    -flto
```

### ▶️ Usage:

```cmd
wait.exe <value>
```

Each value represents **0.5 seconds** of delay:

* `wait.exe 1` → waits **0.5 seconds**
* `wait.exe 2` → waits **1 second**
* `wait.exe 3` → waits **1.5 seconds**
* `wait.exe 4` → waits **2 seconds**
