#stuff

from sys import argv
from collections import Counter
from operator import itemgetter
import xlwt


print "Enter run textfile here: "
file1 = raw_input("> ")
#file1 = "a1.txt"

# FIRST RUN LOGCAT FILE
with open(file1) as f:
    content1 = f.readlines()

final1 = [x for x in content1 if "I/org.umd.logging" in x]

def is_int(s):
    try:
        int(s)
        return True
    except ValueError:
        return False

def remove_beg(s):
    s = s[26:]
    if (s[0] == "M"):
        done = False
        s = s[9:]
        while (not done):
            #s = s[1:]
            if (is_int(s[0]) or  s[0] == " "):
                s = s[1:]
            else:
                done = True
    if(s[0] == "A"):
        done = False
        s = s[5:]
        while (not done):
            if (is_int(s[0]) or  s[0] == " "):
                s = s[1:]
            else:
                done = True
    return s

final1 = [remove_beg(s) for s in final1]

method1 = [x for x in final1 if "Method" in x]
api1 = [x for x in final1 if "Api" in x]


#print "Enter second run here: "
#file2 = raw_input("> ")
#file2 = "a2.txt"

# SECOND RUN LOGCAT FILE
#with open(file2) as f:
#    content2 = f.readlines()

#final2 = [x for x in content2 if "I/org.umd.logging" in x]

def remove_intro(s):
    return s[26:]

#final2 = [remove_intro(s) for s in final2]

#method2 = [x[:-1] for x in final2 if "Method" in x]
#api2 = [x[:-1] for x in final2 if "Api" in x]

# TOTAL LOGFILE LIST
print "Enter file with total logged methods here: "
logFile = raw_input("> ")
#logFile = "a3.txt"

with open(logFile) as f:
    total = f.readlines()

for i, x in enumerate(total):
    s = x[:-1]
    total[i] = s

def remove_left(s):
    num = len(ss) - len(s)
    return ss[num:]

# ANALYZE DATA
for j, s1 in enumerate(total):
    for i, item in enumerate(final1):
        if item.find(s1) != -1:
            final1[i] = total[j]
        #print 'found!'
        else:
            final1[i] = item

#for j, s1 in enumerate(total):
#    for i, item in enumerate(final2):
#        if item.find(s1) != -1:
#            final2[i] = total[j]
#        #print 'found!'
#        else:
#            final2[i] = item



#print "Run 1: "
c1 = Counter(final1)
sorted(c1.items(), key=itemgetter(0))

#print "Run 2: "
#c2 = Counter(final2)
#sorted(c2.items(), key=itemgetter(0))


# Create Excel file
book = xlwt.Workbook(encoding="utf-8")
sheet1 = book.add_sheet("Sheet 1")

print ("Enter # run you are analyzing: ")
runNum = raw_input(" >")
print("Enter name of data analysis file here: ")
excFile = raw_input("> ")
#excFile = "out.xls"

excName = excFile + "-" + runNum + ".xls"

i = 0

for key, value in c1.items():
    sheet1.write(i, 0, key)
    sheet1.write(i, 1, value)
    i = i+1

#i = 0

#for key, value in c2.items():
#    sheet1.write(i, 2, key)
#    sheet1.write(i, 3, value)
#    i = i+1

book.save(excName)





