.\protoc.exe .\proto_defines\*.proto --cpp_out=./
python.exe .\remove_strings_and_debug_from_protos.py