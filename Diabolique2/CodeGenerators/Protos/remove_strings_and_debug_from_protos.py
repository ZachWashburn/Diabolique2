import os
import shutil
FILE_NAME = "WrappedCode"

class StringWrapper:
    def __init__(self, file, out_file, open_statement):
        self.file = file
        self.file_object = open(file, "r", encoding="utf8")
        self.file_out_outobject = open(out_file + ".tmp", "w", encoding="utf8")
        self.open_statement = open_statement
        self.out_name = out_file

    def parse_line(self, line, QuoteOpened):
        delimiter = "\""
        index = line.find(delimiter)

        if index == -1 or line[0] == "#":
            self.file_out_outobject.write(line)
            return QuoteOpened

        while index != -1:
            #print(line)
            if index != 0 and (line[index-1] == "\\" or (not QuoteOpened and line[index-1] == "'")): #escaped character
                str_to_now = line[0:index+1]
                self.file_out_outobject.write(str_to_now)
            elif QuoteOpened:
                str_to_now = line[0:index+1]
                str_to_now += ")"
                self.file_out_outobject.write(str_to_now)
                QuoteOpened = False
            else:
                str_to_delm = line[0:index+1]
                str_to_delm = str_to_delm[:-1]
                str_to_delm += self.open_statement + "(\""
                self.file_out_outobject.write(str_to_delm)
                QuoteOpened = True

            line = line[index+1:]
            #print(line)
            index = line.find(delimiter)

            if index == -1:
                self.file_out_outobject.write(line)
                break



    def wrap_strings(self):
        QuoteOpened = False
        self.file_out_outobject.write("#include <XOR_STR.h>\n")
        for line in self.file_object.readlines():
            QuoteOpened = self.parse_line(line, QuoteOpened)
        self.file_out_outobject.close()
        self.remove_debug_info()

    def remove_debug_info(self):
        cleansed_final = open(self.out_name + ".tmp", "r", encoding="utf8")
        out_final = open(self.out_name, "w", encoding="utf8")
        NextLineStringInfo = False
        for line in cleansed_final.readlines():
            if NextLineStringInfo:
                out_final.write("#if defined(_DEBUG) || defined(SERVER) || defined(SERVER_CLIENT)\n")
                out_final.write(line)
                out_final.write("#else\n")
                out_final.write('  return XorStr("did_you_think_i_would_leave_this_here_auto_code_gen_ftw! nerds");\n')
                out_final.write('#endif\n')
                NextLineStringInfo = False
                continue


            if line.find("GetTypeName()") != -1 and line.find('{') != -1:
                NextLineStringInfo = True

            out_final.write(line)
        out_final.close()




def is_source_file(ext):
    if ext == ".cc":
        return True
    if ext == ".c":
        return True
    if ext == ".cpp":
        return True
    if ext == ".h":
        return True
    if ext == ".hpp":
        return True
    if ext == ".hh":
        return True
    return False

#lol = StringWrapper(".\\CSGO_Patterns.cpp", "XorStr")
#lol.wrap_strings()



try:
    os.mkdir(FILE_NAME)
except:
    pass

for root, dirs, files in os.walk("proto_defines"):
    path = root.split(os.sep)
    #print((len(path) - 1) * '---', os.path.basename(root))
    for file in files:

        current_root = FILE_NAME
        for dir in path:
            try:
                os.mkdir(current_root + "/" + dir)
            except:
                pass
            current_root += "/" + dir
        current_root
        #print(path)
        #print(file)
        split_tup = os.path.splitext(file)
        ext = split_tup[1]

        if not is_source_file(ext):
            #shutil.copy2('/'.join(path) + "/" + file, current_root + "/" + file)
            pass
        else:
            print("Converting file {}".format(file))
            #print('/'.join(path))
            #print(current_root + "/" + file)
            lol = StringWrapper('/'.join(path) + "/" + file, current_root + "/" + file, "XorStr")
            lol.wrap_strings()


        #print(len(path) * '---', file)


