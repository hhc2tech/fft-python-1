clear;

[A] = importdata([pwd '/../output/audio_64.txt']);

srf = surf(A);

set(srf, 'LineStyle', 'none');

xlabel('Frequency');
ylabel('Time');
zlabel('Amplitude');
