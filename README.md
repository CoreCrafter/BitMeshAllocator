# Bit Mesh Allocator
![](https://img.shields.io/badge/C-allocator-blue ) 

![](https://img.shields.io/badge/memory-defragmentation-8A2BE2)

An efficient allocator designed for large objects, optimized for O(1) allocation and deallocation, with no fragmentation issues.
## About project

This is my first project in C as a beginner. There are many concepts and materials that I still don’t fully understand, but I am doing my best. After studying computer science for about 8 to 9 months, I have realized that system programming is incredibly exciting, which motivated me to focus my efforts on it. For my first tool, I chose C because it is special; it provides a great deal of control over hardware.
A few days ago, I started learning C. Prior to this, I was working on a compiler for my programming language in Lisp. I found that memory management in C is more challenging than I initially thought. After further study, I learned about a concept called "fragmentation." When using malloc and free repeatedly, fragmentation can occur, leading to inefficiencies.
To address this issue, I decided to create a memory management system similar to malloc and free that minimizes memory fragmentation. This system can effectively handle large objects since the metadata for each object is approximately 40 bytes. However, for embedded systems, this approach may not be efficient enough, so I plan to develop another project specifically tailored for those systems soon. For now, my solution can be used on general-purpose computers without any problems.
 

## Compilation and Usage

I created a Makefile that can be customized for your own configurations. The default path for the output file is set to /bin, and your source code is located in src/main.c.

To compile the project, first navigate to the root directory and use the make command. :

```bash
cd BitMeshAllocator && make clean && make
```
To run the executable, navigate to the bin directory and execute:

```bash
cd bin && ./the_program
```

## Contributing
Pull requests are welcome. For major changes, please open an issue first
to discuss what you would like to change.

Please make sure to update tests as appropriate.

## License

[MIT](https://choosealicense.com/licenses/mit/)
