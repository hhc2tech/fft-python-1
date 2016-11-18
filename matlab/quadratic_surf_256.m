clear;

[A] = importdata([pwd '/../output/quadratic_64.txt']);

srf = surf(A);

set(srf, 'LineStyle', 'none');

xlabel('Frequency');
ylabel('Time');
zlabel('Amplitude');
