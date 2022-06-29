
import sys
from os import walk
import pathlib

from os import listdir
from os.path import isfile, join

######################################################
###################### MetaData ###################### 
###### MataData about translation units, tunits ######
######################################################

######################## Path ########################

def get_work_path():
    currentFilePath = (str)(pathlib.Path(__file__).parent.resolve())
    return str(currentFilePath
               .rsplit('\\', 1)[0]
               .rsplit('\\', 1)[0]
               .rsplit('\\', 1)[0] + "\\")

def get_input_folder_path():
    return str(get_work_path() + "input\\")

def get_output_folder_path():
    return str(get_work_path() + "output\\")

def get_settings_folder_path():
    return str(get_work_path() + "settings\\")

def get_srcs_folder_path(): # folder translator
    return str(get_work_path() + "translator\\")

#################### input folder ####################

def get_input_folder_file_name_list():
    filepath = get_input_folder_path()
    print("tusints.get_input_folder_file_name_list() \nfilepath[{0:s}]".format(filepath))
    return list([f for f in listdir(filepath) if isfile(join(filepath, f))])

######################################################



























