#pyhton script to write the header file called bootcode.h

import sys
import os
from io import FileIO

with open(sys.argv[1], "rb+") as infile:
    with open(sys.argv[2], "wb") as outfile:
        data = infile.read(1024);
        outfile.write("#include <windows.h>\r#define BYTES 65536\rconst unsigned char code[] = {\r")
        outfile.write(data);
        outfile.write("\r};\r\rconst size_t code_len = sizeof(code);\r\rDWORD wb;");
        outfile.close();
    infile.close();
