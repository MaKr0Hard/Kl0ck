# Kl0ck
Just watch your time fade away...


I split this code in two parts : 
- Making a usable clock
- Making it Windows 1.0 like
so you will find ```//old``` comments (I know, I am new to git...)

If you want to use some tools for your project, just add them, I made the whole thing modular, just respect the order

To build :
- Use the ```CMakeLists.txt``` file (raylib needed)
- build with ```gcc kl0ck.c -o kl0ck -lraylib -lGL -lm -lpthread -ldl -lrt -lX11``` (if you are in the src directory)
  or with ```gcc src/kl0ck.c -o build/kl0ck -lraylib -lGL -lm -lpthread -ldl -lrt -lX11``` (if you are at the root of the project)

