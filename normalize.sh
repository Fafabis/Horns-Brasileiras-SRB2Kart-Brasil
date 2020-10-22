#!/bin/bash
cd Sounds
ffmpeg-normalize *.* -nt rms -t -9 -c:a libvorbis -b:a 112k -ext ogg -f
cd hell
ffmpeg-normalize *.* -nt rms -t -9 -c:a libvorbis -b:a 112k -ext ogg -f
cd ../..
echo Agora basta copiar os arquivos das pastas \"normalized\" sobre os arquivos originais
