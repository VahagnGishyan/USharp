
import sys
from os import walk
import pathlib

sys.path.insert(0, '..\..')
from translator.meta.tunits            import tunits
from translator.input                  import args
from settings.version                  import version
from translator.output                 import output
from translator.translation.meta.using import using_dll
from translator.translation.structure  import smain
from translator.translation.structure  import snamespace

##################### Translate #####################

#temp func
#def get_file_path() -> str:
#    filenames = next(walk(temp.get_folder_path_input()), (None, None, []))[2]
#    return str(temp.get_folder_path_input() + str(filenames[0]))

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
            message = using_dll.call_using(words[1]) + "\n"
            #new_file.write(str(message))
        elif word == "namespace":
            message = snamespace.call_namespace(words) + "\n"
            #new_file.write(str(message))
        elif word == "main":
            message = smain.call_main(words) + "\n"
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
    
    new_filepath = output.get_new_filepath(filepath) # output file name
    new_file     = open(new_filepath, 'w')    # output file object
    new_content  = list()                     # output file content

    #Console message
    print("Start translation()")
    translation_message = "Translate to {0:s} from {1:s}".format(version.tr_to_lang, version.tr_from_lang)
    print("Version :: {0:s}".format(version.version));
    print(translation_message + '\n')
    #Translation file message
    output.add_comment(new_content, translation_message)
    new_content.append("\n")

    remove_endl(content)
    translate_file(content, new_content, new_file)
    
    new_file.write(''.join(new_content)) # save in new file
    new_file.close()
    
#####################################################

####################### Main ########################

def main():
    print("Start main()!\n")    

    #single
    filepath = args.check()
    if filepath == "":
        print("invalid args")
        return
    
    # lexical analysis ???
    translate(str(filepath))

    print("Close main()!")

if __name__ == "__main__":
    main()

##################################################### 


# TODO
# modules-namespaces ????
# input.main(argv)
# input.file-files
# output.file-files
# output, file, files, to cpp ?
# modul::metadata for translation
# modul::translation














