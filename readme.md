# Newton's Iteration to Solve System of Non-linear Equations

NewtonNB stands for Newton Niu Bi!

## MATLAB Inside

The programs calls **MATLAB runtime** to perform high-precision matrix manipulation, which is basically the core of solving system of non-linear equations.

## Before it all works, you'll need to:

1. Download and install [MATLAB runtime](https://ww2.mathworks.cn/products/compiler/matlab-runtime.html "MATLAB runtime China mirror") (only if you haven't installed MATLAB on your computer)(remember to add MATLAB to your `PATH`) (or you can choose to install MATLAB on your computer)

2. Download and install Visual Studio(only if you haven't installed Visual Studio on your computer)

3. Open the `NewtonNB.sln` file in the working directory

4. Select 64bit platform(debug or release? whatever)

5. In `project property`, `C/C++`, change `Additional Include Directory` to your own MATLAB include directory(which should be like: `D:\MATLAB\R2019b\extern\include`)

6. In `project property`, `Linker`,change `Additional Library Directory` to your own MATLAB library directory(which should be like: `D:\MATLAB\R2019b\extern\lib\win64\microsoft`)

7. Add MATLAB bin to your PATH(if you haven't done that already)(thet should be like: `D:\MATLAB\R2019b\bin` and `D:\MATLAB\R2019b\runtime\win64`)

8. Press `F5`(or `Ctrl+F5`) and enjoy

