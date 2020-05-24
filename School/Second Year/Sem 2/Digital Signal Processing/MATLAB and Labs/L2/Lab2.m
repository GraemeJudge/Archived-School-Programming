%lab 2

%Using your function, generate 512 samples of a 320 Hz sine wave with no phase offset,
%into a vector called s320.  Use a sampling rate of 2560 Hz

% N             - number of samples to take
% f             - frequency in hz
% scaler        - a scale value to be able to view only a portion of the wave
%                 to make analysis and overservations easier
% amplitude     - max height of the wave peak
% dc            - dc level of the signal
% sampleRate    - the frequency to sample at in hz

N = 512;
f = 60;
scaler = 1;
amplitude = 1;
dc = 0;
sampleRate = 2560;

[x, y] = Sinusoid(60,amplitude,sampleRate,N, scaler, dc);

hold on;
figure(1);
title('s320');
%stem(x, y);
plot(x, y);
hold off;




