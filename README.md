# About
This project is maze generator which uses "Recursive backtracker" algorithm written in C++17. User interface has been
made with wxWidgets version 3.1.3 with GTK+3 [Linux installation guide](https://wiki.codelite.org/pmwiki.php/Main/WxWidgets31Binaries#toc2)

# Generation examples

![GenerationEX1](/img/gen_1000_10.gif)  
Settings used: 1000 blocks and 10 ms sleep.


![GenerationEX2](/img/gen_4900_0.gif)  
Settings used: 4900 blocks and 0 ms sleep.

# Usage
After building and starting the project you will see following window:
![First view](/img/usage1.png)

Change attributes to your liking and click "Initialize maze".
After that blocks are generated and you should see something like the following picture
![Ready to generate](/img/usage2.png)

Now you can just click "Launch generation" and generation will run to end and show the generated maze.
![Generated maze](/img/usage3.png)

# Dependencies
This project depends on:  
    wxWidgets version 3.1.3

# License and copyright

Licensed under the [GNU GPLv3 License](LICENSE).
