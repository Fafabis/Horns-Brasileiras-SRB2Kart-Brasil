import os
import ffmpeg

def my_function(path):
    if not os.path.exists(path + '/temp'):
        os.makedirs(path + '/temp')
    for filename in os.listdir(path):
        if(filename.startswith('DSH')):
            ffmpeg.input(path + '/' + filename).output(path + '/temp/' + filename, acodec='libvorbis', aq=3, format='ogg').run(overwrite_output=True)

my_function('Sounds')
my_function('Sounds/hell')
print("Done! Remember to copy the contents from the \"temp\" folders to the regular folders, and delete them afterwards")
