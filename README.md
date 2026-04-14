# Keylogger using standard C libraries and Linux Input Event Logger files.

## Disclaimer:
This project is here and has been created just for study purposes. I bear absolutely no responsibility of the misuse any piece of code written here.

----

## Project Structure
    .
    ├── include
    ├── LICENSE
    ├── makefile
    ├── README.md
    └── src
        └── keylogger.c

3 directories, 5 files

-----

## Build and Run
```bash
	make
	sudo ./build/main kbdeventfile
```
-----

## Resources
[Linux Kernel Documentation on Input Events](https://kernel.org/doc/html/v6.0/input/event-codes.html)
Important inferences from the documentation
    Every hardware event creates multiple input events stored in a struct input_event.
    Event/Key codes can be found @/usr/include/linux/input-event-codes.h

    @/usr/include/linux/input.h
    ```c
    struct input_event {
        __u16   type;
        __u16   code;
        __u32   value;
    };
    ```

    struct input_event on a fresh key press { .type = EV_KEY, .value = 1, .code = KEY_X/BTN_X}
    struct input_event on press duplication { .type = EV_KEY, .value = 2, .code = KEY_X/BTN_X}

## Thanks
[Daniel Hirsch] (https://www.youtube.com/@HirschDaniel)

