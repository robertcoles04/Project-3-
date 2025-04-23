# How to Run this Program from the Command Line:
## On MacOS
After downloading this repository and unzipping it, navigate to the projects root directory, named Song-Finder-main.

**Run this command to compile:**<br>
g++ src/main.cpp src/Song.cpp -o songFinder

**Run this command to run the compiled code:**<br>
./songFinder

## On Windows
After downloading this repository and unzipping it, navigate to the projects root directory, named Song-Finder-main.

**Run this command to compile:**<br>
g++ src/main.cpp src/Song.cpp -o songFinder.exe

**Run this command to run the compiled code:**<br>
songFinder.exe

# How to Run this Program in CLion
Download this repository and open it in CLion<br>
Be sure to load the cmake build. Project Wizard should pop up automatically with the options for the build. Keep all of the defaults and press OK.<br>
**If Project Wizard did not pop up and the cmake build did not load:**<br>
Right click on the Song-Finder-main folder and click "Reload CMake Project"
<img width="600" alt="image" src="https://github.com/user-attachments/assets/549e9e3e-5d92-4ec6-8863-07d1b91a8746" />

**Next, ensure that the working directory is set to be the root directory of the project, Song-Finder-main**<br>
In the top right, press "Main" and then "Edit Configurations"
<img width="600" alt="image" src="https://github.com/user-attachments/assets/5b938587-03b1-46f6-86f6-0a15ac95ee79" />

In the "Working directory:" field, enter the path to the projects root directory and press OK.
<img width="600" alt="image" src="https://github.com/user-attachments/assets/f95c84bc-04ce-465f-bbc1-2fded01d9e28" />

Now press run to run the program.

# What the Program Does:

The program finds songs from a dataset that meet your specifications. It asks for release year, duration, and popularity. Then the program asks you which of these attributes you would like to sort by. The attribute that you choose here determines which songs are output. If you choose releaseDate, then songs that have the release year that you asked for will appear. If you choose duration, songs that have the duration that you asked for will appear, and the same goes for popularity. If you choose to sort by all, then songs that are most closely related to all of the specifications that you chose will appear.

The dataset of songs is sorted using merge sort and quick sort according to the attribute that you choose. So when songs are output, there are two lists. One is the result of sorting with merge sort and the other is the result of sorting by quick sort. Additionally, the time taken by each sorting algorithm is output after the list of songs, so you can see how the two compare to each other.



