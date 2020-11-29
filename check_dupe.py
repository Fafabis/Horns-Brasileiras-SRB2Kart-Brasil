# Isso checa ids duplicados no .lua

import os


f = open("Lua/horns.lua", "r")
in_lua = []
line_num = 1
for line in f:
    stuff = line.split("\"")
    if(len(stuff) > 1):
        in_lua.append([stuff[1][4:],line,line_num,False])
    line_num += 1
for sound in in_lua:
    if not sound[3]:
        sound[3] = True
        for sound2 in in_lua:
            if sound[0] == sound2[0] and not sound2[3]:
                sound2[3] = True
                print("Duplicate found: ")
                print("Line " + str(sound[2]) + ": " + sound[1] + "Line " + str(sound2[2]) + ": " + sound2[1])
print("Tenha em mente que algumas duplicatas são apenas sons comuns entre horns normais e horns hell, e não são um problema. Porém, se um id duplicado for sons diferentes (ou seja, dois sons diferentes compartilham o mesmo id), aí sim temos um problema.")
