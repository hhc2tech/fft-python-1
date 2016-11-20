clear;

[A] = importdata([pwd '/../output/test256.txt']);

srf = surf(A);

set(srf, 'LineStyle', 'none');

xlabel('Frequency');
ylabel('Time');
zlabel('Amplitude');
