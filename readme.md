## WSL + GCC 11.4.0 + Make

**WSL**

```
WSL version: 2.4.10.0
```

**GCC**

```
gcc (Ubuntu 11.4.0-1ubuntu1~22.04) 11.4.0
Copyright (C) 2021 Free Software Foundation, Inc.
This is free software; see the source for copying conditions. There is NO
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
```

**Make**

```
GNU Make 4.3
Built for x86_64-pc-linux-gnu
Copyright (C) 1988-2020 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
```

### How to run

```
make run
```

Make might show some warning about Clock skew detected. I don't know how to deal with it, but based on my observations, it shouldn't affect the code (i think).

```
make: warning:  Clock skew detected.  Your build may be incomplete.
```
