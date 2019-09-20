# Buster
Buster is a simple generic virtual stack machine (loosely based on the information available [here](https://users.ece.cmu.edu/~koopman/stack_computers/sec3_2.html)) wrote out of boredom (and some desire to understand something new).

## Building and testing
Buster does not depend on any external library, you'll just need `g++` and the C++ standard library to compile it. The following will compile tests, run them and, if all tests passed successfully, compile the `buster` and `nono` executables:

```
make
```

If you don't want to run the tests you'll have to modify the `Makefile` yourself (I quite like compiling the binary only if all the tests passes but whatever).

## Running Buster
Calling `./build/buster file` will load `file` in Buster's memory and then execute it. Of course `file` needs to be a Buster executable; the `examples` directory contains some pre-made executables, however running them will not be super satisfactory.

```
./build/buster examples/sum
The machine halted!
```

Since Buster does not have any I/O device the only way to see that something is actually going on inside Buster is to run it in debug mode.

```
./build/buster --debug examples/sum
```

Debug mode runs one instruction at a time and, after each instruction has been executed displays the current value of the program counter and all the elements in the stack. For extra debugging you can also set some memory cells "on watch": passing the option `--watch AA12` will also print the content of the memory cell `AA12` after each instruction (you can pass more than one `--watch` to watch on multiple memory cells).

## Details on Buster
Buster is an 8-bit cpu but indexes memory via 16-bits addresses (and thus access to 64K of RAM). It has a total of 15 instructions (encoded with 8-bit opcodes) explained in the following table (please read "pop" as "pop ... from the stack" and "push" as "push ... to the stack").

| Mnemonic | Opcode | Description |
| -------- | ------ | ----------- |
| HALT     | 0x00   | Halt the machine. |
| ADD      | 0x10   | Pop two elements, add them together and push the result. |
| SUB      | 0x11   | Pop two elements, subtract the second one from the first and push the result. |
| AND      | 0x12   | Pop two elements, perform bitwise and between them and push the result. |
| OR       | 0x13   | Pop two elements, perform bitwise or between them and push the result. |
| XOR      | 0x14   | Pop two elements, perform bitwise xor between them and push the result. |
| DROP     | 0x20   | Pop one element. |
| DUP      | 0x21   | Pop one element and push it twice. |
| OVER     | 0x22   | Push a copy of the second element of the stack. |
| SWAP     | 0x23   | Pop two elements and push them so that their original order is now inverted. |
| STORE    | 0x30   | Pop three elements. Store the third one at memory location pointed to by the first two (the first one will be the high nibble of the address and the second one the lower nibble). |
| FETCH    | 0x31   | Pop two elements. Push the value stored in the memory location pointed to by the two elements. |
| LIT      | 0x40   | Push the byte that follows this instruction. |
| IF       | 0x50   | Pop one element. Jump to the location pointed to by the two bytes that follow this instruction if the popped element is zero. |
| CALL     | 0x60   | Push the current program counter to the stack (first the lower nibble, then the higher one) and then jump to the instruction pointed to by the two bytes that follow the instruction. |
| EXIT     | 0x61   | Pop two elements and jump to the instruction pointed to by the two bytes. |

If an unknown opcode in encountered then an `HALT` instruction is executed.

The only two registers that Buster has are the program counter `pc` that point to the next instruction to be executed and the stack pointer `sp` that point to a memory cell immediately next the current first element of the stack. The stack pointer is initialized to `0xFFFF` and grows downwards (so if we push three elements it now points to `0xFFFC`), the program counter is initialized at `0x0000`. When a program is loaded it's contents are loaded in memory starting from `0x0000`, each memory cell is always initialized to `0x0000`.

Currently the only way to write programs for buster is to fire up an hex editor and write down all the opcodes manually (not anymore: see next section). As a reference this is the content of `examples/sum`, visualized through `xxd`:

```
00000000: 40f1 4001 1000                           @.@...
```

Indeed `examples/sum` just sums `0xf1` and `0x01` and leaves the result on the stack.

## Using Nono, an assembler for Buster
Nono is an assembler for a simple assembly language. You can find a simple sketch of the formal grammar for it by reading [grammar.md](./src/nono/grammar.md) or you can read "real life" examples in the `examples` directory (check out the files with the `.buster` extension). The general use of Nono is:

```
./build/nono/nono source_file.buster > buster_executable
```

I'm super lazy so Nono does not write to files by itself but rather dump machine code to stdout that you can redirect to a file using your shell (I'm assuming a POSIX `sh` derivative here). As a further example this is how you would go to write, assemble and execute the program above that sums `0xF1` and `0x01` and leaves the result on Buster's stack:

```
$ cat > sum.buster
LIT 0xF1
LIT 0x01
ADD
HALT
$ ./build/nono/nono sum.buster > sum
$ ./build/buster sum
The machine halted!
```
