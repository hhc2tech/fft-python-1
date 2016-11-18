clear;

[A] = importdata([pwd '/../output/audio_256.txt']);

srf = surf(A);

set(srf, 'LineStyle', 'none');

xlabel('Frequency');
ylabel('Time');
zlabel('Amplitude');
