# Keylogger using libc(glibc) and linux kernel userspace libraries.

Keylogger is a free software licensed under the [GPLv2](https://www.gnu.org/licenses/old-licenses/gpl-2.0.html) license.

## Disclaimer:
This project is here and has been created just for study purposes. I or anybody who might contribute to this project bear absolutely no responsibility for the misuse any piece of code written here.

----

## Project Structure
    .
    ├── include
    │   ├── keylogger.h
    │   └── util.h
    ├── keys
    │   └── keyfile.txt
    ├── LICENSE
    ├── makefile
    ├── README.md
    ├── src
    │   ├── keylogger.c
    │   └── util.c
    └── test
        ├── keys
        │   └── keyfile.txt
        └── test_find.c

5 directories, 10 files


-----

## Instructions
- Written for a computer that runs a linux based OS(Eg Debian GNU/Linux).
- Find your global keylogger by looking for the keyword 'kdb'
    ```sh
        ls -l /dev/input/by-path | grep "kbd" | awk '{print $NF}';
    ```
-----

## Build and Run
```bash
	make
	sudo ./build/main kbdeventfile
```

Write on any window you choose and see that the keys are being logged.

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

    /* Fresh key press */
    struct input_event ev_press = {
        .type  = EV_KEY,
        .code  = KEY_X,   /* or BTN_X for buttons */
        .value = 1        /* 1 = key down (press) */
    };

    /* Press duplication / repeated press event */
    struct input_event ev_repeat = {
        .type  = EV_KEY,
        .code  = KEY_X,   /* same key/button code */
        .value = 2        /* 2 = autorepeat (key repeat) */
    };
```

----- 

## Inspiration and Thanks
[Daniel Hirsch] (https://www.youtube.com/@HirschDaniel)

-----

## Improvments under consideration.
- [ ] UNIX TCP sockets to send all the data to a remote server in real time.
