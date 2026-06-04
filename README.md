# cpp_fun_utilities
Experimenting with c++

The IterInt is an int wrapper that supports digit access (read and write) by index while preserving normal int type behaviour.
For example, if we have IterInt a = 12345; we can do a[0]; //1 a[3] //4. Negative indexing is also supported. a[-1] //wraps around to 5
Digits can also be modified. a[3] = 9 //modifies a to 12395. Negative indexing is supported.

Full arithmetic (+,-,*,/) and (+=,-=,*=,/=) support between:
1. IterInt and IterInt
2. IterInt and int
3. int and IterInt

Prohibits division by zero (does nothing if detected to avoid crash), but no additional overflow underflow guards.
In short, this is convenient to use when digit level access and arithmetics are simultaneously necessary, for instance when writing simulation code for cows & bulls type code breaking games, while saving you headache from converting frequently between strings and ints, which is inelegant and lousy.
