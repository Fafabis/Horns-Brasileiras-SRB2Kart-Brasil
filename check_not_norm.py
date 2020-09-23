# Isso checa arquivos que o comando ffmpeg-normalize não conseguiu normalizar por algum motivo

import os

def my_function(path,in_folder):
    for filename in os.listdir(path):
        if(filename.startswith('DSH')):
            if(filename.lower().endswith('.ogg')):
                filename = filename[:-4]
            in_folder.append(filename.lower()[2:])
    return in_folder


in_folder = my_function('Sounds',[])
in_folder_hell = my_function('Sounds/hell',[])
in_folder_norm = my_function('Sounds/normalized',[])
in_folder_hell_norm = my_function('Sounds/hell/normalized',[])
print("Sounds not normalized:")
print(list(set(in_folder) - set(in_folder_norm)))
print("Hell sounds not normalized:")
print(list(set(in_folder_hell) - set(in_folder_hell_norm)))


