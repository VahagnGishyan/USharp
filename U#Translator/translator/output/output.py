
import sys

sys.path.insert(0, 'D:\\Projects\\U#Leng\\U#Translator\\translator\\meta\\tunits\\')
import tunits

def get_new_filepath(filepath :str) -> str:
    return str(tunits.get_output_folder_path() + "\\new_" + filepath.rsplit('\\', 1)[1])

def add_comment(new_content :list, message :str):
    new_content.append("/*{0:s}*/".format(message))

