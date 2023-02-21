# awsl
Tiny command-line calculator - 轻量级命令行计算器

* Only support `double`, and maybe overflow.

## Build & Install

```
make
sudo make install
```

## Demo

> Syntax detail is in [syntax.ebnf](syntax.ebnf)

```
$ awsl '1+1'
2.000000

$ awsl 'pow(2, 10)'
1024.000000

$ awsl 'pow(sin(233), 2) + pow(cos(233), 2)'
1.000000

$awsl 'log(pow(2, 666))/log(2)'
666.000000
```