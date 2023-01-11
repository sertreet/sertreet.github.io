---
layout: post
title: Python调用C代码
tags: Linux
---

在windows上测试，首先把文件.c转换成.dll或者.so文件

下面是C语言的代码，里面包含一个foo函数：
```c
#include<stdio.h> 
int foo()
{ 
	int i,k,m;
	for(i=0;i<1000;i++)
	{
		for(k=0;k<1000;k++)
		{ 
			for(m=0;m<1000;m++);
		} 
	}
	return 0;  
}
```

将C语言代码保存为.c文件。在当前目录下进入cmd。（前提是有mingw环境）执行命令`gcc -o foo.so -shared -fPIC foo.c`转化为.so文件，`gcc foo.c -shared -o foo.dll`转化为.dll文件。

编写Python测试代码：
```python
from ctypes import cdll
from time import time

#.c-->.so
start=time()
dll=cdll.LoadLibrary('./foo.so')
dll.foo()
print(f'c,so:{time()-start}')

#.c-->.dll
start=time()
dll=cdll.LoadLibrary('./foo.dll')
dll.foo()
print(f'c,dll:{time()-start}')

#Python
start=time()
for i in  range(1000):
    for k in range(1000):
        for m in range(1000):
            pass
print(f'python:{time()-start}')
```

运行后的结果：

>c,so:1.3424348831176758  
>c,dll:1.3364272117614746  
>python:25.8764865398407  

可以看到；so、dll文件都可在windows环境下供python使用。并且可以看到上述Demo中，C的速度比Python快近20倍。
Python+C混合编程这种方式，原因主要有几点：
>1、提高性能，弥补了python性能上的不足。  
>2、相对安全，对dll文件或so文件进行加密，有效防止逆解析保证代码安全。  
>3、结合Python强大的生态环境，也满足了高效快速的开发。  