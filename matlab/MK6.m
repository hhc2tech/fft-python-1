filename = 'CHIRP2_OUT.txt';
[A]=importdata(filename);
srf = surf(A);
set(srf, 'LineStyle','none');
xlabel('Frequency');
ylabel('Time');
zlabel('Amplitude');
