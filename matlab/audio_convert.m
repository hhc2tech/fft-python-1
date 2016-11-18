clear;

[y, Fs] = audioread([pwd '/../data/audio.mp3']);

z = y(:, 1);

txt_file = fopen([pwd '/../data/audio.txt'], 'w');

fprintf(txt_file, '%12.8f ', z);
fclose(txt_file);
