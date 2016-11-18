[A] = importdata('/Users/fifteen/dev/dsp/fft-python/data/1.txt');
srf = surf(A);

set(srf, 'LineStyle', 'none');
xlabel('Frequency');
ylabel('Time');
zlabel('Amplitude');
