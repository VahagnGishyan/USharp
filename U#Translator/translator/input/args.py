
import sys
sys.path.insert(0, 'D:\\Projects\\U#Leng\\U#Translator\\translator\\rules\\modes\\')
import modes

sys.path.insert(0, 'D:\\Projects\\U#Leng\\U#Translator\\translator\\meta\\tunits\\')
import tunits

#def open_init_file():
#    return open()

def check_input_folder():
    return (tunits.get_input_folder_file_name_list())
     

def check():
    argv = sys.argv
    argc = int(len(argv))

    filelist = list()

    if(argc == 1):
        print("Argument count is {0:d}".format(argc)) 
        filelist = check_input_folder()
        print("filelist.count = {0:d}".format(len(filelist)))
        if(len(filelist) == 1):
            filename = filelist[0]
            filepath = tunits.get_input_folder_path() + filelist[0]
            print("filename = {0:s}".format(filename))
            print("filepath = {0:s}".format(filepath))
            return (str(filepath))
        else:
            print(filelist)
    return ""
    #elif argv[1][1] == '#=
    # ...
    
        
