import os

def my_function(path,in_folder):
    for filename in os.listdir(path):
        if(filename.startswith('DSH')):
            if(filename.lower().endswith('.ogg')):
                filename = filename[:-4]
            in_folder.append(filename.lower()[2:])
    return in_folder

f = open("Lua/horns.lua", "r")
in_lua = []
for line in f:
    stuff = line.split("\"")
    if(len(stuff) > 1):
        in_lua.append(stuff[1][4:])
in_folder = my_function('Sounds',[])
in_folder = my_function('Sounds/hell',in_folder)
print("Sounds not included in horns.lua:")
print(list(set(in_folder) - set(in_lua)))
print("Sounds included in horns.lua, but not found in the files:")
print(list(set(in_lua) - set(in_folder)))


