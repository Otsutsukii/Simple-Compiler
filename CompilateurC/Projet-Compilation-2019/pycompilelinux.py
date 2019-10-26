import subprocess
import os
subprocess.Popen(["lex", "lex1.l"]).wait()
subprocess.Popen(["yacc", "-d","yacc1.y"]).wait()
subprocess.Popen(["gcc", "-o", "executable", "y.tab.c" ,"lex.yy.c"]).wait()
for name in os.listdir("Tests"):
    
    if name[-1] == "c":
        print(name)
        subprocess.Popen(["./executable" ,"./"+"Tests/"+name]).wait()
        subprocess.Popen(["dot", "-Tpdf", "file.dot", "-o" ,"pdfs/"+name[:-2]+".pdf"]).wait()
