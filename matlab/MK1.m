[y, Fs] = audioread('/Users/fifteen/dev/dsp/fft-python/data/signal.mp3');

z = y(:,1);

txt_file = fopen('/Users/fifteen/dev/dsp/fft-python/data/signal.txt', 'w');

fprintf(txt_file, '%12.8f ', z);
fclose(txt_file);
