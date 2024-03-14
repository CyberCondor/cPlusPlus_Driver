# cPlusPlus_Driver
<sub><sup>Custom C++ libraries to showcase dynamic memory allocation using circular linked lists.</sup></sub><br>

Import CSV Files into Objects

This main looks for csv files in the runtime arguments. For csv files found in argument list, it imports the csv as a matrix object into a circular linked list of objects. Correlations are made between the csv file data property values and all other csv files. Then this main displays objects identified during object import based on the data in the csv files found in arguments during runtime.

e.g.,
```shell
make
./main *.csv
```
```shell
./main ../path/to/csv/*.csv
```
```shell
./main ./path/to/csv/file.csv
```
```shell
make csv
```
```shell
make run
```

# Main
```c++
#include "main.h"

int main(int argc, char **argv, char **envp)
{
    Objects CSVs;                           // Init Main Object of Objects to hold information from CSVs

    List list;                              // Init list to hold argument values
    for(auto idx = 0; idx < argc; idx++)    // For the Argument Count 
    {                                       // Put the parameterized arguments into an organized list
        Element buffer(argv[idx]);          // Using the Element Constructor to copy argv into Element
        list.insert(buffer);                // And the Sorted Insertion Mutator to insert the Element into the list
    }

    CSVs.importCSVs(list);                  // Import CSVs into objects
    CSVs.print();                           // Display the objects

    return 0;
}
```

#
#
---

<img align="left" width="320px" alt="RuntimeScreenshot" src="https://github.com/CyberCondor/_media/blob/main/Driver_RuntimeScreenshot1.png" /> 
<img width="365px" alt="RuntimeScreenshot" src="https://github.com/CyberCondor/_media/blob/main/Driver_RuntimeScreenshot2.png" /> 

---
#
#
---
# Dependencies

<img width="1080px" alt="Dependencies" src="https://github.com/CyberCondor/_media/blob/main/Driver_Dependencies.png" /> <br>

---
#
#

<details>
	<summary><h3>👁‍🗨 Special Thanks To:</h3></summary>
    <sub><sup>Thank you for teaching C++ with a focus on memory management!</sup></sub><br>
	- <sub><sup>Doug Jones - Computer Science 2</sup></sub><br>
	- <sub><sup>The Cherno - youtube[.]com/@TheCherno</sup></sub><br>
	- <sub><sup>Low Level Learning - youtube[.]com/@LowLevelLearning</sup></sub><br>
</details>
