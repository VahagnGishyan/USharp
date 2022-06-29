
import sys
from os import walk
import pathlib
import temp

##################### Translate #####################

#temp func
def get_file_path() -> str:
    filenames = next(walk(temp.get_folder_path_input()), (None, None, []))[2]
    return str(temp.get_folder_path_input() + str(filenames[0]))

def get_file_content(filename : str) -> list:
    content = list()
    file = open(filename, 'r')
    for line in open(filename):
        content.append(line)
    file.close()
    return content
    
#def lexicalAnalysis(words :list): # words in line
#    for(word : words):
#        if(

def call_using(libName):
    return ("#include <" + libName[5:len(libName)-1] + ">")

def call_namespace(words):
    result = "namespace"
    for index in range(1, len(words)):
        result += ' ' + words[index] 
    return result

def call_main(words):
    if words[1] == "auto":
       words[1] = "void"
    #umain
    arguments = "(int argc, char *argv[])"
    return str('\t' + words[1] + ' u' + words[0] + arguments)

def get_new_filepath(filepath :str) -> str:
    return str(temp.get_folder_path_output() + "\\new_" + filepath.rsplit('\\', 1)[1])

def add_comment(new_content :list, message :str):
    new_content.append("/*{0:s}*/".format(message))

def remove_endl(content :list):
    for index in range(0, len(content)):
        content[index] = content[index].rsplit('\n', 1)[0]

def print_file_content(content :list):
    for line in content:
        print(line)
    
def translate_file(content :list, new_content :list, new_file):
    main_path = "";
    for line in content:
        if not line or line.isspace():
            message = '\n';
            new_content.append(message)
            continue
        
        words = line.split()
        word = words[0];
        
        if word == "using":
            message = call_using(words[1]) + "\n"
            #new_file.write(str(message))
        elif word == "namespace":
            message = call_namespace(words) + "\n"
            #new_file.write(str(message))
        elif word == "main":
            message = call_main(words) + "\n"
            #new_file.write(str(message))
            main_path = "Programm"
        elif word == "\n":
            message = line
        elif word == "{" or word == "}":
            message = line + "\n"
        else:
            notranslate = str("/*no_translate*/")
            message = line + notranslate + "\n"
            #new_file.write(str(message))
        new_content.append(str(message))
    if main_path != "":
        message = "\n"
        message += "int main(int argc, char *argv[])\n"
        message += "{\n"
        message += "\t" + main_path + "::umain(argc, argv);\n"
        message += "\treturn (0);\n"
        message += "}\n"
        message += "\n"
        new_content.append(str(message))
        

def translate(filepath :str):

    content      = list(get_file_content(filepath)) # input  file content
    
    new_filepath = get_new_filepath(filepath) # output file name
    new_file     = open(new_filepath, 'w')    # output file object
    new_content  = list()                     # output file content

    #Console message
    print("Start translation()")
    translation_message = "Translate to {0:s} from {1:s}".format(temp.tr_to_lang, temp.tr_from_lang)
    print("Version :: {0:s}".format(temp.version));
    print(translation_message + '\n')
    #Translation file message
    add_comment(new_content, translation_message)
    new_content.append("\n")

    remove_endl(content)
    translate_file(content, new_content, new_file)
    
    new_file.write(''.join(new_content)) # save in new file
    new_file.close()
    
#####################################################

####################### Main ########################

def main():
    print("Start main()!\n")    

    # lexical analysis ???
    translate(str(get_file_path()))

    print("Close main()!")

if __name__ == "__main__":
    main()

##################################################### 


# TODO
# modules-namespaces
# input,  file, files, states
# output, file, files, to cpp ?
# modul::metadata for translation
# modul::translation














