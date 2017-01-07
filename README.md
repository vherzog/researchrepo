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

### List of Methods/APIs
The C++ file LogData.cpp can be found in the Log-Compare_Methods folder:
```
$./Log.o 
Reading total logging file...
File name (logfile) > yourapp-logfile.txt
Reading logcat output file...
File name (logcat) > yourapp-r1.txt

Output file name (.csv) > yourapp-list.csv 
Output file name (.txt) > yourapp-list.txt
Total logged: 55
```



