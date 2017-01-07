# Non-Deterministic Replay of Mobile Apps
## Redexer
Clone the Redexer repo from [here](https://github.com/plum-umd/redexer).
Follow the instructions on the page carefully to ensure you install all packages necessary.
### Logging
To add logging capabilities to methods/apis of an app, follow the instructions below:
- Pull the apk for the desired application
- Move the apk to the redexer repo folder
- To add logging to the apk:
  ```
  $ ruby ./scripts/cmd.rb com.yourapp.apk --cmd logging
  ```  
- The modified logged apk will now be in the results folder

## List of Methods/APIs
The C++ file LogData.cpp can be found in the Log-Compare_Methods folder:
```
$ ./Log.o 
Reading total logging file...
File name (logfile) > yourapp-logfile.txt
Reading logcat output file...
File name (logcat) > yourapp-r1.txt

Output file name (.csv) > yourapp-list.csv 
Output file name (.txt) > yourapp-list.txt
Total logged: 55
```
The resulting files are a list of all of the methods/apis logged by redexer.

## Run Comparisons
Move to the Log-Compare_Methods folder.
This will analyze/compare the logcat from a single run, to determine which methods were called and how many times:
```
$ python logcat-compare.py 
Enter run textfile here: 
> 2048-r1.txt
Enter file with total logged methods here: 
> 2048-list.txt
Enter # run you are analyzing: 
> 1
Enter name of data analysis file here: 
> 2048-compare
```

