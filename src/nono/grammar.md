# Grammar for Buster's assembly
A program in Buster's assembly consists of a list of statements:

```
program -> stmt program | ϵ
```

With `ε` representing the empty string. Statements are produced with the following production:

```
stmt -> (IDENTIFIER ':')? (noop | imm | ident)
```

There are so three different kinds of statements: `noop` statements that requires no operand, `imm` statements that require an immediate value as operand and `ident` statements that require an identifier as operand. On top of this each statement can be marked with in identifier by prefixing it with `id:` where `id` is a valid identifier.

```
noop  -> HALT | ADD | SUB | AND | OR | XOR | DROP | DUP | OVER | SWAP | STORE | FETCH | EXIT
imm   -> LIT NUMBER
ident -> (IF | CALL) IDENTIFIER
```

`NUMBER` here is a 8-bit number in hexadecimal notation prefixed by `0x` like `0xFF` or `0x1E`. `IDENTIFIER` is any string of alphanumeric characters that does not start with `0` and that is not the name of an instruction such as `HALT` and `SWAP`.

Comments start with `;` and last till the end of the line.
