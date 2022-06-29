
def call_main(words):
    if words[1] == "auto":
       words[1] = "void"
    #umain
    arguments = "(int argc, char *argv[])"
    return str('\t' + words[1] + ' u' + words[0] + arguments)
