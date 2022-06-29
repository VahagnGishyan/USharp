
def call_using(libName):
    return ("#include <" + libName[5:len(libName)-1] + ">")


