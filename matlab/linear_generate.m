clear;

t = 0:0.001:2;
x = chirp(t, 0, 1, 200, 'linear');
plot(x);

fileID = fopen([pwd '/../data/linear.txt'], 'w');

fprintf(fileID, '%12.8f ', x);
fclose(fileID);
