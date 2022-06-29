

import sys
from os import walk
import pathlib

##################### Meta Data ##################### 

def get_work_path():
    currentFilePath = (str)(pathlib.Path(__file__).parent.resolve())
    return str(currentFilePath.rsplit('\\', 1)[0].rsplit('\\', 1)[0] + "\\")

def get_folder_path_input():
    return str(get_work_path() + "input\\")

def get_folder_path_output():
    return str(get_work_path() + "output\\")

def get_folder_path_settings():
    return str(get_work_path() + "settings\\")

def get_folder_path_srcs(): # folder translator
    return str(get_work_path() + "translator\\")

#meta data
#translator project
#folder paths
md_fp_work           = get_work_path()
md_fp_input          = get_folder_path_input();
md_fp_output         = get_folder_path_output();
md_fp_settings       = get_folder_path_settings();
md_fp_srcs           = get_folder_path_srcs();

##################################################### 

##################### Settings ######################

tr_to_lang   = "C++" # translate to   language
tr_from_lang = "U#"  # translate from language

ver_major = 0
ver_minor = 0
ver_patch = 0

version = str("{0:d}.{1:d}.{2:d}".format(ver_major, ver_minor, ver_patch))

#class TranslationSettings(Enum):
#    TranslateFile,

    
#def set_checkSettings()
#    args = list(sys.argv)
#    #temp
#    if(arg[0] != "#"):
#        return TranslationSettings.TranslateFile
#    for arg in args:
#        if():
            
        

#####################################################
