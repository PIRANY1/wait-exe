# wait-exe

**A minimal, feature-rich wait/sleep utility for the command line.**

![Windows Build](https://github.com/PIRANY1/wait-exe/actions/workflows/build-linux.yml/badge.svg)
![Linux Build](https://github.com/PIRANY1/wait-exe/actions/workflows/build-windows.yml/badge.svg)
![MacOS Build](https://github.com/PIRANY1/wait-exe/actions/workflows/build-macos.yml/badge.svg)

This small C program provides a flexible wait/sleep function, originally created as a `sleep` replacement for Windows `cmd.exe` or for scripting environments that lack precise timing control.

This enhanced version is designed for minimal file size while offering features not found in basic `sleep` commands:

  * Precise timing with units: **milliseconds (`ms`)**, **seconds (`s`)**, **minutes (`m`)**, and **hours (`h`)**.
  * An optional **silent mode** (`-s`) to suppress all output.
  * A **progress indicator** (`.`) that is displayed each second during long waits.


### 📦 Downloads

Precompiled binaries for all major platforms can be found in the [`bin/`](bin/) folder:

| Platform | Binary | SHA256 |
|----------|--------|--------|
| 🪟 Windows | [`wait.exe`](bin/wait.exe) | [`wait.exe.sha256`](bin/wait.exe.sha256) |
| 🐧 Linux   | [`wait`](bin/wait)         | [`wait.sha256`](bin/wait.sha256)         |
| 🍎 macOS   | [`wait-macos`](bin/wait-macos) | [`wait-macos.sha256`](bin/wait-macos.sha256) |

You can also compile from source using the instructions below.

### 🛠️ Compile with GCC:

These flags are highly recommended to achieve the smallest possible executable size.

```bash
gcc -o wait.exe wait.c -Os -s \
    -ffunction-sections \
    -fdata-sections \
    -Wl,--gc-sections \
    -fno-ident \
    -fomit-frame-pointer \
    -flto
```

### ▶️ Usage

#### Syntax

```
wait.exe [-s] <value>[unit]
```

#### Arguments

| Argument | Description | Required |
| :--- | :--- | :--- |
| `-s` | Enables **silent mode**. No progress dots will be printed to the console. This flag must come first. | No |
| `<value>` | A non-negative integer that specifies the duration of the wait. | Yes |
| `[unit]` | A suffix that specifies the time unit. If omitted, **seconds (`s`)** are used as the default. | No |

**Available units:**

  * `ms` - Milliseconds
  * `s`  - Seconds (**default**)
  * `m`  - Minutes
  * `h`  - Hours

#### Examples

  * **Wait for 5 seconds (default unit):**

    ```cmd
    wait.exe 5
    ```

    *(Output: .....)*

  * **Wait for 1.5 seconds (by using milliseconds):**

    ```cmd
    wait.exe 1500ms
    ```

    *(Output: .)*

  * **Wait for 1 minute silently (no progress dots):**

    ```cmd
    wait.exe -s 1m
    ```

    *(No output)*

  * **Wait for 10 seconds (explicit unit):**

    ```cmd
    wait.exe 10s
    ```

    *(Output: ..........)*

  * **Wait for half a second (500ms):**

    ```cmd
    wait.exe 500ms
    ```

    *(No output, as the duration is less than one second)*